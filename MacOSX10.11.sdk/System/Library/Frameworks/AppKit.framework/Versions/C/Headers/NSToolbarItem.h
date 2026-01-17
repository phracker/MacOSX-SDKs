/*
	NSToolbarItem.h
	Application Kit
	Copyright (c) 2000-2015, Apple Inc.
	All rights reserved.
*/

#import <AppKit/NSText.h>
#import <AppKit/NSToolbar.h>
#import <AppKit/NSUserInterfaceValidation.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class NSToolbarItemViewer, NSMenuItem, NSView, NSImage;

@interface NSToolbarItem : NSObject <NSCopying, NSValidatedUserInterfaceItem> {
@private
    NSToolbar *		_toolbar;
    NSImage *		_image;
    NSString *		_itemIdentifier;
    
    NSString *		_label;
    NSTextAlignment	_labelAlignment;
    NSString *		_paletteLabel;
    
    NSString *		_toolTip;
    NSMenuItem *	_menuItemRep;
    NSInteger		_tag;
    
    struct __tbiFlags {
	unsigned int viewRespondsToIsEnabled:1;
	unsigned int viewRespondsToSetEnabled:1;
	unsigned int viewRespondsToTag:1;
	unsigned int viewRespondsToSetTag:1;
	unsigned int viewRespondsToAction:1;
	unsigned int viewRespondsToSetAction:1;
	unsigned int viewRespondsToTarget:1;
	unsigned int viewRespondsToSetTarget:1;
        unsigned int viewRespondsToImage:1;
        unsigned int viewRespondsToSetImage:1;
	unsigned int isEnabled:1;
	unsigned int isUserRemovable:1;
	unsigned int menuHasBeenSet:1;
        unsigned int menuRepIsDefault:1;
        unsigned int viewHasBeenLoaded:1;
        unsigned int drawingForDragImage:1;
        unsigned int isCustomItemType:1;
	unsigned int hasValidatedAutoModeConfiguration:1;
	unsigned int useAutoModeConfiguration:1;
        unsigned int fromBaseLocalizedNib:1;
        unsigned int autovalidationDisabled:1;
        unsigned int tagHasBeenSet:1;
	unsigned int sizeHasBeenSet:1;
        unsigned int stateWasDisabledBeforeSheet:1;
        unsigned int wantsToBeCentered:1;

        unsigned int RESERVED:7;
    } _tbiFlags;
    id                  _tbiReserved;
        
    id			_itemViewer;
    NSView *		_view;
    NSSize		_minSize;
    NSSize		_maxSize;
#if __LP64__
    id			_toolbarItemReserved;
#endif
}

/* Initialize the toolbar item with an identifier which is a development language string used by the toolbar and its delegate for identification purposes.  */
- (instancetype)initWithItemIdentifier:(NSString *)itemIdentifier NS_DESIGNATED_INITIALIZER;
@property (readonly, copy) NSString *itemIdentifier;

/* Use this to determine the toolbar in which an item is currently displayed. */
@property (nullable, readonly, assign) NSToolbar *toolbar;

// ----- Setters and Getters -----

/* Use this to set the item's label that appears in the toolbar.  The implication here is that the toolbar will draw the label for the item, and a redraw is triggered by this method.  The toolbar is in charge of the label area.  It is fine for an item to have no toolbar label.  Also, developers should make sure the length of the label is appropriate and not too long.  */
@property (copy) NSString *label;

/* Use this to set the item's label that appears when the item is in the customization palette.  All Items must have a palette label, and for most things it is reasonable to set them to the same string as the label used in the toolbar. */
@property (copy) NSString *paletteLabel;

/* Use this to set a tooltip to be used when the item is displayed in the toolbar.  (forwards to -view if it responds) */
@property (nullable, copy) NSString *toolTip;

/* The menu form of a toolbar item's purpose is twofold.  First, when the window is too small to display an item, it will be clipped but remain accessible from a "clipped items" menu containing the menu item returned here.  Second, in text only mode, the menu returned will be used to create the displayed items.  Singleton menu items will be clickable, while submenu items will be represented as a pull down.  For instance, say you want a button that allows you to switch between modes A, B, and C.  You could represent this as a menu by :  a menu item "mode" with three submenu items "A", "B", and "C".   By default, this method returns a singleton menu item with item label as the title.  For standard items, the target, action is set.  */
@property (nullable, strong) NSMenuItem *menuFormRepresentation;

/* Tag for your own custom purpose. (forwards to -view if it responds) */ 
@property NSInteger tag;

/* Set and get the action of an item. (forwards to -view if it responds) */
@property (nullable, weak) id target;

/* Set and get the action of an item. For custom views, this method will call setAction:/action on the view if it responds. (forwards to -view if it responds) */
@property (nullable) SEL action;

/* Set and get the enabled flag of an item.  For custom views, this method will call setEnabled:/isEnabled on the view if it responds. (forwards to -view if it responds) */
@property (getter=isEnabled) BOOL enabled;

/* Set and get the image of an item.  For custom views, this method will call setImage:/image on the view if it responds. (forwards to -view if it responds) */
@property (nullable, strong) NSImage *image;

/* Use setView: if you want your toolbar item to use something other than the standard.  Note that, by default, many of the set/get methods will be implemented by calls forwarded to the view you set, if it responds to it.  Also, your view must be archivable (in order for the toolbar to make copies of your item to hand off to the config palette). */
@property (nullable, strong) NSView *view;

/* Unless you have already set your own custom view, you should not call this method.  The min size should be small enough to look nice in all display modes. */
@property NSSize minSize;

/* Unless you have set your own custom view, you should not call this method. */
@property NSSize maxSize;


enum {
   NSToolbarItemVisibilityPriorityStandard = 0, // The default visibility priority value.  By default, all items have this priority
   NSToolbarItemVisibilityPriorityLow  = -1000, // A good value to use for items which should be first to fall into the overflow menu
   NSToolbarItemVisibilityPriorityHigh  = 1000, // A good value to use for items you want to stay visible, allowing users to still have highest priority
   NSToolbarItemVisibilityPriorityUser  = 2000  // Value assigned to an item the user wants to "keep visible". You should only use values less than this
};

/* When a toolbar does not have enough space to fit all its items, it must push some into the overflow menu.  Items with the highest visibility priority level are choosen last for the overflow menu.  The default visibilityPriority value is NSToolbarItemVisibilityPriorityStandard.  To suggest that an item always remain visible, give it a value greater than NSToolbarItemVisibilityPriorityStandard, but less than NSToolbarItemVisibilityPriorityUser.   In 10.7, users can no longer modify the toolbar item visibility priority. */
@property NSInteger visibilityPriority;


// ----- Validation of the items -----

/* Typically you should not invoke this method.  This method is called by its toolbar during validation.  Standard items validate themselves by sending the validateToolbarItem: validate message to the current validator.  Since items with custom views don't always have meaningful target/actions, they do nothing.  So for your custom items it may be useful to override this method and invent your own validation. */
- (void)validate;


/* By default NSToolbar automatically invokes its items validate method on a regular basis.  To be in complete control of when the -validate method is invoked, you can disable automatic validation on a per-item basis.  In particular, if your validation code is slow, you may want to do this for performance reasons. */
@property BOOL autovalidates;



// ----- Controlling Duplicates In The Toolbar -----

/* Return YES to allow dragging duplicate items into the toolbar.  By default, if an item with the same identifier is already in the toolbar, dragging in will act as a move of this item.  However, for instance, the separator item drags in as a duplicate always. */
@property (readonly) BOOL allowsDuplicatesInToolbar;

@end


@interface NSObject (NSToolbarItemValidation)

/* NSToolbarItemValidation extends the standard validation idea by introducing this new method which is sent to validators for each visible standard NSToolbarItem with a valid target/action pair.  Note: This message is sent from NSToolbarItem's validate method, however validate will not send this message for items that have custom views. */
- (BOOL)validateToolbarItem:(NSToolbarItem *)theItem;

@end


/* standard toolbar item identifiers */

APPKIT_EXTERN NSString * NSToolbarSeparatorItemIdentifier;
APPKIT_EXTERN NSString * NSToolbarSpaceItemIdentifier;
APPKIT_EXTERN NSString * NSToolbarFlexibleSpaceItemIdentifier;

APPKIT_EXTERN NSString * NSToolbarShowColorsItemIdentifier;        // Shows the color panel.
APPKIT_EXTERN NSString * NSToolbarShowFontsItemIdentifier;         // Shows the font panel.
APPKIT_EXTERN NSString * NSToolbarCustomizeToolbarItemIdentifier;  // Puts the current toolbar into customize mode.
APPKIT_EXTERN NSString * NSToolbarPrintItemIdentifier;             // Sends printDocument: to firstResponder, but you can change this in toolbarWillAddItem: if you need to do so.
APPKIT_EXTERN NSString * NSToolbarToggleSidebarItemIdentifier NS_AVAILABLE_MAC(10_11);  // A standard toolbar item identifier for sidebars. It sends -toggleSidebar: to the firstResponder.

NS_ASSUME_NONNULL_END
