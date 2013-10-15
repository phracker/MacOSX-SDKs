/*
	NSTokenField.h
	Application Kit
	Copyright (c) 2004-2005, Apple Computer, Inc.
	All rights reserved.
*/

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4

#import <Foundation/Foundation.h>
#import <AppKit/NSTokenFieldCell.h>
#import <AppKit/NSTextContainer.h>
#import <AppKit/NSTextField.h>


@interface NSTokenField : NSTextField {    
    BOOL _reserved1;
    BOOL _reserved2;
    BOOL _reserved3;
    BOOL _reserved4;

    int  _trackingRectTag;
    id _reserved5;
    id _reserved6;
    id _reserved7;
}

/* Sets the default token style used for each new token.  However, if the delegate implements tokenField:styleForRepresentedObject:, that return value will be used instead.
*/
- (void)setTokenStyle: (NSTokenStyle) style;
- (NSTokenStyle)tokenStyle;

- (void)setCompletionDelay: (NSTimeInterval) delay;
- (NSTimeInterval)completionDelay;
+ (NSTimeInterval)defaultCompletionDelay;

- (void)setTokenizingCharacterSet:(NSCharacterSet *)characterSet;
- (NSCharacterSet *)tokenizingCharacterSet;
+ (NSCharacterSet *)defaultTokenizingCharacterSet;

@end

@interface NSObject (NSTokenFieldDelegate)
 
// Each element in the array should be an NSString or an array of NSStrings.
// substring is the partial string that is being completed.  tokenIndex is the index of the token being completed.
// selectedIndex allows you to return by reference an index specifying which of the completions should be selected initially. 
// The default behavior is not to have any completions.
- (NSArray *)tokenField:(NSTokenField *)tokenField completionsForSubstring:(NSString *)substring indexOfToken:(int)tokenIndex indexOfSelectedItem: (int *)selectedIndex;

// return an array of represented objects you want to add.
// If you want to reject the add, return an empty array.
// returning nil will cause an error.
- (NSArray *)tokenField:(NSTokenField *)tokenField shouldAddObjects:(NSArray *)tokens atIndex:(unsigned)index;

// If you return nil or don't implement these delegate methods, we will assume
// editing string = display string = represented object
- (NSString *)tokenField:(NSTokenField *)tokenField displayStringForRepresentedObject:(id)representedObject;
- (NSString *)tokenField:(NSTokenField *)tokenField editingStringForRepresentedObject:(id)representedObject;
- (id)tokenField:(NSTokenField *)tokenField representedObjectForEditingString: (NSString *)editingString;

// We put the string on the pasteboard before calling this delegate method. 
// By default, we write the NSStringPboardType as well as an array of NSStrings.
- (BOOL)tokenField:(NSTokenField *)tokenField writeRepresentedObjects:(NSArray *)objects toPasteboard:(NSPasteboard *)pboard;

// Return an array of represented objects to add to the token field.
- (NSArray *)tokenField:(NSTokenField *)tokenField readFromPasteboard:(NSPasteboard *)pboard;

// By default the tokens have no menu.
- (NSMenu *)tokenField:(NSTokenField *)tokenField menuForRepresentedObject:(id)representedObject;
- (BOOL)tokenField:(NSTokenField *)tokenField hasMenuForRepresentedObject:(id)representedObject; 

// This method allows you to change the style for individual tokens as well as have mixed text and tokens.
- (NSTokenStyle)tokenField:(NSTokenField *)tokenField styleForRepresentedObject:(id)representedObject;

@end
#endif
