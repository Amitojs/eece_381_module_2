/*
 * commander.c
 *
 *  Created on: Mar 13, 2013
 *      Author: Scott
 *
 *
 *      Version: 1.0.0
 *
 *
 */

#include "rs232.h"
#include "commander.h"
#include <stdio.h>
#include <string.h>
#include <io.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>



command* consume_message( llist *head ){
	int i = 0;
	command* c = (command*)malloc(sizeof(command));

	if ( head == NULL){
		c->action = 0;
		c->my_note[0] = '\0';
		c->my_note[1] = '\0';
		return c;
	}
	else {
		//printf("\nConsuming message.\n");
	}

	unsigned char message[MAX_STRING_SIZE];

	for (i=0;i<MAX_STRING_SIZE; i++){
		message[i] = head->message[i];
	}
	delete_head_from_list();

	c->action = (int) message[0] - '0';

	if (message[0] == '1'){
		c->my_note[0] = message[1];

		if ( message[2] == 'S' )
			c->my_note[1] = 'S';
		else
			c->my_note[1] = '\0';

	} else {// message[0] != '1';
		c->my_note[0] = '\0';
		c->my_note[1] = '\0';
	}
	return c;
}

// For testing poirposes
// Prints out the contents of a command
void print_command( command* c ){
	printf("\nAction: %d\n", c->action);
	printf("Note: %s\n", c->my_note);
}
