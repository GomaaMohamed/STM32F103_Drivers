/***************************************/
/* Author  :Gomaa                      */
/* Date    :16 Seb 2020                 */
/* Version :V01                        */
/***************************************/

#ifndef _SPI_PRIVATE_H_
#define _SPI_PRIVATE_H_
void (*SPI1_CallBack)(u8);
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
	
}spi_t;
#define    SPI  ((volatile spi_t *)(0x40013000))

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
