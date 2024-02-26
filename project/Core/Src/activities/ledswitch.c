/*
 * ledswitch.c
 *
 *  Created on: Nov 2, 2023
 *      Author: james
 */


#include "GPIO.h"
#include "stm32l4xx.h"
#include "LED.h"

void switch_toggle(){
	GPIO_Init();

	while(1){
		if(GPIOA->IDR & (1<<9)){
			LED_On(8);
		}
		else {
			LED_Off(8);
		}
	}
}
