//
//  PHASESource.h
//  PHASE
//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#ifndef PHASESource_h
#define PHASESource_h

#import <PHASE/PHASEObject.h>
#import <PHASE/PHASEShape.h>
#import <PHASE/PHASETypes.h>

@class PHASEEngine;

NS_ASSUME_NONNULL_BEGIN

/****************************************************************************************************/
/*!
    @class PHASESource
    @abstract A PHASESource represents where sound originates within the simulated acoustic scene.
    @discussion
        PHASE supports both point sources and volumetric sources.
        A point source simulates the sound from a point in space.
        A volumetric source simulates the sound from a shape.
*/
OS_EXPORT API_AVAILABLE(macos(12.0), ios(15.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos)
@interface PHASESource : PHASEObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/*!
    @method initWithEngine:
    @abstract Initialize a new point source.
*/
- (instancetype)initWithEngine:(PHASEEngine*)engine NS_DESIGNATED_INITIALIZER;

/*!
    @method initWithEngine:shapes:
    @abstract Initialize a new volumetric source with shapes.
    @param shapes
        The shape(s) of the source within the world
    @discussion
        The shapes array cannot be empty, otherwise an exception is thrown.
    @note
        This function is thread-safe.
        Clients can safely run this function to create multiple sources from multiple threads, if required.
*/
- (instancetype)initWithEngine:(PHASEEngine*)engine shapes:(NSArray<PHASEShape*>*)shapes NS_DESIGNATED_INITIALIZER;

/*!
    @property gain
    @abstract Linear gain scalar.
    @note
        Values are clamped to the range [0, 1]. Default value is 1.
*/
@property(nonatomic, assign) double gain;

/*!
    @property shapes
    @abstract Array of shapes associated with this source.
*/
@property(nonatomic, readonly, copy) NSArray<PHASEShape*>* shapes;

@end

NS_ASSUME_NONNULL_END

#endif /* PHASESource_h */
