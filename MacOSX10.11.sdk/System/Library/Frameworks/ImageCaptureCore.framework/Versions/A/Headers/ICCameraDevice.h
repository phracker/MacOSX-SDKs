//------------------------------------------------------------------------------------------------------------------------------
//
//  ICCameraDevice.h
//  ImageCaptureCore
//
//  Copyright (c) 2008 Apple Inc., all rights reserved.
//
//  Best viewed with the following settings: Tab width 4, Indent width 2, Wrap lines, Indent wrapped lines by 3, Page guide 128.
//
//------------------------------------------------------------------------------------------------------------------------------

#pragma once

/*!
    @header ICCameraDevice
    ICCameraDevice is a concrete subclass of ICDevice class. ICDeviceBrowser creates instances of this class.
*/

#import <ImageCaptureCore/ICDevice.h>
#import <ImageCaptureCore/ICCameraItem.h>

CF_ASSUME_NONNULL_BEGIN

//------------------------------------------------------------------------------------------------------------------------------
// Constants used to describe capabilities of a camera

/*!
    @const      ICCameraDeviceCanTakePicture
    @abstract   ICCameraDeviceCanTakePicture
    @discussion Indicates that the camera can capture a picture while it is connected, if the client sends a 'requestTakePicture' message to it.
*/
extern NSString *const ICCameraDeviceCanTakePicture;

/*!
    @const      ICCameraDeviceCanTakePictureUsingShutterReleaseOnCamera
    @abstract   ICCameraDeviceCanTakePictureUsingShutterReleaseOnCamera
    @discussion Indicates that the camera can capture a picture while it is connected, if the user presses the shutter release on the camera.
*/
extern NSString *const ICCameraDeviceCanTakePictureUsingShutterReleaseOnCamera;

/*!
    @const      ICCameraDeviceCanDeleteOneFile
    @abstract   ICCameraDeviceCanDeleteOneFile
    @discussion Indicates that the camera can delete a file at a time while it is connected.
*/
extern NSString *const ICCameraDeviceCanDeleteOneFile;

/*!
    @const      ICCameraDeviceCanDeleteAllFiles
    @abstract   ICCameraDeviceCanDeleteAllFiles
    @discussion Indicates that the camera can delete all files in a single operation while it is connected. 
*/
extern NSString *const ICCameraDeviceCanDeleteAllFiles;

/*!
    @const      ICCameraDeviceCanSyncClock
    @abstract   ICCameraDeviceCanSyncClock
    @discussion Indicates that the camera can synchronize its date and time with that of the host computer.
*/
extern NSString *const ICCameraDeviceCanSyncClock;

/*!
    @const      ICCameraDeviceCanReceiveFile
    @abstract   ICCameraDeviceCanReceiveFile
    @discussion Indicates that the host can upload files to the camera.
*/
extern NSString *const ICCameraDeviceCanReceiveFile;

/*!
    @const      ICCameraDeviceCanAcceptPTPCommands
    @abstract   ICCameraDeviceCanAcceptPTPCommands
    @discussion Indicates that the camera can accept PTP commands.
*/
extern NSString *const ICCameraDeviceCanAcceptPTPCommands;

/*!
 @const      ICCameraDeviceSupportsFastPTP
 @abstract   ICCameraDeviceSupportsFastPTP
 @discussion Indicates that the camera supports fast PTP commands.
 */
extern NSString *const ICCameraDeviceSupportsFastPTP;

//------------------------------------------------------------------------------------------------------------------------------
// Allowed keys in the options dictionary used when downloading a file from the camera

/*!
    @const      ICDownloadsDirectoryURL
    @abstract   ICDownloadsDirectoryURL
    @discussion The value for this key should be an NSURL object referencing a writable directory. The downloaded files will be saved in that directory.
*/
extern NSString *const ICDownloadsDirectoryURL;

/*!
    @const      ICSaveAsFilename
    @abstract   ICSaveAsFilename
    @discussion The value for this key should be an NSString object containing the name to be used for the downloaded file.
*/
extern NSString *const ICSaveAsFilename;

/*!
    @const      ICSavedFilename
    @abstract   ICSavedFilename
    @discussion The value for this key will be an NSString object containing the actual name of the saved file. The options dictionary returned in didDownloadFile:error:options:contextInfo: will have this key. 
*/
extern NSString *const ICSavedFilename;

/*!
    @const      ICSavedAncillaryFiles
    @abstract   ICSavedAncillaryFiles
    @discussion The value for this key will be an NSArray object containing names of files associated with the primary file that is downloaded. The options dictionary returned in didDownloadFile:error:options:contextInfo: may have this key.
*/
extern NSString *const ICSavedAncillaryFiles;

/*!
    @const      ICOverwrite
    @abstract   ICOverwrite
    @discussion The value for this key should be an NSNumber object representing a boolean value. If this value is YES, the downloaded file will overwrite an existing file with the same name and extension.
*/
extern NSString *const ICOverwrite;

/*!
    @const      ICDeleteAfterSuccessfulDownload
    @abstract   ICDeleteAfterSuccessfulDownload
    @discussion The value for this key should be an NSNumber object representing a boolean value. If this value is YES, the file will be deleted from the device after it is succcessfully downloaded.
*/
extern NSString *const ICDeleteAfterSuccessfulDownload;

/*!
    @const      ICDownloadSidecarFiles
    @abstract   ICDownloadSidecarFiles
    @discussion The value for this key should be an NSNumber object representing a boolean value. If this value is YES, all sidecar files will be downloaded along with the media file.
*/
extern NSString *const ICDownloadSidecarFiles;

//--------------------------------------------------------------------------------------------------------- Forward Declarations

@class ICCameraDevice;

//------------------------------------------------------------------------------------------------------- ICCameraDeviceDelegate
/*! 
  @protocol ICCameraDeviceDelegate  <ICDeviceDelegate>
  @abstract A delegate of ICCameraDevice must conform to ICCameraDeviceDelegate protocol.
  @discussion The ICCameraDeviceDelegate protocol inherits from the ICDeviceDelegate protocol.
*/

@protocol ICCameraDeviceDelegate  <ICDeviceDelegate>

@optional

/*! 
  @method cameraDevice:didAddItem:
  @abstract This message is sent when an object is added to the device.
  @discussion The object may be an instance of ICCameraFolder or ICCameraFile class.
*/
- (void)cameraDevice:( ICCameraDevice*)camera didAddItem:( ICCameraItem*)item;

/*! 
 @method cameraDevice:didAddItems:
 @abstract This message is sent when an object or objects are added to the device.  Instead of
 receive one message per object, an NSArray of objects is sent.
 @discussion The objects may be instances of ICCameraFolder or ICCameraFile class.
 */
- (void)cameraDevice:( ICCameraDevice*)camera didAddItems:( NSArray<ICCameraItem*>*)items;

/*! 
  @method cameraDevice:didRemoveItem:
  @abstract This message is sent when an object is removed from the device.
  @discussion The object may be an instance of ICCameraFolder or ICCameraFile class.
*/
- (void)cameraDevice:( ICCameraDevice*)camera didRemoveItem:( ICCameraItem*)item;

/*! 
  @method cameraDevice:didRemoveItems:
  @abstract This message is sent when an object or objects are removed from the device.
  @discussion The objects may be instances of ICCameraFolder or ICCameraFile class. This method supercedes 'cameraDevice:didRemoveItem:' method described above.
*/
- (void)cameraDevice:( ICCameraDevice*)camera didRemoveItems:( NSArray<ICCameraItem*>*) items;

/*! 
 @method cameraDevice:didRenameItems:
 @abstract This message is sent when an object or objects are renamed on the device.
 @discussion The objects may be instances of ICCameraFolder or ICCameraFile class. 
 */
- (void)cameraDevice:( ICCameraDevice*)camera didRenameItems:( NSArray<ICCameraItem*> *) items;

/*! 
  @method cameraDevice:didCompleteDeleteFilesWithError:
  @abstract This message is sent after the camera device completes a delete operation initiated by sending a 'requestDeleteFiles:' message to that device.
  @discusson This message is sent after the camera device completes a delete operation initiated by sending a 'requestDeleteFiles:' message to that device.
*/
- (void)cameraDevice:( ICCameraDevice*)scanner didCompleteDeleteFilesWithError:(nullable NSError*)error;

/*! 
  @method cameraDeviceDidChangeCapability:
  @abstract This message is sent when the capability of a device changes.
  @discussion This usually happens when the device module takes control or yields control of the device.
*/
- (void)cameraDeviceDidChangeCapability:( ICCameraDevice*)camera;

/*! 
  @method cameraDevice:didReceiveThumbnailForItem:
  @abstract This message is sent when the thumbnail requested for an item on a device is available.
*/
- (void)cameraDevice:( ICCameraDevice*)camera didReceiveThumbnailForItem:( ICCameraItem*)item;

/*! 
  @method cameraDevice:didReceiveMetadataForItem:
  @abstract This message is sent when the metadata requested for an item on a device is available.
*/
- (void)cameraDevice:( ICCameraDevice*)camera didReceiveMetadataForItem:( ICCameraItem*)item;

/*! 
  @method cameraDevice:didReceivePTPEvent:
  @abstract This message is sent to the delegate to convey a PTP event.
*/
- (void)cameraDevice:( ICCameraDevice*)camera didReceivePTPEvent:( NSData*)eventData;

/*! 
  @method deviceDidBecomeReadyWithCompleteContentCatalog:
  @abstract This message is sent when the camera device is done enumerating its content and is ready to receive requests.
  @discussion A session must be opened on the device in order to enumerate its content and make it ready to receive requests.
*/
- (void)deviceDidBecomeReadyWithCompleteContentCatalog:( ICDevice*)device;

/*!
 @method cameraDevice:shouldGetThumbnailOfItem:
 @abstract This message is sent when the camera device is about to execute queued requests for the thumbnail of a specific item.
 If the request is no longer wanted, eg: the item is no longer displayed on the screen, the client can return NO and abort sending
 a request down to the camera device, speeding up the exection queue.
 */
- (BOOL)cameraDevice:( ICCameraDevice*)cameraDevice shouldGetThumbnailOfItem:( ICCameraItem*)item;

/*!
 @abstract This message is sent when the camera device is about to execute queued requests for the metadata of a specific item.
 If the request is no longer wanted, eg: the item is no longer displayed on the screen, the client can return NO and abort sending
 a request down to the camera device, speeding up the execution queue.
 */
- (BOOL)cameraDevice:( ICCameraDevice*)cameraDevice shouldGetMetadataOfItem:( ICCameraItem*)item;

@end

//----------------------------------------------------------------------------------------------- ICCameraDeviceDownloadDelegate
/*! 
  @protocol ICCameraDeviceDownloadDelegate <NSObject>
  @abstract The object passed in as 'downloadDelegate' in the 'requestDownloadFile:options:downloadDelegate:didDownloadSelector:contextInfo:' message must conform to ICCameraDeviceDownloadDelegate protocol.
*/

@protocol ICCameraDeviceDownloadDelegate <NSObject>

@optional

/*! 
  @method didDownloadFile:error:options:contextInfo:
  @abstract This message is sent to the delegate when the requested download operation is complete.
*/
- (void)didDownloadFile:( ICCameraFile*)file error:(nullable NSError*)error options:(nullable NSDictionary<NSString*,id>*)options contextInfo:(nullable void*)contextInfo;

/*! 
  @method didReceiveDownloadProgressForFile:downloadedBytes:maxBytes:
  @abstract This message is sent to the delegate to provide status of the download operation.
*/

- (void)didReceiveDownloadProgressForFile:( ICCameraFile*)file downloadedBytes:(off_t)downloadedBytes maxBytes:(off_t)maxBytes;

@end

//--------------------------------------------------------------------------------------------------------------- ICCameraDevice
/*!
    @class ICCameraDevice
    @abstract ICCameraDevice is a concrete subclass of ICDevice class. ICDeviceBrowser creates instances of this class.
*/

@interface ICCameraDevice : ICDevice
{
@private
    id _cameraProperties;
}

/*!
    @property batteryLevelAvailable
    @abstract Indicates if the device has reported battery charge level￼.

*/
@property(readonly)   BOOL            batteryLevelAvailable;

/*!
    @property batteryLevel
    @abstract ￼Indicates the battery charge level. Its value ranges from 0 to 100.

*/
@property(readonly)   NSUInteger      batteryLevel;

/*!
    @property contentCatalogPercentCompleted
    @abstract ￼Indicates the percentage of content cataloging completed on the device. Its value ranges from 0 to 100.

*/
@property(readonly)   NSUInteger      contentCatalogPercentCompleted;

/*!
    @property contents
    @abstract ￼Contents of the camera. The structure of the elements in this array will reflect the folder structure of the storage reported by the camera. Each item in this array will correspond to a storage on the camera.

*/
@property(readonly, nullable)   NSArray<ICCameraItem*>*        contents;

/*!
    @property mediaFiles
    @abstract ￼The property mediaFiles represents all image, movie and audio files on the camera. These files are returned as a single array without regard to the folder hierarchy used to store these files on the camera.

*/
@property(readonly, nullable)   NSArray<ICCameraItem*>*        mediaFiles;

/*!
    @property timeOffset
    @abstract Indicates the time offset, in seconds, between the camera's clock and the computer's clock￼. This value is positive if the camera's clock is ahead of the computer's clock. This property should be ignored if the camera's capabilities property does not contain ICCameraDeviceCanSyncClock.

*/
@property(readonly)   NSTimeInterval  timeOffset;

/*!
    @property isAccessRestrictedAppleDevice
    @abstract Set to YES if the device is made by Apple and is pass-coded locked and connected to an untrusted host.

*/
@property(readonly)   BOOL            isAccessRestrictedAppleDevice;

/*!
    @property mountPoint
    @abstract Filesystem mount point for a device with transportType of ICTransportTypeMassStorage. This will be NULL for all other devices.

*/
@property(readonly, nullable)   NSString*       mountPoint;

/*!
    @property tetheredCaptureEnabled
    @abstract This property is set to YES when tethered capture is enabled on the device. 
    @discussion Use 'requestEnableTethering' and 'requestDisableTethering' to enable or disable tethered capture on the device.

*/
@property             BOOL            tetheredCaptureEnabled;

/*! 
  @method filesOfType:
  @abstract This method returns an array of files on the camera of type fileType. 
  @discussion The fileType string is one of the following Uniform Type Identifier strings: kUTTypeImage, kUTTypeMovie, kUTTypeAudio, or kUTTypeData.
*/
- ( NSArray<NSString*>*)filesOfType:( NSString*)fileUTType;

/*! 
  @method requestSyncClock
  @abstract Synchronize camera's clock with the computer's clock. You should send this request only if the camera has the 'ICCameraDeviceCanSyncClock' capability.
*/
- (void)requestSyncClock;

/*! 
  @method requestEnableTethering
  @abstract Send this message to enable tethered capture on the camera device if the camera has the 'ICCameraDeviceCanTakePicture' capability.
*/
- (void)requestEnableTethering;

/*! 
  @method requestDisableTethering
  @abstract Send this message to disable tethered capture on the camera device if the camera has the 'ICCameraDeviceCanTakePicture' capability and if your process has already sent a 'requestEnableTethering' to it.
*/
- (void)requestDisableTethering;

/*! 
  @method requestTakePicture
  @abstract Capture a new image using the camera, the camera capabilities include 'ICCameraDeviceCanTakePicture'.
  @discussion You MUST send 'requestEnableTethering' message to the camera before sending 'requestTakePicture' message.
*/
- (void)requestTakePicture;

/*! 
  @method requestDeleteFiles
  @abstract Deletes files.
*/
- (void)requestDeleteFiles:( NSArray<ICCameraItem*>*)files;

/*! 
  @method cancelDelete
  @abstract Cancels the current delete operation started by sending a 'requestDeleteFiles:'.
*/
- (void)cancelDelete;

/*! 
  @method requestDownloadFile:options:downloadDelegate:didDownloadSelector:contextInfo:
  @abstract Download a file from the camera. Please refer to the top of this header for information about the options.
  @discussion The downloadDelegate passed must not be nil. When this request is completed, the didDownloadSelector of the downloadDelegate object is called.The didDownloadSelector should have the same signature as: - (void)didDownloadFile:(ICCameraFile*)file error:(NSError*)error options:(NSDictionary*)options contextInfo:(void*)contextInfo. The content of error returned should be examined to determine if the request completed successfully. Please see discussion above for 'ICCameraDeviceDownloadDelegate' protocol for more information.
*/
- (void)requestDownloadFile:( ICCameraFile*)file options:(nullable NSDictionary<NSString*,id>*)options downloadDelegate:( id<ICCameraDeviceDownloadDelegate>)downloadDelegate didDownloadSelector:( SEL)selector contextInfo:(nullable void*)contextInfo;

/*! 
  @method cancelDownload
  @abstract Cancels the current download operation.
*/
- (void)cancelDownload;

/*! 
  @method requestUploadFile:options:uploadDelegate:didUploadSelector:contextInfo:
  @abstract Upload a file at fileURL to the camera. The options dictionary is not used in this version.
  @discussion The uploadDelegate passed must not be nil. When this request is completed, the didUploadSelector of the uploadDelegate object is called. The didUploadSelector should have the same signature as: - (void)didUploadFile:(NSURL*)fileURL error:(NSError*)error contextInfo:(void*)contextInfo. The content of error returned should be examined to determine if the request completed successfully.
*/
- (void)requestUploadFile:( NSURL*)fileURL options:(nullable NSDictionary<NSString*,id>*)options uploadDelegate:( id)uploadDelegate didUploadSelector:( SEL)selector contextInfo:(nullable void*)contextInfo;

/*! 
  @method requestReadDataFromFile:atOffset:length:readDelegate:didReadDataSelector:contextInfo:
  @abstract This method asynchronously reads data of a specified length from a specified offset.
  @discussion The readDelegate passed must not be nil. When this request is completed, the didReadDataSelector of the readDelegate object is called. The didReadDataSelector should have the same signature as: - (void)didReadData:(NSData*)data fromFile:(ICCameraFile*)file error:(NSError*)error contextInfo:(void*)contextInfo. The content of error returned should be examined to determine if the request completed successfully.
*/
- (void)requestReadDataFromFile:( ICCameraFile*)file atOffset:(off_t)offset length:(off_t)length readDelegate:( id)readDelegate didReadDataSelector:( SEL)selector contextInfo:(nullable void*)contextInfo;

/*! 
  @method requestSendPTPCommand:outData:sendCommandDelegate:sendCommandDelegate:contextInfo:
  @abstract This method asynchronously sends a PTP command to a camera.
  @discussion This should be sent only if the 'capabilities' property contains 'ICCameraDeviceCanAcceptPTPCommands'. All PTP cameras have this capability. The response to this command will be delivered using didSendCommandSelector of sendCommandDelegate. The didSendCommandSelector should have the same signature as: - (void)didSendPTPCommand:(NSData*)command inData:(NSData*)data response:(NSData*)response error:(NSError*)error contextInfo:(void*)contextInfo. The content of error returned should be examined to determine if the request completed successfully.
*/
- (void)requestSendPTPCommand:( NSData*)command outData:( NSData*)data sendCommandDelegate:( id)sendCommandDelegate didSendCommandSelector:( SEL)selector contextInfo:(nullable void*)contextInfo;

CF_ASSUME_NONNULL_END

@end

//------------------------------------------------------------------------------------------------------------------------------

