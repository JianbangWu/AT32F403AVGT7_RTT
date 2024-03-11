#include "st7796.h"

#define DRV_DEBUG
#define LOG_TAG "st7796"
#include <drv_log.h>

rt_err_t st7796_write_cmd(struct drv_lcd_config *dev, const rt_uint8_t cmd)
{
    rt_size_t len;
    rt_pin_write(rt_pin_get(dev->dc_pin), PIN_LOW);
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

rt_err_t st7796_write_data(struct drv_lcd_config *dev, const rt_uint8_t data)
{
    rt_size_t len;
    rt_pin_write(rt_pin_get(dev->dc_pin), PIN_HIGH);
    len = rt_spi_send(&dev->parent, (const void *)&data, 1);
    if (len != 1)
    {
        LOG_I("sent. %d", len);
        return -RT_ERROR;
    }
    else
    {
        return RT_EOK;
    }
}

rt_err_t st7796_init(struct drv_lcd_config *dev)
{

    struct rt_spi_device *lcd_spi_handle = &dev->parent;

    // rt_kprintf("find %s device!\n", dev->bus_name);
    // {
    //     struct rt_spi_configuration cfg;
    //     cfg.data_width = 8;
    //     cfg.mode = RT_SPI_MODE_0 | RT_SPI_MSB; /* SPI Compatible: Mode 0 and Mode 3 */
    //     cfg.max_hz = 50 * 1000 * 1000;         /* 50M */
    //     rt_spi_configure(lcd_spi_handle, &cfg);
    // }

    rt_pin_write(rt_pin_get(dev->reset_pin), PIN_LOW);
    rt_thread_mdelay(10);

    rt_pin_write(rt_pin_get(dev->reset_pin), PIN_HIGH);
    rt_thread_mdelay(10);

    st7796_write_cmd(dev, 0x11);
    rt_thread_mdelay(120);

    st7796_write_cmd(dev, 0Xf0);
    st7796_write_data(dev, 0xc3);
    st7796_write_cmd(dev, 0Xf0);
    st7796_write_data(dev, 0x96);

    st7796_write_cmd(dev, 0x36); // !!!Display Direction!!!
    st7796_write_data(dev, 0x48);

    st7796_write_cmd(dev, 0X3a);
    st7796_write_data(dev, 0x05);
    st7796_write_cmd(dev, 0Xe6);
    st7796_write_data(dev, 0x0f);
    st7796_write_data(dev, 0xf2);
    st7796_write_data(dev, 0x3f);
    st7796_write_data(dev, 0x4f);
    st7796_write_data(dev, 0x4f);
    st7796_write_data(dev, 0x28);
    st7796_write_data(dev, 0x0e);
    st7796_write_data(dev, 0x00);

    st7796_write_cmd(dev, 0Xc5);
    st7796_write_data(dev, 0x2a);

    st7796_write_cmd(dev, 0Xe0);
    st7796_write_data(dev, 0xf0);
    st7796_write_data(dev, 0x03);
    st7796_write_data(dev, 0x0a);
    st7796_write_data(dev, 0x11);
    st7796_write_data(dev, 0x14);
    st7796_write_data(dev, 0x1c);
    st7796_write_data(dev, 0x3b);
    st7796_write_data(dev, 0x55);
    st7796_write_data(dev, 0x4a);
    st7796_write_data(dev, 0x0a);
    st7796_write_data(dev, 0x13);
    st7796_write_data(dev, 0x14);
    st7796_write_data(dev, 0x1c);
    st7796_write_data(dev, 0x1f);
    st7796_write_cmd(dev, 0Xe1);
    st7796_write_data(dev, 0xf0);
    st7796_write_data(dev, 0x03);
    st7796_write_data(dev, 0x0a);
    st7796_write_data(dev, 0x0c);
    st7796_write_data(dev, 0x0c);
    st7796_write_data(dev, 0x09);
    st7796_write_data(dev, 0x36);
    st7796_write_data(dev, 0x54);
    st7796_write_data(dev, 0x49);
    st7796_write_data(dev, 0x0f);
    st7796_write_data(dev, 0x1b);
    st7796_write_data(dev, 0x18);
    st7796_write_data(dev, 0x1b);
    st7796_write_data(dev, 0x1f);
    st7796_write_cmd(dev, 0Xf0);
    st7796_write_data(dev, 0x3c);
    st7796_write_cmd(dev, 0Xf0);
    st7796_write_data(dev, 0x69);
    st7796_write_cmd(dev, 0X29);
    st7796_write_cmd(dev, 0X21);
}

void st7796_address_set(struct drv_lcd_config *dev, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
    st7796_write_cmd(dev, 0x2a); // 列地址设置
    st7796_write_data(dev, x1 >> 8);
    st7796_write_data(dev, x1 & 0xFF);
    st7796_write_data(dev, x2 >> 8);
    st7796_write_data(dev, x2 & 0xFF);

    st7796_write_cmd(dev, 0x2b); // 行地址设置
    st7796_write_data(dev, y1 >> 8);
    st7796_write_data(dev, y1 & 0xFF);
    st7796_write_data(dev, y2 >> 8);
    st7796_write_data(dev, y2 & 0xFF);

    st7796_write_cmd(dev, 0x2c); // 储存器写
    rt_pin_write(rt_pin_get(dev->dc_pin), PIN_HIGH);
}

void st7796_lcd_fill(struct drv_lcd_config *dev, uint16_t xsta, uint16_t ysta, uint16_t xend, uint16_t yend, uint16_t color)
{
    st7796_address_set(dev, xsta, ysta, xend - 1, yend - 1); // 设置显示范围
    for (uint16_t i = ysta; i < yend; i++)
    {
        for (uint16_t j = xsta; j < xend; j++)
        {
            st7796_write_data(dev, color >> 8);
            st7796_write_data(dev, color);
        }
    }
}