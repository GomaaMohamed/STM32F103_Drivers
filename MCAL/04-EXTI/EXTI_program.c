/*****************************************************************************
* @file:    EXTI_program.c
* @author:  Copyright (c) 2023 Gomaa Mohammed Gomaa.
* @license: GNU GPL version 3 or later.
*			This is free software: you are free to change and redistribute it.  
*			There is NO WARRANTY, to the extent permitted by law.
* @version: V0.2   
* @date:    Fri, 13 Oct 2023 22:00:12 +0200
* @brief:   External Interrupts Driver for STM32F103
******************************************************************************/

/* ==================================================================== */
/* ========================== include files =========================== */
/* ==================================================================== */
#include      "STD_TYPES.h"
#include      "BIT_MATH.h"

#include      "EXTI_interface.h"
#include      "EXTI_private.h"
#include      "EXTI_config.h"

/* ==================================================================== */
/* ================= Public Functions Implementation ================== */
/* ==================================================================== */

// Functin to enable External interrupt
void EXTI_enableExti(ExtiId_type ExtiLine, ExtiMode_type ExtiMode)
{
	// Validate input parameters
	ASSERT(ExtiLine >= 0 && ExtiLine < EXTI_LINE_ERR);
	ASSERT(ExtiMode >= 0 && ExtiMode < EXTI_ERR);

	// Select line and set its mode	
	if(ExtiMode == EXTI_RISING)
	{
		// Enable EXTI
		SET_BIT(EXTI->IMR,ExtiLine);
		// Set rising
		SET_BIT(EXTI->RTSR,ExtiLine);
	}
	else if(ExtiMode == EXTI_FALLING)
	{
		// Enable EXTI
		SET_BIT(EXTI->IMR,ExtiLine);
		// Set falling
		SET_BIT(EXTI->FTSR,ExtiLine);
		
	}
	else if(ExtiMode == EXTI_ON_CHANGE)
	{
		// Enable EXTI
		SET_BIT(EXTI->IMR,ExtiLine);
		// Set rising
		SET_BIT(EXTI->RTSR,ExtiLine);
		// Set falling
		SET_BIT(EXTI->FTSR,ExtiLine);	
	}
	else
	{
		// Do nothing
	}
}

// Function to disable Exti
void EXTI_disableExti(ExtiId_type ExtiLine)
{  
	// Validate input parameters
	ASSERT(ExtiLine >= 0 && ExtiLine < EXTI_LINE_ERR);
	// disable exti
    CLR_BIT(EXTI->IMR,ExtiLine);
}

// Function to trigger Exti interrupt
void EXTI_trigger(ExtiId_type ExtiLine)
{
	// Validate input parameters
	ASSERT(ExtiLine >= 0 && ExtiLine < EXTI_LINE_ERR);
	// Trigger SW 
	SET_BIT(EXTI->SWIER,ExtiLine);
	SET_BIT(EXTI->PR,ExtiLine);
}

// Function to set callback
void EXTI_setCallback(ExtiId_type ExtiLine,void (*Callback)(void))
{
	// Validate input parameters
	ASSERT(ExtiLine >= 0 && ExtiLine < EXTI_LINE_ERR);
	ASSERT(Callback != NULL);

	// Select callback
	switch(ExtiLine)
	{
		case EXTI_LINE0: EXTI0_Callback = Callback; break;
		case EXTI_LINE1: EXTI1_Callback = Callback; break;
		case EXTI_LINE2: EXTI2_Callback = Callback; break;
		case EXTI_LINE3: EXTI3_Callback = Callback; break;
		case EXTI_LINE4: EXTI4_Callback = Callback; break;
	}	
}

/* ==================================================================== */
/* ================= Private Functions Implementation ================= */
/* ==================================================================== */

void EXTI0_IRQHandler(void)
{
	EXTI0_Callback();
	SET_BIT(EXTI->PR,0);
}
void EXTI1_IRQHandler(void)
{
	EXTI1_Callback();
	SET_BIT(EXTI->PR,1);
}
void EXTI2_IRQHandler(void)
{
	EXTI2_Callback();
	SET_BIT(EXTI->PR,2);
}
void EXTI3_IRQHandler(void)
{
	EXTI3_Callback();
	SET_BIT(EXTI->PR,3);
}
void EXTI4_IRQHandler(void)
{
	EXTI4_Callback();
	SET_BIT(EXTI->PR,4);
}
