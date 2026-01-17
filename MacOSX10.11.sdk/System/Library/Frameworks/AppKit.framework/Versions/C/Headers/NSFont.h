/*
	NSFont.h
	Application Kit
	Copyright (c) 1994-2015, Apple Inc.
	All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSString.h> // for NSStringEncoding
#import <AppKit/AppKitDefines.h>
#import <AppKit/NSCell.h> // for NSControlSize

NS_ASSUME_NONNULL_BEGIN

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
APPKIT_EXTERN const CGFloat * NSFontIdentityMatrix;

/********* Glyph packing *********/
/* Other glyph packing modes are deprecated.
*/
typedef NS_ENUM(NSUInteger, NSMultibyteGlyphPacking) {
    NSNativeShortGlyphPacking = 5
};

/********* Screen Font Rendering Mode *********/
typedef NS_ENUM(NSUInteger, NSFontRenderingMode) {
    NSFontDefaultRenderingMode = 0, // Determines the actual mode based on the user preference settings
    NSFontAntialiasedRenderingMode = 1, // Antialiased, floating-point advancements rendering mode (synonym to printerFont)
    NSFontIntegerAdvancementsRenderingMode = 2, // integer advancements rendering mode
    NSFontAntialiasedIntegerAdvancementsRenderingMode = 3 // Antialiased, integer advancements rendering mode
};

NS_AUTOMATED_REFCOUNT_WEAK_UNAVAILABLE
@interface NSFont : NSObject <NSCopying, NSSecureCoding> {
    /* All instance variables are private */
    NSString *_name;
    CGFloat _size;
    NSInteger _retainCount;
    struct __fFlags {
        unsigned int _isScreenFont:1;
        unsigned int _systemFontType:8;
        unsigned int _reserved1:4;
        unsigned int _matrixIsIdentity:1;
        unsigned int _renderingMode:3;
        unsigned int _inInstanceCache:1;
        unsigned int _reserved2:14;
    } _fFlags;
    id _private;
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
+ (void)setUserFont:(nullable NSFont *)aFont;	// set preference for Application font.
+ (void)setUserFixedPitchFont:(nullable NSFont *)aFont; // set preference for fixed-pitch.

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
+ (NSFont *)systemFontOfSize:(CGFloat)fontSize weight:(CGFloat)weight NS_AVAILABLE_MAC(10_11);
+ (NSFont *)monospacedDigitSystemFontOfSize:(CGFloat)fontSize weight:(CGFloat)weight NS_AVAILABLE_MAC(10_11);

/* UI font size settings
*/
+ (CGFloat)systemFontSize; // size of the standard System font.
+ (CGFloat)smallSystemFontSize; // size of standard small System font.
+ (CGFloat)labelFontSize;	// size of the standard Label Font.

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
- (NSGlyph)glyphWithName:(NSString *)aName;
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
- (NSRect)boundingRectForGlyph:(NSGlyph)aGlyph;
- (NSSize)advancementForGlyph:(NSGlyph)ag;

// bulk query
- (void)getBoundingRects:(NSRectArray)bounds forGlyphs:(const NSGlyph *)glyphs count:(NSUInteger)glyphCount;
- (void)getAdvancements:(NSSizeArray)advancements forGlyphs:(const NSGlyph *)glyphs count:(NSUInteger)glyphCount;
- (void)getAdvancements:(NSSizeArray)advancements forPackedGlyphs:(const void *)packedGlyphs length:(NSUInteger)length; // only supports NSNativeShortGlyphPacking

/********* NSGraphicsContext-related *********/
- (void)set;
- (void)setInContext:(NSGraphicsContext *)graphicsContext;

/********* Rendering mode *********/
@property (readonly, copy) NSFont *printerFont;
@property (readonly, copy) NSFont *screenFont; // Same as screenFontWithRenderingMode:NSFontDefaultRenderingMode
- (NSFont *)screenFontWithRenderingMode:(NSFontRenderingMode)renderingMode;
@property (readonly) NSFontRenderingMode renderingMode;

/********* Vertical mode *********/
/* Returns a vertical version of the receiver if such a configuration is supported.  Returns the receiver if no vertical variant available.  A vertical font applies appropriate rotation to the text matrix in -setInContext:, returns vertical metrics, and enables the vertical glyph substitution feature by default. */
@property (readonly, copy) NSFont *verticalFont NS_AVAILABLE_MAC(10_7);

/* Returns YES if a vertical variant */
@property (getter=isVertical, readonly) BOOL vertical NS_AVAILABLE_MAC(10_7);
@end

/********* Glyph packing *********/
/* Take a buffer of NSGlyphs, of some given length, and a packing type, and a place to put some packed glyphs.  Pack up the NSGlyphs according to the NSMultibyteGlyphPacking, null-terminate the bytes, and then put them into the output buffer.  Return the count of bytes output, including the null-terminator.  The output buffer (packedGlyphs) provided by the caller is guaranteed to be at least "count*4+1" bytes long. This function only supports NSNativeShortGlyphPacking on Mac OS X.
*/
APPKIT_EXTERN NSInteger NSConvertGlyphsToPackedGlyphs(NSGlyph * __nonnull glBuf, NSInteger count, NSMultibyteGlyphPacking packing, char * __nonnull packedGlyphs);

/********* Notifications *********/
/* This notification is posted when the antialias threshold is changed by the user.
*/
APPKIT_EXTERN NSString * NSAntialiasThresholdChangedNotification;

/* This notification is posted when the available font set is modified as a result of activation/deactivation.
*/
APPKIT_EXTERN NSString * NSFontSetChangedNotification;

NS_ASSUME_NONNULL_END


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
- (BOOL)glyphIsEncoded:(NSGlyph)aGlyph NS_DEPRECATED_MAC(10_0, 10_4); // Can be deduced by aGlyph < [NSFont numberOfGlyphs] since only NSNativeShortGlyphPacking is supported.
- (CGFloat)defaultLineHeightForFont NS_DEPRECATED_MAC(10_0, 10_4); // Use -[NSLayoutManager defaultLineHeightForFont:] instead.
+ (null_unspecified NSArray *)preferredFontNames NS_DEPRECATED_MAC(10_0, 10_4); // NSFontCascadeListAttribute offers more powerful font substitution management
+ (void)setPreferredFontNames:(null_unspecified NSArray *)fontNameArray NS_DEPRECATED_MAC(10_0, 10_4);
- (null_unspecified NSString *)encodingScheme NS_DEPRECATED_MAC(10_0, 10_4);
- (NSMultibyteGlyphPacking) glyphPacking NS_DEPRECATED_MAC(10_0, 10_4);

NS_ASSUME_NONNULL_BEGIN
// The context-sensitive inter-glyph spacing is now performed at the typesetting stage.
- (NSPoint)positionOfGlyph:(NSGlyph)curGlyph precededByGlyph:(NSGlyph)prevGlyph isNominal:(null_unspecified BOOL *)nominal NS_DEPRECATED_MAC(10_0, 10_4);
- (NSInteger)positionsForCompositeSequence:(null_unspecified NSGlyph *)someGlyphs numberOfGlyphs:(NSInteger)numGlyphs pointArray:(NSPointArray)points NS_DEPRECATED_MAC(10_0, 10_4);
- (NSPoint)positionOfGlyph:(NSGlyph)curGlyph struckOverGlyph:(NSGlyph)prevGlyph metricsExist:(null_unspecified BOOL *)exist NS_DEPRECATED_MAC(10_0, 10_4);
- (NSPoint)positionOfGlyph:(NSGlyph)aGlyph struckOverRect:(NSRect)aRect metricsExist:(null_unspecified BOOL *)exist NS_DEPRECATED_MAC(10_0, 10_4);
- (NSPoint)positionOfGlyph:(NSGlyph)aGlyph forCharacter:(unichar)aChar struckOverRect:(NSRect)aRect NS_DEPRECATED_MAC(10_0, 10_4);
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
