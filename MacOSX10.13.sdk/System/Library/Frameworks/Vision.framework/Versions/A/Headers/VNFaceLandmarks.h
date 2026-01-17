//
//  VNFaceLandmarks.h
//  Vision
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Vision/VNDefines.h>
#import <Vision/VNTypes.h>
#import <simd/simd.h>


NS_ASSUME_NONNULL_BEGIN


/*!
 @class VNFaceLandmarkRegion
 @brief VNFaceLandmarkRegion are accessors to the landmark points of that specific region. The VNFaceLandmarkRegion is an abstract baseclass.
 */

API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
@interface VNFaceLandmarkRegion : NSObject
/*!
 @brief pointCount returns the amount of points in a given region. This can be zero if no points for a region could be found.
 */
@property (readonly) NSUInteger  pointCount;

@end


/*!
 @class VNFaceLandmarkRegion
 @brief VNFaceLandmarkRegion2D gives access to the landmark points in 2D. The points are stored as vector_float2 and must not be modified..
 */

API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
@interface VNFaceLandmarkRegion2D : VNFaceLandmarkRegion

/*!
 @brief All points in the region in form of a C array which can be accessed by points[idx].
 */
@property (readonly, nullable) const vector_float2 *points; // the values of the points cannot be modified

/*!
 @brief Returns a landmark point at the given index, if the index is valid otherwise vector_float2 of {0.0f, 0.0f} gets returned.
 */
- (vector_float2)pointAtIndex:(NSUInteger)index;

@end




API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
@interface VNFaceLandmarks : NSObject

@property (readonly) VNConfidence confidence;

@end



/*!
 @class VNFaceLandmarks2D
 @brief VNFaceLandmarks2D is the result of a face landmarks 2D request.
 
 */
API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
@interface VNFaceLandmarks2D : VNFaceLandmarks
/*!
 @brief allPoints contains all face landmark points.
 */
@property (readonly, nullable) VNFaceLandmarkRegion2D *allPoints;

/*!
 @brief faceContour contains the point that describe the face contour from cheek over chin to cheek.
 */
@property (readonly, nullable) VNFaceLandmarkRegion2D *faceContour;

/*!
 @brief leftEye contains the points describing the outline of the left eye.
 */
@property (readonly, nullable) VNFaceLandmarkRegion2D *leftEye;

/*!
 @brief rightEye contains the points describing the outline of the right eye.
 */
@property (readonly, nullable) VNFaceLandmarkRegion2D *rightEye;

/*!
 @brief leftEyebrow contains the points describing the trace of the left eyebrow.
 */
@property (readonly, nullable) VNFaceLandmarkRegion2D *leftEyebrow;

/*!
 @brief rightEyebrow contains the points describing the trace of the right eyebrow.
 */
@property (readonly, nullable) VNFaceLandmarkRegion2D *rightEyebrow;

/*!
 @brief nose contains the points describing the outline of the nose.
 */
@property (readonly, nullable) VNFaceLandmarkRegion2D *nose;

/*!
 @brief noseCrest contains the points describing the trace of the center crest of the nose.
 */
@property (readonly, nullable) VNFaceLandmarkRegion2D *noseCrest;

/*!
 @brief medianLine contains the points describing the trace of the center line of the face.
 */
@property (readonly, nullable) VNFaceLandmarkRegion2D *medianLine;

/*!
 @brief outer lips contains the points describing the outline of the outside of the lips.
 */
@property (readonly, nullable) VNFaceLandmarkRegion2D *outerLips;

/*!
 @brief innerLips contains the points describing the outline of the space between the of the lips.
 */
@property (readonly, nullable) VNFaceLandmarkRegion2D *innerLips;

/*!
 @brief leftPupil contains the point where the left pupil is located.  This value may be inaccurate if
 the face isBlinking.
 */
@property (readonly, nullable) VNFaceLandmarkRegion2D *leftPupil;

/*!
 @brief rightPupil contains the point where the right pupil is located.  This value may be inaccurate if
 the face isBlinking.
 */
@property (readonly, nullable) VNFaceLandmarkRegion2D *rightPupil;


@end


NS_ASSUME_NONNULL_END
