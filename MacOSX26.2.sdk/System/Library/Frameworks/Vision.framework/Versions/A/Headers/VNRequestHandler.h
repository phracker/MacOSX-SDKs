//
//  VNRequestHandler.h
//  Vision
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//
/*!
 @header There are two types of request handlers: VNSequenceRequestHandler and VNImageRequestHandler.
 
 Each of them are for scheduling one or more @link VNRequest @/link objects for processing. The type of request may dictate which kind of request handler to use. Some VNRequests can be used with both, while others can only be used with a specific one. Please refer to the documentation of the specific request. The general distinction between the two is that requests that are specific to an image (or buffer) would use the VNImageRequestHandler. For requests that span over multiple image buffers the VNSequenceRequestHandler will hold on to past request data to allow algorithms to work on multiple buffers in a sequence, and that sequence can be dynamic.
 
 */


#import <Foundation/Foundation.h>
#import <CoreVideo/CVPixelBuffer.h>
#import <ImageIO/ImageIO.h>
#import <CoreMedia/CoreMedia.h>

#import <Vision/VNDefines.h>
#import <Vision/VNRequest.h>

NS_ASSUME_NONNULL_BEGIN

@class CIImage;
@class AVDepthData;
/*!
 @brief Options keys passed into the VNImageRequestHandler creations or requests that take an auxiliary image. These are options that either describe specific properties of an image like the VNImageOptionCameraIntrinsics or how an image needs to be handled like the VNImageOptionCIContext.
*/
typedef NSString * VNImageOption NS_STRING_ENUM;

/*!
 @const      VNImageOptionProperties
 @abstract   VNImageOptionProperties is the dictionary from CGImageSourceCopyPropertiesAtIndex. This contains metadata that can be used by some algorithms like horizon detection.
 */

VN_EXPORT VNImageOption const VNImageOptionProperties API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0));

/*!
 @brief VNImageOptionCameraIntrinsics  Specifies the camera intrinsics as an NSData or CFData representing a matrix_float3x3. See kCMSampleBufferAttachmentKey_CameraIntrinsicMatrix for details
 @discussion
     Camera intrinsic matrix is a CFData containing a matrix_float3x3, which is column-major. It has the following contents:
     fx	0	ox
     0	fy	oy
     0	0	1
     fx and fy are the focal length in pixels. For square pixels, they will have the same value.
     ox and oy are the coordinates of the principal point. The origin is the upper left of the frame.
 @note When using a CMSampleBuffer as an input and that sample buffer has camera intrinsics attached to it, Vision will use the camera intrinsic from there unless overwritten by passing in as an explicit option which will take precedence.

 */
VN_EXPORT VNImageOption const VNImageOptionCameraIntrinsics API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0));

/*!
 @brief VNImageOptionCIContext  Specifies the CIContext to be used in Core Image operations of request handler. If this is not specified, Vision will create its own CIContext. This option is helpful when the passed in CIImage is the result of a CIFilter chain that has been executed on a CIContext or uses outputs of a CIImage on a given CIContext as they don't have to transfer to other contexts.
 */

VN_EXPORT VNImageOption const VNImageOptionCIContext API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0));

/*!
 @brief Performs requests on a single image.
 @discussion The VNImageRequestHandler is created with an image that is used to be used for the requests a client might want to schedule. The VNImageRequestHandler retains, but never modifies, the image source for its entire lifetime. The client also must not modify the content of the image source once the VNImageRequestHandler is created otherwise the results are undefined.
             The VNImageRequestHandler can choose to also cache intermediate representation of the image or other request-specific information for the purposes of runtime performance.
 */
API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
@interface VNImageRequestHandler : NSObject

- (instancetype)init NS_UNAVAILABLE;

/*!
 @brief initWithCVPixelBuffer:options creates a VNImageRequestHandler to be used for performing requests against the image passed in as buffer.
 
 @param pixelBuffer A CVPixelBuffer containing the image to be used for performing the requests. The content of the buffer cannot be modified for the lifetime of the VNImageRequestHandler.
 @param options A dictionary with options specifying auxiliary information for the buffer/image like VNImageOptionCameraIntrinsics
 */
- (instancetype)initWithCVPixelBuffer:(CVPixelBufferRef)pixelBuffer options:(NSDictionary<VNImageOption, id> *)options;

/*!
 @brief initWithCVPixelBuffer:options creates a VNImageRequestHandler to be used for performing requests against the image passed in as buffer.
 
 @param pixelBuffer A CVPixelBuffer containing the image to be used for performing the requests. The content of the buffer cannot be modified for the lifetime of the VNImageRequestHandler.
 @param orientation The orientation of the image/buffer based on the EXIF specification. For details see kCGImagePropertyOrientation. The value has to be an integer from 1 to 8. This supersedes every other orientation information.
 @param options A dictionary with options specifying auxiliary information for the buffer/image like VNImageOptionCameraIntrinsics
 */
- (instancetype)initWithCVPixelBuffer:(CVPixelBufferRef)pixelBuffer orientation:(CGImagePropertyOrientation)orientation options:(NSDictionary<VNImageOption, id> *)options;

/*!
 @brief initWithCVPixelBuffer:depthData:orientation:options creates a VNImageRequestHandler to be used for performing requests against the image passed in as buffer with depth information.
 @param pixelBuffer A CVPixelBuffer containing the image to be used for performing the requests. The content of the buffer cannot be modified for the lifetime of the VNImageRequestHandler.
 @param depthData An AVDepthData instance associated with the pixelBuffer
 @param orientation The orientation of the image and depth buffers based on the EXIF specification. For details see kCGImagePropertyOrientation. The value has to be an integer from 1 to 8. This supersedes every other orientation information and should match for both buffers.
 @param options A dictionary with options specifying auxiliary information for the buffer/image
 */
- (instancetype)initWithCVPixelBuffer:(CVPixelBufferRef)pixelBuffer
                            depthData:(AVDepthData*)depthData
                          orientation:(CGImagePropertyOrientation)orientation
                              options:(NSDictionary<VNImageOption, id> *)options API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0));

/*!
 @brief initWithCGImage:options creates a VNImageRequestHandler to be used for performing requests against the image passed in as a CGImageRef.
 
 @param image A CGImageRef containing the image to be used for performing the requests. The content of the image cannot be modified.
 @param options A dictionary with options specifying auxiliary information for the buffer/image like VNImageOptionCameraIntrinsics
 */
- (instancetype)initWithCGImage:(CGImageRef)image options:(NSDictionary<VNImageOption, id> *)options;


/*!
 
 @brief initWithCGImage:options creates a VNImageRequestHandler to be used for performing requests against the image passed in as a CGImageRef.
 
 @param image A CGImageRef containing the image to be used for performing the requests. The content of the image cannot be modified.
 @param orientation The orientation of the image/buffer based on the EXIF specification. For details see kCGImagePropertyOrientation. The value has to be an integer from 1 to 8. This supersedes every other orientation information.
 @param options A dictionary with options specifying auxiliary information for the buffer/image like VNImageOptionCameraIntrinsics

 */
- (instancetype)initWithCGImage:(CGImageRef)image orientation:(CGImagePropertyOrientation)orientation options:(NSDictionary<VNImageOption, id> *)options;


/*!
 @brief initWithCIImage:options creates a VNImageRequestHandler to be used for performing requests against the image passed in as a CIImage.
 
 @param image A CIImage containing the image to be used for performing the requests. The content of the image cannot be modified.
 @param options A dictionary with options specifying auxiliary information for the buffer/image like VNImageOptionCameraIntrinsics
 
 
 @note:  Request results may not be accurate in simulator due to CI's inability to render certain pixel formats in the simulator. The orientation of the original image should be applied for instance by using imageByApplyingOrientation or use the initWithCIImage:options:orientation API.
 */
- (instancetype)initWithCIImage:(CIImage *)image options:(NSDictionary<VNImageOption, id> *)options;


/*!
 @brief initWithCIImage:options:orientation creates a VNImageRequestHandler to be used for performing requests against the image passed in as a CIImage.
 
 @param image A CIImage containing the image to be used for performing the requests. The content of the image cannot be modified.
 @param orientation The orientation of the image/buffer based on the EXIF specification. For details see kCGImagePropertyOrientation. The value has to be an integer from 1 to 8. This supersedes every other orientation information.
 @param options A dictionary with options specifying auxiliary information for the buffer/image like VNImageOptionCameraIntrinsics

 
 @note:  Request results may not be accurate in simulator due to CI's inability to render certain pixel formats in the simulator
 */
- (instancetype)initWithCIImage:(CIImage *)image orientation:(CGImagePropertyOrientation)orientation options:(NSDictionary<VNImageOption, id> *)options;


/*!
 @brief initWithURL:options creates a VNImageRequestHandler to be used for performing requests against an image specified by it's URL
 
 @param imageURL A URL pointing at an image to be used for performing the requests. The image has to be in a format that is supported by ImageIO. The content of the image cannot be modified.
 @param options A dictionary with options specifying auxiliary information for the buffer/image like VNImageOptionCameraIntrinsics
 
 @note:  Request results may not be accurate in simulator due to CI's inability to render certain pixel formats in the simulator
 */
- (instancetype)initWithURL:(NSURL *)imageURL options:(NSDictionary<VNImageOption, id> *)options;


/*!
 @brief initWithURL:options creates a VNImageRequestHandler to be used for performing requests against an image specified by it's URL
 
 @param imageURL A URL pointing at an image to be used for performing the requests. The image has to be in a format that is supported by ImageIO. The content of the image cannot be modified.
 @param orientation The orientation of the image/buffer based on the EXIF specification. For details see kCGImagePropertyOrientation. The value has to be an integer from 1 to 8. This supersedes every other orientation information.
 @param options A dictionary with options specifying auxiliary information for the buffer/image like VNImageOptionCameraIntrinsics

 @note:  Request results may not be accurate in simulator due to CI's inability to render certain pixel formats in the simulator
 */
- (instancetype)initWithURL:(NSURL *)imageURL orientation:(CGImagePropertyOrientation)orientation options:(NSDictionary<VNImageOption, id> *)options;


/*!
 @brief initWithData:options creates a VNImageRequestHandler to be used for performing requests against an image contained in an NSData object.
 
 @param imageData An NSData object containing the content of the image to be used for performing the requests. See CIImage imageWithData for supported format. The content of the image cannot be modified.
 @param options A dictionary with options specifying auxiliary information for the buffer/image like VNImageOptionCameraIntrinsics
 
 @note:  Request results may not be accurate in simulator due to CI's inability to render certain pixel formats in the simulator
 
 */
- (instancetype)initWithData:(NSData *)imageData options:(NSDictionary<VNImageOption, id> *)options;


/*!
 @brief initWithData:options creates a VNImageRequestHandler to be used for performing requests against an image contained in an NSData object.
 
 @param imageData An NSData object containing the content of the image to be used for performing the requests. See CIImage imageWithData for supported format. The content of the image cannot be modified.
 @param orientation The orientation of the image/buffer based on the EXIF specification. For details see kCGImagePropertyOrientation. The value has to be an integer from 1 to 8. This supersedes every other orientation information.
 @param options A dictionary with options specifying auxiliary information for the buffer/image like VNImageOptionCameraIntrinsics

 @note:  Request results may not be accurate in simulator due to CI's inability to render certain pixel formats in the simulator
 
 */
- (instancetype)initWithData:(NSData *)imageData orientation:(CGImagePropertyOrientation)orientation options:(NSDictionary<VNImageOption, id> *)options;


/*!
 @brief Creates a VNImageRequestHandler to be used for performing requests against the image buffer contained in the CMSampleBufferRef
 
 @param sampleBuffer A CMSampleBuffer containing the imageBuffer that will be used for performing the requests. Not all types of sample buffers are supported. They need to contain a CVImageBuffer, be valid and ready.
 @param options A dictionary with options specifying auxiliary information for the buffer/image like VNImageOptionCameraIntrinsics
 @note CMSampleBuffers can contain metadata like camera intrinsics that will be used by algorithms supporting it unless overwritten by the options.
 */
- (instancetype)initWithCMSampleBuffer:(CMSampleBufferRef)sampleBuffer options:(NSDictionary<VNImageOption, id> *)options API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));


/*!
 @brief Creates a VNImageRequestHandler to be used for performing requests against the image buffer contained in the CMSampleBufferRef
 
 @param sampleBuffer A CMSampleBuffer containing the imageBuffer that will be used for performing the requests. Not all types of sample buffers are supported. They need to contain a CVImageBuffer, be valid and ready.
 @param orientation The orientation of the image/buffer based on the EXIF specification. For details see kCGImagePropertyOrientation. The value has to be an integer from 1 to 8. This supersedes every other orientation information.
 @param options A dictionary with options specifying auxiliary information for the buffer/image like VNImageOptionCameraIntrinsics
 @note CMSampleBuffers can contain metadata like camera intrinsics that will be used by algorithms supporting it unless overwritten by the options.
 @note:  Because CoreImage is unable to render certain pixel formats in the iOS simulator, request results may not be accurate in those cases.
 */
- (instancetype)initWithCMSampleBuffer:(CMSampleBufferRef)sampleBuffer orientation:(CGImagePropertyOrientation)orientation options:(NSDictionary<VNImageOption, id> *)options API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));

/*!
 @brief Creates a VNImageRequestHandler to be used for performing requests against the image buffer contained in the CMSampleBufferRef
 
 @param sampleBuffer A CMSampleBuffer containing the imageBuffer that will be used for performing the requests. Not all types of sample buffers are supported. They need to contain a CVImageBuffer, be valid and ready.
 @param depthData An AVDepthData instance associated with the pixelBuffer
 @param orientation The orientation of the image and depth buffers based on the EXIF specification. For details see kCGImagePropertyOrientation. The value has to be an integer from 1 to 8. This supersedes every other orientation information and should match for both buffers.
 @param options A dictionary with options specifying auxiliary information for the buffer/image
 @note CMSampleBuffers can contain metadata like camera intrinsics that will be used by algorithms supporting it unless overwritten by the options.
 @note:  Because CoreImage is unable to render certain pixel formats in the iOS simulator, request results may not be accurate in those cases.
 */
- (instancetype)initWithCMSampleBuffer:(CMSampleBufferRef)sampleBuffer
                             depthData:(AVDepthData*)depthData
                           orientation:(CGImagePropertyOrientation)orientation
                               options:(NSDictionary<VNImageOption, id> *)options API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0));

/*!
 @brief performRequests schedules one or more VNRequests to be performed. The function returns once all requests have been finished.
 
 @discussion The results of the VNRequests as well any possible errors of the individual requests are reported in the VNRequests results and error properties.
 
 @param requests An NSArray of VNRequests that are to be performed.
 @param error Returns an error that happened during scheduling of the requests. Check individual requests results and errors for their respective success and failures. This parameter is optional.
 @return Returns true if all requests were scheduled and performed. Check individual requests results and errors for their respective success and failures.
 
 */
- (BOOL)performRequests:(NSArray<VNRequest *> *)requests error:(NSError **)error;


@end





/*!
 @brief Performs requests on a sequence of images.
 @discussion The VNSequenceRequestHandler is created without any specific image source.  The -performRequests:on<ImageSource>:error: methods will retain the image source for no longer than the lifetime of the call.
             The VNSequenceRequestHandler can choose to also cache state information related to the previously-processed image sources.
 */
API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
@interface VNSequenceRequestHandler : NSObject


/*!
	@brief	Creates a new object.
*/
- (instancetype)init NS_DESIGNATED_INITIALIZER;

/*!
	@brief Perform requests on an image in a CVPixelBuffer.
	
	@param	requests		The VNRequests to be performed on the image.
	
	@param	pixelBuffer		The CVPixelBuffer containing the image to be processed.
	
	@param	error			On input, a pointer to an error object. If an error occurs, this pointer is set to an actual error object containing the error information. You may specify NULL for this parameter if you do not want the error information.
 */
- (BOOL)performRequests:(NSArray<VNRequest *> *)requests onCVPixelBuffer:(CVPixelBufferRef)pixelBuffer error:(NSError **)error;

/*!
	@brief Perform requests on an image in a CVPixelBuffer.
	
	@param	requests		The VNRequests to be performed on the image.
	
	@param	pixelBuffer		The CVPixelBuffer containing the image to be processed.
	
	@param	orientation		The orientation of the image as it is captured in the pixel buffer.
	
	@param	error			On input, a pointer to an error object. If an error occurs, this pointer is set to an actual error object containing the error information. You may specify NULL for this parameter if you do not want the error information.
 */
- (BOOL)performRequests:(NSArray<VNRequest *> *)requests onCVPixelBuffer:(CVPixelBufferRef)pixelBuffer orientation:(CGImagePropertyOrientation)orientation error:(NSError **)error;

/*!
	@brief Perform requests on an image in a CGImageRef.
	
	@param	requests		The VNRequests to be performed on the image.
	
	@param	image			The CGImageRef containing the image to be processed.
	
	@param	error			On input, a pointer to an error object. If an error occurs, this pointer is set to an actual error object containing the error information. You may specify NULL for this parameter if you do not want the error information.
 */
- (BOOL)performRequests:(NSArray<VNRequest *> *)requests onCGImage:(CGImageRef)image error:(NSError **)error;


/*!
	@brief Perform requests on an image in a CGImageRef.
	
	@param	requests		The VNRequests to be performed on the image.
	
	@param	image			The CGImageRef containing the image to be processed.
	
	@param	orientation		The orientation of the image.
	
	@param	error			On input, a pointer to an error object. If an error occurs, this pointer is set to an actual error object containing the error information. You may specify NULL for this parameter if you do not want the error information.
 */
- (BOOL)performRequests:(NSArray<VNRequest *> *)requests onCGImage:(CGImageRef)image orientation:(CGImagePropertyOrientation)orientation error:(NSError **)error;


/*!
	@brief Perform requests on an image in a CIImage.
	
	@param	requests		The VNRequests to be performed on the image.
	
	@param	image			The CIImage containing the image to be processed.
	
	@param	error			On input, a pointer to an error object. If an error occurs, this pointer is set to an actual error object containing the error information. You may specify NULL for this parameter if you do not want the error information.
 */
- (BOOL)performRequests:(NSArray<VNRequest *> *)requests onCIImage:(CIImage*)image error:(NSError **)error;


/*!
	@brief Perform requests on an image in a CIImage.
	
	@param	requests		The VNRequests to be performed on the image.
	
	@param	image			The CIImage containing the image to be processed.
	
	@param	orientation		The orientation of the image.
	
	@param	error			On input, a pointer to an error object. If an error occurs, this pointer is set to an actual error object containing the error information. You may specify NULL for this parameter if you do not want the error information.
 */
- (BOOL)performRequests:(NSArray<VNRequest *> *)requests onCIImage:(CIImage*)image orientation:(CGImagePropertyOrientation)orientation error:(NSError **)error;


/*!
	@brief Perform requests on an image referenced by an URL.
	
	@param	requests		The VNRequests to be performed on the image.
	
	@param	imageURL		The URL of the image to be processed.  If this is not a file-based URL, the method will fail.
	
	@param	error			On input, a pointer to an error object. If an error occurs, this pointer is set to an actual error object containing the error information. You may specify NULL for this parameter if you do not want the error information.
 */
- (BOOL)performRequests:(NSArray<VNRequest *> *)requests onImageURL:(NSURL*)imageURL error:(NSError **)error;


/*!
	@brief Perform requests on an image referenced by an URL.
	
	@param	requests		The VNRequests to be performed on the image.
	
	@param	imageURL		The URL of the image to be processed.  If this is not a file-based URL, the method will fail.

	@param	orientation		The orientation of the image.
	
	@param	error			On input, a pointer to an error object. If an error occurs, this pointer is set to an actual error object containing the error information. You may specify NULL for this parameter if you do not want the error information.
 */
- (BOOL)performRequests:(NSArray<VNRequest *> *)requests onImageURL:(NSURL*)imageURL orientation:(CGImagePropertyOrientation)orientation error:(NSError **)error;


/*!
	@brief Perform requests on an image with its source format in memory.
	
	@param	requests		The VNRequests to be performed on the image.
	
	@param	imageData		The data representing the source format of the image to be processed.
	
	@param	error			On input, a pointer to an error object. If an error occurs, this pointer is set to an actual error object containing the error information. You may specify NULL for this parameter if you do not want the error information.
 */
- (BOOL)performRequests:(NSArray<VNRequest *> *)requests onImageData:(NSData*)imageData error:(NSError **)error;


/*!
	@brief Perform requests on an image with its source format in memory.
	
	@param	requests		The VNRequests to be performed on the image.
	
	@param	imageData		The data representing the source format of the image to be processed.

	@param	orientation		The orientation of the image.
	
	@param	error			On input, a pointer to an error object. If an error occurs, this pointer is set to an actual error object containing the error information. You may specify NULL for this parameter if you do not want the error information.
 */
- (BOOL)performRequests:(NSArray<VNRequest *> *)requests onImageData:(NSData*)imageData orientation:(CGImagePropertyOrientation)orientation error:(NSError **)error;


/*!
    @brief Perform requests on the image buffer contained in the CMSampleBufferRef.

	@param	requests		The VNRequests to be performed on the image.

	@param	sampleBuffer	A CMSampleBuffer containing an image that will be used for performing the requests. Not all types of sample buffers are supported. They need to contain a CVImageBuffer, be valid and ready.

	@param	error			On input, a pointer to an error object. If an error occurs, this pointer is set to an actual error object containing the error information. You may specify NULL for this parameter if you do not want the error information.
 */
- (BOOL)performRequests:(NSArray<VNRequest *> *)requests onCMSampleBuffer:(CMSampleBufferRef)sampleBuffer error:(NSError **)error API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));


/*!
    @brief Perform requests on the image buffer contained in the CMSampleBufferRef.
     
	@param	requests		The VNRequests to be performed on the image.
     
	@param	sampleBuffer	A CMSampleBuffer containing an image that will be used for performing the requests. Not all types of sample buffers are supported. They need to contain a CVImageBuffer, be valid and ready.
     
	@param	orientation		The orientation of the image.
     
	@param	error			On input, a pointer to an error object. If an error occurs, this pointer is set to an actual error object containing the error information. You may specify NULL for this parameter if you do not want the error information.
 */
- (BOOL)performRequests:(NSArray<VNRequest *> *)requests onCMSampleBuffer:(CMSampleBufferRef)sampleBuffer orientation:(CGImagePropertyOrientation)orientation error:(NSError **)error API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));

@end




NS_ASSUME_NONNULL_END
