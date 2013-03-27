/*
 * commander.h
 *
 *  Created on: Mar 13, 2013
 *      Author: Scott
 *
 *
 *      Version: 1.4.1
 *
 *
 */

/*
-------------------------------------------
Sample use = Consume
-------------------------------------------

#include "rs232.h"
#include "commander.h"
#include <stdio.h>
#include <stdlib.h>
#include "altera_up_avalon_rs232.h"
#include <string.h>
#include <io.h>
#include "alt_types.h"
#include "sys/alt_irq.h"
#include "altera_avalon_timer_regs.h"

int main(){
	int i;
	command* c;

	setup_timer();
	rsinit();

	for(;;){
		if (i%500000 == 0){
			c = consume_message( get_head() );
			print_command( c );
			free(c);
		}
		i++;
	}

	return 0;
}
 */



#ifndef COMMANDER_H_
#define COMMANDER_H_

#include "rs232.h"


#define afile  "a.wav"
#define asfile "as.wav"
#define bfile  "b.wav"
#define cfile  "c.wav"
#define csfile "cs.wav"
#define dfile  "d.wav"
#define dsfile "ds.wav"
#define efile  "e.wav"
#define ffile  "f.wav"
#define fsfile "fs.wav"
#define gfile  "g.wav"
#define gsfile "gs.wav"



//--- The structure for a message to be sent/recieved ---
typedef struct command{
	int action;
	char my_note[2];
} command;

// State definitions --WIP
typedef enum { setup, ready, play } state;
state mystate;

//--- Functions used by the command structure
void		print_command	( command* c, bool nozero );
command*	consume_message	( llist *head );
bool 		do_command		( command* c );

#endif /* COMMANDER_H_ */
