/* 
    NSSimpleHorizontalTypesetter.h
    Copyright (c) 1993-2018, Apple Inc.
    All rights reserved. 
 
    A concrete class to lay glyphs out in horizontal boxes.
    This class is deprecated starting from Mac OS X 10.4 Tiger.
    Please consider migrating to NSATSTypesetter.
    This header will not be imported automatically by NSTypesetter.h in the next major release.
*/

#import <AppKit/NSTypesetter.h>

#if __LP64__ || MAC_OS_X_VERSION_MIN_REQUIRED > MAC_OS_X_VERSION_10_4
#warning NSSimpleHorizontalTypesetter is deprecated starting from Mac OS X 10.4 Tiger.
#warning Developers are recommended to adopt NSATSTypesetter, the default concrete subclass from Mac OS X 10.3 Panther.
#else /* __LP64__ || MAC_OS_X_VERSION_MIN_REQUIRED > MAC_OS_X_VERSION_10_4 */
@class NSTextContainer;
@class NSTextStorage;
@class NSParagraphStyle;

typedef enum _NSLayoutStatus {
    NSLayoutNotDone = 0,
    NSLayoutDone,
    NSLayoutCantFit,
    NSLayoutOutOfGlyphs
} NSLayoutStatus;

/* Determines how to lay a glyph out in relation to a previous glyph */
typedef enum _NSGlyphLayoutMode {
    NSGlyphLayoutAtAPoint = 0,
    NSGlyphLayoutAgainstAPoint,
    NSGlyphLayoutWithPrevious
} NSGlyphLayoutMode;

/* Layout direction */
typedef enum _NSLayoutDirection {
    NSLayoutLeftToRight = 0,
    NSLayoutRightToLeft
} NSLayoutDirection;

#define NSBaselineNotSet -1.0

#define NumGlyphsToGetEachTime 20

typedef NSPoint (*_NSPositionOfGlyphMethod)(NSFont *obj, SEL sel, NSGlyph cur, NSGlyph prev, BOOL *isNominal);

/* Cache structure used inside NSSimpleHorizontalTypesetter.
*/
typedef struct _NSTypesetterGlyphInfo {
    NSPoint curLocation;		/* Location (relative to the baseline) for laying this glyph out */
    float extent;			/* Required space from curLocation to lay this glyph out; -1.0 if not set */
    float belowBaseline;		/* Distance from baseline to bottom of the line fragment required for all the glyphs so far, including this one (positive if baseline is above the bottom of the line fragment) */
    float aboveBaseline;		/* Distance from baseline to top of the line fragment required for all the glyphs so far, including this one (positive if baseline is below the top of the line fragment) */
    unsigned glyphCharacterIndex;		/* ...and its char index */
    NSFont *font;				/* ...and its font */
    NSSize attachmentSize;  	/* Size of the character if it's an attachment; otherwise meaningless */
    struct {
	unsigned int defaultPositioning:1;	/* This block needs to be "show"ed */
	unsigned int dontShow:1;		/* Don't show this glyph */
	unsigned int isAttachment:1;      	/* Whether the glyph is an attachment */
    } _giflags;
} NSTypesetterGlyphInfo;		/* Glyphs 0..curGlyphIndex-1 are valid in here */

/* Use this to access glyphs
*/
#define NSGlyphInfoAtIndex(IX) ((NSTypesetterGlyphInfo *)((void *)glyphs + (sizeOfGlyphInfo * IX)))

/* A concrete class that does simple left-to-right typesetting with some support for non-spacing marks.
*/
NS_AUTOMATED_REFCOUNT_WEAK_UNAVAILABLE
@interface NSSimpleHorizontalTypesetter : NSTypesetter {
/* These are read-only ivars */
    /* Global Info */
    NSLayoutManager *layoutManager APPKIT_IVAR;	/* Current layout manager */
    NSTextStorage *textStorage APPKIT_IVAR;		/* Current text storage being laid out */

    /* Global info about the state of the layout of current line fragment */
    unsigned firstGlyphIndex APPKIT_IVAR;		/* First glyph of the line fragment, glyph[0] stores this */
    unsigned curGlyphIndex APPKIT_IVAR; 		/* Current glyph (relative to firstGlyphIndex) being laid out */
    unsigned firstInvalidGlyphIndex APPKIT_IVAR;	/* Index into glyphs[]; index of first location where .glyph and .glyphInscription are invalid */

    /* Global info about the current cache of glyphs */
    NSTypesetterGlyphInfo *glyphs APPKIT_IVAR;	/* Glyphs 0..curGlyphIndex-1 are valid in here */
    NSGlyph *glyphCache APPKIT_IVAR;
    NSGlyphInscription *glyphInscriptionCache APPKIT_IVAR;
    unsigned *glyphCharacterIndexCache APPKIT_IVAR;
    BOOL *glyphElasticCache APPKIT_IVAR;

    NSSize glyphLocationOffset APPKIT_IVAR;		/* Offset of all glyphs in glyphs[] array */

    float curMaxGlyphLocation APPKIT_IVAR;		/* Maximum location upto where glyphs can be laid */
    unsigned lastFixedGlyphIndex APPKIT_IVAR;	/* Index of last glyph to be laid out at a fixed location (basically start of line or tab loc) */
    unsigned sizeOfGlyphInfo APPKIT_IVAR;

    /* Info about current glyph (glyph at curGlyphIndex) and previous glyph */
    NSGlyph curGlyph APPKIT_IVAR;
    NSGlyphInscription curGlyphInscription APPKIT_IVAR;
    unsigned curCharacterIndex APPKIT_IVAR;
@private	/* All further instance variables are private */
    unsigned previousGlyph APPKIT_IVAR;		/* Previous glyph */
    unsigned previousBaseGlyphIndex APPKIT_IVAR;	/* Index of previous base glyph */
    unsigned previousBaseGlyph APPKIT_IVAR;		/* Previous base glyph */
    NSFont *previousFont APPKIT_IVAR;		/* Font of the previous glyph; cached */
    float curGlyphOffset APPKIT_IVAR;		/* The location where the next glyph should be laid out (used when glyphLayoutMode != NSGlyphLayoutWithPrevious) */
    BOOL curGlyphOffsetOutOfDate APPKIT_IVAR;	/* If yes, then compute curGlyphOffset */
    BOOL curGlyphIsAControlGlyph APPKIT_IVAR;
    BOOL containerBreakAfterCurGlyph APPKIT_IVAR;   /* If yes, go on to next container. */
    BOOL wrapAfterCurGlyph APPKIT_IVAR;		/* Indicates the the line fragment should be done after this glyph */
    float curSpaceAfter APPKIT_IVAR;		/* Manual kerning attribute; cached */
    float previousSpaceAfter APPKIT_IVAR;
    NSGlyphLayoutMode glyphLayoutMode APPKIT_IVAR;	/* Can we compose current glyph with previous; cached */
    float curGlyphExtentAboveLocation APPKIT_IVAR;	/* Distance above and below its display origin that the glyph requires */
    float curGlyphExtentBelowLocation APPKIT_IVAR;
    NSLayoutDirection curLayoutDirection APPKIT_IVAR;
    NSTextAlignment curTextAlignment APPKIT_IVAR;	/* Evaluated to be one of L, R, or C */

    /* Cached info about character attributes; these can last beyond one line fragment */
@public
    NSFont *curFont APPKIT_IVAR;			/* Current font; cached */
    NSRect curFontBoundingBox APPKIT_IVAR;		/* Bounding box for the current font; cached */
    BOOL curFontIsFixedPitch APPKIT_IVAR;		/* Whether or not the current font is fixed pitch, cached */
    NSPoint curFontAdvancement APPKIT_IVAR;		/* If curFontIsFixedPitch, this stores the advancement, cached */
    _NSPositionOfGlyphMethod curFontPositionOfGlyphMethod APPKIT_IVAR;	/* Obtained from methodFor, cached */
@private
    NSDictionary *attrs APPKIT_IVAR;	       	/* Attributes for the current glyph; cached */
    NSRange attrsRange APPKIT_IVAR;			/* And character range over which it applies */
    float curBaselineOffset APPKIT_IVAR;		/* Current baseline offset, from the baseline offset and superscript attrs; cached */
    float curMinBaselineDistance APPKIT_IVAR;	/* Minimum baseline distance attribute, cached */
    float curMaxBaselineDistance APPKIT_IVAR;	/* Maximum baseline distance attribute, cached */
    int curSuperscript APPKIT_IVAR;			/* Value of the superscript attr; cached */
    NSParagraphStyle *curParaStyle APPKIT_IVAR;	/* Paragraph attributes, cached */
    NSTextContainer *curContainer APPKIT_IVAR;
    unsigned curContainerIndex APPKIT_IVAR;
    float curContainerLineFragmentPadding APPKIT_IVAR;
    BOOL curContainerIsSimpleRectangular APPKIT_IVAR;	/* Whether the current container is simple rectangular, cached */
    NSSize curContainerSize APPKIT_IVAR;		/* [curContainer containerSize], cached */
    float curMinLineHeight APPKIT_IVAR;		/* [curParaStyle minLineHeight], cached */
    float curMaxLineHeight APPKIT_IVAR;		/* [curParaStyle maxLineHeight], cached */
    
    /* Other, more global info */
    NSString *textString APPKIT_IVAR;		/* Basically [textStorage string] */

    /* There is capacityOfGlyphs items in the following arrays. */
    unsigned capacityOfGlyphs APPKIT_IVAR;		/* Capacity of array pointed to by the following items */

    BOOL busy APPKIT_IVAR;	/* This typesetter is currently servicing a call; if the typesetter is "not busy" then none of the other accessor methods are valid, because typesetters don't maintain state across invocations of the main entry point. */

    struct {
	unsigned _glyphPostLay:1;
	unsigned _fragPostLay:1;
	unsigned _useItal:1;
        unsigned _curFontIsDefaultFace:1;
        unsigned _tabState:2;
        unsigned _tabType:2;
        unsigned _tabEOL:1;
	unsigned reserved:23;
    } _tsFlags APPKIT_IVAR;

@public
    /* Bidi-related cached info */
    unsigned char *glyphBidiLevelCache APPKIT_IVAR;
    unsigned char curBidiLevel APPKIT_IVAR;		/* Resolved bidirectional embedding level of current glyph */
    
@private
    unsigned char previousBidiLevel APPKIT_IVAR;
    unsigned char _reservedChars[2] APPKIT_IVAR;
    unsigned _reserved2[6] APPKIT_IVAR;
}

+ (id)sharedInstance; 

/* Methods that return global information.
*/
- (NSLayoutManager *)currentLayoutManager;
- (NSTextContainer *)currentContainer;
- (NSParagraphStyle *)currentParagraphStyle;
- (NSTextStorage *)currentTextStorage;
- (NSTypesetterGlyphInfo *)baseOfTypesetterGlyphInfo NS_RETURNS_INNER_POINTER;
- (NSUInteger)sizeOfTypesetterGlyphInfo;
- (NSUInteger)capacityOfTypesetterGlyphInfo;
- (NSUInteger)firstGlyphIndexOfCurrentLineFragment;

/* Main public entry point
*/
- (void)layoutGlyphsInLayoutManager:(NSLayoutManager *)layoutManager startingAtGlyphIndex:(NSUInteger)startGlyphIndex maxNumberOfLineFragments:(NSUInteger)maxNumLines nextGlyphIndex:(NSUInteger *)nextGlyph;

/* Currently the one called by above.
*/
- (NSLayoutStatus)layoutGlyphsInHorizontalLineFragment:(NSRect *)lineFragmentRect baseline:(float *)baseline;

/* Glyph caching methods
*/
- (void)clearGlyphCache;
- (void)fillAttributesCache;
- (void)clearAttributesCache;

/* Grows the glyph-related caches to have at least the desired capacity. If fillGlyphInfo is YES, also fills with glyph information from the layout manager and updates firstInvalidGlyphIndex. Returns the number of glyphs received.
*/
- (NSUInteger)growGlyphCaches:(NSUInteger)desiredCapacity fillGlyphInfo:(BOOL)fillGlyphInfo;

/* Updates the location where the current glyph should be laid out. Often this isn't computed as it's not needed; however, this routine will bring it uptodate if necessary.
*/
- (void)updateCurGlyphOffset;

/* Only used for inserting hyphenation glyphs; never call layoutManager directly to insert glyphs; go through this method.
*/
- (void)insertGlyph:(NSGlyph)glyph atGlyphIndex:(NSUInteger)glyphIndex characterIndex:(NSUInteger)charIndex;

- (NSLayoutStatus)layoutControlGlyphForLineFragment:(NSRect)lineFrag;
- (void)layoutTab;

- (void)breakLineAtIndex:(NSUInteger)location;
- (NSUInteger)glyphIndexToBreakLineByHyphenatingWordAtIndex:(NSUInteger)charIndex;
- (NSUInteger)glyphIndexToBreakLineByWordWrappingAtIndex:(NSUInteger)charIndex;

- (void)fullJustifyLineAtGlyphIndex:(NSUInteger)glyphIndexForLineBreak;

@end

/* These methods can be OPTIONALLY implemented by subclasses of NSSimpleHorizontalTypesetter.
*/
@interface NSSimpleHorizontalTypesetter(NSTypesetterSubclassExtensions)

/* If implemented by subclasses, this is called within "layoutGlyphsInHorizontalLineFragment:baseline:" after laying out each glyph, allowing a subclass to hook into the layout machinery directly.  Variables curGlyph, curGlyphInscription, curBidiLevel, curCharacterIndex, curGlyphIsAControlGlyph, curFont, glyphLayoutMode, glyphs[curGlyphIndex] are guaranteed to be up-to-date.
*/
- (void)typesetterLaidOneGlyph:(NSTypesetterGlyphInfo *)gl;

/* If implemented by subclasses, this is called within "layoutGlyphsInHorizontalLineFragment:baseline:" after laying out each line fragment, immediately before "setLineFragmentRect:forGlyphRange:usedRect:" in the NSLayoutManager is called to record the used line fragment rectangles.  This is intended for subclasses to be able to affect e.g., linespacing globally.  The "used" rect is expected to be smaller than or equal to the "rect".
*/
- (void) willSetLineFragmentRect:(NSRect *)rect forGlyphRange:(NSRange)range usedRect:(NSRect *)bRect;

@end
#endif /* __LP64__ || MAC_OS_X_VERSION_MIN_REQUIRED > MAC_OS_X_VERSION_10_4 */
