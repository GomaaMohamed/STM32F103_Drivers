/*****************************************************************************
* @file:    FPEC_interface.h
* @author:  Copyright (c) 2023 Gomaa Mohammed Gomaa.
* @license: GNU GPL version 3 or later.
*			This is free software: you are free to change and redistribute it.  
*			There is NO WARRANTY, to the extent permitted by law.
* @version: V0.2   
* @date:    Wed, 11 Oct 2023 14:21:12 +0200
* @brief:   FPEC Driver for STM32F103
******************************************************************************/
#ifndef  _FPEC_INTERFACE
#define  _FPEC_INTERFACE


/* ==================================================================== */
/* ==================== Public Functions Declaration ================== */
/* ==================================================================== */

/**
 * @brief---------------------> Erase flash page
 * @parameter1----------------> (PageNumber) number of page to be erased
 * @return--------------------> None
 * @preconditions-------------> None
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Reentrant       
 */
void FPEC_eraseFlashPage(u8 PageNumber);

/**
 * @brief---------------------> Erase number of flash pages
 * @parameter1----------------> (StartPage) start page
 * @parameter2----------------> (PagesCount) number of pages to be erased
 * @return--------------------> None
 * @preconditions-------------> None
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Reentrant     
 */
void FPEC_eraseNumberOfPages(u8 StartPage, u8 PagesCount);

/**
 * @brief---------------------> Write half array of half words at flash
 * @parameter1----------------> (Address) Address of the first half word
 * @parameter2----------------> (Data) array of half words
 * @parameter3----------------> (Length) number of half words
 * @return--------------------> None
 * @preconditions-------------> None
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Non-Reentrant      
 */
void FPEC_writeFlash(u32 Address, u16* Data, u8 Length);


#endif
