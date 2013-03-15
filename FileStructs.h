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

#define WAV_OFFSET 44

typedef struct {
   int 	datasize;
   unsigned short	channels;
   unsigned int		samplerate;
   unsigned short	samplesize;
   char* 	filename;
}Wave;

#endif /* FILESTRUCTS_H_ */
