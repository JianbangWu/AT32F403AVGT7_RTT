#ifndef __ST7789_H__
#define __ST7789_H__

#include "drv_lcd.h"

rt_err_t st7789_init(struct drv_lcd_device *dev);
void st7789_address_set(struct drv_lcd_device *dev, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
void st7789_lcd_fill(struct drv_lcd_device *dev, uint16_t xsta, uint16_t ysta, uint16_t xend, uint16_t yend, uint16_t color);

#endif