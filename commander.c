/*
 * commander.c
 *
 *  Created on: Mar 13, 2013
 *      Author: Scott
 *
 *
 *      Version: 2.1.0
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
#include "VGA.h"

//Wave** pianoArr;
int green = 150;

Wave* parr[12] = {0};
Wave* darr[12] = {0};


unsigned char play_message[] = "play";


// Completes an action from a command.
// Returns true if successful, false if the action is unknown.
bool do_command( command* c ){
	if ( c->action == 0 ){
		return false;
	}else if ( c->action == 1 && mystate == play){
		switch ( c->my_note[0] ){
		case 'A':
			if (c->my_note[1] == 'S'){
				//playSong(*(pianoArr+10));
				play_in_parr(10);
				green = update_eq_sinc(95, green);
				update_rb( 10 );
			}else{
				//playSong(*(pianoArr+9));
				play_in_parr(9);
				green = update_eq_sinc(90, green);
				update_rb( 9 );
			}break;
		case 'B':
			//playSong(*(pianoArr+11));
			play_in_parr(11);
			green = update_eq_sinc(100, green);
			update_rb( 11 );
			break;
		case 'C':
			if (c->my_note[1] == 'S'){
				//playSong(*(pianoArr+1));
				play_in_parr(1);
				green = update_eq_sinc(10, green);
				update_rb( 1 );
			}else{
				//playSong(*(pianoArr+0));
				play_in_parr(0);
				green = update_eq_sinc(0, green);
				update_rb( 0 );
			}break;
		case 'D':
			if (c->my_note[1] == 'S'){
				play_in_parr(3);
				//playSong(*(pianoArr+3));
				green = update_eq_sinc(30, green);
				update_rb( 3 );
			}else{
				//playSong(*(pianoArr+2));
				play_in_parr(2);
				green = update_eq_sinc(20, green);
				update_rb( 2 );
			}break;
		case 'E':
			//playSong(*(pianoArr+4));
			play_in_parr(4);
			green = update_eq_sinc(40, green);
			update_rb( 4 );
			break;
		case 'F':
			if (c->my_note[1] == 'S'){
				play_in_parr(6);
				//playSong(*(pianoArr+6));
				green = update_eq_sinc(60, green);
				update_rb( 6 );
			}else{
				//playSong(*(pianoArr+5));
				play_in_parr(5);
				green = update_eq_sinc(50, green);
				update_rb( 5 );
			}break;
		case 'G':
			if (c->my_note[1] == 'S'){
				//playSong(*(pianoArr+8));
				play_in_parr(8);
				green = update_eq_sinc(80, green);
				update_rb( 8 );
			}else{
				//playSong(*(pianoArr+7));
				play_in_parr(7);
				green = update_eq_sinc(70, green);
				update_rb( 7 );
			}break;
		case 's':
			if (c->my_note[1] == 'd'){
				play_in_darr(0);
			} else {
				play_in_darr(3);
			}break;
		case 'b':
			play_in_darr(1);
			break;
		case 'l':
			play_in_darr(2);
			break;
		case 'c':
			//play_in_darr(4);
			break;
		case 'r':
			//play_in_darr(5);
			break;
		}
		return true;


	}else if ( c->action == 2 ){
		// Being told to set up an instrument
		//if (mystate != ready) return false;
		//kill_timer();
		if (c->my_note[0] == 'P'){
			printf("Time to load piano stuff!\n");
			//pianoArr = pianoInit();
			//load_piano();
			rssend(play_message);
			mystate = play;
			return true;

		}else if (c->my_note[0] == 'D'){
			printf("Time to load drum stuff!\n");
			//pianoArr = pianoInit();
			//load_drums();
			rssend(play_message);
			mystate = play;
			return true;
		}
		//setup_timer();

	}else if (c->action == 3){
		// Being told to stahp
		mystate = ready;
		return true;
	}else if (c->action == 4){
		//Going to play rockband
		//if (!isfinished()){
		init_rb(c->my_note[0] - '0', 1); //c->my_note[0]
		changemode( notegame );
		//}
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

	// One command and two arguments - Piano playing
	if (message[0] == '1'){
		c->my_note[0] = message[1];

		if ( message[2] == '#' )
			c->my_note[1] = 'S';
		else
			c->my_note[1] = '\0';

		// One command and one argument
	}else if (message[0] == '2' || message[0] == '4'){
		c->my_note[0] = message[1];
		c->my_note[1] = '\0';

		// No command known
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

void play_in_parr(int n){
	playSong(parr[n]);
}


void play_in_darr(int n){
	playSong(darr[n]);
}

void load_drums( void ){
	int i;
	for (i=0;i<12;i++){
		if (darr[i] == NULL || darr[i] == 0){

		}else
			free(darr[i]);
	}
	printf("Loading Drums into memory ");
	darr[0] = isWav("s.wav");
	printf(".");
	darr[1] = isWav("k.wav");
	printf(".");
	darr[2] = isWav("bt.wav");
	printf(".");
	darr[3] = isWav("lt.wav");
	printf(".");
	darr[4] = isWav("cc.wav");
	printf(".");
	darr[5] = isWav("rc.wav");
	printf("Done\n");
}


void load_piano ( void ) {
	int i;
	for (i=0;i<12;i++){
		if (parr[i] == NULL || parr[i] == 0){

		} else
			free(parr[i]);
	}

	printf("Loading Piano into memory ");
	parr[0] = isWav("c.wav");
	printf(".");
	parr[1] = isWav("cs.wav");
	printf(".");
	parr[2] = isWav("d.wav");
	printf(".");
	parr[3] = isWav("ds.wav");
	printf(".");
	parr[4] = isWav("e.wav");
	printf(".");
	parr[5] = isWav("f.wav");
	printf(".");
	parr[6] = isWav("fs.wav");
	printf(".");
	parr[7] = isWav("g.wav");
	printf(".");
	parr[8] = isWav("gs.wav");
	printf(".");
	parr[9] = isWav("a.wav");
	printf(".");
	parr[10] = isWav("as.wav");
	printf(".");
	parr[11] = isWav("b.wav");
	printf("Done\n");
}
