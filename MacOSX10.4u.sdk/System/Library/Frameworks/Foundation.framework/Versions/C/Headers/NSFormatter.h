/*	NSFormatter.h
	Copyright (c) 1995-2005, Apple, Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSRange.h>

@class NSString;
@class NSAttributedString;
@class NSDictionary;

@interface NSFormatter : NSObject <NSCopying, NSCoding>

- (NSString *)stringForObjectValue:(id)obj;

- (NSAttributedString *)attributedStringForObjectValue:(id)obj withDefaultAttributes:(NSDictionary *)attrs;

- (NSString *)editingStringForObjectValue:(id)obj;

- (BOOL)getObjectValue:(id *)obj forString:(NSString *)string errorDescription:(NSString **)error;

- (BOOL)isPartialStringValid:(NSString *)partialString newEditingString:(NSString **)newString errorDescription:(NSString **)error;
    // Compatibility method.  If a subclass overrides this and does not override the new method below, this will be called as before (the new method just calls this one by default).  The selection range will always be set to the end of the text with this method if replacement occurs.

- (BOOL)isPartialStringValid:(NSString **)partialStringPtr proposedSelectedRange:(NSRangePointer)proposedSelRangePtr originalString:(NSString *)origString originalSelectedRange:(NSRange)origSelRange errorDescription:(NSString **)error;

@end

