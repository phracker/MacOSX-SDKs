/*
 File:  AVSpeechSynthesis.h
 
 Framework:  AVFoundation
 
 Copyright 2013-2018 Apple Inc. All rights reserved.
 */

#import <Foundation/Foundation.h>

#ifdef __OBJC2__

@class AVAudioSession, AVAudioSessionChannelDescription, AVAudioBuffer;

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, AVSpeechBoundary) {
    AVSpeechBoundaryImmediate,
    AVSpeechBoundaryWord
} NS_ENUM_AVAILABLE(10_14, 7_0);

typedef NS_ENUM(NSInteger, AVSpeechSynthesisVoiceQuality) {
    AVSpeechSynthesisVoiceQualityDefault = 1,
    AVSpeechSynthesisVoiceQualityEnhanced
} NS_ENUM_AVAILABLE(10_14, 9_0);

typedef NS_ENUM(NSInteger, AVSpeechSynthesisVoiceGender) {
    AVSpeechSynthesisVoiceGenderUnspecified,
    AVSpeechSynthesisVoiceGenderMale,
    AVSpeechSynthesisVoiceGenderFemale
} NS_ENUM_AVAILABLE(10_15, 13_0);

extern const float AVSpeechUtteranceMinimumSpeechRate API_AVAILABLE(ios(7.0), watchos(1.0), tvos(7.0), macos(10.14));
extern const float AVSpeechUtteranceMaximumSpeechRate API_AVAILABLE(ios(7.0), watchos(1.0), tvos(7.0), macos(10.14));
extern const float AVSpeechUtteranceDefaultSpeechRate API_AVAILABLE(ios(7.0), watchos(1.0), tvos(7.0), macos(10.14));

// Use the Alex identifier with voiceWithIdentifier:. If the voice is present on the system,
// an AVSpeechSynthesisVoice will be returned. Alex is en-US only.
extern NSString *const AVSpeechSynthesisVoiceIdentifierAlex API_AVAILABLE(ios(9.0), watchos(2.0), tvos(9.0), macos(10.14));

//NSString, containing International Phonetic Alphabet (IPA) symbols. Controls pronunciation of a certain word or phrase, e.g. a proper name.
extern NSString *const AVSpeechSynthesisIPANotationAttribute API_AVAILABLE(ios(10.0), watchos(3.0), tvos(10.0), macos(10.14));

typedef void (^AVSpeechSynthesizerBufferCallback)(AVAudioBuffer *buffer) NS_SWIFT_NAME(AVSpeechSynthesizer.BufferCallback);

@protocol AVSpeechSynthesizerDelegate;

/*!
 @class AVSpeechSynthesisVoice
 @abstract
 AVSpeechSynthesisVoice encapsulates the attributes of the voice used to synthesize speech on the system.
 
 @discussion
 Retrieve a voice by specifying the language code your text should be spoken in, or by using voiceWithIdentifier
 for a known voice identifier.
 */
NS_CLASS_AVAILABLE(10_14, 7_0)
@interface AVSpeechSynthesisVoice : NSObject<NSSecureCoding>

+ (NSArray<AVSpeechSynthesisVoice *> *)speechVoices;
+ (NSString *)currentLanguageCode;

/*!
 @method        voiceWithLanguage:
 @abstract      Use a BCP-47 language tag to specify the desired language and region.
 @param			languageCode
 Specifies the BCP-47 language tag that represents the voice.
 @discussion
 The default is the system's region and language.
 Passing in nil will return the default voice.
 Passing in an invalid languageCode will return nil.
 Will return enhanced quality voice if available, default quality otherwise.
 Examples: en-US (U.S. English), fr-CA (French Canadian)
 */
+ (nullable AVSpeechSynthesisVoice *)voiceWithLanguage:(nullable NSString *)languageCode;

/*!
 @method        voiceWithIdentifier:
 @abstract      Retrieve a voice by its identifier.
 @param			identifier
 A unique identifier for a voice.
 @discussion
 Passing in an invalid identifier will return nil.
 Returns nil if the identifier is valid, but the voice is not available on device (i.e. not yet downloaded by the user).
 */
+ (nullable AVSpeechSynthesisVoice *)voiceWithIdentifier:(NSString *)identifier API_AVAILABLE(ios(9.0), watchos(2.0), tvos(9.0), macos(10.14));

@property(nonatomic, readonly) NSString *language;
@property(nonatomic, readonly) NSString *identifier API_AVAILABLE(ios(9.0), watchos(2.0), tvos(9.0), macos(10.14));
@property(nonatomic, readonly) NSString *name API_AVAILABLE(ios(9.0), watchos(2.0), tvos(9.0), macos(10.14));
@property(nonatomic, readonly) AVSpeechSynthesisVoiceQuality quality API_AVAILABLE(ios(9.0), watchos(2.0), tvos(9.0), macos(10.14));
@property(nonatomic, readonly) AVSpeechSynthesisVoiceGender gender API_AVAILABLE(ios(13.0), watchos(6.0), tvos(13.0), macos(10.15));

// This is a dictionary of properties that can be used to create an AVAudioFile using -[AVAudioFile initForWriting:settings:commonFormat:interleaved:error:]
// The data provided by AVSpeechSynthesizerBufferCallback will be in this specified format when using this voice.
// The AVAudioCommonFormat and interleaved properties can be determined by properties within the settings dictionary.
@property(nonatomic, readonly) NSDictionary<NSString *, id> *audioFileSettings API_AVAILABLE(ios(13.0), watchos(6.0), tvos(13.0), macos(10.15));

@end

/*!
 @class AVSpeechUtterance
 @abstract
 AVSpeechUtterance is the atom of speaking a string or pausing the synthesizer.
 
 @discussion
 To start speaking, specify the AVSpeechSynthesisVoice and the string to be spoken, then optionally change the rate, pitch or volume if desired.
 */
NS_CLASS_AVAILABLE(10_14, 7_0)
@interface AVSpeechUtterance : NSObject<NSCopying, NSSecureCoding>

+ (instancetype)speechUtteranceWithString:(NSString *)string;
+ (instancetype)speechUtteranceWithAttributedString:(NSAttributedString *)string API_AVAILABLE(ios(10.0), watchos(3.0), tvos(10.0), macos(10.14));

- (instancetype)initWithString:(NSString *)string;
- (instancetype)initWithAttributedString:(NSAttributedString *)string API_AVAILABLE(ios(10.0), watchos(3.0), tvos(10.0), macos(10.14));

/* If no voice is specified, the system's default will be used. */
@property(nonatomic, retain, nullable) AVSpeechSynthesisVoice *voice;

@property(nonatomic, readonly) NSString *speechString;
@property(nonatomic, readonly) NSAttributedString *attributedSpeechString API_AVAILABLE(ios(10.0), watchos(3.0), tvos(10.0), macos(10.14));

/* Setting these values after a speech utterance has been enqueued will have no effect. */

@property(nonatomic) float rate;             // Values are pinned between AVSpeechUtteranceMinimumSpeechRate and AVSpeechUtteranceMaximumSpeechRate.
@property(nonatomic) float pitchMultiplier;  // [0.5 - 2] Default = 1
@property(nonatomic) float volume;           // [0-1] Default = 1

@property(nonatomic) NSTimeInterval preUtteranceDelay;    // Default is 0.0
@property(nonatomic) NSTimeInterval postUtteranceDelay;   // Default is 0.0

@end

/*!
 @class AVSpeechSynthesizer
 @abstract
 AVSpeechSynthesizer allows speaking of speech utterances with a basic queuing mechanism.
 
 @discussion
 Create an instance of AVSpeechSynthesizer to start generating synthesized speech by using AVSpeechUtterance objects.
 */
NS_CLASS_AVAILABLE(10_14, 7_0)
@interface AVSpeechSynthesizer : NSObject

@property(nonatomic, weak, nullable) id<AVSpeechSynthesizerDelegate> delegate;

@property(nonatomic, readonly, getter=isSpeaking) BOOL speaking;
@property(nonatomic, readonly, getter=isPaused) BOOL paused;

/* AVSpeechUtterances are queued by default. 
   Enqueing the same AVSpeechUtterance that is already enqueued or is speaking will raise an exception. */
- (void)speakUtterance:(AVSpeechUtterance *)utterance;

// Use this method to receive audio buffers that can be used to store or further process synthesized speech.
// The dictionary provided by -[AVSpeechSynthesisVoice audioFileSettings] can be used to create an AVAudioFile.
- (void)writeUtterance:(AVSpeechUtterance *)utterance toBufferCallback:(AVSpeechSynthesizerBufferCallback)bufferCallback API_AVAILABLE(ios(13.0), watchos(6.0), tvos(13.0), macos(10.15)) ;

/* These methods will operate on the speech utterance that is speaking. Returns YES if it succeeds, NO for failure. */

/* Call stopSpeakingAtBoundary: to interrupt current speech and clear the queue. */
- (BOOL)stopSpeakingAtBoundary:(AVSpeechBoundary)boundary;
- (BOOL)pauseSpeakingAtBoundary:(AVSpeechBoundary)boundary;
- (BOOL)continueSpeaking;

// Specify the audio channels to be used for synthesized speech as described by the channel descriptions in AVAudioSession's current route.
// Speech audio will be replicated to each specified channel.
// Default is nil, which implies system defaults.
@property(nonatomic, retain, nullable) NSArray<AVAudioSessionChannelDescription *> *outputChannels API_AVAILABLE(ios(10.0), watchos(3.0), tvos(10.0)) API_UNAVAILABLE(macos) ;

/* The AVSpeechSynthesizer will use the AVAudioSession sharedInstance when set to YES.
   The AVSpeechSynthesizer will use a separate AVAudioSession for playback when set to NO. Additionally, the audio session will mix and duck other audio, and its active state will be managed automatically.
   The separate audio session will use AVAudioSessionRouteSharingPolicyDefault, which means that it may have a different route from the app’s shared instance session.
   Default is YES. */
@property(nonatomic, assign) BOOL usesApplicationAudioSession API_AVAILABLE(ios(13.0), watchos(6.0), tvos(13.0)) API_UNAVAILABLE( macCatalyst, macos);

// Set to YES to send synthesized speech into an outgoing telephony audio stream.
// If there's no active call, setting this property has no effect.
@property(nonatomic, assign) BOOL mixToTelephonyUplink API_AVAILABLE(ios(13.0), watchos(6.0)) API_UNAVAILABLE(tvos, macos);

@end

/*!
 @protocol AVSpeechSynthesizerDelegate
 @abstract
 Defines an interface for delegates of AVSpeechSynthesizer to receive notifications of important speech utterance events.
 */
@protocol AVSpeechSynthesizerDelegate <NSObject>

@optional
- (void)speechSynthesizer:(AVSpeechSynthesizer *)synthesizer didStartSpeechUtterance:(AVSpeechUtterance *)utterance API_AVAILABLE(ios(7.0), watchos(1.0), tvos(7.0), macos(10.14));
- (void)speechSynthesizer:(AVSpeechSynthesizer *)synthesizer didFinishSpeechUtterance:(AVSpeechUtterance *)utterance API_AVAILABLE(ios(7.0), watchos(1.0), tvos(7.0), macos(10.14));
- (void)speechSynthesizer:(AVSpeechSynthesizer *)synthesizer didPauseSpeechUtterance:(AVSpeechUtterance *)utterance API_AVAILABLE(ios(7.0), watchos(1.0), tvos(7.0), macos(10.14));
- (void)speechSynthesizer:(AVSpeechSynthesizer *)synthesizer didContinueSpeechUtterance:(AVSpeechUtterance *)utterance API_AVAILABLE(ios(7.0), watchos(1.0), tvos(7.0), macos(10.14));
- (void)speechSynthesizer:(AVSpeechSynthesizer *)synthesizer didCancelSpeechUtterance:(AVSpeechUtterance *)utterance API_AVAILABLE(ios(7.0), watchos(1.0), tvos(7.0), macos(10.14));

- (void)speechSynthesizer:(AVSpeechSynthesizer *)synthesizer willSpeakRangeOfSpeechString:(NSRange)characterRange utterance:(AVSpeechUtterance *)utterance API_AVAILABLE(ios(7.0), watchos(1.0), tvos(7.0), macos(10.14));
@end

NS_ASSUME_NONNULL_END

#endif // __OBJC2__

