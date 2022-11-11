//
//  VZDiskImageStorageDeviceAttachment.h
//  Virtualization
//
//  Copyright © 2019-2021 Apple Inc. All rights reserved.
//

#import <Virtualization/VZStorageDeviceAttachment.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @enum VZDiskImageCachingMode
 @abstract Whether the host caches disk image data.
 @constant VZDiskImageCachingModeAutomatic   Virtualization determines automatically whether to enable data caching.
 @constant VZDiskImageCachingModeUncached    Data caching is disabled.
 @constant VZDiskImageCachingModeCached      Data caching is enabled.
 */
typedef NS_ENUM(NSInteger, VZDiskImageCachingMode) {
    VZDiskImageCachingModeAutomatic = 0,
    VZDiskImageCachingModeUncached = 1,
    VZDiskImageCachingModeCached = 2,
} API_AVAILABLE(macos(12.0));

typedef NS_ENUM(NSInteger, VZDiskImageSynchronizationMode) {
    /*!
     The data is synchronized to the permanent storage holding the disk image.
     No synchronized data is lost on panic or loss of power.
     */
    VZDiskImageSynchronizationModeFull = 1,

    /*!
     Synchronize the data to the drive.

     This mode synchronizes the data with the drive, but does not ensure the data is moved from the disk's internal cache
     to permanent storage.

     This is a best-effort mode with the same guarantees as the fsync() system call.
     */
    VZDiskImageSynchronizationModeFsync,

    /*!
     Do not synchronize the data with the permanent storage.
     This option does not guarantee data integrity if any error condition occurs such as disk full on the host,
     panic, power loss, etc.

     This mode is useful when a virtual machine is only run once to perform a task to completion or failure.
     In that case, the disk image cannot safely be reused on failure.

     Using this mode may result in improved performance since no synchronization with the underlying storage is necessary.
     */
    VZDiskImageSynchronizationModeNone,
} API_AVAILABLE(macos(12.0));

/*!
 @abstract Storage device attachment using a disk image to implement the storage.
 @discussion
    This storage device attachment uses a disk image on the host file system as the drive of the storage device.

    Only raw data disk images are supported.
 @see VZVirtioBlockDeviceConfiguration
 */
VZ_EXPORT API_AVAILABLE(macos(11.0))
@interface VZDiskImageStorageDeviceAttachment : VZStorageDeviceAttachment

/*!
 @abstract Initialize the attachment from a local file url.
 @param url Local file URL to the disk image in RAW format.
 @param readOnly If YES, the device attachment is read-only, otherwise the device can write data to the disk image.
 @param error If not nil, assigned with the error if the initialization failed.
 @return A newly initialized VZDiskImageStorageDeviceAttachment. If an error was encountered returns @c nil, and @c error contains the error.
 */
- (nullable instancetype)initWithURL:(NSURL *)url readOnly:(BOOL)readOnly error:(NSError **)error NS_DESIGNATED_INITIALIZER;

/*!
 @abstract Initialize the attachment from a local file url.
 @param url Local file URL to the disk image in RAW format.
 @param readOnly If YES, the device attachment is read-only, otherwise the device can write data to the disk image.
 @param cachingMode Whether host data caching is enabled for the disk image.
 @param synchronizationMode How the disk image synchronizes with the underlying storage when the guest operating system flushes data.
 @param error If not nil, assigned with the error if the initialization failed.
 @return A newly initialized VZDiskImageStorageDeviceAttachment. If an error was encountered returns @c nil, and @c error contains the error.
 */
- (nullable instancetype)initWithURL:(NSURL *)url readOnly:(BOOL)readOnly cachingMode:(VZDiskImageCachingMode)cachingMode synchronizationMode:(VZDiskImageSynchronizationMode)synchronizationMode error:(NSError **)error NS_DESIGNATED_INITIALIZER API_AVAILABLE(macos(12.0));

/*!
 @abstract URL of the underlying disk image.
*/
@property (readonly, copy) NSURL *URL;

/*!
 @abstract Whether the underlying disk image is read-only.
*/
@property (readonly, getter=isReadOnly) BOOL readOnly;

/*!
 @abstract How disk image data is cached by the host.
*/
@property (readonly) VZDiskImageCachingMode cachingMode API_AVAILABLE(macos(12.0));

/*!
 @abstract The mode in which the disk image synchronizes data with the underlying storage device.
*/
@property (readonly) VZDiskImageSynchronizationMode synchronizationMode API_AVAILABLE(macos(12.0));

@end

NS_ASSUME_NONNULL_END
