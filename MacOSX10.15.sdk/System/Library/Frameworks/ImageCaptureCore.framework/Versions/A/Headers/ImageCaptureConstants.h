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


#define   ICRunLoopMode   @"com.apple.ImageCaptureCore"

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

typedef NS_ENUM(NSInteger)
{
    ICReturnCodeThumbnailOffset           = -21000,
    ICReturnCodeMetadataOffset            = -21050,
    ICReturnCodeDownloadOffset            = -21100,
    ICReturnCodeDeleteOffset              = -21150,
    ICReturnCodeExFATOffset               = -21200,
    ICReturnCodePTPOffset                 = -21250,
    ICReturnCodeSystemOffset              = -21300,
    ICReturnCodeDeviceOffset              = -21350,
    ICReturnCodeDeviceConnection          = -21400,
} ICReturnCodeOffset;


typedef NS_ERROR_ENUM(ICErrorDomain, ICReturnThumbnailErrorCode) {

    /* Item does not have thumbnail available. */
    ICReturnThumbnailNotAvailable               = ICReturnCodeThumbnailOffset,
    /* Item thumbnail request is being serviced. */
    ICReturnThumbnailAlreadyFetching            = ICReturnCodeThumbnailOffset -1,
    /* Item thumbnail request has been canceled. */
    ICReturnThumbnailCanceled                   = ICReturnCodeThumbnailOffset -2,
    /* Item thumbnail request completed with invalid result. */
    ICReturnThumbnailInvalid                    = ICReturnCodeThumbnailOffset -3,
};

typedef NS_ERROR_ENUM(ICErrorDomain, ICReturnMetadataErrorCode) {

    /* Item does not have metadata available. */
    ICReturnMetadataNotAvailable                = ICReturnCodeMetadataOffset,
    /* Item metadata request is being serviced. */
    ICReturnMetadataAlreadyFetching             = ICReturnCodeMetadataOffset -1,
    /* Item metadata request has been canceled. */
    ICReturnMetadataCanceled                    = ICReturnCodeMetadataOffset -2,
    /* Item metadata request completed with invalid result. */
    ICReturnMetadataInvalid                     = ICReturnCodeMetadataOffset -3,
};

typedef NS_ERROR_ENUM(ICErrorDomain, ICReturnConnectionErrorCode) {

    /* Device driver exited without request. */
    ICReturnConnectionDriverExited                  = ICReturnCodeDeviceOffset,
    /* Device closed session without request. */
    ICReturnConnectionClosedSessionSuddenly         = ICReturnCodeDeviceOffset -1,
    /* Device ejected without request. */
    ICReturnConnectionEjectedSuddenly               = ICReturnCodeDeviceOffset -2,
    /* Device reports session is already open. */
    ICReturnConnectionSessionAlreadyOpen            = ICReturnCodeDeviceOffset -3,
    /* Device reports eject has failed. */
    ICReturnConnectionEjectFailed                   = ICReturnCodeDeviceOffset -4,
    /* Failed to open a connection to the device. */
    ICReturnConnectionFailedToOpen                  = ICReturnCodeDeviceConnection,
    /* Failed to open the device. */
    ICReturnConnectionFailedToOpenDevice            = ICReturnCodeDeviceConnection -1,
};

typedef NS_ERROR_ENUM(ICErrorDomain, ICLegacyReturnCode)
{
    /* An error occurred in communication between different components of Image Capture framework. */
    ICLegacyReturnCodeCommunicationErr                = -9900,
    /* The specified device is not found. */
    ICLegacyReturnCodeDeviceNotFoundErr               = -9901,
    /* The specified device is not open. */
    ICLegacyReturnCodeDeviceNotOpenErr                = -9902,
    /* Encountered a corrupt file */
    ICLegacyReturnCodeFileCorruptedErr                = -9903,
    /* There is Pending I/O */
    ICLegacyReturnCodeIOPendingErr                    = -9904,
    /* The specified object is invalid */
    ICLegacyReturnCodeInvalidObjectErr                = -9905,
    /* The specified property is invalid */
    ICLegacyReturnCodeInvalidPropertyErr              = -9906,
    /* The index of the object specified is outside of the available object indexes */
    ICLegacyReturnCodeIndexOutOfRangeErr              = -9907,
    /* Specifi property type not found on object */
    ICLegacyReturnCodePropertyTypeNotFoundErr         = -9908,
    /* Unable to yield device to a secondary process */
    ICLegacyReturnCodeCannotYieldDevice               = -9909,
    /* Device does not support data type */
    ICLegacyReturnCodeDataTypeNotFoundErr             = -9910,
    /* Unable to allocate memory */
    ICLegacyReturnCodeDeviceMemoryAllocationErr       = -9911,
    /* Generic internal error */
    ICLegacyReturnCodeDeviceInternalErr               = -9912,
    /* Generic parameter invalid error */
    ICLegacyReturnCodeDeviceInvalidParamErr           = -9913,
    /* Device already opened */
    ICLegacyReturnCodeDeviceAlreadyOpenErr            = -9914,
    /* Device USB locationID is not valid */
    ICLegacyReturnCodeDeviceLocationIDNotFoundErr     = -9915,
    /* Device FireWire GUID is not valid */
    ICLegacyReturnCodeDeviceGUIDNotFoundErr           = -9916,
    /* Device IOService point is not valid */
    ICLegacyReturnCodeDeviceIOServicePathNotFoundErr  = -9917,
    /* Device is not supported under ICA */
    ICLegacyReturnCodeDeviceUnsupportedErr            = -9918,
    /* Generic framework internal error */
    ICLegacyReturnCodeFrameworkInternalErr            = -9919,
    /* Generic ImageCaptureExtension internal error */
    ICLegacyReturnCodeExtensionInternalErr            = -9920,
    /* Session is invalid */
    ICLegacyReturnCodeInvalidSessionErr               = -9921,
};


typedef NS_ERROR_ENUM(ICErrorDomain, ICReturnCode) {

    /* Operation successful. */
    ICReturnSuccess                               = 0,
    /* An invalid parameter was found. */
    ICReturnInvalidParam                          = -9922,
    /* Communication between different components of Image Capture timed out. */
    ICReturnCommunicationTimedOut                 = -9923,
    /* The scan operation is canceled. */
    ICReturnScanOperationCanceled                 = -9924,
    /*  Scanner is being used by a local user. */
    ICReturnScannerInUseByLocalUser               = -9925,
    /* Scanner is being used by a remote user. */
    ICReturnScannerInUseByRemoteUser              = -9926,
    /* Failed to open a session on a specified device. */
    ICReturnDeviceFailedToOpenSession             = -9927,
    /* Failed to close a session on a specified device. */
    ICReturnDeviceFailedToCloseSession            = -9928,
    /* Failed to select a functional unit on the specified scanner. */
    ICReturnScannerFailedToSelectFunctionalUnit   = -9929,
    /* Overview scan operation failed to complete on the specified scanner. */
    ICReturnScannerFailedToCompleteOverviewScan   = -9930,
    /* Scan operation failed to complete on the specified scanner. */
    ICReturnScannerFailedToCompleteScan           = -9931,
    /* An unsolicited status information was received from a scanner. */
    ICReturnReceivedUnsolicitedScannerStatusInfo  = -9932,
    /* An unsolicited error information was received from a scanner. */
    ICReturnReceivedUnsolicitedScannerErrorInfo   = -9933,
    /* A non-specific error occurred while downloading a file. */
    ICReturnDownloadFailed                        = -9934,
    /* A non-specific error occurred while updownloading a file. */
    ICReturnUploadFailed                          = -9935,
    /* Failed to complete a pass-through (e.g., PTP pass-through) command. */
    ICReturnFailedToCompletePassThroughCommand    = -9936,
    /* A download operation was canceled. */
    ICReturnDownloadCanceled                      = -9937,
    /* Failed to enable tethered-capture on a camera device. */
    ICReturnFailedToEnabeTethering                = -9938,
    /* Failed to disable tethered-capture on a camera device. */
    ICReturnFailedToDisabeTethering               = -9939,
    /* A request to send a message to a device failed. */
    ICReturnFailedToCompleteSendMessageRequest    = -9940,
    /* A request to delete files failed. */
    ICReturnDeleteFilesFailed                     = -9941,
    /*  A request to delete files was canceled. */
    ICReturnDeleteFilesCanceled                   = -9942,
    /* The device is locked with a passcode. Its contents cannot be seen unless it is unlocked. */
    ICReturnDeviceIsPasscodeLocked                = -9943,
    /* Failed to take a tethered-capture picture on a camera device. */
    ICReturnDeviceFailedToTakePicture             = -9944,
    /* Failed to open session because software to communicate with the device is not installed. */
    ICReturnDeviceSoftwareNotInstalled            = -9945,
    /*  Failed to open session because software to communicate with the device is being installed. */
    ICReturnDeviceSoftwareIsBeingInstalled        = -9946,
    /* Software installation for the device has completed successfully. */
    ICReturnDeviceSoftwareInstallationCompleted   = -9947,
    /* Software installation for the device has been canceled. */
    ICReturnDeviceSoftwareInstallationCanceled    = -9948,
    /* Software installation for the device failed. */
    ICReturnDeviceSoftwareInstallationFailed      = -9949,
    /* Software for the device is not available from Apple. */
    ICReturnDeviceSoftwareNotAvailable            = -9950,
    /* A pairing request for a Apple Device failed. */
    ICReturnDeviceCouldNotPair                    = -9951,
    /* A unpairing request for a Apple Device failed. */
    ICReturnDeviceCouldNotUnpair                  = -9952,
    /* The device reports credentials are required to open the device. */
    ICReturnDeviceNeedsCredentials                = -9953,
    /* The device is currently enumerating assets. */
    ICReturnDeviceIsBusyEnumerating               = -9954,
    /* The device has experienced a general failure. */
    ICReturnDeviceCommandGeneralFailure           = -9955,
    /* Failed to complete a data transaction. */
    ICReturnDeviceFailedToCompleteTransfer        = -9956,
    /* Failed to send data. */
    ICReturnDeviceFailedToSendData                = -9957,
    /* Session is not open. */
    ICReturnSessionNotOpened                      = -9958,
    /* EXFAT volume is invalid, and cannot be enumerated. */
    ICReturnExFATVolumeInvalid                  = ICReturnCodeExFATOffset,
    /* Multierror */
    ICReturnMultiErrorDictionary                = -30000,
};

#define ICReturnDeviceIsAccessRestrictedAppleDevice ICReturnDeviceIsPasscodeLocked

//------------------------------------------------------------------------------------------------------------------------------
