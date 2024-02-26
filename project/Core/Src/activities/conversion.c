/*
 * conversion.c
 *
 *  Created on: Nov 28, 2023
 *      Author: james
 */

#include "stdint.h"

uint32_t convert_to_uint16(uint32_t p_value) {
    return ((p_value & 0xFF00) >> 8) | ((p_value & 0x00FF) << 8);
}

uint32_t convert_to_uint24(uint32_t p_value) {
    return ((p_value & 0xFF0000) >> 16) | (p_value & 0x00FF00) |
           ((p_value & 0x0000FF) << 16);
}

uint32_t convert_to_uint32(uint32_t p_value) {
    return ((p_value & 0xFF000000) >> 24) |
               ((p_value & 0x00FF0000) >> 8) | ((p_value & 0x0000FF00) << 8) |
               ((p_value & 0x000000FF) << 24);
}
