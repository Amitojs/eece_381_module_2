/*
 * WavTests.c
 *
 *  Created on: Mar 13, 2013
 *      Author: Leslie
 */

#include <stdio.h>
#include <stdlib.h>
#include "FileStructs.h"
#include "WavOps.h"
#include "interface_SD.h"

int main(void){

	sd_init();
	int wavPos = 0;
	int i;
	//Testing WavInit
	Wave* wavArr = wavInit();

	//Testing the building of the array of songs
	Wave* arrPos = wavArr+wavPos;
	if(wavArr != NULL){
		printf("\nThe audio interface has been initialized\n");
	}
	arrPos = isWav("boing.wav");
	printf("The information for the .wav is:\n");
	printf("channels: %d\nfilename: %s\nsamplerate: %d\nsamplesize: %d\n", (arrPos)->channels,
			(arrPos)->filename,(arrPos)->samplerate, (arrPos)->samplesize);

	//Testing the .wav total retrieval
	printf("The number of .wavs present on the sd card is: %d\n", getPlayable());

	//Testing song playback
	for(i=0; i<1000; i++){
		playSong(arrPos->filename);
		printf("Playing song ");
	}
	free(arrPos);
	free(wavArr);
	return 0;
}

