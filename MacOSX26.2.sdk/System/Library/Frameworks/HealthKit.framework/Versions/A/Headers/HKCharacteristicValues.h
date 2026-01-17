//
//  HKCharacteristicValues.h
//  HealthKit
//
//  Copyright © 2022-2023 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @enum          HKActivityMoveMode
 @abstract      This enumerated type is used to represent the activity mode for the user's move ring.

 @constant      HKActivityMoveModeActiveEnergy      User's move ring is updated from Active Energy Burned
 @constant      HKActivityMoveModeAppleMoveTime     User's move ring is updated from Apple Move Time
 */
typedef NS_ENUM(NSInteger, HKActivityMoveMode) {
    HKActivityMoveModeActiveEnergy = 1,
    HKActivityMoveModeAppleMoveTime = 2,
} API_AVAILABLE(ios(14.0), watchos(7.0), macCatalyst(14.0), macos(13.0));

/*!
 @enum          HKBiologicalSex
 @abstract      This enumerated type is used to represent the biological sex of an individual.
 */
typedef NS_ENUM(NSInteger, HKBiologicalSex) {
    HKBiologicalSexNotSet = 0,
    HKBiologicalSexFemale = 1,
    HKBiologicalSexMale = 2,
    HKBiologicalSexOther API_AVAILABLE(ios(8.2), watchos(2.0), macCatalyst(13.0), macos(13.0)) = 3,
} API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0));

/*!
 @enum          HKBloodType
 @abstract      This enumerated type is used to represent the blood type of an individual.
 */
typedef NS_ENUM(NSInteger, HKBloodType) {
    HKBloodTypeNotSet = 0,
    HKBloodTypeAPositive = 1,
    HKBloodTypeANegative = 2,
    HKBloodTypeBPositive = 3,
    HKBloodTypeBNegative = 4,
    HKBloodTypeABPositive = 5,
    HKBloodTypeABNegative = 6,
    HKBloodTypeOPositive = 7,
    HKBloodTypeONegative = 8,
} API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0));

/*!
 @enum          HKFitzpatrickSkinType
 @abstract      This enumerated type is used to represent the skin type of an individual based on the Fitzpatrick scale.
 @discussion    The Fitzpatrick scale is a numerical classification for skin color based on the skin's response to sun
                exposure in terms of the degree of burning and tanning.

 @constant      HKFitzpatrickSkinTypeI      Pale white skin that always burns easily in the sun and never tans.
 @constant      HKFitzpatrickSkinTypeII     White skin that burns easily and tans minimally.
 @constant      HKFitzpatrickSkinTypeIII    White to light brown skin that burns moderately and tans uniformly.
 @constant      HKFitzpatrickSkinTypeIV     Beige-olive, lightly tanned skin that burns minimally and tans moderately.
 @constant      HKFitzpatrickSkinTypeV      Brown skin that rarely burns and tans profusely.
 @constant      HKFitzpatrickSkinTypeVI     Dark brown to black skin that never burns and tans profusely.
 */
typedef NS_ENUM(NSInteger, HKFitzpatrickSkinType) {
    HKFitzpatrickSkinTypeNotSet = 0,
    HKFitzpatrickSkinTypeI = 1,
    HKFitzpatrickSkinTypeII = 2,
    HKFitzpatrickSkinTypeIII = 3,
    HKFitzpatrickSkinTypeIV = 4,
    HKFitzpatrickSkinTypeV = 5,
    HKFitzpatrickSkinTypeVI = 6,
} API_AVAILABLE(ios(9.0), watchos(2.0), macCatalyst(13.0), macos(13.0));

/*!
 @enum          HKWheelchairUse
 @abstract      This enumerated type is used to represent whether the user uses a wheelchair.

 @constant      HKWheelchairUseNo   The user does not use a wheelchair.
 @constant      HKWheelchairUseYes  The user does use a wheelchair.
 */
typedef NS_ENUM(NSInteger, HKWheelchairUse) {
    HKWheelchairUseNotSet = 0,
    HKWheelchairUseNo = 1,
    HKWheelchairUseYes = 2,
} API_AVAILABLE(ios(10.0), watchos(3.0), macCatalyst(13.0), macos(13.0));

NS_ASSUME_NONNULL_END
