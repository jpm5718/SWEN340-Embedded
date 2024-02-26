/*
 * trackparser.c
 *
 *  Created on: Dec 3, 2023
 *      Author: james
 */

#include "printf.h"
#include "tone.h"
#include "song.h"
#include "conversion.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/**
 * struct to hold info from header section of midi file
 * not all info is used, but still nice to have one spot
 * where all header info is stored
 */
struct header {
	char type[4];
	uint32_t length;
	uint16_t format;
	uint16_t tracks;
	uint16_t division;
};

/**
 * struct to hold relavant info regarding a note on or off event
 */
struct noteEvent{
	uint32_t delay;
	uint8_t type;
	uint8_t key;
	uint8_t velo;
};

struct noteEvent* events[400]; // array to hold all events in a song
struct header* ptr_head; // pointer to the header struct. used when calculating tick and tempo stuff
int eventIndex = 0; // counter to hold index of events[]

/**
 * originally from class activity. takes in current song number
 * and creates a header struct from it.
 */
void structs(int song_num) {
	ptr_head = (struct header*)get_song(song_num).p_song;

	char buffer[5];
	strncpy(buffer, ptr_head->type, sizeof(ptr_head->type)); // copy bytes from song file into buffer
	buffer[sizeof ( ptr_head->type)] = 0;
}

/**
 * takes in an array of bytes to calculate delay. since the delay
 * of each event can vary in length, this function takes an array
 * and calculates the exact decimal value of each event and
 * returns it
 */
uint32_t parse_delay (uint8_t* delay){
	uint32_t result = 0;
	uint8_t currentByte;

	do {
	  currentByte = *delay++;
	  result = (result << 7) | (currentByte & 0x7F);
	} while (currentByte & 0x80);

	return result;
}

/**
 * Takes in array containing bytes relative to tack info.
 * Goes byte by byte parsing it and figures out its meaning
 * based on midi file format. first parses delay, then type,
 * and values (key and velocity) relative to that type and
 * stores it in a noteEvent struct. added to events[]
 */
void parseTrack(unsigned char* track_info) {
	int index = 0;

	while (track_info[index] != 0x2f || track_info[index + 1] != 0x00){ // while not at end of track
		uint8_t delay_placeholder[5]; // used to hold delays for the current event being parsed. sent to parseDelay()
		int delay_index = 0; // index for delay_placeholder
		struct noteEvent* current_event = malloc(sizeof(struct noteEvent)); // initialize struct to serve as the current event being parsed

		while (track_info[index] & 0x80){ //while byte is pertaining to delay
			delay_placeholder[delay_index] = track_info[index]; // add it to delay_placeholder
			delay_index++; //increment both indexes
			index++; // "
		}

		delay_placeholder[delay_index] = track_info[index]; // if delay is only one byte, add it

		current_event->delay = parse_delay(delay_placeholder);

		index++;

		current_event->type = track_info[index]; // add the type to current_event

		if ((current_event->type & 0xF0) == 0x90 || (current_event->type & 0xF0) == 0x80) { // if note on event, add key and velocity to struct
		            current_event->key = track_info[index + 1];
		            current_event->velo = track_info[index + 2];
		            index += 3; // Move index to the next event
		        } else { // if note off, key and velocity are 0
		            current_event->key = 0;
		            current_event->velo = 0;
		            index++;
		        }
		events[eventIndex] = current_event; // add current event to events[]

		eventIndex++;
	}

	for (int i = 0; i < eventIndex; i++) { //free up the memory used
	    free(events[i]);
	}
}

/**
 * takes in current song number and tempo, gets everything ready to make music.
 * calculates how many microseconds are in a midi tick, then uses that, as well
 * as some functions from tone.c to play the song
 */
void playSong (int current_song_num, int tempo) {
	structs(current_song_num); // create header struct
	uint16_t division = convert_to_uint16(ptr_head->division); // get division from the header created

	int miditick = tempo / division; // calculate how many systick ticks are in a midi tick
	int totalDelay = 0; // holds total delay of song as its being played

	reset_counter();

	for(int i = 0; i < eventIndex; i++) { // for each event in the song
//		printf("h");
		if((events[i]->type & 0xF0) == 0x90){ // if note on event
			int delay = (events[i+1]->delay) * miditick; // get the delay of the event
			totalDelay += delay; // add it to total
			add_tone(events[i]->key, events[i]->velo); // adds to tones[] in tone.c to be played
		}
		else if((events[i]->type & 0xF0) == 0x80){ // if note off
			int delay = (events[i+1]->delay) * miditick; // calculate delay
			totalDelay += delay; // add it to total
			remove_tone(events[i]->key); // remove it from tones[]
		}

		play_tones(totalDelay); // play tones[]
	}
}
