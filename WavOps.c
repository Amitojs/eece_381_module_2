/*
 * WavOps.c
 *
 *  Created on: Mar 6, 2013
 *      Author: Leslie
 */

#include <stdio.h>
#include "WavOps.h"
#include "interface_SD.h"
#include <stdlib.h>
#include <string.h>
#include "FileStructs.h"
#include <altera_up_avalon_audio.h>
#include <altera_up_sd_card_avalon_interface.h>
#include "altera_up_avalon_audio_and_video_config.h"
#include "system.h"


/*
 * Initializes the audio output interface and audio configuration.
 * Does not return a value.
 *
 */


void wavInit(void){
	audio_dev = alt_up_audio_open_dev (AUDIO_NAME);
	if ( audio_dev == NULL){
		return;
	}
	av_config = alt_up_av_config_open_dev(AUDIO_AND_VIDEO_CONFIG_NAME);
	while(!alt_up_av_config_read_ready(av_config));

	alt_up_audio_disable_read_interrupt(audio_dev);
	alt_up_audio_enable_write_interrupt(audio_dev);
	playStart = NULL;
	numSongs = 0;
	return;
}
/*
 * Initializes the list of notes for the piano and returns a pointer to an array of pointers to the notes.
 */
Wave** pianoInit(void){
	printf("Initializing Piano..");
	Wave** pianoArr = malloc(PIANO_NOTES*sizeof(Wave*));
	*pianoArr = isWav("c.wav");
	*(pianoArr+1) = isWav("cs.wav");
	printf(".");
	*(pianoArr+2) = isWav("d.wav");
	*(pianoArr+3) = isWav("ds.wav");
	printf(".");
	*(pianoArr+4) = isWav("e.wav");
	*(pianoArr+5) = isWav("f.wav");
	printf(".");
	*(pianoArr+6) = isWav("fs.wav");
	*(pianoArr+7) = isWav("g.wav");
	printf(".");
	*(pianoArr+8) = isWav("gs.wav");
	*(pianoArr+9) = isWav("a.wav");
	printf(".");
	*(pianoArr+10) = isWav("as.wav");
	*(pianoArr+11) = isWav("b.wav");
	printf("done!");
	int i;
	for(i=0; i<12; i++){
		pianoArr[i]->loop = true;
	}

	return pianoArr;

}

/*
 * Checks to see if the filename it takes exists and that it is a .wav file.
 * If it is, returns a pointer to a struct containing the file info
 * If it is not a .wav file or the file does not exist, the pointer is NULL.
 * The returned filedata and file must be deallocated with free.
 */
Wave* isWav(char* filename){
	char fileheader[WAV_OFFSET];
	char* fileheaderptr = &fileheader[0];
	if(file_read(fileheaderptr, filename, WAV_OFFSET)<0){
		return NULL;
	}
	if((fileheader[8] == 'W') && fileheader[9] == 'A' && fileheader [10] == 'V' && fileheader[11] == 'E');
	//else
	//	return NULL;
	Wave* File = malloc(sizeof(Wave));
	if(File == NULL) return NULL;
	File->datasize = (unsigned char)fileheader[40]+(unsigned char)fileheader[41]*256+(unsigned char)fileheader[42]*65536;
	File->channels = fileheader[22];
	File->samplerate = (unsigned char)fileheader[24]+(unsigned char)fileheader[25]*256+(unsigned char)fileheader[26]*65536;
	File->samplesize = fileheader[34];
	File->filename = filename;
	char* currentSong = malloc((File->datasize+WAV_OFFSET)*sizeof(char));
	file_read(currentSong, File->filename, File->datasize+WAV_OFFSET);
	File->songData = currentSong;
	return File;
}

/*
 * Returns the number of files with a .wav file extension as an integer.
 * If it returns 0, no wav files were found
 * If it returns a negative number, an error has occured
 * If there are more than 512 files on the SD card, returns the first 512 files found
 */

int getPlayable(void){

	char namearr[SONGS_MAX*13];
	int wavcnt = 0;
	char* namearrptr = &namearr[0];
	filenames_read(namearrptr, SONGS_MAX*13);
	namearrptr = strtok(namearr, "wav");
	if(namearrptr != NULL){
		wavcnt++;
	}
	while(namearrptr != NULL){
		wavcnt++;
		namearrptr = strtok(NULL, "wav");
	}
	return wavcnt;
}
/*
 * Plays the .wav file using the data stored within the Wave* struct pointed to by the lone argument.
 * This function will add the song to the playing queue. Once the Song is finished it is removed from the queue
 * This function does not return a value.
 *
 * This function supports the simultaneous playback of up to 12 notes. Any additional notes are ignored until
 * a note has finished playing. Returns 0 if the song was added to the playing queue or -1 if there was no space.
 */
int playSong(Wave* Song){
	//Add the song to the play queue if there's enough room - Enforced for quality and CPU power reasons.
	if (numSongs < PLAY_LIMIT){

		//If there are no elements currently playing, initialize
		if (playStart == NULL)
		{
			playStart = malloc(sizeof(playingSong));
			playStart->song = Song;
			playStart->bytesPlayed = 0;
			playStart->finished = false;
			playStart->nextSong = NULL;

		}
		//Find the end of the linked list
		else{
			playingSong* pos = playStart;
			//As long as there is no subsequent element keep iterating
			while(pos->nextSong != NULL){
				pos = pos->nextSong;
			}
			pos->nextSong = malloc(sizeof(playingSong));
			pos = pos->nextSong;
			pos->song = Song;
			pos->bytesPlayed = 0;
			pos->finished = false;
			pos->nextSong = NULL;

		}
		numSongs++;
		return 0;
	}
	//Notify the caller that there wasn't enough room to play the note
	return -1;


}

/*
 * Plays a small section of all the songs currently in the list of songs to be played. Will tie up the processor
 * until the section has been added to the playbuffer. Also clears elements in the list if they have been played fully.
 * If the song has been defined as looping, will continuously play the song up to a limit.
 * Takes no arguments and returns the amplitude of the first value in the buffer which may be used for the equalizer
 */
unsigned int playArr(void){

	int k;
	int j;
	int buffer[24] = {0};


	playingSong* pos = playStart;
	//If the first song in the queue is finished, purge it, start at next song.
	if(playStart->bytesPlayed == playStart->song->datasize){
		pos = playStart->nextSong;
		free(playStart);
		playStart = pos;
		numSongs--;
	}
	//Iterate through all the songs in the playing list
	while(pos!= NULL){
		//If the next element has no bytes left to play, remove it from the playing queue.
		//and set the nextSong parameter accordingly
		if(pos->nextSong != NULL && pos->bytesPlayed == pos->song->datasize){
			playingSong* temp = pos->nextSong;
			pos->nextSong = pos->nextSong->nextSong;
			free(temp);
			numSongs--;
		}
		//If there's more than enough bytes left, only take the next 72.
		if((pos->song->datasize-pos->bytesPlayed) > 72){
			k = 72;
		}
		else{
			k = pos->song->datasize-pos->bytesPlayed;
		}

		//Add k bytes to the buffer for this song.
		for(j=0;j<k/3;j++){
			buffer[j] += //((pos->song->songData[pos->bytesPlayed]) & 0x80) >0 ? 0 : 0xFF000000)
						(pos->song->songData[pos->bytesPlayed] << 16)
					| 	(pos->song->songData[pos->bytesPlayed+1] << 8)
					|	(pos->song->songData[pos->bytesPlayed+2]);
			pos->bytesPlayed += 3;
		}

		//Increment to the next element in the linked list
		pos = pos->nextSong;

	}
	//Play the buffer

	for(j=0;j<24;j++){
		/*
		//If the buffer is greater than 24 bit limit -> 0x007FFFFF
		if (buffer[j] > 0x007FFFFF){
			buffer[j] = 0x7FFFFF;
		}
		//If the buffer is less than 24 bit lower limit -> 0x00800000
		else if (buffer[j] < 0xFF000000){
			buffer[j] = 0x00800000;
		}
		*/
		buffer[j] = buffer[j] << 8;
	}
	//Play the buffer
	while(alt_up_audio_write_fifo_space(audio_dev, ALT_UP_AUDIO_LEFT)<24);
	alt_up_audio_write_fifo(audio_dev, (unsigned int*)buffer, 24, ALT_UP_AUDIO_LEFT);
	while(alt_up_audio_write_fifo_space(audio_dev, ALT_UP_AUDIO_RIGHT)<24);
	alt_up_audio_write_fifo(audio_dev, (unsigned int*)buffer, 24, ALT_UP_AUDIO_RIGHT);

	return buffer[0];

}
//If there is insufficient space return -1

/*
	int i;
	int k=0;

	unsigned int buffer[16];
	char* buffptr = (char*)&buffer[0];
	alt_up_audio_reset_audio_core(audio_dev);
	while(k < Song->datasize){
		for(i=0;i<64;){
 *(buffptr+i) = 0x00;
 *(buffptr+i+1) = Song->songData[k];
 *(buffptr+i+2) = Song->songData[k+1];
 *(buffptr+i+3) = Song->songData[k+2];
			i += 4;
			k += 3;
		}
		//Forces the program to wait until the buffer has space
		while(alt_up_audio_write_fifo_space(audio_dev, ALT_UP_AUDIO_LEFT)<16);
		alt_up_audio_write_fifo(audio_dev, buffer, 16, ALT_UP_AUDIO_LEFT);
		while(alt_up_audio_write_fifo_space(audio_dev, ALT_UP_AUDIO_RIGHT)<16);
		alt_up_audio_write_fifo(audio_dev, buffer, 16, ALT_UP_AUDIO_RIGHT);

	}
	return 0;
 */



/*
 * Plays the song specified in the argument or if the song is not valid, returns -1
 */
Wave* playSongNamed(char* filename){
	Wave* Song = isWav(filename);
	if(Song == NULL){
		return Song;
	}
	else{
		playSong(Song);
		return Song;
	}

}

/*
 * Purges the current list of playable songs and then proceeds to refresh the internal list of songs. Takes the pointer from
 */
void refreshSongs(Wave** Wavearr){

}
