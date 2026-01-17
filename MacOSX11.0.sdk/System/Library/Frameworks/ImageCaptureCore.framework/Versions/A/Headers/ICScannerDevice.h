//------------------------------------------------------------------------------------------------------------------------------
//
//  ICScannerDevice.h
//  ImageCaptureCore
//
//  Copyright (c) 2008 Apple Inc., all rights reserved.
//
//  Best viewed with the following settings: Tab width 4, Indent width 2, Wrap lines, Indent wrapped lines by 3, Page guide 128.
//
//------------------------------------------------------------------------------------------------------------------------------

#pragma once

/*!
  @header ICScannerDevice
    ICScannerDevice is a concrete subclass of ICDevice class. ICDeviceBrowser creates instances of this class. In this release, an instance of ICScannerDevice class is intended to be used by the IKScannerDeviceView object. The IKScannerDeviceView class encapsulates the complexities of setting scan parameters, performing scans and saving the result. The developer should consider using IKScannerDeviceView instead of building their own views using the ICScannerDevice object.
*/

#import <ImageCaptureCore/ICDevice.h>
#import <ImageCaptureCore/ICScannerFunctionalUnits.h>
#import <ImageCaptureCore/ICScannerBandData.h>
#import <ImageCaptureCore/ImageCapturePlatform.h>

NS_ASSUME_NONNULL_BEGIN

//------------------------------------------------------------------------------------------------------------------------------
// Constants used to identify button-press on a device.
/*!
 @const      ICButtonTypeScan
 @abstract   ICButtonTypeScan
 @discussion Indicates that the "Scan" button on the device was pressed.
 */
IMAGECAPTURE_EXTERN NSString *const ICButtonTypeScan IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
 @const      ICButtonTypeMail
 @abstract   ICButtonTypeMail
 @discussion Indicates that the "Mail" button on the device was pressed.
 */
IMAGECAPTURE_EXTERN NSString *const ICButtonTypeMail IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
 @const      ICButtonTypeCopy
 @abstract   ICButtonTypeCopy
 @discussion Indicates that the "Copy" button on the device was pressed.
 */
IMAGECAPTURE_EXTERN NSString *const ICButtonTypeCopy IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
 @const      ICButtonTypeWeb
 @abstract   ICButtonTypeWeb
 @discussion Indicates that the "Web" button on the device was pressed.
 */
IMAGECAPTURE_EXTERN NSString *const ICButtonTypeWeb IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
 @const      ICButtonTypePrint
 @abstract   ICButtonTypePrint
 @discussion Indicates that the "Print" button on the device was pressed.
 */
IMAGECAPTURE_EXTERN NSString *const ICButtonTypePrint IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
 @const      ICButtonTypeTransfer
 @abstract   ICButtonTypeTransfer
 @discussion Indicates that the "Transfer" button on the device was pressed.
 */


IMAGECAPTURE_EXTERN NSString *const ICButtonTypeTransfer IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

//------------------------------------------------------------------------------------------------------------------------------
// Constants used for device status notifications.
/*!
  @const      ICScannerStatusWarmingUp
  @abstract   ICScannerStatusWarmingUp
  @discussion A non-localized notification string to indicate that the scanner is warming up.
*/
IMAGECAPTURE_EXTERN NSString* const ICScannerStatusWarmingUp IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
  @const      ICScannerStatusWarmUpDone
  @abstract   ICScannerStatusWarmUpDone
  @discussion A non-localized notification string to indicate that the scanner has warmed up.
*/
IMAGECAPTURE_EXTERN NSString* const ICScannerStatusWarmUpDone IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
  @const      ICScannerStatusRequestsOverviewScan
  @abstract   ICScannerStatusRequestsOverviewScan
  @discussion A non-localized notification string to indicate that the scanner is requesting an overview scan to be performed.
*/
IMAGECAPTURE_EXTERN NSString* const ICScannerStatusRequestsOverviewScan IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

//-------------------------------------------------------------------------------------------------------------------- Constants
/*!
  @ICScannerTransferMode
  @abstract Transfer mode to be used when transferring scan data from the scanner functional unit.
  @constant ICScannerTransferModeFileBased Save the scan as a file.
  @constant ICScannerTransferModeMemoryBased Transfer the scan as data.
*/

typedef NS_ENUM( NSUInteger, ICScannerTransferMode ) {
    ICScannerTransferModeFileBased   = 0,
    ICScannerTransferModeMemoryBased = 1
} IC_AVAILABLE(macos(10.7)) IC_UNAVAILABLE(ios);

//--------------------------------------------------------------------------------------------------------- Forward Declarations

@class ICScannerDevice;

//------------------------------------------------------------------------------------------------------ ICScannerDeviceDelegate
/*!
  @protocol ICScannerDeviceDelegate <ICDeviceDelegate>
  @abstract A delegate of ICScannerDevice must conform to ICScannerDeviceDelegate protocol.
  @discussion The ICScannerDeviceDelegate protocol inherits from the ICDeviceDelegate protocol.
*/

IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios)
@protocol ICScannerDeviceDelegate <ICDeviceDelegate>

@optional

/*!
  @method scannerDeviceDidBecomeAvailable:
  @abstract This message is sent when another client closes an open session on the scanner.
  @discusson Scanners require exclusive access, only one client can open a session on a scanner. The scanner is available if it does not have a session opened by another client. Attempting to open a session on a scanner that already has an open session for another client will result in an error. A client that wants to open a session on a scanner as soon as it is available should implement this method and send "requestOpenSession" message to scanner object from that method.
*/
- (void)scannerDeviceDidBecomeAvailable:(ICScannerDevice*)scanner IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
  @method scannerDevice:didSelectFunctionalUnit:error:
  @abstract This message is sent when a functional unit is selected on the scanner device.
  @discusson A functional unit is selected immediately after the scanner device is instantiated and in response to "requestSelectFunctionalUnit:" message.
*/
- (void)scannerDevice:(ICScannerDevice*)scanner didSelectFunctionalUnit:(ICScannerFunctionalUnit*)functionalUnit error:(NSError* _Nullable)error IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
  @method scannerDevice:didScanToURL:data:
  @abstract This message is sent when the scanner device receives the requested scan. If selectedFunctionalUnit is a document feeder, then this message will be sent once for each scanned page.
  @discusson This method has been deprecated and superceded by the didScanToURL: method for file based transfer, along with the didScanToBandData: for memory based transfer.
*/
- (void)scannerDevice:(ICScannerDevice*)scanner didScanToURL:(NSURL*)url data:(NSData*)data IC_DEPRECATED("Use didScanToURL: for file URLs and didScanToBandData: for memory based transfers",macos(10.6,10.7)) IC_UNAVAILABLE(ios);

/*!
 @method scannerDevice:didScanToURL:
 @abstract This message is sent when the scanner device receives the requested scan. If selectedFunctionalUnit is a document feeder, then this message will be sent once for each scanned page.
 @discusson This message is sent when the scanner device receives the requested scan. If selectedFunctionalUnit is a document feeder, then this message will be sent once for each scanned page.
 */
- (void)scannerDevice:(ICScannerDevice*)scanner didScanToURL:(NSURL*)url IC_AVAILABLE(macos(10.7)) IC_UNAVAILABLE(ios);

/*!
 @method scannerDevice:didScanToBandData:
 @abstract This message is sent when the scanner device receives the requested scan progress notification and a band of data is sent for each notification received.
 @discusson In memory transfer mode, this will send a band of size that has been selected by the client via the maxMemoryBandSize property.
 */
- (void)scannerDevice:(ICScannerDevice*)scanner didScanToBandData:(ICScannerBandData*)data IC_AVAILABLE(macos(10.7)) IC_UNAVAILABLE(ios);

/*!
  @method scannerDevice:didCompleteOverviewScanWithError:
  @abstract This message is sent after the scanner device completes an overview scan.
  @discusson This message is sent after the scanner device completes an overview scan.
*/
- (void)scannerDevice:(ICScannerDevice*)scanner didCompleteOverviewScanWithError:(NSError* _Nullable)error IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
  @method scannerDevice:didCompleteScanWithError:
  @abstract This message is sent after the scanner device completes a scan.
  @discusson This message is sent after the scanner device completes a scan.
*/
- (void)scannerDevice:(ICScannerDevice*)scanner didCompleteScanWithError:(NSError* _Nullable)error IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

@end

//------------------------------------------------------------------------------------------------------------------------------
/*!
  @class ICScannerDevice
  @abstract ICScannerDevice is a concrete subclass of ICDevice class. ICDeviceBrowser creates instances of this class.
  @discussion In this release, an instance of ICScannerDevice class is intended to be used by the ICScannerDeviceView object. The ICScannerDeviceView class encapsulates the complexities of setting scan parameters, performing scans and saving the result. The developer should consider using ICScannerDeviceView instead of building their own views using the ICScannerDevice object.
*/
__attribute__((visibility("default")))
IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios)
@interface ICScannerDevice : ICDevice
{
@private
    id _scannerProperties;
}

/*!
  @property availableFunctionalUnitTypes
  @abstract ￼An array of functional unit types available on this scanner device. This is an array of NSNumber objects whose values are of type ICScannerFunctionalUnitType.
*/
@property ( readonly ) NSArray<NSNumber*>* availableFunctionalUnitTypes IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
  @property selectedFunctionalUnit
  @abstract ￼The currently selected functional unit on the scanner device.
*/
@property ( readonly ) ICScannerFunctionalUnit* selectedFunctionalUnit IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
  @property transferMode
  @abstract ￼The transfer mode for scanned document.
*/
@property ICScannerTransferMode transferMode IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
 @property maxMemoryBandSize
 @abstract ￼The total maximum band size requested when performing a ICScannerTransferModeMemoryBased.
 
 */
@property UInt32 maxMemoryBandSize IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
  @property downloadsDirectory
  @abstract ￼The downloads directory.
*/
@property ( retain ) NSURL* downloadsDirectory IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
  @property documentName
  @abstract ￼The document name.
*/
@property ( copy ) NSString* documentName IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
  @property documentUTI
  @abstract ￼The document UTI. Currently supported UTIs are: kUTTypeJPEG, kUTTypeJPEG2000, kUTTypeTIFF, kUTTypePNG etc.
*/
@property ( copy ) NSString* documentUTI IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
 @property defaultUsername
 @abstract If the device is protected, instead of prompting the user for a username, this property
        can be set to default to a specific username as a convience.  The value will persist until
        reset by setting it to nil.
 */
@property ( copy ) NSString* defaultUsername IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
 @method requestOpenSessionWithCredentials:
 @abstract This message requests to open a session on the protected device with the authorized username and
           passcode.  If the device reports back a failure of credentials, they can be provided here for the
           launch.
           A client MUST open a session on a device in order to use the device.
 @discussion Make sure the receiver's delegate is set prior to sending this message; otherwise this message will be ignored. This request is completed when the delegate receives a "device:didOpenSessionWithError:" message. No more messages will be sent to the delegate if this request fails.
 */
- (void)requestOpenSessionWithCredentials:(NSString*)username password:(NSString*)password IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
  @method requestSelectFunctionalUnit:delegate:selector:contextInfo:
  @abstract Requests the scanner device to select a functional unit.
  @discussion When this request is completed, the delegate will be notified using the 'scannerDevice:didSelectFunctionalUnit:error:' message.
*/
- (void)requestSelectFunctionalUnit:(ICScannerFunctionalUnitType)type IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
  @method requestOverviewScan
  @abstract Starts an overview scan on selectedFunctionalUnit.
  @discussion When this request is completed, the delegate will be notified using the 'scannerDevice:didCompleteOverviewScanWithError:' message. The content of error returned should be examined to determine if the request completed successfully.
*/
- (void)requestOverviewScan IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
  @method requestScan
  @abstract Starts a scan on selectedFunctionalUnit.
  @discussion When this request is completed, the delegate will be notified using the 'scannerDevice:didCompleteScanWithError:' message. The content of error returned should be examined to determine if the request completed successfully.
*/
- (void)requestScan IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
  @method cancelScan
  @abstract Cancels the current scan operation started by sending a 'requestOverviewScan' or 'requestScan'.
*/
- (void)cancelScan IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

NS_ASSUME_NONNULL_END

@end

//------------------------------------------------------------------------------------------------------------------------------
