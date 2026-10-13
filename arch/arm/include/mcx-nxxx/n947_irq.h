/****************************************************************************
 * arch/arm/include/mcx-nxxx/n947_irq.h
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 ****************************************************************************/

/* This file should never be included directly but, rather,
 * only indirectly through arch/mcx-nxxx/irq.h
 */

#ifndef __ARCH_ARM_INCLUDE_MCX_NXXX_N947_IRQ_H
#define __ARCH_ARM_INCLUDE_MCX_NXXX_N947_IRQ_H

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* External interrupts (vectors >= 16).  Names and numbering follow the
 * IRQn_Type enumeration of the NXP MCUXpresso SDK device header
 * MCXN947_cm33_core0.h.
 */

#define NXXX_IRQ_OR                    (NXXX_IRQ_EXTINT + 0)
#define NXXX_IRQ_EDMA_0_CH0            (NXXX_IRQ_EXTINT + 1)
#define NXXX_IRQ_EDMA_0_CH1            (NXXX_IRQ_EXTINT + 2)
#define NXXX_IRQ_EDMA_0_CH2            (NXXX_IRQ_EXTINT + 3)
#define NXXX_IRQ_EDMA_0_CH3            (NXXX_IRQ_EXTINT + 4)
#define NXXX_IRQ_EDMA_0_CH4            (NXXX_IRQ_EXTINT + 5)
#define NXXX_IRQ_EDMA_0_CH5            (NXXX_IRQ_EXTINT + 6)
#define NXXX_IRQ_EDMA_0_CH6            (NXXX_IRQ_EXTINT + 7)
#define NXXX_IRQ_EDMA_0_CH7            (NXXX_IRQ_EXTINT + 8)
#define NXXX_IRQ_EDMA_0_CH8            (NXXX_IRQ_EXTINT + 9)
#define NXXX_IRQ_EDMA_0_CH9            (NXXX_IRQ_EXTINT + 10)
#define NXXX_IRQ_EDMA_0_CH10           (NXXX_IRQ_EXTINT + 11)
#define NXXX_IRQ_EDMA_0_CH11           (NXXX_IRQ_EXTINT + 12)
#define NXXX_IRQ_EDMA_0_CH12           (NXXX_IRQ_EXTINT + 13)
#define NXXX_IRQ_EDMA_0_CH13           (NXXX_IRQ_EXTINT + 14)
#define NXXX_IRQ_EDMA_0_CH14           (NXXX_IRQ_EXTINT + 15)
#define NXXX_IRQ_EDMA_0_CH15           (NXXX_IRQ_EXTINT + 16)
#define NXXX_IRQ_GPIO00                (NXXX_IRQ_EXTINT + 17)
#define NXXX_IRQ_GPIO01                (NXXX_IRQ_EXTINT + 18)
#define NXXX_IRQ_GPIO10                (NXXX_IRQ_EXTINT + 19)
#define NXXX_IRQ_GPIO11                (NXXX_IRQ_EXTINT + 20)
#define NXXX_IRQ_GPIO20                (NXXX_IRQ_EXTINT + 21)
#define NXXX_IRQ_GPIO21                (NXXX_IRQ_EXTINT + 22)
#define NXXX_IRQ_GPIO30                (NXXX_IRQ_EXTINT + 23)
#define NXXX_IRQ_GPIO31                (NXXX_IRQ_EXTINT + 24)
#define NXXX_IRQ_GPIO40                (NXXX_IRQ_EXTINT + 25)
#define NXXX_IRQ_GPIO41                (NXXX_IRQ_EXTINT + 26)
#define NXXX_IRQ_GPIO50                (NXXX_IRQ_EXTINT + 27)
#define NXXX_IRQ_GPIO51                (NXXX_IRQ_EXTINT + 28)
#define NXXX_IRQ_UTICK0                (NXXX_IRQ_EXTINT + 29)
#define NXXX_IRQ_MRT0                  (NXXX_IRQ_EXTINT + 30)
#define NXXX_IRQ_CTIMER0               (NXXX_IRQ_EXTINT + 31)
#define NXXX_IRQ_CTIMER1               (NXXX_IRQ_EXTINT + 32)
#define NXXX_IRQ_SCT0                  (NXXX_IRQ_EXTINT + 33)
#define NXXX_IRQ_CTIMER2               (NXXX_IRQ_EXTINT + 34)
#define NXXX_IRQ_LP_FLEXCOMM0          (NXXX_IRQ_EXTINT + 35)
#define NXXX_IRQ_LP_FLEXCOMM1          (NXXX_IRQ_EXTINT + 36)
#define NXXX_IRQ_LP_FLEXCOMM2          (NXXX_IRQ_EXTINT + 37)
#define NXXX_IRQ_LP_FLEXCOMM3          (NXXX_IRQ_EXTINT + 38)
#define NXXX_IRQ_LP_FLEXCOMM4          (NXXX_IRQ_EXTINT + 39)
#define NXXX_IRQ_LP_FLEXCOMM5          (NXXX_IRQ_EXTINT + 40)
#define NXXX_IRQ_LP_FLEXCOMM6          (NXXX_IRQ_EXTINT + 41)
#define NXXX_IRQ_LP_FLEXCOMM7          (NXXX_IRQ_EXTINT + 42)
#define NXXX_IRQ_LP_FLEXCOMM8          (NXXX_IRQ_EXTINT + 43)
#define NXXX_IRQ_LP_FLEXCOMM9          (NXXX_IRQ_EXTINT + 44)
#define NXXX_IRQ_ADC0                  (NXXX_IRQ_EXTINT + 45)
#define NXXX_IRQ_ADC1                  (NXXX_IRQ_EXTINT + 46)
#define NXXX_IRQ_PINT0                 (NXXX_IRQ_EXTINT + 47)
#define NXXX_IRQ_PDM_EVENT             (NXXX_IRQ_EXTINT + 48)
#define NXXX_IRQ_RESERVED65            (NXXX_IRQ_EXTINT + 49)
#define NXXX_IRQ_USB0_FS               (NXXX_IRQ_EXTINT + 50)
#define NXXX_IRQ_USB0_DCD              (NXXX_IRQ_EXTINT + 51)
#define NXXX_IRQ_RTC                   (NXXX_IRQ_EXTINT + 52)
#define NXXX_IRQ_SMARTDMA              (NXXX_IRQ_EXTINT + 53)
#define NXXX_IRQ_MAILBOX               (NXXX_IRQ_EXTINT + 54)
#define NXXX_IRQ_CTIMER3               (NXXX_IRQ_EXTINT + 55)
#define NXXX_IRQ_CTIMER4               (NXXX_IRQ_EXTINT + 56)
#define NXXX_IRQ_OS_EVENT              (NXXX_IRQ_EXTINT + 57)
#define NXXX_IRQ_FLEXSPI0              (NXXX_IRQ_EXTINT + 58)
#define NXXX_IRQ_SAI0                  (NXXX_IRQ_EXTINT + 59)
#define NXXX_IRQ_SAI1                  (NXXX_IRQ_EXTINT + 60)
#define NXXX_IRQ_USDHC0                (NXXX_IRQ_EXTINT + 61)
#define NXXX_IRQ_CAN0                  (NXXX_IRQ_EXTINT + 62)
#define NXXX_IRQ_CAN1                  (NXXX_IRQ_EXTINT + 63)
#define NXXX_IRQ_RESERVED80            (NXXX_IRQ_EXTINT + 64)
#define NXXX_IRQ_RESERVED81            (NXXX_IRQ_EXTINT + 65)
#define NXXX_IRQ_USB1_HS_PHY           (NXXX_IRQ_EXTINT + 66)
#define NXXX_IRQ_USB1_HS               (NXXX_IRQ_EXTINT + 67)
#define NXXX_IRQ_SEC_HYPERVISOR_CALL   (NXXX_IRQ_EXTINT + 68)
#define NXXX_IRQ_RESERVED85            (NXXX_IRQ_EXTINT + 69)
#define NXXX_IRQ_PLU                   (NXXX_IRQ_EXTINT + 70)
#define NXXX_IRQ_FREQME                (NXXX_IRQ_EXTINT + 71)
#define NXXX_IRQ_SEC_VIO               (NXXX_IRQ_EXTINT + 72)
#define NXXX_IRQ_ELS                   (NXXX_IRQ_EXTINT + 73)
#define NXXX_IRQ_PKC                   (NXXX_IRQ_EXTINT + 74)
#define NXXX_IRQ_PUF                   (NXXX_IRQ_EXTINT + 75)
#define NXXX_IRQ_PQ                    (NXXX_IRQ_EXTINT + 76)
#define NXXX_IRQ_EDMA_1_CH0            (NXXX_IRQ_EXTINT + 77)
#define NXXX_IRQ_EDMA_1_CH1            (NXXX_IRQ_EXTINT + 78)
#define NXXX_IRQ_EDMA_1_CH2            (NXXX_IRQ_EXTINT + 79)
#define NXXX_IRQ_EDMA_1_CH3            (NXXX_IRQ_EXTINT + 80)
#define NXXX_IRQ_EDMA_1_CH4            (NXXX_IRQ_EXTINT + 81)
#define NXXX_IRQ_EDMA_1_CH5            (NXXX_IRQ_EXTINT + 82)
#define NXXX_IRQ_EDMA_1_CH6            (NXXX_IRQ_EXTINT + 83)
#define NXXX_IRQ_EDMA_1_CH7            (NXXX_IRQ_EXTINT + 84)
#define NXXX_IRQ_EDMA_1_CH8            (NXXX_IRQ_EXTINT + 85)
#define NXXX_IRQ_EDMA_1_CH9            (NXXX_IRQ_EXTINT + 86)
#define NXXX_IRQ_EDMA_1_CH10           (NXXX_IRQ_EXTINT + 87)
#define NXXX_IRQ_EDMA_1_CH11           (NXXX_IRQ_EXTINT + 88)
#define NXXX_IRQ_EDMA_1_CH12           (NXXX_IRQ_EXTINT + 89)
#define NXXX_IRQ_EDMA_1_CH13           (NXXX_IRQ_EXTINT + 90)
#define NXXX_IRQ_EDMA_1_CH14           (NXXX_IRQ_EXTINT + 91)
#define NXXX_IRQ_EDMA_1_CH15           (NXXX_IRQ_EXTINT + 92)
#define NXXX_IRQ_CDOG0                 (NXXX_IRQ_EXTINT + 93)
#define NXXX_IRQ_CDOG1                 (NXXX_IRQ_EXTINT + 94)
#define NXXX_IRQ_I3C0                  (NXXX_IRQ_EXTINT + 95)
#define NXXX_IRQ_I3C1                  (NXXX_IRQ_EXTINT + 96)
#define NXXX_IRQ_NPU                   (NXXX_IRQ_EXTINT + 97)
#define NXXX_IRQ_GDET                  (NXXX_IRQ_EXTINT + 98)
#define NXXX_IRQ_VBAT0                 (NXXX_IRQ_EXTINT + 99)
#define NXXX_IRQ_EWM0                  (NXXX_IRQ_EXTINT + 100)
#define NXXX_IRQ_TSI_END_OF_SCAN       (NXXX_IRQ_EXTINT + 101)
#define NXXX_IRQ_TSI_OUT_OF_SCAN       (NXXX_IRQ_EXTINT + 102)
#define NXXX_IRQ_EMVSIM0               (NXXX_IRQ_EXTINT + 103)
#define NXXX_IRQ_EMVSIM1               (NXXX_IRQ_EXTINT + 104)
#define NXXX_IRQ_FLEXIO                (NXXX_IRQ_EXTINT + 105)
#define NXXX_IRQ_DAC0                  (NXXX_IRQ_EXTINT + 106)
#define NXXX_IRQ_DAC1                  (NXXX_IRQ_EXTINT + 107)
#define NXXX_IRQ_DAC2                  (NXXX_IRQ_EXTINT + 108)
#define NXXX_IRQ_HSCMP0                (NXXX_IRQ_EXTINT + 109)
#define NXXX_IRQ_HSCMP1                (NXXX_IRQ_EXTINT + 110)
#define NXXX_IRQ_HSCMP2                (NXXX_IRQ_EXTINT + 111)
#define NXXX_IRQ_FLEXPWM0_RELOAD_ERROR (NXXX_IRQ_EXTINT + 112)
#define NXXX_IRQ_FLEXPWM0_FAULT        (NXXX_IRQ_EXTINT + 113)
#define NXXX_IRQ_FLEXPWM0_SUBMODULE0   (NXXX_IRQ_EXTINT + 114)
#define NXXX_IRQ_FLEXPWM0_SUBMODULE1   (NXXX_IRQ_EXTINT + 115)
#define NXXX_IRQ_FLEXPWM0_SUBMODULE2   (NXXX_IRQ_EXTINT + 116)
#define NXXX_IRQ_FLEXPWM0_SUBMODULE3   (NXXX_IRQ_EXTINT + 117)
#define NXXX_IRQ_FLEXPWM1_RELOAD_ERROR (NXXX_IRQ_EXTINT + 118)
#define NXXX_IRQ_FLEXPWM1_FAULT        (NXXX_IRQ_EXTINT + 119)
#define NXXX_IRQ_FLEXPWM1_SUBMODULE0   (NXXX_IRQ_EXTINT + 120)
#define NXXX_IRQ_FLEXPWM1_SUBMODULE1   (NXXX_IRQ_EXTINT + 121)
#define NXXX_IRQ_FLEXPWM1_SUBMODULE2   (NXXX_IRQ_EXTINT + 122)
#define NXXX_IRQ_FLEXPWM1_SUBMODULE3   (NXXX_IRQ_EXTINT + 123)
#define NXXX_IRQ_QDC0_COMPARE          (NXXX_IRQ_EXTINT + 124)
#define NXXX_IRQ_QDC0_HOME             (NXXX_IRQ_EXTINT + 125)
#define NXXX_IRQ_QDC0_WDG_SAB          (NXXX_IRQ_EXTINT + 126)
#define NXXX_IRQ_QDC0_IDX              (NXXX_IRQ_EXTINT + 127)
#define NXXX_IRQ_QDC1_COMPARE          (NXXX_IRQ_EXTINT + 128)
#define NXXX_IRQ_QDC1_HOME             (NXXX_IRQ_EXTINT + 129)
#define NXXX_IRQ_QDC1_WDG_SAB          (NXXX_IRQ_EXTINT + 130)
#define NXXX_IRQ_QDC1_IDX              (NXXX_IRQ_EXTINT + 131)
#define NXXX_IRQ_ITRC0                 (NXXX_IRQ_EXTINT + 132)
#define NXXX_IRQ_BSP32                 (NXXX_IRQ_EXTINT + 133)
#define NXXX_IRQ_ELS_ERR               (NXXX_IRQ_EXTINT + 134)
#define NXXX_IRQ_PKC_ERR               (NXXX_IRQ_EXTINT + 135)
#define NXXX_IRQ_ERM_SINGLE_BIT_ERROR  (NXXX_IRQ_EXTINT + 136)
#define NXXX_IRQ_ERM_MULTI_BIT_ERROR   (NXXX_IRQ_EXTINT + 137)
#define NXXX_IRQ_FMU0                  (NXXX_IRQ_EXTINT + 138)
#define NXXX_IRQ_ETHERNET              (NXXX_IRQ_EXTINT + 139)
#define NXXX_IRQ_ETHERNET_PMT          (NXXX_IRQ_EXTINT + 140)
#define NXXX_IRQ_ETHERNET_MACLP        (NXXX_IRQ_EXTINT + 141)
#define NXXX_IRQ_SINC_FILTER           (NXXX_IRQ_EXTINT + 142)
#define NXXX_IRQ_LPTMR0                (NXXX_IRQ_EXTINT + 143)
#define NXXX_IRQ_LPTMR1                (NXXX_IRQ_EXTINT + 144)
#define NXXX_IRQ_SCG                   (NXXX_IRQ_EXTINT + 145)
#define NXXX_IRQ_SPC                   (NXXX_IRQ_EXTINT + 146)
#define NXXX_IRQ_WUU                   (NXXX_IRQ_EXTINT + 147)
#define NXXX_IRQ_PORT_EFT              (NXXX_IRQ_EXTINT + 148)
#define NXXX_IRQ_ETB0                  (NXXX_IRQ_EXTINT + 149)
#define NXXX_IRQ_RESERVED166           (NXXX_IRQ_EXTINT + 150)
#define NXXX_IRQ_RESERVED167           (NXXX_IRQ_EXTINT + 151)
#define NXXX_IRQ_WWDT0                 (NXXX_IRQ_EXTINT + 152)
#define NXXX_IRQ_WWDT1                 (NXXX_IRQ_EXTINT + 153)
#define NXXX_IRQ_CMC0                  (NXXX_IRQ_EXTINT + 154)
#define NXXX_IRQ_CTI0                  (NXXX_IRQ_EXTINT + 155)

#define NXXX_IRQ_NEXTINT               (156)

/* Total amount of entries in system vector table */

#define NR_IRQS                        (NXXX_IRQ_EXTINT + NXXX_IRQ_NEXTINT)

#endif /* __ARCH_ARM_INCLUDE_MCX_NXXX_N947_IRQ_H */
