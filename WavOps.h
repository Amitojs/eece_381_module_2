/*
 * WavOps.h
 *
 *  Created on: Mar 6, 2013
 *      Author: Leslie
 */

#ifndef WAVOPS_H_
#define WAVOPS_H_

#define SONGS_MAX 512

#include "FileStructs.h"
#include <stdio.h>
#include <stdlib.h>
#include "altera_up_avalon_audio.h"


int Songcount;
alt_up_audio_dev * audio_dev;

Wave* wavInit(void);
//Prototype for the wave format checker
Wave* isWav(char* filename);
//Prototype for song retrieval
int getPlayable(char*);
//Prototype for song playback
int playSong(char* filename);
//Prototype for refreshing SD card
void refreshSongs(char*);

#endif /* WAVOPS_H_ */
