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
#include "system.h"


/*
 * Initializes the audio output interface and creates an array to store pointers. Every pointer needs to be malloc'd
 * so that only as much memory as is needed to store the active songs is used. Returns a pointer to the array of songs
 * or a NULL pointer if the audio interface could not be initialized
 */

Wave* wavInit(void){

	Wave* Wavearr= malloc(SONGS_MAX*sizeof(Wave*));
	audio_dev = alt_up_audio_open_dev (AUDIO_NAME);
	alt_up_audio_disable_read_interrupt(audio_dev);
	alt_up_audio_enable_write_interrupt(audio_dev);
	if ( audio_dev == NULL){
		return NULL;
	}
	return Wavearr;
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
		printf("Could not find the specified file\n");
		return NULL;
	}
	if((fileheader[8] == 'W') && fileheader[9] == 'A' && fileheader [10] == 'V' && fileheader[11] == 'E');
	else
		return NULL;
	Wave* File = malloc(sizeof(Wave));
	File->datasize = (unsigned char)fileheader[40]+(unsigned char)fileheader[41]*256+(unsigned char)fileheader[42]*65536;
	printf("40 is %02hhX, 41 is %02hhX, 42 is %02hhX\n", fileheader[40], fileheader[41], fileheader[42]);
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
		printf("One song added\n");
	}
	while(namearrptr != NULL){
		printf("Another song added\n");
		wavcnt++;
		namearrptr = strtok(NULL, "wav");
	}
	return wavcnt;
}
/*
 * Plays the .wav file with the name specified in the argument. Returns a negative number if an error has occured and
 * 0 if the file has played
 * Best used with the [Wave]->filename operator
 */
int playSong(Wave* Song){
	if(Song == NULL){
		return -1;
	}
	int songOffsetL = WAV_OFFSET;
	int songOffsetR = WAV_OFFSET;
	char* currentSong = malloc(Song->datasize+WAV_OFFSET);
	file_read(currentSong+1, Song->filename, Song->datasize+WAV_OFFSET-1);
	while(Song->datasize-songOffsetR > 0 && Song->datasize-songOffsetL > 0){
		songOffsetR += 2*alt_up_audio_play_r(audio_dev, (unsigned int*)(currentSong+songOffsetR), Song->datasize-songOffsetR);
		songOffsetL += 2*alt_up_audio_play_l(audio_dev, (unsigned int*)(currentSong+songOffsetL), Song->datasize-songOffsetL);
	}
	alt_up_audio_reset_audio_core(audio_dev);
	free(currentSong);

	return 0;
}

/*
 * Purges the current list of playable songs and then proceeds to refresh the internal list of songs. Takes an pointer to the
 * array of pointers to structs of "Wave" and returns void.
 */
void refreshSongs(char* Songarr){

}
