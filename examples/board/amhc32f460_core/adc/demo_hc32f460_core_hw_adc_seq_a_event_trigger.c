/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2018 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
*******************************************************************************/

/**
 * \file
 * \brief ADC序列A 事件触发例程 通过 HW 层接口实现
 *
 * - 操作步骤：
 *   1. PIOB_7 接地产生下降沿。
 *
 * - 实验现象：
 *   1. 串口输出电压采样值，输出结果为32次转换的平均值。
 *
 * \note
 *    1. 使用 ADC 模块功能，必须保证 ADC 模块上电；
 *    2. 如需观察串口打印的调试信息，需要将 PIOE_4 引脚连接 PC 串口的 TXD，
 *       PIOE_5 引脚连接 PC 串口的 RXD。
 *
 * \par 源代码
 * \snippet demo_hc32f460_hw_adc_int.c src_hc32f460_hw_adc_int
 *
 * \internal
 * \par Modification History
 * - 1.00 20-04-17  cds, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_hc32f460_hw_adc_int
 * \copydoc demo_hc32f460_hw_adc_int.c
 */

/** [src_hc32f460_hw_adc_int] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_hc32f460.h"
#include "am_gpio.h"
#include "am_clk.h"
#include "demo_hc32f460_core_entries.h"

/**
 * \brief 例程入口
 */
void demo_hc32f460_core_hw_adc_seq_a_event_trigger_entry (void)
{
    AM_DBG_INFO("demo amhc32f460_core hw adc seq a event trigger!\r\n");

    /* 配置模拟输入引脚 */
    am_gpio_pin_cfg(PIOA_0, GPIO_MODE(AMHW_HC32F460_GPIO_MODE_AIN));

    /* 配置外部触发引脚 */
    am_gpio_pin_cfg(PIOB_7,GPIO_AFIO(AMHW_HC32F460_AFIO_ADTRG));

    /* 使能时钟 */
    am_clk_enable(CLK_ADC1);

    demo_hc32f460_hw_adc_seq_a_event_trigger_entry(HC32F460_ADC1,
                                                   INT_VECTOR_16,
                                                   0,
                                                   3300);
}
/** [src_hc32f460_hw_adc_seqa_event_trigger] */

/* end of file */
