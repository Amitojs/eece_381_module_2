/*
 * commander.h
 *
 *  Created on: Mar 13, 2013
 *      Author: Scott
 *
 *
 *      Version: 1.0.0
 *
 *
 */

#ifndef COMMANDER_H_
#define COMMANDER_H_

#include "rs232.h"

typedef struct command{
	int action;
	char my_note[2];
} command;

void	print_command	( command* c );
command* consume_message	( llist *head );

#endif /* COMMANDER_H_ */
