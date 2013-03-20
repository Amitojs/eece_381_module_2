/*
 * WavOps.h
 *
 *  Created on: Mar 6, 2013
 *      Author: Leslie
 */

#ifndef WAVOPS_H_
#define WAVOPS_H_

#define SONGS_MAX 512
#define PIANO_NOTES 11

#include "FileStructs.h"
#include <stdio.h>
#include <stdlib.h>
#include "altera_up_avalon_audio.h"
#include "altera_up_avalon_audio_and_video_config.h"

alt_up_audio_dev * audio_dev;
alt_up_av_config_dev * av_config;

void wavInit(void);
Wave** pianoInit(void);
//Prototype for volume changer
void volume(char);
//Prototype for the wave format checker
Wave* isWav(char* filename);
//Prototype for song retrieval
int getPlayable(void);
//Prototypes for song playback
int playSong(Wave* Song);
int playSongNamed(char* filename);
//Prototype for refreshing SD card
void refreshSongs(Wave** wavArr);

#endif /* WAVOPS_H_ */
