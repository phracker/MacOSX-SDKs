//
//  NSTermOfAddress.h
//  Foundation
//
//  Copyright (c) 2022, Apple Inc.
//

#import <Foundation/NSString.h>
#import <Foundation/NSMorphology.h>
#import <Foundation/NSArray.h>
#import <Foundation/NSCoder.h>


NS_HEADER_AUDIT_BEGIN(nullability, sendability)

API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0))
NS_REFINED_FOR_SWIFT
@interface NSTermOfAddress : NSObject <NSCopying, NSSecureCoding>

/**
 * Term of address that uses gender-neutral pronouns (e.g. they/them/theirs in
 * English), and an epicene grammatical gender when inflecting verbs and 
 * adjectives referring to the person
 */
+ (instancetype)neutral;
/**
 * Term of address that uses feminine pronouns (e.g. she/her/hers in English),
 * and a feminine grammatical gender when inflecting verbs and adjectives
 * referring to the person
 */
+ (instancetype)feminine;
/**
 * Term of address that uses masculine pronouns (e.g. he/him/his in English),
 * and a masculine grammatical gender when inflecting verbs and adjectives
 * referring to the person
 */
+ (instancetype)masculine;

/**
 * The term of address that should be used for addressing the user
 *
 * This term of address will only compare equal to another `+[NSTermOfAddress currentUser]`
 */
+ (instancetype)currentUser API_AVAILABLE(macos(15.0), ios(18.0), tvos(18.0), watchos(11.0), visionos(2.0));

/**
 * A term of address restricted to a given language
 * @param language ISO language code identifier for the language
 * @param pronouns A list of pronouns in the target language that can be used to
 *                 refer to the person.
 */
+ (instancetype)localizedForLanguageIdentifier:(NSString*)language
                                  withPronouns:(NSArray<NSMorphologyPronoun*>*)pronouns;

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/// The ISO language code if this is a localized term of address
@property(nullable, readonly, copy) NSString* languageIdentifier;
/// A list of pronouns for a localized term of address
@property(nullable, readonly, copy) NSArray<NSMorphologyPronoun*>* pronouns;
@end

NS_HEADER_AUDIT_END(nullability, sendability)
