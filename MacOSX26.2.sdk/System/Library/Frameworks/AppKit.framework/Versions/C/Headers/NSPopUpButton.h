/*
        NSPopUpButton.h
        Application Kit
        Copyright (c) 1997-2024, Apple Inc.
        All rights reserved.
*/

#import <Foundation/NSArray.h>
#import <AppKit/NSButton.h>
#import <AppKit/NSPopUpButtonCell.h>
#import <AppKit/NSMenuItem.h>
#import <AppKit/AppKitDefines.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)
APPKIT_API_UNAVAILABLE_BEGIN_MACCATALYST

@class NSMenu;

@interface NSPopUpButton : NSButton

/*!
 Creates a standard pop-up button with a menu, target, and action.
 @param menu A menu presented by the pop-up button, containing items that the user can choose between.
 @param target The target object that receives action messages from the control.
 @param action The action message sent by the control.
 @discussion If `menu` is non-empty, the pop-up button uses the first item for its initial selection.
 @return An initialized pop-up button object.
 */
+ (instancetype)popUpButtonWithMenu:(NSMenu *)menu target:(nullable id)target action:(nullable SEL)action NS_REFINED_FOR_SWIFT API_AVAILABLE(macos(15.0));

/*!
 Creates a standard pull-down button with a title and menu.
 @param title The localized title string that is displayed on the button.
 @param menu The pull-down menu to present when interacting with the button.
 @discussion Pull-down buttons created using this method have the `usesItemFromMenu` property set to `NO`.
 @return An initialized pull-down button object.
 */
+ (instancetype)pullDownButtonWithTitle:(NSString *)title menu:(NSMenu *)menu NS_REFINED_FOR_SWIFT API_AVAILABLE(macos(15.0));

/*!
 Creates a standard pull-down button with an image and menu.
 @param image The icon that is displayed on the button.
 @param menu The pull-down menu to present when interacting with the button.
 @discussion Pull-down buttons created using this method have the `usesItemFromMenu` property set to `NO`.
 @return An initialized pull-down button object.
 */
+ (instancetype)pullDownButtonWithImage:(NSImage *)image menu:(NSMenu *)menu NS_REFINED_FOR_SWIFT API_AVAILABLE(macos(15.0));

/*!
 Creates a standard pull-down button with a title, image, and menu.
 @param title The localized title string that is displayed on the button.
 @param image The icon that is displayed on the button.
 @param menu The pull-down menu to present when interacting with the button.
 @discussion Pull-down buttons created using this method have the `usesItemFromMenu` property set to `NO`.
 @return An initialized pull-down button object.
 */
+ (instancetype)pullDownButtonWithTitle:(NSString *)title image:(NSImage *)image menu:(NSMenu *)menu NS_REFINED_FOR_SWIFT API_AVAILABLE(macos(15.0));

- (instancetype)initWithFrame:(NSRect)buttonFrame pullsDown:(BOOL)flag;

#pragma mark Configuration

/*! The menu that is presented by the popup button. This overrides the inherited NSView property and replaces NSView's standard context menu behavior. */
@property (nullable, strong) NSMenu *menu;

/*! When the value of this property is `YES` the button adopts 'pull-down' behavior, displaying static button contents and presenting its menu at the edge of the button. When the value of this property is `NO` the button behaves as a popup, displaying the currently-selected menu item and presenting its menu above the button, positioning the selected menu item to match the button's contents. */
@property BOOL pullsDown;

/*! When the value of this property is `YES`, the popup button automatically enables and disables its menu items according to the `NSMenuValidation` protocol prior to user interaction. */
@property BOOL autoenablesItems;

/*! For pull-down buttons and for popups under severe screen position restrictions, this property specifies the edge of the control that the menu should present from. */
@property NSRectEdge preferredEdge;

/*! When `usesItemFromMenu` is `YES`, a pull-down button uses the title of the first menu item and hides the first menu item. A pop-up button uses the title of the currently selected menu. The default value is `YES`. */
@property BOOL usesItemFromMenu API_AVAILABLE(macos(15.0));

/*! When the value of this property is `YES`, the selected menu item's `state` is set to `NSControlStateValueOn`. When the value of this property is `NO`, the menu item's `state` is not changed. When this property changes, the `state` of the currently selected item is updated appropriately. This property is ignored for pull-down buttons. */
@property BOOL altersStateOfSelectedItem API_AVAILABLE(macos(15.0));

#pragma mark Adding and Removing Items

- (void)addItemWithTitle:(NSString *)title;
- (void)addItemsWithTitles:(NSArray<NSString *> *)itemTitles;
- (void)insertItemWithTitle:(NSString *)title atIndex:(NSInteger)index;

- (void)removeItemWithTitle:(NSString *)title;
- (void)removeItemAtIndex:(NSInteger)index;
- (void)removeAllItems;

#pragma mark Accessing Items

@property (readonly, copy) NSArray<NSMenuItem *> *itemArray;
@property (readonly) NSInteger numberOfItems;

- (NSInteger)indexOfItem:(NSMenuItem *)item;
- (NSInteger)indexOfItemWithTitle:(NSString *)title;
- (NSInteger)indexOfItemWithTag:(NSInteger)tag;
- (NSInteger)indexOfItemWithRepresentedObject:(nullable id)obj;
- (NSInteger)indexOfItemWithTarget:(nullable id)target andAction:(nullable SEL)actionSelector;

- (nullable NSMenuItem *)itemAtIndex:(NSInteger)index;
- (nullable NSMenuItem *)itemWithTitle:(NSString *)title;
@property (nullable, readonly, strong) NSMenuItem *lastItem;

#pragma mark Selecting Items

- (void)selectItem:(nullable NSMenuItem *)item;
- (void)selectItemAtIndex:(NSInteger)index;
- (void)selectItemWithTitle:(NSString *)title;
- (BOOL)selectItemWithTag:(NSInteger)tag;
- (void)setTitle:(NSString *)string;

@property (nullable, readonly, strong) NSMenuItem *selectedItem;
@property (readonly) NSInteger indexOfSelectedItem;
@property (readonly) NSInteger selectedTag;
- (void)synchronizeTitleAndSelectedItem;

#pragma mark Item Title Conveniences

- (NSString *)itemTitleAtIndex:(NSInteger)index;
@property (readonly, copy) NSArray<NSString *> *itemTitles;
@property (nullable, readonly, copy) NSString *titleOfSelectedItem;

@end

APPKIT_EXTERN NSNotificationName NSPopUpButtonWillPopUpNotification;

API_UNAVAILABLE_END
NS_HEADER_AUDIT_END(nullability, sendability)
