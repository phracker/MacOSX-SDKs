//
//  VNTargetedImageRequest.h
//  Vision
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <Vision/VNRequest.h>
#import <CoreVideo/CVPixelBuffer.h>
#import <CoreImage/CoreImage.h>


NS_ASSUME_NONNULL_BEGIN


/*!
	@brief A request that requires an initial image as a starting point for its work.
*/
API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
@interface VNTargetedImageRequest : VNImageBasedRequest


/*!
	@brief Create a new request that targets an image in a pixel buffer.

	@param pixelBuffer		The pixel buffer containing the targeted image.
*/
- (instancetype) initWithTargetedCVPixelBuffer:(CVPixelBufferRef)pixelBuffer;


/*!
	@brief Create a new request that targets an image in a pixel buffer.

	@param pixelBuffer			The pixel buffer containing the targeted image.
	
	@param	completionHandler	The block that is invoked when the request has been performed.
*/
- (instancetype) initWithTargetedCVPixelBuffer:(CVPixelBufferRef)pixelBuffer completionHandler:(nullable VNRequestCompletionHandler)completionHandler NS_DESIGNATED_INITIALIZER;


/*!
	@brief Create a new request with a targeted CGImageRef.

	@param cgImage		The CGImageRef of the targeted image.
*/
- (instancetype) initWithTargetedCGImage:(CGImageRef)cgImage;


/*!
	@brief Create a new request with a targeted CGImageRef.

	@param cgImage				The CGImageRef of the targeted image.
	
	@param	completionHandler	The block that is invoked when the request has been performed.
*/
- (instancetype) initWithTargetedCGImage:(CGImageRef)cgImage completionHandler:(nullable VNRequestCompletionHandler)completionHandler NS_DESIGNATED_INITIALIZER;


/*!
	@brief Create a new request with a targeted CIImage.

	@param ciImage		The CIImage of the targeted image.
*/
- (instancetype) initWithTargetedCIImage:(CIImage*)ciImage;


/*!
	@brief Create a new request with a targeted CIImage.

	@param ciImage		The CIImage of the targeted image.
	
	@param	completionHandler	The block that is invoked when the request has been performed.
*/
- (instancetype) initWithTargetedCIImage:(CIImage*)ciImage completionHandler:(nullable VNRequestCompletionHandler)completionHandler NS_DESIGNATED_INITIALIZER;


/*!
	@brief Create a new request with a targeted image URL.

	@param imageURL		The URL of the targeted image.
*/
- (instancetype) initWithTargetedImageURL:(NSURL*)imageURL;


/*!
	@brief Create a new request with a targeted image URL.

	@param imageURL				The URL of the targeted image.
	
	@param	completionHandler	The block that is invoked when the request has been performed.
*/
- (instancetype) initWithTargetedImageURL:(NSURL*)imageURL completionHandler:(nullable VNRequestCompletionHandler)completionHandler NS_DESIGNATED_INITIALIZER;


/*!
	@brief Create a new request that targets an image stored in an NSData.

	@param imageData	The data of the targeted image.
*/
- (instancetype) initWithTargetedImageData:(NSData*)imageData;


/*!
	@brief Create a new request that targets an image stored in an NSData.

	@param imageData			The data of the targeted image.
	
	@param	completionHandler	The block that is invoked when the request has been performed.
*/
- (instancetype) initWithTargetedImageData:(NSData*)imageData completionHandler:(nullable VNRequestCompletionHandler)completionHandler NS_DESIGNATED_INITIALIZER;



- (instancetype) init  NS_UNAVAILABLE;
- (instancetype) initWithCompletionHandler:(nullable VNRequestCompletionHandler)completionHandler NS_UNAVAILABLE;


@end



NS_ASSUME_NONNULL_END
