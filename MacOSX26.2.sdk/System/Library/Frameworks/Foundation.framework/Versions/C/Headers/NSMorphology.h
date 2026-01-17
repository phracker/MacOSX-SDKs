/*    NSMorphology.h
      Copyright (c) 2021, Apple Inc. All rights reserved.
 */

#import <Foundation/NSObject.h>
#import <Foundation/NSString.h>
#import <Foundation/NSArray.h>
#import <Foundation/NSError.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

typedef NS_ENUM(NSInteger, NSGrammaticalGender) {
    NSGrammaticalGenderNotSet = 0,
    NSGrammaticalGenderFeminine,
    NSGrammaticalGenderMasculine,
    NSGrammaticalGenderNeuter,
} API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0));

typedef NS_ENUM(NSInteger, NSGrammaticalPartOfSpeech) {
    NSGrammaticalPartOfSpeechNotSet = 0,
    NSGrammaticalPartOfSpeechDeterminer,
    NSGrammaticalPartOfSpeechPronoun,
    NSGrammaticalPartOfSpeechLetter,
    NSGrammaticalPartOfSpeechAdverb,
    NSGrammaticalPartOfSpeechParticle,
    NSGrammaticalPartOfSpeechAdjective,
    NSGrammaticalPartOfSpeechAdposition,
    NSGrammaticalPartOfSpeechVerb,
    NSGrammaticalPartOfSpeechNoun,
    NSGrammaticalPartOfSpeechConjunction,
    NSGrammaticalPartOfSpeechNumeral,
    NSGrammaticalPartOfSpeechInterjection,
    NSGrammaticalPartOfSpeechPreposition,
    NSGrammaticalPartOfSpeechAbbreviation,
} API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0));

typedef NS_ENUM(NSInteger, NSGrammaticalNumber) {
    NSGrammaticalNumberNotSet = 0,
    NSGrammaticalNumberSingular,
    NSGrammaticalNumberZero,
    NSGrammaticalNumberPlural,
    NSGrammaticalNumberPluralTwo,
    NSGrammaticalNumberPluralFew,
    NSGrammaticalNumberPluralMany,
} API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0));

typedef NS_ENUM(NSInteger, NSGrammaticalCase) {
    NSGrammaticalCaseNotSet = 0,
    NSGrammaticalCaseNominative,
    NSGrammaticalCaseAccusative,
    NSGrammaticalCaseDative,
    NSGrammaticalCaseGenitive,
    NSGrammaticalCasePrepositional,
    NSGrammaticalCaseAblative,
    NSGrammaticalCaseAdessive,
    NSGrammaticalCaseAllative,
    NSGrammaticalCaseElative,
    NSGrammaticalCaseIllative,
    NSGrammaticalCaseEssive,
    NSGrammaticalCaseInessive,
    NSGrammaticalCaseLocative,
    NSGrammaticalCaseTranslative
} API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0));

typedef NS_ENUM(NSInteger, NSGrammaticalPronounType) {
    NSGrammaticalPronounTypeNotSet = 0,
    NSGrammaticalPronounTypePersonal,
    NSGrammaticalPronounTypeReflexive,
    NSGrammaticalPronounTypePossessive
} API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0));

typedef NS_ENUM(NSInteger, NSGrammaticalPerson) {
    NSGrammaticalPersonNotSet = 0,
    NSGrammaticalPersonFirst,
    NSGrammaticalPersonSecond,
    NSGrammaticalPersonThird
} API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0));

typedef NS_ENUM(NSInteger, NSGrammaticalDetermination) {
    NSGrammaticalDeterminationNotSet = 0,
    NSGrammaticalDeterminationIndependent,
    NSGrammaticalDeterminationDependent
} API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0));

typedef NS_ENUM(NSInteger, NSGrammaticalDefiniteness) {
    NSGrammaticalDefinitenessNotSet = 0,
    NSGrammaticalDefinitenessIndefinite,
    NSGrammaticalDefinitenessDefinite
} API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0));

API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0))
NS_REFINED_FOR_SWIFT
@interface NSMorphology: NSObject <NSCopying, NSSecureCoding>

@property (nonatomic) NSGrammaticalGender grammaticalGender;
@property (nonatomic) NSGrammaticalPartOfSpeech partOfSpeech;
@property (nonatomic) NSGrammaticalNumber number;
@property (nonatomic) NSGrammaticalCase grammaticalCase API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0));
@property (nonatomic) NSGrammaticalDetermination determination API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0));
@property (nonatomic) NSGrammaticalPerson grammaticalPerson API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0));
@property (nonatomic) NSGrammaticalPronounType pronounType API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0));
@property (nonatomic) NSGrammaticalDefiniteness definiteness API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0));

@end

API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0))
NS_REFINED_FOR_SWIFT
@interface NSMorphologyPronoun : NSObject <NSCopying, NSSecureCoding>
+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;
- (instancetype)initWithPronoun:(NSString*)pronoun
                     morphology:(NSMorphology*)morphology
            dependentMorphology:(nullable NSMorphology*)dependentMorphology;

@property (readonly, copy) NSString* pronoun;
@property (readonly, copy) NSMorphology* morphology;
@property (readonly, copy, nullable) NSMorphology* dependentMorphology;
@end

// Per-language attribute support:

@class NSMorphologyCustomPronoun;

API_DEPRECATED("Use NSTermOfAddress instead", macos(12.0,14.0), ios(15.0,17.0), tvos(15.0,17.0), watchos(8.0,10.0))
@interface NSMorphology (NSCustomPronouns)

- (nullable NSMorphologyCustomPronoun *)customPronounForLanguage:(NSString *)language
API_DEPRECATED("Use NSTermOfAddress instead", macos(12.0,14.0), ios(15.0,17.0), tvos(15.0,17.0), watchos(8.0,10.0));
- (BOOL)setCustomPronoun:(nullable NSMorphologyCustomPronoun *)features forLanguage:(NSString *)language error:(NSError **)error
API_DEPRECATED("Use NSTermOfAddress instead", macos(12.0,14.0), ios(15.0,17.0), tvos(15.0,17.0), watchos(8.0,10.0));

@end

API_DEPRECATED("Use NSTermOfAddress instead", macos(12.0,14.0), ios(15.0,17.0), tvos(15.0,17.0), watchos(8.0,10.0))
NS_REFINED_FOR_SWIFT
@interface NSMorphologyCustomPronoun: NSObject <NSCopying, NSSecureCoding>

+ (BOOL)isSupportedForLanguage:(NSString *)language;
+ (NSArray<NSString *> *)requiredKeysForLanguage:(NSString *)language;

@property(nullable, copy, nonatomic) NSString *subjectForm;
@property(nullable, copy, nonatomic) NSString *objectForm;
@property(nullable, copy, nonatomic) NSString *possessiveForm;
@property(nullable, copy, nonatomic) NSString *possessiveAdjectiveForm;
@property(nullable, copy, nonatomic) NSString *reflexiveForm;

@end


// User settings access:

@interface NSMorphology (NSMorphologyUserSettings)

// Equivalent to the above.
@property (readonly, getter=isUnspecified) BOOL unspecified
 API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0));

@property (class, readonly) NSMorphology *userMorphology
 API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0));

@end

NS_HEADER_AUDIT_END(nullability, sendability)
