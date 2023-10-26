/******************************************************************************
* @file:    AFIO_private.h
* @author:  Copyright (c) 2023 Gomaa Mohammed Gomaa.
* @license: GNU GPL version 3 or later.
*			This is free software: you are free to change and redistribute it.  
*			There is NO WARRANTY, to the extent permitted by law.
* @version: V0.2   
* @date:    Tue, 3 Oct 2023 16:21:12 +0200
* @brief:   Alternative Function Input Output(AFIO) Driver for STM32F103
******************************************************************************/
#ifndef _AFIO_PRIVATE_H
#define _AFIO_PRIVATE_H

/* ==================================================================== */
/* ======================= Private Data Types ========================= */
/* ==================================================================== */

// AFIO Selection structure type
typedef struct{
	volatile  u32  EVCR;
	volatile  u32  MAPR;
	volatile  u32  EXTICR[4];
	volatile  u32  MAPR2;	
}Afio_type;

/* ==================================================================== */
/* =================== Private Variables and Macros =================== */
/* ==================================================================== */

// AFIO Registers Definition
#define AFIO  ((volatile Afio_type*)0x40010000)

#endif
