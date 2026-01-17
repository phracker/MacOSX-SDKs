/* 
	NSTypesetter.h
	Copyright (c) 1994-2011, Apple Inc.  All rights reserved. 

	An abstract class to lay glyphs out in horizontal or vertical boxes	
*/

#import <CoreFoundation/CFCharacterSet.h> // for UTF32Char
#import <Foundation/NSObject.h>
#import <AppKit/NSLayoutManager.h>
#import <AppKit/NSParagraphStyle.h>

enum {
    NSTypesetterZeroAdvancementAction = (1 << 0), // glyphs with this action are flitered out from layout (notShownAttribute == YES)
    NSTypesetterWhitespaceAction = (1 << 1), // the width for glyphs with this action are determined by -boundingBoxForControlGlyphAtIndex:forTextContainer:proposedLineFragment:glyphPosition:characterIndex: if the method is implemented; otherwise, same as NSTypesetterZeroAdvancementAction
    NSTypesetterHorizontalTabAction = (1 << 2), // Treated as tab character
    NSTypesetterLineBreakAction = (1 << 3), // Causes line break
    NSTypesetterParagraphBreakAction = (1 << 4), // Causes paragraph break; firstLineIndent will be used for the following glyph
    NSTypesetterContainerBreakAction = (1 << 5) // Causes container break
};
typedef NSUInteger NSTypesetterControlCharacterAction;
    
@interface NSTypesetter : NSObject {
#if __LP64__
    void *_reserved;
#else /* __LP64__ */
    unsigned _reserved[2];
#endif /* __LP64__ */
}

/* Primitive typesetting methods */
/* NSLayoutManager attributes */
/* Controls whether leading value specified by fonts affects line spacing
*/
- (BOOL)usesFontLeading;
- (void)setUsesFontLeading:(BOOL)flag;

/* Controls various typesetting behavior for backward compatibility
*/
- (NSTypesetterBehavior)typesetterBehavior;
- (void)setTypesetterBehavior:(NSTypesetterBehavior)behavior;

/* Controls hyphenation factor. The value should be between 0.0 and 1.0.
*/
- (float)hyphenationFactor;
- (void)setHyphenationFactor:(float)factor;

/* NSTextContainer attributes */
/* Controls padding at both ends of line fragment.
*/
- (CGFloat)lineFragmentPadding;
- (void)setLineFragmentPadding:(CGFloat)padding;

/* Screen/printer font mapping */
- (NSFont *)substituteFontForFont:(NSFont *)originalFont;

/* Tab stops */
/* Returns an NSTextTab instance for glyphLocation from the current text tab array. glyphLocation must be in the base typesetter coordinate (should not include line fragment rect origin and lineFragmentPadding). direction should be either NSWritingDirectionLeftToRight or NSWritingDirectionRightToLeft. maxLocation specifies the maximum location a glyph can be assigned in the base typesetter coordinate.
*/
- (NSTextTab *)textTabForGlyphLocation:(CGFloat)glyphLocation writingDirection:(NSWritingDirection)direction maxLocation:(CGFloat)maxLocation;

/* Bidi control */
/* Controls whether to perform bi-directional processing.  You can disable the layout stage if you know the parapgraph does not need this stage (i.e. the backing-store is in the display order).
*/
- (BOOL)bidiProcessingEnabled;
- (void)setBidiProcessingEnabled:(BOOL)flag;

/* Accessors for required paragraph typesetting settings */
- (void)setAttributedString:(NSAttributedString *)attrString; // Note this method does not retain attrString
- (NSAttributedString *)attributedString;
- (void)setParagraphGlyphRange:(NSRange)paragraphRange separatorGlyphRange:(NSRange)paragraphSeparatorRange;
- (NSRange)paragraphGlyphRange; // does not include paragraphSeparatorGlyphRange
- (NSRange)paragraphSeparatorGlyphRange;
- (NSRange)paragraphCharacterRange;
- (NSRange)paragraphSeparatorCharacterRange;

/* layout primitive */
/* lineFragmentOrigin specifies the upper-left corner of line fragment rect.  On return, set to the next origin. The method returns the next glyph index. Usually the index right after paragraph separator but can be inside the paragraph range (i.e. text container exhaustion). Concrete subclasses must implement this method. A concrete implementation must invoke -beginParagraph, -endParagraph, -beginLineWithGlyphAtIndex: and -endLineWithGlyphRange:.
*/
- (NSUInteger)layoutParagraphAtPoint:(NSPointPointer)lineFragmentOrigin;

/* Layout parameter setup */
- (void)beginParagraph; // should be invoked at the beginning of -layoutParagraphAtPoint:
- (void)endParagraph; // should be invoked at the end of -layoutParagraphAtPoint:
- (void)beginLineWithGlyphAtIndex:(NSUInteger)glyphIndex; // should be invoked at the beginning of each line
- (void)endLineWithGlyphRange:(NSRange)lineGlyphRange; // should be invoked at the end of each line

/* Line/paragraph spacing */
- (CGFloat)lineSpacingAfterGlyphAtIndex:(NSUInteger)glyphIndex withProposedLineFragmentRect:(NSRect)rect;
- (CGFloat)paragraphSpacingBeforeGlyphAtIndex:(NSUInteger)glyphIndex withProposedLineFragmentRect:(NSRect)rect;
- (CGFloat)paragraphSpacingAfterGlyphAtIndex:(NSUInteger)glyphIndex withProposedLineFragmentRect:(NSRect)rect;

/* Empty paragraph handling */
/* This method calculates the line fragment rect/line fragment used rect for blank lines. theParagraphSeparatorGlyphRange with length == 0 indicates extra line fragment.
*/
- (void)getLineFragmentRect:(NSRectPointer)lineFragmentRect usedRect:(NSRectPointer)lineFragmentUsedRect forParagraphSeparatorGlyphRange:(NSRange)paragraphSeparatorGlyphRange atProposedOrigin:(NSPoint)lineOrigin;

/* Extra line fragment handling */
/* This method returns the attributes used to layout the extra line fragment. The default implementation tries to use -[NSTextView typingAttributes] if possible; otherwise, uses attributes for the last character.
*/
- (NSDictionary *)attributesForExtraLineFragment;

/* Control/format character handling */
/* This method returns the action associated with a control character.
*/
- (NSTypesetterControlCharacterAction)actionForControlCharacterAtIndex:(NSUInteger)charIndex;

/* Cocoa Text System specific interface methods */
/* Friend class accessors */
- (NSLayoutManager *)layoutManager;
- (NSArray *)textContainers;
- (NSTextContainer *)currentTextContainer;
- (NSParagraphStyle *)currentParagraphStyle;

/* Forces NSLayoutManager to invalidate glyph cache in range when invalidating layout.
*/
- (void)setHardInvalidation:(BOOL)flag forGlyphRange:(NSRange)glyphRange;

/*  Actually lay out glyphs starting at the given index.  The given number of line fragments will be generated as long as the NSGlyphStorage doesn't run out of glyphs.  nextGlyph will be set to the index of the next glyph that needs to be laid out. New applications should use -layoutCharactersInRange:forLayoutManager:maximumNumberOfLineFragments: instead.
*/
- (void)layoutGlyphsInLayoutManager:(NSLayoutManager *)layoutManager startingAtGlyphIndex:(NSUInteger)startGlyphIndex maxNumberOfLineFragments:(NSUInteger)maxNumLines nextGlyphIndex:(NSUInteger *)nextGlyph;

/* Layouts characters in characterRange for layoutManager. The method returns the actual character range that the receiving NSTypesetter processed. The layout process can be interrupted when the number of line fragments exceeds maxNumLines. Specify NSUIntegerMax for unlimited number of line fragments.
*/
- (NSRange)layoutCharactersInRange:(NSRange)characterRange forLayoutManager:(NSLayoutManager *)layoutManager maximumNumberOfLineFragments:(NSUInteger)maxNumLines NS_AVAILABLE_MAC(10_5);

/* Returns the offset to be applied to the glyph in question when printing.
*/
+ (NSSize)printingAdjustmentInLayoutManager:(NSLayoutManager *)layoutMgr forNominallySpacedGlyphRange:(NSRange)nominallySpacedGlyphsRange packedGlyphs:(const unsigned char *)packedGlyphs count:(NSUInteger)packedGlyphsCount;

- (CGFloat)baselineOffsetInLayoutManager:(NSLayoutManager *)layoutMgr glyphIndex:(NSUInteger)glyphIndex;


/* Factory methods */
+ (id)sharedSystemTypesetter;
+ (id)sharedSystemTypesetterForBehavior:(NSTypesetterBehavior)theBehavior;
+ (NSTypesetterBehavior)defaultTypesetterBehavior;
@end

/* NSLayoutPhaseInterface declares various subclass override points that are invoked if implemented */
@interface NSTypesetter (NSLayoutPhaseInterface)
// Called right before setLineFragmentRect:forGlyphRange:usedRect:
- (void)willSetLineFragmentRect:(NSRectPointer)lineRect forGlyphRange:(NSRange)glyphRange usedRect:(NSRectPointer)usedRect baselineOffset:(CGFloat *)baselineOffset;

- (BOOL)shouldBreakLineByWordBeforeCharacterAtIndex:(NSUInteger)charIndex;
- (BOOL)shouldBreakLineByHyphenatingBeforeCharacterAtIndex:(NSUInteger)charIndex;

- (float)hyphenationFactorForGlyphAtIndex:(NSUInteger)glyphIndex;
- (UTF32Char)hyphenCharacterForGlyphAtIndex:(NSUInteger)glyphIndex;

- (NSRect)boundingBoxForControlGlyphAtIndex:(NSUInteger)glyphIndex forTextContainer:(NSTextContainer *)textContainer proposedLineFragment:(NSRect)proposedRect glyphPosition:(NSPoint)glyphPosition characterIndex:(NSUInteger)charIndex;
@end

/* NSGlyphStorageInterface declares all primitives interfacing to the glyph storage (usually NSLayoutManager). By overriding all the methods, you can implement an NSTypesetter subclass that interacts with custom glyph storage. */
@interface NSTypesetter (NSGlyphStorageInterface)
// Glyph/character range mappings
- (NSRange)characterRangeForGlyphRange:(NSRange)glyphRange actualGlyphRange:(NSRangePointer)actualGlyphRange;
- (NSRange)glyphRangeForCharacterRange:(NSRange)charRange actualCharacterRange:(NSRangePointer)actualCharRange;

// Glyph data
- (NSUInteger)getGlyphsInRange:(NSRange)glyphsRange glyphs:(NSGlyph *)glyphBuffer characterIndexes:(NSUInteger *)charIndexBuffer glyphInscriptions:(NSGlyphInscription *)inscribeBuffer elasticBits:(BOOL *)elasticBuffer bidiLevels:(unsigned char *)bidiLevelBuffer;

// NSTextContainer attribute
/* Calculates line fragment rect, line fragment used rect, and remaining rect for a line fragment starting at glyph index startingGlyphIndex with proposedRect. The height is determined using lineSpacing, paragraphSpacingBefore, and paragraphSpacingAfter as well as proposedRect. The width for lineFragmentUsedRect is set to the lineFragmentRect width. In the standard implementation, paragraph spacing is included in the line fragment rect but not the line fragment used rect; line spacing is included in both.
*/
- (void)getLineFragmentRect:(NSRectPointer)lineFragmentRect usedRect:(NSRectPointer)lineFragmentUsedRect remainingRect:(NSRectPointer)remainingRect forStartingGlyphAtIndex:(NSUInteger)startingGlyphIndex proposedRect:(NSRect)proposedRect lineSpacing:(CGFloat)lineSpacing paragraphSpacingBefore:(CGFloat)paragraphSpacingBefore paragraphSpacingAfter:(CGFloat)paragraphSpacingAfter;

// Layout storage
- (void)setLineFragmentRect:(NSRect)fragmentRect forGlyphRange:(NSRange)glyphRange usedRect:(NSRect)usedRect baselineOffset:(CGFloat)baselineOffset;
- (void)substituteGlyphsInRange:(NSRange)glyphRange withGlyphs:(NSGlyph *)glyphs;
- (void)insertGlyph:(NSGlyph)glyph atGlyphIndex:(NSUInteger)glyphIndex characterIndex:(NSUInteger)characterIndex;
- (void)deleteGlyphsInRange:(NSRange)glyphRange;
- (void)setNotShownAttribute:(BOOL)flag forGlyphRange:(NSRange)glyphRange;
- (void)setDrawsOutsideLineFragment:(BOOL)flag forGlyphRange:(NSRange)glyphRange;
- (void)setLocation:(NSPoint)location withAdvancements:(const CGFloat *)advancements forStartOfGlyphRange:(NSRange)glyphRange;
- (void)setAttachmentSize:(NSSize)attachmentSize forGlyphRange:(NSRange)glyphRange;
- (void)setBidiLevels:(const uint8_t *)levels forGlyphRange:(NSRange)glyphRange;
@end

#if !__LP64__ && MAC_OS_X_VERSION_MIN_REQUIRED <= MAC_OS_X_VERSION_10_4
#import <AppKit/NSSimpleHorizontalTypesetter.h>
#endif /* MAC_OS_X_VERSION_MIN_REQUIRED <= MAC_OS_X_VERSION_10_4 */
