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
 * \brief LVD驱动实现
 *
 * \internal
 * \par Modification history
 * - 1.00 20-03-18
 * \endinternal
 */

#include "ametal.h"
#include "am_int.h"
#include "am_zsn700.h"
#include "zsn700_periph_map.h"
#include "am_zsn700_lvd.h"
#include "hw/amhw_zsn700_lvd.h"

/*******************************************************************************
* Functions declaration
*******************************************************************************/
/**
 * \brief LVD中断服务函数
 */
void __lvd_irq_handler (void *p_cookie);

/******************************************************************************/
/**
 * \brief LVD中断服务函数
 */
void __lvd_irq_handler (void *p_cookie)
{
    amhw_zsn700_lvd_t *p_hw_lvd;
    am_zsn700_lvd_dev_t *p_dev = (am_zsn700_lvd_dev_t *)p_cookie;
    p_hw_lvd = (amhw_zsn700_lvd_t *)(p_dev->p_devinfo->reg_base);

    if (amhw_zsn700_int_status_check (p_hw_lvd)){

        /* 清除中断标志 */
        amhw_zsn700_int_falg_clr (p_hw_lvd);

        /* 用户回调函数 */
        p_dev->pfn_trigger_cb(p_dev);
    }
}

/**
 * \brief 中断触发函数连接
 */
int am_zsn700_lvd_tri_set (am_lvd_handle_t handle, void (*pfn_tri_cb) (void *))
{
    if (handle == NULL || pfn_tri_cb == NULL ){

        return AM_ERROR;
    }

    handle->pfn_trigger_cb = pfn_tri_cb;

    return AM_OK;
}

/**
 * \brief lvd 使能
 */
int am_zsn700_lvd_enable (am_lvd_handle_t handle)
{
    amhw_zsn700_lvd_t *p_hw_lvd;

    if (handle == NULL){

        return AM_ERROR;
    }

    p_hw_lvd = (amhw_zsn700_lvd_t *)handle->p_devinfo->reg_base;

    /* 使能LVD */
    amhw_zsn700_lvd_enable (p_hw_lvd);

    return AM_OK;
}

/**
 * \brief lvd 初始化
 */
am_lvd_handle_t  am_zsn700_lvd_init (am_zsn700_lvd_dev_t           *p_dev,
                                     const am_zsn700_lvd_devinfo_t *p_devinfo)
{
    amhw_zsn700_lvd_t *p_hw_lvd;

    if ((p_devinfo == NULL) || (p_dev == NULL)) {
        return NULL;
    }

    p_dev->p_devinfo = p_devinfo;

    p_hw_lvd = (amhw_zsn700_lvd_t *)(p_dev->p_devinfo->reg_base);

    if (p_devinfo->pfn_plfm_init) {
        p_devinfo->pfn_plfm_init();
    }

    /* cr寄存器清零 */
    amhw_zsn700_lvd_cr_clr (p_hw_lvd);

    /* 触发条件使能 */
    amhw_zsn700_lvd_tri_enable (p_hw_lvd, p_dev->p_devinfo->tri_type);

    /* 数字滤波时间选择 */
    amhw_zsn700_lvd_deb_time_sel (p_hw_lvd, p_dev->p_devinfo->deb_time);

    /* 使能数字滤波 */
    amhw_zsn700_lvd_deb_time_enable (p_hw_lvd);

    /* 阈值电压选择 */
    amhw_zsn700_lvd_vids_sel (p_hw_lvd, p_dev->p_devinfo->vids);

    /* 监测来源选择 */
    amhw_zsn700_lvd_src_sel (p_hw_lvd, p_dev->p_devinfo->src_sel);

    /* 触发动作配置 */
    amhw_zsn700_lvd_tri_act_sel (p_hw_lvd, p_dev->p_devinfo->tri_act);

    if (p_devinfo->tri_act == ANHW_ZSN700_LVD_TRI_ACT_NVIC_INT){

        /* 中断状态标志清除 */
        amhw_zsn700_int_falg_clr (p_hw_lvd);

        /* 使能中断 */
        amhw_zsn700_lvd_int_enable (p_hw_lvd);

        /* 中断连接 */
        am_int_connect(p_dev->p_devinfo->inum,
                       __lvd_irq_handler,
                       (void *)p_dev);
        /* 开启中断 */
        am_int_enable (p_dev->p_devinfo->inum);
    }

    return p_dev;
}

/**
 * \brief lvd 去初始化
 */
void am_zsn700_lvd_deinit (am_lvd_handle_t handle)
{
    am_zsn700_lvd_dev_t *p_dev  = (am_zsn700_lvd_dev_t *)handle;
    amhw_zsn700_lvd_t *p_hw_lvd =
                          (amhw_zsn700_lvd_t *)(p_dev->p_devinfo->reg_base);

    if (handle == NULL){

        return ;
    }

    /* 滤波禁能 */
    amhw_zsn700_lvd_deb_time_disable (p_hw_lvd);

    if (p_dev->p_devinfo->tri_act == ANHW_ZSN700_LVD_TRI_ACT_NVIC_INT){

        /* 禁能中断 */
        amhw_zsn700_lvd_int_disable (p_hw_lvd);

        /* 中断连接 */
        am_int_disconnect(p_dev->p_devinfo->inum,
                          __lvd_irq_handler,
                          (void *)p_dev);
    }

    /* 禁能LVD */
    amhw_zsn700_lvd_disable (p_hw_lvd);

    /* 平台去初始化 */
    if (p_dev->p_devinfo->pfn_plfm_deinit) {
        p_dev->p_devinfo->pfn_plfm_deinit();
    }
}

/* end of file */
