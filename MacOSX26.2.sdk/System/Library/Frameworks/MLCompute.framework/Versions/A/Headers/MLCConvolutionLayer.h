//
//  MLCConvolutionLayer.h
//  MLCompute
//
//  Copyright © 2019 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <MLCompute/MLCDefines.h>
#import <MLCompute/MLCTypes.h>
#import <MLCompute/MLCLayer.h>

@class MLCDevice;
@class MLCConvolutionDescriptor;
@class MLCTensor;
@class MLCTensorParameter;

NS_ASSUME_NONNULL_BEGIN

/*! @class      MLCConvolutionLayer
    @abstract   A convolution layer
 */
MLCOMPUTE_AVAILABLE_STARTING_BUT_DEPRECATED_MACOS14(11.0, 14.0, 14.0)
@interface MLCConvolutionLayer : MLCLayer

/*! @property   descriptor
    @abstract   The convolution descriptor
 */
@property (readonly, nonatomic, copy) MLCConvolutionDescriptor *descriptor;

/*! @property   weights
    @abstract   The weights tensor used by the convolution layer
 */
@property (readonly, nonatomic, retain) MLCTensor *weights;

/*! @property   biases
    @abstract   The bias tensor used by the convolution layer
 */
@property (readonly, nonatomic, nullable, retain) MLCTensor *biases;

/*! @property   weightsParameter
    @abstract   The weights tensor parameter used for optimizer update
 */
@property (readonly, nonatomic, retain) MLCTensorParameter *weightsParameter;

/*! @property   biasesParameter
    @abstract   The bias tensor parameter used for optimizer update
 */
@property (readonly, nonatomic, nullable, retain) MLCTensorParameter *biasesParameter;


/*! @abstract   Create a convolution layer
    @param      weights        The weights tensor
    @param      biases         The bias tensor
    @param      descriptor     The convolution descriptor
    @return     A new convolution layer.
 */
+ (instancetype _Nullable)layerWithWeights:(MLCTensor *)weights
                                    biases:(MLCTensor * _Nullable)biases
                                descriptor:(MLCConvolutionDescriptor *)descriptor;

@end

NS_ASSUME_NONNULL_END
