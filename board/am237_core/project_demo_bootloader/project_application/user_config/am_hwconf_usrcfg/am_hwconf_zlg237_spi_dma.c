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
 * \brief ZLG237 SPI DMA �û������ļ�
 * \sa am_hwconf_zlg237_spi.c
 *
 * \internal
 * \par Modification history
 * - 1.00 19-07-19  fra, first implementation
 * \endinternal
 */

#include "am_zlg237.h"
#include "zlg237_dma_chan.h"
#include "ametal.h"
#include "am_zlg237_spi_dma.h"
#include "am_gpio.h"
#include "amhw_zlg237_spi.h"
#include "am_clk.h"

/**
 * \addtogroup am_if_src_hwconf_zlg237_spi_dma
 * \copydoc am_hwconf_zlg237_spi_dma.c
 * @{
 */

/** \brief SPI1 ƽ̨��ʼ�� */
static void __zlg237_plfm_spi1_dma_init (void)
{
    am_gpio_pin_cfg(PIOA_5, PIOA_5_SPI1_SCK_REMAP0  | PIOA_5_AF_PP);
    am_gpio_pin_cfg(PIOA_6, PIOA_6_SPI1_MISO_REMAP0 | PIOA_6_INPUT_FLOAT);
    am_gpio_pin_cfg(PIOA_7, PIOA_7_SPI1_MOSI_REMAP0 | PIOA_7_AF_PP);

    am_clk_enable(CLK_SPI1);
}

/** \brief ��� SPI1 ƽ̨��ʼ�� */
static void __zlg237_plfm_spi1_dma_deinit (void)
{
    am_gpio_pin_cfg(PIOA_5, AM_GPIO_INPUT);
    am_gpio_pin_cfg(PIOA_6, AM_GPIO_INPUT);
    am_gpio_pin_cfg(PIOA_7, AM_GPIO_INPUT);

    am_clk_disable(CLK_SPI1);
}

/** \brief SPI1 �豸��Ϣ */
static const  struct am_zlg237_spi_dma_devinfo  __g_spi1_dma_devinfo = {
    ZLG237_SPI1_BASE,                        /**< \brief SPI1�Ĵ���ָ�� */
    CLK_SPI1,                                /**< \brief ʱ��ID�� */
    AMHW_ZLG237_SPI_BAUDRATE_PRESCALER_128,  /**< \brief ʱ�ӷ�Ƶϵ�� */
    INUM_SPI1,                               /**< \brief SPI1�жϺ� */

    0,                                       /**< \brief SPI1 CS���ͺ���ʱ�ȴ���ms�����ٽ������ݴ��䡣
                                              *
                                              *   �ӻ�Ϊ��zlg237��������Ӧ��spi_slaverʱ���뽫��ʱ����Ϊ
                                              *   100ms�����AM_CFG_DELAY_ENABLE�궨��
                                              *   �ӻ���������������ʱ����ʱһ������Ϊ0ms��
                                              **/

    PIOA_7_SPI1_MOSI_REMAP0 | PIOA_7_AF_PP,  /**< \brief SPI1���ñ�ʶ */
    DMA_CHAN_SPI1_TX,
    DMA_CHAN_SPI1_RX,
    __zlg237_plfm_spi1_dma_init,             /**< \brief SPI1ƽ̨��ʼ������ */
    __zlg237_plfm_spi1_dma_deinit            /**< \brief SPI1ƽ̨���ʼ������ */
};
/** \brief SPI1 �豸ʵ�� */
static am_zlg237_spi_dma_dev_t __g_spi1_dma_dev;


/** \brief SPI1 ʵ����ʼ�������SPI��׼������ */
am_spi_handle_t am_zlg237_spi1_dma_inst_init (void)
{
    return am_zlg237_spi_dma_init(&__g_spi1_dma_dev, &__g_spi1_dma_devinfo);
}

/** \brief SPI1 ʵ�����ʼ�� */
void am_zlg237_spi1_dma_inst_deinit (am_spi_handle_t handle)
{
    am_zlg237_spi_dma_deinit(handle);
}

/** \brief SPI2 ƽ̨��ʼ�� */
static void __zlg237_plfm_spi2_dma_init (void)
{
    am_gpio_pin_cfg(PIOB_14, PIOB_14_SPI2_MISO | PIOB_14_INPUT_FLOAT);
    am_gpio_pin_cfg(PIOB_15, PIOB_15_SPI2_MOSI | PIOB_15_AF_PP);
    am_gpio_pin_cfg(PIOB_13, PIOB_13_SPI2_SCK  | PIOB_13_AF_PP);

    am_clk_enable(CLK_SPI2);
}

/** \brief ���SPI2 ƽ̨��ʼ�� */
static void __zlg237_plfm_spi2_dma_deinit (void)
{
    am_gpio_pin_cfg(PIOB_13, AM_GPIO_INPUT);
    am_gpio_pin_cfg(PIOB_14, AM_GPIO_INPUT);
    am_gpio_pin_cfg(PIOB_15, AM_GPIO_INPUT);

    am_clk_disable(CLK_SPI2);
}

/**
 * \brief SPI2 �豸��Ϣ
 */
static const struct am_zlg237_spi_dma_devinfo  __g_spi2_dma_devinfo = {
    ZLG237_SPI2_BASE,                       /**< \brief SPI2�Ĵ���ָ�� */
    CLK_SPI2,                               /**< \brief ʱ��ID�� */
    AMHW_ZLG237_SPI_BAUDRATE_PRESCALER_128, /**< \brief ʱ�ӷ�Ƶϵ�� */
    INUM_SPI2,                              /**< \brief SPI2 �жϺ� */

    0,                                      /**< \brief SPI1 CS���ͺ���ʱ�ȴ���ms�����ٽ������ݴ��䡣
                                             *
                                             *   �ӻ�Ϊ��zlg237��������Ӧ��spi_slaverʱ���뽫��ʱ����Ϊ
                                             *   100ms��
                                             *   �ӻ���������������ʱ����ʱһ������Ϊ0ms��
                                             **/

    PIOB_15_SPI2_MOSI | PIOB_15_AF_PP,      /**< \brief SPI2 ���ñ�ʶ */
    DMA_CHAN_SPI2_TX,
    DMA_CHAN_SPI2_RX,
    __zlg237_plfm_spi2_dma_init,            /**< \brief SPI2ƽ̨��ʼ������ */
    __zlg237_plfm_spi2_dma_deinit           /**< \brief SPI2ƽ̨���ʼ������ */
};

/** \brief SPI2 �豸ʵ�� */
static am_zlg237_spi_dma_dev_t __g_spi2_dma_dev;

/** \brief SPI2 ʵ����ʼ�������SPI��׼������ */
am_spi_handle_t am_zlg237_spi2_dma_inst_init (void)
{
    return am_zlg237_spi_dma_init(&__g_spi2_dma_dev, &__g_spi2_dma_devinfo);
}


/** \brief SPI2 ʵ�����ʼ�� */
void am_zlg237_spi2_dma_inst_deinit (am_spi_handle_t handle)
{
    am_zlg237_spi_dma_deinit(handle);
}

/**
 * @}
 */

/* end of file */