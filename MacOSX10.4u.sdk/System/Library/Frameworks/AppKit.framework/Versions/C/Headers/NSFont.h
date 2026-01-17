/*
	NSFont.h
	Application Kit
	Copyright (c) 1994-2005, Apple Computer, Inc.
	All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSString.h> // for NSStringEncoding
#import <AppKit/AppKitDefines.h>
#import <AppKit/NSCell.h> // for NSControlSize

@class NSFontDescriptor, NSAffineTransform, NSGraphicsContext;

/********* NSGlyph *********/
/* This is the Application Kit glyph ID.
*/
typedef unsigned int NSGlyph;

enum {
    NSControlGlyph = 0x00FFFFFF, // An NSGlyph value representing control characters (i.e. tab, line breaks, etc)
    NSNullGlyph = 0x0 // An NSGlyph value representing glyphs removed by the layout process
};

/********* Font Matrix *********/
/* This is a font matrix value representing [1 0 0 1 0 0].
*/
APPKIT_EXTERN const float *NSFontIdentityMatrix;

/********* Glyph packing *********/
/* Other glyph packing modes are deprecated.
*/
typedef enum {
    NSNativeShortGlyphPacking = 5
} NSMultibyteGlyphPacking;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
/********* Screen Font Rendering Mode *********/
typedef enum {
    NSFontDefaultRenderingMode = 0, // Determines the actual mode based on the user preference settings
    NSFontAntialiasedRenderingMode = 1, // Antialiased, floating-point advancements rendering mode (synonym to printerFont)
    NSFontIntegerAdvancementsRenderingMode = 2, // integer advancements rendering mode
    NSFontAntialiasedIntegerAdvancementsRenderingMode = 3 // Antialiased, integer advancements rendering mode
} NSFontRenderingMode;
#endif /* MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4 */

@interface NSFont : NSObject <NSCopying, NSCoding> {
    /* All instance variables are private */
    NSString *_name;
    float _size;
    void *_reservedFont1;
    struct __fFlags {
        unsigned int _isScreenFont:1;
        unsigned int _systemFontType:8;
        unsigned int _reserved1:4;
        unsigned int _matrixIsIdentity:1;
        unsigned int _renderingMode:3;
        unsigned int _reserved2:15;
    } _fFlags;
    id _private;
}

/********* Factory *********/
+ (NSFont *)fontWithName:(NSString *)fontName size:(float)fontSize;
+ (NSFont *)fontWithName:(NSString *)fontName matrix:(const float *)fontMatrix;
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
/* Instantiates an NSFont object matching fontDescriptor. If fontSize is greater than 0.0, it has precedence over NSFontSizeAttribute in fontDescriptor.
*/
+ (NSFont *)fontWithDescriptor:(NSFontDescriptor *)fontDescriptor size:(float)fontSize;

/* Instantiates an NSFont object matching fontDescriptor. If textTransform is non-nil, it has precedence over NSFontMatrixAttribute in fontDescriptor.
*/
+ (NSFont *)fontWithDescriptor:(NSFontDescriptor *)fontDescriptor textTransform:(NSAffineTransform *)textTransform;
#endif /* MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4 */

/********* Meta Font *********/
/* User font settings
*/
+ (NSFont *)userFontOfSize:(float)fontSize;	// Aqua Application font
+ (NSFont *)userFixedPitchFontOfSize:(float)fontSize; // Aqua fixed-pitch font
+ (void)setUserFont:(NSFont *)aFont;	// set preference for Application font.
+ (void)setUserFixedPitchFont:(NSFont *)aFont; // set preference for fixed-pitch.

/* UI font settings
*/
+ (NSFont *)systemFontOfSize:(float)fontSize;	// Aqua System font
+ (NSFont *)boldSystemFontOfSize:(float)fontSize; // Aqua System font (emphasized)
+ (NSFont *)labelFontOfSize:(float)fontSize; // Aqua label font

+ (NSFont *)titleBarFontOfSize:(float)fontSize;
+ (NSFont *)menuFontOfSize:(float)fontSize;
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3
+ (NSFont *)menuBarFontOfSize:(float)fontSize;
#endif /* MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3 */
+ (NSFont *)messageFontOfSize:(float)fontSize;
+ (NSFont *)paletteFontOfSize:(float)fontSize;
+ (NSFont *)toolTipsFontOfSize:(float)fontSize;
+ (NSFont *)controlContentFontOfSize:(float)fontSize;

/* UI font size settings
*/
+ (float)systemFontSize; // size of the standard System font.
+ (float)smallSystemFontSize; // size of standard small System font.
+ (float)labelFontSize;	// size of the standard Label Font.

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3
+ (float)systemFontSizeForControlSize:(NSControlSize)controlSize;
#endif /* MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3 */

/********* Core font attribute *********/
- (NSString *)fontName;
- (float)pointSize;
- (const float *)matrix;
- (NSString *)familyName;
- (NSString *)displayName;
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3
- (NSFontDescriptor *)fontDescriptor;
#endif /* MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3 */
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
- (NSAffineTransform *)textTransform;
#endif /* MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4 */

/********* Glyph coverage *********/
- (unsigned)numberOfGlyphs;
- (NSStringEncoding)mostCompatibleStringEncoding;
- (NSGlyph)glyphWithName:(NSString *)aName;
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_2
- (NSCharacterSet *)coveredCharacterSet;
#endif /* MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_2 */

/********* Font instance-wide metrics *********/
/* These methods return scaled numbers.  If the font was created with a matrix, the matrix is applied automatically; otherwise the coordinates are multiplied by size.
*/
- (NSRect)boundingRectForFont;
- (NSSize)maximumAdvancement;

- (float)ascender;
- (float)descender;
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
- (float)leading;
#endif /* MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4 */

- (float)underlinePosition;
- (float)underlineThickness;
- (float)italicAngle;
- (float)capHeight;
- (float)xHeight;
- (BOOL)isFixedPitch;

/********* Glyph metrics *********/
- (NSRect)boundingRectForGlyph:(NSGlyph)aGlyph;
- (NSSize)advancementForGlyph:(NSGlyph)ag;

// bulk query
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
- (void)getBoundingRects:(NSRectArray)bounds forGlyphs:(const NSGlyph *)glyphs count:(unsigned)glyphCount;
- (void)getAdvancements:(NSSizeArray)advancements forGlyphs:(const NSGlyph *)glyphs count:(unsigned)glyphCount;
- (void)getAdvancements:(NSSizeArray)advancements forPackedGlyphs:(const void *)packedGlyphs length:(unsigned)length; // only supports NSNativeShortGlyphPacking
#endif /* MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4 */

/********* NSGraphicsContext-related *********/
- (void)set;
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
- (void)setInContext:(NSGraphicsContext *)graphicsContext;
#endif /* MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4 */

/********* Rendering mode *********/
- (NSFont *)printerFont;
- (NSFont *)screenFont; // Same as screenFontWithRenderingMode:NSFontDefaultRenderingMode
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
- (NSFont *)screenFontWithRenderingMode:(NSFontRenderingMode)renderingMode;
- (NSFontRenderingMode)renderingMode;
#endif /* MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4 */
@end

/********* Glyph packing *********/
/* Take a buffer of NSGlyphs, of some given length, and a packing type, and a place to put some packed glyphs.  Pack up the NSGlyphs according to the NSMultibyteGlyphPacking, null-terminate the bytes, and then put them into the output buffer.  Return the count of bytes output, including the null-terminator.  The output buffer (packedGlyphs) provided by the caller is guaranteed to be at least "count*4+1" bytes long. This function only supports NSNativeShortGlyphPacking on Mac OS X.
*/
APPKIT_EXTERN int NSConvertGlyphsToPackedGlyphs(NSGlyph *glBuf, int count, NSMultibyteGlyphPacking packing, char *packedGlyphs);

/********* Notifications *********/
/* This notification is posted when the antialias threshold is changed by the user.
*/
APPKIT_EXTERN NSString *NSAntialiasThresholdChangedNotification AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* This notification is posted when the available font set is modified as a result of activation/deactivation.
*/
APPKIT_EXTERN NSString *NSFontSetChangedNotification AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/********* Deprecated API *********/
// The remaining portion is deprecated on Mac OS X 10.4 and Later.
#if MAC_OS_X_VERSION_MIN_REQUIRED <= MAC_OS_X_VERSION_10_4
typedef enum _NSGlyphRelation {
    NSGlyphBelow = 1,
    NSGlyphAbove = 2
} NSGlyphRelation;

/* Only NSNativeShortGlyphPacking is supported on Mac OS X.
*/
enum {
    NSOneByteGlyphPacking,
    NSJapaneseEUCGlyphPacking,
    NSAsciiWithDoubleByteEUCGlyphPacking,
    NSTwoByteGlyphPacking,
    NSFourByteGlyphPacking,
};

@interface NSFont (NSFontDeprecated)
+ (void)useFont:(NSString *)fontName; // This is now automatically handled by Quartz.
- (float)widthOfString:(NSString *)string; // This API never returns correct value. Use NSStringDrawing API instead.
- (BOOL)isBaseFont;
- (NSDictionary *)afmDictionary;
- (BOOL)glyphIsEncoded:(NSGlyph)aGlyph; // Can be deduced by aGlyph < [NSFont numberOfGlyphs] since only NSNativeShortGlyphPacking is supported.
- (float)defaultLineHeightForFont; // Use -[NSLayoutManager defaultLineHeightForFont:] instead.
+ (NSArray *)preferredFontNames; // NSFontCascadeListAttribute offers more powerful font substitution management
+ (void)setPreferredFontNames:(NSArray *)fontNameArray;
- (NSString *)encodingScheme;
- (NSMultibyteGlyphPacking) glyphPacking;

// The context-sensitive inter-glyph spacing is now performed at the typesetting stage.
- (NSPoint)positionOfGlyph:(NSGlyph)curGlyph precededByGlyph:(NSGlyph)prevGlyph isNominal:(BOOL *)nominal;
- (int)positionsForCompositeSequence:(NSGlyph *)someGlyphs numberOfGlyphs:(int)numGlyphs pointArray:(NSPointArray)points;
- (NSPoint)positionOfGlyph:(NSGlyph)curGlyph struckOverGlyph:(NSGlyph)prevGlyph metricsExist:(BOOL *)exist;
- (NSPoint)positionOfGlyph:(NSGlyph)aGlyph struckOverRect:(NSRect)aRect metricsExist:(BOOL *)exist;
- (NSPoint)positionOfGlyph:(NSGlyph)aGlyph forCharacter:(unichar)aChar struckOverRect:(NSRect)aRect;
- (NSPoint)positionOfGlyph:(NSGlyph)thisGlyph withRelation:(NSGlyphRelation)rel toBaseGlyph:(NSGlyph)baseGlyph totalAdvancement:(NSSizePointer)adv metricsExist:(BOOL *)exist;
@end
#endif /* MAC_OS_X_VERSION_MIN_REQUIRED <= MAC_OS_X_VERSION_10_4 */

APPKIT_EXTERN NSString *NSAFMFamilyName         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;
APPKIT_EXTERN NSString *NSAFMFontName           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;
APPKIT_EXTERN NSString *NSAFMFormatVersion      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;
APPKIT_EXTERN NSString *NSAFMFullName           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;
APPKIT_EXTERN NSString *NSAFMNotice             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;
APPKIT_EXTERN NSString *NSAFMVersion            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;
APPKIT_EXTERN NSString *NSAFMWeight             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;
APPKIT_EXTERN NSString *NSAFMEncodingScheme     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;
APPKIT_EXTERN NSString *NSAFMCharacterSet       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;
APPKIT_EXTERN NSString *NSAFMCapHeight          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;
APPKIT_EXTERN NSString *NSAFMXHeight            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;
APPKIT_EXTERN NSString *NSAFMAscender           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;
APPKIT_EXTERN NSString *NSAFMDescender          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;
APPKIT_EXTERN NSString *NSAFMUnderlinePosition  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;
APPKIT_EXTERN NSString *NSAFMUnderlineThickness AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;
APPKIT_EXTERN NSString *NSAFMItalicAngle        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;
APPKIT_EXTERN NSString *NSAFMMappingScheme      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;
