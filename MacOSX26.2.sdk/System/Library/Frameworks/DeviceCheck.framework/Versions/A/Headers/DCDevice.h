//
//  DCDevice.h
//  DeviceCheck
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <DeviceCheck/DeviceCheck.h>

NS_ASSUME_NONNULL_BEGIN

_DC_EXPORT
API_AVAILABLE(ios(11.0), macos(10.15), tvos(11.0), watchos(9.0))
/// A representation of a device that provides a unique, authenticated token.
///
/// Use the shared instance of the `DCDevice` class to generate a
/// token that identifies a device. Call the
/// ``DeviceCheck/DCDevice/generateTokenWithCompletionHandler:`` method to get
/// the token, and then send it to your server:
///
/// ```swift
/// if DCDevice.current.isSupported { // Always test for availability.
///     DCDevice.current.generateToken { token, error in
///         guard error == nil else { /* Handle the error. */ }
///
///         // Send the token to your server.
///     }
/// }
/// ```
///
/// On your server, combine the token with an authentication key that you obtain
/// from Apple, and use the result to request access to two per-device binary
/// digits (bits). After authenticating the device, Apple passes the current
/// values of the bits, along with the date they were last modified, to your
/// server. Your server applies its business logic to this information and
/// communicates the results to your app. For more information about server-side
/// procedures, see <doc:accessing-and-modifying-per-device-data>.
///
/// - Note: To use the `DCDevice` class, your app must have an app
/// ID that you register on the [Apple
/// Developer](https://developer.apple.com/account/) website.
///
/// Apple records the bits for you, and reports the bits back to you, but you’re
/// responsible for keeping track of what the bits mean. You’re also responsible
/// for determining when to reset the bits for a given device; for example, when
/// a user sells the device to someone else.
@interface DCDevice : NSObject

/// A representation of the device for which you want to query the two bits of
/// data.
@property (class, readonly) DCDevice *currentDevice;

/// A Boolean value that indicates whether the device supports the DeviceCheck
/// API.
@property (getter=isSupported, readonly) BOOL supported;

/// Generates a token that identifies the current device.
///
/// > Concurrency Note: You can call this method from synchronous code using a completion handler,
/// > as shown on this page, or you can call it as an asynchronous method that has the
/// > following declaration:
/// >
/// >  ```swift
/// > func generateToken() async throws -> Data
/// > ```
/// >  For example:
/// >  ```swift
/// > let token = try await generateToken()
/// > ```
/// >  For information about concurrency and asynchronous code in Swift, see <doc://com.apple.documentation/documentation/swift/calling-objective-c-apis-asynchronously>.
///
/// Your server uses the generated token in its requests to get or set the
/// persistent bits for the current device. You should treat the token you
/// receive in the completion block as single-use. Although the token remains
/// valid long enough for your server to retry a specific request if necessary,
/// you should not use a token multiple times. Instead, use this method to
/// generate a new token.
///
/// - Note: The app you use to generate the token must be associated with your
/// developer account; otherwise, the generation request fails.
///
/// - Parameters:
///   - completion: A completion block that includes the following parameters:
///     - `token`:  An ephemeral token that identifies the current device.
///     - `error`: The error that occurred, if any.
- (void)generateTokenWithCompletionHandler:(void(^)(NSData * _Nullable token, NSError * _Nullable error))completion;

@end

NS_ASSUME_NONNULL_END
