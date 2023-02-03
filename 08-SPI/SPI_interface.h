/***************************************/
/* Author  :Gomaa                      */
/* Date    :16 Seb 2020                 */
/* Version :V01                        */
/***************************************/

#ifndef _SPI_INTERFACE_H_
#define _SPI_INTERFACE_H_

void SPI_voidInit(void);
void SPI_voidSendReceiveSynch(u8 Copy_u8DataToSend,u8 *Copy_u8DataToReceive);
void SPI_voidSendReceiveAsynch(u8 Copy_u8DataToSend,void  (*CallBack)(u8));



#endif