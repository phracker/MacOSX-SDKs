/* CoreImage - CIColor.h

   Copyright (c) 2004 Apple Computer, Inc.
   All rights reserved. */

#import <Foundation/NSObject.h>

#import <ApplicationServices/ApplicationServices.h>

@interface CIColor : NSObject <NSCoding, NSCopying>
{
    void *_priv;
    void *_pad[3];
}

/* Create a new color object. */

+ (CIColor *)colorWithCGColor:(CGColorRef)c;

/* Create a new color object. It's created using the GenericRGB color space. */

+ (CIColor *)colorWithRed:(float)r green:(float)g blue:(float)b alpha:(float)a;
+ (CIColor *)colorWithRed:(float)r green:(float)g blue:(float)b;

/* Create a new color object, 'representation' should be a string in one of
 * the formats returned by the stringRepresentation method. */

+ (CIColor *)colorWithString:(NSString *)representation;

/* Initializer. */

- (id)initWithCGColor:(CGColorRef)c;

/* Return the number of color components (including alpha). */

- (size_t)numberOfComponents;

/* Return the color components (including alpha). */

- (const float *)components;

/* Return the alpha value of the color. */

- (float)alpha;

/* Return the color space object associated with the color. */

- (CGColorSpaceRef)colorSpace;

/* Return the (unpremultiplied) red, green or blue components of the color. */

- (float)red;
- (float)green;
- (float)blue;

/* Returns a formatted string with the components of the color. */

- (NSString *)stringRepresentation;

@end
