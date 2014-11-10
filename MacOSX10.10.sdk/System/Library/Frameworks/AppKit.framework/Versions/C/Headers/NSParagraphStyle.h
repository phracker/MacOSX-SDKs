/*
        NSParagraphStyle.h
        Copyright (c) 1994-2014, Apple Inc.  All rights reserved.

	NSParagraphStyle and NSMutableParagraphStyle hold paragraph style information
	NSTextTab holds information about a single tab stop
*/

#import <Foundation/NSObject.h>
#import <AppKit/NSText.h>

typedef NS_ENUM(NSUInteger, NSTextTabType) {
    NSLeftTabStopType = 0,
    NSRightTabStopType,
    NSCenterTabStopType,
    NSDecimalTabStopType
};

typedef NS_ENUM(NSUInteger, NSLineBreakMode) {		/* What to do with long lines */
    NSLineBreakByWordWrapping = 0,     	/* Wrap at word boundaries, default */
    NSLineBreakByCharWrapping,		/* Wrap at character boundaries */
    NSLineBreakByClipping,		/* Simply clip */
    NSLineBreakByTruncatingHead,	/* Truncate at head of line: "...wxyz" */
    NSLineBreakByTruncatingTail,	/* Truncate at tail of line: "abcd..." */
    NSLineBreakByTruncatingMiddle	/* Truncate middle of line:  "ab...yz" */
};

/* An attribute for NSTextTab options.  The value is NSCharacterSet.  The character set is used to determine the tab column terminating character.  The tab itself and newline characters are implied even if non-existent in the character set.
*/
APPKIT_EXTERN NSString *NSTabColumnTerminatorsAttributeName;

NS_AUTOMATED_REFCOUNT_WEAK_UNAVAILABLE
@interface NSTextTab : NSObject <NSCopying, NSCoding> {
    /*All instance variables are private*/
    struct {
	NSTextAlignment alignment:4;
        unsigned int refCount:24;
        unsigned int unused:4;
#if __LP64__
        unsigned int :32;
#endif
    } _flags;
    CGFloat _location;
    id _reserved;
}

/* Initializes a text tab with the text alignment, location, and options.  The text alignment is used to determine the position of text inside the tab column.  These are the mapping from/to NSTextTabType.

To NSTextTabType:
NSLeftTextAlignment -> NSLeftTabStopType
NSRightTextAlignment -> NSRightTabStopType
NSCenterTextAlignment -> NSCenterTabStopType
NSJustifiedTextAlignment -> NSLeftTabStopType
NSNaturalTextAlignment -> NSLeftTabStopType or NSRightTabStopType depending on the user setting
NSRightTextAlignment w/ terminator -> NSDecimalTabStopType

From NSTextTabType:
NSLeftTabStopType -> NSLeftTextAlignment
NSRightTabStopType -> NSRightTextAlignment
NSCenterTabStopType -> NSCenterTextAlignment
NSDecimalTabStopType -> NSRightTextAlignment with the decimal character for the user setting
*/
- (instancetype)initWithTextAlignment:(NSTextAlignment)alignment location:(CGFloat)loc options:(NSDictionary *)options;

@property (readonly) NSTextAlignment alignment;
@property (readonly, copy) NSDictionary *options;
- (instancetype)initWithType:(NSTextTabType)type location:(CGFloat)loc;
@property (readonly) CGFloat location;
@property (readonly) NSTextTabType tabStopType;
@end

NS_AUTOMATED_REFCOUNT_WEAK_UNAVAILABLE
@interface NSParagraphStyle : NSObject <NSCopying, NSMutableCopying, NSSecureCoding> {
    /*All instance variables are private*/
    CGFloat _lineSpacing;
    CGFloat _paragraphSpacing;
    CGFloat _headIndent;
    CGFloat _tailIndent;
    CGFloat _firstLineHeadIndent;
    CGFloat _minimumLineHeight;
    CGFloat _maximumLineHeight;
    NSArray *_tabStops;
    struct {
	NSTextAlignment alignment:4;
        NSLineBreakMode lineBreakMode:4;
        unsigned int tabStopsIsMutable:1;
        unsigned int isNaturalDirection:1;
        unsigned int rightToLeftDirection:1;
        unsigned int fixedMultiple:2;
        unsigned int refCount:19;
#if __LP64__
        unsigned int :32;
#endif
    } _flags;
    CGFloat _defaultTabInterval;
    id _extraData;
}

+ (NSParagraphStyle *)defaultParagraphStyle;

+ (NSWritingDirection)defaultWritingDirectionForLanguage:(NSString *)languageName;  // languageName is in ISO lang region format

@property (readonly) CGFloat lineSpacing;		/* "Leading": distance between the bottom of one line fragment and top of next (applied between lines in the same container). Can't be negative. This value is included in the line fragment heights in layout manager. */
@property (readonly) CGFloat paragraphSpacing; 	/* Distance between the bottom of this paragraph and top of next (or the beginning of its paragraphSpacingBefore, if any). */
@property (readonly) NSTextAlignment alignment;

/* The following values are relative to the appropriate margin (depending on the paragraph direction) */
   
@property (readonly) CGFloat headIndent;		/* Distance from margin to front edge of paragraph */
@property (readonly) CGFloat tailIndent;		/* Distance from margin to back edge of paragraph; if negative or 0, from other margin */
@property (readonly) CGFloat firstLineHeadIndent;	/* Distance from margin to edge appropriate for text direction */
@property (readonly, copy) NSArray *tabStops;		/* Distance from margin to tab stops */

@property (readonly) CGFloat minimumLineHeight;	/* Line height is the distance from bottom of descenders to top of ascenders; basically the line fragment height. Does not include lineSpacing (which is added after this computation). */
@property (readonly) CGFloat maximumLineHeight;	/* 0 implies no maximum. */ 

@property (readonly) NSLineBreakMode lineBreakMode;

@property (readonly) NSWritingDirection baseWritingDirection;

@property (readonly) CGFloat lineHeightMultiple;	/* Natural line height is multiplied by this factor (if positive) before being constrained by minimum and maximum line height. */
@property (readonly) CGFloat paragraphSpacingBefore;/* Distance between the bottom of the previous paragraph (or the end of its paragraphSpacing, if any) and the top of this paragraph. */
@property (readonly) CGFloat defaultTabInterval;	/* Tabs after the last specified in tabStops are placed at integral multiples of this distance (if positive). */

@property (readonly, copy) NSArray *textBlocks;    /* Array to specify the text blocks containing the paragraph, nested from outermost to innermost. */
@property (readonly, copy) NSArray *textLists;     /* Array to specify the text lists containing the paragraph, nested from outermost to innermost. */

/* Specifies the threshold for hyphenation.  Valid values lie between 0.0 and 1.0 inclusive.  Hyphenation will be attempted when the ratio of the text width as broken without hyphenation to the width of the line fragment is less than the hyphenation factor.  When this takes on its default value of 0.0, the layout manager's hyphenation factor is used instead.  When both are 0.0, hyphenation is disabled.
*/
@property (readonly) float hyphenationFactor;

/* Specifies the threshold for using tightening as an alternative to truncation.  When the line break mode specifies truncation, the text system will attempt to tighten inter-character spacing as an alternative to truncation, provided that the ratio of the text width to the line fragment width does not exceed 1.0 + tighteningFactorForTruncation.  Otherwise the text will be truncated at a location determined by the line break mode.  The default value is 0.05.
*/
@property (readonly) float tighteningFactorForTruncation;

/* Specifies whether the paragraph is to be treated as a header for purposes of HTML generation.  Should be set to 0 (the default value) if the paragraph is not a header, or from 1 through 6 if the paragraph is to be treated as a header. */
@property (readonly) NSInteger headerLevel;

@end

@interface NSMutableParagraphStyle : NSParagraphStyle

@property CGFloat lineSpacing;
@property CGFloat paragraphSpacing;
@property NSTextAlignment alignment;
@property CGFloat headIndent;
@property CGFloat tailIndent;
@property CGFloat firstLineHeadIndent;
- (void)addTabStop:(NSTextTab *)anObject;
- (void)removeTabStop:(NSTextTab *)anObject;
@property (copy) NSArray *tabStops;
@property CGFloat minimumLineHeight;
@property CGFloat maximumLineHeight;
@property NSLineBreakMode lineBreakMode;
- (void)setParagraphStyle:(NSParagraphStyle *)obj;
@property NSWritingDirection baseWritingDirection;
@property CGFloat lineHeightMultiple;
@property CGFloat paragraphSpacingBefore;
@property CGFloat defaultTabInterval;
@property (copy) NSArray *textBlocks;
@property (copy) NSArray *textLists;
@property float hyphenationFactor;
@property float tighteningFactorForTruncation;
@property NSInteger headerLevel;

@end
