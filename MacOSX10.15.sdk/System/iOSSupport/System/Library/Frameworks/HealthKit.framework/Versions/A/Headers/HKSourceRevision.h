//
//  HKSourceRevision.h
//  HealthKit
//
//  Copyright © 2015 Apple. All rights reserved.
//

#import <HealthKit/HKDefines.h>

@class HKSource;

NS_ASSUME_NONNULL_BEGIN

/*!
 @class         HKSourceRevision
 @abstract      Represents a specific revision of an HKSource.
 */

HK_EXTERN API_AVAILABLE(ios(9.0), watchos(2.0))
@interface HKSourceRevision : NSObject <NSSecureCoding, NSCopying>

/*!
 @property      source
 @abstract      The HKSource of the receiver.
 */
@property (readonly) HKSource *source;

/*!
 @property      version
 @abstract      The version of the source property.
 @discussion    This value is taken from the CFBundleVersion of the source. May be nil for older data.
 */
@property (readonly, nullable) NSString *version;

/*!
 @property      productType
 @abstract      Represents the product type of the device running HealthKit when the object was created.
 @discussion    This value may be nil for older data, which indicates an unknown product type.
 */
@property (readonly, copy, nullable) NSString *productType API_AVAILABLE(ios(11.0), watchos(4.0));

/*!
 @property      operatingSystemVersion
 @abstract      Represents the operating system version of the device running HealthKit when the object was created.
 @discussion    iOS versions after 8.0 but prior to 8.2 are saved as 8.0, and iOS version after 8.2 but prior to 9.0
                are saved as 8.2.
 */
@property (readonly, assign) NSOperatingSystemVersion operatingSystemVersion API_AVAILABLE(ios(11.0), watchos(4.0));

/*!
 @method        initWithSource:version:productType:operatingSystemVersion:
 @abstract      Initializes a new HKSourceRevision with the given source, version, product type, and operating system
                version.
 */
- (instancetype)initWithSource:(HKSource *)source
                       version:(nullable NSString *)version
                   productType:(nullable NSString *)productType
        operatingSystemVersion:(NSOperatingSystemVersion)operatingSystemVersion API_AVAILABLE(ios(11.0), watchos(4.0));

/*!
 @method        initWithSource:version:
 @abstract      Initializes a new HKSourceRevision with the given source and version.
 */
- (instancetype)initWithSource:(HKSource *)source version:(nullable NSString *)version;

- (instancetype)init NS_UNAVAILABLE;

@end

// Constants to match on any value of that property when querying for samples from an HKSourceRevision
HK_EXTERN NSString * const HKSourceRevisionAnyVersion API_AVAILABLE(ios(11.0), watchos(4.0));
HK_EXTERN NSString * const HKSourceRevisionAnyProductType API_AVAILABLE(ios(11.0), watchos(4.0));
HK_EXTERN NSOperatingSystemVersion const HKSourceRevisionAnyOperatingSystem API_AVAILABLE(ios(11.0), watchos(4.0));

NS_ASSUME_NONNULL_END
