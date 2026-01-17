/*
File:  AVSpeechSynthesisProvider.h

Framework:  AVFoundation

Copyright 2022 Apple Inc. All rights reserved.
*/

#import <TargetConditionals.h>

#ifndef AVSpeeechSynthesisProvider_h
#define AVSpeeechSynthesisProvider_h

#import <AVFAudio/AVSpeechSynthesis.h>

#if __has_include(<AudioToolbox/AUAudioUnit.h>)
#import <AudioToolbox/AUAudioUnit.h>
#endif

NS_ASSUME_NONNULL_BEGIN

@class AVSpeechSynthesisProviderRequest, AVSpeechSynthesisMarker;

#pragma mark - AVSpeechSynthesisProviderVoice -

/*! @brief  The representation of a provided voice that is available for speech synthesis.
    @discussion
        @c AVSpeechSynthesisProviderVoice is distinct from @c AVSpeechSynthesisVoice, in that it is a voice provided to the system by an @c AVSpeechSynthesisProviderAudioUnit.
 
        An @c AVSpeechSynthesisProviderVoice will surface as an @c AVSpeechSynthesisVoice when using @c AVSpeechSynthesisVoice.speechVoices(). The quality will always be listed as @c .enhanced
 */
NS_SWIFT_SENDABLE
API_AVAILABLE(ios(16.0), macos(13.0), watchos(9.0), tvos(16.0)) 
@interface AVSpeechSynthesisProviderVoice : NSObject <NSSecureCoding, NSCopying>

/*! @brief  The localized name of the voice
 */
@property (nonatomic, readonly) NSString *name;

/*! @brief  A unique identifier for the voice
    @discussion
        The recommended format is reverse domain notation.
        Behavior is undefined if identifiers are not unique for all voices within a given extension.
 */
@property (nonatomic, readonly) NSString *identifier;

/*! @brief  A set of BCP 47 codes identifying the languages this synthesizer is primarily used for.
    @discussion
        These languages are what a user would expect a synthesizer to fully support and be primarily used for.
 */
@property (nonatomic, readonly) NSArray<NSString *> *primaryLanguages;

/*! @brief  A superset of BCP 47 codes identifying the voice’s supported languages.
    @discussion
        These languages are what a user would expect a voice to be able to speak such that if the voice is given a multi-lingual phrase, it would be able to speak the entire phrase without a need to to switch voices. For example, a zh-CN voice could have @c ["zh-CN"] as its @c primaryLanguages, but in @c supportedLanguages have @c ["zh-CN","en-US"] indicating if it received "你好 means Hello", it would be able to speak the entire phrase.
 */
@property (nonatomic, readonly) NSArray<NSString *> *supportedLanguages;

/*! @brief  The size of the voice (optional)
    @discussion
       This reported size of the voice package on disk, in bytes. Defaults to 0.
*/
@property (nonatomic, readwrite) int64_t voiceSize;

/*! @brief  The voice version (optional)
    @discussion
        This is an optional property for bookkeeping. This value does not affect system behavior.
 */
@property (nonatomic, strong) NSString *version;

/*! @brief  The gender of the voice (optional)
 */
@property (nonatomic, readwrite) AVSpeechSynthesisVoiceGender gender;

/*! @brief  The age of the voice in years (optional)
    @discussion
       This is an optional property that indicates the age of this voice, to be treated as a personality trait. Defaults to 0.
*/
@property (nonatomic, assign) NSInteger age;


- (instancetype)initWithName:(NSString *)name identifier:(NSString *)identifier primaryLanguages:(NSArray<NSString *> *)primaryLanguages supportedLanguages:(NSArray<NSString *> *)supportedLanguages;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/*! @brief  A call that indicates that a new voice or set of voices is available, or no longer available, for system use.
    @discussion
       Call this method to indicate to the system that there has been change in the availability of the voices your application is providing to the system.
*/
+ (void)updateSpeechVoices;

@end


#pragma mark - AVSpeechSynthesisProviderRequest -

/*!
    An @c AVSpeechSynthesisProviderRequest gets delivered to an @c AVSpeechSynthesisProviderAudioUnit in order to synthesize audio.
    This is distinct from an @c AVSpeechUtterance, which is a generic utterance to be spoken.
 */
NS_SWIFT_SENDABLE
API_AVAILABLE(ios(16.0), macos(13.0), watchos(9.0), tvos(16.0)) 
@interface AVSpeechSynthesisProviderRequest : NSObject <NSSecureCoding, NSCopying>

/*!
    @abstract The SSML representation of the text to be synthesized with the corresponding speech synthesis attributes for customization of pitch, rate, intonation, and more.
    @see https://www.w3.org/TR/speech-synthesis11/
 */
@property (nonatomic, readonly) NSString *ssmlRepresentation;

/*! @abstract The voice to be used in this speech request
 */
@property (nonatomic, readonly) AVSpeechSynthesisProviderVoice *voice;

- (instancetype)initWithSSMLRepresentation:(NSString *)text voice:(AVSpeechSynthesisProviderVoice *)voice;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

#pragma mark - AVSpeechSynthesisProviderAudioUnit -

/*! @brief  An Audio Unit dedicated to speech synthesizer tasks
    @discussion
        An @c AVSpeechSynthesisProviderAudioUnit is dedicated to producing audio buffers that contain synthesized speech, as well as markers that provide metadata on those audio buffers. The text to be synthesized is delivered as an @c AVSpeechSynthesisProviderRequest
 */

#if __has_include(<AudioToolbox/AUAudioUnit.h>)
NS_SWIFT_NONSENDABLE
API_AVAILABLE(ios(16.0), macos(13.0), tvos(16.0)) API_UNAVAILABLE(watchos) 
@interface AVSpeechSynthesisProviderAudioUnit : AUAudioUnit

/*! @brief A block of information that is relevant to the generation of speech synthesis.
    @param metadata An array of speech synthesis metadata
    @param speechRequest The speech request associated with the metadata
*/
typedef void(^AVSpeechSynthesisProviderOutputBlock)(NSArray<AVSpeechSynthesisMarker *> *markers, AVSpeechSynthesisProviderRequest *speechRequest) API_AVAILABLE(ios(16.0), macos(13.0), watchos(9.0), tvos(16.0)) ;

/*! @brief  Returns the voices this audio unit has available and ready for synthesis.
    @discussion
        This method should fetch and return the voices ready to synthesize that a user can select from (usually through Settings).
        Required for speech synthesizer audio unit extensions. An audio unit with a dynamic list of voices can override this property's getter to perform a more complex fetch.
*/
@property (nonatomic, strong) NSArray<AVSpeechSynthesisProviderVoice *> *speechVoices;

/*! @brief A property set by the host that is called by the audio unit to supply metadata for a speech request.
    @discussion
        A synthesizer should call this method when it has produced relevant data to the audio buffers it is sending back to the host. In some cases speech output may be delayed until these markers are delivered. For example, word highlighting depends on marker data from synthesizers in order to properly time which words are highlighted. Many speech synthesizers generate this information on the fly, while synthesizing the audio. The array of markers can reference future audio buffers that have yet to be delivered.
 
        There may be cases in which marker data is not fully known until further audio processing is done. In these cases, and other casers where marker data has changed, calling this block with marker data that contains perviously delivered audio buffer ranges will replace that audio buffer range's marker data, as it will be considered stale.
 */
@property (nonatomic, copy, nullable) AVSpeechSynthesisProviderOutputBlock speechSynthesisOutputMetadataBlock;


/*! @brief  Sends a new speech request to be synthesized
    @discussion
        Sends a new speech request to the synthesizer to render. When the synthesizer audio unit is finished generating audio buffers for the speech request, it should indicate this within its internal render block, @c AUInternalRenderBlock, specifically through the @c AudioUnitRenderActionFlags flag @c kAudioOfflineUnitRenderAction_Complete.
 */
- (void)synthesizeSpeechRequest:(AVSpeechSynthesisProviderRequest *)speechRequest;

/*! @brief  Informs the audio unit that the speech request job should be discarded.
 */
- (void)cancelSpeechRequest;

@end
#endif

NS_ASSUME_NONNULL_END

#endif /* AVSpeeechSynthesisProvider_h */
