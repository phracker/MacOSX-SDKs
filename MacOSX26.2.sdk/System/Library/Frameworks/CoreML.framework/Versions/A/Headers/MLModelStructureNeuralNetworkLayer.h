//
//  MLModelStructureNeuralNetworkLayer.h
//  CoreML_framework
//
//  Copyright © 2023 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <CoreML/MLExport.h>

NS_ASSUME_NONNULL_BEGIN

/// A class representing a layer in a NeuralNetwork.
__attribute__((objc_subclassing_restricted))
ML_EXPORT NS_REFINED_FOR_SWIFT NS_SWIFT_SENDABLE
API_AVAILABLE(macos(14.4), ios(17.4), watchos(10.4), tvos(17.4))
@interface MLModelStructureNeuralNetworkLayer : NSObject

- (instancetype)init NS_UNAVAILABLE;

+ (instancetype)new NS_UNAVAILABLE;

/// The layer name.
@property (readonly, copy, nonatomic) NSString *name;
/// The type of the layer, e,g, "elementwise", "pooling", etc.
@property (readonly, copy, nonatomic) NSString *type;
/// The input names.
@property (readonly, copy, nonatomic) NSArray<NSString *> *inputNames;
/// The output names.
@property (readonly, copy, nonatomic) NSArray<NSString *> *outputNames;

@end

NS_ASSUME_NONNULL_END
