//
//  MPSNNGradientState.h
//  MPSNeuralNetwork
//
//  Created by Ian Ollmann on 11/9/17.
//  Copyright © 2017 Apple. All rights reserved.
//

#ifndef MPSNNGradientState_h
#define MPSNNGradientState_h

#include <MPSCore/MPSState.h>

@class MPSCNNKernel;
@class MPSCNNBinaryKernel;

/*! @class  A state created to record a MPSCNNKernel properties
 *          at the time an -encode call was made. The contents are opaque.
 *
 *          Gradient states must be created with [MPSCNNKernel resultStateForSourceImage:sourceStates:destinationImage:]
 *          or analogous interfaces.
 */
MPS_CLASS_AVAILABLE_STARTING(macos(10.13.4), ios(11.3), tvos(11.3))
@interface MPSNNGradientState : MPSState

@end

typedef NSArray<MPSNNGradientState *>  MPSNNGradientStateBatch
    MPS_AVAILABLE_STARTING( macos(10.13.4), ios(11.3), tvos(11.3));

/*! @class  A state created to record MPSCNNBinaryKernel properties
 *          at the time an -encode call was made. The contents are opaque.
 *
 *          Gradient states must be created with [MPSCNNBinaryKernel resultStateForPrimaryImage:secondaryImage:sourceStates:destinationImage:]
 *          or analogous interfaces.
 */
MPS_CLASS_AVAILABLE_STARTING(macos(10.13.4), ios(11.3), tvos(11.3))
@interface MPSNNBinaryGradientState : MPSState

@end

typedef NSArray<MPSNNBinaryGradientState *>  MPSNNBinaryGradientStateBatch
    MPS_AVAILABLE_STARTING( macos(10.13.4), ios(11.3), tvos(11.3));

#endif /* MPSNNGradientState_h */
