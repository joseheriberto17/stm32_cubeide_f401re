/*
 * uart.h
 *
 *  Created on: Sep 4, 2023
 *      Author: joseheriberto24
 */

#ifndef INC_UART_POLLING_MODE_H_
#define INC_UART_POLLING_MODE_H_

#include "stm32f4xx_hal.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define WELCOME_MSG "Welcome2 to the Nucleo management console\r\n"
#define MAIN_MENU   "Select the option you are interested in:\r\n\t1. Toggle LD2 LED\r\n\t2. Read USER BUTTON status\r\n\t3. Clear screen and print this message "
#define PROMPT "\r\n> "

// r y n ayuda a pegar el puntero hacia una nueva linea
void printWelcomeMessage(UART_HandleTypeDef *huart);
uint8_t readUserInput(UART_HandleTypeDef *huart);
uint8_t processUserInput(UART_HandleTypeDef *huart, uint8_t opt);

#endif /* INC_UART_POLLING_MODE_H_ */
