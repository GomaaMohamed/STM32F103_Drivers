/*****************************************************************************
* @file:    GPTIM_private.h
* @author:  Copyright (c) 2023 Gomaa Mohammed Gomaa.
* @license: GNU GPL version 3 or later.
*			This is free software: you are free to change and redistribute it.  
*			There is NO WARRANTY, to the extent permitted by law.
* @version: V0.2   
* @date:    Tue, 17 Aug 2023 21:35:12 +0200
* @brief:   Advanced Timers(ATIM) Driver for STM32F103
******************************************************************************/
#ifndef    _ATIM_PRIVATE_H
#define    _ATIM_PRIVATE_H

/* ==================================================================== */
/* ======================== Private Data Types ======================== */
/* ==================================================================== */

/* GPTIM Registers Mapping data type */
typedef struct
{
	volatile u32 CR1;           // 00
	volatile u32 CR2;           // 04
	volatile u32 SMCR;          // 08
	volatile u32 DIER;          // 0C
	volatile u32 SR;            // 10
	volatile u32 EGR;           // 14
	volatile u32 CCMR1;         // 18
	volatile u32 CCMR2;         // 1C
	volatile u32 CCER;          // 20
	volatile u32 CNT;           // 24
	volatile u32 PSC;           // 28
	volatile u32 ARR;           // 2C
	volatile u32 RCR;           // 30
	volatile u32 CCR1;          // 34
	volatile u32 CCR2;          // 38
	volatile u32 CCR3;          // 3C
	volatile u32 CCR4;          // 40
	volatile u32 BDTR;          // 44
	volatile u32 DCR;           // 48
	volatile u32 DMAR;          // 4C
}Atim_type;


/* ==================================================================== */
/* =================== Private Variables and Macros =================== */
/* ==================================================================== */

/* ATIM Registers Mapping data type */
#define  TIM1    ((volatile Atim_type*)0x40012C00)

/* CR1 Bits */
#define   ATIM_CEN           0
#define   ATIM_UDIS          1
#define   ATIM_URS           2
#define   ATIM_OPM           3
#define   ATIM_ARPE          7

/* DIER Bits */
#define   ATIM_UIE           0

/* EGR Bits */
#define   ATIM_UG            0

/* SR Bits */
#define   ATIM_UIF           0

/*********** Private Configurations options **********/

/* External Trigger Synchronization Options */
#define   RESET_MODE                 0
#define   GATED_MODE                 1
#define   TRIGGER_MODE               2
#define   EXTERNAL_CLK_TRIGGER_MODE  3

/* Clock Selection options */
#define   CLOCK_INTERNAL_RCC  0
#define   CLOCK_EXTERNAL_TI1  1
#define   CLOCK_EXTERNAL_TI2  2
#define   CLOCK_EXTERNAL_TI3  3
#define   CLOCK_EXTERNAL_TI4  4
#define   CLOCK_EXTERNAL_ETR  4

/* External Trigger Prescaler options */
#define  PRESCALER_1	0
#define  PRESCALER_2	1
#define  PRESCALER_4	2
#define  PRESCALER_8	3

/* Filter Clock options: */
#define  INTERNAL_CLCK_1X 0 
#define  INTERNAL_CLCK_2X 1
#define  INTERNAL_CLCK_4X 2

/* Filter options */
#define  SAMPLING_FDTS          0
#define  SAMPLING_FINT_N2       1
#define  SAMPLING_FINT_N4       2
#define  SAMPLING_FINT_N8       3
#define  SAMPLING_FDTS_DIV2_N6  4
#define  SAMPLING_FDTS_DIV2_N8  5  
#define  SAMPLING_FDTS_DIV4_N6  6
#define  SAMPLING_FDTS_DIV4_N8  7
#define  SAMPLING_FDTS_DIV8_N6  8
#define  SAMPLING_FDTS_DIV8_N8  9
#define  SAMPLING_FDTS_DIV16_N5 10
#define  SAMPLING_FDTS_DIV16_N6 11
#define  SAMPLING_FDTS_DIV16_N8 12
#define  SAMPLING_FDTS_DIV32_N5 13
#define  SAMPLING_FDTS_DIV32_N6 14
#define  SAMPLING_FDTS_DIV32_N8 15

/* Master Slave Configuration options */
#define   TIMER_MASTER  0
#define   TIMER_SLAVE   1  

/* Master Actions */
#define  MASTER_ACTION_RESET_UG            0 
#define  MASTER_ACTION_ENABLE_CEN          1
#define  MASTER_ACTION_UPDATE_UEV          2
#define  MASTER_ACTION_COMPARE_PULSE_CC1IF 3
#define  MASTER_ACTION_COMPARE_OC1REF	   4
#define  MASTER_ACTION_COMPARE_OC2REF	   5
#define  MASTER_ACTION_COMPARE_OC3REF	   6
#define  MASTER_ACTION_COMPARE_OC4REF	   7

/* Slave options */
#define SLAVE_ACTION_DISABLED  0
#define SLAVE_ACTION_ENCODER1  1
#define SLAVE_ACTION_ENCODER2  2
#define SLAVE_ACTION_ENCODER3  3
#define SLAVE_ACTION_RESET     4
#define SLAVE_ACTION_GATED     5
#define SLAVE_ACTION_TRIGGER   6
#define SLAVE_ACTION_EXT_CLCK1 7

/* Trigger Synchronization Selection */
#define  INTERNAL_TRIG_ITR0           0
#define  INTERNAL_TRIG_ITR1           1
#define  INTERNAL_TRIG_ITR2           2
#define  INTERNAL_TRIG_ITR3           3
#define  TI1_EDGE_DETECTOR_TI1F_ED    4
#define  FILTERED_TIMER_INPUT1_TI1FP1 5
#define  FILTERED_TIMER_INPUT2_TI1FP2 6
#define  INTERNAL_TRIG_INPUT_ETRF     7

/* ARR options */
#define ARR_BUFFERD_DISABLED 0
#define ARR_BUFFERD_ENABLED  1

/* Update event private options */
#define UPDATE_EVENT_DISABLED  0
#define UPDATE_EVENT_ENABLED   1

/* Update event source options */
#define UPDATE_EVENT_SOURCE_OVF          0
#define UPDATE_EVENT_SOURCE_OVF_UG_SLV   1

// Callback variables of timer1
void (*TIM1_CH1_CaptureCompareCallback)(void);
void (*TIM1_CH2_CaptureCompareCallback)(void);
void (*TIM1_CH3_CaptureCompareCallback)(void);
void (*TIM1_CH4_CaptureCompareCallback)(void);
void (*TIM1_OverflowCallback)(void);
void (*TIM1_UnderflowCallback)(void);
static u8 Timer1IntervalModeFlag = 0;
static u16 Timer1Prescaler = 0;


#endif
