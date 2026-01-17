//
//  VZDirectorySharingDeviceConfiguration.h
//  Virtualization
//
//  Copyright © 2020-2023 Apple Inc. All rights reserved.
//

#import <Virtualization/VZDefines.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract Base class for a directory sharing device configuration.
 @discussion
    VZDirectorySharingDeviceConfiguration should not be instantiated directly.
    One of its subclasses like VZVirtioFileSystemDeviceConfiguration should be used instead.

 @see VZVirtioFileSystemDeviceConfiguration
*/
VZ_EXPORT API_AVAILABLE(macos(12.0))
@interface VZDirectorySharingDeviceConfiguration : NSObject <NSCopying>

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
