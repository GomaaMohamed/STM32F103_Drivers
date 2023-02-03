/*********************************************************************************/
/* Author    : Gomaa Mohammed                                                    */
/* Version   : V01                                                               */
/* Date      : 21 Dec 2020                                                       */
/*********************************************************************************/
#ifndef   _CAN_CONFIG_H_
#define   _CAN_CONFIG_H_
/*******************************************************************************************************************************/
/* 
    CAN Standard Or Extended
	OPtions Of CAN_STANDRIZATION:
	CAN_STANDRD
	CAN_EXTENDED
*/
#define   CAN_STANDRIZATION  CAN_STANDRD
/******************************************************************************************************************************/
/*
    Select Wakeup Mode
	Options of CAN_WAKEUP_MODE:
	CAN_AUTOMATIC_WAKEUP_MODE
	CAN_MANUAl_WAKEUP_MODE
 */
#define    CAN_WAKEUP_MODE  CAN_AUTOMATIC_WAKEUP_MODE 
/*********************************************************************************************************************************/
/*
    Select to disable Time Triggered Mode Or not
	Options Of CAN_TIMETRIGGERED_MODE:
	CAN_TIMETRIGGERED_MODE_DISABLED
	CAN_TIMETRIGGERED_MODE_ENABLED
*/
#define   CAN_TIMETRIGGERED_MODE   CAN_TIMETRIGGERED_MODE_DISABLED
/***********************************************************************************************************************************/
/* 
      No automatic retransmission
      Options Of  CAN_RETRANSMISSION:
      CAN_AUTOMATIC_RETRANSMISSION	
      CAN_NOTAUTOMATIC_RETRANSMISSION 	  
*/
#define   CAN_RETRANSMISSION   CAN_AUTOMATIC_RETRANSMISSION
/*************************************************************************************************************************************/
/* 
     Recieve FIFO Locked Mode
	 Options Of CAN_RECIEVE_FIFO:
	 CAN_RECIEVE_FIFO_LOCKED
	 CAN_RECIEVE_FIFO_UNLOCED
*/
#define CAN_RECIEVE_FIFO CAN_RECIEVE_FIFO_UNLOCKED
/***************************************************************************************************************************************/
/*
      Priority Of Mail boxes Transmission
	  Options Of CAN_TRANSMIT_PRIORITY:
	  CAN_TRANSMIT_PRIORITY_ID_BASED
	  CAN_TRANSMIT_PRIORITY_REQUEST_BASED
 */
#define CAN_TRANSMIT_PRIORITY CAN_TRANSMIT_PRIORITY_ID_BASED
/****************************************************************************************************************************************/
/*
    CAN During Debug
	CAN_DURING_DEBUG Options:
	CAN_DURING_DEBUG_ENABLED
	CAN_DURING_DEBUG_DISABLED
 */
#define  CAN_DURING_DEBUG   CAN_DURING_DEBUG_ENABLED
/****************************************************************************************************************************************/
/*
     bus-off management Options
	 BUS_OFF_AUTOMATIC_MANAGEMENT
	 BUS_OFF_NONAUTOMATIC_MANAGEMENT
*/
#define  BUS_OFF_MANAGEMENT  BUS_OFF_AUTOMATIC_MANAGEMENT
/****************************************************************************************************************************************/
/*
    BIT TIMING Configurations:
	to calculate the prameters visit http://www.bittiming.can-wiki.info/ and fill requierments
*/
#define  CAN_BTR_FOR_BIT_TIMING    0x00050000
/*********************************************************************************************************************************************/
/*
  CAN_FILTER_BANKx_ACTIVATION  Options:
  CAN_FILTER_BANK_ACTIVATED
  CAN_FILTER_BANK_NONACTIVATED
*/
#define  CAN_FILTER_BANK0_ACTIVATION    CAN_FILTER_BANK_ACTIVATED
#define  CAN_FILTER_BANK1_ACTIVATION    CAN_FILTER_BANK_NONACTIVATED
#define  CAN_FILTER_BANK2_ACTIVATION    CAN_FILTER_BANK_NONACTIVATED
#define  CAN_FILTER_BANK3_ACTIVATION    CAN_FILTER_BANK_NONACTIVATED
#define  CAN_FILTER_BANK4_ACTIVATION    CAN_FILTER_BANK_NONACTIVATED
#define  CAN_FILTER_BANK5_ACTIVATION    CAN_FILTER_BANK_NONACTIVATED
#define  CAN_FILTER_BANK6_ACTIVATION    CAN_FILTER_BANK_NONACTIVATED
#define  CAN_FILTER_BANK7_ACTIVATION    CAN_FILTER_BANK_NONACTIVATED
#define  CAN_FILTER_BANK8_ACTIVATION    CAN_FILTER_BANK_NONACTIVATED
#define  CAN_FILTER_BANK9_ACTIVATION    CAN_FILTER_BANK_NONACTIVATED
#define  CAN_FILTER_BANK10_ACTIVATION   CAN_FILTER_BANK_NONACTIVATED
#define  CAN_FILTER_BANK11_ACTIVATION   CAN_FILTER_BANK_NONACTIVATED
#define  CAN_FILTER_BANK12_ACTIVATION   CAN_FILTER_BANK_NONACTIVATED
#define  CAN_FILTER_BANK13_ACTIVATION   CAN_FILTER_BANK_NONACTIVATED

/***********************************************************************************************************************************************/
/*
New Messsage Interrupt state
Options Of CAN_NEW_MESSAGE_INTERRUPT_FIFOx:
CAN_NEW_MESSAGE_INTERRUPT_ENABLED 
CAN_NEW_MESSAGE_INTERRUPT_DISABLED
*/
#define  CAN_NEW_MESSAGE_INTERRUPT_FIFO0   CAN_NEW_MESSAGE_INTERRUPT_ENSABLED
#define  CAN_NEW_MESSAGE_INTERRUPT_FIFO1   CAN_NEW_MESSAGE_INTERRUPT_ENSABLED
/****************************************************************************************************************************************/
/* 
    Filters Configurations
	evry filter bank may work in on of this modes
	CAN_FILTER_BANKx_MODE OPtions : x from 0 to 13   
	CAN_ONE_32BIT_FILTER_ID_MASK
	CAN_TWO_32BIT_FILTERS_ID_LIST
	CAN_TWO_16BIT_FILTERS_ID_MASK
	CAN_FOUR_16BIT_FILTER_ID_LIST
*/
#define  CAN_FILTER_BANK0_MODE   CAN_TWO_32BIT_FILTER_ID_LIST
#define  CAN_FILTER_BANK1_MODE   CAN_TWO_32BIT_FILTER_ID_LIST
#define  CAN_FILTER_BANK2_MODE   CAN_TWO_32BIT_FILTER_ID_LIST
#define  CAN_FILTER_BANK3_MODE   CAN_TWO_32BIT_FILTER_ID_LIST
#define  CAN_FILTER_BANK4_MODE   CAN_TWO_32BIT_FILTER_ID_LIST
#define  CAN_FILTER_BANK5_MODE   CAN_TWO_32BIT_FILTER_ID_LIST
#define  CAN_FILTER_BANK6_MODE   CAN_TWO_32BIT_FILTER_ID_LIST
#define  CAN_FILTER_BANK7_MODE   CAN_TWO_32BIT_FILTER_ID_LIST
#define  CAN_FILTER_BANK8_MODE   CAN_TWO_32BIT_FILTER_ID_LIST
#define  CAN_FILTER_BANK9_MODE   CAN_TWO_32BIT_FILTER_ID_LIST
#define  CAN_FILTER_BANK10_MODE  CAN_TWO_32BIT_FILTER_ID_LIST
#define  CAN_FILTER_BANK11_MODE  CAN_TWO_32BIT_FILTER_ID_LIST
#define  CAN_FILTER_BANK12_MODE  CAN_TWO_32BIT_FILTER_ID_LIST
#define  CAN_FILTER_BANK13_MODE  CAN_TWO_32BIT_FILTER_ID_LIST
/*********************************************************************************************************************************************/
/*
  CAN_FILTER_BANKi_ASSIGNMENT Options:
  CAN_FILTER_BANK_ASSIGNED_TO_FIFO0
  CAN_FILTER_BANK_ASSIGNED_TO_FIFO1
*/
#define  CAN_FILTER_BANK0_ASSIGNMENT    CAN_FILTER_BANK_ASSIGNED_TO_FIFO1
#define  CAN_FILTER_BANK1_ASSIGNMENT    CAN_FILTER_BANK_ASSIGNED_TO_FIFO1
#define  CAN_FILTER_BANK2_ASSIGNMENT    CAN_FILTER_BANK_ASSIGNED_TO_FIFO1
#define  CAN_FILTER_BANK3_ASSIGNMENT    CAN_FILTER_BANK_ASSIGNED_TO_FIFO1
#define  CAN_FILTER_BANK4_ASSIGNMENT    CAN_FILTER_BANK_ASSIGNED_TO_FIFO1
#define  CAN_FILTER_BANK5_ASSIGNMENT    CAN_FILTER_BANK_ASSIGNED_TO_FIFO1
#define  CAN_FILTER_BANK6_ASSIGNMENT    CAN_FILTER_BANK_ASSIGNED_TO_FIFO1
#define  CAN_FILTER_BANK7_ASSIGNMENT    CAN_FILTER_BANK_ASSIGNED_TO_FIFO1
#define  CAN_FILTER_BANK8_ASSIGNMENT    CAN_FILTER_BANK_ASSIGNED_TO_FIFO1
#define  CAN_FILTER_BANK9_ASSIGNMENT    CAN_FILTER_BANK_ASSIGNED_TO_FIFO1
#define  CAN_FILTER_BANK10_ASSIGNMENT   CAN_FILTER_BANK_ASSIGNED_TO_FIFO1
#define  CAN_FILTER_BANK11_ASSIGNMENT   CAN_FILTER_BANK_ASSIGNED_TO_FIFO1
#define  CAN_FILTER_BANK12_ASSIGNMENT   CAN_FILTER_BANK_ASSIGNED_TO_FIFO1
#define  CAN_FILTER_BANK13_ASSIGNMENT   CAN_FILTER_BANK_ASSIGNED_TO_FIFO1

/***********************************************************************************************************************************************/
/* ID's Of Filter Banks in all Cases 
  Please Fill The Ids And Masks
*/
/* Filter BANK0 */
#if   CAN_FILTER_BANK0_MODE == CAN_ONE_32BIT_FILTER_ID_MASK
    #define  CAN_FILTER_BANK0_ID0   0   /* Fill 32Bit ID   Mapping :STID[10:3]STID[2:0]EXID[12:5]EXID[4:0] IDE RTR 0 */
    #define  CAN_FILTER_BANK0_MASK0 0 /* Fill 32Bit Mask Mapping :STID[10:3]STID[2:0]EXID[12:5]EXID[4:0] IDE RTR 0 */
#elif  CAN_FILTER_BANK0_MODE == CAN_TWO_32BIT_FILTER_ID_LIST
    #define  CAN_FILTER_BANK0_ID0 303   /* Fill 32Bit ID Mapping :STID[10:3]STID[2:0]EXID[12:5]EXID[4:0] IDE RTR 0 */
    #define  CAN_FILTER_BANK0_ID1 304  /* Fill 32Bit IDMapping  :STID[10:3]STID[2:0]EXID[12:5]EXID[4:0] IDE RTR 0   */
#elif  CAN_FILTER_BANK0_MODE == CAN_TWO_16BIT_FILTERS_ID_MASK
    #define  CAN_FILTER_BANK0_ID0    /* Fill 16Bit ID  Mapping:STID[10:3]STID[2:0] RTR IDE EXID[17:15]  */
    #define  CAN_FILTER_BANK0_MASK0  /* Fill 16Bit MASK Mapping:STID[10:3]STID[2:0] RTR IDE EXID[17:15] */
	#define  CAN_FILTER_BANK0_ID1    /* Fill 16Bit ID Mapping:STID[10:3]STID[2:0] RTR IDE EXID[17:15]   */
    #define  CAN_FILTER_BANK0_MASK1  /* Fill 16Bit MASK Mapping:STID[10:3]STID[2:0] RTR IDE EXID[17:15] */
#elif  CAN_FILTER_BANK0_MODE == CAN_FOUR_16BIT_FILTER_ID_LIST
    #define  CAN_FILTER_BANK0_ID0    /* Fill 16Bit ID Mapping:STID[10:3]STID[2:0] RTR IDE EXID[17:15] */
    #define  CAN_FILTER_BANK0_ID1  /* Fill 16Bit ID Mapping:STID[10:3]STID[2:0] RTR IDE EXID[17:15]   */
	#define  CAN_FILTER_BANK0_ID2    /* Fill 16Bit ID Mapping:STID[10:3]STID[2:0] RTR IDE EXID[17:15] */
    #define  CAN_FILTER_BANK0_ID3  /* Fill 16Bit ID Mapping:STID[10:3]STID[2:0] RTR IDE EXID[17:15]   */
#endif

/* Filter BANK1 */
#if   CAN_FILTER_BANK1_MODE == CAN_ONE_32BIT_FILTER_ID_MASK
    #define  CAN_FILTER_BANK1_ID0    /* Fill 32Bit ID */
    #define  CAN_FILTER_BANK1_MASK0  /* Fill 32Bit Mask */
#elif  CAN_FILTER_BANK1_MODE == CAN_TWO_32BIT_FILTER_ID_LIST
    #define  CAN_FILTER_BANK1_ID0 0   /* Fill 32Bit ID */
    #define  CAN_FILTER_BANK1_ID1  0/* Fill 32Bit ID */
#elif  CAN_FILTER_BANK1_MODE == CAN_TWO_16BIT_FILTERS_ID_MASK
    #define  CAN_FILTER_BANK1_ID0    /* Fill 16Bit ID */
    #define  CAN_FILTER_BANK1_MASK0  /* Fill 16Bit MASK */
	#define  CAN_FILTER_BANK1_ID1    /* Fill 16Bit ID */
    #define  CAN_FILTER_BANK1_MASK1  /* Fill 16Bit MASK */
#elif  CAN_FILTER_BANK1_MODE == CAN_FOUR_16BIT_FILTER_ID_LIST
    #define  CAN_FILTER_BANK1_ID0    /* Fill 16Bit ID */
    #define  CAN_FILTER_BANK1_ID1  /* Fill 16Bit ID */
	#define  CAN_FILTER_BANK1_ID2    /* Fill 16Bit ID */
    #define  CAN_FILTER_BANK1_ID3  /* Fill 16Bit ID */
#endif

/* Filter BANK2 */
#if   CAN_FILTER_BANK2_MODE == CAN_ONE_32BIT_FILTER_ID_MASK
    #define  CAN_FILTER_BANK2_ID0    /* Fill 32Bit ID */
    #define  CAN_FILTER_BANK2_MASK0  /* Fill 32Bit Mask */
#elif  CAN_FILTER_BANK2_MODE == CAN_TWO_32BIT_FILTER_ID_LIST
    #define  CAN_FILTER_BANK2_ID0 0   /* Fill 32Bit ID */
    #define  CAN_FILTER_BANK2_ID1 0 /* Fill 32Bit ID */
#elif  CAN_FILTER_BANK2_MODE == CAN_TWO_16BIT_FILTERS_ID_MASK
    #define  CAN_FILTER_BANK2_ID0    /* Fill 16Bit ID */
    #define  CAN_FILTER_BANK2_MASK0  /* Fill 16Bit MASK */
	#define  CAN_FILTER_BANK2_ID1    /* Fill 16Bit ID */
    #define  CAN_FILTER_BANK2_MASK1  /* Fill 16Bit MASK */
#elif  CAN_FILTER_BANK2_MODE == CAN_FOUR_16BIT_FILTER_ID_LIST
    #define  CAN_FILTER_BANK2_ID0    /* Fill 16Bit ID */
    #define  CAN_FILTER_BANK2_ID1  /* Fill 16Bit ID */
	#define  CAN_FILTER_BANK2_ID2    /* Fill 16Bit ID */
    #define  CAN_FILTER_BANK2_ID3  /* Fill 16Bit ID */
#endif


/* Filter BANK3 */
#if   CAN_FILTER_BANK3_MODE == CAN_ONE_32BIT_FILTER_ID_MASK
    #define  CAN_FILTER_BANK3_ID0    /* Fill 32Bit ID */
    #define  CAN_FILTER_BANK3_MASK0  /* Fill 32Bit Mask */
#elif  CAN_FILTER_BANK3_MODE == CAN_TWO_32BIT_FILTER_ID_LIST
    #define  CAN_FILTER_BANK3_ID0  0  /* Fill 32Bit ID */
    #define  CAN_FILTER_BANK3_ID1  0/* Fill 32Bit ID */
#elif  CAN_FILTER_BANK3_MODE == CAN_TWO_16BIT_FILTERS_ID_MASK
    #define  CAN_FILTER_BANK3_ID0    /* Fill 16Bit ID */
    #define  CAN_FILTER_BANK3_MASK0  /* Fill 16Bit MASK */
	#define  CAN_FILTER_BANK3_ID1    /* Fill 16Bit ID */
    #define  CAN_FILTER_BANK3_MASK1  /* Fill 16Bit MASK */
#elif  CAN_FILTER_BANK3_MODE == CAN_FOUR_16BIT_FILTER_ID_LIST
    #define  CAN_FILTER_BANK3_ID0    /* Fill 16Bit ID */
    #define  CAN_FILTER_BANK3_ID1  /* Fill 16Bit ID */
	#define  CAN_FILTER_BANK3_ID2    /* Fill 16Bit ID */
    #define  CAN_FILTER_BANK3_ID3  /* Fill 16Bit ID */
#endif


/* Filter BANK4 */
#if   CAN_FILTER_BANK4_MODE == CAN_ONE_32BIT_FILTER_ID_MASK
    #define  CAN_FILTER_BANK4_ID0    /* Fill 32Bit ID */
    #define  CAN_FILTER_BANK4_MASK0  /* Fill 32Bit Mask */
#elif  CAN_FILTER_BANK4_MODE == CAN_TWO_32BIT_FILTER_ID_LIST
    #define  CAN_FILTER_BANK4_ID0  0  /* Fill 32Bit ID */
    #define  CAN_FILTER_BANK4_ID1 0 /* Fill 32Bit ID */
#elif  CAN_FILTER_BANK4_MODE == CAN_TWO_16BIT_FILTERS_ID_MASK
    #define  CAN_FILTER_BANK4_ID0    /* Fill 16Bit ID */
    #define  CAN_FILTER_BANK4_MASK0  /* Fill 16Bit MASK */
	#define  CAN_FILTER_BANK4_ID1    /* Fill 16Bit ID */
    #define  CAN_FILTER_BANK4_MASK1  /* Fill 16Bit MASK */
#elif  CAN_FILTER_BANK4_MODE == CAN_FOUR_16BIT_FILTER_ID_LIST
    #define  CAN_FILTER_BANK4_ID0    /* Fill 16Bit ID */
    #define  CAN_FILTER_BANK4_ID1  /* Fill 16Bit ID */
	#define  CAN_FILTER_BANK4_ID2    /* Fill 16Bit ID */
    #define  CAN_FILTER_BANK4_ID3  /* Fill 16Bit ID */
#endif


/* Filter BANK5 */
#if   CAN_FILTER_BANK5_MODE == CAN_ONE_32BIT_FILTER_ID_MASK
    #define  CAN_FILTER_BANK5_ID0    /* Fill 32Bit ID */
    #define  CAN_FILTER_BANK5_MASK0  /* Fill 32Bit Mask */
#elif  CAN_FILTER_BANK5_MODE == CAN_TWO_32BIT_FILTER_ID_LIST
    #define  CAN_FILTER_BANK5_ID0  0  /* Fill 32Bit ID */
    #define  CAN_FILTER_BANK5_ID1  0/* Fill 32Bit ID */
#elif  CAN_FILTER_BANK5_MODE == CAN_TWO_16BIT_FILTERS_ID_MASK
    #define  CAN_FILTER_BANK5_ID0    /* Fill 16Bit ID */
    #define  CAN_FILTER_BANK5_MASK0  /* Fill 16Bit MASK */
	#define  CAN_FILTER_BANK5_ID1    /* Fill 16Bit ID */
    #define  CAN_FILTER_BANK5_MASK1  /* Fill 16Bit MASK */
#elif  CAN_FILTER_BANK5_MODE == CAN_FOUR_16BIT_FILTER_ID_LIST
    #define  CAN_FILTER_BANK5_ID0    /* Fill 16Bit ID */
    #define  CAN_FILTER_BANK5_ID1  /* Fill 16Bit ID */
	#define  CAN_FILTER_BANK5_ID2    /* Fill 16Bit ID */
    #define  CAN_FILTER_BANK5_ID3  /* Fill 16Bit ID */
#endif


/* Filter BANK6 */
#if   CAN_FILTER_BANK6_MODE == CAN_ONE_32BIT_FILTER_ID_MASK
    #define  CAN_FILTER_BANK6_ID0    /* Fill 32Bit ID */
    #define  CAN_FILTER_BANK6_MASK0  /* Fill 32Bit Mask */
#elif  CAN_FILTER_BANK6_MODE == CAN_TWO_32BIT_FILTER_ID_LIST
    #define  CAN_FILTER_BANK6_ID0   0 /* Fill 32Bit ID */
    #define  CAN_FILTER_BANK6_ID1  0/* Fill 32Bit ID */
#elif  CAN_FILTER_BANK6_MODE == CAN_TWO_16BIT_FILTERS_ID_MASK
    #define  CAN_FILTER_BANK6_ID0    /* Fill 16Bit ID */
    #define  CAN_FILTER_BANK6_MASK0  /* Fill 16Bit MASK */
	#define  CAN_FILTER_BANK6_ID1    /* Fill 16Bit ID */
    #define  CAN_FILTER_BANK6_MASK1  /* Fill 16Bit MASK */
#elif  CAN_FILTER_BANK6_MODE == CAN_FOUR_16BIT_FILTER_ID_LIST
    #define  CAN_FILTER_BANK6_ID0    /* Fill 16Bit ID */
    #define  CAN_FILTER_BANK6_ID1  /* Fill 16Bit ID */
	#define  CAN_FILTER_BANK6_ID2    /* Fill 16Bit ID */
    #define  CAN_FILTER_BANK6_ID3  /* Fill 16Bit ID */
#endif


/* Filter BANK7 */
#if   CAN_FILTER_BANK7_MODE == CAN_ONE_32BIT_FILTER_ID_MASK
    #define  CAN_FILTER_BANK7_ID0    /* Fill 32Bit ID */
    #define  CAN_FILTER_BANK7_MASK0  /* Fill 32Bit Mask */
#elif  CAN_FILTER_BANK7_MODE == CAN_TWO_32BIT_FILTER_ID_LIST
    #define  CAN_FILTER_BANK7_ID0   0 /* Fill 32Bit ID */
    #define  CAN_FILTER_BANK7_ID1  0/* Fill 32Bit ID */
#elif  CAN_FILTER_BANK7_MODE == CAN_TWO_16BIT_FILTERS_ID_MASK
    #define  CAN_FILTER_BANK7_ID0    /* Fill 16Bit ID */
    #define  CAN_FILTER_BANK7_MASK0  /* Fill 16Bit MASK */
	#define  CAN_FILTER_BANK7_ID1    /* Fill 16Bit ID */
    #define  CAN_FILTER_BANK7_MASK1  /* Fill 16Bit MASK */
#elif  CAN_FILTER_BANK7_MODE == CAN_FOUR_16BIT_FILTER_ID_LIST
    #define  CAN_FILTER_BANK7_ID0    /* Fill 16Bit ID */
    #define  CAN_FILTER_BANK7_ID1  /* Fill 16Bit ID */
	#define  CAN_FILTER_BANK7_ID2    /* Fill 16Bit ID */
    #define  CAN_FILTER_BANK7_ID3  /* Fill 16Bit ID */
#endif


/* Filter BANK8 */
#if   CAN_FILTER_BANK8_MODE == CAN_ONE_32BIT_FILTER_ID_MASK
    #define  CAN_FILTER_BANK8_ID0    /* Fill 32Bit ID */
    #define  CAN_FILTER_BANK8_MASK0  /* Fill 32Bit Mask */
#elif  CAN_FILTER_BANK8_MODE == CAN_TWO_32BIT_FILTER_ID_LIST
    #define  CAN_FILTER_BANK8_ID0   0 /* Fill 32Bit ID */
    #define  CAN_FILTER_BANK8_ID1  0/* Fill 32Bit ID */
#elif  CAN_FILTER_BANK8_MODE == CAN_TWO_16BIT_FILTERS_ID_MASK
    #define  CAN_FILTER_BANK8_ID0    /* Fill 16Bit ID */
    #define  CAN_FILTER_BANK8_MASK0  /* Fill 16Bit MASK */
	#define  CAN_FILTER_BANK8_ID1    /* Fill 16Bit ID */
    #define  CAN_FILTER_BANK8_MASK1  /* Fill 16Bit MASK */
#elif  CAN_FILTER_BANK8_MODE == CAN_FOUR_16BIT_FILTER_ID_LIST
    #define  CAN_FILTER_BANK8_ID0    /* Fill 16Bit ID */
    #define  CAN_FILTER_BANK8_ID1  /* Fill 16Bit ID */
	#define  CAN_FILTER_BANK8_ID2    /* Fill 16Bit ID */
    #define  CAN_FILTER_BANK8_ID3  /* Fill 16Bit ID */
#endif


/* Filter BANK9 */
#if   CAN_FILTER_BANK9_MODE == CAN_ONE_32BIT_FILTER_ID_MASK
    #define  CAN_FILTER_BANK9_ID0    /* Fill 32Bit ID */
    #define  CAN_FILTER_BANK9_MASK0  /* Fill 32Bit Mask */
#elif  CAN_FILTER_BANK9_MODE == CAN_TWO_32BIT_FILTER_ID_LIST
    #define  CAN_FILTER_BANK9_ID0   0 /* Fill 32Bit ID */
    #define  CAN_FILTER_BANK9_ID1  0/* Fill 32Bit ID */
#elif  CAN_FILTER_BANK9_MODE == CAN_TWO_16BIT_FILTERS_ID_MASK
    #define  CAN_FILTER_BANK9_ID0    /* Fill 16Bit ID */
    #define  CAN_FILTER_BANK9_MASK0  /* Fill 16Bit MASK */
	#define  CAN_FILTER_BANK9_ID1    /* Fill 16Bit ID */
    #define  CAN_FILTER_BANK9_MASK1  /* Fill 16Bit MASK */
#elif  CAN_FILTER_BANK9_MODE == CAN_FOUR_16BIT_FILTER_ID_LIST
    #define  CAN_FILTER_BANK9_ID0    /* Fill 16Bit ID */
    #define  CAN_FILTER_BANK9_ID1  /* Fill 16Bit ID */
	#define  CAN_FILTER_BANK9_ID2    /* Fill 16Bit ID */
    #define  CAN_FILTER_BANK9_ID3  /* Fill 16Bit ID */
#endif


/* Filter BANK10 */
#if   CAN_FILTER_BANK10_MODE == CAN_ONE_32BIT_FILTER_ID_MASK
    #define  CAN_FILTER_BANK10_ID0    /* Fill 32Bit ID */
    #define  CAN_FILTER_BANK10_MASK0  /* Fill 32Bit Mask */
#elif  CAN_FILTER_BANK10_MODE == CAN_TWO_32BIT_FILTER_ID_LIST
    #define  CAN_FILTER_BANK10_ID0  0  /* Fill 32Bit ID */
    #define  CAN_FILTER_BANK10_ID1  0/* Fill 32Bit ID */
#elif  CAN_FILTER_BANK10_MODE == CAN_TWO_16BIT_FILTERS_ID_MASK
    #define  CAN_FILTER_BANK10_ID0    /* Fill 16Bit ID */
    #define  CAN_FILTER_BANK10_MASK0  /* Fill 16Bit MASK */
	#define  CAN_FILTER_BANK10_ID1    /* Fill 16Bit ID */
    #define  CAN_FILTER_BANK10_MASK1  /* Fill 16Bit MASK */
#elif  CAN_FILTER_BANK10_MODE == CAN_FOUR_16BIT_FILTER_ID_LIST
    #define  CAN_FILTER_BANK10_ID0    /* Fill 16Bit ID */
    #define  CAN_FILTER_BANK10_ID1  /* Fill 16Bit ID */
	#define  CAN_FILTER_BANK10_ID2    /* Fill 16Bit ID */
    #define  CAN_FILTER_BANK10_ID3  /* Fill 16Bit ID */
#endif


/* Filter BANK11 */
#if   CAN_FILTER_BANK11_MODE == CAN_ONE_32BIT_FILTER_ID_MASK
    #define  CAN_FILTER_BANK11_ID0    /* Fill 32Bit ID */
    #define  CAN_FILTER_BANK11_MASK0  /* Fill 32Bit Mask */
#elif  CAN_FILTER_BANK11_MODE == CAN_TWO_32BIT_FILTER_ID_LIST
    #define  CAN_FILTER_BANK11_ID0   0 /* Fill 32Bit ID */
    #define  CAN_FILTER_BANK11_ID1  0/* Fill 32Bit ID */
#elif  CAN_FILTER_BANK11_MODE == CAN_TWO_16BIT_FILTERS_ID_MASK
    #define  CAN_FILTER_BANK11_ID0    /* Fill 16Bit ID */
    #define  CAN_FILTER_BANK11_MASK0  /* Fill 16Bit MASK */
	#define  CAN_FILTER_BANK11_ID1    /* Fill 16Bit ID */
    #define  CAN_FILTER_BANK11_MASK1  /* Fill 16Bit MASK */
#elif  CAN_FILTER_BANK11_MODE == CAN_FOUR_16BIT_FILTER_ID_LIST
    #define  CAN_FILTER_BANK11_ID0    /* Fill 16Bit ID */
    #define  CAN_FILTER_BANK11_ID1  /* Fill 16Bit ID */
	#define  CAN_FILTER_BANK11_ID2    /* Fill 16Bit ID */
    #define  CAN_FILTER_BANK11_ID3  /* Fill 16Bit ID */
#endif


/* Filter BANK12 */
#if   CAN_FILTER_BANK12_MODE == CAN_ONE_32BIT_FILTER_ID_MASK
    #define  CAN_FILTER_BANK12_ID0    /* Fill 32Bit ID */
    #define  CAN_FILTER_BANK12_MASK0  /* Fill 32Bit Mask */
#elif  CAN_FILTER_BANK12_MODE == CAN_TWO_32BIT_FILTER_ID_LIST
    #define  CAN_FILTER_BANK12_ID0   0 /* Fill 32Bit ID */
    #define  CAN_FILTER_BANK12_ID1  0/* Fill 32Bit ID */
#elif  CAN_FILTER_BANK12_MODE == CAN_TWO_16BIT_FILTERS_ID_MASK
    #define  CAN_FILTER_BANK12_ID0    /* Fill 16Bit ID */
    #define  CAN_FILTER_BANK12_MASK0  /* Fill 16Bit MASK */
	#define  CAN_FILTER_BANK12_ID1    /* Fill 16Bit ID */
    #define  CAN_FILTER_BANK12_MASK1  /* Fill 16Bit MASK */
#elif  CAN_FILTER_BANK12_MODE == CAN_FOUR_16BIT_FILTER_ID_LIST
    #define  CAN_FILTER_BANK12_ID0    /* Fill 16Bit ID */
    #define  CAN_FILTER_BANK12_ID1  /* Fill 16Bit ID */
	#define  CAN_FILTER_BANK12_ID2    /* Fill 16Bit ID */
    #define  CAN_FILTER_BANK12_ID3  /* Fill 16Bit ID */
#endif

/* Filter BANK13 */
#if   CAN_FILTER_BANK13_MODE == CAN_ONE_32BIT_FILTER_ID_MASK
    #define  CAN_FILTER_BANK13_ID0    /* Fill 32Bit ID */
    #define  CAN_FILTER_BANK13_MASK0  /* Fill 32Bit Mask */
#elif  CAN_FILTER_BANK13_MODE == CAN_TWO_32BIT_FILTER_ID_LIST
    #define  CAN_FILTER_BANK13_ID0   0 /* Fill 32Bit ID */
    #define  CAN_FILTER_BANK13_ID1  0/* Fill 32Bit ID */
#elif  CAN_FILTER_BANK13_MODE == CAN_TWO_16BIT_FILTERS_ID_MASK
    #define  CAN_FILTER_BANK13_ID0    /* Fill 16Bit ID */
    #define  CAN_FILTER_BANK13_MASK0  /* Fill 16Bit MASK */
	#define  CAN_FILTER_BANK13_ID1    /* Fill 16Bit ID */
    #define  CAN_FILTER_BANK13_MASK1  /* Fill 16Bit MASK */
#elif  CAN_FILTER_BANK13_MODE == CAN_FOUR_16BIT_FILTER_ID_LIST
    #define  CAN_FILTER_BANK13_ID0    /* Fill 16Bit ID */
    #define  CAN_FILTER_BANK13_ID1  /* Fill 16Bit ID */
	#define  CAN_FILTER_BANK13_ID2    /* Fill 16Bit ID */
    #define  CAN_FILTER_BANK13_ID3  /* Fill 16Bit ID */
#endif




#endif
