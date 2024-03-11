#ifndef __LCD_CONFIG_H__
#define __LCD_CONFIG_H__

#include <rtthread.h>
#include "drv_lcd.h"
#include "rtdef.h"

// #ifdef BSP_USING_LCD1

// #define LCD1_CONFIG                      \
//     {                                    \
//         .bus_name = "spi1",              \
//         .lcd_name = "lcd1",              \
//         .lcd_chip = "st7796",            \
//         .dc_pin = "PA.6",                \
//         .cs_pin = "PA.4",                \
//         .reset_pin = "PC.4",             \
//         .bkl_pin = "PA.2",               \
//         .bkl_type = RT_Device_Class_PWM, \
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
        .bkl_type = RT_Device_Class_PWM, \
    }

// #define LCD2_CONFIG                      \
//     {                                    \
//         .bus_name = "spi4",              \
//         .lcd_name = "lcd2",              \
//         .lcd_chip = "gc9a01",            \
//         .dc_pin = "PB.9",               \
//         .cs_pin = "PE.4",               \
//         .reset_pin = "PE.0",             \
//         .bkl_pin = "PB.8",               \
//         .bkl_type = RT_Device_Class_PWM, \
//     }

#define LCD2_CONFIG                      \
    {                                    \
        .bus_name = "spi4",              \
        .lcd_name = "lcd2",              \
        .lcd_chip = "gc9a01",            \
        .dc_pin = "PE.5",                \
        .cs_pin = "PE.4",                \
        .reset_pin = "PE.1",             \
        .bkl_pin = "PB.9",               \
        .bkl_type = RT_Device_Class_PWM, \
    }

// #endif /* BSP_USING_SPI1 */

#define LCD1_INFO                                      \
    {                                                  \
        .pixel_format = RTGRAPHIC_PIXEL_FORMAT_RGB565, \
        .bits_per_pixel = 16,                          \
        .width = 320,                                  \
        .height = 360,                                 \
        .framebuffer = RT_NULL,                        \
        .smem_len = RT_NULL,                           \
    }

#endif