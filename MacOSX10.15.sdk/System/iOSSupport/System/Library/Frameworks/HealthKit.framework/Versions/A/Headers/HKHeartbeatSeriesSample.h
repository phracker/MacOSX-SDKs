//
//  HKHeartbeatSeriesSample.h
//  HealthKit
//
//  Copyright © 2018 Apple. All rights reserved.
//

#import <HealthKit/HKSeriesSample.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @class         HKHeartbeatSeriesSample
 @abstract      An HKHeartbeatSeriesSample represents a series of heartbeats.
 @discussion    To retrieve the underlying series data for an HKHeartbeatSeriesSample, use HKHeartbeatSeriesQuery
 */
HK_EXTERN API_AVAILABLE(ios(13.0), watchos(6.0))
@interface HKHeartbeatSeriesSample : HKSeriesSample

@end

NS_ASSUME_NONNULL_END
