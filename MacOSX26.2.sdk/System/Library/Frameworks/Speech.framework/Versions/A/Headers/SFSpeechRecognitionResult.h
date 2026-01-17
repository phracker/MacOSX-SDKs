//
//  SFSpeechRecognitionResult.h
//
//  Copyright (c) 2016 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class SFTranscription;
@class SFSpeechRecognitionMetadata;

/**
 An object that contains the partial or final results of a speech recognition request.

 Use an `SFSpeechRecognitionResult` object to retrieve the results of a speech recognition request. You don't create these objects directly. Instead, the Speech framework creates them and passes them to the handler block or delegate object you specified when starting your speech recognition task.

 A speech recognition result object contains one or more ``transcriptions`` of the current utterance. Each transcription has a confidence rating indicating how likely it is to be correct. You can also get the transcription with the highest rating directly from the ``bestTranscription`` property.

 If you requested partial results from the speech recognizer, the transcriptions may represent only part of the total audio content. Use the ``isFinal`` property to determine if the request contains partial or final results.
 */
API_AVAILABLE(ios(10.0), macos(10.15), tvos(18))
@interface SFSpeechRecognitionResult : NSObject <NSCopying, NSSecureCoding>

/**
 The transcription with the highest confidence level.
 */
@property (nonatomic, readonly, copy) SFTranscription *bestTranscription;

/**
 An array of potential transcriptions, sorted in descending order of confidence.

 All transcriptions correspond to the same utterance, which can be a partial or final result of the overall request. The first transcription in the array has the highest confidence rating, followed by transcriptions with decreasing confidence ratings.
 */
@property (nonatomic, readonly, copy) NSArray<SFTranscription *> *transcriptions;

/**
 A Boolean value that indicates whether speech recognition is complete and whether the transcriptions are final.

 When a speech recognition request is final, its transcriptions don't change.
 */
@property (nonatomic, readonly, getter=isFinal) BOOL final;

/**
 An object that contains the metadata results for a speech recognition request.
 */
@property (nonatomic, nullable, readonly) SFSpeechRecognitionMetadata *speechRecognitionMetadata API_AVAILABLE(ios(14.0), macos(11.0), tvos(18));

@end

NS_ASSUME_NONNULL_END
