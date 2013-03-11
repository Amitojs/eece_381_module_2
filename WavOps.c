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


/*
 * Initializes the audio output interface and creates an array to store pointers. Every pointer needs to be malloc'd
 * so that only as much memory as is needed to store the active songs is used. Returns a pointer to the array of songs
 * or a NULL pointer if the audio interface could not be initialized
 */

Wave* wavInit(void){

	Wave* Wavearr[]= malloc(SONGS_MAX*sizeof(Wave*));
	Wave* Waveptr = &Wavearr[0];
	audio_dev = alt_up_audio_open_dev ("/dev/audio");
	alt_up_audio_disable_read_interrupt(audio_dev);
	alt_up_audio_enable_write_interrupt(audio_dev);
	if ( audio_dev == NULL){
		return NULL;
	}
	return Waveptr;
}
/*
 * Checks to see if the filename it takes exists and that it is a .wav file.
 * If it is, returns a pointer to a struct containing the file info
 * If it is not a .wav file or the file does not exist, the pointer is NULL.
 * The returned file must be deallocated with free.
 */


Wave* isWav(char* filename){

	char fileheader[WAV_OFFSET];
	if(file_read(fileheader, filename, WAV_OFFSET)<0){
		return NULL;
	}
	if((fileheader[8] == 'W') && fileheader[9] == 'A' && fileheader [10] == 'V' && fileheader[11] == 'E');
	else
		return NULL;
	Wave* File = malloc(sizeof(Wave));
	File->datasize = fileheader[40]/2;//The size of the data is stored in words to make further operations easier
	File->channels = fileheader[22];
	File->samplerate = fileheader[24];
	File->samplesize = fileheader[34];
	File->filename = filename;
	return File;
}

/*
 * Returns the number of files with a .wav file extension as an integer.
 * If it returns 0, no wav files were found
 * If it returns a negative number, an error has occured
 * If there are more than 512 files on the SD card, returns the first 512 files found
 * Takes a single argument, a point to an array of pointers to structs. This pointer should be initialized with malloc
 */

int getPlayable(char* Songarr){

	char namearr[SONGS_MAX*13];
	int wavcnt = 0;
	char* namearrptr = &namearr[0];
	filenames_read(namearrptr, SONGS_MAX*13);
	if(strtok(namearr, "wav") != NULL){
		wavcnt++;
	}
	while(strtok(NULL, "wav") != NULL){
		wavcnt++;
	}
	return wavcnt;
}
/*
 * Plays the .wav file with the name specified in the argument. Returns a negative number if an error has occured and
 * 0 if the file has played
 * Best used with the [Wave]->filename operator
 */
int playSong(char* filename){
	Wave* Song = isWav(filename);
	if(Song == NULL){
		return -1;
	}
	int songOffsetL = WAV_OFFSET;
	int songOffsetR = WAV_OFFSET;
	char* currentSong = malloc(Song->datasize+WAV_OFFSET);
	file_read(currentSong, Song->filename, Song->datasize+WAV_OFFSET);
	int i = Song->datasize;

	while(i > 0){
		songOffsetR = songOffsetR + alt_up_audio_play_r(audio_dev, currentSong+songOffsetR, Song->datasize-songOffsetR);
		songOffsetL = songOffsetL + alt_up_audio_play_l(audio_dev, currentSong+songOffsetR, Song->datasize-songOffsetL);

	}
	free(currentSong);
	return 0;
}

/*
 * Purges the current list of playable songs and then proceeds to refresh the internal list of songs. Takes an pointer to the
 * array of pointers to structs of "Wave" and returns void.
 */
void refreshSongs(char* Songarr){


}
