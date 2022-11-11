//
//  HKActivityRingView.h
//  HealthKitUI
//
//  Copyright (c) 2015 Apple. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <HealthKit/HKDefines.h>

@class HKActivitySummary;

NS_ASSUME_NONNULL_BEGIN

HK_EXTERN API_AVAILABLE(ios(9.3), watchos(2.2))
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
