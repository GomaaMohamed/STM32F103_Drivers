/******************************************************************************
* @file:    GPTIM_config.h
* @author:  Copyright (c) 2023 Gomaa Mohammed Gomaa.
* @license: GNU GPL version 3 or later.
*			This is free software: you are free to change and redistribute it.  
*			There is NO WARRANTY, to the extent permitted by law.
* @version: V0.2   
* @date:    Tue, 17 Aug 2023 21:35:12 +0200
* @brief:   Advanced Timers(ATIM) Driver for STM32F103
*******************************************************************************/
#ifndef    _ATIM_CONFIG_H
#define    _ATIM_CONFIG_H

/* ==================================================================== */
/* =================== Configurations Selection ======================= */
/* ==================================================================== */

/********************* Timer1 Configurations ************************/

/* TIMER1_CLOCK_SELECTION options: [ CLOCK_INTERNAL_RCC  
                                     CLOCK_EXTERNAL_TI1 
                                     CLOCK_EXTERNAL_TI2 
                                     CLOCK_EXTERNAL_TI3 
                                     CLOCK_EXTERNAL_TI4 
                                     CLOCK_EXTERNAL_ETR ] */   
#define TIMER1_CLOCK_SELECTION  CLOCK_INTERNAL_RCC

/* TIMER1_FILTER_DTS options: [ INTERNAL_CLCK_1X 
                                INTERNAL_CLCK_2X 
                                INTERNAL_CLCK_4X ] */
#define TIMER1_FILTER_DTS  INTERNAL_CLCK_1X

/* ETR_FILTER & TIx_FILTER options: [ SAMPLING_FDTS
                                      SAMPLING_FINT_N2
                                      SAMPLING_FINT_N4
                                      SAMPLING_FINT_N8 
                                      SAMPLING_FDTS_DIV2_N6
                                      SAMPLING_FDTS_DIV2_N8
                                      SAMPLING_FDTS_DIV4_N6
                                      SAMPLING_FDTS_DIV4_N8
                                      SAMPLING_FDTS_DIV8_N6
                                      SAMPLING_FDTS_DIV8_N8 
                                      SAMPLING_FDTS_DIV16_N5
                                      SAMPLING_FDTS_DIV16_N6
                                      SAMPLING_FDTS_DIV16_N8 
                                      SAMPLING_FDTS_DIV32_N5
                                      SAMPLING_FDTS_DIV32_N6
                                      SAMPLING_FDTS_DIV32_N8 ] */
#define TIMER1_ETR_FILTER  SAMPLING_FINT_N8
#define TIMER1_TI1_FILTER  SAMPLING_FINT_N8
#define TIMER1_TI2_FILTER  SAMPLING_FINT_N8
#define TIMER1_TI3_FILTER  SAMPLING_FINT_N8
#define TIMER1_TI4_FILTER  SAMPLING_FINT_N8

/* ETR_PRESCALER & TIx_PRESCALER options: [ PRESCALER_1
                                            PRESCALER_2
                                            PRESCALER_4
                                            PRESCALER_8 ] */
#define TIMER1_ETR_PRESCALER  PRESCALER_1
#define TIMER1_TI1_PRESCALER  PRESCALER_1
#define TIMER1_TI2_PRESCALER  PRESCALER_1
#define TIMER1_TI3_PRESCALER  PRESCALER_1
#define TIMER1_TI4_PRESCALER  PRESCALER_1

/* TIMER1_ARR_BUFFERED options: [ ARR_BUFFERD_ENABLED  
                                  ARR_BUFFERD_DISABLED ] */
// Can't be changed Execpt at Update Event
#define TIMER1_ARR_BUFFERED  ARR_BUFFERD_DISABLED 

/* TIMER1_UPDATE_EVENT options: [ UPDATE_EVENT_ENABLED  
                                  UPDATE_EVENT_DISABLED ] */
#define TIMER1_UPDATE_EVENT  UPDATE_EVENT_DISABLED  

/* TIMER1_UPDATE_EVENT_SOURCE: [ UPDATE_EVENT_SOURCE_OVF
                                 UPDATE_EVENT_SOURCE_OVF_UG_SLV ] */
#if  TIMER1_UPDATE_EVENT == UPDATE_EVENT_ENABLED
    #define TIMER1_UPDATE_EVENT_SOURCE   UPDATE_EVENT_SOURCE_OVF_UG_SLV
#endif

#endif