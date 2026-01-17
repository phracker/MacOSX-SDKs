//
//  HKUserAnnotatedMedication.h
//  HealthKit
//
//  Copyright © 2025 Apple. All rights reserved.
//


#import <Foundation/Foundation.h>
#import <HealthKit/HKDefines.h>

@class HKMedicationConcept;
@class HKUserAnnotatedMedicationType;

NS_ASSUME_NONNULL_BEGIN

/// A reference to the tracked medication and the details a person can customize.
///
/// The details are relevant to the medication tracking experience.
HK_EXTERN
NS_SWIFT_SENDABLE
API_AVAILABLE(ios(26.0), watchos(26.0), macCatalyst(26.0), macos(26.0), visionos(26.0))
@interface HKUserAnnotatedMedication : NSObject <NSSecureCoding, NSCopying>

/// The nickname that a person added to a medication during the entry experience.
///
/// This can be edited at any point.
@property (nonatomic, copy, readonly, nullable) NSString *nickname;

/// A Boolean value that indicates whether a medication is archived.
///
/// The value is `true` if a person moves a medication to the archived section in the Health App.
/// The value is `false` if a medication isn't in the archived section.
@property (nonatomic, assign, readonly) BOOL isArchived;

/// A Boolean value that indicates whether a medication has a schedule set up.
///
/// The value is `true` for medications for which a person has set up reminders and `false` for medications that are only taken as needed.
/// > Note: Scheduled medications can still be taken as needed.
@property (nonatomic, assign, readonly) BOOL hasSchedule;

/// A reference to the specific medication a person is tracking.
///
/// This concept's identifier is directly associated with the logged dose events.
@property (nonatomic, copy, readonly) HKMedicationConcept *medication;

- (instancetype)init NS_UNAVAILABLE;

@end

/// The key path you use to create predicates for the medication's archived status.
///
/// Use to predicate against the ``HKUserAnnotatedMedication/isArchived`` property of a medication.
HK_EXTERN NSString * const HKUserAnnotatedMedicationPredicateKeyPathIsArchived API_AVAILABLE(ios(26.0), watchos(26.0), macCatalyst(26.0), macos(26.0), visionos(26.0));
/// The key path you use to create predicates for whether or not a medication has a schedule.
///
/// Use to predicate against the ``HKUserAnnotatedMedication/hasSchedule`` property of a medication.
HK_EXTERN NSString * const HKUserAnnotatedMedicationPredicateKeyPathHasSchedule API_AVAILABLE(ios(26.0), watchos(26.0), macCatalyst(26.0), macos(26.0), visionos(26.0));

NS_ASSUME_NONNULL_END
