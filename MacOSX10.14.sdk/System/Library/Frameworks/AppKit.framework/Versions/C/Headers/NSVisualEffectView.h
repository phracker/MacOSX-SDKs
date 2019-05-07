/*
    NSVisualEffectView.h
    Application Kit
    Copyright (c) 2014-2018, Apple Inc.
    All rights reserved.
*/

#import <AppKit/NSView.h>
#import <AppKit/NSWindow.h>
#import <AppKit/NSImage.h>
#import <AppKit/NSCell.h>
#import <Foundation/NSObjCRuntime.h>

NS_ASSUME_NONNULL_BEGIN

/// The main material that this view displays.  Materials are dynamic, and their exact look depends on the view's effectiveAppearance, blendingMode, state, emphasized, and possibly other factors.
typedef NS_ENUM(NSInteger, NSVisualEffectMaterial) {
    /// The material used by window titlebars.
    NSVisualEffectMaterialTitlebar = 3,
    
    /// The material used in some table views, menus, etc., to indicate selection.
    NSVisualEffectMaterialSelection = 4,
    
    /// The material used by menus.
    NSVisualEffectMaterialMenu NS_ENUM_AVAILABLE_MAC(10_11) = 5,
    
    /// The material used in the background of NSPopover windows.
    NSVisualEffectMaterialPopover NS_ENUM_AVAILABLE_MAC(10_11) = 6,
    
    /// The material used in the background of window sidebars.
    NSVisualEffectMaterialSidebar NS_ENUM_AVAILABLE_MAC(10_11) = 7,
        
    /// The material used in various in-line header or footer views (e.g., by NSTableView).
    NSVisualEffectMaterialHeaderView NS_ENUM_AVAILABLE_MAC(10_14) = 10,
    
    /// The material used as the background of sheet windows.
    NSVisualEffectMaterialSheet NS_ENUM_AVAILABLE_MAC(10_14) = 11,
    
    /// The material used by opaque window backgrounds.
    NSVisualEffectMaterialWindowBackground NS_ENUM_AVAILABLE_MAC(10_14) = 12,
    
    /// The material used as the background of heads-up display (HUD) windows.
    NSVisualEffectMaterialHUDWindow NS_ENUM_AVAILABLE_MAC(10_14) = 13,
    
    /// The material used as the background of full-screen modal UI.
    NSVisualEffectMaterialFullScreenUI NS_ENUM_AVAILABLE_MAC(10_14) = 15,
    
    /// The material used as the background of tool tips.
    NSVisualEffectMaterialToolTip NS_ENUM_AVAILABLE_MAC(10_14) = 17,
    
    /// The material used as the opaque background of content (e.g., by NSScrollView, NSTableView, NSCollectionView, etc.).
    NSVisualEffectMaterialContentBackground NS_ENUM_AVAILABLE_MAC(10_14) = 18,
    
    /// The material used under window backgrounds.
    NSVisualEffectMaterialUnderWindowBackground NS_ENUM_AVAILABLE_MAC(10_14) = 21,
        
    /// The material used as the background behind document pages.
    NSVisualEffectMaterialUnderPageBackground NS_ENUM_AVAILABLE_MAC(10_14) = 22,
    
    /// A default material appropriate for the view's effectiveAppearance.  You should instead choose an appropriate semantic material.
    NSVisualEffectMaterialAppearanceBased NS_ENUM_DEPRECATED_MAC(10_10, API_TO_BE_DEPRECATED, "Use a specific semantic material instead.") = 0,
    
    // Materials with specific looks.  You should instead choose an appropriate semantic material.
    NSVisualEffectMaterialLight NS_ENUM_DEPRECATED_MAC(10_10, API_TO_BE_DEPRECATED, "Use a semantic material instead.  To force the appearance of a view hierarchy, set the `appearance` property to an appropriate NSAppearance value.") = 1,
    NSVisualEffectMaterialDark NS_ENUM_DEPRECATED_MAC(10_10, API_TO_BE_DEPRECATED, "Use a semantic material instead.  To force the appearance of a view hierarchy, set the `appearance` property to an appropriate NSAppearance value.") = 2,
    NSVisualEffectMaterialMediumLight NS_ENUM_DEPRECATED_MAC(10_11, API_TO_BE_DEPRECATED, "Use a semantic material instead.  To force the appearance of a view hierarchy, set the `appearance` property to an appropriate NSAppearance value.") = 8,
    NSVisualEffectMaterialUltraDark NS_ENUM_DEPRECATED_MAC(10_11, API_TO_BE_DEPRECATED, "Use a semantic material instead.  To force the appearance of a view hierarchy, set the `appearance` property to an appropriate NSAppearance value.") = 9,
} NS_AVAILABLE_MAC(10_10);
                
typedef NS_ENUM(NSInteger, NSVisualEffectBlendingMode) {
    /// Blend with the area behind the window (such as the Desktop or other windows).
    NSVisualEffectBlendingModeBehindWindow,
    
    /// Blend with the area behind the view in the window.
    NSVisualEffectBlendingModeWithinWindow,
} NS_AVAILABLE_MAC(10_10);

typedef NS_ENUM(NSInteger, NSVisualEffectState) {
    /// Use the active look only when the containing window is active.
    NSVisualEffectStateFollowsWindowActiveState,
    
    /// Use the active look always.
    NSVisualEffectStateActive,
    
    /// Use the inactive look always.
    NSVisualEffectStateInactive,
} NS_AVAILABLE_MAC(10_10);

NS_CLASS_AVAILABLE_MAC(10_10)
@interface NSVisualEffectView : NSView {
@private
    struct NSVisualEffectViewInternal *_NSVisualEffectViewInternal APPKIT_IVAR;
    
#if !__LP64__
    uint8_t _reserved[36] APPKIT_IVAR;
#endif
    CALayer *_darkenLayer APPKIT_IVAR;
    CALayer *_colorCopyLayer APPKIT_IVAR;
    CALayer *_backdropLayer APPKIT_IVAR;
    NSImage *_maskImage APPKIT_IVAR;
    
    unsigned int _clear:1 APPKIT_IVAR;
    unsigned int _emphasized:1 APPKIT_IVAR;
    unsigned int _appearsDarker:1 APPKIT_IVAR;
    unsigned int _inheritsBlendGroup:1 APPKIT_IVAR;
    unsigned int _needsClearProxy:1 APPKIT_IVAR;
    unsigned int _usesMaterialPreferredAppearance:1 APPKIT_IVAR;
    unsigned int _reservedFlags:26 __unused APPKIT_IVAR;
}

/// A value indicating which material is shown by the NSVisualEffectView.  See the comments on NSVisualEffectMaterial.  Defaults to NSVisualEffectMaterialAppearanceBased.  You should instead specify an appropriate semantic material value.  See the comments on NSVisualEffectMaterial.
@property NSVisualEffectMaterial material;

/// An NSBackgroundStyle value that most closely matches the look of the material shown by the NSVisualEffectView.
@property (readonly) NSBackgroundStyle interiorBackgroundStyle;

/// A value controlling how the NSVisualEffectView generates its material.  See the comments on NSVisualEffectBlendingMode.  Not all materials support both blending modes, so NSVisualEffectView may fall back to a more appropriate blending mode as needed.  Defaults to NSVisualEffectBlendingModeBehindWindow.
@property NSVisualEffectBlendingMode blendingMode;

/// A value controlling when the NSVisualEffectView takes on the active look.  See the comments on NSVisualEffectState.  Defaults to NSVisualEffectStateFollowsWindowActiveState.
@property NSVisualEffectState state;

/// An image whose alpha channel is used to mask the material generated by the NSVisualEffectView.  (It does not also mask subviews.)  Defaults to nil.  It is best to set this to the smallest mask image possible and properly set the image's capInsets property to stretch it.  Setting the maskImage on an NSVisualEffectView that is the contentView of a window will correctly influence the window's shadow.
@property (nullable, retain) NSImage *maskImage;

/// When YES, the material takes on the emphasized look.  Defaults to NO.  Some, but not all, materials change their look when emphasized.  This is used to indicate that an associated view has firstResponder status.
@property (getter=isEmphasized) BOOL emphasized NS_AVAILABLE_MAC(10_12);

// Some things this class overrides.  It is required to call super if you subclass NSVisualEffectView and override these.

- (void)viewDidMoveToWindow NS_REQUIRES_SUPER;
- (void)viewWillMoveToWindow:(nullable NSWindow *)newWindow NS_REQUIRES_SUPER;

@end

NS_ASSUME_NONNULL_END
