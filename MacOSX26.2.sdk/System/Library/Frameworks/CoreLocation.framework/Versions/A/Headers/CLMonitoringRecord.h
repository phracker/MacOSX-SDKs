//
//  CLMonitoringRecord.h
//  CoreLocation
//
//  Copyright (c) 2021 Apple Inc. All rights reserved.
//
#pragma once

#import <Foundation/Foundation.h>
#import <CoreLocation/CLAvailability.h>
#import <CoreLocation/CLCondition.h>
#import <CoreLocation/CLMonitoringEvent.h>

NS_ASSUME_NONNULL_BEGIN

/*
 *	`CLMonitoringRecord` represents a condition and its associated information
 *	as monitored by a `CLMonitor`
 *
 *	Discussion:
 *		`CLMonitoringRecord` contains a condition and last event that affected it.
 *
 *		When handling a new `CLMonitoringEvent`, the `CLMonitoringRecord`
 *		available for the indicated identifier from the `CLMonitor` will contain
 *		the prior event. The `CLMonitoringRecord` will be updated with the new
 *		event once the handling is complete.
 *
 */
NS_REFINED_FOR_SWIFT
CL_EXTERN
API_AVAILABLE(macos(14.0), ios(17.0)) API_UNAVAILABLE(watchos, tvos, visionos)
@interface CLMonitoringRecord : NSObject<NSSecureCoding>

/*
 *	condition
 *
 *	Discussion:
 *		The condition for which events are being monitored.
 */
@property (readonly, strong) __kindof CLCondition *condition;

/*
 *	lastEvent
 *
 *	Discussion:
 *		Contains the specifics of the last event such as state, date and the
 *		specifics of the condition, if applicable.
 *
 */
@property (readonly, strong) CLMonitoringEvent *lastEvent;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
