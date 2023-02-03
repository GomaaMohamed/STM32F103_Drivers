/***************************************/
/* Author  :Gomaa                      */
/* Date    :16 Seb 2020                 */
/* Version :V01                        */
/***************************************/

#ifndef    _SPI_CONFIG_H_
#define    _SPI_CONFIG_H_ 

/* SPI Pins Select Port and Pins inpairs*/
#define    SPI_MOSI_PIN            GPIOA,GPIO_PIN7
#define    SPI_MISO_PIN            GPIOA,GPIO_PIN6
#define    SPI_SCK_PIN             GPIOA,GPIO_PIN5
#define    SPI_SLAVE_SELECT_PIN    GPIOA,GPIO_PIN0




/* define SPI_MODE Options:
   SPI_MASTER_MODE
   SPI_SLAVE_MODE
 */
#define    SPI_MODE     SPI_MASTER_MODE

/* First Bit that Will be send from Data Frame 
   Options:
   SPI_MSB_FIRST
   SPI_LSB_FIRST
*/
#define  SPI_FIRST_BIT_TO_SEND  SPI_MSB_FIRST

/* Bits Number In The Data Frame
  Otions:
  SPI_8BIT_FORMAT
  SPI_16BIT_FORMAT
 */
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

/* Clock Polarity
  OPtions :
  SPI_0_POLARITY
  SPI_1_POLARITY
 */
#define  SPI_CLOCK_POLARITY   SPI_1_POLARITY
/* Clock Phase
  Options :
  SPI_SETUP_SAMPLE
  SPI_SAMPLE_SETUP
 */
#define  SPI_CLOCK_PHASE      SPI_SETUP_SAMPLE
#endif







