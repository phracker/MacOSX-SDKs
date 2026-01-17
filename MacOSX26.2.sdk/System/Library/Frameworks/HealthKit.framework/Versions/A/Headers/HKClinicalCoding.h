//
//  HKClinicalCoding.h
//  HealthKit
//
//  Copyright © 2025 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HealthKit/HKDefines.h>

NS_ASSUME_NONNULL_BEGIN

/// A clinical coding that represents a medical concept using a standardized coding system.
///
/// A clinical coding pairs a ``system``, an optional ``version``,
/// and a ``code`` which identify a medical concept.
///
/// This model is closely related to the [FHIR Coding model](https://build.fhir.org/datatypes.html#Coding).
HK_EXTERN
NS_SWIFT_SENDABLE
API_AVAILABLE(ios(26.0), watchos(26.0), macCatalyst(26.0), macos(26.0), visionos(26.0))
@interface HKClinicalCoding : NSObject <NSCopying, NSSecureCoding>

/// The string that identifies the coding system that defines this clinical code.
///
/// The system is usually expressed as a URL from the [HL7 Terminology](https://terminology.hl7.org/).
/// For example, the RxNorm, a coding system for medications uses:
/// `http://www.nlm.nih.gov/research/umls/rxnorm`.
@property (nonatomic, copy, readonly) NSString *system;

/// The version of the coding system.
@property (nonatomic, copy, readonly, nullable) NSString *version;

/// The clinical code that represents a medical concept inside the coding system.
///
/// The format depends on the coding system. For example, RxNorm codes are numeric.
@property (nonatomic, copy, readonly) NSString *code;

- (instancetype)init NS_UNAVAILABLE;

/// Creates a clinical coding with the specified system, version, and code.
///
/// @param system  The string that identifies the coding system, typically a HL7 URL.
/// @param version The version of the system, if applicable.
/// @param code    The clinical code string that represents the medical concept.
///
/// Use when you need to explicitly construct a coding object to associate
/// a HealthKit concept with a standardized medical code.
- (instancetype)initWithSystem:(NSString *)system
                       version:(nullable NSString *)version
                          code:(NSString *)code;

@end

NS_ASSUME_NONNULL_END
