//
//  MLCLossDescriptor.h
//  MLCompute
//
//  Copyright © 2019 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <MLCompute/MLCDefines.h>
#import <MLCompute/MLCTypes.h>

NS_ASSUME_NONNULL_BEGIN

/*! @class      MLCLossDescriptor
    @discussion The MLCLossDescriptor specifies a loss filter descriptor.
 */
MLCOMPUTE_CLASS_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))
@interface MLCLossDescriptor : NSObject <NSCopying>

/*! @property   lossType
    @abstract   Specifies the loss function.
 */
@property (readonly, nonatomic) MLCLossType lossType;

/*! @property   reductionType
    @abstract   The reduction operation performed by the loss function.
 */
@property (readonly, nonatomic) MLCReductionType reductionType;

/*! @property   weight
    @abstract   The scale factor to apply to each element of a result.  The default value is 1.0.
 */
@property (readonly, nonatomic) float weight;

/*! @property    labelSmoothing
    @abstract    The label smoothing parameter. The default value is 0.0.
    @discussion  This parameter is valid only for the loss functions of the following type(s):
                     MLCLossTypeSoftmaxCrossEntropy and MLCLossTypeSigmoidCrossEntropy.
 */
@property (readonly, nonatomic) float labelSmoothing;

/*! @property    numberOfClasses
    @abstract    The number of classes parameter. The default value is 1.
    @discussion  This parameter is valid only for the loss function MLCLossTypeSoftmaxCrossEntropy.
 */
@property (readonly, nonatomic) NSUInteger classCount;

/*! @property    epsilon
    @abstract    The epsilon parameter. The default value is 1e-7.
    @discussion  This parameter is valid only for the loss function MLCLossTypeLog.
 */
@property (readonly, nonatomic) float epsilon;

/*! @property    delta
    @abstract    The delta parameter. The default value is 1.0f.
    @discussion  This parameter is valid only for the loss function MLCLossTypeHuber.
 */
@property (readonly, nonatomic) float delta;

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/*! @abstract   Create a loss descriptor object
    @param      lossType        The loss function.
    @param      reductionType   The reduction operation
    @return     A new MLCLossDescriptor object
 */
+ (instancetype)descriptorWithType:(MLCLossType)lossType
                     reductionType:(MLCReductionType)reductionType;

/*! @abstract   Create a loss descriptor object
    @param      lossType        The loss function.
    @param      reductionType   The reduction operation
    @param      weight          The scale factor to apply to each element of a result.
    @return     A new MLCLossDescriptor object
 */
+ (instancetype)descriptorWithType:(MLCLossType)lossType
                     reductionType:(MLCReductionType)reductionType
                            weight:(float)weight;

/*! @abstract   Create a loss descriptor object
    @param      lossType           The loss function.
    @param      reductionType         The reduction operation
    @param      weight             The scale factor to apply to each element of a result.
    @param      labelSmoothing     The label smoothing parameter.
    @param      classCount         The number of classes parameter.
    @return     A new MLCLossDescriptor object
 */
+ (instancetype)descriptorWithType:(MLCLossType)lossType
                     reductionType:(MLCReductionType)reductionType
                            weight:(float)weight
                    labelSmoothing:(float)labelSmoothing
                        classCount:(NSUInteger)classCount;

/*! @abstract   Create a loss descriptor object
 @param      lossType            The loss function.
 @param      reductionType          The reduction operation
 @param      weight              The scale factor to apply to each element of a result.
 @param      labelSmoothing      The label smoothing parameter.
 @param      classCount          The number of classes parameter.
 @param      epsilon             The epsilon used by LogLoss
 @param      delta               The delta parameter used by Huber loss
 @return     A new MLCLossDescriptor object
 */
+ (instancetype)descriptorWithType:(MLCLossType)lossType
                     reductionType:(MLCReductionType)reductionType
                            weight:(float)weight
                    labelSmoothing:(float)labelSmoothing
                        classCount:(NSUInteger)classCount
                           epsilon:(float)epsilon
                             delta:(float)delta;

@end

NS_ASSUME_NONNULL_END
