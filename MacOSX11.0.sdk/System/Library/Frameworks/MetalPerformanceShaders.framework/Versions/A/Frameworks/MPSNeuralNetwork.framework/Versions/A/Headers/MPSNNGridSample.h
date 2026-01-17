//
//  MPSNNGridSample.h
//  MPSNeuralNetwork
//
//  Created on 12/03/18.
//  Copyright © 2018 Apple. All rights reserved.
//

#ifndef MPSNNGridSamplePrivate_h
#define MPSNNGridSamplePrivate_h

#include <MPSNeuralNetwork/MPSCNNKernel.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  @class      MPSNNGridSample
 *  @dependency This depends on Metal.framework
 *  @abstract   Given an input and a flow-field grid, computes the output using input values and pixel locations from the grid.
 *  @discussion More details at https://pytorch.org/docs/stable/nn.html#grid-sample.
 *
 */

MPS_CLASS_AVAILABLE_STARTING( macos(10.15), ios(13.0), macCatalyst(13.0), tvos(13.0))
@interface MPSNNGridSample : MPSCNNBinaryKernel


/*! @property   useGridValueAsInputCoordinate
 *  @abstract   This determines whether the pixel locations from the grid are used as the input coordinate (if set to YES) or
 *              is added to the input coordinate (if set to NO).
 *              The default value is YES.
 */
@property(readwrite, nonatomic) BOOL    useGridValueAsInputCoordinate;

/*!
 *  @abstract Create a grid sample kernel.
 *  @param    device            The device the filter will run on
 *  @return     A valid MPSNNGridSample object or nil, if failure.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device NS_DESIGNATED_INITIALIZER;

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

@end  /* MPSNNGridSample */

#ifdef __cplusplus
}
#endif

#endif /* MPSNNGridSample_h */

