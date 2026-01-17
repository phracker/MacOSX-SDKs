//
//  VZLinuxRosettaDirectoryShare.h
//  Virtualization
//
//  Copyright © 2022-2023 Apple Inc. All rights reserved.
//

#ifdef __arm64__

#import <Virtualization/VZDirectoryShare.h>
#import <Virtualization/VZLinuxRosettaCachingOptions.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract Availability of Rosetta support for Linux binaries.
 */
typedef NS_ENUM(NSInteger, VZLinuxRosettaAvailability) {
    /*! Rosetta support for Linux binaries is not available on the host system. */
    VZLinuxRosettaAvailabilityNotSupported,

    /*! Rosetta support for Linux binaries is not installed on the host system. */
    VZLinuxRosettaAvailabilityNotInstalled,

    /*! Rosetta support for Linux is installed on the host system. */
    VZLinuxRosettaAvailabilityInstalled,

} NS_SWIFT_NAME(VZLinuxRosettaAvailability) API_AVAILABLE(macos(13.0));

/*!
 @abstract Directory share to enable Rosetta support for Linux binaries.
 @discussion This directory share exposes Rosetta within a shared directory in the guest. Linux can use it to translate x86_64 binaries.
 @see VZDirectorySharingDeviceConfiguration
 @see VZSharedDirectory
 */
VZ_EXPORT API_AVAILABLE(macos(13.0))
@interface VZLinuxRosettaDirectoryShare : VZDirectoryShare

/*!
 @abstract Initialize a Rosetta directory share if Rosetta support for Linux binaries is installed.
 @param error Error object to store the error, if an error exists.
 @discussion The call returns an error if Rosetta is not available for a directory share. To install Rosetta support, use +[VZLinuxRosettaDirectoryShare installRosettaIfNeeded:].
 @see +[VZLinuxRosettaDirectoryShare installRosettaIfNeeded:]
 */
- (nullable instancetype)initWithError:(NSError **)error NS_DESIGNATED_INITIALIZER NS_SWIFT_NAME(init());

/*!
 @abstract Download and install Rosetta support for Linux binaries if necessary.
 @param completionHandler The completion handler gets called with a valid error on failure and a nil error on success. It will also be invoked on an arbitrary queue.
 @discussion
    The call prompts the user through the download and install flow for Rosetta. This call is successful if the error is nil.
 @see +[VZLinuxRosettaDirectoryShare availability]
 */
+ (void)installRosettaWithCompletionHandler:(void(^)(NSError * _Nullable))completionHandler;

/*!
 @abstract Enable translation caching and configure the socket communication type for Rosetta.
 */
@property (nullable, strong) VZLinuxRosettaCachingOptions *options NS_REFINED_FOR_SWIFT API_AVAILABLE(macos(14.0));

/*!
 @abstract Check the availability of Rosetta support for the directory share.
 */
@property (class, readonly) VZLinuxRosettaAvailability availability;

@end

NS_ASSUME_NONNULL_END

#endif
