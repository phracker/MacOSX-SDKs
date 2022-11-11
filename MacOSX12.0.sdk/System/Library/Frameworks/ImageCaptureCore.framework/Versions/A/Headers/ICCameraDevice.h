//------------------------------------------------------------------------------------------------------------------------------
//
//  ICCameraDevice.h
//  ImageCaptureCore
//
//  Copyright (c) 2008-2019 Apple Inc., all rights reserved.
//
//  Best viewed with the following settings: Tab width 4, Indent width 2, Wrap lines, Indent wrapped lines by 3, Page guide 128.
//
//------------------------------------------------------------------------------------------------------------------------------

#pragma once

#import <ImageCaptureCore/ImageCapturePlatform.h>

#import <ImageCaptureCore/ICCameraItem.h>
#import <ImageCaptureCore/ICDevice.h>
#import <CoreGraphics/CoreGraphics.h>

@class ICCameraFile;

CF_ASSUME_NONNULL_BEGIN

@protocol ICCameraDeviceDownloadDelegate;

//------------------------------------------------------------------------------------------------------------------------------
// Constants used to describe capabilities of a camera

/*!
  @const      ICCameraDeviceCanTakePicture
  @discussion Indicates that the camera can capture a picture while it is connected, if the client sends a 'requestTakePicture' message to it.
 */
IMAGECAPTURE_EXTERN ICDeviceCapability const ICCameraDeviceCanTakePicture IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
  @const      ICCameraDeviceCanTakePictureUsingShutterReleaseOnCamera
  @discussion Indicates that the camera can capture a picture while it is connected, if the user presses the shutter release on the camera.
 */
IMAGECAPTURE_EXTERN ICDeviceCapability const ICCameraDeviceCanTakePictureUsingShutterReleaseOnCamera IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
  @const      ICCameraDeviceCanDeleteOneFile
  @discussion Indicates that the camera can delete a file at a time while it is connected.
 */
IMAGECAPTURE_EXTERN ICDeviceCapability const ICCameraDeviceCanDeleteOneFile IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
  @const      ICCameraDeviceCanDeleteAllFiles
  @discussion Indicates that the camera can delete all files in a single operation while it is connected.
 */
IMAGECAPTURE_EXTERN ICDeviceCapability const ICCameraDeviceCanDeleteAllFiles IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
  @const      ICCameraDeviceCanSyncClock
  @discussion Indicates that the camera can synchronize its date and time with that of the host computer.
 */
IMAGECAPTURE_EXTERN ICDeviceCapability const ICCameraDeviceCanSyncClock IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
  @const      ICCameraDeviceCanReceiveFile
  @discussion Indicates that the host can upload files to the camera.
 */
IMAGECAPTURE_EXTERN ICDeviceCapability const ICCameraDeviceCanReceiveFile IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
  @const      ICCameraDeviceCanAcceptPTPCommands
  @discussion Indicates that the camera can accept PTP commands.
 */
IMAGECAPTURE_EXTERN ICDeviceCapability const ICCameraDeviceCanAcceptPTPCommands IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
 @const      ICCameraDeviceSupportsHEIF
 @discussion Indicates that the camera supports HEIF transcoding, and can change the presentation of converted assets and original assets on the fly.
 */
IMAGECAPTURE_EXTERN ICDeviceCapability const ICCameraDeviceSupportsHEIF IC_AVAILABLE(macos(10.11), ios(14.0));

typedef NSString* ICUploadOption NS_TYPED_ENUM IC_AVAILABLE (macos (10.4), ios (13.0));

typedef NSString* ICDeleteResult NS_TYPED_ENUM IC_AVAILABLE (macos (10.15), ios (13.0));

/*!
  @const      ICDeleteSuccessful
  @discussion The value for this key should be an NSArray<ICCameraItem*>*
 */
IMAGECAPTURE_EXTERN ICDeleteResult const ICDeleteSuccessful IC_AVAILABLE(macos(10.15), ios(13.0));

/*!
  @const      ICDeleteCanceled
  @discussion The value for this key should be an NSArray<ICCameraItem*>*
 */
IMAGECAPTURE_EXTERN ICDeleteResult const ICDeleteCanceled IC_AVAILABLE(macos(10.15), ios(13.0));

/*!
  @const      ICDeleteFailed
  @discussion The value for this key should be an NSArray<ICCameraItem*>*
 */
IMAGECAPTURE_EXTERN ICDeleteResult const ICDeleteFailed IC_AVAILABLE(macos(10.15), ios(13.0));

typedef NSString* ICDeleteError NS_TYPED_ENUM IC_AVAILABLE (macos (10.15), ios (13.0));

/*!
  @const      ICDeleteErrorReadOnly
  @discussion The value for this key should be an ICCameraItem*
 */
IMAGECAPTURE_EXTERN ICDeleteError const ICDeleteErrorReadOnly IC_AVAILABLE(macos(10.15), ios(13.0));

/*!
  @const      ICDeleteErrorFileMissing
  @discussion The value for this key should be an ICCameraItem*
 */
IMAGECAPTURE_EXTERN ICDeleteError const ICDeleteErrorFileMissing IC_AVAILABLE(macos(10.15), ios(13.0));

/*!
  @const      ICDeleteErrorDeviceMissing
  @discussion The value for this key should be an ICCameraItem*
 */
IMAGECAPTURE_EXTERN ICDeleteError const ICDeleteErrorDeviceMissing IC_AVAILABLE(macos(10.15), ios(13.0));

/*!
  @const      ICDeleteErrorDeviceMissing
  @discussion The value for this key should be an ICCameraItem*
 */
IMAGECAPTURE_EXTERN ICDeleteError const ICDeleteErrorCanceled IC_AVAILABLE(macos(10.15), ios(13.0));

//-------------------------------------------------------------------------------------------------------------------- Constants
/*!
  @ICMediaPresentation
  @abstract
  @constant ICMediaPresentation controls the display of either transcoded or original assets, if the device supports transcoding.
  @constant ICMediaPresentationConvertedAssets sets the device presentation view to display transcoded assets only.
  @constant ICMediaPresentationConvertedAssets sets the device presentation view to display original assets only.
*/

typedef NS_ENUM( NSUInteger, ICMediaPresentation ) {
    ICMediaPresentationConvertedAssets   = 1,
    ICMediaPresentationOriginalAssets    = 2,
} IC_AVAILABLE(macos(10.11), ios(14.0));

//--------------------------------------------------------------------------------------------------------- Forward Declarations

@protocol ICDeviceDelegate;

//--------------------------------------------------------------------------------------------------------------- ICCameraDevice
/*!
  @class ICCameraDevice
  @abstract ICCameraDevice is a concrete subclass of ICDevice class. ICDeviceBrowser creates instances of this class.
 */
IC_AVAILABLE(macos(10.4), ios(13.0))
@interface ICCameraDevice : ICDevice

/*!
  @property contentCatalogPercentCompleted
  @abstract ￼Indicates the percentage of content cataloging completed on the device. Its value ranges from 0 to 100.
 */
@property (nonatomic, readonly) NSUInteger contentCatalogPercentCompleted IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
  @property contents
  @abstract ￼Contents of the camera. The structure of the elements in this array will reflect the folder structure of the storage reported by the camera. Each item in this array will correspond to a storage on the camera.
 */
@property (nonatomic, readonly, nullable) NSArray<ICCameraItem*>* contents IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
  @property mediaFiles
  @abstract ￼The property mediaFiles represents all image, movie and audio files on the camera. These files are returned as a single array without regard to the folder hierarchy used to store these files on the camera.
 */
@property (nonatomic, readonly, nullable) NSArray<ICCameraItem*>* mediaFiles IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
  @property ejectable
  @abstract ￼Indicates whether the device can be 'soft' removed or disconnected.
 */
@property (nonatomic, readonly, getter = isEjectable) BOOL ejectable IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
  @property locked
  @abstract ￼Indicates whether the device is locked.  A locked device does not allow for deletion of any asset.
 */
@property (nonatomic, readonly, getter = isLocked) BOOL locked IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
  @property accessRestrictedAppleDevice
  @abstract Set to YES if the device is made by Apple and is pass-coded locked and connected to an untrusted host.
 */
@property (nonatomic, readonly, getter = isAccessRestrictedAppleDevice) BOOL accessRestrictedAppleDevice IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
  @property iCloudPhotosEnabled
  @abstract Set to YES if the device is made by Apple and is pass-coded locked and connected to an untrusted host.
 */
@property (nonatomic, readonly) BOOL iCloudPhotosEnabled IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
  @property mountPoint
  @abstract Filesystem mount point for a device with transportType of ICTransportTypeMassStorage. This will be NULL for all other devices.
 */
@property (nonatomic, readonly, nullable) NSString* mountPoint IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
  @property mediaPresentation
  @abstract The media presentation describes the visible assets from a device that may contain multiple formats of each media asset.  The asigngments are of the type ICMediaPresentation enumeration.  This property is available only if the capability ICCameraDeviceSupportsHEIF is  present.

  @discussion A device supporting this capability can specify the
  following presentations:

  ICMediaPresentationConverted - The default behavior for applications retrieving images from a device supporting HEIF is to show only converted JPG from HEIF originals, and only H264 encoded video assets from HEVC.
  ICMediaPresentationOriginal - This presentation will show only original images from a device supporting HEIF and HEVC.  Burned in renders are always exported in JPG, as are burned in effects for MOV clips.
 */
@property (nonatomic, readwrite) ICMediaPresentation mediaPresentation IC_AVAILABLE(macos(10.11), ios(14.0));

/*!
  @method filesOfType:
  @abstract This method returns an array of files on the camera of type fileType.
  @discussion The fileType string is one of the following Uniform Type Identifier strings: kUTTypeImage, kUTTypeMovie, kUTTypeAudio, or kUTTypeData.
 */
- (nullable NSArray<NSString*>*)filesOfType:(NSString*) fileUTType IC_AVAILABLE(macos(10.4), ios(13.0));

#pragma mark - Download
/*!
  @method requestReadDataFromFile:atOffset:length:readDelegate:didReadDataSelector:contextInfo:
  @abstract This method asynchronously reads data of a specified length from a specified offset.
  @discussion The readDelegate passed must not be nil. When this request is completed, the didReadDataSelector of the readDelegate object is called. The didReadDataSelector should have the same signature as: - (void)didReadData:(NSData*)data fromFile:(ICCameraFile*)file error:(NSError*)error contextInfo:(void*)contextInfo. The content of error returned should be examined to determine if the request completed successfully.
 */
- (void)requestReadDataFromFile:(ICCameraFile*)file
    atOffset:(off_t)offset
    length:(off_t)length
    readDelegate:(id)readDelegate
    didReadDataSelector:(SEL)selector
    contextInfo:(void* _Nullable) contextInfo IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
  @method requestDownloadFile:options:downloadDelegate:didDownloadSelector:contextInfo:
  @abstract Download a file from the camera. Please refer to the top of this header for information about the options.
  @discussion The downloadDelegate passed must not be nil. When this request is completed, the didDownloadSelector of the downloadDelegate object is called.The didDownloadSelector should have the same signature as: - (void)didDownloadFile:(ICCameraFile*)file error:(NSError*)error options:(NSDictionary*)options contextInfo:(void*)contextInfo. The content of error returned should be examined to determine if the request completed successfully.
 */
- (void)requestDownloadFile:(ICCameraFile*)file
    options:(NSDictionary<ICDownloadOption, id>*)options
    downloadDelegate:(id<ICCameraDeviceDownloadDelegate>)downloadDelegate
    didDownloadSelector:(SEL)selector
    contextInfo:(void* _Nullable) contextInfo IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
  @method cancelDownload
  @abstract Cancels the current download operation if supported
 */
- (void) cancelDownload IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

#pragma mark - Delete

/*!
  @method requestDeleteFiles
  @abstract Deletes files.
 */
- (void)requestDeleteFiles:(NSArray<ICCameraItem*>*) files IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
  @method requestDeleteFiles:deleteFailed:completion
  @abstract Allows for deletion of an array of ICCameraItem objects, with the added ability to catch delete failures using the
  'deleteFailed' block, and a completion block that will return the overall state of the request.
 
  The deleteFailed block will return:
  - NSDictionary<ICDeleteError, ICCameraItem*>*
 
  The completion block will return:
  — error:
  - nil if successful
  - NSError* with an code set to ICReturnDeleteFilesFailed if any file failed.
 
  - result: NSDictionary<ICDeleteResult, NSArray<ICCameraItem*>*>* result
  - ICDeleteSuccessful: NSArray<ICCameraItem*>* success
  - ICDeleteFailed: NSArray<ICCameraItem*>* failed
 */
- (nullable NSProgress*)requestDeleteFiles:(NSArray<ICCameraItem*>*)files
    deleteFailed:(void (^)(NSDictionary<ICDeleteError, ICCameraItem*>*))deleteFailed
    completion:(void (^)(NSDictionary<ICDeleteResult, NSArray<ICCameraItem*>*>* result, NSError* _Nullable error)) completion IC_AVAILABLE(macos(10.15), ios(13.0));

/*!
  @method cancelDelete
  @abstract Cancels the current delete operation started by sending a 'requestDeleteFiles:'. This will only cancel operations in flight when a batch of files have been requested for deletion.
 */
- (void) cancelDelete IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

#pragma mark - Status

/*!
  @method requestSyncClock
  @abstract Synchronize camera's clock with the computer's clock. You should send this request only if the camera has the 'ICCameraDeviceCanSyncClock' capability.
 */
- (void)requestSyncClock IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
  @property timeOffset
  @abstract Indicates the time offset, in seconds, between the camera's clock and the computer's clock￼. This value is positive if the camera's clock is ahead of the computer's clock. This property should be ignored if the camera's capabilities property does not contain ICCameraDeviceCanSyncClock.
 */
@property (readonly) NSTimeInterval timeOffset IC_AVAILABLE(macos(10.4));

/*!
  @property batteryLevelAvailable
  @abstract Indicates if the device has reported battery charge level￼.
 */
@property (readonly) BOOL batteryLevelAvailable IC_AVAILABLE(macos(10.4));

/*!
  @property batteryLevel
  @abstract ￼Indicates the battery charge level. Its value ranges from 0 to 100.
 */
@property (readonly) NSUInteger batteryLevel IC_AVAILABLE(macos(10.4));

/*!
  @method requestUploadFile:options:uploadDelegate:didUploadSelector:contextInfo:
  @abstract Upload a file at fileURL to the camera. The options dictionary is not used in this version.
  @discussion The uploadDelegate passed must not be nil. When this request is completed, the didUploadSelector of the uploadDelegate object is called. The didUploadSelector should have the same signature as: - (void)didUploadFile:(NSURL*)fileURL error:(NSError*)error contextInfo:(void*)contextInfo. The content of error returned should be examined to determine if the request completed successfully.
 */
- (void)requestUploadFile:(NSURL*)fileURL
    options:(NSDictionary<ICUploadOption, id>*)options
    uploadDelegate:(id)uploadDelegate
    didUploadSelector:(SEL)selector
    contextInfo:(void* _Nullable) contextInfo IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

#pragma mark - Camera tethering
/*!
  @property tetheredCaptureEnabled
  @abstract This property is set to YES when tethered capture is enabled on the device.
  @discussion Use 'requestEnableTethering' and 'requestDisableTethering' to enable or disable tethered capture on the device.
 */
@property (nonatomic, readonly) BOOL tetheredCaptureEnabled IC_AVAILABLE(macos(10.4));

/*!
  @method requestEnableTethering
  @abstract Send this message to enable tethered capture on the camera device if the camera has the 'ICCameraDeviceCanTakePicture' capability.
 */
- (void)requestEnableTethering IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
  @method requestDisableTethering
  @abstract Send this message to disable tethered capture on the camera device if the camera has the 'ICCameraDeviceCanTakePicture' capability and if your process has already sent a 'requestEnableTethering' to it.
 */
- (void)requestDisableTethering IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
  @method requestTakePicture
  @abstract Capture a new image using the camera, the camera capabilities include 'ICCameraDeviceCanTakePicture'.
  @discussion You MUST send 'requestEnableTethering' message to the camera before sending 'requestTakePicture' message.
 */
- (void)requestTakePicture IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

#pragma mark - PTP Interaction

/*!
  @property ptpEventHandler
  @abstract As an alternative to setting up an object to handle PTP event packets, a handler can be set.  The handler will always be called in place of the delegate if non-nil.  If the handler is not present, the delegate will be called if present. It is guaranteed only one of the methods will be called if both are implemented.
 */
@property (nonatomic, copy) void (^ptpEventHandler)(NSData* eventData) IC_UNAVAILABLE(macos) IC_AVAILABLE(ios(13.0));

/*!
  @method requestSendPTPCommand:outData:sendCommandDelegate:sendCommandDelegate:contextInfo:
  @abstract This method asynchronously sends a PTP command to a camera.
  @discussion This should be sent only if the 'capabilities' property contains 'ICCameraDeviceCanAcceptPTPCommands'. All PTP cameras have this capability. The response to this command will be delivered using didSendCommandSelector of sendCommandDelegate. The didSendCommandSelector should have the same signature as: - (void)didSendPTPCommand:(NSData*)command inData:(NSData*)data response:(NSData*)response error:(NSError*)error contextInfo:(void*)contextInfo. The content of error returned should be examined to determine if the request completed successfully.
 */
- (void)requestSendPTPCommand:(NSData*)command
    outData:(NSData* _Nullable)data
    sendCommandDelegate:(id)sendCommandDelegate
    didSendCommandSelector:(SEL)selector
    contextInfo:(void* _Nullable) contextInfo IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
  @method requestSendPTPCommand:outData:completion
  @abstract This method asynchronously sends a PTP command to a camera.
  @discussion The response, data, and any error message will be returned the block.
 */
- (void)requestSendPTPCommand:(NSData*)ptpCommand
    outData:(NSData* _Nullable)ptpData
    completion:(void (^)(NSData* responseData, NSData* ptpResponseData, NSError* _Nullable error)) completion IC_AVAILABLE(macos(10.15), ios(13.0));

@end

#pragma mark - ICCameraDeviceDelegate

//------------------------------------------------------------------------------------------------------- ICCameraDeviceDelegate
/*!
  @protocol ICCameraDeviceDelegate  <ICDeviceDelegate>
  @abstract A delegate of ICCameraDevice must conform to ICCameraDeviceDelegate protocol.
  @discussion The ICCameraDeviceDelegate protocol inherits from the ICDeviceDelegate protocol.
 */
@protocol ICCameraDeviceDelegate <ICDeviceDelegate>

/*!
  @method cameraDevice:didAddItems:
  @abstract This message is sent when objects are added to the device.
  @discussion The objects in items are instances ICCameraFile class.
 */
- (void)cameraDevice:(ICCameraDevice*)camera didAddItems:(NSArray<ICCameraItem*>*) items IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
  @method cameraDevice:didRemoveItems:
  @abstract This message is sent when objects are removed from the device.
  @discussion The objects in items are instances ICCameraFile class.
 */
- (void)cameraDevice:(ICCameraDevice*)camera didRemoveItems:(NSArray<ICCameraItem*>*) items IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
  @method cameraDevice:didReceiveThumbnail:forItem:error:
  @abstract This message is sent when the thumbnail requested for an item on a device is available.
 */
- (void)cameraDevice:(ICCameraDevice*)camera
    didReceiveThumbnail:(CGImageRef _Nullable)thumbnail
    forItem:(ICCameraItem*)item
    error:(NSError* _Nullable) error IC_AVAILABLE(macos(10.15), ios(13.0));

/*!
  @method cameraDevice:didReceiveMetadata:forItem:error:
  @abstract This message is sent when the metadata requested for an item on a device is available.
 */
- (void)cameraDevice:(ICCameraDevice*)camera
    didReceiveMetadata:(NSDictionary* _Nullable)metadata
    forItem:(ICCameraItem*)item
    error:(NSError* _Nullable) error IC_AVAILABLE(macos(10.15), ios(13.0));

/*!
  @method cameraDevice:didRenameItems:
  @abstract This message is sent when an object or objects are renamed on the device.
  @discussion The objects may be instances of ICCameraFolder or ICCameraFile class.
 */
- (void)cameraDevice:(ICCameraDevice*)camera didRenameItems:(NSArray<ICCameraItem*>*) items IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
  @method cameraDeviceDidChangeCapability:
  @abstract This message is sent when a capability of a device changes.
  @discussion Detailed capabilitiy descriptions are provided at the top of this header file.
 */
- (void)cameraDeviceDidChangeCapability:(ICCameraDevice*) camera IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
  @method cameraDevice:didReceivePTPEvent:
  @abstract This message is sent to the delegate to convey a PTP event.
 */
- (void)cameraDevice:(ICCameraDevice*)camera didReceivePTPEvent:(NSData*) eventData IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
  @method deviceDidBecomeReadyWithCompleteContentCatalog:
  @abstract This message is sent when the camera device is done enumerating its content and is ready to receive requests.
  @discussion A session must be opened on the device in order to enumerate its content and make it ready to receive requests.
 */
- (void)deviceDidBecomeReadyWithCompleteContentCatalog:(ICCameraDevice*) device IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
  @method deviceDidRemoveAccessRestriction:
  @abstract This message is sent when an Apple device has been unlocked, paired to the host, and media is available.
 */
- (void)cameraDeviceDidRemoveAccessRestriction:(ICDevice*)device;

/*!
  @method deviceDidEnableAccessRestriction:
  @abstract This message is sent when an Apple device has been locked, and media is unavailable until the restriction
  has been removed.
 */
- (void)cameraDeviceDidEnableAccessRestriction:(ICDevice*)device;

@optional

/*!
  @method cameraDevice:shouldGetThumbnailOfItem:
  @abstract This message is sent when the camera device is about to execute queued requests for the thumbnail of a specific item.
  If the request is no longer wanted, eg: the item is no longer displayed on the screen, the client can return NO and abort sending
  a request down to the camera device, speeding up the exection queue.
 */
- (BOOL)cameraDevice:(ICCameraDevice*)cameraDevice shouldGetThumbnailOfItem:(ICCameraItem*) item IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
  @abstract This message is sent when the camera device is about to execute queued requests for the metadata of a specific item.
  If the request is no longer wanted, eg: the item is no longer displayed on the screen, the client can return NO and abort sending
  a request down to the camera device, speeding up the execution queue.
 */
- (BOOL)cameraDevice:(ICCameraDevice*)cameraDevice shouldGetMetadataOfItem:(ICCameraItem*) item IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
  @method cameraDevice:didCompleteDeleteFilesWithError:
  @abstract This message is sent after the camera device completes a delete operation initiated by sending a 'requestDeleteFiles:' message to that device.
  @discusson This message is sent after the camera device completes a delete operation initiated by sending a 'requestDeleteFiles:' message to that device.
 */
- (void)cameraDevice:(ICCameraDevice*)camera didCompleteDeleteFilesWithError:(nullable NSError*) error IC_AVAILABLE(macos(10.4), ios(13.0));

#pragma mark - Deprecated

/*!
  @method cameraDevice:didAddItem:
 */
- (void)cameraDevice:(ICCameraDevice*)camera
    didAddItem:(ICCameraItem*) item IC_DEPRECATED_WITH_REPLACEMENT("Implement cameraDevice:didAddItems:", macos(10.4, 10.15));

/*!
  @method cameraDevice:didRemoveItem:
 */
- (void)cameraDevice:(ICCameraDevice*)camera
    didRemoveItem:(ICCameraItem*) item IC_DEPRECATED_WITH_REPLACEMENT("Implement cameraDevice:didRemoveItems:", macos(10.4, 10.15));

/*!
  @method cameraDevice:didReceiveThumbnailForItem:
 */
- (void)cameraDevice:(ICCameraDevice*)camera
    didReceiveThumbnailForItem:(ICCameraItem*) item
    IC_DEPRECATED_WITH_REPLACEMENT("Implement cameraDevice:didReceiveThumbnail:forItem:error:", macos(10.4, 10.15));

/*!
  @method cameraDevice:didReceiveMetadataForItem:
 */
- (void)cameraDevice:(ICCameraDevice*)camera
    didReceiveMetadataForItem:(ICCameraItem*) item
    IC_DEPRECATED_WITH_REPLACEMENT("Implement cameraDevice:didReceiveMetadata:forItem:error:", macos(10.4, 10.15));

@end

#pragma mark - ICCameraDeviceDownloadDelegate
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
- (void)didDownloadFile:(ICCameraFile*)file
    error:(NSError* _Nullable)error
    options:(NSDictionary<NSString*, id>*)options
    contextInfo:(void* _Nullable) contextInfo IC_AVAILABLE(macos(10.4));

/*!
  @method didReceiveDownloadProgressForFile:downloadedBytes:maxBytes:
  @abstract This message is sent to the delegate to provide status of the download operation.
 */
- (void)didReceiveDownloadProgressForFile:(ICCameraFile*)file downloadedBytes:(off_t)downloadedBytes maxBytes:(off_t) maxBytes IC_AVAILABLE(macos(10.4), ios(13.0));

@end

NS_ASSUME_NONNULL_END
