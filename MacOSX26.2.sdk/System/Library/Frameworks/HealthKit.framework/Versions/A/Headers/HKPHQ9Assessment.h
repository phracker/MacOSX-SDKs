//
//  HKPHQ9Assessment.h
//  HealthKit
//
//  Copyright © 2023-2024 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HealthKit/HKDefines.h>
#import <HealthKit/HKScoredAssessment.h>

NS_ASSUME_NONNULL_BEGIN


/*!
 @enum          HKPHQ9AssessmentRisk
 @abstract      Depression risk level determined by PHQ-9 assessment.
 */
typedef NS_ENUM(NSInteger, HKPHQ9AssessmentRisk) {
    HKPHQ9AssessmentRiskNoneToMinimal = 1,
    HKPHQ9AssessmentRiskMild,
    HKPHQ9AssessmentRiskModerate,
    HKPHQ9AssessmentRiskModeratelySevere,
    HKPHQ9AssessmentRiskSevere
} NS_SWIFT_NAME(HKPHQ9Assessment.Risk) API_AVAILABLE(ios(18.0), watchos(11.0), macCatalyst(18.0), macos(15.0), visionos(2.0));

/*!
 @enum          HKPHQ9AssessmentAnswer
 @abstract      Answer to question on PHQ-9 assessment.
 */
typedef NS_ENUM(NSInteger, HKPHQ9AssessmentAnswer) {
    HKPHQ9AssessmentAnswerNotAtAll = 0,
    HKPHQ9AssessmentAnswerSeveralDays,
    HKPHQ9AssessmentAnswerMoreThanHalfTheDays,
    HKPHQ9AssessmentAnswerNearlyEveryDay,
    HKPHQ9AssessmentAnswerPreferNotToAnswer /// Only acceptable for Question #9 on the PHQ-9
} NS_SWIFT_NAME(HKPHQ9Assessment.Answer) API_AVAILABLE(ios(18.0), watchos(11.0), macCatalyst(18.0), macos(15.0), visionos(2.0));

/// Returns the lower bound of the score range for the given PHQ-9 risk classification.
HK_EXTERN NSInteger HKMinimumScoreForPHQ9AssessmentRisk(HKPHQ9AssessmentRisk risk) API_UNAVAILABLE(ios, watchos, macCatalyst, macos);

/// Returns the upper bound of the score range for the given PHQ-9 risk classification.
HK_EXTERN NSInteger HKMaximumScoreForPHQ9AssessmentRisk(HKPHQ9AssessmentRisk risk) API_UNAVAILABLE(ios, watchos, macCatalyst, macos);

/// Represents the result of a PHQ-9 assessment. Learn more about Pfizer's PHQ-9 at https://support.apple.com/en-us/105070
HK_EXTERN
NS_SWIFT_SENDABLE
API_AVAILABLE(ios(18.0), watchos(11.0), macCatalyst(18.0), macos(15.0), visionos(2.0))
@interface HKPHQ9Assessment: HKScoredAssessment

/// Answers on the PHQ-9 assessment. There are exactly 9 answers, one for each multiple choice question. Each answer is of type `HKPHQ9AssessmentAnswer`. If the 9th question was unanswered,  the answer is `HKPHQ9AssessmentAnswerPreferNotToAnswer`.
@property (nonatomic, copy, readonly) NSArray<NSNumber *> *answers NS_REFINED_FOR_SWIFT;

/*!
 @property   risk
 @discussion The risk determined by the score on a PHQ-9 assessment.
 */
@property (nonatomic, assign, readonly) HKPHQ9AssessmentRisk risk;

/// Creates a new PHQ-9 sample. There must be exactly 9 elements in answers, each answer must be of type `HKPHQ9AssessmentAnswer`.
/// Question #9 is considered optional. If the user does not answer #9, use `HKPHQ9AssessmentAnswerPreferNotToAnswer`
+ (instancetype)assessmentWithDate:(NSDate *)date
                           answers:(NSArray<NSNumber *> *)answers NS_REFINED_FOR_SWIFT;

/// Creates a new PHQ-9 sample. There must be exactly 9 elements in answers, each answer must be of type `HKPHQ9AssessmentAnswer`.
/// Question #9 is considered optional. If the user does not answer #9, use `HKPHQ9AssessmentAnswerPreferNotToAnswer`
+ (instancetype)assessmentWithDate:(NSDate *)date
                           answers:(NSArray<NSNumber *> *)answers
                          metadata:(nullable NSDictionary<NSString *, id> *)metadata NS_REFINED_FOR_SWIFT;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end


NS_ASSUME_NONNULL_END
