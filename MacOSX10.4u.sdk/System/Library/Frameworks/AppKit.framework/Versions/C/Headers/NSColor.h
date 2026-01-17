/*
	NSColor.h
	Application Kit
	Copyright (c) 1994-2005, Apple Computer, Inc.
	All rights reserved.
*/

/* NSColors store colors. Often the only NSColor message you send is the "set" method, which makes the receiver the current color in the drawing context. There is usually no need to dive in and get the individual components (for instance, red, green, blue) that make up a color.

An NSColor may be in one of various colorspaces. Different colorspaces have different ways of getting at the components which define colors in that colorspace. Implementations of NSColors exist for the following colorspaces:

  NSDeviceCMYKColorSpace	Cyan, magenta, yellow, black, and alpha components
  NSDeviceWhiteColorSpace	White and alpha components
  NSDeviceRGBColorSpace		Red, green, blue, and alpha components
				Hue, saturation, brightness, and alpha components
  NSCalibratedWhiteColorSpace	White and alpha components
  NSCalibratedRGBColorSpace	Red, green, blue, and alpha components
				Hue, saturation, brightness, and alpha components
  NSNamedColorSpace		Catalog name, color name components

Alpha component defines opacity on devices which support it (1.0 == full opacity). On other devices the alpha is ignored when the color is used.

It's illegal to ask a color for components that are not defined for its colorspace. If you need to ask a color for a certain set of components (for instance, you need to know the RGB components of a color you got from the color panel), you should first convert the color to the appropriate colorspace using the colorUsingColorSpaceName: method.  If the color is already in the specified colorspace, you get the same color back; otherwise you get a conversion which is usually lossy or is correct only for the current device. You might also get back nil if the specified conversion cannot be done.

Subclassers of NSColor need to implement the methods colorSpaceName, set, the various methods which return the components for that color space, and the NSCoding protocol. Some other methods such as colorWithAlphaComponent:, isEqual:, colorUsingColorSpaceName:device: may also be implemented if they make sense for the colorspace. If isEqual: is overridden, so should hash (because if [a isEqual:b] then [a hash] == [b hash]). Mutable subclassers (if any) should also implement copyWithZone: to a true copy.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSGeometry.h>
#import <AppKit/AppKitDefines.h>
#import <AppKit/NSCell.h>
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
#import <QuartzCore/CIColor.h>
#endif

@class NSDictionary, NSPasteboard, NSImage, NSColorSpace;

#define NSAppKitVersionNumberWithPatternColorLeakFix 641.0



@interface NSColor : NSObject <NSCopying, NSCoding>

/* Create NSCalibratedWhiteColorSpace colors.
*/
+ (NSColor *)colorWithCalibratedWhite:(float)white alpha:(float)alpha;


/* Create NSCalibratedRGBColorSpace colors.
*/
+ (NSColor *)colorWithCalibratedHue:(float)hue saturation:(float)saturation brightness:(float)brightness alpha:(float)alpha;
+ (NSColor *)colorWithCalibratedRed:(float)red green:(float)green blue:(float)blue alpha:(float)alpha;


/* Create colors in various device color spaces. In PostScript these colorspaces correspond directly to the device-dependent operators setgray, sethsbcolor, setrgbcolor, and setcmykcolor.
*/
+ (NSColor *)colorWithDeviceWhite:(float)white alpha:(float)alpha;
+ (NSColor *)colorWithDeviceHue:(float)hue saturation:(float)saturation brightness:(float)brightness alpha:(float)alpha;
+ (NSColor *)colorWithDeviceRed:(float)red green:(float)green blue:(float)blue alpha:(float)alpha;
+ (NSColor *)colorWithDeviceCyan:(float)cyan magenta:(float)magenta yellow:(float)yellow black:(float)black alpha:(float)alpha;


/* Create named colors from standard color catalogs (such as Pantone).
*/
+ (NSColor *)colorWithCatalogName:(NSString *)listName colorName:(NSString *)colorName;


#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
/* Create colors with arbitrary colorspace. The number of components in the provided array should match the number dictated by the specified colorspace, plus one for alpha (supply 1.0 for opaque colors); otherwise an exception will be raised.  If the colorspace is one which cannot be used with NSColors, nil is returned.
*/
+ (NSColor *)colorWithColorSpace:(NSColorSpace *)space components:(const float *)components count:(int)numberOfComponents;
#endif


/* Some convenience methods to create colors in the calibrated color spaces...
*/
+ (NSColor *)blackColor;	/* 0.0 white */
+ (NSColor *)darkGrayColor;	/* 0.333 white */
+ (NSColor *)lightGrayColor;	/* 0.667 white */
+ (NSColor *)whiteColor;	/* 1.0 white */
+ (NSColor *)grayColor;		/* 0.5 white */
+ (NSColor *)redColor;		/* 1.0, 0.0, 0.0 RGB */
+ (NSColor *)greenColor;	/* 0.0, 1.0, 0.0 RGB */
+ (NSColor *)blueColor;		/* 0.0, 0.0, 1.0 RGB */
+ (NSColor *)cyanColor;		/* 0.0, 1.0, 1.0 RGB */
+ (NSColor *)yellowColor;	/* 1.0, 1.0, 0.0 RGB */
+ (NSColor *)magentaColor;	/* 1.0, 0.0, 1.0 RGB */
+ (NSColor *)orangeColor;	/* 1.0, 0.5, 0.0 RGB */
+ (NSColor *)purpleColor;	/* 0.5, 0.0, 0.5 RGB */
+ (NSColor *)brownColor;	/* 0.6, 0.4, 0.2 RGB */
+ (NSColor *)clearColor;	/* 0.0 white, 0.0 alpha */

+ (NSColor *)controlShadowColor;		// Dark border for controls
+ (NSColor *)controlDarkShadowColor;		// Darker border for controls
+ (NSColor *)controlColor;			// Control face and old window background color
+ (NSColor *)controlHighlightColor;		// Light border for controls
+ (NSColor *)controlLightHighlightColor;	// Lighter border for controls
+ (NSColor *)controlTextColor;			// Text on controls
+ (NSColor *)controlBackgroundColor;		// Background of large controls (browser, tableview, clipview, ...)
+ (NSColor *)selectedControlColor;		// Control face for selected controls
+ (NSColor *)secondarySelectedControlColor;	// Color for selected controls when control is not active (that is, not focused)
+ (NSColor *)selectedControlTextColor;		// Text on selected controls
+ (NSColor *)disabledControlTextColor;		// Text on disabled controls
+ (NSColor *)textColor;				// Document text
+ (NSColor *)textBackgroundColor;		// Document text background
+ (NSColor *)selectedTextColor;			// Selected document text
+ (NSColor *)selectedTextBackgroundColor;	// Selected document text background
+ (NSColor *)gridColor;				// Grids in controls
+ (NSColor *)keyboardFocusIndicatorColor;	// Keyboard focus ring around controls
+ (NSColor *)windowBackgroundColor;		// Background fill for window contents

+ (NSColor *)scrollBarColor;			// Scroll bar slot color
+ (NSColor *)knobColor;     			// Knob face color for controls
+ (NSColor *)selectedKnobColor;       		// Knob face color for selected controls

+ (NSColor *)windowFrameColor;			// Window frames
+ (NSColor *)windowFrameTextColor;		// Text on window frames

+ (NSColor *)selectedMenuItemColor;		// Highlight color for menus
+ (NSColor *)selectedMenuItemTextColor;		// Highlight color for menu text

+ (NSColor *)highlightColor;     	     	// Highlight color for UI elements (this is abstract and defines the color all highlights tend toward)
+ (NSColor *)shadowColor;     			// Shadow color for UI elements (this is abstract and defines the color all shadows tend toward)

+ (NSColor *)headerColor;			// Background color for header cells in Table/OutlineView
+ (NSColor *)headerTextColor;			// Text color for header cells in Table/OutlineView

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_2
+ (NSColor *)alternateSelectedControlColor;	// Similar to selectedControlColor; for use in lists and tables 
+ (NSColor *)alternateSelectedControlTextColor;		// Similar to selectedControlTextColor; see alternateSelectedControlColor
#endif

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3
+ (NSArray *)controlAlternatingRowBackgroundColors;	// Standard colors for alternating colored rows in tables and lists (for instance, light blue/white; don't assume just two colors)
#endif

- (NSColor *)highlightWithLevel:(float)val;	// val = 0 => receiver, val = 1 => highlightColor
- (NSColor *)shadowWithLevel:(float)val;	// val = 0 => receiver, val = 1 => shadowColor

+ (NSColor *)colorForControlTint:(NSControlTint)controlTint;	// pass in valid tint to get rough color matching. returns default if invalid tint

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3
+ (NSControlTint) currentControlTint;	// returns current system control tint
#endif


/* Set the color: Sets the fill and stroke colors in the current drawing context. If the color doesn't know about alpha, it's set to 1.0. Should be implemented by subclassers.
*/
- (void)set;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3
/* Set the fill or stroke colors individually. These should be implemented by subclassers.
*/
- (void)setFill;
- (void)setStroke;
#endif

/* Get the color space of the color. Should be implemented by subclassers.
*/
- (NSString *)colorSpaceName;


/* Convert the color to another colorspace, using a colorspace name. This may return nil if the specified conversion cannot be done. The abstract implementation of this method returns the receiver if the specified colorspace matches that of the receiver; otherwise it returns nil. Subclassers who can convert themselves to other colorspaces override this method to do something better.

The version of this method which takes a device description allows the color to specialize itself for the given device.  Device descriptions can be obtained from windows, screens, and printers with the "deviceDescription" method.

If device is nil then the current device (as obtained from the currently lockFocus'ed view's window or, if printing, the current printer) is used. The method without the device: argument passes nil for the device.

If colorSpace is nil, then the most appropriate color space is used.
*/ 
- (NSColor *)colorUsingColorSpaceName:(NSString *)colorSpace;
- (NSColor *)colorUsingColorSpaceName:(NSString *)colorSpace device:(NSDictionary *)deviceDescription;


#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
/* colorUsingColorSpace: will convert existing color to a new colorspace and create a new color, which will likely have different component values but look the same. It will return the same color if the colorspace is already the same as the one specified.  Will return nil if conversion is not possible.
*/
- (NSColor *)colorUsingColorSpace:(NSColorSpace *)space;
#endif


/* Blend using the NSCalibratedRGB color space. Both colors are converted into the calibrated RGB color space, and they are blended by taking fraction of color and 1 - fraction of the receiver. The result is in the calibrated RGB color space. If the colors cannot be converted into the calibrated RGB color space the blending fails and nil is returned.
*/
- (NSColor *)blendedColorWithFraction:(float)fraction ofColor:(NSColor *)color;


/* Returns a color in the same color space as the receiver with the specified alpha component. The abstract implementation of this method returns the receiver if alpha is 1.0, otherwise it returns nil; subclassers who have explicit opacity components override this method to actually return a color with the specified alpha.
*/
- (NSColor *)colorWithAlphaComponent:(float)alpha;


/*** Methods to get various components of colors. Not all of the methods apply to all colors; if called, they raise. ***/

/* Get the catalog and color name of standard colors from catalogs. These colors are special colors which are usually looked up on each device by their name.
*/
- (NSString *)catalogNameComponent;
- (NSString *)colorNameComponent;

/* Return localized versions of the above.
*/
- (NSString *)localizedCatalogNameComponent;
- (NSString *)localizedColorNameComponent;

/* Get the red, green, or blue components of NSCalibratedRGB or NSDeviceRGB colors.
*/
- (float)redComponent;
- (float)greenComponent;
- (float)blueComponent;
- (void)getRed:(float *)red green:(float *)green blue:(float *)blue alpha:(float *)alpha;

/* Get the components of NSCalibratedRGB or NSDeviceRGB colors as hue, saturation, or brightness.
*/
- (float)hueComponent;
- (float)saturationComponent;
- (float)brightnessComponent;
- (void)getHue:(float *)hue saturation:(float *)saturation brightness:(float *)brightness alpha:(float *)alpha;


/* Get the white component of NSCalibratedWhite or NSDeviceWhite colors.
*/
- (float)whiteComponent;
- (void)getWhite:(float *)white alpha:(float *)alpha;


/* Get the CMYK components of NSDeviceCMYK colors.
*/
- (float)cyanComponent;
- (float)magentaComponent;
- (float)yellowComponent;
- (float)blackComponent;
- (void)getCyan:(float *)cyan magenta:(float *)magenta yellow:(float *)yellow black:(float *)black alpha:(float *)alpha;


#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
/* For colors with custom colorspace; get the colorspace and individual floating point components, including alpha. Note that all these methods will work for other NSColors which have floating point components. They will raise exceptions otherwise, like other existing colorspace-specific methods.
*/
- (NSColorSpace *)colorSpace;
- (int)numberOfComponents;
- (void)getComponents:(float *)components;
#endif


/* Get the alpha component. For colors which do not have alpha components, this will return 1.0 (opaque).
*/
- (float)alphaComponent;


/* Pasteboard methods
*/
+ (NSColor *)colorFromPasteboard:(NSPasteboard *)pasteBoard;
- (void)writeToPasteboard:(NSPasteboard *)pasteBoard;

/* Pattern methods. Note that colorWithPatternImage: mistakenly returns a non-autoreleased color in 10.1.x and earlier. This has been fixed in (NSAppKitVersionNumber >= NSAppKitVersionNumberWithPatternColorLeakFix), for apps linked post-10.1.x.
*/
+ (NSColor *)colorWithPatternImage:(NSImage*)image;
- (NSImage *)patternImage; 

/* Draws the color and adorns it to indicate the type of color. Used by colorwells, swatches, and other UI objects that need to display colors. Implementation in NSColor simply draws the color (with an indication of transparency if the color isn't fully opaque); subclassers can draw more stuff as they see fit.
*/
- (void)drawSwatchInRect:(NSRect)rect;


/* Global flag for determining whether an application supports alpha.  This flag is consulted when an application imports alpha (through color dragging, for instance). The value of this flag also determines whether the color panel has an opacity slider. This value is YES by default, indicating that the opacity components of imported colors will be set to 1.0. If an application wants alpha, it can either set the "NSIgnoreAlpha" default to NO or call the set method below.

This method provides a global approach to removing alpha which might not always be appropriate. Applications which need to import alpha sometimes should set this flag to NO and explicitly make colors opaque in cases where it matters to them.
*/
+ (void)setIgnoresAlpha:(BOOL)flag;
+ (BOOL)ignoresAlpha;

@end


#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
@interface NSColor (NSQuartzCoreAdditions)
+ (NSColor *)colorWithCIColor:(CIColor *)color;
@end

@interface CIColor (NSAppKitAdditions)
- (id)initWithColor:(NSColor *)color;
@end
#endif /* MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4 */

@interface NSCoder(NSAppKitColorExtensions)

/* To decode NXColors... Will return nil if the archived color was "invalid" (written out by the kit in a few instances). Otherwise returns autoreleased NSColor. Can't write NSColors as NXColors, so we have no corresponding encode method.
*/
- (NSColor *)decodeNXColor;

@end

APPKIT_EXTERN NSString *NSSystemColorsDidChangeNotification;
