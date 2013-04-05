/*
 * FileStructs.h
 *
 *  Created on: Mar 6, 2013
 *      Author: Leslie
 */

#ifndef FILESTRUCTS_H_
#define FILESTRUCTS_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define WAV_OFFSET 44

typedef struct Wave{
	char* filename;
	int 	datasize;
	unsigned short	channels;
	unsigned int		samplerate;
	unsigned short	samplesize;
	unsigned char* songData;
}Wave;

typedef struct playingSong{

	Wave* song;
	int bytesPlayed;
	struct playingSong* nextSong;

}playingSong;

#endif /* FILESTRUCTS_H_ */
