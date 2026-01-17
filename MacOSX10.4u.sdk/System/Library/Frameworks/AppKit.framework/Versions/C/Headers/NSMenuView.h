/*
        NSMenuView.h
        Application Kit
        Copyright (c) 1997-2005, Apple Computer, Inc.
        All rights reserved.
*/

#import <AppKit/NSView.h>
#import <AppKit/AppKitDefines.h>
#import <AppKit/NSMenu.h>
#import <AppKit/NSMenuItem.h>
#import <AppKit/NSMenuItemCell.h>
@class NSScreen;

@interface NSMenuView : NSView {
    /*All instance variables are private*/
    @private
    NSMenu *_menu;
    NSMutableArray *_cells;
    float _stateImageWidth;
    float _imageAndTitleWidth;
    float _keyEquivalentWidth;
    float *_extents;
    unsigned _extentsCapacity;
    int _highlightedItemIndex;
    void *_submenuPopupTimer;
    NSMenuView *_attachedMenuView;
    float _scrollArrowHeight;
    float _maxWinHeight;
    NSFont *_font;
    NSSize _minSize;
    float _horizontalEdgePad;
    void *trackingState;
    id _scrollingView;
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
    } _mvFlags;
}

+ (float)menuBarHeight;

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
- (NSRect)rectOfItemAtIndex:(int)index;
- (int)indexOfItemAtPoint:(NSPoint)point;
- (void)setNeedsDisplayForItemAtIndex:(int)index;

- (void)setHighlightedItemIndex:(int)index;
- (int)highlightedItemIndex;

- (float)stateImageOffset;
- (float)stateImageWidth;
- (float)imageAndTitleOffset;
- (float)imageAndTitleWidth;
- (float)keyEquivalentOffset;
- (float)keyEquivalentWidth;

- (void)setMenuItemCell:(NSMenuItemCell *)cell forItemAtIndex:(int)index;
- (NSMenuItemCell *)menuItemCellForItemAtIndex:(int)index;

- (NSMenuView *)attachedMenuView;

- (void)setNeedsSizing:(BOOL)flag;
- (BOOL)needsSizing;

- (void)sizeToFit;
- (NSMenu *)attachedMenu;
- (BOOL)isAttached;
- (BOOL)isTornOff;
- (NSPoint)locationForSubmenu:(NSMenu *)aSubmenu;

- (void)setWindowFrameForAttachingToRect:(NSRect)screenRect onScreen:(NSScreen *)screen preferredEdge:(NSRectEdge)edge popUpSelectedItem:(int)selectedItemIndex;
- (void)detachSubmenu;
- (void)attachSubmenuForItemAtIndex:(int)index;

- (void)performActionWithHighlightingForItemAtIndex:(int)index;

- (BOOL)trackWithEvent:(NSEvent *)event;

- (float)horizontalEdgePadding;
- (void)setHorizontalEdgePadding:(float)pad;
    // How much empty pad should be left on either edge of the item.

@end
