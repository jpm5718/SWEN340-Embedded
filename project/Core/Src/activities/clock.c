/*
 * clock.c
 *
 *  Created on: Nov 7, 2023
 *      Author: james
 */

#include "systick.h"
#include "printf.h"

static int timer = 0;

//void SysTick_Handler(){
//	//Called whenever the systick rol over
//	timer++;
//}

void clock(){
	//initialization
	//print out time every second

	init_systick();

	int seconds = 0;

	while (1){
	    if (timer == 1000){
	        seconds++;
	        timer = 0;
	        printf ("%d\r\n", seconds);
	    }
	}
}
