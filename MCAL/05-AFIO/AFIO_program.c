/*****************************************************************************
* @file:    AFIO_program.c
* @author:  Copyright (c) 2023 Gomaa Mohammed Gomaa.
* @license: GNU GPL version 3 or later.
*			This is free software: you are free to change and redistribute it.  
*			There is NO WARRANTY, to the extent permitted by law.
* @version: V0.2   
* @date:    Tue, 3 Oct 2023 16:21:12 +0200
* @brief:   Alternative Function Input Output(AFIO) Driver for STM32F103
******************************************************************************/

/* ==================================================================== */
/* ========================== include files =========================== */
/* ==================================================================== */
#include      "STD_TYPES.h"
#include      "BIT_MATH.h"

#include      "AFIO_interface.h"
#include      "AFIO_private.h"
#include      "AFIO_config.h"


/* ==================================================================== */
/* ================= Public Functions Implementation ================== */
/* ==================================================================== */

// Function to remap external interrupts pins
void AFIO_remapExtiLine(AfioExtiLine_type ExtiLine, AfioExtiPort_type PortMap)
{
	// Validate input parameters
	ASSERT(ExtiLine >= 0 && ExtiLine < EXTI_LINE_ERR);
	ASSERT(PortMap >= 0 && PortMap < EXTI_PORT_ERR);

	// Adjust position of line
	u8 RegIndex = 0;
	if(ExtiLine <=  3)
	{
		RegIndex = 0;
		
	}
	else if(ExtiLine <=  7)
	{
		RegIndex = 1 ;
		ExtiLine -= 4;	
	}
	else if(ExtiLine <=  11)
	{
		RegIndex = 2 ;
		ExtiLine -= 8;
	}
	else if(ExtiLine <=  15)
	{
		RegIndex = 3 ;
		ExtiLine -= 12;
		
	}
	AFIO->EXTICR[RegIndex] &=~ ((0b1111) << (ExtiLine * 4));
	AFIO->EXTICR[RegIndex] |=  ((PortMap) << (ExtiLine * 4));
}

// Function to remap OutputEventPin
void AFIO_remapOutputEventPin(AfioOutputEventPort_type OutputEventPort,AfioOutputEventPin_type OutputEventPin)
{
	// Validate input parameters
	ASSERT(OutputEventPort >= 0 && OutputEventPort < OUTPUT_PORT_ERR);
	ASSERT(OutputEventPin >= 0 && OutputEventPin < OUTPUT_PIN_ERR);

	// Adjust 
	u8 Temp = 0;
	Temp = (OutputEventPort << 4);
	Temp |= OutputEventPin;
	for(u8 i = 0;i <=3; i++)
	{
		if(i == OutputEventPort)
		{
			for(u8 j = 0;j <=16;j++)
			{
				if(j == OutputEventPin)
				{
					AFIO->EVCR = Temp;
					break;
				}
			}
			break;
		}
		
	}
	
}

// Function to enable OutputEvent
void  AFIO_enableOutputEvent(void)
{
	SET_BIT(AFIO->EVCR,7);
}

// Function to disable OutputEvent
void  AFIO_voidDisableOutputEvent(void)
{
	CLR_BIT(AFIO->EVCR,7);
}

// Function to remap periphirals pins
void  AFIO_remapPeriphiralPins(AfioPeriphiralMap_type PeriphiralMap)
{
	// Validate input parameters
	ASSERT(PeriphiralMap >= 0 && PeriphiralMap < PERIPHERAL_MAP_ERR);

	// Remap periphiral
	switch(PeriphiralMap)
	{
        case AFIO_REMAP_SPI1               : SET_BIT(AFIO->MAPR,0); break;
        case AFIO_REMAP_I2C1               : SET_BIT(AFIO->MAPR,1); break;
        case AFIO_REMAP_USART1             : SET_BIT(AFIO->MAPR,2); break;
        case AFIO_REMAP_USART2             : SET_BIT(AFIO->MAPR,3); break;
        case AFIO_REMAP_USART3_MAP1        : SET_BIT(AFIO->MAPR,4);  CLR_BIT(AFIO->MAPR,5);  break;
        case AFIO_REMAP_USART3_MAP2        : SET_BIT(AFIO->MAPR,4);  SET_BIT(AFIO->MAPR,5);  break;
        case AFIO_REMAP_TIM1_MAP1          : SET_BIT(AFIO->MAPR,6);  CLR_BIT(AFIO->MAPR,7);  break;
        case AFIO_REMAP_TIM1_MAP2          : SET_BIT(AFIO->MAPR,6);  SET_BIT(AFIO->MAPR,7);  break;
        case AFIO_REMAP_TIM2_MAP1          : SET_BIT(AFIO->MAPR,8);  CLR_BIT(AFIO->MAPR,9);  break;
        case AFIO_REMAP_TIM2_MAP2          : CLR_BIT(AFIO->MAPR,8);   SET_BIT(AFIO->MAPR,9); break;
        case AFIO_REMAP_TIM2_MAP3          : SET_BIT(AFIO->MAPR,8);  SET_BIT(AFIO->MAPR,9);  break;
        case AFIO_REMAP_TIM3_MAP1          : CLR_BIT(AFIO->MAPR,10); SET_BIT(AFIO->MAPR,11); break;
        case AFIO_REMAP_TIM3_MAP2          : SET_BIT(AFIO->MAPR,10); SET_BIT(AFIO->MAPR,11); break;
        case AFIO_REMAP_TIM4_MAP1          : SET_BIT(AFIO->MAPR,12);                         break;
        case AFIO_REMAP_CAN_MAP1           : CLR_BIT(AFIO->MAPR,13); CLR_BIT(AFIO->MAPR,14); break;
        case AFIO_REMAP_CAN_MAP2           : CLR_BIT(AFIO->MAPR,13); SET_BIT(AFIO->MAPR,14); break;
        case AFIO_REMAP_CAN_MAP3           : SET_BIT(AFIO->MAPR,13); SET_BIT(AFIO->MAPR,14); break;
        case AFIO_REMAP_PD0                : SET_BIT(AFIO->MAPR,15); break;
        case AFIO_REMAP_TIM5CH4_MAP1       : CLR_BIT(AFIO->MAPR,16); break;
        case AFIO_REMAP_TIM5CH4_MAP2       : SET_BIT(AFIO->MAPR,16); break;
        case AFIO_REMAP_ADC1_INJEC_MAP1    : CLR_BIT(AFIO->MAPR,17); break;
        case AFIO_REMAP_ADC1_INJEC_MAP2    : SET_BIT(AFIO->MAPR,17); break;
        case AFIO_REMAP_ADC1_REGULAR_MAP1  : CLR_BIT(AFIO->MAPR,18); break;
        case AFIO_REMAP_ADC1_REGULAR_MAP2  : SET_BIT(AFIO->MAPR,18); break;
		case AFIO_REMAP_ADC2_INJEC_MAP1    : CLR_BIT(AFIO->MAPR,19); break;
        case AFIO_REMAP_ADC2_INJEC_MAP2    : SET_BIT(AFIO->MAPR,19); break;
        case AFIO_REMAP_ADC2_REGULAR_MAP1  : CLR_BIT(AFIO->MAPR,20); break;
        case AFIO_REMAP_ADC2_REGULAR_MAP2  : SET_BIT(AFIO->MAPR,20); break;
        case AFIO_REMAP_JTAG_MAP1          : CLR_BIT(AFIO->MAPR,24); CLR_BIT(AFIO->MAPR,25); CLR_BIT(AFIO->MAPR,26); break;
        case AFIO_REMAP_JTAG_MAP2          : SET_BIT(AFIO->MAPR,24); CLR_BIT(AFIO->MAPR,25); CLR_BIT(AFIO->MAPR,26); break;
        case AFIO_REMAP_JTAG_MAP3          : CLR_BIT(AFIO->MAPR,24); SET_BIT(AFIO->MAPR,25); CLR_BIT(AFIO->MAPR,26); break;
        case AFIO_REMAP_JTAG_MAP4          : CLR_BIT(AFIO->MAPR,24); CLR_BIT(AFIO->MAPR,25); SET_BIT(AFIO->MAPR,26); break;							       			
        case AFIO_REMAP_TIM9               : SET_BIT(AFIO->MAPR2,5);  break;
        case AFIO_REMAP_TIM10              : SET_BIT(AFIO->MAPR2,6);  break;
        case AFIO_REMAP_TIM11              : SET_BIT(AFIO->MAPR2,7);  break;
        case AFIO_REMAP_TIM13              : SET_BIT(AFIO->MAPR2,8);  break;
        case AFIO_REMAP_TIM114             : SET_BIT(AFIO->MAPR2,9);  break;
        case AFIO_REMAP_FSMC_NADV          : SET_BIT(AFIO->MAPR2,10); break;
		default: /* Do nothing */ break;
	}                                          
}	
