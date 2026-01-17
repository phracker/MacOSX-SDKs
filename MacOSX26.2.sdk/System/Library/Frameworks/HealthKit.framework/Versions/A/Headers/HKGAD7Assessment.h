//
//  HKGAD7Assessment.h
//  HealthKit
//
//  Copyright © 2023-2024 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HealthKit/HKDefines.h>
#import <HealthKit/HKScoredAssessment.h>

NS_ASSUME_NONNULL_BEGIN


/*!
 @enum          HKGAD7AssessmentRisk
 @abstract      Anxiety risk level determined by GAD-7 assessment.
 */
typedef NS_ENUM(NSInteger, HKGAD7AssessmentRisk) {
    HKGAD7AssessmentRiskNoneToMinimal = 1,
    HKGAD7AssessmentRiskMild,
    HKGAD7AssessmentRiskModerate,
    HKGAD7AssessmentRiskSevere,
} NS_SWIFT_NAME(HKGAD7Assessment.Risk) API_AVAILABLE(ios(18.0), watchos(11.0), macCatalyst(18.0), macos(15.0), visionos(2.0));

/*!
 @enum          HKGAD7AssessmentAnswer
 @abstract      Answer to question on GAD-7 assessment.
 */
typedef NS_ENUM(NSInteger, HKGAD7AssessmentAnswer) {
    HKGAD7AssessmentAnswerNotAtAll = 0,
    HKGAD7AssessmentAnswerSeveralDays,
    HKGAD7AssessmentAnswerMoreThanHalfTheDays,
    HKGAD7AssessmentAnswerNearlyEveryDay,
} NS_SWIFT_NAME(HKGAD7Assessment.Answer) API_AVAILABLE(ios(18.0), watchos(11.0), macCatalyst(18.0), macos(15.0), visionos(2.0));

/// Returns the lower bound of the score range for the given GAD-7 risk classification.
HK_EXTERN NSInteger HKMinimumScoreForGAD7AssessmentRisk(HKGAD7AssessmentRisk risk) API_UNAVAILABLE(ios, watchos, macCatalyst, macos);

/// Returns the upper bound of the score range for the given GAD-7 risk classification.
HK_EXTERN NSInteger HKMaximumScoreForGAD7AssessmentRisk(HKGAD7AssessmentRisk risk) API_UNAVAILABLE(ios, watchos, macCatalyst, macos);

/// Represents the result of a GAD-7 assessment. Learn more about Pfizer's GAD-7 at https://support.apple.com/en-us/105070
HK_EXTERN
NS_SWIFT_SENDABLE
API_AVAILABLE(ios(18.0), watchos(11.0), macCatalyst(18.0), macos(15.0), visionos(2.0))
@interface HKGAD7Assessment : HKScoredAssessment

/// Answers on the GAD-7 assessment. There are exactly 7 answers, one for each multiple choice question. Each answer is of type `HKGAD7AssessmentAnswer`.
@property (nonatomic, copy, readonly) NSArray<NSNumber *> *answers NS_REFINED_FOR_SWIFT;

/*!
 @property   risk
 @discussion The risk determined by the score on a GAD-7 assessment.
 */
@property (nonatomic, assign, readonly) HKGAD7AssessmentRisk risk;

/// Creates a new GAD-7 sample. There must be exactly 7 elements in answers, each answer must be of type `HKGAD7AssessmentAnswer`.
+ (instancetype)assessmentWithDate:(NSDate *)date
                           answers:(NSArray<NSNumber *> *)answers NS_REFINED_FOR_SWIFT;

/// Creates a new GAD-7 sample. There must be exactly 7 elements in answers, each answer must be of type `HKGAD7AssessmentAnswer`.
+ (instancetype)assessmentWithDate:(NSDate *)date
                           answers:(NSArray<NSNumber *> *)answers
                          metadata:(nullable NSDictionary<NSString *, id> *)metadata NS_REFINED_FOR_SWIFT;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end


NS_ASSUME_NONNULL_END
