//
//  MLCBatchNormalizationLayer.h
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

/*! @class      MLCBatchNormalizationLayer
    @abstract   A batch normalizaion layer
 */
MLCOMPUTE_CLASS_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))
@interface MLCBatchNormalizationLayer : MLCLayer

/*! @property   featureChannelCount
    @abstract   The number of feature channels
 */
@property (readonly, nonatomic) NSUInteger featureChannelCount;

/*! @property   mean
    @abstract   The mean tensor
 */
@property (readonly, nonatomic, retain) MLCTensor *mean;

/*! @property   variance
    @abstract   The variance tensor
 */
@property (readonly, nonatomic, retain) MLCTensor *variance;

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

/*! @abstract   Create a batch normalization layer
    @param featureChannelCount The number of feature channels
    @param mean The mean tensor
    @param variance The variance tensor
    @param beta The beta tensor
    @param gamma The gamma tensor
    @param varianceEpsilon The  epslion value
    @return     A new batch normalization layer.
 */
+ (instancetype _Nullable)layerWithFeatureChannelCount:(NSUInteger)featureChannelCount
                                                  mean:(MLCTensor *)mean
                                              variance:(MLCTensor *)variance
                                                  beta:(MLCTensor * _Nullable)beta
                                                 gamma:(MLCTensor * _Nullable)gamma
                                       varianceEpsilon:(float)varianceEpsilon;

/*! @abstract   Create a batch normalization layer
    @param featureChannelCount The number of feature channels
    @param mean The mean tensor
    @param variance The variance tensor
    @param beta The beta tensor
    @param gamma The gamma tensor
    @param varianceEpsilon The  epslion value
    @param momentum The  momentum value for the running mean and variance computation
    @return A new batch normalization layer.
 */
+ (instancetype _Nullable)layerWithFeatureChannelCount:(NSUInteger)featureChannelCount
                                                  mean:(MLCTensor *)mean
                                              variance:(MLCTensor *)variance
                                                  beta:(MLCTensor * _Nullable)beta
                                                 gamma:(MLCTensor * _Nullable)gamma
                                       varianceEpsilon:(float)varianceEpsilon
                                              momentum:(float)momentum;

@end

NS_ASSUME_NONNULL_END
