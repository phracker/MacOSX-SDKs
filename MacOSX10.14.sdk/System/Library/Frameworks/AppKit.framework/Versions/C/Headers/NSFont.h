/*
	NSFont.h
	Application Kit
	Copyright (c) 1994-2018, Apple Inc.
	All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSString.h> // for NSStringEncoding
#import <AppKit/AppKitDefines.h>
#import <AppKit/NSCell.h> // for NSControlSize
#import <AppKit/NSFontDescriptor.h>

NS_ASSUME_NONNULL_BEGIN

@class NSFontDescriptor, NSAffineTransform, NSGraphicsContext;

/********* Font Matrix *********/
/* This is a font matrix value representing [1 0 0 1 0 0].
*/
APPKIT_EXTERN const CGFloat * NSFontIdentityMatrix;

NS_AUTOMATED_REFCOUNT_WEAK_UNAVAILABLE
@interface NSFont : NSObject <NSCopying, NSSecureCoding> {
    /* All instance variables are private */
    NSString *_name APPKIT_IVAR;
    CGFloat _size APPKIT_IVAR;
    NSInteger _retainCount APPKIT_IVAR;
    struct __fFlags {
        unsigned int _isScreenFont:1;
        unsigned int _systemFontType:8;
        unsigned int _reserved1:4;
        unsigned int _matrixIsIdentity:1;
        unsigned int _renderingMode:3;
        unsigned int _inInstanceCache:1;
        unsigned int _appearanceSize:1;
        unsigned int _reserved2:13;
    } _fFlags APPKIT_IVAR;
    id _private APPKIT_IVAR;
}

/********* Factory *********/
+ (nullable NSFont *)fontWithName:(NSString *)fontName size:(CGFloat)fontSize;
+ (nullable NSFont *)fontWithName:(NSString *)fontName matrix:(const CGFloat *)fontMatrix;
/* Instantiates an NSFont object matching fontDescriptor. If fontSize is greater than 0.0, it has precedence over NSFontSizeAttribute in fontDescriptor.
*/
+ (nullable NSFont *)fontWithDescriptor:(NSFontDescriptor *)fontDescriptor size:(CGFloat)fontSize;

/* Instantiates an NSFont object matching fontDescriptor. If textTransform is non-nil, it has precedence over NSFontMatrixAttribute in fontDescriptor.
*/
+ (nullable NSFont *)fontWithDescriptor:(NSFontDescriptor *)fontDescriptor textTransform:(nullable NSAffineTransform *)textTransform;

/********* Meta Font *********/
/* User font settings
*/
+ (nullable NSFont *)userFontOfSize:(CGFloat)fontSize;	// Application font
+ (nullable NSFont *)userFixedPitchFontOfSize:(CGFloat)fontSize; // fixed-pitch font
+ (void)setUserFont:(nullable NSFont *)font;	// set preference for Application font.
+ (void)setUserFixedPitchFont:(nullable NSFont *)font; // set preference for fixed-pitch.

/* UI font settings
*/
+ (NSFont *)systemFontOfSize:(CGFloat)fontSize;	// System font with NSFontWeightRegular and proportional digits
+ (NSFont *)boldSystemFontOfSize:(CGFloat)fontSize; // System font with NSFontWeightBold and proportional digits
+ (NSFont *)labelFontOfSize:(CGFloat)fontSize; // Label font

+ (NSFont *)titleBarFontOfSize:(CGFloat)fontSize;
+ (NSFont *)menuFontOfSize:(CGFloat)fontSize;
+ (NSFont *)menuBarFontOfSize:(CGFloat)fontSize;
+ (NSFont *)messageFontOfSize:(CGFloat)fontSize;
+ (NSFont *)paletteFontOfSize:(CGFloat)fontSize;
+ (NSFont *)toolTipsFontOfSize:(CGFloat)fontSize;
+ (NSFont *)controlContentFontOfSize:(CGFloat)fontSize;

/* Following two factory methods return system font with NSFontWeightTrait. Returns the system font object corresponding to fontSize and weight. +monospacedDigitSystemFontOfSize:weight: always return a system font instance with monospaced digit glyphs. It's recommended to use the symbolic weight values declared in NSFontDescriptor.h. Due to sophisticated system font weight matching logic underneath, it's recommended to use this factory method all the time when getting non-standard weight system fonts instead of transforming existing instances via methods like -[NSFontManager convertFont:toSize]. When asked for a missing weight for the running version of OS X, this method returns the nearest heavier weight available if the application is linked against the current or older SDK; otherwise, it returns the nearest lighter weight available.
*/
+ (NSFont *)systemFontOfSize:(CGFloat)fontSize weight:(NSFontWeight)weight NS_AVAILABLE_MAC(10_11);
+ (NSFont *)monospacedDigitSystemFontOfSize:(CGFloat)fontSize weight:(NSFontWeight)weight NS_AVAILABLE_MAC(10_11);

/* UI font size settings
*/
@property (class, readonly) CGFloat systemFontSize; // size of the standard System font.
@property (class, readonly) CGFloat smallSystemFontSize; // size of standard small System font.
@property (class, readonly) CGFloat labelFontSize; // size of the standard Label Font.

+ (CGFloat)systemFontSizeForControlSize:(NSControlSize)controlSize;

/********* Core font attribute *********/
@property (readonly, copy) NSString *fontName;
@property (readonly) CGFloat pointSize;
@property (readonly) const CGFloat *matrix NS_RETURNS_INNER_POINTER;
@property (nullable, readonly, copy) NSString *familyName;
@property (nullable, readonly, copy) NSString *displayName;
@property (readonly, strong) NSFontDescriptor *fontDescriptor;
@property (readonly, copy) NSAffineTransform *textTransform;

/********* Glyph coverage *********/
@property (readonly) NSUInteger numberOfGlyphs;
@property (readonly) NSStringEncoding mostCompatibleStringEncoding;
@property (readonly, strong) NSCharacterSet *coveredCharacterSet;

/********* Font instance-wide metrics *********/
/* These methods return scaled numbers.  If the font was created with a matrix, the matrix is applied automatically; otherwise the coordinates are multiplied by size.
*/
@property (readonly) NSRect boundingRectForFont;
@property (readonly) NSSize maximumAdvancement;

@property (readonly) CGFloat ascender;
@property (readonly) CGFloat descender;
@property (readonly) CGFloat leading;

@property (readonly) CGFloat underlinePosition;
@property (readonly) CGFloat underlineThickness;
@property (readonly) CGFloat italicAngle;
@property (readonly) CGFloat capHeight;
@property (readonly) CGFloat xHeight;
@property (getter=isFixedPitch, readonly) BOOL fixedPitch;

/********* Glyph metrics *********/
/********* Glyph metrics *********/
- (NSRect)boundingRectForCGGlyph:(CGGlyph)glyph NS_AVAILABLE_MAC(10_13);
- (NSSize)advancementForCGGlyph:(CGGlyph)glyph NS_AVAILABLE_MAC(10_13);

// bulk query
- (void)getBoundingRects:(NSRectArray)bounds forCGGlyphs:(const CGGlyph *)glyphs count:(NSUInteger)glyphCount NS_AVAILABLE_MAC(10_13);
- (void)getAdvancements:(NSSizeArray)advancements forCGGlyphs:(const CGGlyph *)glyphs count:(NSUInteger)glyphCount NS_AVAILABLE_MAC(10_13);

/********* NSGraphicsContext-related *********/
- (void)set;
- (void)setInContext:(NSGraphicsContext *)graphicsContext;

/********* Vertical mode *********/
/* Returns a vertical version of the receiver if such a configuration is supported.  Returns the receiver if no vertical variant available.  A vertical font applies appropriate rotation to the text matrix in -setInContext:, returns vertical metrics, and enables the vertical glyph substitution feature by default. */
@property (readonly, copy) NSFont *verticalFont NS_AVAILABLE_MAC(10_7);

/* Returns YES if a vertical variant */
@property (getter=isVertical, readonly) BOOL vertical NS_AVAILABLE_MAC(10_7);
@end

/********* Notifications *********/
/* This notification is posted when the antialias threshold is changed by the user.
*/
APPKIT_EXTERN NSNotificationName NSAntialiasThresholdChangedNotification;

/* This notification is posted when the available font set is modified as a result of activation/deactivation.
*/
APPKIT_EXTERN NSNotificationName NSFontSetChangedNotification;


/********* Deprecated API *********/
// NSGlyph and related API are soft deprecated. They will be formally deprecated in a future version. Use CGGlyph-based TextKit API instead
typedef unsigned int NSGlyph; // Use CGGlyph instead

enum {
    NSControlGlyph = 0x00FFFFFF, // Deprecated. Use NSGlyphPropertyControlCharacter instead
    NSNullGlyph = 0x0 // Deprecated. Use NSGlyphPropertyNull instead
};

// NSFontRenderingMode-related API is now deprecated.
/********* Screen Font Rendering Mode *********/
typedef NS_ENUM(NSUInteger, NSFontRenderingMode) {
    NSFontDefaultRenderingMode = 0, // Determines the actual mode based on the user preference settings
    NSFontAntialiasedRenderingMode = 1, // Antialiased, floating-point advancements rendering mode (synonym to printerFont)
    NSFontIntegerAdvancementsRenderingMode = 2, // integer advancements rendering mode
    NSFontAntialiasedIntegerAdvancementsRenderingMode = 3 // Antialiased, integer advancements rendering mode
};

typedef NS_ENUM(NSUInteger, NSMultibyteGlyphPacking) {
    NSNativeShortGlyphPacking NS_ENUM_DEPRECATED_MAC(10_0, 10_13) = 5
} NS_ENUM_DEPRECATED_MAC(10_0, 10_13);

APPKIT_EXTERN NSInteger NSConvertGlyphsToPackedGlyphs(NSGlyph * __nonnull glBuf, NSInteger count, NSMultibyteGlyphPacking packing, char * __nonnull packedGlyphs) NS_DEPRECATED_MAC(10_0, 10_13);

@interface NSFont (NSFont_Deprecated)
- (NSGlyph)glyphWithName:(NSString *)name;
- (NSRect)boundingRectForGlyph:(NSGlyph)glyph; // Deprecated. Use -boundingRectForCGGlyph: instead
- (NSSize)advancementForGlyph:(NSGlyph)glyph; // Deprecated. Use -advancementForCGGlyph: instead

// bulk query
- (void)getBoundingRects:(NSRectArray)bounds forGlyphs:(const NSGlyph *)glyphs count:(NSUInteger)glyphCount; // Deprecated. Use -getBoundingRects:forCGGlyphs:count: instead
- (void)getAdvancements:(NSSizeArray)advancements forGlyphs:(const NSGlyph *)glyphs count:(NSUInteger)glyphCount; // Deprecated. Use -getAdvancements:forCGGlyphs:count: insteda
- (void)getAdvancements:(NSSizeArray)advancements forPackedGlyphs:(const void *)packedGlyphs length:(NSUInteger)length; // Deprecated. Use -getAdvancements:forCGGlyphs:count: instead

/********* Rendering mode *********/
@property (readonly, copy) NSFont *printerFont;
@property (readonly, copy) NSFont *screenFont;
- (NSFont *)screenFontWithRenderingMode:(NSFontRenderingMode)renderingMode;
@property (readonly) NSFontRenderingMode renderingMode;
@end

NS_ASSUME_NONNULL_END

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
} NS_ENUM_DEPRECATED_MAC(10_0, 10_4);

enum _NSGlyphRelation {
    NSGlyphBelow = 1,
    NSGlyphAbove = 2
} NS_ENUM_DEPRECATED_MAC(10_0, 10_4);
#endif /* MAC_OS_X_VERSION_MIN_REQUIRED <= MAC_OS_X_VERSION_10_4 */
typedef NSUInteger  NSGlyphRelation NS_DEPRECATED_MAC(10_0, 10_4);

@interface NSFont (NSFontDeprecated)
+ (void)useFont:(null_unspecified NSString *)fontName NS_DEPRECATED_MAC(10_0, 10_4); // This is now automatically handled by Quartz.
- (CGFloat)widthOfString:(null_unspecified NSString *)string NS_DEPRECATED_MAC(10_0, 10_4); // This API never returns correct value. Use NSStringDrawing API instead.
- (BOOL)isBaseFont NS_DEPRECATED_MAC(10_0, 10_4);
- (null_unspecified NSDictionary *)afmDictionary NS_DEPRECATED_MAC(10_0, 10_4);
- (BOOL)glyphIsEncoded:(NSGlyph)glyph NS_DEPRECATED_MAC(10_0, 10_4); // Can be deduced by aGlyph < [NSFont numberOfGlyphs] since only NSNativeShortGlyphPacking is supported.
- (CGFloat)defaultLineHeightForFont NS_DEPRECATED_MAC(10_0, 10_4); // Use -[NSLayoutManager defaultLineHeightForFont:] instead.
+ (null_unspecified NSArray *)preferredFontNames NS_DEPRECATED_MAC(10_0, 10_4); // NSFontCascadeListAttribute offers more powerful font substitution management
+ (void)setPreferredFontNames:(null_unspecified NSArray *)fontNameArray NS_DEPRECATED_MAC(10_0, 10_4);
- (null_unspecified NSString *)encodingScheme NS_DEPRECATED_MAC(10_0, 10_4);
- (NSMultibyteGlyphPacking) glyphPacking NS_DEPRECATED_MAC(10_0, 10_4);

NS_ASSUME_NONNULL_BEGIN
// The context-sensitive inter-glyph spacing is now performed at the typesetting stage.
- (NSPoint)positionOfGlyph:(NSGlyph)glyph precededByGlyph:(NSGlyph)prevGlyph isNominal:(null_unspecified BOOL *)nominal NS_DEPRECATED_MAC(10_0, 10_4);
- (NSInteger)positionsForCompositeSequence:(null_unspecified NSGlyph *)someGlyphs numberOfGlyphs:(NSInteger)numGlyphs pointArray:(NSPointArray)points NS_DEPRECATED_MAC(10_0, 10_4);
- (NSPoint)positionOfGlyph:(NSGlyph)glyph struckOverGlyph:(NSGlyph)prevGlyph metricsExist:(null_unspecified BOOL *)exist NS_DEPRECATED_MAC(10_0, 10_4);
- (NSPoint)positionOfGlyph:(NSGlyph)glyph struckOverRect:(NSRect)rect metricsExist:(null_unspecified BOOL *)exist NS_DEPRECATED_MAC(10_0, 10_4);
- (NSPoint)positionOfGlyph:(NSGlyph)glyph forCharacter:(unichar)character struckOverRect:(NSRect)rect NS_DEPRECATED_MAC(10_0, 10_4);
- (NSPoint)positionOfGlyph:(NSGlyph)thisGlyph withRelation:(NSGlyphRelation)rel toBaseGlyph:(NSGlyph)baseGlyph totalAdvancement:(NSSizePointer)adv metricsExist:(null_unspecified BOOL *)exist NS_DEPRECATED_MAC(10_0, 10_4);
@end

APPKIT_EXTERN NSString *NSAFMFamilyName         NS_DEPRECATED_MAC(10_0, 10_4);
APPKIT_EXTERN NSString *NSAFMFontName           NS_DEPRECATED_MAC(10_0, 10_4);
APPKIT_EXTERN NSString *NSAFMFormatVersion      NS_DEPRECATED_MAC(10_0, 10_4);
APPKIT_EXTERN NSString *NSAFMFullName           NS_DEPRECATED_MAC(10_0, 10_4);
APPKIT_EXTERN NSString *NSAFMNotice             NS_DEPRECATED_MAC(10_0, 10_4);
APPKIT_EXTERN NSString *NSAFMVersion            NS_DEPRECATED_MAC(10_0, 10_4);
APPKIT_EXTERN NSString *NSAFMWeight             NS_DEPRECATED_MAC(10_0, 10_4);
APPKIT_EXTERN NSString *NSAFMEncodingScheme     NS_DEPRECATED_MAC(10_0, 10_4);
APPKIT_EXTERN NSString *NSAFMCharacterSet       NS_DEPRECATED_MAC(10_0, 10_4);
APPKIT_EXTERN NSString *NSAFMCapHeight          NS_DEPRECATED_MAC(10_0, 10_4);
APPKIT_EXTERN NSString *NSAFMXHeight            NS_DEPRECATED_MAC(10_0, 10_4);
APPKIT_EXTERN NSString *NSAFMAscender           NS_DEPRECATED_MAC(10_0, 10_4);
APPKIT_EXTERN NSString *NSAFMDescender          NS_DEPRECATED_MAC(10_0, 10_4);
APPKIT_EXTERN NSString *NSAFMUnderlinePosition  NS_DEPRECATED_MAC(10_0, 10_4);
APPKIT_EXTERN NSString *NSAFMUnderlineThickness NS_DEPRECATED_MAC(10_0, 10_4);
APPKIT_EXTERN NSString *NSAFMItalicAngle        NS_DEPRECATED_MAC(10_0, 10_4);
APPKIT_EXTERN NSString *NSAFMMappingScheme      NS_DEPRECATED_MAC(10_0, 10_4);
NS_ASSUME_NONNULL_END

#endif /* !__LP64__ */
