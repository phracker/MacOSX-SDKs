/*	NSGeometry.h
	Copyright (c) 1994-2005, Apple, Inc. All rights reserved.
*/

#import <Foundation/NSValue.h>
#import <Foundation/NSCoder.h>

@class NSString;

typedef struct _NSPoint {
    float x;
    float y;
} NSPoint;

typedef NSPoint *NSPointPointer;
typedef NSPoint *NSPointArray;

typedef struct _NSSize {
    float width;		/* should never be negative */
    float height;		/* should never be negative */
} NSSize;

typedef NSSize *NSSizePointer;
typedef NSSize *NSSizeArray;

typedef struct _NSRect {
    NSPoint origin;
    NSSize size;
} NSRect;

typedef NSRect *NSRectPointer;
typedef NSRect *NSRectArray;

typedef enum _NSRectEdge {
    NSMinXEdge = 0,
    NSMinYEdge = 1,
    NSMaxXEdge = 2,
    NSMaxYEdge = 3	
} NSRectEdge;

FOUNDATION_EXPORT const NSPoint NSZeroPoint;
FOUNDATION_EXPORT const NSSize NSZeroSize;
FOUNDATION_EXPORT const NSRect NSZeroRect;

FOUNDATION_STATIC_INLINE NSPoint NSMakePoint(float x, float y) {
    NSPoint p;
    p.x = x;
    p.y = y;
    return p;
}

FOUNDATION_STATIC_INLINE NSSize NSMakeSize(float w, float h) {
    NSSize s;
    s.width = w;
    s.height = h;
    return s;
}

FOUNDATION_STATIC_INLINE NSRect NSMakeRect(float x, float y, float w, float h) {
    NSRect r;
    r.origin.x = x;
    r.origin.y = y;
    r.size.width = w;
    r.size.height = h;
    return r;
}

FOUNDATION_STATIC_INLINE float NSMaxX(NSRect aRect) {
    return (aRect.origin.x + aRect.size.width);
}

FOUNDATION_STATIC_INLINE float NSMaxY(NSRect aRect) {
    return (aRect.origin.y + aRect.size.height);
}

FOUNDATION_STATIC_INLINE float NSMidX(NSRect aRect) {
    return (aRect.origin.x + aRect.size.width / 2.0);
}

FOUNDATION_STATIC_INLINE float NSMidY(NSRect aRect) {
    return (aRect.origin.y + aRect.size.height / 2.0);
}

FOUNDATION_STATIC_INLINE float NSMinX(NSRect aRect) {
    return (aRect.origin.x);
}

FOUNDATION_STATIC_INLINE float NSMinY(NSRect aRect) {
    return (aRect.origin.y);
}

FOUNDATION_STATIC_INLINE float NSWidth(NSRect aRect) {
    return (aRect.size.width);
}

FOUNDATION_STATIC_INLINE float NSHeight(NSRect aRect) {
    return (aRect.size.height);
}

FOUNDATION_EXPORT BOOL NSEqualPoints(NSPoint aPoint, NSPoint bPoint);
FOUNDATION_EXPORT BOOL NSEqualSizes(NSSize aSize, NSSize bSize);
FOUNDATION_EXPORT BOOL NSEqualRects(NSRect aRect, NSRect bRect);
FOUNDATION_EXPORT BOOL NSIsEmptyRect(NSRect aRect);

FOUNDATION_EXPORT NSRect NSInsetRect(NSRect aRect, float dX, float dY);
FOUNDATION_EXPORT NSRect NSIntegralRect(NSRect aRect);
FOUNDATION_EXPORT NSRect NSUnionRect(NSRect aRect, NSRect bRect);
FOUNDATION_EXPORT NSRect NSIntersectionRect(NSRect aRect, NSRect bRect);
FOUNDATION_EXPORT NSRect NSOffsetRect(NSRect aRect, float dX, float dY);
FOUNDATION_EXPORT void NSDivideRect(NSRect inRect, NSRect *slice, NSRect *rem, float amount, NSRectEdge edge);
FOUNDATION_EXPORT BOOL NSPointInRect(NSPoint aPoint, NSRect aRect);
FOUNDATION_EXPORT BOOL NSMouseInRect(NSPoint aPoint, NSRect aRect, BOOL flipped);
FOUNDATION_EXPORT BOOL NSContainsRect(NSRect aRect, NSRect bRect);
FOUNDATION_EXPORT BOOL NSIntersectsRect(NSRect aRect, NSRect bRect);

FOUNDATION_EXPORT NSString *NSStringFromPoint(NSPoint aPoint);
FOUNDATION_EXPORT NSString *NSStringFromSize(NSSize aSize);
FOUNDATION_EXPORT NSString *NSStringFromRect(NSRect aRect);
FOUNDATION_EXPORT NSPoint NSPointFromString(NSString *aString);
FOUNDATION_EXPORT NSSize NSSizeFromString(NSString *aString);
FOUNDATION_EXPORT NSRect NSRectFromString(NSString *aString);

@interface NSValue (NSValueGeometryExtensions)

+ (NSValue *)valueWithPoint:(NSPoint)point;
+ (NSValue *)valueWithSize:(NSSize)size;
+ (NSValue *)valueWithRect:(NSRect)rect;

- (NSPoint)pointValue;
- (NSSize)sizeValue;
- (NSRect)rectValue;

@end

@interface NSCoder (NSGeometryCoding)

- (void)encodePoint:(NSPoint)point;
- (NSPoint)decodePoint;

- (void)encodeSize:(NSSize)size;
- (NSSize)decodeSize;

- (void)encodeRect:(NSRect)rect;
- (NSRect)decodeRect;

@end
