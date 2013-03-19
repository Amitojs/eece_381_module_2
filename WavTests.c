/*
 * WavTests.c
 *
 *  Created on: Mar 13, 2013
 *      Author: Leslie
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FileStructs.h"
#include "WavOps.h"
#include "interface_SD.h"

int main(void){

	sd_init();
	int songCount = getPlayable();
	int i;
	//Testing WavInit
	Wave** wavArr = wavInit();
	if(wavArr == NULL){
		printf("The array was not built successfully, terminating");
	}
	//Testing the building of the array of songs
	else{
	}
	*wavArr = isWav("seph.wav");
	printf("The information for the .wav is:\n");
	printf("datasize: %d\nchannels: %d\nfilename: %s\nsamplerate: %d\nsamplesize: %d\n",(*wavArr)->datasize, (*wavArr)->channels,
			(*wavArr)->filename,(*wavArr)->samplerate, (*wavArr)->samplesize);

	//Testing the .wav total retrieval
	printf("The number of .wavs present on the sd card is: %d\n", getPlayable());

	playSongNamed("seph.wav");
	playSongNamed("seph.wav");
	playSongNamed("seph.wav");
	//playSongNamed("boing.wav");
	//playSongNamed("test.wav");
	//playSongNamed("dingding.wav");

	//Testing song playback
	/*
	for(i=0; i<songCount; i++){
		playSong(*(wavArr+i));
		playSong(*(wavArr+i));
	}

	//Free the memory allocated to song data and the song array itself
	for(i=0; i<songCount; i++){
		free(*(wavArr+i));
	}
	free(wavArr);
	*/
/*
	//Testing song playback continued - filenames
	printf("Now playing named\n");
	if(playSongNamed("dingding.wav")!= 0){
		printf("This failed horribly\n");
	}
	*/
	return 0;
}

