//
//  INRelevanceProvider.h
//  Intents
//
//  Copyright © 2018 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, INDailyRoutineSituation) {
    INDailyRoutineSituationMorning,
    INDailyRoutineSituationEvening,
    INDailyRoutineSituationHome,
    INDailyRoutineSituationWork,
    INDailyRoutineSituationSchool,
    INDailyRoutineSituationGym,
} NS_SWIFT_NAME(INDailyRoutineRelevanceProvider.Situation) API_AVAILABLE(ios(12.0), watchos(5.0)) API_UNAVAILABLE(macosx);

API_AVAILABLE(ios(12.0), watchos(5.0)) API_UNAVAILABLE(macosx)
@interface INRelevanceProvider : NSObject <NSCopying, NSSecureCoding>

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@end

API_AVAILABLE(ios(12.0), watchos(5.0)) API_UNAVAILABLE(macosx)
@interface INDateRelevanceProvider : INRelevanceProvider

@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSDate *startDate;
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSDate *endDate;

- (instancetype)initWithStartDate:(NSDate *)startDate endDate:(nullable NSDate *)endDate NS_DESIGNATED_INITIALIZER;

@end

API_AVAILABLE(ios(12.0), watchos(5.0)) API_UNAVAILABLE(macosx)
@interface INLocationRelevanceProvider : INRelevanceProvider

@property (readonly, copy, NS_NONATOMIC_IOSONLY) CLRegion *region;

- (instancetype)initWithRegion:(CLRegion *)region NS_DESIGNATED_INITIALIZER;

@end

API_AVAILABLE(ios(12.0), watchos(5.0)) API_UNAVAILABLE(macosx)
@interface INDailyRoutineRelevanceProvider : INRelevanceProvider

@property (readonly, NS_NONATOMIC_IOSONLY) INDailyRoutineSituation situation;

- (instancetype)initWithSituation:(INDailyRoutineSituation)situation NS_DESIGNATED_INITIALIZER;

@end

NS_ASSUME_NONNULL_END
