#ifndef GC9A01_H
#define GC9A01_H

#include "drv_lcd.h"

rt_err_t gc9a01_init(struct drv_lcd_device *dev);
void gc9a01_address_set(struct drv_lcd_device *dev, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
void gc9a01_lcd_fill(struct drv_lcd_device *dev, uint16_t xsta, uint16_t ysta, uint16_t xend, uint16_t yend, uint16_t color);

#endif