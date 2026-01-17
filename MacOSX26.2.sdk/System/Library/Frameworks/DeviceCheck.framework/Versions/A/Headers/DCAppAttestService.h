//
//  DCAppAttestService.h
//  DeviceCheck
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//


#import <DeviceCheck/DeviceCheck.h>

NS_ASSUME_NONNULL_BEGIN

_DC_EXPORT
API_AVAILABLE(macos(11.0), ios(14.0), tvos(15.0), watchos(9.0))
/// A service that you use to validate the instance of your app running on a
/// device.
///
/// Use the ``DeviceCheck/DCAppAttestService/sharedService`` instance of the
/// ``DeviceCheck/DCAppAttestService`` class to assert the legitimacy of a
/// particular instance of your app to your server. After ensuring service
/// availability by reading the ``DeviceCheck/DCAppAttestService/supported``
/// property, you use the service to:
///
/// - Create a cryptographic key in the Secure Enclave by calling the
/// ``DeviceCheck/DCAppAttestService/generateKeyWithCompletionHandler:`` method.
/// - Ask Apple to certify the key by calling the
/// ``DeviceCheck/DCAppAttestService/attestKey:clientDataHash:completionHandler:``
/// method. - Prepare an assertion of your app’s integrity to accompany any or
/// all server requests using the
/// ``DeviceCheck/DCAppAttestService/generateAssertion:clientDataHash:completionHandler:``
/// method.
///
/// For more information about how to support App Attest in your app, see
/// <doc:establishing-your-app-s-integrity>. For information about the
/// complementary procedures you implement on your server, see
/// <doc:validating-apps-that-connect-to-your-server>.
///
/// - Note: To use the App Attest service, your app must have an app ID that you
/// register on the [Apple Developer](https://developer.apple.com/account/)
/// website.
@interface DCAppAttestService : NSObject

/// The shared App Attest service that you use to validate your app.
///
/// Use the shared instance of the service to generate and to certify a
/// cryptographic key, and then to assert your app’s validity using that key.
@property (class, readonly) DCAppAttestService *sharedService;

/// A Boolean value that indicates whether a particular device provides the App
/// Attest service.
///
/// > Important: Not all device types support the App Attest service, so check
/// > for support before using the service.
/// >
/// > If you read ``DeviceCheck/DCAppAttestService/supported`` from an app running
/// > on a Mac device, the value is
/// > <doc://com.apple.documentation/documentation/swift/false>. This includes
/// > Mac Catalyst apps, and iOS or iPadOS apps running on Apple silicon.
///
/// If you read ``DeviceCheck/DCAppAttestService/supported`` from within an app
/// extension, the value might be
/// <doc://com.apple.documentation/documentation/swift/true> or
/// <doc://com.apple.documentation/documentation/swift/false>, depending on
/// the extension type. However, most extensions don’t support App Attest. The
/// ``DeviceCheck/DCAppAttestService/generateKeyWithCompletionHandler:`` method
/// fails when you call it from an app extension, regardless of the value of
/// ``DeviceCheck/DCAppAttestService/supported``.
///
/// The only app extensions that support App Attest are watchOS extensions in
/// watchOS 9 or later. For these extensions, you can use the results from
/// ``DeviceCheck/DCAppAttestService/supported`` to indicate whether your
/// WatchKit extension bypasses attestation.
@property (getter=isSupported, readonly) BOOL supported;

/// Creates a new cryptographic key for use with the App Attest service.
///
/// > Concurrency Note: You can call this method from synchronous code using a completion handler,
/// > as shown on this page, or you can call it as an asynchronous method that has the
/// > following declaration:
/// >
/// > ```swift
/// > func generateKey() async throws -> String
/// > ```
/// > For example:
/// > ```swift
/// > let keyIdentifier = try await generateKey()
/// > ```
/// > For information about concurrency and asynchronous code in Swift, see <doc://com.apple.documentation/documentation/swift/calling-objective-c-apis-asynchronously>.
/// 
/// Call this method to request the creation of a secure, unattested key pair on
/// a device for a specific user. On success, the method provides your app with
/// an identifier that represents the key pair stored in the Secure Enclave.
/// Because there’s no way to use or retrieve the key without the identifier,
/// you’ll want to either record it in your app or on your server right away. If
/// key generation fails, the closure provides a ``DeviceCheck/DCError-swift.struct`` that
/// indicates the reason for the failure.
///
/// Create a unique key for each user account on a device. Otherwise it’s hard
/// to detect an attack that uses a single compromised device to serve multiple
/// remote users running a compromised version of your app. For more
/// information, see <doc:assessing-fraud-risk>.
///
/// After you get the identifier, you call the
/// ``DeviceCheck/DCAppAttestService/attestKey:clientDataHash:completionHandler:``
/// method with the key identifier to ask Apple to attest to the validity of the
/// associated key. Later, you call the
/// ``DeviceCheck/DCAppAttestService/generateAssertion:clientDataHash:completionHandler:``
/// method with the key identifier to answer a challenge from your server, and
/// establish the legitimacy of this instance of your app.
///
/// - Parameters:
///   - completionHandler: A closure that the method calls upon completion with
/// the following parameters:
///     - `keyId`:  An identifier that you use to refer to the key. The framework securely
/// stores the key in the Secure Enclave.
///     - `error`:  A ``DeviceCheck/DCError-swift.struct`` instance that indicates the
/// reason for failure, or `nil` on success.
- (void)generateKeyWithCompletionHandler:(void (^)(NSString * _Nullable keyId, NSError * _Nullable error))completionHandler;

/// Asks Apple to attest to the validity of a generated cryptographic key.
///
/// > Concurrency Note: You can call this method from synchronous code using a completion handler,
/// > as shown on this page, or you can call it as an asynchronous method that has the
/// > following declaration:
/// >
/// > ```swift
/// > func attestKey(_ keyId: String, clientDataHash: Data) async throws -> Data
/// > ```
/// >
/// > For information about concurrency and asynchronous code in Swift, see <doc://com.apple.documentation/documentation/swift/calling-objective-c-apis-asynchronously>.
///
/// This method asks Apple to attest to the validity of a key that you
/// previously generated with a call to the
/// ``DeviceCheck/DCAppAttestService/generateKeyWithCompletionHandler:`` method.
/// Provide the method with both the key identifier and a computed hash of a
/// data block that includes a one-time challenge from your server to prevent
/// replay attacks. For example, you can use CryptoKit to create a
/// <doc://com.apple.documentation/documentation/cryptokit/sha256> hash of
/// challenge data:
///
/// ```swift
/// import CryptoKit let hash = Data(SHA256.hash(data: challenge)) // A
/// challenge from your server.
/// ```
/// The attest method calls its completion handler to return an attestation
/// object to you, which you must send to your server for verification. A
/// compromised version of your app could falsify the verification result, thus
/// circumventing App Attest.
///
/// If you successfully verify the attestation object on your server, as
/// described in <doc:validating-apps-that-connect-to-your-server>, then you can
/// associate the key identifier with the user on the device for future
/// reference. You’ll need the identifier to generate assertions with calls to
/// ``DeviceCheck/DCAppAttestService/generateAssertion:clientDataHash:completionHandler:``.
/// If your server fails to verify the attestation object, discard the key
/// identifier.
///
/// If the method’s completion handler returns the
/// ``DeviceCheck/DCError-swift.struct/serverUnavailable`` error — typically due to network
/// connectivity issues — it means that the framework failed to reach the App
/// Attest service to complete the attestation. In this case, retry attestation
/// again using the same key and client data hash later to avoid unnecessarily
/// generating new keys. Retrying with the same inputs helps to preserve the
/// risk metric for a given device.
///
/// - Parameters:
///   - keyId: The identifier you received when generating a cryptographic key by
/// calling the
/// ``DeviceCheck/DCAppAttestService/generateKeyWithCompletionHandler:`` method.
///   - clientDataHash: A SHA256 hash of a unique, single-use data block that
/// embeds a challenge from your server. Should be at least 16 bytes in length.
///   - completionHandler: A closure that the method calls upon completion with
/// the following parameters:
///     - `attestationObject`: A statement from Apple about the validity of the key
/// associated with `keyId`. Send this to your server for processing.
///     - `error`: A ``DeviceCheck/DCError-swift.struct`` instance that indicates the reason for
/// failure, or `nil` on success.
- (void)attestKey:(NSString *)keyId clientDataHash:(NSData *)clientDataHash completionHandler:(void (^)(NSData * _Nullable attestationObject, NSError * _Nullable error))completionHandler;

/// Creates a block of data that demonstrates the legitimacy of an instance of
/// your app running on a device.
///
/// > Concurrency Note: You can call this method from synchronous code using a completion handler,
/// > as shown on this page, or you can call it as an asynchronous method that has the
/// > following declaration:
/// >
/// > ```swift
/// > func generateAssertion(_ keyId: String, clientDataHash: Data) async throws -> Data
/// > ```
/// >
/// > For information about concurrency and asynchronous code in Swift, see <doc://com.apple.documentation/documentation/swift/calling-objective-c-apis-asynchronously>.
///
/// After generating a key with the
/// ``DeviceCheck/DCAppAttestService/generateKeyWithCompletionHandler:`` method
/// and validating it with the
/// ``DeviceCheck/DCAppAttestService/attestKey:clientDataHash:completionHandler:``
/// method, you can use the key at critical moments in your app’s life cycle —
/// like when a user tries to access premium content — to reaffirm the
/// legitimacy of a given instance of your app. Do this by using the
/// ``DeviceCheck/DCAppAttestService/generateAssertion:clientDataHash:completionHandler:``
/// method to sign server requests with your attested key.
///
/// You provide the key identifier and a hash of the request that includes a
/// challenge from your server to prevent replay attacks, where an attacker
/// reuses captured network traffic to pose as someone else. The method returns
/// an assertion object in its completion handler that you send to your server
/// for verification, as described in <doc:establishing-your-app-s-integrity>.
///
/// - Parameters:
///   - keyId: The identifier you received when generating a cryptographic key by
/// calling the
/// ``DeviceCheck/DCAppAttestService/generateKeyWithCompletionHandler:`` method.
///   - clientDataHash: A SHA256 hash of a unique, single-use data block that
/// represents the client data to be signed with the attested private key. Should be at least 16 bytes in length.
///   - completionHandler: A closure that the method calls upon completion with
/// the following parameters:
///     - `assertionObject`: A data structure that you send to your server for processing.
///     - `error` : A ``DeviceCheck/DCError-swift.struct`` instance that indicates the reason for failure, or `nil` on success.
- (void)generateAssertion:(NSString *)keyId clientDataHash:(NSData *)clientDataHash completionHandler:(void (^)(NSData * _Nullable assertionObject, NSError * _Nullable error))completionHandler;

@end

NS_ASSUME_NONNULL_END
