//
//  HKGlassesLensSpecification.h
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
 @class         HKGlassesLensSpecification
 @abstract      An object subclass representing lens specification for glasses
 */
HK_EXTERN
NS_SWIFT_SENDABLE
API_AVAILABLE(ios(16.0), watchos(9.0), macCatalyst(16.0), macos(13.0))
@interface HKGlassesLensSpecification : HKLensSpecification <NSSecureCoding, NSCopying>

/*!
 @property      vertexDistance
 @abstract      The distance between the back of the eyeglass lens and the eye (measured in mm)
 */
@property (nonatomic, copy, readonly, nullable) HKQuantity *vertexDistance;

/*!
 @property      prism
 @abstract      The object encapsulating the prism fields
 */
@property (nonatomic, copy, readonly, nullable) HKVisionPrism *prism;

/*!
 @property      farPupillaryDistance
 @abstract      The distance from each pupil to the center of the nose (measured in mm) when looking at a far target.
                Can be described as combined or individual value. For distance prescriptions, the pupillary distance will be a far value.
 */
@property (nonatomic, copy, readonly, nullable) HKQuantity *farPupillaryDistance;

/*!
 @property      nearPupillaryDistance
 @abstract      The distance from each pupil to the center of the nose (measured in mm) when looking at a near target.
                Can be described as combined or individual value. For near prescriptions, the pupillary distance will be a near value.
 */
@property (nonatomic, copy, readonly, nullable) HKQuantity *nearPupillaryDistance;


/*!
 @method        initWithSphere:cylinder:axis:addPower:vertexDistance:prism:farPupillaryDistance:nearPupillaryDistance

 @param         sphere                  The lens power to correct nearsightedness or farsightedness
 @param         cylinder                The lens power required to correct astigmatism
 @param         axis                    The angle along which cylindrical power should be positioned to correct astigmatism
 @param         addPower                The power adjustment applied to a multifocal lens to correct presbyopia
 @param         vertexDistance          The distance between the back of the eyeglass lens and the eye
 @param         prism                   The object encapsulating the prism fields
 @param         farPupillaryDistance    The distance from each pupil to the center of the nose (measured in mm) when looking at a far target.
                                        Can be described as combined or individual value. For distance prescriptions, the pupillary distance will be a far value.
 @param         nearPupillaryDistance   The distance from each pupil to the center of the nose (measured in mm) when looking at a near target.
                                        Can be described as combined or individual value. For near prescriptions, the pupillary distance will be a near value.
 */
- (instancetype)initWithSphere:(HKQuantity *)sphere
                      cylinder:(nullable HKQuantity *)cylinder
                          axis:(nullable HKQuantity *)axis
                      addPower:(nullable HKQuantity *)addPower
                vertexDistance:(nullable HKQuantity *)vertexDistance
                         prism:(nullable HKVisionPrism *)prism
          farPupillaryDistance:(nullable HKQuantity *)farPupillaryDistance
         nearPupillaryDistance:(nullable HKQuantity *)nearPupillaryDistance;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
