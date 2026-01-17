//
//  PHASEDirectivityModel.h
//  PHASE
//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#ifndef PHASEDirectivityModel_h
#define PHASEDirectivityModel_h

#import <PHASE/PHASETypes.h>

NS_ASSUME_NONNULL_BEGIN

#pragma mark - PHASECardioidDirectivityModelSubbandParameters

/****************************************************************************************************/
/*!
    @interface PHASECardioidDirectivityModelSubbandParameters
    @abstract Cardioid directivity model subband parameters.
 */
OS_EXPORT API_AVAILABLE(macos(12.0), ios(15.0), tvos(17.0)) API_UNAVAILABLE(watchos)
@interface PHASECardioidDirectivityModelSubbandParameters : NSObject

- (instancetype)init;

/*!
    @property frequency
    @abstract The frequency of the subband, in hertz.
    @note
        Values are clamped to the range [20.0, 20000.0]. Default value is 1000.0.
*/
@property(nonatomic) double frequency;

/*!
    @property pattern
    @abstract The directivity pattern.
    @note
        Values are clamped to the range [0.0, 1.0]. Default value is 0.0. 0.0 is omnidirectional. 0.5 is cardioid. 1.0 is dipole.
*/
@property(nonatomic) double pattern;

/*!
    @property sharpness
    @abstract The sharpness of the directivity pattern.
    @note
        Values are clamped to the range [1.0, DBL_MAX]. Default value is 1.0. Values > 1.0 increase sharpness.
*/
@property(nonatomic) double sharpness;

@end

#pragma mark - PHASEConeDirectivityModelSubbandParameters

/****************************************************************************************************/
/*!
    @interface PHASEConeDirectivityModelSubbandParameters
    @abstract Cone directivity model subband parameters.
 */
OS_EXPORT API_AVAILABLE(macos(12.0), ios(15.0), tvos(17.0)) API_UNAVAILABLE(watchos)
@interface PHASEConeDirectivityModelSubbandParameters : NSObject

- (instancetype)init;

/*!
    @method setInnerAngle:outerAngle
    @abstract Set the innerAngle and outerAngle of the Cone Directivity Model Subband
    @param innerAngle
        The inner angle of the cone directivity model, must be less than or equal to outer angle.
    @param outerAngle
        The outer angle of the cone directivity model, must be greater than or equal to inner angle.
    @note The default value for each angle is 360.0. outerAngle must be >= innerAngle.
*/
- (void)setInnerAngle:(double)innerAngle outerAngle:(double)outerAngle
NS_SWIFT_NAME(setAngles(innerAngle:outerAngle:));

/*!
    @property frequency
    @abstract The frequency of the subband, in hertz.
    @note
        Default value is 1000.0.
*/
@property(nonatomic) double frequency;

/*!
    @property innerAngle
    @abstract The inner angle, in degrees.
    @note
        Default value is 360.0.
*/
@property(readonly) double innerAngle;

/*!
    @property outerAngle
    @abstract The outer angle, in degrees.
    @note
        Default value is 360.0.
*/
@property(readonly) double outerAngle;

/*!
    @property outerGain
    @abstract The outer gain.
    @note
        Values are clamped to the range [0.0, 1.0]. Default value is 1.0.
*/
@property(nonatomic) double outerGain;

@end

#pragma mark - PHASEDirectivityModelParameters

/****************************************************************************************************/
/*!
    @interface PHASEDirectivityModelParameters
    @abstract Directivity model parameters.
*/
OS_EXPORT API_AVAILABLE(macos(12.0), ios(15.0), tvos(17.0)) API_UNAVAILABLE(watchos)
@interface PHASEDirectivityModelParameters : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

#pragma mark - PHASECardioidDirectivityModelParameters

/****************************************************************************************************/
/*!
    @interface PHASECardioidDirectivityModelParameters
    @abstract Cardioid directivity model parameters.
*/
OS_EXPORT API_AVAILABLE(macos(12.0), ios(15.0), tvos(17.0)) API_UNAVAILABLE(watchos)
@interface PHASECardioidDirectivityModelParameters : PHASEDirectivityModelParameters

- (instancetype)initWithSubbandParameters: (NSArray<PHASECardioidDirectivityModelSubbandParameters*>*) subbandParameters;

/*!
    @property subbandParameters
    @abstract An array of subband parameters.
*/
@property(nonatomic, strong, readonly) NSArray<PHASECardioidDirectivityModelSubbandParameters*>* subbandParameters;

@end

#pragma mark - PHASEConeDirectivityModelParameters

/****************************************************************************************************/
/*!
    @interface PHASEConeDirectivityModelParameters
    @abstract Cone directivity model parameters.
*/
OS_EXPORT API_AVAILABLE(macos(12.0), ios(15.0), tvos(17.0)) API_UNAVAILABLE(watchos)
@interface PHASEConeDirectivityModelParameters : PHASEDirectivityModelParameters

- (instancetype)initWithSubbandParameters: (NSArray<PHASEConeDirectivityModelSubbandParameters*>*) subbandParameters;

/*!
    @property subbandParameters
    @abstract An array of subband parameters.
*/
@property(nonatomic, strong, readonly) NSArray<PHASEConeDirectivityModelSubbandParameters*>* subbandParameters;

@end

NS_ASSUME_NONNULL_END

#endif /* PHASEDirectivityModel_h */
