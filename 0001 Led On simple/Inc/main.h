/*
 * main.h
 *
 *  Created on: Nov 15, 2021
 *  Author: Viktorija Zelnichki
 */

#ifndef MAIN_H_
#define MAIN_H_

/********************  Base Register Addresses  ********************/
#define RCCBASE   0x40023800
#define RCC_CR    (RCCBASE+0x00)
#define RCC_CFGR  (RCCBASE+0x08)

#define FLASHBASE  0x40023C00
#define FLASH_ACR  (FLASHBASE + 0x00)

#define TIM9_REG_ADDR (0x40014000)
#define TIM9_CNT_ADDR (0x40014024)
#define TIM9_PRESCALER_ADDR (0x40014028)
#define TIM9_STATUS_ADDR (0x40014010)
#define TIM9_ARR_ADDR (0x4001402C)

#define RCC_AHB1_ADDR (0x40023830)
#define RCC_APB2_ADDR (0x40023844)

#define GPIOD_MODE_ADDR (0x40020C00)
#define GPIOD_OUTPUT_ADDR (0x40020C14)

/********************  Bit definition for RCC_CR register  ********************/
#define HSION					(0U)
#define HSIRDY					(1U)
#define RCC_CFGR_SW_HSI			(0x00000000U)   /*!< HSI selected as system clock */
#define RCC_CFGR_SWS_HSI        (0x00000000U)                 /*!< HSI oscillator used as system clock */
#define RCC_CR_HSIRDY 			(0x1UL << HSIRDY)
#define RCC_CR_HSION	   		(0x1UL << HSION)
#define RCC_CFGR_SWS_Pos		(2U)
#define RCC_CFGR_SWS_Msk		(0x3UL << RCC_CFGR_SWS_Pos)    /*!< 0x0000000C */
#define RCC_CFGR_SWS            RCC_CFGR_SWS_Msk              /*!< SWS[1:0] bits (System Clock Switch Status) */

/********************  Bit definition for TIMER 9 register  ********************/
#define TIM9EN_Pos                   (0U)
#define TIM9EN_Msk                   (0x1UL << TIM9EN_Pos) /*!< 0x00000001 */
#define TIM9EN                       TIM9EN_Msk        /*!< Timer 9 clock enable */

/********************  Bit definition for RCC_APB2 register  ********************/
#define RCC_APB2RSTR_TIM9RST_Pos                (16U)
#define RCC_APB2RSTR_TIM9RST_Msk                (0x1UL << RCC_APB2RSTR_TIM9RST_Pos) /*!< 0x00010000 */
#define RCC_APB2RSTR_TIM9RST                    RCC_APB2RSTR_TIM9RST_Msk     /*!< TIM9 reset */

#define RCC_AHB1_Pos                	(3U)
#define RCC_AHB1_Msk                   	(0x1UL << RCC_AHB1_Pos) /*!< 0x0000100 */
#define RCC_AHB1_EN                    	RCC_AHB1_Msk     /*!< AHB1 Enable */

#endif /* MAIN_H_ */
