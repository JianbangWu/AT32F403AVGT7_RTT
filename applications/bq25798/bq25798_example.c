#include <rtthread.h>
#include <rtdevice.h>

#include "bq25798.h"

#define THREAD_PRIORITY 25
#define THREAD_STACK_SIZE 1024
#define THREAD_TIMESLICE 5

static rt_thread_t bq25798_thread = RT_NULL;
static rt_sem_t bq25798_sem = RT_NULL;
static bq25798_device_t dev = RT_NULL;
static struct bq25798_adc read_data;

static void bq25798_entry(void *parameter)
{
    while (1)
    {
        rt_sem_take(bq25798_sem, RT_WAITING_FOREVER);
        rt_uint32_t tick_old;
        if (read_data.timestamp != tick_old)
        {
            dev->ops->bq25798_read_adc(dev, &read_data);
            rt_kprintf("%d vbus:%3d vac1:%3d vac2:%3d  \r\n", read_data.timestamp, read_data.vbus, read_data.vac1, read_data.vac2);
            tick_old = read_data.timestamp;
        }
    }
}

static rt_err_t rx_callback(void *param)
{
    rt_sem_release(bq25798_sem);
    return 0;
}

/* bq25798 interrupt initialization function */
static rt_err_t rt_bq25798_irq_init(bq25798_device_t dev)
{

    if (dev->ioconfig.irq_pin.pin == PIN_IRQ_PIN_NONE)
    {
        return -RT_EINVAL;
    }

    rt_pin_mode(dev->ioconfig.irq_pin.pin, dev->ioconfig.irq_pin.mode);

    if (dev->ioconfig.irq_pin.mode == PIN_MODE_INPUT_PULLDOWN)
    {
        rt_pin_attach_irq(dev->ioconfig.irq_pin.pin, PIN_IRQ_MODE_RISING, rx_callback, (void *)dev);
    }
    else if (dev->ioconfig.irq_pin.mode == PIN_MODE_INPUT_PULLUP)
    {
        rt_pin_attach_irq(dev->ioconfig.irq_pin.pin, PIN_IRQ_MODE_FALLING, rx_callback, (void *)dev);
    }
    else if (dev->ioconfig.irq_pin.mode == PIN_MODE_INPUT)
    {
        rt_pin_attach_irq(dev->ioconfig.irq_pin.pin, PIN_IRQ_MODE_RISING_FALLING, rx_callback, (void *)dev);
    }

    rt_pin_irq_enable(dev->ioconfig.irq_pin.pin, PIN_IRQ_ENABLE);

    return RT_EOK;
}

/* Test function */
void bq25798_sample(void)
{

    dev = rt_device_find("bq25798");
    if (dev == RT_NULL)
    {
        rt_kprintf("can't find device:%s\n", "bq25798");
        return -1;
    }

    if (rt_device_open(dev, RT_DEVICE_FLAG_INT_RX) != RT_EOK) // check device only, touch device has no init function
    {
        rt_kprintf("open device failed!\r\n");
        return -1;
    }

    bq25798_sem = rt_sem_create("dsem", 0, RT_IPC_FLAG_FIFO);
    if (bq25798_sem == RT_NULL)
    {
        rt_kprintf("create dynamic semaphore failed.\r\n");
        return -1;
    }

    rt_device_set_rx_indicate(dev, rx_callback);

    rt_bq25798_irq_init(dev);

    bq25798_thread = rt_thread_create("BQ25798", bq25798_entry, RT_NULL,
                                      THREAD_STACK_SIZE, THREAD_PRIORITY, THREAD_TIMESLICE);

    if (bq25798_thread == RT_NULL)
    {
        rt_kprintf("create thread fail.\r\n");
        return -1;
    }
    rt_thread_startup(bq25798_thread);

    return 0;
}
// INIT_DEVICE_EXPORT(bq25798_sample);