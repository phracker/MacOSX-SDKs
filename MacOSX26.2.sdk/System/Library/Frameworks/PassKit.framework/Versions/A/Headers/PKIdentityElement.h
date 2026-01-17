#if !__has_include(<PassKitCore/PKIdentityElement.h>) || PK_USE_PUBLIC_PASSKIT
//
//  PKIdentityElement.h
//    PassKit
//
//  Copyright © 2022 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/// Elements that can be requested from identity documents. Not
/// all elements are supported by all document types. If an element
/// is requested from a type that does not support it, the element
/// is ignored.
API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface PKIdentityElement: NSObject <NSCopying>

/// The user's given name or first name.
@property (class, nonatomic, readonly) PKIdentityElement *givenNameElement;

/// The user's family name or last name.
@property (class, nonatomic, readonly) PKIdentityElement *familyNameElement;

/// The portrait of the user on record with the issuer.
@property (class, nonatomic, readonly) PKIdentityElement *portraitElement;

/// The address on record with the issuer.
@property (class, nonatomic, readonly) PKIdentityElement *addressElement;

/// The user's height on record with the issuer.
@property (nonatomic, class, readonly) PKIdentityElement *heightElement API_AVAILABLE(ios(26.0));

/// The user's weight on record with the issuer.
@property (nonatomic, class, readonly) PKIdentityElement *weightElement API_AVAILABLE(ios(26.0));

/// The user's eye color on record with the issuer.
@property (nonatomic, class, readonly) PKIdentityElement *eyeColorElement API_AVAILABLE(ios(26.0));

/// The user's hair color on record with the issuer.
@property (nonatomic, class, readonly) PKIdentityElement *hairColorElement API_AVAILABLE(ios(26.0));

/// The user's organ donor status on record with the issuer.
@property (nonatomic, class, readonly) PKIdentityElement *organDonorStatusElement API_AVAILABLE(ios(26.0));

/// The user's veteran status on record with the issuer.
@property (nonatomic, class, readonly) PKIdentityElement *veteranStatusElement API_AVAILABLE(ios(26.0));

/// The state or government that issued the identity document.
@property (class, nonatomic, readonly) PKIdentityElement *issuingAuthorityElement;

/// The document's issue date. This is usually the issue date of the corresponding physical
/// document, if applicable.
@property (class, nonatomic, readonly) PKIdentityElement *documentIssueDateElement;

/// The document's expiration date. This is usually the expiration date of the corresponding physical
/// document, if applicable.
@property (class, nonatomic, readonly) PKIdentityElement *documentExpirationDateElement;

/// The document's DHS (U.S. Department of Homeland Security) compliance status.
///
/// This is also known as the document's "REAL ID status".
@property (class, nonatomic, readonly) PKIdentityElement *documentDHSComplianceStatusElement API_AVAILABLE(ios(17.2));

/// The document's number, as defined by the document's issuing authority.
@property (class, nonatomic, readonly) PKIdentityElement *documentNumberElement;

/// The user's driving privileges.
@property (class, nonatomic, readonly) PKIdentityElement *drivingPrivilegesElement;

/// The user's age in years.
@property (class, nonatomic, readonly) PKIdentityElement *ageElement;

/// The user's date of birth.
@property (class, nonatomic, readonly) PKIdentityElement *dateOfBirthElement;

/// The user's sex.
@property (class, nonatomic, readonly) PKIdentityElement *sexElement API_AVAILABLE(ios(17.2));

/// Boolean indicating whether the user's age is at least the given age.
/// For example, ageThresholdElementWithAge:21 will return true if the user is at least 21 years old.
/// This value is only available for a given age if it was provided by the issuer. If this value
/// is not available, it will automatically fall back to a request for age.
+ (instancetype)ageThresholdElementWithAge:(NSInteger)age NS_SWIFT_NAME(age(atLeast:));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END


#else
#import <TargetConditionals.h>
#import <PassKitCore/PKIdentityElement.h>
#endif