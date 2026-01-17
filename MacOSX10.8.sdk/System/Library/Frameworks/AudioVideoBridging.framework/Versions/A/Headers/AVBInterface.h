//
//  AVBInterface.h
//  AudioVideoBridging
//
//  Copyright 2010-2012 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class AVBMACAddress;
@class AVBNetworkClient;

@class AVBMMRP;
@class AVBMVRP;
@class AVBMSRPDomain;
@class AVBMSRPListener;
@class AVBMSRPTalker;
@class AVB17221EntityDiscovery;

@class AVB8021ASTimeSync;

@class AVB17221AECPInterface;
@class AVB17221ACMPInterface;

/*!
	@class		AVBInterface
	@abstract	AVBInterface is an abstract class providing a central access point for the AVB functionality of an interface.
	@discussion	AVBInterface is an abstract class providing a central access point for the AVB functionality of an interface.
				AVBInterface objects should not be directly created as they cannot provide full functionality, instead a concrete
				subclass should be instantiated.
 */
NS_CLASS_AVAILABLE(10_8, NA)
@interface AVBInterface : NSObject
{
	@private
	AVBNetworkClient *_networkClient;
	
	NSString *_interfaceName;
	
	AVBMMRP *_mmrp;
	AVBMVRP *_mvrp;
	AVBMSRPDomain *_msrpDomain;
	AVBMSRPListener *_msrpListener;
	AVBMSRPTalker *_msrpTalker;
	AVB17221EntityDiscovery *_entityDiscovery;
	
	AVB8021ASTimeSync *_timeSync;

	AVB17221AECPInterface *_aecp;
	AVB17221ACMPInterface *_acmp;
}

/*!
	@property	interfaceName
	@abstract	The BSD interface name.
 */
@property (copy, readonly) NSString *interfaceName;

/*!
	@property	entityDiscovery
	@abstract	The IEEE P1722.1 entity discovery for the interface.
 */
@property (retain, readonly) AVB17221EntityDiscovery *entityDiscovery;

/*!
	@property	aecp
	@abstract	The IEEE P1722.1 AECP interface for the interface.
 */
@property (retain, readonly) AVB17221AECPInterface *aecp;
/*!
	@property	acmp
	@abstract	The IEEE P1722.1 ACMP interface for the interface.
 */
@property (retain, readonly) AVB17221ACMPInterface *acmp;

/*!
 @method		macAddressForInterfaceNamed:
 @abstract	This method looks up the MAC address for an interface with a given BSD name.
 @param		anInterfaceName	The BSD name of the interface to get the address for.
 @result		An instance of AVBMACAddress if the lookup was successful, nil otherwise.
 */
+ (AVBMACAddress *)macAddressForInterfaceNamed:(NSString *)anInterfaceName;

/*!
	@method		supportedInterfaces
	@abstract	This method returns an array of BSD interface names of interfaces supporting AVB. An interface is included in this list if it claims it supports AVB.
	@result		An NSArray of NSStrings, with each string being the BSD name of an interface. This may return nil.
 */
+ (NSArray *)supportedInterfaces;

/*!
	@method		isAVBEnabledOnInterfaceNamed:
	@abstract	This method determines if AVB has been enabled on an interface.
	@param		anInterfaceName	The BSD name of the interface.
	@result		YES if AVB is enabled, NO otherwise.
 */
+ (BOOL)isAVBEnabledOnInterfaceNamed:(NSString *)anInterfaceName;
/*!
	@method		isAVBCapableInterfaceNamed:
	@abstract	This method determines if AVB is supported on an interface.
	@param		anInterfaceName	The BSD name of the interface.
	@result		YES if AVB is supported, NO otherwise.
 */
+ (BOOL)isAVBCapableInterfaceNamed:(NSString *)anInterfaceName;

/*!
	@method		initWithInterfaceName:
	@abstract	This method initializes the receiver to work on the specified interface.
	@param		anInterfaceName	The BSD name of the interface.
	@result		The initialized receiver.
 */
- (id)initWithInterfaceName:(NSString *)anInterfaceName;

/*!
 @method		myGUID
 @abstract	This method returns the GUID which is used by the built-in controller functionality of Mac OS X. This is either the FireWire GUID or an EUI64 based on the first found ethernet type interface (may be an ethernet port, USB ethernet adapter, PCI Express adapter or the AirPort card).
 @result		The GUID which is used by the OS.
 */
+ (uint64_t)myGUID;

@end
