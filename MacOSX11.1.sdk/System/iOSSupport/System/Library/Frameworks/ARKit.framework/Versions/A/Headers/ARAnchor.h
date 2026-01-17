//
//  ARAnchor.h
//  ARKit
//
//  Copyright © 2016-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <simd/simd.h>

NS_ASSUME_NONNULL_BEGIN

@class ARAnchor;
/**
 An anchor object that can be copied from values of an existing anchor.
 */
API_AVAILABLE(ios(12.0))
@protocol ARAnchorCopying <NSCopying>

/**
 Initializes a new anchor object copying values from an existing anchor.
 @discussion This initializer will be called any time copy is called on anchor of this class.
 This method must be implemented for any ARAnchor subclasses that adds properties.
 @param anchor The anchor from which to copy values.
 */
- (instancetype)initWithAnchor:(ARAnchor *)anchor;

@end


/**
 Object representing a physical location and orientation in 3D space.
 */
API_AVAILABLE(ios(11.0))
@interface ARAnchor : NSObject <ARAnchorCopying, NSSecureCoding>

/**
 Unique identifier of the anchor.
 */
@property (nonatomic, readonly) NSUUID *identifier;

/**
 An optional name used to associate with the anchor.
 */
@property (nonatomic, nullable, readonly) NSString *name API_AVAILABLE(ios(12.0));

/**
 Identifier of the session that owns the anchor.
 
 @discussion The session identifier will be assigned to anchor when added to the session.
 */
@property (nonatomic, nullable, readonly) NSUUID *sessionIdentifier API_AVAILABLE(ios(13.0));

/**
 The transformation matrix that defines the anchor’s rotation, translation and scale in world coordinates.
 */
@property (nonatomic, readonly) simd_float4x4 transform;

/**
 Initializes a new anchor object.
 @param transform The transformation matrix that defines the anchor’s rotation, translation and scale in world coordinates.
 */
- (instancetype)initWithTransform:(simd_float4x4)transform;

/**
 Initializes a new anchor object with the provided identifier and name.
 @param name A name to associate with the anchor.
 @param transform The transformation matrix that defines the anchor’s rotation, translation and scale in world coordinates.
 */
- (instancetype)initWithName:(NSString *)name transform:(simd_float4x4)transform API_AVAILABLE(ios(12.0));

/** Unavailable */
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end


/**
 A real world object or location in the scene that is being tracked.
 */
API_AVAILABLE(ios(11.0))
@protocol ARTrackable <NSObject>

/**
 Tracking state of the anchor
 @discussion The isTracked value is used to determine the anchor transform’s validity. When the object being tracked is no longer detected in the
 camera image, its anchor will return NO for isTracked.
 */
@property (nonatomic, readonly) BOOL isTracked;

@end

NS_ASSUME_NONNULL_END
