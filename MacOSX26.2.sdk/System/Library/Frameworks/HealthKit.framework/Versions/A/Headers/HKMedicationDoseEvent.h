//
//  HKMedicationDoseEvent.h
//  HealthKit
//
//  Copyright © 2025 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HealthKit/HKDefines.h>
#import <HealthKit/HKSample.h>

@class HKHealthConceptIdentifier;
@class HKUnit;
@class HKMedicationDoseEventType;

NS_ASSUME_NONNULL_BEGIN

/// The statuses the system assigns to a logged medication dose event.
typedef NS_ENUM(NSInteger, HKMedicationDoseEventLogStatus) {
    /// The person doesn't interact with a scheduled medication reminder.
    ///
    /// The system generates this to represent an untouched reminder slot.
    HKMedicationDoseEventLogStatusNotInteracted = 1,
    /// The system assigns this status when it fails to deliver a scheduled medication notification.
    ///
    /// The system can generate this status because of a person's notification
    /// restrictions or issues with notification delivery.
    HKMedicationDoseEventLogStatusNotificationNotSent,
    /// The person snoozes a scheduled medication notification.
    HKMedicationDoseEventLogStatusSnoozed,
    /// The person logs that they took the medication dose.
    HKMedicationDoseEventLogStatusTaken,
    /// The person logs that they skipped the medication dose.
    HKMedicationDoseEventLogStatusSkipped,
    /// The person undoes a previously logged medication status.
    ///
    /// The system clears the prior status.
    HKMedicationDoseEventLogStatusNotLogged,
} API_AVAILABLE(ios(26.0), watchos(26.0), macCatalyst(26.0), macos(26.0), visionos(26.0)) NS_SWIFT_NAME(HKMedicationDoseEvent.LogStatus);

/// The kind of schedule the system associates with a logged medication dose event.
///
/// Each value tells you whether the person logged the dose ad-hoc or
/// in response to a scheduled medication reminder.
typedef NS_ENUM(NSInteger, HKMedicationDoseEventScheduleType) {
    /// The person logged this dose event ad-hoc, outside of any scheduled reminder.
    HKMedicationDoseEventScheduleTypeAsNeeded = 1,
    /// The person logged this dose event in response to a scheduled medication reminder.
    HKMedicationDoseEventScheduleTypeSchedule
} API_AVAILABLE(ios(26.0), watchos(26.0), macCatalyst(26.0), macos(26.0), visionos(26.0)) NS_SWIFT_NAME(HKMedicationDoseEvent.ScheduleType);

HK_EXTERN
NS_SWIFT_SENDABLE
API_AVAILABLE(ios(26.0), watchos(26.0), macCatalyst(26.0), macos(26.0), visionos(26.0))
@interface HKMedicationDoseEvent : HKSample <NSSecureCoding, NSCopying>

/// The data type that identified the samples that store medication dose event data.
///
/// You use this type when creating queries or filtering results by sample type.
@property (readonly, copy) HKMedicationDoseEventType *medicationDoseEventType;

/// The scheduling context for this logged dose event.
///
/// The system sets this to ``HKMedicationDoseEvent/ScheduleType/asNeeded`` when the person
/// logs a dose without a schedule and ``HKMedicationDoseEvent/ScheduleType/schedule`` when a person logs a dose
/// from a scheduled medication reminder.
@property (nonatomic, assign, readonly) HKMedicationDoseEventScheduleType scheduleType;

/// The identifier of the medication concept the system associates with this dose event.
///
/// The system uses this identifier to link the dose event back to its ``HKMedicationConcept`` object.
@property (nonatomic, copy, readonly) HKHealthConceptIdentifier *medicationConceptIdentifier;

/// The date and time the person takes the medication, if scheduled.
///
/// The value is always non-null for ``HKMedicationDoseEvent/ScheduleType/schedule`` and always null for  ``HKMedicationDoseEvent/ScheduleType/asNeeded``.
@property (nonatomic, copy, readonly, nullable) NSDate *scheduledDate;

/// The dose quantity a person is expected to take based on their medication schedule.
///
/// The value is always non-null for ``HKMedicationDoseEvent/ScheduleType/schedule``, and always null for ``HKMedicationDoseEvent/ScheduleType/asNeeded``.
@property (nonatomic, copy, readonly, nullable) NSNumber *scheduledDoseQuantity NS_REFINED_FOR_SWIFT;

/// The dose quantity the person reports as taken.
///
/// For scheduled dose events, the value defaults to the ``HKMedicationDoseEvent/scheduledDoseQuantity-477ge``, when logged from a
/// reminder. For as needed dose events, the value defaults to `1` in the medication tracking experience, but can always be edited by the person logging.
@property (nonatomic, copy, readonly, nullable) NSNumber *doseQuantity NS_REFINED_FOR_SWIFT;

/// The log status the system assigns to this dose event.
@property (nonatomic, assign, readonly) HKMedicationDoseEventLogStatus logStatus;

/// The unit that the system associates with the medication when the person logs the dose.
///
/// This ensures that the dose quantity is recorded with the correct measurement unit.
@property (nonatomic, copy, readonly, nonnull) HKUnit *unit;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

/// The key path you use to create predicates that query by a dose event’s log status.
HK_EXTERN NSString * const HKPredicateKeyPathStatus API_AVAILABLE(ios(26.0), watchos(26.0), macCatalyst(26.0), macos(26.0), visionos(26.0));
/// The key path you use to create predicates that query by the dose event's medication log origin.
HK_EXTERN NSString * const HKPredicateKeyPathLogOrigin API_AVAILABLE(ios(26.0), watchos(26.0), macCatalyst(26.0), macos(26.0), visionos(26.0));
/// The key path you use to create predicates that query by the dose event's scheduled date.
HK_EXTERN NSString * const HKPredicateKeyPathScheduledDate API_AVAILABLE(ios(26.0), watchos(26.0), macCatalyst(26.0), macos(26.0), visionos(26.0));
/// The key path you use to create predicates that query by the dose event's medication concept identifier.
HK_EXTERN NSString * const HKPredicateKeyPathMedicationConceptIdentifier API_AVAILABLE(ios(26.0), watchos(26.0), macCatalyst(26.0), macos(26.0), visionos(26.0));

NS_ASSUME_NONNULL_END

