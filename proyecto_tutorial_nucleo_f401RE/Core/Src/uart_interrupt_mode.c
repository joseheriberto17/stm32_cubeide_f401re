/*
 * uart_interrupt_mode.c
 *
 *  Created on: Sep 5, 2023
 *      Author: joseheriberto24
 */
#include <uart_interrupt_mode.h>

char readBuf[1];
ITStatus UartReady = SET;



void printWelcomeMessage2(UART_HandleTypeDef *huart) {
	char *strings[] = {"\033[0;0H", "\033[2J", WELCOME_MSG, MAIN_MENU, PROMPT};

	for (uint8_t i = 0; i < 5; i++) {
		HAL_UART_Transmit_IT(huart, (uint8_t*)strings[i], strlen(strings[i]));
		while (HAL_UART_GetState(huart) == HAL_UART_STATE_BUSY_TX ||
				HAL_UART_GetState(huart) == HAL_UART_STATE_BUSY_TX_RX);
	}
}

int8_t readUserInput2(UART_HandleTypeDef *huart) {
	int8_t retVal = -1;

	if(UartReady == SET) {
		UartReady = RESET;

		HAL_UART_Receive_IT(huart, (uint8_t*)readBuf, 1);
		retVal = atoi(readBuf);
	}
	return retVal;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
/* Set transmission flag: transfer complete*/
UartReady = SET;
HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
}

uint8_t processUserInput2(UART_HandleTypeDef *huart,uint8_t opt) {
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
	HAL_UART_Transmit(huart, (uint8_t*)PROMPT, strlen(PROMPT), HAL_MAX_DELAY);
	return 1;
}

void performCriticalTasks2(void) {
  HAL_Delay(1000);
  //HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
  /*
  for(volatile int i = 0; i < 60000000; i++) {
  // Busy wait
  }
  HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
  */

}
