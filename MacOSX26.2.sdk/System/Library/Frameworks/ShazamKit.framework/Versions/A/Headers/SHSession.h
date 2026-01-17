//
//  SHSession.h
//  ShazamKit
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AVFAudio/AVFAudio.h>
#import <ShazamKit/SHDefines.h>
#import <ShazamKit/SHCatalog.h>
#import <ShazamKit/SHSignature.h>
#import <ShazamKit/SHMatch.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

@class SHSession;

/// Methods that the session calls with the result of a match request.
SH_EXPORT API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0))
@protocol SHSessionDelegate <NSObject>

@optional

/// Tells the delegate that the query signature matches an item in the catalog.
///
/// - Parameters:
///   - session: The session object that performs the match.
///   - match: The matching items from the catalog.
- (void)session:(SHSession *)session didFindMatch:(SHMatch *)match;

/// Tells the delegate that the query signature doesn't match an item in the catalog, or that there's an error.
///
/// You can retry the match if the error indicates an issue in communicating with the catalog server, such as ``SHError/Code/matchAttemptFailed``.
///
/// - Parameters:
///   - session: The session object that performs the match.
///   - signature: The query signature to use for the match.
///   - error: The error that occurs; otherwise, `nil`, which indicates that there's no match.
- (void)session:(SHSession *)session didNotFindMatchForSignature:(SHSignature *)signature error:(nullable NSError *)error;

@end

/// An object that matches a specific audio recording when a segment of that recording is part of captured sound in the Shazam catalog or your custom catalog.
///
/// Prepare to make matches by:
///
/// - Creating a session for the catalog that contains the reference signatures
/// - Adding your delegate that receives the match results
///
/// Search for a match in one of two ways:
///
/// - Generate a signature for the captured audio and call ``match(_:)``
/// - Call ``matchStreamingBuffer(_:at:)`` with a streaming audio buffer, and ShazamKit generates the signature for you
///
/// Searching the catalog is asynchronous. The session calls your delegate methods with the result.
///
/// Matching songs in Shazam music requires enabling your app to access the catalog. For more information on enabling your app, see [Enable ShazamKit for an App ID](https://developer.apple.com/help/account/configure-app-services/shazamkit).
///
/// The code below shows searching for a match in the Shazam catalog using an existing audio buffer:
///
/// ```swift
///// Set up the session.
///let session = SHSession()
///
///// Create a signature from the captured audio buffer.
///let signatureGenerator = SHSignatureGenerator()
///try signatureGenerator.append(buffer, at: audioTime)
///let signature = signatureGenerator.signature()
///
///// Check for a match.
///let result = await session.result(from: signature)
///
///// Use the result.
///switch result {
///  case .match(let match):
///       // Match found.
///  case .noMatch(let signature):
///       // No match found.
///  case .error(let error, let signature):
///       // An error occurred.
///}
/// ```
SH_EXPORT API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0))
@interface SHSession : NSObject

/// The catalog object containing the reference signatures and their associated metadata that the session uses to perform matches.
@property (NS_NONATOMIC_IOSONLY, strong, readonly) SHCatalog *catalog;

/// The object that the session calls with the result of a match request.
@property (NS_NONATOMIC_IOSONLY, weak) id<SHSessionDelegate> delegate;


/// Creates a new session object for matching songs in the Shazam Music catalog.
- (instancetype)init;


/// Creates a new session object for matching audio in a custom catalog.
/// 
///  - Parameters:
///     - catalog: The catalog that contains the reference audio signatures and their associated metadata.
- (instancetype)initWithCatalog:(SHCatalog *)catalog;

/// Converts the audio in the buffer to a signature, and searches the reference signatures in the session catalog.
///
/// This method continues to generate signatures and perform searches until the audio in the buffer stops, which may result in multiple calls to the ``SHSession/delegate``.
///
/// The audio buffer must be in one of the supported formats. For the list of the supported audio formats, see ``SHSignatureGenerator/append(_:at:)``.
///
/// To use the microphone as input for the buffer, see <doc:matching-audio-using-the-built-in-microphone>.
///
/// > Note:
/// > You must use the audio format of the first call to this method in the current session in all subsequent calls for the session.
///
/// - Parameters:
///    - buffer: An audio buffer.
///    - time: The start time of the audio to use for generating the signatures.
- (void)matchStreamingBuffer:(AVAudioPCMBuffer *)buffer atTime:(nullable AVAudioTime *)time;

/// Searches for the query signature in the reference signatures that the session catalog contains.
///
///- Parameters:
///  - signature: The signature for searching the catalog of reference signatures.
- (void)matchSignature:(SHSignature *)signature;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
