/*
 * rs232.c
 *
 *  Created on: Mar 6, 2013
 *      Author: Scott
 */

#include "rs232.h"
#include <stdio.h>
#include "altera_up_avalon_rs232.h"
#include <string.h>

void append ( unsigned char* s, char c ) {
	int len = (int) strlen( (char*) s);
	s[len] = c;
	s[len+1] = '\0';
}

rsinfo rsinit (  ) {
	rsinfo a;
	printf("UART Initialization\n");
	a.uart = alt_up_rs232_open_dev(RS232_0_NAME);
	return a;
}

void rssend ( rsinfo a, unsigned char message[] ){
	int i = 0;

	//printf("Clearing read buffer to start\n");
	while (alt_up_rs232_get_used_space_in_read_FIFO(a.uart)) {
		alt_up_rs232_read_data(a.uart, &a.data, &a.parity);
	}

	printf("Sending '%s' to Middleman\n", message);

	// Start with the number of bytes in our message
	alt_up_rs232_write_data(a.uart, (unsigned char) strlen( (char*)message ) );

	// Now send the actual message to the Middleman
	for (i = 0; i < (int) strlen( (char*)message ); i++) {
		alt_up_rs232_write_data(a.uart, message[i]);
	}
}

void rsrecieve ( rsinfo a, unsigned char* s1_ptr ) {
	int i = 0;
	//char s1[] =
	//char* s1_ptr = &s1;

	printf("Waiting for data...\n");
	while (alt_up_rs232_get_used_space_in_read_FIFO(a.uart) == 0){
		//do nothing
	}

	// First byte is the number of characters in our message
	alt_up_rs232_read_data(a.uart, &a.data, &a.parity);
	int num_to_receive = (int)a.data;

	printf("Receiving %d characters:\n'", num_to_receive);

	for (i = 0; i < num_to_receive; i++) {
		while (alt_up_rs232_get_used_space_in_read_FIFO(a.uart) == 0);
		alt_up_rs232_read_data(a.uart, &a.data, &a.parity);

		append(s1_ptr, a.data);
		printf("%c", a.data);
	}
	printf("'\n");
}
