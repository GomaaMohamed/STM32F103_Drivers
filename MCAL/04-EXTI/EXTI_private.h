/*****************************************************************************
* @file:    EXTI_private.h
* @author:  Copyright (c) 2023 Gomaa Mohammed Gomaa.
* @license: GNU GPL version 3 or later.
*			This is free software: you are free to change and redistribute it.  
*			There is NO WARRANTY, to the extent permitted by law.
* @version: V0.2   
* @date:    Fri, 13 Oct 2023 22:00:12 +0200
* @brief:   External Interrupts Driver for STM32F103
******************************************************************************/
#ifndef _EXTI_PRIVATE_H
#define _EXTI_PRIVATE_H

/* ==================================================================== */
/* ======================= private data types ========================= */
/* ==================================================================== */

/* Registers Maping data type */
typedef struct{
	volatile  u32  IMR;
	volatile  u32  EMR;
	volatile  u32  RTSR;
	volatile  u32  FTSR;
	volatile  u32  SWIER;
	volatile  u32  PR;
}Exti_type;


/* ==================================================================== */
/* =================== Private Variables and Macros =================== */
/* ==================================================================== */

/* Registers Mapping */
#define EXTI  ((volatile Exti_type *)0x40010400)

// Variables to hold callbacks
static void (* EXTI0_Callback) (void) = NULL;
static void (* EXTI1_Callback) (void) = NULL;
static void (* EXTI2_Callback) (void) = NULL;
static void (* EXTI3_Callback) (void) = NULL;
static void (* EXTI4_Callback) (void) = NULL;


#endif
