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
 * \brief UART DMA 接收例程，通过 HW 层接口实现
 *
 * - 操作步骤：
 *   1. 通过上位机串口一次性向 MCU 发送 5 个字符。
 *
 * - 实验现象：
 *   1. 串口打印出接收到的数据；
 *   2. 然后串口打印出 "DMA transfer done!"。
 *
 * \note
 *    1. 如需观察串口打印的调试信息，需要将 PIOB_3 引脚连接 PC 串口的 RXD；
 *    2. 如果调试串口使用与本例程相同，则不应在后续继续使用调试信息输出函数
 *      （如：AM_DBG_INFO()）。
 *
 * \par 源代码
 * \snippet demo_aml165_core_hw_uart_rx_dma.c src_aml165_core_hw_uart_rx_dma
 *
 *
 * \internal
 * \par Modification History
 * - 1.00 17-03-10  ari, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_aml165_core_hw_uart_rx_dma
 * \copydoc demo_aml165_core_hw_uart_rx_dma.c
 */

/** [src_aml165_core_hw_uart_rx_dma] */
#include "ametal.h"
#include "am_gpio.h"
#include "am_vdebug.h"
#include "am_zml165.h"
#include "demo_zlg_entries.h"
#include "demo_aml165_core_entries.h"

/**
 * \brief 例程入口
 */
void demo_aml165_core_hw_uart_rx_dma_entry (void)
{
    AM_DBG_INFO("demo aml165_core hw uart rx dma!\r\n");
    am_gpio_pin_cfg(PIOB_3, PIOB_3_UART1_TX | PIOB_3_AF_PP);
    am_gpio_pin_cfg(PIOB_4, PIOB_4_UART1_RX | PIOB_4_INPUT_FLOAT);
    demo_zlg_hw_uart_rx_dma_entry(ZML165_UART1,
                                  am_clk_rate_get(CLK_UART1),
                                  DMA_CHAN_UART1_RX);
}
/** [src_aml165_core_hw_uart_rx_dma] */

/* end of file */
