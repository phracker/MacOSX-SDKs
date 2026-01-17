//
//  VZVirtualMachineDelegate.h
//  Virtualization
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <Virtualization/VZDefines.h>

NS_ASSUME_NONNULL_BEGIN

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

@end

NS_ASSUME_NONNULL_END
