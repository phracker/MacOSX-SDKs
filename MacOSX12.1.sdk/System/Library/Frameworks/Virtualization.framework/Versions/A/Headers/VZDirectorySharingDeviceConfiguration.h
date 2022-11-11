//
//  VZDirectorySharingDeviceConfiguration.h
//  Virtualization
//
//  Copyright © 2020-2021 Apple Inc. All rights reserved.
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
VZ_EXPORT
@interface VZDirectorySharingDeviceConfiguration : NSObject <NSCopying>

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
