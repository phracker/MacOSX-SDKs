//
//  VZLinuxRosettaUnixSocketCachingOptions.h
//  Virtualization
//
//  Copyright © 2023 Apple Inc. All rights reserved.
//

#import <Virtualization/VZLinuxRosettaCachingOptions.h>

#ifdef __arm64__

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract Caching options for a Unix Domain Socket.
 @discussion This object configures Rosetta to communicate with the Rosetta daemon using a Unix Domain Socket.
 @see VZLinuxRosettaCachingOptions
 */
VZ_EXPORT API_AVAILABLE(macos(14.0))
NS_REFINED_FOR_SWIFT
@interface VZLinuxRosettaUnixSocketCachingOptions : VZLinuxRosettaCachingOptions

/*!
 @abstract Initialize options to be set on a VZLinuxRosettaDirectoryShare.
 @param path The path of the Unix Domain Socket to be used to communicate with the Rosetta translation daemon. This cannot exceed maximumPathLength UTF-8 bytes long.
 @param error If not nil, assigned with the error if the initialization failed.
 @discussion
    Rosetta can be optionally configured to use cached translations from the Rosetta translation daemon communicating through a Unix Domain Socket.
    If path exceeds maximumPathLength UTF-8 bytes, nil is returned and the error is set.
    The guest operating system must have a directory at path created in order for translation caching to operate correctly.
 */
- (nullable instancetype)initWithPath:(NSString *)path error:(NSError **)error NS_DESIGNATED_INITIALIZER;

/*!
 @abstract Initialize default options to be set on a VZLinuxRosettaDirectoryShare.
 @discussion
    The default translation caching configuration uses a Unix Domain Socket at /run/rosettad/rosetta.sock.
 */
- (instancetype)init;

/*!
 @abstract Path set by initWithPath.
 @discussion
    This is the path of the Unix Domain Socket to be used by Rosetta.
 */
@property (readonly, copy) NSString *path;

/*!
 @abstract The maximum allowed length of path, as defined by the sockaddr_un structure in Linux.
 */
@property (class, readonly) NSUInteger maximumPathLength;

@end

NS_ASSUME_NONNULL_END

#endif
