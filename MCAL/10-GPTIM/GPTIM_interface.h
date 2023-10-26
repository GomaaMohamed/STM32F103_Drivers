/******************************************************************************
* @file:    GPTIM_interface.h
* @author:  Copyright (c) 2023 Gomaa Mohammed Gomaa.
* @license: GNU GPL version 3 or later.
*			This is free software: you are free to change and redistribute it.  
*			There is NO WARRANTY, to the extent permitted by law.
* @version: V0.2   
* @date:    Sun, 15 Oct 2023 14:21:12 +0200
* @brief:   General Purpose Timers(GPTIM) Driver for STM32F103
*******************************************************************************/
#ifndef    _GPTIM_INTERFACE_H
#define    _GPTIM_INTERFACE_H

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

/************************** Timer2 *****************************/

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
void TIM2_init(TimerMode_type TimerMode, 
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
void TIM2_initChannel(ChannelSelect_type ChannelId, 
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
void TIM2_setBusyWait(u16 Ticks);

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
void TIM2_setSingleInterval(u16 Ticks, void (*Callback)(void));

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
void TIM2_setPeriodicInterval(u16 Ticks, void (*Callback)(void));

/**
 * @brief---------------------> Reload timer value 
 * @parameter1----------------> (TimerValue) value to be loaded to timer
 * @return--------------------> None
 * @preconditions-------------> None
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Reentrant
 */
void TIM2_reloadTimerValue(u16 TimerValue);

/**
 * @brief---------------------> Get timer value 
 * @param---------------------> None
 * @return--------------------> Timer value
 * @preconditions-------------> None
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Reentrant
 */
u16  TIM2_getTimerValue(void);

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
void TIM2_reloadCaptureCompareValue(ChannelSelect_type ChannelId,u16 CaptureCompareValue);

/**
 * @brief---------------------> Get capture compare value 
 * @parameter1----------------> (ChannelId) channel to get its value
 * @return--------------------> None
 * @preconditions-------------> None
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Reentrant
 */
u16  TIM2_getCaptureCompareValue(ChannelSelect_type ChannelId);

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
void TIM2_changeCaptureComparePolarity(ChannelSelect_type ChannelId, 
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
void TIM2_restartTimer(void);

/**
 * @brief---------------------> Stop timer 
 * @param---------------------> None
 * @return--------------------> None
 * @preconditions-------------> None
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Reentrant
 */
void TIM2_stopTimer(void);

/**
 * @brief---------------------> Enable capture compare interrupt
 * @parameter1----------------> (ChannelId) channel to enable its interrupt
 * @return--------------------> None
 * @preconditions-------------> None
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Reentrant
 */
void TIM2_enableCaptureCompareInterrupt(ChannelSelect_type ChannelId);

/**
 * @brief---------------------> Disable capture compare interrupt
 * @parameter1----------------> (ChannelId) channel to disable its interrupt
 * @return--------------------> None
 * @preconditions-------------> None
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Reentrant
 */
void TIM2_disableCaptureCompareInterrupt(ChannelSelect_type ChannelId);

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
void TIM2_setCaptureCompareCallback(ChannelSelect_type ChannelId,void (*Callback)(void));

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
void TIM2_generatePWM1(ChannelSelect_type ChannelId,u32 Frequency,u8 DutyCycle);

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
void TIM2_generatePWM2(ChannelSelect_type ChannelId,u32 Frequency,u8 DutyCycle);



/************************** Timer3 *****************************/

void TIM3_init(TimerMode_type TimerMode, 
               CountMode_type CountMode, 
               u16 TimerPrescaler);
void TIM3_initChannel(ChannelSelect_type ChannelId, 
                      ChannelOutputInput_type ChannelMode,
                      CaptureComparePolarity_type CaptureComparePolarity,
                      PreloadEnable_type PreloadEnableDisable,
                      FastEnable_type FastEnableDisable);
void TIM3_setBusyWait(u16 Ticks);
void TIM3_setSingleInterval(u16 Ticks, void (*Callback)(void));
void TIM3_setPeriodicInterval(u16 Ticks, void (*Callback)(void));
void TIM3_reloadTimerValue(u16 TimerValue);
u16  TIM3_getTimerValue(void);
void TIM3_reloadCaptureCompareValue(ChannelSelect_type ChannelId,u16 CaptureCompareValue);
u16  TIM3_getCaptureCompareValue(ChannelSelect_type ChannelId);
void TIM3_changeCptureComparePolarity(ChannelSelect_type ChannelId, 
                                      CaptureComparePolarity_type CaptureComparePolarity);
void TIM3_restartTimer(void);
void TIM3_stopTimer(void);
void TIM3_enableCaptureCompareInterrupt(ChannelSelect_type ChannelId);
void TIM3_disableCaptureCompareInterrupt(ChannelSelect_type ChannelId);
void TIM3_setCaptureCompareCallback(ChannelSelect_type ChannelId,void (*Callback)(void));
void TIM3_generatePWM1(ChannelSelect_type ChannelId,u32 Frequency,u8 DutyCycle);
void TIM3_generatePWM2(ChannelSelect_type ChannelId,u32 Frequency,u8 DutyCycle);


/************************** Timer4 *****************************/

void TIM4_init(TimerMode_type TimerMode, 
               CountMode_type CountMode, 
               u16 TimerPrescaler);
void TIM4_initChannel(ChannelSelect_type ChannelId, 
                      ChannelOutputInput_type ChannelMode,
                      CaptureComparePolarity_type CaptureComparePolarity,
                      PreloadEnable_type PreloadEnableDisable,
                      FastEnable_type FastEnableDisable);
void TIM4_setBusyWait(u16 Ticks);
void TIM4_setSingleInterval(u16 Ticks, void (*Callback)(void));
void TIM4_setPeriodicInterval(u16 Ticks, void (*Callback)(void));
void TIM4_reloadTimerValue(u16 TimerValue);
u16  TIM4_getTimerValue(void);
void TIM4_reloadCaptureCompareValue(ChannelSelect_type ChannelId,u16 CaptureCompareValue);
u16  TIM4_getCaptureCompareValue(ChannelSelect_type ChannelId);
void TIM4_changeCptureComparePolarity(ChannelSelect_type ChannelId, 
                                      CaptureComparePolarity_type CaptureComparePolarity);
void TIM4_restartTimer(void);
void TIM4_stopTimer(void);
void TIM4_enableCaptureCompareInterrupt(ChannelSelect_type ChannelId);
void TIM4_disableCaptureCompareInterrupt(ChannelSelect_type ChannelId);
void TIM4_setCaptureCompareCallback(ChannelSelect_type ChannelId,void (*Callback)(void));
void TIM4_generatePWM1(ChannelSelect_type ChannelId,u32 Frequency,u8 DutyCycle);
void TIM4_generatePWM2(ChannelSelect_type ChannelId,u32 Frequency,u8 DutyCycle);


/************************** Timer5 *****************************/

void TIM5_init(TimerMode_type TimerMode, 
               CountMode_type CountMode, 
               u16 TimerPrescaler);
void TIM5_initChannel(ChannelSelect_type ChannelId, 
                      ChannelOutputInput_type ChannelMode,
                      CaptureComparePolarity_type CaptureComparePolarity,
                      PreloadEnable_type PreloadEnableDisable,
                      FastEnable_type FastEnableDisable);
void TIM5_setBusyWait(u16 Ticks);
void TIM5_setSingleInterval(u16 Ticks, void (*Callback)(void));
void TIM5_setPeriodicInterval(u16 Ticks, void (*Callback)(void));
void TIM5_reloadTimerValue(u16 TimerValue);
u16  TIM5_getTimerValue(void);
void TIM5_reloadCaptureCompareValue(ChannelSelect_type ChannelId,u16 CaptureCompareValue);
u16  TIM5_getCaptureCompareValue(ChannelSelect_type ChannelId);
void TIM5_changeCptureComparePolarity(ChannelSelect_type ChannelId, 
                                      CaptureComparePolarity_type CaptureComparePolarity);
void TIM5_restartTimer(void);
void TIM5_stopTimer(void);
void TIM5_enableCaptureCompareInterrupt(ChannelSelect_type ChannelId);
void TIM5_disableCaptureCompareInterrupt(ChannelSelect_type ChannelId);
void TIM5_setCaptureCompareCallback(ChannelSelect_type ChannelId,void (*Callback)(void));
void TIM5_generatePWM1(ChannelSelect_type ChannelId,u32 Frequency,u8 DutyCycle);
void TIM5_generatePWM2(ChannelSelect_type ChannelId,u32 Frequency,u8 DutyCycle);




#endif
