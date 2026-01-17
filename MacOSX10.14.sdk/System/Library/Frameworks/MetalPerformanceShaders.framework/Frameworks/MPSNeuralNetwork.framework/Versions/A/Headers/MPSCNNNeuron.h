//
//  MPSCNNNeuron.h
//  MPS
//
//  Created by Anna Tikhonova on 10/27/17.
//  Copyright © 2017 Apple. All rights reserved.
//

#ifndef MPSCNNNeuron_h
#define MPSCNNNeuron_h

#import <MPSNeuralNetwork/MPSCNNKernel.h>
#import <MPSNeuralNetwork/MPSCNNNeuronType.h>

#ifdef __cplusplus
extern "C" {
#endif

    
#pragma mark -
#pragma mark MPSNNNeuronDescriptor
    
/*!
 *  @class      MPSNNNeuronDescriptor
 *  @dependency This depends on Metal.framework
 *  @discussion The MPSNNNeuronDescriptor specifies a neuron descriptor.
 *              Supported neuron types:
 *
 *              Neuron type "none": f(x) = x
 *              Parameters: none
 *
 *              ReLU neuron filter: f(x) = x >= 0 ? x : a * x
 *              This is called Leaky ReLU in literature. Some literature defines
 *              classical ReLU as max(0, x). If you want this behavior, simply pass a = 0.
 *              Parameters: a
 *              For default behavior, set the value of a to 0.0f.
 *
 *              Linear neuron filter: f(x) = a * x + b
 *              Parameters: a, b
 *              For default behavior, set the value of a to 1.0f and the value of b to 0.0f.
 *
 *              Sigmoid neuron filter: f(x) = 1 / (1 + e^-x)
 *              Parameters: none
 *
 *              Hard Sigmoid filter: f(x) = clamp((x * a) + b, 0, 1)
 *              Parameters: a, b
 *              For default behavior, set the value of a to 0.2f and the value of b to 0.5f.
 *
 *              Hyperbolic tangent (TanH) neuron filter: f(x) = a * tanh(b * x)
 *              Parameters: a, b
 *              For default behavior, set the value of a to 1.0f and the value of b to 1.0f.
 *
 *              Absolute neuron filter: f(x) = fabs(x)
 *              Parameters: none
 *
 *              Parametric Soft Plus neuron filter: f(x) = a * log(1 + e^(b * x))
 *              Parameters: a, b
 *              For default behavior, set the value of a to 1.0f and the value of b to 1.0f.
 *
 *              Parametric Soft Sign neuron filter: f(x) = x / (1 + abs(x))
 *              Parameters: none
 *
 *              Parametric ELU neuron filter: f(x) = x >= 0 ? x : a * (exp(x) - 1)
 *              Parameters: a
 *              For default behavior, set the value of a to 1.0f.
 *
 *              Parametric ReLU (PReLU) neuron filter: Same as ReLU, except parameter
 *              aArray is per channel.
 *              For each pixel, applies the following function: f(x_i) = x_i, if x_i >= 0
 *                                                                     = a_i * x_i if x_i < 0
 *              i in [0...channels-1]
 *              i.e. parameters a_i are learned and applied to each channel separately. Compare
 *              this to ReLu where parameter a is shared across all channels.
 *              See https://arxiv.org/pdf/1502.01852.pdf for details.
 *              Parameters: aArray - Array of floats containing per channel value of PReLu parameter
 *                          count - Number of float values in array aArray.
 *
 *              ReLUN neuron filter: f(x) = min((x >= 0 ? x : a * x), b)
 *              Parameters: a, b
 *              As an example, the TensorFlow Relu6 activation layer can be implemented
 *              by setting the parameter b to 6.0f:
 *              https://www.tensorflow.org/api_docs/cc/class/tensorflow/ops/relu6.
 *              For default behavior, set the value of a to 1.0f and the value of b to 6.0f.
 */
MPS_CLASS_AVAILABLE_STARTING(macos(10.13.4), ios(11.3), tvos(11.3))
@interface MPSNNNeuronDescriptor : NSObject <NSCopying>

@property (readwrite, nonatomic) MPSCNNNeuronType neuronType;
@property (readwrite, nonatomic) float a;
@property (readwrite, nonatomic) float b;
@property (readwrite, nonatomic) float c;
@property (readwrite, nonatomic, nullable, retain) NSData* data; /* Note: data is retained, not copied */

/*!
 * You must use one of the interfaces below instead.
 */
-(nonnull instancetype) init NS_UNAVAILABLE;

/*!
 *  @abstract  Make a descriptor for a MPSCNNNeuron object.
 *  @param     neuronType           The type of a neuron filter.
 *  @return    A valid MPSNNNeuronDescriptor object or nil, if failure.
 */
+(nonnull MPSNNNeuronDescriptor*) cnnNeuronDescriptorWithType: (MPSCNNNeuronType)neuronType;

/*!
 *  @abstract  Make a descriptor for a MPSCNNNeuron object.
 *  @param     neuronType           The type of a neuron filter.
 *  @param     a                    Parameter "a".
 *  @return    A valid MPSNNNeuronDescriptor object or nil, if failure.
 */
+(nonnull MPSNNNeuronDescriptor*) cnnNeuronDescriptorWithType: (MPSCNNNeuronType)neuronType
                                                            a: (float) a;

/*!
 *  @abstract  Initialize the neuron descriptor.
 *  @param     neuronType           The type of a neuron filter.
 *  @param     a                    Parameter "a".
 *  @param     b                    Parameter "b".
 *  @return    A valid MPSNNNeuronDescriptor object or nil, if failure.
 */
+(nonnull MPSNNNeuronDescriptor*) cnnNeuronDescriptorWithType: (MPSCNNNeuronType)neuronType
                                                            a: (float) a
                                                            b: (float) b;

/*!
 *  @abstract  Make a descriptor for a MPSCNNNeuron object.
 *  @param     neuronType           The type of a neuron filter.
 *  @param     a                    Parameter "a".
 *  @param     b                    Parameter "b".
 *  @param     c                    Parameter "c".
 *  @return    A valid MPSNNNeuronDescriptor object or nil, if failure.
 */
+(nonnull MPSNNNeuronDescriptor*) cnnNeuronDescriptorWithType: (MPSCNNNeuronType)neuronType
                                                            a: (float) a
                                                            b: (float) b
                                                            c: (float) c;

/*! @abstract   Make a descriptor for a neuron of type MPSCNNNeuronTypePReLU.
 *  @discussion The PReLU neuron is the same as a ReLU neuron, except parameter "a" is per feature channel.
 *  @param      data                A NSData containing a float array with the per feature channel value
 *                                  of PReLu parameter. The number of float values in this array usually
 *                                  corresponds to number of output channels in a convolution layer.
 *                                  The descriptor retains the NSData object.
 *  @param      noCopy              An optimization flag that tells us whether the NSData allocation is
 *                                  suitable for use directly with no copying of the data into internal
 *                                  storage. This allocation has to match the same restrictions as listed
 *                                  for the newBufferWithBytesNoCopy:length:options:deallocator: method of
 *                                  MTLBuffer.
 *  @return     A valid MPSNNNeuronDescriptor object for a neuron of type MPSCNNNeuronTypePReLU or nil, if failure */
+(nonnull MPSNNNeuronDescriptor*) cnnNeuronPReLUDescriptorWithData: (NSData* _Nonnull) data
                                                            noCopy: (bool) noCopy;

@end /* MPSNNNeuronDescriptor */

    
#pragma mark -
#pragma mark MPSCNNNeuron
    
/*!
 *  @class      MPSCNNNeuron
 *  @dependency This depends on Metal.framework
 *  @discussion This filter applies a neuron activation function.
 *              You must use one of the sub-classes of MPSCNNNeuron.
 *
 *  The following filter types are supported:
 *  MPSCNNNeuronTypeNone            ///< f(x) = x
 *  MPSCNNNeuronTypeLinear          ///< f(x) = a * x + b
 *  MPSCNNNeuronTypeReLU            ///< f(x) = x >= 0 ? x : a * x
 *  MPSCNNNeuronTypeSigmoid         ///< f(x) = 1 / (1 + e^-x)
 *  MPSCNNNeuronTypeHardSigmoid     ///< f(x) = clamp((x * a) + b, 0, 1)
 *  MPSCNNNeuronTypeTanH            ///< f(x) = a * tanh(b * x)
 *  MPSCNNNeuronTypeAbsolute        ///< f(x) = fabs(x)
 *  MPSCNNNeuronTypeSoftPlus        ///< f(x) = a * log(1 + e^(b * x))
 *  MPSCNNNeuronTypeSoftSign        ///< f(x) = x / (1 + abs(x))
 *  MPSCNNNeuronTypeELU             ///< f(x) = x >= 0 ? x : a * (exp(x) - 1)
 *  MPSCNNNeuronTypePReLU           ///< Same as ReLU except parameter a is per channel
 *  MPSCNNNeuronTypeReLUN           ///< f(x) = min((x >= 0 ? x : a * x), b)
 *  MPSCNNNeuronTypePower           ///< f(x) = (a * x + b) ^ c
 *  MPSCNNNeuronTypeExponential     ///< f(x) = c ^ (a * x + b)
 *  MPSCNNNeuronTypeLogarithm       ///< f(x) = log_c(a * x + b)
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(10.0), tvos(10.0))
@interface  MPSCNNNeuron : MPSCNNKernel

@property (readonly, nonatomic) MPSCNNNeuronType neuronType MPS_AVAILABLE_STARTING(macos(10.13), ios(11.0), tvos(11.0));
@property (readonly, nonatomic) float a;
@property (readonly, nonatomic) float b;
@property (readonly, nonatomic) float c;
@property (readonly, nonatomic, retain, nullable) NSData* data MPS_AVAILABLE_STARTING(macos(10.13), ios(11.0), tvos(11.0));

/*
 * You must use initWithDevice:neuronDescriptor or use one of the sub-classes of MPSCNNNeuron instead.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device NS_UNAVAILABLE;

/*!
 *  @abstract  Initialize the neuron filter with a neuron descriptor.
 *  @param     device                   The device the filter will run on.
 *  @param     neuronDescriptor         The neuron descriptor.
 *                                      For the neuron of type MPSCNNNeuronTypePReLU, the neuron
 *                                      descriptor references an NSData object containing a float array
 *                                      with the per feature channel value of PReLu parameter and, in this
 *                                      case, the MPSCNNNeuron retains the NSData object.
 *  @return    A valid MPSCNNNeuron object or nil, if failure.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                      neuronDescriptor: (MPSNNNeuronDescriptor* _Nonnull) neuronDescriptor NS_DESIGNATED_INITIALIZER
MPS_AVAILABLE_STARTING(macos(10.13.4), ios(11.3), tvos(11.3));

/*! @abstract NSSecureCoding compatability
 *  @discussion While the standard NSSecureCoding/NSCoding method
 *              -initWithCoder: should work, since the file can't
 *              know which device your data is allocated on, we
 *              have to guess and may guess incorrectly.  To avoid
 *              that problem, use initWithCoder:device instead.
 *  @param      aDecoder    The NSCoder subclass with your serialized MPSKernel
 *  @param      device      The MTLDevice on which to make the MPSKernel
 *  @return     A new MPSKernel object, or nil if failure.
 */
-(nullable instancetype) initWithCoder:(NSCoder * __nonnull) aDecoder
                                device:(nonnull id <MTLDevice>) device NS_DESIGNATED_INITIALIZER;

@end    /* MPSCNNNeuron */
    
    
#pragma mark -
#pragma mark MPSCNNNeuronGradient

/*!
 *  @class      MPSCNNNeuronGradient
 *  @dependency This depends on Metal.framework
 *  @discussion This filter is a backward filter for the neuron activation function filter.
 *
 *  The following filter types are supported:
 *  MPSCNNNeuronTypeNone            ///< df/dx = 1
 *  MPSCNNNeuronTypeLinear          ///< df/dx = a
 *  MPSCNNNeuronTypeReLU            ///< df/dx = [ 1, if x >= 0
 *                                               [ a, if x <  0
 *  MPSCNNNeuronTypeSigmoid         ///< df/dx = e^x / (e^x + 1)^2
 *  MPSCNNNeuronTypeHardSigmoid     ///< df/dx = [ a, if (x >= 0) and (x <= 1)
 *                                               [ 0, otherwise
 *  MPSCNNNeuronTypeTanH            ///< df/dx = a * b * (1 - tanh^2(b * x))
 *  MPSCNNNeuronTypeAbsolute        ///< df/dx = sign(x)
 *  MPSCNNNeuronTypeSoftPlus        ///< df/dx = (a * b * exp(b * x)) / (exp(b * x) + 1)
 *  MPSCNNNeuronTypeSoftSign        ///< df/dx = 1 / (|x| + 1)^2
 *  MPSCNNNeuronTypeELU             ///< df/dx = [ a * exp(x), x <  0
 *                                               [          1, x >= 0
 *  MPSCNNNeuronTypePReLU           ///< df/dx = [  1, if x >= 0
 *                                               [ aV, if x <  0
 *  MPSCNNNeuronTypeReLUN           ///< df/dx = [ 1, if x >= 0
 *                                               [ a, if x <  0
 *                                               [ b, if x >= b
 *  MPSCNNNeuronTypePower           ///< df/dx = a * c * (a * x + b)^(c - 1)
 *  MPSCNNNeuronTypeExponential     ///< df/dx = [         a * exp(a * x + b), if c == -1
 *                                               [ a * log(c) * c^(a * x + b), if c != -1
 *  MPSCNNNeuronTypeLogarithm       ///< df/dx = [            a / (a * in + b), if c == -1
 *                                               [ a / (log(c) * (a * in + b)), if c != -1
 *
 * The result of the above operation is multiplied with the gradient, computed
 * by the preceeding filter (going backwards).
 */
MPS_CLASS_AVAILABLE_STARTING(macos(10.13.4), ios(11.3), tvos(11.3))
@interface MPSCNNNeuronGradient : MPSCNNGradientKernel

@property (readonly, nonatomic) MPSCNNNeuronType neuronType;
@property (readonly, nonatomic) float a;
@property (readonly, nonatomic) float b;
@property (readonly, nonatomic) float c;
@property (readonly, nonatomic, retain, nullable) NSData* data;

/*
 * You must use initWithDevice:neuronDescriptor or use one of the sub-classes of MPSCNNNeuronGradient instead.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device NS_UNAVAILABLE;

/*!
 *  @abstract  Initialize the neuron gradient filter with a neuron descriptor.
 *  @param     device                   The device the filter will run on.
 *  @param     neuronDescriptor         The neuron descriptor.
 *                                      For the neuron of type MPSCNNNeuronTypePReLU, the neuron
 *                                      descriptor references an NSData object containing a float array
 *                                      with the per feature channel value of PReLu parameter and, in this
 *                                      case, the MPSCNNNeuronGradient retains the NSData object.
 *  @return    A valid MPSCNNNeuronGradient object or nil, if failure.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                      neuronDescriptor: (MPSNNNeuronDescriptor* _Nonnull) neuronDescriptor NS_DESIGNATED_INITIALIZER
MPS_AVAILABLE_STARTING(macos(10.13), ios(11.0), tvos(11.0));

/*! @abstract NSSecureCoding compatability
 *  @discussion While the standard NSSecureCoding/NSCoding method
 *              -initWithCoder: should work, since the file can't
 *              know which device your data is allocated on, we
 *              have to guess and may guess incorrectly.  To avoid
 *              that problem, use initWithCoder:device instead.
 *  @param      aDecoder    The NSCoder subclass with your serialized MPSKernel
 *  @param      device      The MTLDevice on which to make the MPSKernel
 *  @return     A new MPSKernel object, or nil if failure.
 */
-(nullable instancetype) initWithCoder:(NSCoder * __nonnull) aDecoder
                                device:(nonnull id <MTLDevice>) device NS_DESIGNATED_INITIALIZER;

@end /* MPSCNNNeuronGradient */


#pragma mark -
#pragma mark Specific MPSCNNNeuron filters

/*!
 *  @class      MPSCNNNeuronLinear
 *  @dependency This depends on Metal.framework
 *  @discussion Specifies the linear neuron filter. For each pixel, applies the following function: f(x) = a * x + b
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(10.0), tvos(10.0))
@interface  MPSCNNNeuronLinear : MPSCNNNeuron

/*!
 *  @abstract  Initialize the linear neuron filter
 *  @param     device   The device the filter will run on
 *  @param     a        Filter property "a". See class discussion.
 *  @param     b        Filter property "b". See class discussion.
 *  @return    A valid MPSCNNNeuronLinear object or nil, if failure.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                                     a: (float) a
                                     b: (float) b NS_DESIGNATED_INITIALIZER
                MPS_AVAILABLE_STARTING_BUT_DEPRECATED(  "Please use MPSCNNNeuron initWithDevice:neuronDescriptor.",
                                                      macos(10.13, 10.14), ios(10.0, 12.0), tvos(10.0, 12.0));

/*
 * You must use initWithDevice:a:b instead
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device NS_UNAVAILABLE;

@end    /* MPSCNNNeuronLinear */
    
    
/*!
 *  @class MPSCNNNeuronReLU
 *  @dependency This depends on Metal.framework
 *  @discussion Specifies the ReLU neuron filter.
 *              For each pixel, applies the following function: f(x) = x, if x >= 0
 *                                                                   = a * x if x < 0
 *              This is called Leaky ReLU in literature. Some literature defines
 *              classical ReLU as max(0, x). If you want this behavior, simply pass a = 0
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(10.0), tvos(10.0))
@interface  MPSCNNNeuronReLU : MPSCNNNeuron

/*!
 *  @abstract  Initialize the ReLU neuron filter
 *  @param     device           The device the filter will run on
 *  @param     a                Filter property "a". See class discussion.
 *  @return    A valid MPSCNNNeuronReLU object or nil, if failure.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                                     a: (float) a NS_DESIGNATED_INITIALIZER
    MPS_AVAILABLE_STARTING_BUT_DEPRECATED(  "Please use MPSCNNNeuron initWithDevice:neuronDescriptor.",
                                      macos(10.13, 10.14), ios(10.0, 12.0), tvos(10.0, 12.0));


/*
 * Use initWithDevice:a: instead
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device NS_UNAVAILABLE;

@end    /* MPSCNNNeuronReLU */
    
/*!
 *  @class MPSCNNNeuronPReLU
 *  @dependency This depends on Metal.framework
 *  @discussion Specifies the parametric ReLU neuron filter.
 *              For each pixel, applies the following function: f(x_i) = x_i, if x_i >= 0
 *                                                                     = a_i * x_i if x_i < 0
 *              i in [0...channels-1]
 *              i.e. parameters a_i are learned and applied to each channel separately. Compare
 *              this to ReLu where parameter a is shared across all channels.
 *              See https://arxiv.org/pdf/1502.01852.pdf for details.
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(11.0), tvos(11.0))
@interface  MPSCNNNeuronPReLU : MPSCNNNeuron

/*!
 *  @abstract  Initialize the PReLU neuron filter
 *  @param     device           The device the filter will run on
 *  @param     a                Array of floats containing per channel value of PReLu parameter
 *  @param     count            Number of float values in array a.
 *                              This usually corresponds to number of output channels in convolution layer
 *  @return    A valid MPSCNNNeuronPReLU object or nil, if failure.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                                     a: (const float* _Nonnull) a
                                 count: (NSUInteger) count NS_DESIGNATED_INITIALIZER
            MPS_AVAILABLE_STARTING_BUT_DEPRECATED(  "Please use MPSCNNNeuron initWithDevice:neuronDescriptor.",
                                      macos(10.13, 10.14), ios(10.0, 12.0), tvos(10.0, 12.0));


/*
 * Use initWithDevice:a: instead
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device NS_UNAVAILABLE;

@end    /* MPSCNNNeuronPReLU */
    
    
/*!
 *  @class MPSCNNNeuronSigmoid
 *  @dependency This depends on Metal.framework
 *  @discussion Specifies the sigmoid neuron filter.  For each pixel, applies the following function: f(x) = 1 / (1 + e^-x)
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(10.0), tvos(10.0))
@interface  MPSCNNNeuronSigmoid : MPSCNNNeuron

/*!
 *  @abstract  Initialize a neuron filter
 *  @param      device          The device the filter will run on
 *  @return     A valid MPSCNNNeuronSigmoid object or nil, if failure.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device NS_DESIGNATED_INITIALIZER
                MPS_AVAILABLE_STARTING_BUT_DEPRECATED(  "Please use MPSCNNNeuron initWithDevice:neuronDescriptor.",
                                      macos(10.13, 10.14), ios(10.0, 12.0), tvos(10.0, 12.0));


@end    /* MPSCNNNeuronSigmoid */
    
    
/*!
 *  @class MPSCNNNeuronHardSigmoid
 *  @dependency This depends on Metal.framework
 *  @discussion Specifies the hard sigmoid neuron filter.  For each pixel, applies the following function: f(x) = clamp((a * x) + b, 0, 1)
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(11.0), tvos(11.0))
@interface  MPSCNNNeuronHardSigmoid : MPSCNNNeuron

/*!
 *  @abstract  Initialize a neuron filter
 *  @param     device           The device the filter will run on
 *  @param     a                Filter property "a". See class discussion.
 *  @param     b                Filter property "b". See class discussion.
 *  @return    A valid MPSCNNNeuronHardSigmoid object or nil, if failure.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                                     a: (float) a
                                     b: (float) b NS_DESIGNATED_INITIALIZER
                MPS_AVAILABLE_STARTING_BUT_DEPRECATED(  "Please use MPSCNNNeuron initWithDevice:neuronDescriptor.",
                                      macos(10.13, 10.14), ios(10.0, 12.0), tvos(10.0, 12.0));

/*
 * Use initWithDevice:a:b: instead
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device NS_UNAVAILABLE;

@end    /* MPSCNNNeuronHardSigmoid */
    
    
/*!
 *  @class MPSCNNNeuronTanH
 *  @dependency This depends on Metal.framework
 *  @discussion Specifies the hyperbolic tangent neuron filter.
 *              For each pixel, applies the following function: f(x) = a * tanh(b * x)
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(10.0), tvos(10.0))
@interface  MPSCNNNeuronTanH : MPSCNNNeuron

/*!
 *  @abstract  Initialize the hyperbolic tangent neuron filter
 *  @param     device           The device the filter will run on
 *  @param     a                Filter property "a". See class discussion.
 *  @param     b                Filter property "b". See class discussion.
 *  @return    A valid MPSCNNNeuronTanH object or nil, if failure.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                                     a: (float) a
                                     b: (float) b NS_DESIGNATED_INITIALIZER
            MPS_AVAILABLE_STARTING_BUT_DEPRECATED(  "Please use MPSCNNNeuron initWithDevice:neuronDescriptor.",
                                      macos(10.13, 10.14), ios(10.0, 12.0), tvos(10.0, 12.0));

/*
 * Use initWithDevice:a:b: instead
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device NS_UNAVAILABLE;

@end    /* MPSCNNNeuronTanH */


/*!
 *  @class MPSCNNNeuronAbsolute
 *  @dependency This depends on Metal.framework
 *  @discussion Specifies the absolute neuron filter.  For each pixel, applies the following function: f(x) = | x |
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(10.0), tvos(10.0))
@interface  MPSCNNNeuronAbsolute : MPSCNNNeuron

/*!
 *  @abstract  Initialize a neuron filter
 *  @param      device          The device the filter will run on
 *  @return     A valid MPSCNNNeuronAbsolute object or nil, if failure.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device NS_DESIGNATED_INITIALIZER
            MPS_AVAILABLE_STARTING_BUT_DEPRECATED(  "Please use MPSCNNNeuron initWithDevice:neuronDescriptor.",
                                      macos(10.13, 10.14), ios(10.0, 12.0), tvos(10.0, 12.0));


@end    /* MPSCNNNeuronAbsolute */
    
    
/*!
 *  @class MPSCNNNeuronSoftPlus
 *  @dependency This depends on Metal.framework
 *  @discussion Specifies the parametric softplus neuron filter.
 *              For each pixel, applies the following function: f(x) = a * log(1 + e^(b * x))
 */
MPS_CLASS_AVAILABLE_STARTING(macos(10.13), ios(11.0), tvos(11.0))
@interface  MPSCNNNeuronSoftPlus : MPSCNNNeuron

/*!
 *  @abstract   Initialize a parametric softplus neuron filter
 *  @param      device          The device the filter will run on
 *  @param      a               Filter property "a". See class discussion.
 *  @param      b               Filter property "b". See class discussion.
 *  @return     A valid MPSCNNNeuronSoftPlus object or nil, if failure.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                                     a: (float) a
                                     b: (float) b NS_DESIGNATED_INITIALIZER
        MPS_AVAILABLE_STARTING_BUT_DEPRECATED(  "Please use MPSCNNNeuron initWithDevice:neuronDescriptor.",
                                      macos(10.13, 10.14), ios(10.0, 12.0), tvos(10.0, 12.0));

/*
 * Use initWithDevice:a:b: instead
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device NS_UNAVAILABLE;

@end    /* MPSCNNNeuronSoftPlus */
    
    
/*!
 *  @class MPSCNNNeuronSoftSign
 *  @dependency This depends on Metal.framework
 *  @discussion Specifies the softsign neuron filter.
 *              For each pixel, applies the following function: f(x) = x / (1 + abs(x))
 */
MPS_CLASS_AVAILABLE_STARTING(macos(10.13), ios(11.0), tvos(11.0))
@interface  MPSCNNNeuronSoftSign : MPSCNNNeuron

/*!
 *  @abstract   Initialize a softsign neuron filter
 *  @param      device          The device the filter will run on
 *  @return     A valid MPSCNNNeuronSoftSign object or nil, if failure.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device NS_DESIGNATED_INITIALIZER
        MPS_AVAILABLE_STARTING_BUT_DEPRECATED(  "Please use MPSCNNNeuron initWithDevice:neuronDescriptor.",
                                      macos(10.13, 10.14), ios(10.0, 12.0), tvos(10.0, 12.0));


@end    /* MPSCNNNeuronSoftSign */
    
    
/*!
 *  @class MPSCNNNeuronELU
 *  @dependency This depends on Metal.framework
 *  @discussion Specifies the parametric ELU neuron filter.
 *              For each pixel, applies the following function: f(x) = [ a * (exp(x) - 1), x <  0
 *                                                                     [ x               , x >= 0
 */
MPS_CLASS_AVAILABLE_STARTING(macos(10.13), ios(11.0), tvos(11.0))
@interface  MPSCNNNeuronELU : MPSCNNNeuron

/*!
 *  @abstract   Initialize a parametric ELU neuron filter
 *  @param      device          The device the filter will run on
 *  @param      a               Filter property "a". See class discussion.
 *  @return     A valid MPSCNNNeuronELU object or nil, if failure.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                                     a: (float) a NS_DESIGNATED_INITIALIZER
    MPS_AVAILABLE_STARTING_BUT_DEPRECATED(  "Please use MPSCNNNeuron initWithDevice:neuronDescriptor.",
                                      macos(10.13, 10.14), ios(10.0, 12.0), tvos(10.0, 12.0));

/*
 * Use initWithDevice:a: instead
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device NS_UNAVAILABLE;

@end    /* MPSCNNNeuronELU */
    
    
/*!
 *  @class MPSCNNNeuronReLUN
 *  @dependency This depends on Metal.framework
 *  @discussion Specifies the ReLUN neuron filter.
 *              For each pixel, applies the following function: f(x) = [ x    , x >= 0
 *                                                                     [ a * x, x <  0
 *                                                                     [ b    , x >= b
 *              As an example, the TensorFlow Relu6 activation layer can be implemented
 *              by setting the parameter b to 6.0f:
 *              https://www.tensorflow.org/api_docs/cc/class/tensorflow/ops/relu6.
 *
 */
MPS_CLASS_AVAILABLE_STARTING(macos(10.13), ios(11.0), tvos(11.0))
@interface  MPSCNNNeuronReLUN : MPSCNNNeuron

/*!
 *  @abstract   Initialize a ReLUN neuron filter
 *  @param      device          The device the filter will run on
 *  @param      a               Filter property "a". See class discussion.
 *  @param      b               Filter property "b". See class discussion.
 *  @return     A valid MPSCNNNeuronReLUN object or nil, if failure.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                                     a: (float) a
                                     b: (float) b NS_DESIGNATED_INITIALIZER
        MPS_AVAILABLE_STARTING_BUT_DEPRECATED(  "Please use MPSCNNNeuron initWithDevice:neuronDescriptor.",
                                      macos(10.13, 10.14), ios(10.0, 12.0), tvos(10.0, 12.0));

/*
 * Use initWithDevice:a: instead
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device NS_UNAVAILABLE;

@end    /* MPSCNNNeuronReLUN */


/*!
 *  @class MPSCNNNeuronPower
 *  @dependency This depends on Metal.framework.
 *  @discussion Specifies the Power neuron filter.
 *              For each pixel, applies the following function: f(x) = (a * x + b) ^ c.
 *
 */
MPS_CLASS_AVAILABLE_STARTING(macos(10.13.4), ios(11.3), tvos(11.3))
@interface  MPSCNNNeuronPower : MPSCNNNeuron

/*!
 *  @abstract   Initialize a Power neuron filter.
 *  @param      device          The device the filter will run on.
 *  @param      a               Filter property "a". See class discussion.
 *  @param      b               Filter property "b". See class discussion.
 *  @param      c               Filter property "c". See class discussion.
 *  @return     A valid MPSCNNNeuronPower object or nil, if failure.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                                     a: (float) a
                                     b: (float) b
                                     c: (float) c NS_DESIGNATED_INITIALIZER
    MPS_AVAILABLE_STARTING_BUT_DEPRECATED(  "Please use MPSCNNNeuron initWithDevice:neuronDescriptor.",
                                      macos(10.13, 10.14), ios(10.0, 12.0), tvos(10.0, 12.0));

/*
 * Use initWithDevice:a:b:c instead
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device NS_UNAVAILABLE;

@end    /* MPSCNNNeuronPower */


/*!
 *  @class MPSCNNNeuronExponential
 *  @dependency This depends on Metal.framework.
 *  @discussion Specifies the Exponential neuron filter.
 *              For each pixel, applies the following function: f(x) = c ^ (a * x + b).
 *
 *              If the value of c is -1.0f, the base (c) is set to e.
 */
MPS_CLASS_AVAILABLE_STARTING(macos(10.13.4), ios(11.3), tvos(11.3))
@interface  MPSCNNNeuronExponential : MPSCNNNeuron

/*!
 *  @abstract   Initialize a Exponential neuron filter.
 *  @param      device          The device the filter will run on.
 *  @param      a               Filter property "a". See class discussion.
 *  @param      b               Filter property "b". See class discussion.
 *  @param      c               Filter property "c". See class discussion.
 *  @return     A valid MPSCNNNeuronExponential object or nil, if failure.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                                     a: (float) a
                                     b: (float) b
                                     c: (float) c NS_DESIGNATED_INITIALIZER
    MPS_AVAILABLE_STARTING_BUT_DEPRECATED(  "Please use MPSCNNNeuron initWithDevice:neuronDescriptor.",
                                      macos(10.13, 10.14), ios(10.0, 12.0), tvos(10.0, 12.0));

/*
 * Use initWithDevice:a:b:c instead
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device NS_UNAVAILABLE;

@end    /* MPSCNNNeuronExponential */


/*!
 *  @class MPSCNNNeuronLogarithm
 *  @dependency This depends on Metal.framework.
 *  @discussion Specifies the Logarithm neuron filter.
 *              For each pixel, applies the following function: f(x) = log_c(a * x + b).
 *
 *              If the value of c is -1.0f, the base (c) is set to e.
 */
MPS_CLASS_AVAILABLE_STARTING(macos(10.13.4), ios(11.3), tvos(11.3))
@interface  MPSCNNNeuronLogarithm : MPSCNNNeuron

/*!
 *  @abstract   Initialize a Logarithm neuron filter.
 *  @param      device          The device the filter will run on.
 *  @param      a               Filter property "a". See class discussion.
 *  @param      b               Filter property "b". See class discussion.
 *  @param      c               Filter property "c". See class discussion.
 *  @return     A valid MPSCNNNeuronLogarithm object or nil, if failure.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                                     a: (float) a
                                     b: (float) b
                                     c: (float) c NS_DESIGNATED_INITIALIZER
    MPS_AVAILABLE_STARTING_BUT_DEPRECATED(  "Please use MPSCNNNeuron initWithDevice:neuronDescriptor.",
                                      macos(10.13, 10.14), ios(10.0, 12.0), tvos(10.0, 12.0));

/*
 * Use initWithDevice:a:b:c instead
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device NS_UNAVAILABLE;

@end    /* MPSCNNNeuronLogarithm */


#ifdef __cplusplus
}
#endif

#endif /* MPSCNNNeuron_h */
