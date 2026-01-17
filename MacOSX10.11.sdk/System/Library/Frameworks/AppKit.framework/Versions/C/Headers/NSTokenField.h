/*
	NSTokenField.h
	Application Kit
	Copyright (c) 2004-2015, Apple Inc.
	All rights reserved.
*/

#import <AppKit/NSTextContainer.h>
#import <AppKit/NSTextField.h>
#import <AppKit/NSTokenFieldCell.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@protocol NSTokenFieldDelegate;


@interface NSTokenField : NSTextField {    
    BOOL _reserved1;
    BOOL _reserved2;
    BOOL _reserved3;
    BOOL _reserved4;

    NSTrackingRectTag  _trackingRectTag;
    id _reserved5;
    id _reserved6;
    id _reserved7;
}

- (void)setDelegate:(nullable id <NSTokenFieldDelegate>)anObject;
- (nullable id <NSTokenFieldDelegate>)delegate;

/* Sets the default token style used for each new token.  However, if the delegate implements tokenField:styleForRepresentedObject:, that return value will be used instead.
*/
@property NSTokenStyle tokenStyle;

@property NSTimeInterval completionDelay;
+ (NSTimeInterval)defaultCompletionDelay;

@property (null_resettable, copy) NSCharacterSet *tokenizingCharacterSet;
+ (NSCharacterSet *)defaultTokenizingCharacterSet;

@end

@protocol NSTokenFieldDelegate <NSTextFieldDelegate>

@optional

// Each element in the array should be an NSString or an array of NSStrings.
// substring is the partial string that is being completed.  tokenIndex is the index of the token being completed.
// selectedIndex allows you to return by reference an index specifying which of the completions should be selected initially. 
// The default behavior is not to have any completions.
- (nullable NSArray *)tokenField:(NSTokenField *)tokenField completionsForSubstring:(NSString *)substring indexOfToken:(NSInteger)tokenIndex indexOfSelectedItem:(nullable NSInteger *)selectedIndex;

// return an array of represented objects you want to add.
// If you want to reject the add, return an empty array.
// returning nil will cause an error.
- (NSArray *)tokenField:(NSTokenField *)tokenField shouldAddObjects:(NSArray *)tokens atIndex:(NSUInteger)index;

// If you return nil or don't implement these delegate methods, we will assume
// editing string = display string = represented object
- (nullable NSString *)tokenField:(NSTokenField *)tokenField displayStringForRepresentedObject:(id)representedObject;
- (nullable NSString *)tokenField:(NSTokenField *)tokenField editingStringForRepresentedObject:(id)representedObject;
- (id)tokenField:(NSTokenField *)tokenField representedObjectForEditingString: (NSString *)editingString;

// We put the string on the pasteboard before calling this delegate method. 
// By default, we write the NSStringPboardType as well as an array of NSStrings.
- (BOOL)tokenField:(NSTokenField *)tokenField writeRepresentedObjects:(NSArray *)objects toPasteboard:(NSPasteboard *)pboard;

// Return an array of represented objects to add to the token field.
- (nullable NSArray *)tokenField:(NSTokenField *)tokenField readFromPasteboard:(NSPasteboard *)pboard;

// By default the tokens have no menu.
- (nullable NSMenu *)tokenField:(NSTokenField *)tokenField menuForRepresentedObject:(id)representedObject;
- (BOOL)tokenField:(NSTokenField *)tokenField hasMenuForRepresentedObject:(id)representedObject; 

// This method allows you to change the style for individual tokens as well as have mixed text and tokens.
- (NSTokenStyle)tokenField:(NSTokenField *)tokenField styleForRepresentedObject:(id)representedObject;


@end

NS_ASSUME_NONNULL_END
