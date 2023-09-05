/*
 * uart_interrupt_mode.c
 *
 *  Created on: Sep 5, 2023
 *      Author: joseheriberto24
 */

#ifndef INC_UART_INTERRUPT_MODE_C_
#define INC_UART_INTERRUPT_MODE_C_

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "stm32f4xx_hal.h"

#define WELCOME_MSG "Welcome2 to the Nucleo management console\r\n"
#define MAIN_MENU   "Select the option you are interested in:\r\n\t1. Toggle LD2 LED\r\n\t2. Read USER BUTTON status\r\n\t3. Clear screen and print this message "
#define PROMPT "\r\n> "

void printWelcomeMessage2(UART_HandleTypeDef *huart);
int8_t readUserInput2(UART_HandleTypeDef *huart);
uint8_t processUserInput2(UART_HandleTypeDef *huart,uint8_t opt);
void performCriticalTasks2(void);

#endif /* INC_UART_INTERRUPT_MODE_C_ */
