
#include "bq25798.h"

static struct rt_i2c_client *bq25798_client;

static rt_err_t bq25798_write_reg(struct rt_i2c_client *dev, rt_uint8_t *write_data, rt_uint8_t write_len)
{
    struct rt_i2c_msg msgs;

    msgs.addr = dev->client_addr;
    msgs.flags = RT_I2C_WR;
    msgs.buf = write_data;
    msgs.len = write_len;

    if (rt_i2c_transfer(dev->bus, &msgs, 1) == 1)
    {
        return RT_EOK;
    }

    return RT_ERROR;
}

static rt_err_t bq25798_read_regs(struct rt_i2c_client *dev, rt_uint8_t *cmd_buf, rt_uint8_t cmd_len, rt_uint8_t *read_buf, rt_uint8_t read_len)
{
    struct rt_i2c_msg msgs[2];

    msgs[0].addr = dev->client_addr;
    msgs[0].flags = RT_I2C_WR;
    msgs[0].buf = cmd_buf;
    msgs[0].len = cmd_len;

    msgs[1].addr = dev->client_addr;
    msgs[1].flags = RT_I2C_RD;
    msgs[1].buf = read_buf;
    msgs[1].len = read_len;

    if (rt_i2c_transfer(dev->bus, msgs, 2) == 2)
    {
        return RT_EOK;
    }

    return RT_ERROR;
}

static rt_err_t bq25798_init_regs(struct bq25798_device *dev)
{
    rt_uint8_t reg[2];
    reg[0] = IBUS_ADC;
    reg[1] = 1;
    bq25798_write_reg(bq25798_client, reg, 2);
    
}

static rt_err_t bq25798_read_adc(struct bq25798_device *dev, void *buf)
{
    struct bq25798_adc *pdata = buf;
    rt_uint8_t reg_val[12];
    rt_uint8_t reg[2];

    reg[0] = IBUS_ADC;
    bq25798_read_regs(bq25798_client, reg, 1, reg_val, 4);

    pdata->ibus = (reg_val[0] << 8 + reg_val[1]);
    pdata->ibat = (reg_val[2] << 8 + reg_val[3]);
    pdata->vbus = (reg_val[4] << 8 + reg_val[5]);
    pdata->vac1 = (reg_val[6] << 8 + reg_val[7]);
    pdata->vac2 = (reg_val[8] << 8 + reg_val[9]);
    pdata->vbat = (reg_val[10] << 8 + reg_val[11]);

    pdata->timestamp = rt_tick_get();
}

int rt_hw_bq25798_register(bq25798_device_t dev, const char *name, rt_uint32_t flag, void *data)
{
    rt_err_t result;
    rt_device_t device;
    RT_ASSERT(dev != RT_NULL);

    device = &dev->parent;

#ifdef RT_USING_DEVICE_OPS
    device->ops = &rt_touch_ops;
#else
    device->init = RT_NULL;
    device->open = RT_NULL;
    device->close = RT_NULL;
    device->read = RT_NULL;
    device->write = RT_NULL;
    device->control = RT_NULL;
#endif
    device->type = RT_Device_Class_Sensor;
    device->rx_indicate = RT_NULL;
    device->tx_complete = RT_NULL;
    device->user_data = data;

    result = rt_device_register(device, name, flag | RT_DEVICE_FLAG_STANDALONE);

    if (result != RT_EOK)
    {
        LOG_E("bq25798 register err code: %d", result);
        return result;
    }

    LOG_I("bq25798 init success");
    return RT_EOK;
}

static struct bq25798_ops device_ops =
    {
        .bq25798_read_adc = bq25798_read_adc,
};

int rt_hw_bq25798_init(const char *name, struct bq25798_gpio_config *cfg)
{

    bq25798_device_t bq25798_dev = RT_NULL;

    bq25798_dev = (rt_touch_t)rt_calloc(1, sizeof(struct bq25798_device));

    if (bq25798_dev == RT_NULL)
        return -RT_ERROR;

    bq25798_client = (struct rt_i2c_client *)rt_calloc(1, sizeof(struct rt_i2c_client));
    bq25798_client->bus = (struct rt_i2c_bus_device *)rt_device_find(cfg->dev_name);
    if (bq25798_client->bus == RT_NULL)
    {
        LOG_E("Can't find device\r\n");
        return -RT_ERROR;
    }
    if (rt_device_open((rt_device_t)bq25798_client->bus, RT_DEVICE_FLAG_RDWR) != RT_EOK)
    {
        LOG_E("open bus failed\r\n");
        return -RT_ERROR;
    }

    /* hardware init */
    rt_pin_mode(cfg->irq_pin.pin, cfg->irq_pin.mode);
    rt_pin_mode(cfg->charge_en_pin.pin, cfg->charge_en_pin.mode);
    rt_pin_mode(cfg->ship_fet_en_pin.pin, cfg->ship_fet_en_pin.mode);

    bq25798_client->client_addr = BQ25798_DEV_ADDR;

    bq25798_dev->ops = &device_ops;

    /* register bq25798 device */
    rt_hw_bq25798_register(bq25798_dev, "bq25798", RT_DEVICE_FLAG_INT_RX, RT_NULL);

    LOG_I("touch device bq25798 init success\n");

    return RT_EOK;
}

int rt_hw_bq25798_port(void)
{
    struct bq25798_gpio_config config;

    config.dev_name = "i2c1";
    config.irq_pin.pin = rt_pin_get("PE.1");
    config.irq_pin.mode = PIN_MODE_INPUT;

    config.charge_en_pin.pin = rt_pin_get("PE.1");
    config.charge_en_pin.mode = PIN_MODE_OUTPUT;

    config.ship_fet_en_pin.pin = rt_pin_get("PE.1");
    config.ship_fet_en_pin.mode = PIN_MODE_OUTPUT;

    rt_hw_bq25798_init("bq25798", &config);

    return 0;
}
// INIT_PREV_EXPORT(rt_hw_bq25798_port);
