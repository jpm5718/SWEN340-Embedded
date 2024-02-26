/*
 * trackparser.h
 *
 *  Created on: Dec 3, 2023
 *      Author: james
 */

#ifndef INC_MIDI_TRACKPARSER_H_
#define INC_MIDI_TRACKPARSER_H_

void structs(int song_num);
uint32_t parse_delay (uint8_t* delay);
void parseTrack(unsigned char* track_info);
void playSong();

#endif /* INC_MIDI_TRACKPARSER_H_ */
