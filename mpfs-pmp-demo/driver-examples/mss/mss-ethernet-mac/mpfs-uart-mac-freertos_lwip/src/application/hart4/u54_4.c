/*******************************************************************************
 * Copyright 2019-2021 Microchip FPGA Embedded Systems Solutions.
 *
 * SPDX-License-Identifier: MIT
 *
 * Application code running on U54_4
 *
 */

#include <stdio.h>
#include <string.h>
#include "mpfs_hal/mss_hal.h"
#if ((MPFS_HAL_FIRST_HART == 4) && (MPFS_HAL_LAST_HART == 4))
#include "drivers/mss/mss_mmuart/mss_uart.h"
#include "inc/common.h"
#include "drivers/mss/mss_ethernet_mac/mss_ethernet_mac_sw_cfg.h"


volatile uint32_t count_sw_ints_h1 = 0U;

/* Main function for the hart1(U54_1 processor).
 * Application code running on hart1 is placed here
 *
 * The hart1 goes into WFI. hart0 brings it out of WFI when it raises the first
 * Software interrupt to this hart.
 */
void u54_4(void)
{
    volatile uint32_t icount = 0U;

#if (MSS_MAC_HW_PLATFORM == MSS_MAC_DESIGN_ICICLE_STD_GEM0_LOCAL)
    /*
     * Enable mac local interrupts to hart 1, U54 1
     */
    SYSREG->FAB_INTEN_U54_4 = (1U<<MAC1_INT_U54_INT)|(1U<<MAC1_QUEUE1_U54_INT)|(1U<<MAC1_QUEUE2_U54_INT)|(1U<<MAC1_QUEUE3_U54_INT)|(1U<<MAC1_EMAC_U54_INT)|(1U<<MAC1_MMSL_U54_INT);
    SYSREG->FAB_INTEN_MISC  = FAB_INTEN_MAC1_U54_4_EN_MASK;

    /*
     * Call free RTOS. Will not return from here
     */
    free_rtos();
#endif
    /*
     * should never get here
     */
    while(1U)
    {
        icount++;
    }

  /* Never return */
}

/* hart1 software interrupt handler */
void Software_h1_IRQHandler(void)
{
    count_sw_ints_h1++;
}

#endif  /* #if ((MPFS_HAL_FIRST_HART == 4) && (MPFS_HAL_LAST_HART ==4)) */
