//
//  VZMacOSInstaller.h
//  Virtualization
//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#ifdef __arm64__

#import <Virtualization/VZDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class VZVirtualMachine;
@class VZMacOSRestoreImage;

/*!
 @abstract VZMacOSInstaller is used to install macOS on the specified virtual machine.
 @discussion
    A VZMacOSInstaller object must be initialized with a VZVirtualMachine and a file URL referring to a macOS restore image.
    The following code example shows how VZMacOSInstaller is used.

    <pre>@textblock

    // VZMacOSInstaller must be called with a URL corresponding to a local file. We need a place to store the restore image we download.
    NSURL *localRestoreImageURL = ...;

    // Load the latest restore image.
    [VZMacOSRestoreImage fetchLatestSupportedWithCompletionHandler:^(VZMacOSRestoreImage *restoreImage, NSError *error) {
        if (error) {
            // Handle the error.
            abort();
        }

        // VZMacOSInstaller must be called with a URL corresponding to a local file. Since restoreImage came from
        // fetchLatestSupportedWithCompletionHandler, its URL property refers to a restore image on the network.
        // Download the restore image to the local filesystem.
        [[NSURLSession sharedSession] downloadTaskWithURL:restoreImage.URL completionHandler:^(NSURL *location, NSURLResponse *response, NSError *error) {
            if (error) {
                // Handle the error.
                abort();
            }
            if (![[NSFileManager defaultManager] moveItemAtURL:location toURL:localRestoreImageURL error:&error]) {
                // Handle the error.
                abort();
            }
            dispatch_async(dispatch_get_main_queue(), ^{
                // Since this restore image came from -[VZMacOSRestoreImage fetchLatestSupportedWithCompletionHandler:], mostFeaturefulSupportedConfiguration should not be nil.
                VZMacOSConfigurationRequirements *configurationRequirements = restoreImage.mostFeaturefulSupportedConfiguration;

                // Construct a VZVirtualMachineConfiguration that satisfies the configuration requirements.
                VZVirtualMachineConfiguration *configuration = [[VZVirtualMachineConfiguration alloc] init];
                configuration.bootLoader = [[VZMacOSBootLoader alloc] init];
                configuration.platform = [[VZMacPlatformConfiguration alloc] init];

                // The following are minimum values; you can use larger values if desired.
                configuration.CPUCount = configurationRequirements.minimumSupportedCPUCount;
                configuration.memorySize = configurationRequirements.minimumSupportedMemorySize;

                // Set other configuration properties as necessary.
                // ...

                assert([configuration validateWithError:nil]);

                VZVirtualMachine *virtualMachine = [[VZVirtualMachine alloc] initWithConfiguration:configuration];
                VZMacOSInstaller *installer = [[VZMacOSInstaller alloc] initWithVirtualMachine:virtualMachine restoreImageURL:localRestoreImageURL];
                [installer installWithCompletionHandler:^(NSError *error) {
                    if (error) {
                        // Handle the error.
                        abort();
                    } else {
                        // Installation was successful.
                    }
                }];

                // Observe progress using installer.progress object.
            });
        }];
    }];

    @/textblock</pre>
 @seealso VZVirtualMachine
 @seealso VZMacOSRestoreImage
*/
VZ_EXPORT API_AVAILABLE(macos(12.0))
@interface VZMacOSInstaller : NSObject

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/*!
 @abstract Initialize a VZMacOSInstaller object.
 @param virtualMachine The virtual machine that the operating system will be installed onto.
 @param restoreImageFileURL A file URL indicating the macOS restore image to install.
 @discussion
    The virtual machine platform must be macOS and the restore image URL must be a file URL referring to a file on disk or an exception will be raised.
    This method must be called on the virtual machine's queue.
 */
- (instancetype)initWithVirtualMachine:(VZVirtualMachine *)virtualMachine restoreImageURL:(NSURL *)restoreImageFileURL NS_SWIFT_NAME(init(virtualMachine:restoringFromImageAt:)) NS_DESIGNATED_INITIALIZER;

/*!
 @abstract Start installing macOS.
 @param completionHandler Block called after installation has successfully completed or has failed.
    The error parameter passed to the block is nil if installation was successful. The block will be invoked on the virtual machine's queue.
 @discussion
    This method starts the installation process. The virtual machine must be in a stopped state. During the installation operation, pausing or stopping
    the virtual machine will result in undefined behavior.
    If installation is started on the same VZMacOSInstaller object more than once, an exception will be raised.
    This method must be called on the virtual machine's queue.
 */
- (void)installWithCompletionHandler:(void(^)(NSError * _Nullable))completionHandler NS_REFINED_FOR_SWIFT NS_SWIFT_ASYNC_NAME(install());

/*!
 @abstract An NSProgress object that can be used to observe or cancel installation.
 @discussion If the progress object is cancelled before installation is started, an exception will be raised.
 */
@property (readonly) NSProgress *progress;

/*!
 @abstract The virtual machine that this installer was initialized with.
 */
@property (readonly) VZVirtualMachine *virtualMachine;

/*!
 @abstract The restore image URL that this installer was initialized with.
 */
@property (readonly) NSURL *restoreImageURL;

@end

NS_ASSUME_NONNULL_END

#endif
