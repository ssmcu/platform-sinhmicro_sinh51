/*
 * i2c.c
 *
 * i2c driver.
 *
 * Copyright (C) 2019 Sinh Micro, Inc.
 * Subject to the GNU Public License, version 2.
 *
 * Author: lipeng<lp@sinhmicro.com>;zhangyifan<zyf@sinhmicro.com>
 */

#include "types.h"

#if defined(CONFIG_SERIES_SS881X)
#include "ss881x.h"
#else
#error("Error MCU Series")
#endif

/*
 * I2C MODE SET: 0,Master mode; 1,Slave mode
 * I2C slave mode address is 0x8A
 */
#define I2C_MODE            (1)
/* I2C SPEED: 0,100KHZ; 1,400KHZ */
#define I2C_SPEED           (0)

#if (I2C_SPEED == 0)
/* 100KHz */
#define I2C_CLKDIV_VAL      (0x37)
#elif (I2C_SPEED == 1)
/* 400KHz */
#define I2C_CLKDIV_VAL      (0x0A)
#else
#error("I2C SPEED IS ERROR")
#endif

static bool wait_transmit(void);
static bool wait_receive(void);
static void controller_reset(void);
/* test */
static uint8_t reg_addr;
uint8_t reg[5];

static void _delay_ms(uint8_t ms)
{
    uint8_t i, j;
    do {
        i = 4;
        j = 200;
        do
        {
            while (--j);
        } while (--i);
    } while (--ms);
}

void i2c_init(void)
{
    /* P06 as SIF0, IICDAT */
    MFP1 = (MFP1 & ~(0x3 << 4)) | (0x2 << 4);
    MFP3 &= ~(0x3 << 2);
    /* P11 as SIF1, IICCLK */
    MFP2 = (MFP2 & ~(0x3 << 2)) | (0x1 << 2);
    MFP3 &= ~(0x3 << 0);
    /* Reset I2C controller */
    CLKCON1 &= ~(1 << 6);
    CLKCON1 |= (1 << 6);
    /* Configurate clock */
    IICDIV = I2C_CLKDIV_VAL;
    /*I2C controller enable; PU; mode select*/
    IICCON &= ~0x02;
    IICCON |= 0x09 | (I2C_MODE << 1);
#if (I2C_MODE == 1)
    EIIC = 1;
    /* Bus control */
    IICCON |= (1<<6);
#endif
}

void i2c_master_write(uint8_t device_addr, uint8_t device_reg, uint8_t val)
{
    if (IICSTAT & 0x01) {
        /* Bus error */
        controller_reset();
    }

    IICSTAT = 0x00;

    /* generate start condition, bus release, wirte device_addr */
    IICDAT = device_addr;
    IICCON = (IICCON & 0x0F) | 0x50;
    if (!wait_transmit())
    	goto i2c_error; 

    /* bus release,wirte deviceReg */
    IICDAT = device_reg;
    IICCON = (IICCON & 0x0F) | 0x40;
    if (!wait_transmit() ) 
    	goto i2c_error;    

    /* bus release,wirte data */
    IICDAT = val;
    IICCON = (IICCON & 0x0F) | 0x40;
    if (!wait_transmit() ) 
    	goto i2c_error;      
    
    /* generate stop bit */
    IICCON = (IICCON & 0x0F) | 0x60;
    
    /* wait stop bit */
    while ((IICSTAT & 0x04) == 0);
    
    /* clear IRQ&stop bit  */
    IICSTAT = 0x00;
    
i2c_error:
    controller_reset();
}

int16_t i2c_master_read(uint8_t device_addr, uint8_t device_reg)
{
    uint8_t val;
  
    if (IICSTAT & 0x01) {
        /* Bus error */
        controller_reset();
    }

    IICSTAT = 0x00;

    /* generate start condition, bus release, wirte device_addr */
    IICDAT = device_addr;
    IICCON = (IICCON & 0x0F) | 0x50;
    if (!wait_transmit()) 
    	goto i2c_error; 

    /* bus release,wirte deviceReg */
    IICDAT = device_reg;
    IICCON = (IICCON & 0x0F) | 0x40;
    if (!wait_transmit() ) 
    	goto i2c_error;    

    /* restart bit, bus release, wirte device_addr + 1 */
    IICDAT = device_addr + 1;
    IICCON = (IICCON & 0x0F) | 0x70;
    if (!wait_transmit() ) 
    	goto i2c_error;  

    /* generate NACK, Read data */
    IICSTAT |= 0x10; 
    IICCON = (IICCON & 0x0F) | 0x40;    // bus release     
    if (!wait_receive())
        goto i2c_error;
    
    val = IICDAT;
    
    /* generate stop bit */
    IICCON = (IICCON & 0x0F) | 0x60;
    
    /* wait stop bit */
    while ((IICSTAT & 0x04) == 0);
    
    /* clear IRQ&stop bit  */
    IICSTAT = 0x00;

    return val;

i2c_error:
    controller_reset();
    
    return -1;    
}

void i2c_exit(void)
{
    /* P06 set IO */
    MFP1 &= ~(0x3 << 4);
    /* P11 set IO */
    MFP2 &= ~(0x3 << 2);

    CLKCON1 &= ~(1 << 6);
    IICCON = 0;
#if (I2C_MODE == 1)
    EIIC = 0;
#endif
}

static bool wait_transmit(void)
{ 
    /* wait IRQ = 1 */
    while ((IICSTAT & 0x20) == 0);
	
    /* bit0 = 1,  bus error */
    if (IICSTAT & 0x01)
        return false;
  
    /* bit7 = 1,  NACK */
    if (IICSTAT & 0x10)
        return false;
  
    /* clear tansfer complete bit IRQ */
    IICSTAT = 0x00;
    
    return true;
}

static bool wait_receive(void)
{    
    /* wait IRQ = 1 */
    while ((IICSTAT & 0x20) == 0);
	
    /* bit0 = 1, bus error */
    if (IICSTAT & 0x01)
        return false;
 
    /* clear tansfer complete bit IRQ */
    IICSTAT = 0x00;
    
    return true; 
}

static void controller_reset(void)
{
    /* re-enable I2C controller */
    IICCON &= ~0x01;
    _delay_ms(1);
    IICCON |= 0x01;
}

#define STA_IDLE        (0)
#define STA_WAIT_ADDR   (1)
#define STA_WAIT_REG    (2)
#define STA_WAIT_DAT    (3)
#define STA_READ        (4)
#if (I2C_MODE == 1)
void i2c_slave_ISR(void) INTERRUPT 12 USING 1
{
    static uint8_t i2c_sta;

    if (!(IICSTAT & 0x02)) {
        /* Bus release quickly except for read mode */
        IICCON |= (1<<6);
    }
    if (IICSTAT & 0x01) {
        controller_reset();
        goto end;
    }
    /* Get start signal */
    if (IICSTAT & 0x08) {
        i2c_sta = STA_WAIT_ADDR;
    }
    if (IICSTAT & 0x02) {
        /* Read */
        IICDAT = reg[reg_addr];
        i2c_sta = STA_READ;
        /* bus release */
        IICCON |= (1<<6);
    } else {
        switch (i2c_sta) {
        case STA_WAIT_ADDR:
             i2c_sta = STA_WAIT_REG;
             break;
        case STA_WAIT_REG:
             reg_addr = IICDAT;
             i2c_sta = STA_WAIT_DAT;
             break;
        case STA_WAIT_DAT:
             reg[reg_addr] = IICDAT;
             break;
        default:
             break;
        }
    }
end:
    /* Clean start pending
       Clean stop pending
       Clean data pending
       Clean bus error pending
       Clean IR pending
    */
    IICSTAT &= ~0x6d;
}
#endif

void main(void)
{
#if (I2C_MODE == 0)
    int16_t recv_val;
#endif
    /* Disbable watch dog at startup*/
    WDTCON = 0x05;
    /* Enable I2C system clock */
    CLKCON1 |= 0x01;

    i2c_init();
    /* General interrupt enable */
    EA = 1;

    while(1) {
    #if (I2C_MODE == 0)
        i2c_master_write(0x8A, 0x01, 0xaa);
        _delay_ms(100);
        recv_val = i2c_master_read(0x8A, 0x01);
        _delay_ms(100);
    #endif
    }
}