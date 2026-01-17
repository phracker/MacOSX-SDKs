/*
        NSParagraphStyle.h
        Copyright (c) 1994-2015, Apple Inc.  All rights reserved.
 
	NSParagraphStyle and NSMutableParagraphStyle hold paragraph style information
	NSTextTab holds information about a single tab stop
 */

#import <Foundation/NSObject.h>
#import <AppKit/NSText.h>

@class NSTextBlock;
@class NSTextList;

NS_ASSUME_NONNULL_BEGIN

// NSTextTab
APPKIT_EXTERN NSString * NSTabColumnTerminatorsAttributeName NS_AVAILABLE(10_0, 7_0); // An attribute for NSTextTab options.  The value is NSCharacterSet.  The character set is used to determine the tab column terminating character.  The tab and newline characters are implied even if not included in the character set.

NS_CLASS_AVAILABLE(10_0, 7_0) @interface NSTextTab : NSObject <NSCopying, NSCoding>
{
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

+ (NSCharacterSet *)columnTerminatorsForLocale:(nullable NSLocale *)aLocale NS_AVAILABLE(10_11, 7_0); // Returns the column terminators for locale. Passing nil returns an instance corresponding to +[NSLocale systemLocale]. For matching user's formatting preferences, pass +[NSLocale currentLocale]. Can be used as the value for NSTabColumnTerminatorsAttributeName to make a decimal tab stop.

- (instancetype)initWithTextAlignment:(NSTextAlignment)alignment location:(CGFloat)loc options:(NSDictionary<NSString *, id> *)options NS_DESIGNATED_INITIALIZER; // Initializes a text tab with the text alignment, location, and options.  The text alignment is used to determine the position of text inside the tab column.


@property(readonly) NSTextAlignment alignment;  // Defines the alignment of tab column contents. NSTextAlignmentNatural and NSTextAlignmentJustified are resolved either NSTextAlignmentLeft or NSTextAlignmentRight based on the user's preferred language.
@property(readonly) CGFloat location; // Location of the tab stop inside the line fragment rect coordinate system
@property(readonly) NSDictionary<NSString *, id> *options; // Optional configuration attributes
@end


// NSParagraphStyle
typedef NS_ENUM(NSUInteger, NSLineBreakMode) {
    NSLineBreakByWordWrapping = 0,     	// Wrap at word boundaries, default
    NSLineBreakByCharWrapping,		// Wrap at character boundaries
    NSLineBreakByClipping,		// Simply clip
    NSLineBreakByTruncatingHead,	// Truncate at head of line: "...wxyz"
    NSLineBreakByTruncatingTail,	// Truncate at tail of line: "abcd..."
    NSLineBreakByTruncatingMiddle	// Truncate middle of line:  "ab...yz"
} NS_ENUM_AVAILABLE(10_0, 6_0);


NS_CLASS_AVAILABLE(10_0, 6_0) @interface NSParagraphStyle : NSObject <NSCopying, NSMutableCopying, NSSecureCoding>
{
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
        unsigned int tightensForTruncation:1;
        unsigned int refCount:18;
#if __LP64__
        unsigned int :32;
#endif
    } _flags;
    CGFloat _defaultTabInterval;
    id _extraData;
}

+ (NSParagraphStyle *)defaultParagraphStyle; // This class method returns a shared and cached NSParagraphStyle instance with the default style settings, with same value as the result of [[NSParagraphStyle alloc] init].

+ (NSWritingDirection)defaultWritingDirectionForLanguage:(nullable NSString *)languageName;  // languageName is in ISO lang region format

@property(readonly) CGFloat lineSpacing; // "Leading": distance between the bottom of one line fragment and top of next (applied between lines in the same container). This value is included in the line fragment heights in layout manager.
@property(readonly) CGFloat paragraphSpacing; // Distance between the bottom of this paragraph and top of next (or the beginning of its paragraphSpacingBefore, if any).
@property(readonly) NSTextAlignment alignment;

// The following values are relative to the appropriate margin (depending on the paragraph direction)

@property(readonly) CGFloat headIndent; // Distance from margin to front edge of paragraph
@property(readonly) CGFloat tailIndent; // Distance from margin to back edge of paragraph; if negative or 0, from other margin
@property(readonly) CGFloat firstLineHeadIndent; // Distance from margin to edge appropriate for text direction

@property(readonly) CGFloat minimumLineHeight; // Line height is the distance from bottom of descenders to top of ascenders; basically the line fragment height. Does not include lineSpacing (which is added after this computation).
@property(readonly) CGFloat maximumLineHeight; // 0 implies no maximum.

@property(readonly) NSLineBreakMode lineBreakMode;

@property(readonly) NSWritingDirection baseWritingDirection;

@property(readonly) CGFloat lineHeightMultiple; // Natural line height is multiplied by this factor (if positive) before being constrained by minimum and maximum line height.
@property(readonly) CGFloat paragraphSpacingBefore; // Distance between the bottom of the previous paragraph (or the end of its paragraphSpacing, if any) and the top of this paragraph.

// Specifies the threshold for hyphenation.  Valid values lie between 0.0 and 1.0 inclusive.  Hyphenation will be attempted when the ratio of the text width as broken without hyphenation to the width of the line fragment is less than the hyphenation factor.  When this takes on its default value of 0.0, the layout manager's hyphenation factor is used instead.  When both are 0.0, hyphenation is disabled.
@property(readonly) float hyphenationFactor;

@property(readonly,copy) NSArray<NSTextTab *> *tabStops NS_AVAILABLE(10_0, 7_0); // An array of NSTextTabs. Contents should be ordered by location. The default value is an array of 12 left-aligned tabs at 28pt interval
@property(readonly) CGFloat defaultTabInterval NS_AVAILABLE(10_0, 7_0); // The default tab interval used for locations beyond the last element in tabStops

@property(readonly) BOOL allowsDefaultTighteningForTruncation NS_AVAILABLE(10_11, 9_0); // Tightens inter-character spacing in attempt to fit lines wider than the available space if the line break mode is one of the truncation modes before starting to truncate. YES by default for apps linked against 10.11 and later SDK. The maximum amount of tightening performed is determined by the system based on contexts such as font, line width, etc.

// Specifies the threshold for using tightening as an alternative to truncation when -allowsDefaultTighteningForTruncation=NO.  When the line break mode specifies truncation, the text system will attempt to tighten inter-character spacing as an alternative to truncation, provided that the ratio of the text width to the line fragment width does not exceed 1.0 + tighteningFactorForTruncation.  Otherwise the text will be truncated at a location determined by the line break mode.  The default value is 0.0 for apps linked against 10.11 and later SDK. This property is ignored when -allowsDefaultTighteningForTruncation=YES. Explicitly setting this property to 0.0 has a side effect of also setting -allowsDefaultTighteningForTruncation to NO.
@property(readonly) float tighteningFactorForTruncation;

@property (readonly, copy) NSArray<__kindof NSTextBlock *> *textBlocks;    // Array to specify the text blocks containing the paragraph, nested from outermost to innermost.
@property (readonly, copy) NSArray<NSTextList *> *textLists;     // Array to specify the text lists containing the paragraph, nested from outermost to innermost.

// Specifies whether the paragraph is to be treated as a header for purposes of HTML generation.  Should be set to 0 (the default value) if the paragraph is not a header, or from 1 through 6 if the paragraph is to be treated as a header.
@property (readonly) NSInteger headerLevel;
@end


NS_CLASS_AVAILABLE(10_0, 6_0) @interface NSMutableParagraphStyle : NSParagraphStyle

@property CGFloat lineSpacing;
@property CGFloat paragraphSpacing;
@property NSTextAlignment alignment;
@property CGFloat firstLineHeadIndent;
@property CGFloat headIndent;
@property CGFloat tailIndent;
@property NSLineBreakMode lineBreakMode;
@property CGFloat minimumLineHeight;
@property CGFloat maximumLineHeight;
@property NSWritingDirection baseWritingDirection;
@property CGFloat lineHeightMultiple;
@property CGFloat paragraphSpacingBefore;
@property float hyphenationFactor;
@property(null_resettable, copy) NSArray<NSTextTab *> *tabStops NS_AVAILABLE(10_0, 7_0);
@property CGFloat defaultTabInterval NS_AVAILABLE(10_0, 7_0);
@property BOOL allowsDefaultTighteningForTruncation NS_AVAILABLE(10_11, 9_0);

- (void)addTabStop:(NSTextTab *)anObject NS_AVAILABLE(10_0, 9_0);
- (void)removeTabStop:(NSTextTab *)anObject NS_AVAILABLE(10_0, 9_0);

- (void)setParagraphStyle:(NSParagraphStyle *)obj NS_AVAILABLE(10_0, 9_0);

@property float tighteningFactorForTruncation;
@property(copy) NSArray<__kindof NSTextBlock *> *textBlocks;
@property(copy) NSArray<NSTextList *> *textLists;
@property NSInteger headerLevel;
@end

/************************ Deprecated ************************/
// NSTextTabType and NSTextTab methods using the type are soft deprecated starting with OS X 10.11. It will be officially deprecated in a future release. Use NSTextAlignment-based API instead
typedef NS_ENUM(NSUInteger, NSTextTabType) {
    NSLeftTabStopType = 0,
    NSRightTabStopType,
    NSCenterTabStopType,
    NSDecimalTabStopType
};

@interface NSTextTab (NSTextTabDeprecated)
- (instancetype)initWithType:(NSTextTabType)type location:(CGFloat)loc; // Use -initWithTextAlignment:location:options:
@property(readonly) NSTextTabType tabStopType; // Use -alignment and -options
@end

NS_ASSUME_NONNULL_END
