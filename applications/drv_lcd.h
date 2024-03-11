#ifndef DRV_LCD_H__
#define DRV_LCD_H__

#include <rtthread.h>
#include "drv_common.h"
#include "rtconfig.h"
#include "lcd_config.h"

/* DC low for data high for cmd */
struct drv_lcd_config
{
    struct rt_spi_device parent;
    const char *bus_name;
    const char *lcd_name;
    const char *lcd_chip;
    const char *dc_pin;
    const char *cs_pin;
    const char *reset_pin;
    const char *bkl_pin;
    enum rt_device_class_type *bkl_type;
    // struct rt_device_graphic_info *lcd_info;
};

#endif // DRV_LCD_H__
