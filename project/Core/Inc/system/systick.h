/*
 * systick.h
 *
 *  Created on: Jan 8, 2023
 *      Author: bruce
 */

#ifndef INC_SYSTICK_H_
#define INC_SYSTICK_H_

#include "stdint.h"


struct systick {
    uint32_t CSR;
    uint32_t RVR;
    uint32_t CVR;
    uint32_t CALIB;
};

void init_systick();
void delay_systick();

#endif /* INC_SYSTICK_H_ */
