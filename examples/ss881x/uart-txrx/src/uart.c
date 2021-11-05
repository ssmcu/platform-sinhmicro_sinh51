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
     * P11��UARTTX,P12��ΪUARTRX
     */
    MFP2   =  0X24;                                  
    MFP3   =  0X85;
    EFRADR =  0X12;                                  /* ��EXTMFP0�Ĵ������в��� */
    EFRDAT =  0X00;                                  /* ʹMFP2��ѡP12�ĸ��ù��� */
    
    SCON   =  0X74;
    SBR    =  0Xfe;                                  /* ������Ϊ460800 */   
}

/*
 * ��sbuf_tx���ͳ�ȥ
 */
void uart_tx(unsigned char sbuf_tx)
{
    while (!TI) {
    }
    TI   = 0;
    SBUF = sbuf_tx;
}

/* 
 * ���պ��������û���յ������򷵻�-1���յ��������յ������ݷ��س�ȥ 
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
        checksum += *a;              /* �������У���checksum_rx */
        a++;
    }
    return checksum;
}

void main()
{
    WDTCON  = 0x05;                                  /* �رտ��Ź� */
    //CKCON   = (CKCON & 0X8F) | 0X10;                 /* ��С������ʵĵȴ����ڣ�����MCU���ٶ� */
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
         * �������ݲ���������a[]��,��ͨ��checksum_rx����У���
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
         * ���յ�������У����������а�����У������жϣ��������������ݣ�������err��ʾ��Ϣ
         */
        checksum_rx = checksum_rxtx(&a, i);          /* �������У���checksum_rx */
        
        if (checksum_rx == a[i - 1]) {
            unsigned char sbuf_tx;
            
            for (j = 0; j < i - 1; j++) {
                sbuf_tx = a[j] & 0xff;
                uart_tx(sbuf_tx);
            }
            
            sbuf_tx = checksum_rxtx(&a, j + 1);      /* ���㷢��У���checksum_tx */
            uart_tx(sbuf_tx);                        /* ����У��� */
            uart_tx(sign);                           /* ���ͽ�����־ */
        }
        else
        {
            for (j = 0; j < 3; j++){
                uart_tx(err[j]);
            }
        }
        
    }
}

























