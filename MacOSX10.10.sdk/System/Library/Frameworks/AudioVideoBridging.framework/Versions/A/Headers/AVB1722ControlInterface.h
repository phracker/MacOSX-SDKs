//
//  AVB1722ControlInterface.h
//  AudioVideoBridging
//
//  Copyright (c) 2010-2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

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
	@protected
	dispatch_queue_t callbackQueue;
	dispatch_queue_t commandsQueue;
	
	@private
	dispatch_queue_t transportQueue;
	
	@protected
	io_connect_t connection;
	
	@private
	IONotificationPortRef notificationPort;
	
	mach_vm_address_t receiveAddress;
	mach_vm_size_t receiveSize;
	mach_vm_address_t transmitAddress;
	mach_vm_size_t transmitSize;
	
	uint32_t transmitWriteHead;
	
	io_object_t notification;
	
	BOOL shouldRemove;
	
#ifndef _LP64
	NSString *interfaceName;
	AVBInterface *interface;
#endif
}

@property (copy) NSString *interfaceName;
/*!
 @property	interface
 @abstract	The AVBInterface object which owns this object. This may be nil if it was not created by an instance of AVBInterface
 */
@property (readonly, assign) AVBInterface *interface;

/*!
	@method		initWithService:onInterface:
	@abstract	Initialize the receiver with the specified service and interface.
	@param		aService	The io_object_t corresponding to the IORegistry entry of the control service on the interface.
	@param		anInterface	The AVBInterface the service is being added to.
	@result		The initialized receiver.
	@discussion	This method calls initWithService:onInterfaceNamed: with anInterface.interfaceName.
 */
- (id)initWithService:(io_object_t)aService onInterface:(AVBInterface *)anInterface NS_DEPRECATED(10_8, 10_9, NA, NA);
/*!
	@method		initWithService:onInterfaceNamed:
	@abstract	Initialize the receiver with the specified service and interface
	@param		aService	The io_object_t corresponding to the IORegistry entry of the control service on the interface.
	@param		anInterfaceName	The BSD name of the interface on which to create the object.
	@result		The initialized receiver.
 */
- (id)initWithService:(io_object_t)aService onInterfaceNamed:(NSString *)anInterfaceName NS_DEPRECATED(10_8, 10_9, NA, NA);
/*!
	@method		initWithInterfaceName:
	@abstract	Initializes the receiver to work with a 1722 control service on the specified interface. The client must have previously be requested to load on the interface.
	@param		anInterfaceName	The BSD name of the interface on which to create the object.
	@result		The initialized receiver.
 */
- (instancetype)initWithInterfaceName:(NSString *)anInterfaceName NS_AVAILABLE(10_9, NA);

@end
