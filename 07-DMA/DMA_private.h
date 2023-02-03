/***************************************/
/* Author  :Gomaa                      */
/* Date    :14 Seb 2020                 */
/* Version :V01                        */
/***************************************/

#ifndef _DMA_PRIVATE_H_
#define _DMA_PRIVATE_H_

typedef struct {
     u32 ISR;	
     u32 IFCR;	
	 u32 CCR1;	
	 u32 CNDTR1;	
	 u32 CPAR1;	
	 u32 CMAR1;
     u32 RESERVED1;	 
	 u32 CCR2;	
	 u32 CNDTR2;	
	 u32 CPAR2;	
	 u32 CMAR2;
     u32 RESERVED2;	 
	 u32 CCR3;	
	 u32 CNDTR3;	
	 u32 CPAR3;	
	 u32 CMAR3;
     u32 RESERVED3;	 
	 u32 CCR4;	
	 u32 CNDTR4;	
	 u32 CPAR4;	
	 u32 CMAR4;
     u32 RESERVED4;	 
	 u32 CCR5;	
	 u32 CNDTR5;	
	 u32 CPAR5;	
	 u32 CMAR5;
     u32 RESERVED5;	 
   	 u32 CCR6;	
	 u32 CNDTR6;	
	 u32 CPAR6;	
	 u32 CMAR6;
     u32 RESERVED6;	 
	 u32 CCR7;	
     u32 CNDTR7;	
     u32 CPAR7;	
     u32 CMAR7;	
	 u32 RESERVED7;
    	
					
}dma_t;

#define DMA1 ((volatile dma_t *)0x4002 0000)




#endif