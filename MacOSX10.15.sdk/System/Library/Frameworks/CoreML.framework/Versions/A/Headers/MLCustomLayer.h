//
//  MLCustomLayer.h
//  CoreML
//
//  Copyright © 2017 Apple Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import <CoreML/MLMultiArray.h>

NS_ASSUME_NONNULL_BEGIN

@protocol MTLTexture;
@protocol MTLCommandBuffer;

/*
 * Protocol for specifying a custom layer implementation.
 */
API_AVAILABLE(macos(10.13.2), ios(11.2), watchos(4.2), tvos(11.2))
@protocol MLCustomLayer

/*
 * Initialize the custom layer implementation. The dictionary contains the contents of the
 * 'parameters' map from the model specification. This function is called once on model load.
 * We expect the implementation to return 'nil' and set an error in the event of failure
 * initializing the object.
 */
- (nullable instancetype)initWithParameterDictionary:(NSDictionary<NSString *, id> *)parameters
                                               error:(NSError **)error;

/*
 * The data encoded in the 'weights' field of the model specification will be loaded and made
 * available to the implementation here, with one entry of the array for each entry in the 'repeated'
 * weights field in the Core ML neural network specification . This is called when the model is loaded,
 * but is a separate call from the initialization. The pointer to weights should be stored, but modifying
 * or copying its contents can significantly increase an app's memory footprint. The implementation
 * should return 'YES' on success, or return 'NO' and set an error in the event of a failure.
 */
- (BOOL)setWeightData:(NSArray<NSData *> *)weights
                error:(NSError **)error;

/*
 * For the given input shapes, the implementation needs to return the output shape produced by this layer.
 * This will be called at least once at load time, and will be called any time the size of the inputs changes
 * in a call to predict. Consumes and returns 5D arrays of shapes in the usual Core ML convention - (Sequence,
 * Batch, Channel Height, Width). See the Core ML neural network protobuf specification for more details
 * about how layers use these dimensions. This will get called at load and run time. In the event of an error
 * the implementation should return 'nil' and set an error.
 */
- (nullable NSArray<NSArray<NSNumber *> *> *)outputShapesForInputShapes:(NSArray<NSArray<NSNumber *> *> *)inputShapes
                                                                  error:(NSError **)error;

/*
 * For the given inputs, populate the provide output memory. This will be called for each evaluation performed
 * on the CPU. The inputs and outputs will have the shapes of the most recent call to outputShapesForInputShapes.
 * The memory for both input and output arrays are preallocated, and should not be copied or moved. The
 * implementation should not alter the inputs. Should return 'YES' on sucess, or 'NO' and set the error on
 * failure.
 */
- (BOOL)evaluateOnCPUWithInputs:(NSArray<MLMultiArray *> *)inputs
                        outputs:(NSArray<MLMultiArray *> *)outputs
                          error:(NSError **)error;

@optional
/*
 * Optional selector for encoding a shader implementing the custom layer to a command buffer.
 * The execution of the buffer will occur inside Core ML. Providing this function does not guarantee
 * GPU evaluation for each prediction. If not provided, the execution of this layer will always be
 * on the CPU. Should return 'YES' on sucessfully encoding, or 'NO' and set an error if the encoding
 * fails.
 */
- (BOOL)encodeToCommandBuffer:(id<MTLCommandBuffer>)commandBuffer
                       inputs:(NSArray<id<MTLTexture>> *)inputs
                      outputs:(NSArray<id<MTLTexture>> *)outputs
                        error:(NSError **)error;

@end

NS_ASSUME_NONNULL_END

