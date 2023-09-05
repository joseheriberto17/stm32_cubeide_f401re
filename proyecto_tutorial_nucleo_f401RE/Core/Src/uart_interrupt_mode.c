/*
 * uart_interrupt_mode.c
 *
 *  Created on: Sep 5, 2023
 *      Author: joseheriberto24
 */
#include <uart_interrupt_mode.h>

char readBuf[1];
__IO ITStatus UartReady = SET;
uint8_t txData;
RingBuffer txBuf, rxBuf;

//creacioin de la interfaz con transmit_IT y un bufer de 1000 bites
void printWelcomeMessage2(UART_HandleTypeDef *huart) {
	char *strings[] = {"\033[0;0H", "\033[2J", WELCOME_MSG, MAIN_MENU, PROMPT};

	for (uint8_t i = 0; i < 5; i++) {
		UART_Transmit(huart, (uint8_t*)strings[i], strlen(strings[i]));
	}
}
//hay datos disponibles?
int8_t readUserInput2(UART_HandleTypeDef *huart) {
	int8_t retVal = -1;

	if(UartReady == SET) {
		UartReady = RESET;

		HAL_UART_Receive_IT(huart, (uint8_t*)readBuf, 1);
		retVal = atoi(readBuf);
	}
	return retVal;
}
//si detecta el envio el tamaño definido de 1 bite
//este tamaño es definito por el terce parametro de HAL_UART_Receive_IT (size)
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
/* Set transmission flag: transfer complete*/
UartReady = SET;
}

uint8_t processUserInput2(UART_HandleTypeDef *huart,uint8_t opt) {
	char msg[30];

	if(!opt || opt > 3)
		return 0;

	sprintf(msg, "%d", opt);
	UART_Transmit(huart, (uint8_t*)msg, strlen(msg));

	switch(opt) {
	case 1:
		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
		break;
	case 2:
		sprintf(msg, "\r\nUSER BUTTON status: %s",
				HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_RESET ? "PRESSED" : "RELEASED");
		UART_Transmit(huart, (uint8_t*)msg, strlen(msg));
		break;
	case 3:
		return 2;
	};
	UART_Transmit(huart, (uint8_t*)PROMPT, strlen(PROMPT));
	return 1;
}

void performCriticalTasks2(void) {
  HAL_Delay(100);
  //HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
  /*
  for(volatile int i = 0; i < 60000000; i++) {
  // Busy wait
  }
  HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
  */

}
//Si la función HAL_UART_Transmit_IT() falla (lo que significa que la UART ya
//está transmitiendo otro mensaje), entonces la secuencia de bytes se coloca dentro de un buffer circular.
uint8_t UART_Transmit(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t len) {
	if(HAL_UART_Transmit_IT(huart, pData, len) != HAL_OK) {
		if(RingBuffer_Write(&txBuf, pData, len) != RING_BUFFER_OK)
			return 0;
		}
	return 1;
	}
//comprobar si hay bytes pendientes dentro del buffer circular
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart) {
	if(RingBuffer_GetDataLength(&txBuf) > 0) {
		RingBuffer_Read(&txBuf, &txData, 1);
		HAL_UART_Transmit_IT(huart, &txData, 1);
	}
}
