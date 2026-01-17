//
//  HKAppleWalkingSteadinessClassification.h
//  HealthKit
//
//  Copyright © 2021-2022 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HealthKit/HKDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class HKQuantity;

/*!
 @enum          HKAppleWalkingSteadinessClassification
 @abstract      This enumerated type is used to represent the classification for the user's walking steadiness.
 @constant      HKAppleWalkingSteadinessClassificationOK         Walking steadiness is OK.
 @constant      HKAppleWalkingSteadinessClassificationLow        Walking steadiness is Low.
 @constant      HKAppleWalkingSteadinessClassificationVeryLow    Walking steadiness is Very Low.
 */
typedef NS_ENUM(NSInteger, HKAppleWalkingSteadinessClassification) {
    HKAppleWalkingSteadinessClassificationOK NS_SWIFT_NAME(ok) = 1,
    HKAppleWalkingSteadinessClassificationLow,
    HKAppleWalkingSteadinessClassificationVeryLow,
} API_AVAILABLE(ios(15.0), watchos(8.0), macCatalyst(15.0), macos(13.0));

/*!
 @abstract Determines the Apple Walking Steadiness classification for the provided Apple Walking Steadiness value.
 @param value Apple Walking Steadiness quantity with expected value between 0% and 100%.
 @param classificationOut A pointer to the classification determined for the provided value.
 @param errorOut A pointer to an error describing why an unknown classification was returned.
 @return YES if the classification was successful. NO otherwise, meaning the provided value could not be classified.
 */
HK_EXTERN BOOL HKAppleWalkingSteadinessClassificationForQuantity(HKQuantity *value, HKAppleWalkingSteadinessClassification *classificationOut, NSError **errorOut) API_AVAILABLE(ios(15.0), watchos(8.0), macCatalyst(15.0), macos(13.0)) NS_REFINED_FOR_SWIFT;

/*!
 @abstract Retrieves the minimum quantity in percent unit for an Apple Walking Steadiness classification.
 @param classification Apple Walking Steadiness classification for desired minimum value.
 */
HK_EXTERN HKQuantity * HKAppleWalkingSteadinessMinimumQuantityForClassification(HKAppleWalkingSteadinessClassification classification) API_AVAILABLE(ios(15.0), watchos(8.0), macCatalyst(15.0), macos(13.0)) NS_REFINED_FOR_SWIFT;

/*!
 @abstract Retrieves the maximum quantity in percent unit for an Apple Walking Steadiness classification.
 @param classification Apple Walking Steadiness classification for desired maximum value.
 */
HK_EXTERN HKQuantity * HKAppleWalkingSteadinessMaximumQuantityForClassification(HKAppleWalkingSteadinessClassification classification) API_AVAILABLE(ios(15.0), watchos(8.0), macCatalyst(15.0), macos(13.0)) NS_REFINED_FOR_SWIFT;

NS_ASSUME_NONNULL_END
