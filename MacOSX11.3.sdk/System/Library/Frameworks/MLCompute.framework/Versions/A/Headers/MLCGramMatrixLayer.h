//
//  MLCGramMatrixLayer.h
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

NS_ASSUME_NONNULL_BEGIN


/*! @class       MLCGramMatrixLayer
    @abstract    A gram matrix layer
    @discussion  The MLComputeGramMatrix  specifies a layer which computes the uncentered cross-correlation
                 values between the spatial planes of each feature channel of a tensor. If the input tensor batch is
                 x = x[b, y, x, c], where 'b' is batch index, 'y' and 'x' are the spatial coordinates and 'c' is the feature channel
                 index then this layer computes the values:

                       y = y[b, 1, f, c] = alpha * sum_{x,y} x[b,y,x,f] * x[b,y,x,c], where 'alpha' is a scaling factor.

                 This operation can be interpreted to be computing all combinations of fully connected layers
                 between the different spatial planes of the input tensor. The results are stored in the feature channel and
                 'x'-coordinate indices of the output batch.

                 The operation is performed independently for each tensor in a batch.
 */
MLCOMPUTE_CLASS_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))
@interface MLCGramMatrixLayer : MLCLayer

/*! @property   scale
    @abstract   The scale factor
 */
@property (readonly, nonatomic) float scale;

/*! @abstract   Create a GramMatrix layer
    @param      scale  The scaling factor for the output.
    @return     A new GramMatrix layer
 */
+ (instancetype)layerWithScale:(float)scale;

@end

NS_ASSUME_NONNULL_END


