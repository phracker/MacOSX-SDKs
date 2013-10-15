/*	NSAttributedString.h
	Copyright (c) 1994-2005, Apple, Inc. All rights reserved.
*/

#import <Foundation/NSString.h>
#import <Foundation/NSDictionary.h>

@interface NSAttributedString : NSObject <NSCopying, NSMutableCopying, NSCoding>

- (NSString *)string;
- (NSDictionary *)attributesAtIndex:(unsigned)location effectiveRange:(NSRangePointer)range;

@end

@interface NSAttributedString (NSExtendedAttributedString)

- (unsigned)length;
- (id)attribute:(NSString *)attrName atIndex:(unsigned int)location effectiveRange:(NSRangePointer)range;
- (NSAttributedString *)attributedSubstringFromRange:(NSRange)range;

- (NSDictionary *)attributesAtIndex:(unsigned)location longestEffectiveRange:(NSRangePointer)range inRange:(NSRange)rangeLimit;
- (id)attribute:(NSString *)attrName atIndex:(unsigned int)location longestEffectiveRange:(NSRangePointer)range inRange:(NSRange)rangeLimit;

- (BOOL)isEqualToAttributedString:(NSAttributedString *)other;

- (id)initWithString:(NSString *)str;
- (id)initWithString:(NSString *)str attributes:(NSDictionary *)attrs;
- (id)initWithAttributedString:(NSAttributedString *)attrStr;

@end

@interface NSMutableAttributedString : NSAttributedString

- (void)replaceCharactersInRange:(NSRange)range withString:(NSString *)str;
- (void)setAttributes:(NSDictionary *)attrs range:(NSRange)range;

@end

@interface NSMutableAttributedString (NSExtendedMutableAttributedString)

- (NSMutableString *)mutableString;

- (void)addAttribute:(NSString *)name value:(id)value range:(NSRange)range;
- (void)addAttributes:(NSDictionary *)attrs range:(NSRange)range;
- (void)removeAttribute:(NSString *)name range:(NSRange)range;

- (void)replaceCharactersInRange:(NSRange)range withAttributedString:(NSAttributedString *)attrString;
- (void)insertAttributedString:(NSAttributedString *)attrString atIndex:(unsigned)loc;
- (void)appendAttributedString:(NSAttributedString *)attrString;
- (void)deleteCharactersInRange:(NSRange)range;
- (void)setAttributedString:(NSAttributedString *)attrString;

- (void)beginEditing;
- (void)endEditing;

@end

