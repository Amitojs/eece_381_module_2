/*
 * rs232.c
 *
 *  Created on: Mar 6, 2013
 *      Author: Scott
 *
 *
 *      Version: 2.0.0
 *
 *
 */

#include "rs232.h"
#include <stdio.h>
#include "altera_up_avalon_rs232.h"
#include <string.h>
#include <io.h>
#include "alt_types.h"
#include "sys/alt_irq.h"
#include "altera_avalon_timer_regs.h"


// This funciton will be called on even interval of TIMER_INTERVAL
void timed_function(){
	//TODO: Do something useful with this interval
	printf("hi");
}


// The function called on IQR from the timer 0.
// IE, this is the ISR. It will call timed_function() to do something useful,
// then it will re-build the timer, and set it.
void handle_timer_interrupt (void* context, alt_u32 id){
	int timer_period = TIMER_INTERVAL * 50000000;

	// Stop timer
	IOWR_16DIRECT(MY_HW_ONLY_TIMER_BASE, 4, 1 << 3);

	// Setup period (ex. 5 seconds)
	IOWR_16DIRECT(MY_HW_ONLY_TIMER_BASE, 8, timer_period & 0xFFFF);
	IOWR_16DIRECT(MY_HW_ONLY_TIMER_BASE, 12, timer_period >> 16);

	// Start timer
	IOWR_16DIRECT(MY_HW_ONLY_TIMER_BASE, 4, 1 << 2);
	IOWR_ALTERA_AVALON_TIMER_CONTROL(MY_HW_ONLY_TIMER_BASE, 1);

	// Do something useful when the ISR is called
	timed_function();

	// Clear the status bit
	IOWR_ALTERA_AVALON_TIMER_STATUS(MY_HW_ONLY_TIMER_BASE, 0);
}


// Sets up the timer 0 with TIMER_INTERVAL in seconds, and starts the timer.
// In addition, registers the timer interrupt handler.
void setup_timer(){
	int status;
	int timer_period = TIMER_INTERVAL * 50000000;

	// Register the timer interrupt handler
	alt_irq_register(1, 0, handle_timer_interrupt);

	// Setup period
	IOWR_16DIRECT(MY_HW_ONLY_TIMER_BASE, 8, timer_period & 0xFFFF);
	IOWR_16DIRECT(MY_HW_ONLY_TIMER_BASE, 12, timer_period >> 16);

	// Stop the timer
	status = IORD_16DIRECT(MY_HW_ONLY_TIMER_BASE, 0);
	//if (status & 0x2) {
	// Force stop timer
	IOWR_16DIRECT(MY_HW_ONLY_TIMER_BASE, 4, 1 << 3);
	//	printf(" Stopping Timer\n");}

	// Start the timer
	printf("Starting Timer\n");
	IOWR_16DIRECT(MY_HW_ONLY_TIMER_BASE, 4, 1 << 2);

	// Make the timer send out IRQ
	IOWR_ALTERA_AVALON_TIMER_CONTROL(MY_HW_ONLY_TIMER_BASE, 1);
}


// Sets the timer 0 to stop
void kill_timer(){
	// Stop the timer
	//int status = IORD_16DIRECT(MY_HW_ONLY_TIMER_BASE, 0);
	//if (status & 0x2) {
	// Force stop timer
	IOWR_16DIRECT(MY_HW_ONLY_TIMER_BASE, 4, 1 << 3);
	printf("Stopping Timer\n");
}


// Appends a single char to the end of a string
void append ( unsigned char* s, char c ) {
	int len = (int) strlen( (char*) s);
	s[len] = c;
	s[len+1] = '\0';
}


// Initialize the RS232 connection & struct
rsinfo rsinit (  ) {
	rsinfo a;
	printf("UART Initialization\n");
	a.uart = alt_up_rs232_open_dev(RS232_0_NAME);
	return a;
}


// Send data over the RS232
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


// Pull data from the RS232
// Currently waits until data is present, then reads.
void rsrecieve ( rsinfo a, unsigned char* s1_ptr ) {
	int i = 0;

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
