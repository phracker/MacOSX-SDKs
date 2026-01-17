//
//  VZSharedDirectory.h
//  Virtualization
//
//  Copyright © 2021-2023 Apple Inc. All rights reserved.
//

#import <Virtualization/VZDefines.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract A directory on the host that can be exposed to a guest.
 */
VZ_EXPORT API_AVAILABLE(macos(12.0))
@interface VZSharedDirectory : NSObject

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/*!
 @abstract Initialize with a host directory.
 @param url Local file URL to expose to the guest.
 @param readOnly Whether or not the directory will be exposed as read-only to the guest.
 */
- (instancetype)initWithURL:(NSURL *)url readOnly:(BOOL)readOnly NS_DESIGNATED_INITIALIZER;

/*!
 @abstract File URL to a directory on the host to expose to the guest.
 @discussion The URL must point to an existing directory path in the host file system.
 */
@property (readonly, copy) NSURL *URL;

/*!
 @abstract Whether or not the directory will be exposed as read-only to the guest.
*/
@property (readonly, getter=isReadOnly) BOOL readOnly;

@end

NS_ASSUME_NONNULL_END
