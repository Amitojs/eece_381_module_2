
/*
 * EECE 381 Module 2 - Group 3
 * Musical Intrument Android Application
 * VGA graphics source code file
 * Author: Cameron Johnston
 * Date: March 28, 2013
 */


#if 1

#include "VGA.h"
#include "WavOps.h"

// Global structs :O
vga_data v;
mode m;
RB_data rb;

// Struct functions

void updatemode(){
	if (check_switches() % 8 == 0)
		changemode(blank);
	else if (check_switches() % 8 == 1)
		changemode(eq);
	else if (check_switches() % 8 == 2)
		changemode(notegame);
	/*
	else if (check_switches() % 8 == 4)
		changemode(musicdisplay);
	*/
}

void changemode(mode newmode){
	m = newmode;
}

void vga_init()
{
	// Initialise buffers
	v.pixel_buffer = initialise_pixel();
	v.char_buffer = alt_up_char_buffer_open_dev("/dev/char_drawer");
	alt_up_char_buffer_init(v.char_buffer);
	alt_up_char_buffer_clear(v.char_buffer);
	printf("Exiting vga_init\n");
}

void RB_init(){
	m = blank;
	//alt_timestamp_start();
}

void init_rb(int song, int difficulty)
// FUNCTION: Starts a new rock band game
// REQUIRES: Song == {0, 1, 2, 3, 4} && difficulty == {1, 2, 3, 4}
// RETURNS: None
{
	int i;
	rb.song = song;
	rb.difficulty = difficulty;

	// Set time constant and correct zone height based on difficulty
	if(difficulty == 1)
	{
		rb.RB_TIME_CONSTANT_S = 0.1;
		rb.CORRECT_ZONE_HEIGHT = 8;
	}
	else if(difficulty == 2)
	{
		rb.RB_TIME_CONSTANT_S = 0.1;
		rb.CORRECT_ZONE_HEIGHT = 4;
	}
	else if(difficulty == 3)
	{
		rb.RB_TIME_CONSTANT_S = 0.05;
		rb.CORRECT_ZONE_HEIGHT = 8;
	}
	else // difficulty == 4
	{
		rb.RB_TIME_CONSTANT_S = 0.05;
		rb.CORRECT_ZONE_HEIGHT = 4;
	}

	// Fill the arrays based on song
	if(song == 1) // Mary had a little lamb
	{
		rb.notes[0] = 4;
		rb.notes[1] = 2;
		rb.notes[2] = 0;
		rb.notes[3] = 2;
		rb.notes[4] = 4;
		rb.notes[5] = 4;
		rb.notes[6] = 4;
		rb.notes[7] = -1;
		rb.notes[8] = 2;
		rb.notes[9] = 2;
		rb.notes[10] = 2;
		rb.notes[11] = -1;
		rb.notes[12] = 4;
		rb.notes[13] = 7;
		rb.notes[14] = 7;
		rb.notes[15] = -1;
		rb.notes[16] = 4;
		rb.notes[17] = 2;
		rb.notes[18] = 0;
		rb.notes[19] = 2;
		rb.notes[20] = 4;
		rb.notes[21] = 4;
		rb.notes[22] = 4;
		rb.notes[23] = 4;
		rb.notes[24] = 2;
		rb.notes[25] = 2;
		rb.notes[26] = 4;
		rb.notes[27] = 2;
		rb.notes[28] = 0;
		rb.n = 29;
		for(i=29; i<MAX_NOTES_IN_RB_SONG; i++) rb.notes[i] = -1;
	}
	else if(song == 2) // Twinkle twinkle little star
	{
		rb.notes[0] = 0;
		rb.notes[1] = 0;
		rb.notes[2] = 7;
		rb.notes[3] = 7;
		rb.notes[4] = 9;
		rb.notes[5] = 9;
		rb.notes[6] = 7;
		rb.notes[7] = -1;
		rb.notes[8] = 5;
		rb.notes[9] = 5;
		rb.notes[10] = 4;
		rb.notes[11] = 4;
		rb.notes[12] = 2;
		rb.notes[13] = 2;
		rb.notes[14] = 0;
		rb.notes[15] = -1;
		rb.notes[16] = 7;
		rb.notes[17] = 7;
		rb.notes[18] = 5;
		rb.notes[19] = 5;
		rb.notes[20] = 4;
		rb.notes[21] = 4;
		rb.notes[22] = 2;
		rb.notes[23] = -1;
		rb.notes[24] = 7;
		rb.notes[25] = 7;
		rb.notes[26] = 5;
		rb.notes[27] = 5;
		rb.notes[28] = 4;
		rb.notes[29] = 4;
		rb.notes[30] = 2;
		rb.notes[31] = -1;
		rb.notes[32] = 0;
		rb.notes[33] = 0;
		rb.notes[34] = 7;
		rb.notes[35] = 7;
		rb.notes[36] = 9;
		rb.notes[37] = 9;
		rb.notes[38] = 7;
		rb.notes[39] = -1;
		rb.notes[40] = 5;
		rb.notes[41] = 5;
		rb.notes[42] = 4;
		rb.notes[43] = 4;
		rb.notes[44] = 2;
		rb.notes[45] = 2;
		rb.notes[46] = 0;
		rb.n = 47;
	}
	else if(song == 3) // Yankee Doodle
	{
		rb.notes[0] = 5;
		rb.notes[1] = 5;
		rb.notes[2] = 7;
		rb.notes[3] = 9;
		rb.notes[4] = 5;
		rb.notes[5] = 9;
		rb.notes[6] = 7;
		rb.notes[7] = -1;
		rb.notes[8] = 5;
		rb.notes[9] = 5;
		rb.notes[10] = 7;
		rb.notes[11] = 9;
		rb.notes[12] = 5;
		rb.notes[13] = -1;
		rb.notes[14] = 4;
		rb.notes[15] = -1;
		rb.notes[16] = 5;
		rb.notes[17] = 5;
		rb.notes[18] = 7;
		rb.notes[19] = 9;
		rb.notes[20] = 10;
		rb.notes[21] = 9;
		rb.notes[22] = 7;
		rb.notes[23] = 5;
		rb.notes[24] = 4;
		rb.notes[25] = 0;
		rb.notes[26] = 2;
		rb.notes[27] = 4;
		rb.notes[28] = 5;
		rb.notes[29] = -1;
		rb.notes[30] = 5;
		rb.n = 31;
		for(i=31; i<MAX_NOTES_IN_RB_SONG; i++) rb.notes[i] = -1;
	}
	else if(song == 4) // Mexican Hat Dance
	{
		rb.notes[0] = 0;
		rb.notes[1] = 5;
		rb.notes[2] = -1;
		rb.notes[3] = 0;
		rb.notes[4] = 5;
		rb.notes[5] = -1;
		rb.notes[6] = 0;
		rb.notes[7] = 5;
		rb.notes[8] = -1;
		rb.notes[9] = -1;
		rb.notes[10] = -1;
		rb.notes[11] = -1;
		rb.notes[12] = 0;
		rb.notes[13] = 5;
		rb.notes[14] = 7;
		rb.notes[15] = 5;
		rb.notes[16] = 4;
		rb.notes[17] = -1;
		rb.notes[18] = 5;
		rb.notes[19] = 7;
		rb.notes[20] = -1;
		rb.notes[21] = -1;
		rb.notes[22] = -1;
		rb.notes[23] = -1;
		rb.notes[24] = 0;
		rb.notes[25] = 4;
		rb.notes[26] = -1;
		rb.notes[27] = 0;
		rb.notes[28] = 4;
		rb.notes[29] = -1;
		rb.notes[30] = 0;
		rb.notes[31] = 4;
		rb.notes[32] = -1;
		rb.notes[33] = -1;
		rb.notes[34] = -1;
		rb.notes[35] = -1;
		rb.notes[36] = 0;
		rb.notes[37] = 4;
		rb.notes[38] = 5;
		rb.notes[39] = 4;
		rb.notes[40] = 2;
		rb.notes[41] = -1;
		rb.notes[42] = 4;
		rb.notes[43] = 5;
		rb.n = 44;
		for(i=44; i<MAX_NOTES_IN_RB_SONG; i++) rb.notes[i] = -1;
	}

	for(i=0; i<MAX_NOTES_IN_RB_SONG; i++)
	{
		if(song == 0) rb.notes[i] = rand() % 12; // If song 0, randomly generate notes
		if(rb.notes[i] == 0) rb.notes_char[i] = "C";
		else if(rb.notes[i] == 1) rb.notes_char[i] = "C#";
		else if(rb.notes[i] == 2) rb.notes_char[i] = "D";
		else if(rb.notes[i] == 3) rb.notes_char[i] = "D#";
		else if(rb.notes[i] == 4) rb.notes_char[i] = "E";
		else if(rb.notes[i] == 5) rb.notes_char[i] = "F";
		else if(rb.notes[i] == 6) rb.notes_char[i] = "F#";
		else if(rb.notes[i] == 7) rb.notes_char[i] = "G";
		else if(rb.notes[i] == 8) rb.notes_char[i] = "G#";
		else if(rb.notes[i] == 9) rb.notes_char[i] = "A";
		else if(rb.notes[i] == 10) rb.notes_char[i] = "A#";
		else if(rb.notes[i] == 11) rb.notes_char[i] = "B";
		else rb.notes_char[i] = "R"; // R stands for "rest"

		// Initialise
		rb.already_counted[i] = FALSE;
		rb.y_locations[i] = 0;
		rb.x_locations[i] = 10 + 5*rb.notes[i];
		printf("x_locations[%d]: %d\n", i, rb.x_locations[i]);
	}
	rb.index = 0;
	rb.score = 0;
	rb.time = 0.0;
	rb.finished = FALSE;
	//alt_timestamp_start();
	printf("Exiting init_rb\n");
}

void update_rb(int note_pressed)
// FUNCTION: Updates the RB_data struct and displays the new data on the moniter.
// REQUIRES: if no note has been pressed, note_pressed < 0
// 			 if a note has been pressed, 0 <= note_pressed <= 11
// RETURNS: None
{
	// Declare variables
	int i, j, difference;
	char* all_notes[12] = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};

	if(m == notegame) // Check if in rockband mode
	{
		v.blank_flag = FALSE;

		if(rb.background_flag == FALSE)
		{

			// Clear char buffer
			alt_up_char_buffer_clear(v.char_buffer);
			for(j=0; j<12; j++)
				alt_up_char_buffer_string(v.char_buffer, all_notes[j], 10 + 5*j, 55 - rb.CORRECT_ZONE_HEIGHT/2); // Print the pitch at its corresponding location
			rb.background_flag = TRUE;
		}

			/*
			// Draw blue background and correct zone to back buffer

			bluebackground(v.pixel_buffer);

			alt_up_pixel_buffer_dma_draw_hline(v.pixel_buffer, 0, 319, 220-4*rb.CORRECT_ZONE_HEIGHT, 0x0000, 1); // Top of the correct zone

			alt_up_pixel_buffer_dma_draw_box(v.pixel_buffer, 0, 221-4*rb.CORRECT_ZONE_HEIGHT, 319, 219, 0xCCCC, 1);

			alt_up_pixel_buffer_dma_draw_hline(v.pixel_buffer, 0, 319, 220, 0x0000, 1); // Bottom of the correct zone



			// Swap buffers
			alt_up_pixel_buffer_dma_swap_buffers(v.pixel_buffer);

			while (alt_up_pixel_buffer_dma_check_swap_buffers_status(v.pixel_buffer));

			*/

			// Draw blue background and correct zone to back buffer
			bluebackground(v.pixel_buffer);

			draw_correct_zone(v.pixel_buffer, rb.CORRECT_ZONE_HEIGHT);

			// Clear char buffer
			alt_up_char_buffer_clear(v.char_buffer);
			for(j=0; j<12; j++)
				alt_up_char_buffer_string(v.char_buffer, all_notes[j], 10 + 5*j, 55 - rb.CORRECT_ZONE_HEIGHT/2); // Print the pitch at its corresponding location

		// Clear char buffer
		// alt_up_char_buffer_clear(v.char_buffer);

		for(j=0; j<12; j++) rb.in_correct_zone[j] = FALSE; // Reset all entries at each update


		//rb.time = alt_timestamp() / (float) alt_timestamp_freq();
		// Time represents the amount of time passed since the game started, in seconds

		rb.count = rb.time / rb.RB_TIME_CONSTANT_S;
		// Count represents the number of time constants that have passed since the game started

		rb.count_difference = rb.count - rb.old_count;
		// Count_difference represents the number of time constants that have passed since the last time update_rb was called

		rb.old_count = rb.count;
		// Old_count represents the number of time constants passed from the start of the game to the last time update_rb was called

		rb.index = rb.count / 10;
		// Index represents the number of notes that are active
		// printf("Index:%d\n", rb.index);

		if(rb.index > rb.n + 6)
		{
			rb.finished = TRUE;
			m = displayscore;
		}

		rb.bottom_index = -1; // Initialise. This will be changed at some point in the for loop below, or after the for loop



		for(i=0; i<rb.index; i++)
		{
			difference = rb.index - i;
			rb.y_locations[i] = /* 4 + */ difference*10 + rb.count%10;

			// Check if there exists a note to be displayed and it is within range to be displayed on the screen
			if(rb.notes[i] != -1 && rb.y_locations[i] < 66)
			{
				// alt_up_char_buffer_string(v.char_buffer, rb.notes_char[i], rb.x_locations[i], rb.y_locations[i]); // Print the pitch at its corresponding location
				// eraser_rb(v.pixel_buffer, rb.y_locations[i] - rb.count_difference - 1, rb.x_locations[i], rb.CORRECT_ZONE_HEIGHT); // Erase the old note

				draw_rb_note_at(v.pixel_buffer, rb.y_locations[i], rb.x_locations[i]); // Draw new note

				if(rb.y_locations[i] >= 56 - rb.CORRECT_ZONE_HEIGHT && rb.y_locations[i] <= 55) // Check if the location is within the correct range
				{
					rb.in_correct_zone[rb.notes[i]] = TRUE; // Record that the pitch of note i is in the correct zone
					rb.bottom_index = i; // Since note i is in the correct zone
					{
						if(note_pressed == rb.notes[i]) // Check if the note in the correct zone matches the most recent piano key press
						{
							if(rb.already_counted[i] == FALSE)
							{
								rb.score++;
								rb.already_counted[i] = TRUE;
							}
							draw_rb_correct_note_at(v.pixel_buffer, rb.y_locations[i], rb.x_locations[i]);

						}
					}
				}
			}
		}

		if(rb.bottom_index == -1) // This means there was no note within the correct zone
		{
			while(rb.y_locations[i] < 56 - rb.CORRECT_ZONE_HEIGHT) i--;

			rb.bottom_index = i+1; // Set bottom_index to the index of the note closest to, and on top of, the correct zone
		}
		if(note_pressed >= 0) // Check if there has been a note pressed
		{
			if(rb.in_correct_zone[note_pressed] == TRUE) // Check if the note pressed is in the correct zone
			{
				draw_rb_correct_note_at(v.pixel_buffer, rb.y_locations[rb.bottom_index], rb.x_locations[rb.bottom_index]);
				rb.score++;
			}

			else
			{
				draw_rb_incorrect_note_at(v.pixel_buffer, rb.y_locations[rb.bottom_index], rb.x_locations[rb.bottom_index]);
				rb.score--;
			}

		}

		// Swap buffers
		alt_up_pixel_buffer_dma_swap_buffers(v.pixel_buffer);

		while (alt_up_pixel_buffer_dma_check_swap_buffers_status(v.pixel_buffer));


		// Draw blue background and correct zone to back buffer
		/*
		bluebackground(v.pixel_buffer);
		alt_up_pixel_buffer_dma_draw_hline(v.pixel_buffer, 0, 319, 220-4*rb.CORRECT_ZONE_HEIGHT, 0x0000, 1); // Top of the correct zone
		alt_up_pixel_buffer_dma_draw_box(v.pixel_buffer, 0, 221-4*rb.CORRECT_ZONE_HEIGHT, 319, 219, 0xCCCC, 1);
		alt_up_pixel_buffer_dma_draw_hline(v.pixel_buffer, 0, 319, 220, 0x0000, 1); // Bottom of the correct zone
		*/
		// for(;;);
	}
}


// Waiting (blank) mode functions

void draw_nothing()
{
	if(0) // Check if in waiting mode
	{
		bluebackground(v.pixel_buffer);
		alt_up_pixel_buffer_dma_swap_buffers(v.pixel_buffer);
		while (alt_up_pixel_buffer_dma_check_swap_buffers_status(v.pixel_buffer));
		if(v.blank_flag == FALSE)
		{
			alt_up_char_buffer_clear(v.char_buffer);
			alt_up_char_buffer_string(v.char_buffer, "Waiting for user input...", 27, 30);
			v.blank_flag = TRUE;
		}
	}
}


// Equaliser (eq) mode functions

int update_eq_sinc(int amplitude, int green)
// FUNCTION: Updates the equaliser for pretty graphics and swaps the pixel buffer
// REQUIRES: Initialised pixel buffer
// RETURNS: New green value
{
	// Declare variables
	int i, j, red, blue, height, y_value, original_top, x_axis, x_value;
	float period = ((rand() % 200) + 600.0) / 100.0; // Randomly generate period between 6.0 and 8.0
	uint16_t colour;
	int random_amplitude;
	float random_period;

	if(/* alt_timestamp()/(float) alt_timestamp_freq() > EQ_TIME_CONSTANT_S && */ m == eq)
	{
		v.blank_flag = FALSE;
		rb.background_flag = FALSE;
		alt_up_char_buffer_clear(v.char_buffer);
		random_amplitude = (rand() % 50) + 50;
		random_period = ((rand() % 200) + 600.0) / 100.0;
		printf("Random amplitude: %d\n", random_amplitude);
		if(rand() % 1 == 0)
		{
			if(green < 251) green += 5;
		}
		else if(green > 5) green -= 5;
		alt_up_pixel_buffer_dma_clear_screen(v.pixel_buffer, 1); // Clear back buffer
		x_axis = 190;
		original_top = x_axis - x_axis*amplitude/MAX_AMPLITUDE;


		for(x_value=0; x_value < 160; x_value++) // Draw two-sided sinc function, almost to each side of the screen
		{
			red = 255*(160-x_value)/160; // red will increase towards the middle of the screen

			// Calculate value of the sinc function for x-coordinate x_value
			if(x_value>0) height = (x_axis*amplitude/MAX_AMPLITUDE)*sin(x_value/period) /(x_value/period);
			else height = x_axis*amplitude/MAX_AMPLITUDE;

			y_value = x_axis - height;
			if(height>0) // This means the sinc function is above the x-axis
			{
				for(j=y_value; j<=x_axis; j++) // j is the y-coordinate
				{
					blue = 255*(j - original_top)/(x_axis*amplitude/MAX_AMPLITUDE); // blue will increase towards the x_axis of the screen
					colour = drawRGB24toRGB565(red, green, blue);
					i=160-x_value; // i is the x-coordinate
					alt_up_pixel_buffer_dma_draw(v.pixel_buffer, colour, i, j);
					i=160+x_value; // i is the x-coordinate
					alt_up_pixel_buffer_dma_draw(v.pixel_buffer, colour, i, j);
				}
			}
			else // This means the sinc function is on or below the x-axis
			{
				for(j=y_value; j>=x_axis; j--) // j is the y-coordinate
				{
					blue = 255*(2*x_axis-j - original_top)/(x_axis*amplitude/MAX_AMPLITUDE); // blue will increase towards the x_axis of the screen
					colour = drawRGB24toRGB565(red, green, blue);
					i=160-x_value; // i is the x-coordinate
					alt_up_pixel_buffer_dma_draw(v.pixel_buffer, colour, i, j);
					i=160+x_value; // i is the x-coordinate
					alt_up_pixel_buffer_dma_draw(v.pixel_buffer, colour, i, j);
				}
			}
		}
		// Swap buffers
		alt_up_pixel_buffer_dma_swap_buffers(v.pixel_buffer);
		while (alt_up_pixel_buffer_dma_check_swap_buffers_status(v.pixel_buffer));
		// alt_timestamp_start();
	}
	return green;
}


// Display sheet music mode functions

void draw_sheetmusic()
{
	// Symbolic constants
	int x_indent = 16;
	int y_indent = 100;
	int space_height = (240 - 2*y_indent)/4;

	// Declare variables
	int i;

	if(m == blank)
	{
		rb.background_flag = FALSE;
		if(v.blank_flag == FALSE)
		{
			alt_up_pixel_buffer_dma_draw_box(v.pixel_buffer, 0, 0, 319, 239, 0xFFFF, 1); // White box to fill the back buffer
			for(i=0; i<5; i++) // Draw 5 horizontal lines of the musical staff to the back buffer
				alt_up_pixel_buffer_dma_draw_hline(v.pixel_buffer, x_indent-2, 320-(x_indent-2), y_indent+space_height*i, 0x0000, 1);

			// Double bar line at the start
			alt_up_pixel_buffer_dma_draw_box(v.pixel_buffer, x_indent-4, y_indent, x_indent-2, 240-y_indent, 0x0000, 1);
			alt_up_pixel_buffer_dma_draw_vline(v.pixel_buffer, x_indent, y_indent, 240-y_indent, 0x0000, 1);

			// Double bar line at the end
			alt_up_pixel_buffer_dma_draw_box(v.pixel_buffer, 320-(x_indent-4), y_indent, 320-(x_indent-2), 240-y_indent, 0x0000, 1);
			alt_up_pixel_buffer_dma_draw_vline(v.pixel_buffer, 320-x_indent, y_indent, 240-y_indent, 0x0000, 1);

			// Three bar lines to divide the staff into four measures
			alt_up_pixel_buffer_dma_draw_vline(v.pixel_buffer, (160+x_indent)/2, y_indent, 240-y_indent, 0x0000, 1);
			alt_up_pixel_buffer_dma_draw_vline(v.pixel_buffer, 160, y_indent, 240-y_indent, 0x0000, 1);
			alt_up_pixel_buffer_dma_draw_vline(v.pixel_buffer, (480-x_indent)/2, y_indent, 240-y_indent, 0x0000, 1);

			// Draw some notes: C major scale
			draw_qnote_on_sheetmusic(v.pixel_buffer, 0, 0);
			draw_qnote_on_sheetmusic(v.pixel_buffer, 1, 1);
			draw_qnote_on_sheetmusic(v.pixel_buffer, 2, 2);
			draw_qnote_on_sheetmusic(v.pixel_buffer, 3, 3);
			draw_qnote_on_sheetmusic(v.pixel_buffer, 4, 4);
			draw_qnote_on_sheetmusic(v.pixel_buffer, 5, 5);
			draw_qnote_on_sheetmusic(v.pixel_buffer, 6, 6);
			draw_qnote_on_sheetmusic(v.pixel_buffer, 7, 7);
			draw_qnote_on_sheetmusic(v.pixel_buffer, 7, 8);
			draw_qnote_on_sheetmusic(v.pixel_buffer, 6, 9);
			draw_qnote_on_sheetmusic(v.pixel_buffer, 5, 10);
			draw_qnote_on_sheetmusic(v.pixel_buffer, 4, 11);
			draw_qnote_on_sheetmusic(v.pixel_buffer, 3, 12);
			draw_qnote_on_sheetmusic(v.pixel_buffer, 2, 13);
			draw_qnote_on_sheetmusic(v.pixel_buffer, 1, 14);
			draw_qnote_on_sheetmusic(v.pixel_buffer, 0, 15);

			// Blue box and message near top of the screen
			alt_up_pixel_buffer_dma_draw_box(v.pixel_buffer, 100, 26, 220, 40, 0x122B, 1);
			alt_up_char_buffer_clear(v.char_buffer);
			alt_up_char_buffer_string(v.char_buffer, "Waiting for user input...", 28, 8);
			v.blank_flag = TRUE;

			// Swap buffers
			alt_up_pixel_buffer_dma_swap_buffers(v.pixel_buffer);
			while (alt_up_pixel_buffer_dma_check_swap_buffers_status(v.pixel_buffer));


		}
	}
}

void draw_qnote_on_sheetmusic(alt_up_pixel_buffer_dma_dev * pixel_buffer, int pitch, int location)
// FUNCTION: Draws a quarter note with the given pitch at the given location to the back buffer
// REQUIRES: 0 <= pitch <= 7 && 0 <= location <= 15
// RETURNS: None
{
	// Symbolic constants
	int h_spacing = 18;
	int first_note_left = 21;
	int lowc_bottom = 153;

	// Declare variables
	int left, right, top, bottom;

	left = first_note_left + location*h_spacing;
	right = left + 8;
	bottom = lowc_bottom - 5*pitch;
	top = bottom - 6;

	// Draw note with stem
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, left, bottom, right, top, 0x0000, 1);
	if(pitch<6) // Draw stem extending upwards
		alt_up_pixel_buffer_dma_draw_vline(pixel_buffer, right, top, top-32, 0x0000, 1);
	else // Draw stem extending downwards
		alt_up_pixel_buffer_dma_draw_vline(pixel_buffer, left, bottom, bottom+32, 0x0000, 1);

	// Check if the pitch is low C, and if so draw an extra horizontal line
	if(pitch==0)
		alt_up_pixel_buffer_dma_draw_hline(pixel_buffer, left-3, right+3, bottom-3, 0x0000, 1);
}


// Rock band (notegame) mode functions

void draw_correct_zone(alt_up_pixel_buffer_dma_dev* pixel_buffer, int CORRECT_ZONE_HEIGHT)
// FUNCTION: Draws the correct zone for the note game
// REQUIRES: 1 <= CORRECT_ZONE_HEIGHT <= 50
// RETURNS: None
{
	int i;
	alt_up_pixel_buffer_dma_draw_hline(pixel_buffer, 0, 319, 220-4*CORRECT_ZONE_HEIGHT, 0x0000, 1); // Top of the correct zone


	for(i=0; i<320; i++)
	{
		alt_up_pixel_buffer_dma_draw_vline(pixel_buffer, i, 221-4*CORRECT_ZONE_HEIGHT, 219, 0xCCCC, 1);

	}
	alt_up_pixel_buffer_dma_draw_hline(pixel_buffer, 0, 319, 220, 0x0000, 1); // Bottom of the correct zone

}

void eraser_rb(alt_up_pixel_buffer_dma_dev* pixel_buffer, int location, int x_location, int CORRECT_ZONE_HEIGHT)
// FUNCTION: Draws over the note at the given location in the appropriate background colour to the backbuffer
// REQUIRES: 1 <= location <= 60 && 1 <= x_location <= 80 && 1 <= CORRECT_ZONE_HEIGHT <= 50
// RETURNS: None
{
	if(location < 55 - CORRECT_ZONE_HEIGHT - 2) // location is completely outside of correct zone. Erase in blue background colour.
	{
#if 1
		// Draw double thickness square in blue background colour
		alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, x_location*4 - 9, location*4 - 12, x_location*4 + 11, location*4 + 8,0x122B, 1);

		alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, x_location*4 - 8, location*4 - 11,  x_location*4 + 10, location*4 + 7,0x122B, 1);

		alt_up_pixel_buffer_dma_draw_box(pixel_buffer, x_location*4 - 9, location*4 - 16,  x_location*4 + 11, location*4 - 13,0x122B, 1);

#endif

#if 0
		alt_up_pixel_buffer_dma_draw_box(pixel_buffer, x_location*4 - 9, location*4 - 16,  x_location*4 + 11, location*4 + 10,0x122B, 1);
#endif
	}
	else // Some overlap with correct zone. Redraw a portion of the correct zone
	{
#if 1
		// Draw double thickness square in blue background colour
		alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, x_location*4 - 9, location*4 - 12, x_location*4 + 11, location*4 + 8,0x122B, 1);

		alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, x_location*4 - 8, location*4 - 11,  x_location*4 + 10, location*4 + 7,0x122B, 1);

		alt_up_pixel_buffer_dma_draw_box(pixel_buffer, x_location*4 - 9, location*4 - 16,  x_location*4 + 11, location*4 - 13,0x122B, 1);

#endif

#if 0
		// alt_up_pixel_buffer_dma_draw_box(pixel_buffer, x_location*4 - 9, location*4 - 16,  x_location*4 + 11, location*4 + 10,0x122B, 1);
#endif

		alt_up_pixel_buffer_dma_draw_hline(pixel_buffer, x_location*4 - 9, x_location*4 + 11, 220-4*CORRECT_ZONE_HEIGHT, 0x0000, 1); // Top of the correct zone

		alt_up_pixel_buffer_dma_draw_box(pixel_buffer, x_location*4 - 9, 221-4*CORRECT_ZONE_HEIGHT,  x_location*4 + 11, 219, 0xCCCC, 1); // Correct zone

		alt_up_pixel_buffer_dma_draw_hline(pixel_buffer, x_location*4 - 9, x_location*4 + 11, 220, 0x0000, 1); // Bottom of the correct zone

	}
}

void draw_rb_note_at(alt_up_pixel_buffer_dma_dev* pixel_buffer, int location, int x_location)
// FUNCTION: Draws the template for a note in the rock band game mode to the back buffer.
// Doesn't write the pitch to the char buffer. This is done inside the update_rockband function.
// REQUIRES: 1 <= location <= 60
// RETURNS: None
{
	// Draw double thickness square in black
	alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, x_location*4 - 9, location*4 - 12, x_location*4 + 11, location*4 + 8,0x0000, 1);

	alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, x_location*4 - 8, location*4 - 11,  x_location*4 + 10, location*4 + 7,0x0000, 1);

}

void draw_rb_correct_note_at(alt_up_pixel_buffer_dma_dev* pixel_buffer, int location, int x_location)
// FUNCTION: Draws the template for a correct note in the rock band game mode to the back buffer.
// Doesn't write the pitch to the char buffer. This is done inside the execute_rockband function.
// REQUIRES: 1 <= location <= 60
// RETURNS: None
{
	/*
	// Draw double thickness square in black
	alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, x_location*4 - 9, location*4 - 12, x_location*4 + 11, location*4 + 8,0x0000, 1);
	alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, x_location*4 - 8, location*4 - 11,  x_location*4 + 10, location*4 + 7,0x0000, 1);
	*/

	// Fill the inside in green
	uint16_t fill_colour = drawRGB24toRGB565(0, 114, 54); // Dark green
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, x_location*4 - 7, location*4 - 10,  x_location*4 + 9, location*4 + 6, fill_colour, 1);

}

void draw_rb_incorrect_note_at(alt_up_pixel_buffer_dma_dev* pixel_buffer, int location, int x_location)
// FUNCTION: Draws the template for an incorrect note in the rock band game mode to the back buffer.
// Doesn't write the pitch to the char buffer. This is done inside the update_rb function.
// REQUIRES: 1 <= location <= 60
// RETURNS: None
{
	/*
	// Draw double thickness square in black
	alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, x_location*4 - 9, location*4 - 12, x_location*4 + 11, location*4 + 8,0x0000, 1);
	alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, x_location*4 - 8, location*4 - 11,  x_location*4 + 10, location*4 + 7,0x0000, 1);
	*/

	// Fill the inside in green
	uint16_t fill_colour = drawRGB24toRGB565(0x66, 0x33, 0x00); // Brown cave colour
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, x_location*4 - 7, location*4 - 10,  x_location*4 + 9, location*4 + 6, fill_colour, 1);

}

_Bool is_rb_finished()
{
	return rb.finished;
}


// Display score functions

void display_score()
{
	char* display_score_message[20];
	if(m == displayscore)
	{
		bluebackground(v.pixel_buffer);

		// Swap buffers
		alt_up_pixel_buffer_dma_swap_buffers(v.pixel_buffer);
		while (alt_up_pixel_buffer_dma_check_swap_buffers_status(v.pixel_buffer));

		alt_up_char_buffer_clear(v.char_buffer);
		sprintf( display_score_message, "FINAL SCORE: %d", rb.score );
		alt_up_char_buffer_string(v.char_buffer, "GAME OVER.", 36, 20);
		alt_up_char_buffer_string(v.char_buffer, display_score_message, 32, 30);
	}
}


// Colour converter

uint16_t drawRGB24toRGB565(uint8_t r, uint8_t g, uint8_t b)
{
	// PURPOSE:		take hex numbers and return a close colour
	// RETURNS:		A 16bit hex value
	return ((r / 8) << 11) | ((g / 4) << 5) | (b / 8);
}


// General purpose functions

void bluebackground(alt_up_pixel_buffer_dma_dev* pixel_buffer)
{
	// PURPOSE:		draws a light blue background to back buffer
	// REQUIRES:	pixel_buffer != NULL
	// RETURNS:		nothing

	int i;
	for(i=0; i<320; i++)
	{
		alt_up_pixel_buffer_dma_draw_vline(pixel_buffer, i, 0, 239, 0x122B, 1);

	}
	// alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 0, 0, 319, 239, 0x122B, 1);
	return;
}

int check_switches()
// FUNCTION: Reads the value of all switches
// RETURNS: Value of all switches
{

	return IORD_8DIRECT(SWITCHES_BASE, 0);
}

alt_up_pixel_buffer_dma_dev * initialise_pixel()
// PURPOSE:	to set up the VGA adapter
// RETURNS:	nothing
{
	alt_up_pixel_buffer_dma_dev * pixel_buffer = alt_up_pixel_buffer_dma_open_dev("/dev/video_pixel_buffer_dma_0");

	unsigned int pixel_buffer_addr1 = 0x80000;
	unsigned int pixel_buffer_addr2 = 0x80000 + (320 * 240 * 2);

	// Set the 1st buffer address
	alt_up_pixel_buffer_dma_change_back_buffer_address(pixel_buffer,pixel_buffer_addr1);
	// Swap buffers - we have to swap because there is only an API function
	// to set the address of the background buffer.

	alt_up_pixel_buffer_dma_swap_buffers(pixel_buffer);
	while (alt_up_pixel_buffer_dma_check_swap_buffers_status(pixel_buffer));

	// Set the 2nd buffer address
	alt_up_pixel_buffer_dma_change_back_buffer_address(pixel_buffer,pixel_buffer_addr2);
	// Clear both buffers (this makes all pixels black)
	alt_up_pixel_buffer_dma_clear_screen(pixel_buffer, 0);
	alt_up_pixel_buffer_dma_clear_screen(pixel_buffer, 1);

	return pixel_buffer;
}

#endif
