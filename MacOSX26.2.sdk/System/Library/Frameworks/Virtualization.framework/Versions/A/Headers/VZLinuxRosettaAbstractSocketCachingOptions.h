//
//  VZLinuxRosettaAbstractSocketCachingOptions.h
//  Virtualization
//
//  Copyright © 2023 Apple Inc. All rights reserved.
//

#import <Virtualization/VZLinuxRosettaCachingOptions.h>

#ifdef __arm64__

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract Caching options for an Abstract Socket.
 @discussion This object configures Rosetta to communicate with the Rosetta daemon using an Abstract Socket.
 @see VZLinuxRosettaCachingOptions
 */
VZ_EXPORT API_AVAILABLE(macos(14.0))
NS_REFINED_FOR_SWIFT
@interface VZLinuxRosettaAbstractSocketCachingOptions : VZLinuxRosettaCachingOptions

/*!
 @abstract Initialize options to be set on a VZLinuxRosettaDirectoryShare.
 @param name The name of the Abstract Socket to be used to communicate with the Rosetta translation daemon. This cannot exceed maximumNameLength UTF-8 bytes long.
 @param error If not nil, assigned with the error if the initialization failed.
 @discussion
    Rosetta can be optionally configured to use cached translations from the Rosetta translation daemon communicating through an Abstract Socket.
    If name exceeds maximumNameLength UTF-8 bytes, nil is returned and the error is set.
 */
- (nullable instancetype)initWithName:(NSString *)name error:(NSError **)error NS_DESIGNATED_INITIALIZER;

/*!
 @abstract Name set by initWithName.
 @discussion
    This is the name of the Abstract Socket to be used by Rosetta.
 */
@property (readonly, copy) NSString *name;

/*!
 @abstract The maximum allowed length of name, as defined by the sockaddr_un structure in Linux.
 */
@property (class, readonly) NSUInteger maximumNameLength;

@end

NS_ASSUME_NONNULL_END

#endif
