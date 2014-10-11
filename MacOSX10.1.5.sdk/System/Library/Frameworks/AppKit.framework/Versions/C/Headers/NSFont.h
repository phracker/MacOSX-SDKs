/*
	NSFont.h
	Application Kit
	Copyright (c) 1994-2001, Apple Computer, Inc.
	All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSString.h>
#import <Foundation/NSGeometry.h>
#import <AppKit/AppKitDefines.h>

@class NSArray;

typedef unsigned int NSGlyph;

enum {
    NSControlGlyph = 0x00FFFFFF,
    NSNullGlyph = 0x0
};

typedef enum _NSGlyphRelation {
    NSGlyphBelow = 1,
    NSGlyphAbove = 2
} NSGlyphRelation;

/* These are values that tell us how to extract glyphs from a font for making a multi-byte (or single byte) array of glyphs for passing to an interpreter, such as the window server, which expects a big-endian multi-byte stream (i.e., packed glyphs") instead of a pure NSGlyph stream.
*/
typedef enum _NSMultibyteGlyphPacking {
    NSOneByteGlyphPacking,
    NSJapaneseEUCGlyphPacking,
    NSAsciiWithDoubleByteEUCGlyphPacking,
    NSTwoByteGlyphPacking,
    NSFourByteGlyphPacking,
    NSNativeShortGlyphPacking
} NSMultibyteGlyphPacking;

APPKIT_EXTERN const float *NSFontIdentityMatrix;

@interface NSFont : NSObject <NSCopying, NSCoding> {
/*All instance variables are private*/
    NSString *_name;
    float _size;
    void *_reservedFont1;
    struct __fFlags {
      /* the following instance variables are no longer part of the API */
	unsigned int usedByWS:1;
	unsigned int usedByPrinter:1;
	unsigned int isScreenFont:1;
	unsigned int _systemFontType:4;
	unsigned int _flippedUsedByWS:1;
	unsigned int _flippedUsedByPrinter:1;
	unsigned int _hasCharWidth:1;
	unsigned int _RESERVED:3;
	unsigned int _matrixIsIdentity:1;
	unsigned int _matrixIsFlipped:1;
	unsigned int _hasStyle:1;
    } _fFlags;
    unsigned short _reservedFont2;
}

+ (NSFont *)fontWithName:(NSString *)fontName size:(float)fontSize;
+ (NSFont *)fontWithName:(NSString *)fontName matrix:(const float *)fontMatrix;
+ (void)useFont:(NSString *)fontName;

/* Getting/setting user/app fonts...
*/
+ (NSFont *)userFontOfSize:(float)fontSize;	// Aqua Application font
+ (NSFont *)userFixedPitchFontOfSize:(float)fontSize; // Aqua fixed-pitch font
+ (void)setUserFont:(NSFont *)aFont;	// set preference for Application font.
+ (void)setUserFixedPitchFont:(NSFont *)aFont; // set preference for fixed-pitch.

/* Methods for "system fonts"...
*/
+ (NSFont *)systemFontOfSize:(float)fontSize;	// Aqua System font
+ (NSFont *)boldSystemFontOfSize:(float)fontSize; // Aqua System font (emphasized)
+ (NSFont *)labelFontOfSize:(float)fontSize; // Aqua label font

+ (float) systemFontSize;	// size of the standard System font.
+ (float) smallSystemFontSize;	// size of standard small System font.
+ (float) labelFontSize;	// size of the standard Label Font.

/* The six methods below are for getting various types of pre-defined fonts... corresponding to older Windows & OpenStep API.
*/
+ (NSFont *)titleBarFontOfSize:(float)fontSize;
+ (NSFont *)menuFontOfSize:(float)fontSize;
+ (NSFont *)messageFontOfSize:(float)fontSize;
+ (NSFont *)paletteFontOfSize:(float)fontSize;
+ (NSFont *)toolTipsFontOfSize:(float)fontSize;
+ (NSFont *)controlContentFontOfSize:(float)fontSize;

- (float)pointSize;
- (NSString *)fontName;
- (NSString *)familyName;
- (NSString *)displayName;

- (const float *)matrix;
- (void)set;
- (float)widthOfString:(NSString *)string;
- (NSFont *)screenFont;
- (NSFont *)printerFont;

- (BOOL)isBaseFont; // this method is obsolete and should not be used.

/* These methods return scaled numbers.  If the font was created with a matrix, the matrix is applied automatically; otherwise the coordinates are multiplied by size.
*/
- (NSRect)boundingRectForFont;
- (float) defaultLineHeightForFont; // ascent + descent + linegap
- (NSRect)boundingRectForGlyph:(NSGlyph)aGlyph;
- (NSSize)advancementForGlyph:(NSGlyph)ag;
- (NSDictionary *)afmDictionary; // only applicable to some fonts; deprecated.
- (BOOL)glyphIsEncoded:(NSGlyph)aGlyph;

+ (NSArray *)preferredFontNames;
+ (void)setPreferredFontNames:(NSArray *)fontNameArray;

- (NSSize) maximumAdvancement; // returns widest advancement, or constant advancement if the font is fixed-pitch.
- (NSStringEncoding) mostCompatibleStringEncoding;

- (unsigned) numberOfGlyphs;	/* how many glyphs are in the font; numbered 0-n. */
- (float) underlinePosition;	/* was fontUnderlinePosition */
- (float) underlineThickness;	/* was fontUnderlineThickness */
- (float) italicAngle;	/* was fontItalicAngle */
- (float) capHeight;	/* used for translating vertical baselines */
- (float) xHeight;
- (float) ascender;
- (float) descender;
- (BOOL) isFixedPitch;
- (NSString *) encodingScheme;
- (NSGlyph) glyphWithName:(NSString *)aName;

/* Glyph related methods.

The position of a glyph is where you need to be to show the glyph. The position is relative to the position of the other glyph supplied as argument. If other glyph is 0 (no glyph), then this reduces to being relative to the origin.

The optional isNominal argument indicates whether the returned position is the standard advancement specified for the previous glyph (ie, width from the AFM file). It could be NO if the two glyphs are kerned, for instance.

The optional metricsExist argument specifies whether the metrics for the combination were found; if not, the returned point will be computed using the bounding boxes of the glyphs and may not be very pretty.

*/

/* Position two base glyphs next to each other.  In this method, 0 (i.e., no glyph) may be specified for either glyph.
*/
- (NSPoint)positionOfGlyph:(NSGlyph)curGlyph precededByGlyph:(NSGlyph)prevGlyph isNominal:(BOOL *)nominal;

/* Given a base glyph followed by a bunch of "overstruck" glyphs, see if there's a corresponding set of metrics in the font.  If so, return the NUMBER of matching glyphs from the group and fill in "points" with the positions, relative to (0,0) for the base glyph.  Partial sequences may be returned.  If the return value is less than numGlyphs, then the leftover glyphs can be rendered via positionOfGlyph:forCharacter:struckOverRect:, using the union-rect of the glyphs for which the font had metrics.
*/
- (int) positionsForCompositeSequence:(NSGlyph *)someGlyphs numberOfGlyphs:(int)numGlyphs pointArray:(NSPointArray)points;

/* Basic base/accent positioning.  Try to position the glyphs, using metric information if it exists.  If metrics do not exist, this method may defer to "positionOfGlyph:struckOverRect:metricsExist:" for the answer.  In any case, if metrics do not exist, the answer may be invalid.
*/
- (NSPoint)positionOfGlyph:(NSGlyph)curGlyph struckOverGlyph:(NSGlyph)prevGlyph metricsExist:(BOOL *)exist;

/* Base/accent positioning when a previous glyph (i.e., aRect) may not be in the same font or has no metrics -- use its rectangle.  Try to position the glyphs, using generalized metric information if it exists.  If metrics do not exist, the result may not be valid.
*/
- (NSPoint)positionOfGlyph:(NSGlyph)aGlyph struckOverRect:(NSRect)aRect metricsExist:(BOOL *)exist;

/* As a last resort, this attempts to do positioning of base/accent based on semantic knowledge of various "accent" characters.  It is NOT guaranteed to be pretty, but works in the absence of proper metrics for "many" diacritical marks in the Latin, Greek, and Cyrillic scripts.  The caller asserts that "aGlyph" is a rendering in the font for the Unicode character "aChar".  The rectangle is presumed to be the rectangle of some other glyph, whether known in this font or not.  The returned position tells where to put "aGlyph" in relation to "aRect"; i.e., presuming aRect is shown at {0,0} one may "moveto" the returned position and show "aGlyph".
*/
- (NSPoint)positionOfGlyph:(NSGlyph)aGlyph forCharacter:(unichar)aChar struckOverRect:(NSRect)aRect;

/* This is for specific types of positioning above/below (mainly for Indic support).  Metric support is usually required for the result to be pretty.  The default is to join glyphs without gaps and return the advancement of baseGlyph.
*/
- (NSPoint)positionOfGlyph:(NSGlyph)thisGlyph withRelation:(NSGlyphRelation)rel toBaseGlyph:(NSGlyph)baseGlyph totalAdvancement:(NSSizePointer)adv metricsExist:(BOOL *)exist;

/* This simply returns the font's packing type.
*/
- (NSMultibyteGlyphPacking) glyphPacking;

@end

/* Take a buffer of NSGlyphs, of some given length, and a packing type, and a place to put some packed glyphs.  Pack up the NSGlyphs according to the NSMultibyteGlyphPacking, null-terminate the bytes, and then put them into the output buffer.  Return the count of bytes output, including the null-terminator.  The output buffer (packedGlyphs) provided by the caller is guaranteed to be at least "count*4+1" bytes long.
*/
int NSConvertGlyphsToPackedGlyphs(NSGlyph *glBuf, int count, NSMultibyteGlyphPacking packing, char *packedGlyphs);

/* These are the strings that are available in the "afmDictionary".  For other things, use "afmFileContents".  The floating point values (e.g., ascender, cap height) can be converted to floating point via NSString's "floatValue" method.
*/
APPKIT_EXTERN NSString *NSAFMFamilyName;
APPKIT_EXTERN NSString *NSAFMFontName;
APPKIT_EXTERN NSString *NSAFMFormatVersion;
APPKIT_EXTERN NSString *NSAFMFullName;
APPKIT_EXTERN NSString *NSAFMNotice;
APPKIT_EXTERN NSString *NSAFMVersion;
APPKIT_EXTERN NSString *NSAFMWeight;
APPKIT_EXTERN NSString *NSAFMEncodingScheme;
APPKIT_EXTERN NSString *NSAFMCharacterSet;

APPKIT_EXTERN NSString *NSAFMCapHeight;
APPKIT_EXTERN NSString *NSAFMXHeight;
APPKIT_EXTERN NSString *NSAFMAscender;
APPKIT_EXTERN NSString *NSAFMDescender;
APPKIT_EXTERN NSString *NSAFMUnderlinePosition;
APPKIT_EXTERN NSString *NSAFMUnderlineThickness;
APPKIT_EXTERN NSString *NSAFMItalicAngle;
APPKIT_EXTERN NSString *NSAFMMappingScheme;

