//
//  VNTargetedImageRequest.h
//  Vision
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <CoreVideo/CVPixelBuffer.h>
#import <CoreImage/CoreImage.h>

#import <Vision/VNRequest.h>
#import <Vision/VNRequestHandler.h>


NS_ASSUME_NONNULL_BEGIN


/*!
	@brief A request that requires an initial image as a starting point for its work.
*/
API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
@interface VNTargetedImageRequest : VNImageBasedRequest

- (instancetype) init  NS_UNAVAILABLE;
- (instancetype) initWithCompletionHandler:(nullable VNRequestCompletionHandler)completionHandler NS_UNAVAILABLE;



#pragma mark • Targeting CVPixelBuffer


/*!
	@brief Create a new request that targets an image in a pixel buffer.
	
	@param	pixelBuffer			The pixel buffer containing the targeted image.
	@param	options				A dictionary with options specifying auxiliary information for the image.
*/
- (instancetype) initWithTargetedCVPixelBuffer:(CVPixelBufferRef)pixelBuffer options:(NSDictionary<VNImageOption, id> *)options;


/*!
	@brief Create a new request that targets an image in a pixel buffer.
	
	@param	pixelBuffer			The pixel buffer containing the targeted image.
	@param	options				A dictionary with options specifying auxiliary information for the image.
	@param	completionHandler	The block that is invoked when the request has been performed.
*/
- (instancetype) initWithTargetedCVPixelBuffer:(CVPixelBufferRef)pixelBuffer options:(NSDictionary<VNImageOption, id> *)options completionHandler:(nullable VNRequestCompletionHandler)completionHandler;


/*!
	@brief Create a new request that targets an image in a pixel buffer.
	
	@param	pixelBuffer			The pixel buffer containing the targeted image.
	@param	orientation			The orientation of the image/buffer based on the EXIF specification. For details see kCGImagePropertyOrientation. The value has to be an integer from 1 to 8. This supersedes every other orientation information.
	@param	options				A dictionary with options specifying auxiliary information for the image.
*/
- (instancetype) initWithTargetedCVPixelBuffer:(CVPixelBufferRef)pixelBuffer orientation:(CGImagePropertyOrientation)orientation options:(NSDictionary<VNImageOption, id> *)options;


/*!
	@brief Create a new request that targets an image in a pixel buffer.
	
	@param	pixelBuffer			The pixel buffer containing the targeted image.
	@param	orientation			The orientation of the image/buffer based on the EXIF specification. For details see kCGImagePropertyOrientation. The value has to be an integer from 1 to 8. This supersedes every other orientation information.
	@param	options				A dictionary with options specifying auxiliary information for the image.
	@param	completionHandler	The block that is invoked when the request has been performed.
*/
- (instancetype) initWithTargetedCVPixelBuffer:(CVPixelBufferRef)pixelBuffer orientation:(CGImagePropertyOrientation)orientation options:(NSDictionary<VNImageOption, id> *)options completionHandler:(nullable VNRequestCompletionHandler)completionHandler;




#pragma mark • Targeting CGImage


/*!
	@brief Create a new request with a targeted CGImage.
	
	@param	cgImage				The CGImageRef of the targeted image.
	@param	options				A dictionary with options specifying auxiliary information for the image.
*/
- (instancetype) initWithTargetedCGImage:(CGImageRef)cgImage options:(NSDictionary<VNImageOption, id> *)options;


/*!
	@brief Create a new request with a targeted CGImage.
	
	@param	cgImage				The CGImageRef of the targeted image.
	@param	options				A dictionary with options specifying auxiliary information for the image.
	@param	completionHandler	The block that is invoked when the request has been performed.
*/
- (instancetype) initWithTargetedCGImage:(CGImageRef)cgImage options:(NSDictionary<VNImageOption, id> *)options completionHandler:(nullable VNRequestCompletionHandler)completionHandler;


/*!
	@brief Create a new request with a targeted CGImage.
	
	@param	cgImage				The CGImageRef of the targeted image.
	@param	orientation			The orientation of the image/buffer based on the EXIF specification. For details see kCGImagePropertyOrientation. The value has to be an integer from 1 to 8. This supersedes every other orientation information.
	@param	options				A dictionary with options specifying auxiliary information for the image.
*/
- (instancetype) initWithTargetedCGImage:(CGImageRef)cgImage orientation:(CGImagePropertyOrientation)orientation options:(NSDictionary<VNImageOption, id> *)options;


/*!
	@brief Create a new request with a targeted CGImage.
	
	@param	cgImage				The CGImageRef of the targeted image.
	@param	orientation			The orientation of the image/buffer based on the EXIF specification. For details see kCGImagePropertyOrientation. The value has to be an integer from 1 to 8. This supersedes every other orientation information.
	@param	options				A dictionary with options specifying auxiliary information for the image.
	@param	completionHandler	The block that is invoked when the request has been performed.
*/
- (instancetype) initWithTargetedCGImage:(CGImageRef)cgImage orientation:(CGImagePropertyOrientation)orientation options:(NSDictionary<VNImageOption, id> *)options completionHandler:(nullable VNRequestCompletionHandler)completionHandler;




#pragma mark • Targeting CIImage


/*!
	@brief Create a new request with a targeted CIImage.
	
	@param	ciImage				The CIImage of the targeted image.
	@param	options				A dictionary with options specifying auxiliary information for the image.
*/
- (instancetype) initWithTargetedCIImage:(CIImage *)ciImage options:(NSDictionary<VNImageOption, id> *)options;


/*!
	@brief Create a new request with a targeted CIImage.
	
	@param	ciImage				The CIImage of the targeted image.
	@param	options				A dictionary with options specifying auxiliary information for the image.
	@param	completionHandler	The block that is invoked when the request has been performed.
*/
- (instancetype) initWithTargetedCIImage:(CIImage *)ciImage options:(NSDictionary<VNImageOption, id> *)options completionHandler:(nullable VNRequestCompletionHandler)completionHandler;


/*!
	@brief Create a new request with a targeted CIImage.
	
	@param	ciImage				The CIImage of the targeted image.
	@param	orientation			The orientation of the image/buffer based on the EXIF specification. For details see kCGImagePropertyOrientation. The value has to be an integer from 1 to 8. This supersedes every other orientation information.
	@param	options				A dictionary with options specifying auxiliary information for the image.
*/
- (instancetype) initWithTargetedCIImage:(CIImage *)ciImage orientation:(CGImagePropertyOrientation)orientation options:(NSDictionary<VNImageOption, id> *)options;


/*!
	@brief Create a new request with a targeted CIImage.
	
	@param	ciImage				The CIImage of the targeted image.
	@param	orientation			The orientation of the image/buffer based on the EXIF specification. For details see kCGImagePropertyOrientation. The value has to be an integer from 1 to 8. This supersedes every other orientation information.
	@param	options				A dictionary with options specifying auxiliary information for the image.
	@param	completionHandler	The block that is invoked when the request has been performed.
*/
- (instancetype) initWithTargetedCIImage:(CIImage *)ciImage orientation:(CGImagePropertyOrientation)orientation options:(NSDictionary<VNImageOption, id> *)options completionHandler:(nullable VNRequestCompletionHandler)completionHandler;




#pragma mark • Targeting NSURL


/*!
	@brief Create a new request with a targeted image URL.
	
	@param	imageURL			The URL of the targeted image.
	@param	options				A dictionary with options specifying auxiliary information for the image.
*/
- (instancetype) initWithTargetedImageURL:(NSURL *)imageURL options:(NSDictionary<VNImageOption, id> *)options;


/*!
	@brief Create a new request with a targeted image URL.
	
	@param	imageURL			The URL of the targeted image.
	@param	options				A dictionary with options specifying auxiliary information for the image.
	@param	completionHandler	The block that is invoked when the request has been performed.
*/
- (instancetype) initWithTargetedImageURL:(NSURL *)imageURL options:(NSDictionary<VNImageOption, id> *)options completionHandler:(nullable VNRequestCompletionHandler)completionHandler;


/*!
	@brief Create a new request with a targeted image URL.
	
	@param	imageURL			The URL of the targeted image.
	@param	orientation			The orientation of the image/buffer based on the EXIF specification. For details see kCGImagePropertyOrientation. The value has to be an integer from 1 to 8. This supersedes every other orientation information.
	@param	options				A dictionary with options specifying auxiliary information for the image.
*/
- (instancetype) initWithTargetedImageURL:(NSURL *)imageURL orientation:(CGImagePropertyOrientation)orientation options:(NSDictionary<VNImageOption, id> *)options;


/*!
	@brief Create a new request with a targeted image URL.
	
	@param	imageURL			The URL of the targeted image.
	@param	orientation			The orientation of the image/buffer based on the EXIF specification. For details see kCGImagePropertyOrientation. The value has to be an integer from 1 to 8. This supersedes every other orientation information.
	@param	options				A dictionary with options specifying auxiliary information for the image.
	@param	completionHandler	The block that is invoked when the request has been performed.
*/
- (instancetype) initWithTargetedImageURL:(NSURL *)imageURL orientation:(CGImagePropertyOrientation)orientation options:(NSDictionary<VNImageOption, id> *)options completionHandler:(nullable VNRequestCompletionHandler)completionHandler;




#pragma mark • Targeting NSData


/*!
	@brief Create a new request with a targeted image data.
	
	@param imageData			The data of the targeted image.
	@param	options				A dictionary with options specifying auxiliary information for the image.
*/
- (instancetype) initWithTargetedImageData:(NSData *)imageData options:(NSDictionary<VNImageOption, id> *)options;


/*!
	@brief Create a new request with a targeted image data.
	
	@param imageData			The data of the targeted image.
	@param	options				A dictionary with options specifying auxiliary information for the image.
	@param	completionHandler	The block that is invoked when the request has been performed.
*/
- (instancetype) initWithTargetedImageData:(NSData *)imageData options:(NSDictionary<VNImageOption, id> *)options completionHandler:(nullable VNRequestCompletionHandler)completionHandler;


/*!
	@brief Create a new request with a targeted image data.
	
	@param imageData			The data of the targeted image.
	@param	orientation			The orientation of the image/buffer based on the EXIF specification. For details see kCGImagePropertyOrientation. The value has to be an integer from 1 to 8. This supersedes every other orientation information.
	@param	options				A dictionary with options specifying auxiliary information for the image.
*/
- (instancetype) initWithTargetedImageData:(NSData *)imageData orientation:(CGImagePropertyOrientation)orientation options:(NSDictionary<VNImageOption, id> *)options;


/*!
	@brief Create a new request with a targeted image data.
	
	@param imageData			The data of the targeted image.
	@param	orientation			The orientation of the image/buffer based on the EXIF specification. For details see kCGImagePropertyOrientation. The value has to be an integer from 1 to 8. This supersedes every other orientation information.
	@param	options				A dictionary with options specifying auxiliary information for the image.
	@param	completionHandler	The block that is invoked when the request has been performed.
*/
- (instancetype) initWithTargetedImageData:(NSData *)imageData orientation:(CGImagePropertyOrientation)orientation options:(NSDictionary<VNImageOption, id> *)options completionHandler:(nullable VNRequestCompletionHandler)completionHandler;


@end



NS_ASSUME_NONNULL_END
