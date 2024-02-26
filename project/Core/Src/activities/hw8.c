/*
 * hw8.c
 *
 *  Created on: Nov 30, 2023
 *      Author: james
 */

#include "printf.h"
#include <stdint.h>

//uint32_t parseDelay (uint8_t* delay){
//	uint8_t currentByte;
//	uint32_t delayValue = 0;
//
//    do {
//      currentByte = *delay++;
//      delayValue = (delayValue << 7) | (currentByte & 0x7F);
//    } while (currentByte & 0x80);
//
//    return delayValue;
//}

// bruce's implementation

//uint32_t parseDelay (uint8_t* delay) {
//    int i = 0;
//    uint8_t curr = delay [i];
//    uint32_t parsed_delay = 0;
//    while (curr >> 7) { // More
//        parsed_delay += (curr & 0x7F) << 7;
//        curr = delay [++i];
//    }
//    parsed_delay += curr & 0x7F;
//
//    return parsed_delay;
//}
