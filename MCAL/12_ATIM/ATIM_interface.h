/******************************************************************************
* @file:    GPTIM_interface.h
* @author:  Copyright (c) 2023 Gomaa Mohammed Gomaa.
* @license: GNU GPL version 3 or later.
*			This is free software: you are free to change and redistribute it.  
*			There is NO WARRANTY, to the extent permitted by law.
* @version: V0.2   
* @date:    Tue, 17 Aug 2023 21:35:12 +0200
* @brief:   Advanced Timers(GPTIM) Driver for STM32F103
*******************************************************************************/
#ifndef    _ATIM_INTERFACE_H
#define    _ATIM_INTERFACE_H

/* ==================================================================== */
/* ======================= public data types ========================== */
/* ==================================================================== */

/* Count Mode data type */
typedef enum
{
    COUNT_UP=0,
    COUNT_DOWN=1,
    COUNT_UP_DOWN=6,
    COUNT_MODE_ERR
} CountMode_type;

/* Timer Mode data type */
typedef enum
{
    NORMAL_MODE=0,
    INPUT_CAPTURE_MODE,
    INPUT_PWM_MODE,
    FORCED_OUTPUT_MODE,
    OUTPUT_COMPARE_MODE,
    PWM_MODE,
    ONE_PULSE_MODE,
    ENCODER_INTERFACE_MODE,
    DEBUG_MODE,
    TIMER_MODE_ERR
} TimerMode_type;

typedef enum
{
    CHANNEL1=0,
    CHANNEL2,
    CHANNEL3,
    CHANNEL4,
    CHANNEL_ERR
} ChannelSelect_type;

typedef enum
{
    // Channel as output configurations
    CH_OUTPUT_WAVEFORM_FROZEN=0,
    CH_OUTPUT_WAVEFORM_HIGH,
    CH_OUTPUT_WAVEFORM_LOW,
    CH_OUTPUT_WAVEFORM_TOGGLE,
    CH_OUTPUT_WAVEFORM_FORCED_LOW,
    CH_OUTPUT_WAVEFORM_FORCED_HIGH,
    CH_OUTPUT_WAVEFORM_PWM1,
    CH_OUTPUT_WAVEFORM_PWM2,
    // Channel as input configurations
    CH_INPUT_TI1,
    CH_INPUT_TI2,
    CH_INPUT_TI3,
    CH_INPUT_TI4,
    CH_INPUT_TRC,
    CH_MODE_ERR
} ChannelOutputInput_type;

typedef enum
{
    CAPTURE_COMPARE_POL_0=0,  // Active high at output...Rising at input
    CAPTURE_COMPARE_POL_1,    // Active low at output...Falling at input
    CAPTURE_COMPARE_POL_ERR
} CaptureComparePolarity_type;

typedef enum
{
    PRELOAD_DISABLE=0,
    PRELOAD_ENABLE,
    PRELOAD_ERR
} PreloadEnable_type;

typedef enum
{
    FAST_DISABLE=0,
    FAST_ENABLE,
    FAST_ERR
} FastEnable_type;

/* ==================================================================== */
/* ==================== Public Functions Declaration ================== */
/* ==================================================================== */

/************************** Timer1 *****************************/

/**
 * @brief---------------------> Initialize timer
 * @parameter1----------------> (TimerMode) timer mode to be set
 * @parameter2----------------> (CountMode) count mode up/down to be set
 * @parameter3----------------> (TimerPrescaler) timer prescaler to be set
 * @return--------------------> None
 * @preconditions-------------> None
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Reentrant
 */
void TIM1_init(TimerMode_type TimerMode, 
               CountMode_type CountMode, 
               u16 TimerPrescaler);

/**
 * @brief---------------------> Initialize timer channel
 * @parameter1----------------> (ChannelId) id of channel to be initialized
 * @parameter2----------------> (ChannelMode) mode of channel
 * @parameter3----------------> (CaptureComparePolarity) timer response edge 
 * @parameter4----------------> (PreloadEnableDisable) disable and enable preload
 * @parameter5----------------> (CaptureComparePolarity) timer response edge 
 * @return--------------------> None
 * @preconditions-------------> None
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Reentrant
 * Note: Channel1 and Channel2 can be mapped on TI1, TI2 or TRC only
 *       Channel3 and Channel4 can be mapped on TI3, TI4 or TRC only
 */
void TIM1_initChannel(ChannelSelect_type ChannelId, 
                      ChannelOutputInput_type ChannelMode,
                      CaptureComparePolarity_type CaptureComparePolarity,
                      PreloadEnable_type PreloadEnableDisable,
                      FastEnable_type FastEnableDisable);

/**
 * @brief---------------------> Make delay with number of ticks
 * @parameter1----------------> (Ticks) number of ticks to be delayed
 * @return--------------------> None
 * @preconditions-------------> None
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Reentrant
 */
void TIM1_setBusyWait(u16 Ticks);

/**
 * @brief---------------------> Call a function after number of ticks one time
 * @parameter1----------------> (Ticks) number of ticks to be delayed
 * @parameter2----------------> (Callback) function to be called
 * @return--------------------> None
 * @preconditions-------------> None
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Reentrant
 */
void TIM1_setSingleInterval(u16 Ticks, void (*Callback)(void));

/**
 * @brief---------------------> Call a function after number of ticks periodically
 * @parameter1----------------> (Ticks) number of ticks to be delayed
 * @parameter2----------------> (Callback) function to be called
 * @return--------------------> None
 * @preconditions-------------> None
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Reentrant
 */
void TIM1_setPeriodicInterval(u16 Ticks, void (*Callback)(void));

/**
 * @brief---------------------> Reload timer value 
 * @parameter1----------------> (TimerValue) value to be loaded to timer
 * @return--------------------> None
 * @preconditions-------------> None
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Reentrant
 */
void TIM1_reloadTimerValue(u16 TimerValue);

/**
 * @brief---------------------> Get timer value 
 * @param---------------------> None
 * @return--------------------> Timer value
 * @preconditions-------------> None
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Reentrant
 */
u16  TIM1_getTimerValue(void);

/**
 * @brief---------------------> Reload capture compare value 
 * @parameter1----------------> (ChannelId) channel to be loaded its value
 * @parameter2----------------> (CaptureCompareValue) value to be loaded to channel
 * @return--------------------> None
 * @preconditions-------------> None
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Reentrant
 */
void TIM1_reloadCaptureCompareValue(ChannelSelect_type ChannelId,u16 CaptureCompareValue);

/**
 * @brief---------------------> Get capture compare value 
 * @parameter1----------------> (ChannelId) channel to get its value
 * @return--------------------> None
 * @preconditions-------------> None
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Reentrant
 */
u16  TIM1_getCaptureCompareValue(ChannelSelect_type ChannelId);

/**
 * @brief---------------------> Change capture compare polarity 
 * @parameter1----------------> (ChannelId) channel to change its polarity
 * @parameter2----------------> (CaptureComparePolarity) capture compare polarity to be set
 * @return--------------------> None
 * @preconditions-------------> None
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Reentrant
 */
void TIM1_changeCaptureComparePolarity(ChannelSelect_type ChannelId, 
                                      CaptureComparePolarity_type CaptureComparePolarity);

/**
 * @brief---------------------> Restart timer 
 * @param---------------------> None
 * @return--------------------> None
 * @preconditions-------------> None
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Reentrant
 */
void TIM1_restartTimer(void);

/**
 * @brief---------------------> Stop timer 
 * @param---------------------> None
 * @return--------------------> None
 * @preconditions-------------> None
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Reentrant
 */
void TIM1_stopTimer(void);

/**
 * @brief---------------------> Enable capture compare interrupt
 * @parameter1----------------> (ChannelId) channel to enable its interrupt
 * @return--------------------> None
 * @preconditions-------------> None
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Reentrant
 */
void TIM1_enableCaptureCompareInterrupt(ChannelSelect_type ChannelId);

/**
 * @brief---------------------> Disable capture compare interrupt
 * @parameter1----------------> (ChannelId) channel to disable its interrupt
 * @return--------------------> None
 * @preconditions-------------> None
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Reentrant
 */
void TIM1_disableCaptureCompareInterrupt(ChannelSelect_type ChannelId);

/**
 * @brief---------------------> Enable capture compare interrupt
 * @parameter1----------------> (ChannelId) channel to set its callback
 * @parameter2----------------> (Callback) callback function to be set
 * @return--------------------> None
 * @preconditions-------------> None
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Reentrant
 */
void TIM1_setCaptureCompareCallback(ChannelSelect_type ChannelId,void (*Callback)(void));

/**
 * @brief---------------------> Set pwm1 parameters
 * @parameter1----------------> (ChannelId) channel to set its pwm parameters
 * @parameter2----------------> (Frequency) frequency of pwm signal
 * @parameter3----------------> (DutyCycle) duty cycle of pwm signal
 * @return--------------------> None
 * @preconditions-------------> Timer is initialized in up count mode
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Reentrant
 */
void TIM1_generatePWM1(ChannelSelect_type ChannelId,u32 Frequency,u8 DutyCycle);

/**
 * @brief---------------------> Set pwm2 parameters
 * @parameter1----------------> (ChannelId) channel to set its pwm parameters
 * @parameter2----------------> (Frequency) frequency of pwm signal
 * @parameter3----------------> (DutyCycle) duty cycle of pwm signal
 * @return--------------------> None
 * @preconditions-------------> Timer is initialized in up/down count mode
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Reentrant
 */
void TIM1_generatePWM2(ChannelSelect_type ChannelId,u32 Frequency,u8 DutyCycle);

#endif