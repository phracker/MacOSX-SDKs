//
//  SFSpeechRecognitionTaskHint.h
//  Copyright (c) 2016 Apple Inc. All rights reserved.

#import <Foundation/Foundation.h>

/**
 The type of task for which you are using speech recognition.
 */
typedef NS_ENUM(NSInteger, SFSpeechRecognitionTaskHint) {
    /// An unspecified type of task.
    ///
    /// Use this hint type when the intended use for captured speech does not match the other task types.
    SFSpeechRecognitionTaskHintUnspecified = 0,

    /// A task that uses captured speech for text entry.
    ///
    /// Use this hint type when you are using speech recognition for a task that's similar to the keyboard's built-in dictation function.
    SFSpeechRecognitionTaskHintDictation = 1,

    /// A task that uses captured speech to specify search terms.
    ///
    /// Use this hint type when you are using speech recognition to identify search terms.
    SFSpeechRecognitionTaskHintSearch = 2,

    /// A task that uses captured speech for short, confirmation-style requests.
    ///
    /// Use this hint type when you are using speech recognition to handle confirmation commands, such as "yes," "no," or "maybe."
    SFSpeechRecognitionTaskHintConfirmation = 3,
} API_AVAILABLE(ios(10.0), macos(10.15), tvos(18));
