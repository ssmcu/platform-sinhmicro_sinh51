/* Author: zhanyingwei<3080940495@qq.com>
 * 
 * Copyright (C) 2021 Sinh Micro, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "ss888x.h"

typedef unsigned char u8;

code u8 pack_start[4]={
	0xFF, 0xFF, 0xFF, 0x7F
};

code u8 pack_0[4]={
	0x74, 0x00, 0x02, 0x1f
};

code u8 pack_1[2]={
	0x72, 0x71
};

code u8 pack_2[4]={
	0x70, 0x00, 0x80, 0x12
};

static void _delay_ms(unsigned char ms)
{	
    unsigned char i, j;
    do {
        i = 4;
        j = 200;
        do
        {
            while (--j);
        } while (--i);
    } while (--ms);
}

void ssp_hdq_tx(u8 dt)
{
	while (AFR_SSP_FIFOSTART & 0x01);
	AFR_SSP_DAT = dt;
}

void send_StartFlag(u8 j, u8 packet_type[])
{
	u8 i;
	
	AFR_SSP_CON0  = 0x05;
	
    AFR_SSP_T_ZERO  = 0x5E;
	AFR_SSP_T_ONE   = 0xF0;
	
	for (i = 0; i < j; i++)
	{
		ssp_hdq_tx(packet_type[i]);
	}
}

void send_StopFlag(u8 off)
{
	AFR_SSP_CON0  = 0x05;
	
    AFR_SSP_T_ZERO  = 0x50;
	AFR_SSP_T_ONE   = 0x02;
	
	ssp_hdq_tx(off);
}

void send_packet(u8 j, u8 packet_type[])
{
	u8 i;
	
	AFR_SSP_CON0  = 0x25;
	
	AFR_SSP_T_ZERO  = 0x37;
	AFR_SSP_T_ONE   = 0x82;
	AFR_SSP_T_STOP  = 0xC0;
	
	for (i = 0; i < j; i++)
	{
		ssp_hdq_tx(packet_type[i]);
	}
}

int main()
{
	WDTCON = 0x05;                             /* disable watchdog at startup */
	
	MFP3  |= 0x10;                             /* P14 as ssp */
	
	CLK_CTL2  |= 0x08;                         /* enable SSP Clock */
	
	while (1) {
		send_StartFlag(4,pack_start);
		send_packet(4,pack_0);
		_delay_ms(200);
		send_packet(2,pack_1);
		_delay_ms(200);
		send_packet(4,pack_2);
		send_StopFlag(0x7F);
		_delay_ms(200);
	}
}
