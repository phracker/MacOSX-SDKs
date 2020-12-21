//
//  STScreenTimeConfiguration.h
//  ScreenTime
//
//  Copyright © 2019–2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macos(11.0), ios(14.0))
@interface STScreenTimeConfiguration : NSObject

@property (readonly) BOOL enforcesChildRestrictions;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

API_AVAILABLE(macos(11.0), ios(14.0))
@interface STScreenTimeConfigurationObserver : NSObject

- (instancetype)initWithUpdateQueue:(dispatch_queue_t)updateQueue NS_DESIGNATED_INITIALIZER NS_SWIFT_NAME(init(updateQueue:));
- (void)startObserving;
- (void)stopObserving;

/// The current Screen Time configuration.
///
/// The configuration's properties are automatically updated via KVO on the update queue.
@property (readonly, nullable, strong) STScreenTimeConfiguration *configuration;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
