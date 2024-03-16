#include "gc9a01.h"

#define DRV_DEBUG
#define LOG_TAG "gc9a01"
#include <drv_log.h>

rt_err_t gc9a01_write_cmd(struct drv_lcd_config *dev, const rt_uint8_t cmd)
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

rt_err_t gc9a01_write_data(struct drv_lcd_config *dev, const rt_uint8_t data)
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

rt_err_t gc9a01_init(struct drv_lcd_config *dev)
{
    struct rt_spi_device *lcd_spi_handle = &dev->parent;

    // rt_pin_write(rt_pin_get(dev->reset_pin), PIN_LOW);
    // rt_thread_mdelay(10);
    // rt_pin_write(rt_pin_get(dev->reset_pin), PIN_HIGH);
    // rt_thread_mdelay(120);

#if 1
 {
    gc9a01_write_cmd(dev, 0xFE);
    gc9a01_write_cmd(dev, 0xEF);

    gc9a01_write_cmd(dev, 0xEB);
    gc9a01_write_data(dev, 0x14);

    gc9a01_write_cmd(dev, 0x84);
    gc9a01_write_data(dev, 0x40);

    gc9a01_write_cmd(dev, 0x86);
    gc9a01_write_data(dev, 0xFF);

    gc9a01_write_cmd(dev, 0xC0);
    gc9a01_write_data(dev, 0x1A);

    gc9a01_write_cmd(dev, 0x88);
    gc9a01_write_data(dev, 0x0A);

    gc9a01_write_cmd(dev, 0x89);
    gc9a01_write_data(dev, 0x21);

    gc9a01_write_cmd(dev, 0x8A);
    gc9a01_write_data(dev, 0x00);

    gc9a01_write_cmd(dev, 0x8B);
    gc9a01_write_data(dev, 0x80);

    gc9a01_write_cmd(dev, 0x8C);
    gc9a01_write_data(dev, 0x01);

    gc9a01_write_cmd(dev, 0x8D);
    gc9a01_write_data(dev, 0x01);

    gc9a01_write_cmd(dev, 0x8F);
    gc9a01_write_data(dev, 0xFF);

    gc9a01_write_cmd(dev, 0xB6);
    gc9a01_write_data(dev, 0x20);

    gc9a01_write_cmd(dev, 0x36);
    gc9a01_write_data(dev, 0x48);

    gc9a01_write_cmd(dev, 0x3A);  // Pixel Format set
    gc9a01_write_data(dev, 0x05); // 16bits

    gc9a01_write_cmd(dev, 0x90);
    gc9a01_write_data(dev, 0x08);
    gc9a01_write_data(dev, 0x08);
    gc9a01_write_data(dev, 0x08);
    gc9a01_write_data(dev, 0x08);

    gc9a01_write_cmd(dev, 0xBD);
    gc9a01_write_data(dev, 0x06);

    gc9a01_write_cmd(dev, 0xBC);
    gc9a01_write_data(dev, 0x00);

    gc9a01_write_cmd(dev, 0xFF);
    gc9a01_write_data(dev, 0x60);
    gc9a01_write_data(dev, 0x01);
    gc9a01_write_data(dev, 0x04);

    // gc9a01_write_cmd(dev, 0xC3);  // VCOM for Borad
    // gc9a01_write_data(dev, 0x3d); // bit[6:0] VREG1A
    // gc9a01_write_cmd(dev, 0xC4);
    // gc9a01_write_data(dev, 0x3d); // bit[6:0] VREG2A

    // gc9a01_write_cmd(dev, 0xC9);
    // gc9a01_write_data(dev, 0x22); //

    gc9a01_write_cmd(dev, 0xBE);
    gc9a01_write_data(dev, 0x11);

    gc9a01_write_cmd(dev, 0xE1);
    gc9a01_write_data(dev, 0x10);
    gc9a01_write_data(dev, 0x0E);

    gc9a01_write_cmd(dev, 0xDF);
    gc9a01_write_data(dev, 0x21);
    gc9a01_write_data(dev, 0x0c);
    gc9a01_write_data(dev, 0x02);

    //----------Negative-----------
    gc9a01_write_cmd(dev, 0xF0);
    gc9a01_write_data(dev, 0x45); // VR62[5:0]
    gc9a01_write_data(dev, 0x09); // VR61[5:0]
    gc9a01_write_data(dev, 0x08); // VR59[4:0]
    gc9a01_write_data(dev, 0x08); // VR57[4:0]
    gc9a01_write_data(dev, 0x26); // VR63[7:4]/VR50[3:0]
    gc9a01_write_data(dev, 0x2A); // VR43[6:0]

    gc9a01_write_cmd(dev, 0xF1);
    gc9a01_write_data(dev, 0x43); // VR20[6:0]
    gc9a01_write_data(dev, 0x70); // VR36[7:5]/VR6[4:0]
    gc9a01_write_data(dev, 0x72); // VR27[7:5]/VR4[4:0]
    gc9a01_write_data(dev, 0x36); // VR2[5:0]
    gc9a01_write_data(dev, 0x37); // VR1[5:0]
    gc9a01_write_data(dev, 0x6F); // VR13[7:4]/VR0[3:0]

    //----------Positive-----------
    gc9a01_write_cmd(dev, 0xF2);
    gc9a01_write_data(dev, 0x45); // VR62[5:0]
    gc9a01_write_data(dev, 0x09); // VR61[5:0]
    gc9a01_write_data(dev, 0x08); // VR59[4:0]
    gc9a01_write_data(dev, 0x08); // VR57[4:0]
    gc9a01_write_data(dev, 0x26); // VR63[7:4]/VR50[3:0]
    gc9a01_write_data(dev, 0x2A); // VR43[6:0]

    gc9a01_write_cmd(dev, 0xF3);
    gc9a01_write_data(dev, 0x43); // VR20[6:0]
    gc9a01_write_data(dev, 0x70); // VR36[7:5]/VR6[4:0]
    gc9a01_write_data(dev, 0x72); // VR27[7:5]/VR4[4:0]
    gc9a01_write_data(dev, 0x36); // VR2[5:0]
    gc9a01_write_data(dev, 0x37); // VR1[5:0]
    gc9a01_write_data(dev, 0x6F); // VR13[7:4]/VR0[3:0]

    gc9a01_write_cmd(dev, 0xED);
    gc9a01_write_data(dev, 0x1B);
    gc9a01_write_data(dev, 0x8B);

    gc9a01_write_cmd(dev, 0xAE);
    gc9a01_write_data(dev, 0x77);

    gc9a01_write_cmd(dev, 0xCD);
    gc9a01_write_data(dev, 0x63);

    gc9a01_write_cmd(dev, 0xAC);
    gc9a01_write_data(dev, 0x27); // 44

    gc9a01_write_cmd(dev, 0x70); // VGH VGL_CLK
    gc9a01_write_data(dev, 0x07);
    gc9a01_write_data(dev, 0x07);
    gc9a01_write_data(dev, 0x04);
    gc9a01_write_data(dev, 0x06); // bit[4:0] VGH 01
    gc9a01_write_data(dev, 0x0F); // bit[4:0] VGL
    gc9a01_write_data(dev, 0x09);
    gc9a01_write_data(dev, 0x07);
    gc9a01_write_data(dev, 0x08);
    gc9a01_write_data(dev, 0x03);

    gc9a01_write_cmd(dev, 0xE8);
    gc9a01_write_data(dev, 0x04); // 04:column 14:1-dot 24:2-dot inversion

    gc9a01_write_cmd(dev, 0x62);
    gc9a01_write_data(dev, 0x18);
    gc9a01_write_data(dev, 0x0D);
    gc9a01_write_data(dev, 0x71);
    gc9a01_write_data(dev, 0xED);
    gc9a01_write_data(dev, 0x70);
    gc9a01_write_data(dev, 0x70);
    gc9a01_write_data(dev, 0x18);
    gc9a01_write_data(dev, 0x0F);
    gc9a01_write_data(dev, 0x71);
    gc9a01_write_data(dev, 0xEF);
    gc9a01_write_data(dev, 0x70);
    gc9a01_write_data(dev, 0x70);

    gc9a01_write_cmd(dev, 0x63);
    gc9a01_write_data(dev, 0x18);
    gc9a01_write_data(dev, 0x11);
    gc9a01_write_data(dev, 0x71);
    gc9a01_write_data(dev, 0xF1);
    gc9a01_write_data(dev, 0x70);
    gc9a01_write_data(dev, 0x70);
    gc9a01_write_data(dev, 0x18);
    gc9a01_write_data(dev, 0x13);
    gc9a01_write_data(dev, 0x71);
    gc9a01_write_data(dev, 0xF3);
    gc9a01_write_data(dev, 0x70);
    gc9a01_write_data(dev, 0x70);

    gc9a01_write_cmd(dev, 0x64);
    gc9a01_write_data(dev, 0x28);
    gc9a01_write_data(dev, 0x29);
    gc9a01_write_data(dev, 0xF1);
    gc9a01_write_data(dev, 0x01);
    gc9a01_write_data(dev, 0xF1);
    gc9a01_write_data(dev, 0x00);
    gc9a01_write_data(dev, 0x07);

    gc9a01_write_cmd(dev, 0x66);
    gc9a01_write_data(dev, 0x3C);
    gc9a01_write_data(dev, 0x00);
    gc9a01_write_data(dev, 0xCD);
    gc9a01_write_data(dev, 0x67);
    gc9a01_write_data(dev, 0x45);
    gc9a01_write_data(dev, 0x45);
    gc9a01_write_data(dev, 0x10);
    gc9a01_write_data(dev, 0x00);
    gc9a01_write_data(dev, 0x00);
    gc9a01_write_data(dev, 0x00);

    gc9a01_write_cmd(dev, 0x67);
    gc9a01_write_data(dev, 0x00);
    gc9a01_write_data(dev, 0x3C);
    gc9a01_write_data(dev, 0x00);
    gc9a01_write_data(dev, 0x00);
    gc9a01_write_data(dev, 0x00);
    gc9a01_write_data(dev, 0x01);
    gc9a01_write_data(dev, 0x54);
    gc9a01_write_data(dev, 0x10);
    gc9a01_write_data(dev, 0x32);
    gc9a01_write_data(dev, 0x98);

    gc9a01_write_cmd(dev, 0x74); // frame rate
    gc9a01_write_data(dev, 0x10);
    gc9a01_write_data(dev, 0x85); // 60Hz
    gc9a01_write_data(dev, 0x80);
    gc9a01_write_data(dev, 0x00); // bit[4:0] VGH
    gc9a01_write_data(dev, 0x00); // bit[4:0] VGL
    gc9a01_write_data(dev, 0x4E);
    gc9a01_write_data(dev, 0x00);

    gc9a01_write_cmd(dev, 0x98);
    gc9a01_write_data(dev, 0x3e);
    gc9a01_write_data(dev, 0x07);

    gc9a01_write_cmd(dev, 0x35);
    gc9a01_write_cmd(dev, 0x21);
    rt_thread_mdelay(10);
    //--------end gamma setting--------------//

    gc9a01_write_cmd(dev, 0x11);
    rt_thread_mdelay(10);
    gc9a01_write_cmd(dev, 0x29);
    rt_thread_mdelay(10);
    // gc9a01_write_cmd(dev, 0x2C);
}
#else 
{
    gc9a01_write_cmd(dev, 0xEF);
    gc9a01_write_cmd(dev, 0xEB);
    gc9a01_write_data(dev, 0x14);

    gc9a01_write_cmd(dev, 0xFE);
    gc9a01_write_cmd(dev, 0xEF);

    gc9a01_write_cmd(dev, 0xEB);
    gc9a01_write_data(dev, 0x14);

    gc9a01_write_cmd(dev, 0x84);
    gc9a01_write_data(dev, 0x40);

    gc9a01_write_cmd(dev, 0x85);
    gc9a01_write_data(dev, 0xFF);

    gc9a01_write_cmd(dev, 0x86);
    gc9a01_write_data(dev, 0xFF);

    gc9a01_write_cmd(dev, 0x87);
    gc9a01_write_data(dev, 0xFF);

    gc9a01_write_cmd(dev, 0x88);
    gc9a01_write_data(dev, 0x0A);

    gc9a01_write_cmd(dev, 0x89);
    gc9a01_write_data(dev, 0x21);

    gc9a01_write_cmd(dev, 0x8A);
    gc9a01_write_data(dev, 0x00);

    gc9a01_write_cmd(dev, 0x8B);
    gc9a01_write_data(dev, 0x80);

    gc9a01_write_cmd(dev, 0x8C);
    gc9a01_write_data(dev, 0x01);

    gc9a01_write_cmd(dev, 0x8D);
    gc9a01_write_data(dev, 0x01);

    gc9a01_write_cmd(dev, 0x8E);
    gc9a01_write_data(dev, 0xFF);

    gc9a01_write_cmd(dev, 0x8F);
    gc9a01_write_data(dev, 0xFF);

    gc9a01_write_cmd(dev, 0xB6);
    gc9a01_write_data(dev, 0x00);
    gc9a01_write_data(dev, 0x20);

    gc9a01_write_cmd(dev, 0x36);
    gc9a01_write_data(dev, 0x08);

    gc9a01_write_cmd(dev, 0x3A);
    gc9a01_write_data(dev, 0x05);

    gc9a01_write_cmd(dev, 0x90);
    gc9a01_write_data(dev, 0x08);
    gc9a01_write_data(dev, 0x08);
    gc9a01_write_data(dev, 0x08);
    gc9a01_write_data(dev, 0x08);

    gc9a01_write_cmd(dev, 0xBD);
    gc9a01_write_data(dev, 0x06);

    gc9a01_write_cmd(dev, 0xBC);
    gc9a01_write_data(dev, 0x00);

    gc9a01_write_cmd(dev, 0xFF);
    gc9a01_write_data(dev, 0x60);
    gc9a01_write_data(dev, 0x01);
    gc9a01_write_data(dev, 0x04);

    gc9a01_write_cmd(dev, 0xC3);
    gc9a01_write_data(dev, 0x13);
    gc9a01_write_cmd(dev, 0xC4);
    gc9a01_write_data(dev, 0x13);

    gc9a01_write_cmd(dev, 0xC9);
    gc9a01_write_data(dev, 0x22);

    gc9a01_write_cmd(dev, 0xBE);
    gc9a01_write_data(dev, 0x11);

    gc9a01_write_cmd(dev, 0xE1);
    gc9a01_write_data(dev, 0x10);
    gc9a01_write_data(dev, 0x0E);

    gc9a01_write_cmd(dev, 0xDF);
    gc9a01_write_data(dev, 0x21);
    gc9a01_write_data(dev, 0x0c);
    gc9a01_write_data(dev, 0x02);

    gc9a01_write_cmd(dev, 0xF0);
    gc9a01_write_data(dev, 0x45);
    gc9a01_write_data(dev, 0x09);
    gc9a01_write_data(dev, 0x08);
    gc9a01_write_data(dev, 0x08);
    gc9a01_write_data(dev, 0x26);
    gc9a01_write_data(dev, 0x2A);

    gc9a01_write_cmd(dev, 0xF1);
    gc9a01_write_data(dev, 0x43);
    gc9a01_write_data(dev, 0x70);
    gc9a01_write_data(dev, 0x72);
    gc9a01_write_data(dev, 0x36);
    gc9a01_write_data(dev, 0x37);
    gc9a01_write_data(dev, 0x6F);

    gc9a01_write_cmd(dev, 0xF2);
    gc9a01_write_data(dev, 0x45);
    gc9a01_write_data(dev, 0x09);
    gc9a01_write_data(dev, 0x08);
    gc9a01_write_data(dev, 0x08);
    gc9a01_write_data(dev, 0x26);
    gc9a01_write_data(dev, 0x2A);

    gc9a01_write_cmd(dev, 0xF3);
    gc9a01_write_data(dev, 0x43);
    gc9a01_write_data(dev, 0x70);
    gc9a01_write_data(dev, 0x72);
    gc9a01_write_data(dev, 0x36);
    gc9a01_write_data(dev, 0x37);
    gc9a01_write_data(dev, 0x6F);

    gc9a01_write_cmd(dev, 0xED);
    gc9a01_write_data(dev, 0x1B);
    gc9a01_write_data(dev, 0x0B);

    gc9a01_write_cmd(dev, 0xAE);
    gc9a01_write_data(dev, 0x77);

    gc9a01_write_cmd(dev, 0xCD);
    gc9a01_write_data(dev, 0x63);

    gc9a01_write_cmd(dev, 0x70);
    gc9a01_write_data(dev, 0x07);
    gc9a01_write_data(dev, 0x07);
    gc9a01_write_data(dev, 0x04);
    gc9a01_write_data(dev, 0x0E);
    gc9a01_write_data(dev, 0x0F);
    gc9a01_write_data(dev, 0x09);
    gc9a01_write_data(dev, 0x07);
    gc9a01_write_data(dev, 0x08);
    gc9a01_write_data(dev, 0x03);

    gc9a01_write_cmd(dev, 0xE8);
    gc9a01_write_data(dev, 0x34);

    gc9a01_write_cmd(dev, 0x62);
    gc9a01_write_data(dev, 0x18);
    gc9a01_write_data(dev, 0x0D);
    gc9a01_write_data(dev, 0x71);
    gc9a01_write_data(dev, 0xED);
    gc9a01_write_data(dev, 0x70);
    gc9a01_write_data(dev, 0x70);
    gc9a01_write_data(dev, 0x18);
    gc9a01_write_data(dev, 0x0F);
    gc9a01_write_data(dev, 0x71);
    gc9a01_write_data(dev, 0xEF);
    gc9a01_write_data(dev, 0x70);
    gc9a01_write_data(dev, 0x70);

    gc9a01_write_cmd(dev, 0x63);
    gc9a01_write_data(dev, 0x18);
    gc9a01_write_data(dev, 0x11);
    gc9a01_write_data(dev, 0x71);
    gc9a01_write_data(dev, 0xF1);
    gc9a01_write_data(dev, 0x70);
    gc9a01_write_data(dev, 0x70);
    gc9a01_write_data(dev, 0x18);
    gc9a01_write_data(dev, 0x13);
    gc9a01_write_data(dev, 0x71);
    gc9a01_write_data(dev, 0xF3);
    gc9a01_write_data(dev, 0x70);
    gc9a01_write_data(dev, 0x70);

    gc9a01_write_cmd(dev, 0x64);
    gc9a01_write_data(dev, 0x28);
    gc9a01_write_data(dev, 0x29);
    gc9a01_write_data(dev, 0xF1);
    gc9a01_write_data(dev, 0x01);
    gc9a01_write_data(dev, 0xF1);
    gc9a01_write_data(dev, 0x00);
    gc9a01_write_data(dev, 0x07);

    gc9a01_write_cmd(dev, 0x66);
    gc9a01_write_data(dev, 0x3C);
    gc9a01_write_data(dev, 0x00);
    gc9a01_write_data(dev, 0xCD);
    gc9a01_write_data(dev, 0x67);
    gc9a01_write_data(dev, 0x45);
    gc9a01_write_data(dev, 0x45);
    gc9a01_write_data(dev, 0x10);
    gc9a01_write_data(dev, 0x00);
    gc9a01_write_data(dev, 0x00);
    gc9a01_write_data(dev, 0x00);

    gc9a01_write_cmd(dev, 0x67);
    gc9a01_write_data(dev, 0x00);
    gc9a01_write_data(dev, 0x3C);
    gc9a01_write_data(dev, 0x00);
    gc9a01_write_data(dev, 0x00);
    gc9a01_write_data(dev, 0x00);
    gc9a01_write_data(dev, 0x01);
    gc9a01_write_data(dev, 0x54);
    gc9a01_write_data(dev, 0x10);
    gc9a01_write_data(dev, 0x32);
    gc9a01_write_data(dev, 0x98);

    gc9a01_write_cmd(dev, 0x74);
    gc9a01_write_data(dev, 0x10);
    gc9a01_write_data(dev, 0x85);
    gc9a01_write_data(dev, 0x80);
    gc9a01_write_data(dev, 0x00);
    gc9a01_write_data(dev, 0x00);
    gc9a01_write_data(dev, 0x4E);
    gc9a01_write_data(dev, 0x00);

    gc9a01_write_cmd(dev, 0x98);
    gc9a01_write_data(dev, 0x3e);
    gc9a01_write_data(dev, 0x07);

    gc9a01_write_cmd(dev, 0x11);
    rt_thread_mdelay(120);

    gc9a01_write_cmd(dev, 0x34); // Tearing effect line off
                                 //  gc9a01_write_cmd(dev, 0x35); // Tearing effect line on
                                 //  gc9a01_write_cmd(dev, 0x20); // Display inversion off
    gc9a01_write_cmd(dev, 0x21); // Display inversion on
    gc9a01_write_cmd(dev, 0x29); // Display On
}
#endif

}

void gc9a01_address_set(struct drv_lcd_config *dev, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
    gc9a01_write_cmd(dev, 0x2a); // 列地址设置
    gc9a01_write_data(dev, x1 >> 8);
    gc9a01_write_data(dev, x1 & 0xFF);
    gc9a01_write_data(dev, x2 >> 8);
    gc9a01_write_data(dev, x2 & 0xFF);

    gc9a01_write_cmd(dev, 0x2b); // 行地址设置
    gc9a01_write_data(dev, y1 >> 8);
    gc9a01_write_data(dev, y1 & 0xFF);
    gc9a01_write_data(dev, y2 >> 8);
    gc9a01_write_data(dev, y2 & 0xFF);

    gc9a01_write_cmd(dev, 0x2c); // 储存器写
    rt_pin_write(rt_pin_get(dev->dc_pin), PIN_HIGH);
}

void gc9a01_lcd_fill(struct drv_lcd_config *dev, uint16_t xsta, uint16_t ysta, uint16_t xend, uint16_t yend, uint16_t color)
{
    gc9a01_address_set(dev, xsta, ysta, xend - 1, yend - 1); // 设置显示范围
    for (uint16_t i = ysta; i < yend; i++)
    {
        for (uint16_t j = xsta; j < xend; j++)
        {
            gc9a01_write_data(dev, color >> 8);
            gc9a01_write_data(dev, color);
        }
    }
}