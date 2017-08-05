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

CF_ASSUME_NONNULL_BEGIN

//------------------------------------------------------------------------------------------------------------------------------
// Constants used for device status notifications.
/*!
    @const      ICScannerStatusWarmingUp
    @abstract   ICScannerStatusWarmingUp
    @discussion A non-localized notification string to indicate that the scanner is warming up.
*/
extern NSString *const ICScannerStatusWarmingUp;

/*!
    @const      ICScannerStatusWarmUpDone
    @abstract   ICScannerStatusWarmUpDone
    @discussion A non-localized notification string to indicate that the scanner has warmed up.
*/
extern NSString *const ICScannerStatusWarmUpDone;

/*!
    @const      ICScannerStatusRequestsOverviewScan
    @abstract   ICScannerStatusRequestsOverviewScan
    @discussion A non-localized notification string to indicate that the scanner is requesting an overview scan to be performed.
*/
extern NSString *const ICScannerStatusRequestsOverviewScan;

//-------------------------------------------------------------------------------------------------------------------- Constants
/*!
  @ICScannerTransferMode
  @abstract Transfer mode to be used when transferring scan data from the scanner functional unit.
  @constant ICScannerTransferModeFileBased Save the scan as a file.
  @constant ICScannerTransferModeMemoryBased Transfer the scan as data.
*/

typedef NS_ENUM(NSUInteger, ICScannerTransferMode)
{
    ICScannerTransferModeFileBased    = 0,
    ICScannerTransferModeMemoryBased  = 1
    
};

//--------------------------------------------------------------------------------------------------------- Forward Declarations

@class ICScannerDevice;

//------------------------------------------------------------------------------------------------------ ICScannerDeviceDelegate
/*! 
  @protocol ICScannerDeviceDelegate <ICDeviceDelegate>
  @abstract A delegate of ICScannerDevice must conform to ICScannerDeviceDelegate protocol.
  @discussion The ICScannerDeviceDelegate protocol inherits from the ICDeviceDelegate protocol.
*/

@protocol ICScannerDeviceDelegate  <ICDeviceDelegate>

@optional

/*! 
  @method scannerDeviceDidBecomeAvailable:
  @abstract This message is sent when another client closes an open session on the scanner.
  @discusson Scanners require exclusive access, only one client can open a session on a scanner. The scanner is available if it does not have a session opened by another client. Attempting to open a session on a scanner that already has an open session for another client will result in an error. A client that wants to open a session on a scanner as soon as it is available should implement this method and send "requestOpenSession" message to scanner object from that method.
*/
- (void)scannerDeviceDidBecomeAvailable:( ICScannerDevice*)scanner;

/*! 
  @method scannerDevice:didSelectFunctionalUnit:error:
  @abstract This message is sent when a functional unit is selected on the scanner device.
  @discusson A functional unit is selected immediately after the scanner device is instantiated and in response to "requestSelectFunctionalUnit:" message.
*/
- (void)scannerDevice:( ICScannerDevice*)scanner didSelectFunctionalUnit:( ICScannerFunctionalUnit*)functionalUnit error:(nullable NSError*)error;

/*! 
  @method scannerDevice:didScanToURL:data:
  @abstract This message is sent when the scanner device receives the requested scan. If selectedFunctionalUnit is a document feeder, then this message will be sent once for each scanned page.
  @discusson This method has been deprecated and superceded by the didScanToURL: method for file based transfer, along with the didScanToBandData: for memory based transfer.
*/
- (void)scannerDevice:( ICScannerDevice*)scanner didScanToURL:( NSURL*)url data:( NSData*)data NS_DEPRECATED(10_6, 10_7, NA, NA);

/*! 
 @method scannerDevice:didScanToURL:
 @abstract This message is sent when the scanner device receives the requested scan. If selectedFunctionalUnit is a document feeder, then this message will be sent once for each scanned page.
 @discusson This message is sent when the scanner device receives the requested scan. If selectedFunctionalUnit is a document feeder, then this message will be sent once for each scanned page.
 */
- (void)scannerDevice:( ICScannerDevice*)scanner didScanToURL:( NSURL*)url;

/*! 
 @method scannerDevice:didScanToBandData:
 @abstract This message is sent when the scanner device receives the requested scan progress notification and a band of data is sent for each notification received.
 @discusson In memory transfer mode, this will send a band of size that has been selected by the client via the maxMemoryBandSize property.
 */
- (void)scannerDevice:( ICScannerDevice*)scanner didScanToBandData:( ICScannerBandData*)data;

/*! 
  @method scannerDevice:didCompleteOverviewScanWithError:
  @abstract This message is sent after the scanner device completes an overview scan.
  @discusson This message is sent after the scanner device completes an overview scan.
*/
- (void)scannerDevice:( ICScannerDevice*)scanner didCompleteOverviewScanWithError:(nullable NSError*)error;

/*! 
  @method scannerDevice:didCompleteScanWithError:
  @abstract This message is sent after the scanner device completes a scan.
  @discusson This message is sent after the scanner device completes a scan.
*/
- (void)scannerDevice:( ICScannerDevice*)scanner didCompleteScanWithError:(nullable NSError*)error;

@end

//------------------------------------------------------------------------------------------------------------------------------
/*! 
  @class ICScannerDevice
  @abstract ICScannerDevice is a concrete subclass of ICDevice class. ICDeviceBrowser creates instances of this class.
  @discussion In this release, an instance of ICScannerDevice class is intended to be used by the ICScannerDeviceView object. The ICScannerDeviceView class encapsulates the complexities of setting scan parameters, performing scans and saving the result. The developer should consider using ICScannerDeviceView instead of building their own views using the ICScannerDevice object.
*/


@interface ICScannerDevice : ICDevice
{
@private
    id _scannerProperties;
}

/*!
    @property availableFunctionalUnitTypes
    @abstract ￼An array of functional unit types available on this scanner device. This is an array of NSNumber objects whose values are of type ICScannerFunctionalUnitType.

*/
@property(readonly) NSArray<NSNumber*>*                    availableFunctionalUnitTypes;

/*!
    @property selectedFunctionalUnit
    @abstract ￼The currently selected functional unit on the scanner device.

*/
@property(readonly) ICScannerFunctionalUnit*    selectedFunctionalUnit;

/*!
    @property transferMode
    @abstract ￼The transfer mode for scanned document.

*/
@property           ICScannerTransferMode       transferMode;

/*!
 @property maxMemoryBandSize
 @abstract ￼The total maximum band size requested when performing a ICScannerTransferModeMemoryBased.
 
 */
@property           UInt32                      maxMemoryBandSize;

/*!
    @property downloadsDirectory
    @abstract ￼The downloads directory.

*/
@property(retain)   NSURL*             downloadsDirectory;

/*!
    @property documentName
    @abstract ￼The document name.

*/
@property(copy)     NSString*                   documentName;

/*!
    @property documentUTI
    @abstract ￼The document UTI. Currently supported UTIs are: kUTTypeJPEG, kUTTypeJPEG2000, kUTTypeTIFF, kUTTypePNG etc.

*/
@property(copy)     NSString*                   documentUTI;

/*! 
  @method requestSelectFunctionalUnit:delegate:selector:contextInfo:
  @abstract Requests the scanner device to select a functional unit.
  @discussion When this request is completed, the delegate will be notified using the 'scannerDevice:didSelectFunctionalUnit:error:' message.
*/
- (void)requestSelectFunctionalUnit:(ICScannerFunctionalUnitType)type;

/*! 
  @method requestOverviewScan
  @abstract Starts an overview scan on selectedFunctionalUnit.
  @discussion When this request is completed, the delegate will be notified using the 'scannerDevice:didCompleteOverviewScanWithError:' message. The content of error returned should be examined to determine if the request completed successfully.
*/
- (void)requestOverviewScan;

/*! 
  @method requestScan
  @abstract Starts a scan on selectedFunctionalUnit.
  @discussion When this request is completed, the delegate will be notified using the 'scannerDevice:didCompleteScanWithError:' message. The content of error returned should be examined to determine if the request completed successfully.
*/
- (void)requestScan;

/*! 
  @method cancelScan
  @abstract Cancels the current scan operation started by sending a 'requestOverviewScan' or 'requestScan'.
*/
- (void)cancelScan;

NS_ASSUME_NONNULL_END

@end

//------------------------------------------------------------------------------------------------------------------------------
