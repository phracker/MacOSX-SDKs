//
//  VZMacOSRestoreImage.h
//  Virtualization
//
//  Copyright © 2021-2023 Apple Inc. All rights reserved.
//

#ifdef __arm64__

#import <Virtualization/VZDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class VZMacOSConfigurationRequirements;

/*!
 @abstract VZMacOSRestoreImage describes a version of macOS to be installed to a virtual machine.
 @discussion
    A VZMacOSRestoreImage object can be created by loading an installation media file. A VZMacOSInstaller
    object must be initialized with this VZMacOSRestoreImage object in order to install the operating
    system onto a virtual machine.

    Loading a restore image requires the app to have the "com.apple.security.virtualization" entitlement.
 @seealso VZMacHardwareModel
 @seealso VZMacOSInstaller
 @seealso VZMacOSConfigurationRequirements
*/
VZ_EXPORT API_AVAILABLE(macos(12.0))
@interface VZMacOSRestoreImage : NSObject

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/*!
 @abstract Load a restore image from a file on the local file system.
 @param fileURL A file URL indicating the macOS restore image to load.
 @param completionHandler Block called after the restore image has successfully loaded or has failed to load.
    The error parameter passed to the block is nil if the restore image was loaded successfully.
    The completion handler will be invoked on an arbitrary thread.
 @discussion
    VZMacOSRestoreImage can load IPSW installation media from a local file. If the fileURL parameter does not refer to
    a local file, an exception will be raised.
 */
+ (void)loadFileURL:(NSURL *)fileURL completionHandler:(void (^)(VZMacOSRestoreImage * _Nullable, NSError * _Nullable))completionHandler NS_REFINED_FOR_SWIFT NS_SWIFT_ASYNC_NAME(image(from:));

/*!
 @abstract Fetch the latest restore image supported by this host from the network.
 @param completionHandler Block called after the restore image fetch has succeeded or failed.
    The error parameter passed to the block is nil if the restore image was fetched successfully.
    The completion handler will be invoked on an arbitrary thread.
 @discussion
    A VZMacOSInstaller object must be constructed with a VZMacOSRestoreImage loaded from a file on the local
    filesystem. A VZMacOSRestoreImage fetched with the fetchLatestSupportedWithCompletionHandler method
    will have a URL property referring to a restore image on the network. To use such a restore image, the
    file referred to by the URL property should be downloaded locally (using NSURLSession or similar API). After
    the restore image has been downloaded, a VZMacOSInstaller can be initialized using a URL referring to the
    local file.
 */
+ (void)fetchLatestSupportedWithCompletionHandler:(void (^)(VZMacOSRestoreImage * _Nullable, NSError * _Nullable))completionHandler NS_REFINED_FOR_SWIFT NS_SWIFT_ASYNC_NAME(getter:latestSupported());

/*!
 @abstract Whether this restore image is supported on the current host.
 */
@property (readonly, getter=isSupported) BOOL supported API_AVAILABLE(macos(13.0));

/*!
 @abstract The URL of this restore image.
 @discussion
    If the restore image was loaded using +[VZMacOSRestoreImage loadFileURL:completionHandler:], the value of this property will be a file URL.
    If the restore image was fetched using +[VZMacOSRestoreImage fetchLatestSupportedWithCompletionHandler:],
    the value of this property will be a network URL referring to an installation media file.
 */
@property (readonly, copy) NSURL *URL;

/*!
 @abstract The build version this restore image contains.
 */
@property (readonly, copy) NSString *buildVersion;

/*!
 @abstract The operating system version this restore image contains.
 */
@property (readonly) NSOperatingSystemVersion operatingSystemVersion;

/*!
 @abstract
    The configuration requirements for the most featureful configuration supported by the current host and by this restore image.
 @discussion
    A VZMacOSRestoreImage can contain installation media for multiple Mac hardware models (VZMacHardwareModel). Some of these
    hardware models may not be supported by the current host. The mostFeaturefulSupportedConfiguration property can be used to
    determine the hardware model and configuration requirements that will provide the most complete feature set on the current
    host. If none of the hardware models are supported on the current host, this property is nil.
 */
@property (readonly, nullable, copy) VZMacOSConfigurationRequirements *mostFeaturefulSupportedConfiguration;

@end

NS_ASSUME_NONNULL_END

#endif
