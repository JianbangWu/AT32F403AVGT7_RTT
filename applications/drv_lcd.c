#include "rtthread.h"
#include "rtdevice.h"
#include "drv_spi.h"
#include "drv_lcd.h"
#include "drv_gpio.h"

#define DRV_DEBUG
#define LOG_TAG "drv_lcd"
#include <drv_log.h>

#define PIN_NUM(port, no) (((((port) & 0xFu) << 4) | ((no) & 0xFu)))
#define PIN_PORT(pin) ((uint8_t)(((pin) >> 4) & 0xFu))
#define PIN_NO(pin) ((uint8_t)((pin) & 0xFu))

#define PIN_ATPORT(pin) ((gpio_type *)(GPIOA_BASE + (0x400u * PIN_PORT(pin))))
#define PIN_ATPIN(pin) ((uint16_t)(1u << PIN_NO(pin)))

static struct drv_lcd_config lcd_config[] = {
#ifdef BSP_USING_LCD1
    LCD1_CONFIG,
#endif

#ifdef BSP_USING_LCD2
    LCD2_CONFIG,
#endif

#ifdef BSP_USING_LCD3
    LCD3_CONFIG,
#endif

#ifdef BSP_USING_LCD4
    LCD4_CONFIG,
#endif
};

// static struct rt_device_graphic_info lcd_info[] = {
// #ifdef BSP_USING_LCD1
//     LCD1_INFO,
// #endif

// #ifdef BSP_USING_LCD2
//     LCD2_INFO,
// #endif

// #ifdef BSP_USING_LCD3
//     LCD3_INFO,
// #endif

// #ifdef BSP_USING_LCD4
//     LCD4_INFO,
// #endif
// };

#include "st7796.h"
#include "gc9a01.h"
static rt_err_t drv_lcd_init(struct drv_lcd_config *dev)
{
    if (dev->lcd_chip == "st7796")
    {
        LOG_D("now initing %s on %s ", dev->lcd_chip, dev->bus_name);
        rt_pin_write(&dev->bkl_pin, PIN_HIGH);
        st7796_init(dev);
    }
    if (dev->lcd_chip == "gc9a01")
    {
        LOG_D("now initing %s on %s ", dev->lcd_chip, dev->bus_name);
        rt_pin_write(&dev->bkl_pin, PIN_HIGH);
        gc9a01_init(dev);
    }
}

int drv_lcd_hw_init(void)
{

    rt_size_t obj_num = sizeof(lcd_config) / sizeof(lcd_config[0]);

    for (size_t i = 0; i < obj_num; i++)
    {
        // lcd_config[i].lcd_info = &lcd_info[i];
        gpio_init_type gpio_init_struct;
        rt_err_t result;

        struct drv_lcd_config *lcd_device;
        struct rt_spi_device *spi_device;
        struct at32_spi_cs *spi_cs;

        /* attach the device to spi bus */
        lcd_device = (struct drv_lcd_config *)rt_malloc(sizeof(struct drv_lcd_config));
        RT_ASSERT(lcd_device != RT_NULL);
        // spi_device = (struct rt_spi_device *)rt_malloc(sizeof(struct rt_spi_device));
        spi_device = &lcd_device->parent;
        RT_ASSERT(spi_device != RT_NULL);

        {
            lcd_device->bus_name = lcd_config[i].bus_name;
            lcd_device->lcd_name = lcd_config[i].lcd_name;
            lcd_device->lcd_chip = lcd_config[i].lcd_chip;
            lcd_device->dc_pin = lcd_config[i].dc_pin;
            lcd_device->cs_pin = lcd_config[i].cs_pin;
            lcd_device->reset_pin = lcd_config[i].reset_pin;
            lcd_device->bkl_pin = lcd_config[i].bkl_pin;
            lcd_device->bkl_type = lcd_config[i].bkl_type;
        }


        rt_pin_mode(rt_pin_get(lcd_device->dc_pin), PIN_MODE_OUTPUT);
        rt_pin_mode(rt_pin_get(lcd_device->cs_pin), PIN_MODE_OUTPUT);
        rt_pin_mode(rt_pin_get(lcd_device->reset_pin), PIN_MODE_OUTPUT);
        rt_pin_mode(rt_pin_get(lcd_device->bkl_pin), PIN_MODE_OUTPUT);

        rt_pin_write(rt_pin_get(lcd_device->bkl_pin), PIN_HIGH);
        
        spi_cs = (struct at32_spi_cs *)rt_malloc(sizeof(struct at32_spi_cs));
        RT_ASSERT(spi_cs != RT_NULL);

        spi_cs->gpio_x = PIN_ATPORT(rt_pin_get(lcd_device->cs_pin));
        spi_cs->gpio_pin = PIN_ATPIN(rt_pin_get(lcd_device->cs_pin));

        result = rt_spi_bus_attach_device(spi_device, lcd_device->lcd_name, lcd_device->bus_name, (void *)spi_cs);

        {
            struct rt_spi_configuration cfg;
            cfg.data_width = 8;
            cfg.mode = RT_SPI_MODE_0 | RT_SPI_MSB; /* SPI Compatible: Mode 0 and Mode 3 */
            cfg.max_hz = 50 * 1000 * 1000;         /* 50M */
            rt_spi_configure(spi_device, &cfg);
        }

        drv_lcd_init(spi_device);

        if (result != RT_EOK)
        {
            LOG_D("%s attach to %s faild, %d\n", lcd_device->lcd_name, lcd_device->bus_name, result);
            return result;
        }
        RT_ASSERT(result == RT_EOK);
        LOG_D("%s attach to %s done", lcd_device->lcd_name, lcd_device->bus_name);
    }
}
INIT_DEVICE_EXPORT(drv_lcd_hw_init);