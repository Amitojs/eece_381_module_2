/*
 * rs232.h
 *
 *  Created on: Mar 6, 2013
 *      Author: Scott
 *
 *
 *      Version: 3.1.1
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
	rsinit();

	for(;;){
		// Clear any string data
		message[0] = '\0';
		s1[0] = '\0';

		// Receive the message from the Middleman
		rsrecieve( s1_ptr );

		// Take the string and reorganize it backwards
		for (i = 0; i <= strlen( (char*)s1 ); i++){
			append(message, s1[strlen(( char*)s1 )-i]);
		}

		//printf("Sending message: '%s'\n", message);

		// Send the message to the Middleman
		rssend( message );
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
	int i;

	setup_timer();
	rsinit();

	print_list();

	for ( i = 0; i<10000000; i++ ){
		if (i%50000 == 0)
			printf(".");
	}
	printf("end");

	print_list();

	return 0;
}

-------------------------------------------

 */



#ifndef RS232_H_
#define RS232_H_

#include "altera_up_avalon_rs232.h"
#include <stdbool.h>



//String size of data rec/sent
#define MAX_STRING_SIZE 8

//Base address of timer
#define MY_HW_ONLY_TIMER_BASE 0x1000

// Interval of timer checking in ms
#define TIMER_INTERVAL 250



//--- Structs ---
typedef struct{
	alt_up_rs232_dev* uart;
	unsigned char data;
	unsigned char parity;
} rsinfo;

typedef struct llist{
	unsigned char message[MAX_STRING_SIZE];
    struct llist *next;
} llist;



//--- RS232 stuff ---
void 	rssend					( unsigned char message[] );
void 	append					( unsigned char* s, char c );
void 	rsrecieve				( unsigned char* s1_ptr );
rsinfo 	rsinit					(  );


//--- Timer stuff ---
void 	timed_function			(  );
void 	handle_timer_interrupt 	( void* context, alt_u32 id );
void 	setup_timer				(  );
void 	kill_timer				(  );


//--- Linked list stuff ---
void 	delete_head_from_list	(  );
llist* 	add_to_list				( unsigned char message[], bool add_to_end );
llist* 	create_list				( unsigned char message[] );
void 	print_list				(  );
llist*	get_head				(  );


#endif /* RS232_H_ */
