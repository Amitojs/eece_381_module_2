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
#include "commander.h"

int main(){

	printf("starting \n");
	int i;
	sd_init();
	//Testing WavInit
	wavInit();


	load_piano();
	load_drums();

	/*for(i=0;i<2; i++){
		play_in_parr(i);
		/*printf("The information for the .wav is: \n");
		printf("datasize: %d\nchannels: %d\nfilename: %s\nsamplerate: %d\nsamplesize: %d\n",parr[i]->datasize, parr[i]->channels,
				parr[i]->filename,parr[i]->samplerate, parr[i]->samplesize);
	}*/
	//Testing the .wav total retrieval
	//printf("Total .wavs present on the sd card is: %d\n\n", getPlayable());
	//playSong(parr[0]);


	while(1){
		int i = 0;
		play_in_parr(0);
		while(i < 12){
			if(numSongs == 0){
				i++;
				play_in_parr(i);
			}
		}
		i=0;
		play_in_darr(0);
		while(i < 6){
			if(numSongs == 0){
				i++;
				play_in_darr(i);
			}
		}
	}
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

