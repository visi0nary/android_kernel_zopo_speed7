/* Copyright Statement:
 *
 * This software/firmware and related documentation ("MediaTek Software") are
 * protected under relevant copyright laws. The information contained herein
 * is confidential and proprietary to MediaTek Inc. and/or its licensors.
 * Without the prior written permission of MediaTek inc. and/or its licensors,
 * any reproduction, modification, use or disclosure of MediaTek Software,
 * and information contained herein, in whole or in part, shall be strictly prohibited.
 */
/* MediaTek Inc. (C) 2010. All rights reserved.
 *
 * BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
 * THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE")
 * RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO RECEIVER ON
 * AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
 * NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
 * SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
 * SUPPLIED WITH THE MEDIATEK SOFTWARE, AND RECEIVER AGREES TO LOOK ONLY TO SUCH
 * THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. RECEIVER EXPRESSLY ACKNOWLEDGES
 * THAT IT IS RECEIVER'S SOLE RESPONSIBILITY TO OBTAIN FROM ANY THIRD PARTY ALL PROPER LICENSES
 * CONTAINED IN MEDIATEK SOFTWARE. MEDIATEK SHALL ALSO NOT BE RESPONSIBLE FOR ANY MEDIATEK
 * SOFTWARE RELEASES MADE TO RECEIVER'S SPECIFICATION OR TO CONFORM TO A PARTICULAR
 * STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND
 * CUMULATIVE LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
 * AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE,
 * OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY RECEIVER TO
 * MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
 *
 * The following software/firmware and/or related documentation ("MediaTek Software")
 * have been modified by MediaTek Inc. All revisions are subject to any receiver's
 * applicable license agreements with MediaTek Inc.
 */

/*****************************************************************************
 *  Copyright Statement:
 *  --------------------
 *  This software is protected by Copyright and the information contained
 *  herein is confidential. The software may not be copied and the information
 *  contained herein may not be used or disclosed except with the written
 *  permission of MediaTek Inc. (C) 2008
 *
 *  BY OPENING THIS FILE, BUYER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
 *  THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE")
 *  RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO BUYER ON
 *  AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES,
 *  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
 *  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
 *  NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
 *  SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
 *  SUPPLIED WITH THE MEDIATEK SOFTWARE, AND BUYER AGREES TO LOOK ONLY TO SUCH
 *  THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. MEDIATEK SHALL ALSO
 *  NOT BE RESPONSIBLE FOR ANY MEDIATEK SOFTWARE RELEASES MADE TO BUYER'S
 *  SPECIFICATION OR TO CONFORM TO A PARTICULAR STANDARD OR OPEN FORUM.
 *
 *  BUYER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND CUMULATIVE
 *  LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
 *  AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE,
 *  OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY BUYER TO
 *  MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
 *
 *  THE TRANSACTION CONTEMPLATED HEREUNDER SHALL BE CONSTRUED IN ACCORDANCE
 *  WITH THE LAWS OF THE STATE OF CALIFORNIA, USA, EXCLUDING ITS CONFLICT OF
 *  LAWS PRINCIPLES.  ANY DISPUTES, CONTROVERSIES OR CLAIMS ARISING THEREOF AND
 *  RELATED THERETO SHALL BE SETTLED BY ARBITRATION IN SAN FRANCISCO, CA, UNDER
 *  THE RULES OF THE INTERNATIONAL CHAMBER OF COMMERCE (ICC).
 *
 *****************************************************************************/

#if defined(BUILD_LK)
#include <platform/mt_gpio.h>
#include <platform/mt_pmic.h>
#else
#include <mach/mt_gpio.h>
#include <mach/mt_pm_ldo.h>
#include <mach/upmu_common.h>
#endif

#if !defined(BUILD_LK)
#include <linux/string.h>
#endif
#include "lcm_drv.h"


#ifdef BUILD_LK
#define LCD_DEBUG(fmt)  dprintf(CRITICAL,fmt)
#else
#define LCD_DEBUG(fmt)  printk(fmt)
#endif


const static unsigned char LCD_MODULE_ID = 0x02;
// ---------------------------------------------------------------------------
//  Local Constants
// ---------------------------------------------------------------------------

#define FRAME_WIDTH  (720)
#define FRAME_HEIGHT (1280)

#define REGFLAG_DELAY             							0xFC
#define REGFLAG_END_OF_TABLE      							0xFD   // END OF REGISTERS MARKER
#warning "klutu"
#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif
// ---------------------------------------------------------------------------
//  Local Variables
// ---------------------------------------------------------------------------

static LCM_UTIL_FUNCS lcm_util = {0};

#define SET_RESET_PIN(v)    (lcm_util.set_reset_pin((v)))

#define UDELAY(n) (lcm_util.udelay(n))
#define MDELAY(n) (lcm_util.mdelay(n))


// ---------------------------------------------------------------------------
//  Local Functions
// ---------------------------------------------------------------------------

#define dsi_set_cmdq_V2(cmd, count, ppara, force_update)	lcm_util.dsi_set_cmdq_V2(cmd, count, ppara, force_update)
#define dsi_set_cmdq(pdata, queue_size, force_update)		lcm_util.dsi_set_cmdq(pdata, queue_size, force_update)
#define wrtie_cmd(cmd)										lcm_util.dsi_write_cmd(cmd)
#define write_regs(addr, pdata, byte_nums)					lcm_util.dsi_write_regs(addr, pdata, byte_nums)
#define read_reg(cmd)										lcm_util.dsi_dcs_read_lcm_reg(cmd)
#define read_reg_v2(cmd, buffer, buffer_size)   			lcm_util.dsi_dcs_read_lcm_reg_v2(cmd, buffer, buffer_size)

struct LCM_setting_table {
  unsigned cmd;
  unsigned char count;
  unsigned char para_list[64];
};

static bool lcm_is_init = false;



static void lcm_init_power(void)
{
}

static void lcm_suspend_power(void)
{
}

static void lcm_resume_power(void)
{
}

static struct LCM_setting_table lcm_initialization_setting_tm[] = {
//***NT35521_JDI4.7_mipi******************
{0xF0,5,{0x55,0xAA,0x52,0x08,0x00}},
{0xFF,4,{0xAA,0x55,0xA5,0x80}},


//MPIP single parameter issue
{0x6F,2,{0x11,0x00}},
{0xF7,2,{0x20,0x00}},

//2013/03/27
{0xC8,1,{0x80}},


{0xB1,2,{0x28,0x21}},
{0xB5,1,{0xC8}},
{0xB6,1,{0x14}},
{0xB8,4,{0x00,0x00,0x14,0x0A}},
{0xB9,1,{0x00}},
{0xBA,1,{0x00}},
{0xBB,2,{0x63,0x63}},
{0xBC,2,{0x00,0x00}},
{0xBD,5,{0x02,0x78,0x10,0x18,0x00}},
{0xCC,16,{0x41,0x36,0x87,0x54,0x46,0x65,0x10,0x12,0x14,0x10,0x12,0x14,0x40,0x08,0xA5,0x05}},
{0xD0,1,{0x00}},
{0xD1,16,{0x00,0x04,0x08,0x0C,0x10,0x14,0x18,0x1C,0x20,0x24,0x28,0x2C,0x30,0x34,0x38,0x3C}},
{0xD3,1,{0x00}},
{0xD6,2,{0x44,0x44}},
{0xD7,12,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}},
{0xD8,13,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}},
{0xD9,3,{0x00,0x28,0x00}},
{0xE5,2,{0x00,0xFF}},
{0xE6,4,{0xF3,0xEC,0xE7,0xDF}},
{0xE7,10,{0xF3,0xD9,0xCC,0xC0,0xB3,0xA6,0x99,0x99,0x99,0x95}},
{0xE8,10,{0xF3,0xD9,0xCC,0xC0,0xB3,0xA6,0x99,0x99,0x99,0x95}},
{0xE9,2,{0x00,0x04}},
{0xEA,1,{0x00}},
{0xF0,5,{0x55,0xAA,0x52,0x00,0x00}},
{0xF0,5,{0x55,0xAA,0x52,0x08,0x01}},

{0xB0,2,{0x09,0x09}},
{0xB1,2,{0x09,0x09}},
{0xB3,2,{0x28,0x28}},
{0xB4,2,{0x23,0x23}},//15
{0xB6,2,{0x05,0x05}},
{0xB7,2,{0x05,0x05}},
{0xB8,2,{0x05,0x05}},
{0xB9,2,{0x35,0x35}},
{0xBA,2,{0x34,0x34}},
{0xBC,2,{0x6a,0x00}},//8C 72
{0xBD,2,{0x6a,0x00}},//8C 72
{0xC0,1,{0x04}},//0C
{0xBE,1,{0x8a}},//95 8a
//{0xBF,1,{0x50}},//VCOM 50
//{0xB8,2,{0x05,0x05}},
    
{0xB9,2,{0x35,0x35}},
//{0xBA,2,{0x35,0x35}},
{0xC1,1,{0x01}},
{0xC7,3,{0x00,0x00,0x00}},
{0xC9,6,{0x00,0x00,0x00,0x00,0x00,0x00}},
{0xCA,1,{0x00}},
{0xCB,2,{0x0B,0x53}},
{0xCD,3,{0x0B,0x52,0x53}},
{0xCF,3,{0x00,0x50,0x50}},
{0xF0,5,{0x55,0xAA,0x52,0x00,0x00}},
{0xF0,5,{0x55,0xAA,0x52,0x08,0x02}},
{0xB0,16,{0x00,0x41,0x00,0x54,0x00,0x73,0x00,0x81,0x00,0x95,0x00,0xB7,0x00,0xD3,0x00,0xFE}},
{0xB1,16,{0x01,0x25,0x01,0x5D,0x01,0x8D,0x01,0xD4,0x02,0x10,0x02,0x10,0x02,0x45,0x02,0x85}},
{0xB2,16,{0x02,0xAF,0x02,0xE5,0x03,0x14,0x03,0x46,0x03,0x74,0x03,0x9B,0x03,0xA6,0x03,0xAF}},
{0xB3,4,{0x03,0xBB,0x03,0xD0}},
{0xB4,16,{0x00,0x41,0x00,0x54,0x00,0x73,0x00,0x81,0x00,0x95,0x00,0xB7,0x00,0xD3,0x00,0xFE}},
{0xB5,16,{0x01,0x25,0x01,0x5D,0x01,0x8D,0x01,0xD4,0x02,0x10,0x02,0x10,0x02,0x45,0x02,0x85}},
{0xB6,16,{0x02,0xAF,0x02,0xE5,0x03,0x14,0x03,0x46,0x03,0x74,0x03,0x9B,0x03,0xA6,0x03,0xAF}},
{0xB7,4,{0x03,0xBB,0x03,0xD0}},
{0xB8,16,{0x00,0x41,0x00,0x54,0x00,0x73,0x00,0x81,0x00,0x95,0x00,0xB7,0x00,0xD3,0x00,0xFE}},
{0xB9,16,{0x01,0x25,0x01,0x5D,0x01,0x8D,0x01,0xD4,0x02,0x10,0x02,0x10,0x02,0x45,0x02,0x85}},
{0xBA,16,{0x02,0xAF,0x02,0xE5,0x03,0x14,0x03,0x46,0x03,0x74,0x03,0x9B,0x03,0xA6,0x03,0xAF}},
{0xBB,4,{0x03,0xBB,0x03,0xD0}},
{0xBC,16,{0x00,0x41,0x00,0x54,0x00,0x73,0x00,0x81,0x00,0x95,0x00,0xB7,0x00,0xD3,0x00,0xFE}},
{0xBD,16,{0x01,0x25,0x01,0x5D,0x01,0x8D,0x01,0xD4,0x02,0x10,0x02,0x10,0x02,0x45,0x02,0x85}},
{0xBE,16,{0x02,0xAF,0x02,0xE5,0x03,0x14,0x03,0x46,0x03,0x74,0x03,0x9B,0x03,0xA6,0x03,0xAF}},
{0xBF,4,{0x03,0xBB,0x03,0xD0}},
{0xC0,16,{0x00,0x41,0x00,0x54,0x00,0x73,0x00,0x81,0x00,0x95,0x00,0xB7,0x00,0xD3,0x00,0xFE}},
{0xC1,16,{0x01,0x25,0x01,0x5D,0x01,0x8D,0x01,0xD4,0x02,0x10,0x02,0x10,0x02,0x45,0x02,0x85}},
{0xC2,16,{0x02,0xAF,0x02,0xE5,0x03,0x14,0x03,0x46,0x03,0x74,0x03,0x9B,0x03,0xA6,0x03,0xAF}},
{0xC3,4,{0x03,0xBB,0x03,0xD0}},
{0xC4,16,{0x00,0x41,0x00,0x54,0x00,0x73,0x00,0x81,0x00,0x95,0x00,0xB7,0x00,0xD3,0x00,0xFE}},
{0xC5,16,{0x01,0x25,0x01,0x5D,0x01,0x8D,0x01,0xD4,0x02,0x10,0x02,0x10,0x02,0x45,0x02,0x85}},
{0xC6,16,{0x02,0xAF,0x02,0xE5,0x03,0x14,0x03,0x46,0x03,0x74,0x03,0x9B,0x03,0xA6,0x03,0xAF}},
{0xC7,4,{0x03,0xBB,0x03,0xD0}},
{0xEE,1,{0x00}},
{0xF0,5,{0x55,0xAA,0x52,0x00,0x00}},


{0xF0,5,{0x55,0xAA,0x52,0x08,0x03}},
{0xB0,2,{0xF5,0x00}},
{0xB1,2,{0xF5,0x00}},
{0xB2,5,{0x03,0x00,0x4B,0x00,0x00}},
{0xB6,5,{0x03,0x00,0x4B,0x00,0x00}},
{0xBA,5,{0x35,0x00,0x4B,0x00,0x00}},
{0xBB,5,{0x35,0x00,0x4B,0x00,0x00}},
{0xC0,4,{0x30,0x00,0x00,0x00}},
{0xC1,4,{0x30,0x00,0x00,0x00}},
{0xC2,4,{0x12,0x00,0x00,0x00}},
{0xC3,4,{0x12,0x00,0x00,0x00}},
{0xC4,1,{0x40}},
{0xC5,1,{0x40}},
{0xEF,1,{0x00}},

{0xF0,5,{0x55,0xAA,0x52,0x00,0x00}},
{0xF0,5,{0x55,0xAA,0x52,0x08,0x05}},
 
{0xCC,3,{0x00,0x00,0x04}},
{0xCD,3,{0x00,0x00,0x04}},
{0xCE,3,{0x00,0x00,0x04}},
{0xCF,3,{0x00,0x00,0x04}},
{0xD0,1,{0x14}},
{0xD1,4,{0x02,0x00,0x00,0x00}},
{0xD2,4,{0x02,0x00,0x00,0x06}},
{0xED,1,{0x03}},

//Added By Frank2013_04_10
{0xBD,5,{0x03,0x01,0x01,0x0F,0x0F}},
{0xB3,2,{0x17,0x26}},
{0xB7,2,{0x17,0x26}},
{0xE5,1,{0x06}},
{0xE6,1,{0x06}},
{0xE7,1,{0x06}},
{0xE8,1,{0x06}},
{0xEC,1,{0x06}},

{0xF0,5,{0x55,0xAA,0x52,0x00,0x00}},
{0xF0,5,{0x55,0xAA,0x52,0x08,0x06}},
{0xB0,2,{0x2E,0x00}},
{0xB1,2,{0x2D,0x10}},
{0xB2,2,{0x12,0x14}},
{0xB3,2,{0x16,0x31}},
{0xB4,2,{0x31,0x31}},
{0xB5,2,{0x31,0x31}},
{0xB6,2,{0x31,0x34}},
{0xB7,2,{0x2B,0x2A}},
{0xB8,2,{0x34,0x2C}},
{0xB9,2,{0x29,0x34}},
{0xBA,2,{0x34,0x29}},
{0xBB,2,{0x2C,0x34}},
{0xBC,2,{0x2A,0x2B}},
{0xBD,2,{0x34,0x31}},
{0xBE,2,{0x31,0x31}},
{0xBF,2,{0x31,0x31}},
{0xC0,2,{0x31,0x17}},
{0xC1,2,{0x15,0x13}},
{0xC2,2,{0x11,0x2D}},
{0xC3,2,{0x01,0x2E}},
{0xC4,2,{0x2E,0x2D}},
{0xC5,2,{0x01,0x17}},
{0xC6,2,{0x15,0x13}},
{0xC7,2,{0x11,0x31}},
{0xC8,2,{0x31,0x31}},
{0xC9,2,{0x31,0x31}},
{0xCA,2,{0x31,0x34}},
{0xCB,2,{0x2B,0x2A}},
{0xCC,2,{0x34,0x2C}},
{0xCD,2,{0x29,0x34}},
{0xCE,2,{0x34,0x29}},
{0xCF,2,{0x2C,0x34}},
{0xD0,2,{0x2A,0x2B}},
{0xD1,2,{0x34,0x31}},
{0xD2,2,{0x31,0x31}},
{0xD3,2,{0x31,0x31}},
{0xD4,2,{0x31,0x10}},
{0xD5,2,{0x12,0x14}},
{0xD6,2,{0x16,0x00}},
{0xD7,2,{0x2D,0x2E}},

{0xD8,5,{0x00,0x00,0x00,0x00,0x00}},
{0xD9,5,{0x00,0x00,0x00,0x00,0x00}},
{0xE5,2,{0x34,0x34}},
{0xE6,2,{0x34,0x34}},
{0xE7,1,{0x00}},
{0xF0,5,{0x55,0xAA,0x52,0x00,0x00}},
{0x35,1,{0x00}},

//{0xF0,5,{0x55,0xAA,0x52,0x08,0x00}},
//{0xD7,12,{0x30,0x30,0x30,0x3F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}},
//{0xD8,13,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3F,0x30,0x00}},
    
{0xF0,5,{0x55,0xAA,0x52,0x08,0x05}},
 


{0xC0,1,{0x05}},//05
{0xC4,1,{0x81}},//81
{0xC8,2,{0x03,0x30}},//03 30
{0xC9,2,{0x01,0x11}},//01 11
{0x6F,1,{0x1E}},
{0xFA,1,{0x20}},


//Regulator Reload
{0x6F,1,{0x11}},
{0xF3,1,{0x01}},
//////////////////////////////////////////////////////////////////


{0x11,1,{0x00}},
{REGFLAG_DELAY, 120, {}},
// Display ON
{0x29, 1, {0x00}},
{REGFLAG_DELAY, 50, {}},

	{REGFLAG_END_OF_TABLE, 0x00, {}},

};


static struct LCM_setting_table lcm_deep_sleep_mode_in_setting[] = {
    // Display off sequence
    {0x28, 1, {0x00}},
    {REGFLAG_DELAY, 20, {}},

    // Sleep Mode On
    {0x10, 1, {0x00}},
    {REGFLAG_DELAY, 120, {}},
    {REGFLAG_END_OF_TABLE, 0x00, {}}
};
static void push_table(struct LCM_setting_table *table, unsigned int count, unsigned char force_update)
{
    unsigned int i;

    for(i = 0; i < count; i++)
    {

        unsigned cmd;
        cmd = table[i].cmd;

        switch (cmd)
        {

            case REGFLAG_DELAY :
                MDELAY(table[i].count);
                break;

            case REGFLAG_END_OF_TABLE :
                break;

            default:
				
				dsi_set_cmdq_V2(cmd, table[i].count, table[i].para_list, force_update);
        }
    }
}
// ---------------------------------------------------------------------------
//  LCM Driver Implementations
// ---------------------------------------------------------------------------

static void lcm_set_util_funcs(const LCM_UTIL_FUNCS *util)
{
    memcpy(&lcm_util, util, sizeof(LCM_UTIL_FUNCS));
}


static void lcm_get_params(LCM_PARAMS *params)
{

    memset(params, 0, sizeof(LCM_PARAMS));

    params->type   = LCM_TYPE_DSI;

    params->width  = FRAME_WIDTH;
    params->height = FRAME_HEIGHT;

    // enable tearing-free
    params->dbi.te_mode                 = LCM_DBI_TE_MODE_DISABLED; //LCM_DBI_TE_MODE_VSYNC_ONLY;
    params->dbi.te_edge_polarity        = LCM_POLARITY_RISING;

#if (LCM_DSI_CMD_MODE)
    params->dsi.mode   = CMD_MODE;
#else
    params->dsi.mode   = BURST_VDO_MODE;
#endif

    // DSI
    /* Command mode setting */
    //1 Three lane or Four lane
    params->dsi.LANE_NUM                = LCM_FOUR_LANE;
    //The following defined the fomat for data coming from LCD engine.
    params->dsi.data_format.color_order = LCM_COLOR_ORDER_RGB;
    params->dsi.data_format.trans_seq   = LCM_DSI_TRANS_SEQ_MSB_FIRST;
    params->dsi.data_format.padding     = LCM_DSI_PADDING_ON_LSB;
    params->dsi.data_format.format      = LCM_DSI_FORMAT_RGB888;

    // Highly depends on LCD driver capability.
    // Not support in MT6573
    params->dsi.packet_size=256;

    // Video mode setting       
    params->dsi.intermediat_buffer_num = 0;//because DSI/DPI HW design change, this parameters should be 0 when video mode in MT658X; or memory leakage

    params->dsi.PS=LCM_PACKED_PS_24BIT_RGB888;
    params->dsi.word_count=720*3;

	params->dsi.vertical_sync_active = 2; //1
	params->dsi.vertical_backporch = 14;   //1
	params->dsi.vertical_frontporch = 14;  //6
	params->dsi.vertical_active_line = FRAME_HEIGHT;

	params->dsi.horizontal_sync_active = 4;
	params->dsi.horizontal_backporch = 100;
	params->dsi.horizontal_frontporch = 100;
	params->dsi.horizontal_active_pixel = FRAME_WIDTH;

	//params->dsi.LPX=8;

	// Bit rate calculation
	//1 Every lane speed
    params->dsi.PLL_CLOCK = 220;
}

static void lcm_init(void)
{
    SET_RESET_PIN(1);
    MDELAY(10);
    SET_RESET_PIN(0);
    MDELAY(20);
    SET_RESET_PIN(1);
    MDELAY(50);

    push_table(lcm_initialization_setting_tm, sizeof(lcm_initialization_setting_tm) / sizeof(struct LCM_setting_table), 1);
}

static void lcm_suspend(void)
{
    push_table(lcm_deep_sleep_mode_in_setting, sizeof(lcm_deep_sleep_mode_in_setting) / sizeof(struct LCM_setting_table), 1);
    SET_RESET_PIN(0);
    MDELAY(5);
}

static void lcm_resume(void)
{
    lcm_init();
}

static unsigned int lcm_compare_id(void)
{
    unsigned int id;
    unsigned char buffer[5];
    unsigned int array[5];
	unsigned int data_array[16];

    SET_RESET_PIN(1);
    MDELAY(10);
    SET_RESET_PIN(0);
    MDELAY(50);
    SET_RESET_PIN(1);
    MDELAY(120);

    data_array[0] = 0x00063902;
    data_array[1] = 0x52AA55F0;
    data_array[2] = 0x00000108;
    dsi_set_cmdq(&data_array, 3, 1);

	array[0] = 0x00033700;// read id return two byte,version and id
	dsi_set_cmdq(array, 1, 1);

	read_reg_v2(0xC5, buffer, 3);
	id = buffer[1]; //we only need ID
    #ifdef BUILD_LK
	printf("%s, LK nt35521 debug: nt35521 id = 0x%08x buffer[0]=0x%08x,buffer[1]=0x%08x,buffer[2]=0x%08x\n", __func__, id,buffer[0],buffer[1],buffer[2]);
    #else
	printk("%s, LK nt35521 debug: nt35521 id = 0x%08x buffer[0]=0x%08x,buffer[1]=0x%08x,buffer[2]=0x%08x\n", __func__, id,buffer[0],buffer[1],buffer[2]);
    #endif

   // if(id == LCM_ID_NT35521)
    if(buffer[0]==0x55 && buffer[1]==0x21)
    	return 1;
    else
        return 0;
}
//
// ---------------------------------------------------------------------------
//  Get LCM Driver Hooks
// ---------------------------------------------------------------------------
LCM_DRIVER nt35521_jdi47_rixian_hd_lcm_drv =
{
    .name			= "nt35521_jdi47_rixian_hd",
    .set_util_funcs = lcm_set_util_funcs,
    .get_params     = lcm_get_params,
    .init           = lcm_init,
    .suspend        = lcm_suspend,
    .resume         = lcm_resume,
    .compare_id     = lcm_compare_id,
#if (LCM_DSI_CMD_MODE)
    .update         = lcm_update,
#endif
    .init_power        = lcm_init_power,
    .resume_power = lcm_resume_power,
    .suspend_power = lcm_suspend_power,

};
