//
//  MLParameterKey.h
//  CoreML
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <CoreML/CoreML.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * A class to specify list of supported model update parameters.
 */
ML_EXPORT
API_AVAILABLE(macos(10.15), ios(13.0))
@interface MLParameterKey : MLKey

// Double parameter used to control the learning rate of an optimizer. Adjustable in progress
@property (class, readonly, nonatomic) MLParameterKey *learningRate;

// Double parameter used to control the momentum of gradient based optimizers. Adjustable at load-time
@property (class, readonly, nonatomic) MLParameterKey *momentum;

// Int64 parameter used to specify the size of a miniBatch used by optimizer. Adjustable at load-time
@property (class, readonly, nonatomic) MLParameterKey *miniBatchSize;

// Double parameter used to control the beta1 of Adam optimizer. Adjustable at load-time
@property (class, readonly, nonatomic) MLParameterKey *beta1;

// Double parameter used to control the beta2 of Adam optimizer. Adjustable at load-time
@property (class, readonly, nonatomic) MLParameterKey *beta2;

// Double parameter used to control the epsilon of Adam optimizer. Adjustable at load-time
@property (class, readonly, nonatomic) MLParameterKey *eps;

// Int64 parameter used to specify the number of epochs used by optimizer. Adjustable at load-time
@property (class, readonly, nonatomic) MLParameterKey *epochs;

// Bool parameter used to specify whether to shuffle the data between epochs. Adjustable at load-time
@property (class, readonly, nonatomic) MLParameterKey *shuffle;

// Int64 parameter used to specify the seed to be used if shuffling data between epochs. Adjustable at load-time
@property (class, readonly, nonatomic) MLParameterKey *seed;

// Int64 parameter used to specify the number of neighbors to use for class affinity (applicable to kNN). Not adjustable in progress
@property (class, readonly, nonatomic) MLParameterKey *numberOfNeighbors;

// cannot construct MLParameterKey without parameters.
- (instancetype)init NS_UNAVAILABLE;

// cannot construct MLParameterKey without parameters.
+ (id)new NS_UNAVAILABLE;

@end

@interface MLParameterKey (MLLinkedModelParameters)

// String parameter used to specify the name of a linked model
@property (class, readonly, nonatomic) MLParameterKey *linkedModelFileName;

// String parameteru sed to specify the search path for a linked model
@property (class, readonly, nonatomic) MLParameterKey *linkedModelSearchPath;

@end

@interface MLParameterKey (MLNeuralNetworkParameters)

// MLMultiArray parameter returned when client requests for weights of a particular layer using a scoped parameter.
@property (class, readonly, nonatomic) MLParameterKey *weights;

// MLMultiArray parameter returned when client requests for biases of a particular layer using a scoped parameter.
@property (class, readonly, nonatomic) MLParameterKey *biases;

@end

@interface MLParameterKey (MLScopedParameters)

// Returns a new MLParameterKey instance after adding additional scoping
- (MLParameterKey *)scopedTo:(NSString *)scope;

@end

NS_ASSUME_NONNULL_END

