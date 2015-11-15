/*
	NSComboBox.h
	Application Kit
	Copyright (c) 1996-2015, Apple Inc.
	All rights reserved.
*/

#import <Foundation/NSArray.h>
#import <AppKit/NSTextField.h>

NS_ASSUME_NONNULL_BEGIN

APPKIT_EXTERN NSString * NSComboBoxWillPopUpNotification;
APPKIT_EXTERN NSString * NSComboBoxWillDismissNotification;
APPKIT_EXTERN NSString * NSComboBoxSelectionDidChangeNotification;
APPKIT_EXTERN NSString * NSComboBoxSelectionIsChangingNotification;

@protocol NSComboBoxDelegate, NSComboBoxDataSource;

@interface NSComboBox : NSTextField {
    /*All instance variables are private*/
    id _dataSource;
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

- (nullable id <NSComboBoxDelegate>)delegate;
- (void)setDelegate:(nullable id <NSComboBoxDelegate>)anObject;

/* These two methods can only be used when usesDataSource is YES */
@property (nullable, assign) id<NSComboBoxDataSource> dataSource;

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

@protocol NSComboBoxDataSource <NSObject>
@optional
/* These two methods are required when not using bindings */
- (NSInteger)numberOfItemsInComboBox:(NSComboBox *)aComboBox;
- (id)comboBox:(NSComboBox *)aComboBox objectValueForItemAtIndex:(NSInteger)index;

- (NSUInteger)comboBox:(NSComboBox *)aComboBox indexOfItemWithStringValue:(NSString *)string;
- (nullable NSString *)comboBox:(NSComboBox *)aComboBox completedString:(NSString *)string;
@end

@protocol NSComboBoxDelegate <NSTextFieldDelegate>
@optional

/* Notifications */
- (void)comboBoxWillPopUp:(NSNotification *)notification;
- (void)comboBoxWillDismiss:(NSNotification *)notification;
- (void)comboBoxSelectionDidChange:(NSNotification *)notification;
- (void)comboBoxSelectionIsChanging:(NSNotification *)notification;

@end

NS_ASSUME_NONNULL_END
