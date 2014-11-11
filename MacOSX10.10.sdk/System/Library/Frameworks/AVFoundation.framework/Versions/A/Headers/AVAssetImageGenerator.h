/*
	File:  AVAssetImageGenerator.h

	Framework:  AVFoundation
 
	Copyright 2010-2013 Apple Inc. All rights reserved.

*/

/*!
    @class			AVAssetImageGenerator

    @abstract		AVAssetImageGenerator provides thumbnail or preview images of assets independently of playback.
	
	@discussion		Generating a single image in isolation can require the decoding of a large number of video frames
					with complex interdependencies. Whenever a series of images is required, far greater efficiency
					can be achieved by use of the asynchronous method, -generateCGImagesAsynchronouslyForTimes:completionHandler:,
					which employs decoding efficiencies similar to those used during playback.
*/

#import <AVFoundation/AVBase.h>
#import <Foundation/Foundation.h>
#import <CoreMedia/CMTime.h>

#if TARGET_OS_IPHONE
#import <CoreGraphics/CoreGraphics.h>
#else // ! TARGET_OS_IPHONE
#import <ApplicationServices/../Frameworks/CoreGraphics.framework/Headers/CoreGraphics.h>
#endif // ! TARGET_OS_IPHONE

@class AVAsset;
@class AVVideoComposition;
@class AVAssetImageGeneratorInternal;
@protocol AVVideoCompositing;

/*!
	@constant		AVAssetImageGeneratorApertureModeCleanAperture
	@abstract		Both pixel aspect ratio and clean aperture will be applied.
*/
AVF_EXPORT NSString *const AVAssetImageGeneratorApertureModeCleanAperture NS_AVAILABLE(10_7, 4_0);

/*!
	@constant		AVAssetImageGeneratorApertureModeProductionAperture
	@abstract		Only pixel aspect ratio will be applied.
*/
AVF_EXPORT NSString *const AVAssetImageGeneratorApertureModeProductionAperture NS_AVAILABLE(10_7, 4_0);

/*!
	@constant		AVAssetImageGeneratorApertureModeEncodedPixels
	@abstract		Neither pixel aspect ratio nor clean aperture will be applied.
*/
AVF_EXPORT NSString *const AVAssetImageGeneratorApertureModeEncodedPixels NS_AVAILABLE(10_7, 4_0);

typedef NS_ENUM(NSInteger, AVAssetImageGeneratorResult)
{
	AVAssetImageGeneratorSucceeded,
	AVAssetImageGeneratorFailed,
	AVAssetImageGeneratorCancelled,
};

NS_CLASS_AVAILABLE(10_7, 4_0)
@interface AVAssetImageGenerator : NSObject
{
@private
	AVAssetImageGeneratorInternal		*_priv;
}

/* Indicates the instance of AVAsset with which the AVAssetImageGenerator was initialized  */ 
@property (nonatomic, readonly) AVAsset *asset NS_AVAILABLE(10_9, 6_0);

/* Specifies whether or not to apply the track's preferredTransform (see -[AVAssetTrack preferredTransform]) when extracting an image from the asset.
   Default is NO.  Only rotation by 90, 180, or 270 degrees is supported. */
@property (nonatomic) BOOL appliesPreferredTrackTransform;

/* Specifies the maximum dimensions for generated image.  Default (CGSizeZero) is the asset's unscaled dimensions.
   AVAssetImageGenerator will scale images such that they fit within the defined bounding box.
   Images will never be scaled up.  The aspect ratio of the scaled image will be defined by the apertureMode property. */
@property (nonatomic) CGSize maximumSize;

/* Specifies the aperture mode for the generated image.  Default is AVAssetImageGeneratorApertureModeCleanAperture. */
@property (nonatomic, copy) NSString *apertureMode;

/* Specifies the video composition to use when extracting images from assets with multiple video tracks.
   If no videoComposition is specified, only the first enabled video track will be used.
   If a videoComposition is specified, the value of appliesPreferredTrackTransform is ignored. */
@property (nonatomic, copy) AVVideoComposition *videoComposition;

/* Indicates the custom video compositor instance used, if any */
@property (nonatomic, readonly) id<AVVideoCompositing> customVideoCompositor NS_AVAILABLE(10_9, 7_0);

/* The actual time of the generated images will be within the range [requestedTime-toleranceBefore, requestedTime+toleranceAfter] and may differ from the requested time for efficiency.
   Pass kCMTimeZero for both toleranceBefore and toleranceAfter to request frame-accurate image generation; this may incur additional decoding delay.
   Default is kCMTimePositiveInfinity. */
@property (nonatomic) CMTime requestedTimeToleranceBefore NS_AVAILABLE(10_7, 5_0);
@property (nonatomic) CMTime requestedTimeToleranceAfter NS_AVAILABLE(10_7, 5_0);

/*!
	@method			assetImageGeneratorWithAsset:
	@abstract		Returns an instance of AVAssetImageGenerator for use with the specified asset.
	@param			asset
					The asset from which images will be extracted.
	@result			An instance of AVAssetImageGenerator
	@discussion		This method may succeed even if the asset possesses no visual tracks at the time of initialization.
					Clients may wish to test whether an asset has any tracks with the visual characteristic via
					-[AVAsset tracksWithMediaCharacteristic:].
					
					Note also that assets that belong to a mutable subclass of AVAsset, AVMutableComposition or AVMutableMovie,
					may gain visual tracks after initialization of an associated AVAssetImageGenerator.
					
					However, the results of image generation are undefined if mutations of the asset occur while images
					are being generated. 

					AVAssetImageGenerator will use the default enabled video track(s) to generate images.
*/
+ (AVAssetImageGenerator *)assetImageGeneratorWithAsset:(AVAsset *)asset;

/*!
	@method			initWithAsset:
	@abstract		Initializes an instance of AVAssetImageGenerator for use with the specified asset.
	@param			asset
					The asset from which images will be extracted.
	@result			An instance of AVAssetImageGenerator
	@discussion		This method may succeed even if the asset possesses no visual tracks at the time of initialization.
					Clients may wish to test whether an asset has any tracks with the visual characteristic via
					-[AVAsset tracksWithMediaCharacteristic:].
					
					Note also that assets that belong to a mutable subclass of AVAsset, AVMutableComposition or AVMutableMovie,
					may gain visual tracks after initialization of an associated AVAssetImageGenerator.
					
					However, the results of image generation are undefined if mutations of the asset occur while images
					are being generated. 

					AVAssetImageGenerator will use the default enabled video track(s) to generate images.
*/
- (instancetype)initWithAsset:(AVAsset *)asset;

/*!
	@method			copyCGImageAtTime:actualTime:error:
	@abstract		Returns a CFRetained CGImageRef for an asset at or near the specified time.
	@param			requestedTime
					The time at which the image of the asset is to be created.
	@param			actualTime
					A pointer to a CMTime to receive the time at which the image was actually generated. If you are not interested
					in this information, pass NULL.
	@param			outError
					An error object describing the reason for failure, in the event that this method returns NULL.
	@result			A CGImageRef.
	@discussion		Returns the CGImage synchronously. Ownership follows the Create Rule.
*/
- (CGImageRef)copyCGImageAtTime:(CMTime)requestedTime actualTime:(CMTime *)actualTime error:(NSError **)outError CF_RETURNS_RETAINED;

/* error object indicates the reason for failure if the result is AVAssetImageGeneratorFailed */
typedef void (^AVAssetImageGeneratorCompletionHandler)(CMTime requestedTime, CGImageRef image, CMTime actualTime, AVAssetImageGeneratorResult result, NSError *error);

/*!
	@method			generateCGImagesAsynchronouslyForTimes:completionHandler:
	@abstract		Returns a series of CGImageRefs for an asset at or near the specified times.
	@param			requestedTimes
					An NSArray of NSValues, each containing a CMTime, specifying the asset times at which an image is requested.
	@param			handler
					A block that will be called when an image request is complete.
	@discussion		Employs an efficient "batch mode" for getting images in time order.
					The client will receive exactly one handler callback for each requested time in requestedTimes.
					Changes to generator properties (snap behavior, maximum size, etc...) will not affect outstanding asynchronous image generation requests.
					The generated image is not retained.  Clients should retain the image if they wish it to persist after the completion handler returns.
*/
- (void)generateCGImagesAsynchronouslyForTimes:(NSArray *)requestedTimes completionHandler:(AVAssetImageGeneratorCompletionHandler)handler;

/*!
	@method			cancelAllCGImageGeneration
	@abstract		Cancels all outstanding image generation requests.
	@discussion		Calls the handler block with AVAssetImageGeneratorCancelled for each image time in every previous invocation of -generateCGImagesAsynchronouslyForTimes:completionHandler:
					for which images have not yet been supplied.
*/
- (void)cancelAllCGImageGeneration;

@end
