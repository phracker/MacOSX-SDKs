/*	NSFormatter.h
	Copyright (c) 1995-2014, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSRange.h>

@class NSString;
@class NSAttributedString;
@class NSDictionary;

typedef NS_ENUM(NSInteger, NSFormattingContext) {
    
    // The capitalization context to be used is unknown (this is the default value).
    NSFormattingContextUnknown = 0,
    
    // The capitalization context is determined dynamically from the set {NSFormattingContextStandalone, NSFormattingContextBeginningOfSentence, NSFormattingContextMiddleOfSentence}. For example, if a date is placed at the beginning of a sentence, NSFormattingContextBeginningOfSentence is used to format the string automatically. When this context is used, the formatter will return a string proxy that works like a normal string in most cases. After returning from the formatter, the string in the string proxy is formatted by using NSFormattingContextUnknown. When the string proxy is used in stringWithFormat:, we can determine where the %@ is and then set the context accordingly. With the new context, the string in the string proxy will be formatted again and be put into the final string returned from stringWithFormat:.
    NSFormattingContextDynamic = 1,
    
    // The capitalization context if a date or date symbol is to be formatted with capitalization appropriate for stand-alone usage such as an isolated name on a calendar page.
    NSFormattingContextStandalone = 2,
    
    // The capitalization context if a date or date symbol is to be formatted with capitalization appropriate for a list or menu item.
    NSFormattingContextListItem = 3,
    
    // The capitalization context if a date or date symbol is to be formatted with capitalization appropriate for the beginning of a sentence.
    NSFormattingContextBeginningOfSentence = 4,
    
    // The capitalization context if a date or date symbol is to be formatted with capitalization appropriate for the middle of a sentence.
    NSFormattingContextMiddleOfSentence = 5,
    
} NS_ENUM_AVAILABLE(10_10, 8_0);

/*
 * There are 3 widths: long, medium, and short.
 * For example, for English, when formatting "3 pounds"
 * Long is "3 pounds"; medium is "3 lb"; short is "3#”;
 */
typedef NS_ENUM(NSInteger, NSFormattingUnitStyle) {
    NSFormattingUnitStyleShort = 1,
    NSFormattingUnitStyleMedium,
    NSFormattingUnitStyleLong,
} NS_ENUM_AVAILABLE(10_10, 8_0);

@interface NSFormatter : NSObject <NSCopying, NSCoding>

- (NSString *)stringForObjectValue:(id)obj;

- (NSAttributedString *)attributedStringForObjectValue:(id)obj withDefaultAttributes:(NSDictionary *)attrs;

- (NSString *)editingStringForObjectValue:(id)obj;

- (BOOL)getObjectValue:(out id *)obj forString:(NSString *)string errorDescription:(out NSString **)error;

- (BOOL)isPartialStringValid:(NSString *)partialString newEditingString:(NSString **)newString errorDescription:(NSString **)error;
    // Compatibility method.  If a subclass overrides this and does not override the new method below, this will be called as before (the new method just calls this one by default).  The selection range will always be set to the end of the text with this method if replacement occurs.

- (BOOL)isPartialStringValid:(NSString **)partialStringPtr proposedSelectedRange:(NSRangePointer)proposedSelRangePtr originalString:(NSString *)origString originalSelectedRange:(NSRange)origSelRange errorDescription:(NSString **)error;

@end

