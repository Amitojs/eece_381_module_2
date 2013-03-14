/*
 * commander.c
 *
 *  Created on: Mar 13, 2013
 *      Author: Scott
 *
 *
 *      Version: 1.2.0
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


// Completes an action from a command.
// Returns true if successful, false if the action is unknown.
bool do_command( command* c ){
	if ( c->action == 0 ){
		return false;
	}else if ( c->action == 1 ){
		switch ( c->my_note[0] ){
			case 'A':
				if (my_note[1] == 'S')
					// play A sharp
				else
					// play A
				break;
			case 'B':
					// play B
				break;
			case 'C':
				if (my_note[1] == 'S')
					// play C sharp
				else
					// play C
				break;
			case 'D':
				if (my_note[1] == 'S')
					// play D sharp
				else
					// play D
				break;
			case 'E':
					// play E
				break;
			case 'F':
				if (my_note[1] == 'S')
					// play F sharp
				else
					// play F
				break;
			case 'G':
				if (my_note[1] == 'S')
					// play G sharp
				else
					// play G
				break;
		}
		return true;
	}else if ( c->action == 2 ){
		//Do action 2...
		//return true;
	}
	//No known action
	return false;
}


// Consumes a message from the linked list, and gives back a (pointer to a)
// struct containing the parsed info.
// Remember to free the struct after parsing it and using it.
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
// nozero - does not print out command if action is zero
void print_command( command* c , bool nozero){
	if (nozero == true && c->action == 0){
		//do nothing
	}else{
		printf("\nAction: %d\n", c->action);
		printf("Note: %s\n", c->my_note);
	}
}
