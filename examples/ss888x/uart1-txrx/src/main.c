/*
 * main.c
 *
 * uart1-txrx.
 *
 * Author: qiujunling<qiujunling@sinhmicro.com.cn>
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

#define BAUD_RATE	(0x1f8)						/* 数据手册波特率设置115200对应值 */
#define REC_MAX 	(15)						/* 最大接收数 */

unsigned char 	flag_receive		= 0,		/* 接受到数据标志 */
				flag_rx_0d			= 0,		/* 接受到0x0d标志 */
				flag_rx_complete	= 0,		/* 接受完成标志 */
				flag_err		 	= 0,		/* 接受错误标志 */
				receive_length 		= 0,		/* 接受数据的长度 */
				receive_buff[REC_MAX];			/* 接受缓存数组 */

void uart_init()
{
	EFR_ADR 		 = MFP4;                    /* EFR_ADR选中EXTMFP2寄存器地址 */     
	EFR_DAT 		&= ~(0x3 << 4);				/* 清0 */
	EFR_DAT 		|=  (0x2 << 4);				/* 配置P21为UART1TX */
	EFR_DAT 		&= ~(0x3 << 2);				/* 清0 */
	EFR_DAT 		|=  (0x2 << 2);				/* 配置P22为UART1RX */
	
	CLKCON2 		|=  (1 << 2);				/* 开启UART1时钟 */
	
	AFR_UART1_CTL0   =  0X43;					/* 配置13分频，不用校验位，使能使发送和接收 */
	AFR_UART1_STATE |=  ((BAUD_RATE >> 8) << 7);/* 配置波特率BAUD_RATE第9位 */
	AFR_UART1_BRL    =  BAUD_RATE; 				/* 配置波特率BAUD_RATE低8位 */
	
	AFR_UART1_CTL1 	|=  (1 << 1);				/* RXFIFO不为空中断使能 */
	INT_CTRL3 		|=  (1 << 0); 				/* UART1中断使能 */
	EA				 =  1;						/* 全局中断使能 */
}

void send_byte(unsigned char byte)
{
    while (AFR_UART1_STATE & 0x40);						/* FIFO满时，等待FIFO变换到未满状态 */
    AFR_UART1_TX_DATA = byte;							/* 发送数据 */
}

void array_send(unsigned char *ary, unsigned char num)	/* 串行通讯数组发送多个8位码函数 */
{
	while (num) {
		send_byte(*ary++);								/* 指针地址自加，指向下一个数组数据的地址 */
		num--;
	}
}

static void _delay_ms(unsigned char ms)
{	
    unsigned char i, j;
    do {
        i = 4;	
        j = 200;
        do {
            while (--j);
        } while (--i);
    } while (--ms);
}

int main()
{
	unsigned char	times 	= 0,								/* 循环次数，用于每约2s自动发送信息 */
					timeout = 0;								/* 循环次数，用于检测超时置位err */
    WDTCON  = 0x05;												/* 关闭看门狗 */
    uart_init();
    
    while (1) {
		if (timeout > 1) {
			timeout	 = 0;
			flag_err = 1;
		}
		
		if (flag_rx_complete) {	
			array_send((unsigned char *)"send message:", 13);	/* 发送字符 */			
			array_send(&receive_buff, receive_length);			/* 发送接收数值 */
			array_send((unsigned char *)"\r\n", 2);				/* 发送换行 */
			flag_rx_complete = 0;
			flag_receive	 = 0;
			flag_rx_0d		 = 0;
			receive_length	 = 0;
		} else if (flag_err) {
			flag_err		 = 0;
			flag_receive	 = 0;
			flag_rx_0d		 = 0;
			receive_length	 = 0;
			array_send((unsigned char *)"err\r\n", 5);			/* 发送错误信息 */
		}
		
		if (flag_receive) {
			timeout++;
		}
		
		times++;
		_delay_ms(10);
		if (times == 200) {
			times = 0;
			array_send((unsigned char *)"please input\r\n", 14);/* 每约2s自动发送信息 */
		}				
	}
}
#if defined(__C51__)
void uart1_ISR(void) interrupt 16
#else
void uart1_ISR(void) __interrupt 16
#endif
{ 
	flag_receive = 1;
	while (AFR_UART1_FIFO_CTL & 0x0f) {
		if (!flag_err) {										/* 接收到数据但未发生错误 */
			if (!flag_rx_complete) {							/* 接收未完成 */
				if (flag_rx_0d) {								/* 接收到了0x0d(\r) */
					if (AFR_UART1_RX_DATA != 0x0a) {			/* 并非0x0a(\n)结尾，接收错误,重新开始 */
						flag_err = 1;
					} else { 
						flag_rx_complete = 1;					/* 接收完成了 */
					}
				} else { 										/* 还没收到0X0d(\r) */	
					if (AFR_UART1_RX_DATA == 0x0d) {
						flag_rx_0d = 1;
					} else {
						receive_buff[receive_length] = AFR_UART1_RX_DATA;
						receive_length++;
						if (receive_length > (REC_MAX - 1)) {	/* 接收数据错误,重新开始接收 */
							flag_err		= 1;
							receive_length  = 0;
						}
					}
				}
			}
		} else {
			receive_buff[receive_length] = AFR_UART1_RX_DATA;	/* 将错误的数据接收但不保留，清除RXCNT计数 */
		}
	}
}
