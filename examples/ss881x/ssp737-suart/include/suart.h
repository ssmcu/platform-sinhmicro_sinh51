/*
* suart.h
* IO simulate uart.
*
* Copyright (C) 2021 Sinh Micro, Inc.
* Author: zhangzhao@sinhmicro.com.cn
*
* Changelog:
* 20220214: Init version
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
#ifndef __SUART_H__
#define __SUART_H__

#define SUART_SET_TRX_PIN(sta)        (P0_1 = sta)
#define SUART_GET_TRX_PIN()           (P0_1)

#define SUART_SET_TX()                do {P0MOD &= 0xFD;} while (0)
#define SUART_SET_RX()                do {P0MOD |= 0x02;} while (0)

#define SUART_BIT_TIME_HALF()         suart_delay(17)
#define SUART_BIT_TIME_WHOLE()        suart_delay(40)

#define SUART_PARITY_CHCEK_NONE        (0)
#define SUART_PARITY_CHCEK_ODD         (1)
#define SUART_PARITY_CHCEK_EVEN        (2)
#define SUART_PARITY_CHCEK             (SUART_PARITY_CHCEK_ODD)

#define SUART_IRQ_DISABLE()             (EA = 0)
#define SUART_IRQ_ENABLE()              (EA = 1)

#define SUART_SEND_CLR_RX_DATA          (1)
#define SUART_CONFIGURABLE_BR           (0)

void suart_init(void);
void suart_putc(unsigned char c);

/**
 * @brief get a received byte
 * @note  
 * @return ** unsigned char 
 *          received data
 */
unsigned char suart_getc(void);

/**
 * @brief parse bitstream on falling edge
 * 
 * @return ** bit 
 *          1 successfully received a byte
 *          0 no data received
 */
bit suart_receiver(void);

/**
 * @brief set baud rate
 * @note replace SUART_BIT_TIME_HALF() and SUART_BIT_TIME_WHOLE()
 *       with parameters whole and half.
 *      example: #define SUART_BIT_TIME_HALF()  suart_delay(whole_bit_tim)
 * @param whole 
 *          one bit time
 * @param half 
 *          half bit time
 * @return ** void 
 */
void suart_set_baudrate(unsigned char whole, unsigned char half);

#endif /* __UART_H__ */
