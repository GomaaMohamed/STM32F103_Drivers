/***************************************/
/* Author  :Gomaa                      */
/* Date    :28 Seb 2020                 */
/* Version :V01                        */
/***************************************/
#ifndef FPEC_INTERFACE
#define FPEC_INTERFACE

void FPEC_voidFlashPageErase(u8 Copy_u8PageNumber);

void FPEC_voidEraseNumberOfPages(u8 Copy_u8StartPage, u8 Copy_u8PagesCount);

void FPEC_voidFlashWrite(u32 Copy_u32Address, u16* Copy_u16Data, u8 Copy_u8Length);

#endif
