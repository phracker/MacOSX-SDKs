/*
        AppKitLegacySwiftCompatibility.h
        Application Kit
        Copyright (c) 2016, Apple Inc.
        All rights reserved.
*/

/* This header and its contents should only be used within AppKit headers. */

#import <AppKit/NSImage.h>
#import <AppKit/NSOpenGL.h>
#import <AppKit/NSColor.h>
#import <AppKit/NSColorSpace.h>
#import <AppKit/NSAppearance.h>
#import <AppKit/NSWindow.h>

NS_ASSUME_NONNULL_BEGIN

#if !NS_IMAGE_DECLARES_DESIGNATED_INITIALIZERS

@interface NSImage ()

- (instancetype)initWithSize:(NSSize)size;

@end

#endif

#if !NS_OPENGL_PIXEL_FORMAT_DECLARES_DESIGNATED_INITIALIZERS

@interface NSOpenGLPixelFormat ()

- (nullable NSOpenGLPixelFormat *)initWithCGLPixelFormatObj:(struct _CGLPixelFormatObject *)format NS_AVAILABLE_MAC(10_6);

@end

#endif

#if !NSCOLOR_USE_CLASS_PROPERTIES
// Older declarations for APIs that have been converted into class properties in 10.12
@interface NSColor (NSColorLegacyDeclarationsForClassProperties)
+ (NSColor *)blackColor;
+ (NSColor *)darkGrayColor;
+ (NSColor *)lightGrayColor;
+ (NSColor *)whiteColor;
+ (NSColor *)grayColor;
+ (NSColor *)redColor;
+ (NSColor *)greenColor;
+ (NSColor *)blueColor;
+ (NSColor *)cyanColor;
+ (NSColor *)yellowColor;
+ (NSColor *)magentaColor;
+ (NSColor *)orangeColor;
+ (NSColor *)purpleColor;
+ (NSColor *)brownColor;
+ (NSColor *)clearColor;
+ (NSColor *)controlShadowColor;
+ (NSColor *)controlDarkShadowColor;
+ (NSColor *)controlColor;
+ (NSColor *)controlHighlightColor;
+ (NSColor *)controlLightHighlightColor;
+ (NSColor *)controlTextColor;
+ (NSColor *)controlBackgroundColor;
+ (NSColor *)selectedControlColor;
+ (NSColor *)secondarySelectedControlColor;
+ (NSColor *)selectedControlTextColor;
+ (NSColor *)disabledControlTextColor;
+ (NSColor *)textColor;
+ (NSColor *)textBackgroundColor;
+ (NSColor *)selectedTextColor;
+ (NSColor *)selectedTextBackgroundColor;
+ (NSColor *)gridColor;
+ (NSColor *)keyboardFocusIndicatorColor;
+ (NSColor *)windowBackgroundColor;
+ (NSColor *)underPageBackgroundColor NS_AVAILABLE_MAC(10_8);
+ (NSColor *)labelColor NS_AVAILABLE_MAC(10_10);
+ (NSColor *)secondaryLabelColor NS_AVAILABLE_MAC(10_10);
+ (NSColor *)tertiaryLabelColor NS_AVAILABLE_MAC(10_10);
+ (NSColor *)quaternaryLabelColor NS_AVAILABLE_MAC(10_10);
+ (NSColor *)scrollBarColor;
+ (NSColor *)knobColor;
+ (NSColor *)selectedKnobColor;
+ (NSColor *)windowFrameColor;
+ (NSColor *)windowFrameTextColor;
+ (NSColor *)selectedMenuItemColor;
+ (NSColor *)selectedMenuItemTextColor;
+ (NSColor *)highlightColor;
+ (NSColor *)shadowColor;
+ (NSColor *)headerColor;
+ (NSColor *)headerTextColor;
+ (NSColor *)alternateSelectedControlColor;
+ (NSColor *)alternateSelectedControlTextColor;
+ (NSArray<NSColor *> *)controlAlternatingRowBackgroundColors;
+ (NSControlTint)currentControlTint;
+ (void)setIgnoresAlpha:(BOOL)flag;
+ (BOOL)ignoresAlpha;
@end
#endif

#if !NSCOLORSPACE_USE_CLASS_PROPERTIES
// Older declarations for APIs that have been converted into class properties in 10.12
@interface NSColorSpace (NSColorSpaceLegacyDeclarationsForClassProperties)
+ (NSColorSpace *)sRGBColorSpace NS_AVAILABLE_MAC(10_5);
+ (NSColorSpace *)genericGamma22GrayColorSpace NS_AVAILABLE_MAC(10_6);
+ (NSColorSpace *)extendedSRGBColorSpace NS_AVAILABLE_MAC(10_12);
+ (NSColorSpace *)extendedGenericGamma22GrayColorSpace NS_AVAILABLE_MAC(10_12);
+ (NSColorSpace *)displayP3ColorSpace NS_AVAILABLE_MAC(10_12);
+ (NSColorSpace *)adobeRGB1998ColorSpace NS_AVAILABLE_MAC(10_5);
+ (NSColorSpace *)genericRGBColorSpace;
+ (NSColorSpace *)genericGrayColorSpace;
+ (NSColorSpace *)genericCMYKColorSpace;
+ (NSColorSpace *)deviceRGBColorSpace;
+ (NSColorSpace *)deviceGrayColorSpace;
+ (NSColorSpace *)deviceCMYKColorSpace;
@end
#endif

#if !NS_APPEARANCE_DECLARES_DESIGNATED_INITIALIZERS

@interface NSAppearance ()

- (nullable instancetype)initWithAppearanceNamed:(NSString *)name bundle:(nullable NSBundle *)bundle;

@end

#endif

#if !NSWINDOW_TRACK_EVENTS_DECLARES_NULLABILITY
@interface NSWindow ()
- (void)trackEventsMatchingMask:(NSEventMask)mask timeout:(NSTimeInterval)timeout mode:(NSRunLoopMode)mode handler:(void(^)(NSEvent *event, BOOL *stop))trackingHandler NS_AVAILABLE_MAC(10_10);
@end
#endif


NS_ASSUME_NONNULL_END
