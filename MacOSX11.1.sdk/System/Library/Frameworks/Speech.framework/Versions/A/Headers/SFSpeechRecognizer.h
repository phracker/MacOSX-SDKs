//
//  SFSpeechRecognizer.h
//
//  Copyright (c) 2016 Apple, Inc. All rights reserved.
//


#import <AVFoundation/AVFoundation.h>
#import <Foundation/Foundation.h>

#import <Speech/SFSpeechRecognitionTaskHint.h>

NS_ASSUME_NONNULL_BEGIN

@class SFSpeechRecognitionRequest;
@class SFSpeechRecognitionResult;
@class SFSpeechRecognitionTask;

@protocol SFSpeechRecognizerDelegate;
@protocol SFSpeechRecognitionTaskDelegate;

typedef NS_ENUM(NSInteger, SFSpeechRecognizerAuthorizationStatus) {
    SFSpeechRecognizerAuthorizationStatusNotDetermined,
    SFSpeechRecognizerAuthorizationStatusDenied,
    SFSpeechRecognizerAuthorizationStatusRestricted,
    SFSpeechRecognizerAuthorizationStatusAuthorized,
} API_AVAILABLE(ios(10.0), macos(10.15));

API_AVAILABLE(ios(10.0), macos(10.15))
@interface SFSpeechRecognizer : NSObject

// Locales which support speech recognition.
// Note that supported does not mean currently available; some locales may require an internet connection, for example.
+ (NSSet<NSLocale *> *)supportedLocales;

+ (SFSpeechRecognizerAuthorizationStatus)authorizationStatus;
+ (void)requestAuthorization:(void(^)(SFSpeechRecognizerAuthorizationStatus status))handler;

- (nullable instancetype)init; // Returns speech recognizer with user's current locale, or nil if is not supported
- (nullable instancetype)initWithLocale:(NSLocale *)locale NS_DESIGNATED_INITIALIZER; // returns nil if the locale is not supported

@property (nonatomic, readonly, getter=isAvailable) BOOL available;
@property (nonatomic, readonly, copy) NSLocale *locale;

// True if this recognition can handle requests with requiresOnDeviceRecognition set to true
@property (nonatomic) BOOL supportsOnDeviceRecognition API_AVAILABLE(ios(13));

@property (nonatomic, weak) id<SFSpeechRecognizerDelegate> delegate;

// Default task for requests, overrides SFSpeechRecognitionTaskHintUnspecified for requests
@property (nonatomic) SFSpeechRecognitionTaskHint defaultTaskHint;

// Recognize speech utterance with a request
// If request.shouldReportPartialResults is true, result handler will be called
// repeatedly with partial results, then finally with a final result or an error.
- (SFSpeechRecognitionTask *)recognitionTaskWithRequest:(SFSpeechRecognitionRequest *)request
                                          resultHandler:(void (^)(SFSpeechRecognitionResult * __nullable result, NSError * __nullable error))resultHandler;

// Advanced API: Recognize a custom request with with a delegate
// The delegate will be weakly referenced by the returned task
- (SFSpeechRecognitionTask *)recognitionTaskWithRequest:(SFSpeechRecognitionRequest *)request
                                               delegate:(id <SFSpeechRecognitionTaskDelegate>)delegate;

// Queue used the recognizer for recognition task handlers and delegate messages
// Defaults to the main queue
@property (nonatomic, strong) NSOperationQueue *queue;

@end

API_AVAILABLE(ios(10.0), macos(10.15))
@protocol SFSpeechRecognizerDelegate <NSObject>
@optional

// Called when the availability of the given recognizer changes
- (void)speechRecognizer:(SFSpeechRecognizer *)speechRecognizer availabilityDidChange:(BOOL)available;

@end

NS_ASSUME_NONNULL_END
