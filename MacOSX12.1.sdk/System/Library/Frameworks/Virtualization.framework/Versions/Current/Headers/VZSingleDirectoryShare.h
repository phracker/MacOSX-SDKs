//
//  VZSingleDirectoryShare.h
//  Virtualization
//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#import <Virtualization/VZDirectoryShare.h>

NS_ASSUME_NONNULL_BEGIN

@class VZSharedDirectory;

/*!
 @abstract Directory share for a single directory.
 @discussion This directory share exposes a single directory from the host file system to the guest.
 @see VZDirectorySharingDeviceConfiguration
 @see VZSharedDirectory
 */
VZ_EXPORT API_AVAILABLE(macos(12.0))
@interface VZSingleDirectoryShare : VZDirectoryShare

/*!
 @abstract Initialize the directory share with a directory on the host.
 @param directory Directory to share.
 */
- (instancetype)initWithDirectory:(VZSharedDirectory *)directory NS_DESIGNATED_INITIALIZER;

/*!
 @abstract Directory on the host to share.
 */
@property (readonly, strong) VZSharedDirectory *directory;

@end

NS_ASSUME_NONNULL_END
