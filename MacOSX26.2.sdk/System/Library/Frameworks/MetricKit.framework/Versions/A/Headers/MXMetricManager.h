//
//  MXMetricManager.h
//  MetricKit
//
//  Copyright (c) 2018 Apple Inc.
//  All rights reserved.

#import <Foundation/Foundation.h>
#import <MetricKit/MXMetricPayload.h>
#import <MetricKit/MXDiagnosticPayload.h>
#import <os/log.h>
#import <os/availability.h>

NS_ASSUME_NONNULL_BEGIN

@protocol MXMetricManagerSubscriber;

/*!
 @typedef       MXLaunchTaskID
 @abstract      Describes the general purpose of a specific launch task.
 */
API_AVAILABLE(ios(16.0), macos(13.0)) API_UNAVAILABLE(tvos, watchos)
typedef const NSString *const MXLaunchTaskID NS_TYPED_EXTENSIBLE_ENUM;

/*!
 @class         MXMetricManager
 @abstract      An instance of this class can be used to retrieve periodic, aggregated power and performance metrics.
 @discussion    To receive metrics, clients must acquire a reference to the shared instance of the metric manager and add an eligible MXMetricManagerSubscriber.
 @discussion    Metrics are not guaranteed to be delivered, but can be expected atleast once per day when conditions permit.
 @discussion    Subscribers to the metric manager can remove themselves using removeSubscriber:subscriber if they no longer wish to receive metrics.
 */
API_AVAILABLE(ios(13.0), macos(12.0)) API_UNAVAILABLE(tvos, watchos)
@interface MXMetricManager : NSObject

/*!
 @property      pastPayloads
 @abstract      A list of past metric payloads received.
 */
@property (readonly, nonnull, strong) NSArray<MXMetricPayload *> *pastPayloads;

/*!
 @property      pastDiagnosticPayloads
 @abstract      A list of past diagnostic payloads received.
 */
@property (readonly, nonnull, strong) NSArray<MXDiagnosticPayload *> *pastDiagnosticPayloads API_AVAILABLE(ios(14.0), macos(12.0)) API_UNAVAILABLE(tvos, watchos);

/*!
 @property      sharedManager
 @abstract      Singleton instance of MXMetricManager.
 */
@property (class, readonly, strong) MXMetricManager *sharedManager;

/*!
 @method        makeLogHandleWithCategory:category
 @abstract      Retrieve a log handle for flagging critical sections with os_signpost().
 @param         category A string used to define a log category
 @discussion    The log handle configures persistence for any signposts emit while using the log handle.
 @result        A log handle that can be used with the logging framework.
 */
+ (os_log_t _Nonnull)makeLogHandleWithCategory:(NSString *)category NS_SWIFT_NAME(makeLogHandle(category:));

/*!
 @method        addSubscriber:subscriber
 @abstract      Adds a subscriber to the metric manager.
 @param         subscriber An object that conforms to the MXMetricManagerSubscriber protocol.
 @discussion    Subscribers can receive metric payloads by conforming to the MXMetricManagerSubscriber protocol.
 */
- (void)addSubscriber:(id<MXMetricManagerSubscriber>)subscriber;

/*!
 @method        removeSubscriber:subscriber
 @abstract      Removes a subscriber from the metric manager.
 @param         subscriber An object that conforms to the MXMetricManagerSubscriber protocol.
 @discussion    The subscriber indicated, if previously registered, will no longer receive metric payloads.
 */
- (void)removeSubscriber:(id<MXMetricManagerSubscriber>)subscriber;

/*!
 @method        extendLaunchMeasurementForTaskID:error:
 @abstract      Start measuring an extended launch task with the given task id.
 @discussion    This method tracks extra setup tasks required to make the application perceived as fully launched, such as loading up content from the disk or refreshing data from the network, rendering images, etc.
 @discussion    The first task needs to start before or during @c UISceneDelegate.scene(_:restoreInteractionStateWith:) or before @c UISceneDelegate.sceneDidBecomeActive(_:) is called on the first scene to connect. For example, at the time @c UIApplicationDelegate.application(_:didFinishLaunchingWithOptions:) is called. Other tasks need to start before the last current task is finished, otherwise the extended launch measurement will end.  
 @discussion    The maximum number of tasks is 16.
 @discussion    This method needs to be called on the main thread.
 @param         taskID              The task identifier. Must be an unique nonnull custom string.
 @param         error               If an error occurs, this will contain a valid @c NSError object on exit.
 @result        Returns @c YES if the measurement started successfully and @c NO otherwise.
 */

+ (BOOL)extendLaunchMeasurementForTaskID:(MXLaunchTaskID)taskID error:(NSError **)error API_AVAILABLE(ios(16.0), macos(13.0)) API_UNAVAILABLE(tvos, watchos);

/*!
 @method        finishExtendedLaunchMeasurementForTaskID:error:
 @abstract      Signal the end of an extended launch task previously started with @c extendLaunchMeasurementForTaskID:error: .
 @discussion    This method needs to be called on the main thread.
 @param         taskID              The task identifier. Must match the task identifier passed to @c extendLaunchMeasurementForTaskID:error: .
 @param         error               If an error occurs, this will contain a valid @c NSError object on exit.
 @result        Returns @c YES if the measurement for the task finished successfully and @c NO otherwise.
 */

+ (BOOL)finishExtendedLaunchMeasurementForTaskID:(MXLaunchTaskID)taskID error:(NSError **)error API_AVAILABLE(ios(16.0), macos(13.0)) API_UNAVAILABLE(tvos, watchos);

@end

/*!
 @protocol      MXMetricManagerSubscriber
 @abstract      A protocol that allows the conforming object to receive metric payloads from the metric manager.
 @discussion    In order to receive metric payloads, atleast one object must conform to this protocol and be subscribed   to the metric manager.
 @discussion    Objects which conform to this protocol can be passed to addSubscriber:subscriber and removeSubscriber:subscriber to manage their subscription state.
 */
API_AVAILABLE(ios(13.0), macos(12.0)) API_UNAVAILABLE(tvos, watchos)
@protocol MXMetricManagerSubscriber <NSObject>

@optional

/*!
 @method        didReceiveMetricPayloads:payloads
 @abstract      This method is invoked when a new MXMetricPayload has been received.
 @param         payloads
 An NSArray of MXMetricPayload objects. This array of payloads contains data from previous usage sessions.
 @discussion    You can expect for this method to be invoked atleast once per day when the app is running and subscribers are available.
 @discussion    If no subscribers are available, this method will not be invoked.
 @discussion    Atleast one subscriber must be available to receive metrics.
 @discussion    This method is invoked on a background queue.
 */
- (void)didReceiveMetricPayloads:(NSArray<MXMetricPayload *> * _Nonnull)payloads API_AVAILABLE(macos(10.15));

/*!
 @method        didReceiveDiagnosticPayloads:payloads
 @abstract      This method is invoked when a new MXDiagnosticPayload has been received.
 @param         payloads
 An NSArray of MXDiagnosticPayload objects. This array of payloads contains diagnostics from previous usage sessions.
 @discussion    You can expect for this method to be invoked atleast once per day when the app is running and subscribers are available.
 @discussion    If no subscribers are available, this method will not be invoked.
 @discussion    Atleast one subscriber must be available to receive diagnostics.
 @discussion    This method is invoked on a background queue.
 */
- (void)didReceiveDiagnosticPayloads:(NSArray<MXDiagnosticPayload *> * _Nonnull)payloads API_AVAILABLE(ios(14.0), macos(12.0)) API_UNAVAILABLE(tvos, watchos);

@end

NS_ASSUME_NONNULL_END
