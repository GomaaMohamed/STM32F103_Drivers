/*****************************************************************************
* @file:    GPTM_program.c
* @author:  Copyright (c) 2023 Gomaa Mohammed Gomaa.
* @license: GNU GPL version 3 or later.
*			This is free software: you are free to change and redistribute it.  
*			There is NO WARRANTY, to the extent permitted by law.
* @version: V0.2   
* @date:    Tue, 17 Aug 2023 21:35:12 +0200
* @brief:   Advanced Timers(GPTIM) Driver for STM32F103
******************************************************************************/

/* ==================================================================== */
/* ========================== include files =========================== */
/* ==================================================================== */
#include     "STD_TYPES.h"
#include     "BIT_MATH.h"

#include     "ATIM_interface.h"
#include     "ATIM_private.h"
#include     "ATIM_config.h"

/* ==================================================================== */
/* ================= Public Functions Implementation ================== */
/* ==================================================================== */

/*************************** Timer2 ********************************/

// Function to initialize timer 2
void TIM1_init(TimerMode_type TimerMode, 
			   CountMode_type CountMode, 
			   u16 TimerPrescaler)
{
	// Validate input parameters
	ASSERT(TimerMode >= 0 && TimerMode < TIMER_MODE_ERR);
	ASSERT(CountMode >= 0 && CountMode < 7 );
	ASSERT(TimerPrescaler >= 1 && TimerPrescaler < 65535);

	// Configure auto reload
	#if TIMER1_ARR_BUFFERED == ARR_BUFFERD_ENABLED
		SET_BIT(TIM1->CR1,7);
	#elif TIMER1_ARR_BUFFERED == ARR_BUFFERD_DISABLED
		CLR_BIT(TIM1->CR1,7);
	#endif

	// Configure update event
	#if TIMER1_UPDATE_EVENT == UPDATE_EVENT_ENABLED
		CLR_BIT(TIM1->CR1,1);
		// Select update event source
		#if TIMER1_UPDATE_EVENT_SOURCE == UPDATE_EVENT_SOURCE_OVF
			SET_BIT(TIM1->CR1,2);
		#elif TIMER1_UPDATE_EVENT_SOURCE == UPDATE_EVENT_SOURCE_OVF_UG_SLV
			CLR_BIT(TIM1->CR1,2);
		#endif
		// disable update interrupt
		CLR_BIT(TIM1->DIER,0);
	#elif TIMER1_UPDATE_EVENT == UPDATE_EVENT_DISABLED
		SET_BIT(TIM1->CR1,1);
	#endif

	// Select clock
	#if  TIMER1_CLOCK_SELECTION == CLOCK_INTERNAL_RCC
		// Disable slave mode
		TIM1->SMCR &= ~(0b111 << 0);
	#elif  TIMER1_CLOCK_SELECTION == CLOCK_
	#endif

	// Set timer mode
	switch (TimerMode)
	{
		case ONE_PULSE_MODE:
			SET_BIT(TIM1->CR1,3);
			break;
		default:
			// Do nothing
			break;
	}

	// Set input filters parameters in case of input modes 
	if (TimerMode >= INPUT_CAPTURE_MODE && TimerMode <= ONE_PULSE_MODE)
	{
		// Configure filters clock
		TIM1->CR1 |= (TIMER1_FILTER_DTS << 8);

		// Configure filters sampling rate
		// ETR
		TIM1->SMCR &= ~(0b1111 << 8);
		TIM1->SMCR |= (TIMER1_ETR_FILTER << 8);
		// TI1
		TIM1->CCMR1 &= ~(0b1111 << 4);
		TIM1->CCMR1 |= (TIMER1_TI1_FILTER << 4);
		// TI2
		TIM1->CCMR1 &= ~(0b1111 << 12);
		TIM1->CCMR1 |= (TIMER1_TI2_FILTER << 12);
		// TI3
		TIM1->CCMR2 &= ~(0b1111 << 4);
		TIM1->CCMR2 |= (TIMER1_TI3_FILTER << 4);
		// TI4
		TIM1->CCMR2 &= ~(0b1111 << 12);
		TIM1->CCMR2 |= (TIMER1_TI4_FILTER << 12);

		// Configure capture compare prescalers
		// ETR
		TIM1->SMCR &= ~(0b11 << 12);
		TIM1->SMCR |= (TIMER1_ETR_PRESCALER << 12);
		// TI1
		TIM1->CCMR1 &= ~(0b11 << 2);
		TIM1->CCMR1 |= (TIMER1_TI1_PRESCALER << 2);
		// TI2
		TIM1->CCMR1 &= ~(0b11 << 12);
		TIM1->CCMR1 |= (TIMER1_TI2_PRESCALER << 10);
		// TI3
		TIM1->CCMR2 &= ~(0b11 << 2);
		TIM1->CCMR2 |= (TIMER1_TI3_PRESCALER << 2);
		// TI4
		TIM1->CCMR2 &= ~(0b11 << 12);
		TIM1->CCMR2 |= (TIMER1_TI4_PRESCALER << 10);
	}

	// Set count mode
	TIM1->CR1 |= (CountMode << 4);

	// Set prescaler
	TIM1->PSC = TimerPrescaler;
	Timer1Prescaler = TimerPrescaler;

	// Update timer registers
	if (CountMode == COUNT_UP || CountMode == COUNT_UP_DOWN)
	{
		TIM1->ARR = 65535;
	}
	else
	{
		TIM1->ARR = 0;
	}
	TIM1->SR = 0;
	SET_BIT(TIM1->EGR,0);

	// Initialize channels as input by default to avoid setting flags
	TIM1->CCMR1 |= (1 << 0);
	TIM1->CCMR1 |= (1 << 8);
	TIM1->CCMR2 |= (1 << 0);
	TIM1->CCMR2 |= (1 << 8);

	// Enable timer
	SET_BIT(TIM1->CR1, 0);
}

// Function to initialize channels of timer2
void TIM1_initChannel(ChannelSelect_type ChannelId, 
					  ChannelOutputInput_type ChannelMode,
					  CaptureComparePolarity_type CaptureComparePolarity,
					  PreloadEnable_type PreloadEnableDisable,
                      FastEnable_type FastEnableDisable)
{
	// Validate input parameters
	ASSERT(ChannelId >= 0 && ChannelId < CHANNEL_ERR);
	ASSERT(ChannelMode >= 0 && ChannelMode < CH_MODE_ERR);
	ASSERT(CaptureComparePolarity >= 0 && CaptureComparePolarity < CAPTURE_COMPARE_POL_ERR);
	ASSERT(PreloadEnableDisable >= 0 && PreloadEnableDisable < PRELOAD_ERR);
	ASSERT(FastEnableDisable >= 0 && FastEnableDisable < FAST_ERR);
	// Additional validations
	if (ChannelMode >= CH_INPUT_TI1 && ChannelMode <= CH_INPUT_TRC)
	{
		if (ChannelId == CHANNEL1 || ChannelId == CHANNEL2)
		{
			ASSERT((ChannelMode == CH_INPUT_TI1 || ChannelMode == CH_INPUT_TI2 || ChannelMode == CH_INPUT_TRC));
		}
		else if (ChannelId == CHANNEL3 || ChannelId == CHANNEL4)
		{
			ASSERT((ChannelMode == CH_INPUT_TI3 || ChannelMode == CH_INPUT_TI4 || ChannelMode == CH_INPUT_TRC));
		}
	}
	
	// Select channel to set its parameters
	switch (ChannelId)
	{
	case CHANNEL1:

		// Set channel mode
		if (ChannelMode >= 0 && ChannelMode < 8 )
		{
			// Select output mode
			TIM1->CCMR1 &= ~(0b11 << 0);
			TIM1->CCMR1 |= (ChannelMode << 4);

			// Set preload enable disable
			if (PreloadEnableDisable == PRELOAD_ENABLE)
			{
				// Enable preload
				SET_BIT(TIM1->CCMR1, 3);
			}
			else if (PreloadEnableDisable == PRELOAD_DISABLE)
			{
				// Disable preload
				CLR_BIT(TIM1->CCMR1, 3);
			}

			// Set fast enable disable
			if (FastEnableDisable == FAST_ENABLE)
			{
				// Enable fast
				SET_BIT(TIM1->CCMR1, 2);
			}
			else if (FastEnableDisable == FAST_DISABLE)
			{
				// Disable fast
				SET_BIT(TIM1->CCMR1, 2);
			}
		}
		else 
		{
			// Adjust parameter 
			if (ChannelMode == CH_INPUT_TRC)
			{
				ChannelMode -= 9;
			}
			else if (ChannelMode == CH_INPUT_TI1)
			{
				ChannelMode -= 7;
			}
			else if (ChannelMode == CH_INPUT_TI2)
			{
				ChannelMode -= 7;
			}
			
			// Select input mode
			TIM1->CCMR1 &= ~(0b11 << 0);
			TIM1->CCMR1 |= (ChannelMode << 0);
		}

		// Set capture compare polarity
		if (CaptureComparePolarity == CAPTURE_COMPARE_POL_0)
		{
			// Enable capture compare
			CLR_BIT(TIM1->CCER, 1);
		}
		else if (CaptureComparePolarity == CAPTURE_COMPARE_POL_1)
		{
			// Enable capture compare
			SET_BIT(TIM1->CCER, 1);
		}

		// Enable capture compare
		SET_BIT(TIM1->CCER, 0);
		break;
	case CHANNEL2:

		// Set channel mode
		if (ChannelMode >= 0 && ChannelMode < 8 )
		{
			// Select output mode
			TIM1->CCMR1 &= ~(0b11 << 8);
			TIM1->CCMR1 |= (ChannelMode << 12);

			// Set preload enable disable
			if (PreloadEnableDisable == PRELOAD_ENABLE)
			{
				// Enable preload
				SET_BIT(TIM1->CCMR1, 11);
			}
			else if (PreloadEnableDisable == PRELOAD_DISABLE)
			{
				// Disable preload
				CLR_BIT(TIM1->CCMR1, 11);
			}

			// Set fast enable disable
			if (FastEnableDisable == FAST_ENABLE)
			{
				// Enable fast
				SET_BIT(TIM1->CCMR1, 10);
			}
			else if (FastEnableDisable == FAST_DISABLE)
			{
				// Disable fast
				SET_BIT(TIM1->CCMR1, 10);
			}
		}
		else 
		{
			// Adjust parameter 
			if (ChannelMode == CH_INPUT_TRC)
			{
				ChannelMode -= 9;
			}
			else if (ChannelMode == CH_INPUT_TI1)
			{
				ChannelMode -= 6;
			}
			else if (ChannelMode == CH_INPUT_TI2)
			{
				ChannelMode -= 8;
			}
				
			// Select input mode
			TIM1->CCMR1 &= ~(0b11 << 8);
			TIM1->CCMR1 |= (ChannelMode << 8);
		}

		// Set capture compare polarity
		if (CaptureComparePolarity == CAPTURE_COMPARE_POL_0)
		{
			// Enable capture compare
			CLR_BIT(TIM1->CCER, 5);
		}
		else if (CaptureComparePolarity == CAPTURE_COMPARE_POL_1)
		{
			// Enable capture compare
			SET_BIT(TIM1->CCER, 5);
		}

		// Enable capture compare
		SET_BIT(TIM1->CCER, 4);
		break;
	case CHANNEL3:

		// Set channel mode
		if (ChannelMode >= 0 && ChannelMode < 8 )
		{
			// Select output mode
			TIM1->CCMR2 &= ~(0b11 << 0);
			TIM1->CCMR2 |= (ChannelMode << 4);

			// Set preload enable disable
			if (PreloadEnableDisable == PRELOAD_ENABLE)
			{
				// Enable preload
				SET_BIT(TIM1->CCMR2, 3);
			}
			else if (PreloadEnableDisable == PRELOAD_DISABLE)
			{
				// Disable preload
				CLR_BIT(TIM1->CCMR2, 3);
			}

			// Set fast enable disable
			if (FastEnableDisable == FAST_ENABLE)
			{
				// Enable fast
				SET_BIT(TIM1->CCMR2, 2);
			}
			else if (FastEnableDisable == FAST_DISABLE)
			{
				// Disable fast
				SET_BIT(TIM1->CCMR2, 2);
			}
		}
		else if (ChannelMode >= 8 && ChannelMode < CH_MODE_ERR)
		{
			// Adjust parameter 
			if (ChannelMode == CH_INPUT_TRC)
			{
				ChannelMode -= 9;
			}
			else if (ChannelMode == CH_INPUT_TI3)
			{
				ChannelMode -= 9;
			}
			else if (ChannelMode == CH_INPUT_TI4)
			{
				ChannelMode -= 9;
			}
			// Select input mode
			TIM1->CCMR2 &= ~(0b11 << 0);
			TIM1->CCMR2 |= (ChannelMode << 0);
		}

		// Set capture compare polarity
		if (CaptureComparePolarity == CAPTURE_COMPARE_POL_0)
		{
			// Enable capture compare
			CLR_BIT(TIM1->CCER, 9);
		}
		else if (CaptureComparePolarity == CAPTURE_COMPARE_POL_1)
		{
			// Enable capture compare
			SET_BIT(TIM1->CCER, 9);
		}

		// Enable capture compare
		SET_BIT(TIM1->CCER, 8);
		break;
	case CHANNEL4:

		// Set channel mode
		if (ChannelMode >= 0 && ChannelMode < 8 )
		{
			// Select output mode
			TIM1->CCMR2 &= ~(0b11 << 8);
			TIM1->CCMR2 |= (ChannelMode << 12);

			// Set preload enable disable
			if (PreloadEnableDisable == PRELOAD_ENABLE)
			{
				// Enable preload
				SET_BIT(TIM1->CCMR1, 11);
			}
			else if (PreloadEnableDisable == PRELOAD_DISABLE)
			{
				// Disable preload
				CLR_BIT(TIM1->CCMR1, 11);
			}

			// Set fast enable disable
			if (FastEnableDisable == FAST_ENABLE)
			{
				// Enable fast
				SET_BIT(TIM1->CCMR1, 10);
			}
			else if (FastEnableDisable == FAST_DISABLE)
			{
				// Disable fast
				SET_BIT(TIM1->CCMR1, 10);
			}
		}
		else if (ChannelMode >= 8 && ChannelMode < CH_MODE_ERR)
		{
			// Adjust parameter 
			if (ChannelMode == CH_INPUT_TRC)
			{
				ChannelMode -= 9;
			}
			else if (ChannelMode == CH_INPUT_TI3)
			{
				ChannelMode -= 8;
			}
			else if (ChannelMode == CH_INPUT_TI4)
			{
				ChannelMode -= 10;
			}
			// Select input mode
			TIM1->CCMR2 &= ~(0b11 << 8);
			TIM1->CCMR2 |= (ChannelMode << 8);
		}

		// Set capture compare polarity
		if (CaptureComparePolarity == CAPTURE_COMPARE_POL_0)
		{
			// Enable capture compare
			CLR_BIT(TIM1->CCER, 13);
		}
		else if (CaptureComparePolarity == CAPTURE_COMPARE_POL_1)
		{
			// Enable capture compare
			SET_BIT(TIM1->CCER, 13);
		}

		// Enable capture compare
		SET_BIT(TIM1->CCER, 12);
		break;
	default:
		// Do nothing
		break;
	}
}

// Function to change capture compare edge
void TIM1_changeCaptureComparePolarity(ChannelSelect_type ChannelId, 
                      CaptureComparePolarity_type CaptureComparePolarity)
{
	// Validate input parameters
	ASSERT(ChannelId >= 0 && ChannelId < CHANNEL_ERR);
	ASSERT(CaptureComparePolarity >= 0 && CaptureComparePolarity < CAPTURE_COMPARE_POL_ERR);

	// Select channel to set its parameters
	switch (ChannelId)
	{
	case CHANNEL1:

		// Set capture compare polarity
		if (CaptureComparePolarity == CAPTURE_COMPARE_POL_0)
		{
			// Enable capture compare
			CLR_BIT(TIM1->CCER, 1);
		}
		else if (CaptureComparePolarity == CAPTURE_COMPARE_POL_1)
		{
			// Enable capture compare
			SET_BIT(TIM1->CCER, 1);
		}
		break;
	case CHANNEL2:
		
		// Set capture compare polarity
		if (CaptureComparePolarity == CAPTURE_COMPARE_POL_0)
		{
			// Enable capture compare
			CLR_BIT(TIM1->CCER, 5);
		}
		else if (CaptureComparePolarity == CAPTURE_COMPARE_POL_1)
		{
			// Enable capture compare
			SET_BIT(TIM1->CCER, 5);
		}
		break;
	case CHANNEL3:

		// Set capture compare polarity
		if (CaptureComparePolarity == CAPTURE_COMPARE_POL_0)
		{
			// Enable capture compare
			CLR_BIT(TIM1->CCER, 9);
		}
		else if (CaptureComparePolarity == CAPTURE_COMPARE_POL_1)
		{
			// Enable capture compare
			SET_BIT(TIM1->CCER, 9);
		}
		break;
	case CHANNEL4:
		
		// Set capture compare polarity
		if (CaptureComparePolarity == CAPTURE_COMPARE_POL_0)
		{
			// Enable capture compare
			CLR_BIT(TIM1->CCER, 13);
		}
		else if (CaptureComparePolarity == CAPTURE_COMPARE_POL_1)
		{
			// Enable capture compare
			SET_BIT(TIM1->CCER, 13);
		}
		break;
	default:
		// Do nothing
		break;
	}
}

// Function to make a delay with specific ticks
void TIM1_setBusyWait(u16 Ticks)
{
	// Disable timer
	CLR_BIT(TIM1->CR1,0);

	// Upload timer
	TIM1->ARR = Ticks;
	SET_BIT(TIM1->EGR,0);

	// Enable Timer
	SET_BIT(TIM1->CR1,0);
	while(GET_BIT(TIM1->SR,0)==0);

	// Clear Uderflow Flag
	CLR_BIT(TIM1->SR,0);

	// Disable timer
	CLR_BIT(TIM1->CR1,0);
}

// Function to call another function after number of ticks one time
void TIM1_setSingleInterval(u16 Ticks, void (*Callback)(void))
{
	// Validate input parameters
	ASSERT(Callback != NULL);

	// Save callBack
	TIM1_UnderflowCallback=Callback;

	// Set Mode to Single
	Timer1IntervalModeFlag=1;

	// stop timer 
	CLR_BIT(TIM1->CR1,ATIM_CEN);

	// Re-Initialize the the counter 
	TIM1->ARR=Ticks;
	SET_BIT(TIM1->EGR,ATIM_UG);
		
	// Enable Update Interrupt 
	SET_BIT(TIM1->DIER,ATIM_UIE);

	// Enable counter
	SET_BIT(TIM1->CR1,ATIM_CEN);
	
}

// Function to call another function after number of ticks periodic
void TIM1_setPeriodicInterval(u16 Ticks, void (*Callback)(void))
{
	// Validate input parameters
	ASSERT(Callback != NULL);

	// Save callBack
	TIM1_UnderflowCallback=Callback;

	// Set Mode to Single
	Timer1IntervalModeFlag=0;

	// stop timer 
	CLR_BIT(TIM1->CR1,ATIM_CEN);

	// Re-Initialize the the counter 
	TIM1->ARR=Ticks;
	SET_BIT(TIM1->EGR,ATIM_UG);
		
	// Enable Update Interrupt 
	SET_BIT(TIM1->DIER,ATIM_UIE);

	// Enable counter
	SET_BIT(TIM1->CR1,ATIM_CEN);
	
}

// Function to reload timer value
void TIM1_reloadTimerValue(u16 TimerValue)
{
	TIM1->CNT = TimerValue;
}
u16  TIM1_getTimerValue(void)
{
	return TIM1->CNT;
}

// Function to reload capture compare value
void TIM1_reloadCaptureCompareValue(ChannelSelect_type ChannelId,u16 CaptureCompareValue)
{
	// Validate input parameters
	ASSERT(ChannelId >= 0 && ChannelId < CHANNEL_ERR);

	// Temp variable to hold the CCR of the nedded channel
	u16 TempValue = 0; 

	// Select a channel to return its value
	switch (ChannelId)
	{
	case CHANNEL1:
		TIM1->CCR1 = CaptureCompareValue;
		break;
	case CHANNEL2:
		TIM1->CCR2 = CaptureCompareValue;
		break;
	case CHANNEL3:
		TIM1->CCR3 = CaptureCompareValue;
		break;
	case CHANNEL4:
		TIM1->CCR4 = CaptureCompareValue;
		break;
	default:
		// Do nothing
		break;
	}
}

// Function to get capture compare value
u16  TIM1_getCaptureCompareValue(ChannelSelect_type ChannelId)
{
	// Validate input parameters
	ASSERT(ChannelId >= 0 && ChannelId < CHANNEL_ERR);

	// Temp variable to hold the CCR of the nedded channel
	u16 TempValue = 0; 

	// Select a channel to return its value
	switch (ChannelId)
	{
	case CHANNEL1:
		TempValue = TIM1->CCR1;
		break;
	case CHANNEL2:
		TempValue = TIM1->CCR2;
		break;
	case CHANNEL3:
		TempValue = TIM1->CCR3;
		break;
	case CHANNEL4:
		TempValue = TIM1->CCR4;
		break;
	default:
		// Do nothing
		break;
	}
	return TempValue;
}

// Function to restart timer
void TIM1_restartTimer(void)
{
	// Enable counter
	SET_BIT(TIM1->CR1, 0);
}

// Function to stop timer
void TIM1_stopTimer(void)
{
	// Disable counter
	CLR_BIT(TIM1->CR1, 0);
}

// Function to enable capture compare interrupt
void TIM1_enableCaptureCompareInterrupt(ChannelSelect_type ChannelId)
{
	// Validate input parameters
	ASSERT(ChannelId >= 0 && ChannelId < CHANNEL_ERR);

	// Select a channel to return its value
	switch (ChannelId)
	{
	case CHANNEL1:
		SET_BIT(TIM1->DIER,1);
		break;
	case CHANNEL2:
		SET_BIT(TIM1->DIER,2);
		break;
	case CHANNEL3:
		SET_BIT(TIM1->DIER,3);
		break;
	case CHANNEL4:
		SET_BIT(TIM1->DIER,4);
		break;
	default:
		// Do nothing
		break;
	}
}

// Function to disable capture compare interrupt
void TIM1_disableCaptureCompareInterrupt(ChannelSelect_type ChannelId)
{
	// Validate input parameters
	ASSERT(ChannelId >= 0 && ChannelId < CHANNEL_ERR);

	// Select a channel to return its value
	switch (ChannelId)
	{
	case CHANNEL1:
		CLR_BIT(TIM1->DIER,1);
		break;
	case CHANNEL2:
		CLR_BIT(TIM1->DIER,2);
		break;
	case CHANNEL3:
		CLR_BIT(TIM1->DIER,3);
		break;
	case CHANNEL4:
		CLR_BIT(TIM1->DIER,4);
		break;
	default:
		// Do nothing
		break;
	}
}

// Function to set capture compare callback
void TIM1_setCaptureCompareCallback(ChannelSelect_type ChannelId,void (*Callback)(void))
{
	// Validate input parameters
	ASSERT(ChannelId >= 0 && ChannelId < CHANNEL_ERR);
	ASSERT(Callback != NULL);

	// Select a channel to return its value
	switch (ChannelId)
	{
	case CHANNEL1:
		TIM1_CH1_CaptureCompareCallback = Callback;
		break;
	case CHANNEL2:
		TIM1_CH2_CaptureCompareCallback = Callback;
		break;
	case CHANNEL3:
		TIM1_CH3_CaptureCompareCallback = Callback;
		break;
	case CHANNEL4:
		TIM1_CH4_CaptureCompareCallback = Callback;
		break;
	default:
		// Do nothing
		break;
	}
}

// Function to set pwm1 parameters
void TIM1_generatePWM1(ChannelSelect_type ChannelId,u32 Frequency,u8 DutyCycle)
{
	// Validate input parameters
	ASSERT(ChannelId >= 0 && ChannelId < CHANNEL_ERR);

	// Disable timer
	CLR_BIT(TIM1->CR1,0);

	// Set pwm parameters
	u16 Temp1 = (4000000/(Timer1Prescaler*Frequency))+1;
	u16 Temp2 = (((Temp1+1)/ 100)*DutyCycle)+1;
	TIM1->CCR1 = Temp2;
	TIM1->ARR = Temp1;

	// Update registers
	SET_BIT(TIM1->EGR,0);

	// Enable Timer
	SET_BIT(TIM1->CR1,0);
}

// Function to set pwm2 parameters
void TIM1_generatePWM2(ChannelSelect_type ChannelId,u32 Frequency,u8 DutyCycle)
{
	// Validate input parameters
	ASSERT(ChannelId >= 0 && ChannelId < CHANNEL_ERR);
	
	// Disable timer
	CLR_BIT(TIM1->CR1,0);

	// Set pwm parameters
	u16 Temp1 = 4000000/(2*Timer1Prescaler*Frequency);
	u16 Temp2 = (Temp1/ 100)*DutyCycle;
	TIM1->ARR = Temp1;
	TIM1->CCR1 = Temp2;

	// Update registers
	SET_BIT(TIM1->EGR,0);

	// Enable Timer
	SET_BIT(TIM1->CR1,0);

}





/* ==================================================================== */
/* ================ Private Functions Implementation ================== */
/* ==================================================================== */

// Timer1 isr
void TIM1_IRQHandler(void)
{
	// Overflow callback	
	if (GET_BIT(TIM1->SR,0) == 1 && GET_BIT(TIM1->DIER,0) == 1 && TIM1_OverflowCallback != NULL)
	{
		TIM1_OverflowCallback();
		CLR_BIT(TIM1->SR, 0);
		if (Timer1IntervalModeFlag == 1)
		{
			// Disable timer
			CLR_BIT(TIM1->CR1, 0);
		}	
	}

	// Channel1 callback
	if (GET_BIT(TIM1->SR,1) == 1 && GET_BIT(TIM1->DIER,1) == 1 && TIM1_CH1_CaptureCompareCallback != NULL)
	{
		TIM1_CH1_CaptureCompareCallback();
		CLR_BIT(TIM1->SR, 1);
	}

	// Channel2 callback
	if (GET_BIT(TIM1->SR,2) == 1 && GET_BIT(TIM1->DIER,2) == 1 && TIM1_CH2_CaptureCompareCallback != NULL)  
	{
		TIM1_CH2_CaptureCompareCallback();
		CLR_BIT(TIM1->SR, 2);
	}

	// Channel3 callback
	if (GET_BIT(TIM1->SR,3) == 1 && GET_BIT(TIM1->DIER,3) == 1 && TIM1_CH3_CaptureCompareCallback != NULL)
	{
		TIM1_CH3_CaptureCompareCallback();
		CLR_BIT(TIM1->SR, 3);
	}

	// Channel4 callback
	if (GET_BIT(TIM1->SR,4) == 1 && GET_BIT(TIM1->DIER,4) == 1 && TIM1_CH4_CaptureCompareCallback != NULL)
	{
		TIM1_CH4_CaptureCompareCallback();
		CLR_BIT(TIM1->SR, 4);
	}

}