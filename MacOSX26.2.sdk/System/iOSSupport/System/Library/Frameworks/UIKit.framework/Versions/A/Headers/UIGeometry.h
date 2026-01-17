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
#import <UIUtilities/UIGeometry.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

UIKIT_SWIFT_FORWARD_DECLARE(@class NSCoder)
UIKIT_SWIFT_FORWARD_DECLARE(struct CGRect)

#ifdef FOUNDATION_HAS_DIRECTIONAL_GEOMETRY
typedef NSEdgeInsets UIEdgeInsets;
#else
typedef struct __attribute__((objc_boxable)) NS_SWIFT_SENDABLE API_AVAILABLE(watchos(2.0)) UIEdgeInsets {
    CGFloat top, left, bottom, right;  // specify amount to inset (positive) for each of the edges. values can be negative to 'outset'
} UIEdgeInsets;
#endif // FOUNDATION_HAS_DIRECTIONAL_GEOMETRY

/* Geometry type declarations marked with `#ifndef FOUNDATION_HAS_DIRECTIONAL_GEOMETRY` are being relocated to Foundation/NSGeometry.h */

#ifndef FOUNDATION_HAS_DIRECTIONAL_GEOMETRY
#if UIKIT_HAS_UIFOUNDATION_SYMBOLS

/* Specifically for use in methods and functions supporting user interface layout direction
 */
typedef struct __attribute__((objc_boxable)) NS_SWIFT_SENDABLE API_AVAILABLE(watchos(4.0)) NSDirectionalEdgeInsets {
    CGFloat top, leading, bottom, trailing;  // specify amount to inset (positive) for each of the edges. values can be negative to 'outset'
} NSDirectionalEdgeInsets API_AVAILABLE(ios(11.0),tvos(11.0),watchos(4.0));

#endif // UIKIT_HAS_UIFOUNDATION_SYMBOLS
#endif // FOUNDATION_HAS_DIRECTIONAL_GEOMETRY

typedef struct __attribute__((objc_boxable)) NS_SWIFT_SENDABLE API_AVAILABLE(watchos(2.0)) UIOffset {
    CGFloat horizontal, vertical; // specify amount to offset a position, positive for right or down, negative for left or up
} UIOffset;

typedef NS_OPTIONS(NSUInteger, UIRectCorner) {
    UIRectCornerTopLeft     = 1 << 0,
    UIRectCornerTopRight    = 1 << 1,
    UIRectCornerBottomLeft  = 1 << 2,
    UIRectCornerBottomRight = 1 << 3,
    UIRectCornerAllCorners  = ~0UL
} API_AVAILABLE(watchos(2.0));

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
} API_AVAILABLE(ios(13.0), watchos(6.0));


typedef NS_OPTIONS(NSUInteger, UIDirectionalRectEdge) {
    UIDirectionalRectEdgeNone       = 0,
    UIDirectionalRectEdgeTop        = 1 << 0,
    UIDirectionalRectEdgeLeading    = 1 << 1,
    UIDirectionalRectEdgeBottom     = 1 << 2,
    UIDirectionalRectEdgeTrailing   = 1 << 3,
    UIDirectionalRectEdgeAll    = UIDirectionalRectEdgeTop | UIDirectionalRectEdgeLeading | UIDirectionalRectEdgeBottom | UIDirectionalRectEdgeTrailing
} API_DEPRECATED_WITH_REPLACEMENT("NSDirectionalRectEdge", ios(13.0, 13.0), watchos(6.0,6.0), tvos(13.0,13.0)) API_UNAVAILABLE(visionos);

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
} API_AVAILABLE(ios(13.0), watchos(6.0));

#endif // UIKIT_HAS_UIFOUNDATION_SYMBOLS
#endif // FOUNDATION_HAS_DIRECTIONAL_GEOMETRY

UIKIT_STATIC_INLINE UIEdgeInsets UIEdgeInsetsMake(CGFloat top, CGFloat left, CGFloat bottom, CGFloat right) API_AVAILABLE(watchos(2.0)) {
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

UIKIT_STATIC_INLINE CGRect UIEdgeInsetsInsetRect(CGRect rect, UIEdgeInsets insets) API_AVAILABLE(watchos(2.0)) {
    rect.origin.x    += insets.left;
    rect.origin.y    += insets.top;
    rect.size.width  -= (insets.left + insets.right);
    rect.size.height -= (insets.top  + insets.bottom);
    return rect;
}

UIKIT_STATIC_INLINE UIOffset UIOffsetMake(CGFloat horizontal, CGFloat vertical) API_AVAILABLE(watchos(2.0)) {
    UIOffset offset = {horizontal, vertical};
    return offset;
}

UIKIT_STATIC_INLINE BOOL UIEdgeInsetsEqualToEdgeInsets(UIEdgeInsets insets1, UIEdgeInsets insets2) API_AVAILABLE(watchos(2.0)) {
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

UIKIT_STATIC_INLINE BOOL UIOffsetEqualToOffset(UIOffset offset1, UIOffset offset2) API_AVAILABLE(watchos(2.0)) {
    return offset1.horizontal == offset2.horizontal && offset1.vertical == offset2.vertical;
}

UIKIT_EXTERN const UIEdgeInsets UIEdgeInsetsZero API_AVAILABLE(watchos(2.0));
#ifndef FOUNDATION_HAS_DIRECTIONAL_GEOMETRY
#if UIKIT_HAS_UIFOUNDATION_SYMBOLS
UIKIT_EXTERN const NSDirectionalEdgeInsets NSDirectionalEdgeInsetsZero API_AVAILABLE(ios(11.0),tvos(11.0),watchos(4.0));
#endif // UIKIT_HAS_UIFOUNDATION_SYMBOLS
#endif // FOUNDATION_HAS_DIRECTIONAL_GEOMETRY
UIKIT_EXTERN const UIOffset UIOffsetZero API_AVAILABLE(watchos(2.0));

UIKIT_EXTERN NSString *NSStringFromCGPoint(CGPoint point) API_AVAILABLE(watchos(2.0));
UIKIT_EXTERN NSString *NSStringFromCGVector(CGVector vector) API_AVAILABLE(watchos(2.0));
UIKIT_EXTERN NSString *NSStringFromCGSize(CGSize size) API_AVAILABLE(watchos(2.0));
UIKIT_EXTERN NSString *NSStringFromCGRect(CGRect rect) API_AVAILABLE(watchos(2.0));
UIKIT_EXTERN NSString *NSStringFromCGAffineTransform(CGAffineTransform transform) API_AVAILABLE(watchos(2.0));
UIKIT_EXTERN NSString *NSStringFromUIEdgeInsets(UIEdgeInsets insets) API_AVAILABLE(watchos(2.0));
#ifndef FOUNDATION_HAS_DIRECTIONAL_GEOMETRY
#if UIKIT_HAS_UIFOUNDATION_SYMBOLS
UIKIT_EXTERN NSString *NSStringFromDirectionalEdgeInsets(NSDirectionalEdgeInsets insets) API_AVAILABLE(ios(11.0),tvos(11.0),watchos(4.0));
#endif // UIKIT_HAS_UIFOUNDATION_SYMBOLS
#endif // FOUNDATION_HAS_DIRECTIONAL_GEOMETRY
UIKIT_EXTERN NSString *NSStringFromUIOffset(UIOffset offset) API_AVAILABLE(watchos(2.0));

UIKIT_EXTERN CGPoint CGPointFromString(NSString *string) API_AVAILABLE(watchos(2.0));
UIKIT_EXTERN CGVector CGVectorFromString(NSString *string) API_AVAILABLE(watchos(2.0));
UIKIT_EXTERN CGSize CGSizeFromString(NSString *string) API_AVAILABLE(watchos(2.0));
UIKIT_EXTERN CGRect CGRectFromString(NSString *string) API_AVAILABLE(watchos(2.0));
UIKIT_EXTERN CGAffineTransform CGAffineTransformFromString(NSString *string) API_AVAILABLE(watchos(2.0));
UIKIT_EXTERN UIEdgeInsets UIEdgeInsetsFromString(NSString *string) API_AVAILABLE(watchos(2.0));
#ifndef FOUNDATION_HAS_DIRECTIONAL_GEOMETRY
#if UIKIT_HAS_UIFOUNDATION_SYMBOLS
UIKIT_EXTERN NSDirectionalEdgeInsets NSDirectionalEdgeInsetsFromString(NSString *string) API_AVAILABLE(ios(11.0),tvos(11.0),watchos(4.0));
#endif // UIKIT_HAS_UIFOUNDATION_SYMBOLS
#endif // FOUNDATION_HAS_DIRECTIONAL_GEOMETRY
UIKIT_EXTERN UIOffset UIOffsetFromString(NSString *string) API_AVAILABLE(watchos(2.0));

@interface NSValue (NSValueUIGeometryExtensions)

+ (NSValue *)valueWithCGPoint:(CGPoint)point API_AVAILABLE(watchos(2.0));
+ (NSValue *)valueWithCGVector:(CGVector)vector API_AVAILABLE(watchos(2.0));
+ (NSValue *)valueWithCGSize:(CGSize)size API_AVAILABLE(watchos(2.0));
+ (NSValue *)valueWithCGRect:(CGRect)rect API_AVAILABLE(watchos(2.0));
+ (NSValue *)valueWithCGAffineTransform:(CGAffineTransform)transform API_AVAILABLE(watchos(2.0));
+ (NSValue *)valueWithUIEdgeInsets:(UIEdgeInsets)insets API_AVAILABLE(watchos(2.0));
#ifndef FOUNDATION_HAS_DIRECTIONAL_GEOMETRY
#if UIKIT_HAS_UIFOUNDATION_SYMBOLS
+ (NSValue *)valueWithDirectionalEdgeInsets:(NSDirectionalEdgeInsets)insets API_AVAILABLE(ios(11.0),tvos(11.0),watchos(4.0));
#endif // UIKIT_HAS_UIFOUNDATION_SYMBOLS
#endif // FOUNDATION_HAS_DIRECTIONAL_GEOMETRY
+ (NSValue *)valueWithUIOffset:(UIOffset)insets API_AVAILABLE(ios(5.0), watchos(2.0));

@property(nonatomic, readonly) CGPoint CGPointValue API_AVAILABLE(watchos(2.0));
@property(nonatomic, readonly) CGVector CGVectorValue API_AVAILABLE(watchos(2.0));
@property(nonatomic, readonly) CGSize CGSizeValue API_AVAILABLE(watchos(2.0));
@property(nonatomic, readonly) CGRect CGRectValue API_AVAILABLE(watchos(2.0));
@property(nonatomic, readonly) CGAffineTransform CGAffineTransformValue API_AVAILABLE(watchos(2.0));
@property(nonatomic, readonly) UIEdgeInsets UIEdgeInsetsValue API_AVAILABLE(watchos(2.0));
#ifndef FOUNDATION_HAS_DIRECTIONAL_GEOMETRY
#if UIKIT_HAS_UIFOUNDATION_SYMBOLS
@property(nonatomic, readonly) NSDirectionalEdgeInsets directionalEdgeInsetsValue API_AVAILABLE(ios(11.0),tvos(11.0),watchos(4.0));
#endif // UIKIT_HAS_UIFOUNDATION_SYMBOLS
#endif // FOUNDATION_HAS_DIRECTIONAL_GEOMETRY
@property(nonatomic, readonly) UIOffset UIOffsetValue API_AVAILABLE(ios(5.0), watchos(2.0));

@end
    
@interface NSCoder (UIGeometryKeyedCoding)

- (void)encodeCGPoint:(CGPoint)point forKey:(NSString *)key API_AVAILABLE(watchos(2.0));
- (void)encodeCGVector:(CGVector)vector forKey:(NSString *)key API_AVAILABLE(watchos(2.0));
- (void)encodeCGSize:(CGSize)size forKey:(NSString *)key API_AVAILABLE(watchos(2.0));
- (void)encodeCGRect:(CGRect)rect forKey:(NSString *)key API_AVAILABLE(watchos(2.0));
- (void)encodeCGAffineTransform:(CGAffineTransform)transform forKey:(NSString *)key API_AVAILABLE(watchos(2.0));
- (void)encodeUIEdgeInsets:(UIEdgeInsets)insets forKey:(NSString *)key API_AVAILABLE(watchos(2.0));
#ifndef FOUNDATION_HAS_DIRECTIONAL_GEOMETRY
#if UIKIT_HAS_UIFOUNDATION_SYMBOLS
- (void)encodeDirectionalEdgeInsets:(NSDirectionalEdgeInsets)insets forKey:(NSString *)key API_AVAILABLE(ios(11.0),tvos(11.0),watchos(4.0));
#endif // UIKIT_HAS_UIFOUNDATION_SYMBOLS
#endif // FOUNDATION_HAS_DIRECTIONAL_GEOMETRY
- (void)encodeUIOffset:(UIOffset)offset forKey:(NSString *)key API_AVAILABLE(ios(5.0), watchos(2.0));

- (CGPoint)decodeCGPointForKey:(NSString *)key API_AVAILABLE(watchos(2.0));
- (CGVector)decodeCGVectorForKey:(NSString *)key API_AVAILABLE(watchos(2.0));
- (CGSize)decodeCGSizeForKey:(NSString *)key API_AVAILABLE(watchos(2.0));
- (CGRect)decodeCGRectForKey:(NSString *)key API_AVAILABLE(watchos(2.0));
- (CGAffineTransform)decodeCGAffineTransformForKey:(NSString *)key API_AVAILABLE(watchos(2.0));
- (UIEdgeInsets)decodeUIEdgeInsetsForKey:(NSString *)key API_AVAILABLE(watchos(2.0));
#ifndef FOUNDATION_HAS_DIRECTIONAL_GEOMETRY
#if UIKIT_HAS_UIFOUNDATION_SYMBOLS
- (NSDirectionalEdgeInsets)decodeDirectionalEdgeInsetsForKey:(NSString *)key API_AVAILABLE(ios(11.0),tvos(11.0),watchos(4.0));
#endif // UIKIT_HAS_UIFOUNDATION_SYMBOLS
#endif // FOUNDATION_HAS_DIRECTIONAL_GEOMETRY
- (UIOffset)decodeUIOffsetForKey:(NSString *)key API_AVAILABLE(ios(5.0), watchos(2.0));

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIGeometry.h>
#endif
