/* CoreImage - CIColor.h

   Copyright (c) 2004 Apple Computer, Inc.
   All rights reserved. */

#import <CoreImage/CIVector.h>
#import <CoreImage/CoreImageDefines.h>

CORE_IMAGE_CLASS_EXPORT
@interface CIColor : NSObject <NSCoding, NSCopying>
{
    void *_priv;
    void *_pad[3];
}

/* Create a new color object. */
+ (CIColor *)colorWithCGColor:(CGColorRef)c;

/* Create a new color object.
 It's created using the GenericRGB color space. To create a CIColor with a different color space, use +colorWithCGColor:. */
+ (CIColor *)colorWithRed:(CGFloat)r green:(CGFloat)g blue:(CGFloat)b alpha:(CGFloat)a;
+ (CIColor *)colorWithRed:(CGFloat)r green:(CGFloat)g blue:(CGFloat)b;

/* Create a new color object, 'representation' should be a string in one of
 * the formats returned by the stringRepresentation method. */
+ (CIColor *)colorWithString:(NSString *)representation;

/* Initializer. */

- (id)initWithCGColor:(CGColorRef)c;

/* Return the number of color components (including alpha). */
- (size_t)numberOfComponents;

/* Return the color components (including alpha). */
- (const CGFloat *)components;

/* Return the alpha value of the color. */
- (CGFloat)alpha;

/* Return the color space object associated with the color. */
- (CGColorSpaceRef)colorSpace;

/* Return the (unpremultiplied) red, green or blue components of the color. */
- (CGFloat)red;
- (CGFloat)green;
- (CGFloat)blue;

/* Returns a formatted string with the components of the color. */
- (NSString *)stringRepresentation;

@end
