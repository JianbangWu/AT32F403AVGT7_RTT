#include "st7789.h"

#define DRV_DEBUG
#define LOG_TAG "st7789"
#include <drv_log.h>

rt_err_t st7789_write_cmd(struct drv_lcd_device *dev, const rt_uint8_t cmd)
{
    rt_size_t len;
    rt_pin_write(rt_pin_get(dev->config.dc_pin), PIN_LOW);
    len = rt_spi_send(&dev->parent, (const void *)&cmd, 1);
    if (len != 1)
    {
        LOG_I("sent %d", len);
        return -RT_ERROR;
    }
    else
    {
        return RT_EOK;
    }
}

rt_err_t st7789_write_data(struct drv_lcd_device *dev, const rt_uint8_t data)
{
    rt_size_t len;
    rt_pin_write(rt_pin_get(dev->config.dc_pin), PIN_HIGH);
    len = rt_spi_send(&dev->parent, (const void *)&data, 1);
    if (len != 1)
    {
        LOG_I("sent %d", len);
        return -RT_ERROR;
    }

    return RT_EOK;
}

rt_err_t st7789_init(struct drv_lcd_device *dev)
{
    struct rt_spi_device *lcd_spi_handle = &dev->parent;

    rt_pin_write(rt_pin_get(dev->config.reset_pin), PIN_LOW);
    rt_thread_mdelay(10);
    rt_pin_write(rt_pin_get(dev->config.reset_pin), PIN_HIGH);
    rt_thread_mdelay(120);

    st7789_write_cmd(dev, 0x11); // Sleep out
    rt_thread_mdelay(10);       // Delay 10ms

    st7789_write_cmd(dev, 0x36);

    st7789_write_data(dev, 0x00);

    st7789_write_cmd(dev, 0x3A);
    st7789_write_data(dev, 0X55);

    st7789_write_cmd(dev, 0xB2); //	Porch control
    st7789_write_data(dev, 0x0C);
    st7789_write_data(dev, 0x0C);
    st7789_write_data(dev, 0x00);
    st7789_write_data(dev, 0x33);
    st7789_write_data(dev, 0x33);

    /* Internal LCD Voltage generator settings */
    st7789_write_cmd(dev, 0xB7);  //	Gate Control
    st7789_write_data(dev, 0x35); //	Default value

    st7789_write_cmd(dev, 0xBB);  //	VCOM setting
    st7789_write_data(dev, 0x19); //	0.725v (default 0.75v for 0x20)

    st7789_write_cmd(dev, 0xC0);  //	LCMCTRL
    st7789_write_data(dev, 0x2C); //	Default value

    st7789_write_cmd(dev, 0xC2);  //	VDV and VRH command Enable
    st7789_write_data(dev, 0x01); //	Default value

    st7789_write_cmd(dev, 0xC3);  //	VRH set
    st7789_write_data(dev, 0x12); //	+-4.45v (defalut +-4.1v for 0x0B)

    st7789_write_cmd(dev, 0xC4);  //	VDV set
    st7789_write_data(dev, 0x20); //	Default value

    st7789_write_cmd(dev, 0xC6);  //	Frame rate control in normal mode
    st7789_write_data(dev, 0x0F); //	Default value (60HZ)

    st7789_write_cmd(dev, 0xD0);  //	Power control
    st7789_write_data(dev, 0xA4); //	Default value
    st7789_write_data(dev, 0xA1); //	Default value

    st7789_write_cmd(dev, 0xE0);
    st7789_write_data(dev, 0xD0);
    st7789_write_data(dev, 0x04);
    st7789_write_data(dev, 0x0D);
    st7789_write_data(dev, 0x11);
    st7789_write_data(dev, 0x13);
    st7789_write_data(dev, 0x2B);
    st7789_write_data(dev, 0x3F);
    st7789_write_data(dev, 0x54);
    st7789_write_data(dev, 0x4C);
    st7789_write_data(dev, 0x18);
    st7789_write_data(dev, 0x0D);
    st7789_write_data(dev, 0x0B);
    st7789_write_data(dev, 0x1F);
    st7789_write_data(dev, 0x23);

    st7789_write_cmd(dev, 0xE1);
    st7789_write_data(dev, 0xD0);
    st7789_write_data(dev, 0x04);
    st7789_write_data(dev, 0x0C);
    st7789_write_data(dev, 0x11);
    st7789_write_data(dev, 0x13);
    st7789_write_data(dev, 0x2C);
    st7789_write_data(dev, 0x3F);
    st7789_write_data(dev, 0x44);
    st7789_write_data(dev, 0x51);
    st7789_write_data(dev, 0x2F);
    st7789_write_data(dev, 0x1F);
    st7789_write_data(dev, 0x1F);
    st7789_write_data(dev, 0x20);
    st7789_write_data(dev, 0x23);

    st7789_write_cmd(dev, 0x21); //	Inversion ON
    st7789_write_cmd(dev, 0x11); //	Out of sleep mode
    st7789_write_cmd(dev, 0x13); //	Normal Display on
    st7789_write_cmd(dev, 0x29); //	Main screen turned on
}

void st7789_address_set(struct drv_lcd_device *dev, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
    st7789_write_cmd(dev, 0x2a); // 列地址设置
    st7789_write_data(dev, x1 >> 8);
    st7789_write_data(dev, x1 & 0xFF);
    st7789_write_data(dev, x2 >> 8);
    st7789_write_data(dev, x2 & 0xFF);

    st7789_write_cmd(dev, 0x2b); // 行地址设置
    st7789_write_data(dev, y1 >> 8);
    st7789_write_data(dev, y1 & 0xFF);
    st7789_write_data(dev, y2 >> 8);
    st7789_write_data(dev, y2 & 0xFF);

    st7789_write_cmd(dev, 0x2c); // 储存器写
    rt_pin_write(rt_pin_get(dev->config.dc_pin), PIN_HIGH);
}

void st7789_lcd_fill(struct drv_lcd_device *dev, uint16_t xsta, uint16_t ysta, uint16_t xend, uint16_t yend, uint16_t color)
{
    st7789_address_set(dev, xsta, ysta, xend - 1, yend - 1); // 设置显示范围
    for (uint16_t i = ysta; i < yend; i++)
    {
        for (uint16_t j = xsta; j < xend; j++)
        {
            st7789_write_data(dev, color >> 8);
            st7789_write_data(dev, color);
        }
    }
}