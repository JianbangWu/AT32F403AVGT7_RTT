#ifndef ST7796_H__
#define ST7796_H__

#include "drv_lcd.h"

rt_err_t st7796_write_cmd(struct drv_lcd_device *dev, const rt_uint8_t cmd);
rt_err_t st7796_write_data(struct drv_lcd_device *dev, const rt_uint8_t data);
rt_err_t st7796_init(struct drv_lcd_device *dev);

void st7796_address_set(struct drv_lcd_device *dev, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
void st7796_lcd_fill(struct drv_lcd_device *dev, uint16_t xsta, uint16_t ysta, uint16_t xend, uint16_t yend, uint16_t color);

#endif