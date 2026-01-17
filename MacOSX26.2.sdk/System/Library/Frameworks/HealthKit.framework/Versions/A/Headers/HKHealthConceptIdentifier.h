//
//  HKHealthConceptIdentifier.h
//  HealthKit
//
//  Copyright © 2025 Apple. All rights reserved.
//


#import <Foundation/Foundation.h>
#import <HealthKit/HKDefines.h>

NS_ASSUME_NONNULL_BEGIN

#pragma mark - Concepts

/// A domain that represents a health concept.
///
/// A health concept describes what type of medical information a concept belongs to.
/// For example, the medication domain groups all medication concepts together.
typedef NSString * HKHealthConceptDomain NS_TYPED_ENUM API_AVAILABLE(ios(26.0), watchos(26.0), macCatalyst(26.0), macos(26.0), visionos(26.0));

/// The domain that represents medication concepts.
///
/// Use with identifiers for medications, such as ibuprofen or insulin.
HK_EXTERN HKHealthConceptDomain const HKHealthConceptDomainMedication API_AVAILABLE(ios(26.0), watchos(26.0), macCatalyst(26.0), macos(26.0), visionos(26.0));

/// A unique identifier for a specific health concept within a domain.
///
/// Each identifier points to one concept inside a domain. For example, within the medication
/// domain, one identifier might represent ibuprofen while another represents insulin.
HK_EXTERN
NS_SWIFT_SENDABLE
API_AVAILABLE(ios(26.0), watchos(26.0), macCatalyst(26.0), macos(26.0), visionos(26.0))
@interface HKHealthConceptIdentifier : NSObject <NSSecureCoding, NSCopying>

/// The domain this identifier belongs to.
///
/// This value identifies the group of concepts the identifier comes from. For example,
/// if the identifier represents a medication, the category will be the medication domain.
@property (nonatomic, copy, readonly) HKHealthConceptDomain domain;

- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
