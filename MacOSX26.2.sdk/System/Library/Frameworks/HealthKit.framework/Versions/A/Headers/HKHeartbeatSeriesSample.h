//
//  HKHeartbeatSeriesSample.h
//  HealthKit
//
//  Copyright © 2018-2022 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HealthKit/HKDefines.h>
#import <HealthKit/HKSeriesSample.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @class         HKHeartbeatSeriesSample
 @abstract      An HKHeartbeatSeriesSample represents a series of heartbeats.
 @discussion    To retrieve the underlying series data for an HKHeartbeatSeriesSample, use HKHeartbeatSeriesQuery
 */
HK_EXTERN
NS_SWIFT_SENDABLE
API_AVAILABLE(ios(13.0), watchos(6.0), macCatalyst(13.0), macos(13.0))
@interface HKHeartbeatSeriesSample : HKSeriesSample

@end

NS_ASSUME_NONNULL_END
