//
//  Copyright © 2023 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <LocalAuthentication/LAEnvironmentState.h>

NS_ASSUME_NONNULL_BEGIN

@protocol LAEnvironmentObserver;

API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0), visionos(2.0))
@interface LAEnvironment : NSObject

/// The clients should use @c currentUser class property.
+ (instancetype)new NS_UNAVAILABLE;

/// The clients should use  @c currentUser class property.
- (instancetype)init NS_UNAVAILABLE;

/// @brief Adds observer to monitor changes of the environment.
/// @discussion The observer will be held weakly so its instance should be kept alive by the caller.
- (void)addObserver:(id<LAEnvironmentObserver>)observer NS_SWIFT_NAME(addObserver(_:));

/// @brief Removes the previously registered observer.
/// @discussion If the observer is deallocated, it will be removed automatically.
- (void)removeObserver:(id<LAEnvironmentObserver>)observer NS_SWIFT_NAME(removeObserver(_:));

/// Environment of the current user.
@property (nonatomic, readonly, class) LAEnvironment *currentUser;

/// The environment state information.
@property (nonatomic, readonly) LAEnvironmentState *state;

@end

API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0), visionos(2.0))
NS_SWIFT_NAME(LAEnvironment.Observer)
@protocol LAEnvironmentObserver<NSObject>
@optional
/// Called when there has been a change in the environment.
/// @discussion Invoked on a queue private to LocalAuthentication framework. At the moment of invocation of this method,
///             @c LAEnvironment.state already contains the new updated state.
/// @param oldState The old environment state (before update)
- (void)environment:(LAEnvironment *)environment stateDidChangeFromOldState:(LAEnvironmentState *)oldState;
@end


NS_ASSUME_NONNULL_END
