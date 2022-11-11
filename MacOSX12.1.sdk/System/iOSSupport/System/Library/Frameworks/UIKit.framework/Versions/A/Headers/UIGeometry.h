#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIGeometry.h>)
//
//  UIGeometry.h
//  UIKit
//
//  Copyright (c) 2005-2018 Apple Inc. All rights reserved.
//


#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

UIKIT_SWIFT_FORWARD_DECLARE(@class NSCoder)
UIKIT_SWIFT_FORWARD_DECLARE(struct CGRect)

#ifdef FOUNDATION_HAS_DIRECTIONAL_GEOMETRY
typedef NSEdgeInsets UIEdgeInsets;
#else
typedef struct __attribute__((objc_boxable)) UIEdgeInsets {
    CGFloat top, left, bottom, right;  // specify amount to inset (positive) for each of the edges. values can be negative to 'outset'
} UIEdgeInsets;
#endif // FOUNDATION_HAS_DIRECTIONAL_GEOMETRY

/* Geometry type declarations marked with `#ifndef FOUNDATION_HAS_DIRECTIONAL_GEOMETRY` are being relocated to Foundation/NSGeometry.h */

#ifndef FOUNDATION_HAS_DIRECTIONAL_GEOMETRY
#if UIKIT_HAS_UIFOUNDATION_SYMBOLS

/* Specifically for use in methods and functions supporting user interface layout direction
 */
typedef struct __attribute__((objc_boxable)) NSDirectionalEdgeInsets {
    CGFloat top, leading, bottom, trailing;  // specify amount to inset (positive) for each of the edges. values can be negative to 'outset'
} NSDirectionalEdgeInsets API_AVAILABLE(ios(11.0),tvos(11.0),watchos(4.0));

#endif // UIKIT_HAS_UIFOUNDATION_SYMBOLS
#endif // FOUNDATION_HAS_DIRECTIONAL_GEOMETRY

typedef struct __attribute__((objc_boxable)) UIOffset {
    CGFloat horizontal, vertical; // specify amount to offset a position, positive for right or down, negative for left or up
} UIOffset;

typedef NS_OPTIONS(NSUInteger, UIRectEdge) {
    UIRectEdgeNone   = 0,
    UIRectEdgeTop    = 1 << 0,
    UIRectEdgeLeft   = 1 << 1,
    UIRectEdgeBottom = 1 << 2,
    UIRectEdgeRight  = 1 << 3,
    UIRectEdgeAll    = UIRectEdgeTop | UIRectEdgeLeft | UIRectEdgeBottom | UIRectEdgeRight
} API_AVAILABLE(ios(7.0));

typedef NS_OPTIONS(NSUInteger, UIRectCorner) {
    UIRectCornerTopLeft     = 1 << 0,
    UIRectCornerTopRight    = 1 << 1,
    UIRectCornerBottomLeft  = 1 << 2,
    UIRectCornerBottomRight = 1 << 3,
    UIRectCornerAllCorners  = ~0UL
};

typedef NS_OPTIONS(NSUInteger, UIAxis) {
    UIAxisNeither    = 0,
    UIAxisHorizontal = 1 << 0,
    UIAxisVertical   = 1 << 1,
    UIAxisBoth       = (UIAxisHorizontal | UIAxisVertical),
} API_AVAILABLE(ios(13.4), tvos(13.4)) API_UNAVAILABLE(watchos);

#ifdef FOUNDATION_HAS_DIRECTIONAL_GEOMETRY

typedef NSDirectionalRectEdge UIDirectionalRectEdge;

enum {
    UIDirectionalRectEdgeNone       = NSDirectionalRectEdgeNone,
    UIDirectionalRectEdgeTop        = NSDirectionalRectEdgeTop,
    UIDirectionalRectEdgeLeading    = NSDirectionalRectEdgeLeading,
    UIDirectionalRectEdgeBottom     = NSDirectionalRectEdgeBottom,
    UIDirectionalRectEdgeTrailing   = NSDirectionalRectEdgeTrailing,
    UIDirectionalRectEdgeAll        = NSDirectionalRectEdgeAll
};

#else

#if UIKIT_HAS_UIFOUNDATION_SYMBOLS

typedef NS_OPTIONS(NSUInteger, NSDirectionalRectEdge) {
    NSDirectionalRectEdgeNone       = 0,
    NSDirectionalRectEdgeTop        = 1 << 0,
    NSDirectionalRectEdgeLeading    = 1 << 1,
    NSDirectionalRectEdgeBottom     = 1 << 2,
    NSDirectionalRectEdgeTrailing   = 1 << 3,
    NSDirectionalRectEdgeAll    = NSDirectionalRectEdgeTop | NSDirectionalRectEdgeLeading | NSDirectionalRectEdgeBottom | NSDirectionalRectEdgeTrailing
} API_AVAILABLE(ios(13.0));


typedef NS_OPTIONS(NSUInteger, UIDirectionalRectEdge) {
    UIDirectionalRectEdgeNone       = 0,
    UIDirectionalRectEdgeTop        = 1 << 0,
    UIDirectionalRectEdgeLeading    = 1 << 1,
    UIDirectionalRectEdgeBottom     = 1 << 2,
    UIDirectionalRectEdgeTrailing   = 1 << 3,
    UIDirectionalRectEdgeAll    = UIDirectionalRectEdgeTop | UIDirectionalRectEdgeLeading | UIDirectionalRectEdgeBottom | UIDirectionalRectEdgeTrailing
} API_DEPRECATED_WITH_REPLACEMENT("NSDirectionalRectEdge", ios(13.0, 13.0), watchos(6.0,6.0), tvos(13.0,13.0));

typedef NS_ENUM(NSInteger, NSRectAlignment) {
    NSRectAlignmentNone = 0,
    NSRectAlignmentTop,
    NSRectAlignmentTopLeading,
    NSRectAlignmentLeading,
    NSRectAlignmentBottomLeading,
    NSRectAlignmentBottom,
    NSRectAlignmentBottomTrailing,
    NSRectAlignmentTrailing,
    NSRectAlignmentTopTrailing,
} API_AVAILABLE(ios(13.0));

#endif // UIKIT_HAS_UIFOUNDATION_SYMBOLS
#endif // FOUNDATION_HAS_DIRECTIONAL_GEOMETRY

UIKIT_STATIC_INLINE UIEdgeInsets UIEdgeInsetsMake(CGFloat top, CGFloat left, CGFloat bottom, CGFloat right) {
    UIEdgeInsets insets = {top, left, bottom, right};
    return insets;
}

#ifndef FOUNDATION_HAS_DIRECTIONAL_GEOMETRY
#if UIKIT_HAS_UIFOUNDATION_SYMBOLS
UIKIT_STATIC_INLINE NSDirectionalEdgeInsets NSDirectionalEdgeInsetsMake(CGFloat top, CGFloat leading, CGFloat bottom, CGFloat trailing) API_AVAILABLE(ios(11.0),tvos(11.0),watchos(4.0))
{
    NSDirectionalEdgeInsets insets = {top, leading, bottom, trailing};
    return insets;
}
#endif // UIKIT_HAS_UIFOUNDATION_SYMBOLS
#endif // FOUNDATION_HAS_DIRECTIONAL_GEOMETRY

UIKIT_STATIC_INLINE CGRect UIEdgeInsetsInsetRect(CGRect rect, UIEdgeInsets insets) {
    rect.origin.x    += insets.left;
    rect.origin.y    += insets.top;
    rect.size.width  -= (insets.left + insets.right);
    rect.size.height -= (insets.top  + insets.bottom);
    return rect;
}

UIKIT_STATIC_INLINE UIOffset UIOffsetMake(CGFloat horizontal, CGFloat vertical) {
    UIOffset offset = {horizontal, vertical};
    return offset;
}

UIKIT_STATIC_INLINE BOOL UIEdgeInsetsEqualToEdgeInsets(UIEdgeInsets insets1, UIEdgeInsets insets2) {
    return insets1.left == insets2.left && insets1.top == insets2.top && insets1.right == insets2.right && insets1.bottom == insets2.bottom;
}

#ifndef FOUNDATION_HAS_DIRECTIONAL_GEOMETRY
#if UIKIT_HAS_UIFOUNDATION_SYMBOLS
UIKIT_STATIC_INLINE BOOL NSDirectionalEdgeInsetsEqualToDirectionalEdgeInsets(NSDirectionalEdgeInsets insets1, NSDirectionalEdgeInsets insets2) API_AVAILABLE(ios(11.0),tvos(11.0),watchos(4.0))
{
    return insets1.leading == insets2.leading && insets1.top == insets2.top && insets1.trailing == insets2.trailing && insets1.bottom == insets2.bottom;
}
#endif // UIKIT_HAS_UIFOUNDATION_SYMBOLS
#endif // FOUNDATION_HAS_DIRECTIONAL_GEOMETRY

UIKIT_STATIC_INLINE BOOL UIOffsetEqualToOffset(UIOffset offset1, UIOffset offset2) {
    return offset1.horizontal == offset2.horizontal && offset1.vertical == offset2.vertical;
}

UIKIT_EXTERN const UIEdgeInsets UIEdgeInsetsZero;
#ifndef FOUNDATION_HAS_DIRECTIONAL_GEOMETRY
#if UIKIT_HAS_UIFOUNDATION_SYMBOLS
UIKIT_EXTERN const NSDirectionalEdgeInsets NSDirectionalEdgeInsetsZero API_AVAILABLE(ios(11.0),tvos(11.0),watchos(4.0));
#endif // UIKIT_HAS_UIFOUNDATION_SYMBOLS
#endif // FOUNDATION_HAS_DIRECTIONAL_GEOMETRY
UIKIT_EXTERN const UIOffset UIOffsetZero;

UIKIT_EXTERN NSString *NSStringFromCGPoint(CGPoint point);
UIKIT_EXTERN NSString *NSStringFromCGVector(CGVector vector);
UIKIT_EXTERN NSString *NSStringFromCGSize(CGSize size);
UIKIT_EXTERN NSString *NSStringFromCGRect(CGRect rect);
UIKIT_EXTERN NSString *NSStringFromCGAffineTransform(CGAffineTransform transform);
UIKIT_EXTERN NSString *NSStringFromUIEdgeInsets(UIEdgeInsets insets);
#ifndef FOUNDATION_HAS_DIRECTIONAL_GEOMETRY
#if UIKIT_HAS_UIFOUNDATION_SYMBOLS
UIKIT_EXTERN NSString *NSStringFromDirectionalEdgeInsets(NSDirectionalEdgeInsets insets) API_AVAILABLE(ios(11.0),tvos(11.0),watchos(4.0));
#endif // UIKIT_HAS_UIFOUNDATION_SYMBOLS
#endif // FOUNDATION_HAS_DIRECTIONAL_GEOMETRY
UIKIT_EXTERN NSString *NSStringFromUIOffset(UIOffset offset);

UIKIT_EXTERN CGPoint CGPointFromString(NSString *string);
UIKIT_EXTERN CGVector CGVectorFromString(NSString *string);
UIKIT_EXTERN CGSize CGSizeFromString(NSString *string);
UIKIT_EXTERN CGRect CGRectFromString(NSString *string);
UIKIT_EXTERN CGAffineTransform CGAffineTransformFromString(NSString *string);
UIKIT_EXTERN UIEdgeInsets UIEdgeInsetsFromString(NSString *string);
#ifndef FOUNDATION_HAS_DIRECTIONAL_GEOMETRY
#if UIKIT_HAS_UIFOUNDATION_SYMBOLS
UIKIT_EXTERN NSDirectionalEdgeInsets NSDirectionalEdgeInsetsFromString(NSString *string) API_AVAILABLE(ios(11.0),tvos(11.0),watchos(4.0));
#endif // UIKIT_HAS_UIFOUNDATION_SYMBOLS
#endif // FOUNDATION_HAS_DIRECTIONAL_GEOMETRY
UIKIT_EXTERN UIOffset UIOffsetFromString(NSString *string);

@interface NSValue (NSValueUIGeometryExtensions)

+ (NSValue *)valueWithCGPoint:(CGPoint)point;
+ (NSValue *)valueWithCGVector:(CGVector)vector;
+ (NSValue *)valueWithCGSize:(CGSize)size;
+ (NSValue *)valueWithCGRect:(CGRect)rect;
+ (NSValue *)valueWithCGAffineTransform:(CGAffineTransform)transform;
+ (NSValue *)valueWithUIEdgeInsets:(UIEdgeInsets)insets;
#ifndef FOUNDATION_HAS_DIRECTIONAL_GEOMETRY
#if UIKIT_HAS_UIFOUNDATION_SYMBOLS
+ (NSValue *)valueWithDirectionalEdgeInsets:(NSDirectionalEdgeInsets)insets API_AVAILABLE(ios(11.0),tvos(11.0),watchos(4.0));
#endif // UIKIT_HAS_UIFOUNDATION_SYMBOLS
#endif // FOUNDATION_HAS_DIRECTIONAL_GEOMETRY
+ (NSValue *)valueWithUIOffset:(UIOffset)insets API_AVAILABLE(ios(5.0));

@property(nonatomic, readonly) CGPoint CGPointValue;
@property(nonatomic, readonly) CGVector CGVectorValue;
@property(nonatomic, readonly) CGSize CGSizeValue;
@property(nonatomic, readonly) CGRect CGRectValue;
@property(nonatomic, readonly) CGAffineTransform CGAffineTransformValue;
@property(nonatomic, readonly) UIEdgeInsets UIEdgeInsetsValue;
#ifndef FOUNDATION_HAS_DIRECTIONAL_GEOMETRY
#if UIKIT_HAS_UIFOUNDATION_SYMBOLS
@property(nonatomic, readonly) NSDirectionalEdgeInsets directionalEdgeInsetsValue API_AVAILABLE(ios(11.0),tvos(11.0),watchos(4.0));
#endif // UIKIT_HAS_UIFOUNDATION_SYMBOLS
#endif // FOUNDATION_HAS_DIRECTIONAL_GEOMETRY
@property(nonatomic, readonly) UIOffset UIOffsetValue API_AVAILABLE(ios(5.0));

@end
    
@interface NSCoder (UIGeometryKeyedCoding)

- (void)encodeCGPoint:(CGPoint)point forKey:(NSString *)key;
- (void)encodeCGVector:(CGVector)vector forKey:(NSString *)key;
- (void)encodeCGSize:(CGSize)size forKey:(NSString *)key;
- (void)encodeCGRect:(CGRect)rect forKey:(NSString *)key;
- (void)encodeCGAffineTransform:(CGAffineTransform)transform forKey:(NSString *)key;
- (void)encodeUIEdgeInsets:(UIEdgeInsets)insets forKey:(NSString *)key;
#ifndef FOUNDATION_HAS_DIRECTIONAL_GEOMETRY
#if UIKIT_HAS_UIFOUNDATION_SYMBOLS
- (void)encodeDirectionalEdgeInsets:(NSDirectionalEdgeInsets)insets forKey:(NSString *)key API_AVAILABLE(ios(11.0),tvos(11.0),watchos(4.0));
#endif // UIKIT_HAS_UIFOUNDATION_SYMBOLS
#endif // FOUNDATION_HAS_DIRECTIONAL_GEOMETRY
- (void)encodeUIOffset:(UIOffset)offset forKey:(NSString *)key API_AVAILABLE(ios(5.0));

- (CGPoint)decodeCGPointForKey:(NSString *)key;
- (CGVector)decodeCGVectorForKey:(NSString *)key;
- (CGSize)decodeCGSizeForKey:(NSString *)key;
- (CGRect)decodeCGRectForKey:(NSString *)key;
- (CGAffineTransform)decodeCGAffineTransformForKey:(NSString *)key;
- (UIEdgeInsets)decodeUIEdgeInsetsForKey:(NSString *)key;
#ifndef FOUNDATION_HAS_DIRECTIONAL_GEOMETRY
#if UIKIT_HAS_UIFOUNDATION_SYMBOLS
- (NSDirectionalEdgeInsets)decodeDirectionalEdgeInsetsForKey:(NSString *)key API_AVAILABLE(ios(11.0),tvos(11.0),watchos(4.0));
#endif // UIKIT_HAS_UIFOUNDATION_SYMBOLS
#endif // FOUNDATION_HAS_DIRECTIONAL_GEOMETRY
- (UIOffset)decodeUIOffsetForKey:(NSString *)key API_AVAILABLE(ios(5.0));

@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UIGeometry.h>
#endif
