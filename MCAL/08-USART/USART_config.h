/*****************************************************************************
* @file:    USART_config.h
* @author:  Copyright (c) 2023 Gomaa Mohammed Gomaa.
* @license: GNU GPL version 3 or later.
*			This is free software: you are free to change and redistribute it.  
*			There is NO WARRANTY, to the extent permitted by law.
* @version: V0.2   
* @date:    Sat, 7 Oct 2023 12:21:12 +0200
* @brief:   USART Driver for STM32F103
******************************************************************************/
#ifndef    _USART_CONFIG_H
#define    _USART_CONFIG_H 

/* ==================================================================== */
/* =================== Configurations Selection ======================= */
/* ==================================================================== */

/******** USART pin configurations ***************/
#define USART_TX_PORT   GPIOA
#define USART_TX_PIN    GPIO_PIN9
#define USART_RX_PORT   GPIOA
#define USART_RX_PIN    GPIO_PIN10

/* Baud Rate Configuration at Clock 8 MHZ
       USART_BAUD_RATE:
	   BR_9600
	   BR_4800
	   BR_115200
 */
#define   USART_BAUD_RATE   BR_115200

/* Parity Check Enabled Or Disabled */
#define   USART_PARITY  USART_PARITY_DISABLED

#if   USART_PARITY ==   USART_PARITY_ENABLED
/* Parity Check Configuration
          Options:
		  USART_EVEN_PARITY
		  USART_ODD_PARITY
 */
#define   USART_PARITY_CHECK   USART_EVEN_PARITY
#endif

/* Frame Size Configuration
         Options:
		 USART_8BIT_DATA_SIZE
		 USART_9BIT_DATA_SIZE
 */
#define   USART_DATA_SIZE   USART_8BIT_DATA_SIZE

#endif







