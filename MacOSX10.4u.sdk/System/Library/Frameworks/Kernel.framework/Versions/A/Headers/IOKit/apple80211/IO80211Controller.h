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

#ifndef _IO80211CONTROLLER_H
#define _IO80211CONTROLLER_H

/*
 * Kernel
 */
#if defined(KERNEL) && defined(__cplusplus)

#include <libkern/version.h>

#if VERSION_MAJOR > 8
	#define _MODERN_BPF
#endif

#include <IOKit/network/IOEthernetController.h>

#include <sys/param.h>
#include <net/bpf.h>

#include "apple80211_ioctl.h"

// always compile with legacy compatibility for now. This will go away soon.
#ifndef IO80211_LEGACY_COMPAT
#define IO80211_LEGACY_COMPAT
#endif 

#ifdef IO80211_LEGACY_COMPAT
#ifndef __STRUCT_WEPNETWORK__
#define __STRUCT_WEPNETWORK__
// Have to redifine this here because can't include AirPortComm.h; this header file is used by all the vendors
typedef struct WepNetwork
{
//	UInt32	keyLen;					// zero keyLen ==> encryption off
	UInt16	bssType;				// selects Infra/IBSS
	UInt16	keyLen;					// zero keyLen ==> encryption off
	UInt8	key[16];				// WEP key (5 or 13 bytes)
	UInt16	authentication;			// open system, or shared key
	char	ssid[34];               // Network name.
	UInt8	rsnKey[32];				// RSN keys are bigger
} WepNetwork;
typedef WepNetwork *WepNetworkPtr;
#endif
#endif

#define DEFAULT_SCAN_TIME		3	// seconds
#define AUTH_TIMEOUT			15	// seconds

/*! @enum LinkSpeed.
    @abstract ???.
    @discussion ???.
	@constant LINK_SPEED_80211A 54 Mbps
    @constant LINK_SPEED_80211B 11 Mbps.
    @constant LINK_SPEED_80211G 54 Mbps.
	*/
enum {
	LINK_SPEED_80211A	= 54000000ul,		// 54 Mbps
	LINK_SPEED_80211B	= 11000000ul,		// 11 Mbps
	LINK_SPEED_80211G	= 54000000ul,		// 54 Mbps
	LINK_SPEED_80211N	= 300000000ul,		// 300 Mbps (MCS index 15, 400ns GI, 40 MHz channel)
};

enum IO80211CountryCodeOp
{
	kIO80211CountryCodeReset,				// Reset country code to world wide default, and start
											// searching for 802.11d beacon
};
typedef enum IO80211CountryCodeOp IO80211CountryCodeOp;

enum IO80211SystemPowerState
{
	kIO80211SystemPowerStateUnknown,
	kIO80211SystemPowerStateAwake,
	kIO80211SystemPowerStateSleeping,
};
typedef enum IO80211SystemPowerState IO80211SystemPowerState;

#define IO80211_LOG( _interface, _level, _msg, ... )	do{ if( _interface && ( _interface->debugFlags() & _level ) ) IOLog( _msg, ##__VA_ARGS__ ); }while(0)

class IO80211Interface;
class IO80211Scanner;
class IO80211WorkLoop;

/*! @class IO80211Controller
    @abstract Abstract superclass for 80211 controllers. 
    @discussion 80211 controller drivers should subclass IO80211Controller, and implement or override the hardware specific methods to create an 80211 driver. An interface object (an IO80211Interface instance) must be instantiated by the driver, through attachInterface(), to connect the controller driver to the data link layer. 
	*/
class IO80211Controller : public IOEthernetController
{
    OSDeclareAbstractStructors( IO80211Controller )

	#ifdef IO80211_LEGACY_COMPAT
	private:
		struct apple80211_key			_lastAssocKey;
		struct apple80211_assoc_data	_lastAssocData;
		UInt8							_mcastCipher;
		bool							_interferenceRobustness;
		IO80211Scanner					*_scanner;
		WepNetwork						_lastLegacyAssocInfo;

	public:
		IOReturn newUserClient( task_t owningTask, void * securityID, UInt32 type, 
						OSDictionary * properties, IOUserClient ** handler );
		IOReturn queueCommand( UInt8 commandCode, void *arguments, void *returnValue );
		static IOReturn execCommand( OSObject * obj, void *field0, void *field1, void *field2, void *field3 );

		IOReturn getLastAssocKey(struct apple80211_key* key, UInt8* mcastCipher);
		IOReturn setLastAssocKey(struct apple80211_key* key, UInt8 mcastCipher);
		
		SInt32 getLastAssocData( struct apple80211_assoc_data * ad );
		SInt32 setLastAssocData( struct apple80211_assoc_data * ad );

		IOReturn getLastLegacyAssocInfo(WepNetworkPtr netPtr );
		IOReturn setLastLegacyAssocInfo(WepNetworkPtr netPtr );
		
		bool getInterferenceRobustness()			{ return _interferenceRobustness; }
		void setInterferenceRobustness(bool flag)	{ _interferenceRobustness = flag; }
		
		IO80211Scanner *getScanner()				{ return _scanner; }
		void setScanner(IO80211Scanner *scanner)	{ _scanner = scanner; }
	#endif

public:
	
	/*! @function start
		@abstract ???.
		@param provider ???.
		@result Returns true on success, false otherwise. 
		*/ 
	virtual bool				start(IOService *provider);

	/*! @function stop
		@abstract ???.
		@param provider ???.
		*/ 
	virtual void				stop(IOService *provider);

	/*! @function init
		@abstract ???.
		@result ???. 
		*/ 
	virtual bool				init(OSDictionary * properties);
	
	/*! @function free
		@abstract ???.
		@result ???. 
		*/ 
	virtual void				free();

	/*! @function createWorkLoop
		@abstract ???.
		@result ???. 
		*/ 
	virtual bool				createWorkLoop();

	/*! @function getWorkLoop
		@abstract ???.
		@result ???. 
		*/ 
	virtual IOWorkLoop			*getWorkLoop() const;
	
	/*! @function getProvider
		@abstract ???.
		@result ???. 
		*/
	IOService * getProvider();

	/*! @function enable
		@abstract ???.
		@param aNetif ???.
		@result Returns ???. 
		*/ 
	virtual IOReturn			enable(IONetworkInterface *aNetif);

	/*! @function disable
		@abstract ???.
		@param aNetif ???.
		@result Returns ???. 
		*/ 
	virtual IOReturn			disable(IONetworkInterface *aNetif);

	/*! @function getHardwareAddress
		@abstract Gets the 80211 controller's station address.
		@discussion The default implementation of the abstract method inherited from IONetworkController. This method will call the overloaded form IO80211Controller::getHardwareAddress() that subclasses are expected to override.
		@param addr The buffer where the controller's hardware address should be written.
		@param inOutAddrBytes The size of the address buffer provided by the client, and replaced by this method with the actual size of the hardware address in bytes.
		@result Returns kIOReturnSuccess on success, or an error otherwise. 
		*/
	virtual IOReturn			getHardwareAddress(IOEthernetAddress *addr);
	
	/*! @function getOutputQueue
		@abstract ???.
		@param ???.
		@result Returns ???. 
		*/ 
	virtual IOOutputQueue * getOutputQueue() const;

	/*! @function configureInterface
		@abstract Configures a newly created network interface object.
		@discussion This method configures an interface object that was created by
		createInterface(). Subclasses can override this method to customize
		and examine the interface object that will be attached to the
		controller as a client.
		@param interface The interface object to be configured.
		@result Returns true if the operation was successful, false otherwise
		(this will cause attachInterface() to fail and return 0). 
		*/
	virtual bool configureInterface(IONetworkInterface * netIf);
	
	/*! @function registerWithPolicyMaker
		@abstract ???.
		@param policyMaker ???.
		@result Returns ???. 
		*/ 
    virtual IOReturn			registerWithPolicyMaker(IOService *policyMaker);
	
	/*! @function scanTimeForRequest
		@abstract ???.
		@param policyMaker ???.
		@result Returns ???. 
		*/ 
	virtual UInt32				scanTimeForRequest( IO80211Interface * interface, 
													struct apple80211_scan_data * sd ) { return DEFAULT_SCAN_TIME; }
	
	/*! @function inputMonitorPacket
		@abstract ???.
		@param m ???.
		*/ 
#if defined( _MODERN_BPF )
	virtual void				inputMonitorPacket( mbuf_t m, UInt32 dlt, void * header, size_t header_len );
#else
	virtual void				inputMonitorPacket( mbuf_t m );
#endif
	
	/*! @function outputRaw80211Packet
		@abstract ???.
		@param m ???.
		*/ 
	virtual int					outputRaw80211Packet( IO80211Interface * interface, mbuf_t m )	{ return ENXIO; }

	/*! @function monitorPacketHeaderLength
		@abstract ???.
		@result Returns ???. 
		*/ 
	virtual UInt32				monitorPacketHeaderLength( IO80211Interface * interface )	{ return 0; }

	/*! @function inputMonitorPacket
		@abstract ???.
		@result Returns ???. 
		*/ 
	virtual UInt32				monitorDLT( IO80211Interface * interface ) { return DLT_NULL; }
	
	
	/*! @function monitorModeSetEnabled
		@abstract ???.
		@result Returns ???. 
		*/ 
	
#if defined( _MODERN_BPF )
	virtual SInt32				monitorModeSetEnabled( IO80211Interface * interface, bool enabled, UInt32 dlt ) {return ENXIO; }
#else
	virtual	SInt32				monitorModeSetEnabled( IO80211Interface * interface, bool enabled )	{ return ENXIO; }
#endif
	
	
	/*! @function getNetworkInterface
		@abstract ???.
		@result Returns ???. 
		*/ 

	virtual IO80211Interface	*getNetworkInterface();
	
	/*! @function apple80211_ioctl
		@abstract ???.
		@param interface ???.
		@param ifn ???.
		@param cmd ???.
		@param data ???.
		@result Returns ???. 
		*/ 
	virtual	SInt32				apple80211_ioctl(IO80211Interface	*interface,
												 ifnet_t			ifn,
												 u_int32_t			cmd,
												 void				*data);
	
	/* ioctl handlers */
	
	// SIOCGA80211
	
	SInt32 getASSOCIATE_RESULT( IO80211Interface * interface, 
								struct apple80211_assoc_result_data * ard );
	
	// Required
	virtual SInt32				getSSID(IO80211Interface			*interface,
										struct apple80211_ssid_data *sd) = 0;

	virtual SInt32				getCHANNEL(IO80211Interface			*interface,
										   struct apple80211_channel_data *cd) = 0;

	virtual SInt32				getBSSID(IO80211Interface			*interface,
										 struct apple80211_bssid_data *bd) = 0;

	virtual SInt32				getCARD_CAPABILITIES(IO80211Interface	*interface,
													 struct apple80211_capability_data *cd) = 0;

	virtual SInt32				getSTATE(IO80211Interface			*interface,
										 struct apple80211_state_data *sd) = 0;

	virtual SInt32				getRSSI(IO80211Interface			*interface,
										struct apple80211_rssi_data *rd) = 0;

	virtual SInt32				getPOWER(IO80211Interface			*interface,
										 struct apple80211_power_data *pd) = 0;

	virtual SInt32				getSCAN_RESULT(IO80211Interface		*interface,
											   struct apple80211_scan_result **scan_result)	= 0;
	
	virtual SInt32				getASSOCIATION_STATUS( IO80211Interface * interface,
														struct apple80211_assoc_status_data * asd ) = 0;

	virtual SInt32				getRATE(IO80211Interface			*interface,
										struct apple80211_rate_data *rd) = 0;

	virtual SInt32				getSTATUS_DEV(IO80211Interface		*interface,
											  struct apple80211_status_dev_data *dd) = 0;
											  
	virtual SInt32				getRATE_SET(IO80211Interface	*interface,
												  struct apple80211_rate_set_data *rd) = 0;

	virtual SInt32				getPOWERSAVE(IO80211Interface		*interface,
											 struct apple80211_powersave_data *pd)
		{ return EOPNOTSUPP; }

	virtual SInt32				getPROTMODE(IO80211Interface		*interface,
											struct apple80211_protmode_data *pd)
		{ return EOPNOTSUPP; }

	virtual SInt32				getTXPOWER(IO80211Interface			*interface,
										   struct apple80211_txpower_data *td)
		{ return EOPNOTSUPP; }

	virtual SInt32				getPHY_MODE(IO80211Interface		*interface,
											struct apple80211_phymode_data *pd)
		{ return EOPNOTSUPP; }

	virtual SInt32				getOP_MODE(IO80211Interface			*interface,
										   struct apple80211_opmode_data *od)
		{ return EOPNOTSUPP; }

	virtual SInt32				getNOISE(IO80211Interface			*interface,
										 struct apple80211_noise_data *nd)
		{ return EOPNOTSUPP; }

	virtual SInt32				getINT_MIT(IO80211Interface			*interface,
										   struct apple80211_intmit_data *imd)
		{ return EOPNOTSUPP; }

	virtual SInt32				getAUTH_TYPE(IO80211Interface		*interface,
											 struct apple80211_authtype_data *ad)
		{ return EOPNOTSUPP; }

	virtual SInt32				getSUPPORTED_CHANNELS(IO80211Interface	*interface,
													  struct apple80211_sup_channel_data *sd)
		{ return EOPNOTSUPP; }

	virtual SInt32				getLOCALE(IO80211Interface			*interface,
										  struct apple80211_locale_data *ld)
		{ return EOPNOTSUPP; }

	virtual SInt32				getAP_MODE(IO80211Interface			*interface,
										   struct apple80211_apmode_data *ad)
		{ return EOPNOTSUPP; }

	virtual SInt32				getFRAG_THRESHOLD(IO80211Interface	*interface,
												  struct apple80211_frag_threshold_data *td)
		{ return EOPNOTSUPP; }
		
	virtual SInt32				getSHORT_SLOT(IO80211Interface *interface, 
												  struct apple80211_short_slot_data * sd)
		{ return EOPNOTSUPP; }
		
	virtual SInt32				getMULTICAST_RATE( IO80211Interface * interface,
												  struct apple80211_rate_data * rd )
		{ return EOPNOTSUPP; }
		
	virtual SInt32				getSHORT_RETRY_LIMIT( IO80211Interface * interface,
													struct apple80211_retry_limit_data * rld )
		{ return EOPNOTSUPP; }
		
	virtual SInt32				getLONG_RETRY_LIMIT( IO80211Interface * interface,
													struct apple80211_retry_limit_data * rld )
		{ return EOPNOTSUPP; }
		
	virtual SInt32				getTX_ANTENNA( IO80211Interface * interface,
											   struct apple80211_antenna_data * ad )
		{ return EOPNOTSUPP; }
		
	virtual SInt32				getRX_ANTENNA( IO80211Interface * interface,
											   struct apple80211_antenna_data * ad )
		{ return EOPNOTSUPP; }
		
	virtual SInt32				getANTENNA_DIVERSITY( IO80211Interface * interface,
													  struct apple80211_antenna_data * ad )
		{ return EOPNOTSUPP; }
		
	virtual SInt32				getDTIM_INT( IO80211Interface * interface,
											  struct apple80211_dtim_int_data * dd )
		{ return EOPNOTSUPP; }
	
	virtual SInt32				getSTATION_LIST( IO80211Interface * interface,
												 struct apple80211_sta_data * sd )
		{ return EOPNOTSUPP; }
		
	virtual SInt32				getDRIVER_VERSION( IO80211Interface * interface,
												   struct apple80211_version_data * vd )
		{ return EOPNOTSUPP; }
		
	virtual SInt32				getHARDWARE_VERSION( IO80211Interface * interface,
												    struct apple80211_version_data * vd )
		{ return EOPNOTSUPP; }
		
	virtual SInt32				getROM( IO80211Interface * interface,
										struct apple80211_rom_data * rd )
		{ return EOPNOTSUPP; }
		
	virtual SInt32				getRAND( IO80211Interface * interface,
										 struct apple80211_rand_data * rd )
		{ return EOPNOTSUPP; }
		
	virtual SInt32				getBACKGROUND_SCAN( IO80211Interface * interface,
													struct apple80211_scan_data * sd )
		{ return EOPNOTSUPP; }
	
	virtual SInt32				getRSN_IE( IO80211Interface * interface,
											struct apple80211_rsn_ie_data * rid )
		{ return EOPNOTSUPP; }
	
	virtual SInt32				getAP_IE_LIST( IO80211Interface * interface,
												struct apple80211_ap_ie_data * ied )
		{ return EOPNOTSUPP; }
		
	virtual SInt32				getSTATS( IO80211Interface * interface,
										   struct apple80211_stats_data * sd )
		{ return EOPNOTSUPP; }
	
	virtual SInt32				getDEAUTH( IO80211Interface * interface,
										   struct apple80211_deauth_data *dd )
		{ return EOPNOTSUPP; }
		
	virtual SInt32				getCOUNTRY_CODE( IO80211Interface * interface,
												 struct apple80211_country_code_data * ccd )
		{ return EOPNOTSUPP; }
		
	virtual SInt32				getLAST_RX_PKT_DATA( IO80211Interface * interface,
													 struct apple80211_last_rx_pkt_data * pd )
		{ return EOPNOTSUPP; }
		
	virtual SInt32				getRADIO_INFO( IO80211Interface * interface,
											   struct apple80211_radio_info_data * rid )
		{ rid->count = 1; return 0; }
		
	virtual SInt32				getGUARD_INTERVAL( IO80211Interface * interface,
												   struct apple80211_guard_interval_data * gid )
		{ return EOPNOTSUPP; }
		
	virtual SInt32				getMIMO_POWERSAVE( IO80211Interface * interface,
												   struct apple80211_powersave_data * pd )
		{ return EOPNOTSUPP; }
		
	virtual SInt32				getMCS(	IO80211Interface * interface,
										struct apple80211_mcs_data * md )
		{ return EOPNOTSUPP; }
		
	virtual SInt32				getRIFS( IO80211Interface * interface,
										 struct apple80211_rifs_data * rd )
		{ return EOPNOTSUPP; }
		
	virtual SInt32				getLDPC( IO80211Interface * interface,
										 struct apple80211_ldpc_data * ld )
		{ return EOPNOTSUPP; }
		
	virtual SInt32				getMSDU( IO80211Interface * interface,
										 struct apple80211_msdu_data * md )
		{ return EOPNOTSUPP; }
	
	virtual SInt32				getMPDU( IO80211Interface * interface,
										 struct apple80211_mpdu_data * md )
		{ return EOPNOTSUPP; }
	
	virtual SInt32				getBLOCK_ACK( IO80211Interface * interface,
											  struct apple80211_block_ack_data * bad )
		{ return EOPNOTSUPP; }
	
	virtual SInt32				getPLS( IO80211Interface * interface,
										struct apple80211_pls_data * pd )
		{ return EOPNOTSUPP; }
		
	virtual SInt32				getPSMP( IO80211Interface * interface,
										 struct apple80211_psmp_data * pd )
		{ return EOPNOTSUPP; }
	
	virtual SInt32				getPHY_SUB_MODE( IO80211Interface * interface,
												 struct apple80211_physubmode_data * pd )
		{ return EOPNOTSUPP; }
		
	virtual SInt32				getMCS_INDEX_SET( IO80211Interface * interface,
												  struct apple80211_mcs_index_set_data * misd )
		{ return EOPNOTSUPP; }
	
	
	// SIOCSA80211
	
	// Required 
	virtual SInt32				setSCAN_REQ(IO80211Interface		*interface,
											struct apple80211_scan_data *sd) = 0;

	virtual SInt32				setASSOCIATE(IO80211Interface		*interface,
											 struct apple80211_assoc_data *ad) = 0;

	virtual SInt32				setPOWER(IO80211Interface			*interface,
										 struct apple80211_power_data *pd) = 0;

	virtual SInt32				setCIPHER_KEY(IO80211Interface		*interface,
											  struct apple80211_key *key) = 0;

	virtual SInt32				setAUTH_TYPE(IO80211Interface		*interface,
											 struct apple80211_authtype_data *ad) = 0;

	virtual SInt32				setDISASSOCIATE(IO80211Interface	*interface) = 0;

	virtual SInt32				setSSID(IO80211Interface			*interface,
										struct apple80211_ssid_data *sd) = 0;

	virtual SInt32				setAP_MODE(IO80211Interface			*interface,
										   struct apple80211_apmode_data *ad) = 0;
	
	virtual SInt32				setCHANNEL(IO80211Interface			*interface,
										   struct apple80211_channel_data *cd)
		{ return EOPNOTSUPP; }

	virtual SInt32				setPOWERSAVE(IO80211Interface		*interface,
											 struct apple80211_powersave_data *pd)
		{ return EOPNOTSUPP; }

	virtual SInt32				setPROTMODE(IO80211Interface		*interface,
											struct apple80211_protmode_data *pd)
		{ return EOPNOTSUPP; }

	virtual SInt32				setTXPOWER(IO80211Interface			*interface,
										   struct apple80211_txpower_data *td)
		{ return EOPNOTSUPP; }

	virtual SInt32				setIBSS_MODE(IO80211Interface		*interface,
											 struct apple80211_network_data *nd)
		{ return EOPNOTSUPP; }

	virtual SInt32				setHOST_AP_MODE(IO80211Interface	*interface,
												struct apple80211_network_data *nd)
		{ return EOPNOTSUPP; }

	virtual SInt32				setLOCALE(IO80211Interface			*interface,
										  struct apple80211_locale_data *ld)
		{ return EOPNOTSUPP; }

	virtual SInt32				setINT_MIT(IO80211Interface			*interface,
										   struct apple80211_intmit_data *imd)
		{ return EOPNOTSUPP; }

	virtual SInt32				setBSSID(IO80211Interface			*interface,
										 struct apple80211_bssid_data *bd)
		{ return EOPNOTSUPP; }

	virtual SInt32				setDEAUTH(IO80211Interface			*interface,
										  struct apple80211_deauth_data *dd)
		{ return EOPNOTSUPP; }

	virtual SInt32				setCOUNTERMEASURES(IO80211Interface	*interface,
												   struct apple80211_countermeasures_data *cd)
		{ return EOPNOTSUPP; }

	virtual SInt32				setFRAG_THRESHOLD(IO80211Interface	*interface,
												  struct apple80211_frag_threshold_data *td)
		{ return EOPNOTSUPP; }
		
	virtual SInt32				setRATE_SET(IO80211Interface	*interface,
												  struct apple80211_rate_set_data *rd)
		{ return EOPNOTSUPP; }
		
	virtual SInt32				setSHORT_SLOT(IO80211Interface *interface, 
												  struct apple80211_short_slot_data * sd)
		{ return EOPNOTSUPP; }
		
	virtual SInt32				setRATE( IO80211Interface * interface,
												  struct apple80211_rate_data * rd )
		{ return EOPNOTSUPP; }
		
	virtual SInt32				setMULTICAST_RATE( IO80211Interface * interface,
												  struct apple80211_rate_data * rd )
		{ return EOPNOTSUPP; }
		
	virtual SInt32				setSHORT_RETRY_LIMIT( IO80211Interface * interface,
													struct apple80211_retry_limit_data * rld )
		{ return EOPNOTSUPP; }
		
	virtual SInt32				setLONG_RETRY_LIMIT( IO80211Interface * interface,
													struct apple80211_retry_limit_data * rld )
		{ return EOPNOTSUPP; }
		
	virtual SInt32				setTX_ANTENNA( IO80211Interface * interface,
											   struct apple80211_antenna_data * ad )
		{ return EOPNOTSUPP; }
		
	virtual SInt32				setANTENNA_DIVERSITY( IO80211Interface * interface,
													  struct apple80211_antenna_data * ad )
		{ return EOPNOTSUPP; }
		
	virtual SInt32				setDTIM_INT( IO80211Interface * interface,
											  struct apple80211_dtim_int_data * dd )
		{ return EOPNOTSUPP; }
		
	virtual SInt32				setRSN_IE( IO80211Interface * interface,
											struct apple80211_rsn_ie_data * rid )
		{ return EOPNOTSUPP; }
		
	virtual SInt32				setBACKGROUND_SCAN( IO80211Interface * interface,
													struct apple80211_scan_data * sd )
		{ return EOPNOTSUPP; }
		
	virtual SInt32				setPHY_MODE(IO80211Interface		*interface,
											struct apple80211_phymode_data *pd)
		{ return EOPNOTSUPP; }
		
	virtual SInt32				setGUARD_INTERVAL( IO80211Interface * interface,
												   struct apple80211_guard_interval_data * gid )
		{ return EOPNOTSUPP; }
		
	virtual SInt32				setMCS(	IO80211Interface * interface,
										struct apple80211_mcs_data * md )
		{ return EOPNOTSUPP; }
		
	virtual SInt32				setRIFS( IO80211Interface * interface,
										 struct apple80211_rifs_data * rd )
		{ return EOPNOTSUPP; }
	
	virtual SInt32				setLDPC( IO80211Interface * interface,
										 struct apple80211_ldpc_data * ld )
		{ return EOPNOTSUPP; }
		
	virtual SInt32				setMSDU( IO80211Interface * interface,
										 struct apple80211_msdu_data * md )
		{ return EOPNOTSUPP; }
		
	virtual SInt32				setMPDU( IO80211Interface * interface,
										 struct apple80211_mpdu_data * md )
		{ return EOPNOTSUPP; }
		
	virtual SInt32				setBLOCK_ACK( IO80211Interface * interface,
											  struct apple80211_block_ack_data * bad )
		{ return EOPNOTSUPP; }
		
	virtual SInt32				setPLS( IO80211Interface * interface,
										struct apple80211_pls_data * pd )
		{ return EOPNOTSUPP; }
		
	virtual SInt32				setPSMP( IO80211Interface * interface,
										 struct apple80211_psmp_data * pd )
		{ return EOPNOTSUPP; }
	
	virtual SInt32				setPHY_SUB_MODE( IO80211Interface * interface,
												 struct apple80211_physubmode_data * pd )
		{ return EOPNOTSUPP; }
	
	virtual SInt32				setMCS_INDEX_SET( IO80211Interface * interface,
												  struct apple80211_mcs_index_set_data * misd )
		{ return EOPNOTSUPP; }
	
	// Power management methods
	static	IOReturn	stopDMAGated( OSObject *owner, void *arg0, void *arg1, void *arg2, void *arg3 );
	
	virtual SInt32	stopDMA() { return EOPNOTSUPP; }
	
	// Output queue introspection
	virtual UInt32	hardwareOutputQueueDepth( IO80211Interface * interface )	{ return 0; }
	
	// For control of country code settings
	virtual SInt32	performCountryCodeOperation( IO80211Interface * interface, IO80211CountryCodeOp op )	{ return EOPNOTSUPP; }
	
	virtual bool	useAppleRSNSupplicant( IO80211Interface * interface ) { return true; }
	
	virtual void	dataLinkLayerAttachComplete( IO80211Interface * interface );
	
	UInt32 radioCountForInterface( IO80211Interface * interface );

protected:
	
		/*! @function powerDownHandler
		@abstract ???.
		@discussion ???.
		*/
	static IOReturn		powerDownHandler( void *target, void *refCon, UInt32 messageType,
										  IOService *service, void *messageArgument, vm_size_t argSize );
	
		// optional methods provided by subclass
	virtual bool				promiscuousEnabled();
	
		// mostly internal use, but may need to override
	
	virtual IONetworkInterface *createInterface();

	virtual void				inputPacket( mbuf_t m );

	virtual SInt32				apple80211_ioctl_get(IO80211Interface	*interface,
													 ifnet_t			ifn,
													 void				*data);

	virtual SInt32				apple80211_ioctl_set(IO80211Interface	*interface,
													 ifnet_t			ifn,
													 void				*data);
													 
	virtual bool attachInterface(IONetworkInterface ** interface,
                                 bool                  doRegister = true);
	
	// Force a second interface to attach to the same controller
	virtual bool attachInterfaceWithMacAddress( void * macAddr, 
												UInt32 macLen, 
												IONetworkInterface ** interface, 
												bool doRegister = true,
												UInt32 timeout = 5000 /*ms*/ );

private:

	bool forceInterfaceRegistration( IO80211Interface * interface );
	
	IO80211WorkLoop				*_myWorkLoop;
	IONetworkInterface			*_netIF;

	// Intel power management handler
	IONotifier	*	_powerDownNotifier;
	
	IOService	*	_provider;
	
	bool _ifAttachPending;
	

		// Virtual function padding
	OSMetaClassDeclareReservedUnused( IO80211Controller,  0);
	OSMetaClassDeclareReservedUnused( IO80211Controller,  1);
    OSMetaClassDeclareReservedUnused( IO80211Controller,  2);
    OSMetaClassDeclareReservedUnused( IO80211Controller,  3);
    OSMetaClassDeclareReservedUnused( IO80211Controller,  4);
    OSMetaClassDeclareReservedUnused( IO80211Controller,  5);
    OSMetaClassDeclareReservedUnused( IO80211Controller,  6);
    OSMetaClassDeclareReservedUnused( IO80211Controller,  7);
    OSMetaClassDeclareReservedUnused( IO80211Controller,  8);
    OSMetaClassDeclareReservedUnused( IO80211Controller,  9);
    OSMetaClassDeclareReservedUnused( IO80211Controller, 10);
    OSMetaClassDeclareReservedUnused( IO80211Controller, 11);
    OSMetaClassDeclareReservedUnused( IO80211Controller, 12);
    OSMetaClassDeclareReservedUnused( IO80211Controller, 13);
    OSMetaClassDeclareReservedUnused( IO80211Controller, 14);
    OSMetaClassDeclareReservedUnused( IO80211Controller, 15);
};
	
#endif /* defined(KERNEL) && defined(__cplusplus) */
	
#endif /* !_IO80211CONTROLLER_H */
	