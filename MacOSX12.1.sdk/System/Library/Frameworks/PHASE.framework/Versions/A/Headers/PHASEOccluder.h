//
//  PHASEOccluder.h
//  PHASE
//
//  Copyright © 2021 Apple. All rights reserved.
//

#ifndef PHASEOccluder_h
#define PHASEOccluder_h

#import <PHASE/PHASEObject.h>
#import <PHASE/PHASEShape.h>
#import <PHASE/PHASETypes.h>

@class PHASEEngine;

NS_ASSUME_NONNULL_BEGIN

/****************************************************************************************************/
/*!
    @interface PHASEOccluder
    @abstract A PHASEOccluder represents a shape (with associated materials) that can affect sound transmission within the simulated acoustic scene.
*/
OS_EXPORT API_AVAILABLE(macos(12.0), ios(15.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos)
@interface PHASEOccluder : PHASEObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

- (instancetype)initWithEngine:(PHASEEngine*)engine NS_UNAVAILABLE;

/*!
    @method initWithEngine:shapes:
    @abstract Initialize a new occluder with shapes.
    @discussion
        The shapes array cannot be empty, otherwise an exception is thrown.
    @note
        This function is thread-safe.
        Clients can safely run this function to create multiple occluders from multiple threads, if required.
*/
- (instancetype)initWithEngine:(PHASEEngine*)engine shapes:(NSArray<PHASEShape*>*)shapes NS_DESIGNATED_INITIALIZER;

/*!
    @property shapes
    @abstract Array of shapes associated with this occluder.
*/
@property(nonatomic, readonly, copy) NSArray<PHASEShape*>* shapes;

@end

NS_ASSUME_NONNULL_END

#endif /* PHASEOccluder_h */
