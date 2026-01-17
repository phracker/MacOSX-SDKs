//
//  HKHeartbeatSeriesBuilder.h
//  HealthKit
//
//  Copyright © 2018-2022 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HealthKit/HKDefines.h>
#import <HealthKit/HKSeriesBuilder.h>

NS_ASSUME_NONNULL_BEGIN

@class HKHealthStore;
@class HKDevice;
@class HKHeartbeatSeriesSample;

/*!
 @class              HKHeartbeatSeriesBuilder
 @abstract           An HKHeartbeatSeriesBuilder is used to generate an HKHeartbeatSeriesSample.
 @discussion         This class is intended for generating an HKHeartbeatSeriesSample which represents a series of
                     heartbeats. If the discard method is called, collected data will be deleted.
                     Calling finishSeriesWithcompletion: will stop and complete the series. If the builder is deleted,
                     or the client goes away before calling the finish method, data will be lost.
 */
HK_EXTERN
NS_SWIFT_SENDABLE
API_AVAILABLE(ios(13.0), watchos(6.0), macCatalyst(13.0), macos(13.0))
@interface HKHeartbeatSeriesBuilder : HKSeriesBuilder

/*!
 @property           maximumCount
 @abstract           The maximum number of heartbeats that can be added to an HKHeartbeatSeriesBuilder.
 @discussion         Any calls to addHeartbeatWithTimeIntervalSinceSeriesStartDate:precededByGap:completion: once
                     maximumCount has been reached will fail and an error will be returned in the completion handler.
 */
@property (class, readonly) NSUInteger maximumCount;

/*!
 @method             initWithHealthStore:device:startDate:
 @abstract           The designated initializer to create an HKHeartbeatSeriesBuilder.
 @discussion         The HKHealthStore is retained during the life of the object for the saving of the series data and final
                     return of the series sample.
 
 @param              healthStore  Specifies the HKHealthStore object to use for building the series.
 @param              device       The optional device represents the HKDevice from which the data is provided.
 @param              startDate    The start date of the HKHeartbeatSeriesSample that will be generated.
 */
- (instancetype)initWithHealthStore:(HKHealthStore *)healthStore
                             device:(nullable HKDevice *)device
                          startDate:(NSDate *)startDate NS_DESIGNATED_INITIALIZER;

/*!
 @method             addHeartbeatWithTimeIntervalSinceSeriesStartDate:precededByGap:completion:
 @abstract           Associate a heartbeat with the receiver.
 @discussion         Use this method to asynchronously add a heartbeat to the series.
 
 @param     timeIntervalSinceStart  The elapsed time between the series startDate and the heartbeat occurence. Must be
                                    a positive value.
 @param              precededByGap  Whether or not this heartbeat was preceded by a gap in data collection.
 @param              completion     The completion callback handler returns the status of the save. If the completion
                                    handler success is NO, then error is non-nil. An error here is considered fatal and
                                    the series builder will be complete.
 */
- (void)addHeartbeatWithTimeIntervalSinceSeriesStartDate:(NSTimeInterval)timeIntervalSinceStart
                                           precededByGap:(BOOL)precededByGap
                                              completion:(void (^)(BOOL success, NSError * _Nullable error))completion NS_SWIFT_ASYNC_NAME(addHeartbeat(at:precededByGap:)) NS_SWIFT_ASYNC_THROWS_ON_FALSE(1);

/*!
 @method             addMetadata:completion:
 @discussion         Adds new metadata to the builder instance. This method can be called more than once; each time
                     the newly provided metadata will be incorporated in the same manner as
                     -[NSMutableDictionary addEntriesFromDictionary:].
                     This operation is performed asynchronously and the completion will be executed on an arbitrary
                     background queue.
 
 @param              metadata    The metadata to add to the builder.
 @param              completion  Block to be called when the addition of metadata to the builder is complete.
                                 If success is YES, the metadata has been added to the builder successfully. If success
                                 is NO, error will be non-null and will contain the error encountered during the
                                 insertion operation. When an error occurs, the builder's metadata will remain unchanged.
 */
- (void)addMetadata:(NSDictionary<NSString *, id> *)metadata
         completion:(void (^)(BOOL success, NSError * _Nullable error))completion NS_SWIFT_ASYNC_THROWS_ON_FALSE(1);

/*!
 @method             finishSeriesWithCompletion:
 @abstract           Method to stop data collection and return the associated HKHeartbeatSeriesSample.
 @discussion         Call this method when you have added all heartbeats to this builder. The completion handler will
                     return the saved HKHeartbeatSeriesSample. If no heartbeat was added, then heartbeatSeries will be
                     nil and an error returned. The receiver will be considered invalid afterwards and any further calls
                     to it will result in an error.

 @param              completion  The completion callback handler returns the saved HKHeartbeatSeriesSample object. If
                                 heartbeatSeries is nil, an error will indicate why the series could not be returned
                                 including database inaccessibility during device lock. Subsequent requests for the
                                 HKHeartbeatSeriesSample can be made through HKSampleQuery or similar queries. To
                                 retrieve the data stored with an HKHeartbeatSeriesSample use HKHeartbeatSeriesQuery.
 */
- (void)finishSeriesWithCompletion:(void (^)(HKHeartbeatSeriesSample * _Nullable heartbeatSeries, NSError * _Nullable error))completion;

@end

NS_ASSUME_NONNULL_END
