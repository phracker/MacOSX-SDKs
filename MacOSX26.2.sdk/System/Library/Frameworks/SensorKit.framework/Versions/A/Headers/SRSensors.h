//
//  SRSensors.h
//  SensorKit
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SensorKit/SRDefines.h>

/*!
 * @typedef SRSensor
 *
 * @brief
 * A type of data stream stored in the SensorKit data store.
 *
 */
typedef NSString * SRSensor NS_TYPED_ENUM API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, macos, visionos) API_UNAVAILABLE(tvos);

NS_ASSUME_NONNULL_BEGIN

/*!
 * @const SRSensorAmbientLightSensor
 *
 * @brief
 * Sensor stream for Environmental Brightness and Color.
 *
 * @discussion
 * This data stream stores ambient light sensor data from devices when the screen is on.
 * Fetches from this stream return objects of type SRAmbientLightSample.
 */
SR_EXTERN SRSensor const SRSensorAmbientLightSensor API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, macos, visionos) API_UNAVAILABLE(tvos);

/*!
 * @const SRSensorAccelerometer
 *
 * @brief
 * Accelerometer sensor stream for Motion.
 *
 * @discussion
 * This data stream stores acceleration measured by the device's accelerometer.
 * Fetches from this stream return objects of type NSArray<CMRecordedAccelerometerData *> * as defined in the CoreMotion framework.
 */
SR_EXTERN SRSensor const SRSensorAccelerometer API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, macos, visionos) API_UNAVAILABLE(tvos);

/*!
 * @const SRSensorRotationRate
 *
 * @brief
 * Rotation rate sensor stream for Motion.
 *
 * @discussion
 * This data stream stores rotation rate measured by the device's gyroscope.
 * Fetches from this stream return objects of type NSArray<CMRecordedRotationRateData *> * as defined in the CoreMotion framework.
 */
SR_EXTERN SRSensor const SRSensorRotationRate API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, macos, visionos) API_UNAVAILABLE(tvos);

/*!
 * @const SRSensorVisits
 *
 * @brief
 * Sensor stream for Frequently Visited Locations.
 *
 * @discussion
 * This data stream stores visit information from frequently visited locations including:
 * @textblock
 *   - arrival and departure times
 *   - distance from your home
 *   - an anonymous location identifier but no specific location information
 * @/textblock
 *
 * Fetches from this stream return objects of type SRVisit.
 */
SR_EXTERN SRSensor const SRSensorVisits API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, macos, visionos) API_UNAVAILABLE(tvos);

/*!
 * @const SRSensorPedometerData
 *
 * @brief
 * Sensor stream for Pedometer.
 *
 * @discussion
 * This stream stores information about your step count.
 * Fetches from this stream return objects of type CMPedometerData as defined in the CoreMotion framework.
 */
SR_EXTERN SRSensor const SRSensorPedometerData API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, macos, visionos) API_UNAVAILABLE(tvos);

/*!
 * @const SRSensorDeviceUsageReport
 *
 * @brief
 * Sensor stream for Device Usage.
 *
 * @discussion
 * This stream stores information about device usage including:
 * @textblock
 *   - Types of apps used
 *   - Types of notifications received
 *   - Types of websites visited
 *   - Number of device unlocks and unlock duration
 *   - Number of times the screen is on and the duration
 * @/textblock
 *
 * Fetches from this stream return objects of type SRDeviceUsageReport.
 */
SR_EXTERN SRSensor const SRSensorDeviceUsageReport API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, macos, visionos) API_UNAVAILABLE(tvos);

/*!
 * @const SRSensorMessagesUsageReport
 *
 * @brief
 * Sensor stream for Messages Usage.
 *
 * @discussion
 * This streams stores information about messages usage including:
 * @textblock
 *   - The number of incoming and outgoing messages
 *   - The number of individuals contacted but none of their personal information
 * @/textblock
 *
 * Fetches from this stream return objects of type SRMessagesUsageReport.
 */
SR_EXTERN SRSensor const SRSensorMessagesUsageReport API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, macos, visionos) API_UNAVAILABLE(tvos);

/*!
 * @const SRSensorPhoneUsageReport
 *
 * @brief
 * Sensor stream for Phone Usage
 *
 * @discussion
 * This streams stores information about phone usage including:
 * @textblock
 *   - The number of incoming and outgoing calls
 *   - The number of individuals contacted but none of their personal information
 * @/textblock
 *
 * Fetches from this stream return objects of type SRPhoneUsageReport.
 */
SR_EXTERN SRSensor const SRSensorPhoneUsageReport API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, macos, visionos) API_UNAVAILABLE(tvos);

/*!
 * @const SRSensorOnWristState
 *
 * @brief
 * Sensor stream for Watch on Wrist
 *
 * @discussion
 * This streams stores information about Apple Watch wear including:
 * @textblock
 *   - When the watch is worn
 *   - Digital crown and orientation settings
 * @/textblock
 *
 * Fetches from this stream return objects of type SRWristDetection.
 */
SR_EXTERN SRSensor const SRSensorOnWristState API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, macos, visionos) API_UNAVAILABLE(tvos);

/*!
 * @const SRSensorKeyboardMetrics
 *
 * @brief
 * Sensor stream for Keyboard Usage
 *
 * @discussion
 * This stream stores information about keyboard usage from all apps where a keyboard is used including:
 * @textblock
 *   - Metrics about typing speed and accuracy
 *   - Metrics about the length of typed or swiped words
 *   - Metrics about the typing errors made
 *   - The number of words and emojis that convey emotion
 * @/textblock
 *
 * Fetches from this stream return objects of type SRKeyboardMetrics.
 */
SR_EXTERN SRSensor const SRSensorKeyboardMetrics API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, macos, visionos) API_UNAVAILABLE(tvos);

/*!
 * @const SRSensorSiriSpeechMetrics
 *
 * @brief
 * Siri sensor stream for Speech Metrics
 *
 * @discussion
 * This stream stores information data about your voice during Siri sessions including:
 * @textblock
 *   - Tenor, pitch, and cadence
 *   - Metrics such as average words per minute and average pause length
 * @/textblock
 * This steam does not store any raw audio nor any audio or data from other parties.
 *
 * Fetches from this stream return objects of type \c SRSpeechMetrics
 */
SR_EXTERN SRSensor const SRSensorSiriSpeechMetrics API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(watchos, macos, visionos) API_UNAVAILABLE(tvos);

/*!
 * @const SRSensorTelephonySpeechMetrics
 *
 * @brief
 * Telephony sensor stream for Speech Metrics
 *
 * @discussion
 * This stream stores information data about your voice during phone calls including:
 * @textblock
 *   - Tenor, pitch, and cadence
 *   - Metrics such as average words per minute and average pause length
 * @/textblock
 *
 * This steam does not store any raw audio nor any audio or data from other parties.
 *
 * Fetches from this stream return objects of type \c SRSpeechMetrics
 */
SR_EXTERN SRSensor const SRSensorTelephonySpeechMetrics API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(watchos, macos, visionos) API_UNAVAILABLE(tvos);

/*!
 * @const SRSensorAmbientPressure
 *
 * @brief
 * Ambient pressure sensor stream
 *
 * @discussion
 * This stream stores simple pressure and temperature measurements including:
 * @textblock
 *   - Pressure and temperature
 *   - Date when metric was collected
 * @/textblock
 *
 * Fetches from this stream return objects of type NSArray<CMRecordedPressureData *> * as defined in the CoreMotion framework.
 */
SR_EXTERN SRSensor const SRSensorAmbientPressure API_AVAILABLE(ios(15.4)) API_UNAVAILABLE(watchos, macos, visionos) API_UNAVAILABLE(tvos);

/*!
 * @const SRSensorMediaEvents
 *
 * @brief
 * Media events sensor stream
 *
 * @discussion
 * This stream stores data about user interaction with photo and video content in messaging apps including:
 * @textblock
 *   - Event type
 *   - Media identifier
 * @/textblock
 * Fetches from this stream return objects of type SRMediaEvent.
 */
SR_EXTERN SRSensor const SRSensorMediaEvents API_AVAILABLE(ios(16.4)) API_UNAVAILABLE(watchos, macos, visionos) API_UNAVAILABLE(tvos);

/*!
 * @const SRSensorWristTemperature
 *
 * @brief
 * Sensor stream for Apple Watch temperatures on wrist while sleeping
 *
 * @discussion
 * This stream stores Apple Watch on wrist temperature measurements including:
 * @textblock
 *   - StartTime
 *   - Duration of collected temperature measurements
 *   - version of algorithm
 *   - Temperature samples
 * @/textblock
 *
 * Fetches from this stream return objects of type SRWristTemperatureSession.
 */
SR_EXTERN SRSensor const SRSensorWristTemperature API_AVAILABLE(ios(17.0)) API_UNAVAILABLE(watchos, macos, visionos) API_UNAVAILABLE(tvos);

/*!
 * @const SRSensorHeartRate
 *
 * @brief
 * Estimated heart rate
 *
 * @discussion
 * Fetches from this stream return objects of type \c CMHighFrequencyHeartRateData
 */
SR_EXTERN SRSensor const SRSensorHeartRate API_AVAILABLE(ios(17.0)) API_UNAVAILABLE(watchos, macos, visionos) API_UNAVAILABLE(tvos);


/*!
 * @const SRSensorFaceMetrics
 *
 * @brief
 * Sensor stream for face metrics collection
 *
 * @discussion
 * This stream stores face metrics including:
 * @textblock
 *   - algorithm version
 *   - face description and face expressions
 *   - data collection session identifier
 * @/textblock
 *
 * Fetches from this stream return objects of type SRFaceMetrics.
 */
SR_EXTERN SRSensor const SRSensorFaceMetrics API_AVAILABLE(ios(17.0)) API_UNAVAILABLE(watchos, macos, visionos) API_UNAVAILABLE(tvos);

/*!
 * @const SRSensorOdometer
 *
 * @brief
 * Odometer sensor stream
 *
 * @discussion
 * This stream stores measurements of your distance and speed
 * Fetches from this stream return objects of type \c CMOdometerData as defined in the CoreMotion framework.
 */
SR_EXTERN SRSensor const SRSensorOdometer API_AVAILABLE(ios(17.0)) API_UNAVAILABLE(watchos, macos, visionos) API_UNAVAILABLE(tvos);


/*!
 * @const SRSensorElectrocardiogram
 *
 * @brief
 * ECG sensor stream
 *
 * @discussion
 * This stream stores samples of the ECG sensor
 * Fetches from this stream return objects of type \c NSArray<SRElectrocardiogramSample *> *  
 */
SR_EXTERN SRSensor const SRSensorElectrocardiogram API_AVAILABLE(ios(17.4)) API_UNAVAILABLE(watchos, macos, visionos) API_UNAVAILABLE(tvos);

/*!
 * @const SRSensorPhotoplethysmogram
 *
 * @brief
 * PPG sensor stream
 *
 * @discussion
 * This stream stores samples of the PPG sensor
 * Fetches from this stream return objects of type \c NSArray<SRPhotoplethysmogramSample *> *
 */
SR_EXTERN SRSensor const SRSensorPhotoplethysmogram API_AVAILABLE(ios(17.4)) API_UNAVAILABLE(watchos, macos, visionos) API_UNAVAILABLE(tvos);

/*!
 * @const SRSensorAcousticSettings
 *
 * @brief
 * Sensor stream for Acoustic Settings
 *
 * @discussion
 * This stream stores samples of the Acoustic Settings sensor
 * Fetches from this stream return objects of type \c SRAcousticSettings
 */
SR_EXTERN SRSensor const SRSensorAcousticSettings API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(watchos, macos, visionos) API_UNAVAILABLE(tvos);

/*!
 * @const SRSensorSleepSessions
 *
 * @brief
 * Sesnor stream for sleep sessions collection
 *
 * @discussion
 * This stream stores samples of the Sleep Sessions sensor
 * Fetches from this stream return objects of type \c SRSleepSession
 */
SR_EXTERN SRSensor const SRSensorSleepSessions API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(watchos, macos, visionos) API_UNAVAILABLE(tvos);

NS_ASSUME_NONNULL_END
