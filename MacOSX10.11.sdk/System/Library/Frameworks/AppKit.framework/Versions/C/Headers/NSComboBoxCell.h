/*
	NSComboBoxCell.h
	Application Kit
	Copyright (c) 1996-2015, Apple Inc.
	All rights reserved.
*/

#import <Foundation/NSArray.h>
#import <AppKit/NSTextFieldCell.h>

NS_ASSUME_NONNULL_BEGIN

@class NSButtonCell, NSTableView;
@protocol NSComboBoxCellDataSource;

@interface NSComboBoxCell : NSTextFieldCell   {
    /*All instance variables are private*/
    id _delegate;
    id _dataSource;
    struct __cbcFlags {
        unsigned int usesDataSource:1;
        unsigned int completes:1;
	unsigned int buttonBordered:1;
        unsigned int popUpIsUp:1;
	unsigned int filteringEvents:1;
        unsigned int drawing:1;
        unsigned int synchronizingSelection:1;
        unsigned int reserved:9;
	unsigned int visibleItems:16;
    } _cbcFlags;
    NSButtonCell *_buttonCell;
    NSTableView *_tableView;
    NSScrollView *_scrollView;
    NSWindow *_popUp;
    NSMutableArray *_popUpList;
    __strong NSRect *_cellFrame;
    void *_reserved;
 }

@property BOOL hasVerticalScroller;
@property NSSize intercellSpacing; 
@property CGFloat itemHeight;
@property NSInteger numberOfVisibleItems;

@property (getter=isButtonBordered) BOOL buttonBordered;

- (void)reloadData;
- (void)noteNumberOfItemsChanged;

@property BOOL usesDataSource;

- (void)scrollItemAtIndexToTop:(NSInteger)index;
- (void)scrollItemAtIndexToVisible:(NSInteger)index;

- (void)selectItemAtIndex:(NSInteger)index;
- (void)deselectItemAtIndex:(NSInteger)index;
@property (readonly) NSInteger indexOfSelectedItem;
@property (readonly) NSInteger numberOfItems;

@property BOOL completes;
- (nullable NSString *)completedString:(NSString *)string;

/* These two methods can only be used when usesDataSource is YES */
@property (nullable, assign) id<NSComboBoxCellDataSource> dataSource;

/* These methods can only be used when usesDataSource is NO */
- (void)addItemWithObjectValue:(id)object;
- (void)addItemsWithObjectValues:(NSArray *)objects;
- (void)insertItemWithObjectValue:(id)object atIndex:(NSInteger)index;
- (void)removeItemWithObjectValue:(id)object;
- (void)removeItemAtIndex:(NSInteger)index;
- (void)removeAllItems;
- (void)selectItemWithObjectValue:(nullable id)object;
- (id)itemObjectValueAtIndex:(NSInteger)index;
@property (nullable, readonly, strong) id objectValueOfSelectedItem;
- (NSInteger)indexOfItemWithObjectValue:(id)object;
@property (readonly, copy) NSArray *objectValues;

@end

@protocol NSComboBoxCellDataSource <NSObject>
@optional
/* These two methods are required when not using bindings */
- (NSInteger)numberOfItemsInComboBoxCell:(NSComboBoxCell *)comboBoxCell;
- (id)comboBoxCell:(NSComboBoxCell *)aComboBoxCell objectValueForItemAtIndex:(NSInteger)index;

- (NSUInteger)comboBoxCell:(NSComboBoxCell *)aComboBoxCell indexOfItemWithStringValue:(NSString *)string;
- (nullable NSString *)comboBoxCell:(NSComboBoxCell *)aComboBoxCell completedString:(NSString *)uncompletedString; 
@end

NS_ASSUME_NONNULL_END
