/*
 * project.c
 *
 *  Created on: Jan 8, 2023
 *      Author: bruce
 */

#include "project.h"
#include "printf.h"
#include <string.h>
#include "LED.h"
#include "systick.h"
#include "UART.h"
#include "midiparser.h"
#include "GPIO.h"
#include "stm32l4xx_hal.h"
#include "trackparser.h"
#include "song.h"
#include "tone.h"

uint8_t mode = 0; // flag to keep track between local vs remote modes
int current_song_num = 0;
unsigned char* current_song;
int size; // size of current song
int t = 0; // holds tempo of current song (didnt want to use 't' but 'tempo' is used elsewhere)
int d = 0; // holds division of current song (didn't want to use 'd' but 'division' is used elsewhere)

/**
 *  This is the inerrupt handler for the B1 Button. It
 *  simply toggles the state of the mode variable from 0 to 1
 *  or vice versa. Also prints out message telling the user whether
 *  they are in remote or local mode, and turns LED off upon switching
 *  modes.
 */
void EXTI15_10_IRQHandler () {
	EXTI->PR1 |= (1 << 13);

	mode = !mode;

	if(mode == 1)
		printf("\r\n%s\r\n", "***MANUAL OVERRIDE ACTIVE***");
	if(mode == 0)
		printf("\r\n%s\r\n", "***REMOTE MODE ACTIVE***");

	stop();
}

int systickCounter = 0; // keeps track of how many milliseconds the s1 button is held. used exclusively in this method
int systickTotal = 0; // keeps track of total milliseconds the s1 button is held. used in run_project()
int pause_toggle = 0; // toggle variable used when s1 is hit once to switch from play to pause.
int button = 0;

/*
 * This is the interrupt handler for the s1 button. When fired,
 * it toggles the pause_toggle variable between 0 and 1. Used in
 * run_project to determine what satte the LED is in.
 */
void EXTI9_5_IRQHandler() {
	EXTI->PR1 |= (1<<9);

	if (HAL_GPIO_ReadPin(S1_GPIO_Port, S1_Pin) == GPIO_PIN_SET){
		if(pause_toggle == 0){
			pause_toggle = 1;
		}
		else if (pause_toggle == 1){
			pause_toggle = 0;
		}
	}
}

unsigned char s1_pin; // variable to hold information about the s1 button's pin

/**
 * displays list of all available commands
 * to the terminal.
 */
void display_menu(){
	printf("%s\r\n", "***REMOTE LED CONTROL MENU***");
	printf("%s\r\n", "Available User Commands");
	printf("%s\r\n", "NEXT - Show next song info");
	printf("%s\r\n", "PLAY - Play the song (LED On)");
	printf("%s\r\n", "PAUSE - Pause the song (LED Flash)");
	printf("%s\r\n", "STOP - Stop the song (LED Off)");

}

/**
 * Handles 'next' command. Calls parsenext()
 * function in midiparser.c to read midi data.
 * changes song num depending on the current song,
 * and sets useful information regarding current song
 * and its size
 */
void next(){
	song current_song_array = get_song(current_song_num);
	current_song = current_song_array.p_song;
	size = current_song_array.size;

	parsenext(current_song, size);

	// loops back to first song if current song is last in loop, otherwise increment
	if (current_song_num == 4){
	    current_song_num = 0;
	}
	else{
	    current_song_num++;
	}
}

/**
 * Handles 'play' command. Turns on LED. Parses throught
 * midi file and creates an array of all bytes relative to the
 * track information. uses that info and sends it to parseTrack,
 * and then plays the current song.
 */
void play(){
	unsigned char* track_info;
	track_info = createTrackArray(current_song, size);

	LED_On(8);

	t = getTempo(); //tempo

	parseTrack(track_info);
	playSong(current_song_num, t);
}

/**
 * Handles 'stop' command. Turns off LED
 */
void stop(){
	LED_Off(8);
}


/**
 * Runs the project, called in main.c
 * runs an infinite loop that reads in user data byte by byte,
 * and stores it in a buffer. Upon hitting enter after typing
 * a command, the buffer is compared against different command cases.
 * If the buffer matches a command, it runs that designated handler,
 * if not, "Invalid Command" is printed.
 */
void run_project(){
	init_systick();
	GPIO_Init();

	char input[128]; // buffer for input
	int buffer_index = 0; // index to keep track of position in buffer
	int count = 0; // count for pause to make sure flashing 1/sec
	int pause = 0; // flag to keep track of whether light should be flashing or not. pseudo-boolean
	char byte; // used to store each character when reading user input

	while(1){

		if(mode == 0){ //remote mode controls

			delay_systick(); // start systick timer

			byte = USART_Read_Nonblocking(USART2); // read in character
			printf("%c", byte);

			if(byte == '\r'){ // once enter is pressed
				input[buffer_index] = '\0'; //add terminating character
				buffer_index = 0; // reset
				printf("%s\r\n", (char*)input);

				if(strcmp(input, "NEXT") == 0){ // if user entered next
					pause = 0;
					next();
				}

				else if(strcmp(input, "PLAY") == 0){ // if user entered play
					pause = 0;
					play();
				}

				else if(strcmp(input, "PAUSE") == 0){ // if user entered pause

					pause = 1;
				}

				else if(strcmp(input, "STOP") == 0) { // if user entered stop
					pause = 0;
					stop();
				}

				else{ // if user entered something other than the above commands
					printf("%s\r\n", "Invalid Command");
				}
			}

			else if(byte != 0){ // if user did not hit enter, add byte to the buffer
				input[buffer_index] = (char)byte;
				buffer_index++;
			}

			if(pause==1){ // if user enter pause, start flashing until pause flag is set back to 0
				if(count == 1000000){
					LED_Toggle(8);
					count = 0;
				}
				count++;
			}
		}

		// local mode controls
		else if(mode == 1){
			delay_systick(); // start systick timer

			if(systickTotal > 1000){ // if button is held down for over a second, stop
				stop();
				pause = 0;
			}

			if(pause_toggle == 1){ // if button is held down for less than a second, toggle play and pause
				play();
				pause = 0;
			}
			else if(pause_toggle == 0){
				pause = 1;
			}

			if(pause == 1){ // flash until pause is 0
				if(count == 100000){
					LED_Toggle(8);
					count = 0;
				}
				count++;
			}
			byte = USART_Read_Nonblocking(USART2); // resets buffer
		}
	}
}
