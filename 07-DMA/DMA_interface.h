/***************************************/
/* Author  :Gomaa                      */
/* Date    :14 Seb 2020                 */
/* Version :V01                        */
/***************************************/

#ifndef _DMA_INTERFACE_H_
#define _DMA_INTERFACE_H_

void DMA_voidChannelInit(void);
void DMA_voidChannelStart(u32 Copy_u32SourceAdress,u32 Copy_u32DestinationAdress,u16 Copy_u16BlockLength,Copy_u8CircularEnable);



#endif