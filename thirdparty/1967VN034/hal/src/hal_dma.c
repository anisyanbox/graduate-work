/**********************************************************************************************************************
  Copyright (c) 2016 Milandr Corporation. All rights reserved.

  History:
  	  Zatonsky Pavel - Created.
**********************************************************************************************************************/
#include <hal_1967VN034R1.h>
#include <sysreg.h>
#include <builtins.h>

#define TCB_INTMEM16  	(2<<29)
#define TCB_INTMEM22	(3<<29)
#define TCB_EXTMEM16	(4<<29)
#define TCB_EXTMEM22	(7<<29)


// Writes to DMA channel configuration registers.
// Use this function for channels with single DC (channels 4-13)
void HAL_DMA_WriteDC(int ch_number, void *qw_tcb)
{
	switch (ch_number)
	{
		case 4:	__builtin_sysreg_write4 (__DC4, *(__builtin_quad *)qw_tcb);	break;
		case 5:	__builtin_sysreg_write4 (__DC5, *(__builtin_quad *)qw_tcb);	break;
		case 6:	__builtin_sysreg_write4 (__DC6, *(__builtin_quad *)qw_tcb);	break;
		case 7:	__builtin_sysreg_write4 (__DC7, *(__builtin_quad *)qw_tcb);	break;
		case 8:	__builtin_sysreg_write4 (__DC8, *(__builtin_quad *)qw_tcb);	break;
		case 9:	__builtin_sysreg_write4 (__DC9, *(__builtin_quad *)qw_tcb);	break;
		case 10:	__builtin_sysreg_write4 (__DC10, *(__builtin_quad *)qw_tcb);	break;
		case 11:	__builtin_sysreg_write4 (__DC11, *(__builtin_quad *)qw_tcb);	break;
		case 12:	__builtin_sysreg_write4 (__DC12, *(__builtin_quad *)qw_tcb);	break;
		case 13:	__builtin_sysreg_write4 (__DC13, *(__builtin_quad *)qw_tcb);	break;
	}
}

// Writes to DMA channel SOURCE configuration registers.
// Use this function for channels 0-3
void HAL_DMA_WriteDCS(int ch_number, void *qw_tcb)
{
	switch (ch_number)
	{
		case 0:	__builtin_sysreg_write4 (__DCS0, *(__builtin_quad *)qw_tcb);	break;
		case 1:	__builtin_sysreg_write4 (__DCS1, *(__builtin_quad *)qw_tcb);	break;
		case 2:	__builtin_sysreg_write4 (__DCS2, *(__builtin_quad *)qw_tcb);	break;
		case 3:	__builtin_sysreg_write4 (__DCS3, *(__builtin_quad *)qw_tcb);	break;
	}
}

// Writes to DMA channel DESTINATION configuration registers.
// Use this function for channels 0-3
void HAL_DMA_WriteDCD(int ch_number, void *qw_tcb)
{
	switch (ch_number)
	{
		case 0:	__builtin_sysreg_write4 (__DCD0, *(__builtin_quad *)qw_tcb);	break;
		case 1:	__builtin_sysreg_write4 (__DCD1, *(__builtin_quad *)qw_tcb);	break;
		case 2:	__builtin_sysreg_write4 (__DCD2, *(__builtin_quad *)qw_tcb);	break;
		case 3:	__builtin_sysreg_write4 (__DCD3, *(__builtin_quad *)qw_tcb);	break;
	}
}


// Reads DMA channel configuration registers.
// Use this function for channels with single DC (channels 4-13)
void HAL_DMA_ReadDC(int ch_number, __builtin_quad *qw_tcb)
{
	switch (ch_number)
	{
		case 4:	*qw_tcb = __builtin_sysreg_read4 (__DC4);	break;
		case 5:	*qw_tcb = __builtin_sysreg_read4 (__DC5);	break;
		case 6:	*qw_tcb = __builtin_sysreg_read4 (__DC6);	break;
		case 7:	*qw_tcb = __builtin_sysreg_read4 (__DC7);	break;
		case 8:	*qw_tcb = __builtin_sysreg_read4 (__DC8);	break;
		case 9:	*qw_tcb = __builtin_sysreg_read4 (__DC9);	break;
		case 10:*qw_tcb = __builtin_sysreg_read4 (__DC10);	break;
		case 11:*qw_tcb = __builtin_sysreg_read4 (__DC11);	break;
		case 12:*qw_tcb = __builtin_sysreg_read4 (__DC12);	break;
		case 13:*qw_tcb = __builtin_sysreg_read4 (__DC13);	break;
	}
}

// Reads DMA channel SOURCE configuration registers.
// Use this function for channels 0-3
void HAL_DMA_ReadDCS(int ch_number, __builtin_quad *qw_tcb)
{
	switch (ch_number)
	{
		case 0:	*qw_tcb = __builtin_sysreg_read4 (__DCS0);	break;
		case 1:	*qw_tcb = __builtin_sysreg_read4 (__DCS1);	break;
		case 2:	*qw_tcb = __builtin_sysreg_read4 (__DCS2);	break;
		case 3:	*qw_tcb = __builtin_sysreg_read4 (__DCS3);	break;

	}
}

// Reads DMA channel DESTINATION configuration registers.
// Use this function for channels 0-3
void HAL_DMA_ReadDCD(int ch_number, __builtin_quad *qw_tcb)
{
	switch (ch_number)
	{
		case 0:	*qw_tcb = __builtin_sysreg_read4 (__DCD0);	break;
		case 1:	*qw_tcb = __builtin_sysreg_read4 (__DCD1);	break;
		case 2:	*qw_tcb = __builtin_sysreg_read4 (__DCD2);	break;
		case 3:	*qw_tcb = __builtin_sysreg_read4 (__DCD3);	break;
	}
}

//-------------------------------------------------------//
// Waits for DMA channel to complete
// Input:
//			ch_number - channel number
//-------------------------------------------------------//
void HAL_DMA_Stop(int ch_number)
{
	__builtin_quad zero_tcb = __builtin_compose_128(0,0);
	if (ch_number > 3)
	{
		HAL_DMA_WriteDC(ch_number, &zero_tcb);
	}
	else
	{
		HAL_DMA_WriteDCS(ch_number, &zero_tcb);
		HAL_DMA_WriteDCD(ch_number, &zero_tcb);
	}

}


// Extracts channel status bits
int HAL_DMA_DecodeStatus(long long dmaStatus, int channel)
{
	 switch(channel)
	{
		case 0:		return 	(int)((dmaStatus >> 0) & 0x07);
		case 1:		return 	(int)((dmaStatus >> 3) & 0x07);
		case 2:		return 	(int)((dmaStatus >> 6) & 0x07);
		case 3:		return 	(int)((dmaStatus >> 9) & 0x07);
		case 4:		return 	(int)((dmaStatus >> 12) & 0x07);
		case 5:		return 	(int)((dmaStatus >> 15) & 0x07);
		case 6:		return 	(int)((dmaStatus >> 18) & 0x07);
		case 7:		return 	(int)((dmaStatus >> 21) & 0x07);
		case 8:		return 	(int)((dmaStatus >> 32) & 0x07);
		case 9:		return 	(int)((dmaStatus >> 35) & 0x07);
		case 10:	return 	(int)((dmaStatus >> 38) & 0x07);
		case 11:	return 	(int)((dmaStatus >> 41) & 0x07);
		case 12:	return 	(int)((dmaStatus >> 50) & 0x07);
		case 13:	return 	(int)((dmaStatus >> 53) & 0x07);
		default:	return 0x05;	// illegal
	}
}

//-------------------------------------------------------//
// Returns DMA channel status
//-------------------------------------------------------//
int HAL_DMA_GetChannelStatus(int channel)
{
	long long int dmaStatus = __builtin_sysreg_read2(__DSTAT);
	return HAL_DMA_DecodeStatus(dmaStatus, channel);
}


//-------------------------------------------------------//
// Waits for DMA channel to complete
// Returns:
//	 0 if channel is done successfully,
//	 1 if there was an error
//	 2 if channel is disabled
//-------------------------------------------------------//
int HAL_DMA_WaitForChannel(int channel)
{
	int status;
	do
		status = HAL_DMA_GetChannelStatus(channel);
	while(status == DSTAT_ACT);

	switch(status)
	{
		case DSTAT_IDLE:
			return 2;
		case DSTAT_DONE:
			return 0;
		default:
			return 1;
	}
}

//-------------------------------------------------------//
// Waits for DMA channel to complete
// Input:
//			ch_number - channel number
//-------------------------------------------------------//
unsigned int HAL_DMA_GetDcCountX(int ch_number)
{
	__builtin_quad temp_tcb;
	unsigned int *ptr = (unsigned int*)&temp_tcb;
	unsigned int temp;
	switch (ch_number)
	{
		case 4:	temp_tcb = __builtin_sysreg_read4 (__DC4);	break;
		case 5:	temp_tcb = __builtin_sysreg_read4 (__DC5);	break;
		case 6:	temp_tcb = __builtin_sysreg_read4 (__DC6);	break;
		case 7:	temp_tcb = __builtin_sysreg_read4 (__DC7);	break;
		case 8:	temp_tcb = __builtin_sysreg_read4 (__DC8);	break;
		case 9:	temp_tcb = __builtin_sysreg_read4 (__DC9);	break;
		case 10:temp_tcb = __builtin_sysreg_read4 (__DC10);	break;
		case 11:temp_tcb = __builtin_sysreg_read4 (__DC11);	break;
		case 12:temp_tcb = __builtin_sysreg_read4 (__DC12);	break;
		case 13:temp_tcb = __builtin_sysreg_read4 (__DC13);	break;
	}

	temp = *(ptr+1);
	return (temp >> 16);
}


// Returns TCB_DMAxDEST field for a channel
int HAL_DMA_GetTCBChannelDest(int channel)
{
	 switch(channel)
	{
		case 4:		return 	TCB_DMA4DEST;
		case 5:		return 	TCB_DMA5DEST;
		case 6:		return 	TCB_DMA6DEST;
		case 7:		return 	TCB_DMA7DEST;
		case 8:		return 	TCB_DMA8DEST;
		case 9:		return 	TCB_DMA9DEST;
		case 10:	return 	TCB_DMA10DEST;
		case 11:	return 	TCB_DMA11DEST;
		default:	return 	0;
	}
}

// Returns TCB_DMAxDEST field for a channel
void HAL_DMA_CreateChannelDest(int channel, void *tcb_current, void *tcb_next ){
	unsigned int tmp;
	tmp = HAL_DMA_GetTCBChannelDest(channel);
	*((unsigned int *)(tcb_current)+3) |= ((unsigned int)tcb_next>>2) | tmp | TCB_CHAIN;
}

//-------------------------------------------------------//
// Returns DMA channel status and clears dma errors
// by reading DSTATC register
//-------------------------------------------------------//
int HAL_DMA_GetChannelStatusClear(int channel)
{
	long long int dmaStatus = __builtin_sysreg_read2(__DSTATC);
	return HAL_DMA_DecodeStatus(dmaStatus, channel);
}


#define HAL_DMA_InitMemType(addr, DPReg)\
	if ((addr <= (0x00FFF) ) || (addr >= 0x040000 && addr <= (0x04FFFF) ) ||\
		(addr >= 0x080000 && addr <= (0x08FFFF) ) || (addr >= 0x0C0000 && addr <= (0x0CFFFF) ) ||\
		(addr >= 0x100000 && addr <= (0x10FFFF) ) || (addr >= 0x140000 && addr <= (0x14FFFF) ))\
		DPReg |= TCB_INTMEM16;\
	else if((addr >= 0x30000000 && addr <= (0x44000000)) || (addr >= 0x50000000 && addr <= (0x54000000)) ||\
			(addr >= 0x60000000 && addr <= (0x64000000)) || (addr >= 0x70000000 && addr <= (0x74000000)))\
		DPReg |= TCB_EXTMEM16;\
	else return dmaCopyAddrErr

DMAReturnType HAL_DMA_MemCopy32(int ch_number, const void *src, const void *dst, int size){
	unsigned int tcb_dcs[4];
	unsigned int tcb_dcd[4];
	long int chStat;
	//check size
	if (size > 0xFFFF) return dmaCopyLengthErr;
	//init DCS
	tcb_dcs[3] = 0;
	HAL_DMA_InitMemType((int)src, tcb_dcs[3]);
	tcb_dcs[0] = (unsigned int)src;
	tcb_dcs[1] = (size<<16) | 1;
	tcb_dcs[2] = 0;
	tcb_dcs[3] |= TCB_NORMAL;
	//init DCD
	tcb_dcd[3] = 0;
	HAL_DMA_InitMemType((int)dst, tcb_dcd[3]);
	tcb_dcd[0] = (unsigned int)dst;
	tcb_dcd[1] = (size<<16) | 1;
	tcb_dcd[2] = 0;
	tcb_dcd[3] |= TCB_NORMAL;

	// Start DMA
	if(ch_number<4){
		HAL_DMA_WriteDCD(ch_number,&tcb_dcd);
		HAL_DMA_WriteDCS(ch_number,&tcb_dcs);
	}
	else return dmaCopyChNumErr;
	//Check DMA STATUS
	chStat = __builtin_sysreg_read2(__DSTAT);
	chStat = (chStat & (7<<(ch_number*3)));
	chStat = chStat >> (ch_number*3);
	switch(chStat){
	case 4: return dmaCopyChNumErr;
	case 5: return dmaCopyInitActCh;
	case 7: return dmaCopyAddrErr;
	default: return dmaCopyValid;
	}
}

//-------------------------------------------------------//
// Set DMA Requester TX
//------------------------------------------------------//
void HAL_DMA_SourceRqstSet(int ch_number, DMARequester_type dmaRqster){
	if(ch_number>3 && ch_number<8){
		*(unsigned *)base_DMACFGL &= ~(0xF<<(ch_number*4));
		*(unsigned *)base_DMACFGL |= (dmaRqster<<(ch_number*4));
	}
}
//-------------------------------------------------------//
// Set DMA Requester RX
//------------------------------------------------------//
void HAL_DMA_DestRqstSet(int ch_number, DMARequester_type dmaRqster){
	if(ch_number>=8 && ch_number <=11){
		ch_number*=4;
		ch_number&=0x1F;
		*(unsigned *)base_DMACFGH &= ~(0xF<<ch_number);
		*(unsigned *)base_DMACFGH |= (dmaRqster<<ch_number);
	}
}
//-------------------------------------------------------//
// Clear DMA Requester TX
//------------------------------------------------------//
void HAL_DMA_SourceRqstCl(int ch_number){
	if(ch_number>3 && ch_number<8){
		*(unsigned *)base_DMACFGL &= ~(0xF<<ch_number*4);
	}
}
//-------------------------------------------------------//
// Clear DMA Requester RX
//------------------------------------------------------//
void HAL_DMA_DestRqstCl(int ch_number){
	if(ch_number>=8){
		ch_number*=4;
		ch_number&=0x1F;
		*(unsigned *)base_DMACFGH &= ~(0xF<<ch_number);
	}
}
//-------------------------------------------------------//
// Clear All DMA Requester
//------------------------------------------------------//
void HAL_DMA_SourceDestRqstReset(void){
	*(unsigned *)base_DMACFGL = 0;
	*(unsigned *)base_DMACFGH = 0;
}

//-------------------------------------------------------//
// DMA higher priority than Core
//------------------------------------------------------//
void HAL_DMA_PrimaryPriority(void){
	*(unsigned *)CMU_CFG1_LOC |= (1<<12);
}

void HAL_DMA_RqstSet( uint32_t ch_number, DMARequester_type dmaRqster )
{
	if( ch_number < 8 )
	{
		*( uint32_t * ) base_DMACFGL &= ~( 0xF << ( ch_number * 4 ) );
		*( uint32_t * ) base_DMACFGH &= ~( 0x10000 << ch_number );
		*( uint32_t * ) base_DMACFGL |= ( ( dmaRqster & 0xF ) << ( ch_number * 4 ) );
		*( uint32_t * ) base_DMACFGH |= ( ( ( dmaRqster & 0x10 ) << 12 ) << ch_number );
	}
	else if( ch_number <= 11 )
	{
		*( uint32_t * ) base_DMACFGH &= ~( 0x10000 << ch_number );
		*( uint32_t * ) base_DMACFGH |= ( ( ( dmaRqster & 0x10 ) << 12 ) << ch_number );
		ch_number *= 4;
		ch_number &= 0x1F;
		*( uint32_t * ) base_DMACFGH &= ~( 0xF << ch_number );
		*( uint32_t * ) base_DMACFGH |= ( ( dmaRqster & 0xF ) << ch_number );
	}
}
