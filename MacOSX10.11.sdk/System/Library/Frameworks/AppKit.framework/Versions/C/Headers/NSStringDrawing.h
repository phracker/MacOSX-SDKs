/*
        NSStringDrawing.h
        Copyright (c) 1994-2015, Apple Inc.  All rights reserved.
*/

#import <Foundation/NSString.h>
#import <AppKit/NSAttributedString.h>

@class NSStringDrawingContext;

NS_ASSUME_NONNULL_BEGIN

// When attributes=nil, the methods declared here uses the default behavior for each attribute described in <AppKit/NSAttributedString.h>. When stringDrawingContext=nil, it's equivalent of passing the default instance initialized with [[NSStringDrawingContext alloc] init].

NS_CLASS_AVAILABLE(10_11, 6_0) @interface NSStringDrawingContext : NSObject
#if !__OBJC2__
{
@private
    id impl;
}
#endif

// Minimum scale factor for drawWithRect:options:context: and boundingRectWithSize:options:context: methods. If this property is set, the extended string drawing methods will attempt to draw the attributed string in the given bounds by proportionally scaling the font(s) in the attributed string
@property CGFloat minimumScaleFactor;

// actual scale factor used by the last drawing call where minimum scale factor was specified
@property(readonly) CGFloat actualScaleFactor;

// bounds of the string drawn by the previous invocation of drawWithRect:options:context:
@property(readonly) NSRect totalBounds;

@end

@interface NSString(NSStringDrawing)
- (NSSize)sizeWithAttributes:(nullable NSDictionary<NSString *, id> *)attrs NS_AVAILABLE(10_0, 7_0);
- (void)drawAtPoint:(NSPoint)point withAttributes:(nullable NSDictionary<NSString *, id> *)attrs NS_AVAILABLE(10_0, 7_0);
- (void)drawInRect:(NSRect)rect withAttributes:(nullable NSDictionary<NSString *, id> *)attrs NS_AVAILABLE(10_0, 7_0);
@end

@interface NSAttributedString(NSStringDrawing)
- (NSSize)size NS_AVAILABLE(10_0, 6_0);
- (void)drawAtPoint:(NSPoint)point NS_AVAILABLE(10_0, 6_0);
- (void)drawInRect:(NSRect)rect NS_AVAILABLE(10_0, 6_0);
@end

typedef NS_OPTIONS(NSInteger, NSStringDrawingOptions) {
    NSStringDrawingUsesLineFragmentOrigin = 1 << 0, // The specified origin is the line fragment origin, not the base line origin
    NSStringDrawingUsesFontLeading = 1 << 1, // Uses the font leading for calculating line heights
    NSStringDrawingUsesDeviceMetrics = 1 << 3, // Uses image glyph bounds instead of typographic bounds
    NSStringDrawingTruncatesLastVisibleLine NS_ENUM_AVAILABLE(10_5, 6_0) = 1 << 5, // Truncates and adds the ellipsis character to the last visible line if the text doesn't fit into the bounds specified. Ignored if NSStringDrawingUsesLineFragmentOrigin is not also set.

    NSStringDrawingDisableScreenFontSubstitution NS_ENUM_DEPRECATED_MAC(10_0, 10_11) = (1 << 2),
    NSStringDrawingOneShot NS_ENUM_DEPRECATED_MAC(10_0, 10_11) = (1 << 4)
} NS_ENUM_AVAILABLE(10_0, 6_0);


// NOTE: All of the following methods will default to drawing on a baseline, limiting drawing to a single line.
// To correctly draw and size multi-line text, pass NSStringDrawingUsesLineFragmentOrigin in the options parameter.
@interface NSString (NSExtendedStringDrawing)
- (void)drawWithRect:(NSRect)rect options:(NSStringDrawingOptions)options attributes:(nullable NSDictionary<NSString *, id> *)attributes context:(nullable NSStringDrawingContext *)context NS_AVAILABLE(10_11, 7_0);
- (NSRect)boundingRectWithSize:(NSSize)size options:(NSStringDrawingOptions)options attributes:(nullable NSDictionary<NSString *, id> *)attributes context:(nullable NSStringDrawingContext *)context NS_AVAILABLE(10_11, 7_0);
@end

@interface NSAttributedString (NSExtendedStringDrawing)
- (void)drawWithRect:(NSRect)rect options:(NSStringDrawingOptions)options context:(nullable NSStringDrawingContext *)context NS_AVAILABLE(10_11, 6_0);
- (NSRect)boundingRectWithSize:(NSSize)size options:(NSStringDrawingOptions)options context:(nullable NSStringDrawingContext *)context NS_AVAILABLE(10_11, 6_0);
@end

/************************ Deprecated ************************/
// Following NSStringDrawing methods are soft deprecated starting with OS X 10.11. It will be officially deprecated in a future release. Use corresponding API with NSStringDrawingContext instead
@interface NSString (NSStringDrawingDeprecated)
- (void)drawWithRect:(NSRect)rect options:(NSStringDrawingOptions)options attributes:(nullable NSDictionary<NSString *, id> *)attributes; // Use -drawWithRect:options:attributes:context: instead

- (NSRect)boundingRectWithSize:(NSSize)size options:(NSStringDrawingOptions)options attributes:(nullable NSDictionary<NSString *, id> *)attributes; // Use -boundingRectWithSize:options:attributes:context: instead
@end

@interface NSAttributedString (NSStringDrawingDeprecated)
- (void)drawWithRect:(NSRect)rect options:(NSStringDrawingOptions)options; // Use -drawWithRect:options:context: instead
- (NSRect)boundingRectWithSize:(NSSize)size options:(NSStringDrawingOptions)options; // Use -boundingRectWithSize:options:context: instead
@end


NS_ASSUME_NONNULL_END
