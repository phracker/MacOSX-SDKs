/*
	NSTokenFieldCell.h
	Application Kit
	Copyright (c) 2004-2005, Apple Computer, Inc.
	All rights reserved.

*/

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4

#import <AppKit/NSTextFieldCell.h>
#import <Foundation/Foundation.h>

@class NSTextContainer;

typedef enum NSTokenStyle {
    NSDefaultTokenStyle,             // Style best used for keyword type tokens.  Currently a rounded style, but this may change in future releases.
    NSPlainTextTokenStyle,	     // Style to use for data you want represented as plain-text and without any token background.
    NSRoundedTokenStyle              // Style best used for address type tokens.
} NSTokenStyle;


@interface NSTokenFieldCell : NSTextFieldCell {    
    NSTimeInterval _completionDelay;
    NSTokenStyle _tokenStyle;
    id _delegate;
    NSMutableDictionary *_tokens;
    NSCharacterSet *_tokenizingCharacterSet;
    NSMutableCharacterSet *_fancyTokenizingCharacterSet;
    BOOL _editingText;
    BOOL _lastTextChangeWasSelectionDeletion;
    BOOL _reserved;
    BOOL _editing;
    BOOL _inAutoCompleteTyping;
    BOOL _addingObject;
    id _spotlightedAttachment;
    id _layoutManager;
    NSTextContainer *_textContainer;
    NSRange _editingRange;
    NSMutableArray *_dirtyTokens;
    NSString *_lastTokenizingCharacter;

    unsigned int _insertionGlyphIndexForDrag;
    id _reserved2; 
    id _reserved3;
    id _reserved4;
}

/* Sets the default token style used for each new token.  However, if the delegate implements tokenField:styleForRepresentedObject:, that return value will be used instead.
*/
- (void)setTokenStyle: (NSTokenStyle) style;
- (NSTokenStyle)tokenStyle;

/* Sets the auto-completion delay before the list of possible completions automatically pops up.  Completions are only offered if the delegate implements the completion delegate API.  A negative delay will disable completion while a delay of 0.0 will make completion UI presentation immediate.
*/
- (void)setCompletionDelay: (NSTimeInterval) delay;
- (NSTimeInterval)completionDelay;
+ (NSTimeInterval)defaultCompletionDelay;

- (void)setTokenizingCharacterSet:(NSCharacterSet *)characterSet;
- (NSCharacterSet *)tokenizingCharacterSet;
+ (NSCharacterSet *)defaultTokenizingCharacterSet;

- (void)setDelegate:(id)anObject;
- (id)delegate;

@end

@interface NSObject (NSTokenFieldCellDelegate)
 
// Each element in the array should be an NSString or an array of NSStrings.
// substring is the partial string that is being completed.  tokenIndex is the index of the token being completed.
// selectedIndex allows you to return by reference an index specifying which of the completions should be selected initially. 
// The default behavior is not to have any completions.
- (NSArray *)tokenFieldCell:(NSTokenFieldCell *)tokenFieldCell completionsForSubstring:(NSString *)substring indexOfToken:(int)tokenIndex indexOfSelectedItem: (int *)selectedIndex;

// return an array of represented objects you want to add.
// If you want to reject the add, return an empty array.
// returning nil will cause an error.
- (NSArray *)tokenFieldCell:(NSTokenFieldCell *)tokenFieldCell shouldAddObjects:(NSArray *)tokens atIndex:(unsigned)index;

// If you return nil or don't implement these delegate methods, we will assume
// editing string = display string = represented object
- (NSString *)tokenFieldCell:(NSTokenFieldCell *)tokenFieldCell displayStringForRepresentedObject:(id)representedObject;
- (NSString *)tokenFieldCell:(NSTokenFieldCell *)tokenFieldCell editingStringForRepresentedObject:(id)representedObject;
- (id)tokenFieldCell:(NSTokenFieldCell *)tokenFieldCell representedObjectForEditingString: (NSString *)editingString;

// We put the string on the pasteboard before calling this delegate method. 
// By default, we write the NSStringPboardType as well as an array of NSStrings.
- (BOOL)tokenFieldCell:(NSTokenFieldCell *)tokenFieldCell writeRepresentedObjects:(NSArray *)objects toPasteboard:(NSPasteboard *)pboard;

// Return an array of represented objects to add to the token field.
- (NSArray *)tokenFieldCell:(NSTokenFieldCell *)tokenFieldCell readFromPasteboard:(NSPasteboard *)pboard;

// By default the tokens have no menu.
- (NSMenu *)tokenFieldCell:(NSTokenFieldCell *)tokenFieldCell menuForRepresentedObject:(id)representedObject;
- (BOOL)tokenFieldCell:(NSTokenFieldCell *)tokenFieldCell hasMenuForRepresentedObject:(id)representedObject; 

// This method allows you to change the style for individual tokens as well as have mixed text and tokens.
- (NSTokenStyle)tokenFieldCell:(NSTokenFieldCell *)tokenFieldCell styleForRepresentedObject:(id)representedObject;

@end
#endif
