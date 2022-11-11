//
//  VZMultipleDirectoryShare.h
//  Virtualization
//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#import <Virtualization/VZDirectoryShare.h>

NS_ASSUME_NONNULL_BEGIN

@class VZSharedDirectory;

/*!
 @abstract Directory share for multiple directories.
 @discussion This directory share exposes multiple directories from the host file system to the guest.
 @see VZDirectorySharingDeviceConfiguration
 @see VZSharedDirectory
 */
VZ_EXPORT API_AVAILABLE(macos(12.0))
@interface VZMultipleDirectoryShare : VZDirectoryShare

/*!
 @abstract Initialize the directory share with an empty set of directories.
 */
- (instancetype)init;

/*!
 @abstract Initialize the directory share with a set of directories on the host.
 @param directories Directories on the host to expose to the guest by name.
 @discussion The dictionary string keys will be the name for the directory. The keys must be valid names or an exception will be raised.
 @see +[VZMultipleDirectoryShare validateName:error:]
 */
- (instancetype)initWithDirectories:(NSDictionary<NSString *, VZSharedDirectory *> *)directories NS_DESIGNATED_INITIALIZER;

/*!
 @abstract The directories on the host to expose to the guest.
 @discussion The dictionary string keys will be the name for the directory. The keys must be valid names or an exception will be raised.
 @see +[VZMultipleDirectoryShare validateName:error:]
 */
@property (readonly, copy) NSDictionary<NSString *, VZSharedDirectory *> *directories;

/*!
 @abstract Check if a name is a valid directory name.
 @param name The name to validate.
 @param error If not nil, assigned with an error describing why the name is not valid.
 @discussion The name must not be empty, have characters unsafe for file systems, be longer than NAME_MAX, or other restrictions.
 @see +[VZMultipleDirectoryShare canonicalizedNameFromName:]
*/
+ (BOOL)validateName:(NSString *)name error:(NSError **)error;

/*!
 @abstract Canonicalize a string to be a valid directory name.
 @param name The name to canonicalize.
 @discussion This returns nil when it cannot produce a valid name. When not nil, the result is a valid directory name.
 @see +[VZMultipleDirectoryShare validateName:error:]
*/
+ (nullable NSString *)canonicalizedNameFromName:(NSString *)name NS_SWIFT_NAME(canonicalizedName(from:));

@end

NS_ASSUME_NONNULL_END
