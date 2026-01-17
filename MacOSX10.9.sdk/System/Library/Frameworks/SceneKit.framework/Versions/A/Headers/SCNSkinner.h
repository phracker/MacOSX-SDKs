//
//  SCNSkinner.h
//
//  Copyright (c) 2013 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

/*!
 @class SCNSkinner
 @abstract SCNSkinner controls the deformation of skinned geometries */

SCENEKIT_CLASS_AVAILABLE(10_9, NA)
@interface SCNSkinner : NSObject
{
@private
    id _reserved;
}

/*!
 @property skeleton
 @abstract Specifies the skeleton of the receiver.
 @discussion When setting a new skeleton, the new skeleton must have the same hierarchy of joints.
 */
@property(nonatomic, retain) SCNNode *skeleton;

@end
