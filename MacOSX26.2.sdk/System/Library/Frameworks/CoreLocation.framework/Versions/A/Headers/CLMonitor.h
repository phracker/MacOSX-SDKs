//
//  CLMonitor.h
//  CoreLocation
//
//  Copyright (c) 2021 Apple Inc. All rights reserved.
//

#ifndef CLMonitor_h
#define CLMonitor_h

#import <Foundation/Foundation.h>
#import <CoreLocation/CLAvailability.h>
#import <CoreLocation/CLCondition.h>
#import <CoreLocation/CLMonitoringRecord.h>
#import <CoreLocation/CLMonitorConfiguration.h>

NS_ASSUME_NONNULL_BEGIN


/*
 *	`CLMonitor` is a name scoped instance which monitors all the conditions
 *	added to it
 *
 */
NS_REFINED_FOR_SWIFT NS_SWIFT_SENDABLE
CL_EXTERN
API_AVAILABLE(macos(14.0), ios(17.0)) API_UNAVAILABLE(watchos, tvos, visionos)
@interface CLMonitor : NSObject

/* requestMonitorWithConfiguration:completion:
 * 	Discussion:
 *		Creates or opens, a `CLMonitor` instance with the given name.
 *      The completion handler will be called with the instance of `CLMonitor`
 *		on the queue that was set in the configuration instance.
 *
 *		Conditions can be added for monitoring or removed from monitoring by
 *		this instance of `CLMonitor`. When an event occurs, the passed in block
 *		would be called on the specified queue. The callback handler is invoked
 *		with this instance of `CLMonitor` and an instance of `CLMonitoringEvent`
 *		containing the identifier under which the condition is monitored,
 *		an optional instance of `CLCondition` containing specifics, the new
 *		state, and the timestamp of the event.
 *
 *		All interaction directly with the returned `CLMonitor` must occur on
 *		the specified queue. Failing to do so will result in undefined behavior.
 *
 *		Conditions added to an instance of `CLMonitor` will persist until
 *		removed from monitoring. However, CoreLocation will stop monitoring
 *		conditions if an event is pending for them, but no `CLMonitor` has been
 *		configured to receive it.
 *
 *		The conditions are stored in an opaque file at
 *		~/Library/CoreLocation/BundleId (or Process name)/`name`.monitor.
 *		Note that for containerized Apps this will be inside the Data container.
 *		Apps need to observe when protected data becomes available using
 *		`UIApplicationProtectedDataDidBecomeAvailable` before creating a
 *		`CLMonitor` instance. Persistence of Conditions enables an app to query
 *		efficiently for conditions currently being monitored and the last
 *		event delivered for each.
 *
 *		The app can choose to initialize the monitoring state for a condition.
 *		By default, it is set to `CLMonitoringStateUnknown`.
 *
 *		- Note: Only one instance of `CLMonitor` with a given name may be
 *				opened at a time. Attempting to open another instance with the
 *				same name will return `false`.
 *
 */
+ (void)requestMonitorWithConfiguration:(CLMonitorConfiguration *)config
							 completion:(void(^)(CLMonitor *monitor))completionHandler
NS_REFINED_FOR_SWIFT NS_SWIFT_ASYNC(2);

/*
 *	name
 *
 *	Discussion:
 *		Name associated with the `CLMonitor` instance.
 *
 */
@property (nonatomic, readonly) NSString *name;

/*
 *	monitoredIdentifiers
 *
 *	Discussion:
 *		Array containing all the identifiers with each identifying a condition
 *		that is monitored.
 *
 */
@property (nonatomic, readonly) NSArray<NSString *> *monitoredIdentifiers;

/*
 *	addConditionForMonitoring:identifier:
 *
 *	Discussion:
 *		Adds `condition` to be monitored under `identifier`.
 *		It initializes the monitoring state to `CLMonitoringStateUnknown`.
 *
 */
- (void)addConditionForMonitoring:(CLCondition *)condition
					   identifier:(NSString *)identifier;

/*
 *	addConditionForMonitoring:identifier:assumedState
 *
 *	Discussion:
 *		Adds `condition` to be monitored under `identifier`.
 *		It initializes the monitoring state with the given value.
 *
 */
- (void)addConditionForMonitoring:(CLCondition *)condition
					   identifier:(NSString *)identifier
					 assumedState:(CLMonitoringState)state;

/*
 *	removeConditionFromMonitoringWithIdentifier:
 *
 *	Discussion:
 *		Removes the monitoring record with given `identifier` from monitoring
 *
 */
- (void)removeConditionFromMonitoringWithIdentifier:(NSString *)identifier;

/*
 *	monitoringRecordForIdentifier:
 *
 *	Discussion:
 *		Gets the monitoring record containing the condition and last
 *		monitoring event, if applicable
 *
 */
- (nullable CLMonitoringRecord *)monitoringRecordForIdentifier:(NSString *)identifier;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
#endif /* CLMonitor_h */
