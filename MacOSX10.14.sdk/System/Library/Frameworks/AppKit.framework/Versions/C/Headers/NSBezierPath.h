/*
        NSBezierPath.h
        Application Kit
        Copyright (c) 1997-2018, Apple Inc.
        All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSGeometry.h>
#import <AppKit/NSFont.h>

NS_ASSUME_NONNULL_BEGIN

@class NSAffineTransform;

typedef NS_ENUM(NSUInteger, NSLineCapStyle) {
    NSLineCapStyleButt = 0,
    NSLineCapStyleRound = 1,
    NSLineCapStyleSquare = 2
};

typedef NS_ENUM(NSUInteger, NSLineJoinStyle) {
    NSLineJoinStyleMiter = 0,
    NSLineJoinStyleRound = 1,
    NSLineJoinStyleBevel = 2
};

typedef NS_ENUM(NSUInteger, NSWindingRule) {
    NSWindingRuleNonZero = 0,
    NSWindingRuleEvenOdd = 1
};

typedef NS_ENUM(NSUInteger, NSBezierPathElement) {
    NSBezierPathElementMoveTo,
    NSBezierPathElementLineTo,
    NSBezierPathElementCurveTo,
    NSBezierPathElementClosePath
};

@interface NSBezierPath : NSObject <NSCopying, NSSecureCoding>
{
    @private
    NSInteger _elementCount APPKIT_IVAR;
    NSInteger _elementMax APPKIT_IVAR;
    struct PATHSEGMENT *_head APPKIT_IVAR;
    NSInteger _lastSubpathIndex APPKIT_IVAR;
    void *_extraSegments APPKIT_IVAR;
    CGFloat _lineWidth APPKIT_IVAR;
    NSRect _controlPointBounds APPKIT_IVAR;
    CGFloat _miterLimit APPKIT_IVAR;
    CGFloat _flatness APPKIT_IVAR;
    CGFloat *_dashedLinePattern APPKIT_IVAR;
    NSUInteger _dashedLineCount APPKIT_IVAR;
    CGFloat _dashedLinePhase APPKIT_IVAR;
    void *_path APPKIT_IVAR;
    NSInteger _extraSegmentCount APPKIT_IVAR;
    NSInteger _extraSegmentMax APPKIT_IVAR;
#if !__LP64__    
    id _private[2] APPKIT_IVAR;
#endif
    struct {
        unsigned int _flags:8;
        unsigned int _pathState:2;

        unsigned int _unused:22;
    } _bpFlags APPKIT_IVAR;
}

// Creating common paths.

+ (NSBezierPath *)bezierPath;
+ (NSBezierPath *)bezierPathWithRect:(NSRect)rect;
+ (NSBezierPath *)bezierPathWithOvalInRect:(NSRect)rect;
+ (NSBezierPath *)bezierPathWithRoundedRect:(NSRect)rect xRadius:(CGFloat)xRadius yRadius:(CGFloat)yRadius NS_AVAILABLE_MAC(10_5);

// Immediate mode drawing of common paths.

+ (void)fillRect:(NSRect)rect;
+ (void)strokeRect:(NSRect)rect;
+ (void)clipRect:(NSRect)rect;
+ (void)strokeLineFromPoint:(NSPoint)point1 toPoint:(NSPoint)point2;
+ (void)drawPackedGlyphs:(const char *)packedGlyphs atPoint:(NSPoint)point;

// Default path rendering parameters.

@property (class) CGFloat defaultMiterLimit;
@property (class) CGFloat defaultFlatness;

@property (class) NSWindingRule defaultWindingRule;
@property (class) NSLineCapStyle defaultLineCapStyle;
@property (class) NSLineJoinStyle defaultLineJoinStyle;
@property (class) CGFloat defaultLineWidth;

// Path construction.

- (void)moveToPoint:(NSPoint)point;
- (void)lineToPoint:(NSPoint)point;
- (void)curveToPoint:(NSPoint)endPoint
       controlPoint1:(NSPoint)controlPoint1
       controlPoint2:(NSPoint)controlPoint2;
- (void)closePath;

- (void)removeAllPoints;

// Relative path construction.

- (void)relativeMoveToPoint:(NSPoint)point;
- (void)relativeLineToPoint:(NSPoint)point;
- (void)relativeCurveToPoint:(NSPoint)endPoint
	       controlPoint1:(NSPoint)controlPoint1
	       controlPoint2:(NSPoint)controlPoint2;

// Path rendering parameters.

@property CGFloat lineWidth;
@property NSLineCapStyle lineCapStyle;
@property NSLineJoinStyle lineJoinStyle;
@property NSWindingRule windingRule;
@property CGFloat miterLimit;
@property CGFloat flatness;
- (void)getLineDash:(nullable CGFloat *)pattern count:(nullable NSInteger *)count phase:(nullable CGFloat *)phase;
- (void)setLineDash:(nullable const CGFloat *)pattern count:(NSInteger)count phase:(CGFloat)phase;

// Path operations.

- (void)stroke;
- (void)fill;
- (void)addClip;
- (void)setClip;

// Path modifications.

@property (readonly, copy) NSBezierPath *bezierPathByFlatteningPath;
@property (readonly, copy) NSBezierPath *bezierPathByReversingPath;

// Applying transformations.

- (void)transformUsingAffineTransform:(NSAffineTransform *)transform;

// Path info

@property (getter=isEmpty, readonly) BOOL empty;
@property (readonly) NSPoint currentPoint;
@property (readonly) NSRect controlPointBounds;
@property (readonly) NSRect bounds;

// Elements.

@property (readonly) NSInteger elementCount;

// `points' should contain space for at least three points.  `points'
// may be NULL.  In the case of NSBezierPathElementCurveTo, the order
// of the points is controlPoint1 (points[0]), controlPoint2 (points[1]),
// endPoint (points[2]).
- (NSBezierPathElement)elementAtIndex:(NSInteger)index
		     associatedPoints:(nullable NSPointArray)points;
// As above with points == NULL.
- (NSBezierPathElement)elementAtIndex:(NSInteger)index;
- (void)setAssociatedPoints:(nullable NSPointArray)points atIndex:(NSInteger)index;

// Appending common paths

- (void)appendBezierPath:(NSBezierPath *)path;
- (void)appendBezierPathWithRect:(NSRect)rect;
- (void)appendBezierPathWithPoints:(NSPointArray)points count:(NSInteger)count;
- (void)appendBezierPathWithOvalInRect:(NSRect)rect;
- (void)appendBezierPathWithArcWithCenter:(NSPoint)center radius:(CGFloat)radius
			       startAngle:(CGFloat)startAngle
				 endAngle:(CGFloat)endAngle
				clockwise:(BOOL)clockwise;
// As above with clockwise == NO. */	
- (void)appendBezierPathWithArcWithCenter:(NSPoint)center radius:(CGFloat)radius
			       startAngle:(CGFloat)startAngle
				 endAngle:(CGFloat)endAngle;
- (void)appendBezierPathWithArcFromPoint:(NSPoint)point1
				 toPoint:(NSPoint)point2
				  radius:(CGFloat)radius;

- (void)appendBezierPathWithCGGlyph:(CGGlyph)glyph inFont:(NSFont *)font NS_AVAILABLE_MAC(10_13);
- (void)appendBezierPathWithCGGlyphs:(const CGGlyph *)glyphs count:(NSInteger)count inFont:(NSFont *)font NS_AVAILABLE_MAC(10_13);

// Appends paths for a rounded rectangle.
- (void)appendBezierPathWithRoundedRect:(NSRect)rect xRadius:(CGFloat)xRadius yRadius:(CGFloat)yRadius NS_AVAILABLE_MAC(10_5);

// Hit detection.
- (BOOL)containsPoint:(NSPoint)point;
@end

@interface NSBezierPath (NSBezierPathDeprecated)
- (BOOL)cachesBezierPath NS_DEPRECATED_MAC(10_0, 10_0);
- (void)setCachesBezierPath:(BOOL)flag NS_DEPRECATED_MAC(10_0, 10_0);

// The following NSGlyph-related methods are deprecated. Use corresponding CGGlyph-based methods instead
- (void)appendBezierPathWithGlyph:(NSGlyph)glyph inFont:(NSFont *)font NS_DEPRECATED_MAC(10_0, 10_14, "Use -appendBezierPathWithCGGlyph:inFont: instead");
- (void)appendBezierPathWithGlyphs:(NSGlyph *)glyphs count:(NSInteger)count inFont:(NSFont *)font NS_DEPRECATED_MAC(10_0, 10_14, "Use -appendBezierPathWithCGGlyphs:count:inFont: instead");
- (void)appendBezierPathWithPackedGlyphs:(const char *)packedGlyphs NS_DEPRECATED_MAC(10_0, 10_14, "Use -appendBezierPathWithCGGlyphs:count:inFont: instead");
@end

NS_ASSUME_NONNULL_END

/* Deprecated legacy line cap style constants. Prefer to use NSLineCapStyle values instead.
*/
static const NSLineCapStyle NSButtLineCapStyle NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSLineCapStyleButt", 10_0, API_TO_BE_DEPRECATED) = NSLineCapStyleButt;
static const NSLineCapStyle NSRoundLineCapStyle NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSLineCapStyleRound", 10_0, API_TO_BE_DEPRECATED) = NSLineCapStyleRound;
static const NSLineCapStyle NSSquareLineCapStyle NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSLineCapStyleSquare", 10_0, API_TO_BE_DEPRECATED) = NSLineCapStyleSquare;

/* Deprecated legacy line join style constants. Prefer to use NSLineJoinStyle values instead.
*/
static const NSLineJoinStyle NSMiterLineJoinStyle NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSLineJoinStyleMiter", 10_0, API_TO_BE_DEPRECATED) = NSLineJoinStyleMiter;
static const NSLineJoinStyle NSRoundLineJoinStyle NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSLineJoinStyleRound", 10_0, API_TO_BE_DEPRECATED) = NSLineJoinStyleRound;
static const NSLineJoinStyle NSBevelLineJoinStyle NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSLineJoinStyleBevel", 10_0, API_TO_BE_DEPRECATED) = NSLineJoinStyleBevel;

/* Deprecated legacy winding rule constants. Prefer to use NSWindingRule values instead.
*/
static const NSWindingRule NSNonZeroWindingRule NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSWindingRuleNonZero", 10_0, API_TO_BE_DEPRECATED) = NSWindingRuleNonZero;
static const NSWindingRule NSEvenOddWindingRule NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSWindingRuleEvenOdd", 10_0, API_TO_BE_DEPRECATED) = NSWindingRuleEvenOdd;

/* Deprecated legacy Bezier path element constants. Prefer to use NSBezierPathElement values instead.
*/
static const NSBezierPathElement NSMoveToBezierPathElement NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSBezierPathElementMoveTo", 10_0, API_TO_BE_DEPRECATED) = NSBezierPathElementMoveTo;
static const NSBezierPathElement NSLineToBezierPathElement NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSBezierPathElementLineTo", 10_0, API_TO_BE_DEPRECATED) = NSBezierPathElementLineTo;
static const NSBezierPathElement NSCurveToBezierPathElement NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSBezierPathElementCurveTo", 10_0, API_TO_BE_DEPRECATED) = NSBezierPathElementCurveTo;
static const NSBezierPathElement NSClosePathBezierPathElement NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSBezierPathElementClosePath", 10_0, API_TO_BE_DEPRECATED) = NSBezierPathElementClosePath;
