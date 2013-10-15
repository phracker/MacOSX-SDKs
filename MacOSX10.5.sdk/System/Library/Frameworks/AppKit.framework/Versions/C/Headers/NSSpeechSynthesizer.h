/*
	NSSpeechSynthesizer.h
	Application Kit
	Copyright (c) 2003-2007, Apple Inc.
	All rights reserved.
*/

#import <AppKit/AppKitDefines.h>
#import <Foundation/NSObject.h>
#import <Foundation/NSRange.h>

@class NSArray, NSDictionary, NSString, NSURL, NSError;


APPKIT_EXTERN NSString *const NSVoiceName AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
APPKIT_EXTERN NSString *const NSVoiceIdentifier AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
APPKIT_EXTERN NSString *const NSVoiceAge AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
APPKIT_EXTERN NSString *const NSVoiceGender AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
APPKIT_EXTERN NSString *const NSVoiceDemoText AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
APPKIT_EXTERN NSString *const NSVoiceLocaleIdentifier AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
APPKIT_EXTERN NSString *const NSVoiceSupportedCharacters AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
APPKIT_EXTERN NSString *const NSVoiceIndividuallySpokenCharacters AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

// Values for NSVoiceGender voice attribute
APPKIT_EXTERN NSString *const NSVoiceGenderNeuter AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
APPKIT_EXTERN NSString *const NSVoiceGenderMale AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
APPKIT_EXTERN NSString *const NSVoiceGenderFemale AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

// NSVoiceLanguage has been replaced by NSVoiceLocaleIdentifier
APPKIT_EXTERN NSString *const NSVoiceLanguage DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5
// Values for NSSpeechBoundary
enum {
    NSSpeechImmediateBoundary =  0,
    NSSpeechWordBoundary,
    NSSpeechSentenceBoundary
};
typedef NSUInteger NSSpeechBoundary;
#endif

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3

@interface NSSpeechSynthesizer : NSObject {
@private // All instance variables are private
    id	_privateNSSpeechSynthesizerVars;
}

- (id)initWithVoice:(NSString *)voice;

- (BOOL)startSpeakingString:(NSString *)string;
- (BOOL)startSpeakingString:(NSString *)string toURL:(NSURL *)url;

- (BOOL)isSpeaking;
- (void)stopSpeaking;
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5
- (void)stopSpeakingAtBoundary:(NSSpeechBoundary)boundary;
- (void)pauseSpeakingAtBoundary:(NSSpeechBoundary)boundary;
- (void)continueSpeaking;
#endif

- (id)delegate;
- (void)setDelegate:(id)anObject;
- (NSString *)voice;
- (BOOL)setVoice:(NSString *)voice;
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5
- (float)rate;
- (void)setRate:(float)rate;
- (float)volume;
- (void)setVolume:(float)volume;
#endif
- (BOOL)usesFeedbackWindow;
- (void)setUsesFeedbackWindow:(BOOL)flag;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5
- (void)addSpeechDictionary:(NSDictionary*)speechDictionary;
- (NSString *)phonemesFromText:(NSString *)text;

- (id)objectForProperty:(NSString *)property error:(NSError **)outError;
- (BOOL)setObject:(id)object forProperty:(NSString *)property error:(NSError **)outError;
#endif

+ (BOOL)isAnyApplicationSpeaking;
+ (NSString *)defaultVoice;
+ (NSArray *)availableVoices;
+ (NSDictionary *)attributesForVoice:(NSString*)voice;

@end

@interface NSObject (NSSpeechSynthesizerDelegate)

- (void)speechSynthesizer:(NSSpeechSynthesizer *)sender didFinishSpeaking:(BOOL)finishedSpeaking;
- (void)speechSynthesizer:(NSSpeechSynthesizer *)sender willSpeakWord:(NSRange)characterRange ofString:(NSString *)string;
- (void)speechSynthesizer:(NSSpeechSynthesizer *)sender willSpeakPhoneme:(short)phonemeOpcode;
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5
- (void)speechSynthesizer:(NSSpeechSynthesizer *)sender didEncounterErrorAtIndex:(NSUInteger)characterIndex ofString:(NSString *)string message:(NSString *)message;
- (void)speechSynthesizer:(NSSpeechSynthesizer *)sender didEncounterSyncMessage:(NSString *)message;
#endif
@end

// Synthesizer Properties (including object type)
APPKIT_EXTERN NSString *const NSSpeechStatusProperty AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;  // NSDictionary, see keys below
APPKIT_EXTERN NSString *const NSSpeechErrorsProperty AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;  // NSDictionary, see keys below
APPKIT_EXTERN NSString *const NSSpeechInputModeProperty AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;  // NSString: NSSpeechModeTextProperty or NSSpeechModePhonemeProperty
APPKIT_EXTERN NSString *const NSSpeechCharacterModeProperty AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER; // NSString: NSSpeechModeNormalProperty or NSSpeechModeLiteralProperty
APPKIT_EXTERN NSString *const NSSpeechNumberModeProperty AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER; // NSString: NSSpeechModeNormalProperty or NSSpeechModeLiteralProperty
APPKIT_EXTERN NSString *const NSSpeechRateProperty AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;  // NSNumber
APPKIT_EXTERN NSString *const NSSpeechPitchBaseProperty AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;  // NSNumber
APPKIT_EXTERN NSString *const NSSpeechPitchModProperty AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;  // NSNumber
APPKIT_EXTERN NSString *const NSSpeechVolumeProperty AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;  // NSNumber
APPKIT_EXTERN NSString *const NSSpeechSynthesizerInfoProperty AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;  // NSDictionary, see keys below
APPKIT_EXTERN NSString *const NSSpeechRecentSyncProperty AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;  // NSString
APPKIT_EXTERN NSString *const NSSpeechPhonemeSymbolsProperty AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;  // NSDictionary, see keys below
APPKIT_EXTERN NSString *const NSSpeechCurrentVoiceProperty AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;  // NSString
APPKIT_EXTERN NSString *const NSSpeechCommandDelimiterProperty AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;  // NSDictionary, see keys below
APPKIT_EXTERN NSString *const NSSpeechResetProperty AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
APPKIT_EXTERN NSString *const NSSpeechOutputToFileURLProperty AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;  // NSURL

// Speaking Modes for NSSpeechInputModeProperty
APPKIT_EXTERN NSString *const NSSpeechModeText AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
APPKIT_EXTERN NSString *const NSSpeechModePhoneme AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

// Speaking Modes for NSSpeechInputModeProperty and NSSpeechNumberModeProperty
APPKIT_EXTERN NSString *const NSSpeechModeNormal AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
APPKIT_EXTERN NSString *const NSSpeechModeLiteral AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

// Dictionary keys returned by NSSpeechStatusProperty
APPKIT_EXTERN NSString *const NSSpeechStatusOutputBusy AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;  // NSNumber
APPKIT_EXTERN NSString *const NSSpeechStatusOutputPaused AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;  // NSNumber
APPKIT_EXTERN NSString *const NSSpeechStatusNumberOfCharactersLeft AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;  // NSNumber
APPKIT_EXTERN NSString *const NSSpeechStatusPhonemeCode AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;  // NSNumber

// Dictionary keys returned by NSSpeechErrorProperty
APPKIT_EXTERN NSString *const NSSpeechErrorCount AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;  // NSNumber
APPKIT_EXTERN NSString *const NSSpeechErrorOldestCode AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;  // NSNumber
APPKIT_EXTERN NSString *const NSSpeechErrorOldestCharacterOffset AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;  // NSNumber
APPKIT_EXTERN NSString *const NSSpeechErrorNewestCode AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;  // NSNumber
APPKIT_EXTERN NSString *const NSSpeechErrorNewestCharacterOffset AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;  // NSNumber

// Dictionary keys returned by NSSpeechSynthesizerInfoProperty
APPKIT_EXTERN NSString *const NSSpeechSynthesizerInfoIdentifier AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;  // NSString
APPKIT_EXTERN NSString *const NSSpeechSynthesizerInfoVersion AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;  // NSString

// Dictionary keys returned by NSSpeechPhonemeSymbolsProperty
APPKIT_EXTERN NSString *const NSSpeechPhonemeInfoOpcode AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;  // NSNumber
APPKIT_EXTERN NSString *const NSSpeechPhonemeInfoSymbol AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;  // NSString
APPKIT_EXTERN NSString *const NSSpeechPhonemeInfoExample AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;  // NSString
APPKIT_EXTERN NSString *const NSSpeechPhonemeInfoHiliteStart AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;  // NSNumber
APPKIT_EXTERN NSString *const NSSpeechPhonemeInfoHiliteEnd AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;  // NSNumber

// Dictionary keys returned by NSSpeechCommandDelimiterProperty
APPKIT_EXTERN NSString *const NSSpeechCommandPrefix AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;  // NSString
APPKIT_EXTERN NSString *const NSSpeechCommandSuffix AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;  // NSString

// Use with addSpeechDictionary:
APPKIT_EXTERN NSString *const NSSpeechDictionaryLocaleIdentifier AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;  // NSString
APPKIT_EXTERN NSString *const NSSpeechDictionaryModificationDate AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;  // NSString
APPKIT_EXTERN NSString *const NSSpeechDictionaryPronunciations AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;  // NSArray
APPKIT_EXTERN NSString *const NSSpeechDictionaryAbbreviations AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;  // NSArray
APPKIT_EXTERN NSString *const NSSpeechDictionaryEntrySpelling AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;  // NSString
APPKIT_EXTERN NSString *const NSSpeechDictionaryEntryPhonemes AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;  // NSString


#endif

