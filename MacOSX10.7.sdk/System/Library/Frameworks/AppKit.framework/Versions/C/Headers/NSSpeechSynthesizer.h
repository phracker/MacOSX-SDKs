/*
	NSSpeechSynthesizer.h
	Application Kit
	Copyright (c) 2003-2011, Apple Inc.
	All rights reserved.
*/

#import <AppKit/AppKitDefines.h>
#import <Foundation/NSObject.h>
#import <Foundation/NSRange.h>

@class NSArray, NSDictionary, NSString, NSURL, NSError;
@protocol NSSpeechSynthesizerDelegate;

APPKIT_EXTERN NSString *const NSVoiceName;
APPKIT_EXTERN NSString *const NSVoiceIdentifier;
APPKIT_EXTERN NSString *const NSVoiceAge;
APPKIT_EXTERN NSString *const NSVoiceGender;
APPKIT_EXTERN NSString *const NSVoiceDemoText;
APPKIT_EXTERN NSString *const NSVoiceLocaleIdentifier NS_AVAILABLE_MAC(10_5);
APPKIT_EXTERN NSString *const NSVoiceSupportedCharacters NS_AVAILABLE_MAC(10_5);
APPKIT_EXTERN NSString *const NSVoiceIndividuallySpokenCharacters NS_AVAILABLE_MAC(10_5);

// Values for NSVoiceGender voice attribute
APPKIT_EXTERN NSString *const NSVoiceGenderNeuter;
APPKIT_EXTERN NSString *const NSVoiceGenderMale;
APPKIT_EXTERN NSString *const NSVoiceGenderFemale;

// NSVoiceLanguage has been replaced by NSVoiceLocaleIdentifier
APPKIT_EXTERN NSString *const NSVoiceLanguage NS_DEPRECATED_MAC(10_0, 10_5);

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5
// Values for NSSpeechBoundary
enum {
    NSSpeechImmediateBoundary =  0,
    NSSpeechWordBoundary,
    NSSpeechSentenceBoundary
};
#endif
typedef NSUInteger NSSpeechBoundary;


@interface NSSpeechSynthesizer : NSObject {
@private // All instance variables are private
    id	_privateNSSpeechSynthesizerVars;
}

- (id)initWithVoice:(NSString *)voice;

- (BOOL)startSpeakingString:(NSString *)string;
- (BOOL)startSpeakingString:(NSString *)string toURL:(NSURL *)url;

- (BOOL)isSpeaking;
- (void)stopSpeaking;
- (void)stopSpeakingAtBoundary:(NSSpeechBoundary)boundary NS_AVAILABLE_MAC(10_5);
- (void)pauseSpeakingAtBoundary:(NSSpeechBoundary)boundary NS_AVAILABLE_MAC(10_5);
- (void)continueSpeaking NS_AVAILABLE_MAC(10_5);

- (id <NSSpeechSynthesizerDelegate>)delegate;
- (void)setDelegate:(id <NSSpeechSynthesizerDelegate>)anObject;
- (NSString *)voice;
- (BOOL)setVoice:(NSString *)voice;
- (float)rate NS_AVAILABLE_MAC(10_5);
- (void)setRate:(float)rate NS_AVAILABLE_MAC(10_5);
- (float)volume NS_AVAILABLE_MAC(10_5);
- (void)setVolume:(float)volume NS_AVAILABLE_MAC(10_5);
- (BOOL)usesFeedbackWindow;
- (void)setUsesFeedbackWindow:(BOOL)flag;

- (void)addSpeechDictionary:(NSDictionary*)speechDictionary NS_AVAILABLE_MAC(10_5);
- (NSString *)phonemesFromText:(NSString *)text NS_AVAILABLE_MAC(10_5);

- (id)objectForProperty:(NSString *)property error:(NSError **)outError NS_AVAILABLE_MAC(10_5);
- (BOOL)setObject:(id)object forProperty:(NSString *)property error:(NSError **)outError NS_AVAILABLE_MAC(10_5);

+ (BOOL)isAnyApplicationSpeaking;
+ (NSString *)defaultVoice;
+ (NSArray *)availableVoices;
+ (NSDictionary *)attributesForVoice:(NSString*)voice;

@end

@protocol NSSpeechSynthesizerDelegate <NSObject>
@optional
- (void)speechSynthesizer:(NSSpeechSynthesizer *)sender didFinishSpeaking:(BOOL)finishedSpeaking;
- (void)speechSynthesizer:(NSSpeechSynthesizer *)sender willSpeakWord:(NSRange)characterRange ofString:(NSString *)string;
- (void)speechSynthesizer:(NSSpeechSynthesizer *)sender willSpeakPhoneme:(short)phonemeOpcode;
- (void)speechSynthesizer:(NSSpeechSynthesizer *)sender didEncounterErrorAtIndex:(NSUInteger)characterIndex ofString:(NSString *)string message:(NSString *)message NS_AVAILABLE_MAC(10_5);
- (void)speechSynthesizer:(NSSpeechSynthesizer *)sender didEncounterSyncMessage:(NSString *)message NS_AVAILABLE_MAC(10_5);
@end

// Synthesizer Properties (including object type)
APPKIT_EXTERN NSString *const NSSpeechStatusProperty NS_AVAILABLE_MAC(10_5);  // NSDictionary, see keys below
APPKIT_EXTERN NSString *const NSSpeechErrorsProperty NS_AVAILABLE_MAC(10_5);  // NSDictionary, see keys below
APPKIT_EXTERN NSString *const NSSpeechInputModeProperty NS_AVAILABLE_MAC(10_5);  // NSString: NSSpeechModeTextProperty or NSSpeechModePhonemeProperty
APPKIT_EXTERN NSString *const NSSpeechCharacterModeProperty NS_AVAILABLE_MAC(10_5); // NSString: NSSpeechModeNormalProperty or NSSpeechModeLiteralProperty
APPKIT_EXTERN NSString *const NSSpeechNumberModeProperty NS_AVAILABLE_MAC(10_5); // NSString: NSSpeechModeNormalProperty or NSSpeechModeLiteralProperty
APPKIT_EXTERN NSString *const NSSpeechRateProperty NS_AVAILABLE_MAC(10_5);  // NSNumber
APPKIT_EXTERN NSString *const NSSpeechPitchBaseProperty NS_AVAILABLE_MAC(10_5);  // NSNumber
APPKIT_EXTERN NSString *const NSSpeechPitchModProperty NS_AVAILABLE_MAC(10_5);  // NSNumber
APPKIT_EXTERN NSString *const NSSpeechVolumeProperty NS_AVAILABLE_MAC(10_5);  // NSNumber
APPKIT_EXTERN NSString *const NSSpeechSynthesizerInfoProperty NS_AVAILABLE_MAC(10_5);  // NSDictionary, see keys below
APPKIT_EXTERN NSString *const NSSpeechRecentSyncProperty NS_AVAILABLE_MAC(10_5);  // NSNumber
APPKIT_EXTERN NSString *const NSSpeechPhonemeSymbolsProperty NS_AVAILABLE_MAC(10_5);  // NSDictionary, see keys below
APPKIT_EXTERN NSString *const NSSpeechCurrentVoiceProperty NS_AVAILABLE_MAC(10_5);  // NSString
APPKIT_EXTERN NSString *const NSSpeechCommandDelimiterProperty NS_AVAILABLE_MAC(10_5);  // NSDictionary, see keys below
APPKIT_EXTERN NSString *const NSSpeechResetProperty NS_AVAILABLE_MAC(10_5);
APPKIT_EXTERN NSString *const NSSpeechOutputToFileURLProperty NS_AVAILABLE_MAC(10_5);  // NSURL

// Speaking Modes for NSSpeechInputModeProperty
APPKIT_EXTERN NSString *const NSSpeechModeText NS_AVAILABLE_MAC(10_5);
APPKIT_EXTERN NSString *const NSSpeechModePhoneme NS_AVAILABLE_MAC(10_5);

// Speaking Modes for NSSpeechInputModeProperty and NSSpeechNumberModeProperty
APPKIT_EXTERN NSString *const NSSpeechModeNormal NS_AVAILABLE_MAC(10_5);
APPKIT_EXTERN NSString *const NSSpeechModeLiteral NS_AVAILABLE_MAC(10_5);

// Dictionary keys returned by NSSpeechStatusProperty
APPKIT_EXTERN NSString *const NSSpeechStatusOutputBusy NS_AVAILABLE_MAC(10_5);  // NSNumber
APPKIT_EXTERN NSString *const NSSpeechStatusOutputPaused NS_AVAILABLE_MAC(10_5);  // NSNumber
APPKIT_EXTERN NSString *const NSSpeechStatusNumberOfCharactersLeft NS_AVAILABLE_MAC(10_5);  // NSNumber
APPKIT_EXTERN NSString *const NSSpeechStatusPhonemeCode NS_AVAILABLE_MAC(10_5);  // NSNumber

// Dictionary keys returned by NSSpeechErrorProperty
APPKIT_EXTERN NSString *const NSSpeechErrorCount NS_AVAILABLE_MAC(10_5);  // NSNumber
APPKIT_EXTERN NSString *const NSSpeechErrorOldestCode NS_AVAILABLE_MAC(10_5);  // NSNumber
APPKIT_EXTERN NSString *const NSSpeechErrorOldestCharacterOffset NS_AVAILABLE_MAC(10_5);  // NSNumber
APPKIT_EXTERN NSString *const NSSpeechErrorNewestCode NS_AVAILABLE_MAC(10_5);  // NSNumber
APPKIT_EXTERN NSString *const NSSpeechErrorNewestCharacterOffset NS_AVAILABLE_MAC(10_5);  // NSNumber

// Dictionary keys returned by NSSpeechSynthesizerInfoProperty
APPKIT_EXTERN NSString *const NSSpeechSynthesizerInfoIdentifier NS_AVAILABLE_MAC(10_5);  // NSString
APPKIT_EXTERN NSString *const NSSpeechSynthesizerInfoVersion NS_AVAILABLE_MAC(10_5);  // NSString

// Dictionary keys returned by NSSpeechPhonemeSymbolsProperty
APPKIT_EXTERN NSString *const NSSpeechPhonemeInfoOpcode NS_AVAILABLE_MAC(10_5);  // NSNumber
APPKIT_EXTERN NSString *const NSSpeechPhonemeInfoSymbol NS_AVAILABLE_MAC(10_5);  // NSString
APPKIT_EXTERN NSString *const NSSpeechPhonemeInfoExample NS_AVAILABLE_MAC(10_5);  // NSString
APPKIT_EXTERN NSString *const NSSpeechPhonemeInfoHiliteStart NS_AVAILABLE_MAC(10_5);  // NSNumber
APPKIT_EXTERN NSString *const NSSpeechPhonemeInfoHiliteEnd NS_AVAILABLE_MAC(10_5);  // NSNumber

// Dictionary keys returned by NSSpeechCommandDelimiterProperty
APPKIT_EXTERN NSString *const NSSpeechCommandPrefix NS_AVAILABLE_MAC(10_5);  // NSString
APPKIT_EXTERN NSString *const NSSpeechCommandSuffix NS_AVAILABLE_MAC(10_5);  // NSString

// Use with addSpeechDictionary:
APPKIT_EXTERN NSString *const NSSpeechDictionaryLocaleIdentifier NS_AVAILABLE_MAC(10_5);  // NSString
APPKIT_EXTERN NSString *const NSSpeechDictionaryModificationDate NS_AVAILABLE_MAC(10_5);  // NSString
APPKIT_EXTERN NSString *const NSSpeechDictionaryPronunciations NS_AVAILABLE_MAC(10_5);  // NSArray
APPKIT_EXTERN NSString *const NSSpeechDictionaryAbbreviations NS_AVAILABLE_MAC(10_5);  // NSArray
APPKIT_EXTERN NSString *const NSSpeechDictionaryEntrySpelling NS_AVAILABLE_MAC(10_5);  // NSString
APPKIT_EXTERN NSString *const NSSpeechDictionaryEntryPhonemes NS_AVAILABLE_MAC(10_5);  // NSString



