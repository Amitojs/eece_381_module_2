/*
 * EECE 381 Module 2 - Group 3
 * Musical Intrument Android Application
 * VGA graphics header file
 * Author: Cameron Johnston
 * Date: March 28, 2013
 */

#ifndef VGA_H_
#define VGA_H_

// Header files
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "system.h"
#include <altera_up_avalon_video_pixel_buffer_dma.h>
#include <altera_up_avalon_video_character_buffer_with_dma.h>
#include <altera_avalon_timer.h>
#include "sys/alt_timestamp.h"
#include "sys/alt_alarm.h"
#include <math.h>
#include <stdint.h>
#include <altera_up_sd_card_avalon_interface.h>
#include <io.h>


// Symbolic constants
#define EQ_TIME_CONSTANT_S 0.01
#define MAX_AMPLITUDE 100
#define MAX_NOTES_IN_RB_SONG 47
#define TRUE 1
#define FALSE 0


//*** Structs ***//

typedef enum {blank, eq, notegame, displayscore} mode;

typedef struct vga_data{
	alt_up_pixel_buffer_dma_dev* pixel_buffer;
	alt_up_char_buffer_dev* char_buffer;
	_Bool blank_flag;
}vga_data;

typedef struct RB_data
{
	int n; // The length of the song
	int song, difficulty, CORRECT_ZONE_HEIGHT, score; // Self-explanatory?
	int count; // Used to create the appropriate spacing between notes on the screen
	int old_count; // The previously recorded count from the last time update_rb was called
	int count_difference; // count - old_count. Used to know where to erase previous notes
	int index;
	int bottom_index; // Index of the note closest to the correct zone. Range: 0 to MAX_NOTES_IN_RB_SONG
	float RB_TIME_CONSTANT_S; // 10 time constants will pass for each note in the song
	float time; // The amount of time since the game started
	int notes[MAX_NOTES_IN_RB_SONG], x_locations[MAX_NOTES_IN_RB_SONG], y_locations[MAX_NOTES_IN_RB_SONG];
	char* notes_char[MAX_NOTES_IN_RB_SONG]; // Strings representing the pitch of each note
	_Bool in_correct_zone[12]; // Records whether there is currently a note of each pitch in the correct zone
	_Bool already_counted[MAX_NOTES_IN_RB_SONG];
	_Bool background_flag; // TRUE iff the background for the rockband game has already been drawn
	_Bool printf_flag;
	_Bool finished;
}RB_data;


//*** Function signatures ***//

// Struct functions
void updatemode();
void changemode(mode newmode);
void vga_init();
void RB_init();
void init_rb(int song, int difficulty);
void update_rb(int note_pressed);

// Equaliser (eq) mode functions
int update_eq_sinc(int amplitude, int green);

// Display sheet music mode functions
void draw_sheetmusic();
void draw_qnote_on_sheetmusic(alt_up_pixel_buffer_dma_dev* pixel_buffer, int pitch, int location);

// Rock band (notegame) mode functions
void draw_correct_zone(alt_up_pixel_buffer_dma_dev* pixel_buffer, int CORRECT_ZONE_HEIGHT);
void eraser_rb(alt_up_pixel_buffer_dma_dev* pixel_buffer, int location, int x_location, int CORRECT_ZONE_HEIGHT);
void draw_rb_note_at(alt_up_pixel_buffer_dma_dev* pixel_buffer, int location, int x_location);
void draw_rb_correct_note_at(alt_up_pixel_buffer_dma_dev* pixel_buffer, int location, int x_location);
void draw_rb_incorrect_note_at(alt_up_pixel_buffer_dma_dev* pixel_buffer, int location, int x_location);
_Bool is_rb_finished();

// Display score functions
void display_score();

// Colour converter
uint16_t drawRGB24toRGB565(uint8_t, uint8_t, uint8_t);

// General purpose functions
void bluebackground(alt_up_pixel_buffer_dma_dev* pixel_buffer);
int check_switches();
alt_up_pixel_buffer_dma_dev * initialise_pixel();


#endif /* VGA_H_ */
