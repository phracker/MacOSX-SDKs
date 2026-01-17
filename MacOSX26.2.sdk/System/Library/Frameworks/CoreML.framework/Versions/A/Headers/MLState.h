//
//  MLState.h
//  CoreML
//
//  Copyright © 2023 Apple Inc. All rights reserved.
//

#import <CoreML/MLExport.h>
#import <Foundation/Foundation.h>

@class MLMultiArray;

NS_ASSUME_NONNULL_BEGIN

/// Handle to the state buffers.
///
/// A stateful model maintains a state from one prediction to another by storing the information in the state buffers. To use such a model, the client must request the model to create state buffers and get `MLState` object, which is the handle to those buffers. Then, at the prediction time, pass the `MLState` object in one of the stateful prediction functions.
///
/// ```swift
/// // Load a stateful model
/// let modelAsset = try MLModelAsset(url: modelURL)
/// let model = try await MLModel.load(asset: modelAsset, configuration: MLModelConfiguration())
///
/// // Request a state
/// let state = model.newState()
///
/// // Run predictions
/// for _ in 0 ..< 42 {
///   _ = try await model.prediction(from: inputFeatures, using: state)
/// }
///
/// // Access the state buffer.
/// state.withMultiArray(for: "accumulator") { stateMultiArray in
///   ...
/// }
/// ```
///
/// The object is a handle to the state buffers. The client shall not read or write the buffers while a prediction is in-flight.
///
/// Each stateful prediction that uses the same `MLState` must be serialized. Otherwise, if two such predictions run concurrently, the behavior is undefined.
///
API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0))
ML_EXPORT NS_SWIFT_SENDABLE
__attribute__((objc_subclassing_restricted))
@interface MLState : NSObject

/// Gets a mutable view into a state buffer.
///
/// The underlying state buffer's address can differ for each call; one shall not access the state buffer outside of the closure.
///
/// - Parameters:
///   - handler: Block to access the state buffer through `MLMultiArray`.
- (void)getMultiArrayForStateNamed:(NSString *)stateName
                           handler:(void (NS_NOESCAPE ^)(MLMultiArray *buffer))handler
    NS_REFINED_FOR_SWIFT
    API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0));

// This type is currently unavailable
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
