/*
 * midiparser.c
 *
 *  Created on: Oct 24, 2023
 *      Author: james
 */

#include <stdlib.h>
#include "song.h"
#include "printf.h"
#include "trackparser.h"

int tempo = 0; // holds tempo of song

// reutrns tempo of current song
int getTempo() {
	return tempo;
}


/**
 * parses the title of the current song
 * @param current_song- referene to the song currently being parsed
 * @param size- length of the current song array
 */
void parseTitle (unsigned char* current_song, int size) {
	// gets title bytes
    for(int i = 0; i < size; i++){
    	if (current_song[i] == 0xFF && current_song[i+1] == 0x03){
            int index = 0;
            int length = current_song[i+2];

            printf("%s", "Song Title: ");

            while(index < length){
                printf("%c", current_song[i+3]);
                i++;
                index++;
            }
            break;
        }
    }
}

/**
 * parses the copyright of the current song
 * @param current_song- referene to the song currently being parsed
 * @param size- length of the current song array
 */
void parseCopyright (unsigned char* current_song, int size) {
	// gets copyright bytes
    for(int i = 0; i < size; i++){
        if (current_song[i] == 0xFF && current_song[i+1] == 0x02){
            int index = 0;
            int length = current_song[i+2];

            printf("%s", "  Copyright: ");

            while(index < length){
	            printf("%c", current_song[i+3]);
	            i++;
	            index++;
	        }
            break;
        }
    }
}

/**
 * parses the tempo of the current song. also sets tempo
 * @param current_song- referene to the song currently being parsed
 * @param size- length of the current song array
 */
void parseTempo(unsigned char* current_song, int size) {
	// gets tempo bytes
    for (int i = 0; i < size; i++){
        if (current_song[i] == 0xFF && current_song[i+1] == 0x51){
            printf("%s", "  Tempo: ");

            int temp = ((current_song[i + 3]<<16) | (current_song[i+4]<<8) | (current_song[i+5]));
            tempo = temp;

            printf("%d\r\n",  temp);
            break;
        }
    }
}

/**
 * uses current_song and its size to create an array of bytes containing
 * only information regarding the track.
 */
unsigned char* createTrackArray(unsigned char* current_song, int size) {
	int index = 0;

    int trackStartPosition = 0; // once set, hold the index of the entire song where the track begins

    for (int i = 0; i < size; i++){
        if (current_song[i] == 0x4d && current_song[i+1] == 0x54 && current_song[i+2] == 0x72 && current_song[i+3] == 0x6b){
            trackStartPosition = i+8; // + 8 so that chunk type and length are not stored
        }
    }

    int track_size = size - trackStartPosition; // size of track
    unsigned char* track_info = (unsigned char*)malloc(track_size); // allocate memory to copy array

    while (trackStartPosition < size){ // while not at end of file, copy current song into track_info 1 for 1
        track_info[index] = current_song[trackStartPosition];
        trackStartPosition++;
        index++;
    }

    return track_info;
}

/**
 * Parses song.c
 * Using the midi format, stores relative bytes
 * into their assigned array, and converts those
 * bytes into characters. Prints out the information
 * Every time called, cycles through to the next song in
 * the array
 */
void parsenext(unsigned char* current_song, int size){
    parseTitle(current_song, size);
    parseCopyright(current_song, size);
    parseTempo(current_song, size);
}
