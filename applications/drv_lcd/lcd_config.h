#ifndef __LCD_CONFIG_H__
#define __LCD_CONFIG_H__

#include <rtthread.h>
#include "drv_lcd.h"

#define LCD1_CONFIG                      \
    {                                    \
        .bus_name = "spi2",              \
        .lcd_name = "lcd1",              \
        .lcd_chip = "st7796",            \
        .dc_pin = "PB.14",               \
        .cs_pin = "PB.12",               \
        .reset_pin = "PB.1",             \
        .bkl_pin = "PC.7",               \
    }

/*  */
// #define LCD2_CONFIG           \
//     {                         \
//         .bus_name = "spi4",   \
//         .lcd_name = "lcd2",   \
//         .lcd_chip = "st7789", \
//         .dc_pin = "PE.0",     \
//         .cs_pin = "PE.4",     \
//         .reset_pin = "PB.9",  \
//         .bkl_pin = "PB.8",    \
//     }

/* ALL IN ONE BOARD PMOD DEFINE */
#define LCD2_CONFIG           \
    {                         \
        .bus_name = "spi4",   \
        .lcd_name = "lcd2",   \
        .lcd_chip = "st7789", \
        .dc_pin = "PB.9",     \
        .cs_pin = "PE.4",     \
        .reset_pin = "PE.0",  \
        .bkl_pin = "PB.8",    \
    }

#endif