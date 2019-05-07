//
//  MPSCNNNormalization.h
//  MPS
//
//  Created by Ian Ollmann on 8/21/16.
//  Copyright © 2016 Apple. All rights reserved.
//

#ifndef MPSCNNNormalization_h
#define MPSCNNNormalization_h

#include <MPSNeuralNetwork/MPSCNNKernel.h>

#ifdef __cplusplus
extern "C" {
#endif


#pragma mark - SpatialNormalization

/*!
 *  @class MPSCNNSpatialNormalization
 *  @dependency This depends on Metal.framework
 *  @discussion Specifies the spatial normalization filter.
 *              The spatial normalization for a feature channel applies the filter over local regions which extend
 *              spatially, but are in separate feature channels (i.e., they have shape 1 x kernelWidth x kernelHeight).
 *              For each feature channel, the function computes the sum of squares of X inside each rectangle, N2(i,j).
 *              It then divides each element of X as follows:
 *                  Y(i,j) = X(i,j) / (delta + alpha/(kw*kh) * N2(i,j))^beta,
 *              where kw and kh are the kernelWidth and the kernelHeight.
 *              It is the end-users responsibility to ensure that the combination of the
 *              parameters delta and alpha does not result in a situation where the denominator
 *              becomes zero - in such situations the resulting pixel-value is undefined.
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.12), ios(10.0), tvos(10.0))
@interface MPSCNNSpatialNormalization : MPSCNNKernel

/*! @property   alpha
 *  @abstract   The value of alpha.  Default is 1.0. Must be non-negative.
 */
@property (readwrite, nonatomic) float   alpha;

/*! @property   beta
 *  @abstract   The value of beta.  Default is 5.0
 */
@property (readwrite, nonatomic) float   beta;

/*! @property   delta
 *  @abstract   The value of delta.  Default is 1.0
 */
@property (readwrite, nonatomic) float   delta;

/*!
 *  @abstract  Initialize a spatial normalization filter
 *  @param      device              The device the filter will run on
 *  @param      kernelWidth         The width of the kernel
 *  @param      kernelHeight        The height of the kernel
 *  @return     A valid MPSCNNSpatialNormalization object or nil, if failure.
 *
 *  NOTE:  For now, kernelWidth must be equal to kernelHeight
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                           kernelWidth: (NSUInteger) kernelWidth
                          kernelHeight: (NSUInteger) kernelHeight NS_DESIGNATED_INITIALIZER;

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
-(nullable instancetype) initWithCoder:(NSCoder * __nonnull)aDecoder
                                device:(nonnull id <MTLDevice>) device NS_DESIGNATED_INITIALIZER
                    MPS_AVAILABLE_STARTING(macos(10.13), ios(11.0), tvos(11.0));

/*
 * Use initWithDevice:kernelWidth:kernelHeight instead
 *  @abstract *** Unavailable
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device NS_UNAVAILABLE;

@end    /* MPSCNNSpatialNormalization */


/*!
 *  @class MPSCNNSpatialNormalizationGradient
 *  @dependency This depends on Metal.framework
 *  @discussion Specifies the spatial normalization gradient filter.
 *              The spatial normalization for a feature channel applies the filter over local regions which extend
 *              spatially, but are in separate feature channels (i.e., they have shape 1 x kernelWidth x kernelHeight).
 *              For each feature channel, the function computes the sum of squares of X inside each rectangle, N2(i,j).
 *              It then divides each element of X as follows:
 *                  Y(i,j) = X(i,j) / (delta + alpha/(kw*kh) * N2(i,j))^beta,
 *              where kw and kh are the kernelWidth and the kernelHeight.
 *              It is the end-users responsibility to ensure that the combination of the
 *              parameters delta and alpha does not result in a situation where the denominator
 *              becomes zero - in such situations the resulting pixel-value is undefined.
 *
 *              T(i,j) = (delta + alpha/(kw*kh) * N2(i,j))
 *              N      = kw * kh
 *
 *              OutputGradient:
 *                  dZ/dX(i,j) =  T(i,j)^(-beta) * ( dZ/dY(i,j) - (2*alpha*beta*X(i,j)/T(i,j)) * (sum_{l,k in L(i),K(j)} dZ/dY(l,k)*X(l,k)) )
 *              N is the kernel size. The window R(k) itself is defined as:
 *                  L(i) = [i-floor((kw-1)/2), i+floor(kw/2]
 *                  K(j) = [j-floor((kh-1)/2), j+floor(kh/2]
 *
 *              For correct gradient computation all parameters must be the same as the original normalization filter.
 */

MPS_CLASS_AVAILABLE_STARTING( macos(10.13.4), ios(11.3), tvos(11.3))
@interface MPSCNNSpatialNormalizationGradient : MPSCNNGradientKernel

/*! @property   alpha
 *  @abstract   The value of alpha.  Default is 1.0. Must be non-negative.
 */
@property (readwrite, nonatomic) float   alpha;

/*! @property   beta
 *  @abstract   The value of beta.  Default is 5.0
 */
@property (readwrite, nonatomic) float   beta;

/*! @property   delta
 *  @abstract   The value of delta.  Default is 1.0
 */
@property (readwrite, nonatomic) float   delta;

/*!
 *  @abstract  Initialize a spatial normalization filter
 *  @param      device              The device the filter will run on
 *  @param      kernelWidth         The width of the kernel
 *  @param      kernelHeight        The height of the kernel
 *  @return     A valid MPSCNNSpatialNormalization object or nil, if failure.
 *
 *  NOTE:  For now, kernelWidth must be equal to kernelHeight
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                           kernelWidth: (NSUInteger) kernelWidth
                          kernelHeight: (NSUInteger) kernelHeight NS_DESIGNATED_INITIALIZER;

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
-(nullable instancetype) initWithCoder:(NSCoder * __nonnull)aDecoder
                                device:(nonnull id <MTLDevice>) device NS_DESIGNATED_INITIALIZER;

@end    /* MPSCNNSpatialNormalizationGradient */


#pragma mark - LocalContrastNormalization


/*!
 *  @class MPSCNNLocalContrastNormalization
 *  @dependency This depends on Metal.framework
 *  @discussion Specifies the local contrast normalization filter.
 *              The local contrast normalization is quite similar to spatial normalization
 *              (see @ref MPSCNNSpatialNormalization) in that it applies the filter over local regions which extend
 *              spatially, but are in separate feature channels (i.e., they have shape 1 x kernelWidth x kernelHeight),
 *              but instead of dividing by the local "energy" of the feature, the denominator uses the local variance
 *              of the feature - effectively the mean value of the feature is subtracted from the signal.
 *              For each feature channel, the function computes the variance VAR(i,j) and
 *              mean M(i,j) of X(i,j) inside each rectangle around the spatial point (i,j).
 *
 *              Then the result is computed for each element of X as follows:
 *
 *                  Y(i,j) = pm + ps * ( X(i,j) - p0 * M(i,j)) / (delta + alpha * VAR(i,j))^beta,
 *
 *              where kw and kh are the kernelWidth and the kernelHeight and pm, ps and p0 are parameters that
 *              can be used to offset and scale the result in various ways. For example setting
 *              pm=0, ps=1, p0=1, delta=0, alpha=1.0 and beta=0.5 scales input data so that the result has
 *              unit variance and zero mean, provided that input variance is positive.
 *              It is the end-users responsibility to ensure that the combination of the
 *              parameters delta and alpha does not result in a situation where the denominator
 *              becomes zero - in such situations the resulting pixel-value is undefined. A good way to guard
 *              against tiny variances is to regulate the expression with a small value for delta, for example
 *              delta = 1/1024 = 0.0009765625.
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(10.0), tvos(10.0))
@interface MPSCNNLocalContrastNormalization : MPSCNNKernel

/*! @property   alpha
 *  @abstract   The value of alpha.  Default is 0.0
 *  @discussion The default value 0.0 is not recommended and is
 *              preserved for backwards compatibility. With alpha 0,
 *              it performs a local mean subtraction. The
 *              MPSCNNLocalContrastNormalizationNode used with
 *              the MPSNNGraph uses 1.0 as a default.
 */
@property (readwrite, nonatomic) float   alpha;

/*! @property   beta
 *  @abstract   The value of beta.  Default is 0.5
 */
@property (readwrite, nonatomic) float   beta;

/*! @property   delta
 *  @abstract   The value of delta.  Default is 1/1024
 */
@property (readwrite, nonatomic) float   delta;

/*! @property   p0
 *  @abstract   The value of p0.  Default is 1.0
 */
@property (readwrite, nonatomic) float   p0;

/*! @property   pm
 *  @abstract   The value of pm.  Default is 0.0
 */
@property (readwrite, nonatomic) float   pm;

/*! @property   ps
 *  @abstract   The value of ps.  Default is 1.0
 */
@property (readwrite, nonatomic) float   ps;


/*!
 *  @abstract  Initialize a local contrast normalization filter
 *  @param      device              The device the filter will run on
 *  @param      kernelWidth         The width of the kernel
 *  @param      kernelHeight        The height of the kernel
 *  @return     A valid MPSCNNLocalContrastNormalization object or nil, if failure.
 *
 *  NOTE:  For now, kernelWidth must be equal to kernelHeight
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                           kernelWidth: (NSUInteger) kernelWidth
                          kernelHeight: (NSUInteger) kernelHeight NS_DESIGNATED_INITIALIZER;

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
-(nullable instancetype) initWithCoder:(NSCoder * __nonnull)aDecoder
                                device:(nonnull id <MTLDevice>) device NS_DESIGNATED_INITIALIZER
                    MPS_AVAILABLE_STARTING(macos(10.13), ios(11.0), tvos(11.0));

/*
 * Use initWithDevice:kernelWidth:kernelHeight instead
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device NS_UNAVAILABLE;

@end    /* MPSCNNLocalContrastNormalization */


/*!
 *  @class MPSCNNLocalContrastNormalizationGradient
 *  @dependency This depends on Metal.framework
 *  @discussion Specifies the local contrast normalization gradient filter.
 *              The local contrast normalization is quite similar to spatial normalization
 *              (see @ref MPSCNNSpatialNormalization) in that it applies the filter over local regions which extend
 *              spatially, but are in separate feature channels (i.e., they have shape 1 x kernelWidth x kernelHeight),
 *              but instead of dividing by the local "energy" of the feature, the denominator uses the local variance
 *              of the feature - effectively the mean value of the feature is subtracted from the signal.
 *              For each feature channel, the function computes the variance VAR(i,j) and
 *              mean M(i,j) of X(i,j) inside each rectangle around the spatial point (i,j).
 *
 *              Then the result is computed for each element of X as follows:
 *
 *                  Y(i,j) = pm + ps * ( X(i,j) - p0 * M(i,j)) / (delta + alpha * VAR(i,j))^beta,
 *
 *              where kw and kh are the kernelWidth and the kernelHeight and pm, ps and p0 are parameters that
 *              can be used to offset and scale the result in various ways. For example setting
 *              pm=0, ps=1, p0=1, delta=0, alpha=1.0 and beta=0.5 scales input data so that the result has
 *              unit variance and zero mean, provided that input variance is positive.
 *              It is the end-users responsibility to ensure that the combination of the
 *              parameters delta and alpha does not result in a situation where the denominator
 *              becomes zero - in such situations the resulting pixel-value is undefined. A good way to guard
 *              against tiny variances is to regulate the expression with a small value for delta, for example
 *              delta = 1/1024 = 0.0009765625.
 *
 *              T(i,j) = (delta + alpha * VAR(i,j))
 *              N      = kw * kh
 *
 *              OutputGradient:
 *                  dZ/dX(i,j) =  ps * T(i,j)^(-beta) * ( dZ/dY(i,j) - (sum_{l,k in L(i),K(j)} dZ/dY(l,k) * (((p0/N) + (2*alpha*beta/N)*(X(k,l)-1)*(X(i,j)-M(i,j)*p0)/T(i,j)))) )
 *              N is the kernel size. The window L(i) and K(j) itself is defined as:
 *                  L(i) = [i-floor((kw-1)/2), i+floor(kw/2]
 *                  K(j) = [j-floor((kh-1)/2), j+floor(kh/2]
 *
 *              For correct gradient computation all parameters must be the same as the original normalization filter.
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13.4), ios(11.3), tvos(11.3))
@interface MPSCNNLocalContrastNormalizationGradient : MPSCNNGradientKernel

/*! @property   alpha
 *  @abstract   The value of alpha.  Default is 0.0
 *  @discussion The default value 0.0 is not recommended and is
 *              preserved for backwards compatibility. With alpha 0,
 *              it performs a local mean subtraction. The
 *              MPSCNNLocalContrastNormalizationNode used with
 *              the MPSNNGraph uses 1.0 as a default.
 */
@property (readwrite, nonatomic) float   alpha;

/*! @property   beta
 *  @abstract   The value of beta.  Default is 0.5
 */
@property (readwrite, nonatomic) float   beta;

/*! @property   delta
 *  @abstract   The value of delta.  Default is 1/1024
 */
@property (readwrite, nonatomic) float   delta;

/*! @property   p0
 *  @abstract   The value of p0.  Default is 1.0
 */
@property (readwrite, nonatomic) float   p0;

/*! @property   pm
 *  @abstract   The value of pm.  Default is 0.0
 */
@property (readwrite, nonatomic) float   pm;

/*! @property   ps
 *  @abstract   The value of ps.  Default is 1.0
 */
@property (readwrite, nonatomic) float   ps;

/*!
 *  @abstract  Initialize a local contrast normalization filter
 *  @param      device              The device the filter will run on
 *  @param      kernelWidth         The width of the kernel
 *  @param      kernelHeight        The height of the kernel
 *  @return     A valid MPSCNNLocalContrastNormalization object or nil, if failure.
 *
 *  NOTE:  For now, kernelWidth must be equal to kernelHeight
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                           kernelWidth: (NSUInteger) kernelWidth
                          kernelHeight: (NSUInteger) kernelHeight NS_DESIGNATED_INITIALIZER;

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
-(nullable instancetype) initWithCoder:(NSCoder * __nonnull)aDecoder
                                device:(nonnull id <MTLDevice>) device NS_DESIGNATED_INITIALIZER;


@end    /* MPSCNNLocalContrastNormalizationGradient */


#pragma mark - CrossChannelNormalization


/*!
 *  @class MPSCNNCrossChannelNormalization
 *  @dependency This depends on Metal.framework
 *  @discussion Specifies the normalization filter across feature channels.
 *               This normalization filter applies the filter to a local region across nearby feature channels,
 *              but with no spatial extent (i.e., they have shape kernelSize x 1 x 1).
 *              The normalized output is given by:
 *                  Y(i,j,k) = X(i,j,k) / L(i,j,k)^beta,
 *              where the normalizing factor is:
 *                  L(i,j,k) = delta + alpha/N * (sum_{q in Q(k)} X(i,j,q)^2, where
 *              N is the kernel size. The window Q(k) itself is defined as:
 *                  Q(k) = [max(0, k-floor(N/2)), min(D-1, k+floor((N-1)/2)], where
 *
 *              k is the feature channel index (running from 0 to D-1) and
 *              D is the number of feature channels, and alpha, beta and delta are paremeters.
 *              It is the end-users responsibility to ensure that the combination of the
 *              parameters delta and alpha does not result in a situation where the denominator
 *              becomes zero - in such situations the resulting pixel-value is undefined.
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(10.0), tvos(10.0))
@interface MPSCNNCrossChannelNormalization : MPSCNNKernel

/*! @property   alpha
 *  @abstract   The value of alpha.  Default is 1.0. Must be non-negative.
 */
@property (readwrite, nonatomic) float   alpha;

/*! @property   beta
 *  @abstract   The value of beta.  Default is 5.0
 */
@property (readwrite, nonatomic) float   beta;

/*! @property   delta
 *  @abstract   The value of delta.  Default is 1.0
 */
@property (readwrite, nonatomic) float   delta;

/*! @property   kernelSize
 *  @abstract   The size of the square filter window.  Default is 5
 */
@property(readonly, nonatomic) NSUInteger       kernelSize;

/*!
 *  @abstract  Initialize a local response normalization filter in a channel
 *  @param      device              The device the filter will run on
 *  @param      kernelSize          The kernel filter size in each dimension.
 *  @return     A valid MPSCNNCrossChannelNormalization object or nil, if failure.
 *
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                            kernelSize: (NSUInteger) kernelSize NS_DESIGNATED_INITIALIZER;


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
-(nullable instancetype) initWithCoder:(NSCoder * __nonnull)aDecoder
                                device:(nonnull id <MTLDevice>) device NS_DESIGNATED_INITIALIZER
                    MPS_AVAILABLE_STARTING(macos(10.13), ios(11.0), tvos(11.0));


/*
 * Use initWithDevice:kernelSize: instead
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device NS_UNAVAILABLE;


@end    /* MPSCNNCrossChannelNormalization */


/*!
 *  @class MPSCNNCrossChannelNormalizationGradient
 *  @dependency This depends on Metal.framework
 *  @discussion Specifies the normalization gradient filter across feature channels.
 *               This normalization filter applies the filter to a local region across nearby feature channels,
 *              but with no spatial extent (i.e., they have shape kernelSize x 1 x 1).
 *              The normalized output is given by:
 *                  Y(i,j,k) = X(i,j,k) / L(i,j,k)^beta,
 *              where the normalizing factor is:
 *                  L(i,j,k) = delta + alpha/N * (sum_{q in Q(k)} X(i,j,q)^2, where
 *              N is the kernel size. The window Q(k) itself is defined as:
 *                  Q(k) = [max(0, k-floor(N/2)), min(D-1, k+floor((N-1)/2)], where
 *
 *              k is the feature channel index (running from 0 to D-1) and
 *              D is the number of feature channels, and alpha, beta and delta are paremeters.
 *              It is the end-users responsibility to ensure that the combination of the
 *              parameters delta and alpha does not result in a situation where the denominator
 *              becomes zero - in such situations the resulting pixel-value is undefined.
 *
 *              OutputGradient:
 *                  dZ/dX(i,j,k) = dZ/dY(i,j,k) * (L(i,j,k)^-beta) - 2 * alpha * beta * X(i,j,k) * ( sum_{r in R(k)} dZ/dY(i,j,r) * X(i,j,r) * (L(i,j,r) ^ (-beta-1)) )
 *              N is the kernel size. The window L(i) and K(j) itself is defined as:
 *                  R(k) = [max(0, k-floor((N-1)/2)), min(D-1, k+floor(N/2)]
 *
 *              For correct gradient computation all parameters must be the same as the original normalization filter.
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13.4), ios(11.3), tvos(11.3))
@interface MPSCNNCrossChannelNormalizationGradient : MPSCNNGradientKernel

/*! @property   alpha
 *  @abstract   The value of alpha.  Default is 1.0. Must be non-negative.
 */
@property (readwrite, nonatomic) float   alpha;

/*! @property   beta
 *  @abstract   The value of beta.  Default is 5.0
 */
@property (readwrite, nonatomic) float   beta;

/*! @property   delta
 *  @abstract   The value of delta.  Default is 1.0
 */
@property (readwrite, nonatomic) float   delta;

/*! @property   kernelSize
 *  @abstract   The size of the square filter window.  Default is 5
 */
@property(readonly, nonatomic) NSUInteger       kernelSize;

/*!
 *  @abstract  Initialize a cross channel normalization gradient filter
 *  @param      device              The device the filter will run on
 *  @param      kernelSize          The kernel filter size in each dimension.
 *  @return     A valid MPSCNNCrossChannelNormalization object or nil, if failure.
 *
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                            kernelSize: (NSUInteger) kernelSize NS_DESIGNATED_INITIALIZER;

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
-(nullable instancetype) initWithCoder:(NSCoder * __nonnull)aDecoder
                                device:(nonnull id <MTLDevice>) device NS_DESIGNATED_INITIALIZER;

@end    /* MPSCNNCrossChannelNormalizationGradient */



#ifdef __cplusplus
}
#endif

    
#endif /* MPSCNNNormalization_h */
