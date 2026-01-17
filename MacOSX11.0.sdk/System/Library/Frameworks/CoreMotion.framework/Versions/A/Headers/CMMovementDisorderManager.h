//
//  CMMovementDisorderManager.h
//  CoreMotion
//
//  Copyright (c) 2018 Apple Inc. All rights reserved.
//

#import <CoreMotion/CMAvailability.h>
#import <CoreMotion/CMAuthorization.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * @class CMDyskineticSymptomResult
 * @discussion A CMDyskineticSymptomResult object describes the presence and prevalence of dyskinetic symptoms (specifically, choreiform movements) during a one minute result period when subjects wear the Apple Watch on their most affected arm.
 * percentUnlikely + percentLikely = 1.0
 * Please note dyskinetic symptom measurements are designed for subjects with known presence of chorea in the arm and should not be displayed to users who do not report episodes of dyskinetic symptoms.
 */
API_AVAILABLE(ios(12.0), watchos(5.0)) API_UNAVAILABLE(macos, tvos)
@interface CMDyskineticSymptomResult : NSObject <NSCopying, NSSecureCoding>

/*!
 * @brief The date and time representing the start of the result.
 */
@property (copy, nonatomic, readonly) NSDate *startDate;

/*!
 * @brief The date and time representing the end of the result.
 */
@property (copy, nonatomic, readonly) NSDate *endDate;

/*!
 * @brief The percentage of time dyskinetic symptoms were unlikely for the result.
 */
@property (nonatomic, readonly) float percentUnlikely;

/*!
 * @brief The percentage of time dyskinetic symptoms were likely for the result.
 */
@property (nonatomic, readonly) float percentLikely;

@end

/*!
 * @class CMTremorResult
 * @discussion A CMTremorResult object describes the presence and prevalence of tremor symptoms (specifically, resting tremor) during a one minute result period when subjects wear the Apple Watch on their most affected arm.
 * percentUnknown + percentNoTremor + percentTremorSlight + percentTremorMild + percentTremorModerate + percentTremorStrong = 1.0
 */
API_AVAILABLE(ios(12.0), watchos(5.0)) API_UNAVAILABLE(macos, tvos)
@interface CMTremorResult : NSObject <NSCopying, NSSecureCoding>

/*!
 * @brief The date and time representing the start of the result.
 */
@property (copy, nonatomic, readonly) NSDate *startDate;

/*!
 * @brief The date and time representing the end of the result.
 */
@property (copy, nonatomic, readonly) NSDate *endDate;

/*!
 * @discussion The percentage of time tremor was unknown for the result.
 * Unknown periods include times when:
 *   1. the subject is moving and therefore a resting tremor cannot be assessed, and
 *   2. the signal strength is too low to measure tremor confidently.
 */
@property (nonatomic, readonly) float percentUnknown;

/*!
 * @brief The percentage of time no tremor was detected for the result.
 */
@property (nonatomic, readonly) float percentNone;

/*!
 * @brief The percentage of time tremor was likely and displacement amplitude was slight for the result.
 */
@property (nonatomic, readonly) float percentSlight;

/*!
 * @brief The percentage of time tremor was likely and displacement amplitude was mild for the result.
 */
@property (nonatomic, readonly) float percentMild;

/*!
 * @brief The percentage of time tremor was likely and displacement amplitude was moderate for the result.
 */
@property (nonatomic, readonly) float percentModerate;

/*!
 * @brief The percentage of time tremor was likely and displacement amplitude was strong for the result.
 */
@property (nonatomic, readonly) float percentStrong;

@end

/*!
 * @typedef CMDyskineticSymptomResultHandler
 * @brief Completion handler for CMDyskineticSymptomResult values.
 */
typedef void(^CMDyskineticSymptomResultHandler)(NSArray<CMDyskineticSymptomResult *> * _Nonnull dyskineticSymptomResult, NSError * _Nullable error) API_AVAILABLE(watchos(5.0)) API_UNAVAILABLE(ios, macos, tvos);

/*!
 * @typedef CMTremorResultHandler
 * @brief Completion handler for CMTremorResult values.
 */
typedef void(^CMTremorResultHandler)(NSArray<CMTremorResult *> * _Nonnull tremorResult, NSError * _Nullable error) API_AVAILABLE(watchos(5.0)) API_UNAVAILABLE(ios, macos, tvos);

/*!
 * @class CMMovementDisorderManager
 * @discussion A CMMovementDisorderManager object with methods for persistence and query of movement disorder results.
 */
API_AVAILABLE(watchos(5.0)) API_UNAVAILABLE(ios, macos, tvos)
@interface CMMovementDisorderManager : NSObject

/*!
 * @method isAvailable
 * @discussion Whether movement disorder results are available on this platform.
 * @return Returns the availability of movement disorder results on this platform.
 */
+ (BOOL)isAvailable;

/*!
 * @method authorizationStatus
 * @discussion Authorization status of movement disorder results for this user.
 * @return Returns the authorization status of movement disorder results for this user.
 */
+ (CMAuthorizationStatus)authorizationStatus;

/*!
 * @method monitorKinesiasForDuration:
 * @discussion Enables the calculation and persistence of result values for the specified duration in seconds.
 * @param duration The duration in seconds to enable the calculation and persistence of result values.
 * @warning Please note that the maximum duration allowed is seven (7) days.
 */
- (void)monitorKinesiasForDuration:(NSTimeInterval)duration;

/*!
 * @method queryDyskineticSymptomFromDate:toDate:withHandler:
 * @discussion Queries the system for result values for the specified date range.
 * @param fromDate The begin date for the query range.
 * @param toDate The end date for the query range.
 * @param handler The completion handler for accessing and processing result values.
 * @warning Please note that movement disorder results are available for a maximum of seven (7) days.
 */
- (void)queryDyskineticSymptomFromDate:(NSDate *)fromDate toDate:(NSDate *)toDate withHandler:(CMDyskineticSymptomResultHandler)handler;

/*!
 * @method queryTremorFromDate:toDate:withHandler:
 * @discussion Queries the system for result values for the specified date range.
 * @param fromDate The begin date for the query range.
 * @param toDate The end date for the query range.
 * @param handler The completion handler for accessing and processing result values.
 * @warning Please note that movement disorder results are available for a maximum of seven (7) days.
 */
- (void)queryTremorFromDate:(NSDate *)fromDate toDate:(NSDate *)toDate withHandler:(CMTremorResultHandler)handler;

/*!
 * @method lastProcessedDate
 * @discussion The last time that data has been processed; queries for periods before this point will return their final results. Data after this point may become available later if monitoring is continuing.
 * @warning Returns nil if no data has been processed or monitoring was not enabled.
 */
- (NSDate * _Nullable)lastProcessedDate;

/*!
 * @method monitorKinesiasExpirationDate
 * @discussion The expiration date for the most recent monitoring period.
 * @warning Returns nil if no previous monitoring period is available.
 */
- (NSDate * _Nullable)monitorKinesiasExpirationDate;

@end

NS_ASSUME_NONNULL_END
