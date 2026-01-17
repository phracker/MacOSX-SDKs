//
//  SFSpeechRecognitionRequest.h
//
//  Copyright (c) 2016 Apple, Inc. All rights reserved.
//

#import <AVFoundation/AVFoundation.h>
#import <Foundation/Foundation.h>

#import <Speech/SFSpeechRecognitionTaskHint.h>
#import <Speech/SFSpeechLanguageModel.h>

NS_ASSUME_NONNULL_BEGIN

/**
 An abstract class that represents a request to recognize speech from an audio source.

 Don't create ``SFSpeechRecognitionRequest`` objects directly. Create an ``SFSpeechURLRecognitionRequest`` or ``SFSpeechAudioBufferRecognitionRequest`` object instead. Use the properties of this class to configure various aspects of your request object before you start the speech recognition process. For example, use the ``shouldReportPartialResults`` property to specify whether you want partial results or only the final result of speech recognition.
 */
API_AVAILABLE(ios(10.0), macos(10.15), tvos(18))
@interface SFSpeechRecognitionRequest : NSObject

/**
 A value that indicates the type of speech recognition being performed.

 The default value of this property is ``SFSpeechRecognitionTaskHint/unspecified``. For a valid list of values, see ``SFSpeechRecognitionTaskHint``.
 */
@property (nonatomic) SFSpeechRecognitionTaskHint taskHint;

/**
 A Boolean value that indicates whether you want intermediate results returned for each utterance.

 The default value of this property is `true`. If you want only final results (and you don't care about intermediate results), set this property to `false` to prevent the system from doing extra work.
 */
// If true, partial (non-final) results for each utterance will be reported.
@property (nonatomic) BOOL shouldReportPartialResults;

/**
 An array of phrases that should be recognized, even if they are not in the system vocabulary.

 Use this property to specify short custom phrases that are unique to your app. You might include phrases with the names of characters, products, or places that are specific to your app. You might also include domain-specific terminology or unusual or made-up words. Assigning custom phrases to this property improves the likelihood of those phrases being recognized.

 Keep phrases relatively brief, limiting them to one or two words whenever possible. Lengthy phrases are less likely to be recognized. In addition, try to limit each phrase to something the user can say without pausing.

 Limit the total number of phrases to no more than 100.
 */
@property (nonatomic, copy) NSArray<NSString *> *contextualStrings;

/**
 An identifier string that you use to describe the type of interaction associated with the speech recognition request.

 If different parts of your app have different speech recognition needs, you can use this property to identify the part of your app that is making each request. For example, if one part of your app lets users speak phone numbers and another part lets users speak street addresses, consistently identifying the part of the app that makes a recognition request may help improve the accuracy of the results.
 */
@property (nonatomic, copy, nullable) NSString *interactionIdentifier NS_DEPRECATED(10_15, 12_0, 10_0, 15_0, "Not used anymore");

/**
 A Boolean value that determines whether a request must keep its audio data on the device.

 Set this property to `true` to prevent an ``SFSpeechRecognitionRequest`` from sending audio over the network. However, on-device requests won't be as accurate.

 > Note:
 > The request only honors this setting if the ``SFSpeechRecognizer/supportsOnDeviceRecognition`` (``SFSpeechRecognizer``) property is also `true`.
 */
@property (nonatomic) BOOL requiresOnDeviceRecognition API_AVAILABLE(ios(13), macos(10.15), tvos(18));

/**
 A Boolean value that indicates whether to add punctuation to speech recognition results.

 Set this property to `true` for the speech framework to automatically include punctuation in the recognition results. Punctuation includes a period or question mark at the end of a sentence, and a comma within a sentence.
 */
@property (nonatomic) BOOL addsPunctuation API_AVAILABLE(ios(16), macos(13), tvos(18));

@property (nonatomic, copy, nullable) SFSpeechLanguageModelConfiguration *customizedLanguageModel API_AVAILABLE(ios(17), macos(14), tvos(18));

@end

/**
 A request to recognize speech in a recorded audio file.

 Use this object to perform speech recognition on the contents of an audio file.

 The following example shows a method that performs recognition on an audio file based on the user's default language and prints out the transcription.

 Listing 1. Getting a speech recognizer and making a recognition request

 ```swift
 func recognizeFile(url: URL) {
     // Create a speech recognizer associated with the user's default language.
     guard let myRecognizer = SFSpeechRecognizer() else {
         // The system doesn't support the user's default language.
         return
     }
     
     guard myRecognizer.isAvailable else {
         // The recognizer isn't available.
         return
     }
     
     // Create and execute a speech recognition request for the audio file at the URL.
     let request = SFSpeechURLRecognitionRequest(url: url)
     myRecognizer.recognitionTask(with: request) { (result, error) in
         guard let result else {
             // Recognition failed, so check the error for details and handle it.
             return
         }
         
         // Print the speech transcription with the highest confidence that the
         // system recognized.
         if result.isFinal {
             print(result.bestTranscription.formattedString)
         }
     }
 }
 ```
 */
API_AVAILABLE(ios(10.0), macos(10.15), tvos(18))
@interface SFSpeechURLRecognitionRequest : SFSpeechRecognitionRequest

- (instancetype)init NS_UNAVAILABLE;

/**
 Creates a speech recognition request, initialized with the specified URL.

 Use this method to create a request to recognize speech in a recorded audio file that resides at the specified URL. Pass the request to the recognizer's ``SFSpeechRecognizer/recognitionTask(with:delegate:)`` method to start recognition.
 */
- (instancetype)initWithURL:(NSURL *)URL NS_DESIGNATED_INITIALIZER;

/**
 The URL of the audio file.
 */
@property (nonatomic, readonly, copy) NSURL *URL;

@end

/**
 A request to recognize speech from captured audio content, such as audio from the device's microphone.

 Use an ``SFSpeechAudioBufferRecognitionRequest`` object to perform speech recognition on live audio, or on a set of existing audio buffers. For example, use this request object to route audio from a device's microphone to the speech recognizer.

 The request object contains no audio initially. As you capture audio, call ``append(_:)`` or ``appendAudioSampleBuffer(_:)`` to add audio samples to the request object. The speech recognizer continuously analyzes the audio you appended, stopping only when you call the ``endAudio()`` method. You must call ``endAudio()`` explicitly to stop the speech recognition process.

 For a complete example of how to use audio buffers with speech recognition, see [SpeakToMe: Using Speech Recognition with AVAudioEngine](https://developer.apple.com/library/archive/samplecode/SpeakToMe/Introduction/Intro.html#//apple_ref/doc/uid/TP40017110).
 */
API_AVAILABLE(ios(10.0), macos(10.15), tvos(18))
@interface SFSpeechAudioBufferRecognitionRequest : SFSpeechRecognitionRequest

/**
 The preferred audio format for optimal speech recognition.

 Use the audio format in this property as a hint for optimal recording, but don't depend on the value remaining unchanged.
 */
@property (nonatomic, readonly) AVAudioFormat *nativeAudioFormat;

/**
 Appends audio in the PCM format to the end of the recognition request.

 The audio must be in a native format and uncompressed.

 - Parameters:
   - audioPCMBuffer: An audio buffer that contains audio in the PCM format.
 */
- (void)appendAudioPCMBuffer:(AVAudioPCMBuffer *)audioPCMBuffer;

/**
 Appends audio to the end of the recognition request.

 The audio must be in a native format.

 - Parameters:
   - sampleBuffer: A buffer of audio.
 */
- (void)appendAudioSampleBuffer:(CMSampleBufferRef)sampleBuffer;

/**
 Marks the end of audio input for the recognition request.

 Call this method explicitly to let the speech recognizer know that no more audio input is coming.
 */
- (void)endAudio;

@end

NS_ASSUME_NONNULL_END
