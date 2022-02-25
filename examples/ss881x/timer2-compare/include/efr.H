/*
 * efr.h
 *
 * The EFR read and write APIs.
 *
 * Copyright (C) 2018 Sinh Micro, Inc.
 * Subject to the GNU Public License, version 2.
 *
 * Author: zhaozeyan<zhaozeyan@sinhmicro.com>
 */

#ifndef _EFR_H_
#define _EFR_H_

#include "ss881x.h"
#include "types.h"

/*
 *  efr dummy name
 */
#if defined(__C51__)
sfr EFR_ADDR = 0x84; 
sfr EFR_DAT  = 0x85;
#else
__sfr __at 0x84 EFR_ADDR;
__sfr __at 0x85 EFR_DAT;
#endif

#define RESET       (0)
#define SET         (1)   

/* define eeprom registers */
#define EEPADR      (0x00)
#define EEPDAT      (0x01)
#define EEPCON      (0x02)

/* GPIO EFR registers */
#define EXTMFP0     (0x12)
#define EXTMFP1     (0x13)
#define PEXTCON0    (0x14)
#define PEXTCON1    (0x15)

/* touch sensor EFR registers */
#define TSCHEN      (0x10)
#define TSCON       (0x11)
#define TSSTAT0     (0x1A)
#define TSSTAT1     (0x1B)
#define	TSINT0      (0x1C)
#define TSINT1      (0x1D)
#define TSINT2      (0x1E)
#define TS01LV0     (0x20)
#define TS23LV0     (0x21)
#define TS45LV0     (0x22)
#define TS01LV1     (0x23)
#define TS23LV1     (0x24)
#define TS45LV1     (0x25)
#define TS01LV2     (0x26)
#define TS23LV2     (0x27)
#define TS45LV2     (0x28)
#define TSBVL       (0x2E)
#define TSBVH       (0x2F)
#define TS0VALL     (0x30)
#define TS0VALH     (0x31)
#define TS1VALL     (0x32)
#define TS1VALH     (0x33)
#define TS2VALL     (0x34)
#define TS2VALH     (0x35)
#define TS3VALL     (0x36)
#define TS3VALH     (0x37)
#define TS4VALL     (0x38)
#define TS4VALH     (0x39)
#define TS5VALL     (0x3A)
#define TS5VALH     (0x3B)
#define TS0OFFL     (0x40)
#define TS0OFFH     (0x41)
#define TS1OFFL     (0x42)
#define TS1OFFH     (0x43)
#define TS2OFFL     (0x44)
#define TS2OFFH     (0x45)
#define TS3OFFL     (0x46)
#define TS3OFFH     (0x47)
#define TS4OFFL     (0x48)
#define TS4OFFH     (0x49)
#define TS5OFFL     (0x4A)
#define TS5OFFH     (0x4B)

#define PEXTWKCON   (0x60)

uint8_t efr_read(uint8_t addr);
void efr_bit_change(uint8_t addr, uint8_t start_bit, uint8_t value, bool set_or_reset);
void efr_write(uint8_t addr, uint8_t wr_dt);
void efr_set_bit(uint8_t addr, uint8_t bitmask);
void efr_clear_bit(uint8_t addr, uint8_t bitmask);
void efr_toggle_bit(uint8_t addr, uint8_t bitmask);

#endif