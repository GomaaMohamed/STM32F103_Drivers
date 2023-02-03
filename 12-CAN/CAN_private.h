/*********************************************************************************/
/* Author    : Gomaa Mohammed                                                    */
/* Version   : V01                                                               */
/* Date      : 21 Dec 2020                                                       */
/*********************************************************************************/
#ifndef    _CAN_PRIVATE_H_
#define    _CAN_PRIVATE_H_



/************************************************Private Functions & Variables Of CAN Driver**************************************************/
/* Current Mode Of CAN Controller Flag  sleep = 0, initialization = 1, Normal = 2 */
static volatile u8 Copy_u8CurrentModeFlag = 0;

/* CallBack */
void(*CAN1_CallBack)(void);

/* Configuration Of Filters */
static void CAN_voidFiltersConfig(void);
/************************************************Registers Definition Of CAN Module************************************************************/
/* CAN1 BASE ADRESS */
#define  CAN1_BASE  0x40006400

/* Transmitter & Reciever Control Registers */
#define  CAN_MCR    *((volatile u32 *)(CAN1_BASE+0x000))
#define  CAN_MSR    *((volatile u32 *)(CAN1_BASE+0x004)) 
#define  CAN_TSR    *((volatile u32 *)(CAN1_BASE+0x008)) 
#define  CAN_RF0R   *((volatile u32 *)(CAN1_BASE+0x00C)) 
#define  CAN_RF1R   *((volatile u32 *)(CAN1_BASE+0x010)) 
#define  CAN_IER    *((volatile u32 *)(CAN1_BASE+0x014)) 
#define  CAN_ESR    *((volatile u32 *)(CAN1_BASE+0x018)) 
#define  CAN_BTR    *((volatile u32 *)(CAN1_BASE+0x01C))
 
 /* Transmitter Registers */
#define  CAN_TI0R   *((volatile u32 *)(CAN1_BASE+0x180)) 
#define  CAN_TDT0R  *((volatile u32 *)(CAN1_BASE+0x184)) 
#define  CAN_TDL0R  *((volatile u32 *)(CAN1_BASE+0x188))			    
#define  CAN_TDH0R  *((volatile u32 *)(CAN1_BASE+0x18C))

#define  CAN_TI1R   *((volatile u32 *)(CAN1_BASE+0x190))
#define  CAN_TDT1R  *((volatile u32 *)(CAN1_BASE+0x194))
#define  CAN_TDL1R  *((volatile u32 *)(CAN1_BASE+0x198))
#define  CAN_TDH1R  *((volatile u32 *)(CAN1_BASE+0x19C))

#define  CAN_TI2R   *((volatile u32 *)(CAN1_BASE+0x1A0))
#define  CAN_TDT2R  *((volatile u32 *)(CAN1_BASE+0x1A4))
#define  CAN_TDL2R  *((volatile u32 *)(CAN1_BASE+0x1A8))
#define  CAN_TDH2R  *((volatile u32 *)(CAN1_BASE+0x1AC))

/* Reciever Registers */
#define  CAN_RI0R   *((volatile u32 *)(CAN1_BASE+0x1B0))
#define  CAN_RDT0R  *((volatile u32 *)(CAN1_BASE+0x1B4))
#define  CAN_RDL0R  *((volatile u32 *)(CAN1_BASE+0x1B8))
#define  CAN_RDH0R  *((volatile u32 *)(CAN1_BASE+0x1BC))

#define  CAN_RI1R   *((volatile u32 *)(CAN1_BASE+0x1C0))				    
#define  CAN_RDT1R  *((volatile u32 *)(CAN1_BASE+0x1C4))
#define  CAN_RDL1R  *((volatile u32 *)(CAN1_BASE+0x1C8))
#define  CAN_RDH1R  *((volatile u32 *)(CAN1_BASE+0x1CC))

/* Filter Control Registers */
#define  CAN_FMR    *((volatile u32 *)(CAN1_BASE+0x200))
#define  CAN_FM1R   *((volatile u32 *)(CAN1_BASE+0x204))
#define  CAN_FS1R   *((volatile u32 *)(CAN1_BASE+0x20C))
#define  CAN_FFA1R  *((volatile u32 *)(CAN1_BASE+0x214))
#define  CAN_FA1R   *((volatile u32 *)(CAN1_BASE+0x21C))

/* Filter Registers */				    
#define  CAN_F0R1   *((volatile u32 *)(CAN1_BASE+0x240))
#define  CAN_F0R2   *((volatile u32 *)(CAN1_BASE+0x244))
#define  CAN_F1R1   *((volatile u32 *)(CAN1_BASE+0x248))
#define  CAN_F1R2   *((volatile u32 *)(CAN1_BASE+0x24C))
#define  CAN_F2R1   *((volatile u32 *)(CAN1_BASE+0x250))
#define  CAN_F2R2   *((volatile u32 *)(CAN1_BASE+0x254))
#define  CAN_F3R1   *((volatile u32 *)(CAN1_BASE+0x258))
#define  CAN_F3R2   *((volatile u32 *)(CAN1_BASE+0x25C))
#define  CAN_F4R1   *((volatile u32 *)(CAN1_BASE+0x260))
#define  CAN_F4R2   *((volatile u32 *)(CAN1_BASE+0x264))
#define  CAN_F5R1   *((volatile u32 *)(CAN1_BASE+0x268))
#define  CAN_F5R2   *((volatile u32 *)(CAN1_BASE+0x26C))
#define  CAN_F6R1   *((volatile u32 *)(CAN1_BASE+0x270))
#define  CAN_F6R2   *((volatile u32 *)(CAN1_BASE+0x274))
#define  CAN_F7R1   *((volatile u32 *)(CAN1_BASE+0x278))
#define  CAN_F7R2   *((volatile u32 *)(CAN1_BASE+0x27C))
#define  CAN_F8R1   *((volatile u32 *)(CAN1_BASE+0x280))
#define  CAN_F8R2   *((volatile u32 *)(CAN1_BASE+0x284))
#define  CAN_F9R1   *((volatile u32 *)(CAN1_BASE+0x288))
#define  CAN_F9R2   *((volatile u32 *)(CAN1_BASE+0x28C))
#define  CAN_F10R1  *((volatile u32 *)(CAN1_BASE+0x290))
#define  CAN_F10R2  *((volatile u32 *)(CAN1_BASE+0x294))
#define  CAN_F11R1  *((volatile u32 *)(CAN1_BASE+0x298))
#define  CAN_F11R2  *((volatile u32 *)(CAN1_BASE+0x29C))
#define  CAN_F12R1  *((volatile u32 *)(CAN1_BASE+0x2A0))
#define  CAN_F12R2  *((volatile u32 *)(CAN1_BASE+0x2A4))
#define  CAN_F13R1  *((volatile u32 *)(CAN1_BASE+0x2A8))
#define  CAN_F13R2  *((volatile u32 *)(CAN1_BASE+0x2AC))

/**************************************************Configurations Definition Of CAN Driver********************************************************/
/* WAKEUP Mode Options Defintion */
#define  CAN_AUTOMATIC_WAKEUP_MODE  0
#define  CAN_MANUAl_WAKEUP_MODE     1
/* Time Triggered Mode Options */
#define  CAN_TIMETRIGGERED_MODE_DISABLED  0
#define  CAN_TIMETRIGGERED_MODE_ENABLED   1
/* Retransmission Options */
#define  CAN_AUTOMATIC_RETRANSMISSION     0
#define  CAN_NOTAUTOMATIC_RETRANSMISSION  1
/* Recive FiFoLoced Mode Options */
#define  CAN_RECIEVE_FIFO_LOCKED    0
#define  CAN_RECIEVE_FIFO_UNLOCED   1
/* OPtions Of Transmission Priority */
#define  CAN_TRANSMIT_PRIORITY_ID_BASED       0
#define	 CAN_TRANSMIT_PRIORITY_REQUEST_BASED  1
/* CAN during Debug */
#define   CAN_DURING_DEBUG_ENABLED    0
#define   CAN_DURING_DEBUG_DISABLED   1
/* CAN Standarization */
#define  CAN_STANDRD   0
#define  CAN_EXTENDED  1
/* Filters Configurationsm*/
#define   CAN_ONE_32BIT_FILTER_ID_MASK     0
#define   CAN_TWO_32BIT_FILTER_ID_LIST     1
#define   CAN_TWO_16BIT_FILTER_ID_MASK     2
#define   CAN_FOUR_16BIT_FILTER_ID_LIST     3
/*CAN_FILTER_BANK0_ASSIGNMENT Options:*/
#define  CAN_FILTER_BANK_ASSIGNED_TO_FIFO0   0
#define  CAN_FILTER_BANK_ASSIGNED_TO_FIFO1   1
/* CAN_NEW_MESSAGE_INTERRUPT_FIFOx Options */
#define   CAN_NEW_MESSAGE_INTERRUPT_ENABLED   0
#define   CAN_NEW_MESSAGE_INTERRUPT_DISABLED  1	
/* BUS_OFF_MANAGEMENT Options */
#define  BUS_OFF_AUTOMATIC_MANAGEMENT        0
#define	 BUS_OFF_NONAUTOMATIC_MANAGEMENT     1 
/* CAN_FILTER_BANKx_ACTIVATION  Options */
#define  CAN_FILTER_BANK_ACTIVATED       0
#define  CAN_FILTER_BANK_NONACTIVATED    1


  

#endif
