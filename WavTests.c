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
#include <altera_up_sd_card_avalon_interface.h>

int main(){

	printf("starting \n");
	int i;
	sd_init();
	//Testing WavInit
	wavInit();
	/*
	Wave** pianoArr = pianoInit();

	if(pianoArr == NULL){
		printf("The array was not built successfully, terminating");
	}
	for(i=0;i<PIANO_NOTES; i++){
		printf("The information for the .wav is: \n");
		printf("datasize: %d\nchannels: %d\nfilename: %s\nsamplerate: %d\nsamplesize: %d\n",(*pianoArr+i)->datasize, (*pianoArr+i)->channels,
				(*pianoArr+i)->filename,(*pianoArr+i)->samplerate, (*pianoArr+i)->samplesize);
	}
	//Testing the .wav total retrieval
	printf("Total .wavs present on the sd card is: %d\n\n", getPlayable());
	playSong(pianoArr[0]);
	while(numSongs > 0){
		playArr();
	}*/
	Wave* Song = playSongNamed("c.wav");
	//Wave* Song2= playSongNamed("a.wav");
	while(numSongs > 0){
		playArr();
	}
	free(Song->songData);
	free(Song);
	//free(Song2->songData);
	//free(Song2);
	printf("done");
	//while(1){
		/*Testing the readspeed of the SD card
	char* testbuffer = malloc (330000*sizeof(char));
	short int test = openRead("seph.wav");
	int i;
	printf("Testing readspeed\n");
		for(i=0;i<330000;i++)
			testbuffer[i] = alt_up_sd_card_read(test);
	printf("done\n");
	free(testbuffer);
	*/
	/*
		if(playStart == NULL){
			playSong(pianoArr[0]);
			printf("Should be playing\n");
		}
		playArr();
	}
	*/
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

