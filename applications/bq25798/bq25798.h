#ifndef __BQ25798_H__
#define __BQ25798_H__

#include <rtthread.h>
#include <rtdevice.h>

struct bq25798_gpio_config
{
    char *dev_name; /* The name of the communication device */
    struct rt_device_pin_mode irq_pin;
    struct rt_device_pin_mode charge_en_pin;
    struct rt_device_pin_mode ship_fet_en_pin;
};

struct bq25798_adc
{

    rt_int16_t ibus;
    rt_int16_t ibat;
    rt_int16_t vbus;
    rt_int16_t vac1;
    rt_int16_t vac2;
    rt_int16_t vbat;
    rt_int16_t vsys;
    rt_int16_t ts;
    rt_int16_t tdie;
    rt_int16_t vdp;
    rt_int16_t vdm;
    rt_tick_t timestamp; /* The timestamp when the data was received */
};

typedef struct bq25798_device *bq25798_device_t;

struct bq25798_device
{
    struct rt_device parent; /* The standard device */
    struct bq25798_gpio_config ioconfig;
    const struct bq25798_ops *ops;                  /* The bq25798 ops */
    rt_err_t (*irq_handle)(bq25798_device_t touch); /* Called when an interrupt is generated, registered by the driver */
};

struct bq25798_ops
{
    rt_size_t (*bq25798_read_adc)(struct bq25798_device *dev, void *buf);
};

/* Reg Define */

#define BQ25798_DEV_ADDR 0x6B

#define Minimal_System_Voltage 0X00
#define Charge_Voltage_Limit 0X01
#define Charge_Current_Limit 0X03
#define Input_Voltage_Limit 0X05
#define Input_Current_Limit 0X06
#define Precharge_Control 0X08
#define Termination_Control 0X09
#define Recharge_Control 0X0A
#define VOTG_regulation 0X0B
#define IOTG_regulation 0X0D
#define Timer_Control 0X0E
#define Charger_Control_0 0X0F
#define Charger_Control_1 0X10
#define Charger_Control_2 0X11
#define Charger_Control_3 0X12
#define Charger_Control_4 0X13
#define Charger_Control_5 0X14
#define MPPT_Control 0X15
#define Temperature_Control 0X16
#define NTC_Control_0 0X17
#define NTC_Control_1 0X18
#define ICO_Current_Limit 0X19
#define Charger_Status_0 0X1B
#define Charger_Status_1 0X1C
#define Charger_Status_2 0X1D
#define Charger_Status_3 0X1E
#define Charger_Status_4 0X1F
#define FAULT_Status_0 0X20
#define FAULT_Status_1 0X21
#define Charger_Flag_0 0X22
#define Charger_Flag_1 0X23
#define Charger_Flag_2 0X24
#define Charger_Flag_3 0X24
#define FAULT_Flag_0 0X26
#define FAULT_Flag_1 0X27
#define Charger_Mask_0 0X28
#define Charger_Mask_1 0X29
#define Charger_Mask_2 0X2A
#define Charger_Mask_3 0X2B
#define FAULT_Mask_0 0X2C
#define FAULT_Mask_1 0X2D
#define ADC_Control 0X2E
#define ADC_Function_Disable_0 0X2F
#define ADC_Function_Disable_1 0X30
#define IBUS_ADC 0X31
#define IBAT_ADC 0X33
#define VBUS_ADC 0X35
#define VAC1_ADC 0X37
#define VAC2_ADC 0X39
#define VBAT_ADC 0X3B
#define VSYS_ADC 0X3D
#define TS_ADC 0X3F
#define TDIE_ADC 0x41
#define DP_ADC 0x43
#define DM_ADC 0x45
#define DPDM_Driver 0x47
#define Part_Information 0x48

#endif