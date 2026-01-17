//
//  MPSNDArrayGradientState.h
//  MPS
//
//  Created on 1/3/19.
//  Copyright © 2019 Apple. All rights reserved.
//

#ifndef MPSNDArrayGradientState_h
#define MPSNDArrayGradientState_h

#include <MPSCore/MPSState.h>

@class MPSNDArrayMultiaryKernel;
@class MPSNDArrayMultiaryGradientKernel;

/*! @class  A state created to record a MPSCNNKernel properties
 *          at the time an -encode call was made. The contents are opaque.
 *
 *          Gradient states must be created with [MPSCNNKernel resultStateForSourceImage:sourceStates:destinationImage:]
 *          or analogous interfaces.
 */
MPS_CLASS_AVAILABLE_STARTING(macos(10.15), ios(13.0), macCatalyst(13.0), tvos(13.0))
@interface MPSNDArrayGradientState : MPSState

@end


#endif /* MPSNDArrayGradientState_h */
