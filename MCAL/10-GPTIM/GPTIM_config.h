/******************************************************************************
* @file:    GPTIM_config.h
* @author:  Copyright (c) 2023 Gomaa Mohammed Gomaa.
* @license: GNU GPL version 3 or later.
*			This is free software: you are free to change and redistribute it.  
*			There is NO WARRANTY, to the extent permitted by law.
* @version: V0.2   
* @date:    Sun, 15 Oct 2023 14:21:12 +0200
* @brief:   General Purpose Timers(GPTIM) Driver for STM32F103
*******************************************************************************/
#ifndef    _GPTIM_CONFIG_H
#define    _GPTIM_CONFIG_H

/* ==================================================================== */
/* =================== Configurations Selection ======================= */
/* ==================================================================== */

/********************* Timer2 Configurations ************************/

/* TIMER2_CLOCK_SELECTION options: [ CLOCK_INTERNAL_RCC  
                                     CLOCK_EXTERNAL_TI1 
                                     CLOCK_EXTERNAL_TI2 
                                     CLOCK_EXTERNAL_TI3 
                                     CLOCK_EXTERNAL_TI4 
                                     CLOCK_EXTERNAL_ETR ] */   
#define TIMER2_CLOCK_SELECTION  CLOCK_INTERNAL_RCC

/* TIMER2_FILTER_DTS options: [ INTERNAL_CLCK_1X 
                                INTERNAL_CLCK_2X 
                                INTERNAL_CLCK_4X ] */
#define TIMER2_FILTER_DTS  INTERNAL_CLCK_1X

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
#define TIMER2_ETR_FILTER  SAMPLING_FINT_N8
#define TIMER2_TI1_FILTER  SAMPLING_FINT_N8
#define TIMER2_TI2_FILTER  SAMPLING_FINT_N8
#define TIMER2_TI3_FILTER  SAMPLING_FINT_N8
#define TIMER2_TI4_FILTER  SAMPLING_FINT_N8

/* ETR_PRESCALER & TIx_PRESCALER options: [ PRESCALER_1
                                            PRESCALER_2
                                            PRESCALER_4
                                            PRESCALER_8 ] */
#define TIMER2_ETR_PRESCALER  PRESCALER_1
#define TIMER2_TI1_PRESCALER  PRESCALER_1
#define TIMER2_TI2_PRESCALER  PRESCALER_1
#define TIMER2_TI3_PRESCALER  PRESCALER_1
#define TIMER2_TI4_PRESCALER  PRESCALER_1

/* TIMER2_ARR_BUFFERED options: [ ARR_BUFFERD_ENABLED  
                                  ARR_BUFFERD_DISABLED ] */
// Can't be changed Execpt at Update Event
#define TIMER2_ARR_BUFFERED  ARR_BUFFERD_DISABLED 

/* TIMER2_UPDATE_EVENT options: [ UPDATE_EVENT_ENABLED  
                                  UPDATE_EVENT_DISABLED ] */
#define TIMER2_UPDATE_EVENT  UPDATE_EVENT_DISABLED  

/* TIMER2_UPDATE_EVENT_SOURCE: [ UPDATE_EVENT_SOURCE_OVF
                                 UPDATE_EVENT_SOURCE_OVF_UG_SLV ] */
#if  TIMER2_UPDATE_EVENT == UPDATE_EVENT_ENABLED
    #define TIMER2_UPDATE_EVENT_SOURCE   UPDATE_EVENT_SOURCE_OVF_UG_SLV
#endif




/********************* Timer3 Configurations ************************/

/* TIMER3_CLOCK_SELECTION options: [ CLOCK_INTERNAL_RCC  
                                     CLOCK_EXTERNAL_TI1 
                                     CLOCK_EXTERNAL_TI2 
                                     CLOCK_EXTERNAL_TI3 
                                     CLOCK_EXTERNAL_TI4 
                                     CLOCK_EXTERNAL_ETR ] */   
#define TIMER3_CLOCK_SELECTION  CLOCK_INTERNAL_RCC

/* TIMER3_FILTER_DTS options: [ INTERNAL_CLCK_1X 
                                INTERNAL_CLCK_2X 
                                INTERNAL_CLCK_4X ] */
#define TIMER3_FILTER_DTS  INTERNAL_CLCK_1X

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
#define TIMER3_ETR_FILTER  SAMPLING_FDTS
#define TIMER3_TI1_FILTER  SAMPLING_FDTS
#define TIMER3_TI2_FILTER  SAMPLING_FDTS
#define TIMER3_TI3_FILTER  SAMPLING_FDTS
#define TIMER3_TI4_FILTER  SAMPLING_FDTS

/* ETR_PRESCALER & TIx_PRESCALER options: [ PRESCALER_1
                                            PRESCALER_2
                                            PRESCALER_4
                                            PRESCALER_8 ] */
#define TIMER3_ETR_PRESCALER  PRESCALER_1
#define TIMER3_TI1_PRESCALER  PRESCALER_1
#define TIMER3_TI2_PRESCALER  PRESCALER_1
#define TIMER3_TI3_PRESCALER  PRESCALER_1
#define TIMER3_TI4_PRESCALER  PRESCALER_1

/* TIMER3_ARR_BUFFERED options: [ ARR_BUFFERD_ENABLED  
                                  ARR_BUFFERD_DISABLED ] */
// Can't be changed Execpt at Update Event
#define TIMER3_ARR_BUFFERED            ARR_BUFFERD_DISABLED 

/* TIMER3_UPDATE_EVENT options: [ UPDATE_EVENT_ENABLED  
                                  UPDATE_EVENT_DISABLED ] */
#define TIMER3_UPDATE_EVENT            UPDATE_EVENT_DISABLED  

/* TIMER3_UPDATE_EVENT_SOURCE: [ UPDATE_EVENT_SOURCE_OVF
                                 UPDATE_EVENT_SOURCE_OVF_UG_SLV ] */
#if  TIMER3_UPDATE_EVENT == UPDATE_EVENT_ENABLED
    #define TIMER3_UPDATE_EVENT_SOURCE   UPDATE_EVENT_SOURCE_OVF
#endif


/********************* Timer4 Configurations ************************/

/* TIMER4_CLOCK_SELECTION options: [ CLOCK_INTERNAL_RCC  
                                     CLOCK_EXTERNAL_TI1 
                                     CLOCK_EXTERNAL_TI2 
                                     CLOCK_EXTERNAL_TI3 
                                     CLOCK_EXTERNAL_TI4 
                                     CLOCK_EXTERNAL_ETR ] */   
#define TIMER4_CLOCK_SELECTION  CLOCK_INTERNAL_RCC

/* TIMER4_FILTER_DTS options: [ INTERNAL_CLCK_1X 
                                INTERNAL_CLCK_2X 
                                INTERNAL_CLCK_4X ] */
#define TIMER4_FILTER_DTS  INTERNAL_CLCK_1X

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
#define TIMER4_ETR_FILTER  SAMPLING_FDTS
#define TIMER4_TI1_FILTER  SAMPLING_FDTS
#define TIMER4_TI2_FILTER  SAMPLING_FDTS
#define TIMER4_TI3_FILTER  SAMPLING_FDTS
#define TIMER4_TI4_FILTER  SAMPLING_FDTS

/* ETR_PRESCALER & TIx_PRESCALER options: [ PRESCALER_1
                                            PRESCALER_2
                                            PRESCALER_4
                                            PRESCALER_8 ] */
#define TIMER4_ETR_PRESCALER  PRESCALER_1
#define TIMER4_TI1_PRESCALER  PRESCALER_1
#define TIMER4_TI2_PRESCALER  PRESCALER_1
#define TIMER4_TI3_PRESCALER  PRESCALER_1
#define TIMER4_TI4_PRESCALER  PRESCALER_1

/* TIMER4_ARR_BUFFERED options: [ ARR_BUFFERD_ENABLED  
                                  ARR_BUFFERD_DISABLED ] */
// Can't be changed Execpt at Update Event
#define TIMER4_ARR_BUFFERED            ARR_BUFFERD_DISABLED 

/* TIMER4_UPDATE_EVENT options: [ UPDATE_EVENT_ENABLED  
                                  UPDATE_EVENT_DISABLED ] */
#define TIMER4_UPDATE_EVENT            UPDATE_EVENT_DISABLED  

/* TIMER4_UPDATE_EVENT_SOURCE: [ UPDATE_EVENT_SOURCE_OVF
                                 UPDATE_EVENT_SOURCE_OVF_UG_SLV ] */
#if  TIMER4_UPDATE_EVENT == UPDATE_EVENT_ENABLED
    #define TIMER4_UPDATE_EVENT_SOURCE   UPDATE_EVENT_SOURCE_OVF
#endif




/********************* Timer5 Configurations ************************/

/* TIMER5_CLOCK_SELECTION options: [ CLOCK_INTERNAL_RCC  
                                     CLOCK_EXTERNAL_TI1 
                                     CLOCK_EXTERNAL_TI2 
                                     CLOCK_EXTERNAL_TI3 
                                     CLOCK_EXTERNAL_TI4 
                                     CLOCK_EXTERNAL_ETR ] */   
#define TIMER5_CLOCK_SELECTION  CLOCK_INTERNAL_RCC

/* TIMER5_FILTER_DTS options: [ INTERNAL_CLCK_1X 
                                INTERNAL_CLCK_2X 
                                INTERNAL_CLCK_4X ] */
#define TIMER5_FILTER_DTS  INTERNAL_CLCK_1X

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
#define TIMER5_ETR_FILTER  SAMPLING_FDTS
#define TIMER5_TI1_FILTER  SAMPLING_FDTS
#define TIMER5_TI2_FILTER  SAMPLING_FDTS
#define TIMER5_TI3_FILTER  SAMPLING_FDTS
#define TIMER5_TI4_FILTER  SAMPLING_FDTS

/* ETR_PRESCALER & TIx_PRESCALER options: [ PRESCALER_1
                                            PRESCALER_2
                                            PRESCALER_4
                                            PRESCALER_8 ] */
#define TIMER5_ETR_PRESCALER  PRESCALER_1
#define TIMER5_TI1_PRESCALER  PRESCALER_1
#define TIMER5_TI2_PRESCALER  PRESCALER_1
#define TIMER5_TI3_PRESCALER  PRESCALER_1
#define TIMER5_TI4_PRESCALER  PRESCALER_1

/* TIMER5_ARR_BUFFERED options: [ ARR_BUFFERD_ENABLED  
                                  ARR_BUFFERD_DISABLED ] */
// Can't be changed Execpt at Update Event
#define TIMER5_ARR_BUFFERED            ARR_BUFFERD_DISABLED 

/* TIMER5_UPDATE_EVENT options: [ UPDATE_EVENT_ENABLED  
                                  UPDATE_EVENT_DISABLED ] */
#define TIMER5_UPDATE_EVENT            UPDATE_EVENT_DISABLED  

/* TIMER5_UPDATE_EVENT_SOURCE: [ UPDATE_EVENT_SOURCE_OVF
                                 UPDATE_EVENT_SOURCE_OVF_UG_SLV ] */
#if  TIMER5_UPDATE_EVENT == UPDATE_EVENT_ENABLED
    #define TIMER5_UPDATE_EVENT_SOURCE   UPDATE_EVENT_SOURCE_OVF
#endif




#endif
