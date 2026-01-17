/*
	NSSearchFieldCell.h
	Application Kit
	Copyright (c) 2003-2018, Apple Inc.
	All rights reserved.
 */

#import <Foundation/NSArray.h>
#import <AppKit/NSTextFieldCell.h>
#import <AppKit/NSSearchField.h>

// Search menu template tags. Special items in the search menu are tagged so when the actual dynamic search menu is constructed, we know which items to show or hide.

// Title of recents menu group. Hidden if no recents. Also use for separators that my go away with recents
static const NSInteger NSSearchFieldRecentsTitleMenuItemTag = 1000;

// Recent items have this tag. Use to indicate location of recents in custom menu if no title specified
static const NSInteger NSSearchFieldRecentsMenuItemTag = 1001;

// The 'Clear Recents' item has this tag. Hidden if no recents
static const NSInteger NSSearchFieldClearRecentsMenuItemTag = 1002;

// The item describing a lack of recents uses this tag. Hidden if recents
static const NSInteger NSSearchFieldNoRecentsMenuItemTag = 1003;

NS_ASSUME_NONNULL_BEGIN

@class NSButtonCell, NSMenu, NSMutableArray, NSTimer;

@interface NSSearchFieldCell : NSTextFieldCell {
  @private
    struct __sfFlags {
	unsigned int sendsWholeSearchString:1;
	unsigned int maximumRecents:8;
	unsigned int cancelVisible:1;
	unsigned int reserved2:2;
	unsigned int disableText:1;
	unsigned int menuTracking:1;
	unsigned int deferredUpdate:1;
	unsigned int sendsImmediately:1;
        unsigned int centeredLook:1;
        unsigned int renderingCentered:1;
        unsigned int becomeTransition:1;
        unsigned int resignTransition:1;
        unsigned int subclassOverridesRectForSearchButtonWhenCentered:2;
        unsigned int subclassOverridesRectForSearchTextWhenCentered:2;
        unsigned int subclassOverridesRectForCancelButtonWhenCentered:2;
	unsigned int resumeEditingOnCancel:1;
	unsigned int reserved:5;
    } _sfFlags APPKIT_IVAR;
    NSButtonCell*   _searchButtonCell APPKIT_IVAR;
    NSButtonCell*   _cancelButtonCell APPKIT_IVAR;
    NSMenu*         _searchMenuTemplate APPKIT_IVAR;
    NSString*       _recentsAutosaveName APPKIT_IVAR;
    NSMutableArray* _recentSearches APPKIT_IVAR;
    NSMenu*         _searchMenu APPKIT_IVAR;
    NSTimer*        _partialStringTimer APPKIT_IVAR;
    unsigned int _reserved1 APPKIT_IVAR;
    unsigned int _reserved2 APPKIT_IVAR;
    unsigned int _reserved3 APPKIT_IVAR;
    unsigned int _reserved4 __unused APPKIT_IVAR;
}


- (instancetype)initTextCell:(NSString *)string NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;
- (instancetype)initImageCell:(nullable NSImage *)image NS_UNAVAILABLE;

@property (nullable, strong) NSButtonCell *searchButtonCell;
    // can modify, set or cancel search button.

@property (nullable, strong) NSButtonCell *cancelButtonCell;
    // can modify, set or clear cancel button.

- (void) resetSearchButtonCell;
- (void) resetCancelButtonCell;
    // restore target, action, and image. if cell has been cleared, creates a new cell with default values.

- (NSRect) searchTextRectForBounds:(NSRect)rect;
- (NSRect) searchButtonRectForBounds:(NSRect)rect;
- (NSRect) cancelButtonRectForBounds:(NSRect)rect;
    // for custom layout or to get current sizes

@property (nullable, strong) NSMenu *searchMenuTemplate;
    // set/get search menu template. Menu can use custom tagged items to indicate special items. this menu isn't actually set but used to construct the dynamic search menu. if cleared, then we don't track recents.

@property BOOL sendsWholeSearchString;
    // if clear, send action on each key stroke (after sufficient amount of time so we don't interfere with typing). if set, send only on return/enter or clicking magnifying search button

@property NSInteger maximumRecents;
    // set/get limit max recents. allowable between 0 and 254. setting -1 will use default.

@property (null_resettable, copy) NSArray<NSString *> *recentSearches;
    // if app wants to do custom search lists. will return empty array if no searches

@property (nullable, copy) NSSearchFieldRecentsAutosaveName recentsAutosaveName;
    // must be set to use. default is nil which means no autosave.

@property BOOL sendsSearchStringImmediately;

@end

NS_ASSUME_NONNULL_END

