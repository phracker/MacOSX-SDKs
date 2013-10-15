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

#ifndef _IO80211INTERFACE_H
#define _IO80211INTERFACE_H

/*
 * Kernel
 */
#if defined(KERNEL) && defined(__cplusplus)

#include <libkern/version.h>

#if VERSION_MAJOR > 8
	#define _MODERN_BPF
#endif

#include <IOKit/network/IOEthernetInterface.h>
#include <net/if_var.h>
#include <sys/queue.h>

enum IO80211LinkState
{
	kIO80211NetworkLinkUndefined,			// Starting link state when an interface is created
	kIO80211NetworkLinkDown,				// Interface not capable of transmitting packets
	kIO80211NetworkLinkUp,					// Interface capable of transmitting packets
};
typedef enum IO80211LinkState IO80211LinkState;

/*!	@defined kIO80211InterfaceClass
	@abstract The name of the IO80211Interface class. 
	*/
#define kIO80211InterfaceClass     "IO80211Interface"

class RSNSupplicant;
class IOTimerEventSource;
class IOGatedOutputQueue;
class IO80211Controller;
struct rsn_pmksa_node;

/*!	@class IO80211Interface
	@abstract The 80211 interface object. 
	@discussion An 80211 controller driver, that is a subclass of IOEthernetInterface, will instantiate an object of this class when the driver calls the attachInterface() method. This interface object will then vend an Ethernet interface to DLIL, and manage the connection between the controller driver and the upper networking layers. Drivers will seldom need to subclass IO80211Interface. 
	*/
class IO80211Interface : public IOEthernetInterface
{
	OSDeclareDefaultStructors( IO80211Interface );
	
public:
	
	/*!	@function init
		@abstract Initializes an IO80211Interface instance.
		@discussion Instance variables are initialized, and ???.
		@param controller A network controller object that will service the interface object being initialized.
		@result Returns true on success, false otherwise. 
		*/
	virtual bool		init(IONetworkController *controller );
	
	/*! @function attachToDataLinkLayer
		@abstract ???.
		@discussion ???. 
		*/
	virtual IOReturn	attachToDataLinkLayer(IOOptionBits	options,
											  void			*parameter);
											
	/*! @function detachFromDataLinkLayer
		@abstract ???.
		@discussion ???. 
		*/
	virtual void		detachFromDataLinkLayer(IOOptionBits options,
												void		*parameter);
												
	/*! @function inputEvent
		@abstract Sends an event to the data link layer.
		@discussion This method can be used by the network controller to
		send an event to the data link layer.
		@param type A constant describing the event type.
		@param data Data associated with the event.
		@result Returns true if the event was delivered, false if the event type
		specified is invalid, or if the event delivery was unsuccesful. 
		*/
	virtual bool inputEvent(UInt32 type, void * data);
										  
	/*! @function setPoweredOnByUser
		@abstract ???.
		@discussion ???. 
		*/
	virtual void		setPoweredOnByUser(bool poweredOn);

	/*! @function poweredOnByUser
		@abstract ???.
		@discussion ???. 
		*/
	bool		poweredOnByUser();
	
	/*! @function setEnabledBySystem
		@abstract ???.
		@discussion ???. 
		*/
	virtual void		setEnabledBySystem(bool systemEnabled);

	/*! @function enabledBySystem
		@abstract ???.
		@discussion ???. 
		*/
	bool		enabledBySystem();

	/*! @function createStatusDevice
		@abstract ???.
		@discussion ???. 
		*/
	IOReturn			createStatusDevice(char *name );

	/*! @function postMessage
		@abstract <abstract>.
		@discussion ???. 
		*/
	void				postMessage(int msg);
	
	/*! @function setScanTimeout
		@abstract <abstract>.
		@discussion ???. 
		*/
	void				setScanTimeout( unsigned int timeout );
	
	/*! @function scanTimeout
		@abstract <abstract>.
		@discussion ???. 
		*/
	unsigned int		scanTimeout();
	
	/*! @function setAuthTimeout
		@abstract <abstract>.
		@discussion ???. 
		*/
	void				setAuthTimeout( unsigned int timeout );
	
	/*! @function authTimeout
		@abstract <abstract>.
		@discussion ???. 
		*/
	unsigned int		authTimeout();
	
	/*! @function setScanPid
		@abstract <abstract>.
		@discussion ???. 
		*/
	void				setScanPid( pid_t pid );
	
	/*! @function scanPid
		@abstract <abstract>.
		@discussion ???. 
		*/
	pid_t				scanPid();
	
	/*! @function setLinkState
		@abstract <abstract>.
		@discussion ???. 
		*/
	virtual bool		setLinkState( IO80211LinkState linkState );
	
	/*! @function linkState
		@abstract <abstract>.
		@discussion ???. 
		*/
	IO80211LinkState	linkState();
	
	/*! @function supplicantListening
		@abstract <abstract>.
		@discussion ???. 
		*/
	bool initSupplicant( UInt8 * ie );
	
	/*! @function terminateSupplicant
		@abstract <abstract>.
		@discussion ???. 
		*/
	void terminateSupplicant();
	
	/*! @function resetSupplicant
		@abstract <abstract>.
		@discussion ???. 
		*/
	void resetSupplicant();
	
	/*! @function setPMK
		@abstract <abstract>.
		@discussion ???. 
		*/
	bool setPMK( UInt8 * pmk );
	
	/*! @function supplicantExchangeComplete
		@abstract <abstract>.
		@discussion ???. 
		*/
	bool supplicantExchangeComplete();
	
	/*! @function supplicantInitialized
		@abstract <abstract>.
		@discussion ???. 
		*/
	bool supplicantInitialized();
	
	/*! @function outputEAPOLFrame
		@abstract <abstract>.
		@discussion ???. 
		*/
	UInt32 outputEAPOLFrame( mbuf_t m );
	
	/*! @function inputEAPOLFrame
		@abstract <abstract>.
		@discussion ???. 
		*/
	void inputEAPOLFrame( mbuf_t m );
	
	/*! @function cachePMKSA
		@abstract <abstract>.
		@discussion ???. 
		*/
	void cachePMKSA( UInt8 * pmk, size_t pmkLen, struct ether_addr * aa, UInt8 * pmkID );
	
	/*! @function pmksaLookup
		@abstract <abstract>.
		@discussion ???. 
		*/
	struct rsn_pmksa_node * pmksaLookup( struct ether_addr * authenticatorEA, UInt8 * pmkID );
	
	/*! @function shouldRoam
		@abstract <abstract>.
		@discussion ???. 
		*/
	bool shouldRoam( struct apple80211_scan_result * asr );
	
	/*! @function willRoam
		@abstract <abstract>.
		@discussion ???. 
		*/
	void willRoam( struct ether_addr * bssid );
	
	/*! @function inputPacket
		@abstract <abstract>.
		@discussion ???. 
		*/
	virtual UInt32 inputPacket(mbuf_t m,
                               UInt32        length  = 0,
                               IOOptionBits  options = 0,
                               void *        param   = 0);
	
	/*! @function outputPacket
		@abstract <abstract>.
		@discussion ???. 
		*/						   
	virtual UInt32	outputPacket( mbuf_t m, void * param );
	
	/*! @function getBSDName
		@abstract <abstract>.
		@discussion ???. 
		*/
	const char * getBSDName();
	
	/*! @function getStatusDevName
		@abstract <abstract>.
		@discussion ???. 
		*/
	char * getStatusDevName();
	
	/*! @function setCountermeasuresTimer
		@abstract <abstract>.
		@discussion ???. 
		*/
	void setCountermeasuresTimer( IOTimerEventSource * timer );
	
	/*! @function stopCountermeasures
		@abstract <abstract>.
		@discussion ???. 
		*/
	static void stopCountermeasures( OSObject *owner, IOTimerEventSource *sender );
	
	/*! @function updateChannelProperty
		@abstract <abstract>.
		@discussion ???. 
		*/
	void updateChannelProperty();
	
	/*! @function updateSSIDProperty
		@abstract <abstract>.
		@discussion ???. 
		*/
	void updateSSIDProperty();
	
	/*! @function updateStaticProperties
		@abstract <abstract>.
		@discussion ???. 
		*/
	void updateStaticProperties();
	
	/*! @function updateCountryCodeProperty
		@abstract <abstract>.
		@discussion ???. 
		*/
	void updateCountryCodeProperty( bool shouldLog );
	
	/*! @function performCountryCodeOpGated
		@abstract ???.
		@discussion ???. 
		*/
	static IOReturn	performCountryCodeOpGated( OSObject *owner, void * inInterface, void * inParams, void *arg2, void *arg3 );
	
	/*! @function configureAntennae
		@abstract ???.
		@discussion ???. 
		*/
	void configureAntennae();
	
	/*! @function setDebugFlags
		@abstract ???.
		@discussion ???. 
		*/
	void setDebugFlags( UInt32 debugFlags );
	
	/*! @function debugFlags
		@abstract ???.
		@discussion ???. 
		*/
	UInt32 debugFlags();
	
	/*! @function getOutputQueue
		@abstract <abstract>.
		@discussion ???. 
		*/
	IOGatedOutputQueue * getOutputQueue();
	
#if defined( _MODERN_BPF )
	
	/*! @function bpfAttach
		@abstract <abstract>.
		@discussion ???. 
		*/
	errno_t		bpfAttach( UInt32 dlt, UInt32 headerLen );
	
	/*! @function bpfTap
		@abstract <abstract>.
		@discussion ???. 
		*/
	errno_t		monitorModeInputPacket( mbuf_t m, UInt32 dlt, void * header, size_t header_len );
	
#else
	
	/*! @function monitorModeInputPacket
		@abstract ???.
		@discussion ???. 
		*/
	void		monitorModeInputPacket(mbuf_t m);
	
#endif

	/*! @function get80211OutputQueue
		@abstract <abstract>.
		@discussion ???. 
		*/
	IOGatedOutputQueue * get80211OutputQueue();

	/*! @function output80211Packet
		@abstract <abstract>.
		@discussion ???. 
		*/
	virtual UInt32 output80211Packet( mbuf_t m, void * param );
	
protected:
	
	/*!	@function performCommand
		@abstract Handles an ioctl command sent to the Ethernet interface.
		@discussion This method handles socket ioctl commands sent to the Ethernet interface from DLIL. Commands recognized and processed by this method are SIOCSIFADDR, SIOCSIFFLAGS, SIOCADDMULTI, and SIOCDELMULTI. Other commands are passed to the superclass.
		@param controller The controller object.
		@param cmd The ioctl command code.
		@param arg0 Command argument 0. Generally a pointer to an ifnet structure associated with the interface.
		@param arg1 Command argument 1.
		@result Returns a BSD return value defined in bsd/sys/errno.h. 
		*/
	virtual SInt32		performCommand(IONetworkController	*controller,
									   UInt32				cmd,
									   void					*arg0,
									   void					*arg1);
									   
	/*! @function performGatedCommand
		@abstract <abstract>.
		@discussion ???. 
		*/
	static int performGatedCommand( void *, void *, void *, void *, void * );
									   
	/*! @function free
		@abstract Frees the IO80211Interface instance.
		@discussion ???, followed by a call to super::free().
		*/
	virtual void		free();
	
	/*! @function powerChangeHandler
		@abstract <abstract>.
		@discussion ???. 
		*/
	static IOReturn powerChangeHandler( void *target, void *refCon, UInt32 messageType,
										  IOService *service, void *messageArgument, vm_size_t argSize );
	
private:
	
	/*! @function inputAWSPacket
		@abstract <abstract>.
		@discussion ???. 
		*/
	void inputAWSPacket( mbuf_t m );
	
	/*! @function awsRespond
		@abstract <abstract>.
		@discussion ???. 
		*/
	void awsRespond( mbuf_t m, struct AWSRequest * requestList, size_t numRequests, UInt16 packetID );
	
	/*! @function purgePMKSACache
		@abstract <abstract>.
		@discussion ???. 
		*/
	void purgePMKSACache();
	
	/*! @function freePMKSACache
		@abstract <abstract>.
		@discussion ???. 
		*/
	void freePMKSACache();
		
	ifnet_t		wlt_if;
	int			_minor;
	u_int32_t	_devUnit;
	char *		_statusDevName;
	size_t		_statusDevNameLen;
	
	bool		_poweredOnByUser;
	bool		_enabledBySystem;	// IFF_UP flag set?
	
	// Scan data
	unsigned int	_scanTimeout;
	pid_t			_scanPid;
	
	unsigned int	_authTimeout;
	
	IO80211LinkState _linkState;
	bool			 _pendingLinkEvent;
	
	RSNSupplicant * _rsnSupplicant;
	
	ifmultiaddr_t	_awsAddr;
	
	IOTimerEventSource * _countermeasuresTimer;
	
	char _bsdName[IFNAMSIZ];
	
	//struct rsn_pmksa_node * _pmksaCacheHead;
	LIST_HEAD( , rsn_pmksa_node ) _pmksaCacheHead;
	
	IONotifier * _powerChangeNotifier;
	IOLock *	_powerChangeWakeUpLock;
	
	UInt32	_debugFlags;
	
	IOGatedOutputQueue * _outputQueue;
	
	IOGatedOutputQueue * _80211outputQueue;
	
	IO80211Controller * _controller;
	
	void * _llAddr;
	UInt8 _ifiType;
	
	bool _wmeSupported;
	bool _shortGISupported;
	
public:

	// Virtual function padding
	
	OSMetaClassDeclareReservedUnused( IO80211Interface,  0);
	OSMetaClassDeclareReservedUnused( IO80211Interface,  1);
	OSMetaClassDeclareReservedUnused( IO80211Interface,  2);
	OSMetaClassDeclareReservedUnused( IO80211Interface,  3);
	OSMetaClassDeclareReservedUnused( IO80211Interface,  4);
	OSMetaClassDeclareReservedUnused( IO80211Interface,  5);
	OSMetaClassDeclareReservedUnused( IO80211Interface,  6);
	OSMetaClassDeclareReservedUnused( IO80211Interface,  7);
	OSMetaClassDeclareReservedUnused( IO80211Interface,  8);
	OSMetaClassDeclareReservedUnused( IO80211Interface,  9);
	OSMetaClassDeclareReservedUnused( IO80211Interface, 10);
	OSMetaClassDeclareReservedUnused( IO80211Interface, 11);
	OSMetaClassDeclareReservedUnused( IO80211Interface, 12);
	OSMetaClassDeclareReservedUnused( IO80211Interface, 13);
	OSMetaClassDeclareReservedUnused( IO80211Interface, 14);
	OSMetaClassDeclareReservedUnused( IO80211Interface, 15);
};

#endif /* defined(KERNEL) && defined(__cplusplus) */

#endif /* ! _IO80211INTERFACE_H */

