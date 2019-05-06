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
 * \brief LPC82X MRT �û������ļ�
 * \sa am_hwconf_lpc84x_mrt.c
 *
 * \internal
 * \par Modification history
 * - 1.01 15-12-08  mem,modified
 * - 1.00 15-07-15  win, first implementation
 * \endinternal
 */

#include <am_lpc84x.h>
#include "ametal.h"
#include "am_lpc_mrt.h"
#include "hw/amhw_lpc84x_clk.h"
#include "hw/amhw_lpc84x_syscon.h"

/**
 * \addtogroup am_if_src_hwconf_lpc84x_mrt
 * \copydoc am_hwconf_lpc84x_mrt.c
 * @{
 */

/**
 * \brief MRT ƽ̨��ʼ��
 */
am_local void __lpc84x_mrt_plfm_init (void)
{
    amhw_lpc84x_clk_periph_enable(AMHW_LPC84X_CLK_MRT);
    amhw_lpc84x_syscon_periph_reset(AMHW_LPC84X_RESET_MRT);
}

/**
 * \brief MRT ƽ̨���ʼ��
 */
am_local void __lpc84x_mrt_plfm_deinit (void)
{
    amhw_lpc84x_syscon_periph_reset(AMHW_LPC84X_RESET_MRT);
    amhw_lpc84x_clk_periph_disable(AMHW_LPC84X_CLK_MRT);
}

/** \brief MRT �豸��Ϣ */
am_local am_const am_lpc_mrt_devinfo_t __g_lpc84x_mrt_devinfo = {
    LPC84X_MRT_BASE,             /* MRT �Ĵ������ַ */
    INUM_MRT,                    /* MRT �жϺ� */
    CLK_MRT,                     /* MRT ʱ�Ӻ� */
    4,                           /* ʹ�õ�ͨ���� */
    __lpc84x_mrt_plfm_init,      /* ƽ̨��ʼ������ */
    __lpc84x_mrt_plfm_deinit,    /* ƽ̨���ʼ������ */
};

/** \brief MRT �豸ʵ�� */
am_local am_lpc_mrt_dev_t __g_lpc84x_mrt_dev;

/**
 * \brief MRT ʵ����ʼ��
 */
am_timer_handle_t am_lpc84x_mrt_inst_init (void)
{
    return am_lpc_mrt_init(&__g_lpc84x_mrt_dev, &__g_lpc84x_mrt_devinfo);
}

/**
 * \brief MRT ʵ�����ʼ��
 */
void am_lpc84x_mrt_inst_deinit (am_timer_handle_t handle)
{
    am_lpc_mrt_deinit((am_lpc_mrt_dev_t *)handle);
}

/**
 * @}
 */

/* end of file */