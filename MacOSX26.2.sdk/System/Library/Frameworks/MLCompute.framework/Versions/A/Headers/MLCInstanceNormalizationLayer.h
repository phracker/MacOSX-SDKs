//
//  MLCInstanceNormalizationLayer.h
//  MLCompute
//
//  Copyright © 2019 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <MLCompute/MLCDefines.h>
#import <MLCompute/MLCTypes.h>
#import <MLCompute/MLCLayer.h>

@class MLCDevice;
@class MLCTensor;
@class MLCTensorParameter;
@class MLCActivationLayer;

NS_ASSUME_NONNULL_BEGIN

/*! @class      MLCInstanceNormalizationLayer
    @abstract   An instance normalization layer.  For more information refer to https://pytorch.org/docs/stable/nn.html#instancenorm2d
 */
MLCOMPUTE_AVAILABLE_STARTING_BUT_DEPRECATED_MACOS14(11.0, 14.0, 14.0)
@interface MLCInstanceNormalizationLayer : MLCLayer

/*! @property   featureChannelCount
    @abstract   The number of feature channels
 */
@property (readonly, nonatomic) NSUInteger featureChannelCount;

/*! @property   mean
    @abstract   The running mean tensor
 */
@property (readonly, nonatomic, nullable, retain) MLCTensor *mean
    MLCOMPUTE_AVAILABLE_STARTING(macos(11.3), ios(14.5), tvos(14.5));

/*! @property   variance
    @abstract   The running variance tensor
 */
@property (readonly, nonatomic, nullable, retain) MLCTensor *variance
    MLCOMPUTE_AVAILABLE_STARTING(macos(11.3), ios(14.5), tvos(14.5));

/*! @property   beta
    @abstract   The beta tensor
 */
@property (readonly, nonatomic, nullable, retain) MLCTensor *beta;

/*! @property   gamma
    @abstract   The gamma tensor
 */
@property (readonly, nonatomic, nullable, retain) MLCTensor *gamma;

/*! @property   betaParameter
    @abstract   The beta tensor parameter used for optimizer update
 */
@property (readonly, nonatomic, nullable, retain) MLCTensorParameter *betaParameter;

/*! @property   gammaParameter
    @abstract   The gamma tensor parameter used for optimizer update
 */
@property (readonly, nonatomic, nullable, retain) MLCTensorParameter *gammaParameter;

/*! @property   varianceEpsilon
    @abstract   A value used for numerical stability
 */
@property (readonly, nonatomic) float varianceEpsilon;

/*! @property   momentum
    @abstract   The value used for the running mean and variance computation
    @discussion The default is 0.99f.
 */
@property (readonly, nonatomic) float momentum;

/*! @abstract   Create an instance normalization layer
    @param featureChannelCount The number of feature channels
    @param beta The beta tensor
    @param gamma The gamma tensor
    @param varianceEpsilon The  epslion value
    @return A new instance normalization layer.
 */
+ (instancetype _Nullable)layerWithFeatureChannelCount:(NSUInteger)featureChannelCount
                                                  beta:(MLCTensor * _Nullable)beta
                                                 gamma:(MLCTensor * _Nullable)gamma
                                       varianceEpsilon:(float)varianceEpsilon;

/*! @abstract   Create an instance normalization layer
    @param featureChannelCount The number of feature channels
    @param beta The beta tensor
    @param gamma The gamma tensor
    @param varianceEpsilon The  epslion value
    @param momentum The  momentum value for the running mean and variance computation
    @return A new instance normalization layer.
 */
+ (instancetype _Nullable)layerWithFeatureChannelCount:(NSUInteger)featureChannelCount
                                                  beta:(MLCTensor * _Nullable)beta
                                                 gamma:(MLCTensor * _Nullable)gamma
                                       varianceEpsilon:(float)varianceEpsilon
                                              momentum:(float)momentum;

/*! @abstract   Create an instance normalization layer
    @param featureChannelCount The number of feature channels
    @param mean The running mean tensor
    @param variance The running variance tensor
    @param beta The beta tensor
    @param gamma The gamma tensor
    @param varianceEpsilon The  epslion value
    @param momentum The  momentum value for the running mean and variance computation
    @return A new instance normalization layer.
 */
+ (instancetype _Nullable)layerWithFeatureChannelCount:(NSUInteger)featureChannelCount
                                                  mean:(MLCTensor *)mean
                                              variance:(MLCTensor *)variance
                                                  beta:(MLCTensor * _Nullable)beta
                                                 gamma:(MLCTensor * _Nullable)gamma
                                       varianceEpsilon:(float)varianceEpsilon
                                              momentum:(float)momentum
    MLCOMPUTE_AVAILABLE_STARTING(macos(11.3), ios(14.5), tvos(14.5));

@end

NS_ASSUME_NONNULL_END
