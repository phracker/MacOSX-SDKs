//
//  MLCLayerNormalizationLayer.h
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

/*! @class      MLCLayerNormalizationLayer
    @abstract   The layer normalizaion layer.  For more information, refer to https://pytorch.org/docs/stable/nn.html#layernorm.
 */
MLCOMPUTE_CLASS_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))
@interface MLCLayerNormalizationLayer : MLCLayer

/*! @property   normalizedShape
    @abstract   The shape of the axes over which normalization occurs, (W), (H,W) or (C,H,W) 
 */
@property (readonly, nonatomic, copy) NSArray<NSNumber *> *normalizedShape NS_REFINED_FOR_SWIFT;

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

/*! @abstract Create a layer normalization layer
    @param normalizedShape The shape of the axes over which normalization occurs, currently (C,H,W) only
    @param beta Training parameter
    @param gamma Training parameter
    @param varianceEpsilon  A small numerical value added to variance for stability
    @return A new layer normalization layer.
 */
+ (instancetype _Nullable)layerWithNormalizedShape:(NSArray<NSNumber *> *)normalizedShape
                                              beta:(MLCTensor * _Nullable)beta
                                             gamma:(MLCTensor * _Nullable)gamma
                                   varianceEpsilon:(float)varianceEpsilon
    NS_REFINED_FOR_SWIFT;

@end

NS_ASSUME_NONNULL_END
