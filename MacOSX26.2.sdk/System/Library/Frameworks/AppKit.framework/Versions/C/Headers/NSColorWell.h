/*
	NSColorWell.h
	Application Kit
	Copyright (c) 1994-2024, Apple Inc.
	All rights reserved.
*/

#import <AppKit/NSControl.h>
#import <AppKit/AppKitDefines.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)
APPKIT_API_UNAVAILABLE_BEGIN_MACCATALYST

typedef NS_ENUM(NSInteger, NSColorWellStyle) {
    NSColorWellStyleDefault = 0,    /// The default `colorWellStyle`. A well that accepts drag/drop of colors as well as reveals the color panel when clicked.
    NSColorWellStyleMinimal,        /// A minimally adorned well. By default shows a popover color picker when clicked; this interaction behavior can be customized.
    NSColorWellStyleExpanded,       /// An expanded well with a dedicated button for revealing the color panel. By default, clicking the well will show a popover color picker; this interaction behavior can be customized.
} NS_SWIFT_NAME(NSColorWell.Style) API_AVAILABLE(macos(13.0));

@interface NSColorWell : NSControl

+ (instancetype) colorWellWithStyle:(NSColorWellStyle)style API_AVAILABLE(macos(13.0)); /// Instantiates a well in the given style with a default configuration.

- (void)deactivate;
- (void)activate:(BOOL)exclusive;
@property (getter=isActive, readonly) BOOL active;

- (void)drawWellInside:(NSRect)insideRect;

@property (getter=isBordered) BOOL bordered API_DEPRECATED("This property will be deprecated in a future release.", macos(10.0, API_TO_BE_DEPRECATED));

- (void)takeColorFrom:(nullable id)sender;
@property (copy) NSColor *color;

@property (assign) NSColorWellStyle colorWellStyle API_AVAILABLE(macos(13.0));

@property (nullable, strong) NSImage *image API_AVAILABLE(macos(13.0)); /// The image that appears on the button portion of the expanded control. This property only applicable when `colorWellStyle` is `NSColorWellStyleExpanded`.

@property (nullable, weak) id pulldownTarget API_AVAILABLE(macos(13.0)); /// The target which `pulldownAction` is sent to. This property only applicable when `colorWellStyle` is `NSColorWellStyleExpanded` or `NSColorWellStyleMinimal`.
@property (nullable) SEL pulldownAction API_AVAILABLE(macos(13.0)); /// The action sent to `pulldownTarget` when the user interacts with the well. This property only applicable when `colorWellStyle` is `NSColorWellStyleExpanded` or `NSColorWellStyleMinimal`. If no action is set, the well will show the system color picker popover.

/// Controls alpha support for the current color well, and the visibility of alpha slider in the color panel.
/// When `NSColor.ignoresAlpha` (deprecated) is set to `YES`, this property will always return `NO` and alpha is not supported globally.
@property BOOL supportsAlpha API_AVAILABLE(macos(14.0));

/// The maximum linear exposure a color in this color well can be set to. Defaults to 1 and ignores any value less than 1. If set to a value >= 2, the color picked for this well may have a linear exposure applied to it.
@property CGFloat maximumLinearExposure API_AVAILABLE(macos(26.0));

@end

API_UNAVAILABLE_END
NS_HEADER_AUDIT_END(nullability, sendability)
