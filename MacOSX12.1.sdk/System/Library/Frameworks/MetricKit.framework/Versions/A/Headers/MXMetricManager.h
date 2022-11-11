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
@property (readonly, nonnull, strong) NSArray<MXMetricPayload *> *pastPayloads API_UNAVAILABLE(macos);

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
- (void)didReceiveMetricPayloads:(NSArray<MXMetricPayload *> * _Nonnull)payloads API_UNAVAILABLE(macos);

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
