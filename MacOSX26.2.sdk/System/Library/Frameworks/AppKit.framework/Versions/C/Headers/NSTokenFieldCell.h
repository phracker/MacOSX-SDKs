/*
	NSTokenFieldCell.h
	Application Kit
	Copyright (c) 2004-2024, Apple Inc.
	All rights reserved.

*/

#import <AppKit/NSTextFieldCell.h>
#import <AppKit/AppKitDefines.h>
#import <Foundation/Foundation.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)
APPKIT_API_UNAVAILABLE_BEGIN_MACCATALYST

@class NSTextContainer;
@protocol NSTokenFieldCellDelegate;

typedef NS_ENUM(NSUInteger, NSTokenStyle) {
    NSTokenStyleDefault, // This is equivalent to NSTokenStyleRounded. This may change in future releases.
    NSTokenStyleNone, // Style to use for data you want represented as plain-text and without any token background.
    NSTokenStyleRounded, // A token with rounded edges.
    NSTokenStyleSquared API_AVAILABLE(macos(10.10)), // A token with squared edges.
    NSTokenStylePlainSquared API_AVAILABLE(macos(10.10)), // A token with squared edges that has no background unless selected or highlighted.
};

@interface NSTokenFieldCell : NSTextFieldCell

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

/// Allows the delegate to provide an array of appropriate completions for the contents of the receiver
/// @param tokenFieldCell The token field cell where editing is occurring
/// @param substring The partial string that is being completed
/// @param tokenIndex The index of the token being completed
/// @param selectedIndex Optionally, you can return by reference an index into the returned array that specifies which of the completions should be initially selected. If none are to be selected, return by reference `-1`.
/// @return An array of strings (`NSString`) that are possible completions
/// @discussion If the delegate does not implement this method, no completions are provided
- (NSArray *)tokenFieldCell:(NSTokenFieldCell *)tokenFieldCell completionsForSubstring:(NSString *)substring indexOfToken:(NSInteger)tokenIndex indexOfSelectedItem:(NSInteger *)selectedIndex NS_SWIFT_UI_ACTOR;

// return an array of represented objects you want to add.
// If you want to reject the add, return an empty array.
// returning nil will cause an error.
- (NSArray *)tokenFieldCell:(NSTokenFieldCell *)tokenFieldCell shouldAddObjects:(NSArray *)tokens atIndex:(NSUInteger)index NS_SWIFT_UI_ACTOR;

// If you return nil or don't implement these delegate methods, we will assume
// editing string = display string = represented object
- (nullable NSString *)tokenFieldCell:(NSTokenFieldCell *)tokenFieldCell displayStringForRepresentedObject:(id)representedObject NS_SWIFT_UI_ACTOR;
- (nullable NSString *)tokenFieldCell:(NSTokenFieldCell *)tokenFieldCell editingStringForRepresentedObject:(id)representedObject NS_SWIFT_UI_ACTOR;
- (nullable id)tokenFieldCell:(NSTokenFieldCell *)tokenFieldCell representedObjectForEditingString: (NSString *)editingString NS_SWIFT_UI_ACTOR;

// We put the string on the pasteboard before calling this delegate method. 
// By default, we write the NSStringPboardType as well as an array of NSStrings.
- (BOOL)tokenFieldCell:(NSTokenFieldCell *)tokenFieldCell writeRepresentedObjects:(NSArray *)objects toPasteboard:(NSPasteboard *)pboard NS_SWIFT_UI_ACTOR;

// Return an array of represented objects to add to the token field.
- (nullable NSArray *)tokenFieldCell:(NSTokenFieldCell *)tokenFieldCell readFromPasteboard:(NSPasteboard *)pboard NS_SWIFT_UI_ACTOR;

// By default the tokens have no menu.
- (nullable NSMenu *)tokenFieldCell:(NSTokenFieldCell *)tokenFieldCell menuForRepresentedObject:(id)representedObject NS_SWIFT_UI_ACTOR;
- (BOOL)tokenFieldCell:(NSTokenFieldCell *)tokenFieldCell hasMenuForRepresentedObject:(id)representedObject NS_SWIFT_UI_ACTOR;

// This method allows you to change the style for individual tokens as well as have mixed text and tokens.
- (NSTokenStyle)tokenFieldCell:(NSTokenFieldCell *)tokenFieldCell styleForRepresentedObject:(id)representedObject NS_SWIFT_UI_ACTOR;

@end

static const NSTokenStyle NSDefaultTokenStyle API_DEPRECATED_WITH_REPLACEMENT("NSTokenStyleDefault", macos(10.0,10.14)) = NSTokenStyleDefault;
static const NSTokenStyle NSPlainTextTokenStyle API_DEPRECATED_WITH_REPLACEMENT("NSTokenStyleNone", macos(10.0,10.14)) = NSTokenStyleNone;
static const NSTokenStyle NSRoundedTokenStyle API_DEPRECATED_WITH_REPLACEMENT("NSTokenStyleRounded", macos(10.0,10.14)) = NSTokenStyleRounded;

API_UNAVAILABLE_END
NS_HEADER_AUDIT_END(nullability, sendability)
