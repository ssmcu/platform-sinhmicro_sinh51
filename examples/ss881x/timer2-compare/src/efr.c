/*
 * efr.c
 *
 * The EFR read and write APIs.
 *
 * Copyright (C) 2018 Sinh Micro, Inc.
 * Subject to the GNU Public License, version 2.
 *
 * Author: zhaozeyan<zhaozeyan@sinhmicro.com>
 */

#include "efr.h"

/*
 * this function is used to rewrite the efr registers
 *
 * @param[in]  addr   efr registers address
 * @param[in]  wr_dt  the value you want to fill in
 */
void efr_write(uint8_t addr, uint8_t wr_dt)
{
    EA = 0;
    EFR_ADDR = addr;
    EFR_DAT = wr_dt;
    EA = 1;
}

/*
 * this function is used to read the efr registers
 *
 * @param[in]  addr  efr Register address
 * @return the value of Register
 */
uint8_t efr_read(uint8_t addr)
{
    uint8_t efr_data;

    EA = 0;
    EFR_ADDR = addr;
    efr_data = EFR_DAT;
    EA = 1;
    
    return efr_data;
}

/*
 * this function modifies the bits you want to modify
 *
 * @param[in]  addr          efr Register address
 * @param[in]  start_bit     the start bit that you want to modify
 * @param[in]  value         the value you want to change from the start bit
 * @param[in]  set_or_clear  select set or reset
 * @return the value of Register
 */
void efr_bit_change(uint8_t addr, uint8_t start_bit, uint8_t value, bool set_or_reset)
{
    uint8_t read_efr;
    if (set_or_reset) {
        read_efr = efr_read(addr);
        read_efr |= (value << start_bit);
        efr_write(addr, read_efr);
    } else {
        read_efr = efr_read(addr);
        read_efr &= ~(value << start_bit);
        efr_write(addr, read_efr);
    }
}

/*
 * this function set the bits you want to modify
 *
 * @param[in]  addr          efr Register address
 * @param[in]  bitmask       the bitmask should be set
 */
void efr_set_bit(uint8_t addr, uint8_t bitmask)
{
    uint8_t read_efr;
    
    read_efr = efr_read(addr);
    read_efr |= bitmask;
    efr_write(addr, read_efr);
}

/*
 * this function clear the bits you want to modify
 *
 * @param[in]  addr          efr Register address
 * @param[in]  bitmask       the bitmask should be clear
 */
void efr_clear_bit(uint8_t addr, uint8_t bitmask)
{
    uint8_t read_efr;
    
    read_efr = efr_read(addr);
    read_efr &= ~bitmask;
    efr_write(addr, read_efr);
}

/*
 * this function toggle the bits you want to modify
 *
 * @param[in]  addr          efr Register address
 * @param[in]  bitmask       the bitmask should be clear
 */
void efr_toggle_bit(uint8_t addr, uint8_t bitmask)
{
    uint8_t read_efr;
    
    read_efr = efr_read(addr);
    read_efr ^= bitmask;
    efr_write(addr, read_efr);
}