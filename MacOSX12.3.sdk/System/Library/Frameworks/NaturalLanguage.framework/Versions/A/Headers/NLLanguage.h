/*    NLLanguage.h
      Copyright (c) 2017-2020, Apple Inc. All rights reserved.
*/

#import <Foundation/Foundation.h>

/* An NLLanguage is a BCP-47 language tag, such as "en" for English, "fr" for French, etc. Constants are provided for a set of languages, but this list is by no means exhaustive; clients may specify their own values using any language tag.
*/

typedef NSString *NLLanguage NS_TYPED_EXTENSIBLE_ENUM;

FOUNDATION_EXPORT NLLanguage const NLLanguageUndetermined API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));

FOUNDATION_EXPORT NLLanguage const NLLanguageAmharic API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguageArabic API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguageArmenian API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguageBengali API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguageBulgarian API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguageBurmese API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguageCatalan API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguageCherokee API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguageCroatian API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguageCzech API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguageDanish API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguageDutch API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguageEnglish API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguageFinnish API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguageFrench API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguageGeorgian API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguageGerman API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguageGreek API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguageGujarati API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguageHebrew API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguageHindi API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguageHungarian API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguageIcelandic API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguageIndonesian API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguageItalian API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguageJapanese API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguageKannada API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguageKhmer API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguageKorean API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguageLao API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguageMalay API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguageMalayalam API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguageMarathi API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguageMongolian API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguageNorwegian API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguageOriya API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguagePersian API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguagePolish API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguagePortuguese API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguagePunjabi API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguageRomanian API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguageRussian API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguageSimplifiedChinese API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguageSinhalese API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguageSlovak API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguageSpanish API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguageSwedish API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguageTamil API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguageTelugu API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguageThai API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguageTibetan API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguageTraditionalChinese API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguageTurkish API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguageUkrainian API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguageUrdu API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguageVietnamese API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
