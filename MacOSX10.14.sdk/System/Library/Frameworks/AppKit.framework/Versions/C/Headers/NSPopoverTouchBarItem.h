/*
 NSPopoverTouchBarItem.h
 Application Kit
 Copyright (c) 2015-2018, Apple Inc.
 All rights reserved.
*/

#import <AppKit/NSTouchBarItem.h>

NS_ASSUME_NONNULL_BEGIN

NS_CLASS_AVAILABLE_MAC(10_12_2)
@interface NSPopoverTouchBarItem : NSTouchBarItem {
@private
    NSTouchBar *_popoverTouchBar APPKIT_IVAR;
    NSTouchBar *_pressAndHoldTouchBar APPKIT_IVAR;
    
    id _overlay APPKIT_IVAR;
    
    NSString *_customizationLabel APPKIT_IVAR;
    
    NSView *_collapsedRepresentation APPKIT_IVAR;
    
    NSImage *_collapsedRepresentationImage APPKIT_IVAR;
    NSString *_collapsedRepresentationLabel APPKIT_IVAR;
    
    unsigned _showsCloseButton:1 APPKIT_IVAR;
    unsigned _showsControlStrip:1 APPKIT_IVAR;
    unsigned _collapsedRepresentationChevronBehavior:2 APPKIT_IVAR;
#if !__OBJC2__
    unsigned _popoverTouchBarItemReservedFlags: 28 __unused APPKIT_IVAR;
    void *_popoverTouchBarItemReserved[3] __unused APPKIT_IVAR;
#endif /* !__OBJC2__ */
}

/*
    The NSTouchBar displayed when this item is "popped." By default this is an empty bar that cannot be customized. This property is archived.
*/
@property (strong) NSTouchBar *popoverTouchBar;

/*
    The localized string labelling this item during user customization. The default value is the empty string. This property is archived.
*/
@property (readwrite, copy, null_resettable) NSString *customizationLabel;

/*
    The view displayed when the item is in its hosted NSTouchBar. By default, this is an NSButton whose target is this popover item, whose action is showPopover:, and whose image and title are bound to this item's collapsedRepresentationImage and collapsedRepresentationLabel respectively. This property is archived.
*/
@property (strong) __kindof NSView *collapsedRepresentation;

/*
    The image displayed by the button used by default for the default collapsed representation. If the collapsedRepresentation button has been replaced by a different view, this property may not have any effect. This property is archived.
*/
@property (strong, nullable) NSImage *collapsedRepresentationImage;

/*
    The localized string displayed by the button used by default for the default collapsed representation. If the collapsedRepresentation button has been replaced by a different view, this property may not have any effect. This property is archived.
*/
@property (strong) NSString *collapsedRepresentationLabel;

/*
    An NSTouchBar to be used exclusively for press-and-hold popovers. This NSTouchBar can be the same as the one used for "popoverTouchBar" property, but does not have to be. When non-nil this NSTouchBar will be displayed while the user holds their finger down on the collapsed representation and released when the user raises their finger. This tracking behavior is automatic, but popovers with custom collapsed representations will still need to send -showPopover: to start tracking.

    This property is archived.
*/
@property (strong, nullable) NSTouchBar *pressAndHoldTouchBar;

/*
    When YES, automatically displays a close button in the popover. When NO it is the responsibility of the client to dismiss the popover.
*/
@property BOOL showsCloseButton;

/*
    Replaces the main NSTouchBar with this item's popover NSTouchBar. If this item is not visible, this method will have no effect. If this item ceases to be visible, the popover NSTouchBar will automatically be ordered out.
*/
- (void)showPopover:(nullable id)sender;

/*
    This method will restore the previously visible main NSTouchBar. This method can be invoked explicitly to order out a popover if interacting with an item inside it should close it.
*/
- (void)dismissPopover:(nullable id)sender;

/* 
    Returns a new gesture recognizer, already wired up to send this popover -showPopover:. It is the callers responsibility to attach this GR to a custom collapsedRepresentation view 
*/
- (NSGestureRecognizer *)makeStandardActivatePopoverGestureRecognizer;
@end

NS_ASSUME_NONNULL_END
