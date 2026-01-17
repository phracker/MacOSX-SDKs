//
//  SRDeviceUsageCategories.h
//  SensorKit
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SensorKit/SRDefines.h>

NS_ASSUME_NONNULL_BEGIN

typedef NSString *SRDeviceUsageCategoryKey NS_TYPED_ENUM;

SR_EXTERN SRDeviceUsageCategoryKey const SRDeviceUsageCategoryGames API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, visionos) API_UNAVAILABLE(tvos, macos);
SR_EXTERN SRDeviceUsageCategoryKey const SRDeviceUsageCategoryBusiness API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, visionos) API_UNAVAILABLE(tvos, macos);
SR_EXTERN SRDeviceUsageCategoryKey const SRDeviceUsageCategoryWeather API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, visionos) API_UNAVAILABLE(tvos, macos);
SR_EXTERN SRDeviceUsageCategoryKey const SRDeviceUsageCategoryUtilities API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, visionos) API_UNAVAILABLE(tvos, macos);
SR_EXTERN SRDeviceUsageCategoryKey const SRDeviceUsageCategoryTravel API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, visionos) API_UNAVAILABLE(tvos, macos);
SR_EXTERN SRDeviceUsageCategoryKey const SRDeviceUsageCategorySports API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, visionos) API_UNAVAILABLE(tvos, macos);
SR_EXTERN SRDeviceUsageCategoryKey const SRDeviceUsageCategorySocialNetworking API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, visionos) API_UNAVAILABLE(tvos, macos);
SR_EXTERN SRDeviceUsageCategoryKey const SRDeviceUsageCategoryReference API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, visionos) API_UNAVAILABLE(tvos, macos);
SR_EXTERN SRDeviceUsageCategoryKey const SRDeviceUsageCategoryProductivity API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, visionos) API_UNAVAILABLE(tvos, macos);
SR_EXTERN SRDeviceUsageCategoryKey const SRDeviceUsageCategoryPhotoAndVideo API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, visionos) API_UNAVAILABLE(tvos, macos);
SR_EXTERN SRDeviceUsageCategoryKey const SRDeviceUsageCategoryNews API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, visionos) API_UNAVAILABLE(tvos, macos);
SR_EXTERN SRDeviceUsageCategoryKey const SRDeviceUsageCategoryNavigation API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, visionos) API_UNAVAILABLE(tvos, macos);
SR_EXTERN SRDeviceUsageCategoryKey const SRDeviceUsageCategoryMusic API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, visionos) API_UNAVAILABLE(tvos, macos);
SR_EXTERN SRDeviceUsageCategoryKey const SRDeviceUsageCategoryLifestyle API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, visionos) API_UNAVAILABLE(tvos, macos);
SR_EXTERN SRDeviceUsageCategoryKey const SRDeviceUsageCategoryHealthAndFitness API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, visionos) API_UNAVAILABLE(tvos, macos);
SR_EXTERN SRDeviceUsageCategoryKey const SRDeviceUsageCategoryFinance API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, visionos) API_UNAVAILABLE(tvos, macos);
SR_EXTERN SRDeviceUsageCategoryKey const SRDeviceUsageCategoryEntertainment API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, visionos) API_UNAVAILABLE(tvos, macos);
SR_EXTERN SRDeviceUsageCategoryKey const SRDeviceUsageCategoryEducation API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, visionos) API_UNAVAILABLE(tvos, macos);
SR_EXTERN SRDeviceUsageCategoryKey const SRDeviceUsageCategoryBooks API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, visionos) API_UNAVAILABLE(tvos, macos);
SR_EXTERN SRDeviceUsageCategoryKey const SRDeviceUsageCategoryMedical API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, visionos) API_UNAVAILABLE(tvos, macos);
SR_EXTERN SRDeviceUsageCategoryKey const SRDeviceUsageCategoryNewsstand API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, visionos) API_UNAVAILABLE(tvos, macos);
SR_EXTERN SRDeviceUsageCategoryKey const SRDeviceUsageCategoryCatalogs API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, visionos) API_UNAVAILABLE(tvos, macos);
SR_EXTERN SRDeviceUsageCategoryKey const SRDeviceUsageCategoryKids API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, visionos) API_UNAVAILABLE(tvos, macos);
SR_EXTERN SRDeviceUsageCategoryKey const SRDeviceUsageCategoryMiscellaneous API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, visionos) API_UNAVAILABLE(tvos, macos);
SR_EXTERN SRDeviceUsageCategoryKey const SRDeviceUsageCategoryFoodAndDrink API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, visionos) API_UNAVAILABLE(tvos, macos);
SR_EXTERN SRDeviceUsageCategoryKey const SRDeviceUsageCategoryDeveloperTools API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, visionos) API_UNAVAILABLE(tvos, macos);
SR_EXTERN SRDeviceUsageCategoryKey const SRDeviceUsageCategoryGraphicsAndDesign API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, visionos) API_UNAVAILABLE(tvos, macos);
SR_EXTERN SRDeviceUsageCategoryKey const SRDeviceUsageCategoryShopping API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, visionos) API_UNAVAILABLE(tvos, macos);
SR_EXTERN SRDeviceUsageCategoryKey const SRDeviceUsageCategoryStickers API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, visionos) API_UNAVAILABLE(tvos, macos);

NS_SWIFT_SENDABLE // Immutable with no mutable subclasses
SR_EXTERN API_AVAILABLE(ios(16.4)) API_UNAVAILABLE(watchos) API_UNAVAILABLE(tvos, macos)
/*!
 * @class SRSupplementalCategory
 *
 * @brief
 * A supplemental category to provide more context than just the app category
 *
 * @discussion
 * The app categories from \c SRDeviceUsageCategoryKey are very general.
 * Providing a supplemental category allows more context about the specific app while
 * not revealing the exact app identity.
 */
@interface SRSupplementalCategory : NSObject <NSCopying, NSSecureCoding>

/*!
 * @property identifier
 * @brief An opaque identifier for the supplemental category
 * @discussion More information about what this category represents can be found in Apple's developer documentation
 */
@property (nonatomic, readonly, copy) NSString *identifier;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
