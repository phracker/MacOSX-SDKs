//
//  VZSpiceAgentPortAttachment.h
//  Virtualization
//
//  Copyright © 2022-2023 Apple Inc. All rights reserved.
//

#import <Virtualization/VZSerialPortAttachment.h>

NS_ASSUME_NONNULL_BEGIN

VZ_EXPORT API_AVAILABLE(macos(13.0))
@interface VZSpiceAgentPortAttachment : VZSerialPortAttachment

- (instancetype)init NS_DESIGNATED_INITIALIZER;

/*!
 @abstract Enable the Spice agent clipboard sharing capability.
 @discussion
    If enabled, the clipboard capability will be advertised to the Spice guest agent. Copy and paste events
    will be shared between the host and the virtual machine.

    This property is enabled by default.
 */
@property BOOL sharesClipboard;

/*!
 @abstract The Spice agent port name.
 @discussion
    A console port configured with this name will spawn a Spice guest agent if supported by the guest.

    VZConsolePortConfiguration.attachment must be set to VZSpiceAgentPortAttachment.
    VZVirtioConsolePortConfiguration.isConsole must remain false on a Spice agent port.
 */
@property (class, readonly, copy) NSString *spiceAgentPortName;

@end

NS_ASSUME_NONNULL_END

