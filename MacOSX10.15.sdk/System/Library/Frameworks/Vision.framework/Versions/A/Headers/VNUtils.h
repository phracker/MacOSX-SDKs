//
//  VNUtils.h
//  Vision
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <simd/simd.h>

#import <Vision/VNDefines.h>
#import <Vision/VNTypes.h>



NS_ASSUME_NONNULL_BEGIN


/*!
	@brief	The normalized identity rect of { {0, 0}, {1, 1} }.
*/
VN_EXPORT const CGRect VNNormalizedIdentityRect API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0));


/*!
	@discussion	Determines whether or not the normalized rect describes the identity rect of { {0, 0}, {1, 1} }.

	@param	normalizedRect			The rectangle in the normalized coordinate space of [0..1].
	
	@return YES if the rect is the identity rect; otherwise, NO.
*/
VN_EXPORT bool VNNormalizedRectIsIdentityRect(CGRect normalizedRect) API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0));


/*!
	@discussion	Returns a point in (possibly non-integral) image coordinates that is projected from a point in a normalized coordinate space.

	@param	normalizedPoint			The point in the normalized coordinate space of [0..1].
	
	@param	imageWidth				The pixel width of the image.

	@param	imageHeight				The pixel height of the image.

	@return the point in normalized coordinates.
*/
VN_EXPORT CGPoint VNImagePointForNormalizedPoint(CGPoint normalizedPoint, size_t imageWidth, size_t imageHeight) API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0));


/*!
	@discussion	Returns a rectangle in (possibly non-integral) image coordinates that is projected from a rectangle in a normalized coordinate space.

	@param	normalizedRect			The rectangle in the normalized coordinate space of [0..1].
	
	@param	imageWidth				The pixel width of the image.

	@param	imageHeight				The pixel height of the image.

	@return the rectangle in pixel coordinates.
*/
VN_EXPORT CGRect VNImageRectForNormalizedRect(CGRect normalizedRect, size_t imageWidth, size_t imageHeight) API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0));


/*!
	@discussion	Returns an image rectangle in normalized coordinates.

	@param	imageRect				The rectangle in image coordinate space.
	
	@param	imageWidth				The pixel width of the image.

	@param	imageHeight				The pixel height of the image.

	@return the normalized rectangle.
*/
VN_EXPORT CGRect VNNormalizedRectForImageRect(CGRect imageRect, size_t imageWidth, size_t imageHeight) API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0));


/*!
	@discussion Returns the cooridnate of a given face landmark point relative to a face bounding box.
	
	@param	faceLandmarkPoint		A face landmark point obtained from a VNFaceLandmarkRegion2D instance.
	
	@param	faceBoundingBox			The normalized bounding box of a face obtaining from a VNFaceObservation.
	
	@param	imageWidth				The pixel width of the image from which the VNFaceObservation was generated.
	
	@param	imageHeight				The pixel height of the image from which the VNFaceObservation was generated.

	@return	the face landmark point in face bounding box coordinates.
*/
VN_EXPORT CGPoint VNNormalizedFaceBoundingBoxPointForLandmarkPoint(vector_float2 faceLandmarkPoint, CGRect faceBoundingBox, size_t imageWidth, size_t imageHeight) API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0));


/*!
	@discussion Returns the (possibly non-integral) image cooridnate of a given face landmark point.
	
	@param	faceLandmarkPoint		A face landmark point obtained from a VNFaceLandmarkRegion2D instance.
	
	@param	faceBoundingBox			The normalized bounding box of a face obtaining from a VNFaceObservation.
	
	@param	imageWidth				The pixel width of the image from which the VNFaceObservation was generated.
	
	@param	imageHeight				The pixel height of the image from which the VNFaceObservation was generated.

	@return	the face landmark point in image coordinates.
*/
VN_EXPORT CGPoint VNImagePointForFaceLandmarkPoint(vector_float2 faceLandmarkPoint, CGRect faceBoundingBox, size_t imageWidth, size_t imageHeight) API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0));


/*!
	@brief Obtain the size, in bytes, of a given element type.
 
	@param	elementType		The element type.
 
	@return a byte count, or 0 if the element type is unknown.
*/
VN_EXPORT NSUInteger VNElementTypeSize(VNElementType elementType) API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0));


NS_ASSUME_NONNULL_END
