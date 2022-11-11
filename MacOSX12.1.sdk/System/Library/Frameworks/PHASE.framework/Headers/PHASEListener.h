//
//  PHASEListener.h
//  PHASE
//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#ifndef PHASEListener_h
#define PHASEListener_h

#import <PHASE/PHASEObject.h>
#import <PHASE/PHASETypes.h>

@class PHASEEngine;

NS_ASSUME_NONNULL_BEGIN

/****************************************************************************************************/
/*!
    @interface PHASEListener
    @abstract A PHASEListener represents the listener's point of view within the simulated acoustic scene.
*/
OS_EXPORT API_AVAILABLE(macos(12.0), ios(15.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos)
@interface PHASEListener : PHASEObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/*!
    @method initWithEngine:
    @abstract Initialize a new listener.
*/
- (instancetype)initWithEngine:(PHASEEngine*)engine NS_DESIGNATED_INITIALIZER;

/*!
    @property gain
    @abstract Linear gain scalar.
    @note
        Values are clamped to the range [0, 1]. Default value is 1.
*/
@property(nonatomic, assign) double gain;

@end

NS_ASSUME_NONNULL_END

#endif /* PHASEListener_h */
