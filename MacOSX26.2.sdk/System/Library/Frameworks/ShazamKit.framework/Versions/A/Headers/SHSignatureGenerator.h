//
//  SHSignatureGenerator.h
//  ShazamKit
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#if __has_include(<AVFoundation/AVFoundation.h>)
#import <AVFoundation/AVFoundation.h>
#else
#import <AVFAudio/AVFAudio.h>
#endif

#import <ShazamKit/SHSignature.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// An object for converting audio data into a signature.
///
/// Create both reference and query signatures using this class.
SH_EXPORT API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0))
@interface SHSignatureGenerator : NSObject

#if __has_include(<AVFoundation/AVFoundation.h>)
/// Creates a signature with the asset you specify.
///
/// > Important:
/// > You can call this method from synchronous code using a completion handler, as shown on this page, or you can call it as an asynchronous method that has the following declaration:
/// >
/// > ```swift
/// > class func signature(from asset: AVAsset) async throws -> SHSignature
/// > ```
/// >
/// > For information about concurrency and asynchronous code in Swift, see <doc://com.apple.documentation/documentation/swift/calling-objective-c-apis-asynchronously>.
///
/// The asset you specify can be any type of media that contains audio tracks. If the asset has multiple tracks, the system mixes them into one ``SHSignature``.
///
/// - Parameters:
///   - asset: An asset that contains the audio to convert.
///   - completionHandler: The system calls this completion block after creating the signature, or an error if the system couldn't create it.
///
///     This block takes the following parameters:
///
///     - term `signature`: A new signature instance.
///     - term error: An error object if a problem occurs when creating thesignature; otherwise, `nil`.
+ (void)generateSignatureFromAsset:(AVAsset *)asset completionHandler:(void (^)(SHSignature * __nullable signature, NSError * __nullable error))completionHandler API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0), watchos(9.0)) NS_SWIFT_ASYNC_NAME(signature(from:));
#endif

/// Adds audio to the generator.
///
/// Using noncontiguous audio may result in a lower-quality signature.
///
/// The audio must be PCM at one of these rates:
///
/// - `48000` hertz
/// - `44100` hertz
/// - `32000` hertz
/// - `16000` hertz
///
/// - Parameters:
///   - buffer: The audio data to append to the signature generator.
///   - time: The time position of the start of the audio buffer in the full audio you use to generate the signature.
///   - error: The error that occurs; otherwise, `nil`.
- (BOOL)appendBuffer:(AVAudioPCMBuffer *)buffer atTime:(nullable AVAudioTime *)time error:(NSError **)error;

/// Converts the audio buffer into a signature.
///
/// - Returns: A signature that ShazamKit generates from the audio buffer.
- (SHSignature *)signature;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
