/*
 * WavOps.h
 *
 *  Created on: Mar 6, 2013
 *      Author: Leslie
 *
 *      This header defines constants for use with the wave function and creates function prototypes for them.
 *      It also creates global variables for the use of storing the audio output and configuration locations as
 *      well as the list of playing songs.
 */

#ifndef WAVOPS_H_
#define WAVOPS_H_

#define SONGS_MAX 512
#define PIANO_NOTES 12
#define PLAY_LIMIT 2
#define LOOP_LIMIT 8000

#include "FileStructs.h"
#include <stdio.h>
#include <stdlib.h>
#include "altera_up_avalon_audio.h"
#include "altera_up_avalon_audio_and_video_config.h"

alt_up_audio_dev * audio_dev;
alt_up_av_config_dev * av_config;
playingSong* playStart;
int numSongs;

//Prototype for initialization of the wave file player
void wavInit(void);
//Prototype for initialization of piano notes
Wave** pianoInit(void);
//Prototype for volume changer
void volume(char);
//Prototype for the wave format checker
Wave* isWav(char* filename);
//Prototype for song retrieval
int getPlayable(void);
//Prototypes for adding song to playback list
int playSong(Wave* Song);
//Prototype for playing the songs in the list
void playArr(void* context, alt_u32 id);
//Prototype for explicit song playback
Wave* playSongNamed(char* filename);
//Prototype for refreshing SD card
void refreshSongs(Wave** wavArr);

#endif /*WAVOPS_H_*/
