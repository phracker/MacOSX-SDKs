//
//  HKHeartbeatSeriesQuery.h
//  HealthKit
//
//  Copyright © 2018 Apple. All rights reserved.
//

#import <HealthKit/HKQuery.h>

NS_ASSUME_NONNULL_BEGIN

@class HKHeartbeatSeriesSample;

/*!
 @class         HKHeartbeatSeriesQuery
 @abstract      An HKHeartbeatSeriesQuery is used to access data associated with an HKHeartbeatSeriesSample.
 @discussion    Once instantiated, call HKHealthStore executeQuery to begin enumerating the heartbeat series data.
 */
HK_EXTERN
#if defined(__swift__) && __swift__
API_DEPRECATED("Use HKHeartbeatSeriesQueryDescriptor", ios(13.0, API_TO_BE_DEPRECATED), watchos(6.0, API_TO_BE_DEPRECATED));
#else
API_AVAILABLE(ios(13.0), watchos(6.0))
#endif
@interface HKHeartbeatSeriesQuery : HKQuery

/*!
 @method        initWithHeartbeatSeries:dataHandler:
 @abstract      Returns a query that will retrieve heartbeat timestamps for the specified HKHeartbeatSeriesSample.
 
 @param         heartbeatSeries    The HKHeartbeatSeriesSample for which the heartbeat data will be returned.
 @param         dataHandler        The block to invoke with results from the query. It is called repeatedly for each
                                   heartbeat in the series. timeSinceSeriesStart is the time elapsed in seconds after the
                                   series startDate that represents when the heartbeat occured. precededByGap indicates if
                                   there was a gap in data collection before the current heartbeat, meaning that one or more
                                   heartbeats may have occured since the previous heartbeat in the series. Once done is YES,
                                   or stopQuery called, the query is complete and no more calls to the handler will be made.
 */
- (instancetype)initWithHeartbeatSeries:(HKHeartbeatSeriesSample *)heartbeatSeries
                            dataHandler:(void(^)(HKHeartbeatSeriesQuery *query, NSTimeInterval timeSinceSeriesStart, BOOL precededByGap, BOOL done, NSError * _Nullable error))dataHandler NS_DESIGNATED_INITIALIZER;

@end

NS_ASSUME_NONNULL_END
