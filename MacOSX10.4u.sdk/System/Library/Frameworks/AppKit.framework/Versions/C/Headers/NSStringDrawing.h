/*
        NSStringDrawing.h
        Copyright (c) 1994-2005, Apple Computer, Inc.  All rights reserved.

        Methods to deal with NSString drawing, measuring
   
*/

#import <Foundation/NSString.h>
#import <AppKit/NSAttributedString.h>

@interface NSString(NSStringDrawing)

- (NSSize)sizeWithAttributes:(NSDictionary *)attrs;
- (void)drawAtPoint:(NSPoint)point withAttributes:(NSDictionary *)attrs;
- (void)drawInRect:(NSRect)rect withAttributes:(NSDictionary *)attrs;

@end

@interface NSAttributedString(NSStringDrawing)

- (NSSize)size;
- (void)drawAtPoint:(NSPoint)point;
- (void)drawInRect:(NSRect)rect;

@end

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
typedef enum {
    NSStringDrawingUsesLineFragmentOrigin = (1 << 0), // The specified origin is the line fragment origin, not the base line origin
    NSStringDrawingUsesFontLeading = (1 << 1), // Uses the font leading for calculating line heights
    NSStringDrawingDisableScreenFontSubstitution = (1 << 2), // Disable screen font substitution (-[NSLayoutManager setUsesScreenFonts:NO])
    NSStringDrawingUsesDeviceMetrics = (1 << 3), // Uses image glyph bounds instead of typographic bounds
    NSStringDrawingOneShot = (1 << 4) // Suppresses caching layout information
} NSStringDrawingOptions;

@interface NSString (NSExtendedStringDrawing)
/* Renders the receiver using the argument in the current graphics context. The rect argument's origin field specifies the rendering origin. The point is interpreted as the baseline origin by default. With NSStringDrawingUsesLineFragmentOrigin, it is interpreted as the upper left corner of the line fragment rect. The size field specifies the text container size. The width part of the size field specifies the maximum line fragment width if larger than 0.0. The height defines the maximum size that can be occupied with text if larger than 0.0 and NSStringDrawingUsesLineFragmentOrigin is specified. If NSStringDrawingUsesLineFragmentOrigin is not specified, height is ignored and considered to be single-line rendering (NSLineBreakByWordWrapping and NSLineBreakByCharWrapping are treated as NSLineBreakByClipping).
*/
- (void)drawWithRect:(NSRect)rect options:(NSStringDrawingOptions)options attributes:(NSDictionary *)attributes;

 /* Calculates and returns bounding rect for the recceiver. The rect origin returned from this method is the first glyph origin.
*/
- (NSRect)boundingRectWithSize:(NSSize)size options:(NSStringDrawingOptions)options attributes:(NSDictionary *)attributes;
@end

@interface NSAttributedString (NSExtendedStringDrawing)
- (void)drawWithRect:(NSRect)rect options:(NSStringDrawingOptions)options;
- (NSRect)boundingRectWithSize:(NSSize)size options:(NSStringDrawingOptions)options;
@end
#endif /* MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4 */

