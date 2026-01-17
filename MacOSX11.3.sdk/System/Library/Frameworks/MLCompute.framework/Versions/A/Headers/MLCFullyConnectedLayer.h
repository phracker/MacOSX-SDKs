//
//  MLCFullyConnectedLayer.h
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

/*! @class      MLCFullyConnectedLayer
    @abstract   A fully connected layer a.k.a a dense layer
    @discussion For C:input feature channel, C':output feature channel, the layer maps (*,C) --> (*,C') where * can be 1, 2 or 3 dimesnion.
                There is an exception for the case of (N,C,1,1) which gets mapped to (N,C',1,1).
 */
MLCOMPUTE_CLASS_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))
@interface MLCFullyConnectedLayer : MLCLayer

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
@property (readonly, nonatomic, retain, nullable) MLCTensor *biases;

/*! @property   weightsParameter
    @abstract   The weights tensor parameter used for optimizer update
 */
@property (readonly, nonatomic, retain) MLCTensorParameter *weightsParameter;

/*! @property   biasesParameter
    @abstract   The bias tensor parameter used for optimizer update
 */
@property (readonly, nonatomic, nullable, retain) MLCTensorParameter *biasesParameter;


/*! @abstract   Create a fully connected layer
    @param      weights        The weights tensor
    @param      biases         The bias tensor
    @param      descriptor     The convolution descriptor
    @return     A new fully connected layer
 */
+ (instancetype _Nullable)layerWithWeights:(MLCTensor *)weights
                                    biases:(MLCTensor * _Nullable)biases
                                descriptor:(MLCConvolutionDescriptor *)descriptor;

@end

NS_ASSUME_NONNULL_END
