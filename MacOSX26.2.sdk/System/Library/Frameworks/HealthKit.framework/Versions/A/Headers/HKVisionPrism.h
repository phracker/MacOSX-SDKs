//
//  HKVisionPrism.h
//  HealthKit
//
//  Copyright © 2022 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HealthKit/HKDefines.h>

@class HKQuantity;

NS_ASSUME_NONNULL_BEGIN

/*!
 @enum          HKPrismBase
 @abstract      Represents the prism base for rectangular coordinates
 */
typedef NS_ENUM(NSInteger, HKPrismBase) {
    HKPrismBaseNone = 0,
    HKPrismBaseUp,
    HKPrismBaseDown,
    HKPrismBaseIn,
    HKPrismBaseOut,
} API_AVAILABLE(ios(16.0), watchos(9.0), macCatalyst(16.0), macos(13.0));

/*!
 @enum          HKVisionEye
 @abstract      Represents an eye
 */
typedef NS_ENUM(NSInteger, HKVisionEye) {
    HKVisionEyeLeft = 1,
    HKVisionEyeRight,
} API_AVAILABLE(ios(16.0), watchos(9.0), macCatalyst(16.0), macos(13.0));

/*!
 @class         HKVisionPrism
 @abstract      An object subclass representing prism vision fields used in eye glasses to correct double vision.
                The prism aligns the two images so only one is seen.
 */
HK_EXTERN
NS_SWIFT_SENDABLE
API_AVAILABLE(ios(16.0), watchos(9.0), macCatalyst(16.0), macos(13.0))
@interface HKVisionPrism : NSObject <NSSecureCoding, NSCopying>

/*!
 @property      amount
 @abstract      The compensation in prism diopters to correct eye misalignment [polar coordinates]
 */
@property (nonatomic, copy, readonly) HKQuantity *amount;

/*!
 @property      angle
 @abstract      The direction of the prism base [polar coordinates]
 */
@property (nonatomic, copy, readonly) HKQuantity *angle;

/*!
 @property      verticalAmount
 @abstract      The vertical component of compensation in prism diopters [rectangular coordinates]
 */
@property (nonatomic, copy, readonly) HKQuantity *verticalAmount;

/*!
 @property      horizontalAmount
 @abstract      The horizontal component of compensation in prism diopters [rectangular coordinates]
 */
@property (nonatomic, copy, readonly) HKQuantity *horizontalAmount;

/*!
 @property      verticalBase
 @abstract      The direction of the prism base relative to the vertical axis of the lens;
                base up or base down. [rectangular coordinates]
 */
@property (nonatomic, readonly) HKPrismBase verticalBase;

/*!
 @property      horizontalBase
 @abstract      The direction of the prism base relative to the horizontal axis of the lens;
                base in (toward the nose) or base out (away from the nose). [rectangular coordinates]
 */
@property (nonatomic, readonly) HKPrismBase horizontalBase;

/*!
 @property      eye
 @abstract      Which eye (left or right)
 */
@property (nonatomic, assign, readonly) HKVisionEye eye;

/*!
 @method        initWithAmount:angle:eye

 @param         amount    The compensation for amount eye misalignment
 @param         angle     The angle of the lens required to correct diplopia
 @param         eye       The eye associated with the prism values
 */
- (instancetype)initWithAmount:(HKQuantity *)amount
                         angle:(HKQuantity *)angle
                           eye:(HKVisionEye)eye;

/*!
 @method        initWithVerticalAmount:verticalBase:horizontalAmount:horizontalBase:eye

 @param         verticalAmount      The vertical component of compensation in prism diopters
 @param         verticalBase        The direction of the prism base relative to the vertical axis of the lens;
                                    base up or base down.
 @param         horizontalAmount    The horizontal component of compensation in prism diopters
 @param         horizontalBase      The direction of the prism base relative to the horizontal axis of the lens;
                                    base in (toward the nose) or base out (away from the nose).
 @param         eye                 The eye associated with the prism values
 */
- (instancetype)initWithVerticalAmount:(HKQuantity *)verticalAmount
                          verticalBase:(HKPrismBase)verticalBase
                      horizontalAmount:(HKQuantity *)horizontalAmount
                        horizontalBase:(HKPrismBase)horizontalBase
                                   eye:(HKVisionEye)eye;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
