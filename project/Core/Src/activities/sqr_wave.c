/*
 * sqr_wave.c
 *
 *  Created on: Nov 28, 2023
 *      Author: james
 */

#include "tone.h"
#include "printf.h"
#include "dac.h"
#include <stdint.h>
#include "systick.h"

void Error_Handler () {

}


//void SysTick_Handler () {
//	count++;
//}

void run_wave(uint32_t freq){
	init_systick ();

	DAC_Init();
	DAC_Start();

    uint32_t duration = hertz_to_duration (freq);
    while (1) {
        if (get_counter() % duration < (duration >> 1)) {
            DAC_Set_Value(1500);
        }
        else {
            DAC_Set_Value(0);
        }
    }
}
