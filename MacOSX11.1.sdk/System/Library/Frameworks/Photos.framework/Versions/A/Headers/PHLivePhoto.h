//
//  PHLivePhoto.h
//  Photos
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <Photos/PhotosTypes.h>
#import <CoreGraphics/CGGeometry.h>
#if TARGET_OS_IPHONE || TARGET_OS_MACCATALYST
@class UIImage;
#else
@class NSImage;
#endif

NS_ASSUME_NONNULL_BEGIN
API_AVAILABLE_BEGIN(macos(10.15), ios(9.1), tvos(10))

typedef int32_t PHLivePhotoRequestID;
static const PHLivePhotoRequestID PHLivePhotoRequestIDInvalid = 0;

/// These keys may be found in the info dictionary delivered to a live photo request result handler block.
extern NSString * const PHLivePhotoInfoErrorKey; // key : NSError decribing an error that has occurred while creating the live photo
extern NSString * const PHLivePhotoInfoIsDegradedKey; // key : NSNumber containing a BOOL, YES whenever the deivered live photo object does not contain all content required for full playback.
extern NSString * const PHLivePhotoInfoCancelledKey; // key : NSNumber containing a BOOL, YES when the result handler is being called after the request has been cancelled.


OS_EXPORT API_AVAILABLE(macos(10.12))
@interface PHLivePhoto : NSObject <NSCopying, NSSecureCoding>

- (instancetype)init NS_UNAVAILABLE;

/// The dimensions of the live photo measured in pixels.
@property (readonly, nonatomic) CGSize size API_AVAILABLE(macos(10.12));

#pragma mark - Export

/// Requests a Live Photo from the given resource URLs. The result handler will be called multiple times to deliver new PHLivePhoto instances with increasingly more content. If a placeholder image is provided, the result handler will first be invoked synchronously to deliver a live photo containing only the placeholder image. Subsequent invocations of the result handler will occur on the main queue.
//  The targetSize and contentMode parameters are used to resize the live photo content if needed. If targetSize is equal to CGRectZero, content will not be resized.
//  When using this method to provide content for a PHLivePhotoView, each live photo instance delivered via the result handler should be passed to -[PHLivePhotoView setLivePhoto:].
#if TARGET_OS_IPHONE || TARGET_OS_MACCATALYST
+ (PHLivePhotoRequestID)requestLivePhotoWithResourceFileURLs:(NSArray<NSURL *> *)fileURLs placeholderImage:(nullable UIImage *)image targetSize:(CGSize)targetSize contentMode:(PHImageContentMode)contentMode resultHandler:(void(^)(PHLivePhoto *_Nullable livePhoto, NSDictionary *info))resultHandler;
#else
+ (PHLivePhotoRequestID)requestLivePhotoWithResourceFileURLs:(NSArray<NSURL *> *)fileURLs placeholderImage:(nullable NSImage *)image targetSize:(CGSize)targetSize contentMode:(PHImageContentMode)contentMode resultHandler:(void(^)(PHLivePhoto *_Nullable livePhoto, NSDictionary *info))resultHandler;
#endif

/// Cancels the loading of a PHLivePhoto. The request's completion handler will be called.
+ (void)cancelLivePhotoRequestWithRequestID:(PHLivePhotoRequestID)requestID;

@end

API_AVAILABLE(ios(14))
API_UNAVAILABLE(macos, tvos, watchos)
@interface PHLivePhoto (NSItemProvider) <NSItemProviderReading>

@end

API_AVAILABLE_END
NS_ASSUME_NONNULL_END
