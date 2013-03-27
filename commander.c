/*
 * commander.c
 *
 *  Created on: Mar 13, 2013
 *      Author: Scott
 *
 *
 *      Version: 1.4.1
 *
 *
 */

#include "rs232.h"
#include "commander.h"
#include "WavOps.h"
#include <stdio.h>
#include <string.h>
#include <io.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "RBheader.h"

Wave** pianoArr;
int green = 150;


// Completes an action from a command.
// Returns true if successful, false if the action is unknown.
bool do_command( command* c ){
	if ( c->action == 0 ){
		return false;
	}else if ( c->action == 1 && mystate == play){
		switch ( c->my_note[0] ){
		case 'A':
			if (c->my_note[1] == 'S'){
				playSong(*(pianoArr+10));
				green = update_eq_sinc(95, green);
			}else{
				playSong(*(pianoArr+9));
				green = update_eq_sinc(90, green);
			}break;
		case 'B':
			playSong(*(pianoArr+11));
			green = update_eq_sinc(100, green);
			break;
		case 'C':
			if (c->my_note[1] == 'S'){
				playSong(*(pianoArr+1));
				green = update_eq_sinc(10, green);
			}else{
				playSong(*(pianoArr+0));
				green = update_eq_sinc(0, green);
			}break;
		case 'D':
			if (c->my_note[1] == 'S'){
				playSong(*(pianoArr+3));
				green = update_eq_sinc(30, green);
			}else{
				playSong(*(pianoArr+2));
				green = update_eq_sinc(20, green);
			}break;
		case 'E':
			playSong(*(pianoArr+4));
			green = update_eq_sinc(40, green);
			break;
		case 'F':
			if (c->my_note[1] == 'S'){
				playSong(*(pianoArr+6));
				green = update_eq_sinc(60, green);
			}else{
				playSong(*(pianoArr+5));
				green = update_eq_sinc(50, green);
			}break;
		case 'G':
			if (c->my_note[1] == 'S'){
				playSong(*(pianoArr+8));
				green = update_eq_sinc(80, green);
			}else{
				playSong(*(pianoArr+7));
				green = update_eq_sinc(70, green);
			}break;
		}
		return true;


	}else if ( c->action == 2 ){
		// Being told to set up an instrument
		if (mystate != ready) return false;

		if (c->my_note[0] == 'P'){
			printf("Time to load piano stuff!\n");
			pianoArr = pianoInit();
			rssend("play");
			mystate = play;
			return true;

		}else if (c->my_note[0] == 'D'){
			printf("Time to load (drums) piano stuff!\n");
			pianoArr = pianoInit();
			rssend("play");
			mystate = play;
			return true;
		}


	}else if (c->action == 3){
		// Being told to stahp
		mystate = ready;
		return true;
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

	// If we have no message, send back a blank message
	if ( head == NULL){
		c->action = 0;
		c->my_note[0] = '\0';
		c->my_note[1] = '\0';
		return c;
	}else {
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

		if ( message[2] == '#' )
			c->my_note[1] = 'S';
		else
			c->my_note[1] = '\0';

	}else if (message[0] == '2'){
		c->my_note[0] = message[1];
		c->my_note[1] = '\0';
	}else{// message[0] != '1';
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
