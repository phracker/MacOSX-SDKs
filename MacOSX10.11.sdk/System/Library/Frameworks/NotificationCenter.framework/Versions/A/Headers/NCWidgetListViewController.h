/*
 * NCWidgetListViewController.h
 * NotificationCenter.framework
 * Copyright (c) 2014 Apple Inc. All rights reserved.
 */

#import <AppKit/AppKit.h>

@protocol NCWidgetListViewDelegate;


NS_CLASS_AVAILABLE_MAC(10_10)
@interface NCWidgetListViewController : NSViewController

@property (weak) IBOutlet id<NCWidgetListViewDelegate> delegate;

/* Set the contents array in order to provide contents for display in the list
   view. The list view controller will request a new content view controller
   for each object in the array, and set the representedObject of the newly
   created content view controller accordingly.
 
   As an optimization, when resetting contents, the list view controller may
   re-use content view controllers for identical objects already in contents. */
@property (copy) NSArray *contents;

/* The minimum number of visible rows to display. When this property is set and
   the count of contetns is greater than this number, the list view controller
   will show this number fo rows with a "Show More…" button.
   This property is unset (zero) by default. */
@property (assign) NSUInteger minimumVisibleRowCount;

/* Defaults to YES. Display divider lines between rows. */
@property (assign) BOOL hasDividerLines;

/* Set to YES to put the list view controller into editing mode which
   (optionally) displays row reordering and delete controls. */
@property (assign) BOOL editing;

/* Defaults to YES. Show a (+) button for adding new content while editing.
   The button's action will send the widgetListPerformAddAction: message to
   the delegate. */
@property (assign) BOOL showsAddButtonWhenEditing;

/* Returns an existing content view controller for the given row or creates
   one if necessary by calling the delegate's widgetList:viewControllerForRow:
   method. */
- (NSViewController *)viewControllerAtRow:(NSUInteger)row makeIfNecessary:(BOOL)makeIfNecesary;

/* Returns the row represented by the given content view controller. */
- (NSUInteger)rowForViewController:(NSViewController *)viewController;

@end


@protocol NCWidgetListViewDelegate <NSObject>

/* Required delegate method to create new content view controllers. */
- (NSViewController *)widgetList:(NCWidgetListViewController *)list viewControllerForRow:(NSUInteger)row;

@optional

/* Optional delegate method to implement an action for the (+) button when
   visible in editing mode.
 
   To use the default search view, instantiate an NCWidgetSearchViewController
   and present it on the widget's principal view controller using
   presentViewControllerInWidget: */
- (void)widgetListPerformAddAction:(NCWidgetListViewController *)list;


/* Optional delegate methods to allow reordering of list content.
   No reordering is allowed if not implemented.

   The reordering will be immediately reflected in the list view controller's
   contents array before widgetList:didReorderRow:toRow: is called. */
- (BOOL)widgetList:(NCWidgetListViewController *)list shouldReorderRow:(NSUInteger)row;
- (void)widgetList:(NCWidgetListViewController *)list didReorderRow:(NSUInteger)row toRow:(NSUInteger)newIndex;


/* Optional delegate methods to allow deleting list content.
   No deletion is allowed if not implemented.

   The deletion will be immediately reflected in the list view controller's
   contents array before widgetList:didRemoveRow: is called. */
- (BOOL)widgetList:(NCWidgetListViewController *)list shouldRemoveRow:(NSUInteger)row;
- (void)widgetList:(NCWidgetListViewController *)list didRemoveRow:(NSUInteger)row;

@end
