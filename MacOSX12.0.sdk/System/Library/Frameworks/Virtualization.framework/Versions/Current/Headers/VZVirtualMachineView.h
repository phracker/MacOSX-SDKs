//
//  VZVirtualMachineView.h
//  Virtualization
//
//  Copyright © 2019-2021 Apple Inc. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <Virtualization/VZDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class VZVirtualMachine;

/*!
 @abstract A view that allows user interaction with a virtual machine.
 @discussion
    The VZVirtualMachineView shows the contents of the virtual machine framebuffer. If the virtual machine configuration includes a keyboard and a pointing device,
    the view forwards keyboard and mouse events to the virtual machine via those devices.
 @seealso VZVirtualMachine
*/
VZ_EXPORT API_AVAILABLE(macos(12.0))
@interface VZVirtualMachineView : NSView

/*! @abstract The virtual machine to display in the view. */
@property (nullable, strong) VZVirtualMachine *virtualMachine;

/*! @abstract Whether certain system hot keys should be sent to the guest instead of the host. Defaults to NO. */
@property BOOL capturesSystemKeys;

@end

NS_ASSUME_NONNULL_END
