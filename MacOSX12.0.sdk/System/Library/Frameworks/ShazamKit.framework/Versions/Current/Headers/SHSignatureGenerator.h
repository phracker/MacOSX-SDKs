//
//  SHSignatureGenerator.h
//  ShazamKit
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AVFAudio/AVFAudio.h>
#import <ShazamKit/SHSignature.h>

NS_ASSUME_NONNULL_BEGIN

/// @brief @c SHSignatureGenerator provides a way to convert audio data into instances of @c SHSignature
SH_EXPORT API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0))
@interface SHSignatureGenerator : NSObject

/// @brief Add audio to the generator
/// @discussion Audio passed to the generator should be contiguous, passing non contiguous data will affect the quality of the @c SHSignature
/// produced. Passing the @c AVAudioTime is not required but recommended, it allows the generator to detect when the audio is not contiguous.
/// This method will throw an exception if the audio format is not PCM in one of the following sample rates: 48000, 44100, 32000, 16000.
/// @param time Where in the stream the audio represents
/// @param buffer The audio data to be appended to the signature
/// @param error An error if there was an issue appending the buffer
- (BOOL)appendBuffer:(AVAudioPCMBuffer *)buffer atTime:(nullable AVAudioTime *)time error:(NSError **)error;

/// @brief Convert the current audio data into a @c SHSignature
/// @discussion Signature may be called as many times as needed, each time producing a @c SHSignature from
/// the audio data
- (SHSignature *)signature;

@end

NS_ASSUME_NONNULL_END
