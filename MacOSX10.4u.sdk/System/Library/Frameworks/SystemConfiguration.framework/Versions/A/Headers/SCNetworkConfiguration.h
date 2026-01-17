/*
 * Copyright (c) 2004, 2005 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */

#ifndef _SCNETWORKCONFIGURATION_H
#define _SCNETWORKCONFIGURATION_H

#include <AvailabilityMacros.h>
#include <sys/cdefs.h>
#include <CoreFoundation/CoreFoundation.h>
#include <SystemConfiguration/SystemConfiguration.h>

#if MAC_OS_X_VERSION_MAX_ALLOWED >= 1040

/*!
	@header SCNetworkConfiguration
	@discussion The SCNetworkConfiguration API provides access to the
		stored network configuration.  The functions include
		providing access to the network capable devices on the
		system, the network sets, network services, and network
		protocols.

		Note: When using the SCNetworkConfiguraiton APIs you must
		keep in mind that in order for any of your changes to be
		committed to permanent storage a call must be made to the
		SCPreferencesCommitChanges function.
 */

/*!
	@group Interface configuration
 */

/*!
	@typedef SCNetworkInterfaceRef
	@discussion This is the type of a reference to an object that represents
		a network interface.
 */
typedef const struct __SCNetworkInterface * SCNetworkInterfaceRef;

/*!
	@const kSCNetworkInterfaceType6to4
 */
extern const CFStringRef kSCNetworkInterfaceType6to4						AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@const kSCNetworkInterfaceTypeBluetooth
 */
extern const CFStringRef kSCNetworkInterfaceTypeBluetooth					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@const kSCNetworkInterfaceTypeBond
 */
extern const CFStringRef kSCNetworkInterfaceTypeBond						AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@const kSCNetworkInterfaceTypeEthernet
 */
extern const CFStringRef kSCNetworkInterfaceTypeEthernet					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@const kSCNetworkInterfaceTypeFireWire
 */
extern const CFStringRef kSCNetworkInterfaceTypeFireWire					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@const kSCNetworkInterfaceTypeIEEE80211
 */
extern const CFStringRef kSCNetworkInterfaceTypeIEEE80211					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// IEEE 802.11, AirPort

/*!
	@const kSCNetworkInterfaceTypeIrDA
 */
extern const CFStringRef kSCNetworkInterfaceTypeIrDA						AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@const kSCNetworkInterfaceTypeL2TP
 */
extern const CFStringRef kSCNetworkInterfaceTypeL2TP						AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@const kSCNetworkInterfaceTypeModem
 */
extern const CFStringRef kSCNetworkInterfaceTypeModem						AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@const kSCNetworkInterfaceTypePPP
 */
extern const CFStringRef kSCNetworkInterfaceTypePPP						AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@const kSCNetworkInterfaceTypePPTP
 */
extern const CFStringRef kSCNetworkInterfaceTypePPTP						AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@const kSCNetworkInterfaceTypeSerial
 */
extern const CFStringRef kSCNetworkInterfaceTypeSerial						AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@const kSCNetworkInterfaceTypeVLAN
 */
extern const CFStringRef kSCNetworkInterfaceTypeVLAN						AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* special network interfaces (and types) */

/*!
	@const kSCNetworkInterfaceTypeIPv4
 */
extern const CFStringRef kSCNetworkInterfaceTypeIPv4						AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@const kSCNetworkInterfaceIPv4
	@discussion A network interface that can used for layering other
		interfaces (e.g. 6to4, PPP, PPTP, L2TP) over an existing
		IPv4 network.
 */
extern const SCNetworkInterfaceRef kSCNetworkInterfaceIPv4					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*!
	@group Protocol configuration
 */

/*!
	@typedef SCNetworkProtocolRef
	@discussion This is the type of a reference to an object that represents
		a network protocol.
 */
typedef const struct __SCNetworkProtocol * SCNetworkProtocolRef;

/* network "protocol" types */

/*!
	@const kSCNetworkProtocolTypeAppleTalk
 */
extern const CFStringRef kSCNetworkProtocolTypeAppleTalk					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@const kSCNetworkProtocolTypeDNS
 */
extern const CFStringRef kSCNetworkProtocolTypeDNS						AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@const kSCNetworkProtocolTypeIPv4
 */
extern const CFStringRef kSCNetworkProtocolTypeIPv4						AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@const kSCNetworkProtocolTypeIPv6
 */
extern const CFStringRef kSCNetworkProtocolTypeIPv6						AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@const kSCNetworkProtocolTypeProxies
 */
extern const CFStringRef kSCNetworkProtocolTypeProxies						AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*!
	@group Service configuration
 */

/*!
	@typedef SCNetworkServiceRef
	@discussion This is the type of a reference to an object that represents
		a network service.
 */
typedef const struct __SCNetworkService * SCNetworkServiceRef;


/*!
	@group Set configuration
 */

/*!
	@typedef SCNetworkSetRef
	@discussion This is the type of a reference to an object that represents
		a network set.
 */
typedef const struct __SCNetworkSet	* SCNetworkSetRef;


__BEGIN_DECLS


/* --------------------------------------------------------------------------------
 * INTERFACES
 * -------------------------------------------------------------------------------- */

/*!
	@group Interface configuration
 */

/*!
	@function SCNetworkInterfaceGetTypeID
	@discussion Returns the type identifier of all SCNetworkInterface instances.
 */
CFTypeID
SCNetworkInterfaceGetTypeID			(void)						AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@function SCNetworkInterfaceCopyAll
	@discussion Returns all network capable devices on the system.
	@result The list of SCNetworkInterface devices on the system.
		You must release the returned value.
 */
CFArrayRef /* of SCNetworkInterfaceRef's */
SCNetworkInterfaceCopyAll			(void)						AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@function SCNetworkInterfaceGetSupportedInterfaceTypes
	@discussion Identify all of the network interface types (e.g. PPP) that
		can be layered on top of this interface.
	@param interface The network interface.
	@result The list of SCNetworkInterface types supported by the interface;
		NULL if no interface types are supported.
 */
CFArrayRef /* of kSCNetworkInterfaceTypeXXX CFStringRef's */
SCNetworkInterfaceGetSupportedInterfaceTypes	(SCNetworkInterfaceRef		interface)	AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@function SCNetworkInterfaceGetSupportedProtocolTypes
	@discussion Identify all of the network protocol types (e.g. IPv4, IPv6) that
		can be layered on top of this interface.
	@param interface The network interface.
	@result The list of SCNetworkProtocol types supported by the interface;
		NULL if no protocol types are supported.
 */
CFArrayRef /* of kSCNetworkProtocolTypeXXX CFStringRef's */
SCNetworkInterfaceGetSupportedProtocolTypes	(SCNetworkInterfaceRef		interface)	AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@function SCNetworkInterfaceCreateWithInterface
	@discussion Create a new network interface layered on top of another.  For
		example, this function would be used to create a "PPP" interface
		on top of a "modem".
	@param interface The network interface.
	@param interfaceType The type of SCNetworkInterface to be layered on
		top of the provided interface.
	@result A reference to the new SCNetworkInterface.
		You must release the returned value.
 */
SCNetworkInterfaceRef
SCNetworkInterfaceCreateWithInterface		(SCNetworkInterfaceRef		interface,
						 CFStringRef			interfaceType)	AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@function SCNetworkInterfaceGetBSDName
	@discussion Returns the BSD interface (en0) or device name (modem)
		for the interface.
	@param interface The network interface.
	@result The BSD name associated with the interface (e.g. "en0");
		NULL if no BSD name is available.
 */
CFStringRef
SCNetworkInterfaceGetBSDName			(SCNetworkInterfaceRef		interface)	AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@function SCNetworkInterfaceGetConfiguration
	@discussion Returns the configuration settings associated with a interface.
	@param interface The network interface.
	@result The configuration settings associated with the interface;
		NULL if no changes to the default configuration have been saved.
 */
CFDictionaryRef
SCNetworkInterfaceGetConfiguration		(SCNetworkInterfaceRef		interface)	AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@function SCNetworkInterfaceGetHardwareAddressString
	@discussion Returns a displayable link layer address for the interface.
	@param interface The network interface.
	@result A string representing the hardware (MAC) address for the interface.
 */
CFStringRef
SCNetworkInterfaceGetHardwareAddressString	(SCNetworkInterfaceRef		interface)	AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@function SCNetworkInterfaceGetInterface
	@discussion For layered network interfaces, return the underlying interface.
	@param interface The network interface.
	@result The underlying network interface;
		NULL if this is a leaf interface.
 */
SCNetworkInterfaceRef
SCNetworkInterfaceGetInterface			(SCNetworkInterfaceRef		interface)	AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@function SCNetworkInterfaceGetInterfaceType
	@discussion Returns the associated network interface type.
	@param interface The network interface.
	@result The interface type.
 */
CFStringRef
SCNetworkInterfaceGetInterfaceType		(SCNetworkInterfaceRef		interface)	AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@function SCNetworkInterfaceGetLocalizedDisplayName
	@discussion Returns the localized name (e.g. "Built-in Ethernet") for
		the interface.
	@param interface The network interface.
	@result A localized, display name for the interface;
		NULL if no name is available.
 */
CFStringRef
SCNetworkInterfaceGetLocalizedDisplayName	(SCNetworkInterfaceRef		interface)	AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@function SCNetworkInterfaceSetConfiguration
	@discussion Stores the configuration settings for the interface.
	@param interface The network interface.
	@param config The configuration settings to associate with this interface.
	@result TRUE if the configuration was stored; FALSE if an error was encountered.
 */
Boolean
SCNetworkInterfaceSetConfiguration		(SCNetworkInterfaceRef		interface,
						 CFDictionaryRef		config)		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* --------------------------------------------------------------------------------
 * PROTOCOLS
 * -------------------------------------------------------------------------------- */

/*!
	@group Protocol configuration
 */

/*!
	@function SCNetworkProtocolGetTypeID
	@discussion Returns the type identifier of all SCNetworkProtocol instances.
 */
CFTypeID
SCNetworkProtocolGetTypeID			(void)						AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@function SCNetworkProtocolGetConfiguration
	@discussion Returns the configuration settings associated with the protocol.
	@param protocol The network protocol.
	@result The configuration settings associated with the protocol;
		NULL if no changes to the default configuration have been saved.
 */
CFDictionaryRef
SCNetworkProtocolGetConfiguration		(SCNetworkProtocolRef		protocol)	AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@function SCNetworkProtocolGetEnabled
	@discussion Returns whether this protocol has been enabled.
	@param protocol The network protocol.
	@result TRUE if the protocol is enabled.
 */
Boolean
SCNetworkProtocolGetEnabled			(SCNetworkProtocolRef		protocol)	AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@function SCNetworkProtocolGetProtocolType
	@discussion Returns the associated network protocol type.
	@param protocol The network protocol.
	@result The protocol type.
 */
CFStringRef
SCNetworkProtocolGetProtocolType		(SCNetworkProtocolRef		protocol)	AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@function SCNetworkProtocolSetConfiguration
	@discussion Stores the configuration settings for the protocol.
	@param protocol The network protocol.
	@param config The configuration settings to associate with this protocol.
	@result TRUE if the configuration was stored; FALSE if an error was encountered.
 */
Boolean
SCNetworkProtocolSetConfiguration		(SCNetworkProtocolRef		protocol,
						 CFDictionaryRef		config)		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@function SCNetworkProtocolSetEnabled
	@discussion Enables or disables the protocol.
	@param protocol The network protocol.
	@param enabled TRUE if the protocol should be enabled.
	@result TRUE if the enabled status was saved; FALSE if an error was encountered.
 */
Boolean
SCNetworkProtocolSetEnabled			(SCNetworkProtocolRef		protocol,
						 Boolean			enabled)	AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* --------------------------------------------------------------------------------
 * SERVICES
 * -------------------------------------------------------------------------------- */

/*!
	@group Service configuration
 */

/*!
	@function SCNetworkServiceGetTypeID
	@discussion Returns the type identifier of all SCNetworkService instances.
 */
CFTypeID
SCNetworkServiceGetTypeID			(void);

/*!
	@function SCNetworkServiceAddProtocolType
	@discussion Adds a network protocol of the specified type to the
		service.  The protocal configuration is set to default values
		that are appropriate for the interface associated with the
		service.
	@param service The network service.
	@param protocolType The type of SCNetworkProtocol to be added to the service.
	@result TRUE if the protocol was added to the service; FALSE if the
		protocol was already present or an error was encountered.
 */
Boolean
SCNetworkServiceAddProtocolType			(SCNetworkServiceRef		service,
						 CFStringRef			protocolType)	AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@function SCNetworkServiceCopyAll
	@discussion Returns all available network services for the specified preferences.
	@param prefs The "preferences" session.
	@result The list of SCNetworkService services associated with the preferences.
		You must release the returned value.
 */
CFArrayRef /* of SCNetworkServiceRef's */
SCNetworkServiceCopyAll				(SCPreferencesRef		prefs)		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@function SCNetworkServiceCopyProtocols
	@discussion Returns all network protocols associated with the service.
	@param service The network service.
	@result The list of SCNetworkProtocol protocols associated with the service.
		You must release the returned value.
 */
CFArrayRef /* of SCNetworkProtocolRef's */
SCNetworkServiceCopyProtocols			(SCNetworkServiceRef		service)	AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@function SCNetworkServiceCreate
	@discussion Create a new network service for the specified interface in the
		configuration.
	@param prefs The "preferences" session.
	@result A reference to the new SCNetworkService.
		You must release the returned value.
 */
SCNetworkServiceRef
SCNetworkServiceCreate				(SCPreferencesRef		prefs,
						 SCNetworkInterfaceRef		interface)	AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@function SCNetworkServiceCopy
	@discussion Returns the network service with the specified identifier.
	@param prefs The "preferences" session.
	@param serviceID The unique identifier for the service.
	@result A reference to the SCNetworkService from the associated preferences;
		NULL if the serviceID does not exist in the preferences or if an
		error was encountered.
		You must release the returned value.
 */
SCNetworkServiceRef
SCNetworkServiceCopy				(SCPreferencesRef		prefs,
						 CFStringRef			serviceID)	AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@function SCNetworkServiceGetEnabled
	@discussion Returns whether this service has been enabled.
	@param service The network service.
	@result TRUE if the service is enabled.
 */
Boolean
SCNetworkServiceGetEnabled			(SCNetworkServiceRef		service)	AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@function SCNetworkServiceGetInterface
	@discussion Returns the network interface associated with the service.
	@param service The network service.
	@result A reference to the SCNetworkInterface associated with the service;
		NULL if an error was encountered.
 */
SCNetworkInterfaceRef
SCNetworkServiceGetInterface			(SCNetworkServiceRef		service)	AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@function SCNetworkServiceGetName
	@discussion Returns the [user specified] name associated with the service.
	@param service The network service.
	@result The [user specified] name.
 */
CFStringRef
SCNetworkServiceGetName				(SCNetworkServiceRef		service)	AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@function SCNetworkServiceCopyProtocol
	@discussion Returns the network protocol of the specified type for
		the service.
	@param service The network service.
	@result A reference to the SCNetworkProtocol associated with the service;
		NULL if this protocol has not been added or if an error was encountered.
		You must release the returned value.
 */
SCNetworkProtocolRef
SCNetworkServiceCopyProtocol			(SCNetworkServiceRef		service,
						 CFStringRef			protocolType)	AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@function SCNetworkServiceGetServiceID
	@discussion Returns the identifier for the service.
	@param service The network service.
	@result The service identifier.
 */
CFStringRef
SCNetworkServiceGetServiceID			(SCNetworkServiceRef		service)	AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@function SCNetworkServiceRemove
	@discussion Removes the network service from the configuration.
	@param service The network service.
	@result TRUE if the service was removed; FALSE if an error was encountered.
 */
Boolean
SCNetworkServiceRemove				(SCNetworkServiceRef		service)	AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@function SCNetworkServiceRemoveProtocolType
	@discussion Removes the network protocol of the specified type from the service.
	@param service The network service.
	@param protocolType The type of SCNetworkProtocol to be removed from the service.
	@result TRUE if the protocol was removed to the service; FALSE if the
		protocol was not configured or an error was encountered.
 */
Boolean
SCNetworkServiceRemoveProtocolType		(SCNetworkServiceRef		service,
						 CFStringRef			protocolType)	AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@function SCNetworkServiceSetEnabled
	@discussion Enables or disables the service.
	@param service The network service.
	@param enabled TRUE if the service should be enabled.
	@result TRUE if the enabled status was saved; FALSE if an error was encountered.
 */
Boolean
SCNetworkServiceSetEnabled			(SCNetworkServiceRef		service,
						 Boolean			enabled)	AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@function SCNetworkServiceSetName
	@discussion Stores the [user specified] name for the service.
	@param service The network service.
	@param name The [user defined] name to associate with the service.
	@result TRUE if the name was saved; FALSE if an error was encountered.

	Note: although not technically required, the [user specified] names
	for all services within any given set should be unique.  As such, an
	error will be returned if you attemp to name two services with the
	same string.
 */
Boolean
SCNetworkServiceSetName				(SCNetworkServiceRef		service,
						 CFStringRef			name)		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* --------------------------------------------------------------------------------
 * SETS
 * -------------------------------------------------------------------------------- */

/*!
	@group Set configuration
 */

/*!
	@function SCNetworkSetGetTypeID
	@discussion Returns the type identifier of all SCNetworkSet instances.
 */
CFTypeID
SCNetworkSetGetTypeID				(void)						AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@function SCNetworkSetAddService
	@discussion Adds the network service to the set.
	@param set The network set.
	@param service The service to be added.
	@result TRUE if the service was added to the set; FALSE if the
		service was already present or an error was encountered.

	Note: at the present time, the Network Prefs UI does not
	support having a single service be a member of more than
	one set.  As such, an error will be returned if you attempt
	to add a service to more than one set.
 */
Boolean
SCNetworkSetAddService				(SCNetworkSetRef		set,
						 SCNetworkServiceRef		service)	AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@function SCNetworkSetCopyAll
	@discussion Returns all available sets for the specified preferences.
	@param prefs The "preferences" session.
	@result The list of SCNetworkSet sets associated with the preferences.
		You must release the returned value.
 */
CFArrayRef /* of SCNetworkSetRef's */
SCNetworkSetCopyAll				(SCPreferencesRef		prefs)		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@function SCNetworkSetCopyCurrent
	@discussion Returns the "current" set.
	@param prefs The "preferences" session.
	@result The current set; NULL if no current set has been defined.
 */
SCNetworkSetRef
SCNetworkSetCopyCurrent				(SCPreferencesRef		prefs)		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@function SCNetworkSetCopyServices
	@discussion Returns all network services associated with the set.
	@param set The network set.
	@result The list of SCNetworkService services associated with the set.
		You must release the returned value.
 */
CFArrayRef /* of SCNetworkServiceRef's */
SCNetworkSetCopyServices			(SCNetworkSetRef		set)		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@function SCNetworkSetCreate
	@discussion Create a new set in the configuration.
	@param prefs The "preferences" session.
	@result A reference to the new SCNetworkSet.
		You must release the returned value.
 */
SCNetworkSetRef
SCNetworkSetCreate				(SCPreferencesRef		prefs)		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@function SCNetworkSetCopy
	@discussion Returns the set with the specified identifier.
	@param prefs The "preferences" session.
	@param setID The unique identifier for the set.
	@result A reference to the SCNetworkSet from the associated preferences;
		NULL if the setID does not exist in the preferences or if an
		error was encountered.
		You must release the returned value.
 */
SCNetworkSetRef
SCNetworkSetCopy				(SCPreferencesRef		prefs,
						 CFStringRef			setID)		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@function SCNetworkSetGetName
	@discussion Returns the [user specified] name associated with the set.
	@param set The network set.
	@result The [user specified] name.
 */
CFStringRef
SCNetworkSetGetName				(SCNetworkSetRef		set)		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@function SCNetworkSetGetSetID
	@discussion Returns the identifier for the set.
	@param set The network set.
	@result The set identifier.
 */
CFStringRef
SCNetworkSetGetSetID				(SCNetworkSetRef		set)		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@function SCNetworkSetGetServiceOrder
	@discussion Returns the [user specified] ordering of network services
		within the set.
	@param set The network set.
	@result The ordered list of CFStringRef service identifiers associated
		with the set;
		NULL if no service order has been specified or if an error
		was encountered.
 */
CFArrayRef /* of serviceID CFStringRef's */
SCNetworkSetGetServiceOrder			(SCNetworkSetRef		set)		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@function SCNetworkSetRemove
	@discussion Removes the set from the configuration.
	@param set The network set.
	@result TRUE if the set was removed; FALSE if an error was encountered.
 */
Boolean
SCNetworkSetRemove				(SCNetworkSetRef		set)		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@function SCNetworkSetRemoveService
	@discussion Removes the network service from the set.
	@param set The network set.
	@param service The service to be removed.
	@result TRUE if the service was removed from the set; FALSE if the
		service was not already present or an error was encountered.
 */
Boolean
SCNetworkSetRemoveService			(SCNetworkSetRef		set,
						 SCNetworkServiceRef		service)	AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@function SCNetworkSetSetCurrent
	@discussion Specifies the set that should be the "current" set.
	@param set The network set.
	@result TRUE if the current set was updated;
		FALSE if an error was encountered.
 */
Boolean
SCNetworkSetSetCurrent				(SCNetworkSetRef		set)		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@function SCNetworkSetSetName
	@discussion Stores the [user specified] name for the set.
	@param set The network set.
	@param name The [user defined] name to associate with the set.
	@result TRUE if the name was saved; FALSE if an error was encountered.

	Note: although not technically required, the [user specified] names
	for all set should be unique.  As such, an error will be returned if
	you attemp to name two sets with the same string.
 */
Boolean
SCNetworkSetSetName				(SCNetworkSetRef		set,
						 CFStringRef			name)		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@function SCNetworkSetGetServiceOrder
	@discussion Stores the [user specified] ordering of network services for the set.
	@param set The network set.
	@param newOrder The ordered list of CFStringRef service identifiers for the set.
	@result TRUE if the new service order was saved; FALSE if an error was encountered.
 */
Boolean
SCNetworkSetSetServiceOrder			(SCNetworkSetRef		set,
						 CFArrayRef			newOrder)	AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	/* serviceID CFStringRef's */


__END_DECLS

#endif	/* MAC_OS_X_VERSION_MAX_ALLOWED >= 1040 */

#endif	/* _SCNETWORKCONFIGURATION_H */
