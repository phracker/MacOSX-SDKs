//
//  HKFHIRVersion.h
//  HealthKit
//
//  Copyright © 2019 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HealthKit/HKDefines.h>

#import <HealthKit/HKFHIRRelease.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @class         HKFHIRVersion
 @abstract      Represents a FHIR version.
 @discussion    FHIR uses semantic versions ("1.0.2", "4.0.1") to communicate which FHIR version a server supports or a
                given resource is represented in. A FHIR version is associated with one FHIR release.
 @see           http://hl7.org/fhir/versions.html#versions
 */
HK_EXTERN API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos)
@interface HKFHIRVersion : NSObject <NSCopying, NSSecureCoding>

@property (nonatomic, assign, readonly) NSInteger majorVersion;

@property (nonatomic, assign, readonly) NSInteger minorVersion;

@property (nonatomic, assign, readonly) NSInteger patchVersion;

@property (nonatomic, strong, readonly) HKFHIRRelease FHIRRelease;

/*!
 @property      stringRepresentation
 @abstract      A string representation in the format "{major}.{minor}.{patch}".
 */
@property (nonatomic, copy, readonly) NSString *stringRepresentation;

- (instancetype)init NS_UNAVAILABLE;

+ (nullable instancetype)versionFromVersionString:(NSString *)versionString error:(NSError **)errorOut;

+ (instancetype)primaryDSTU2Version;

+ (instancetype)primaryR4Version;

@end

NS_ASSUME_NONNULL_END
