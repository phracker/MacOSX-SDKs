//
//  HKActivityRingView.h
//  HealthKitUI
//
//  Copyright (c) 2015 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HealthKit/HealthKit.h>
#import <os/availability.h>
#import <UIKit/UIKit.h>

@class HKActivitySummary;

NS_ASSUME_NONNULL_BEGIN

HK_EXTERN API_AVAILABLE(ios(9.3), macCatalyst(13.0), macos(13.0)) API_UNAVAILABLE(watchos)
@interface HKActivityRingView : UIView

/**
 @property      activitySummary
 @abstract      The activity summary that is currently being displayed in the activity ring view
 @discussion    Setting this property directly will not animate ring changes
 */
@property (nonatomic, strong, nullable) HKActivitySummary *activitySummary;

- (void)setActivitySummary:(nullable HKActivitySummary *)activitySummary animated:(BOOL)animated;

@end

NS_ASSUME_NONNULL_END
