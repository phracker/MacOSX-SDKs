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

enum IO80211FeatureCode
{
	kIO80211Feature80211n = 1,
};
typedef enum IO80211FeatureCode IO80211FeatureCode;

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
		struct apple80211_assoc_data	_lastAssocData;
		bool							_interferenceRobustness;
		IO80211Scanner					*_scanner;
		WepNetwork						_lastLegacyAssocInfo;

	public:
		IOReturn newUserClient( task_t owningTask, void * securityID, UInt32 type, 
						OSDictionary * properties, IOUserClient ** handler );
		IOReturn queueCommand( UInt8 commandCode, void *arguments, void *returnValue );
		static IOReturn execCommand( OSObject * obj, void *field0, void *field1, void *field2, void *field3 );
		
		SInt32 getLastAssocData( struct apple80211_assoc_data * ad);
		SInt32 setLastAssocData( struct apple80211_assoc_data * ad);

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
	
	/*! @function inputMonitorPacket
		@abstract ???.
		@param m ???.
		*/ 

	virtual void				inputMonitorPacket( mbuf_t m, UInt32 dlt, void * header, size_t header_len );
	
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
	
	virtual SInt32				monitorModeSetEnabled( IO80211Interface * interface, bool enabled, UInt32 dlt ) {return ENXIO; }
	
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
	
	#define IOCTL_GET( type, intf, data ) apple80211Request( SIOCGA80211, APPLE80211_IOC_##type, intf, (void *)data )
	#define IOCTL_SET( type, intf, data ) apple80211Request( SIOCSA80211, APPLE80211_IOC_##type, intf, (void *)data )
	virtual SInt32 apple80211Request( UInt32 req, int type, IO80211Interface * intf, void * data ) = 0;
	
	// SIOCGA80211
	
	SInt32 getASSOCIATE_RESULT( IO80211Interface * interface, 
								struct apple80211_assoc_result_data * ard );
	
	// Power management methods
	static	IOReturn	powerChangeGated( OSObject *owner, void *arg0, void *arg1, void *arg2, void *arg3 );
	
	virtual SInt32	stopDMA() { return EOPNOTSUPP; }
	void setSleeping( bool sleeping ) { _sleeping = sleeping; }
	
	// Output queue introspection
	virtual UInt32	hardwareOutputQueueDepth( IO80211Interface * interface )	{ return 0; }
	
	// For control of country code settings
	virtual SInt32	performCountryCodeOperation( IO80211Interface * interface, IO80211CountryCodeOp op )	{ return EOPNOTSUPP; }
	
	virtual bool	useAppleRSNSupplicant( IO80211Interface * interface ) { return true; }
	
	virtual void	dataLinkLayerAttachComplete( IO80211Interface * interface );
	
	UInt32 radioCountForInterface( IO80211Interface * interface );

	virtual SInt32 enableFeature( IO80211FeatureCode feature, void * refcon ) { return EOPNOTSUPP; }

protected:
	
		/*! @function powerDownHandler
		@abstract ???.
		@discussion ???.
		*/
	static IOReturn		powerChangeHandler( void *target, void *refCon, UInt32 messageType,
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
	
	bool _sleeping;

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
	