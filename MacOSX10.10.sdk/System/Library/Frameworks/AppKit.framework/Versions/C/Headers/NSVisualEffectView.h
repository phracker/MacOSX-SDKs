/*
    NSVisualEffectView.h
    Application Kit
    Copyright (c) 2014, Apple Inc.
    All rights reserved.
*/

#import <AppKit/NSView.h>
#import <AppKit/NSCell.h>

/* The main material that this view displays.
 */
typedef NS_ENUM(NSInteger, NSVisualEffectMaterial) {
    // When NSVisualEffectMaterialAppearanceBased is set, the material color is determined by the current effectiveAppearance that is on the view
    NSVisualEffectMaterialAppearanceBased,
    NSVisualEffectMaterialLight,
    NSVisualEffectMaterialDark,
    NSVisualEffectMaterialTitlebar
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
    uint8_t _reserved[60];
#endif
    
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
    unsigned int _reservedFlags:22;
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

/* The mask image masks this view.
 */
@property(retain) NSImage *maskImage;

/* Some things this class overrides; it is required to call super if you subclass and override these.
 */
- (void)viewDidMoveToWindow NS_REQUIRES_SUPER;
- (void)viewWillMoveToWindow:(NSWindow *)newWindow NS_REQUIRES_SUPER;

@end





