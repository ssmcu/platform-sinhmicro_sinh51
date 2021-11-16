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

u8 sending_buf[1];

code u8 preamble[2] ={
	0xFF, 0xFF 
};

code u8 Packet_Ping[2] ={
	0x01, 0x80 
};

code u8 Packet_ID[8] ={
	0x71, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00 , 0x00 
};

code u8 Packet_Config[6] ={
	0x51, 0x0A, 0x00, 0x00, 0x26 , 0x00 
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

void ssp_wprx_init()
{
	CLK_CTL2  |= 0x08;                         /* enable SSP Clock */
	
	AFR_SSP_CON0  = 0x7D;
	
	AFR_SSP_T_START |= 0x40;
}

void ssp_wprx_tx(u8 dt)
{
	while (AFR_SSP_FIFOSTART & 0x01);
	AFR_SSP_DAT = dt;
}

void send_packet(u8 j, u8 packet_type[])
{
	u8 i, crc;
	crc = 0;
	for (i = 0; i < j; i++)
	{
		ssp_wprx_tx(packet_type[i]);
		sending_buf[0] = packet_type[i];
		crc ^= sending_buf[0];
	}
	sending_buf[0] = crc;
	ssp_wprx_tx(sending_buf[0]);
}

int main()
{
	WDTCON = 0x05;                             /* disable watchdog at startup */
	
	MFP3  |= 0x10;                             /* P14 as ssp */
	
	ssp_wprx_init();	

	while (1) {
	ssp_wprx_tx(preamble[0]);
	ssp_wprx_tx(preamble[1]);
	send_packet(2, Packet_Ping);
	_delay_ms(20);
	
	ssp_wprx_tx(preamble[0]);
	ssp_wprx_tx(preamble[1]);
	send_packet(8, Packet_ID);
	_delay_ms(20);
	
	ssp_wprx_tx(preamble[0]);
	ssp_wprx_tx(preamble[1]);
	send_packet(6, Packet_Config);
	_delay_ms(20);
	}
}
