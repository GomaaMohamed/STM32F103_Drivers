/******************************************************************************
* @file:    USART_private.h
* @author:  Copyright (c) 2023 Gomaa Mohammed Gomaa.
* @license: GNU GPL version 3 or later.
*			This is free software: you are free to change and redistribute it.  
*			There is NO WARRANTY, to the extent permitted by law.
* @version: V0.2   
* @date:    Sat, 7 Oct 2023 12:21:12 +0200
* @brief:   USART Driver for STM32F103
******************************************************************************/
#ifndef _USART_PRIVATE_H
#define _USART_PRIVATE_H

/* ==================================================================== */
/* ======================= private data types ========================= */
/* ==================================================================== */

/* USART registers mapping type */
typedef struct {
	volatile u32 SR;
	volatile u32 DR;
	volatile u32 BRR;
	volatile u32 CR1;
	volatile u32 CR2;
	volatile u32 CR3;
	volatile u32 GTPR;
}Usart_type;

/* ==================================================================== */
/* =================== Private Variables and Macros =================== */
/* ==================================================================== */

/* USART registers mapping */
#define  USART  ((volatile Usart_type*)(0x40013800))

/* Variable to hold Callback */
void (*UASRT_TxCompleteCallback)(void);

/* Variable to hold Callback */
void (*UASRT_RxCompleteCallback)(void);

/* Variable to hold Callback */
void (*UASRT_TxEmptyCallback)(void);

/* Private configurations */
/* Parity On Or Off */
#define   USART_PARITY_ENABLED    0
#define   USART_PARITY_DISABLED   1

/* Parity Check Options */
#define   USART_EVEN_PARITY  0
#define	  USART_ODD_PARITY   1

/* Data Size Options */
#define   USART_8BIT_DATA_SIZE  0
#define   USART_9BIT_DATA_SIZE  1

/* Baud Rate Configuration */
#define   BR_9600    0
#define   BR_4800    1
#define   BR_115200  2



#endif
