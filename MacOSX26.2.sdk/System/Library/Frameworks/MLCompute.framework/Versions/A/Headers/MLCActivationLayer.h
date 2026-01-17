//
//  MLCActivationLayer.h
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
@class MLCActivationDescriptor;

NS_ASSUME_NONNULL_BEGIN

MLCOMPUTE_AVAILABLE_STARTING_BUT_DEPRECATED_MACOS14(11.0, 14.0, 14.0)
@interface MLCActivationLayer : MLCLayer

/*! @property   descriptor
    @abstract   The activation descriptor
 */
@property (readonly, nonatomic, copy) MLCActivationDescriptor *descriptor;


/*! @abstract   Create an activation layer
    @param      descriptor     The activation descriptor
    @return     A new activation layer
 */
+ (instancetype)layerWithDescriptor:(MLCActivationDescriptor *)descriptor;

/*! @abstract   Create a ReLU activation layer
    @return     A new activation layer
 */
@property (nonatomic, class, readonly) MLCActivationLayer *reluLayer;

/*! @abstract   Create a ReLU6 activation layer
    @return     A new activation layer
 */
@property (nonatomic, class, readonly) MLCActivationLayer *relu6Layer;

/*! @abstract   Create a leaky ReLU activation layer
    @return     A new activation layer
 */
@property (nonatomic, class, readonly) MLCActivationLayer *leakyReLULayer;

/*! @abstract   Create a leaky ReLU activation layer
    @param      negativeSlope     Controls the angle of the negative slope
    @return     A new activation layer
 */
+ (instancetype)leakyReLULayerWithNegativeSlope:(float)negativeSlope
    NS_SWIFT_NAME(leakyReLU(negativeSlope:));

/*! @abstract   Create a linear activation layer
    @param      scale   The scale factor
    @param      bias     The bias value
    @return     A new activation layer
 */
+ (instancetype)linearLayerWithScale:(float)scale
                                bias:(float)bias
    NS_SWIFT_NAME(linear(scale:bias:));

/*! @abstract   Create a sigmoid activation layer
    @return     A new activation layer
 */
@property (nonatomic, class, readonly) MLCActivationLayer *sigmoidLayer;

/*! @abstract   Create a hard sigmoid activation layer
    @return     A new activation layer
 */
@property (nonatomic, class, readonly) MLCActivationLayer *hardSigmoidLayer;

/*! @abstract   Create a tanh activation layer
    @return     A new activation layer
 */
@property (nonatomic, class, readonly) MLCActivationLayer *tanhLayer;

/*! @abstract   Create an absolute activation layer
    @return     A new activation layer
 */
@property (nonatomic, class, readonly) MLCActivationLayer *absoluteLayer;

/*! @abstract   Create a soft plus activation layer
    @return     A new activation layer
 */
@property (nonatomic, class, readonly) MLCActivationLayer *softPlusLayer;

/*! @abstract   Create a soft plus activation layer
    @param      beta    The beta value for the softplus formation
    @return     A new activation layer
 */
+ (instancetype)softPlusLayerWithBeta:(float)beta
    NS_SWIFT_NAME(softPlus(beta:));

/*! @abstract   Create a soft sign activation layer
    @return     A new activation layer
 */
@property (nonatomic, class, readonly) MLCActivationLayer *softSignLayer;

/*! @abstract   Create an ELU activation layer
    @return     A new activation layer
 */
@property (nonatomic, class, readonly) MLCActivationLayer *eluLayer;

/*! @abstract   Create an ELU activation layer
    @param      a   The \p a value for the ELU formation
    @return     A new activation layer
 */
+ (instancetype)eluLayerWithA:(float)a
    NS_SWIFT_NAME(elu(a:));

/*! @abstract   Create a ReLUN activation layer
    @discussion This can be used to implement layers such as ReLU6 for example.
    @param      a   The \p a value
    @param      b   The \p b value
    @return     A new activation layer
 */
+ (instancetype)relunLayerWithA:(float)a b:(float)b
    NS_SWIFT_NAME(relun(a:b:));

/*! @abstract   Create a log sigmoid activation layer
    @return     A new activation layer
 */
@property (nonatomic, class, readonly) MLCActivationLayer *logSigmoidLayer;

/*! @abstract   Create a SELU activation layer
    @return     A new activation layer
 */
@property (nonatomic, class, readonly) MLCActivationLayer *seluLayer;

/*! @abstract   Create a CELU activation layer
    @return     A new activation layer
 */
@property (nonatomic, class, readonly) MLCActivationLayer *celuLayer;

/*! @abstract   Create a CELU activation layer
    @param      a   The \p a value for the CELU formation
    @return     A new activation layer
 */
+ (instancetype)celuLayerWithA:(float)a
    NS_SWIFT_NAME(celu(a:));

/*! @abstract   Create a hard shrink activation layer
    @return     A new activation layer
 */
@property (nonatomic, class, readonly) MLCActivationLayer *hardShrinkLayer;

/*! @abstract   Create a hard shrink activation layer
    @param      a   The \p a value for the hard shrink formation
    @return     A new activation layer
 */
+ (instancetype)hardShrinkLayerWithA:(float)a
   NS_SWIFT_NAME(hardShrink(a:));

/*! @abstract   Create a soft shrink activation layer
    @return     A new activation layer
 */
@property (nonatomic, class, readonly) MLCActivationLayer *softShrinkLayer;

/*! @abstract   Create a soft shrink activation layer
    @param      a   The \p a value for the soft shrink formation
    @return     A new activation layer
 */
+ (instancetype)softShrinkLayerWithA:(float)a
    NS_SWIFT_NAME(softShrink(a:));

/*! @abstract   Create a TanhShrink activation layer
    @return     A new activation layer
 */
@property (nonatomic, class, readonly) MLCActivationLayer *tanhShrinkLayer;

/*! @abstract   Create a threshold activation layer
    @param      threshold    The value to threshold at
    @param      replacement  The value to replace with
    @return     A new activation layer
 */
+ (instancetype)thresholdLayerWithThreshold:(float)threshold
                                replacement:(float)replacement
    NS_SWIFT_NAME(threshold(_:replacement:));

/*! @abstract   Create a GELU activation layer
    @return     A new activation layer
 */
@property (nonatomic, class, readonly) MLCActivationLayer *geluLayer;
/*! @abstract   Create a hardswish activation layer
    @return     A new activation layer
 */
@property (nonatomic, class, readonly) MLCActivationLayer *hardSwishLayer;

/*! @abstract   Create a clamp activation layer
    @param      minValue    The minimum range used by clamp
    @param      maxValue    The maximum range used by clamp
    @return     A new activation layer
 */
+ (instancetype)clampLayerWithMinValue:(float)minValue
                              maxValue:(float)maxValue
    NS_SWIFT_NAME(clamp(min:max:));


@end

NS_ASSUME_NONNULL_END
