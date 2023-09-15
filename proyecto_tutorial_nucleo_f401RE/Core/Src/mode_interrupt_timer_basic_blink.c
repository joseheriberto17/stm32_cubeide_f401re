/*
 * mode_interrupt_timer_basic_blink.c
 *
 *  Created on: Sep 14, 2023
 *      Author: joseheriberto24
 */
#include "mode_interrupt_timer_basic_blink.h"


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if(htim->Instance == TIM3)
	    HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
}
