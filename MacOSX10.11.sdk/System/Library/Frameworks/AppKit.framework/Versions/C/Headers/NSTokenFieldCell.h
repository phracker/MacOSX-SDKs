/*
	NSTokenFieldCell.h
	Application Kit
	Copyright (c) 2004-2015, Apple Inc.
	All rights reserved.

*/

#import <AppKit/NSTextFieldCell.h>
#import <Foundation/Foundation.h>


NS_ASSUME_NONNULL_BEGIN

@class NSTextContainer;
@protocol NSTokenFieldCellDelegate;

typedef NS_ENUM(NSUInteger, NSTokenStyle) {
    NSTokenStyleDefault, // This is equivalent to NSTokenStyleRounded. This may change in future releases.
    NSTokenStyleNone, // Style to use for data you want represented as plain-text and without any token background.
    NSTokenStyleRounded, // A token with rounded edges.
    NSTokenStyleSquared NS_ENUM_AVAILABLE_MAC(10_10), // A token with squared edges.
    NSTokenStylePlainSquared NS_ENUM_AVAILABLE_MAC(10_10), // A token with squared edges that has no background unless selected or highlighted.
};

// Deprecated in 10.10. Use the above NSTokenStyles instead.
static const NSTokenStyle NSDefaultTokenStyle = NSTokenStyleDefault;
static const NSTokenStyle NSPlainTextTokenStyle = NSTokenStyleNone;
static const NSTokenStyle NSRoundedTokenStyle = NSTokenStyleRounded;

@interface NSTokenFieldCell : NSTextFieldCell {
@private
    NSCharacterSet *_tokenizingCharacterSet;
    id _delegate;
    NSTimeInterval _completionDelay;
    id _cache;
    id _defaultTerminator;
    id _trackingArea;
    id _lastCell;
    NSRect _lastCellFrame;
    BOOL *_autoCompleteCancel;
    id _reserved[6];
    struct {
        unsigned int _style:4;

        unsigned int _invalidCache:1;
        unsigned int _inDidChange:1;
        unsigned int _validationDisabled:1;
        unsigned int _reserved1:1;
        unsigned int _autoCompleteMode:2;
        unsigned int _inValidateEditing:1;
        unsigned int _performingDrop:1;

        unsigned int _reserved:20;
    } _tfcFlags;
}

/* Sets the default token style used for each new token.  However, if the delegate implements tokenField:styleForRepresentedObject:, that return value will be used instead.
*/
@property NSTokenStyle tokenStyle;

/* Sets the auto-completion delay before the list of possible completions automatically pops up.  Completions are only offered if the delegate implements the completion delegate API.  A negative delay will disable completion while a delay of 0.0 will make completion UI presentation immediate.
*/
@property NSTimeInterval completionDelay;
+ (NSTimeInterval)defaultCompletionDelay;

@property (null_resettable, copy) NSCharacterSet *tokenizingCharacterSet;
+ (NSCharacterSet *)defaultTokenizingCharacterSet;

@property (nullable, assign) id<NSTokenFieldCellDelegate> delegate;

@end

@protocol NSTokenFieldCellDelegate <NSObject>

@optional

// Each element in the array should be an NSString or an array of NSStrings.
// substring is the partial string that is being completed.  tokenIndex is the index of the token being completed.
// selectedIndex allows you to return by reference an index specifying which of the completions should be selected initially. 
// The default behavior is not to have any completions.
- (NSArray *)tokenFieldCell:(NSTokenFieldCell *)tokenFieldCell completionsForSubstring:(NSString *)substring indexOfToken:(NSInteger)tokenIndex indexOfSelectedItem:(NSInteger *)selectedIndex;

// return an array of represented objects you want to add.
// If you want to reject the add, return an empty array.
// returning nil will cause an error.
- (NSArray *)tokenFieldCell:(NSTokenFieldCell *)tokenFieldCell shouldAddObjects:(NSArray *)tokens atIndex:(NSUInteger)index;

// If you return nil or don't implement these delegate methods, we will assume
// editing string = display string = represented object
- (nullable NSString *)tokenFieldCell:(NSTokenFieldCell *)tokenFieldCell displayStringForRepresentedObject:(id)representedObject;
- (nullable NSString *)tokenFieldCell:(NSTokenFieldCell *)tokenFieldCell editingStringForRepresentedObject:(id)representedObject;
- (id)tokenFieldCell:(NSTokenFieldCell *)tokenFieldCell representedObjectForEditingString: (NSString *)editingString;

// We put the string on the pasteboard before calling this delegate method. 
// By default, we write the NSStringPboardType as well as an array of NSStrings.
- (BOOL)tokenFieldCell:(NSTokenFieldCell *)tokenFieldCell writeRepresentedObjects:(NSArray *)objects toPasteboard:(NSPasteboard *)pboard;

// Return an array of represented objects to add to the token field.
- (nullable NSArray *)tokenFieldCell:(NSTokenFieldCell *)tokenFieldCell readFromPasteboard:(NSPasteboard *)pboard;

// By default the tokens have no menu.
- (nullable NSMenu *)tokenFieldCell:(NSTokenFieldCell *)tokenFieldCell menuForRepresentedObject:(id)representedObject;
- (BOOL)tokenFieldCell:(NSTokenFieldCell *)tokenFieldCell hasMenuForRepresentedObject:(id)representedObject; 

// This method allows you to change the style for individual tokens as well as have mixed text and tokens.
- (NSTokenStyle)tokenFieldCell:(NSTokenFieldCell *)tokenFieldCell styleForRepresentedObject:(id)representedObject;

@end

NS_ASSUME_NONNULL_END
