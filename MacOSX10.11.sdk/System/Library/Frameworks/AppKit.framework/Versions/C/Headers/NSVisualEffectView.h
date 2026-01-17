/*
    NSVisualEffectView.h
    Application Kit
    Copyright (c) 2014-2015, Apple Inc.
    All rights reserved.
*/

#import <AppKit/NSView.h>
#import <AppKit/NSCell.h>

/* The main material that this view displays.
 */
NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, NSVisualEffectMaterial) {
    // These first colors are abstract materials managed by AppKit and should be used when creating UI that needs to mimic these material types
    // Many of these colors are dynamic and depend on the current NSAppearance set on the view (or its parent view)
    NSVisualEffectMaterialAppearanceBased = 0, // Maps to Light or Dark, depending on the appearance set on the view
    NSVisualEffectMaterialTitlebar = 3, // Mainly designed to be used for NSVisualEffectBlendingModeWithinWindow
    NSVisualEffectMaterialMenu NS_ENUM_AVAILABLE_MAC(10_11) = 5,
    NSVisualEffectMaterialPopover NS_ENUM_AVAILABLE_MAC(10_11) = 6,
    NSVisualEffectMaterialSidebar NS_ENUM_AVAILABLE_MAC(10_11) = 7,
    
    // These next colors are specific palette colors that can be used to create a specific design or look that doesn’t fit into the above system defined materials
    NSVisualEffectMaterialLight = 1,
    NSVisualEffectMaterialDark = 2,
    NSVisualEffectMaterialMediumLight NS_ENUM_AVAILABLE_MAC(10_11) = 8,
    NSVisualEffectMaterialUltraDark NS_ENUM_AVAILABLE_MAC(10_11) = 9,
} NS_ENUM_AVAILABLE_MAC(10_10);
                
/* How the view blends with things behind it.
 */
typedef NS_ENUM(NSInteger, NSVisualEffectBlendingMode) {
    NSVisualEffectBlendingModeBehindWindow, // Blends and blurs with the contents behind the window (such as the desktop or other windows). These can overlap, and the view lower in the hierarchy will "win".
    NSVisualEffectBlendingModeWithinWindow, // Blends and blurs with contents behind the view in the current window only. For now, these cannot overlap each other. This mode REQUIRES layer-backing with view.wantsLayer = YES.
} NS_ENUM_AVAILABLE_MAC(10_10);

/* The material may look different when it is inactive. 
 */
typedef NS_ENUM(NSInteger, NSVisualEffectState) {
    NSVisualEffectStateFollowsWindowActiveState, // The backdrop automatically appears active when the window is active, and inactive when it is not active.
    NSVisualEffectStateActive, // The backdrop is explicitly active, always
    NSVisualEffectStateInactive, // The backdrop is explicitly inactive
} NS_ENUM_AVAILABLE_MAC(10_10);

/* The NSVisualEffectView is the basis for all visual effects, including "vibrant" appearances. You can optionally set the appearance to [NSAppearance appearanceNamed:NSAppearanceNameVibrantDark] (or Light) to get the desired light or dark appearance. Combine this with an appropriate light or dark material to get the desired vibrant look. Combining NSAppearanceNameVibrantDark with a light material will look bad, and should not be done.
 */
NS_CLASS_AVAILABLE_MAC(10_10)
@interface NSVisualEffectView : NSView {
@private
    __strong struct NSVisualEffectViewInternal *_NSVisualEffectViewInternal;
    
#if !__LP64__
    uint8_t _reserved[48];
#endif
    CALayer *_darkenLayer;
    CALayer *_maskLayer;
    CALayer *_clearCopyLayer;
    
    unsigned int _dirty:1;
    unsigned int _hasMask:1;
    unsigned int _disableBlurFilter:1;
    unsigned int _titlebarMaterialDrawsSeparator:1;
    unsigned int _maskSet:1;
    unsigned int _clear:1;
    unsigned int _updateInDidMoveToWindow:1;
    unsigned int _hasAcceleration:1;
    unsigned int _emphasized:1;
    unsigned int _hasAccelerationCached:1;
    unsigned int _requiresBackdrop:1;
    unsigned int _appearsDarker:1;
    unsigned int _inheritsBlendGroup:1;
    unsigned int _registeredForFrameChanges:1;
    unsigned int _reservedFlags:18;
}

/* The default value is NSVisualEffectMaterialAppearanceBased; the material is updated to be the correct material based on the appearance set on this view.
 */
@property NSVisualEffectMaterial material;

/*  Returns "Light" or "Dark" depending on the material selected.
*/
@property(readonly) NSBackgroundStyle interiorBackgroundStyle;

/* How this backdrop view blurs its contents. It can either blend with the contents behind the window (NSVisualEffectBlendingModeBehindWindow -- the default), or within the current window (NSVisualEffectBlendingModeWithinWindow). The blending mode for the material NSVisualEffectMaterialTitlebar can only be NSVisualEffectBlendingModeWithinWindow.
 
 The blendingMode NSVisualEffectBlendingModeWithinWindow requires setWantsLayer:YES to be done on the parent view that you desire to blend with.
*/
@property NSVisualEffectBlendingMode blendingMode;

/* The state defaults to NSVisualEffectStateFollowsWindowActiveState.
 */
@property NSVisualEffectState state;

/* The mask image masks this view. It is best to set this to the smallest mask image possible and properly set the image.capInsets to inform the image on how to stretch the contents when it is used as a mask. Setting the maskImage on an NSVisualEffectView that is the window.contentView will correctly set the window's shadow.
 */
@property(nullable, retain) NSImage *maskImage;

/* Some things this class overrides; it is required to call super if you subclass and override these.
 */
- (void)viewDidMoveToWindow NS_REQUIRES_SUPER;
- (void)viewWillMoveToWindow:(nullable NSWindow *)newWindow NS_REQUIRES_SUPER;

@end

NS_ASSUME_NONNULL_END





