/*****************************************************************************
* @file:    GPTM_program.c
* @author:  Copyright (c) 2023 Gomaa Mohammed Gomaa.
* @license: GNU GPL version 3 or later.
*			This is free software: you are free to change and redistribute it.  
*			There is NO WARRANTY, to the extent permitted by law.
* @version: V0.2   
* @date:    Sun, 15 Oct 2023 14:21:12 +0200
* @brief:   General Purpose Timers(GPTIM) Driver for STM32F103
******************************************************************************/

/* ==================================================================== */
/* ========================== include files =========================== */
/* ==================================================================== */
#include     "STD_TYPES.h"
#include     "BIT_MATH.h"

#include     "GPTIM_interface.h"
#include     "GPTIM_private.h"
#include     "GPTIM_config.h"

/* ==================================================================== */
/* ================= Public Functions Implementation ================== */
/* ==================================================================== */

/*************************** Timer2 ********************************/

// Function to initialize timer2
void TIM2_init(TimerMode_type TimerMode, 
			   CountMode_type CountMode, 
			   u16 TimerPrescaler)
{
	// Validate input parameters
	ASSERT(TimerMode >= 0 && TimerMode < TIMER_MODE_ERR);
	ASSERT(CountMode >= 0 && CountMode < 7 );
	ASSERT(TimerPrescaler >= 1 && TimerPrescaler < 65535);

	// Configure auto reload
	#if TIMER2_ARR_BUFFERED == ARR_BUFFERD_ENABLED
		SET_BIT(TIM2->CR1,7);
	#elif TIMER2_ARR_BUFFERED == ARR_BUFFERD_DISABLED
		CLR_BIT(TIM2->CR1,7);
	#endif

	// Configure update event
	#if TIMER2_UPDATE_EVENT == UPDATE_EVENT_ENABLED
		CLR_BIT(TIM2->CR1,1);
		// Select update event source
		#if TIMER2_UPDATE_EVENT_SOURCE == UPDATE_EVENT_SOURCE_OVF
			SET_BIT(TIM2->CR1,2);
		#elif TIMER2_UPDATE_EVENT_SOURCE == UPDATE_EVENT_SOURCE_OVF_UG_SLV
			CLR_BIT(TIM2->CR1,2);
		#endif
		// disable update interrupt
		CLR_BIT(TIM2->DIER,0);
	#elif TIMER2_UPDATE_EVENT == UPDATE_EVENT_DISABLED
		SET_BIT(TIM2->CR1,1);
	#endif

	// Select clock
	#if  TIMER2_CLOCK_SELECTION == CLOCK_INTERNAL_RCC
		// Disable slave mode
		TIM2->SMCR &= ~(0b111 << 0);
	#elif  TIMER2_CLOCK_SELECTION == CLOCK_
	#endif

	// Set timer mode
	switch (TimerMode)
	{
		case ONE_PULSE_MODE:
			SET_BIT(TIM2->CR1,3);
			break;
		default:
			// Do nothing
			break;
	}

	// Set input filters parameters in case of input modes 
	if (TimerMode >= INPUT_CAPTURE_MODE && TimerMode <= ONE_PULSE_MODE)
	{
		// Configure filters clock
		TIM2->CR1 |= (TIMER2_FILTER_DTS << 8);

		// Configure filters sampling rate
		// ETR
		TIM2->SMCR &= ~(0b1111 << 8);
		TIM2->SMCR |= (TIMER2_ETR_FILTER << 8);
		// TI1
		TIM2->CCMR1 &= ~(0b1111 << 4);
		TIM2->CCMR1 |= (TIMER2_TI1_FILTER << 4);
		// TI2
		TIM2->CCMR1 &= ~(0b1111 << 12);
		TIM2->CCMR1 |= (TIMER2_TI2_FILTER << 12);
		// TI3
		TIM2->CCMR2 &= ~(0b1111 << 4);
		TIM2->CCMR2 |= (TIMER2_TI3_FILTER << 4);
		// TI4
		TIM2->CCMR2 &= ~(0b1111 << 12);
		TIM2->CCMR2 |= (TIMER2_TI4_FILTER << 12);

		// Configure capture compare prescalers
		// ETR
		TIM2->SMCR &= ~(0b11 << 12);
		TIM2->SMCR |= (TIMER2_ETR_PRESCALER << 12);
		// TI1
		TIM2->CCMR1 &= ~(0b11 << 2);
		TIM2->CCMR1 |= (TIMER2_TI1_PRESCALER << 2);
		// TI2
		TIM2->CCMR1 &= ~(0b11 << 12);
		TIM2->CCMR1 |= (TIMER2_TI2_PRESCALER << 10);
		// TI3
		TIM2->CCMR2 &= ~(0b11 << 2);
		TIM2->CCMR2 |= (TIMER2_TI3_PRESCALER << 2);
		// TI4
		TIM2->CCMR2 &= ~(0b11 << 12);
		TIM2->CCMR2 |= (TIMER2_TI4_PRESCALER << 10);
	}

	// Set count mode
	TIM2->CR1 |= (CountMode << 4);

	// Set prescaler
	TIM2->PSC = TimerPrescaler;
	Timer2Prescaler = TimerPrescaler;

	// Update timer registers
	if (CountMode == COUNT_UP || CountMode == COUNT_UP_DOWN)
	{
		TIM2->ARR = 65535;
	}
	else
	{
		TIM2->ARR = 0;
	}
	TIM2->SR = 0;
	SET_BIT(TIM2->EGR,0);

	// Initialize channels as input by default to avoid setting flags
	TIM2->CCMR1 |= (1 << 0);
	TIM2->CCMR1 |= (1 << 8);
	TIM2->CCMR2 |= (1 << 0);
	TIM2->CCMR2 |= (1 << 8);

	// Enable timer
	SET_BIT(TIM2->CR1, 0);
}

// Function to initialize channels of timer2
void TIM2_initChannel(ChannelSelect_type ChannelId, 
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
			TIM2->CCMR1 &= ~(0b11 << 0);
			TIM2->CCMR1 |= (ChannelMode << 4);

			// Set preload enable disable
			if (PreloadEnableDisable == PRELOAD_ENABLE)
			{
				// Enable preload
				SET_BIT(TIM2->CCMR1, 3);
			}
			else if (PreloadEnableDisable == PRELOAD_DISABLE)
			{
				// Disable preload
				CLR_BIT(TIM2->CCMR1, 3);
			}

			// Set fast enable disable
			if (FastEnableDisable == FAST_ENABLE)
			{
				// Enable fast
				SET_BIT(TIM2->CCMR1, 2);
			}
			else if (FastEnableDisable == FAST_DISABLE)
			{
				// Disable fast
				SET_BIT(TIM2->CCMR1, 2);
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
			TIM2->CCMR1 &= ~(0b11 << 0);
			TIM2->CCMR1 |= (ChannelMode << 0);
		}

		// Set capture compare polarity
		if (CaptureComparePolarity == CAPTURE_COMPARE_POL_0)
		{
			// Enable capture compare
			CLR_BIT(TIM2->CCER, 1);
		}
		else if (CaptureComparePolarity == CAPTURE_COMPARE_POL_1)
		{
			// Enable capture compare
			SET_BIT(TIM2->CCER, 1);
		}

		// Enable capture compare
		SET_BIT(TIM2->CCER, 0);
		break;
	case CHANNEL2:

		// Set channel mode
		if (ChannelMode >= 0 && ChannelMode < 8 )
		{
			// Select output mode
			TIM2->CCMR1 &= ~(0b11 << 8);
			TIM2->CCMR1 |= (ChannelMode << 12);

			// Set preload enable disable
			if (PreloadEnableDisable == PRELOAD_ENABLE)
			{
				// Enable preload
				SET_BIT(TIM2->CCMR1, 11);
			}
			else if (PreloadEnableDisable == PRELOAD_DISABLE)
			{
				// Disable preload
				CLR_BIT(TIM2->CCMR1, 11);
			}

			// Set fast enable disable
			if (FastEnableDisable == FAST_ENABLE)
			{
				// Enable fast
				SET_BIT(TIM2->CCMR1, 10);
			}
			else if (FastEnableDisable == FAST_DISABLE)
			{
				// Disable fast
				SET_BIT(TIM2->CCMR1, 10);
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
			TIM2->CCMR1 &= ~(0b11 << 8);
			TIM2->CCMR1 |= (ChannelMode << 8);
		}

		// Set capture compare polarity
		if (CaptureComparePolarity == CAPTURE_COMPARE_POL_0)
		{
			// Enable capture compare
			CLR_BIT(TIM2->CCER, 5);
		}
		else if (CaptureComparePolarity == CAPTURE_COMPARE_POL_1)
		{
			// Enable capture compare
			SET_BIT(TIM2->CCER, 5);
		}

		// Enable capture compare
		SET_BIT(TIM2->CCER, 4);
		break;
	case CHANNEL3:

		// Set channel mode
		if (ChannelMode >= 0 && ChannelMode < 8 )
		{
			// Select output mode
			TIM2->CCMR2 &= ~(0b11 << 0);
			TIM2->CCMR2 |= (ChannelMode << 4);

			// Set preload enable disable
			if (PreloadEnableDisable == PRELOAD_ENABLE)
			{
				// Enable preload
				SET_BIT(TIM2->CCMR2, 3);
			}
			else if (PreloadEnableDisable == PRELOAD_DISABLE)
			{
				// Disable preload
				CLR_BIT(TIM2->CCMR2, 3);
			}

			// Set fast enable disable
			if (FastEnableDisable == FAST_ENABLE)
			{
				// Enable fast
				SET_BIT(TIM2->CCMR2, 2);
			}
			else if (FastEnableDisable == FAST_DISABLE)
			{
				// Disable fast
				SET_BIT(TIM2->CCMR2, 2);
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
			TIM2->CCMR2 &= ~(0b11 << 0);
			TIM2->CCMR2 |= (ChannelMode << 0);
		}

		// Set capture compare polarity
		if (CaptureComparePolarity == CAPTURE_COMPARE_POL_0)
		{
			// Enable capture compare
			CLR_BIT(TIM2->CCER, 9);
		}
		else if (CaptureComparePolarity == CAPTURE_COMPARE_POL_1)
		{
			// Enable capture compare
			SET_BIT(TIM2->CCER, 9);
		}

		// Enable capture compare
		SET_BIT(TIM2->CCER, 8);
		break;
	case CHANNEL4:

		// Set channel mode
		if (ChannelMode >= 0 && ChannelMode < 8 )
		{
			// Select output mode
			TIM2->CCMR2 &= ~(0b11 << 8);
			TIM2->CCMR2 |= (ChannelMode << 12);

			// Set preload enable disable
			if (PreloadEnableDisable == PRELOAD_ENABLE)
			{
				// Enable preload
				SET_BIT(TIM2->CCMR1, 11);
			}
			else if (PreloadEnableDisable == PRELOAD_DISABLE)
			{
				// Disable preload
				CLR_BIT(TIM2->CCMR1, 11);
			}

			// Set fast enable disable
			if (FastEnableDisable == FAST_ENABLE)
			{
				// Enable fast
				SET_BIT(TIM2->CCMR1, 10);
			}
			else if (FastEnableDisable == FAST_DISABLE)
			{
				// Disable fast
				SET_BIT(TIM2->CCMR1, 10);
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
			TIM2->CCMR2 &= ~(0b11 << 8);
			TIM2->CCMR2 |= (ChannelMode << 8);
		}

		// Set capture compare polarity
		if (CaptureComparePolarity == CAPTURE_COMPARE_POL_0)
		{
			// Enable capture compare
			CLR_BIT(TIM2->CCER, 13);
		}
		else if (CaptureComparePolarity == CAPTURE_COMPARE_POL_1)
		{
			// Enable capture compare
			SET_BIT(TIM2->CCER, 13);
		}

		// Enable capture compare
		SET_BIT(TIM2->CCER, 12);
		break;
	default:
		// Do nothing
		break;
	}
}

// Function to change capture compare edge
void TIM2_changeCaptureComparePolarity(ChannelSelect_type ChannelId, 
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
			CLR_BIT(TIM2->CCER, 1);
		}
		else if (CaptureComparePolarity == CAPTURE_COMPARE_POL_1)
		{
			// Enable capture compare
			SET_BIT(TIM2->CCER, 1);
		}
		break;
	case CHANNEL2:
		
		// Set capture compare polarity
		if (CaptureComparePolarity == CAPTURE_COMPARE_POL_0)
		{
			// Enable capture compare
			CLR_BIT(TIM2->CCER, 5);
		}
		else if (CaptureComparePolarity == CAPTURE_COMPARE_POL_1)
		{
			// Enable capture compare
			SET_BIT(TIM2->CCER, 5);
		}
		break;
	case CHANNEL3:

		// Set capture compare polarity
		if (CaptureComparePolarity == CAPTURE_COMPARE_POL_0)
		{
			// Enable capture compare
			CLR_BIT(TIM2->CCER, 9);
		}
		else if (CaptureComparePolarity == CAPTURE_COMPARE_POL_1)
		{
			// Enable capture compare
			SET_BIT(TIM2->CCER, 9);
		}
		break;
	case CHANNEL4:
		
		// Set capture compare polarity
		if (CaptureComparePolarity == CAPTURE_COMPARE_POL_0)
		{
			// Enable capture compare
			CLR_BIT(TIM2->CCER, 13);
		}
		else if (CaptureComparePolarity == CAPTURE_COMPARE_POL_1)
		{
			// Enable capture compare
			SET_BIT(TIM2->CCER, 13);
		}
		break;
	default:
		// Do nothing
		break;
	}
}

// Function to make a delay with specific ticks
void TIM2_setBusyWait(u16 Ticks)
{
	// Disable timer
	CLR_BIT(TIM2->CR1,0);

	// Upload timer
	TIM2->ARR = Ticks;
	SET_BIT(TIM2->EGR,0);

	// Enable Timer
	SET_BIT(TIM2->CR1,0);
	while(GET_BIT(TIM2->SR,0)==0);

	// Clear Uderflow Flag
	CLR_BIT(TIM2->SR,0);

	// Disable timer
	CLR_BIT(TIM2->CR1,0);
}

// Function to call another function after number of ticks one time
void TIM2_setSingleInterval(u16 Ticks, void (*Callback)(void))
{
	// Validate input parameters
	ASSERT(Callback != NULL);

	// Save callBack
	TIM2_UnderflowCallback=Callback;

	// Set Mode to Single
	Timer2IntervalModeFlag=1;

	// stop timer 
	CLR_BIT(TIM2->CR1,GPTIM_CEN);

	// Re-Initialize the the counter 
	TIM2->ARR=Ticks;
	SET_BIT(TIM2->EGR,GPTIM_UG);
		
	// Enable Update Interrupt 
	SET_BIT(TIM2->DIER,GPTIM_UIE);

	// Enable counter
	SET_BIT(TIM2->CR1,GPTIM_CEN);
	
}

// Function to call another function after number of ticks periodic
void TIM2_setPeriodicInterval(u16 Ticks, void (*Callback)(void))
{
	// Validate input parameters
	ASSERT(Callback != NULL);

	// Save callBack
	TIM2_UnderflowCallback=Callback;

	// Set Mode to Single
	Timer2IntervalModeFlag=0;

	// stop timer 
	CLR_BIT(TIM2->CR1,GPTIM_CEN);

	// Re-Initialize the the counter 
	TIM2->ARR=Ticks;
	SET_BIT(TIM2->EGR,GPTIM_UG);
		
	// Enable Update Interrupt 
	SET_BIT(TIM2->DIER,GPTIM_UIE);

	// Enable counter
	SET_BIT(TIM2->CR1,GPTIM_CEN);
	
}

// Function to reload timer value
void TIM2_reloadTimerValue(u16 TimerValue)
{
	TIM2->CNT = TimerValue;
}
u16  TIM2_getTimerValue(void)
{
	return TIM2->CNT;
}

// Function to reload capture compare value
void TIM2_reloadCaptureCompareValue(ChannelSelect_type ChannelId,u16 CaptureCompareValue)
{
	// Validate input parameters
	ASSERT(ChannelId >= 0 && ChannelId < CHANNEL_ERR);

	// Temp variable to hold the CCR of the nedded channel
	u16 TempValue = 0; 

	// Select a channel to return its value
	switch (ChannelId)
	{
	case CHANNEL1:
		TIM2->CCR1 = CaptureCompareValue;
		break;
	case CHANNEL2:
		TIM2->CCR2 = CaptureCompareValue;
		break;
	case CHANNEL3:
		TIM2->CCR3 = CaptureCompareValue;
		break;
	case CHANNEL4:
		TIM2->CCR4 = CaptureCompareValue;
		break;
	default:
		// Do nothing
		break;
	}
}

// Function to get capture compare value
u16  TIM2_getCaptureCompareValue(ChannelSelect_type ChannelId)
{
	// Validate input parameters
	ASSERT(ChannelId >= 0 && ChannelId < CHANNEL_ERR);

	// Temp variable to hold the CCR of the nedded channel
	u16 TempValue = 0; 

	// Select a channel to return its value
	switch (ChannelId)
	{
	case CHANNEL1:
		TempValue = TIM2->CCR1;
		break;
	case CHANNEL2:
		TempValue = TIM2->CCR2;
		break;
	case CHANNEL3:
		TempValue = TIM2->CCR3;
		break;
	case CHANNEL4:
		TempValue = TIM2->CCR4;
		break;
	default:
		// Do nothing
		break;
	}
	return TempValue;
}

// Function to restart timer
void TIM2_restartTimer(void)
{
	// Enable counter
	SET_BIT(TIM2->CR1, 0);
}

// Function to stop timer
void TIM2_stopTimer(void)
{
	// Disable counter
	CLR_BIT(TIM2->CR1, 0);
}

// Function to enable capture compare interrupt
void TIM2_enableCaptureCompareInterrupt(ChannelSelect_type ChannelId)
{
	// Validate input parameters
	ASSERT(ChannelId >= 0 && ChannelId < CHANNEL_ERR);

	// Select a channel to return its value
	switch (ChannelId)
	{
	case CHANNEL1:
		SET_BIT(TIM2->DIER,1);
		break;
	case CHANNEL2:
		SET_BIT(TIM2->DIER,2);
		break;
	case CHANNEL3:
		SET_BIT(TIM2->DIER,3);
		break;
	case CHANNEL4:
		SET_BIT(TIM2->DIER,4);
		break;
	default:
		// Do nothing
		break;
	}
}

// Function to disable capture compare interrupt
void TIM2_disableCaptureCompareInterrupt(ChannelSelect_type ChannelId)
{
	// Validate input parameters
	ASSERT(ChannelId >= 0 && ChannelId < CHANNEL_ERR);

	// Select a channel to return its value
	switch (ChannelId)
	{
	case CHANNEL1:
		CLR_BIT(TIM2->DIER,1);
		break;
	case CHANNEL2:
		CLR_BIT(TIM2->DIER,2);
		break;
	case CHANNEL3:
		CLR_BIT(TIM2->DIER,3);
		break;
	case CHANNEL4:
		CLR_BIT(TIM2->DIER,4);
		break;
	default:
		// Do nothing
		break;
	}
}

// Function to set capture compare callback
void TIM2_setCaptureCompareCallback(ChannelSelect_type ChannelId,void (*Callback)(void))
{
	// Validate input parameters
	ASSERT(ChannelId >= 0 && ChannelId < CHANNEL_ERR);
	ASSERT(Callback != NULL);

	// Select a channel to return its value
	switch (ChannelId)
	{
	case CHANNEL1:
		TIM2_CH1_CaptureCompareCallback = Callback;
		break;
	case CHANNEL2:
		TIM2_CH2_CaptureCompareCallback = Callback;
		break;
	case CHANNEL3:
		TIM2_CH3_CaptureCompareCallback = Callback;
		break;
	case CHANNEL4:
		TIM2_CH4_CaptureCompareCallback = Callback;
		break;
	default:
		// Do nothing
		break;
	}
}

// Function to set pwm1 parameters
void TIM2_generatePWM1(ChannelSelect_type ChannelId,u32 Frequency,u8 DutyCycle)
{
	// Validate input parameters
	ASSERT(ChannelId >= 0 && ChannelId < CHANNEL_ERR);

	// Disable timer
	CLR_BIT(TIM2->CR1,0);

	// Set pwm parameters
	u16 Temp1 = (4000000/(Timer2Prescaler*Frequency))+1;
	u16 Temp2 = (((Temp1+1)/ 100)*DutyCycle)+1;
	TIM2->CCR1 = Temp2;
	TIM2->ARR = Temp1;

	// Update registers
	SET_BIT(TIM2->EGR,0);

	// Enable Timer
	SET_BIT(TIM2->CR1,0);
}

// Function to set pwm2 parameters
void TIM2_generatePWM2(ChannelSelect_type ChannelId,u32 Frequency,u8 DutyCycle)
{
	// Validate input parameters
	ASSERT(ChannelId >= 0 && ChannelId < CHANNEL_ERR);
	
	// Disable timer
	CLR_BIT(TIM2->CR1,0);

	// Set pwm parameters
	u16 Temp1 = 4000000/(2*Timer2Prescaler*Frequency);
	u16 Temp2 = (Temp1/ 100)*DutyCycle;
	TIM2->ARR = Temp1;
	TIM2->CCR1 = Temp2;

	// Update registers
	SET_BIT(TIM2->EGR,0);

	// Enable Timer
	SET_BIT(TIM2->CR1,0);

}


/*************************** Timer3 ********************************/

// Function to initialize timer3
void TIM3_init(TimerMode_type TimerMode, 
			   CountMode_type CountMode, 
			   u16 TimerPrescaler)
{
	// Validate input parameters
	ASSERT(TimerMode >= 0 && TimerMode < TIMER_MODE_ERR);
	ASSERT(CountMode >= 0 && CountMode < 7 );
	ASSERT(TimerPrescaler >= 1 && TimerPrescaler < 65535);

	// Configure auto reload
	#if TIMER3_ARR_BUFFERED == ARR_BUFFERD_ENABLED
		SET_BIT(TIM3->CR1,7);
	#elif TIMER3_ARR_BUFFERED == ARR_BUFFERD_DISABLED
		CLR_BIT(TIM3->CR1,7);
	#endif

	// Configure update event
	#if TIMER3_UPDATE_EVENT == UPDATE_EVENT_ENABLED
		CLR_BIT(TIM3->CR1,1);
		// Select update event source
		#if TIMER3_UPDATE_EVENT_SOURCE == UPDATE_EVENT_SOURCE_OVF
			SET_BIT(TIM3->CR1,2);
		#elif TIMER3_UPDATE_EVENT_SOURCE == UPDATE_EVENT_SOURCE_OVF_UG_SLV
			CLR_BIT(TIM3->CR1,2);
		#endif
		// disable update interrupt
		CLR_BIT(TIM3->DIER,0);
	#elif TIMER3_UPDATE_EVENT == UPDATE_EVENT_DISABLED
		SET_BIT(TIM3->CR1,1);
	#endif

	// Select clock
	#if  TIMER3_CLOCK_SELECTION == CLOCK_INTERNAL_RCC
		// Disable slave mode
		TIM3->SMCR &= ~(0b111 << 0);
	#elif  TIMER3_CLOCK_SELECTION == CLOCK_
	#endif

	// Set timer mode
	switch (TimerMode)
	{
		case ONE_PULSE_MODE:
			SET_BIT(TIM3->CR1,3);
			break;
		default:
			// Do nothing
			break;
	}

	// Set input filters parameters in case of input modes 
	if (TimerMode >= INPUT_CAPTURE_MODE && TimerMode <= ONE_PULSE_MODE)
	{
		// Configure filters clock
		TIM3->CR1 |= (TIMER3_FILTER_DTS << 8);

		// Configure filters sampling rate
		// ETR
		TIM3->SMCR &= ~(0b1111 << 8);
		TIM3->SMCR |= (TIMER3_ETR_FILTER << 8);
		// TI1
		TIM3->CCMR1 &= ~(0b1111 << 4);
		TIM3->CCMR1 |= (TIMER3_TI1_FILTER << 4);
		// TI2
		TIM3->CCMR1 &= ~(0b1111 << 12);
		TIM3->CCMR1 |= (TIMER3_TI2_FILTER << 12);
		// TI3
		TIM3->CCMR2 &= ~(0b1111 << 4);
		TIM3->CCMR2 |= (TIMER3_TI3_FILTER << 4);
		// TI4
		TIM3->CCMR2 &= ~(0b1111 << 12);
		TIM3->CCMR2 |= (TIMER3_TI4_FILTER << 12);

		// Configure capture compare prescalers
		// ETR
		TIM3->SMCR &= ~(0b11 << 12);
		TIM3->SMCR |= (TIMER3_ETR_PRESCALER << 12);
		// TI1
		TIM3->CCMR1 &= ~(0b11 << 2);
		TIM3->CCMR1 |= (TIMER3_TI1_PRESCALER << 2);
		// TI2
		TIM3->CCMR1 &= ~(0b11 << 12);
		TIM3->CCMR1 |= (TIMER3_TI2_PRESCALER << 10);
		// TI3
		TIM3->CCMR2 &= ~(0b11 << 2);
		TIM3->CCMR2 |= (TIMER3_TI3_PRESCALER << 2);
		// TI4
		TIM3->CCMR2 &= ~(0b11 << 12);
		TIM3->CCMR2 |= (TIMER3_TI4_PRESCALER << 10);
	}

	// Set count mode
	TIM3->CR1 |= (CountMode << 4);

	// Set prescaler
	TIM3->PSC = TimerPrescaler;
	Timer3Prescaler = TimerPrescaler;

	// Update timer registers
	if (CountMode == COUNT_UP || CountMode == COUNT_UP_DOWN)
	{
		TIM3->ARR = 65535;
	}
	else
	{
		TIM3->ARR = 0;
	}
	TIM3->SR = 0;
	SET_BIT(TIM3->EGR,0);

	// Initialize channels as input by default to avoid setting flags
	TIM3->CCMR1 |= (1 << 0);
	TIM3->CCMR1 |= (1 << 8);
	TIM3->CCMR2 |= (1 << 0);
	TIM3->CCMR2 |= (1 << 8);

	// Enable timer
	SET_BIT(TIM3->CR1, 0);
}

// Function to initialize channels of timer3
void TIM3_initChannel(ChannelSelect_type ChannelId, 
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
			TIM3->CCMR1 &= ~(0b11 << 0);
			TIM3->CCMR1 |= (ChannelMode << 4);

			// Set preload enable disable
			if (PreloadEnableDisable == PRELOAD_ENABLE)
			{
				// Enable preload
				SET_BIT(TIM3->CCMR1, 3);
			}
			else if (PreloadEnableDisable == PRELOAD_DISABLE)
			{
				// Disable preload
				CLR_BIT(TIM3->CCMR1, 3);
			}

			// Set fast enable disable
			if (FastEnableDisable == FAST_ENABLE)
			{
				// Enable fast
				SET_BIT(TIM3->CCMR1, 2);
			}
			else if (FastEnableDisable == FAST_DISABLE)
			{
				// Disable fast
				SET_BIT(TIM3->CCMR1, 2);
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
			TIM3->CCMR1 &= ~(0b11 << 0);
			TIM3->CCMR1 |= (ChannelMode << 0);
		}

		// Set capture compare polarity
		if (CaptureComparePolarity == CAPTURE_COMPARE_POL_0)
		{
			// Enable capture compare
			CLR_BIT(TIM3->CCER, 1);
		}
		else if (CaptureComparePolarity == CAPTURE_COMPARE_POL_1)
		{
			// Enable capture compare
			SET_BIT(TIM3->CCER, 1);
		}

		// Enable capture compare
		SET_BIT(TIM3->CCER, 0);
		break;
	case CHANNEL2:

		// Set channel mode
		if (ChannelMode >= 0 && ChannelMode < 8 )
		{
			// Select output mode
			TIM3->CCMR1 &= ~(0b11 << 8);
			TIM3->CCMR1 |= (ChannelMode << 12);

			// Set preload enable disable
			if (PreloadEnableDisable == PRELOAD_ENABLE)
			{
				// Enable preload
				SET_BIT(TIM3->CCMR1, 11);
			}
			else if (PreloadEnableDisable == PRELOAD_DISABLE)
			{
				// Disable preload
				CLR_BIT(TIM3->CCMR1, 11);
			}

			// Set fast enable disable
			if (FastEnableDisable == FAST_ENABLE)
			{
				// Enable fast
				SET_BIT(TIM3->CCMR1, 10);
			}
			else if (FastEnableDisable == FAST_DISABLE)
			{
				// Disable fast
				SET_BIT(TIM3->CCMR1, 10);
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
			TIM3->CCMR1 &= ~(0b11 << 8);
			TIM3->CCMR1 |= (ChannelMode << 8);
		}

		// Set capture compare polarity
		if (CaptureComparePolarity == CAPTURE_COMPARE_POL_0)
		{
			// Enable capture compare
			CLR_BIT(TIM3->CCER, 5);
		}
		else if (CaptureComparePolarity == CAPTURE_COMPARE_POL_1)
		{
			// Enable capture compare
			SET_BIT(TIM3->CCER, 5);
		}

		// Enable capture compare
		SET_BIT(TIM3->CCER, 4);
		break;
	case CHANNEL3:

		// Set channel mode
		if (ChannelMode >= 0 && ChannelMode < 8 )
		{
			// Select output mode
			TIM3->CCMR2 &= ~(0b11 << 0);
			TIM3->CCMR2 |= (ChannelMode << 4);

			// Set preload enable disable
			if (PreloadEnableDisable == PRELOAD_ENABLE)
			{
				// Enable preload
				SET_BIT(TIM3->CCMR2, 3);
			}
			else if (PreloadEnableDisable == PRELOAD_DISABLE)
			{
				// Disable preload
				CLR_BIT(TIM3->CCMR2, 3);
			}

			// Set fast enable disable
			if (FastEnableDisable == FAST_ENABLE)
			{
				// Enable fast
				SET_BIT(TIM3->CCMR2, 2);
			}
			else if (FastEnableDisable == FAST_DISABLE)
			{
				// Disable fast
				SET_BIT(TIM3->CCMR2, 2);
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
			TIM3->CCMR2 &= ~(0b11 << 0);
			TIM3->CCMR2 |= (ChannelMode << 0);
		}

		// Set capture compare polarity
		if (CaptureComparePolarity == CAPTURE_COMPARE_POL_0)
		{
			// Enable capture compare
			CLR_BIT(TIM3->CCER, 9);
		}
		else if (CaptureComparePolarity == CAPTURE_COMPARE_POL_1)
		{
			// Enable capture compare
			SET_BIT(TIM3->CCER, 9);
		}

		// Enable capture compare
		SET_BIT(TIM3->CCER, 8);
		break;
	case CHANNEL4:

		// Set channel mode
		if (ChannelMode >= 0 && ChannelMode < 8 )
		{
			// Select output mode
			TIM3->CCMR2 &= ~(0b11 << 8);
			TIM3->CCMR2 |= (ChannelMode << 12);

			// Set preload enable disable
			if (PreloadEnableDisable == PRELOAD_ENABLE)
			{
				// Enable preload
				SET_BIT(TIM3->CCMR1, 11);
			}
			else if (PreloadEnableDisable == PRELOAD_DISABLE)
			{
				// Disable preload
				CLR_BIT(TIM3->CCMR1, 11);
			}

			// Set fast enable disable
			if (FastEnableDisable == FAST_ENABLE)
			{
				// Enable fast
				SET_BIT(TIM3->CCMR1, 10);
			}
			else if (FastEnableDisable == FAST_DISABLE)
			{
				// Disable fast
				SET_BIT(TIM3->CCMR1, 10);
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
			TIM3->CCMR2 &= ~(0b11 << 8);
			TIM3->CCMR2 |= (ChannelMode << 8);
		}

		// Set capture compare polarity
		if (CaptureComparePolarity == CAPTURE_COMPARE_POL_0)
		{
			// Enable capture compare
			CLR_BIT(TIM3->CCER, 13);
		}
		else if (CaptureComparePolarity == CAPTURE_COMPARE_POL_1)
		{
			// Enable capture compare
			SET_BIT(TIM3->CCER, 13);
		}

		// Enable capture compare
		SET_BIT(TIM3->CCER, 12);
		break;
	default:
		// Do nothing
		break;
	}
}

// Function to change capture compare edge
void TIM3_changeCaptureComparePolarity(ChannelSelect_type ChannelId, 
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
			CLR_BIT(TIM3->CCER, 1);
		}
		else if (CaptureComparePolarity == CAPTURE_COMPARE_POL_1)
		{
			// Enable capture compare
			SET_BIT(TIM3->CCER, 1);
		}
		break;
	case CHANNEL2:
		
		// Set capture compare polarity
		if (CaptureComparePolarity == CAPTURE_COMPARE_POL_0)
		{
			// Enable capture compare
			CLR_BIT(TIM3->CCER, 5);
		}
		else if (CaptureComparePolarity == CAPTURE_COMPARE_POL_1)
		{
			// Enable capture compare
			SET_BIT(TIM3->CCER, 5);
		}
		break;
	case CHANNEL3:

		// Set capture compare polarity
		if (CaptureComparePolarity == CAPTURE_COMPARE_POL_0)
		{
			// Enable capture compare
			CLR_BIT(TIM3->CCER, 9);
		}
		else if (CaptureComparePolarity == CAPTURE_COMPARE_POL_1)
		{
			// Enable capture compare
			SET_BIT(TIM3->CCER, 9);
		}
		break;
	case CHANNEL4:
		
		// Set capture compare polarity
		if (CaptureComparePolarity == CAPTURE_COMPARE_POL_0)
		{
			// Enable capture compare
			CLR_BIT(TIM3->CCER, 13);
		}
		else if (CaptureComparePolarity == CAPTURE_COMPARE_POL_1)
		{
			// Enable capture compare
			SET_BIT(TIM3->CCER, 13);
		}
		break;
	default:
		// Do nothing
		break;
	}
}

// Function to make a delay with specific ticks
void TIM3_setBusyWait(u16 Ticks)
{
	// Disable timer
	CLR_BIT(TIM3->CR1,0);

	// Upload timer
	TIM3->ARR = Ticks;
	SET_BIT(TIM3->EGR,0);

	// Enable Timer
	SET_BIT(TIM3->CR1,0);
	while(GET_BIT(TIM3->SR,0)==0);

	// Clear Uderflow Flag
	CLR_BIT(TIM3->SR,0);

	// Disable timer
	CLR_BIT(TIM3->CR1,0);
}

// Function to call another function after number of ticks one time
void TIM3_setSingleInterval(u16 Ticks, void (*Callback)(void))
{
	// Validate input parameters
	ASSERT(Callback != NULL);

	// Save callBack
	TIM3_UnderflowCallback=Callback;

	// Set Mode to Single
	Timer3IntervalModeFlag=1;

	// stop timer 
	CLR_BIT(TIM3->CR1,GPTIM_CEN);

	// Re-Initialize the the counter 
	TIM3->ARR=Ticks;
	SET_BIT(TIM3->EGR,GPTIM_UG);
		
	// Enable Update Interrupt 
	SET_BIT(TIM3->DIER,GPTIM_UIE);

	// Enable counter
	SET_BIT(TIM3->CR1,GPTIM_CEN);
	
}

// Function to call another function after number of ticks periodic
void TIM3_setPeriodicInterval(u16 Ticks, void (*Callback)(void))
{
	// Validate input parameters
	ASSERT(Callback != NULL);

	// Save callBack
	TIM3_UnderflowCallback=Callback;

	// Set Mode to Single
	Timer3IntervalModeFlag=0;

	// stop timer 
	CLR_BIT(TIM3->CR1,GPTIM_CEN);

	// Re-Initialize the the counter 
	TIM3->ARR=Ticks;
	SET_BIT(TIM3->EGR,GPTIM_UG);
		
	// Enable Update Interrupt 
	SET_BIT(TIM3->DIER,GPTIM_UIE);

	// Enable counter
	SET_BIT(TIM3->CR1,GPTIM_CEN);
	
}

// Function to reload timer value
void TIM3_reloadTimerValue(u16 TimerValue)
{
	TIM3->CNT = TimerValue;
}
u16  TIM3_getTimerValue(void)
{
	return TIM3->CNT;
}

// Function to reload capture compare value
void TIM3_reloadCaptureCompareValue(ChannelSelect_type ChannelId,u16 CaptureCompareValue)
{
	// Validate input parameters
	ASSERT(ChannelId >= 0 && ChannelId < CHANNEL_ERR);

	// Temp variable to hold the CCR of the nedded channel
	u16 TempValue = 0; 

	// Select a channel to return its value
	switch (ChannelId)
	{
	case CHANNEL1:
		TIM3->CCR1 = CaptureCompareValue;
		break;
	case CHANNEL2:
		TIM3->CCR2 = CaptureCompareValue;
		break;
	case CHANNEL3:
		TIM3->CCR3 = CaptureCompareValue;
		break;
	case CHANNEL4:
		TIM3->CCR4 = CaptureCompareValue;
		break;
	default:
		// Do nothing
		break;
	}
}

// Function to get capture compare value
u16  TIM3_getCaptureCompareValue(ChannelSelect_type ChannelId)
{
	// Validate input parameters
	ASSERT(ChannelId >= 0 && ChannelId < CHANNEL_ERR);

	// Temp variable to hold the CCR of the nedded channel
	u16 TempValue = 0; 

	// Select a channel to return its value
	switch (ChannelId)
	{
	case CHANNEL1:
		TempValue = TIM3->CCR1;
		break;
	case CHANNEL2:
		TempValue = TIM3->CCR2;
		break;
	case CHANNEL3:
		TempValue = TIM3->CCR3;
		break;
	case CHANNEL4:
		TempValue = TIM3->CCR4;
		break;
	default:
		// Do nothing
		break;
	}
	return TempValue;
}

// Function to restart timer
void TIM3_restartTimer(void)
{
	// Enable counter
	SET_BIT(TIM3->CR1, 0);
}

// Function to stop timer
void TIM3_stopTimer(void)
{
	// Disable counter
	CLR_BIT(TIM3->CR1, 0);
}

// Function to enable capture compare interrupt
void TIM3_enableCaptureCompareInterrupt(ChannelSelect_type ChannelId)
{
	// Validate input parameters
	ASSERT(ChannelId >= 0 && ChannelId < CHANNEL_ERR);

	// Select a channel to return its value
	switch (ChannelId)
	{
	case CHANNEL1:
		SET_BIT(TIM3->DIER,1);
		break;
	case CHANNEL2:
		SET_BIT(TIM3->DIER,2);
		break;
	case CHANNEL3:
		SET_BIT(TIM3->DIER,3);
		break;
	case CHANNEL4:
		SET_BIT(TIM3->DIER,4);
		break;
	default:
		// Do nothing
		break;
	}
}

// Function to disable capture compare interrupt
void TIM3_disableCaptureCompareInterrupt(ChannelSelect_type ChannelId)
{
	// Validate input parameters
	ASSERT(ChannelId >= 0 && ChannelId < CHANNEL_ERR);

	// Select a channel to return its value
	switch (ChannelId)
	{
	case CHANNEL1:
		CLR_BIT(TIM3->DIER,1);
		break;
	case CHANNEL2:
		CLR_BIT(TIM3->DIER,2);
		break;
	case CHANNEL3:
		CLR_BIT(TIM3->DIER,3);
		break;
	case CHANNEL4:
		CLR_BIT(TIM3->DIER,4);
		break;
	default:
		// Do nothing
		break;
	}
}

// Function to set capture compare callback
void TIM3_setCaptureCompareCallback(ChannelSelect_type ChannelId,void (*Callback)(void))
{
	// Validate input parameters
	ASSERT(ChannelId >= 0 && ChannelId < CHANNEL_ERR);
	ASSERT(Callback != NULL);

	// Select a channel to return its value
	switch (ChannelId)
	{
	case CHANNEL1:
		TIM3_CH1_CaptureCompareCallback = Callback;
		break;
	case CHANNEL2:
		TIM3_CH2_CaptureCompareCallback = Callback;
		break;
	case CHANNEL3:
		TIM3_CH3_CaptureCompareCallback = Callback;
		break;
	case CHANNEL4:
		TIM3_CH4_CaptureCompareCallback = Callback;
		break;
	default:
		// Do nothing
		break;
	}
}

// Function to set pwm1 parameters
void TIM3_generatePWM1(ChannelSelect_type ChannelId,u32 Frequency,u8 DutyCycle)
{
	// Validate input parameters
	ASSERT(ChannelId >= 0 && ChannelId < CHANNEL_ERR);

	// Disable timer
	CLR_BIT(TIM3->CR1,0);

	// Set pwm parameters
	u16 Temp1 = (4000000/(Timer3Prescaler*Frequency))+1;
	u16 Temp2 = (((Temp1+1)/ 100)*DutyCycle)+1;
	TIM3->CCR1 = Temp2;
	TIM3->ARR = Temp1;

	// Update registers
	SET_BIT(TIM3->EGR,0);

	// Enable Timer
	SET_BIT(TIM3->CR1,0);
}

// Function to set pwm2 parameters
void TIM3_generatePWM2(ChannelSelect_type ChannelId,u32 Frequency,u8 DutyCycle)
{
	// Validate input parameters
	ASSERT(ChannelId >= 0 && ChannelId < CHANNEL_ERR);
	
	// Disable timer
	CLR_BIT(TIM3->CR1,0);

	// Set pwm parameters
	u16 Temp1 = 4000000/(2*Timer3Prescaler*Frequency);
	u16 Temp2 = (Temp1/ 100)*DutyCycle;
	TIM3->ARR = Temp1;
	TIM3->CCR1 = Temp2;

	// Update registers
	SET_BIT(TIM3->EGR,0);

	// Enable Timer
	SET_BIT(TIM3->CR1,0);

}


/*************************** Timer4 ********************************/

// Function to initialize timer2
void TIM4_init(TimerMode_type TimerMode, 
			   CountMode_type CountMode, 
			   u16 TimerPrescaler)
{
	// Validate input parameters
	ASSERT(TimerMode >= 0 && TimerMode < TIMER_MODE_ERR);
	ASSERT(CountMode >= 0 && CountMode < 7 );
	ASSERT(TimerPrescaler >= 1 && TimerPrescaler < 65535);

	// Configure auto reload
	#if TIMER4_ARR_BUFFERED == ARR_BUFFERD_ENABLED
		SET_BIT(TIM4->CR1,7);
	#elif TIMER4_ARR_BUFFERED == ARR_BUFFERD_DISABLED
		CLR_BIT(TIM4->CR1,7);
	#endif

	// Configure update event
	#if TIMER4_UPDATE_EVENT == UPDATE_EVENT_ENABLED
		CLR_BIT(TIM4->CR1,1);
		// Select update event source
		#if TIMER4_UPDATE_EVENT_SOURCE == UPDATE_EVENT_SOURCE_OVF
			SET_BIT(TIM4->CR1,2);
		#elif TIMER4_UPDATE_EVENT_SOURCE == UPDATE_EVENT_SOURCE_OVF_UG_SLV
			CLR_BIT(TIM4->CR1,2);
		#endif
		// disable update interrupt
		CLR_BIT(TIM4->DIER,0);
	#elif TIMER4_UPDATE_EVENT == UPDATE_EVENT_DISABLED
		SET_BIT(TIM4->CR1,1);
	#endif

	// Select clock
	#if  TIMER4_CLOCK_SELECTION == CLOCK_INTERNAL_RCC
		// Disable slave mode
		TIM4->SMCR &= ~(0b111 << 0);
	#elif  TIMER4_CLOCK_SELECTION == CLOCK_
	#endif

	// Set timer mode
	switch (TimerMode)
	{
		case ONE_PULSE_MODE:
			SET_BIT(TIM4->CR1,3);
			break;
		default:
			// Do nothing
			break;
	}

	// Set input filters parameters in case of input modes 
	if (TimerMode >= INPUT_CAPTURE_MODE && TimerMode <= ONE_PULSE_MODE)
	{
		// Configure filters clock
		TIM4->CR1 |= (TIMER4_FILTER_DTS << 8);

		// Configure filters sampling rate
		// ETR
		TIM4->SMCR &= ~(0b1111 << 8);
		TIM4->SMCR |= (TIMER4_ETR_FILTER << 8);
		// TI1
		TIM4->CCMR1 &= ~(0b1111 << 4);
		TIM4->CCMR1 |= (TIMER4_TI1_FILTER << 4);
		// TI2
		TIM4->CCMR1 &= ~(0b1111 << 12);
		TIM4->CCMR1 |= (TIMER4_TI2_FILTER << 12);
		// TI3
		TIM4->CCMR2 &= ~(0b1111 << 4);
		TIM4->CCMR2 |= (TIMER4_TI3_FILTER << 4);
		// TI4
		TIM4->CCMR2 &= ~(0b1111 << 12);
		TIM4->CCMR2 |= (TIMER4_TI4_FILTER << 12);

		// Configure capture compare prescalers
		// ETR
		TIM4->SMCR &= ~(0b11 << 12);
		TIM4->SMCR |= (TIMER4_ETR_PRESCALER << 12);
		// TI1
		TIM4->CCMR1 &= ~(0b11 << 2);
		TIM4->CCMR1 |= (TIMER4_TI1_PRESCALER << 2);
		// TI2
		TIM4->CCMR1 &= ~(0b11 << 12);
		TIM4->CCMR1 |= (TIMER4_TI2_PRESCALER << 10);
		// TI3
		TIM4->CCMR2 &= ~(0b11 << 2);
		TIM4->CCMR2 |= (TIMER4_TI3_PRESCALER << 2);
		// TI4
		TIM4->CCMR2 &= ~(0b11 << 12);
		TIM4->CCMR2 |= (TIMER4_TI4_PRESCALER << 10);
	}

	// Set count mode
	TIM4->CR1 |= (CountMode << 4);

	// Set prescaler
	TIM4->PSC = TimerPrescaler;
	Timer4Prescaler = TimerPrescaler;

	// Update timer registers
	if (CountMode == COUNT_UP || CountMode == COUNT_UP_DOWN)
	{
		TIM4->ARR = 65535;
	}
	else
	{
		TIM4->ARR = 0;
	}
	TIM4->SR = 0;
	SET_BIT(TIM4->EGR,0);

	// Initialize channels as input by default to avoid setting flags
	TIM4->CCMR1 |= (1 << 0);
	TIM4->CCMR1 |= (1 << 8);
	TIM4->CCMR2 |= (1 << 0);
	TIM4->CCMR2 |= (1 << 8);

	// Enable timer
	SET_BIT(TIM4->CR1, 0);
}

// Function to initialize channels of timer2
void TIM4_initChannel(ChannelSelect_type ChannelId, 
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
			TIM4->CCMR1 &= ~(0b11 << 0);
			TIM4->CCMR1 |= (ChannelMode << 4);

			// Set preload enable disable
			if (PreloadEnableDisable == PRELOAD_ENABLE)
			{
				// Enable preload
				SET_BIT(TIM4->CCMR1, 3);
			}
			else if (PreloadEnableDisable == PRELOAD_DISABLE)
			{
				// Disable preload
				CLR_BIT(TIM4->CCMR1, 3);
			}

			// Set fast enable disable
			if (FastEnableDisable == FAST_ENABLE)
			{
				// Enable fast
				SET_BIT(TIM4->CCMR1, 2);
			}
			else if (FastEnableDisable == FAST_DISABLE)
			{
				// Disable fast
				SET_BIT(TIM4->CCMR1, 2);
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
			TIM4->CCMR1 &= ~(0b11 << 0);
			TIM4->CCMR1 |= (ChannelMode << 0);
		}

		// Set capture compare polarity
		if (CaptureComparePolarity == CAPTURE_COMPARE_POL_0)
		{
			// Enable capture compare
			CLR_BIT(TIM4->CCER, 1);
		}
		else if (CaptureComparePolarity == CAPTURE_COMPARE_POL_1)
		{
			// Enable capture compare
			SET_BIT(TIM4->CCER, 1);
		}

		// Enable capture compare
		SET_BIT(TIM4->CCER, 0);
		break;
	case CHANNEL2:

		// Set channel mode
		if (ChannelMode >= 0 && ChannelMode < 8 )
		{
			// Select output mode
			TIM4->CCMR1 &= ~(0b11 << 8);
			TIM4->CCMR1 |= (ChannelMode << 12);

			// Set preload enable disable
			if (PreloadEnableDisable == PRELOAD_ENABLE)
			{
				// Enable preload
				SET_BIT(TIM4->CCMR1, 11);
			}
			else if (PreloadEnableDisable == PRELOAD_DISABLE)
			{
				// Disable preload
				CLR_BIT(TIM4->CCMR1, 11);
			}

			// Set fast enable disable
			if (FastEnableDisable == FAST_ENABLE)
			{
				// Enable fast
				SET_BIT(TIM4->CCMR1, 10);
			}
			else if (FastEnableDisable == FAST_DISABLE)
			{
				// Disable fast
				SET_BIT(TIM4->CCMR1, 10);
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
			TIM4->CCMR1 &= ~(0b11 << 8);
			TIM4->CCMR1 |= (ChannelMode << 8);
		}

		// Set capture compare polarity
		if (CaptureComparePolarity == CAPTURE_COMPARE_POL_0)
		{
			// Enable capture compare
			CLR_BIT(TIM4->CCER, 5);
		}
		else if (CaptureComparePolarity == CAPTURE_COMPARE_POL_1)
		{
			// Enable capture compare
			SET_BIT(TIM4->CCER, 5);
		}

		// Enable capture compare
		SET_BIT(TIM4->CCER, 4);
		break;
	case CHANNEL3:

		// Set channel mode
		if (ChannelMode >= 0 && ChannelMode < 8 )
		{
			// Select output mode
			TIM4->CCMR2 &= ~(0b11 << 0);
			TIM4->CCMR2 |= (ChannelMode << 4);

			// Set preload enable disable
			if (PreloadEnableDisable == PRELOAD_ENABLE)
			{
				// Enable preload
				SET_BIT(TIM4->CCMR2, 3);
			}
			else if (PreloadEnableDisable == PRELOAD_DISABLE)
			{
				// Disable preload
				CLR_BIT(TIM4->CCMR2, 3);
			}

			// Set fast enable disable
			if (FastEnableDisable == FAST_ENABLE)
			{
				// Enable fast
				SET_BIT(TIM4->CCMR2, 2);
			}
			else if (FastEnableDisable == FAST_DISABLE)
			{
				// Disable fast
				SET_BIT(TIM4->CCMR2, 2);
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
			TIM4->CCMR2 &= ~(0b11 << 0);
			TIM4->CCMR2 |= (ChannelMode << 0);
		}

		// Set capture compare polarity
		if (CaptureComparePolarity == CAPTURE_COMPARE_POL_0)
		{
			// Enable capture compare
			CLR_BIT(TIM4->CCER, 9);
		}
		else if (CaptureComparePolarity == CAPTURE_COMPARE_POL_1)
		{
			// Enable capture compare
			SET_BIT(TIM4->CCER, 9);
		}

		// Enable capture compare
		SET_BIT(TIM4->CCER, 8);
		break;
	case CHANNEL4:

		// Set channel mode
		if (ChannelMode >= 0 && ChannelMode < 8 )
		{
			// Select output mode
			TIM4->CCMR2 &= ~(0b11 << 8);
			TIM4->CCMR2 |= (ChannelMode << 12);

			// Set preload enable disable
			if (PreloadEnableDisable == PRELOAD_ENABLE)
			{
				// Enable preload
				SET_BIT(TIM4->CCMR1, 11);
			}
			else if (PreloadEnableDisable == PRELOAD_DISABLE)
			{
				// Disable preload
				CLR_BIT(TIM4->CCMR1, 11);
			}

			// Set fast enable disable
			if (FastEnableDisable == FAST_ENABLE)
			{
				// Enable fast
				SET_BIT(TIM4->CCMR1, 10);
			}
			else if (FastEnableDisable == FAST_DISABLE)
			{
				// Disable fast
				SET_BIT(TIM4->CCMR1, 10);
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
			TIM4->CCMR2 &= ~(0b11 << 8);
			TIM4->CCMR2 |= (ChannelMode << 8);
		}

		// Set capture compare polarity
		if (CaptureComparePolarity == CAPTURE_COMPARE_POL_0)
		{
			// Enable capture compare
			CLR_BIT(TIM4->CCER, 13);
		}
		else if (CaptureComparePolarity == CAPTURE_COMPARE_POL_1)
		{
			// Enable capture compare
			SET_BIT(TIM4->CCER, 13);
		}

		// Enable capture compare
		SET_BIT(TIM4->CCER, 12);
		break;
	default:
		// Do nothing
		break;
	}
}

// Function to change capture compare edge
void TIM4_changeCaptureComparePolarity(ChannelSelect_type ChannelId, 
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
			CLR_BIT(TIM4->CCER, 1);
		}
		else if (CaptureComparePolarity == CAPTURE_COMPARE_POL_1)
		{
			// Enable capture compare
			SET_BIT(TIM4->CCER, 1);
		}
		break;
	case CHANNEL2:
		
		// Set capture compare polarity
		if (CaptureComparePolarity == CAPTURE_COMPARE_POL_0)
		{
			// Enable capture compare
			CLR_BIT(TIM4->CCER, 5);
		}
		else if (CaptureComparePolarity == CAPTURE_COMPARE_POL_1)
		{
			// Enable capture compare
			SET_BIT(TIM4->CCER, 5);
		}
		break;
	case CHANNEL3:

		// Set capture compare polarity
		if (CaptureComparePolarity == CAPTURE_COMPARE_POL_0)
		{
			// Enable capture compare
			CLR_BIT(TIM4->CCER, 9);
		}
		else if (CaptureComparePolarity == CAPTURE_COMPARE_POL_1)
		{
			// Enable capture compare
			SET_BIT(TIM4->CCER, 9);
		}
		break;
	case CHANNEL4:
		
		// Set capture compare polarity
		if (CaptureComparePolarity == CAPTURE_COMPARE_POL_0)
		{
			// Enable capture compare
			CLR_BIT(TIM4->CCER, 13);
		}
		else if (CaptureComparePolarity == CAPTURE_COMPARE_POL_1)
		{
			// Enable capture compare
			SET_BIT(TIM4->CCER, 13);
		}
		break;
	default:
		// Do nothing
		break;
	}
}

// Function to make a delay with specific ticks
void TIM4_setBusyWait(u16 Ticks)
{
	// Disable timer
	CLR_BIT(TIM4->CR1,0);

	// Upload timer
	TIM4->ARR = Ticks;
	SET_BIT(TIM4->EGR,0);

	// Enable Timer
	SET_BIT(TIM4->CR1,0);
	while(GET_BIT(TIM4->SR,0)==0);

	// Clear Uderflow Flag
	CLR_BIT(TIM4->SR,0);

	// Disable timer
	CLR_BIT(TIM4->CR1,0);
}

// Function to call another function after number of ticks one time
void TIM4_setSingleInterval(u16 Ticks, void (*Callback)(void))
{
	// Validate input parameters
	ASSERT(Callback != NULL);

	// Save callBack
	TIM4_UnderflowCallback=Callback;

	// Set Mode to Single
	Timer4IntervalModeFlag=1;

	// stop timer 
	CLR_BIT(TIM4->CR1,GPTIM_CEN);

	// Re-Initialize the the counter 
	TIM4->ARR=Ticks;
	SET_BIT(TIM4->EGR,GPTIM_UG);
		
	// Enable Update Interrupt 
	SET_BIT(TIM4->DIER,GPTIM_UIE);

	// Enable counter
	SET_BIT(TIM4->CR1,GPTIM_CEN);
	
}

// Function to call another function after number of ticks periodic
void TIM4_setPeriodicInterval(u16 Ticks, void (*Callback)(void))
{
	// Validate input parameters
	ASSERT(Callback != NULL);

	// Save callBack
	TIM4_UnderflowCallback=Callback;

	// Set Mode to Single
	Timer4IntervalModeFlag=0;

	// stop timer 
	CLR_BIT(TIM4->CR1,GPTIM_CEN);

	// Re-Initialize the the counter 
	TIM4->ARR=Ticks;
	SET_BIT(TIM4->EGR,GPTIM_UG);
		
	// Enable Update Interrupt 
	SET_BIT(TIM4->DIER,GPTIM_UIE);

	// Enable counter
	SET_BIT(TIM4->CR1,GPTIM_CEN);
	
}

// Function to reload timer value
void TIM4_reloadTimerValue(u16 TimerValue)
{
	TIM4->CNT = TimerValue;
}
u16  TIM4_getTimerValue(void)
{
	return TIM4->CNT;
}

// Function to reload capture compare value
void TIM4_reloadCaptureCompareValue(ChannelSelect_type ChannelId,u16 CaptureCompareValue)
{
	// Validate input parameters
	ASSERT(ChannelId >= 0 && ChannelId < CHANNEL_ERR);

	// Temp variable to hold the CCR of the nedded channel
	u16 TempValue = 0; 

	// Select a channel to return its value
	switch (ChannelId)
	{
	case CHANNEL1:
		TIM4->CCR1 = CaptureCompareValue;
		break;
	case CHANNEL2:
		TIM4->CCR2 = CaptureCompareValue;
		break;
	case CHANNEL3:
		TIM4->CCR3 = CaptureCompareValue;
		break;
	case CHANNEL4:
		TIM4->CCR4 = CaptureCompareValue;
		break;
	default:
		// Do nothing
		break;
	}
}

// Function to get capture compare value
u16  TIM4_getCaptureCompareValue(ChannelSelect_type ChannelId)
{
	// Validate input parameters
	ASSERT(ChannelId >= 0 && ChannelId < CHANNEL_ERR);

	// Temp variable to hold the CCR of the nedded channel
	u16 TempValue = 0; 

	// Select a channel to return its value
	switch (ChannelId)
	{
	case CHANNEL1:
		TempValue = TIM4->CCR1;
		break;
	case CHANNEL2:
		TempValue = TIM4->CCR2;
		break;
	case CHANNEL3:
		TempValue = TIM4->CCR3;
		break;
	case CHANNEL4:
		TempValue = TIM4->CCR4;
		break;
	default:
		// Do nothing
		break;
	}
	return TempValue;
}

// Function to restart timer
void TIM4_restartTimer(void)
{
	// Enable counter
	SET_BIT(TIM4->CR1, 0);
}

// Function to stop timer
void TIM4_stopTimer(void)
{
	// Disable counter
	CLR_BIT(TIM4->CR1, 0);
}

// Function to enable capture compare interrupt
void TIM4_enableCaptureCompareInterrupt(ChannelSelect_type ChannelId)
{
	// Validate input parameters
	ASSERT(ChannelId >= 0 && ChannelId < CHANNEL_ERR);

	// Select a channel to return its value
	switch (ChannelId)
	{
	case CHANNEL1:
		SET_BIT(TIM4->DIER,1);
		break;
	case CHANNEL2:
		SET_BIT(TIM4->DIER,2);
		break;
	case CHANNEL3:
		SET_BIT(TIM4->DIER,3);
		break;
	case CHANNEL4:
		SET_BIT(TIM4->DIER,4);
		break;
	default:
		// Do nothing
		break;
	}
}

// Function to disable capture compare interrupt
void TIM4_disableCaptureCompareInterrupt(ChannelSelect_type ChannelId)
{
	// Validate input parameters
	ASSERT(ChannelId >= 0 && ChannelId < CHANNEL_ERR);

	// Select a channel to return its value
	switch (ChannelId)
	{
	case CHANNEL1:
		CLR_BIT(TIM4->DIER,1);
		break;
	case CHANNEL2:
		CLR_BIT(TIM4->DIER,2);
		break;
	case CHANNEL3:
		CLR_BIT(TIM4->DIER,3);
		break;
	case CHANNEL4:
		CLR_BIT(TIM4->DIER,4);
		break;
	default:
		// Do nothing
		break;
	}
}

// Function to set capture compare callback
void TIM4_setCaptureCompareCallback(ChannelSelect_type ChannelId,void (*Callback)(void))
{
	// Validate input parameters
	ASSERT(ChannelId >= 0 && ChannelId < CHANNEL_ERR);
	ASSERT(Callback != NULL);

	// Select a channel to return its value
	switch (ChannelId)
	{
	case CHANNEL1:
		TIM4_CH1_CaptureCompareCallback = Callback;
		break;
	case CHANNEL2:
		TIM4_CH2_CaptureCompareCallback = Callback;
		break;
	case CHANNEL3:
		TIM4_CH3_CaptureCompareCallback = Callback;
		break;
	case CHANNEL4:
		TIM4_CH4_CaptureCompareCallback = Callback;
		break;
	default:
		// Do nothing
		break;
	}
}

// Function to set pwm1 parameters
void TIM4_generatePWM1(ChannelSelect_type ChannelId,u32 Frequency,u8 DutyCycle)
{
	// Validate input parameters
	ASSERT(ChannelId >= 0 && ChannelId < CHANNEL_ERR);

	// Disable timer
	CLR_BIT(TIM4->CR1,0);

	// Set pwm parameters
	u16 Temp1 = (4000000/(Timer4Prescaler*Frequency))+1;
	u16 Temp2 = (((Temp1+1)/ 100)*DutyCycle)+1;
	TIM4->CCR1 = Temp2;
	TIM4->ARR = Temp1;

	// Update registers
	SET_BIT(TIM4->EGR,0);

	// Enable Timer
	SET_BIT(TIM4->CR1,0);
}

// Function to set pwm2 parameters
void TIM4_generatePWM2(ChannelSelect_type ChannelId,u32 Frequency,u8 DutyCycle)
{
	// Validate input parameters
	ASSERT(ChannelId >= 0 && ChannelId < CHANNEL_ERR);
	
	// Disable timer
	CLR_BIT(TIM4->CR1,0);

	// Set pwm parameters
	u16 Temp1 = 4000000/(2*Timer4Prescaler*Frequency);
	u16 Temp2 = (Temp1/ 100)*DutyCycle;
	TIM4->ARR = Temp1;
	TIM4->CCR1 = Temp2;

	// Update registers
	SET_BIT(TIM4->EGR,0);

	// Enable Timer
	SET_BIT(TIM4->CR1,0);

}



/*************************** Timer5 ********************************/

// Function to initialize timer5
void TIM5_init(TimerMode_type TimerMode, 
			   CountMode_type CountMode, 
			   u16 TimerPrescaler)
{
	// Validate input parameters
	ASSERT(TimerMode >= 0 && TimerMode < TIMER_MODE_ERR);
	ASSERT(CountMode >= 0 && CountMode < 7 );
	ASSERT(TimerPrescaler >= 1 && TimerPrescaler < 65535);

	// Configure auto reload
	#if TIMER5_ARR_BUFFERED == ARR_BUFFERD_ENABLED
		SET_BIT(TIM5->CR1,7);
	#elif TIMER5_ARR_BUFFERED == ARR_BUFFERD_DISABLED
		CLR_BIT(TIM5->CR1,7);
	#endif

	// Configure update event
	#if TIMER5_UPDATE_EVENT == UPDATE_EVENT_ENABLED
		CLR_BIT(TIM5->CR1,1);
		// Select update event source
		#if TIMER5_UPDATE_EVENT_SOURCE == UPDATE_EVENT_SOURCE_OVF
			SET_BIT(TIM5->CR1,2);
		#elif TIMER5_UPDATE_EVENT_SOURCE == UPDATE_EVENT_SOURCE_OVF_UG_SLV
			CLR_BIT(TIM5->CR1,2);
		#endif
		// disable update interrupt
		CLR_BIT(TIM5->DIER,0);
	#elif TIMER5_UPDATE_EVENT == UPDATE_EVENT_DISABLED
		SET_BIT(TIM5->CR1,1);
	#endif

	// Select clock
	#if  TIMER5_CLOCK_SELECTION == CLOCK_INTERNAL_RCC
		// Disable slave mode
		TIM5->SMCR &= ~(0b111 << 0);
	#elif  TIMER5_CLOCK_SELECTION == CLOCK_
	#endif

	// Set timer mode
	switch (TimerMode)
	{
		case ONE_PULSE_MODE:
			SET_BIT(TIM5->CR1,3);
			break;
		default:
			// Do nothing
			break;
	}

	// Set input filters parameters in case of input modes 
	if (TimerMode >= INPUT_CAPTURE_MODE && TimerMode <= ONE_PULSE_MODE)
	{
		// Configure filters clock
		TIM5->CR1 |= (TIMER5_FILTER_DTS << 8);

		// Configure filters sampling rate
		// ETR
		TIM5->SMCR &= ~(0b1111 << 8);
		TIM5->SMCR |= (TIMER5_ETR_FILTER << 8);
		// TI1
		TIM5->CCMR1 &= ~(0b1111 << 4);
		TIM5->CCMR1 |= (TIMER5_TI1_FILTER << 4);
		// TI2
		TIM5->CCMR1 &= ~(0b1111 << 12);
		TIM5->CCMR1 |= (TIMER5_TI2_FILTER << 12);
		// TI3
		TIM5->CCMR2 &= ~(0b1111 << 4);
		TIM5->CCMR2 |= (TIMER5_TI3_FILTER << 4);
		// TI4
		TIM5->CCMR2 &= ~(0b1111 << 12);
		TIM5->CCMR2 |= (TIMER5_TI4_FILTER << 12);

		// Configure capture compare prescalers
		// ETR
		TIM5->SMCR &= ~(0b11 << 12);
		TIM5->SMCR |= (TIMER5_ETR_PRESCALER << 12);
		// TI1
		TIM5->CCMR1 &= ~(0b11 << 2);
		TIM5->CCMR1 |= (TIMER5_TI1_PRESCALER << 2);
		// TI2
		TIM5->CCMR1 &= ~(0b11 << 12);
		TIM5->CCMR1 |= (TIMER5_TI2_PRESCALER << 10);
		// TI3
		TIM5->CCMR2 &= ~(0b11 << 2);
		TIM5->CCMR2 |= (TIMER5_TI3_PRESCALER << 2);
		// TI4
		TIM5->CCMR2 &= ~(0b11 << 12);
		TIM5->CCMR2 |= (TIMER5_TI4_PRESCALER << 10);
	}

	// Set count mode
	TIM5->CR1 |= (CountMode << 4);

	// Set prescaler
	TIM5->PSC = TimerPrescaler;
	Timer5Prescaler = TimerPrescaler;

	// Update timer registers
	if (CountMode == COUNT_UP || CountMode == COUNT_UP_DOWN)
	{
		TIM5->ARR = 65535;
	}
	else
	{
		TIM5->ARR = 0;
	}
	TIM5->SR = 0;
	SET_BIT(TIM5->EGR,0);

	// Initialize channels as input by default to avoid setting flags
	TIM5->CCMR1 |= (1 << 0);
	TIM5->CCMR1 |= (1 << 8);
	TIM5->CCMR2 |= (1 << 0);
	TIM5->CCMR2 |= (1 << 8);

	// Enable timer
	SET_BIT(TIM5->CR1, 0);
}

// Function to initialize channels of timer2
void TIM5_initChannel(ChannelSelect_type ChannelId, 
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
			TIM5->CCMR1 &= ~(0b11 << 0);
			TIM5->CCMR1 |= (ChannelMode << 4);

			// Set preload enable disable
			if (PreloadEnableDisable == PRELOAD_ENABLE)
			{
				// Enable preload
				SET_BIT(TIM5->CCMR1, 3);
			}
			else if (PreloadEnableDisable == PRELOAD_DISABLE)
			{
				// Disable preload
				CLR_BIT(TIM5->CCMR1, 3);
			}

			// Set fast enable disable
			if (FastEnableDisable == FAST_ENABLE)
			{
				// Enable fast
				SET_BIT(TIM5->CCMR1, 2);
			}
			else if (FastEnableDisable == FAST_DISABLE)
			{
				// Disable fast
				SET_BIT(TIM5->CCMR1, 2);
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
			TIM5->CCMR1 &= ~(0b11 << 0);
			TIM5->CCMR1 |= (ChannelMode << 0);
		}

		// Set capture compare polarity
		if (CaptureComparePolarity == CAPTURE_COMPARE_POL_0)
		{
			// Enable capture compare
			CLR_BIT(TIM5->CCER, 1);
		}
		else if (CaptureComparePolarity == CAPTURE_COMPARE_POL_1)
		{
			// Enable capture compare
			SET_BIT(TIM5->CCER, 1);
		}

		// Enable capture compare
		SET_BIT(TIM5->CCER, 0);
		break;
	case CHANNEL2:

		// Set channel mode
		if (ChannelMode >= 0 && ChannelMode < 8 )
		{
			// Select output mode
			TIM5->CCMR1 &= ~(0b11 << 8);
			TIM5->CCMR1 |= (ChannelMode << 12);

			// Set preload enable disable
			if (PreloadEnableDisable == PRELOAD_ENABLE)
			{
				// Enable preload
				SET_BIT(TIM5->CCMR1, 11);
			}
			else if (PreloadEnableDisable == PRELOAD_DISABLE)
			{
				// Disable preload
				CLR_BIT(TIM5->CCMR1, 11);
			}

			// Set fast enable disable
			if (FastEnableDisable == FAST_ENABLE)
			{
				// Enable fast
				SET_BIT(TIM5->CCMR1, 10);
			}
			else if (FastEnableDisable == FAST_DISABLE)
			{
				// Disable fast
				SET_BIT(TIM5->CCMR1, 10);
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
			TIM5->CCMR1 &= ~(0b11 << 8);
			TIM5->CCMR1 |= (ChannelMode << 8);
		}

		// Set capture compare polarity
		if (CaptureComparePolarity == CAPTURE_COMPARE_POL_0)
		{
			// Enable capture compare
			CLR_BIT(TIM5->CCER, 5);
		}
		else if (CaptureComparePolarity == CAPTURE_COMPARE_POL_1)
		{
			// Enable capture compare
			SET_BIT(TIM5->CCER, 5);
		}

		// Enable capture compare
		SET_BIT(TIM5->CCER, 4);
		break;
	case CHANNEL3:

		// Set channel mode
		if (ChannelMode >= 0 && ChannelMode < 8 )
		{
			// Select output mode
			TIM5->CCMR2 &= ~(0b11 << 0);
			TIM5->CCMR2 |= (ChannelMode << 4);

			// Set preload enable disable
			if (PreloadEnableDisable == PRELOAD_ENABLE)
			{
				// Enable preload
				SET_BIT(TIM5->CCMR2, 3);
			}
			else if (PreloadEnableDisable == PRELOAD_DISABLE)
			{
				// Disable preload
				CLR_BIT(TIM5->CCMR2, 3);
			}

			// Set fast enable disable
			if (FastEnableDisable == FAST_ENABLE)
			{
				// Enable fast
				SET_BIT(TIM5->CCMR2, 2);
			}
			else if (FastEnableDisable == FAST_DISABLE)
			{
				// Disable fast
				SET_BIT(TIM5->CCMR2, 2);
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
			TIM5->CCMR2 &= ~(0b11 << 0);
			TIM5->CCMR2 |= (ChannelMode << 0);
		}

		// Set capture compare polarity
		if (CaptureComparePolarity == CAPTURE_COMPARE_POL_0)
		{
			// Enable capture compare
			CLR_BIT(TIM5->CCER, 9);
		}
		else if (CaptureComparePolarity == CAPTURE_COMPARE_POL_1)
		{
			// Enable capture compare
			SET_BIT(TIM5->CCER, 9);
		}

		// Enable capture compare
		SET_BIT(TIM5->CCER, 8);
		break;
	case CHANNEL4:

		// Set channel mode
		if (ChannelMode >= 0 && ChannelMode < 8 )
		{
			// Select output mode
			TIM5->CCMR2 &= ~(0b11 << 8);
			TIM5->CCMR2 |= (ChannelMode << 12);

			// Set preload enable disable
			if (PreloadEnableDisable == PRELOAD_ENABLE)
			{
				// Enable preload
				SET_BIT(TIM5->CCMR1, 11);
			}
			else if (PreloadEnableDisable == PRELOAD_DISABLE)
			{
				// Disable preload
				CLR_BIT(TIM5->CCMR1, 11);
			}

			// Set fast enable disable
			if (FastEnableDisable == FAST_ENABLE)
			{
				// Enable fast
				SET_BIT(TIM5->CCMR1, 10);
			}
			else if (FastEnableDisable == FAST_DISABLE)
			{
				// Disable fast
				SET_BIT(TIM5->CCMR1, 10);
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
			TIM5->CCMR2 &= ~(0b11 << 8);
			TIM5->CCMR2 |= (ChannelMode << 8);
		}

		// Set capture compare polarity
		if (CaptureComparePolarity == CAPTURE_COMPARE_POL_0)
		{
			// Enable capture compare
			CLR_BIT(TIM5->CCER, 13);
		}
		else if (CaptureComparePolarity == CAPTURE_COMPARE_POL_1)
		{
			// Enable capture compare
			SET_BIT(TIM5->CCER, 13);
		}

		// Enable capture compare
		SET_BIT(TIM5->CCER, 12);
		break;
	default:
		// Do nothing
		break;
	}
}

// Function to change capture compare edge
void TIM5_changeCaptureComparePolarity(ChannelSelect_type ChannelId, 
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
			CLR_BIT(TIM5->CCER, 1);
		}
		else if (CaptureComparePolarity == CAPTURE_COMPARE_POL_1)
		{
			// Enable capture compare
			SET_BIT(TIM5->CCER, 1);
		}
		break;
	case CHANNEL2:
		
		// Set capture compare polarity
		if (CaptureComparePolarity == CAPTURE_COMPARE_POL_0)
		{
			// Enable capture compare
			CLR_BIT(TIM5->CCER, 5);
		}
		else if (CaptureComparePolarity == CAPTURE_COMPARE_POL_1)
		{
			// Enable capture compare
			SET_BIT(TIM5->CCER, 5);
		}
		break;
	case CHANNEL3:

		// Set capture compare polarity
		if (CaptureComparePolarity == CAPTURE_COMPARE_POL_0)
		{
			// Enable capture compare
			CLR_BIT(TIM5->CCER, 9);
		}
		else if (CaptureComparePolarity == CAPTURE_COMPARE_POL_1)
		{
			// Enable capture compare
			SET_BIT(TIM5->CCER, 9);
		}
		break;
	case CHANNEL4:
		
		// Set capture compare polarity
		if (CaptureComparePolarity == CAPTURE_COMPARE_POL_0)
		{
			// Enable capture compare
			CLR_BIT(TIM5->CCER, 13);
		}
		else if (CaptureComparePolarity == CAPTURE_COMPARE_POL_1)
		{
			// Enable capture compare
			SET_BIT(TIM5->CCER, 13);
		}
		break;
	default:
		// Do nothing
		break;
	}
}

// Function to make a delay with specific ticks
void TIM5_setBusyWait(u16 Ticks)
{
	// Disable timer
	CLR_BIT(TIM5->CR1,0);

	// Upload timer
	TIM5->ARR = Ticks;
	SET_BIT(TIM5->EGR,0);

	// Enable Timer
	SET_BIT(TIM5->CR1,0);
	while(GET_BIT(TIM5->SR,0)==0);

	// Clear Uderflow Flag
	CLR_BIT(TIM5->SR,0);

	// Disable timer
	CLR_BIT(TIM5->CR1,0);
}

// Function to call another function after number of ticks one time
void TIM5_setSingleInterval(u16 Ticks, void (*Callback)(void))
{
	// Validate input parameters
	ASSERT(Callback != NULL);

	// Save callBack
	TIM5_UnderflowCallback=Callback;

	// Set Mode to Single
	Timer5IntervalModeFlag=1;

	// stop timer 
	CLR_BIT(TIM5->CR1,GPTIM_CEN);

	// Re-Initialize the the counter 
	TIM5->ARR=Ticks;
	SET_BIT(TIM5->EGR,GPTIM_UG);
		
	// Enable Update Interrupt 
	SET_BIT(TIM5->DIER,GPTIM_UIE);

	// Enable counter
	SET_BIT(TIM5->CR1,GPTIM_CEN);
	
}

// Function to call another function after number of ticks periodic
void TIM5_setPeriodicInterval(u16 Ticks, void (*Callback)(void))
{
	// Validate input parameters
	ASSERT(Callback != NULL);

	// Save callBack
	TIM5_UnderflowCallback=Callback;

	// Set Mode to Single
	Timer5IntervalModeFlag=0;

	// stop timer 
	CLR_BIT(TIM5->CR1,GPTIM_CEN);

	// Re-Initialize the the counter 
	TIM5->ARR=Ticks;
	SET_BIT(TIM5->EGR,GPTIM_UG);
		
	// Enable Update Interrupt 
	SET_BIT(TIM5->DIER,GPTIM_UIE);

	// Enable counter
	SET_BIT(TIM5->CR1,GPTIM_CEN);
	
}

// Function to reload timer value
void TIM5_reloadTimerValue(u16 TimerValue)
{
	TIM5->CNT = TimerValue;
}
u16  TIM5_getTimerValue(void)
{
	return TIM5->CNT;
}

// Function to reload capture compare value
void TIM5_reloadCaptureCompareValue(ChannelSelect_type ChannelId,u16 CaptureCompareValue)
{
	// Validate input parameters
	ASSERT(ChannelId >= 0 && ChannelId < CHANNEL_ERR);

	// Temp variable to hold the CCR of the nedded channel
	u16 TempValue = 0; 

	// Select a channel to return its value
	switch (ChannelId)
	{
	case CHANNEL1:
		TIM5->CCR1 = CaptureCompareValue;
		break;
	case CHANNEL2:
		TIM5->CCR2 = CaptureCompareValue;
		break;
	case CHANNEL3:
		TIM5->CCR3 = CaptureCompareValue;
		break;
	case CHANNEL4:
		TIM5->CCR4 = CaptureCompareValue;
		break;
	default:
		// Do nothing
		break;
	}
}

// Function to get capture compare value
u16  TIM5_getCaptureCompareValue(ChannelSelect_type ChannelId)
{
	// Validate input parameters
	ASSERT(ChannelId >= 0 && ChannelId < CHANNEL_ERR);

	// Temp variable to hold the CCR of the nedded channel
	u16 TempValue = 0; 

	// Select a channel to return its value
	switch (ChannelId)
	{
	case CHANNEL1:
		TempValue = TIM5->CCR1;
		break;
	case CHANNEL2:
		TempValue = TIM5->CCR2;
		break;
	case CHANNEL3:
		TempValue = TIM5->CCR3;
		break;
	case CHANNEL4:
		TempValue = TIM5->CCR4;
		break;
	default:
		// Do nothing
		break;
	}
	return TempValue;
}

// Function to restart timer
void TIM5_restartTimer(void)
{
	// Enable counter
	SET_BIT(TIM5->CR1, 0);
}

// Function to stop timer
void TIM5_stopTimer(void)
{
	// Disable counter
	CLR_BIT(TIM5->CR1, 0);
}

// Function to enable capture compare interrupt
void TIM5_enableCaptureCompareInterrupt(ChannelSelect_type ChannelId)
{
	// Validate input parameters
	ASSERT(ChannelId >= 0 && ChannelId < CHANNEL_ERR);

	// Select a channel to return its value
	switch (ChannelId)
	{
	case CHANNEL1:
		SET_BIT(TIM5->DIER,1);
		break;
	case CHANNEL2:
		SET_BIT(TIM5->DIER,2);
		break;
	case CHANNEL3:
		SET_BIT(TIM5->DIER,3);
		break;
	case CHANNEL4:
		SET_BIT(TIM5->DIER,4);
		break;
	default:
		// Do nothing
		break;
	}
}

// Function to disable capture compare interrupt
void TIM5_disableCaptureCompareInterrupt(ChannelSelect_type ChannelId)
{
	// Validate input parameters
	ASSERT(ChannelId >= 0 && ChannelId < CHANNEL_ERR);

	// Select a channel to return its value
	switch (ChannelId)
	{
	case CHANNEL1:
		CLR_BIT(TIM5->DIER,1);
		break;
	case CHANNEL2:
		CLR_BIT(TIM5->DIER,2);
		break;
	case CHANNEL3:
		CLR_BIT(TIM5->DIER,3);
		break;
	case CHANNEL4:
		CLR_BIT(TIM5->DIER,4);
		break;
	default:
		// Do nothing
		break;
	}
}

// Function to set capture compare callback
void TIM5_setCaptureCompareCallback(ChannelSelect_type ChannelId,void (*Callback)(void))
{
	// Validate input parameters
	ASSERT(ChannelId >= 0 && ChannelId < CHANNEL_ERR);
	ASSERT(Callback != NULL);

	// Select a channel to return its value
	switch (ChannelId)
	{
	case CHANNEL1:
		TIM5_CH1_CaptureCompareCallback = Callback;
		break;
	case CHANNEL2:
		TIM5_CH2_CaptureCompareCallback = Callback;
		break;
	case CHANNEL3:
		TIM5_CH3_CaptureCompareCallback = Callback;
		break;
	case CHANNEL4:
		TIM5_CH4_CaptureCompareCallback = Callback;
		break;
	default:
		// Do nothing
		break;
	}
}

// Function to set pwm1 parameters
void TIM5_generatePWM1(ChannelSelect_type ChannelId,u32 Frequency,u8 DutyCycle)
{
	// Validate input parameters
	ASSERT(ChannelId >= 0 && ChannelId < CHANNEL_ERR);

	// Disable timer
	CLR_BIT(TIM5->CR1,0);

	// Set pwm parameters
	u16 Temp1 = (4000000/(Timer5Prescaler*Frequency))+1;
	u16 Temp2 = (((Temp1+1)/ 100)*DutyCycle)+1;
	TIM5->CCR1 = Temp2;
	TIM5->ARR = Temp1;

	// Update registers
	SET_BIT(TIM5->EGR,0);

	// Enable Timer
	SET_BIT(TIM5->CR1,0);
}

// Function to set pwm2 parameters
void TIM5_generatePWM2(ChannelSelect_type ChannelId,u32 Frequency,u8 DutyCycle)
{
	// Validate input parameters
	ASSERT(ChannelId >= 0 && ChannelId < CHANNEL_ERR);
	
	// Disable timer
	CLR_BIT(TIM5->CR1,0);

	// Set pwm parameters
	u16 Temp1 = 4000000/(2*Timer5Prescaler*Frequency);
	u16 Temp2 = (Temp1/ 100)*DutyCycle;
	TIM5->ARR = Temp1;
	TIM5->CCR1 = Temp2;

	// Update registers
	SET_BIT(TIM5->EGR,0);

	// Enable Timer
	SET_BIT(TIM5->CR1,0);

}





/* ==================================================================== */
/* ================ Private Functions Implementation ================== */
/* ==================================================================== */

// Timer2 isr
void TIM2_IRQHandler(void)
{
	// Overflow callback	
	if (GET_BIT(TIM2->SR,0) == 1 && GET_BIT(TIM2->DIER,0) == 1 && TIM2_OverflowCallback != NULL)
	{
		TIM2_OverflowCallback();
		CLR_BIT(TIM2->SR, 0);
		if (Timer2IntervalModeFlag == 1)
		{
			// Disable timer
			CLR_BIT(TIM2->CR1, 0);
		}	
	}

	// Channel1 callback
	if (GET_BIT(TIM2->SR,1) == 1 && GET_BIT(TIM2->DIER,1) == 1 && TIM2_CH1_CaptureCompareCallback != NULL)
	{
		TIM2_CH1_CaptureCompareCallback();
		CLR_BIT(TIM2->SR, 1);
	}

	// Channel2 callback
	if (GET_BIT(TIM2->SR,2) == 1 && GET_BIT(TIM2->DIER,2) == 1 && TIM2_CH2_CaptureCompareCallback != NULL)  
	{
		TIM2_CH2_CaptureCompareCallback();
		CLR_BIT(TIM2->SR, 2);
	}

	// Channel3 callback
	if (GET_BIT(TIM2->SR,3) == 1 && GET_BIT(TIM2->DIER,3) == 1 && TIM2_CH3_CaptureCompareCallback != NULL)
	{
		TIM2_CH3_CaptureCompareCallback();
		CLR_BIT(TIM2->SR, 3);
	}

	// Channel4 callback
	if (GET_BIT(TIM2->SR,4) == 1 && GET_BIT(TIM2->DIER,4) == 1 && TIM2_CH4_CaptureCompareCallback != NULL)
	{
		TIM2_CH4_CaptureCompareCallback();
		CLR_BIT(TIM2->SR, 4);
	}

}


// Timer3 isr
void TIM3_IRQHandler(void)
{
	// Overflow callback	
	if (GET_BIT(TIM3->SR,0) == 1 && GET_BIT(TIM3->DIER,0) == 1 && TIM3_OverflowCallback != NULL)
	{
		TIM3_OverflowCallback();
		CLR_BIT(TIM3->SR, 0);
		if (Timer3IntervalModeFlag == 1)
		{
			// Disable timer
			CLR_BIT(TIM3->CR1, 0);
		}	
	}

	// Channel1 callback
	if (GET_BIT(TIM3->SR,1) == 1 && GET_BIT(TIM3->DIER,1) == 1 && TIM3_CH1_CaptureCompareCallback != NULL)
	{
		TIM3_CH1_CaptureCompareCallback();
		CLR_BIT(TIM3->SR, 1);
	}

	// Channel2 callback
	if (GET_BIT(TIM3->SR,2) == 1 && GET_BIT(TIM3->DIER,2) == 1 && TIM3_CH2_CaptureCompareCallback != NULL)  
	{
		TIM3_CH2_CaptureCompareCallback();
		CLR_BIT(TIM3->SR, 2);
	}

	// Channel3 callback
	if (GET_BIT(TIM3->SR,3) == 1 && GET_BIT(TIM3->DIER,3) == 1 && TIM3_CH3_CaptureCompareCallback != NULL)
	{
		TIM2_CH3_CaptureCompareCallback();
		CLR_BIT(TIM3->SR, 3);
	}

	// Channel4 callback
	if (GET_BIT(TIM3->SR,4) == 1 && GET_BIT(TIM3->DIER,4) == 1 && TIM3_CH4_CaptureCompareCallback != NULL)
	{
		TIM3_CH4_CaptureCompareCallback();
		CLR_BIT(TIM3->SR, 4);
	}

}

// Timer4 isr
void TIM4_IRQHandler(void)
{
	// Overflow callback	
	if (GET_BIT(TIM4->SR,0) == 1 && GET_BIT(TIM4->DIER,0) == 1 && TIM4_OverflowCallback != NULL)
	{
		TIM4_OverflowCallback();
		CLR_BIT(TIM4->SR, 0);
		if (Timer4IntervalModeFlag == 1)
		{
			// Disable timer
			CLR_BIT(TIM4->CR1, 0);
		}	
	}

	// Channel1 callback
	if (GET_BIT(TIM4->SR,1) == 1 && GET_BIT(TIM4->DIER,1) == 1 && TIM4_CH1_CaptureCompareCallback != NULL)
	{
		TIM4_CH1_CaptureCompareCallback();
		CLR_BIT(TIM4->SR, 1);
	}

	// Channel2 callback
	if (GET_BIT(TIM4->SR,2) == 1 && GET_BIT(TIM4->DIER,2) == 1 && TIM4_CH2_CaptureCompareCallback != NULL)  
	{
		TIM4_CH2_CaptureCompareCallback();
		CLR_BIT(TIM4->SR, 2);
	}

	// Channel3 callback
	if (GET_BIT(TIM4->SR,3) == 1 && GET_BIT(TIM4->DIER,3) == 1 && TIM4_CH3_CaptureCompareCallback != NULL)
	{
		TIM4_CH3_CaptureCompareCallback();
		CLR_BIT(TIM4->SR, 3);
	}

	// Channel4 callback
	if (GET_BIT(TIM4->SR,4) == 1 && GET_BIT(TIM4->DIER,4) == 1 && TIM4_CH4_CaptureCompareCallback != NULL)
	{
		TIM3_CH4_CaptureCompareCallback();
		CLR_BIT(TIM4->SR, 4);
	}

}

// Timer5 isr
void TIM5_IRQHandler(void)
{
	// Overflow callback	
	if (GET_BIT(TIM5->SR,0) == 1 && GET_BIT(TIM5->DIER,0) == 1 && TIM5_OverflowCallback != NULL)
	{
		TIM5_OverflowCallback();
		CLR_BIT(TIM5->SR, 0);
		if (Timer5IntervalModeFlag == 1)
		{
			// Disable timer
			CLR_BIT(TIM5->CR1, 0);
		}	
	}

	// Channel1 callback
	if (GET_BIT(TIM5->SR,1) == 1 && GET_BIT(TIM5->DIER,1) == 1 && TIM5_CH1_CaptureCompareCallback != NULL)
	{
		TIM5_CH1_CaptureCompareCallback();
		CLR_BIT(TIM5->SR, 1);
	}

	// Channel2 callback
	if (GET_BIT(TIM5->SR,2) == 1 && GET_BIT(TIM5->DIER,2) == 1 && TIM5_CH2_CaptureCompareCallback != NULL)  
	{
		TIM5_CH2_CaptureCompareCallback();
		CLR_BIT(TIM5->SR, 2);
	}

	// Channel3 callback
	if (GET_BIT(TIM5->SR,3) == 1 && GET_BIT(TIM5->DIER,3) == 1 && TIM5_CH3_CaptureCompareCallback != NULL)
	{
		TIM5_CH3_CaptureCompareCallback();
		CLR_BIT(TIM5->SR, 3);
	}

	// Channel4 callback
	if (GET_BIT(TIM5->SR,4) == 1 && GET_BIT(TIM5->DIER,4) == 1 && TIM5_CH4_CaptureCompareCallback != NULL)
	{
		TIM5_CH4_CaptureCompareCallback();
		CLR_BIT(TIM5->SR, 4);
	}

}