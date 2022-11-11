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

NS_ASSUME_NONNULL_BEGIN

@class SHSession;

/// All communication about matches is performed through this delegate.
SH_EXPORT API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0))
@protocol SHSessionDelegate <NSObject>

@optional

/// @brief A match was found in the @c SHCatalog for the provided @c SHSignature
/// @param session The @c SHSession that made the match
/// @param match The @c SHMatch of the matching audio
- (void)session:(SHSession *)session didFindMatch:(SHMatch *)match;

/// @brief The @c SHSignature did not match anything
/// @param session The @c SHSession that attempted to match the @c SHSignature
/// @param signature The @c SHSignature that did not match
/// @param error An optional error. If simply no match was found this will be set to nil. It will be populated if there was an issue performing the match
- (void)session:(SHSession *)session didNotFindMatchForSignature:(SHSignature *)signature error:(nullable NSError *)error;

@end

/// @brief A @c SHSession matches instances of @c SHSignature against a @c SHCatalog
///
/// @discussion A @c SHSession can be used in two distinct ways to match against a @c SHCatalog
///
/// 1. Pass a @c SHSignature to the -[SHSession matchSignature:] method and respond to matches sent to the delegate
///      There is a 1 to 1 relationship between calls to this method and calls to the delegate
/// 2. Pass a continuous stream of @c AVAudioPCMBuffer to the -[SHSession matchStreamingBuffer:atTime:] method, matches are sent to the delegate.
///        ShazamKit will convert the buffers in SHSignature objects internally and perform matches against the @c SHCatalog. The details of how the matching
///        is performed is an implementation detail and is subject to change. As such there will be many callbacks to the delegate per stream of audio, and the same match
///        may be reported multiple times in succession.
///
SH_EXPORT API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0))
@interface SHSession : NSObject

/// @brief The @c SHCatalog used to initialize this session and which all matches will be made against
@property (NS_NONATOMIC_IOSONLY, strong, readonly) SHCatalog *catalog;

/// @brief A delegate for communicating the results of matching
@property (NS_NONATOMIC_IOSONLY, weak) id<SHSessionDelegate> delegate;

/// Create A new @c SHSession that searches the Shazam Catalog
- (instancetype)init;

/// Create A new @c SHSession based upon the supplied @c SHCatalog
/// @param catalog The store of signatures to match against
- (instancetype)initWithCatalog:(SHCatalog *)catalog;

/// @brief Flow audio buffers for matching into the session
/// @discussion Audio will be converted into signatures and matched against the store. Results are communicated through the delegate.
/// The initial buffer specifies the @c AVAudioFormat and all subsequent buffers must contain the same format otherwise an error will be communicated through
/// the delegate.
///
/// It is advisable but not required to pass an @c AVAudioTime along with the audio buffer. The audio provided must be contiguous, gaps in the audio will have adverse
/// effects on the ability to match the audio. The time variable is validated by the session to ensure that the audio is contiguous and mitigate the effect of discontiguous audio.
/// @param buffer A buffer of audio to be used for recognition
/// @param time Where in the stream the audio occurs
/// @note This method will throw an exception if the audio format is not PCM in one of the following sample rates: 48000, 44100, 32000, 16000.
- (void)matchStreamingBuffer:(AVAudioPCMBuffer *)buffer atTime:(nullable AVAudioTime *)time;

/// Match the @c SHSignature against the provided @c SHCatalog
/// @param signature a @c SHSignature to be matched
- (void)matchSignature:(SHSignature *)signature;

@end

NS_ASSUME_NONNULL_END
