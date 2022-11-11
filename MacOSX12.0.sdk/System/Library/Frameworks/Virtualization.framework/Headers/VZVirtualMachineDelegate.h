//
//  VZVirtualMachineDelegate.h
//  Virtualization
//
//  Copyright © 2020-2021 Apple Inc. All rights reserved.
//

#import <Virtualization/VZDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class VZNetworkDevice;
@class VZVirtualMachine;

/*! @abstract A class conforming to the VZVirtualMachineDelegate protocol can provide
 methods for tracking the virtual machine state.
 */
@protocol VZVirtualMachineDelegate <NSObject>

@optional

/*!
 @abstract Invoked when a guest has stopped the virtual machine.
 @param virtualMachine The virtual machine invoking the delegate method.
 */
- (void)guestDidStopVirtualMachine:(VZVirtualMachine *)virtualMachine;

/*!
 @abstract Invoked when a virtual machine is stopped due to an error.
 @param virtualMachine The virtual machine invoking the delegate method.
 @param error The error.
 */
- (void)virtualMachine:(VZVirtualMachine *)virtualMachine didStopWithError:(NSError *)error;

/*!
 @abstract Invoked when a virtual machine's network attachment has been disconnected.
 @discussion
    This method is invoked every time that the network interface fails to start, resulting in the network attachment being disconnected. This can happen
    in many situations such as initial boot, device reset, reboot, etc. Therefore, this method may be invoked several times during a virtual machine's life cycle.

    The VZNetworkDevice.attachment property will be nil after the method is invoked.
 @param virtualMachine The virtual machine invoking the delegate method.
 @param networkDevice The network device whose attachment was disconnected.
 @param error The error.
 */
- (void)virtualMachine:(VZVirtualMachine *)virtualMachine networkDevice:(VZNetworkDevice *)networkDevice attachmentWasDisconnectedWithError:(NSError *)error API_AVAILABLE(macos(12.0));

@end

NS_ASSUME_NONNULL_END
