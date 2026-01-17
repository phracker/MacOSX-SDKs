/* 
    NSSimpleHorizontalTypesetter.h
    Copyright (c) 2004-2005, Apple Computer, Inc.  All rights reserved. 
 
    A concrete class to lay glyphs out in horizontal boxes.
    This class is deprecated starting from Mac OS X 10.4 Tiger.
    Please consider migrating to NSATSTypesetter.
    This header will not be imported automatically by NSTypesetter.h in the next major release.
*/

#import <AppKit/NSTypesetter.h>

#if MAC_OS_X_VERSION_MIN_REQUIRED > MAC_OS_X_VERSION_10_4
#warning NSSimpleHorizontalTypesetter is deprecated starting from Mac OS X 10.4 Tiger.
#warning Developers are recommended to adopt NSATSTypesetter, the default concrete subclass from Mac OS X 10.3 Panther.
#else /* MAC_OS_X_VERSION_MIN_REQUIRED > MAC_OS_X_VERSION_10_4 */
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
@interface NSSimpleHorizontalTypesetter : NSTypesetter {
/* These are read-only ivars */
    /* Global Info */
    NSLayoutManager *layoutManager;	/* Current layout manager */
    NSTextStorage *textStorage;		/* Current text storage being laid out */

    /* Global info about the state of the layout of current line fragment */
    unsigned firstGlyphIndex;		/* First glyph of the line fragment, glyph[0] stores this */
    unsigned curGlyphIndex; 		/* Current glyph (relative to firstGlyphIndex) being laid out */
    unsigned firstInvalidGlyphIndex;	/* Index into glyphs[]; index of first location where .glyph and .glyphInscription are invalid */

    /* Global info about the current cache of glyphs */
    NSTypesetterGlyphInfo *glyphs;	/* Glyphs 0..curGlyphIndex-1 are valid in here */
    NSGlyph *glyphCache;
    NSGlyphInscription *glyphInscriptionCache;
    unsigned *glyphCharacterIndexCache;
    BOOL *glyphElasticCache;

    NSSize glyphLocationOffset;		/* Offset of all glyphs in glyphs[] array */

    float curMaxGlyphLocation;		/* Maximum location upto where glyphs can be laid */
    unsigned lastFixedGlyphIndex;	/* Index of last glyph to be laid out at a fixed location (basically start of line or tab loc) */
    unsigned sizeOfGlyphInfo;

    /* Info about current glyph (glyph at curGlyphIndex) and previous glyph */
    NSGlyph curGlyph;
    NSGlyphInscription curGlyphInscription;
    unsigned curCharacterIndex;
@private	/* All further instance variables are private */
    unsigned previousGlyph;		/* Previous glyph */
    unsigned previousBaseGlyphIndex;	/* Index of previous base glyph */
    unsigned previousBaseGlyph;		/* Previous base glyph */
    NSFont *previousFont;		/* Font of the previous glyph; cached */
    float curGlyphOffset;		/* The location where the next glyph should be laid out (used when glyphLayoutMode != NSGlyphLayoutWithPrevious) */
    BOOL curGlyphOffsetOutOfDate;	/* If yes, then compute curGlyphOffset */
    BOOL curGlyphIsAControlGlyph;
    BOOL containerBreakAfterCurGlyph;   /* If yes, go on to next container. */
    BOOL wrapAfterCurGlyph;		/* Indicates the the line fragment should be done after this glyph */
    float curSpaceAfter;		/* Manual kerning attribute; cached */
    float previousSpaceAfter;
    NSGlyphLayoutMode glyphLayoutMode;	/* Can we compose current glyph with previous; cached */
    float curGlyphExtentAboveLocation;	/* Distance above and below its display origin that the glyph requires */
    float curGlyphExtentBelowLocation;
    NSLayoutDirection curLayoutDirection;
    NSTextAlignment curTextAlignment;	/* Evaluated to be one of L, R, or C */

    /* Cached info about character attributes; these can last beyond one line fragment */
@public
    NSFont *curFont;			/* Current font; cached */
    NSRect curFontBoundingBox;		/* Bounding box for the current font; cached */
    BOOL curFontIsFixedPitch;		/* Whether or not the current font is fixed pitch, cached */
    NSPoint curFontAdvancement;		/* If curFontIsFixedPitch, this stores the advancement, cached */
    _NSPositionOfGlyphMethod curFontPositionOfGlyphMethod;	/* Obtained from methodFor, cached */
@private
    NSDictionary *attrs;	       	/* Attributes for the current glyph; cached */
    NSRange attrsRange;			/* And character range over which it applies */
    float curBaselineOffset;		/* Current baseline offset, from the baseline offset and superscript attrs; cached */
    float curMinBaselineDistance;	/* Minimum baseline distance attribute, cached */
    float curMaxBaselineDistance;	/* Maximum baseline distance attribute, cached */
    int curSuperscript;			/* Value of the superscript attr; cached */
    NSParagraphStyle *curParaStyle;	/* Paragraph attributes, cached */
    NSTextContainer *curContainer;
    unsigned curContainerIndex;
    float curContainerLineFragmentPadding;
    BOOL curContainerIsSimpleRectangular;	/* Whether the current container is simple rectangular, cached */
    NSSize curContainerSize;		/* [curContainer containerSize], cached */
    float curMinLineHeight;		/* [curParaStyle minLineHeight], cached */
    float curMaxLineHeight;		/* [curParaStyle maxLineHeight], cached */
    
    /* Other, more global info */
    NSString *textString;		/* Basically [textStorage string] */

    /* There is capacityOfGlyphs items in the following arrays. */
    unsigned capacityOfGlyphs;		/* Capacity of array pointed to by the following items */

    BOOL busy;	/* This typesetter is currently servicing a call; if the typesetter is "not busy" then none of the other accessor methods are valid, because typesetters don't maintain state across invocations of the main entry point. */

    struct {
	unsigned _glyphPostLay:1;
	unsigned _fragPostLay:1;
	unsigned _useItal:1;
        unsigned _curFontIsDefaultFace:1;
        unsigned _tabState:2;
        unsigned _tabType:2;
        unsigned _tabEOL:1;
	unsigned reserved:23;
    } _tsFlags;

@public
    /* Bidi-related cached info */
    unsigned char *glyphBidiLevelCache;
    unsigned char curBidiLevel;		/* Resolved bidirectional embedding level of current glyph */
    
@private
    unsigned char previousBidiLevel;
    unsigned char _reservedChars[2];
    unsigned _reserved2[6];
}

+ (id)sharedInstance; 

/* Methods that return global information.
*/
- (NSLayoutManager *)currentLayoutManager;
- (NSTextContainer *)currentContainer;
- (NSParagraphStyle *)currentParagraphStyle;
- (NSTextStorage *)currentTextStorage;
- (NSTypesetterGlyphInfo *)baseOfTypesetterGlyphInfo;
- (unsigned)sizeOfTypesetterGlyphInfo;
- (unsigned)capacityOfTypesetterGlyphInfo;
- (unsigned)firstGlyphIndexOfCurrentLineFragment;

/* Main public entry point
*/
- (void)layoutGlyphsInLayoutManager:(NSLayoutManager *)layoutManager startingAtGlyphIndex:(unsigned)startGlyphIndex maxNumberOfLineFragments:(unsigned)maxNumLines nextGlyphIndex:(unsigned *)nextGlyph;

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
- (unsigned)growGlyphCaches:(unsigned)desiredCapacity fillGlyphInfo:(BOOL)fillGlyphInfo;

/* Updates the location where the current glyph should be laid out. Often this isn't computed as it's not needed; however, this routine will bring it uptodate if necessary.
*/
- (void)updateCurGlyphOffset;

/* Only used for inserting hyphenation glyphs; never call layoutManager directly to insert glyphs; go through this method.
*/
- (void)insertGlyph:(NSGlyph)glyph atGlyphIndex:(unsigned)glyphIndex characterIndex:(unsigned)charIndex;

- (NSLayoutStatus)layoutControlGlyphForLineFragment:(NSRect)lineFrag;
- (void)layoutTab;

- (void)breakLineAtIndex:(unsigned)location;
- (unsigned)glyphIndexToBreakLineByHyphenatingWordAtIndex:(unsigned)charIndex;
- (unsigned)glyphIndexToBreakLineByWordWrappingAtIndex:(unsigned)charIndex;
- (void)layoutTab;
- (NSLayoutStatus)layoutControlGlyphForLineFragment:(NSRect)lineFrag;

- (void)fullJustifyLineAtGlyphIndex:(unsigned)glyphIndexForLineBreak;

@end

/* These methods can be OPTIONALLY implemented by subclasses of NSSimpleHorizontalTypesetter.
*/
@interface NSSimpleHorizontalTypesetter(NSTypesetterSubclassExtensions)

/* If implemented by subclasses, this is called within "layoutGlyphsInHorizontalLineFragment:baseline:" after laying out each glyph, allowing a subclass to hook into the layout machinery directly.  Variables curGlyph, curGlyphInscription, curBidiLevel, curCharacterIndex, curGlyphIsAControlGlyph, curFont, glyphLayoutMode, glyphs[curGlyphIndex] are guaranteed to be up-to-date.
*/
- (void)typesetterLaidOneGlyph:(NSTypesetterGlyphInfo *)gl;

/* If implemented by subclasses, this is called within "layoutGlyphsInHorizontalLineFragment:baseline:" after laying out each line fragment, immediately before "setLineFragmentRect:forGlyphRange:usedRect:" in the NSLayoutManager is called to record the used line fragment rectangles.  This is intended for subclasses to be able to affect e.g., linespacing globally.  The "used" rect is expected to be smaller than or equal to the "aRect".
*/
- (void) willSetLineFragmentRect:(NSRect *)aRect forGlyphRange:(NSRange)aRange usedRect:(NSRect *)bRect;

@end
#endif /* MAC_OS_X_VERSION_MIN_REQUIRED > MAC_OS_X_VERSION_10_4 */
