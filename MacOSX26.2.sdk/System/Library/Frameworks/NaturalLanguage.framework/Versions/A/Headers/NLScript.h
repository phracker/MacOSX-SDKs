/*    NLScript.h
      Copyright (c) 2022-2023, Apple Inc. All rights reserved.
*/

#import <Foundation/Foundation.h>

/* An NLScript is a BCP-47 script tag, such as "Latn" for Latin, "Cyrl" for Cyrillic, etc. Constants are provided for a set of scripts, but this list is by no means exhaustive; clients may specify their own values using any script tag.
*/

typedef NSString *NLScript NS_TYPED_EXTENSIBLE_ENUM;

FOUNDATION_EXPORT NLScript const NLScriptUndetermined API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0));

FOUNDATION_EXPORT NLScript const NLScriptArabic API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0));
FOUNDATION_EXPORT NLScript const NLScriptArmenian API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0));
FOUNDATION_EXPORT NLScript const NLScriptBengali API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0));
FOUNDATION_EXPORT NLScript const NLScriptCanadianAboriginalSyllabics API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0));
FOUNDATION_EXPORT NLScript const NLScriptCherokee API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0));
FOUNDATION_EXPORT NLScript const NLScriptCyrillic API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0));
FOUNDATION_EXPORT NLScript const NLScriptDevanagari API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0));
FOUNDATION_EXPORT NLScript const NLScriptEthiopic API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0));
FOUNDATION_EXPORT NLScript const NLScriptGeorgian API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0));
FOUNDATION_EXPORT NLScript const NLScriptGreek API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0));
FOUNDATION_EXPORT NLScript const NLScriptGujarati API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0));
FOUNDATION_EXPORT NLScript const NLScriptGurmukhi API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0));
FOUNDATION_EXPORT NLScript const NLScriptHebrew API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0));
FOUNDATION_EXPORT NLScript const NLScriptJapanese API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0));
FOUNDATION_EXPORT NLScript const NLScriptKannada API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0));
FOUNDATION_EXPORT NLScript const NLScriptKhmer API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0));
FOUNDATION_EXPORT NLScript const NLScriptKorean API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0));
FOUNDATION_EXPORT NLScript const NLScriptLao API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0));
FOUNDATION_EXPORT NLScript const NLScriptLatin API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0));
FOUNDATION_EXPORT NLScript const NLScriptMalayalam API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0));
FOUNDATION_EXPORT NLScript const NLScriptMongolian API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0));
FOUNDATION_EXPORT NLScript const NLScriptMyanmar API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0));
FOUNDATION_EXPORT NLScript const NLScriptOriya API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0));
FOUNDATION_EXPORT NLScript const NLScriptSimplifiedChinese API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0));
FOUNDATION_EXPORT NLScript const NLScriptSinhala API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0));
FOUNDATION_EXPORT NLScript const NLScriptTamil API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0));
FOUNDATION_EXPORT NLScript const NLScriptTelugu API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0));
FOUNDATION_EXPORT NLScript const NLScriptThai API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0));
FOUNDATION_EXPORT NLScript const NLScriptTibetan API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0));
FOUNDATION_EXPORT NLScript const NLScriptTraditionalChinese API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0));
