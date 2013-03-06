/*
 * rs232.h
 *
 *  Created on: Mar 6, 2013
 *      Author: Scott
 */

/*
-------------------------------------------
Sample use
-------------------------------------------

#include "rs232.h"
#include <stdio.h>
#include "altera_up_avalon_rs232.h"
#include <string.h>

int main()
{
	int i;
	unsigned char message[MAX_STRING_SIZE] = "";
	unsigned char s1[MAX_STRING_SIZE] = "";
	unsigned char* s1_ptr = s1;

	// Initialize the rs232 connection & struct
	rsinfo a = rsinit();

	for(;;){
		// Clear any string data
		message[0] = '\0';
		s1[0] = '\0';

		// Receive the message from the Middleman
		rsrecieve(a, s1_ptr);

		// Take the string and reorganize it backwards
		for (i = 0; i <= strlen( (char*)s1 ); i++){
			append(message, s1[strlen(( char*)s1 )-i]);
		}

		//printf("Sending message: '%s'\n", message);

		// Send the message to the Middleman
		rssend( a, message );
	}
	return 0;
}

-------------------------------------------
 */



#ifndef RS232_H_
#define RS232_H_

#include "altera_up_avalon_rs232.h"

#define MAX_STRING_SIZE 265

typedef struct{
	alt_up_rs232_dev* uart;
	unsigned char data;
	unsigned char parity;
} rsinfo;

void 	rssend		( rsinfo a, unsigned char message[] );
void 	append		( unsigned char* s, char c );
void 	rsrecieve	( rsinfo a, unsigned char* s1_ptr );
rsinfo 	rsinit		(  );


#endif /* RS232_H_ */
