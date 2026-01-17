//
//  MPSFunctionConstantIndices.h
//  MPSCore
//
//  Created on 12/13/19.
//  Copyright © 2019 Apple. All rights reserved.
//

#ifndef MPSFunctionConstantIndices_h
#define MPSFunctionConstantIndices_h

#define MPSDeviceCapsIndex                             127                     // unavailable to user
#define MPSFunctionConstantIndex                       (MPSDeviceCapsIndex-1)  // unavailable to user
#define MPSBatchSizeIndex                              (MPSDeviceCapsIndex-2)  // unavailable to user
#define MPSUserConstantIndex                           (MPSDeviceCapsIndex-3)  // unavailable to user
#define MPSNDArrayConstantIndex                        (MPSDeviceCapsIndex-4)  // unavailable to user
#define MPSFunctionConstantIndexReserved               (MPSDeviceCapsIndex-5)  // unavailable to user
#define MPSTextureLinkingConstantIndex                 (MPSDeviceCapsIndex-6)  // unavailable to user
#define MPSNDArrayConstantMultiDestIndex               (MPSDeviceCapsIndex-7)  // unavailable to user
#define MPSNDArrayConstantMultiDestIndex0              (MPSDeviceCapsIndex-8)  // unavailable to user
#define MPSNDArrayConstantMultiDestIndex1              (MPSDeviceCapsIndex-9)  // unavailable to user
#define MPSNDArrayConstantMultiDestSrcAddressingIndex  (MPSDeviceCapsIndex-10)  // unavailable to user
#define MPSNDArrayConstantMultiDestDstAddressingIndex  (MPSDeviceCapsIndex-11)  // unavailable to user
#define MPSUserAvailableFunctionConstantStartIndex     (MPSDeviceCapsIndex-12)  // first index availble to user

#endif /* MPSFunctionConstantIndices_h */
