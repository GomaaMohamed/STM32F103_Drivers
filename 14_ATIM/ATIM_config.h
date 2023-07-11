/*********************************************************************************/
/* Author    : Gomaa Mohammed                                                    */
/* Version   : V01                                                               */
/* Date      : 21 Dec 2020                                                    */
/*********************************************************************************/ 
#ifndef   ATIM_CONFIG_H
#define	  ATIM_CONFIG_H

/**************TIM1 Configration***********************/
/* Options:     ATIM_COUNTS_UP
                ATIM_COUNTS_DOWN
                ATIM_CENTER-ALIGNED MODE 1
                ATIM_CENTER-ALIGNED MODE 2
                ATIM_CENTER-ALIGNED MODE 3
*/
#define     ATIM1_COUNT_DIRECTION    ATIM_COUNTS_DOWN


/**************TIM8 Configration***********************/
/* Options:     ATIM_COUNTS_UP
                ATIM_COUNTS_DOWN
                ATIM_CENTER-ALIGNED MODE 1
                ATIM_CENTER-ALIGNED MODE 2
                ATIM_CENTER-ALIGNED MODE 3
*/
#define     ATIM8_COUNT_DIRECTION    ATIM_COUNTS_DOWN

#define    UPCOUNTER          0b000
#define    DOWNCOUNTER        0b001


#endif
