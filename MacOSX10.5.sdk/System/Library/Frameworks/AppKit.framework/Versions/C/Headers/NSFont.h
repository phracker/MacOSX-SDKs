/*
	NSFont.h
	Application Kit
	Copyright (c) 1994-2007, Apple Inc.
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
APPKIT_EXTERN const CGFloat *NSFontIdentityMatrix;

/********* Glyph packing *********/
/* Other glyph packing modes are deprecated.
*/
enum {
    NSNativeShortGlyphPacking = 5
};
typedef NSUInteger NSMultibyteGlyphPacking;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
/********* Screen Font Rendering Mode *********/
enum {
    NSFontDefaultRenderingMode = 0, // Determines the actual mode based on the user preference settings
    NSFontAntialiasedRenderingMode = 1, // Antialiased, floating-point advancements rendering mode (synonym to printerFont)
    NSFontIntegerAdvancementsRenderingMode = 2, // integer advancements rendering mode
    NSFontAntialiasedIntegerAdvancementsRenderingMode = 3 // Antialiased, integer advancements rendering mode
};
typedef NSUInteger NSFontRenderingMode;
#endif /* MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4 */

@interface NSFont : NSObject <NSCopying, NSCoding> {
    /* All instance variables are private */
    NSString *_name;
    CGFloat _size;
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
+ (NSFont *)fontWithName:(NSString *)fontName size:(CGFloat)fontSize;
+ (NSFont *)fontWithName:(NSString *)fontName matrix:(const CGFloat *)fontMatrix;
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
/* Instantiates an NSFont object matching fontDescriptor. If fontSize is greater than 0.0, it has precedence over NSFontSizeAttribute in fontDescriptor.
*/
+ (NSFont *)fontWithDescriptor:(NSFontDescriptor *)fontDescriptor size:(CGFloat)fontSize;

/* Instantiates an NSFont object matching fontDescriptor. If textTransform is non-nil, it has precedence over NSFontMatrixAttribute in fontDescriptor.
*/
+ (NSFont *)fontWithDescriptor:(NSFontDescriptor *)fontDescriptor textTransform:(NSAffineTransform *)textTransform;
#endif /* MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4 */

/********* Meta Font *********/
/* User font settings
*/
+ (NSFont *)userFontOfSize:(CGFloat)fontSize;	// Aqua Application font
+ (NSFont *)userFixedPitchFontOfSize:(CGFloat)fontSize; // Aqua fixed-pitch font
+ (void)setUserFont:(NSFont *)aFont;	// set preference for Application font.
+ (void)setUserFixedPitchFont:(NSFont *)aFont; // set preference for fixed-pitch.

/* UI font settings
*/
+ (NSFont *)systemFontOfSize:(CGFloat)fontSize;	// Aqua System font
+ (NSFont *)boldSystemFontOfSize:(CGFloat)fontSize; // Aqua System font (emphasized)
+ (NSFont *)labelFontOfSize:(CGFloat)fontSize; // Aqua label font

+ (NSFont *)titleBarFontOfSize:(CGFloat)fontSize;
+ (NSFont *)menuFontOfSize:(CGFloat)fontSize;
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3
+ (NSFont *)menuBarFontOfSize:(CGFloat)fontSize;
#endif /* MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3 */
+ (NSFont *)messageFontOfSize:(CGFloat)fontSize;
+ (NSFont *)paletteFontOfSize:(CGFloat)fontSize;
+ (NSFont *)toolTipsFontOfSize:(CGFloat)fontSize;
+ (NSFont *)controlContentFontOfSize:(CGFloat)fontSize;

/* UI font size settings
*/
+ (CGFloat)systemFontSize; // size of the standard System font.
+ (CGFloat)smallSystemFontSize; // size of standard small System font.
+ (CGFloat)labelFontSize;	// size of the standard Label Font.

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3
+ (CGFloat)systemFontSizeForControlSize:(NSControlSize)controlSize;
#endif /* MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3 */

/********* Core font attribute *********/
- (NSString *)fontName;
- (CGFloat)pointSize;
- (const CGFloat *)matrix;
- (NSString *)familyName;
- (NSString *)displayName;
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3
- (NSFontDescriptor *)fontDescriptor;
#endif /* MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3 */
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
- (NSAffineTransform *)textTransform;
#endif /* MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4 */

/********* Glyph coverage *********/
- (NSUInteger)numberOfGlyphs;
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

- (CGFloat)ascender;
- (CGFloat)descender;
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
- (CGFloat)leading;
#endif /* MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4 */

- (CGFloat)underlinePosition;
- (CGFloat)underlineThickness;
- (CGFloat)italicAngle;
- (CGFloat)capHeight;
- (CGFloat)xHeight;
- (BOOL)isFixedPitch;

/********* Glyph metrics *********/
- (NSRect)boundingRectForGlyph:(NSGlyph)aGlyph;
- (NSSize)advancementForGlyph:(NSGlyph)ag;

// bulk query
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
- (void)getBoundingRects:(NSRectArray)bounds forGlyphs:(const NSGlyph *)glyphs count:(NSUInteger)glyphCount;
- (void)getAdvancements:(NSSizeArray)advancements forGlyphs:(const NSGlyph *)glyphs count:(NSUInteger)glyphCount;
- (void)getAdvancements:(NSSizeArray)advancements forPackedGlyphs:(const void *)packedGlyphs length:(NSUInteger)length; // only supports NSNativeShortGlyphPacking
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
APPKIT_EXTERN NSInteger NSConvertGlyphsToPackedGlyphs(NSGlyph *glBuf, NSInteger count, NSMultibyteGlyphPacking packing, char *packedGlyphs);

/********* Notifications *********/
/* This notification is posted when the antialias threshold is changed by the user.
*/
APPKIT_EXTERN NSString *NSAntialiasThresholdChangedNotification AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* This notification is posted when the available font set is modified as a result of activation/deactivation.
*/
APPKIT_EXTERN NSString *NSFontSetChangedNotification AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/********* Deprecated API *********/
// The remaining portion is deprecated on Mac OS X 10.4 and Later.
#if !__LP64__
#if MAC_OS_X_VERSION_MIN_REQUIRED <= MAC_OS_X_VERSION_10_4
/* Only NSNativeShortGlyphPacking is supported on Mac OS X.
*/
enum {
    NSOneByteGlyphPacking,
    NSJapaneseEUCGlyphPacking,
    NSAsciiWithDoubleByteEUCGlyphPacking,
    NSTwoByteGlyphPacking,
    NSFourByteGlyphPacking,
};

enum _NSGlyphRelation {
    NSGlyphBelow = 1,
    NSGlyphAbove = 2
};
#endif /* MAC_OS_X_VERSION_MIN_REQUIRED <= MAC_OS_X_VERSION_10_4 */
typedef NSUInteger  NSGlyphRelation;

@interface NSFont (NSFontDeprecated)
+ (void)useFont:(NSString *)fontName DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER; // This is now automatically handled by Quartz.
- (CGFloat)widthOfString:(NSString *)string DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER; // This API never returns correct value. Use NSStringDrawing API instead.
- (BOOL)isBaseFont DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;
- (NSDictionary *)afmDictionary DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;
- (BOOL)glyphIsEncoded:(NSGlyph)aGlyph DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER; // Can be deduced by aGlyph < [NSFont numberOfGlyphs] since only NSNativeShortGlyphPacking is supported.
- (CGFloat)defaultLineHeightForFont DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER; // Use -[NSLayoutManager defaultLineHeightForFont:] instead.
+ (NSArray *)preferredFontNames DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER; // NSFontCascadeListAttribute offers more powerful font substitution management
+ (void)setPreferredFontNames:(NSArray *)fontNameArray DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;
- (NSString *)encodingScheme DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;
- (NSMultibyteGlyphPacking) glyphPacking DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;

// The context-sensitive inter-glyph spacing is now performed at the typesetting stage.
- (NSPoint)positionOfGlyph:(NSGlyph)curGlyph precededByGlyph:(NSGlyph)prevGlyph isNominal:(BOOL *)nominal DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;
- (NSInteger)positionsForCompositeSequence:(NSGlyph *)someGlyphs numberOfGlyphs:(NSInteger)numGlyphs pointArray:(NSPointArray)points DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;
- (NSPoint)positionOfGlyph:(NSGlyph)curGlyph struckOverGlyph:(NSGlyph)prevGlyph metricsExist:(BOOL *)exist DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;
- (NSPoint)positionOfGlyph:(NSGlyph)aGlyph struckOverRect:(NSRect)aRect metricsExist:(BOOL *)exist DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;
- (NSPoint)positionOfGlyph:(NSGlyph)aGlyph forCharacter:(unichar)aChar struckOverRect:(NSRect)aRect DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;
- (NSPoint)positionOfGlyph:(NSGlyph)thisGlyph withRelation:(NSGlyphRelation)rel toBaseGlyph:(NSGlyph)baseGlyph totalAdvancement:(NSSizePointer)adv metricsExist:(BOOL *)exist DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;
@end

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
#endif /* !__LP64__ */
