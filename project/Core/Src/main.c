// main.c with demo
// Updated and refactored Larry Kiser copyright 2021


// include project specific header files
#include <activity3.h>
#include <stdint.h>
#include "SysClock.h"
#include "LED.h"
#include "UART.h"
#include "demo.h"
#include "hw4.h"
#include "systick.h"
#include <stdio.h>
#include "hello.h"
#include "homework.h"
#include "project.h"
#include "ledswitch.h"
#include "echo.h"
#include "clock.h"
#include "structs.h"
#include "sqr_wave.h"
#include "hw8.h"
	
int main(void){

	// initialization code
	System_Clock_Init(); // set System Clock = 80 MHz
	LED_Init(8);
	UART2_Init();

	display_menu();
	run_project();

}

