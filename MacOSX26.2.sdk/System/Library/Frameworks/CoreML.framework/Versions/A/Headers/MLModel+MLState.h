//
//  MLModel+MLState.h
//  CoreML_framework
//
//  Copyright © 2024 Apple Inc. All rights reserved.
//

#import <CoreML/MLModel.h>
#import <CoreML/MLState.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0))
ML_EXPORT
@interface MLModel (MLState)

/// Creates a new state object.
///
/// Core ML framework will allocate the state buffers declared in the model.
///
/// The allocated state buffers are initialized to zeros. To initialize with different values, use `.withMultiArray(for:)` to get the mutable `MLMultiArray`-view to the state buffer.
///
/// It returns an empty state when the model is stateless. One can use the empty state with stateful prediction functions such as `prediction(from:using:)` and those predictions will be stateless. This simplifies the call site which may or may not use a stateful model.
///
/// ```swift
/// // Create state that contains two state buffers: s1 and s2.
/// // Then, initialize s1 to 1.0 and s2 to 2.0.
/// let state = model.newState()
/// state.withMultiArray(for: "s1") { stateMultiArray in
///     stateMultiArray[0] = 1.0
/// }
/// state.withMultiArray(for: "s2") { stateMultiArray in
///     stateMultiArray[0] = 2.0
/// }
/// ```
- (MLState *)newState
    NS_REFINED_FOR_SWIFT
    API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0));

/// Run a stateful prediction synchronously.
///
/// Use this method to run predictions on a stateful model.
///
/// ```swift
/// let state = model.newState()
/// let prediction = try model.prediction(from: inputFeatures, using: state)
/// ```
///
/// - Parameters:
///  - inputFeatures: The input features as declared in the model description.
///  - state: The state object created by `newState()` method.
///  - error: The output parameter to receive an error information on failure.
- (nullable id<MLFeatureProvider>)predictionFromFeatures:(id<MLFeatureProvider>)inputFeatures
                                              usingState:(MLState *)state
                                                   error:(NSError * __autoreleasing *)error
    NS_SWIFT_NAME(prediction(from:using:))
    API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0));

/// Run a stateful prediction synchronously with options.
///
/// Use this method to run predictions on a stateful model.
///
/// ```swift
/// let state = model.newState()
/// let prediction = try model.prediction(from: inputFeatures, using: state, options: predictionOptions)
/// ```
///
/// - Parameters:
///  - inputFeatures: The input features as declared in the model description.
///  - state: The state object created by `newState()` method.
///  - options: The prediction options.
///  - error: The output parameter to receive an error information on failure.
- (nullable id<MLFeatureProvider>)predictionFromFeatures:(id<MLFeatureProvider>)inputFeatures
                                              usingState:(MLState *)state
                                                 options:(MLPredictionOptions *)options
                                                   error:(NSError * __autoreleasing *)error
    NS_SWIFT_NAME(prediction(from:using:options:))
    API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0));

/// Run a stateful prediction asynchronously.
///
/// Use this method to run predictions on a stateful model.
/// 
/// Do not request a prediction while another prediction that shares the same state is in-flight, otherwise the behavior is undefined.
///
/// ```swift
/// let state = model.newState()
/// let prediction = try await model.prediction(from: inputFeatures, using: state)
/// ```
///
/// - Parameters
///  - input: The input features to make a prediction from.
///  - state: The state object created by `newState()` method.
///  - options: Prediction options to modify how the prediction is run.
///  - completionHandler: A block that will be invoked once the prediction has completed successfully or unsuccessfully. On success, it is invoked with a valid model output. On failure, it is invoked with a nil output and NSError
- (void)predictionFromFeatures:(id<MLFeatureProvider>)inputFeatures
                    usingState:(MLState *)state
                       options:(MLPredictionOptions *)options
             completionHandler:(void (^)(_Nullable id<MLFeatureProvider> output, NSError * _Nullable error))completionHandler
                 API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0))
                 NS_REFINED_FOR_SWIFT NS_SWIFT_DISABLE_ASYNC;

@end

NS_ASSUME_NONNULL_END

