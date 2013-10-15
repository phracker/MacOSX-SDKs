/*
        NSBezierPath.h
        Application Kit
        Copyright (c) 1997-2005, Apple Computer, Inc.
        All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSGeometry.h>
#import <AppKit/NSFont.h>

@class NSAffineTransform;

typedef enum {
    NSButtLineCapStyle = 0,
    NSRoundLineCapStyle = 1,
    NSSquareLineCapStyle = 2
} NSLineCapStyle;

typedef enum {
    NSMiterLineJoinStyle = 0,
    NSRoundLineJoinStyle = 1,
    NSBevelLineJoinStyle = 2
} NSLineJoinStyle;

typedef enum {
    NSNonZeroWindingRule = 0,
    NSEvenOddWindingRule = 1
} NSWindingRule;

typedef enum {
    NSMoveToBezierPathElement,
    NSLineToBezierPathElement,
    NSCurveToBezierPathElement,
    NSClosePathBezierPathElement
} NSBezierPathElement;

@interface NSBezierPath : NSObject <NSCopying, NSCoding>
{
    @private
    int _state;
    int _segmentCount;
    int _segmentMax;
    struct PATHSEGMENT *_head;
    int _lastSubpathIndex;
    int _elementCount;
    float _lineWidth;
    NSRect _bounds;
    NSRect _controlPointBounds;
    unsigned char _flags;
    float _miterLimit;
    float _flatness;
    float *_dashedLinePattern;
    unsigned int _dashedLineCount;
    float _dashedLinePhase;
}

// Creating common paths.

+ (NSBezierPath *)bezierPath;
+ (NSBezierPath *)bezierPathWithRect:(NSRect)rect;
+ (NSBezierPath *)bezierPathWithOvalInRect:(NSRect)rect;

// Immediate mode drawing of common paths.

+ (void)fillRect:(NSRect)rect;
+ (void)strokeRect:(NSRect)rect;
+ (void)clipRect:(NSRect)rect;
+ (void)strokeLineFromPoint:(NSPoint)point1 toPoint:(NSPoint)point2;
+ (void)drawPackedGlyphs:(const char *)packedGlyphs atPoint:(NSPoint)point;

// Default path rendering parameters.

+ (void)setDefaultMiterLimit:(float)limit;
+ (float)defaultMiterLimit;
+ (void)setDefaultFlatness:(float)flatness;
+ (float)defaultFlatness;

+ (void)setDefaultWindingRule:(NSWindingRule)windingRule;
+ (NSWindingRule)defaultWindingRule;
+ (void)setDefaultLineCapStyle:(NSLineCapStyle)lineCapStyle;
+ (NSLineCapStyle)defaultLineCapStyle;
+ (void)setDefaultLineJoinStyle:(NSLineJoinStyle)lineJoinStyle;
+ (NSLineJoinStyle)defaultLineJoinStyle;
+ (void)setDefaultLineWidth:(float)lineWidth;
+ (float)defaultLineWidth;

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

- (float)lineWidth;
- (void)setLineWidth:(float)lineWidth;
- (NSLineCapStyle)lineCapStyle;
- (void)setLineCapStyle:(NSLineCapStyle)lineCapStyle;
- (NSLineJoinStyle)lineJoinStyle;
- (void)setLineJoinStyle:(NSLineJoinStyle)lineJoinStyle;
- (NSWindingRule)windingRule;
- (void)setWindingRule:(NSWindingRule)windingRule;
- (float)miterLimit;
- (void)setMiterLimit:(float)miterLimit;
- (float)flatness;
- (void)setFlatness:(float)flatness;
- (void)getLineDash:(float *)pattern count:(int *)count phase:(float *)phase;
- (void)setLineDash:(const float *)pattern count:(int)count phase:(float)phase;

// Path operations.

- (void)stroke;
- (void)fill;
- (void)addClip;
- (void)setClip;

// Path modifications.

- (NSBezierPath *)bezierPathByFlatteningPath;
- (NSBezierPath *)bezierPathByReversingPath;

// Applying transformations.

- (void)transformUsingAffineTransform:(NSAffineTransform *)transform;

// Path info

- (BOOL)isEmpty;
- (NSPoint)currentPoint;
- (NSRect)controlPointBounds;
- (NSRect)bounds;

// Elements.

- (int)elementCount;

// `points' should contain space for at least three points.  `points'
// may be NULL.  In the case of NSCurveToBezierPathElement, the order
// of the points is controlPoint1 (points[0]), controlPoint2 (points[1]),
// endPoint (points[2]).
- (NSBezierPathElement)elementAtIndex:(int)index
		     associatedPoints:(NSPointArray)points;
// As above with points == NULL.
- (NSBezierPathElement)elementAtIndex:(int)index;
- (void)setAssociatedPoints:(NSPointArray)points atIndex:(int)index;

// Appending common paths

- (void)appendBezierPath:(NSBezierPath *)path;
- (void)appendBezierPathWithRect:(NSRect)rect;
- (void)appendBezierPathWithPoints:(NSPointArray)points count:(int)count;
- (void)appendBezierPathWithOvalInRect:(NSRect)rect;
- (void)appendBezierPathWithArcWithCenter:(NSPoint)center radius:(float)radius
			       startAngle:(float)startAngle
				 endAngle:(float)endAngle
				clockwise:(BOOL)clockwise;
// As above with clockwise == NO. */	
- (void)appendBezierPathWithArcWithCenter:(NSPoint)center radius:(float)radius
			       startAngle:(float)startAngle
				 endAngle:(float)endAngle;
- (void)appendBezierPathWithArcFromPoint:(NSPoint)point1
				 toPoint:(NSPoint)point2
				  radius:(float)radius;
- (void)appendBezierPathWithGlyph:(NSGlyph)glyph inFont:(NSFont *)font;
- (void)appendBezierPathWithGlyphs:(NSGlyph *)glyphs count:(int)count
			    inFont:(NSFont *)font;
- (void)appendBezierPathWithPackedGlyphs:(const char *)packedGlyphs;

// Hit detection.
- (BOOL)containsPoint:(NSPoint)point;

// Caching
- (BOOL)cachesBezierPath;
- (void)setCachesBezierPath:(BOOL)flag;

@end
