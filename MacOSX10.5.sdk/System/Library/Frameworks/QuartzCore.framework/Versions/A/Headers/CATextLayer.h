/* CoreAnimation - CATextLayer.h

   Copyright (c) 2006-2007 Apple Inc.
   All rights reserved. */

#import <QuartzCore/CALayer.h>

/* The text layer provides simple text layout and rendering of plain
 * or attributed strings. The first line is aligned to the top of the
 * layer. */

@interface CATextLayer : CALayer
{
@private
  CFTypeRef _state;
}

/* The text to be rendered, should be either an NSString or an
 * NSAttributedString. Defaults to nil. */

@property(copy) id string;

/* The font to use, currently may be either a CTFontRef (toll-free
 * bridged from NSFont), a CGFontRef, or a string naming the font.
 * Defaults to the Helvetica font. Only used when the `string' property
 * is not an NSAttributedString. */

@property CFTypeRef font;

/* The font size. Defaults to 36. Only used when the `string' property
 * is not an NSAttributedString. */

@property CGFloat fontSize;

/* The color object used to draw the text. Defaults to opaque white.
 * Only used when the `string' property is not an NSAttributedString. */

@property CGColorRef foregroundColor;

/* When true the string is wrapped to fit within the layer bounds.
 * Defaults to false.*/

@property(getter=isWrapped) BOOL wrapped;

/* Describes how the string is truncated to fit within the layer
 * bounds. The possible options are `none', `start', `middle' and
 * `end'. Defaults to `none'. */

@property(copy) NSString *truncationMode;

/* Describes how individual lines of text are aligned within the layer
 * bounds. The possible options are `natural', `left', `right',
 * `center' and `justified'. Defaults to `natural'. */

@property(copy) NSString *alignmentMode;

@end

/* Truncation modes. */

CA_EXTERN NSString * const kCATruncationNone AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
CA_EXTERN NSString * const kCATruncationStart AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
CA_EXTERN NSString * const kCATruncationEnd AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
CA_EXTERN NSString * const kCATruncationMiddle AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/* Alignment modes. */

CA_EXTERN NSString * const kCAAlignmentNatural AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
CA_EXTERN NSString * const kCAAlignmentLeft AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
CA_EXTERN NSString * const kCAAlignmentRight AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
CA_EXTERN NSString * const kCAAlignmentCenter AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
CA_EXTERN NSString * const kCAAlignmentJustified AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
