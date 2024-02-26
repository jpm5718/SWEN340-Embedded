/*
 * hw4.c
 *
 *  Created on: Oct 19, 2023
 *      Author: james
 */


#include "printf.h"
#include "systick.h"
#include "LED.h"
#include "UART.h"

void hw4_run () {
    init_systick ();
    int count = 0;
    while (1) {
        count++;

        char ch = USART_Read_Nonblocking (USART2);
        if (ch != 0){
            printf ("%c", ch);
        }

        // Move 10 count from delay
        delay_systick ();

        // to while loop, only toggle every 10
        if (count == 1000) {
            LED_Toggle (8);
            count = 0;
        }
    }
}
