/*
 * SD_Interface.c
 *
 *  Last Modified: March 6, 2013
 *  Author: Leslie Mui
 *
 *  This file contains methods for functionality from the SD card
 *  All read operations read into the a buffer supplied by the macrofunction that calls it
 *  This is to enable the use of a single multi-purpose array for reading to the SD card and
 *  at a future date, write operations may be supported. The pointer to the filenames is not modified
 *  by the functions below and may be reused by other functions
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include "interface_SD.h"
#include <altera_up_sd_card_avalon_interface.h>


/*
 * This function initializes the SD card for use. It must be run once and only once before any other functions within this file are used
 */
void sd_init(void){

	alt_up_sd_card_dev *device_reference = NULL;
	device_reference = alt_up_sd_card_open_dev(ALTERA_UP_SD_CARD_AVALON_INTERFACE_0_NAME);
}


/*
 * This function is used for reading data to a buffer from the SD card. It takes in three arguments, a
 * pointer to a character buffer where the data will be stored, the name of a file i.e. "Readme.txt"
 * and the size of the character buffer. It will return the number of
 * characters read into the buffer. If the SD card is inaccessible, returns -1
 *
 * Example of use
 *
 *  char charbuffer[1024];
	int charbuffersize = 1024;
	char* charptr;
	charptr = &charbuffer[0];
	int charcount=0;
 *  charcount = file_read(charptr, "README.TXT", charbuffersize);
 */
int file_read(char* charbuffer, char* filename, int charmax){

	if ((alt_up_sd_card_is_Present())) {
		if (alt_up_sd_card_is_FAT16()) {

			short int file0;
			int k;
			int charcount;

			//Open the file in the argument for reading. False means that the file will not be created
			//if it is not found. A negative return value means that the file was not opened successfully
			file0 = alt_up_sd_card_fopen(filename, false);

			if (file0 == -1) return -1;
			if (file0 == -2) return -2;

			//Read as many characters as possible from the file, up to charmax or until the file has been read
			//to completion.
			else {
				for(k=0; k<charmax; k++){
					*(charbuffer+k) = (char)alt_up_sd_card_read(file0);

					//If the end of file has been reached, stop reading. EOF is designated with a negative value
					if ((*(charbuffer+k) == -1) && (*(charbuffer+k-1) == -1) && (*(charbuffer+k-2) == -1) && (*(charbuffer+k-3)== -1)){
						break;
					}

					charcount = k;

				}

			}

			//Close the file and return the amount of characters read into the buffer
			alt_up_sd_card_fclose(file0);
			return charcount;
		}

	}
	return -1;

}
/*
 * Opens a file and prepares it to be streamed by calling the function with the file handle -1
 * Further calls to the function will return a single byte of data. The user must determine when the file has been
 * completely read and call file_close() manually.
 */

char filestream(char* filename, short int filehandle){
	return 0;
}

/* Returns the number of files 	 within the SD card and adds all all filenames to an array provided
 * by the calling function.
 * The array will contain the filenames in the format [filename].[extension].
 * All files will be separated by a ; character to ensure compatability with the strtok function
 * The filename must be eight characters or less in length and have a three character extension
 * The function returns the number of files within the array. Charmax should be a minimum of a 12 character array.
 *
 * Example of use:
 *
 * 	char charbuffer[1024];
	int charbuffersize = 1024;
	char* charptr;
	charptr = &charbuffer[0];
	int charcount=0;

	charcount = filenames_read(charptr, charbuffersize);
 * If the function returns -1, an error has occured when trying to access the SD card
 * If the function returns -2, no files are contained within the SD card
 */

int filenames_read(char* filename, int charmax){

	//Test if the SD card is inserted and is in a valid file format for reading

	if ((alt_up_sd_card_is_Present())) {
		if (alt_up_sd_card_is_FAT16()) {

			int offset = 0;
			int filecount = 0;

			int returnval = alt_up_sd_card_find_first(0x0, filename);
			if (returnval < 0){
				printf("the read failed");
				return -2;
			}

			/*
			 * Read the first filename within the SD card as long as there is sufficient space within the character buffer
			 */
			if((returnval == 0))
			{
				filecount++;
				while(*(filename+offset) != '.')
					offset++;
				offset+=4;
				*(filename+offset) = ';';
				offset++;
			}

			/* As long as there is sufficient space within the character buffer, will read every name within the
			 * SD card to a buffer.
			 */
			while (1){

				returnval = alt_up_sd_card_find_next((filename+offset));

				if (returnval == -1 ){
					break;
				}

				filecount++;

				if((charmax-offset) <= 12){
					break;
				}
				while(*(filename+offset) != '.'){
					offset++;
				}
				offset+=4;
				*(filename+offset) = ';';
				offset++;
			}

			return filecount;

		}
	}

	return -1;

}

/*
Enter a filename such as "blank.txt" including the quotes, and an array with enough storage for one byte per pixel (20x24 = 480 bytes = 480 element array)
It will return a pointer to an array containing three byte color data. The colours in the array are arranged in BGR order.
I'm not sure about how colours are saved within windows. There is a chance that all palettes are identical, in which case we only need to strip the palette
once. Inside the initial array, all pixels are stored going from left to right, row by row from the bottom to top of the image. The size of the image is not stripped
so I propose to have the storage array change based on the size of the level (S/M/L)
 */


void bmp_read(char* filename, char* pixeldata, char* palptr) {

	char image[2048] = {0};
	char* imageptr;
	imageptr = &image[0];
	//char* palptr;
	//palptr = &palette[0];
	int i;
	int offset = 0;//0x36;

	//file_read (imageptr, filename, 2048);


	if ((alt_up_sd_card_is_Present())) {
			if (alt_up_sd_card_is_FAT16()) {

				short int file0;
				int k;
				//int charcount;

				//Open the file in the argument for reading. False means that the file will not be created
				//if it is not found. A negative return value means that the file was not opened successfully
				file0 = alt_up_sd_card_fopen(filename, false);

				if (file0 == -1) return -1;
				if (file0 == -2) return -2;

				//Read as many characters as possible from the file, up to charmax or until the file has been read
				//to completion.
				else {
					for(k=0; k<2048; k++){
						*(imageptr+k) = (char)alt_up_sd_card_read(file0);

						//If the end of file has been reached, stop reading. EOF is designated with a negative value
						//if ((*(charbuffer+k) == -1) && (*(charbuffer+k-1) == -1) && (*(charbuffer+k-2) == -1) && (*(charbuffer+k-3)== -1)){
							//break;
						//}

						//charcount = k;

					}

				}

				//Close the file and return the amount of characters read into the buffer
				alt_up_sd_card_fclose(file0);
				//return charcount;
			}

		}
		//return -1;


	offset += *(imageptr+0xA);
	offset += *(imageptr+0xB)*256;

	for(i=0; i<480;i++){
		//if(i%16 == 0)
			*(pixeldata+i)= *(imageptr+offset+i);
			//printf( "%02hhX ", *(pixeldata+i) );
			//if(i%20 == 0) printf("\n");

	}

	for(i=0; i<256; i++){
		*(palptr + 3*i)   = *(imageptr + 4*i + 0 + 0x36);
		*(palptr + 3*i + 1) = *(imageptr + 4*i + 1 + 0x36);
		*(palptr + 3*i + 2) = *(imageptr + 4*i + 2 + 0x36);
	}
	//printf("");

	//printf( "\n %02hhX , %02hhX , %02hhX, %02hhX \n",  *(imageptr+4*0xFC+0x36),*(imageptr+4*0xFc+1+0x36),*(imageptr+4*0xFC+2+0x36),*(imageptr+4*0xFC+3+0x36)); //b --1
	//printf( "\n %02hhX , %02hhX , %02hhX \n",  palette[750], palette[751], palette[752]);

	return;

}


