//
//  MPSNNReshape.h
//  MPSNeuralNetwork
//
//  Created by Aaftab Munshi on 12/11/17.
//  Copyright © 2017 Apple. All rights reserved.
//

#ifndef MPSNNReshape_h
#define MPSNNReshape_h

#include <MPSNeuralNetwork/MPSCNNKernel.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  @class      MPSNNReshape
 *  @dependency This depends on Metal.framework
 *  @abstract   Describes a reshape operation
 *  @discussion This functions copies data from source MPSImage intot the new shape in the destination MPSImage
 *
 */

MPS_CLASS_AVAILABLE_STARTING(macos(10.13.4), ios(11.3), tvos(11.3))
@interface MPSNNReshape : MPSCNNKernel

/*!
 *  @abstract Initialize a MPSNNReshape kernel
 *  @param    device    The device the filter will run on
 *  @return   A valid MPSNNReshape object or nil, if failure.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device     NS_DESIGNATED_INITIALIZER;


-(nullable instancetype) initWithCoder:(NSCoder * __nonnull)aDecoder
                                device:(__nonnull id<MTLDevice>)device    NS_DESIGNATED_INITIALIZER;

@end  /* MPSNNReshape_h */


#ifdef __cplusplus
}
#endif

#endif /* MPSNNReshape_h */

