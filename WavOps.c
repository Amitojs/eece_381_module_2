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
#include "altera_up_avalon_audio_and_video_config.h"
#include "system.h"


/*
 * Initializes the audio output interface and creates an array to store pointers. Every pointer needs to be malloc'd
 * so that only as much memory as is needed to store the active songs is used. Returns a pointer to the array of songs
 * or a NULL pointer if the audio interface could not be initialized. This pointer should be freed when it is no longer used.
 * If the function returns NULL something seriously wrong has occured.
 */

Wave** wavInit(void){

	Wave** wavArr = malloc(SONGS_MAX*sizeof(Wave*));
	audio_dev = alt_up_audio_open_dev (AUDIO_0_NAME);
	if ( audio_dev == NULL){
		return NULL;
	}
	alt_up_audio_disable_read_interrupt(audio_dev);
	alt_up_audio_enable_write_interrupt(audio_dev);
	if( audio_dev == NULL){
		return NULL;
	}
	refreshSongs(wavArr);
	return wavArr;
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
	File->datasize = (unsigned char)fileheader[40]+(unsigned char)fileheader[41]*256+(unsigned char)fileheader[42]*65536;
	File->channels = fileheader[22];
	File->samplerate = (unsigned char)fileheader[24]+(unsigned char)fileheader[25]*256+(unsigned char)fileheader[26]*65536;
	File->samplesize = fileheader[34];
	File->filename = filename;
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


	unsigned char* currentSong = malloc((Song->datasize+WAV_OFFSET)*sizeof(char));
	file_read((char*)(currentSong), Song->filename, Song->datasize+WAV_OFFSET);
	/*
	short* temp2 = (short*)&currentSong[WAV_OFFSET];
	unsigned short* temp = (unsigned short*)&currentSong[WAV_OFFSET];

	int i;
	printf("%d, %u\n", temp2[0], temp[0]);
	for (i=0; i<(Song->datasize/2); i++){
		temp[i]= temp2[i]+(32768);
	}
	printf("%d, %u\n", temp2[0], temp[0]);
	*/
	unsigned int rightOffset = WAV_OFFSET;
	unsigned int leftOffset = WAV_OFFSET;
	alt_up_audio_reset_audio_core( audio_dev );
	while (rightOffset < Song->datasize && leftOffset < Song->datasize){
		//rightOffset += alt_up_audio_write_fifo(audio_dev, (unsigned int*)(&currentSong[rightOffset]), (Song->datasize-rightOffset), ALT_UP_AUDIO_RIGHT);
		rightOffset += 2*alt_up_audio_play_r(audio_dev,(unsigned int*)(&currentSong[rightOffset]),(Song->datasize-rightOffset));
		leftOffset += 2*alt_up_audio_play_l(audio_dev,(unsigned int*)(&currentSong[leftOffset]),(Song->datasize-leftOffset));
	}
	free(currentSong);
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
		free(Song);
		return 0;
	}

}

/*
 * Purges the current list of playable songs and then proceeds to refresh the internal list of songs. Takes the pointer from
 */
void refreshSongs(Wave** Wavearr){
	int i = getPlayable();

}
