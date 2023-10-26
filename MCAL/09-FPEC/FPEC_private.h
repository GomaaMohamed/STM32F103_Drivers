/*****************************************************************************
* @file:    FPEC_private.h
* @author:  Copyright (c) 2023 Gomaa Mohammed Gomaa.
* @license: GNU GPL version 3 or later.
*			This is free software: you are free to change and redistribute it.  
*			There is NO WARRANTY, to the extent permitted by law.
* @version: V0.2   
* @date:    Wed, 11 Oct 2023 14:21:12 +0200
* @brief:   FPEC Driver for STM32F103
******************************************************************************/
#ifndef  _FPEC_PRIVATE
#define  _FPEC_PRIVATE

/* ==================================================================== */
/* ======================= private data types ========================= */
/* ==================================================================== */

/* Registers Mapping data types */
typedef union
{
	struct{
		u32  PG    :1 ;
		u32  PER   :1 ;
		u32  MER   :1 ;
		u32  RES1  :1 ;
		u32  OPTPG :1 ;
		u32  OPTER :1 ;
		u32  STRT  :1 ;
		u32  LOCK  :1 ;
		u32  RES2  :1 ;
		u32  OPTWRE:1 ;
		u32  ERRIE :1 ;
		u32  RES3  :1 ;
		u32  EOPIE :1 ;
		u32  RES4  :19;
	}BitAccess;
	
	u32 WordAccess;
}FpecCr_type;

typedef struct
{
	volatile u32 ACR;
	volatile u32 KEYR;
	volatile u32 OPTKEYR;
	volatile u32 SR;
	volatile u32 CR;
	volatile u32 AR;
	volatile u32 RESERVED;
	volatile u32 OBR;
	volatile u32 WRPR;
}Fpec_type;


/* ==================================================================== */
/* =================== Private Variables and Macros =================== */
/* ==================================================================== */

/* Registers Mapping */
#define FPEC_CR ((FpecCr_type*)0x40022010)
#define FPEC ((Fpec_type*)0x40022000)




#endif
