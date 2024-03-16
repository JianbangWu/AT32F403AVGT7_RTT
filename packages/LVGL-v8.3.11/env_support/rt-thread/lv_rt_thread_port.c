/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: MIT
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-10-18     Meco Man     the first version
 * 2022-05-10     Meco Man     improve rt-thread initialization process
 */

#ifdef __RTTHREAD__

#include <lvgl.h>
#include <rtthread.h>

#define DBG_TAG    "LVGL"
#define DBG_LVL    DBG_INFO
#include <rtdbg.h>

#ifndef PKG_LVGL_THREAD_STACK_SIZE
#define PKG_LVGL_THREAD_STACK_SIZE 4096
#endif /* PKG_LVGL_THREAD_STACK_SIZE */

#ifndef PKG_LVGL_THREAD_PRIO
#define PKG_LVGL_THREAD_PRIO (RT_THREAD_PRIORITY_MAX*2/3)
#endif /* PKG_LVGL_THREAD_PRIO */

extern void lv_port_disp_init(void);
// extern void lv_port_indev_init(void);
// extern void lv_user_gui_init(void);

lv_obj_t *label0;

static struct rt_thread lvgl_thread;

#ifdef rt_align
rt_align(RT_ALIGN_SIZE)
#else
ALIGN(RT_ALIGN_SIZE)
#endif
static rt_uint8_t lvgl_thread_stack[PKG_LVGL_THREAD_STACK_SIZE];

#if LV_USE_LOG
static void lv_rt_log(const char *buf)
{
    LOG_I(buf);
}
#endif /* LV_USE_LOG */

static void lvgl_thread_entry(void *parameter)
{
#if LV_USE_LOG
    lv_log_register_print_cb(lv_rt_log);
#endif /* LV_USE_LOG */
    lv_init();
    lv_port_disp_init();
    // lv_port_indev_init();
    // lv_user_gui_init();
    // lv_obj_set_style_bg_color(lv_scr_act(), lv_color_hex(0x00E5EE), LV_PART_MAIN);

    static lv_style_t style;
    lv_style_init(&style);
    lv_style_set_radius(&style, 5);

    /*Make a gradient*/
    lv_style_set_bg_opa(&style, LV_OPA_COVER);
    lv_style_set_bg_color(&style, lv_palette_lighten(LV_PALETTE_BLUE, 1));
    lv_style_set_bg_grad_color(&style, lv_palette_main(LV_PALETTE_ORANGE));
    lv_style_set_bg_grad_dir(&style, LV_GRAD_DIR_VER);

    /*Shift the gradient to the bottom*/
    lv_style_set_bg_main_stop(&style, 0);   // 样式起点
    lv_style_set_bg_grad_stop(&style, 240); // 样式结束位置

    /*Create an object with the new style*/
    lv_obj_t *obj = lv_obj_create(lv_scr_act());
    lv_obj_add_style(obj, &style, 0); // 为对象增加 样式
    lv_obj_set_size(obj, 240, 240);   // 设置对象 宽高
    lv_obj_center(obj);

    /*Create a white label, set its text and align it to the center*/
    label0 = lv_label_create(lv_scr_act());
    lv_label_set_text(label0, "Hello World!");
    lv_obj_set_style_text_color(lv_scr_act(), lv_color_hex(0x000000), LV_PART_MAIN);
    lv_obj_align(label0, LV_ALIGN_TOP_LEFT, 120, 120);

    /* handle the tasks of LVGL */
    while(1)
    {
        lv_task_handler();
        rt_thread_mdelay(LV_DISP_DEF_REFR_PERIOD);
    }
}

static int lvgl_thread_init(void)
{
    rt_err_t err;

    err = rt_thread_init(&lvgl_thread, "LVGL", lvgl_thread_entry, RT_NULL,
           &lvgl_thread_stack[0], sizeof(lvgl_thread_stack), PKG_LVGL_THREAD_PRIO, 10);
    if(err != RT_EOK)
    {
        LOG_E("Failed to create LVGL thread");
        return -1;
    }
    rt_thread_startup(&lvgl_thread);

    return 0;
}
INIT_ENV_EXPORT(lvgl_thread_init);

#endif /*__RTTHREAD__*/
