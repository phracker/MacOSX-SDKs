/*
	NSSpeechSynthesizer.h
	Application Kit
	Copyright (c) 2003-2005, Apple Computer, Inc.
	All rights reserved.
*/

#import <AppKit/AppKitDefines.h>
#import <Foundation/NSObject.h>
#import <Foundation/NSRange.h>

@class NSArray, NSDictionary, NSString, NSURL;


APPKIT_EXTERN NSString *NSVoiceName AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
APPKIT_EXTERN NSString *NSVoiceIdentifier AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
APPKIT_EXTERN NSString *NSVoiceAge AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
APPKIT_EXTERN NSString *NSVoiceGender AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
APPKIT_EXTERN NSString *NSVoiceDemoText AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
APPKIT_EXTERN NSString *NSVoiceLanguage AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

APPKIT_EXTERN NSString *NSVoiceGenderNeuter AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
APPKIT_EXTERN NSString *NSVoiceGenderMale AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
APPKIT_EXTERN NSString *NSVoiceGenderFemale AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3

@interface NSSpeechSynthesizer : NSObject {
@private // All instance variables are private
    id	_privateNSSpeechSynthesizerVars;
}

- (id)initWithVoice:(NSString *)voice;

- (BOOL)startSpeakingString:(NSString *)string;
- (BOOL)startSpeakingString:(NSString *)string toURL:(NSURL *)url;
- (void)stopSpeaking;
- (BOOL)isSpeaking;

- (id)delegate;
- (void)setDelegate:(id)anObject;
- (NSString *)voice;
- (BOOL)setVoice:(NSString *)voice;
- (BOOL)usesFeedbackWindow;
- (void)setUsesFeedbackWindow:(BOOL)flag;

+ (BOOL)isAnyApplicationSpeaking;
+ (NSString *)defaultVoice;
+ (NSArray *)availableVoices;
+ (NSDictionary *)attributesForVoice:(NSString*)voice;

@end

@interface NSObject (NSSpeechSynthesizerDelegate)

- (void)speechSynthesizer:(NSSpeechSynthesizer *)sender didFinishSpeaking:(BOOL)finishedSpeaking;
- (void)speechSynthesizer:(NSSpeechSynthesizer *)sender willSpeakWord:(NSRange)characterRange ofString:(NSString *)string;
- (void)speechSynthesizer:(NSSpeechSynthesizer *)sender willSpeakPhoneme:(short)phonemeOpcode;

@end

#endif

