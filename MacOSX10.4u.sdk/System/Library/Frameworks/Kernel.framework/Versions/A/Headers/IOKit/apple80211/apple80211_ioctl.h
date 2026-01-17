/*
 * Copyright (c) 2005 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * The contents of this file constitute Original Code as defined in and
 * are subject to the Apple Public Source License Version 1.1 (the
 * "License").  You may not use this file except in compliance with the
 * License.  Please obtain a copy of the License at
 * http://www.apple.com/publicsource and read it before using this file.
 * 
 * This Original Code and all software distributed under the License are
 * distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE OR NON-INFRINGEMENT.  Please see the
 * License for the specific language governing rights and limitations
 * under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */

#ifndef _APPLE80211_IOCTL_H_
#define _APPLE80211_IOCTL_H_

#include <sys/socket.h>
#include <net/if.h>
#include <net/ethernet.h>
#include <sys/param.h>

#include "apple80211_var.h"

struct apple80211req
{
	char		req_if_name[IFNAMSIZ];	// 16 bytes
	int			req_type;				// 4 bytes
	int			req_val;				// 4 bytes
	u_int32_t	req_len;				// 4 bytes
	void	   *req_data;				// 4 bytes
};

#define SIOCSA80211 _IOW( 'i', 200, struct apple80211req )
#define SIOCGA80211 _IOWR( 'i', 201, struct apple80211req )

// req_type


#define	APPLE80211_IOC_SSID						1	// req_type
	
#define	APPLE80211_IOC_AUTH_TYPE				2	// req_type
#define		APPLE80211_AUTH_TYPE_UNICAST	1		// req_val, SIOCGA80211 only
#define		APPLE80211_AUTH_TYPE_MULTICAST	2		// req_val, SIOCGA80211 only

#define	APPLE80211_IOC_CIPHER_KEY				3	// req_type
#define		APPLE80211_CIPHER_KEY_UNICAST	1		// req_val
#define		APPLE80211_CIPHER_KEY_MULICAST	2		// req_val

#define	APPLE80211_IOC_CHANNEL					4	// req_type

#define	APPLE80211_IOC_POWERSAVE				5	// req_type

#define	APPLE80211_IOC_PROTMODE					6	// req_type

#define APPLE80211_IOC_TXPOWER					7	// req_type
#define APPLE80211_IOC_RATE						8	// req_type
#define APPLE80211_IOC_BSSID					9	// req_type

#define APPLE80211_IOC_SCAN_REQ					10	// req_type

#define APPLE80211_IOC_SCAN_RESULT				11	// req_type

#define APPLE80211_IOC_CARD_CAPABILITIES		12	// req_type

#define APPLE80211_IOC_STATE					13	// req_type (apple80211_state)
#define APPLE80211_IOC_PHY_MODE					14	// req_type (apple80211_phymode)

#define APPLE80211_IOC_OP_MODE					15	// req_type (apple80211_opmode)
#define APPLE80211_IOC_RSSI						16	// req_type
#define APPLE80211_IOC_NOISE					17	// req_type

#define APPLE80211_IOC_INT_MIT					18
#define		APPLE80211_IOC_INT_MIT_OFF 1			// req_val
#define		APPLE80211_IOC_INT_MIT_ON  2			// req_val

// card power
#define APPLE80211_IOC_POWER					19	// req_type

#define	APPLE80211_IOC_ASSOCIATE				20	// req_type
#define APPLE80211_IOC_ASSOCIATE_RESULT			21	// req_type
#define APPLE80211_IOC_DISASSOCIATE				22	// req_type
#define APPLE80211_IOC_STATUS_DEV_NAME			23	// req_type

#define APPLE80211_IOC_IBSS_MODE				24	// req_type
#define		APPLE80211_IOC_IBSS_MODE_START	1		// req_val
#define		APPLE80211_IOC_IBSS_MODE_STOP	2		// req_val

#define APPLE80211_IOC_HOST_AP_MODE				25	// req_type
#define		APPLE80211_IOC_HOST_AP_MODE_START	1	// req_val
#define		APPLE80211_IOC_HOST_AP_MODE_STOP	2	// req_val

#define APPLE80211_IOC_AP_MODE					26	// req_type (apple80211_apmode)
#define APPLE80211_IOC_SUPPORTED_CHANNELS		27	// req_type
#define APPLE80211_IOC_LOCALE					28	// req_type
#define APPLE80211_IOC_DEAUTH					29  // req_type
#define APPLE80211_IOC_COUNTERMEASURES			30	// req_type
#define APPLE80211_IOC_FRAG_THRESHOLD			31	// req_type
#define APPLE80211_IOC_RATE_SET					32	// req_type
#define APPLE80211_IOC_SHORT_SLOT				33	// req_type
#define APPLE80211_IOC_MULTICAST_RATE			34	// req_type
#define APPLE80211_IOC_SHORT_RETRY_LIMIT		35	// req_type
#define APPLE80211_IOC_LONG_RETRY_LIMIT			36	// req_type
#define APPLE80211_IOC_TX_ANTENNA				37	// req_type
#define APPLE80211_IOC_RX_ANTENNA				38	// req_type
#define APPLE80211_IOC_ANTENNA_DIVERSITY		39	// req_type
#define APPLE80211_IOC_ROM						40	// req_type
#define APPLE80211_IOC_DTIM_INT					41	// req_type
#define APPLE80211_IOC_STATION_LIST				42	// req_type
#define APPLE80211_IOC_DRIVER_VERSION			43	// req_type
#define APPLE80211_IOC_HARDWARE_VERSION			44	// req_type
#define APPLE80211_IOC_RAND						45	// req_type
#define APPLE80211_IOC_RSN_IE					46	// req_type
#define APPLE80211_IOC_BACKGROUND_SCAN			47	// req_type
#define APPLE80211_IOC_AP_IE_LIST				48	// req_type
#define APPLE80211_IOC_STATS					49	// req_type
#define APPLE80211_IOC_ASSOCIATION_STATUS		50  // req_type
#define APPLE80211_IOC_COUNTRY_CODE				51	// req_type
#define APPLE80211_IOC_DEBUG_FLAGS				52	// req_type
#define APPLE80211_IOC_LAST_RX_PKT_DATA			53	// req_type
#define APPLE80211_IOC_RADIO_INFO				54	// req_type
#define APPLE80211_IOC_GUARD_INTERVAL			55	// req_type
#define APPLE80211_IOC_MIMO_POWERSAVE			56	// req_type
#define APPLE80211_IOC_MCS						57	// req_type
#define APPLE80211_IOC_RIFS						58	// req_type
#define APPLE80211_IOC_LDPC						59	// req_type
#define APPLE80211_IOC_MSDU						60	// req_type
#define APPLE80211_IOC_MPDU						61	// req_type
#define APPLE80211_IOC_BLOCK_ACK				62	// req_type
#define APPLE80211_IOC_PLS						63	// req_type
#define APPLE80211_IOC_PSMP						64	// req_type
#define APPLE80211_IOC_PHY_SUB_MODE				65	// req_type
#define APPLE80211_IOC_MCS_INDEX_SET			66	// req_type

#define APPLE80211_IOC_CARD_SPECIFIC			255	// req_type

// Kernel interface

// Bump this value when structures change
#define APPLE80211_VERSION	1

struct apple80211_ssid_data
{
	u_int32_t	version;
	u_int32_t	ssid_len;
	u_int8_t	ssid_bytes[APPLE80211_MAX_SSID_LEN];
};

struct apple80211_channel_data
{
	u_int32_t					version;
	struct apple80211_channel	channel;
};

struct apple80211_bssid_data
{
	u_int32_t			version;
	struct ether_addr	bssid;
};

struct apple80211_capability_data
{
	u_int32_t	version;
	u_int32_t	capabilities[APPLE80211_CAP_MAX];
};

struct apple80211_state_data
{
	u_int32_t	version;
	u_int32_t	state;
};

struct apple80211_rssi_data	
{
	u_int32_t	version;
	u_int32_t	num_radios;
	u_int32_t	rssi_unit;
	int32_t		rssi[APPLE80211_MAX_RADIO];		// control channel
	int32_t		aggregate_rssi;					// aggregate control channel rssi
	int32_t		rssi_ext[APPLE80211_MAX_RADIO];	// extension channel rssi
	int32_t		aggregate_rssi_ext;				// aggregate extension channel rssi
};

struct apple80211_power_data
{
	u_int32_t	version;
	u_int32_t	num_radios;
	u_int32_t	power_state[APPLE80211_MAX_RADIO];
};

struct apple80211_assoc_result_data
{
	u_int32_t	version;
	u_int32_t	result;
};

struct apple80211_assoc_status_data
{
	u_int32_t	version;
	u_int32_t	status;
};

struct apple80211_rate_data
{
	u_int32_t	version;
	u_int32_t	num_radios;
	u_int32_t	rate[APPLE80211_MAX_RADIO];
};

struct apple80211_status_dev_data
{
	u_int32_t	version;
	u_int8_t	dev_name[MAXPATHLEN];
};

struct apple80211_powersave_data
{
	u_int32_t	version;
	u_int32_t	powersave_level; 
};

struct apple80211_protmode_data
{
	u_int32_t	version;
	u_int32_t	protmode;
	u_int32_t	threshold;		// bytes
};

struct apple80211_txpower_data
{
	u_int32_t	version;
	u_int32_t	txpower_unit;
	int32_t		txpower;
};

struct apple80211_phymode_data
{
	u_int32_t	version;
	u_int32_t	phy_mode;			// vector of supported phy modes
	u_int32_t	active_phy_mode;	// current active phy mode
};

struct apple80211_opmode_data
{
	u_int32_t	version;
	u_int32_t	op_mode;
};

struct apple80211_noise_data
{
	u_int32_t	version;
	u_int32_t	num_radios;
	u_int32_t	noise_unit;
	int32_t		noise[APPLE80211_MAX_RADIO];		// control channel
	int32_t		aggregate_noise;					// aggregate control channel noise
	int32_t		noise_ext[APPLE80211_MAX_RADIO];	// extension channel noise
	int32_t		aggregate_noise_ext;				// aggregate extension channel noise
};

struct apple80211_intmit_data
{
	u_int32_t	version;
	u_int32_t	int_mit;
};

struct apple80211_authtype_data
{
	u_int32_t	version;
	u_int32_t	authtype_lower;	//	apple80211_authtype_lower
	u_int32_t	authtype_upper;	//	apple80211_authtype_upper
};

struct apple80211_sup_channel_data
{
	u_int32_t					version;
	u_int32_t					num_channels;
	struct apple80211_channel	supported_channels[APPLE80211_MAX_CHANNELS];
};

struct apple80211_locale_data
{
	u_int32_t	version;
	u_int32_t	locale;
};

struct apple80211_scan_data
{
	u_int32_t					version;
	u_int32_t					bss_type;							// apple80211_apmode
	struct ether_addr			bssid;								// target BSSID
	u_int32_t					ssid_len;							// length of the SSID
	u_int8_t					ssid[APPLE80211_MAX_SSID_LEN];
	u_int32_t					scan_type;							// apple80211_scan_type
	u_int32_t					phy_mode;							// apple80211_phymode vector
	u_int16_t					dwell_time;							// time to spend on each channel (ms)
	u_int32_t					rest_time;							// time between scanning each channel (ms)
	u_int32_t					num_channels;						// 0 if not passing in channels
	struct apple80211_channel	channels[APPLE80211_MAX_CHANNELS];	// channel list
};

struct apple80211_apmode_data
{
	u_int32_t	version;
	u_int32_t	apmode;
};

struct apple80211_assoc_data
{
	u_int32_t				version;
	u_int16_t				ad_mode;		// apple80211_apmode
	u_int16_t				ad_auth_lower;	// apple80211_authtype_lower
	u_int16_t				ad_auth_upper;	// apple80211_authtype_upper
	u_int32_t				ad_ssid_len;
	u_int8_t				ad_ssid[ APPLE80211_MAX_SSID_LEN ];
	struct ether_addr		ad_bssid;		// prefer over ssid if not zeroed
	struct apple80211_key	ad_key;	
	u_int16_t				ad_rsn_ie_len;
	u_int8_t				ad_rsn_ie[ APPLE80211_MAX_RSN_IE_LEN ];
};

struct apple80211_deauth_data
{
	u_int32_t			version;
	u_int32_t			deauth_reason;	// reason code
	struct ether_addr	deauth_ea;		// BSSID of AP
};

struct apple80211_countermeasures_data
{
	u_int32_t	version;
	u_int32_t	enabled;
};

struct apple80211_frag_threshold_data
{
	u_int32_t	version;
	u_int32_t	threshold;	// bytes
};

struct apple80211_rate_set_data
{
	u_int32_t				version;
	u_int16_t				num_rates;
	struct apple80211_rate	rates[APPLE80211_MAX_RATES];
};

struct apple80211_short_slot_data
{
	u_int32_t	version;
	u_int8_t	mode;
};

struct apple80211_retry_limit_data
{
	u_int32_t	version;
	u_int32_t	limit;
};

struct apple80211_antenna_data
{
	u_int32_t	version;
	u_int32_t	num_radios;
	int32_t		antenna_index[APPLE80211_MAX_RADIO];
};

struct apple80211_dtim_int_data
{
	u_int32_t	version;
	u_int32_t	interval;
};

struct apple80211_sta_data
{
	u_int32_t					version;
	u_int32_t					num_stations;
	struct apple80211_station	station_list[APPLE80211_MAX_STATIONS];
};

struct apple80211_version_data
{
	u_int32_t	version;
	u_int16_t	string_len;
	char		string[APPLE80211_MAX_VERSION_LEN];
};

struct apple80211_rom_data
{
	u_int32_t	version;
	u_int32_t	rom_len;
	u_int8_t	rom[1];	// variable length
};

struct apple80211_rand_data
{
	u_int32_t	version;
	u_int32_t	rand;
};

struct apple80211_rsn_ie_data
{
	u_int32_t	version;
	u_int16_t	len;
	u_int8_t	ie[ APPLE80211_MAX_RSN_IE_LEN ];
};

struct apple80211_ap_ie_data
{
	u_int32_t	version;
	u_int32_t	len;
	u_int8_t	*ie_data;
};

struct apple80211_stats_data
{
	u_int32_t	version;
	u_int32_t	tx_frame_count;
	u_int32_t	tx_errors;
	u_int32_t	rx_frame_count;
	u_int32_t	rx_errors;
};

struct apple80211_country_code_data
{
	u_int32_t	version;
	u_int8_t	cc[APPLE80211_MAX_CC_LEN];
};

struct apple80211_last_rx_pkt_data
{
	u_int32_t	version;
	u_int32_t	rate;
	int32_t		rssi;
	u_int32_t	num_streams;	// number of spatial streams
	struct ether_addr sa;		// source address
};

struct apple80211_radio_info_data
{
	u_int32_t	version;
	u_int32_t	count;		// number of rf chains
};

struct apple80211_guard_interval_data
{
	u_int32_t	version;
	u_int32_t	interval;	// apple80211_guard_interval
};

struct apple80211_mcs_data
{
	u_int32_t	version;
	u_int32_t	index;		// 0 to APPLE80211_MAX_MCS_INDEX
};

struct apple80211_rifs_data
{
	u_int32_t	version;
	u_int32_t	enabled;
};

struct apple80211_ldpc_data
{
	u_int32_t	version;
	u_int32_t	enabled;
};

struct apple80211_msdu_data
{
	u_int32_t	version;
	u_int32_t	max_length;		// 3839 or 7935 bytes
};

struct apple80211_mpdu_data
{
	u_int32_t	version;
	u_int32_t	max_factor;		// 0 - APPLE80211_MAX_MPDU_FACTOR
	u_int32_t	max_density;	// 0 - APPLE80211_MAX_MPDU_DENSITY
};

struct apple80211_block_ack_data
{
	u_int32_t	version;
	u_int8_t	ba_enabled;				// block ack enabled
	u_int8_t	immediate_ba_enabled;	// immediate block ack enabled
	u_int8_t	cbba_enabled;			// compressed bitmap block ack enabled
	u_int8_t	implicit_ba_enabled;	// implicit block ack enabled
};

struct apple80211_pls_data
{
	u_int32_t	version;
	u_int32_t	enabled;	// phy level spoofing enabled
};

struct apple80211_psmp_data
{
	u_int32_t	version;
	u_int32_t	enabled;
};

struct apple80211_physubmode_data
{
	u_int32_t	version;
	u_int32_t	phy_mode;		// one apple80211_phymode
	u_int32_t	phy_submode;	// one apple80211_physubmode
	u_int32_t	flags;			// apple80211_channel_flag vector
};

struct apple80211_mcs_index_set_data
{
	u_int32_t	version;
	u_int8_t	mcs_set_map[APPLE80211_MAP_SIZE( APPLE80211_MAX_MCS_INDEX + 1 )];
};

#endif // _APPLE80211_IOCTL_H_
