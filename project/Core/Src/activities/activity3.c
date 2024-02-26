/*
 * activity3.c
 *
 *  Created on: Sep 14, 2023
 *      Author: james
 */

#include "UART.h"
#include "printf.h"
#include <string.h>


static char buffer[128];
/*
 * Reads one line from the terminal
 */
char* readline(){
	uint8_t byte;
	int i = 0;

	while(1){
		byte = USART_Read(USART2);
		USART_Write(USART2, &byte, 1);
		buffer[i] = (char)byte;
		if(byte == '\r'){
			USART_Write(USART2, (unsigned char*) "\n", 1);
			buffer[i] = '\0';
			return buffer;
		}
		i++;
	}
}

char* readline_nb() {
	uint8_t byte;
	int i = 0;

	while(1){
		byte = USART_Read_Nonblocking(USART2);

		if(byte != 0){
			USART_Write(USART2, &byte, 1);

			if(byte == '\r'){
				USART_Write(USART2, (unsigned char*)"\n", 1);
				buffer[i] = '\0';
				return buffer;
			} else {
				buffer[i] = (char)byte;
			}
			i++;
		}
	}
	return 0;
}

void run(){
	while (1){
		char* line = readline();
		puts(line);
//		uint8_t byte = USART_Read(USART2);
//		USART_Write(USART2, &byte, 1);
	}
}
