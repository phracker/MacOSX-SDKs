//
//  AVB1722ControlInterface.h
//  AudioVideoBridging
//
//  Copyright (c) 2010-2014 Apple Inc. All rights reserved.
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
NS_CLASS_AVAILABLE(10_8, NA)
@interface AVB1722ControlInterface : NSObject
{
#if AVB_LEGACY_OBJC_RUNTIME
@private
	void *_implControlInterface;
#endif
}

@property (readonly, copy) NSString *interfaceName;
/*!
 @property	interface
 @abstract	The AVBInterface object which owns this object. This may be nil if it was not created by an instance of AVBInterface
 */
@property (readonly, assign, nullable) AVBInterface *interface;

- (instancetype)init NS_UNAVAILABLE;

/*!
	@method		initWithInterfaceName:
	@abstract	Initializes the receiver to work with a 1722 control service on the specified interface. The client must have previously be requested to load on the interface.
	@param		anInterfaceName	The BSD name of the interface on which to create the object.
	@result		The initialized receiver.
 */
- (nullable instancetype)initWithInterfaceName:(NSString *)anInterfaceName NS_AVAILABLE(10_9, NA);

/*!
	@method		initWithInterface:
	@abstract	Initializes the receiver to work with a 1722 control service on the specified interface. The client must have previously be requested to load on the interface.
	@param		anInterface	The AVBInterface object of the interface on which to create the object.
	@result		The initialized receiver.
 */
- (nullable instancetype)initWithInterface:(AVBInterface *)anInterface NS_AVAILABLE(10_11, NA);

@end

NS_ASSUME_NONNULL_END
