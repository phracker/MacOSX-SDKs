//
//  AXBrailleTranslator.h
//  Accessibility
//
//  Copyright © 2025 Apple. All rights reserved.
//

#import <Accessibility/AXFoundation.h>

NS_ASSUME_NONNULL_BEGIN

/// A rule for translating print text to Braille, and back-translating Braille to print text.
AX_EXTERN API_AVAILABLE(ios(26.0), macos(26.0), tvos(26.0), watchos(26.0), visionos(26.0))
@interface AXBrailleTable: NSObject <NSCopying, NSCoding>

/// A unique string that identifies this table.
@property (nonatomic, readonly) NSString *identifier;

/// The localized name of this table for user display.
@property (nonatomic, readonly) NSString *localizedName;

/// The identifier of the provider of this table.
@property (nonatomic, readonly) NSString *providerIdentifier;

/// The localized name of the provider of this table for user display.
@property (nonatomic, readonly) NSString *localizedProviderName;

/// The 3-character code from ISO 639-2 for the language this Braille table pertains to.
@property (nonatomic, readonly) NSString *language NS_REFINED_FOR_SWIFT;

/// All locales this table supports.
@property (nonatomic, readonly) NSSet<NSLocale *> *locales;

/// Returns true if this table makes use of eight dots as opposed to six dots.
@property (nonatomic, readonly) BOOL isEightDot;

/// All locales supported by existing tables.
+ (NSSet<NSLocale *> *)supportedLocales;

/// The default table that provides translations for the given locale's language. Returns nil if there is none.
+ (nullable AXBrailleTable *)defaultTableForLocale:(NSLocale *)locale;

/// All tables that provide translations for the given locale's language.
+ (NSSet<AXBrailleTable *> *)tablesForLocale:(NSLocale *)locale;

/// All tables that are not specific to any language.
+ (NSSet<AXBrailleTable *> *)languageAgnosticTables;

/// Returns nil if there is no table with the given identifier.
- (nullable instancetype)initWithIdentifier:(NSString *)identifier;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;
@end

/// The result of translation or back-translation.
AX_EXTERN API_AVAILABLE(ios(26.0), macos(26.0), tvos(26.0), watchos(26.0), visionos(26.0))
@interface AXBrailleTranslationResult : NSObject <NSCopying, NSCoding>

/// The resulting string after translation or back-translation.
@property (nonatomic, readonly) NSString *resultString;

/// An array of integers that has the same length as the resultString.
/// locationMap[i]-th character in the input string corresponds to resultString[i].
@property (nonatomic, readonly) NSArray<NSNumber *> *locationMap NS_REFINED_FOR_SWIFT;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

/// Translates print text to Braille and Braille to print text according to the given Braille table.
AX_EXTERN API_AVAILABLE(ios(26.0), macos(26.0), tvos(26.0), watchos(26.0), visionos(26.0))
@interface AXBrailleTranslator : NSObject

- (instancetype)initWithBrailleTable:(AXBrailleTable *)brailleTable;

/// Output Braille uses the unicode Braille characters (0x2800-0x28FF).
- (AXBrailleTranslationResult *)translatePrintText:(NSString *)printText;

/// Input Braille should use the unicode Braille characters (0x2800-0x28FF).
- (AXBrailleTranslationResult *)backTranslateBraille:(NSString *)braille;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
