//
//  MLCLossLayer.h
//  MLCompute
//
//  Copyright © 2019 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <MLCompute/MLCDefines.h>
#import <MLCompute/MLCTypes.h>
#import <MLCompute/MLCLayer.h>
#import <MLCompute/MLCLossDescriptor.h>

@class MLCDevice;
@class MLCTensor;

NS_ASSUME_NONNULL_BEGIN

/*! @class      MLCLossLayer
    @abstract   A loss layer
 */
MLCOMPUTE_CLASS_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))
@interface MLCLossLayer : MLCLayer

/*! @property   descriptor
    @abstract   The loss descriptor
 */
@property (readonly, nonatomic, copy) MLCLossDescriptor *descriptor;

/*! @property   weights
    @abstract   The loss label weights tensor
 */
@property (readonly, nonatomic, nullable, retain) MLCTensor *weights;

/*! @abstract   Create a loss layer
    @param      lossDescriptor          The loss descriptor
    @return     A new loss layer.
 */
+ (instancetype)layerWithDescriptor:(MLCLossDescriptor *)lossDescriptor;

/*! @abstract   Create a MLComputeLoss layer
    @param      lossDescriptor          The loss descriptor
    @param      weights                          The loss label weights tensor
    @return     A new loss layer.
 */
+ (instancetype)layerWithDescriptor:(MLCLossDescriptor *)lossDescriptor
                            weights:(MLCTensor *)weights;

#pragma mark - Convenience Methods

/*! @abstract   Create a loss layer
    @param      reductionType      The reduction type to use
    @param      labelSmoothing     Label smoothing value
    @param      classCount             Number of classes
    @param      weight                      A scalar floating point value
    @return     A new softmax cross entropy loss layer.
 */
+ (instancetype)softmaxCrossEntropyLossWithReductionType:(MLCReductionType)reductionType
                                          labelSmoothing:(float)labelSmoothing
                                              classCount:(NSUInteger)classCount
                                                  weight:(float)weight
    NS_SWIFT_NAME(softmaxCrossEntropy(reductionType:labelSmoothing:classCount:weight:));


/*! @abstract   Create a loss layer
    @param      reductionType         The reduction type to use
    @param      labelSmoothing        Label smoothing value
    @param      classCount                 Number of classes
    @param      weights                        The loss label weights tensor
    @return     A new softmax cross entropy loss layer.
 */
+ (instancetype)softmaxCrossEntropyLossWithReductionType:(MLCReductionType)reductionType
                                          labelSmoothing:(float)labelSmoothing
                                              classCount:(NSUInteger)classCount
                                                 weights:(MLCTensor * _Nullable)weights
    NS_SWIFT_NAME(softmaxCrossEntropy(reductionType:labelSmoothing:classCount:weights:));

/*! @abstract   Create a loss layer
    @param      reductionType      The reduction type to use
    @param      labelSmoothing     Label smoothing value
    @param      classCount              Number of classes
    @param      weight                       A scalar floating point value
    @return     A new categorical cross entropy loss layer.
 */
+ (instancetype)categoricalCrossEntropyLossWithReductionType:(MLCReductionType)reductionType
                                              labelSmoothing:(float)labelSmoothing
                                                  classCount:(NSUInteger)classCount
                                                      weight:(float)weight
    NS_SWIFT_NAME(categoricalCrossEntropy(reductionType:labelSmoothing:classCount:weight:));


/*! @abstract   Create a loss layer
    @param      reductionType         The reduction type to use
    @param      labelSmoothing        Label smoothing value
    @param      classCount                 Number of classes
    @param      weights                        The loss label weights tensor
    @return     A new categorical cross entropy loss layer.
 */
+ (instancetype)categoricalCrossEntropyLossWithReductionType:(MLCReductionType)reductionType
                                              labelSmoothing:(float)labelSmoothing
                                                  classCount:(NSUInteger)classCount
                                                     weights:(MLCTensor * _Nullable)weights
    NS_SWIFT_NAME(categoricalCrossEntropy(reductionType:labelSmoothing:classCount:weights:));


/*! @abstract   Create a loss layer
    @param      reductionType         The reduction type to use
    @param      labelSmoothing       Label smoothing value
    @param      weight                         A scalar floating-point value
    @return     A new sigmoid cross entropy loss layer.
 */
+ (instancetype)sigmoidCrossEntropyLossWithReductionType:(MLCReductionType)reductionType
                                          labelSmoothing:(float)labelSmoothing
                                                  weight:(float)weight
    NS_SWIFT_NAME(sigmoidCrossEntropy(reductionType:labelSmoothing:weight:));

/*! @abstract   Create a loss layer
    @param      reductionType         The reduction type to use
    @param      labelSmoothing       Label smoothing value
    @param      weights                       The loss label weights tensor
    @return     A new sigmoid cross entropy loss layer.
 */
+ (instancetype)sigmoidCrossEntropyLossWithReductionType:(MLCReductionType)reductionType
                                          labelSmoothing:(float)labelSmoothing
                                                 weights:(MLCTensor * _Nullable)weights
    NS_SWIFT_NAME(sigmoidCrossEntropy(reductionType:labelSmoothing:weights:));


/*! @abstract   Create a loss layer
    @param      reductionType         The reduction type to use
    @param      epsilon                       The epsilon parameter
    @param      weight                         A scalar floating-point value
    @return     A new log loss layer.
 */
+ (instancetype)logLossWithReductionType:(MLCReductionType)reductionType
                                 epsilon:(float)epsilon
                                  weight:(float)weight
    // NOTE: `NS_SWIFT_NAME` cannot be used here since `log` would be macro-expanded.
    __attribute__((swift_name("log(reductionType:epsilon:weight:)")));

/*! @abstract   Create a loss layer
    @param      reductionType          The reduction type to use
    @param      epsilon                       The epsilon parameter
    @param      weights                       The loss label weights tensor
    @return     A new log loss layer.
 */
+ (instancetype)logLossWithReductionType:(MLCReductionType)reductionType
                                 epsilon:(float)epsilon
                                 weights:(MLCTensor * _Nullable)weights
    // NOTE: `NS_SWIFT_NAME` cannot be used here since `log` would be macro-expanded.
    __attribute__((swift_name("log(reductionType:epsilon:weights:)")));

/*! @abstract   Create a loss layer
    @param      reductionType         The reduction type to use
    @param      delta                           The delta parameter
    @param      weight                         A scalar floating-point value
    @return     A new huber loss layer.
 */
+ (instancetype)huberLossWithReductionType:(MLCReductionType)reductionType
                                     delta:(float)delta
                                    weight:(float)weight
    NS_SWIFT_NAME(huberLoss(reductionType:delta:weight:));

/*! @abstract   Create a loss layer
    @param      reductionType          The reduction type to use
    @param      delta                            The delta parameter
    @param      weights                        The loss label weights tensor
    @return     A new huber loss layer.
 */
+ (instancetype)huberLossWithReductionType:(MLCReductionType)reductionType
                                     delta:(float)delta
                                   weights:(MLCTensor * _Nullable)weights
    NS_SWIFT_NAME(huberLoss(reductionType:delta:weights:));

/*! @abstract   Create a loss layer
    @param      reductionType         The reduction type to use
    @param      weight                         A scalar floating-point value
    @return     A new L1 i.e. mean absolute error loss layer.
 */
+ (instancetype)meanAbsoluteErrorLossWithReductionType:(MLCReductionType)reductionType
                                                weight:(float)weight
    NS_SWIFT_NAME(meanAbsoluteError(reductionType:weight:));

/*! @abstract   Create a loss layer
    @param      reductionType          The reduction type to use
    @param      weights                       The loss label weights tensor
    @return     A new L1 i.e. mean absolute error loss layer.
 */
+ (instancetype)meanAbsoluteErrorLossWithReductionType:(MLCReductionType)reductionType
                                               weights:(MLCTensor * _Nullable)weights
    NS_SWIFT_NAME(meanAbsoluteError(reductionType:weights:));


/*! @abstract   Create a loss layer
    @param      reductionType          The reduction type to use
    @param      weight                         A scalar floating-point value
    @return     A new L2 i.e. mean squared error loss layer.
 */
+ (instancetype)meanSquaredErrorLossWithReductionType:(MLCReductionType)reductionType
                                               weight:(float)weight
    NS_SWIFT_NAME(meanSquaredError(reductionType:weight:));

/*! @abstract   Create a loss layer
    @param      reductionType          The reduction type to use
    @param      weights                       The loss label weights tensor
    @return     A new L2 i.e. mean squared error loss layer.
 */
+ (instancetype)meanSquaredErrorLossWithReductionType:(MLCReductionType)reductionType
                                              weights:(MLCTensor * _Nullable)weights
    NS_SWIFT_NAME(meanSquaredError(reductionType:weights:));

/*! @abstract   Create a loss layer
    @param      reductionType         The reduction type to use
    @param      weight                         A scalar floating-point value
    @return     A new hinge loss layer.
 */
+ (instancetype)hingeLossWithReductionType:(MLCReductionType)reductionType
                                    weight:(float)weight
    NS_SWIFT_NAME(hingeLoss(reductionType:weight:));

/*! @abstract   Create a loss layer
    @param      reductionType          The reduction type to use
    @param      weights                       The loss label weights tensor
    @return     A new hinge loss layer.
 */
+ (instancetype)hingeLossWithReductionType:(MLCReductionType)reductionType
                                   weights:(MLCTensor * _Nullable)weights
    NS_SWIFT_NAME(hingeLoss(reductionType:weights:));

/*! @abstract   Create a loss layer
    @param      reductionType          The reduction type to use
    @param      weight                         A scalar floating-point value
    @return     A new cosine distance loss layer.
 */
+ (instancetype)cosineDistanceLossWithReductionType:(MLCReductionType)reductionType
                                          weight:(float)weight
    NS_SWIFT_NAME(cosineDistance(reductionType:weight:));

/*! @abstract   Create a loss layer
    @param      reductionType          The reduction type to use
    @param      weights                       The loss label weights tensor
    @return     A new cosine distance loss layer.
 */
+ (instancetype)cosineDistanceLossWithReductionType:(MLCReductionType)reductionType
                                         weights:(MLCTensor * _Nullable)weights
    NS_SWIFT_NAME(cosineDistance(reductionType:weights:));

@end

NS_ASSUME_NONNULL_END
