//
//  VZVirtualMachineView.h
//  Virtualization
//
//  Copyright © 2019-2025 Apple Inc. All rights reserved.
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

/*!
 @abstract The virtual machine to display in the view.
*/
@property (nullable, strong) VZVirtualMachine *virtualMachine;

/*!
 @abstract Whether certain system hot keys should be sent to the guest instead of the host. Defaults to NO.
*/
@property BOOL capturesSystemKeys;

/*!
 @abstract Automatically reconfigures the graphics display associated with this view with respect to view changes. Defaults to NO.
 @discussion
    Automatically resize or reconfigure this graphics display when the view properties update.
    For example, resizing the display when the view has a live resize operation. When enabled,
    the graphics display will automatically be reconfigured to match the host display environment.

    This property can only be set on a single VZVirtualMachineView targeting a particular VZGraphicsDisplay
    at a time. If multiple VZVirtualMachineViews targeting the same VZGraphicsDisplay enable this property,
    only one view will respect the property, and the other view will have had the property disabled.
 */
@property BOOL automaticallyReconfiguresDisplay API_AVAILABLE(macos(14.0));

@end

NS_ASSUME_NONNULL_END
