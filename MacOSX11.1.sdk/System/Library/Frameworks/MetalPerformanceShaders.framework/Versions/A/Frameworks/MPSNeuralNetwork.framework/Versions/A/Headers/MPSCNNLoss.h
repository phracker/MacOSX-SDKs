//
//  MPSCNNLoss.h
//  MPS
//
//  Created on 10/6/17.
//  Copyright © 2017 Apple. All rights reserved.
//

#ifndef MPSCNNLoss_h
#define MPSCNNLoss_h

#import <MPSNeuralNetwork/MPSCNNKernel.h>
#import <MPSNeuralNetwork/MPSCNNTypes.h>
#import <MPSCore/MPSState.h>

#ifdef __cplusplus
extern "C" {
#endif

#pragma mark -
#pragma mark MPSCNNLossDataDescriptor
    
/*!
 *  @class      MPSCNNLossDataDescriptor
 *  @dependency This depends on Metal.framework.
 *  @discussion The MPSCNNLossDataDescriptor specifies a loss data descriptor.
 *              The same descriptor can be used to initialize both the
 *              labels and the optional weights data.
 */
MPS_CLASS_AVAILABLE_STARTING(macos(10.13.4), ios(11.3), macCatalyst(13.0), tvos(11.3))
@interface MPSCNNLossDataDescriptor : NSObject <NSCopying>

/*! @property   layout
 *  @abstract   Data layout of loss data. See MPSImage.h for more information.
 *  @discussion This parameter specifies the layout of loss data.
 */
@property (readonly, nonatomic) MPSDataLayout layout;

/*! @property   size
 *  @abstract   Size of loss data: (width, height, feature channels}.
 *  @discussion This parameter specifies the size of loss data.
 */
@property (readonly, nonatomic) MTLSize size;

/*! @property   bytesPerRow
 *  @abstract   Row bytes of loss data.
 *  @discussion This parameter specifies the row bytes of loss data.
 */
@property (readwrite, nonatomic) NSUInteger bytesPerRow;

/*! @property   bytesPerImage
 *  @abstract   Slice bytes of loss data.
 *  @discussion This parameter specifies the slice bytes of loss data.
 */
@property (readwrite, nonatomic) NSUInteger bytesPerImage;

/*
 * You must use the cnnLossDataDescriptorWithDataLayout interface instead.
 */
-(nonnull instancetype) init NS_UNAVAILABLE;

/*!
 *  @abstract   Make a descriptor loss data. The bytesPerRow and bytesPerImage
 *              are automatically calculated assuming a dense array. If it is
 *              not a dense array, adjust bytesPerRow and bytesPerImage to the
 *              right value by changing properties.
 *  @param      data                        The per-element loss data. The data must be in floating point format.
 *  @param      layout                      The data layout of loss data.
 *  @param      size                        The size of loss data.
 *  @return     A valid MPSCNNLossDataDescriptor object or nil, if failure.
 */
+(nullable MPSCNNLossDataDescriptor*) cnnLossDataDescriptorWithData: (NSData*__nonnull) data
                                                             layout: (MPSDataLayout) layout
                                                               size: (MTLSize) size;

@end /* MPSCNNLossDataDescriptor */

    
#pragma mark -
#pragma mark MPSCNNLossLabels

/*!
 *  @class      MPSCNNLossLabels
 *  @dependency This depends on Metal.framework.
 *  @discussion The MPSCNNLossLabels is used to hold the per-element weights buffer
 *              used by both MPSCNNLoss forward filter and MPSNNLossGradient backward filter.
 *              The MPSCNNLoss forward filter populates the MPSCNNLossLabels object
 *              and the MPSNNLossGradient backward filter consumes the state object.
 */
MPS_CLASS_AVAILABLE_STARTING(macos(10.13.4), ios(11.3), macCatalyst(13.0), tvos(11.3))
@interface MPSCNNLossLabels : MPSState

/*!
 *  Use one of the interfaces below instead.
 */
-(nonnull instancetype) init NS_UNAVAILABLE;

/*!
 *  @abstract   Set labels (aka targets, ground truth) for the MPSCNNLossLabels object. 
 *  @discussion The labels and weights data are copied into internal storage. The computed loss can either be a
 *                                      scalar value (in batch mode, a single value per image in a batch) or it
 *                                      can be one value per feature channel. Thus, the size of the loss image
 *                                      must either match the size of the input source image or be {1, 1, 1},
 *                                      which results in a scalar value. In this convinience initializer, the
 *                                      assumed size of the loss image is {1, 1, 1}.
 *  @param      device                  Device the state resources will be created on.
 *  @param      labelsDescriptor        Describes the labels data. This includes:
 *                                          - The per-element labels data. The data must be in floating point format.
 *                                          - Data layout of labels data. See MPSImage.h for more information.
 *                                          - Size of labels data: (width, height, feature channels}.
 *                                          - Optionally, row bytes of labels data.
 *                                          - Optionally, slice bytes of labels data.
 */
-(nonnull instancetype) initWithDevice: (nonnull id<MTLDevice>)device
                      labelsDescriptor: (MPSCNNLossDataDescriptor* _Nonnull) labelsDescriptor;

/*!
 *  @abstract   Set labels (aka targets, ground truth) and weights for the MPSCNNLossLabels object.
 *              Weights are optional.
 *  @discussion The labels and weights data are copied into internal storage.
 *  @param      device                  Device the state resources will be created on.
 *  @param      lossImageSize           The size of the resulting loss image: { width, height, featureChannels }.
 *                                      The computed loss can either be a scalar value (in batch mode, a single
 *                                      value per image in a batch) or it can be one value per feature channel.
 *                                      Thus, the size of the loss image must either match the size of the input
 *                                      source image or be {1, 1, 1}, which results in a scalar value.
 *  @param      labelsDescriptor        Describes the labels data. This includes:
 *                                          - The per-element labels data. The data must be in floating point format.
 *                                          - Data layout of labels data. See MPSImage.h for more information.
 *                                          - Size of labels data: (width, height, feature channels}.
 *                                          - Optionally, row bytes of labels data.
 *                                          - Optionally, slice bytes of labels data.
 *  @param      weightsDescriptor       Describes the weights data. This includes:
 *                                          - The per-element weights data. The data must be in floating point format.
 *                                          - Data layout of weights data. See MPSImage.h for more information.
 *                                          - Size of weights data: (width, height, feature channels}.
 *                                          - Optionally, row bytes of weights data.
 *                                          - Optionally, slice bytes of weights data.
 *                                      This parameter is optional. If you are using a single weight, please use the
 *                                      weight property of the MPSCNNLossDescriptor object.
 */
-(nonnull instancetype) initWithDevice: (nonnull id<MTLDevice>)device
                         lossImageSize: (MTLSize) lossImageSize
                      labelsDescriptor: (MPSCNNLossDataDescriptor* _Nonnull) labelsDescriptor
                     weightsDescriptor: (MPSCNNLossDataDescriptor* _Nullable) weightsDescriptor NS_DESIGNATED_INITIALIZER;


/*!
 *  @abstract   Set labels (aka targets, ground truth) and weights for the MPSCNNLossLabels object.
 *              Weights are optional.
 *  @discussion The labels and weights images are retained - it is the users responsibility to make sure that they contain
 *              the right data when the loss filter is run on the device.
 *  @param      device                  Device the state resources will be created on.
 *  @param      lossImageSize           The size of the resulting loss image: { width, height, featureChannels }.
 *                                      The computed loss can either be a scalar value (in batch mode, a single
 *                                      value per image in a batch) or it can be one value per feature channel.
 *                                      Thus, the size of the loss image must either match the size of the input
 *                                      source image or be {1, 1, 1}, which results in a scalar value.
 *  @param      labelsImage             Describes the labels data.
 *  @param      weightsImage            Describes the weights data.
 *                                      This parameter is optional. If you are using a single weight, please use the
 *                                      weight property of the MPSCNNLossDescriptor object.
 */
-(nonnull instancetype) initWithDevice: (nonnull id<MTLDevice>)device
                         lossImageSize: (MTLSize) lossImageSize
                           labelsImage: (MPSImage* _Nonnull) labelsImage
                          weightsImage: (MPSImage* _Nullable) weightsImage
MPS_AVAILABLE_STARTING(macos(10.15.0), ios(13.0), macCatalyst(13.0), tvos(13.0))
NS_DESIGNATED_INITIALIZER;

/*!
 *  @abstract   Loss image accessor method.
 *  @return     An autoreleased MPSImage object, containing the loss data.
 *              The loss data is populated in the -encode call, thus the contents
 *              are undefined until you -encode the filter.
 *
 *              In order to guarantee that the image is correctly synchronized for CPU side access,
 *              it is the application's responsibility to call the [gradientState synchronizeOnCommandBuffer:]
 *              method before accessing the data in the image.
 */
-(nonnull MPSImage*) lossImage;

/*!
 *  @abstract   Labels image accessor method.
 *  @return     An autoreleased MPSImage object, containing the labels data.
 *              The labels data is populated in the -initWithDevice call.
 *
 *              In order to guarantee that the image is correctly synchronized for CPU side access,
 *              it is the application's responsibility to call the [gradientState synchronizeOnCommandBuffer:]
 *              method before accessing the data in the image.
 */
-(nonnull MPSImage*) labelsImage;

/*!
 *  @abstract   Weights image accessor method.
 *  @return     An autoreleased MPSImage object, containing the weights data.
 *              The weights data is populated in the -initWithDevice call.
 *
 *              In order to guarantee that the image is correctly synchronized for CPU side access,
 *              it is the application's responsibility to call the [gradientState synchronizeOnCommandBuffer:]
 *              method before accessing the data in the image.
 */
-(nonnull MPSImage*) weightsImage;

@end /* MPSCNNLossLabels */
    

typedef NSArray <MPSCNNLossLabels*>  MPSCNNLossLabelsBatch MPS_AVAILABLE_STARTING(macos(10.13.4), ios(11.3), macCatalyst(13.0), tvos(11.3));

#pragma mark -
#pragma mark MPSCNNLossDescriptor
    
/*!
 *  @class      MPSCNNLossDescriptor
 *  @dependency This depends on Metal.framework.
 *  @discussion The MPSCNNLossDescriptor specifies a loss filter descriptor.
 *              The same descriptor can be used to initialize both the
 *              MPSCNNLoss and the MPSNNLossGradient filters.
 */
MPS_CLASS_AVAILABLE_STARTING(macos(10.13.4), ios(11.3), macCatalyst(13.0), tvos(11.3))
@interface MPSCNNLossDescriptor : NSObject <NSCopying>

/*! @property   lossType
 *  @abstract   The type of a loss filter.
 *  @discussion This parameter specifies the type of a loss filter.
 */
@property (readwrite, nonatomic) MPSCNNLossType lossType;

/*! @property   reductionType
 *  @abstract   The type of a reduction operation performed in the loss filter.
 *  @discussion This parameter specifies the type of a reduction operation
 *              performed in the loss filter.
 */
@property (readwrite, nonatomic) MPSCNNReductionType reductionType;

/*! @property   reduceAcrossBatch
 *  @abstract   If set to YES then the reduction operation is applied also across the batch-index dimension,
 *              ie. the loss value is summed over images in the batch and the result of the reduction is written
 *              on the first loss image in the batch while the other loss images will be set to zero.
 *              If set to NO, then no reductions are performed across the batch dimension and each image in the batch
 *              will contain the loss value associated with that one particular image.
 *              NOTE: If reductionType == MPSCNNReductionTypeNone, then this flag has no effect on results,
 *              that is no reductions are done in this case.
 *              NOTE: If reduceAcrossBatch is set to YES and reductionType == MPSCNNReductionTypeMean then
 *              the final forward loss value is computed by first summing over the components and then by
 *              dividing the result with: number of feature channels * width * height * number of images in the batch.
 *              The default value is NO.
 */
@property (readwrite, nonatomic) BOOL reduceAcrossBatch MPS_AVAILABLE_STARTING(macos(11.0), ios(14.0), macCatalyst(14.0), tvos(14.0));


/*! @property   weight
 *  @abstract   The scale factor to apply to each element of a result.
 *  @discussion Each element of a result is multiplied by the weight value.
 *              The default value is 1.0f.
 */
@property (readwrite, nonatomic) float weight;

/*!
 * @property    labelSmoothing
 * @abstract    The label smoothing parameter. The default value is 0.0f.
 * @discussion  This parameter is valid only for the loss functions of the following type(s):
 *              MPSCNNLossFunctionTypeSoftmaxCrossEntropy, MPSCNNLossFunctionTypeSigmoidCrossEntropy.
 *
 *              MPSCNNLossFunctionTypeSoftmaxCrossEntropy: given labels (ground truth), it is applied in the following way:
 *              labels = labelSmoothing > 0 ? labels * (1 - labelSmoothing) + labelSmoothing / numberOfClasses : labels
 *
 *              MPSCNNLossFunctionTypeSigmoidCrossEntropy: given labels (ground truth), it is applied in the following way:
 *              labels = labelSmoothing > 0 ? labels * (1 - labelSmoothing) + 0.5 * labelSmoothing : labels
 */
@property (readwrite, nonatomic) float labelSmoothing;

/*!
 * @property    numberOfClasses
 * @abstract    The number of classes parameter. The default value is 1.
 * @discussion  This parameter is valid only for the loss functions of the following type(s):
 *              MPSCNNLossFunctionTypeSoftmaxCrossEntropy.
 *
 *              Given labels (ground truth), it is applied in the following way:
 *              labels = labelSmoothing > 0 ? labels * (1 - labelSmoothing) + labelSmoothing / numberOfClasses : labels
 */
@property (readwrite, nonatomic) NSUInteger numberOfClasses;

/*!
 * @property    epsilon
 * @abstract    The epsilon parameter. The default value is 1e-7.
 * @discussion  This parameter is valid only for the loss functions of the following type(s):
 *              MPSCNNLossTypeLog.
 *
 *              Given predictions and labels (ground truth), it is applied in the following way:
 *              -(labels * log(predictions + epsilon)) - ((1 - labels) * log(1 - predictions + epsilon))
 */
@property (readwrite, nonatomic) float epsilon;

/*!
 * @property    delta
 * @abstract    The delta parameter. The default value is 1.0f.
 * @discussion  This parameter is valid only for the loss functions of the following type(s):
 *              MPSCNNLossTypeHuber.
 *
 *              Given predictions and labels (ground truth), it is applied in the following way:
 *              if (|predictions - labels| <= delta, loss = 0.5f * predictions^2
 *              if (|predictions - labels| >  delta, loss = 0.5 * delta^2 + delta * (|predictions - labels| - delta)
 */
@property (readwrite, nonatomic) float delta;

/*
 * You must use one of the interfaces below instead.
 */
-(nonnull instancetype) init NS_UNAVAILABLE;

/*!
 *  @abstract   Make a descriptor for a MPSCNNLoss or MPSNNLossGradient object.
 *  @param      lossType                    The type of a loss filter.
 *  @param      reductionType               The type of a reduction operation to apply.
 *                                          This argument is ignored in the MPSNNLossGradient filter.
 *  @return     A valid MPSCNNLossDescriptor object or nil, if failure.
 */
+(nonnull MPSCNNLossDescriptor*) cnnLossDescriptorWithType:(MPSCNNLossType) lossType
                                             reductionType:(MPSCNNReductionType) reductionType;

@end /* MPSCNNLossDescriptor */


#pragma mark -
#pragma mark MPSCNNLoss

/*!
 *  @class      MPSCNNLoss
 *  @dependency This depends on Metal.framework.
 *  @discussion The MPSCNNLoss filter is only used for training. This filter performs both the forward and
 *              backward pass computations. Specifically, it computes the loss between the input (predictions)
 *              and target data (labels) and the loss gradient. The loss value can be a 1 x 1 x 1 image containing
 *              a scalar loss value or an image (of the same size as the input source image) with per feature
 *              channel losses. The loss value is used to determine whether to continue the training operation or
 *              to terminate it, once satisfactory results are achieved. The loss gradient is the first gradient
 *              computed for the backward pass and serves as input to the next gradient filter (in the backward
 *              direction).
 *
 *              The MPSCNNLoss filter is created with a MPSCNNLossDescriptor describing the type of a loss filter
 *              and the type of a reduction to use for computing the overall loss.
 *
 *              The MPSCNNLoss filter takes the output of the inference pass (predictions) as input. It also
 *              requires the target data (labels) and optionally, weights for the labels. If per-label weights
 *              are not supplied, there is an option to use a single weight value by setting the 'weight' properly
 *              on the MPSCNNLossDescriptor object. The labels and optional weights need to be supplied by the user
 *              using the MPSCNNLossLabels object. The labels and weights are described via the MPSCNNLossDataDescriptor
 *              objects, which are in turn used to initialize the MPSCNNLossLabels object.
 *
 *              If the specified reduction operation is MPSCNNReductionTypeNone, the destinationImage should be
 *              at least as large as the specified clipRect. The destinationImage will then contain per-element
 *              losses. Otherse, a reduction operation will be performed, according to the specified reduction
 *              type, and the filter will return a scalar value containing the overall loss. For more information
 *              on the available reduction types, see MPSCNNTypes.h. Also see MPSCNNLossDescriptor for the
 *              description of optional parameters.
 *
 *              Here is a code example:
 *
 *              // Setup
 *              MPSCNNLossDataDescriptor* labelsDescriptor =
 *                  [MPSCNNLossDataDescriptor cnnLossDataDescriptorWithData: labelsData
 *                                                                   layout: MPSDataLayoutHeightxWidthxFeatureChannels
 *                                                                     size: labelsDataSize];
 *              MPSCNNLossLabels* labels = [[MPSCNNLossLabels alloc] initWithDevice: device
 *                                                                 labelsDescriptor: labelsDescriptor];
 *              MPSCNNLossDescriptor *lossDescriptor =
 *                  [MPSCNNLossDescriptor cnnLossDescriptorWithType: (MPSCNNLossType)MPSCNNLossTypeMeanAbsoluteError
 *                                                    reductionType: (MPSCNNReductionType)MPSCNNReductionTypeSum];
 *              MPSCNNLoss* lossFilter = [[MPSCNNLoss alloc] initWithDevice: device lossDescriptor: lossDescriptor];
 *
 *              // Encode loss filter.
 *              // The sourceImage is the output of a previous layer, for example, the SoftMax layer. The lossGradientsImage
 *              // is the sourceGradient input image to the first gradient layer (in the backward direction), for example,
 *              // the SoftMax gradient filter.
 *              [lossFilter encodeToCommandBuffer: commandBuffer sourceImage: sourceImage
 *                                                                    labels: labels
 *                                                          destinationImage: lossGradientsImage];
 *
 *              // In order to guarantee that the loss image data is correctly synchronized for CPU side access,
 *              // it is the application's responsibility to call the [labels synchronizeOnCommandBuffer:]
 *              // method before accessing the loss image data.
 *              [labels synchronizeOnCommandBuffer:commandBuffer];
 *              MPSImage* lossImage = [labels lossImage];
 *
 *
 *
 *              For predictions (y) and labels (t), the available loss filter types are the following:
 *
 *              Mean Absolute Error loss filter. This filter measures the absolute error of the element-wise
 *              difference between the predictions and labels.
 *              This loss function is computed according to the following formulas:
 *                  Compute losses:          losses = |y - t|
 *                  Compute weighted losses: weighted_losses = weight(s) * losses
 *                  Compute overall loss:    loss = reduce(weighted_losses, reductionType)
 *
 *              Mean Squared Error loss filter. This filter measures the squared error of the element-wise
 *              difference between the predictions and labels.
 *              This loss function is computed according to the following formulas:
 *                  Compute losses:          losses = (y - t)^2
 *                  Compute weighted losses: weighted_losses = weight(s) * losses
 *                  Compute overall loss:    loss = reduce(weighted_losses, reductionType)
 * 
 *              SoftMax Cross Entropy loss filter. This loss filter is applied element-wise.
 *              This loss filter combines the LogSoftMax and Negative Log Likelihood operations in a
 *              single filter. It is useful for training a classification problem with multiple classes.
 *              This loss function is computed according to the following formulas:
 *                  Compute losses:          losses = -t * LogSoftMax(y)
 *                  Compute weighted losses: weighted_losses = weight(s) * losses
 *                  Compute overall loss:    loss = reduce(weighted_losses, reductionType)
 *                                           If reductionType is MPSCNNReductionTypeMean, the accumulated
 *                                           loss value is divided by width * height instead of
 *                                           width * height * featureChannels.
 *
 *              Sigmoid Cross Entropy loss filter. This loss filter is applied element-wise.
 *              This loss function is computed according to the following formulas:
 *                  Compute losses:          losses = max(y, 0) - y * t + log(1 + exp(-|y|))
 *                  Compute weighted losses: weighted_losses = weight(s) * losses
 *                  Compute overall loss:    loss = reduce(weighted_losses, reductionType)
 *
 *              Categorical Cross Entropy loss filter. This loss filter is applied element-wise.
 *              This loss function is computed according to the following formulas:
 *                  Compute losses:          losses = -t * log(y)
 *                  Compute weighted losses: weighted_losses = weight(s) * losses
 *                  Compute overall loss:    loss = reduce(weighted_losses, reductionType)
 *
 *              Hinge loss filter. This loss filter is applied element-wise.
 *              The labels are expected to be 0.0 or 1.0.
 *              This loss function is computed according to the following formulas:
 *                  Compute losses:          losses = max(1 - (t * y), 0.0f)
 *                  Compute weighted losses: weighted_losses = weight(s) * losses
 *                  Compute overall loss:    loss = reduce(weighted_losses, reductionType)
 *
 *              Huber loss filter. This loss filter is applied element-wise.
 *              This loss function is computed according to the following formulas:
 *                  Compute losses:          if (|y - t| <= delta, losses = 0.5 * y^2
 *                                           if (|y - t| >  delta, losses = 0.5 * delta^2 + delta * (|y - t| - delta)
 *                  Compute weighted losses: weighted_losses = weight(s) * losses
 *                  Compute overall loss:    loss = reduce(weighted_losses, reductionType)
 *
 *              Cosine Distance loss filter. This loss filter is applied element-wise.
 *              The only valid reduction type for this loss filter is MPSCNNReductionTypeSum.
 *              This loss function is computed according to the following formulas:
 *                  Compute losses:          loss = 1 - reduce_sum(y * t)
 *                  Compute overall loss:    weighted_loss = weight * loss
 *
 *              Log loss filter. This loss filter is applied element-wise.
 *              This loss function is computed according to the following formulas:
 *                  Compute losses:          losses = -(t * log(y + epsilon)) - ((1 - t) * log(1 - y + epsilon))
 *                  Compute weighted losses: weighted_losses = weight(s) * losses
 *                  Compute overall loss:    loss = reduce(weighted_losses, reductionType)
 *
 *              Kullback-Leibler Divergence loss filter. This loss filter is applied element-wise.
 *              The input (predictions) is expected to contain log-probabilities.
 *                  This loss function is computed according to the following formulas:
 *                  Compute losses:          losses = t * (log(t) - y)
 *                  Compute weighted losses: weighted_losses = weight(s) * losses
 *                  Compute overall loss:    loss = reduce(weighted_losses, reductionType)
 *
 *
 *
 *              For predictions (y) and labels (t), the loss gradient for each available loss filter type
 *              is computed as follows:
 *
 *              Mean Absolute Error loss.
 *              The loss gradient is computed according to the following formulas:
 *                  Compute gradient:          d/dy = (y - t) / |y - t|
 *                  Compute weighted gradient: weighted_gradient = weight(s) * gradient
 *
 *              Mean Squared Error loss.
 *              The loss gradient is computed according to the following formulas:
 *                  Compute gradient:          d/dy = 2 * (y - t)
 *                  Compute weighted gradient: weighted_gradient = weight(s) * gradient
 *
 *              SoftMax Cross Entropy loss.
 *              The loss gradient is computed according to the following formulas:
 *                  First, apply the same label smoothing as in the MPSCNNLoss filter.
 *                  Compute gradient:          d/dy = y - t
 *                  Compute weighted gradient: weighted_gradient = weight(s) * gradient
 *
 *              Sigmoid Cross Entropy loss.
 *              The loss gradient is computed according to the following formulas:
 *              First, apply the same label smoothing as in the MPSCNNLoss filter.
 *                  Compute gradient:          d/dy = (1 / (1 + exp(-y)) - t
 *                  Compute weighted gradient: weighted_gradient = weight(s) * gradient
 *
 *              Categorical Cross Entropy loss.
 *              The loss gradient is computed according to the following formulas:
 *                  Compute gradient:          d/dy = -t / y
 *                  Compute weighted gradient: weighted_gradient = weight(s) * gradient
 *
 *              Hinge loss.
 *              The loss gradient is computed according to the following formulas:
 *                  Compute gradient:          d/dy = ((1 + ((1 - (2 * t)) * y)) > 0) ? 1 - (2 * t) : 0
 *                  Compute weighted gradient: weighted_gradient = weight(s) * gradient
 *
 *              Huber loss.
 *              The loss gradient is computed according to the following formulas:
 *                  Compute gradient:          d/dy = |y - t| > delta ? delta : y - t
 *                  Compute weighted gradient: weighted_gradient = weight(s) * gradient
 *
 *              Cosine Distance loss.
 *              The loss gradient is computed according to the following formulas:
 *                  Compute gradient:          d/dy = -t
 *                  Compute weighted gradient: weighted_gradient = weight(s) * gradient
 *
 *              Log loss.
 *              The loss gradient is computed according to the following formulas:
 *                  Compute gradient:          d/dy = (-2 * epsilon * t - t + y + epsilon) / (y * (1 - y) + epsilon * (epsilon + 1))
 *                  Compute weighted gradient: weighted_gradient = weight(s) * gradient
 *
 *              Kullback-Leibler Divergence loss.
 *              The loss gradient is computed according to the following formulas:
 *                  Compute gradient:          d/dy = -t / y
 *                  Compute weighted gradient: weighted_gradient = weight(s) * gradient
 *
 *              The number of output feature channels remains the same as the number of input feature
 *              channels.
 */
MPS_CLASS_AVAILABLE_STARTING(macos(10.13.4), ios(11.3), macCatalyst(13.0), tvos(11.3))
@interface MPSCNNLoss : MPSCNNKernel

/*!
 * See MPSCNNLossDescriptor for information about the following properties.
 */
@property (readonly, nonatomic) MPSCNNLossType lossType;
@property (readonly, nonatomic) MPSCNNReductionType reductionType;
@property (readonly, nonatomic) float weight;
@property (readonly, nonatomic) float labelSmoothing;
@property (readonly, nonatomic) NSUInteger numberOfClasses;
@property (readonly, nonatomic) float epsilon;
@property (readonly, nonatomic) float delta;
@property (readonly, nonatomic) BOOL reduceAcrossBatch MPS_AVAILABLE_STARTING(macos(11.0), ios(14.0), macCatalyst(14.0), tvos(14.0));

/*
 * You must use initWithDevice:lossDescriptor instead.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device NS_UNAVAILABLE;

/*!
 *  @abstract   Initialize the loss filter with a loss descriptor.
 *  @param      device                   The device the filter will run on.
 *  @param      lossDescriptor           The loss descriptor.
 *  @return     A valid MPSCNNLoss object or nil, if failure.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                        lossDescriptor: (MPSCNNLossDescriptor*_Nonnull) lossDescriptor NS_DESIGNATED_INITIALIZER;

/*! @abstract <NSSecureCoding> support */
-(nullable instancetype) initWithCoder:(NSCoder * __nonnull)aDecoder device:(nonnull id <MTLDevice>) device NS_DESIGNATED_INITIALIZER;

/*! @abstract   Encode a MPSCNNLoss filter and return a gradient in the destinationImage.
 *  @discussion This filter consumes the output of a previous layer, for example, the SoftMax layer containing
 *              predictions, and the MPSCNNLossLabels object containing the target data (labels) and optionally,
 *              weights for the labels. The destinationImage contains the computed gradient for the loss layer.
 *              It serves as a source gradient input image to the first gradient layer (in the backward direction),
 *              in our example, the SoftMax gradient layer.
 *
 *  @param      commandBuffer       The MTLCommandBuffer on which to encode.
 *  @param      sourceImage         The source image from the previous filter in the graph (in the inference direction).
 *  @param      labels              The object containing the target data (labels) and optionally, weights for the labels.
 *  @param      destinationImage    The MPSImage into which to write the gradient result.
 */
-(void) encodeToCommandBuffer: (nonnull id <MTLCommandBuffer>) commandBuffer
                  sourceImage: (MPSImage * __nonnull) sourceImage
                       labels: (MPSCNNLossLabels * __nonnull) labels
             destinationImage: (MPSImage * __nonnull) destinationImage
            MPS_SWIFT_NAME( encode(commandBuffer:sourceImage:labels:destinationImage:));

/*! @abstract   Encode a MPSCNNLoss filter and return a gradient.
 *  @discussion This -encode call is similar to the encodeToCommandBuffer:sourceImage:labels:destinationImage: above,
 *              except that it creates and returns the MPSImage with the loss gradient result.
 *
 *  @param      commandBuffer       The MTLCommandBuffer on which to encode.
 *  @param      sourceImage         The source image from the previous filter in the graph (in the inference direction).
 *  @param      labels              The object containing the target data (labels) and optionally, weights for the labels.
 *  @return     The MPSImage containing the gradient result.
 */
-(MPSImage*__nonnull) encodeToCommandBuffer: (nonnull id <MTLCommandBuffer>) commandBuffer
                                sourceImage: (MPSImage * __nonnull) sourceImage
                                     labels: (MPSCNNLossLabels * __nonnull) labels
            MPS_SWIFT_NAME( encode(commandBuffer:sourceImage:labels:));


-(void) encodeBatchToCommandBuffer: (nonnull id <MTLCommandBuffer>) commandBuffer
                      sourceImages: (MPSImageBatch * __nonnull) sourceImage
                            labels: (MPSCNNLossLabelsBatch * __nonnull) labels
                 destinationImages: (MPSImageBatch * __nonnull) destinationImage
            MPS_SWIFT_NAME( encode(commandBuffer:sourceImages:labels:destinationImages:));

-(MPSImageBatch*__nonnull) encodeBatchToCommandBuffer: (nonnull id <MTLCommandBuffer>) commandBuffer
                                         sourceImages: (MPSImageBatch * __nonnull) sourceImage
                                               labels: (MPSCNNLossLabelsBatch * __nonnull) labels
            MPS_SWIFT_NAME( encode(commandBuffer:sourceImages:labels:));

@end /* MPSCNNLoss */




#pragma mark -
#pragma mark MPSCNNYOLOLossDescriptor

/*!
 *  @class      MPSCNNYOLOLossDescriptor
 *  @dependency This depends on Metal.framework.
 *  @discussion The MPSCNNYOLOLossDescriptor specifies a loss filter descriptor
 *              that is used to create a MPSCNNLoss filter. The MPSCNNYOLOLoss is a filter that
 *              has been specialized for object detection tasks and follows a specific layout
 *              for the feature-channels of the input, output, weight and label data.
 *
 *              The layout of the data within the feature-channels is as follows:
 *
 *                  Each anchorbox uses ( 2+2+1 + numberOfClasses = 5 + numberOfClasses ) feature channels.
 *
 *              Therefore the total number of feature channels used is: (5 + numberOfClasses) * numberOfAnchorBoxes.
 *              The first feature channel for anchorbox index 'anchorIdx' is at fcIndex = (5 + numberOfClasses) * anchorIdx,
 *              and the feature channels within each anchorbox are stored in the layout: 'XYWHCFFFFFF...', where (XY) are
 *              the so-called raw x and y coordinates of the bounding box within each gridcell and (WH) are the corresponding
 *              width and height. 'C' signifies a confidence for having an object in the cell and FFFFF... are the feature channel
 *              values for each class of object to be classified in the object detector.
 *
 *              The YOLO-loss filter works by operating mostly independently on each anchorbox:
 *                  *   The XY-channels of the inputs are first transformed to relative XY-values by applying the sigmoid-neuron on them,
 *                      after which they are passed through the loss function defined by @ref XYLossDescriptor, which is typically chosen
 *                      to be the @ref MPSCNNLossTypeMeanSquaredError type loss function.
 *                  *   The WH-channels contain the raw width and height of the bounding box and they are operated with the
 *                      loss function defined by @ref WHLossDescriptor, which is typically of type @ref MPSCNNLossTypeHuber.
 *                  *   The C-channel contains the confidence value of having an object in the bounding box and it is operated
 *                      by the loss function defined by @ref confidenceLossDescriptor, which is typically chosen to be
 *                      @ref MPSCNNLossTypeSigmoidCrossEntropy.
 *                  *   The FFFFF... (number of channels is number of classes) channels contains the raw feature channels for
 *                      object classes, used to identify which objects are the most probable ones in the bounding box and
 *                      these channels are passed through the loss function defined by @ref classesLossDescriptor, which in
 *                      typical cases is of the type @ref MPSCNNLossTypeSoftMaxCrossEntropy.
 *
 *              For details on how to set up the label values and anchorboxes see https://arxiv.org/abs/1612.08242
 */
MPS_CLASS_AVAILABLE_STARTING(macos(10.14), ios(12), macCatalyst(13.0), tvos(12))
@interface MPSCNNYOLOLossDescriptor : NSObject <NSCopying>

/*! @property   XYLossDescriptor
 *  @abstract   The type of a loss filter.
 *  @discussion This parameter specifies the type of a loss filter.
 */
@property (readwrite, nonatomic, nonnull, retain) MPSCNNLossDescriptor *XYLossDescriptor;

/*! @property   WHLossDescriptor
 *  @abstract   The type of a loss filter.
 *  @discussion This parameter specifies the type of a loss filter.
 */
@property (readwrite, nonatomic, nonnull, retain) MPSCNNLossDescriptor *WHLossDescriptor;

/*! @property   confidenceLossDescriptor
 *  @abstract   The type of a loss filter.
 *  @discussion This parameter specifies the type of a loss filter.
 */
@property (readwrite, nonatomic, nonnull, retain) MPSCNNLossDescriptor *confidenceLossDescriptor;

/*! @property   classesLossDescriptor
 *  @abstract   The type of a loss filter.
 *  @discussion This parameter specifies the type of a loss filter.
 */
@property (readwrite, nonatomic, nonnull, retain) MPSCNNLossDescriptor *classesLossDescriptor;

/*! @property   reductionType
 *  @abstract   ReductionType shared accross all losses (so they may generate same sized output)
 */
@property (readwrite, nonatomic) MPSCNNReductionType reductionType;

/*! @property   reduceAcrossBatch
 *  @abstract   If set to YES then the reduction operation is applied also across the batch-index dimension,
 *              ie. the loss value is summed over images in the batch and the result of the reduction is written
 *              on the first loss image in the batch while the other loss images will be set to zero.
 *              If set to NO, then no reductions are performed across the batch dimension and each image in the batch
 *              will contain the loss value associated with that one particular image.
 *              NOTE: If reductionType == MPSCNNReductionTypeNone, then this flag has no effect on results,
 *              that is no reductions are done in this case.
 *              NOTE: If reduceAcrossBatch is set to YES and reductionType == MPSCNNReductionTypeMean then
 *              the final forward loss value is computed by first summing over the components and then by
 *              dividing the result with: number of feature channels * width * height * number of images in the batch.
 *              The default value is NO.
 */
@property (readwrite, nonatomic) BOOL reduceAcrossBatch MPS_AVAILABLE_STARTING(macos(11.0), ios(14.0), macCatalyst(14.0), tvos(14.0));


/*! @property   rescore
 *  @abstract   Rescore pertains to multiplying the confidence groundTruth with IOU (intersection over union)
 *              of predicted bounding box and the groundTruth boundingBox. Default is YES
 */
@property (readwrite, nonatomic) BOOL rescore;

/*! @property   scaleXY
 *  @abstract   scale factor for XY loss and loss gradient default is 10.0
 */
@property (readwrite, nonatomic) float scaleXY;

/*! @property   scaleWH
 *  @abstract   scale factor for WH loss and loss gradient default is 10.0
 */
@property (readwrite, nonatomic) float scaleWH;

/*! @property   scaleNoObject
 *  @abstract   scale factor for no object confidence loss and loss gradient default is 5.0
 */
@property (readwrite, nonatomic) float scaleNoObject;

/*! @property   scaleObject
 *  @abstract   scale factor for no object confidence loss and loss gradient default is 100.0
 */
@property (readwrite, nonatomic) float scaleObject;

/*! @property   scaleClass
 *  @abstract   scale factor for no object classes loss and loss gradient default is 2.0
 */
@property (readwrite, nonatomic) float scaleClass;

/*! @property   pos_iou
 *  @abstract   If the prediction IOU with groundTruth is higher than this
 *              value we consider it a confident object presence, default is 0.7
 */
@property (readwrite, nonatomic) float minIOUForObjectPresence;

/*! @property   neg_iou
 *  @abstract   If the prediction IOU with groundTruth is lower than this
 *              value we consider it a confident object absence, default is 0.3
 */
@property (readwrite, nonatomic) float maxIOUForObjectAbsence;

/*! @property   numberOfAnchorBoxes
 *  @abstract   number of anchor boxes used to detect object per grid cell
 */
@property (readwrite, nonatomic) NSUInteger numberOfAnchorBoxes;

/*! @property   anchorBoxes
 *  @abstract   NSData containing the width and height for numberOfAnchorBoxes anchor boxes
 *              This NSData should have 2 float values per anchor box which represent the width
 *              and height of the anchor box.
 *  @code
 *              typedef struct anchorBox{
 *                  float width;
 *                  float height;
 *              }anchorBox;
 *
 *
 *              anchorBox_t gAnchorBoxes[MAX_NUM_ANCHOR_BOXES] = {
 *                  {.width = 1.f, .height = 2.f},
 *                  {.width = 1.f, .height = 1.f},
 *                  {.width = 2.f, .height = 1.f},
 *              };
 *              NSData* labelsInputData = [NSData dataWithBytes: gAnchorBoxes length: MAX_NUM_ANCHOR_BOXES * sizeof(anchorBox)];
 *  @endcode
 *
 */
@property (readwrite, nonatomic, nonnull, retain) NSData *anchorBoxes;

/*
 * You must use one of the interfaces below instead.
 */
-(nonnull instancetype) init NS_UNAVAILABLE;

/*!
 *  @abstract   Make a descriptor for a MPSCNNYOLOLoss object.
 *  @param      XYLossType                  The type of spatial position loss filter.
 *  @param      WHLossType                  The type of spatial size loss filter.
 *  @param      confidenceLossType          The type of confidence filter.
 *  @param      classesLossType             The type of classes filter.
 *  @param      reductionType               The type of a reduction operation to apply.
 *  @param      anchorBoxes                 This is an NSData which has an array of anchorBoxes defined as a struct{ float width; float height; };
 *  @return     A valid MPSCNNYOLOLossDescriptor object or nil, if failure.
 */
+(nonnull MPSCNNYOLOLossDescriptor*) cnnLossDescriptorWithXYLossType:(MPSCNNLossType) XYLossType
                                                          WHLossType:(MPSCNNLossType) WHLossType
                                                  confidenceLossType:(MPSCNNLossType) confidenceLossType
                                                     classesLossType:(MPSCNNLossType) classesLossType
                                                       reductionType:(MPSCNNReductionType) reductionType
                                                         anchorBoxes:(NSData*__nonnull) anchorBoxes
                                                 numberOfAnchorBoxes:(NSUInteger) numberOfAnchorBoxes;

@end /* MPSCNNYOLOLossDescriptor */


MPS_CLASS_AVAILABLE_STARTING(macos(10.14), ios(12.0), macCatalyst(13.0), tvos(12.0))
@interface MPSCNNYOLOLoss : MPSCNNKernel

/*! @property   lossXY
 *  @abstract   loss filter for prediction of bounding box position
 */
@property (readonly, nonatomic, retain, nonnull) MPSCNNLoss *lossXY;

/*! @property   lossWH
 *  @abstract   loss filter for prediction of bounding box size
 */
@property (readonly, nonatomic, retain, nonnull) MPSCNNLoss *lossWH;

/*! @property   lossConfidence
 *  @abstract   loss filter for prediction of bounding box probability of presence of object
 */
@property (readonly, nonatomic, retain, nonnull) MPSCNNLoss *lossConfidence;

/*! @property   lossClasses
 *  @abstract   loss filter for prediction of bounding box predicted class of the detected object
 */
@property (readonly, nonatomic, retain, nonnull) MPSCNNLoss *lossClasses;

/*!
 * See MPSCNNYOLOLossDescriptor for information about the following properties.
 */
@property (readonly, nonatomic) float scaleXY;
@property (readonly, nonatomic) float scaleWH;
@property (readonly, nonatomic) float scaleNoObject;
@property (readonly, nonatomic) float scaleObject;
@property (readonly, nonatomic) float scaleClass;
@property (readonly, nonatomic) float minIOUForObjectPresence;
@property (readonly, nonatomic) float maxIOUForObjectAbsence;
@property (readonly, nonatomic) MPSCNNReductionType reductionType;
@property (readonly, nonatomic) NSUInteger numberOfAnchorBoxes;
@property (readonly, nonatomic, nonnull, retain) NSData *anchorBoxes;
@property (readonly, nonatomic) BOOL reduceAcrossBatch MPS_AVAILABLE_STARTING(macos(11.0), ios(14.0), macCatalyst(14.0), tvos(14.0));


/*
 * You must use initWithDevice:lossDescriptor instead.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device NS_UNAVAILABLE;

/*!
 *  @abstract   Initialize the loss filter with a loss descriptor.
 *  @param      device                   The device the filter will run on.
 *  @param      lossDescriptor           The loss descriptor.
 *  @return     A valid MPSCNNLoss object or nil, if failure.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                        lossDescriptor: (MPSCNNYOLOLossDescriptor*_Nonnull) lossDescriptor NS_DESIGNATED_INITIALIZER;

/*! @abstract <NSSecureCoding> support */
-(nullable instancetype) initWithCoder:(NSCoder * __nonnull)aDecoder device:(nonnull id <MTLDevice>) device NS_DESIGNATED_INITIALIZER;

/*! @abstract   Encode a MPSCNNYOLOLoss filter and return a gradient in the destinationImage.
 *  @discussion This filter consumes the output of a previous layer and the MPSCNNLossLabels object containing
 *              the target data (labels) and optionally, weights for the labels.
 *              The destinationImage contains the computed gradient for the loss layer.
 *              It serves as a source gradient input image to the first gradient layer (in the backward direction).
 *              For information on the data-layout see @ref MPSCNNYOLOLossDescriptor.
 *
 *  @param      commandBuffer       The MTLCommandBuffer on which to encode.
 *  @param      sourceImage         The source image from the previous filter in the graph (in the inference direction).
 *  @param      labels              The object containing the target data (labels) and optionally, weights for the labels.
 *  @param      destinationImage    The MPSImage into which to write the gradient result.
 */
-(void) encodeToCommandBuffer: (nonnull id <MTLCommandBuffer>) commandBuffer
                  sourceImage: (MPSImage * __nonnull) sourceImage
                       labels: (MPSCNNLossLabels * __nonnull) labels
             destinationImage: (MPSImage * __nonnull) destinationImage
MPS_SWIFT_NAME( encode(commandBuffer:sourceImage:labels:destinationImage:));

/*! @abstract   Encode a MPSCNNLoss filter and return a gradient.
 *  @discussion This -encode call is similar to the encodeToCommandBuffer:sourceImage:labels:destinationImage: above,
 *              except that it creates and returns the MPSImage with the loss gradient result.
 *
 *  @param      commandBuffer       The MTLCommandBuffer on which to encode.
 *  @param      sourceImage         The source image from the previous filter in the graph (in the inference direction).
 *  @param      labels              The object containing the target data (labels) and optionally, weights for the labels.
 *  @return     The MPSImage containing the gradient result.
 */
-(MPSImage*__nonnull) encodeToCommandBuffer: (nonnull id <MTLCommandBuffer>) commandBuffer
                                sourceImage: (MPSImage * __nonnull) sourceImage
                                     labels: (MPSCNNLossLabels * __nonnull) labels
MPS_SWIFT_NAME( encode(commandBuffer:sourceImage:labels:));


-(void) encodeBatchToCommandBuffer: (nonnull id <MTLCommandBuffer>) commandBuffer
                      sourceImages: (MPSImageBatch * __nonnull) sourceImage
                            labels: (MPSCNNLossLabelsBatch * __nonnull) labels
                 destinationImages: (MPSImageBatch * __nonnull) destinationImage
MPS_SWIFT_NAME( encode(commandBuffer:sourceImages:labels:destinationImages:));

-(MPSImageBatch*__nonnull) encodeBatchToCommandBuffer: (nonnull id <MTLCommandBuffer>) commandBuffer
                                         sourceImages: (MPSImageBatch * __nonnull) sourceImage
                                               labels: (MPSCNNLossLabelsBatch * __nonnull) labels
MPS_SWIFT_NAME( encode(commandBuffer:sourceImages:labels:));

@end /* MPSCNNYOLOLoss */



#pragma mark -
#pragma mark MPSNNForwardLoss

/*!
 *  @class      MPSNNForwardLoss
 *  @dependency This depends on Metal.framework.
 *  @discussion The MPSNNForwardLoss filter specifies a version of the loss filter which separates the forward
 *              computation from the gradient computation. In order to compute gradients for the loss filter
 *              use @ref MPSNNLossGradient filter and in order to start the gradient computation of an arbitrary
 *              image use the @ref MPSNNInitialGradient filter.
 *              NOTE: This filter does not support non-default offset or cliprects and setting them to other
 *              than default values will result in undefined results.
 */
MPS_CLASS_AVAILABLE_STARTING(macos(10.15.0), ios(13.0), macCatalyst(13.0), tvos(13.0))
@interface MPSNNForwardLoss : MPSCNNKernel

/*!
 * See MPSCNNLossDescriptor for information about the following properties.
 */
@property (readonly, nonatomic) MPSCNNLossType lossType;
@property (readonly, nonatomic) MPSCNNReductionType reductionType;
@property (readonly, nonatomic) BOOL reduceAcrossBatch MPS_AVAILABLE_STARTING(macos(11.0), ios(14.0), macCatalyst(14.0), tvos(14.0));

@property (readonly, nonatomic) NSUInteger numberOfClasses;

// Dynamically adjustable parameters
@property (readwrite, nonatomic) float weight;
@property (readwrite, nonatomic) float labelSmoothing;
@property (readwrite, nonatomic) float epsilon;
@property (readwrite, nonatomic) float delta;

/*
 * You must use initWithDevice:lossDescriptor instead.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device NS_UNAVAILABLE;

/*!
 *  @abstract   Initialize the loss forward pass filter with a loss descriptor.
 *  @param      device                   The device the filter will run on.
 *  @param      lossDescriptor           The loss descriptor.
 *  @return     A valid MPSNNForwardLoss object or nil, if failure.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                        lossDescriptor: (MPSCNNLossDescriptor*_Nonnull) lossDescriptor NS_DESIGNATED_INITIALIZER;

/*! @abstract <NSSecureCoding> support */
-(nullable instancetype) initWithCoder:(NSCoder * __nonnull)aDecoder device:(nonnull id <MTLDevice>) device NS_DESIGNATED_INITIALIZER;



/*! @abstract   Encode a MPSNNForwardLoss filter and return the result in the destinationImage.
 *
 *  @param      commandBuffer       The MTLCommandBuffer on which to encode.
 *  @param      sourceImages        The source images that contains the network prediction (logits).
 *  @param      labels              The source images that contains the labels (targets).
 *  @param      weights             The object containing weights for the labels. Optional.
 *  @param      destinationStates   Optional gradient state - carries dynamical property values to the gradient pass
 *                                  (weight, labelSmoothing, epsilon, delta). Create state using resultStateBatchForSourceImage: or
 *                                  temporaryResultStateBatchForCommandBuffer:.
 *  @param      destinationImages   The MPSImages into which to write the loss results.
 */

-(void) encodeBatchToCommandBuffer: (nonnull id <MTLCommandBuffer>) commandBuffer
                      sourceImages: (MPSImageBatch * __nonnull) sourceImages
                            labels: (MPSImageBatch * __nonnull) labels
                           weights: (MPSImageBatch * __nullable) weights
                 destinationStates: (MPSStateBatch * __nullable) destinationStates
                 destinationImages: (MPSImageBatch * __nonnull) destinationImages
MPS_SWIFT_NAME( encodeBatch(commandBuffer:sourceImages:labels:weights:destinationStates:destinationImages:));


/*! @abstract   Encode a MPSNNForwardLoss filter and return the loss result image(s).
 *  @discussion This -encode call is similar to the encodeBatchToCommandBuffer:sourceImages:labels:destinationImages: above,
 *              except that it creates and returns the MPSImages with the loss result.
 *
 *  @param      commandBuffer       The MTLCommandBuffer on which to encode.
 *  @param      sourceImages        The source images that contains the network prediction (logits).
 *  @param      labels              The source images that contains the labels (targets).
 *  @param      weights             The object containing weights for the labels. Optional.
 *  @param      outStates           Optional gradient state - carries dynamical property values to the gradient pass
 *                                  (weight, labelSmoothing, epsilon, delta).
 *  @param      isTemporary         Whether the returned state (if any) should be temporary or not.
 *  @return     The MPSImages containing the loss computation results.
 */

-(MPSImageBatch * __nonnull) encodeBatchToCommandBuffer: (nonnull id <MTLCommandBuffer>) commandBuffer
                                           sourceImages: (MPSImageBatch * __nonnull) sourceImages
                                                 labels: (MPSImageBatch * __nonnull) labels
                                                weights: (MPSImageBatch * __nullable) weights
                                      destinationStates: (__autoreleasing MPSStateBatch * __nullable * __nullable) outStates
                            destinationStateIsTemporary: (BOOL) isTemporary
MPS_SWIFT_NAME( encodeBatch(commandBuffer:sourceImages:labels:weights:outStates:isTemporary:));

@end /* MPSNNForwardLoss */


#pragma mark -
#pragma mark MPSNNLossGradient

/*!
 *  @class      MPSNNLossGradient
 *  @dependency This depends on Metal.framework.
 *  @discussion The MPSNNLossGradient filter specifies the gradient filter for @ref MPSNNForwardLoss.
 */
MPS_CLASS_AVAILABLE_STARTING(macos(10.15.0), ios(13.0), macCatalyst(13.0), tvos(13.0))
@interface MPSNNLossGradient : MPSCNNBinaryKernel

/*!
 * See MPSCNNLossDescriptor for information about the following properties.
 */
@property (readonly, nonatomic) MPSCNNLossType lossType;
@property (readonly, nonatomic) MPSCNNReductionType reductionType;
@property (readonly, nonatomic) BOOL reduceAcrossBatch MPS_AVAILABLE_STARTING(macos(11.0), ios(14.0), macCatalyst(14.0), tvos(14.0));
@property (readonly, nonatomic) NSUInteger numberOfClasses;

@property (readwrite, nonatomic) float weight;
@property (readwrite, nonatomic) float labelSmoothing;
@property (readwrite, nonatomic) float epsilon;
@property (readwrite, nonatomic) float delta;

/*! @property   computeLabelGradients
 *  @abstract   The computeLabelGradients property is used to control whether the loss gradient
 *              filter computes gradients for the primary (predictions) or secondary (labels) source image from the forward pass.
 *              Default: NO.
 */
@property (readwrite, nonatomic) BOOL            computeLabelGradients;



/*
 * You must use initWithDevice:lossDescriptor instead.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device NS_UNAVAILABLE;

/*!
 *  @abstract   Initialize the loss gradient filter with a loss descriptor.
 *  @param      device                   The device the filter will run on.
 *  @param      lossDescriptor           The loss descriptor.
 *  @return     A valid MPSNNLossGradient object or nil, if failure.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                        lossDescriptor: (MPSCNNLossDescriptor*_Nonnull) lossDescriptor NS_DESIGNATED_INITIALIZER;

/*! @abstract <NSSecureCoding> support */
-(nullable instancetype) initWithCoder:(NSCoder * __nonnull)aDecoder device:(nonnull id <MTLDevice>) device NS_DESIGNATED_INITIALIZER;



/*! @abstract   Encode the loss gradient filter and return a gradient
 *  @param      commandBuffer    The MTLCommandBuffer on which to encode
 *  @param      sourceGradients  The gradient images from the "next" filter in the graph
 *  @param      sourceImages     The images used as source image from the forward pass
 *  @param      labels           The source images that contains the labels (targets).
 *  @param      weights          The object containing weights for the labels. Optional.
 *  @param      sourceStates     Optional gradient state - carries dynamical property values from the forward pass
 *                                  (weight, labelSmoothing, epsilon, delta).
 */
-(MPSImageBatch*__nonnull) encodeBatchToCommandBuffer: (__nonnull id <MTLCommandBuffer>) commandBuffer
                                      sourceGradients: (MPSImageBatch * __nonnull ) sourceGradients        // a.k.a. primaryImage
                                         sourceImages: (MPSImageBatch * __nonnull ) sourceImages           // prediction source images from forward pass
                                               labels: (MPSImageBatch * __nonnull ) labels                 // label images from forward pass
                                              weights: (MPSImageBatch * __nullable) weights
                                         sourceStates: (MPSStateBatch * __nullable) sourceStates
MPS_SWIFT_NAME( encodeBatch(commandBuffer:sourceGradients:sourceImages:labels:weights:sourceStates:));

/*! @abstract   Encode the loss gradient filter and return a gradient
 *  @param      commandBuffer    The MTLCommandBuffer on which to encode
 *  @param      sourceGradients  The gradient images from the "next" filter in the graph
 *  @param      sourceImages     The image used as source images from the forward pass
 *  @param      labels           The source images that contains the labels (targets).
 *  @param      weights          The object containing weights for the labels. Optional.
 *  @param      sourceStates     Optional gradient state - carries dynamical property values from the forward pass
 *                                  (weight, labelSmoothing, epsilon, delta).
 *  @param      destinationGradients  The MPSImages into which to write the filter result */
-(void) encodeBatchToCommandBuffer: (__nonnull id <MTLCommandBuffer>) commandBuffer
                   sourceGradients: (MPSImageBatch * __nonnull ) sourceGradients        // a.k.a. primaryImage
                      sourceImages: (MPSImageBatch * __nonnull ) sourceImages           // source Image from forward pass, a.k.a. secondaryImage
                            labels: (MPSImageBatch * __nonnull ) labels                 // label images from forward pass
                           weights: (MPSImageBatch * __nullable) weights
                      sourceStates: (MPSStateBatch * __nullable) sourceStates
              destinationGradients: (MPSImageBatch * __nonnull ) destinationGradients
MPS_SWIFT_NAME( encodeBatch(commandBuffer:sourceGradients:sourceImages:labels:weights:sourceStates:destinationGradients:));

@end /* MPSNNLossGradient */


#pragma mark -
#pragma mark MPSNNInitialGradient

/*!
 *  @class      MPSNNInitialGradient
 *  @dependency This depends on Metal.framework
 *  @discussion The MPSCNNInitialGradient filter specifies a layer which computes the initial gradient for
 *              an aribitrary input image. The operation itself is extremely simple: it computes the gradient of the input image
 *              with itself, resulting in an output image which is filled with '1's for all the inputs that were used.
 *              This serves as the starting point for the computation of gradients between arbitrary images in a network.
 *              Example:
 *                  Suppose that we want to compute gradients for a function that multiplies together two losses:
 *                      f = f(L1, L2) = L1 * L2
 *                  The losses themselves are computed from some inputs x1,x2:
 *                      L1 = L1(x1),
 *                      L2 = L2(x2)
 *                  The filters to compute f, L1, L2 are:
 *                      f = MPSCNNMultiply(L1, L2), where
 *                      L1 = MPSNNForwardLoss1(x1) and
 *                      L2 = MPSNNForwardLoss1(x2)
 *
 *                  To compute df/dx1 we apply the chain rule:
 *
 *                      df/dx1 = d(L1 * L2)/dx1 = d(L1 * L2)/dL1 * dL1/dx1 + d(L1 * L2)/dL2 * dL2/dx1
 *                             = d(L1 * L2)/dL1 * dL1/dx1 = L2 * dL1/dx1
 *
 *                  The MPSCNNMultiplyGradient filter computes for f = L1 * L2 forward op:
 *                      dL/dL1 = dL/df * df/dL1 = dL/df * L2 and
 *                      dL/dL2 = dL/df * df/dL2 = dL/df * L1 where
 *                  dL/df is the input gradient of the chain rule / backpropagation algorithm.
 *                  But in our case we want MPSCNNMultiplyGradient to compute the gradient:
 *                      df/dL1 = d(L1 * L2)/dL1 = L2,
 *                  which shows that
 *                      L = f, which means that dL/dL1 = df/df * df/dL1 = 1 * L2, which
 *                  shows that we get the correct gradient by providing unit input as input gradient to
 *                  the MPSCNNMultiplyGradient.
 */

MPS_CLASS_AVAILABLE_STARTING( macos(10.15), ios(13.0), macCatalyst(13.0), tvos(13.0))
@interface  MPSNNInitialGradient : MPSCNNKernel


/*!
 *  @abstract   Initializes a MPSNNInitialGradient kernel.
 *
 *  @param      device      The MTLDevice on which this MPSNNInitialGradient filter will be used.
 *  @return     A valid MPSNNInitialGradient object or nil, if failure.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device;

/*!
 * NOTE:    The encodeToCommandBuffer API in MPSCNNKernel can be used to encode this kernel to a MTLCommandBuffer.
 */

@end    /* MPSNNInitialGradient */




#ifdef __cplusplus
}
#endif

#endif /* MPSCNNLoss_h */
