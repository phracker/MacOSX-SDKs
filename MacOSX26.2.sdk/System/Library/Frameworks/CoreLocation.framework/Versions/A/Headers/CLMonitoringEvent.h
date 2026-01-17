//
//  CLMonitoringEvent.h
//  CoreLocation
//
//  Copyright (c) 2021 Apple Inc. All rights reserved.

#ifndef CLMonitoringEvent_h
#define CLMonitoringEvent_h

#import <CoreLocation/CLAvailability.h>

@class CLCondition;

NS_ASSUME_NONNULL_BEGIN

/*
 * 	Enum representing the current state of the condition.
 */
typedef NS_ENUM(NSUInteger, CLMonitoringState) {
	CLMonitoringStateUnknown,
	CLMonitoringStateSatisfied,
	CLMonitoringStateUnsatisfied,
	CLMonitoringStateUnmonitored API_AVAILABLE(macos(14.2), ios(17.2)) API_UNAVAILABLE(tvos, watchos, visionos),
} NS_REFINED_FOR_SWIFT;

/*
 *	Event object that would be passed to the callback handler upon an event
 *
 *	Discussion:
 *		Instances of `CLMonitoringEvent` contain detailed information about
 *		an event in the monitoring of a `CLCondition` by a `CLMonitor`.
 *
 */
NS_REFINED_FOR_SWIFT
CL_EXTERN
API_AVAILABLE(macos(14.0), ios(17.0)) API_UNAVAILABLE(watchos, tvos, visionos)
@interface CLMonitoringEvent : NSObject<NSSecureCoding>

/*
 *	identifier
 *
 *	Discussion:
 *		An `NSString` representing the identifier under which the condition
 *		was added for monitoring.
 *
 */
@property (readonly, strong) NSString *identifier;

/*
 *	refinement
 *
 *	Discussion:
 *		An optional instance of CLCondition that represents the most specific
 *		condition to which this event could apply. The type of the refinement
 *		condition depends onthe monitored condition itself.
 *
 */
@property (readonly, strong) __kindof CLCondition * _Nullable refinement;

/*
 * 	state
 *
 *	Discussion:
 *		State of the condition at the time of the event.
 */
@property (readonly, nonatomic) CLMonitoringState state;

/*
 *	date
 *
 *	Discussion:
 *		An instance of NSDate indicating the time of the event.
 */
@property (readonly, strong) NSDate *date;

/*
 *  authorizationDenied
 *
 *  Discussion:
 *      True if events will be suspended while the app has been denied
 *      location authorization.
 *
 */
@property (nonatomic, readonly) BOOL authorizationDenied API_AVAILABLE(macos(15.0), ios(18.0)) API_UNAVAILABLE(watchos, tvos);

/*
 *  authorizationDeniedGlobally
 *
 *  Discussion:
 *      True if events will be suspended while the user has disabled Location
 *      Services system-wide.
 *
 */
@property (nonatomic, readonly) BOOL authorizationDeniedGlobally API_AVAILABLE(macos(15.0), ios(18.0)) API_UNAVAILABLE(watchos, tvos);

/*
 *  authorizationRestricted
 *
 *  Discussion:
 *     True if events will be suspended while the app lacks authorization,
 *     and authorization changes are prevented by parental restrictions,
 *     MDM configuration, or other factors.
 *
 */
@property (nonatomic, readonly) BOOL authorizationRestricted API_AVAILABLE(macos(15.0), ios(18.0)) API_UNAVAILABLE(watchos, tvos);

/*
 *  insufficientlyInUse
 *
 *  Discussion:
 *      True if events will be suspended while the app is not sufficiently
 *      in-use.
 *
 */
@property (nonatomic, readonly) BOOL insufficientlyInUse API_AVAILABLE(macos(15.0), ios(18.0)) API_UNAVAILABLE(watchos, tvos);

/*
 *  accuracyLimited
 *
 *  Discussion:
 *      True if events will not be delivered because the app is subject
 *      to accuracy limitation.
 *
 */
@property (nonatomic, readonly) BOOL accuracyLimited API_AVAILABLE(macos(15.0), ios(18.0)) API_UNAVAILABLE(watchos, tvos);

/*
 *  conditionUnsupported
 *
 *  Discussion:
 *      True if events will be suspended for this condition because
 *      monitoring is not supported for conditions of its type.
 *
 */
 @property (nonatomic, readonly) BOOL conditionUnsupported API_AVAILABLE(macos(15.0), ios(18.0)) API_UNAVAILABLE(watchos, tvos);

/*
 *  conditionLimitExceeded
 *
 *  Discussion:
 *      True if events will be suspended for this condition while the app
 *      has too many other conditions of this type monitored.
 *
 */
@property (nonatomic, readonly) BOOL conditionLimitExceeded API_AVAILABLE(macos(15.0), ios(18.0)) API_UNAVAILABLE(watchos, tvos);

 /*
  *  persistenceUnavailable
  *
  *  Discussion:
  *      True if monitoring is not possible due to persistence failure.
  *      Some or all properties of the condition, if identified, or all conditions,
  *      and events associated with the monitoring of affected conditions may not
  *      be stored persistently.
  *
  */
@property (nonatomic, readonly) BOOL persistenceUnavailable API_AVAILABLE(macos(15.0), ios(18.0)) API_UNAVAILABLE(watchos, tvos);

/*
 *  serviceSessionRequired
 *
 *  Discussion:
 *      True if LocationServices are disabled because the app has adopted CLRequireExplicitServiceSession
 *      info.plist key but no CLServiceSession requiring authorization is outstanding yet.
 *
 */
@property (nonatomic, readonly) BOOL serviceSessionRequired API_AVAILABLE(macos(15.0), ios(18.0)) API_UNAVAILABLE(watchos, tvos);

/*
 *  authorizationRequestInProgress
 *
 *  Discussion:
 *      True if the system is requesting authorization from the user on behalf of the app, but no response has been received yet.
 *
 */
@property (nonatomic, readonly) BOOL authorizationRequestInProgress API_AVAILABLE(macos(15.0), ios(18.0)) API_UNAVAILABLE(watchos, tvos);

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
#endif /* CLMonitoringEvent_h */
