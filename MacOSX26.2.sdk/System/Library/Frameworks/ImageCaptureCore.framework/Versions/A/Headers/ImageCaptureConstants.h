//------------------------------------------------------------------------------------------------------------------------------
//
//  ImageCaptureConstants.h
//  ImageCaptureCore
//
//  Copyright (c) 2008 Apple, Inc., all rights reserved.
//
//  Best viewed with the following settings: Tab width 4, Indent width 2, Wrap lines, Indent wrapped lines by 3, Page guide 128.
//
//------------------------------------------------------------------------------------------------------------------------------

#pragma once

#import <Foundation/Foundation.h>
#import <ImageCaptureCore/ImageCapturePlatform.h>

IMAGECAPTURE_EXTERN NSString* const ICRunLoopMode IC_DEPRECATED("ICRunLoopMode has been deprecated and may break in future releases.", macos(10.4, 10.15)) IC_UNAVAILABLE(ios);

//------------------------------------------------------------------------------------------------------------------------------
/*!
  @ICEXIFOrientationType
  @abstract Type representing EXIF Orientation tag value
  @discussion The meaning of this value is defined by the EXIF specification. Here is what the letter F would look like if it were tagged correctly and displayed by a program that ignores the orientation tag (thus showing the stored image):

               1             2             3             4

            8888888       8888888            88       88
            88                 88            88       88
            8888             8888          8888       8888
            88                 88            88       88
            88                 88       8888888       8888888

               5             6             7             8

            8888888888    88                    88    8888888888
            88  88        88  88            88  88        88  88
            88            8888888888    8888888888            88


*/
extern NSErrorDomain const ICErrorDomain API_AVAILABLE(macos(10.15), ios(13.0));

typedef NS_ENUM(NSUInteger, ICEXIFOrientationType)
{
    ICEXIFOrientation1  = 1,    // Normal
    ICEXIFOrientation2  = 2,    // Flipped horizontally
    ICEXIFOrientation3  = 3,    // Rotated 180°
    ICEXIFOrientation4  = 4,    // Flipped vertically
    ICEXIFOrientation5  = 5,    // Rotated 90° CCW and flipped vertically
    ICEXIFOrientation6  = 6,    // Rotated 90° CCW
    ICEXIFOrientation7  = 7,    // Rotated 90° CW and flipped vertically
    ICEXIFOrientation8  = 8     // Rotated 90° CW
};

//------------------------------------------------------------------------------------------------------------------------------

typedef NS_ENUM (NSInteger)
{
    ICReturnCodeThumbnailOffset = -21000,
    ICReturnCodeMetadataOffset = -21050,
    ICReturnCodeDownloadOffset = -21100,
    ICReturnCodeDeleteOffset = -21150,
    ICReturnCodeExFATOffset = -21200,
    ICReturnCodePTPOffset = -21250,
    ICReturnCodeSystemOffset = -21300,
    ICReturnCodeDeviceOffset = -21350,
    ICReturnCodeDeviceConnection = -21400,
    ICReturnCodeObjectOffset = -21450,
} ICReturnCodeOffset;

typedef NS_ERROR_ENUM (ICErrorDomain, ICReturnThumbnailErrorCode)
{
    ICReturnThumbnailNotAvailable = -21000,                     // Item does not have thumbnail available.
    ICReturnThumbnailAlreadyFetching = -20999,                  // Item thumbnail request is being serviced.
    ICReturnThumbnailCanceled = -20098,                         // Item thumbnail request has been canceled.
    ICReturnThumbnailInvalid = -20097,                          // Item thumbnail request completed with invalid result.
};

typedef NS_ERROR_ENUM (ICErrorDomain, ICReturnMetadataErrorCode)
{
    ICReturnMetadataNotAvailable = -20150,                      // Item does not have metadata available.
    ICReturnMetadataAlreadyFetching = -20149,                   // Item metadata request is being serviced.
    ICReturnMetadataCanceled = -20148,                          // Item metadata request has been canceled.
    ICReturnMetadataInvalid = -20147,                           // Item metadata request completed with invalid result.
};

typedef NS_ERROR_ENUM (ICErrorDomain, ICReturnConnectionErrorCode)
{
    ICReturnConnectionDriverExited = -21350,                    // Device driver exited without request.
    ICReturnConnectionClosedSessionSuddenly = -21349,           // Device closed session without request.
    ICReturnConnectionEjectedSuddenly = -21348,                 // Device ejected without request.
    ICReturnConnectionSessionAlreadyOpen = -21347,              // Device reports session is already open.
    ICReturnConnectionEjectFailed = -21346,                     // Device reports eject has failed.
    ICReturnConnectionFailedToOpen = -21345,                    // Failed to open a connection to the device.
    ICReturnConnectionFailedToOpenDevice = -21344,              // Failed to open the device.
    ICReturnConnectionNotAuthorizedToOpenDevice = -21343,       // Not authorized to open device.
};

typedef NS_ERROR_ENUM (ICErrorDomain, ICReturnPTPDeviceErrorCode)
{
    ICReturnPTPFailedToSendCommand = -21250,                    // PTP Command failed to send
    ICReturnPTPNotAuthorizedToSendCommand = -21249,             // PTP Command not authorized
};

typedef NS_ERROR_ENUM (ICErrorDomain, ICReturnDownloadErrorCode)
{
    ICReturnDownloadPathInvalid = -21100,                       // Destination path supplied is invalid
    ICReturnDownloadFileWritable = -21099,                      // Destination file is not writable
};

typedef NS_ERROR_ENUM (ICErrorDomain, ICLegacyReturnCode)
{
    ICLegacyReturnCodeCommunicationErr = -9900,                 // An communication error occurred.
    ICLegacyReturnCodeDeviceNotFoundErr = -9901,                // The specified device is not found.
    ICLegacyReturnCodeDeviceNotOpenErr = -9902,                 // The specified device is not open.
    ICLegacyReturnCodeFileCorruptedErr = -9903,                 // Encountered a corrupt file
    ICLegacyReturnCodeIOPendingErr = -9904,                     // There is Pending I/O
    ICLegacyReturnCodeInvalidObjectErr = -9905,                 // The specified object is invalid
    ICLegacyReturnCodeInvalidPropertyErr = -9906,               // The specified property is invalid
    ICLegacyReturnCodeIndexOutOfRangeErr = -9907,               // The index of the object specified is outside of the available object indexes
    ICLegacyReturnCodePropertyTypeNotFoundErr = -9908,          // Specific property type not found on object
    ICLegacyReturnCodeCannotYieldDevice = -9909,                // Unable to yield device to a secondary process
    ICLegacyReturnCodeDataTypeNotFoundErr = -9910,              // Device does not support data type
    ICLegacyReturnCodeDeviceMemoryAllocationErr = -9911,        // Unable to allocate memory
    ICLegacyReturnCodeDeviceInternalErr = -9912,                // Generic internal error
    ICLegacyReturnCodeDeviceInvalidParamErr = -9913,            // Generic parameter invalid error
    ICLegacyReturnCodeDeviceAlreadyOpenErr = -9914,             // Device already opened
    ICLegacyReturnCodeDeviceLocationIDNotFoundErr = -9915,      // Device USB locationID is not valid
    ICLegacyReturnCodeDeviceGUIDNotFoundErr = -9916,            // Device FireWire GUID is not valid
    ICLegacyReturnCodeDeviceIOServicePathNotFoundErr = -9917,   // Device IOService point is not valid
    ICLegacyReturnCodeDeviceUnsupportedErr = -9918,             // Device is not supported under ICA
    ICLegacyReturnCodeFrameworkInternalErr = -9919,             // Generic framework internal error
    ICLegacyReturnCodeExtensionInternalErr = -9920,             // Generic ImageCaptureExtension internal error
    ICLegacyReturnCodeInvalidSessionErr = -9921,                // Session is invalid
};

typedef NS_ERROR_ENUM (ICErrorDomain, ICReturnCode)
{
    ICReturnSuccess = 0,                                        // Operation successful.
    ICReturnInvalidParam = -9922,                               // An invalid parameter was found.
    ICReturnCommunicationTimedOut = -9923,                      // Communication between different components of Image Capture timed out.
    ICReturnScanOperationCanceled = -9924,                      // The scan operation is canceled.
    ICReturnScannerInUseByLocalUser = -9925,                    // Scanner is being used by a local user.
    ICReturnScannerInUseByRemoteUser = -9926,                   // Scanner is being used by a remote user.
    ICReturnDeviceFailedToOpenSession = -9927,                  // Failed to open a session on a specified device.
    ICReturnDeviceFailedToCloseSession = -9928,                 // Failed to close a session on a specified device.
    ICReturnScannerFailedToSelectFunctionalUnit = -9929,        // Failed to select a functional unit on the specified scanner.
    ICReturnScannerFailedToCompleteOverviewScan = -9930,        // Overview scan operation failed to complete on the specified scanner.
    ICReturnScannerFailedToCompleteScan = -9931,                // Scan operation failed to complete on the specified scanner.
    ICReturnReceivedUnsolicitedScannerStatusInfo = -9932,       // An unsolicited status information was received from a scanner.
    ICReturnReceivedUnsolicitedScannerErrorInfo = -9933,        // An unsolicited error information was received from a scanner.
    ICReturnDownloadFailed = -9934,                             // A non-specific error occurred while downloading a file.
    ICReturnUploadFailed = -9935,                               // A non-specific error occurred while updownloading a file.
    ICReturnFailedToCompletePassThroughCommand = -9936,         // Failed to complete a pass-through (e.g., PTP pass-through) command.
    ICReturnDownloadCanceled = -9937,                           // A download operation was canceled.
    ICReturnFailedToEnabeTethering = -9938,                     // Failed to enable tethered-capture on a camera device.
    ICReturnFailedToDisabeTethering = -9939,                    // Failed to disable tethered-capture on a camera device.
    ICReturnFailedToCompleteSendMessageRequest = -9940,         // A request to send a message to a device failed.
    ICReturnDeleteFilesFailed = -9941,                          // A request to delete files failed.
    ICReturnDeleteFilesCanceled = -9942,                        // A request to delete files was canceled.
    ICReturnDeviceIsPasscodeLocked = -9943,                     // The device is locked with a passcode. Its contents cannot be seen unless it is unlocked.
    ICReturnDeviceFailedToTakePicture = -9944,                  // Failed to take a tethered-capture picture on a camera device.
    ICReturnDeviceSoftwareNotInstalled = -9945,                 // Failed to open session because software to communicate with the device is not installed.
    ICReturnDeviceSoftwareIsBeingInstalled = -9946,             // Failed to open session because software to communicate with the device is being installed.
    ICReturnDeviceSoftwareInstallationCompleted = -9947,        // Software installation for the device has completed successfully.
    ICReturnDeviceSoftwareInstallationCanceled = -9948,         // Software installation for the device has been canceled.
    ICReturnDeviceSoftwareInstallationFailed = -9949,           // Software installation for the device failed.
    ICReturnDeviceSoftwareNotAvailable = -9950,                 // Software for the device is not available from Apple.
    ICReturnDeviceCouldNotPair = -9951,                         // A pairing request for a Apple Device failed.
    ICReturnDeviceCouldNotUnpair = -9952,                       // A unpairing request for a Apple Device failed.
    ICReturnDeviceNeedsCredentials = -9953,                     // The device reports credentials are required to open the device.
    ICReturnDeviceIsBusyEnumerating = -9954,                    // The device is currently enumerating assets.
    ICReturnDeviceCommandGeneralFailure = -9955,                // The device has experienced a general failure.
    ICReturnDeviceFailedToCompleteTransfer = -9956,             // Failed to complete a data transaction.
    ICReturnDeviceFailedToSendData = -9957,                     // Failed to send data.
    ICReturnSessionNotOpened = -9958,                           // Session is not open.
    ICReturnExFATVolumeInvalid = 21200,                         // EXFAT volume is invalid, and cannot be enumerated.
    ICReturnMultiErrorDictionary = -30000,                      // Multierror
};

typedef NS_ERROR_ENUM(ICErrorDomain, ICReturnObjectErrorCode)
{
    ICReturnCodeObjectDoesNotExist = -21450,                    // Object does not exist.
    ICReturnCodeObjectDataOffsetInvalid = -21449,               // Object data offset invalid.
    ICReturnCodeObjectCouldNotBeRead = -21448,                  // Object could not be read
    ICReturnCodeObjectDataEmpty = -21447,                       // Object data empty.
    ICReturnCodeObjectDataRequestTooLarge = -21446,             // Requested transfer size is greater than the current maximum allowed.
};

#define ICReturnDeviceIsAccessRestrictedAppleDevice ICReturnDeviceIsPasscodeLocked
#define ICReturnFailedToEnableTethering ICReturnFailedToEnabeTethering
#define ICReturnFailedToDisableTethering ICReturnFailedToDisabeTethering

//------------------------------------------------------------------------------------------------------------------------------
