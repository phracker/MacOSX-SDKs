//
//  PHASEObject.h
//  PHASE
//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#ifndef PHASEObject_h
#define PHASEObject_h

#import <PHASE/PHASETypes.h>

#import <simd/types.h>

@class PHASEEngine;

NS_ASSUME_NONNULL_BEGIN

/****************************************************************************************************/
/*!
    @interface PHASEObject
    @abstract A PHASEObject represents a 3D object in the engine, which can be organized into a hierarchy with relative transforms.
*/

OS_EXPORT API_AVAILABLE(macos(12.0), ios(15.0), tvos(17.0)) API_UNAVAILABLE(watchos)
@interface PHASEObject : NSObject<NSCopying>

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/*!
    @method initWithEngine:
    @abstract Initialize a new object.
*/
- (instancetype)initWithEngine:(PHASEEngine*)engine NS_DESIGNATED_INITIALIZER;

/*!
    @method addChild:error:
    @abstract Add a child to this object
    @param child
        The child object
    @param error
        Returns an error if the child already has a parent.
    @return
        YES for success
*/
- (BOOL)addChild:(PHASEObject*)child error:(NSError**)error;

/*!
    @method removeChild:
    @abstract Remove a child from this object.
*/
- (void)removeChild:(PHASEObject*)child;

/*!
    @method removeChildren
    @abstract Remove all the children from this object
*/
- (void)removeChildren;

/*!
    @property parent
    @abstract The parent of this object, or nil if this object doesn't have a parent object.
*/
@property(nullable, nonatomic, readonly, weak) PHASEObject* parent;

/*!
    @property children
    @abstract The children of this object.
*/
@property(nonatomic, readonly, copy) NSArray<PHASEObject*>* children;

/*!
    @property right
    @abstract The direction PHASE treats as "right" in local space for all objects.
*/
@property(class, readonly) simd_float3 right;

/*!
    @property up
    @abstract The direction PHASE treats as "up" in local space for all objects.
*/
@property(class, readonly) simd_float3 up;

/*!
    @property forward
    @abstract The direction PHASE treats as "forward" in local space for all objects.
*/
@property(class, readonly) simd_float3 forward;

/*!
    @property transform
    @abstract The object's transform.
    @note
        The transform must have orthogonal basis vectors and uniform scale.
*/
@property(nonatomic, assign) simd_float4x4 transform;

/*!
    @property worldTransform
    @abstract The world transform applied to the object.
    @note
        The transform must have orthogonal basis vectors and uniform scale.
*/
@property(nonatomic, assign) simd_float4x4 worldTransform;

@end

NS_ASSUME_NONNULL_END

#endif /* PHASEObject_h*/
