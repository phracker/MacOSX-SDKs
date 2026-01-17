/*
        NSMenuView.h
        Application Kit
        Copyright (c) 1997-2018, Apple Inc.
        All rights reserved.
*/

/* old-style menus are not available on 64-bit */
#if ! __LP64__

#import <AppKit/NSView.h>
#import <AppKit/AppKitDefines.h>
#import <AppKit/NSMenu.h>
#import <AppKit/NSMenuItem.h>
#import <AppKit/NSMenuItemCell.h>
@class NSScreen;

NS_AUTOMATED_REFCOUNT_WEAK_UNAVAILABLE
@interface NSMenuView : NSView {
    /*All instance variables are private*/
    @private
    NSMenu *_menu APPKIT_IVAR;
    NSMutableArray *_cells APPKIT_IVAR;
    CGFloat _stateImageWidth APPKIT_IVAR;
    CGFloat _imageAndTitleWidth APPKIT_IVAR;
    CGFloat _keyEquivalentWidth APPKIT_IVAR;
    CGFloat *_extents APPKIT_IVAR;
    unsigned _extentsCapacity APPKIT_IVAR;
    int _highlightedItemIndex APPKIT_IVAR;
    BOOL *_submenuPopupCancel APPKIT_IVAR;
    NSMenuView *_attachedMenuView APPKIT_IVAR;
    CGFloat _scrollArrowHeight APPKIT_IVAR;
    CGFloat _maxWinHeight APPKIT_IVAR;
    NSFont *_font APPKIT_IVAR;
    NSSize _minSize APPKIT_IVAR;
    CGFloat _horizontalEdgePad APPKIT_IVAR;
    void *trackingState APPKIT_IVAR;
    id _scrollingView APPKIT_IVAR;
    struct __mvFlags {
        unsigned int needsSizing:1;
        unsigned int releasingWindow:1;
        unsigned int isHorizontal:1;
        unsigned int disableSizing:1;
        unsigned int attachedSubmenuWhileMouseWasUp:1;
        unsigned int needsToCreateCells:1;
        unsigned int allowsTearOffs:1;
        unsigned int isTearOff:1;
        unsigned int keyEquivGlyphWidth:16;
        unsigned int disableResize:1;
        unsigned int savedHODState:1;
        unsigned int drawCenter:1;
        unsigned int RESERVED:5;
    } _mvFlags APPKIT_IVAR;
}

+ (CGFloat)menuBarHeight;

- (id)initWithFrame:(NSRect)frame;  // DI
- (id)initAsTearOff;

- (void)setMenu:(NSMenu *)menu;
- (NSMenu *)menu;

- (void)itemChanged:(NSNotification *)notification;
- (void)itemAdded:(NSNotification *)notification;
- (void)itemRemoved:(NSNotification *)notification;

- (void)update;

- (void)setHorizontal:(BOOL)flag;
- (BOOL)isHorizontal;

- (void)setFont:(NSFont *)font;
- (NSFont *)font;

- (NSRect)innerRect; // inside the bezel (if any)
- (NSRect)rectOfItemAtIndex:(NSInteger)index;
- (NSInteger)indexOfItemAtPoint:(NSPoint)point;
- (void)setNeedsDisplayForItemAtIndex:(NSInteger)index;

- (void)setHighlightedItemIndex:(NSInteger)index;
- (NSInteger)highlightedItemIndex;

- (CGFloat)stateImageOffset;
- (CGFloat)stateImageWidth;
- (CGFloat)imageAndTitleOffset;
- (CGFloat)imageAndTitleWidth;
- (CGFloat)keyEquivalentOffset;
- (CGFloat)keyEquivalentWidth;

- (void)setMenuItemCell:(NSMenuItemCell *)cell forItemAtIndex:(NSInteger)index;
- (NSMenuItemCell *)menuItemCellForItemAtIndex:(NSInteger)index;

- (NSMenuView *)attachedMenuView;

- (void)setNeedsSizing:(BOOL)flag;
- (BOOL)needsSizing;

- (void)sizeToFit;
- (NSMenu *)attachedMenu;
- (BOOL)isAttached;
- (BOOL)isTornOff;
- (NSPoint)locationForSubmenu:(NSMenu *)submenu;

- (void)setWindowFrameForAttachingToRect:(NSRect)screenRect onScreen:(NSScreen *)screen preferredEdge:(NSRectEdge)edge popUpSelectedItem:(NSInteger)selectedItemIndex;
- (void)detachSubmenu;
- (void)attachSubmenuForItemAtIndex:(NSInteger)index;

- (void)performActionWithHighlightingForItemAtIndex:(NSInteger)index;

- (BOOL)trackWithEvent:(NSEvent *)event;

- (CGFloat)horizontalEdgePadding;
- (void)setHorizontalEdgePadding:(CGFloat)pad;
    // How much empty pad should be left on either edge of the item.

@end

#endif
