//
//  VZMacGraphicsDeviceConfiguration.h
//  Virtualization
//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#import <Virtualization/VZGraphicsDeviceConfiguration.h>

NS_ASSUME_NONNULL_BEGIN

@class VZMacGraphicsDisplayConfiguration;

/*!
 @abstract Configuration for a Mac graphics device.
 @discussion This device can be used to attach a display to be shown in a VZVirtualMachineView.
*/
VZ_EXPORT API_AVAILABLE(macos(12.0))
@interface VZMacGraphicsDeviceConfiguration : VZGraphicsDeviceConfiguration

- (instancetype)init;

/*!
 @abstract The displays to be attached to this graphics device.
*/
@property (copy) NSArray<VZMacGraphicsDisplayConfiguration *> *displays;

@end

NS_ASSUME_NONNULL_END
