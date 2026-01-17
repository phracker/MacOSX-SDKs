/*
    NSImageView.h
    Application Kit
    Copyright (c) 1994-2024, Apple Inc.
    All rights reserved.
*/

#import <AppKit/NSControl.h>
#import <AppKit/NSImageCell.h>
#import <AppKit/NSMenu.h>
#import <AppKit/AppKitDefines.h>
#import <Symbols/NSSymbolEffect.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)
APPKIT_API_UNAVAILABLE_BEGIN_MACCATALYST

@class NSImageSymbolConfiguration;

/*!
 Values that can be used to enable or constrain display of High Dynamic Range (HDR) content in NSImageViews. Displaying HDR content in an NSImageView requires that the assigned NSImage has HDR content in the ITU-R 2100 color space and also that the output device has Extended Dynamic Range (EDR) capabilities.
 */
typedef NS_ENUM(NSInteger, NSImageDynamicRange) {
    NSImageDynamicRangeUnspecified = -1,
    
    /// Restrict the image content dynamic range to the standard range regardless of the actual range of the image content.
    NSImageDynamicRangeStandard = 0,
    /// Allow constrained HDR image content. Useful when mixing HDR and SDR content.
    NSImageDynamicRangeConstrainedHigh = 1,
    /// Allow image content to use extended dynamic range if it has high dynamic range content.
    NSImageDynamicRangeHigh = 2
} NS_SWIFT_NAME(NSImage.DynamicRange) API_AVAILABLE(macos(14.0));

@interface NSImageView : NSControl <NSAccessibilityImage, NSMenuItemValidation>

/*!
 Creates a non-editable image view containing the provided image. The image is scaled proportionally down to fit the view, and is centered within the view.
 @param image The image to display within the view.
 @return An initialized image view.
 */
+ (instancetype)imageViewWithImage:(NSImage *)image API_AVAILABLE(macos(10.12));

@property (nullable, strong) NSImage *image;

@property (getter=isEditable) BOOL editable;

@property NSImageAlignment imageAlignment;
@property NSImageScaling imageScaling;
@property NSImageFrameStyle imageFrameStyle;

/*!
 Specifies a combination of point size, weight, and scale to use when sizing and displaying symbol images. If a symbol configuration isn't provided, the image view uses a default size, weight, and scale provided by the system. The default value is `nil`.
 */
@property (nullable, copy) NSImageSymbolConfiguration *symbolConfiguration API_AVAILABLE(macos(11.0));

/*!
 A tint color to be used when rendering template image content. This color may be combined with other effects to produce a theme-appropriate rendition of the template image. A nil value indicates the standard set of effects without color modification. The default value is nil.
 */
@property (nullable, copy) NSColor *contentTintColor API_AVAILABLE(macos(10.14));

@property BOOL animates;

@property BOOL allowsCutCopyPaste;

/// Default preferred image dynamic range. Defaults to `NSImageDynamicRangeConstrainedHigh` on macOS 14 and higher, `NSImageDynamicRangeStandard` otherwise. Set to another value to change the default for all subsequently created `NSImageView`s in your app.
@property (class) NSImageDynamicRange defaultPreferredImageDynamicRange API_AVAILABLE(macos(14.0));

/// Preferred dynamic range when displaying an image in the receiving image view.
@property NSImageDynamicRange preferredImageDynamicRange API_AVAILABLE(macos(14.0));

/// Resolved dynamic range based on fully resolved image content. Note: this will return `NSImageDynamicRangeUnspecified` if the image view has not or can not resolve the content (either because it has no resolvable image content or has not resolved because the image view hasn't displayed.)
@property (readonly) NSImageDynamicRange imageDynamicRange API_AVAILABLE(macos(14.0));

@end

@interface NSImageView (NSSymbolEffect)
/// Adds a symbol effect to the image view with default options and animation.
- (void)addSymbolEffect:(NSSymbolEffect *)symbolEffect API_AVAILABLE(macos(14.0)) NS_REFINED_FOR_SWIFT;
/// Adds a symbol effect to the image view with specified options and default animation.
- (void)addSymbolEffect:(NSSymbolEffect *)symbolEffect options:(NSSymbolEffectOptions *)options API_AVAILABLE(macos(14.0)) NS_REFINED_FOR_SWIFT;
/// Adds a symbol effect to the image view with specified options and animation.
- (void)addSymbolEffect:(NSSymbolEffect *)symbolEffect options:(NSSymbolEffectOptions *)options animated:(BOOL)animated API_AVAILABLE(macos(14.0)) NS_REFINED_FOR_SWIFT;

/// Removes from the image view the symbol effect matching the type of effect passed in, with default options and animation.
- (void)removeSymbolEffectOfType:(NSSymbolEffect *)symbolEffect API_AVAILABLE(macos(14.0)) NS_REFINED_FOR_SWIFT;
/// Removes from the image view the symbol effect matching the type of effect passed in, with specified options and default animation.
- (void)removeSymbolEffectOfType:(NSSymbolEffect *)symbolEffect options:(NSSymbolEffectOptions *)options API_AVAILABLE(macos(14.0)) NS_REFINED_FOR_SWIFT;
/// Removes from the image view the symbol effect matching the type of effect passed in, with specified options and animation.
- (void)removeSymbolEffectOfType:(NSSymbolEffect *)symbolEffect options:(NSSymbolEffectOptions *)options animated:(BOOL)animated API_AVAILABLE(macos(14.0)) NS_REFINED_FOR_SWIFT;

/// Removes all symbol effects from the image view with default options and animation.
- (void)removeAllSymbolEffects API_AVAILABLE(macos(14.0)) NS_REFINED_FOR_SWIFT;
/// Removes all symbol effects from the image view with specified options and default animation.
- (void)removeAllSymbolEffectsWithOptions:(NSSymbolEffectOptions *)options API_AVAILABLE(macos(14.0)) NS_REFINED_FOR_SWIFT;
/// Removes all symbol effects from the image view with specified options and animation.
- (void)removeAllSymbolEffectsWithOptions:(NSSymbolEffectOptions *)options animated:(BOOL)animated API_AVAILABLE(macos(14.0)) NS_REFINED_FOR_SWIFT;

/// Sets the symbol image on the image view with a symbol content transition and default options.
/// Passing in a non-symbol image will result in undefined behavior.
- (void)setSymbolImage:(NSImage *)symbolImage withContentTransition:(NSSymbolContentTransition *)transition API_AVAILABLE(macos(14.0)) NS_REFINED_FOR_SWIFT;
/// Sets the symbol image on the image view with a symbol content transition and specified options.
/// Passing in a non-symbol image will result in undefined behavior.
- (void)setSymbolImage:(NSImage *)symbolImage withContentTransition:(NSSymbolContentTransition *)transition options:(NSSymbolEffectOptions *)options API_AVAILABLE(macos(14.0)) NS_REFINED_FOR_SWIFT;

@end

API_UNAVAILABLE_END
NS_HEADER_AUDIT_END(nullability, sendability)


