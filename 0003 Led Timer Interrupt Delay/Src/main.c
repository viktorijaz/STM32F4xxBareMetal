/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Viktorija Zelnichki
 * @brief          : CLOCK Setup For STM32F411RE
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

#include <stdint.h>
#include <stdio.h>
#include "main.h"

void delay_ms(uint16_t ms);

volatile unsigned int globcounter;
volatile unsigned int ledon;

/**************************************************
 * Delay in microseconds
 1. RESET the Counter
 2. Wait for the Counter to reach the entered value. As each count will take 1 us,
 the total waiting time will be the required us delay
 ************************************************/

/* ******************************************************************************
 * @brief System Clock Configuration
 * The system Clock is configured as follow :
 * System Clock source = HSI (Internal RC Oscillator)
 * SYSCLK(Hz) = 16000000
 * HCLK(Hz) = 16000000
 * AHB Prescaler = 1
 * APB1 Prescaler = 4
 * APB2 Prescaler = 1	// TIMER9 hangs on AP2
 * HSI Frequency(Hz) = 16000000
 * @param None
 * @retval None
 */
void SysClockConfig(void) {
	/*******************************************************
	 *
	 1. ENABLE HSI and wait for the HSI to become Ready
	 2. Select the Clock Source and wait for it to be set

	 ********************************************************/
	uint32_t *RCC_CR_REG = (uint32_t*) RCC_CR;
	uint32_t *RCC_CFGR_REG = (uint32_t*) RCC_CFGR;

	// 1. ENABLE HSI and wait for the HSI to become Ready
	*RCC_CR_REG |= RCC_CR_HSION;
	while (!(*RCC_CR_REG & RCC_CR_HSIRDY));

	// 2. Select the Clock Source and wait for it to be set
	*RCC_CFGR_REG |= RCC_CFGR_SW_HSI;
	while ((*RCC_CFGR_REG & RCC_CFGR_SWS) != RCC_CFGR_SWS_HSI);
}

/************************************************
 * Initialize and configure TIMER 9 peripheral
 1. Enable Timer clock
 2. Set the prescalar and the ARR
 3. Enable the Timer, and wait for the update Flag to set
 ************************************************/
void TIM9Config(void) {
	//enable Peripheral Clock for APB2
	*RCC_APB2_REG |= RCC_APB2RSTR_TIM9RST;

	// 2. Set the prescalar and the ARR so that the TimeBase is 1 milisecond
	*TIM9_PRESCALER_REG = 15;  // 16MHz/(15+1) = 1 MHz Counter Clock
	*TIM9_ARR_REG = 1000;  // MAX ARR value

	// 3. Enable the Timer, and wait for the update Flag to set
	*TIM9_STATUS_REG = 0x00000000;
	*TIM9_REG |= TIM9EN; // Enable the Counter

	//4. Enable Interrupts
	*TIM9_IRQ_EN |= (1 << 0); //Enable the interrupt
	*NVIC_ISER0 |= (1 << 24);

	*TIM9_STATUS_REG = 0x00000000;
}

void GPIO_Init(void) {
	//enable Peripheral Clock for AHB1
	*RCC_AHB1_REG |= 1 << 3;
	//clear the 30th and 31st bit
	*GPIOD_MODE_REG &= ~(3 << 30);
	//configure PD15 as output
	*GPIOD_MODE_REG |= 1 << 30;
}

void TIM1_BRK_TIM9_IRQHandler(void) {
	//if uif flag of status register is set
	if ((*TIM9_STATUS_REG & (1 << 0))) {
		delay_ms(200);
		*TIM9_STATUS_REG = 0x00000000;
	}

}

void delay_ms(uint16_t ms) {
	globcounter += 1;
	if (globcounter == ms) {
		ledon = !ledon;
		if (!ledon) {
			*GPIOD_OUTPUT_REG |= 1 << 15;
		} else {
			*GPIOD_OUTPUT_REG &= ~(1 << 15);
		}

		globcounter = 0;
	}
}

int main(void) {

	SysClockConfig();
	GPIO_Init();
	TIM9Config();

	globcounter = 0;
	ledon = 0;

}

