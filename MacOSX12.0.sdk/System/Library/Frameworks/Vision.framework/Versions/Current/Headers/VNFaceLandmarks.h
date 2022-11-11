//
//  VNFaceLandmarks.h
//  Vision
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CGGeometry.h>
#import <Vision/VNDefines.h>
#import <Vision/VNTypes.h>
#import <simd/simd.h>

#import <Vision/VNRequestRevisionProviding.h>


NS_ASSUME_NONNULL_BEGIN


/*!
 @class VNFaceLandmarkRegion
 @brief VNFaceLandmarkRegion is an immutable object acting as a collection of landmark points for defining a specific region of the face (including potentially all of the landmark points for a face). The VNFaceLandmarkRegion is an abstract base class.
 */

API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
@interface VNFaceLandmarkRegion : NSObject<NSCopying, NSSecureCoding, VNRequestRevisionProviding>

+ (instancetype) new NS_UNAVAILABLE;
- (instancetype) init NS_UNAVAILABLE;

/*!
 @brief pointCount returns the amount of points in a given region. This can be zero if no points for a region could be found.
 */
@property (readonly) NSUInteger pointCount;

@end


/*!
 @class VNFaceLandmarkRegion2D
 @brief VNFaceLandmarkRegion2D gives access to the 2D landmark points for the region. The points are stored as vector_float2 and must not be modified.
 */

API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
@interface VNFaceLandmarkRegion2D : VNFaceLandmarkRegion

/*!
	@brief	Obtains the array of normalized landmark points.
 
	@discussion	Provides the address of a buffer containing the array of CGPoints representing the landmark points.  This buffer is owned by the target object and is guaranteed to exist as long as the VNFaceLandmarkRegion2D does.

	@return the address of the array of pointCount points.
*/
@property (readonly, assign, nullable) const CGPoint* normalizedPoints NS_RETURNS_INNER_POINTER;


/*!
	@brief	Provides the array of landmark points in the coordinate space of a specific image size.
	
	@discussion	Provides the address of a buffer containing the array of CGPoints representing the landmark points in the coordinate space of a specific image size.  This buffer is owned by the target object and is guaranteed to exist as long as the VNFaceLandmarkRegion2D does.

	@param	imageSize			The pixel dimensions of the image in which the landmark points are being presented.
	
	@return the address of the array of pointCount points, or NULL if the conversion could not take place.
*/
- (const CGPoint*) pointsInImageOfSize:(CGSize)imageSize NS_RETURNS_INNER_POINTER;


/*!
 @brief    Obtains the array of accuracy placement estimates per landmark point.
 
 @discussion    Provides the NSArray object containing landmarks accuracy placement estimates per landmark point. This property is only
                populated when VNDetectFaceLandmarksRequest object is configured with VNRequestFaceLandmarksConstellation76Points. It is
                set to nil for other constellations
 
 @return NSArray object of NSNumber(s) initialized to floating point values.
 */
@property (readonly, nullable) NSArray<NSNumber*>* precisionEstimatesPerPoint API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0));


@end



/*!
 @class VNFaceLandmarks
 @brief VNFaceLandmarks2D is the result of a face landmarks request. It is an abstract base class.
 
 */
API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
@interface VNFaceLandmarks : NSObject<NSCopying, NSSecureCoding, VNRequestRevisionProviding>

- (instancetype) init NS_UNAVAILABLE;

/*!
 @brief a confidence estimate for the returned landmarks.
 */
@property (readonly) VNConfidence confidence;

@end



/*!
 @class VNFaceLandmarks2D
 @brief VNFaceLandmarks2D is the result of a face landmarks 2D request, containing detected facial landmark points organized into VNFaceLandmarkRegion2D regions. The points are accessible as a full list, or as sub-gruops representing pre-defined facial regions.
 
 */
API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
@interface VNFaceLandmarks2D : VNFaceLandmarks
/*!
 @brief allPoints the region containing all face landmark points.
 */
@property (readonly, nullable) VNFaceLandmarkRegion2D *allPoints;

/*!
 @brief faceContour the region containing the points that describe the face contour from cheek over chin to cheek.
 */
@property (readonly, nullable) VNFaceLandmarkRegion2D *faceContour;

/*!
 @brief leftEye the region containing the points describing the outline of the left eye.
 */
@property (readonly, nullable) VNFaceLandmarkRegion2D *leftEye;

/*!
 @brief rightEye the region containing the points describing the outline of the right eye.
 */
@property (readonly, nullable) VNFaceLandmarkRegion2D *rightEye;

/*!
 @brief leftEyebrow the region containing the points describing the trace of the left eyebrow.
 */
@property (readonly, nullable) VNFaceLandmarkRegion2D *leftEyebrow;

/*!
 @brief rightEyebrow the region containing the points describing the trace of the right eyebrow.
 */
@property (readonly, nullable) VNFaceLandmarkRegion2D *rightEyebrow;

/*!
 @brief nose the region containing the points describing the outline of the nose.
 */
@property (readonly, nullable) VNFaceLandmarkRegion2D *nose;

/*!
 @brief noseCrest the region containing the points describing the trace of the center crest of the nose.
 */
@property (readonly, nullable) VNFaceLandmarkRegion2D *noseCrest;

/*!
 @brief medianLine the region containing the points describing the trace of the center line of the face.
 */
@property (readonly, nullable) VNFaceLandmarkRegion2D *medianLine;

/*!
 @brief outer lips the region containing the points describing the outline of the outside of the lips.
 */
@property (readonly, nullable) VNFaceLandmarkRegion2D *outerLips;

/*!
 @brief innerLips the region containing the points describing the outline of the space between the of the lips.
 */
@property (readonly, nullable) VNFaceLandmarkRegion2D *innerLips;

/*!
 @brief leftPupil the region containing the point where the left pupil is located.  This value may be inaccurate if
 the face isBlinking.
 */
@property (readonly, nullable) VNFaceLandmarkRegion2D *leftPupil;

/*!
 @brief rightPupil the region containing the point where the right pupil is located.  This value may be inaccurate if
 the face isBlinking.
 */
@property (readonly, nullable) VNFaceLandmarkRegion2D *rightPupil;


@end


NS_ASSUME_NONNULL_END
