/*****************************************************************************
* @file:    SPI_private.h
* @author:  Copyright (c) 2023 Gomaa Mohammed Gomaa. 
* @license: GNU GPL version 3 or later.
*			This is free software: you are free to change and redistribute it.  
*			There is NO WARRANTY, to the extent permitted by law.
* @version: V0.2   
* @date:    Sun, 8 Oct 2023 16:55:32 +0200
* @brief:   SPI Driver for STM32F103
******************************************************************************/
#ifndef _SPI_PRIVATE_H
#define _SPI_PRIVATE_H

/* ==================================================================== */
/* ======================= private data types ========================= */
/* ==================================================================== */

/* Registers Maping data type */
typedef struct {
	
	volatile u32 CR1;
	volatile u32 CR2;
	volatile u32 SR;
	volatile u32 DR;
	volatile u32 CRCPR;
	volatile u32 RXCRCR;
	volatile u32 TXCRCR;
	volatile u32 I2SCFGR;
	volatile u32 I2SPR;	
}Spi_type;


/* ==================================================================== */
/* =================== Private Variables and Macros =================== */
/* ==================================================================== */

/* Registers Maping */
#define    SPI  ((volatile Spi_type *)(0x40013000))

void (*SPI1_Callback)(void);

/* SPI_MODE OPTIONS */
#define    SPI_MASTER_MODE       0
#define    SPI_SLAVE_MODE        1
/* First Bit To Send */
#define    SPI_MSB_FIRST         0
#define    SPI_LSB_FIRST         1
/* Data Frame Format */
#define    SPI_8BIT_FORMAT       0
#define    SPI_16BIT_FORMAT      1
/* Clock Polarity */
#define    SPI_0_POLARITY        0
#define    SPI_1_POLARITY        1
/* Clock Phase */
#define    SPI_SETUP_SAMPLE  0
#define    SPI_SAMPLE_SETUP  1


#endif
