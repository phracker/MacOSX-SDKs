//
//  SRSensorReader.h
//  SensorKit
//
//  Copyright © 2017 Apple Inc All rights reserved.
//

#import <SensorKit/SRAbsoluteTime.h>
#import <SensorKit/SRDevice.h>
#import <SensorKit/SRSensors.h>
#import <SensorKit/SRFetchRequest.h>
#import <SensorKit/SRFetchResult.h>
#import <SensorKit/SRAuthorization.h>

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class SRSensorReader;
SR_EXTERN API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, macos, visionos) API_UNAVAILABLE(tvos)
@protocol SRSensorReaderDelegate <NSObject>
@optional

/**
 * @brief Invoked when a sample has been fetched
 *
 * @description This callback can be called multiple times
 * when there are multiple results.
 *
 * @param fetchRequest The request corresponding to the this result
 * @param result One result of the fetch. The caller is expected to
 * know what type of sample is returned.
 *
 * @note The fetchResult is not valid after the callback is complete. If the caller needs
 * to access the result at a later time, it must be copied not merely retained
 *
 * @return
 * The delegate should return YES if the fetch should continue, NO if the fetch should stop
 */
- (BOOL)sensorReader:(SRSensorReader *)reader
     fetchingRequest:(SRFetchRequest *)fetchRequest
      didFetchResult:(SRFetchResult *)result;

/**
 * @brief Invoked when a fetch has been completed successfully
 */
- (void)sensorReader:(SRSensorReader *)reader
    didCompleteFetch:(SRFetchRequest *)fetchRequest;
/**
 * @brief Invoked when a fetch has completed with an error
 */
- (void)sensorReader:(SRSensorReader *)reader
     fetchingRequest:(SRFetchRequest *)fetchRequest
     failedWithError:(NSError *)error;

/**
 * @brief Invoked when authorization status has changed
 */
- (void)sensorReader:(SRSensorReader *)reader didChangeAuthorizationStatus:(SRAuthorizationStatus)authorizationStatus;

/**
 * @brief Invoked after a SRSensorReader has request that recording be
 * started for a sensor
 */
- (void)sensorReaderWillStartRecording:(SRSensorReader *)reader;

/**
 * @brief Invoked if there was an error starting recording for a given sensor
 */
- (void)sensorReader:(SRSensorReader *)reader startRecordingFailedWithError:(NSError *)error;

/**
 * @brief Invoked after a SRSensorReader has request that recording be
 * stopped for a sensor
 */
- (void)sensorReaderDidStopRecording:(SRSensorReader *)reader;

/**
 * @brief Invoked if there was an error starting recording for a given sensor
 */
- (void)sensorReader:(SRSensorReader *)reader stopRecordingFailedWithError:(NSError *)error;

- (void)sensorReader:(SRSensorReader *)reader didFetchDevices:(NSArray<SRDevice *> *)devices;
- (void)sensorReader:(SRSensorReader *)reader fetchDevicesDidFailWithError:(NSError *)error;

@end

SR_EXTERN API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, macos, visionos) API_UNAVAILABLE(tvos)
@interface SRSensorReader : NSObject

/**
 * @brief
 * Initializes an SRSensorReader that will fetch data for the current device
 * and any companion
 */
- (instancetype)initWithSensor:(SRSensor)sensor;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/**
 * @brief
 * Starts recording for the reader's sensor
 *
 * @discussion
 * The reader must be authorized for the sensor for this to succeed.
 * This starts recording on this device and any paired devices.
 * If other readers have already started the sensor recording this
 * reader's interest in recording will be maintained. Other readers in
 * other apps for the same sensor will not affect the recording status
 * of this reader.
 *
 * In the case of success, completion notification will be delivered
 * to the delegate in the sensorReaderWillStartRecording:
 * delegate method.
 *
 * In the case of failure, error notification will be delivered
 * to the delegate in the sensorReader:startRecordingFailedWithError:
 * delegate method.
 */
- (void)startRecording;

/**
 * @brief
 * Stops recording for the reader's sensor
 *
 * @discussion
 * The reader must be authorized for the sensor for this to succeed.
 * This stops recording on this device and any paired devices.
 * Sensor recording will continue until the last interested reader has
 * stopped recording.
 *
 * In the case of success, completion notification will be delivered
 * to the delegate in the sensorReaderDidStopRecording:
 * delegate method.
 *
 * In the case of failure, error notification will be delivered
 * to the delegate in the sensorReader:stopRecordingFailedWithError:
 * delegate method.
 */
- (void)stopRecording;

/**
 * @brief
 * Fetches device information for all devices that have stored data for
 * the given sensor in SensorKit
 *
 * If the request completes successfully, devices will be returned to the
 * delegate in the sensorReader:fetchedDevices: callback. If the request
 * failed, an error will be returned to the delegate in the
 * sensorReader:fetchDevicesFailedWithError:
 * method
 */
- (void)fetchDevices;

/**
 * @brief
 * Fetches samples for the reader's sensor for given request parameters
 *
 * @discussion
 * The reader must be authorized for the sensor for this to succeed.
 *
 * Samples will be delivered to the delegate through multiple calls
 * to the sensorReader:fetchingRequest:didFetchResult: delegate method
 *
 * In the case of a failure, any error will be delivered to the delegate in the
 * sensorReader:fetchingRequest:failedWithError: method.
 *
 * In the case of success, completion notification will be delivered
 * to the delegate in the sensorReader:didCompleteFetch: method.
 *
 * @param request The query parameters for this fetch
 */
- (void)fetch:(SRFetchRequest *)request;

/**
 * @brief  The current authorization status of the calling application.
 */
@property (readonly) SRAuthorizationStatus authorizationStatus;

/**
 * @brief the sensor this reader was initialized with
 */
@property (readonly, copy) SRSensor sensor;

@property (weak) id<SRSensorReaderDelegate> delegate;

/**
 * @brief Request authorization to a given set of sensors
 *
 * @discussion If the SRSensorReader instance is not authorized, this
 * method must be called before any other methods. Failure to request
 * authorization will cause errors to be returned from the other methods.
 *
 * When SensorKit prepares the prompt for display, it will look at the
 * NSSensorKitUsageDetail key in your Info.plist.  The value should be
 * a dictionary containing usage descriptions for all of the sensors being
 * requested.  The description key you provide to this method must
 * correspond to an entry in that dictionary.  To retrieve a localized
 * string, SensorKit will load your InfoPlist.strings file and try to look
 * up a string using the description key you provided.  If that fails,
 * SensorKit will use the content provided in your Info.plist.
 *
 * SensorKit may decide against showing the user a prompt.  For example,
 * if the user has already chosen whether to grant the application access
 * to all of the types provided.  When that happens, your completion block
 * will be called with an appropriate  NSError.  If the user responded to
 * the prompt, your completion block will be called with a nil error.
 * Changes in authorization status will delivered to the delegate in the
 * sensorReader:didChangeAuthorizationStatus: method.
 *
 */
+ (void)requestAuthorizationForSensors:(NSSet<SRSensor> *)sensors
                            completion:(void (^)(NSError * _Nullable error))completion;

@end

NS_ASSUME_NONNULL_END
