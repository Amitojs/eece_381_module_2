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
 * Initializes the audio output interface and creates an array to store pointers. Every pointer needs to be malloc'd
 * so that only as much memory as is needed to store the active songs is used. Returns a pointer to the array of songs
 * or a NULL pointer if the audio interface could not be initialized. This pointer should be freed when it is no longer used.
 * If the function returns NULL something seriously wrong has occured.
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
	return;
}

Wave** pianoInit(void){

	Wave** pianoArr = malloc(PIANO_NOTES*sizeof(Wave*));
	*pianoArr = isWav("c.wav");
	*(pianoArr+1) = isWav("cs.wav");
	*(pianoArr+2) = isWav("d.wav");
	*(pianoArr+3) = isWav("ds.wav");
	*(pianoArr+4) = isWav("e.wav");
	*(pianoArr+5) = isWav("f.wav");
	*(pianoArr+6) = isWav("fs.wav");
	*(pianoArr+7) = isWav("g.wav");
	*(pianoArr+8) = isWav("a.wav");
	*(pianoArr+9) = isWav("as.wav");
	*(pianoArr+10) = isWav("b.wav");

	return pianoArr;

}

/*
 * Checks to see if the filename it takes exists and that it is a .wav file.
 * If it is, returns a pointer to a struct containing the file info
 * If it is not a .wav file or the file does not exist, the pointer is NULL.
 * The returned file must be deallocated with free.
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
	if(File == NULL){
	}
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
 * Plays the .wav file using the data stored within the Wave* struct pointed to by the lone argument. If the pointer is null
 * returns -1, otherwise plays the song and returns 0.
 */
int playSong(Wave* Song){
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

}

/*
 * Plays the song specified in the argument or if the song is not valid, returns -1
 */
int playSongNamed(char* filename){
	Wave* Song = isWav(filename);
	if(Song == NULL){
		return -1;
	}
	else{
		playSong(Song);
		free(Song->songData);
		free(Song);
		return 0;
	}

}

/*
 * Purges the current list of playable songs and then proceeds to refresh the internal list of songs. Takes the pointer from
 */
void refreshSongs(Wave** Wavearr){

}
