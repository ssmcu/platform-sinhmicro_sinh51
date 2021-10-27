/*
 * eeprom
 *
 * read and write eeprom.
 *
 * Author: <liwanbang@sinhmicro.com.cn>
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

unsigned char WD[5] = "hello";
unsigned char RD[5] = "     ";  

void eeprom_write_byte(unsigned char addr,unsigned char byt)
{
        
        EFRADR = 0x00;
        EFRDAT = addr;          /* set addr */
        
        EFRADR = 0x01;
        EFRDAT = byt;           /* set dat */
        
        EFRADR = 0x02;
        EFRDAT |= (1<<3);       /* start write */
        
        EFRADR = 0x02;
        while(EFRDAT&(1<<3));   /* wait finish */
}

void eeprom_write(unsigned char addr,unsigned char *dat,unsigned char num)
{
        unsigned char i=0;
        
        EFRADR = 0x02;
        EFRDAT |= 0x02;         /* enable write */
        
        while(i<num){
                eeprom_write_byte(addr+i,dat[i]);
                i++;
        }
        EFRDAT &= ~0x03;        /* clear write */
}

unsigned char eeprom_read_byte(unsigned char addr)
{
        unsigned char dat=0;
        
        EFRADR = 0x00;
        EFRDAT = addr;          /* set addr */
        
        
        EFRADR = 0x02;
        EFRDAT |= (1<<2);       /* start read */
        
        EFRADR = 0x02;
        while(EFRDAT&(1<<2));   /* wait finish */
        
        EFRADR = 0x01;
        dat = EFRDAT;
        
        return dat;
}

void eeprom_read(unsigned char addr,unsigned char *date,unsigned char num)
{       
        unsigned char i=0;

        EFRADR = 0x02;
        EFRDAT |= 0x01;         /* enable read */
        
        while(i<num){
                *(date+i) = eeprom_read_byte(addr+i);
                i++;
        }
        EFRDAT &= ~0x03;        /* clear write */
}

void main()
{       
        WDTCON = 0x05;            /* disable watchdog at startup */
        
        eeprom_write(0x02,WD,5);
        eeprom_read(0x02,RD,5);   /* eeprom read 0x02 5 */
        while (1){
			
        }
}
