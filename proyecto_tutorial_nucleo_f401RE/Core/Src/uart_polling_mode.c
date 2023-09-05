/*
 * uart.c
 *
 *  Created on: Sep 4, 2023
 *      Author: joseheriberto24
 */
#include <uart_polling_mode.h>

void printWelcomeMessage(UART_HandleTypeDef *huart) {

	HAL_UART_Transmit(huart, (uint8_t*)"\033[0;0H", strlen("\033[0;0H"), HAL_MAX_DELAY);
	HAL_UART_Transmit(huart, (uint8_t*)"\033[2J", strlen("\033[2J"), HAL_MAX_DELAY);
	HAL_UART_Transmit(huart, (uint8_t*)WELCOME_MSG, strlen(WELCOME_MSG), HAL_MAX_DELAY);
	HAL_UART_Transmit(huart, (uint8_t*)MAIN_MENU, strlen(MAIN_MENU), HAL_MAX_DELAY);
}

uint8_t readUserInput(UART_HandleTypeDef *huart) {
	//buffer de 1 bite de ancho
	char readBuf[1];

	HAL_UART_Transmit(huart, (uint8_t*)PROMPT, strlen(PROMPT), HAL_MAX_DELAY);
	HAL_UART_Receive(huart, (uint8_t*)readBuf, 1, HAL_MAX_DELAY);
	return atoi(readBuf);
}

uint8_t processUserInput(UART_HandleTypeDef *huart,uint8_t opt) {
	char msg[30];

	if(!opt || opt > 3)
		return 0;

	sprintf(msg, "%d", opt);
	HAL_UART_Transmit(huart, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);

	switch(opt) {
	case 1:
		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
		break;
	case 2:
		sprintf(msg, "\r\nUSER BUTTON status: %s",
				HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_RESET ? "PRESSED" : "RELEASED");
		HAL_UART_Transmit(huart, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
		break;
	case 3:
		return 2;
	};
	return 1;
}

