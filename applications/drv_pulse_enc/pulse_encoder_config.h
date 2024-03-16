#ifndef __PULSE_ENCODER_CONFIG_H__
#define __PULSE_ENCODER_CONFIG_H__

#include <rtthread.h>
#include "at32f403a_407.h"

#ifdef __cplusplus
extern "C"
{
#endif

#ifdef BSP_USING_PULSE_ENCODER1
#ifndef PULSE_ENCODER1_CONFIG
#define PULSE_ENCODER1_CONFIG        \
    {                                \
        .tmr_handler = TMR1,         \
        .encoder_irqn = TMR_OVF_INT, \
        .name = "enc1"               \
    }
#endif /* PULSE_ENCODER1_CONFIG */
#endif /* BSP_USING_PULSE_ENCODER1 */

#ifdef BSP_USING_PULSE_ENCODER2
#ifndef PULSE_ENCODER2_CONFIG
#define PULSE_ENCODER2_CONFIG        \
    {                                \
        .tmr_handler = TMR2,         \
        .encoder_irqn = TMR_OVF_INT, \
        .name = "enc2"               \
    }
#endif /* PULSE_ENCODER2_CONFIG */
#endif /* BSP_USING_PULSE_ENCODER2 */

#ifdef BSP_USING_PULSE_ENCODER3
#ifndef PULSE_ENCODER3_CONFIG
#define PULSE_ENCODER3_CONFIG        \
    {                                \
        .tmr_handler = TMR3,         \
        .encoder_irqn = TMR_OVF_INT, \
        .name = "enc3"               \
    }
#endif /* PULSE_ENCODER3_CONFIG */
#endif /* BSP_USING_PULSE_ENCODER3 */

#ifdef BSP_USING_PULSE_ENCODER4
#ifndef PULSE_ENCODER4_CONFIG
#define PULSE_ENCODER4_CONFIG        \
    {                                \
        .tmr_handler = TMR4,         \
        .encoder_irqn = TMR_OVF_INT, \
        .name = "enc4"               \
    }
#endif /* PULSE_ENCODER4_CONFIG */
#endif /* BSP_USING_PULSE_ENCODER4 */

#ifdef BSP_USING_PULSE_ENCODER5
#ifndef PULSE_ENCODER5_CONFIG
#define PULSE_ENCODER5_CONFIG        \
    {                                \
        .tmr_handler = TMR5,         \
        .encoder_irqn = TMR_OVF_INT, \
        .name = "enc5"               \
    }
#endif /* PULSE_ENCODER5_CONFIG */
#endif /* BSP_USING_PULSE_ENCODER5 */

#ifdef BSP_USING_PULSE_ENCODER8
#ifndef PULSE_ENCODER8_CONFIG
#define PULSE_ENCODER8_CONFIG        \
    {                                \
        .tmr_handler = TMR8,         \
        .encoder_irqn = TMR_OVF_INT, \
        .name = "enc8"               \
    }
#endif /* PULSE_ENCODER8_CONFIG */
#endif /* BSP_USING_PULSE_ENCODER8 */

#ifdef __cplusplus
}
#endif

#endif /* __PULSE_ENCODER_CONFIG_H__ */
