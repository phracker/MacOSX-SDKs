//
//  SFSpeechRecognitionRequest.h
//
//  Copyright (c) 2016 Apple, Inc. All rights reserved.
//

#import <AVFoundation/AVFoundation.h>
#import <Foundation/Foundation.h>

#import <Speech/SFSpeechRecognitionTaskHint.h>

NS_ASSUME_NONNULL_BEGIN

// A request for a speech recognition from an audio source
API_AVAILABLE(ios(10.0), macos(10.15))
@interface SFSpeechRecognitionRequest : NSObject

@property (nonatomic) SFSpeechRecognitionTaskHint taskHint;

// If true, partial (non-final) results for each utterance will be reported.
// Default is true
@property (nonatomic) BOOL shouldReportPartialResults;

// Phrases which should be recognized even if they are not in the system vocabulary
@property (nonatomic, copy) NSArray<NSString *> *contextualStrings;

// String which can be used to identify the receiver by the developer
@property (nonatomic, copy, nullable) NSString *interactionIdentifier NS_DEPRECATED(10_15, 12_0, 10_0, 15_0, "Not used anymore");

// If true, speech recognition will not send any audio over the Internet
// This will reduce accuracy but enables certain applications where it is
// inappropriate to transmit user speech to a remote service.
// Default is false
@property (nonatomic) BOOL requiresOnDeviceRecognition API_AVAILABLE(ios(13), macos(10.15));

@end

// A request to recognize speech from a recorded audio file
API_AVAILABLE(ios(10.0), macos(10.15))
@interface SFSpeechURLRecognitionRequest : SFSpeechRecognitionRequest

- (instancetype)init NS_UNAVAILABLE;

// Request to transcribe speech from an audio file from the given URL.
- (instancetype)initWithURL:(NSURL *)URL NS_DESIGNATED_INITIALIZER;

@property (nonatomic, readonly, copy) NSURL *URL;

@end

// A request to recognize speech from arbitrary audio buffers
API_AVAILABLE(ios(10.0), macos(10.15))
@interface SFSpeechAudioBufferRecognitionRequest : SFSpeechRecognitionRequest

// Preferred audio format for optimal speech recognition
@property (nonatomic, readonly) AVAudioFormat *nativeAudioFormat;

// Append audio to the end of the recognition stream. Must currently be in native format.
- (void)appendAudioPCMBuffer:(AVAudioPCMBuffer *)audioPCMBuffer;
- (void)appendAudioSampleBuffer:(CMSampleBufferRef)sampleBuffer;

// Indicate that the audio source is finished and no more audio will be appended
- (void)endAudio;

@end

NS_ASSUME_NONNULL_END
