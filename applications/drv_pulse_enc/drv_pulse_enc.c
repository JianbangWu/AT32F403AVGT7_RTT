#include "drv_common.h"
#include "drv_pulse_enc.h"

#include "pulse_encoder_config.h"

// #define DRV_DEBUG
#define LOG_TAG "drv.pulse_encoder"
#include <drv_log.h>

#if !defined(BSP_USING_PULSE_ENCODER1) && !defined(BSP_USING_PULSE_ENCODER2) && !defined(BSP_USING_PULSE_ENCODER3) && !defined(BSP_USING_PULSE_ENCODER4) && !defined(BSP_USING_PULSE_ENCODER5) && !defined(BSP_USING_PULSE_ENCODER6)
#error "Please define at least one BSP_USING_PULSE_ENCODERx"
/* this driver can be disabled at menuconfig -> RT-Thread Components -> Device Drivers */
#endif

#define AUTO_RELOAD_VALUE 0X7FFF

enum
{
#ifdef BSP_USING_PULSE_ENCODER1
    PULSE_ENCODER1_INDEX,
#endif
#ifdef BSP_USING_PULSE_ENCODER2
    PULSE_ENCODER2_INDEX,
#endif
#ifdef BSP_USING_PULSE_ENCODER3
    PULSE_ENCODER3_INDEX,
#endif
#ifdef BSP_USING_PULSE_ENCODER4
    PULSE_ENCODER4_INDEX,
#endif
#ifdef BSP_USING_PULSE_ENCODER5
    PULSE_ENCODER5_INDEX,
#endif
#ifdef BSP_USING_PULSE_ENCODER6
    PULSE_ENCODER6_INDEX,
#endif
};

struct at32_pulse_encoder_device
{
    struct rt_pulse_encoder_device pulse_encoder;
    tmr_type *tmr_handler;
    IRQn_Type encoder_irqn;
    rt_int32_t over_under_flowcount;
    char *name;
};

static struct at32_pulse_encoder_device at32_pulse_encoder_obj[] =
    {
#ifdef BSP_USING_PULSE_ENCODER1
        PULSE_ENCODER1_CONFIG,
#endif
#ifdef BSP_USING_PULSE_ENCODER2
        PULSE_ENCODER2_CONFIG,
#endif
#ifdef BSP_USING_PULSE_ENCODER3
        PULSE_ENCODER3_CONFIG,
#endif
#ifdef BSP_USING_PULSE_ENCODER4
        PULSE_ENCODER4_CONFIG,
#endif
#ifdef BSP_USING_PULSE_ENCODER5
        PULSE_ENCODER5_CONFIG,
#endif
#ifdef BSP_USING_PULSE_ENCODER6
        PULSE_ENCODER6_CONFIG,
#endif
};

rt_err_t pulse_encoder_init(struct rt_pulse_encoder_device *pulse_encoder)
{
    struct at32_pulse_encoder_device *at32_device;
    at32_device = (struct at32_pulse_encoder_device *)pulse_encoder;

    at32_msp_pulse_encoder_init(at32_device->tmr_handler); // init gpio and clock

    tmr_base_init(at32_device->tmr_handler, AUTO_RELOAD_VALUE, 0);

    tmr_cnt_dir_set(at32_device->tmr_handler, TMR_COUNT_UP);

    /* config encoder mode */
    tmr_encoder_mode_config(at32_device->tmr_handler, TMR_ENCODER_MODE_C, TMR_INPUT_RISING_EDGE, TMR_INPUT_RISING_EDGE);

    /* overflow interrupt enable */
    tmr_interrupt_enable(at32_device->tmr_handler, at32_device->encoder_irqn, TRUE);

    nvic_irq_enable(at32_device->encoder_irqn, 3, 0);

    return RT_EOK;
}

rt_err_t pulse_encoder_clear_count(struct rt_pulse_encoder_device *pulse_encoder)
{
    struct at32_pulse_encoder_device *at32_device;
    at32_device = (struct at32_pulse_encoder_device *)pulse_encoder;
    tmr_counter_value_set(at32_device->tmr_handler, 0);
    return RT_EOK;
}

rt_int32_t pulse_encoder_get_count(struct rt_pulse_encoder_device *pulse_encoder)
{
    struct at32_pulse_encoder_device *at32_device;
    at32_device = (struct at32_pulse_encoder_device *)pulse_encoder;
    return (rt_int32_t)(tmr_counter_value_get(at32_device->tmr_handler) + at32_device->over_under_flowcount * AUTO_RELOAD_VALUE);
}

rt_err_t pulse_encoder_control(struct rt_pulse_encoder_device *pulse_encoder, rt_uint32_t cmd, void *args)
{
    rt_err_t result;
    struct at32_pulse_encoder_device *at32_device;
    at32_device = (struct at32_pulse_encoder_device *)pulse_encoder;
    result = RT_EOK;

    switch (cmd)
    {
    case PULSE_ENCODER_CMD_ENABLE:
        tmr_counter_enable(at32_device->tmr_handler, TRUE);
        break;
    case PULSE_ENCODER_CMD_DISABLE:
        tmr_counter_enable(at32_device->tmr_handler, FALSE);
        break;
    default:
        result = -RT_ENOSYS;
        break;
    }

    return result;
}

void pulse_encoder_update_isr(struct at32_pulse_encoder_device *device)
{
    if (tmr_flag_get(device->tmr_handler, TMR_OVF_FLAG) == SET)
    {
        tmr_flag_clear(device->tmr_handler, TMR_OVF_FLAG);
        if (device->tmr_handler->ctrl1_bit.cnt_dir) // 0:count up 1:count down
        {
            device->over_under_flowcount--;
        }
        else
        {
            device->over_under_flowcount++;
        }
    }
}

#ifdef BSP_USING_PULSE_ENCODER1
void TMR1_OVF_TMR10_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    pulse_encoder_update_isr(&at32_pulse_encoder_obj[PULSE_ENCODER1_INDEX]);
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif
#ifdef BSP_USING_PULSE_ENCODER2
void TMR2_GLOBAL_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    pulse_encoder_update_isr(&at32_pulse_encoder_obj[PULSE_ENCODER2_INDEX]);
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif
#ifdef BSP_USING_PULSE_ENCODER3
void TMR3_GLOBAL_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    pulse_encoder_update_isr(&at32_pulse_encoder_obj[PULSE_ENCODER3_INDEX]);
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif
#ifdef BSP_USING_PULSE_ENCODER4
void TMR4_GLOBAL_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    pulse_encoder_update_isr(&at32_pulse_encoder_obj[PULSE_ENCODER4_INDEX]);
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

static const struct rt_pulse_encoder_ops _ops =
    {
        .init = pulse_encoder_init,
        .get_count = pulse_encoder_get_count,
        .clear_count = pulse_encoder_clear_count,
        .control = pulse_encoder_control,
};

int hw_pulse_encoder_init(void)
{
    int i;
    int result;
    result = RT_EOK;
    for (i = 0; i < sizeof(at32_pulse_encoder_obj) / sizeof(at32_pulse_encoder_obj[0]); i++)
    {
        at32_pulse_encoder_obj[i].pulse_encoder.type = AB_PHASE_PULSE_ENCODER;
        at32_pulse_encoder_obj[i].pulse_encoder.ops = &_ops;

        if (rt_device_pulse_encoder_register(&at32_pulse_encoder_obj[i].pulse_encoder, at32_pulse_encoder_obj[i].name, RT_NULL) != RT_EOK)
        {
            LOG_E("%s register failed", at32_pulse_encoder_obj[i].name);
            result = -RT_ERROR;
        }
    }

    return result;
}
INIT_BOARD_EXPORT(hw_pulse_encoder_init);

#define THREAD_PRIORITY 20
#define THREAD_STACK_SIZE 1024
#define THREAD_TIMESLICE 5
static rt_thread_t enc_thread = RT_NULL;

static void enc_entry(void *parameter)
{
    struct rt_pulse_encoder_device *pulse_encoder;
    pulse_encoder = rt_device_find("enc4");
    struct at32_pulse_encoder_device *at32_device;
    at32_device = pulse_encoder;
    rt_base_t val = 0;
    while (1)
    {
        val = pulse_encoder->ops->get_count(pulse_encoder);
        rt_kprintf("current cal = %5d \r\n", val);
        rt_thread_mdelay(100);
    }
}

void pluse_encoder_test()
{
    struct rt_pulse_encoder_device *pulse_encoder;
    pulse_encoder = rt_device_find("enc4");
    struct at32_pulse_encoder_device *at32_device;
    at32_device = pulse_encoder;

    if (at32_device != RT_NULL)
    {
        pulse_encoder->ops->init(pulse_encoder);
        pulse_encoder->ops->control(pulse_encoder,PULSE_ENCODER_CMD_ENABLE,RT_NULL);
    }
    else
    {
        return RT_ERROR;
    }

    enc_thread = rt_thread_create("enc", enc_entry, RT_NULL,
                                  THREAD_STACK_SIZE, THREAD_PRIORITY, THREAD_TIMESLICE);

    if (enc_thread == RT_NULL)
    {
        rt_kprintf("create enc_thread fail.\r\n");
        return RT_ERROR;
    }
    rt_thread_startup(enc_thread);
}
MSH_CMD_EXPORT(pluse_encoder_test, enc test);