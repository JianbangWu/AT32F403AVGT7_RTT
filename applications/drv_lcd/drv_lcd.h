#ifndef __DRV_LCD_H__
#define __DRV_LCD_H__

#include <rtthread.h>
#include "drv_common.h"
#include "rtconfig.h"
#include "lcd_config.h"

/* DC low for data high for cmd */

struct drv_lcd_config
{
    const char *bus_name;
    const char *lcd_name;
    const char *lcd_chip;
    const char *dc_pin;
    const char *cs_pin;
    const char *reset_pin;
    const char *bkl_pin;
};

struct drv_lcd_device
{
    struct rt_spi_device parent;
    struct drv_lcd_config config;
};

#endif // __DRV_LCD_H__
