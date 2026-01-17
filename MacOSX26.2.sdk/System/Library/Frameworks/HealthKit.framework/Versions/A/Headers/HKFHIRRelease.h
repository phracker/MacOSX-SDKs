//
//  HKFHIRRelease.h
//  HealthKit
//
//  Copyright © 2019-2022 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HealthKit/HKDefines.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract      FHIR releases are official releases of the FHIR specification.
 @discussion    FHIR releases are published on https://hl7.org/fhir. There is a one-to-many relationship between FHIR
                releases and FHIR versions.
 */
typedef NSString * HKFHIRRelease NS_TYPED_ENUM;

/*!
 @abstract      The "DSTU2" release: http://hl7.org/fhir/DSTU2/
 */
HK_EXTERN HKFHIRRelease const HKFHIRReleaseDSTU2 NS_SWIFT_NAME(dstu2) API_AVAILABLE(ios(14.0), macCatalyst(14.0), macos(13.0)) API_UNAVAILABLE(watchos);

/*!
 @abstract      The "R4" release: http://hl7.org/fhir/R4/
 */
HK_EXTERN HKFHIRRelease const HKFHIRReleaseR4 NS_SWIFT_NAME(r4) API_AVAILABLE(ios(14.0), macCatalyst(14.0), macos(13.0)) API_UNAVAILABLE(watchos);

/*!
 @abstract      An unknown release
 */
HK_EXTERN HKFHIRRelease const HKFHIRReleaseUnknown API_AVAILABLE(ios(14.0), macCatalyst(14.0), macos(13.0)) API_UNAVAILABLE(watchos);

NS_ASSUME_NONNULL_END
