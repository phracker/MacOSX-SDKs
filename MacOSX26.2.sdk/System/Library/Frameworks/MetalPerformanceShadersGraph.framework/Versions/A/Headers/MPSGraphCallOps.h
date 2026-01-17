//
//  MPSGraphCallOps.h
//  MPSGraph
//
//  Created by George Pawelczak on 7/26/23.
//  Copyright © 2023 Apple Inc. All rights reserved.
//

#ifndef MPSGraphCallOps_h
#define MPSGraphCallOps_h

#import <MetalPerformanceShadersGraph/MPSGraph.h>

NS_ASSUME_NONNULL_BEGIN

@interface MPSGraph(CallOp)

/// Creates an operation which invokes another executable.
///
/// - Parameters:
///   - symbolName: The unique identifier used to find the executable in the ``MPSGraphCompilationDescriptor.callables`` directory.
///   - inputTensors: The tensors which are passed as inputs to the executable being invoked.
///   - outputTypes: The expected return types of the executable being invoked.
///   - name: name of operation.
/// - Returns: An array of valid ``MPSGraphTensor`` objects representing the return tensors of the invoked executable.
-(NSArray<MPSGraphTensor *> *) callSymbolName:(NSString *) symbolName
                                 inputTensors:(NSArray<MPSGraphTensor *> *) inputTensors
                                  outputTypes:(NSArray<MPSGraphType *> *) outputTypes
                                         name:(NSString * _Nullable) name
MPS_SWIFT_NAME( call(symbolName:inputTensors:outputTypes:name:) )
MPS_AVAILABLE_STARTING(macos(15.0), ios(18.0), macCatalyst(18.0), tvos(18.0));

@end
NS_ASSUME_NONNULL_END

#endif /* MPSGraphCallOps_h */
