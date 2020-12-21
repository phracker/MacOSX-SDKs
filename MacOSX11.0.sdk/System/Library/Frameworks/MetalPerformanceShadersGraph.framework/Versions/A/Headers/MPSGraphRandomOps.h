//
//  MPSGraphRandomOps.h
//  MPSGraph
//
//  Created on 6/1/20.
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#ifndef MPSGraphRandomOps_h
#define MPSGraphRandomOps_h

#import <MetalPerformanceShadersGraph/MPSGraph.h>

NS_ASSUME_NONNULL_BEGIN

MPS_CLASS_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))
@interface MPSGraph(MPSGraphRandomOps)

-(MPSGraphTensor *) dropoutTensor:(MPSGraphTensor *) tensor
                             rate:(double) rate
                             name:(NSString * _Nullable) name
MPS_SWIFT_NAME( dropout(_:rate:name:) );

-(MPSGraphTensor *) dropoutTensor:(MPSGraphTensor *) tensor
                       rateTensor:(MPSGraphTensor *) rate
                             name:(NSString * _Nullable) name
MPS_SWIFT_NAME( dropout(_:rate:name:) );

@end

NS_ASSUME_NONNULL_END

#endif /* MPSGraphRandomOps_h */
