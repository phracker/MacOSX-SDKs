//
//  HKLensSpecification.h
//  HealthKit
//
//  Copyright © 2022 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HealthKit/HKDefines.h>

@class HKQuantity;

NS_ASSUME_NONNULL_BEGIN

/*!
 @class         HKLensSpecification
 @abstract      An object subclass representing common lens specification
 */
HK_EXTERN
NS_SWIFT_SENDABLE
API_AVAILABLE(ios(16.0), watchos(9.0), macCatalyst(16.0), macos(13.0))
@interface HKLensSpecification : NSObject

/*!
 @property      sphere
 @abstract      The lens power to correct nearsightedness or farsightedness. (-) means nearsighted while (+) farsighted.
 */
@property (nonatomic, copy, readonly) HKQuantity *sphere;

/*!
 @property      cylinder
 @abstract      The lens power required to correct astigmatism. Can be positive or negative.
 */
@property (nonatomic, copy, readonly, nullable) HKQuantity *cylinder;

/*!
 @property      axis
 @abstract      The angle along which cylindrical power should be positioned to correct astigmatism
 */
@property (nonatomic, copy, readonly, nullable) HKQuantity *axis;

/*!
 @property      addPower
 @abstract      The power adjustment applied to a multifocal lens to correct presbyopia
 */
@property (nonatomic, copy, readonly, nullable) HKQuantity *addPower;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
