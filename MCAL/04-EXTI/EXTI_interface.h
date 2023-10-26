/*****************************************************************************
* @file:    EXTI_interface.h
* @author:  Copyright (c) 2023 Gomaa Mohammed Gomaa.
* @license: GNU GPL version 3 or later.
*			      This is free software: you are free to change and redistribute it.  
*			      There is NO WARRANTY, to the extent permitted by law.
* @version: V0.2   
* @date:    Fri, 13 Oct 2023 22:00:12 +0200
* @brief:   External Interrupts Driver for STM32F103
******************************************************************************/
#ifndef _EXTI_INTERFACE_H
#define _EXTI_INTERFACE_H

/* ==================================================================== */
/* ======================= public data types ========================== */
/* ==================================================================== */

/* External lines data type */
typedef enum
{
  EXTI_LINE0=0,
  EXTI_LINE1,
  EXTI_LINE2,
  EXTI_LINE3,
  EXTI_LINE4,
  EXTI_LINE5,
  EXTI_LINE6,
  EXTI_LINE7,
  EXTI_LINE8,
  EXTI_LINE9,
  EXTI_LINE10,
  EXTI_LINE11,
  EXTI_LINE12,
  EXTI_LINE13,
  EXTI_LINE14,
  EXTI_LINE15,
  EXTI_LINE_ERR
} ExtiId_type;

/* Exti mode data type */
typedef enum
{
  EXTI_RISING = 0,
  EXTI_FALLING,
  EXTI_ON_CHANGE,
  EXTI_ERR,
} ExtiMode_type;


/* ==================================================================== */
/* ==================== Public Functions Declaration ================== */
/* ==================================================================== */

/**
 * @brief---------------------> Enable external interrupt
 * @parameter1----------------> (ExtiLine) external line
 * @parameter2----------------> (ExtiMode) exti mode
 * @return--------------------> None
 * @preconditions-------------> None
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Reentrant        
 */
void EXTI_enableExti(ExtiId_type ExtiLine, ExtiMode_type ExtiMode);

/**
 * @brief---------------------> Disable external interrupt
 * @parameter1----------------> (ExtiLine) external line
 * @return--------------------> None
 * @preconditions-------------> None
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Reentrant      
 */
void EXTI_disableExti(ExtiId_type ExtiLine);

/**
 * @brief---------------------> Trigger external interrupt
 * @parameter1----------------> (ExtiLine) external line
 * @return--------------------> None
 * @preconditions-------------> None
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Reentrant
 */
void EXTI_trigger(ExtiId_type ExtiLine);

/**
 * @brief---------------------> Set callback of external interrupt
 * @parameter1----------------> (ExtiLine) external line
 * @parameter2----------------> (Callback) callback function to be called at exti 
 * @return--------------------> None
 * @preconditions-------------> None
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Reentrant      
 */
void EXTI_setCallback(ExtiId_type ExtiLine,void (*Callback)(void));


       

#endif
