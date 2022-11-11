//
//  MLModelError.h
//  CoreML
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

FOUNDATION_EXPORT NSString * const MLModelErrorDomain API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));

/*!
  MLModelError defines the set of MLModel related error codes.

  The framework communicates the error code to the application through NSError's code property. The
  application could use the error code to present an helpful error message to the user or to
  diagnose the problem.

  See also NSError's localizedDescription property, which often contains more detailed information.
 */
typedef NS_ENUM(NSInteger, MLModelError) {

    /*!
      Core ML throws/returns this error when the framework encounters an generic error.

      The typical cause for this error is an unexpected framework level problem.
    */
    MLModelErrorGeneric = 0,

    /*!  Core ML throws/returns this error when the model client, typically an application, sends
      the wrong feature type to a model's input.

      The typical cause for this error is a programming mistake.

      For example, a prediction method will throw/return the error when the caller passes an image
      to a model's input that expects an `MLMultiArray`.
    */
    MLModelErrorFeatureType = 1,

    /*!  Core ML throws/returns this error when the framework encounters some I/O problem, most
      likely a file I/O problem.

      For example, a model loading will throw/return the error when the caller requests a
      non-existing model URL.
    */
    MLModelErrorIO = 3,

    /*!  Core ML throws/returns this error when the framework encounters an error in the custom
      layer subsystem.

      The typical cause for this error is a programming mistake.

      For example, a prediction method will throw/return the error when it fails to find the custom
      layer implementation.
    */
    MLModelErrorCustomLayer API_AVAILABLE(macos(10.13.2), ios(11.2), watchos(4.2), tvos(11.2)) = 4,

    /*!  Core ML throws/returns this error when the framework encounters an error in the custom
      model subsystem.

      The typical cause for this error is a programming mistake.

      For example, a prediction method will throw/return the error when it fails to find the custom
      model implementation.
    */
    MLModelErrorCustomModel API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0)) = 5,

    /*!  Core ML throws/returns this error when the framework encounters an error while performing
      the on-device model update.

      For example, the framework will throw/return the error when it fails to save the updated model.
    */
    MLModelErrorUpdate API_AVAILABLE(macos(10.15), ios(13.0), tvos(14.0)) = 6,

    /*!  Core ML throws/returns this error when the model client, typically an application, queries
      an unsupported model parameter (see MLParameterKey).

      The typical cause for this error is a programming mistake.
    */
    MLModelErrorParameters API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0)) = 7,

    /*!  Core ML throws/returns this error when the framework fails to download the model decryption
      key.

      The typical cause for this error is a network connection issue to the key server.
    */
    MLModelErrorModelDecryptionKeyFetch API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 8,

    /*!  Core ML throws/returns this error when the framework encounters an error in the model
      decryption subsystem.

      The typical cause for this error is in the key server configuration and the client application
      cannot do much about it.

      For example, a model loading method will throw/return the error when it uses incorrect model
      decryption key.
    */
    MLModelErrorModelDecryption API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 9,

    /*!  Core ML throws/returns this error when the framework encounters an error in the model
      collection deployment subsystem.

      The typical cause for this error is the network connectability issue to the model deployment
      server.
    */
    MLModelErrorModelCollection API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 10,
} API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));

NS_ASSUME_NONNULL_END
