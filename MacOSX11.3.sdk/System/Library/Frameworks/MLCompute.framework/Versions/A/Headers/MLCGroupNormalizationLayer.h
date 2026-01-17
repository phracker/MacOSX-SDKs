//
//  MLCGroupNormalizationLayer.h
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

NS_ASSUME_NONNULL_BEGIN

/*! @class      MLCGroupNormalizationLayer
    @abstract   A group normalizaion layer.  For more information, refer to https://pytorch.org/docs/stable/nn.html#groupnorm
 */
MLCOMPUTE_CLASS_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))
@interface MLCGroupNormalizationLayer : MLCLayer

/*! @property   featureChannelCount
    @abstract   The number of feature channels
 */
@property (readonly, nonatomic) NSUInteger featureChannelCount;

/*! @property   groupCount
    @abstract   The number of groups to separate the channels into
 */
@property (readonly, nonatomic) NSUInteger groupCount;

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

/*! @abstract Create a group normalization layer
    @param featureChannelCount  The number of feature channels
    @param beta  Training parameter
    @param gamma  Training parameter
    @param groupCount  The number of groups to divide the feature channels into
    @param varianceEpsilon  A small numerical value added to variance for stability
    @return A new group normalization layer.
 */
+ (instancetype _Nullable)layerWithFeatureChannelCount:(NSUInteger)featureChannelCount
                                            groupCount:(NSUInteger)groupCount
                                                  beta:(MLCTensor * _Nullable)beta
                                                 gamma:(MLCTensor * _Nullable)gamma
                                       varianceEpsilon:(float)varianceEpsilon;

@end

NS_ASSUME_NONNULL_END
