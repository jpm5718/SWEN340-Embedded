/*
 * structs.c
 *
 *  Created on: Nov 14, 2023
 *      Author: james
 */

#include "stdint.h"
#include "printf.h"
#include "song.h"
#include "string.h"
#include "conversion.h"

// Create a struct to represent a song header

//struct header {
//	char type[4];
//	uint32_t length;
//	uint16_t format;
//	uint16_t tracks;
//	uint16_t division;
//};
//
//void structs () {
//	struct header* ptr_head;
//
//	//Assign the header to the start of the first song
//	//Print all song info
//	ptr_head = (struct header*)get_song(0).p_song;
//
////	char buffer[5];
////	strncpy(buffer, ptr_head->type, sizeof(ptr_head->type));
////	buffer[sizeof(ptr_head->type)] = 0;
//
//	uint32_t converted_length = convert_to_uint32(ptr_head->length);
//	uint16_t converted_format = convert_to_uint16(ptr_head->format);
//	uint16_t converted_tracks = convert_to_uint16(ptr_head->tracks);
//	uint16_t converted_division = convert_to_uint16(ptr_head->division);
//
//	printf("%s\r\n", ptr_head->type);
//	printf("%ld\r\n", converted_length);
//	printf("%d\r\n", converted_format);
//	printf("%d\r\n", converted_tracks);
//	printf("%d\r\n", converted_division);
//}
