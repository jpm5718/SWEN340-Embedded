/*
 * systick.c
 *
 *  Created on: Oct 12, 2023
 *      Author: james
 */


#include "stdint.h"
#include "systick.h"


struct systick* SYS_TICK = (struct systick*) 0xE000E010;
// This function is to Initialize SysTick registers
void init_systick()
{
	//sets timer to 1ms
	SYS_TICK->RVR = 79;
	SYS_TICK->CSR = SYS_TICK->CSR | (1<<2);
	SYS_TICK->CSR = SYS_TICK->CSR | (1<<1);
	SYS_TICK->CSR = SYS_TICK->CSR | (1<<0);
}

// This function is to create delay using SysTick timer counter
void delay_systick()
{
	while(!(SYS_TICK->CSR & (1<<16)));
}
