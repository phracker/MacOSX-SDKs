//
//  INRelevanceProvider.h
//  Intents
//
//  Copyright (c) 2016-2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract A relevant daily routine situation.
 @seealso INDailyRoutineRelevanceProvider
 */
typedef NS_ENUM(NSInteger, INDailyRoutineSituation) {
    /*!
     @abstract A situation that occurs in the morning, around the time the user wakes up.
     */
    INDailyRoutineSituationMorning,
    
    /*!
     @abstract A situation that occurs in the evening, around the time the user goes to bed.
     */
    INDailyRoutineSituationEvening,
    
    /*!
     @abstract A situation that occurs when the user is at home.
     @note Your app needs Always location authorization to use this situation.
     @seealso CLLocationManager
     */
    INDailyRoutineSituationHome,
    
    /*!
     @abstract A situation that occurs when the user is at work.
     @note Your app needs Always location authorization to use this situation.
     @seealso CLLocationManager
     */
    INDailyRoutineSituationWork,
    
    /*!
     @abstract A situation that occurs when the user is at school.
     @note Your app needs Always location authorization to use this situation.
     @seealso CLLocationManager
     */
    INDailyRoutineSituationSchool,
    
    /*!
     @abstract A situation that occurs when the user is at the gym.
     @note Your app needs Always location authorization to use this situation.
     @seealso CLLocationManager
     */
    INDailyRoutineSituationGym,
    
    /*!
     @abstract A situation that occurs when the user is commuting, for example driving into work.
     */
    INDailyRoutineSituationCommute API_AVAILABLE(ios(13.0), watchos(6.0)) API_UNAVAILABLE(macos),
    
    /*!
     @abstract A situation that occurs when the user connects headphones.
     */
    INDailyRoutineSituationHeadphonesConnected API_AVAILABLE(ios(13.0), watchos(6.0)) API_UNAVAILABLE(macos),
    
    /*!
     @abstract A situation that occurs when the user is currently in a workout.
     */
    INDailyRoutineSituationActiveWorkout API_AVAILABLE(ios(13.0), watchos(6.0)) API_UNAVAILABLE(macos),
    
    /*!
     @abstract A situation that occurs when the user is expected to perform more physical activity during the day.
     */
    INDailyRoutineSituationPhysicalActivityIncomplete API_AVAILABLE(ios(13.0), watchos(6.0)) API_UNAVAILABLE(macos),
} NS_SWIFT_NAME(INDailyRoutineRelevanceProvider.Situation) API_AVAILABLE(ios(12.0), watchos(5.0)) API_UNAVAILABLE(macos, tvos);

/*!
 @abstract A relevance provider represents a piece of relevance information that can be used by Siri when predicting relevant shortcuts.
 */
API_AVAILABLE(ios(12.0), watchos(5.0)) API_UNAVAILABLE(macos, tvos)
@interface INRelevanceProvider : NSObject <NSCopying, NSSecureCoding>

/*!
 @note @c INRelevanceProvider should not be initilaized directly. Use one of the subclasses instead.
 */
- (instancetype)init NS_UNAVAILABLE;

@end

/*!
 @abstract A relevance provider to indicate relevance at a date or date interval.
 */
API_AVAILABLE(ios(12.0), watchos(5.0)) API_UNAVAILABLE(macos, tvos)
@interface INDateRelevanceProvider : INRelevanceProvider

/*!
 @abstract The start date of the relevant time interval.
 */
@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSDate *startDate;

/*!
 @abstract The end date of the relevant time interval.
 @note If @c endDate is @c nil, the relevant time interval will be assumed to represent a single point in time instead of a time interval.
 */
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSDate *endDate;

/*!
 @abstract Initializes a date relevance provider with the specified relevant date interval.
 */
- (instancetype)initWithStartDate:(NSDate *)startDate endDate:(nullable NSDate *)endDate NS_DESIGNATED_INITIALIZER;

@end

/*!
 @abstract A relevance provider to indicate relevance at a specific location.
 @note Your app needs Always or When in Use location authorization to use this relevance provider.
 */
API_AVAILABLE(ios(12.0), watchos(5.0)) API_UNAVAILABLE(macos, tvos)
@interface INLocationRelevanceProvider : INRelevanceProvider

/*!
 @abstract The region representing the relevant location.
 @seealso CLCircularRegion
 */
@property (readonly, copy, NS_NONATOMIC_IOSONLY) CLRegion *region;

/*!
 @abstract Initializes a location relevance provider with the specified region.
 */
- (instancetype)initWithRegion:(CLRegion *)region NS_DESIGNATED_INITIALIZER;

@end

/*!
 @abstract A relevance provider that specifies relevance during a specific situation.
 @seealso INDailyRoutineSituation
 */
API_AVAILABLE(ios(12.0), watchos(5.0)) API_UNAVAILABLE(macos, tvos)
@interface INDailyRoutineRelevanceProvider : INRelevanceProvider

/*!
 @abstract The relevant daily routine situation of the provider.
 */
@property (readonly, NS_NONATOMIC_IOSONLY) INDailyRoutineSituation situation;

/*!
 @abstract Initializes a daily routine relevance provider with the specified situation.
 */
- (instancetype)initWithSituation:(INDailyRoutineSituation)situation NS_DESIGNATED_INITIALIZER;

@end

NS_ASSUME_NONNULL_END
