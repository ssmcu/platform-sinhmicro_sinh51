/*
 * uart-txrx
 *
 * Serial data transceiver.
 *
 * Author: huxingmin<cyan1219@sina.com>
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
 
#include "ss881x.h"


static unsigned char  i, j, err[3], sign;
static unsigned int checksum_rx, checksum_tx;
static int a[20];


void uart_init()
{
    /* 
     * P11作UARTTX,P12作为UARTRX
     */
    MFP2   =  0X24;                                  
    MFP3   =  0X85;
    EFRADR =  0X12;                                  /* 对EXTMFP0寄存器进行操作 */
    EFRDAT =  0X00;                                  /* 使MFP2可选P12的复用功能 */
    
    SCON   =  0X74;
    SBR    =  0Xfe;                                  /* 波特率为460800 */   
}

/*
 * 将sbuf_tx发送出去
 */
void uart_tx(unsigned char sbuf_tx)
{
    while (!TI) {
    }
    TI   = 0;
    SBUF = sbuf_tx;
}

/* 
 * 接收函数，如果没有收到数据则返回-1，收到数据则将收到的数据返回出去 
 */
int uart_rx()
{
    if (!RI)
        return -1;
    RI = 0;
    return SBUF;
}

unsigned int checksum_rxtx( int *a, unsigned int length)
{
    unsigned int i, checksum;
    checksum = 0;
    for (i = 0; i < length - 1; i++) {
        checksum += *a;              /* 计算接收校验和checksum_rx */
        a++;
    }
    return checksum;
}

void main()
{
    WDTCON  = 0x05;                                  /* 关闭看门狗 */
    //CKCON   = (CKCON & 0X8F) | 0X10;                 /* 减小程序访问的等待周期，增加MCU的速度 */
    sign    = 0XFE;
    err[0]  = 'e';
    err[1]  = 'r';
    err[2]  = 'r';
    
    uart_init();
    
    while (1) {
        checksum_rx = 0;
        checksum_tx = 0;
        i           = 0;
        RI          = 0;
        TI          = 1;
        
        /*
         * 接收数据并存在数组a[]中,并通过checksum_rx计算校验和
         */
        while (1) {
            a[i] = uart_rx();
                                     
            if (a[i] != -1) {

                if (a[i] == sign) {
                    break;
                }
                i++;
            }
        }
        /*
         * 对收到的数据校验和与数据中包含的校验和作判断，如果相等则发送数据，否则发送err提示信息
         */
        checksum_rx = checksum_rxtx(&a, i);          /* 计算接收校验和checksum_rx */
        
        if (checksum_rx == a[i - 1]) {
            unsigned char sbuf_tx;
            
            for (j = 0; j < i - 1; j++) {
                sbuf_tx = a[j] & 0xff;
                uart_tx(sbuf_tx);
            }
            
            sbuf_tx = checksum_rxtx(&a, j + 1);      /* 计算发送校验和checksum_tx */
            uart_tx(sbuf_tx);                        /* 发送校验和 */
            uart_tx(sign);                           /* 发送结束标志 */
        }
        else
        {
            for (j = 0; j < 3; j++){
                uart_tx(err[j]);
            }
        }
        
    }
}

























