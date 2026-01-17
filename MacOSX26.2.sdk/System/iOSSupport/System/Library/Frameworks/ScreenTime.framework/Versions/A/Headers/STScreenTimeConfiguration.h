//
//  STScreenTimeConfiguration.h
//  ScreenTime
//
//  Copyright © 2019–2021 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macos(11.0), ios(14.0))
/// The configuration for this device.
@interface STScreenTimeConfiguration : NSObject

/// A Boolean that indicates whether the device is currently enforcing child
/// restrictions.
@property (readonly) BOOL enforcesChildRestrictions;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

API_AVAILABLE(macos(11.0), ios(14.0))
/// The object you use to observe changes to the current configuration.
///
/// Use this class to start and stop observing the current configuration. For
/// example, you can opt to disable private browsing in your web browser’s view
/// controller when ``STScreenTimeConfiguration/enforcesChildRestrictions`` is
/// `true`.
@interface STScreenTimeConfigurationObserver : NSObject

/// Creates a configuration observer that reports updates on the queue you
/// specify.
///
/// - Parameters:
///   - updateQueue: The queue on which to report updates.
- (instancetype)initWithUpdateQueue:(dispatch_queue_t)updateQueue NS_DESIGNATED_INITIALIZER NS_SWIFT_NAME(init(updateQueue:));
/// Starts observing changes to the current configuration.
- (void)startObserving;
/// Stops observing changes to the current configuration.
- (void)stopObserving;

/// The configuration being observed.
@property (readonly, nullable, strong) STScreenTimeConfiguration *configuration;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
