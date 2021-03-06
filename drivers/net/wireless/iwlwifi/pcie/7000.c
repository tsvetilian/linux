/******************************************************************************
 *
 * Copyright(c) 2008 - 2013 Intel Corporation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110, USA
 *
 * The full GNU General Public License is included in this distribution in the
 * file called LICENSE.
 *
 * Contact Information:
 *  Intel Linux Wireless <ilw@linux.intel.com>
 * Intel Corporation, 5200 N.E. Elam Young Parkway, Hillsboro, OR 97124-6497
 *
 *****************************************************************************/

#include <linux/module.h>
#include <linux/stringify.h>
#include "iwl-config.h"
#include "iwl-agn-hw.h"
#include "cfg.h"

/* Highest firmware API version supported */
#define IWL7260_UCODE_API_MAX	6
#define IWL3160_UCODE_API_MAX	6

/* Oldest version we won't warn about */
#define IWL7260_UCODE_API_OK	6
#define IWL3160_UCODE_API_OK	6

/* Lowest firmware API version supported */
#define IWL7260_UCODE_API_MIN	6
#define IWL3160_UCODE_API_MIN	6

/* NVM versions */
#define IWL7260_NVM_VERSION		0x0a1d
#define IWL7260_TX_POWER_VERSION	0xffff /* meaningless */
#define IWL3160_NVM_VERSION		0x709
#define IWL3160_TX_POWER_VERSION	0xffff /* meaningless */

#define IWL7260_FW_PRE "iwlwifi-7260-"
#define IWL7260_MODULE_FIRMWARE(api) IWL7260_FW_PRE __stringify(api) ".ucode"

#define IWL3160_FW_PRE "iwlwifi-3160-"
#define IWL3160_MODULE_FIRMWARE(api) IWL3160_FW_PRE __stringify(api) ".ucode"

static const struct iwl_base_params iwl7000_base_params = {
	.eeprom_size = OTP_LOW_IMAGE_SIZE,
	.num_of_queues = IWLAGN_NUM_QUEUES,
	.pll_cfg_val = 0,
	.shadow_ram_support = true,
	.led_compensation = 57,
	.adv_thermal_throttle = true,
	.support_ct_kill_exit = true,
	.plcp_delta_threshold = IWL_MAX_PLCP_ERR_THRESHOLD_DEF,
	.chain_noise_scale = 1000,
	.wd_timeout = IWL_LONG_WD_TIMEOUT,
	.max_event_log_size = 512,
	.shadow_reg_enable = false, /* TODO: fix bugs using this feature */
};

static const struct iwl_ht_params iwl7000_ht_params = {
	.ht_greenfield_support = true,
	.use_rts_for_aggregation = true, /* use rts/cts protection */
	.ht40_bands = BIT(IEEE80211_BAND_2GHZ) | BIT(IEEE80211_BAND_5GHZ),
};

#define IWL_DEVICE_7000						\
	.ucode_api_max = IWL7260_UCODE_API_MAX,			\
	.ucode_api_ok = IWL7260_UCODE_API_OK,			\
	.ucode_api_min = IWL7260_UCODE_API_MIN,			\
	.device_family = IWL_DEVICE_FAMILY_7000,		\
	.max_inst_size = IWL60_RTC_INST_SIZE,			\
	.max_data_size = IWL60_RTC_DATA_SIZE,			\
	.base_params = &iwl7000_base_params,			\
	/* TODO: .bt_params? */					\
	.need_temp_offset_calib = true,				\
	.led_mode = IWL_LED_RF_STATE,				\
	.adv_pm = true						\


const struct iwl_cfg iwl7260_2ac_cfg = {
	.name = "Intel(R) Dual Band Wireless AC7260",
	.fw_name_pre = IWL7260_FW_PRE,
	IWL_DEVICE_7000,
	.ht_params = &iwl7000_ht_params,
	.nvm_ver = IWL7260_NVM_VERSION,
	.nvm_calib_ver = IWL7260_TX_POWER_VERSION,
};

const struct iwl_cfg iwl3160_ac_cfg = {
	.name = "Intel(R) Dual Band Wireless AC3160",
	.fw_name_pre = IWL3160_FW_PRE,
	IWL_DEVICE_7000,
	.ht_params = &iwl7000_ht_params,
	.nvm_ver = IWL3160_NVM_VERSION,
	.nvm_calib_ver = IWL3160_TX_POWER_VERSION,
};

MODULE_FIRMWARE(IWL7260_MODULE_FIRMWARE(IWL7260_UCODE_API_OK));
MODULE_FIRMWARE(IWL3160_MODULE_FIRMWARE(IWL3160_UCODE_API_OK));
