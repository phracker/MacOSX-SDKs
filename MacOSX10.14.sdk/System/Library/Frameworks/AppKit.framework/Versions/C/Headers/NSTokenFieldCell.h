/*
	NSTokenFieldCell.h
	Application Kit
	Copyright (c) 2004-2018, Apple Inc.
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

@interface NSTokenFieldCell : NSTextFieldCell {
@private
    NSCharacterSet *_tokenizingCharacterSet APPKIT_IVAR;
    __weak id _delegate APPKIT_IVAR;
    NSTimeInterval _completionDelay APPKIT_IVAR;
    id _cache APPKIT_IVAR;
    id _defaultTerminator APPKIT_IVAR;
    id _trackingArea APPKIT_IVAR;
    id _lastCell APPKIT_IVAR;
    NSRect _lastCellFrame APPKIT_IVAR;
    BOOL *_autoCompleteCancel APPKIT_IVAR;
    id _reserved[6] __unused APPKIT_IVAR;
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
    } _tfcFlags APPKIT_IVAR;
}

/* Sets the default token style used for each new token.  However, if the delegate implements tokenField:styleForRepresentedObject:, that return value will be used instead.
*/
@property NSTokenStyle tokenStyle;

/* Sets the auto-completion delay before the list of possible completions automatically pops up.  Completions are only offered if the delegate implements the completion delegate API.  A negative delay will disable completion while a delay of 0.0 will make completion UI presentation immediate.
*/
@property NSTimeInterval completionDelay;
@property (class, readonly) NSTimeInterval defaultCompletionDelay;

@property (null_resettable, copy) NSCharacterSet *tokenizingCharacterSet;
@property (class, readonly, copy) NSCharacterSet *defaultTokenizingCharacterSet;

@property (nullable, weak) id<NSTokenFieldCellDelegate> delegate;

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
- (nullable id)tokenFieldCell:(NSTokenFieldCell *)tokenFieldCell representedObjectForEditingString: (NSString *)editingString;

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

static const NSTokenStyle NSDefaultTokenStyle NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSTokenStyleDefault", 10_0, 10_14) = NSTokenStyleDefault;
static const NSTokenStyle NSPlainTextTokenStyle NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSTokenStyleNone", 10_0, 10_14) = NSTokenStyleNone;
static const NSTokenStyle NSRoundedTokenStyle NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSTokenStyleRounded", 10_0, 10_14) = NSTokenStyleRounded;

NS_ASSUME_NONNULL_END
