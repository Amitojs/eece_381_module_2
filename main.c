/*
 * main.c
 *
 *  Created on: Mar 13, 2013
 *      Author: Scott
 *
 *
 *      Version: 5.3.0
 *
 *
 */


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
#include "WavOps.h"
#include "interface_SD.h"
#include "VGA.h"

#if 1
int main(){
	//Wave** pianoArr;
	int i=0;
	int k = 0;
	//score;
	command* c;

	mystate = setup;

	rsinit();
	setup_timer();
	sd_init();
	wavInit();
	vga_init();
	//init_rb(2, 1);
	//changemode( notegame );
	load_piano();
	load_drums();
	changemode( blank );
	draw_sheetmusic();

	mystate = ready;

	for(;;){
		if (i%100 == 0 ){
			c = consume_message( get_head() );

			if ( !do_command( c ) ) {
				if (c->action != 0){
					printf("Command error:");
					print_command( c, false );
				}
			}
			free(c);
			c = NULL;
		}

		/*
		if (i%500 == 0){
			update_rb( -2 );
			draw_sheetmusic();
			//if( rb_isfinished() ){
			//	score = rb_score();
			//	printf("Score:%d\n", score );
			//	changemode ( blank );
			//}
		}
		 */
		i++;
	}

	return 0;}
#endif
