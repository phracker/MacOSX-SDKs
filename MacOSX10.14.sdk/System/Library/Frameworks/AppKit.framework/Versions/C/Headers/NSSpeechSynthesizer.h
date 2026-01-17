/*
	NSSpeechSynthesizer.h
	Application Kit
	Copyright (c) 2003-2018, Apple Inc.
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

typedef NSString * NSSpeechSynthesizerVoiceName NS_TYPED_ENUM;

typedef NSString * NSVoiceAttributeKey NS_TYPED_ENUM;
APPKIT_EXTERN NSVoiceAttributeKey const NSVoiceName;
APPKIT_EXTERN NSVoiceAttributeKey const NSVoiceIdentifier;
APPKIT_EXTERN NSVoiceAttributeKey const NSVoiceAge;
APPKIT_EXTERN NSVoiceAttributeKey const NSVoiceGender;
APPKIT_EXTERN NSVoiceAttributeKey const NSVoiceDemoText;
APPKIT_EXTERN NSVoiceAttributeKey const NSVoiceLocaleIdentifier NS_AVAILABLE_MAC(10_5);
APPKIT_EXTERN NSVoiceAttributeKey const NSVoiceSupportedCharacters NS_AVAILABLE_MAC(10_5);
APPKIT_EXTERN NSVoiceAttributeKey const NSVoiceIndividuallySpokenCharacters NS_AVAILABLE_MAC(10_5);

// Use with addSpeechDictionary:
typedef NSString * NSSpeechDictionaryKey NS_TYPED_ENUM;
APPKIT_EXTERN NSSpeechDictionaryKey const NSSpeechDictionaryLocaleIdentifier NS_AVAILABLE_MAC(10_5);  // NSString
APPKIT_EXTERN NSSpeechDictionaryKey const NSSpeechDictionaryModificationDate NS_AVAILABLE_MAC(10_5);  // NSString
APPKIT_EXTERN NSSpeechDictionaryKey const NSSpeechDictionaryPronunciations NS_AVAILABLE_MAC(10_5);  // NSArray
APPKIT_EXTERN NSSpeechDictionaryKey const NSSpeechDictionaryAbbreviations NS_AVAILABLE_MAC(10_5);  // NSArray
APPKIT_EXTERN NSSpeechDictionaryKey const NSSpeechDictionaryEntrySpelling NS_AVAILABLE_MAC(10_5);  // NSString
APPKIT_EXTERN NSSpeechDictionaryKey const NSSpeechDictionaryEntryPhonemes NS_AVAILABLE_MAC(10_5);  // NSString

// Values for NSVoiceGender voice attribute
typedef NSString * NSVoiceGenderName NS_TYPED_ENUM;
APPKIT_EXTERN NSVoiceGenderName const NSVoiceGenderNeuter;
APPKIT_EXTERN NSVoiceGenderName const NSVoiceGenderMale;
APPKIT_EXTERN NSVoiceGenderName const NSVoiceGenderFemale;

// Synthesizer Properties (including object type)
typedef NSString * NSSpeechPropertyKey NS_TYPED_ENUM;
APPKIT_EXTERN NSSpeechPropertyKey const NSSpeechStatusProperty NS_AVAILABLE_MAC(10_5);  // NSDictionary, see keys below
APPKIT_EXTERN NSSpeechPropertyKey const NSSpeechErrorsProperty NS_AVAILABLE_MAC(10_5);  // NSDictionary, see keys below
APPKIT_EXTERN NSSpeechPropertyKey const NSSpeechInputModeProperty NS_AVAILABLE_MAC(10_5);  // NSString: NSSpeechModeTextProperty or NSSpeechModePhonemeProperty
APPKIT_EXTERN NSSpeechPropertyKey const NSSpeechCharacterModeProperty NS_AVAILABLE_MAC(10_5); // NSString: NSSpeechModeNormalProperty or NSSpeechModeLiteralProperty
APPKIT_EXTERN NSSpeechPropertyKey const NSSpeechNumberModeProperty NS_AVAILABLE_MAC(10_5); // NSString: NSSpeechModeNormalProperty or NSSpeechModeLiteralProperty
APPKIT_EXTERN NSSpeechPropertyKey const NSSpeechRateProperty NS_AVAILABLE_MAC(10_5);  // NSNumber
APPKIT_EXTERN NSSpeechPropertyKey const NSSpeechPitchBaseProperty NS_AVAILABLE_MAC(10_5);  // NSNumber
APPKIT_EXTERN NSSpeechPropertyKey const NSSpeechPitchModProperty NS_AVAILABLE_MAC(10_5);  // NSNumber
APPKIT_EXTERN NSSpeechPropertyKey const NSSpeechVolumeProperty NS_AVAILABLE_MAC(10_5);  // NSNumber
APPKIT_EXTERN NSSpeechPropertyKey const NSSpeechSynthesizerInfoProperty NS_AVAILABLE_MAC(10_5);  // NSDictionary, see keys below
APPKIT_EXTERN NSSpeechPropertyKey const NSSpeechRecentSyncProperty NS_AVAILABLE_MAC(10_5);  // NSNumber
APPKIT_EXTERN NSSpeechPropertyKey const NSSpeechPhonemeSymbolsProperty NS_AVAILABLE_MAC(10_5);  // NSDictionary, see keys below
APPKIT_EXTERN NSSpeechPropertyKey const NSSpeechCurrentVoiceProperty NS_AVAILABLE_MAC(10_5);  // NSString
APPKIT_EXTERN NSSpeechPropertyKey const NSSpeechCommandDelimiterProperty NS_AVAILABLE_MAC(10_5);  // NSDictionary, see keys below
APPKIT_EXTERN NSSpeechPropertyKey const NSSpeechResetProperty NS_AVAILABLE_MAC(10_5);
APPKIT_EXTERN NSSpeechPropertyKey const NSSpeechOutputToFileURLProperty NS_AVAILABLE_MAC(10_5);  // NSURL


// NSVoiceLanguage has been replaced by NSVoiceLocaleIdentifier
APPKIT_EXTERN NSVoiceAttributeKey const NSVoiceLanguage NS_DEPRECATED_MAC(10_0, 10_5);

// Values for NSSpeechBoundary
typedef NS_ENUM(NSUInteger, NSSpeechBoundary) {
    NSSpeechImmediateBoundary =  0,
    NSSpeechWordBoundary,
    NSSpeechSentenceBoundary
} NS_ENUM_AVAILABLE_MAC(10_5);


@interface NSSpeechSynthesizer : NSObject {
@private // All instance variables are private
    id	_privateNSSpeechSynthesizerVars APPKIT_IVAR;
}

- (nullable instancetype)initWithVoice:(nullable NSSpeechSynthesizerVoiceName)voice;

- (BOOL)startSpeakingString:(NSString *)string;
- (BOOL)startSpeakingString:(NSString *)string toURL:(NSURL *)url;

@property (getter=isSpeaking, readonly) BOOL speaking;
- (void)stopSpeaking;
- (void)stopSpeakingAtBoundary:(NSSpeechBoundary)boundary NS_AVAILABLE_MAC(10_5);
- (void)pauseSpeakingAtBoundary:(NSSpeechBoundary)boundary NS_AVAILABLE_MAC(10_5);
- (void)continueSpeaking NS_AVAILABLE_MAC(10_5);

@property (nullable, weak) id<NSSpeechSynthesizerDelegate> delegate;
- (nullable NSSpeechSynthesizerVoiceName)voice;
- (BOOL)setVoice:(nullable NSSpeechSynthesizerVoiceName)voice;
@property float rate NS_AVAILABLE_MAC(10_5);
@property float volume NS_AVAILABLE_MAC(10_5);
@property BOOL usesFeedbackWindow;

- (void)addSpeechDictionary:(NSDictionary<NSSpeechDictionaryKey, id> *)speechDictionary NS_AVAILABLE_MAC(10_5);
- (NSString *)phonemesFromText:(NSString *)text NS_AVAILABLE_MAC(10_5);

- (nullable id)objectForProperty:(NSSpeechPropertyKey)property error:(NSError **)outError NS_AVAILABLE_MAC(10_5);
- (BOOL)setObject:(nullable id)object forProperty:(NSSpeechPropertyKey)property error:(NSError **)outError NS_AVAILABLE_MAC(10_5);

@property (class, readonly, getter=isAnyApplicationSpeaking) BOOL anyApplicationSpeaking;
@property (class, readonly, copy) NSSpeechSynthesizerVoiceName defaultVoice;
@property (class, readonly, copy) NSArray<NSSpeechSynthesizerVoiceName> *availableVoices;
+ (NSDictionary<NSVoiceAttributeKey, id> *)attributesForVoice:(NSSpeechSynthesizerVoiceName)voice;

@end

@protocol NSSpeechSynthesizerDelegate <NSObject>
@optional
- (void)speechSynthesizer:(NSSpeechSynthesizer *)sender didFinishSpeaking:(BOOL)finishedSpeaking;
- (void)speechSynthesizer:(NSSpeechSynthesizer *)sender willSpeakWord:(NSRange)characterRange ofString:(NSString *)string;
- (void)speechSynthesizer:(NSSpeechSynthesizer *)sender willSpeakPhoneme:(short)phonemeOpcode;
- (void)speechSynthesizer:(NSSpeechSynthesizer *)sender didEncounterErrorAtIndex:(NSUInteger)characterIndex ofString:(NSString *)string message:(NSString *)message NS_AVAILABLE_MAC(10_5);
- (void)speechSynthesizer:(NSSpeechSynthesizer *)sender didEncounterSyncMessage:(NSString *)message NS_AVAILABLE_MAC(10_5);
@end

typedef NSString * NSSpeechMode NS_TYPED_ENUM;
// Speaking Modes for NSSpeechInputModeProperty
APPKIT_EXTERN NSSpeechMode const NSSpeechModeText NS_AVAILABLE_MAC(10_5);
APPKIT_EXTERN NSSpeechMode const NSSpeechModePhoneme NS_AVAILABLE_MAC(10_5);
// Speaking Modes for NSSpeechInputModeProperty and NSSpeechNumberModeProperty
APPKIT_EXTERN NSSpeechMode const NSSpeechModeNormal NS_AVAILABLE_MAC(10_5);
APPKIT_EXTERN NSSpeechMode const NSSpeechModeLiteral NS_AVAILABLE_MAC(10_5);

// Dictionary keys returned by NSSpeechStatusProperty
typedef NSString * NSSpeechStatusKey NS_TYPED_ENUM;
APPKIT_EXTERN NSSpeechStatusKey const NSSpeechStatusOutputBusy NS_AVAILABLE_MAC(10_5);  // NSNumber
APPKIT_EXTERN NSSpeechStatusKey const NSSpeechStatusOutputPaused NS_AVAILABLE_MAC(10_5);  // NSNumber
APPKIT_EXTERN NSSpeechStatusKey const NSSpeechStatusNumberOfCharactersLeft NS_AVAILABLE_MAC(10_5);  // NSNumber
APPKIT_EXTERN NSSpeechStatusKey const NSSpeechStatusPhonemeCode NS_AVAILABLE_MAC(10_5);  // NSNumber

// Dictionary keys returned by NSSpeechErrorProperty
typedef NSString * NSSpeechErrorKey NS_TYPED_ENUM;
APPKIT_EXTERN NSSpeechErrorKey const NSSpeechErrorCount NS_AVAILABLE_MAC(10_5);  // NSNumber
APPKIT_EXTERN NSSpeechErrorKey const NSSpeechErrorOldestCode NS_AVAILABLE_MAC(10_5);  // NSNumber
APPKIT_EXTERN NSSpeechErrorKey const NSSpeechErrorOldestCharacterOffset NS_AVAILABLE_MAC(10_5);  // NSNumber
APPKIT_EXTERN NSSpeechErrorKey const NSSpeechErrorNewestCode NS_AVAILABLE_MAC(10_5);  // NSNumber
APPKIT_EXTERN NSSpeechErrorKey const NSSpeechErrorNewestCharacterOffset NS_AVAILABLE_MAC(10_5);  // NSNumber

// Dictionary keys returned by NSSpeechSynthesizerInfoProperty
typedef NSString * NSSpeechSynthesizerInfoKey NS_TYPED_ENUM;
APPKIT_EXTERN NSSpeechSynthesizerInfoKey const NSSpeechSynthesizerInfoIdentifier NS_AVAILABLE_MAC(10_5);  // NSString
APPKIT_EXTERN NSSpeechSynthesizerInfoKey const NSSpeechSynthesizerInfoVersion NS_AVAILABLE_MAC(10_5);  // NSString

// Dictionary keys returned by NSSpeechPhonemeSymbolsProperty
typedef NSString * NSSpeechPhonemeInfoKey NS_TYPED_ENUM;
APPKIT_EXTERN NSSpeechPhonemeInfoKey const NSSpeechPhonemeInfoOpcode NS_AVAILABLE_MAC(10_5);  // NSNumber
APPKIT_EXTERN NSSpeechPhonemeInfoKey const NSSpeechPhonemeInfoSymbol NS_AVAILABLE_MAC(10_5);  // NSString
APPKIT_EXTERN NSSpeechPhonemeInfoKey const NSSpeechPhonemeInfoExample NS_AVAILABLE_MAC(10_5);  // NSString
APPKIT_EXTERN NSSpeechPhonemeInfoKey const NSSpeechPhonemeInfoHiliteStart NS_AVAILABLE_MAC(10_5);  // NSNumber
APPKIT_EXTERN NSSpeechPhonemeInfoKey const NSSpeechPhonemeInfoHiliteEnd NS_AVAILABLE_MAC(10_5);  // NSNumber

// Dictionary keys returned by NSSpeechCommandDelimiterProperty
typedef NSString * NSSpeechCommandDelimiterKey NS_TYPED_ENUM;
APPKIT_EXTERN NSSpeechCommandDelimiterKey const NSSpeechCommandPrefix NS_AVAILABLE_MAC(10_5);  // NSString
APPKIT_EXTERN NSSpeechCommandDelimiterKey const NSSpeechCommandSuffix NS_AVAILABLE_MAC(10_5);  // NSString

NS_ASSUME_NONNULL_END



