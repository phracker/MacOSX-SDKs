//
//  SFSpeechRecognitionTaskHint.h
//  Copyright (c) 2016 Apple Inc. All rights reserved.

#import <Foundation/Foundation.h>

//  Hints on kind of speech recognition being performed
typedef NS_ENUM(NSInteger, SFSpeechRecognitionTaskHint) {
    SFSpeechRecognitionTaskHintUnspecified = 0,     // Unspecified recognition

    SFSpeechRecognitionTaskHintDictation = 1,       // General dictation/keyboard-style
    SFSpeechRecognitionTaskHintSearch = 2,          // Search-style requests
    SFSpeechRecognitionTaskHintConfirmation = 3,    // Short, confirmation-style requests ("Yes", "No", "Maybe")
} API_AVAILABLE(ios(10.0), macos(10.15));
