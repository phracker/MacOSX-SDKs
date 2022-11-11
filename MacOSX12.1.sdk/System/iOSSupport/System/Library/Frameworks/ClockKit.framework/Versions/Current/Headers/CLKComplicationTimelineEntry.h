//
//  CLKComplicationTimelineEntry.h
//  ClockKit
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class CLKComplicationTemplate;

API_AVAILABLE(watchos(2.0)) API_UNAVAILABLE(ios)
@interface CLKComplicationTimelineEntry : NSObject

+ (instancetype)entryWithDate:(NSDate *)date complicationTemplate:(CLKComplicationTemplate *)complicationTemplate;
+ (instancetype)entryWithDate:(NSDate *)date complicationTemplate:(CLKComplicationTemplate *)complicationTemplate timelineAnimationGroup:(NSString * __nullable)timelineAnimationGroup;

@property (nonatomic, retain) NSDate *date;
@property (nonatomic, copy) CLKComplicationTemplate *complicationTemplate;
@property (nonatomic, copy) NSString * __nullable timelineAnimationGroup;

@end

NS_ASSUME_NONNULL_END
