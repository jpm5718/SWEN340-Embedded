/*
 * midiparser.h
 *
 *  Created on: Oct 24, 2023
 *      Author: james
 */

#ifndef INC_MIDI_MIDIPARSER_H_
#define INC_MIDI_MIDIPARSER_H_

int getTempo();
int getDivision();
void parsenext();
void parseTitle (unsigned char* current_song, int size);
void parseCopyright (unsigned char* current_song, int size);
void parseTempo (unsigned char* current_song, int size);
unsigned char* createTrackArray(unsigned char* current_song, int size);

#endif /* INC_MIDI_MIDIPARSER_H_ */
