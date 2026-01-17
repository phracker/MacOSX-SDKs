//
//  DCError.h
//  DeviceCheck
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <DeviceCheck/DeviceCheck.h>

NS_ASSUME_NONNULL_BEGIN

    /// The error domain for errors associated with DeviceCheck APIs.
extern NSErrorDomain const DCErrorDomain API_AVAILABLE(ios(11.0), macos(10.15), tvos(11.0), watchos(9.0));
   /// DeviceCheck error codes.

typedef NS_ERROR_ENUM(DCErrorDomain, DCError) {
    /// A failure has occurred, such as the failure to generate a token.
    DCErrorUnknownSystemFailure,
    /// DeviceCheck is unavailable on this device.
    DCErrorFeatureUnsupported,
    /// An error code that indicates when your app provides data that isn’t
    /// formatted correctly.
    DCErrorInvalidInput,
    /// An error caused by a failed attempt to use the App Attest key.
    ///
    /// You receive this error if something goes wrong with generating,
    /// retrieving, or using an App Attest cryptographic key, when:
    ///
    /// - You call
    /// ``DeviceCheck/DCAppAttestService/attestKey:clientDataHash:completionHandler:``
    /// for a key that’s already been attested.
    /// - You call
    /// ``DeviceCheck/DCAppAttestService/generateAssertion:clientDataHash:completionHandler:``
    /// with an unattested key.
    /// - The App Attest service rejects the key.
    DCErrorInvalidKey,
    /// An error that indicates a failed attempt to contact the App Attest service
    /// during an attestation.
    ///
    /// You receive this error when you call
    /// ``DeviceCheck/DCAppAttestService/attestKey:clientDataHash:completionHandler:``
    /// and the framework isn’t able to complete the attestation. If you receive
    /// this error, try the attestation again later using the same key and the same
    /// value for the `clientDataHash` parameter. Retrying with the same inputs
    /// helps to preserve the risk metric for a given device.
    DCErrorServerUnavailable,

} API_AVAILABLE(ios(11.0), macos(10.15), tvos(11.0), watchos(9.0));

NS_ASSUME_NONNULL_END

