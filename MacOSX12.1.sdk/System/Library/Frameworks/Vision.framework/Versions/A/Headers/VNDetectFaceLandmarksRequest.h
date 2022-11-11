//
//  VNDetectFaceLandmarksRequest.h
//  Vision
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <Vision/VNRequest.h>
#import <Vision/VNFaceObservationAccepting.h>
#import <Vision/VNObservation.h>


NS_ASSUME_NONNULL_BEGIN


/*!
 @brief    Constellation type defines how many landmark points are used to map a face. Revisions 1, 2, and 3 support 65 points, where Rev3 also supports 76 points.
 */
typedef NS_ENUM(NSUInteger, VNRequestFaceLandmarksConstellation)
{
    VNRequestFaceLandmarksConstellationNotDefined = 0,
    VNRequestFaceLandmarksConstellation65Points,
    VNRequestFaceLandmarksConstellation76Points
};


/*!
	@brief A request that will produce face landmark information.

	@details This request will generate VNFaceObservation objects with the landmarks property populated with information describing face landmarks. If VNFaceObservations are provided via the VNFaceObservationAccepting protocol without the landmarks property populated, new observations will be created as copies of the input VNFaceObservations with the landmarks property populated. If the landmarks property has already been populated, the original VNFaceObservations will be returned. If no VNFaceObservations are provided, face detection will be run first. 
*/
API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
@interface VNDetectFaceLandmarksRequest : VNImageBasedRequest <VNFaceObservationAccepting>

+ (BOOL) revision:(NSUInteger)requestRevision supportsConstellation:(VNRequestFaceLandmarksConstellation)constellation;

/*!
 @property property constellation
 @abstract Constellation type defines how many landmark points are used to map a face. Revisions 1, 2, and 3 of the request support 65 points, where Revision 3 also supports 76 points.
 */
@property (readwrite, assign) VNRequestFaceLandmarksConstellation constellation API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0));

/*!
	@discussion VNFaceObservation with populated landmarks-related properties results.
*/
@property (readonly, copy, nullable) NSArray<VNFaceObservation*>* results;

@end


API_AVAILABLE(macos(10.14), ios(12.0), tvos(12.0))
static const NSUInteger VNDetectFaceLandmarksRequestRevision1 = 1;

API_AVAILABLE(macos(10.14), ios(12.0), tvos(12.0))
static const NSUInteger VNDetectFaceLandmarksRequestRevision2 = 2;

API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0))
static const NSUInteger VNDetectFaceLandmarksRequestRevision3 = 3;


NS_ASSUME_NONNULL_END
