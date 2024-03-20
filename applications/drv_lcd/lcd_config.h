#ifndef __LCD_CONFIG_H__
#define __LCD_CONFIG_H__

#include <rtthread.h>
#include "drv_lcd.h"

// #define LCD1_CONFIG                      \
//     {                                    \
//         .bus_name = "spi1",              \
//         .lcd_name = "lcd1",              \
//         .lcd_chip = "st7796",            \
//         .dc_pin = "PA.6",                \
//         .cs_pin = "PA.4",                \
//         .reset_pin = "PC.4",             \
//         .bkl_pin = "PA.2",               \
//     }

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

/* pmod spi4 */
// #define LCD2_CONFIG                      \
//     {                                    \
//         .bus_name = "spi4",              \
//         .lcd_name = "lcd2",              \
//         .lcd_chip = "gc9a01",            \
//         .dc_pin = "PB.9",               \
//         .cs_pin = "PE.4",               \
//         .reset_pin = "PE.0",             \
//         .bkl_pin = "PB.8",               \
//     }

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

// /* board on spi4 */
// #define LCD2_CONFIG                      \
//     {                                    \
//         .bus_name = "spi4",              \
//         .lcd_name = "lcd2",              \
//         .lcd_chip = "gc9a01",            \
//         .dc_pin = "PE.5",                \
//         .cs_pin = "PE.4",                \
//         .reset_pin = "PE.1",             \
//         .bkl_pin = "PB.9",               \
//     }



#endif