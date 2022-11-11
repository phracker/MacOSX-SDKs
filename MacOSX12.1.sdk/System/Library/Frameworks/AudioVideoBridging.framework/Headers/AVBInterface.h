//
//  AVBInterface.h
//  AudioVideoBridging
//
//  Copyright (c) 2010-2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#include <IOKit/IOKitLib.h>

NS_ASSUME_NONNULL_BEGIN

@class AVBMACAddress;

@class AVB17221EntityDiscovery;

@class AVB17221AECPInterface;
@class AVB17221ACMPInterface;


@protocol AVBInterfaceDelegate;

/*!
	@class		AVBInterface
	@abstract	AVBInterface is an abstract class providing a central access point for the AVB functionality of an interface.
	@discussion	AVBInterface is an abstract class providing a central access point for the AVB functionality of an interface.
				AVBInterface objects should not be directly created as they cannot provide full functionality, instead a concrete
				subclass should be instantiated.
 */
API_AVAILABLE(macos(10.8))
@interface AVBInterface : NSObject
{
}

/*!
	@property	interfaceName
	@abstract	The BSD interface name.
 */
@property (copy, readonly) NSString *interfaceName;

/*!
	@property	entityDiscovery
	@abstract	The IEEE Std 1722.1™-2013 entity discovery for the interface.
 */
@property (strong, readonly, nullable) AVB17221EntityDiscovery *entityDiscovery;

/*!
	@property	aecp
	@abstract	The IEEE Std 1722.1™-2013 AECP interface for the interface.
 */
@property (strong, readonly, nullable) AVB17221AECPInterface *aecp;
/*!
	@property	acmp
	@abstract	The IEEE Std 1722.1™-2013 ACMP interface for the interface.
 */
@property (strong, readonly, nullable) AVB17221ACMPInterface *acmp;

/*!
 @method		macAddressForInterfaceNamed:
 @abstract	This method looks up the MAC address for an interface with a given BSD name.
 @param		anInterfaceName	The BSD name of the interface to get the address for.
 @result		An instance of AVBMACAddress if the lookup was successful, nil otherwise.
 */
+ (nullable AVBMACAddress *)macAddressForInterfaceNamed:(NSString *)anInterfaceName;

/*!
	@method		supportedInterfaces
	@abstract	This method returns an array of BSD interface names of interfaces supporting AVB. An interface is included in this list if it claims it supports AVB.
	@result		An NSArray of NSStrings, with each string being the BSD name of an interface. This may return nil.
 */
+ (nullable NSArray <NSString *>*)supportedInterfaces;

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

- (instancetype)init NS_UNAVAILABLE;

/*!
	@method		initWithInterfaceName:
	@abstract	This method initializes the receiver to work on the specified interface.
	@param		anInterfaceName	The BSD name of the interface.
	@result		The initialized receiver.
 */
- (nullable instancetype)initWithInterfaceName:(NSString *)anInterfaceName NS_DESIGNATED_INITIALIZER;

/*!
 @method		myEntityID
 @abstract	This method returns the EntityID which is used by the built-in controller functionality of Mac OS X. This is either the FireWire GUID or an EUI64 based on the first found ethernet type interface (may be an ethernet port, USB ethernet adapter, PCI Express adapter or the AirPort card).
 @result		The EntityID which is used by the OS.
 */
+ (uint64_t)myEntityID;

@end

NS_ASSUME_NONNULL_END
