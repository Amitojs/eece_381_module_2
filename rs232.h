/*
 * rs232.h
 *
 *  Created on: Mar 6, 2013
 *      Author: Scott
 *
 *
 *      Version: 2.0.0
 *
 *
 */

/*
-------------------------------------------
Sample use = Simple wait for data
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
Sample use = Using timer to check for data
-------------------------------------------

#include "rs232.h"
#include <stdio.h>
#include "altera_up_avalon_rs232.h"
#include <string.h>
#include <io.h>
#include "alt_types.h"
#include "sys/alt_irq.h"
#include "altera_avalon_timer_regs.h"

int main(){
	int i=0;

	setup_timer();

	//TODO:
	//@@@@WORK IN PROGRESS@@@
	for(;;) {
		i++;
		if (i%100000 == 0) printf(".");
	}

	return 0;
}

-------------------------------------------

 */



#ifndef RS232_H_
#define RS232_H_

#include "altera_up_avalon_rs232.h"

//String size of data rec/sent
#define MAX_STRING_SIZE 265

//Base address of timer
#define MY_HW_ONLY_TIMER_BASE 0x1000

// Interval of timer checking
#define TIMER_INTERVAL 5

typedef struct{
	alt_up_rs232_dev* uart;
	unsigned char data;
	unsigned char parity;
} rsinfo;

void 	rssend					( rsinfo a, unsigned char message[] );
void 	append					( unsigned char* s, char c );
void 	rsrecieve				( rsinfo a, unsigned char* s1_ptr );
rsinfo 	rsinit					(  );
void 	timed_function			(  );
void 	handle_timer_interrupt 	( void* context, alt_u32 id );
void 	setup_timer				(  );
void 	kill_timer				(  );


#endif /* RS232_H_ */
