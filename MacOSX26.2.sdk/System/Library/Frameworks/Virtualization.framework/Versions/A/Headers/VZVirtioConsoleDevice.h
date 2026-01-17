//
//  VZVirtioConsoleDevice.h
//  Virtualization
//
//  Copyright © 2022-2023 Apple Inc. All rights reserved.
//

#import <Virtualization/VZConsoleDevice.h>
#import <Virtualization/VZDefines.h>
#import <Virtualization/VZVirtioConsolePort.h>
#import <Virtualization/VZVirtioConsolePortArray.h>

NS_ASSUME_NONNULL_BEGIN

@class VZVirtioConsoleDevice;

/*!
 @abstract Delegate object for VZVirtioConsoleDevice.
 @discussion
    A class conforming to the VZVirtioConsoleDeviceDelegate protocol can provide methods that notify when a console port is opened or closed in the virtual machine.
 @see VZVirtioConsoleDevice
 @see VZVirtioConsolePort
 */
VZ_EXPORT API_AVAILABLE(macos(13.0))
@protocol VZVirtioConsoleDeviceDelegate <NSObject>
@optional

/*!
 @abstract Invoked when a guest process has opened a Virtio console port.
 @param consoleDevice The console port's console device.
 @param consolePort The console port that has been opened.
 @discussion
    Extra care should be taken to ensure that any pending data from the VZVirtioConsolePort attachment has been processed or flushed before communicating with a new virtual machine process.
 */
- (void)consoleDevice:(VZVirtioConsoleDevice *)consoleDevice didOpenPort:(VZVirtioConsolePort *)consolePort;

/*!
 @abstract Invoked when a guest process has closed a Virtio console port.
 @param consoleDevice The console port's console device.
 @param consolePort The console port that has been closed.
 @discussion
    It is recommended to finish processing or flushing any remaining data from the VZVirtioConsolePort attachment after a port has been closed.
 */
- (void)consoleDevice:(VZVirtioConsoleDevice *)consoleDevice didClosePort:(VZVirtioConsolePort *)consolePort;

@end

/*!
 @abstract Class representing a Virtio console device in a virtual machine.
 @discussion
    VZVirtioConsoleDevice should not be instantiated directly.
 @see VZConsoleDeviceConfiguration
 */
VZ_EXPORT API_AVAILABLE(macos(13.0))
@interface VZVirtioConsoleDevice : VZConsoleDevice

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/*!
 @abstract Pointer to a delegate object for the console device.
 */
@property (nullable, weak) id <VZVirtioConsoleDeviceDelegate> delegate;

/*!
 @abstract The console ports currently being used by this console device.
 */
@property (readonly, strong) VZVirtioConsolePortArray *ports;

@end

NS_ASSUME_NONNULL_END
