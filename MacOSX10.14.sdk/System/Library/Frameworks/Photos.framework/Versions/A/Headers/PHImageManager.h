//
//  PHImageManager.h
//  Photos
//
//  Copyright © 2017 Apple, Inc. All rights reserved.
//

#import <AppKit/AppKit.h>
#import <Photos/PhotosTypes.h>

@class PHAsset;

NS_ASSUME_NONNULL_BEGIN

#pragma mark - PHImageRequestOptions - Configuration

typedef NS_ENUM(NSInteger, PHImageRequestOptionsVersion) {
    PHImageRequestOptionsVersionCurrent = 0, // version with edits (aka adjustments) rendered or unadjusted version if there is no edits
    PHImageRequestOptionsVersionUnadjusted, // original version without any adjustments
    PHImageRequestOptionsVersionOriginal // original version, in the case of a combined format the highest fidelity format will be returned (e.g. RAW for a RAW+JPG source image)
} NS_ENUM_AVAILABLE(10_13, 8_0);

typedef NS_ENUM(NSInteger, PHImageRequestOptionsDeliveryMode) {
    PHImageRequestOptionsDeliveryModeOpportunistic = 0, // client may get several image results when the call is asynchronous or will get one result when the call is synchronous
    PHImageRequestOptionsDeliveryModeHighQualityFormat = 1, // client will get one result only and it will be as asked or better than asked (sync requests are automatically processed this way regardless of the specified mode)
    PHImageRequestOptionsDeliveryModeFastFormat = 2 // client will get one result only and it may be degraded
} NS_ENUM_AVAILABLE(10_13, 8_0);

typedef NS_ENUM(NSInteger, PHImageRequestOptionsResizeMode) {
    PHImageRequestOptionsResizeModeNone = 0, // no resize
    PHImageRequestOptionsResizeModeFast, // use targetSize as a hint for optimal decoding when the source image is a compressed format (i.e. subsampling), the delivered image may be larger than targetSize
    PHImageRequestOptionsResizeModeExact, // same as above but also guarantees the delivered image is exactly targetSize (must be set when a normalizedCropRect is specified)
} NS_ENUM_AVAILABLE(10_13, 8_0);

// Progress handler, called in an arbitrary serial queue. Only called when the data is not available locally and is retrieved from iCloud.
typedef void (^PHAssetImageProgressHandler)(double progress, NSError *__nullable error, BOOL *stop, NSDictionary *__nullable info) NS_AVAILABLE(10_13, 8_0);

NS_CLASS_AVAILABLE(10_13, 8_0) @interface PHImageRequestOptions : NSObject <NSCopying>

@property (nonatomic, assign) PHImageRequestOptionsVersion version; // version
@property (nonatomic, assign) PHImageRequestOptionsDeliveryMode deliveryMode; // delivery mode. Defaults to PHImageRequestOptionsDeliveryModeOpportunistic
@property (nonatomic, assign) PHImageRequestOptionsResizeMode resizeMode; // resize mode. Does not apply when size is PHImageManagerMaximumSize. Defaults to PHImageRequestOptionsResizeModeNone (or no resize)
@property (nonatomic, assign) CGRect normalizedCropRect; // specify crop rectangle in unit coordinates of the original image, such as a face. Defaults to CGRectZero (not applicable)
@property (nonatomic, assign, getter=isNetworkAccessAllowed) BOOL networkAccessAllowed; // if necessary will download the image from iCloud (client can monitor or cancel using progressHandler). Defaults to NO (see start/stopCachingImagesForAssets)
@property (nonatomic, assign, getter=isSynchronous) BOOL synchronous; // return only a single result, blocking until available (or failure). Defaults to NO
@property (nonatomic, copy, nullable) PHAssetImageProgressHandler progressHandler; // provide caller a way to be told how much progress has been made prior to delivering the data when it comes from iCloud. Defaults to nil, shall be set by caller

@end

#pragma mark - PHImageManager - Fetching

// Uniquely identify a cancellable async request
typedef int32_t PHImageRequestID NS_AVAILABLE(10_13, 8_0);
static const PHImageRequestID PHInvalidImageRequestID = 0;

// Size to pass when requesting the original image or the largest rendered image available (resizeMode will be ignored)
extern CGSize const PHImageManagerMaximumSize NS_AVAILABLE(10_13, 8_0);

// Result's handler info dictionary keys
extern NSString *const PHImageResultIsInCloudKey NS_AVAILABLE(10_13, 8_0); // key (NSNumber): result is in iCloud, meaning a new request will need to get issued (with networkAccessAllowed set) to get the result
extern NSString *const PHImageResultIsDegradedKey NS_AVAILABLE(10_13, 8_0); // key (NSNumber): result  is a degraded image (only with async requests), meaning other images will be sent unless the request is cancelled in the meanwhile (note that the other request may fail if, for example, data is not available locally and networkAccessAllowed was not specified)
extern NSString *const PHImageResultRequestIDKey NS_AVAILABLE(10_13, 8_0); // key (NSNumber): Request ID of the request for this result
extern NSString *const PHImageCancelledKey NS_AVAILABLE(10_13, 8_0); // key (NSNumber): result is not available because the request was cancelled
extern NSString *const PHImageErrorKey NS_AVAILABLE(10_13, 8_0); // key (NSError): NSFileManager or iCloud Photos errors


NS_CLASS_AVAILABLE(10_13, 8_0) @interface PHImageManager : NSObject

+ (PHImageManager *)defaultManager;

/**
 @abstract Request an image representation for the specified asset.
 @param asset The asset whose image data is to be loaded.
 @param targetSize The target size of image to be returned.
 @param contentMode An option for how to fit the image to the aspect ratio of the requested size.
     If the asset's aspect ratio does not match that of the given targetSize, contentMode determines how the image will be resized.
       PHImageContentModeAspectFit: Fit the asked size by maintaining the aspect ratio, the delivered image may not necessarily be the asked targetSize (see PHImageRequestOptionsDeliveryMode and PHImageRequestOptionsResizeMode)
       PHImageContentModeAspectFill: Fill the asked size, some portion of the content may be clipped, the delivered image may not necessarily be the asked targetSize (see PHImageRequestOptionsDeliveryMode and PHImageRequestOptionsResizeMode)
       PHImageContentModeDefault: Use PHImageContentModeDefault when size is PHImageManagerMaximumSize (though no scaling/cropping will be done on the result)
 @param options Options specifying how Photos should handle the request, format the requested image, and notify your app of progress or errors.
     If -[PHImageRequestOptions isSynchronous] returns NO (or options is nil), resultHandler may be called 1 or more times. Typically in this case, resultHandler will be called asynchronously on the main thread with the requested results. However, if deliveryMode = PHImageRequestOptionsDeliveryModeOpportunistic, resultHandler may be called synchronously on the calling thread if any image data is immediately available. If the image data returned in this first pass is of insufficient quality, resultHandler will be called again, asychronously on the main thread at a later time with the "correct" results. If the request is cancelled, resultHandler may not be called at all.
     If -[PHImageRequestOptions isSynchronous] returns YES, resultHandler will be called exactly once, synchronously and on the calling thread. Synchronous requests cannot be cancelled.
 @param resultHandler A block that is called one or more times either synchronously on the current thread or asynchronously on the main thread depending on the options specified in the PHImageRequestOptions options parameter.
 @return A numeric identifier for the request. If you need to cancel the request before it completes, pass this identifier to the cancelImageRequest: method.
 */
- (PHImageRequestID)requestImageForAsset:(PHAsset *)asset targetSize:(CGSize)targetSize contentMode:(PHImageContentMode)contentMode options:(nullable PHImageRequestOptions *)options resultHandler:(void (^)(NSImage *__nullable result, NSDictionary *__nullable info))resultHandler;

/**
 @abstract Request largest represented image as data bytes for the specified asset.
 @param asset The asset whose image data is to be loaded.
 @param options Options specifying how Photos should handle the request, format the requested image, and notify your app of progress or errors.
      If PHImageRequestOptionsVersionCurrent is requested and the asset has adjustments then the largest rendered image data is returned. In all other cases then the original image data is returned.
 @param resultHandler A block that is called exactly once either synchronously on the current thread or asynchronously on the main thread depending on the synchronous option specified in the PHImageRequestOptions options parameter (deliveryMode is ignored).
 */
- (PHImageRequestID)requestImageDataForAsset:(PHAsset *)asset options:(nullable PHImageRequestOptions *)options resultHandler:(void(^)(NSData *__nullable imageData, NSString *__nullable dataUTI, CGImagePropertyOrientation orientation, NSDictionary *__nullable info))resultHandler;

- (void)cancelImageRequest:(PHImageRequestID)requestID;

@end

NS_ASSUME_NONNULL_END
