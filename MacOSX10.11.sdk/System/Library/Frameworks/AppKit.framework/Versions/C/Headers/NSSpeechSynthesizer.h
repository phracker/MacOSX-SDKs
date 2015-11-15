/*
	NSSpeechSynthesizer.h
	Application Kit
	Copyright (c) 2003-2015, Apple Inc.
	All rights reserved.
*/

#import <AppKit/AppKitDefines.h>
#import <Foundation/NSObject.h>
#import <Foundation/NSArray.h>
#import <Foundation/NSDictionary.h>
#import <Foundation/NSRange.h>

NS_ASSUME_NONNULL_BEGIN

@class NSString, NSURL, NSError;
@protocol NSSpeechSynthesizerDelegate;

APPKIT_EXTERN NSString * const NSVoiceName;
APPKIT_EXTERN NSString * const NSVoiceIdentifier;
APPKIT_EXTERN NSString * const NSVoiceAge;
APPKIT_EXTERN NSString * const NSVoiceGender;
APPKIT_EXTERN NSString * const NSVoiceDemoText;
APPKIT_EXTERN NSString * const NSVoiceLocaleIdentifier NS_AVAILABLE_MAC(10_5);
APPKIT_EXTERN NSString * const NSVoiceSupportedCharacters NS_AVAILABLE_MAC(10_5);
APPKIT_EXTERN NSString * const NSVoiceIndividuallySpokenCharacters NS_AVAILABLE_MAC(10_5);

// Values for NSVoiceGender voice attribute
APPKIT_EXTERN NSString * const NSVoiceGenderNeuter;
APPKIT_EXTERN NSString * const NSVoiceGenderMale;
APPKIT_EXTERN NSString * const NSVoiceGenderFemale;

// NSVoiceLanguage has been replaced by NSVoiceLocaleIdentifier
APPKIT_EXTERN NSString * const NSVoiceLanguage NS_DEPRECATED_MAC(10_0, 10_5);

// Values for NSSpeechBoundary
typedef NS_ENUM(NSUInteger, NSSpeechBoundary) {
    NSSpeechImmediateBoundary =  0,
    NSSpeechWordBoundary,
    NSSpeechSentenceBoundary
} NS_ENUM_AVAILABLE_MAC(10_5);


@interface NSSpeechSynthesizer : NSObject {
@private // All instance variables are private
    id	_privateNSSpeechSynthesizerVars;
}

- (nullable instancetype)initWithVoice:(nullable NSString *)voice;

- (BOOL)startSpeakingString:(NSString *)string;
- (BOOL)startSpeakingString:(NSString *)string toURL:(NSURL *)url;

@property (getter=isSpeaking, readonly) BOOL speaking;
- (void)stopSpeaking;
- (void)stopSpeakingAtBoundary:(NSSpeechBoundary)boundary NS_AVAILABLE_MAC(10_5);
- (void)pauseSpeakingAtBoundary:(NSSpeechBoundary)boundary NS_AVAILABLE_MAC(10_5);
- (void)continueSpeaking NS_AVAILABLE_MAC(10_5);

@property (nullable, assign) id<NSSpeechSynthesizerDelegate> delegate;
- (nullable NSString *)voice;
- (BOOL)setVoice:(nullable NSString *)voice;
@property float rate NS_AVAILABLE_MAC(10_5);
@property float volume NS_AVAILABLE_MAC(10_5);
@property BOOL usesFeedbackWindow;

- (void)addSpeechDictionary:(NSDictionary<NSString *, id> *)speechDictionary NS_AVAILABLE_MAC(10_5);
- (NSString *)phonemesFromText:(NSString *)text NS_AVAILABLE_MAC(10_5);

- (nullable id)objectForProperty:(NSString *)property error:(NSError **)outError NS_AVAILABLE_MAC(10_5);
- (BOOL)setObject:(nullable id)object forProperty:(NSString *)property error:(NSError **)outError NS_AVAILABLE_MAC(10_5);

+ (BOOL)isAnyApplicationSpeaking;
+ (NSString *)defaultVoice;
+ (NSArray<NSString *> *)availableVoices;
+ (NSDictionary<NSString *, id> *)attributesForVoice:(NSString *)voice;

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
APPKIT_EXTERN NSString * const NSSpeechStatusProperty NS_AVAILABLE_MAC(10_5);  // NSDictionary, see keys below
APPKIT_EXTERN NSString * const NSSpeechErrorsProperty NS_AVAILABLE_MAC(10_5);  // NSDictionary, see keys below
APPKIT_EXTERN NSString * const NSSpeechInputModeProperty NS_AVAILABLE_MAC(10_5);  // NSString: NSSpeechModeTextProperty or NSSpeechModePhonemeProperty
APPKIT_EXTERN NSString * const NSSpeechCharacterModeProperty NS_AVAILABLE_MAC(10_5); // NSString: NSSpeechModeNormalProperty or NSSpeechModeLiteralProperty
APPKIT_EXTERN NSString * const NSSpeechNumberModeProperty NS_AVAILABLE_MAC(10_5); // NSString: NSSpeechModeNormalProperty or NSSpeechModeLiteralProperty
APPKIT_EXTERN NSString * const NSSpeechRateProperty NS_AVAILABLE_MAC(10_5);  // NSNumber
APPKIT_EXTERN NSString * const NSSpeechPitchBaseProperty NS_AVAILABLE_MAC(10_5);  // NSNumber
APPKIT_EXTERN NSString * const NSSpeechPitchModProperty NS_AVAILABLE_MAC(10_5);  // NSNumber
APPKIT_EXTERN NSString * const NSSpeechVolumeProperty NS_AVAILABLE_MAC(10_5);  // NSNumber
APPKIT_EXTERN NSString * const NSSpeechSynthesizerInfoProperty NS_AVAILABLE_MAC(10_5);  // NSDictionary, see keys below
APPKIT_EXTERN NSString * const NSSpeechRecentSyncProperty NS_AVAILABLE_MAC(10_5);  // NSNumber
APPKIT_EXTERN NSString * const NSSpeechPhonemeSymbolsProperty NS_AVAILABLE_MAC(10_5);  // NSDictionary, see keys below
APPKIT_EXTERN NSString * const NSSpeechCurrentVoiceProperty NS_AVAILABLE_MAC(10_5);  // NSString
APPKIT_EXTERN NSString * const NSSpeechCommandDelimiterProperty NS_AVAILABLE_MAC(10_5);  // NSDictionary, see keys below
APPKIT_EXTERN NSString * const NSSpeechResetProperty NS_AVAILABLE_MAC(10_5);
APPKIT_EXTERN NSString * const NSSpeechOutputToFileURLProperty NS_AVAILABLE_MAC(10_5);  // NSURL

// Speaking Modes for NSSpeechInputModeProperty
APPKIT_EXTERN NSString * const NSSpeechModeText NS_AVAILABLE_MAC(10_5);
APPKIT_EXTERN NSString * const NSSpeechModePhoneme NS_AVAILABLE_MAC(10_5);

// Speaking Modes for NSSpeechInputModeProperty and NSSpeechNumberModeProperty
APPKIT_EXTERN NSString * const NSSpeechModeNormal NS_AVAILABLE_MAC(10_5);
APPKIT_EXTERN NSString * const NSSpeechModeLiteral NS_AVAILABLE_MAC(10_5);

// Dictionary keys returned by NSSpeechStatusProperty
APPKIT_EXTERN NSString * const NSSpeechStatusOutputBusy NS_AVAILABLE_MAC(10_5);  // NSNumber
APPKIT_EXTERN NSString * const NSSpeechStatusOutputPaused NS_AVAILABLE_MAC(10_5);  // NSNumber
APPKIT_EXTERN NSString * const NSSpeechStatusNumberOfCharactersLeft NS_AVAILABLE_MAC(10_5);  // NSNumber
APPKIT_EXTERN NSString * const NSSpeechStatusPhonemeCode NS_AVAILABLE_MAC(10_5);  // NSNumber

// Dictionary keys returned by NSSpeechErrorProperty
APPKIT_EXTERN NSString * const NSSpeechErrorCount NS_AVAILABLE_MAC(10_5);  // NSNumber
APPKIT_EXTERN NSString * const NSSpeechErrorOldestCode NS_AVAILABLE_MAC(10_5);  // NSNumber
APPKIT_EXTERN NSString * const NSSpeechErrorOldestCharacterOffset NS_AVAILABLE_MAC(10_5);  // NSNumber
APPKIT_EXTERN NSString * const NSSpeechErrorNewestCode NS_AVAILABLE_MAC(10_5);  // NSNumber
APPKIT_EXTERN NSString * const NSSpeechErrorNewestCharacterOffset NS_AVAILABLE_MAC(10_5);  // NSNumber

// Dictionary keys returned by NSSpeechSynthesizerInfoProperty
APPKIT_EXTERN NSString * const NSSpeechSynthesizerInfoIdentifier NS_AVAILABLE_MAC(10_5);  // NSString
APPKIT_EXTERN NSString * const NSSpeechSynthesizerInfoVersion NS_AVAILABLE_MAC(10_5);  // NSString

// Dictionary keys returned by NSSpeechPhonemeSymbolsProperty
APPKIT_EXTERN NSString * const NSSpeechPhonemeInfoOpcode NS_AVAILABLE_MAC(10_5);  // NSNumber
APPKIT_EXTERN NSString * const NSSpeechPhonemeInfoSymbol NS_AVAILABLE_MAC(10_5);  // NSString
APPKIT_EXTERN NSString * const NSSpeechPhonemeInfoExample NS_AVAILABLE_MAC(10_5);  // NSString
APPKIT_EXTERN NSString * const NSSpeechPhonemeInfoHiliteStart NS_AVAILABLE_MAC(10_5);  // NSNumber
APPKIT_EXTERN NSString * const NSSpeechPhonemeInfoHiliteEnd NS_AVAILABLE_MAC(10_5);  // NSNumber

// Dictionary keys returned by NSSpeechCommandDelimiterProperty
APPKIT_EXTERN NSString * const NSSpeechCommandPrefix NS_AVAILABLE_MAC(10_5);  // NSString
APPKIT_EXTERN NSString * const NSSpeechCommandSuffix NS_AVAILABLE_MAC(10_5);  // NSString

// Use with addSpeechDictionary:
APPKIT_EXTERN NSString * const NSSpeechDictionaryLocaleIdentifier NS_AVAILABLE_MAC(10_5);  // NSString
APPKIT_EXTERN NSString * const NSSpeechDictionaryModificationDate NS_AVAILABLE_MAC(10_5);  // NSString
APPKIT_EXTERN NSString * const NSSpeechDictionaryPronunciations NS_AVAILABLE_MAC(10_5);  // NSArray
APPKIT_EXTERN NSString * const NSSpeechDictionaryAbbreviations NS_AVAILABLE_MAC(10_5);  // NSArray
APPKIT_EXTERN NSString * const NSSpeechDictionaryEntrySpelling NS_AVAILABLE_MAC(10_5);  // NSString
APPKIT_EXTERN NSString * const NSSpeechDictionaryEntryPhonemes NS_AVAILABLE_MAC(10_5);  // NSString

NS_ASSUME_NONNULL_END



