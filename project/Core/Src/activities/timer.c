/*
 * timer.c
 *
 *  Created on: Oct 4, 2023
 *      Author: james
 */

#include "systick.h"
#include "printf.h"

static struct systick* SYST_TICK = (struct systick*) 0xE000E010;

void init_syst () {
    // Create an instance of systick

    printf ("0x%x\n", (unsigned int)SYST_TICK);

    // Set timer to 10 ms
    SYST_TICK->RVR = 79999;

    // Turn on timer
    SYST_TICK->CSR = SYST_TICK->CSR | (1<<2);
    SYST_TICK->CSR = SYST_TICK->CSR | (1<<0);

}

void timer_clock () {
    init_syst();
    // Display num seconds since started, once a second

    int count = 0;
    int seconds = 0;

    while (1){
        if ((SYST_TICK->CSR >> 16) == 1){
            count++;
            if (count == 10){
                seconds++;
                count = 0;
                printf ("%d\r\n", seconds);
            }
        }
    }

}
