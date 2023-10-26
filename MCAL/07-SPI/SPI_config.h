/*****************************************************************************
* @file:    SPI_config.h
* @author:  Copyright (c) 2023 Gomaa Mohammed Gomaa.
* @license: GNU GPL version 3 or later.
*		This is free software: you are free to change and redistribute it.  
*		There is NO WARRANTY, to the extent permitted by law.
* @version: V0.2   
* @date:    Sun, 8 Oct 2023 16:55:32 +0200
* @brief:   SPI Driver for STM32F103
******************************************************************************/
#ifndef    _SPI_CONFIG_H
#define    _SPI_CONFIG_H 

/* ==================================================================== */
/* =================== Configurations Selection ======================= */
/* ==================================================================== */

/******* SPI Pins configurations *******/
#define   SPI_MOSI_PORT     GPIOA
#define   SPI_MOSI_PIN      GPIO_PIN7

#define   SPI_MISO_PORT     GPIOA
#define   SPI_MISO_PIN      GPIO_PIN6

#define   SPI_SCK_PORT      GPIOA
#define   SPI_SCK_PIN       GPIO_PIN5

#define   SPI_SS_PORT       GPIOA
#define   SPI_SS_PIN        GPIO_PIN0


/* SPI_MODE Options: [ SPI_MASTER_MODE | SPI_SLAVE_MODE ] */
#define    SPI_MODE     SPI_MASTER_MODE

/* SPI_FIRST_BIT_TO_SEND Options: [ SPI_MSB_FIRST | SPI_LSB_FIRST ] */
#define  SPI_FIRST_BIT_TO_SEND  SPI_MSB_FIRST

/* SPI_DATA_FRAME_FORMAT Otions: [ SPI_8BIT_FORMAT | SPI_16BIT_FORMAT ] */
#define  SPI_DATA_FRAME_FORMAT  SPI_8BIT_FORMAT

/* Baud Rate
Options:
       0b000: fPCLK/2
       0b001: fPCLK/4
       0b010: fPCLK/8
       0b011: fPCLK/16
       0b100: fPCLK/32
       0b101: fPCLK/64
       0b110: fPCLK/128
       0b111: fPCLK/256
 */
#define  SPI_BAUD_RATE   0b000

/* Clock Polarity OPtions : [ SPI_0_POLARITY | SPI_1_POLARITY ] */
#define  SPI_CLOCK_POLARITY   SPI_1_POLARITY

/* Clock Phase Options : [ SPI_SETUP_SAMPLE | SPI_SAMPLE_SETUP ] */
#define  SPI_CLOCK_PHASE      SPI_SETUP_SAMPLE

#endif







