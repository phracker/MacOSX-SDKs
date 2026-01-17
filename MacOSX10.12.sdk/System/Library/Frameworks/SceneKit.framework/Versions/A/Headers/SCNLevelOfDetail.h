//
//  SCNLevelOfDetail.h
//
//  Copyright (c) 2013-2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SceneKit/SCNGeometry.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @class SCNLevelOfDetail
 @abstract SCNLevelOfDetail represents a level of detail of a geometry.
 */
API_AVAILABLE(macosx(10.9))
@interface SCNLevelOfDetail : NSObject <NSCopying, NSSecureCoding>

/*!
 @method levelOfDetailWithGeometry:screenSpaceRadius:
 @abstract This is a convenience method to create a level of detail with a coverage radius threshold mode.
 @param geometry The geometry for this level of detail. nil is supported and indicates that no geometry should be rendered for this level of detail.
 @param radius The maximum radius in screen-space that this level of detail is suitable for. The coverage radius is calculated from the projected bounding sphere and expressed in pixels.
 */
+ (instancetype)levelOfDetailWithGeometry:(nullable SCNGeometry *)geometry screenSpaceRadius:(CGFloat)radius;

/*!
 @method levelOfDetailWithGeometry:worldSpaceDistance:
 @abstract This is a convenience method to create a level of detail with a distance threshold mode.
 @param geometry The geometry for this level of detail. nil is supported and indicates that no geometry should be rendered for this level of detail.
 @param distance The minimum distance to the current point of view that this level of detail is suitable for.
 */
+ (instancetype)levelOfDetailWithGeometry:(nullable SCNGeometry *)geometry worldSpaceDistance:(CGFloat)distance;

/*!
 @property geometry
 @abstract Returns the geometry of the receiver.
 */
@property(readonly, nullable) SCNGeometry *geometry;

/*!
 @property screenSpaceRadius
 @abstract Returns the screen space radius of the receiver if any, 0 otherwise.
 */
@property(readonly) CGFloat screenSpaceRadius;

/*!
 @property worldSpaceDistance
 @abstract Returns the world space distance of the receiver if any, 0 otherwise.
 */
@property(readonly) CGFloat worldSpaceDistance;

@end

NS_ASSUME_NONNULL_END
