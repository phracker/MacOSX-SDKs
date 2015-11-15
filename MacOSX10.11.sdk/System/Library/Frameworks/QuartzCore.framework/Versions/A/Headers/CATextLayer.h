/* CoreAnimation - CATextLayer.h

   Copyright (c) 2006-2015, Apple Inc.
   All rights reserved. */

#import <QuartzCore/CALayer.h>

/* The text layer provides simple text layout and rendering of plain
 * or attributed strings. The first line is aligned to the top of the
 * layer. */

NS_ASSUME_NONNULL_BEGIN

@interface CATextLayer : CALayer
{
@private
  struct CATextLayerPrivate *_state;
}

/* The text to be rendered, should be either an NSString or an
 * NSAttributedString. Defaults to nil. */

@property(nullable, copy) id string;

/* The font to use, currently may be either a CTFontRef (toll-free
 * bridged from NSFont), a CGFontRef, or a string naming the font.
 * Defaults to the Helvetica font. Only used when the `string' property
 * is not an NSAttributedString. */

@property(nullable) CFTypeRef font;

/* The font size. Defaults to 36. Only used when the `string' property
 * is not an NSAttributedString. Animatable (Mac OS X 10.6 and later.) */

@property CGFloat fontSize;

/* The color object used to draw the text. Defaults to opaque white.
 * Only used when the `string' property is not an NSAttributedString.
 * Animatable (Mac OS X 10.6 and later.) */

@property(nullable) CGColorRef foregroundColor;

/* When true the string is wrapped to fit within the layer bounds.
 * Defaults to NO.*/

@property(getter=isWrapped) BOOL wrapped;

/* Describes how the string is truncated to fit within the layer
 * bounds. The possible options are `none', `start', `middle' and
 * `end'. Defaults to `none'. */

@property(copy) NSString *truncationMode;

/* Describes how individual lines of text are aligned within the layer
 * bounds. The possible options are `natural', `left', `right',
 * `center' and `justified'. Defaults to `natural'. */

@property(copy) NSString *alignmentMode;

/* Sets allowsFontSubpixelQuantization parameter of CGContextRef
 * passed to the -drawInContext: method. Defaults to NO. */

@property BOOL allowsFontSubpixelQuantization;

@end

/* Truncation modes. */

CA_EXTERN NSString * const kCATruncationNone
    __OSX_AVAILABLE_STARTING (__MAC_10_5, __IPHONE_3_2);
CA_EXTERN NSString * const kCATruncationStart
    __OSX_AVAILABLE_STARTING (__MAC_10_5, __IPHONE_3_2);
CA_EXTERN NSString * const kCATruncationEnd
    __OSX_AVAILABLE_STARTING (__MAC_10_5, __IPHONE_3_2);
CA_EXTERN NSString * const kCATruncationMiddle
    __OSX_AVAILABLE_STARTING (__MAC_10_5, __IPHONE_3_2);

/* Alignment modes. */

CA_EXTERN NSString * const kCAAlignmentNatural
    __OSX_AVAILABLE_STARTING (__MAC_10_5, __IPHONE_3_2);
CA_EXTERN NSString * const kCAAlignmentLeft
    __OSX_AVAILABLE_STARTING (__MAC_10_5, __IPHONE_3_2);
CA_EXTERN NSString * const kCAAlignmentRight
    __OSX_AVAILABLE_STARTING (__MAC_10_5, __IPHONE_3_2);
CA_EXTERN NSString * const kCAAlignmentCenter
    __OSX_AVAILABLE_STARTING (__MAC_10_5, __IPHONE_3_2);
CA_EXTERN NSString * const kCAAlignmentJustified
    __OSX_AVAILABLE_STARTING (__MAC_10_5, __IPHONE_3_2);

NS_ASSUME_NONNULL_END
