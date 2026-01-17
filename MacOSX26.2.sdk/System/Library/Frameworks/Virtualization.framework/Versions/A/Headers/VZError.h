//
//  VZError.h
//  Virtualization
//
//  Copyright © 2019-2024 Apple Inc. All rights reserved.
//

#import <Virtualization/VZDefines.h>

VZ_EXPORT NSErrorDomain const VZErrorDomain API_AVAILABLE(macos(11.0));

/*!
 @enum VZErrorCode
 @abstract
    Error type returned by the Virtualization framework.
    The NSError domain is VZErrorDomain, the code is one of the VZErrorCode constants.

    The virtualization framework can also report errors from other domains when the error originates from a lower level component.

 @constant VZErrorInternal
    Internal error such as the virtual machine unexpectedly stopping.
 @constant VZErrorInvalidVirtualMachineConfiguration
    Invalid machine configuration.
 @constant VZErrorInvalidVirtualMachineState
    API used with a machine in the wrong state (e.g. interacting with a machine before it is running).
 @constant VZErrorInvalidVirtualMachineStateTransition
    Invalid change of state (e.g. pausing a virtual machine that is not started).
 @constant VZErrorInvalidDiskImage
    Unrecognized disk image format or invalid disk image.
 @constant VZErrorVirtualMachineLimitExceeded
    The running virtual machine limit was exceeded.
 @constant VZErrorNetworkError
    Network error occurred.
 @constant VZErrorOutOfDiskSpace
    Machine ran out of disk space.
 @constant VZErrorOperationCancelled
    The operation was cancelled.
 @constant VZErrorNotSupported
    The operation is not supported.
 @constant VZErrorSave
    The save operation failed.
 @constant VZErrorRestore
    The restore operation failed.
 @constant VZErrorRestoreImageCatalogLoadFailed
    The restore image catalog failed to load.
 @constant VZErrorInvalidRestoreImageCatalog
    The restore image catalog is invalid.
 @constant VZErrorNoSupportedRestoreImagesInCatalog
    The restore image catalog has no supported restore images.
 @constant VZErrorRestoreImageLoadFailed
    The restore image failed to load.
 @constant VZErrorInvalidRestoreImage
    The restore image is invalid.
 @constant VZErrorInstallationRequiresUpdate
    A software update is required to complete the installation.
 @constant VZErrorInstallationFailed
    An error occurred during installation.
 @constant VZErrorNetworkBlockDeviceNegotiationFailed
    The connection or the negotiation with the NBD server failed.
 @constant VZErrorNetworkBlockDeviceDisconnected
    The NBD client is disconnected from the server.
 @constant VZErrorUSBControllerNotFound
    Controller not found.
 @constant VZErrorDeviceAlreadyAttached
    Device is already attached.
 @constant VZErrorDeviceInitializationFailure
    Device initialization failure.
 @constant VZErrorDeviceNotFound
    Device not found.
 */
typedef NS_ERROR_ENUM(VZErrorDomain, VZErrorCode) {
    VZErrorInternal NS_SWIFT_NAME(internalError) = 1,
    VZErrorInvalidVirtualMachineConfiguration = 2,
    VZErrorInvalidVirtualMachineState = 3,
    VZErrorInvalidVirtualMachineStateTransition = 4,
    VZErrorInvalidDiskImage = 5,
    VZErrorVirtualMachineLimitExceeded API_AVAILABLE(macos(12.0)) = 6,
    VZErrorNetworkError API_AVAILABLE(macos(13.0)) = 7,
    VZErrorOutOfDiskSpace API_AVAILABLE(macos(13.0)) = 8,
    VZErrorOperationCancelled API_AVAILABLE(macos(13.0)) = 9,
    VZErrorNotSupported API_AVAILABLE(macos(13.0)) = 10,
    VZErrorSave API_AVAILABLE(macos(14.0)) = 11,
    VZErrorRestore API_AVAILABLE(macos(14.0)) = 12,

    /* macOS installation errors. */
    VZErrorRestoreImageCatalogLoadFailed API_AVAILABLE(macos(13.0)) = 10001,
    VZErrorInvalidRestoreImageCatalog API_AVAILABLE(macos(13.0)) = 10002,
    VZErrorNoSupportedRestoreImagesInCatalog API_AVAILABLE(macos(13.0)) = 10003,
    VZErrorRestoreImageLoadFailed API_AVAILABLE(macos(13.0)) = 10004,
    VZErrorInvalidRestoreImage API_AVAILABLE(macos(13.0)) = 10005,
    VZErrorInstallationRequiresUpdate API_AVAILABLE(macos(13.0)) = 10006,
    VZErrorInstallationFailed API_AVAILABLE(macos(13.0)) = 10007,

    /* Network Block Device errors. */
    VZErrorNetworkBlockDeviceNegotiationFailed API_AVAILABLE(macos(14.0)) = 20001,
    VZErrorNetworkBlockDeviceDisconnected API_AVAILABLE(macos(14.0)) = 20002,

    /* USB device hot-plug errors. */
    VZErrorUSBControllerNotFound API_AVAILABLE(macos(15.0)) = 30001,
    VZErrorDeviceAlreadyAttached API_AVAILABLE(macos(15.0)) = 30002,
    VZErrorDeviceInitializationFailure API_AVAILABLE(macos(15.0)) = 30003,
    VZErrorDeviceNotFound API_AVAILABLE(macos(15.0)) = 30004,
} API_AVAILABLE(macos(11.0));
