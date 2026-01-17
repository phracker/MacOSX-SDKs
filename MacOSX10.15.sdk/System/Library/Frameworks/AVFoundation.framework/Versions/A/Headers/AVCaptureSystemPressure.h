/*
    File:  AVCaptureSystemPressure.h
 
    Framework:  AVFoundation
 
    Copyright 2017 Apple Inc. All rights reserved.
*/

#import <AVFoundation/AVBase.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @group AVCaptureSystemPressureLevel string constants
 
 @discussion
    The AVCaptureSystemPressureLevel string constants describe varying levels of system pressure that affect capture hardware availability and/or quality.
 */
typedef NSString *AVCaptureSystemPressureLevel NS_STRING_ENUM API_AVAILABLE(ios(11.1)) API_UNAVAILABLE(macos) API_UNAVAILABLE(watchos, tvos);

/*!
 @constant AVCaptureSystemPressureLevelNominal
    System pressure level is normal (not pressured).
 */
AVF_EXPORT AVCaptureSystemPressureLevel const AVCaptureSystemPressureLevelNominal API_AVAILABLE(ios(11.1)) API_UNAVAILABLE(macos) API_UNAVAILABLE(watchos, tvos);

/*!
 @constant AVCaptureSystemPressureLevelFair
    System pressure is slightly elevated.
 */
AVF_EXPORT AVCaptureSystemPressureLevel const AVCaptureSystemPressureLevelFair API_AVAILABLE(ios(11.1)) API_UNAVAILABLE(macos) API_UNAVAILABLE(watchos, tvos);

/*!
 @constant AVCaptureSystemPressureLevelSerious
    System pressure is highly elevated. Capture performance may be impacted. Frame rate throttling is advised.
 */
AVF_EXPORT AVCaptureSystemPressureLevel const AVCaptureSystemPressureLevelSerious API_AVAILABLE(ios(11.1)) API_UNAVAILABLE(macos) API_UNAVAILABLE(watchos, tvos);

/*!
 @constant AVCaptureSystemPressureLevelCritical
    System pressure is critically elevated. Capture quality and performance are significantly impacted. Frame rate throttling is highly advised.
 */
AVF_EXPORT AVCaptureSystemPressureLevel const AVCaptureSystemPressureLevelCritical API_AVAILABLE(ios(11.1)) API_UNAVAILABLE(macos) API_UNAVAILABLE(watchos, tvos);

/*!
 @constant AVCaptureSystemPressureLevelShutdown
    System pressure is beyond critical. Capture must immediately stop.
 */
AVF_EXPORT AVCaptureSystemPressureLevel const AVCaptureSystemPressureLevelShutdown API_AVAILABLE(ios(11.1)) API_UNAVAILABLE(macos) API_UNAVAILABLE(watchos, tvos);

/*!
 @enum AVCaptureSystemPressureFactors
 @abstract
    Constants indicating factors contributing to the current system pressured state.
 
 @constant AVCaptureSystemPressureFactorNone
    Indicates that the system is not currently pressured.
 @constant AVCaptureSystemPressureFactorSystemTemperature
    Indicates that the entire system is currently experiencing an elevated thermal level.
 @constant AVCaptureSystemPressureFactorPeakPower
    Indicates that the system's peak power requirements exceed the battery's current capacity and may result in a system power off.
 @constant AVCaptureSystemPressureFactorDepthModuleTemperature
    Indicates that the module capturing depth information is operating at an elevated temperature. As system pressure increases, depth quality may become degraded.
 */
typedef NS_OPTIONS(NSUInteger, AVCaptureSystemPressureFactors) {
    AVCaptureSystemPressureFactorNone                   = 0UL,
    AVCaptureSystemPressureFactorSystemTemperature      = (1UL << 0),
    AVCaptureSystemPressureFactorPeakPower              = (1UL << 1),
    AVCaptureSystemPressureFactorDepthModuleTemperature = (1UL << 2),
} API_AVAILABLE(ios(11.1)) API_UNAVAILABLE(macos) API_UNAVAILABLE(watchos, tvos);

@class AVCaptureSystemPressureStateInternal;

/*!
 @class AVCaptureSystemPressureState
 @abstract
    A model object describing a system pressure level and contributing factors to the pressured state.
 
 @discussion
    Beginning in iOS 11.1, AVCaptureDevice can report its current system pressure state. System pressure refers to a state in which capture quality is degraded or capture hardware availability is limited due to factors such as overall system temperature, insufficient battery charge for current peak power requirements, or camera module temperature.
 */
API_AVAILABLE(ios(11.1)) API_UNAVAILABLE(macos) API_UNAVAILABLE(watchos, tvos)
@interface AVCaptureSystemPressureState : NSObject
{
@private
    AVCaptureSystemPressureStateInternal *_internal;
}

AV_INIT_UNAVAILABLE

/*!
 @property level
 @discussion
    An enumerated string value characterizing the pressure level to which the system is currently elevated.
 */
@property(atomic, readonly) AVCaptureSystemPressureLevel level;

/*!
 @property factors
 @discussion
    A bitmask of values indicating the factors contributing to the current system pressure level.
 */
@property(atomic, readonly) AVCaptureSystemPressureFactors factors;

@end

NS_ASSUME_NONNULL_END
