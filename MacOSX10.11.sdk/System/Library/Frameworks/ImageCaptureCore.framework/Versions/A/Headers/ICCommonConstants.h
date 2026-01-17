//------------------------------------------------------------------------------------------------------------------------------
//
//  ICCommonConstants.h
//  ImageCaptureCore
//
//  Copyright (c) 2008 Apple, Inc., all rights reserved.
//
//  Best viewed with the following settings: Tab width 4, Indent width 2, Wrap lines, Indent wrapped lines by 3, Page guide 128.
//
//------------------------------------------------------------------------------------------------------------------------------

#pragma once

#import <Foundation/Foundation.h>

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

/*!
    @ICReturnCode
    @discussion
        Definition of codes returned by APIs in ImageCaptureCore framework
    @constant ICReturnSuccess
        Operation successful.
    @constant ICReturnInvalidParam
        An invalid parameter was found.
    @constant ICReturnCommunicationTimedOut
        Communication between different components of Image Capture timed out.
    @constant ICReturnScanOperationCanceled
        The scan operation is canceled.
    @constant ICReturnScannerInUseByLocalUser
        Scanner is being used by a local user.
    @constant ICReturnScannerInUseByRemoteUser
        Scanner is being used by a remote user.
    @constant ICReturnDeviceFailedToOpenSession
        Failed to open a session on a specified device.
    @constant ICReturnDeviceFailedToCloseSession
        Failed to close a session on a specified device.
    @constant ICReturnScannerFailedToSelectFunctionalUnit
        Failed to select a functional unit on the specified scanner.
    @constant ICReturnScannerFailedToCompleteOverviewScan
        Overview scan operation failed to complete on the specified scanner.
    @constant ICReturnScannerFailedToCompleteScan
        Scan operation failed to complete on the specified scanner.
    @constant ICReturnReceivedUnsolicitedScannerStatusInfo
        An unsolicited status information was received from a scanner.
    @constant ICReturnReceivedUnsolicitedScannerErrorInfo
        An unsolicited error information was received from a scanner.
    @constant ICReturnDownloadFailed
        A non-specific error occurred while downloading a file.
    @constant ICReturnUploadFailed
        A non-specific error occurred while updownloading a file.
    @constant ICReturnFailedToCompletePassThroughCommand
        Failed to complete a pass-through (e.g., PTP pass-through) command.
    @constant ICReturnDownloadCanceled
        A download operation was canceled.
    @constant ICReturnFailedToEnabeTethering
        Failed to enable tethered-capture on a camera device.
    @constant ICReturnFailedToDisabeTethering
        Failed to disable tethered-capture on a camera device.
    @constant ICReturnFailedToCompleteSendMessageRequest
        A request to send a message to a device failed.
    @constant ICReturnDeleteFilesFailed
        A request to delete files failed.
    @constant ICReturnDeleteFilesCanceled
        A request to delete files was canceled.
    @constant ICReturnDeviceIsPasscodeLocked
        The device is locked with a passcode. Its contents cannot be seen unless it is unlocked.
    @constant ICReturnDeviceFailedToTakePicture
        Failed to take a tethered-capture picture on a camera device.
    @constant ICReturnDeviceSoftwareNotInstalled
        Failed to open session because software to communicate with the device is not installed.
    @constant ICReturnDeviceSoftwareIsBeingInstalled
        Failed to open session because software to communicate with the device is being installed.
    @constant ICReturnDeviceSoftwareInstallationCompleted
        Software installation for the device has completed successfully.
    @constant ICReturnDeviceSoftwareInstallationCanceled
        Software installation for the device has been canceled.
    @constant ICReturnDeviceSoftwareInstallationFailed
        Software installation for the device failed.
    @constant ICReturnDeviceSoftwareNotAvailable
        Software for the device is not available from Apple.
*/
typedef NS_ENUM( NSInteger, ICReturnCode )
{
    ICReturnSuccess                               = 0,
    ICReturnInvalidParam                          = -9922,
    ICReturnCommunicationTimedOut                 = -9923,
    ICReturnScanOperationCanceled                 = -9924,
    ICReturnScannerInUseByLocalUser               = -9925,
    ICReturnScannerInUseByRemoteUser              = -9926,
    ICReturnDeviceFailedToOpenSession             = -9927,
    ICReturnDeviceFailedToCloseSession            = -9928,
    ICReturnScannerFailedToSelectFunctionalUnit   = -9929,
    ICReturnScannerFailedToCompleteOverviewScan   = -9930,
    ICReturnScannerFailedToCompleteScan           = -9931,
    ICReturnReceivedUnsolicitedScannerStatusInfo  = -9932,
    ICReturnReceivedUnsolicitedScannerErrorInfo   = -9933,
    ICReturnDownloadFailed                        = -9934,
    ICReturnUploadFailed                          = -9935,
    ICReturnFailedToCompletePassThroughCommand    = -9936,
    ICReturnDownloadCanceled                      = -9937,
    ICReturnFailedToEnabeTethering                = -9938,
    ICReturnFailedToDisabeTethering               = -9939,
    ICReturnFailedToCompleteSendMessageRequest    = -9940,
    ICReturnDeleteFilesFailed                     = -9941,
    ICReturnDeleteFilesCanceled                   = -9942,
    ICReturnDeviceIsPasscodeLocked                = -9943,
    ICReturnDeviceFailedToTakePicture             = -9944,
    ICReturnDeviceSoftwareNotInstalled            = -9945,
    ICReturnDeviceSoftwareIsBeingInstalled        = -9946,
    ICReturnDeviceSoftwareInstallationCompleted   = -9947,
    ICReturnDeviceSoftwareInstallationCanceled    = -9948,
    ICReturnDeviceSoftwareInstallationFailed      = -9949,
    ICReturnDeviceSoftwareNotAvailable            = -9950,
    ICReturnDeviceCouldNotPair                    = -9951,
    ICReturnDeviceCouldNotUnpair                  = -9952,
    ICReturnDeviceNeedsCredentials                = -9953,
};

////------------------------------------------------------------------------------------------------------------------------------
