//
//  AVB1722ControlInterface.h
//  AudioVideoBridging
//
//  Copyright (c) 2010-2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#include <IOKit/IOKitLib.h>

NS_ASSUME_NONNULL_BEGIN

@class AVBInterface;

/*!
	@class		AVB1722ControlInterface
	@abstract	AVB1722ControlInterface is an abstract class providing the common API for utilizing control services based on IEEE 1722-2011 control frames.
	@discussion	AVB1722ControlInterface is an abstract class providing the common API for utilizing control services based on IEEE 1722-2011 control frames.
				It provides the API for the basic IOKit interactions to talk to the kernel driver.
 */
API_AVAILABLE(macos(10.8))
@interface AVB1722ControlInterface : NSObject


@property (readonly, copy) NSString *interfaceName;
/*!
 @property	interface
 @abstract	The AVBInterface object which owns this object. This may be nil if it was not created by an instance of AVBInterface
 */
@property (readonly, weak, nullable) AVBInterface *interface;

- (instancetype)init NS_UNAVAILABLE;

/*!
	@method		initWithInterfaceName:
	@abstract	Initializes the receiver to work with a 1722 control service on the specified interface. The client must have previously be requested to load on the interface.
	@param		anInterfaceName	The BSD name of the interface on which to create the object.
	@result		The initialized receiver.
 */
- (nullable instancetype)initWithInterfaceName:(NSString *)anInterfaceName API_AVAILABLE(macos(10.9));

/*!
	@method		initWithInterface:
	@abstract	Initializes the receiver to work with a 1722 control service on the specified interface. The client must have previously be requested to load on the interface.
	@param		anInterface	The AVBInterface object of the interface on which to create the object.
	@result		The initialized receiver.
 */
- (nullable instancetype)initWithInterface:(AVBInterface *)anInterface API_AVAILABLE(macos(10.11));

@end

NS_ASSUME_NONNULL_END
