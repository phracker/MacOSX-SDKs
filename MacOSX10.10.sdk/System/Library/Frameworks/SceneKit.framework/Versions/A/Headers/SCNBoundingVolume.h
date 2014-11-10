//
//  SCNBoundingVolume.h
//
//  Copyright (c) 2012-2014 Apple Inc. All rights reserved.
//

/*!
 @protocol SCNBoundingVolume
 @abstract The SCNBoundingVolume protocol is implemented by objects which can compute their bounding boxes.
 @discussion You can currently use this protocol to get the bounding boxes of nodes and geometries.
 */

@protocol SCNBoundingVolume <NSObject>
@required

/*! 
 @method getBoundingBoxMin:max:
 @abstract Fill the min and max vectors with the min and max vertex of the bounding box.
 @param min A pointer to a SCNVector3 to store the min vertex of the bounding box into.
 @param max A pointer to a SCNVector3 to store the max vertex of the bounding box into.
 */
- (BOOL)getBoundingBoxMin:(SCNVector3 *)min max:(SCNVector3 *)max;

/*!
 @method getBoundingSphereCenter:radius:
 @abstract Fill the center vector with the center of the bounding sphere and store the radius of the bounding sphere in 'radius'.
 @param center A pointer to a SCNVector3 to store the center of the bounding sphere into.
 @param radius A pointer to a CGFloat to store the radius of the bounding sphere into.
 */
- (BOOL)getBoundingSphereCenter:(SCNVector3 *)center radius:(CGFloat *)radius;


/*!
 @method setBoundingBoxMin:max:
 @abstract Override the receiver bounding box with the min and max vectors provided.
 @param min A pointer to a SCNVector3 representing the min vertex of the desired bounding box.
 @param max A pointer to a SCNVector3 representing the max vertex of the desired bounding box.
 @discussion Passing nil as arguments will recompute the original bounding box of the receiver.
 */
- (void)setBoundingBoxMin:(SCNVector3 *)min max:(SCNVector3 *)max SCENEKIT_AVAILABLE(10_9, 8_0);

@end
