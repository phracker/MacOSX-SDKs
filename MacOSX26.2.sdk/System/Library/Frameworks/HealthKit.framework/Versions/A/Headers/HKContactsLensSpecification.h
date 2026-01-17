//
//  HKContactsLensSpecification.h
//  HealthKit
//
//  Copyright © 2022 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HealthKit/HKDefines.h>
#import <HealthKit/HKLensSpecification.h>

@class HKQuantity;
@class HKVisionPrism;

NS_ASSUME_NONNULL_BEGIN
/*!
 @class         HKContactsLensSpecification
 @abstract      An object subclass representing lens specification for contacts
 */
HK_EXTERN
NS_SWIFT_SENDABLE
API_AVAILABLE(ios(16.0), watchos(9.0), macCatalyst(16.0), macos(13.0))
@interface HKContactsLensSpecification : HKLensSpecification <NSSecureCoding, NSCopying>

/*!
 @property      baseCurve
 @abstract      The curvature of the back surface of the lens (measured in mm)
 */
@property (nonatomic, copy, readonly, nullable) HKQuantity *baseCurve;

/*!
 @property      diameter
 @abstract      The width of the lens from edge to edge (measured in mm)
 */
@property (nonatomic, copy, readonly, nullable) HKQuantity *diameter;

/*!
 @method        initWithSphere:cylinder:axis:addPower:baseCurve:diameter

 @param         sphere     The lens power to correct nearsightedness or farsightedness
 @param         cylinder   The lens power required to correct astigmatism
 @param         axis       The angle along which cylindrical power should be positioned to correct astigmatism
 @param         addPower   The power adjustment applied to a multifocal lens to correct presbyopia
 @param         baseCurve  The curvature of the back surface of the lens
 @param         diameter   The width of the lens from edge to edge
 */
- (instancetype)initWithSphere:(HKQuantity *)sphere
                      cylinder:(nullable HKQuantity *)cylinder
                          axis:(nullable HKQuantity *)axis
                      addPower:(nullable HKQuantity *)addPower
                     baseCurve:(nullable HKQuantity *)baseCurve
                      diameter:(nullable HKQuantity *)diameter;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
