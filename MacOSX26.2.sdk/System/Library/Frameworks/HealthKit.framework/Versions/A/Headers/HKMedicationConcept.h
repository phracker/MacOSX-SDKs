//
//  HKMedicationConcept.h
//  HealthKit
//
//  Copyright © 2025 Apple. All rights reserved.
//


#import <Foundation/Foundation.h>
#import <HealthKit/HKDefines.h>

@class HKClinicalCoding;
@class HKHealthConceptIdentifier;

NS_ASSUME_NONNULL_BEGIN

/// The manufactured form of a medication.
typedef NSString * NS_TYPED_ENUM HKMedicationGeneralForm;
/// The medication comes in capsule form, such as a hard-shell capsule or softgel.
HK_EXTERN HKMedicationGeneralForm const HKMedicationGeneralFormCapsule;
/// The medication is applied as a cream.
HK_EXTERN HKMedicationGeneralForm const HKMedicationGeneralFormCream;
/// The medication is administered through a device, such as an infusion pump for controlled fluid delivery.
HK_EXTERN HKMedicationGeneralForm const HKMedicationGeneralFormDevice;
/// The medication is taken as drops, for example eye drops or ear drops.
HK_EXTERN HKMedicationGeneralForm const HKMedicationGeneralFormDrops;
/// The medication is applied as a foam.
HK_EXTERN HKMedicationGeneralForm const HKMedicationGeneralFormFoam;
/// The medication is applied as a gel.
HK_EXTERN HKMedicationGeneralForm const HKMedicationGeneralFormGel;
/// The medication is delivered through an inhaler.
HK_EXTERN HKMedicationGeneralForm const HKMedicationGeneralFormInhaler;
/// The medication is given as an injection.
HK_EXTERN HKMedicationGeneralForm const HKMedicationGeneralFormInjection;
/// The medication is taken as a liquid, such as a syrup.
HK_EXTERN HKMedicationGeneralForm const HKMedicationGeneralFormLiquid;
/// The medication is applied as a lotion.
HK_EXTERN HKMedicationGeneralForm const HKMedicationGeneralFormLotion;
/// The medication is applied as an ointment.
HK_EXTERN HKMedicationGeneralForm const HKMedicationGeneralFormOintment;
/// The medication is applied as a patch worn on the skin.
HK_EXTERN HKMedicationGeneralForm const HKMedicationGeneralFormPatch;
/// The medication is taken as a powder.
HK_EXTERN HKMedicationGeneralForm const HKMedicationGeneralFormPowder;
/// The medication is delivered as a spray, for example a nasal spray or throat spray.
HK_EXTERN HKMedicationGeneralForm const HKMedicationGeneralFormSpray;
/// The medication is delivered as a suppository.
HK_EXTERN HKMedicationGeneralForm const HKMedicationGeneralFormSuppository;
/// The medication comes in tablet form, such as a pill or caplet.
HK_EXTERN HKMedicationGeneralForm const HKMedicationGeneralFormTablet;
/// The medication is applied topically in a form that wasn't specified.
HK_EXTERN HKMedicationGeneralForm const HKMedicationGeneralFormTopical;
/// The system doesn't know the general form of the medication.
HK_EXTERN HKMedicationGeneralForm const HKMedicationGeneralFormUnknown;

/// An object that describes a specific medication concept.
///
/// A medication concept represents the idea of a medication, like ibuprofen or insulin.
/// It can have clinical significance, or can be created by the person using your app.
HK_EXTERN
NS_SWIFT_SENDABLE
API_AVAILABLE(ios(26.0), watchos(26.0), macCatalyst(26.0), macos(26.0), visionos(26.0))
@interface HKMedicationConcept : NSObject <NSSecureCoding, NSCopying>

/// The unique identifier for the specific medication concept.
///
/// Each concept has one stable identifier that stays the same across devices.
/// You can use this identifier to directly compare medications, for example,
/// to check whether two objects represent the same medication.
@property (nonatomic, copy, readonly) HKHealthConceptIdentifier *identifier;


/// The display name for this medication.
///
/// The name of the medication a person enters or selects during medication onboarding.
@property (nonatomic, copy, readonly) NSString *displayText;

/// The general form the medication is manufactured in.
///
/// A general manufactured dose form for the specific medication.
/// This value tells you the manufactured form of the medication,
/// such as tablet, capsule, cream, injection, or inhaler.
@property (nonatomic, copy, readonly) HKMedicationGeneralForm generalForm;

/// The set of related clinical codings for the medication.
///
/// Each coding links the medication to an external medical terminology system,
/// such as RxNorm.
@property (nonatomic, copy, readonly) NSSet<HKClinicalCoding *> *relatedCodings;

- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
