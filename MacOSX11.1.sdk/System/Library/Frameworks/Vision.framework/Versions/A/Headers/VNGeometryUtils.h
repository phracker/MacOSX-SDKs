//
//  VNGeometryUtils.h
//  Vision
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <simd/simd.h>

#import <Vision/VNDefines.h>
#import <Vision/VNTypes.h>
#import <Vision/VNGeometry.h>


NS_ASSUME_NONNULL_BEGIN


@class VNContour;

 
API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0))
@interface VNGeometryUtils : NSObject

/*!
    @discussion    Calculates a bounding circle that includes a collection of points or a VNContour object. Note that because this is based on a geometric shape the aspect ratio is important when using normalized points.
				   This takes the aspect ratio of the contour into account when using a VNContour as an input. 
				   boundingCircleForPoints and boundingCircleForSIMDPoints assume that the aspect ratio is correctly applied to the points.

    @param    contour          A contour around which to find the bounding circle.
    
    @param    points            A collection of points around which to find the bounding circle.

    @param    pointCount   Number of points in points

    @param    contour          VNContour object whose bounding circle needs to be calculated

    @param    error              An output parameter, populated only in case of algorithmic failure

    @return the VNCircle object describing the bounding circle or nil, if the algorithm failed. The latter case is accompanied by populating an 'error' output parameter
*/
+ (nullable VNCircle*)boundingCircleForContour:(VNContour*)contour
                                         error:(NSError**)error;
+ (nullable VNCircle*)boundingCircleForPoints:(NSArray<VNPoint*>*)points
                                        error:(NSError**)error;
+ (nullable VNCircle*)boundingCircleForSIMDPoints:(simd_float2 const *)points
                                       pointCount:(NSInteger)pointCount
                                            error:(NSError**)error;


/*!
    @discussion    Calculates a closed contour area using Green's theorem. The contour is represented by a set of points in VNContour object,
                   It's important to note that a random set of points, or a contour with self-crossing edges will likely produce undefined results
				   Note that because this is based on a geometric shape the aspect ratio is important when using normalized points.
				   This takes the aspect ratio of the contour into account when using a VNContour as an input. 

    @param    area                   Output parameter to be populated with calculated contour area

    @param    contour             A VNContour object whose area is being calculated
    
    @param    orientedArea  If true, returns signed area - positive for CCW oriented contours and negative for CW oriented contours.
                           If false, returned area is always positive.

    @param    error                 An output parameter, populated only in case of algorithmic failure

    @return Area calculation status, YES indicates success, NO - failure. The failure case is accompanied by populating an 'error' output parameter
*/
+ (BOOL)calculateArea:(double*)area
           forContour:(VNContour*)contour
         orientedArea:(BOOL)orientedArea
                error:(NSError**)error;


/*!
    @discussion    Calculates perimeter, or a sum of all arc-lengths (edges), of a closed contour. The contour is represented by a set of points in VNContour object.
				   Note that because this is based on a geometric shape the aspect ratio is important when using normalized points.
				   This takes the aspect ratio of the contour into account when using a VNContour as an input.

    @param    perimeter      Output parameter to be populated with calculated contour perimeter

    @param    contour          A VNContour object whose perimeter is being calculated

    @param    error              An output parameter, populated only in case of algorithmic failure

    @return Perimeter calculation status, YES indicates success, NO - failure. The failure case is accompanied by populating an 'error' output parameter
*/
+ (BOOL)calculatePerimeter:(double*)perimeter
                forContour:(VNContour*)contour
                     error:(NSError**)error;

@end


NS_ASSUME_NONNULL_END
