//
//  SRAbsoluteTime.h
//  SensorKit
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#ifndef SRAbsoluteTime_h
#define SRAbsoluteTime_h

#import <CoreFoundation/CoreFoundation.h>
#import <SensorKit/SRDefines.h>

typedef CFTimeInterval SRAbsoluteTime
API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, macos, visionos) API_UNAVAILABLE(tvos);

/**
 * @brief Get the current SRAbsoluteTime for this device.
 *
 * This timestamp ticks across sleeps and reboots.
 */
SR_EXTERN SRAbsoluteTime SRAbsoluteTimeGetCurrent(void) API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, macos, visionos) API_UNAVAILABLE(tvos);

/**
 * @brief Convert a mach_continuous_time to an SRAbsoluteTime.
 *
 * Because mach_continuous_time is volatile and hardware specific, the
 * mach_continuous_time must originate from the same device and boot session
 * that SRAbsoluteTimeFromContinuousTime() is called from.
 * The return value for mach_continuous_times spanning boot sessions or devices
 * is undefined.
 */
SR_EXTERN SRAbsoluteTime SRAbsoluteTimeFromContinuousTime(uint64_t cont) API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, macos, visionos) API_UNAVAILABLE(tvos);

/**
 * @brief Convert a SRAbsoluteTime to a CFAbsoluteTime.
 *
 * The CFAbsoluteTime returned is based on calculations relative to the current
 * wall clock. This means that if the system time is 5 seconds fast against UTC,
 * the result will be 5 seconds fast to when the event happened relative to UTC.
 */
SR_EXTERN CFAbsoluteTime SRAbsoluteTimeToCFAbsoluteTime(SRAbsoluteTime sr) API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, macos, visionos) API_UNAVAILABLE(tvos);

/**
 * @brief Convert a CFAbsoluteTime to an SRAbsoluteTime.
 *
 * The SRAbsoluteTime returned is based on calculations relative to the current
 * wall clock. This means that if the system time is 5 seconds fast against UTC,
 * the result will be 5 seconds fast to when the event happened relative to UTC.
 */
SR_EXTERN SRAbsoluteTime SRAbsoluteTimeFromCFAbsoluteTime(CFAbsoluteTime cf) API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, macos, visionos) API_UNAVAILABLE(tvos);

#endif /* SRAbsoluteTime_h */
