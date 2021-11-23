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

typedef unsigned char uint8_t;

uint8_t sending_buf[1];

/* The preamble consists of a minimum of 11 and a maximum of 25 bits, all set to ONE */
#define PREAMBLE_BYTE_CNT    (2)               /* PREAMBLE_BYTE_CNT == 2 or 3 */

code uint8_t Packet_Ping[2] ={
	0x01, 0x80 
};

code uint8_t Packet_ID[8] ={
	0x71, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00 , 0x00 
};

code uint8_t Packet_Config[6] ={
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

void wp_init(void)
{
	CLK_CTL2  |= 0x08;                         /* enable SSP Clock */
	
	AFR_SSP_CON1  &= ~0x80;
	
	AFR_SSP_T_START |= 0x40;
}

static void wp_rx_tx(uint8_t dt)
{
	while ( (AFR_SSP_FIFOSTART & 0x01) != 0 );
	AFR_SSP_DAT = dt;
}

static void send_preamble(void)
{
	uint8_t i;

	AFR_SSP_CON0  = 0x0D;
	
    for (i = 0; i < PREAMBLE_BYTE_CNT; i++) {
		wp_rx_tx(0xFF);
    }
}

static void send_packet(uint8_t *pkt_type, uint8_t len)
{
	uint8_t i, crc = 0;
	
	send_preamble();
	
	AFR_SSP_CON0  = 0x7D;
	
	for (i = 0; i < len; i++) {
		wp_rx_tx(pkt_type[i]);
		crc ^= pkt_type[i];
	}
	wp_rx_tx(crc);
}

int main()
{
	WDTCON = 0x05;                             /* disable watchdog at startup */
	
	MFP3  |= 0x10;                             /* P14 as ssp */
	
	wp_init();	
	
	while (1) {
		send_packet(Packet_Ping,2);
		_delay_ms(10);
		send_packet(Packet_ID,8);
		_delay_ms(10);
		send_packet(Packet_Config,6);
		_delay_ms(10);
	}
}
