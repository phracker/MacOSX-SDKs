//
//  VZVirtioConsolePortArray.h
//  Virtualization
//
//  Copyright © 2022-2023 Apple Inc. All rights reserved.
//

#import <Virtualization/VZDefines.h>
#import <Virtualization/VZVirtioConsolePort.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract Virtio Console Port Array
 @discussion
    This array stores a collection of ports configured for use by a VZVirtioConsoleDevice. VZVirtioConsolePort objects may be retrieved by index.
 @see VZVirtioConsoleDevice
 @see VZVirtioConsolePort
 */
VZ_EXPORT API_AVAILABLE(macos(13.0))
@interface VZVirtioConsolePortArray : NSObject

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/*!
 @abstract Get a port at the specified index.
 */
- (nullable VZVirtioConsolePort *)objectAtIndexedSubscript:(NSUInteger)portIndex;

/*!
 @abstract The maximum number of ports allocated by this device.
 */
@property (readonly) uint32_t maximumPortCount;

@end

NS_ASSUME_NONNULL_END
