#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UISearchTextField.h>)
//
//  UISearchTextField.h
//  UIKit
//
//  Copyright (c) 2019 Apple Inc. All rights reserved.
//

#import <UIKit/UITextField.h>
#import <UIKit/UITextPasteDelegate.h>
#import <UIKit/UIKitDefines.h>

#if TARGET_OS_IOS

NS_ASSUME_NONNULL_BEGIN

@class UISearchToken;
@protocol UISearchTextFieldDelegate;

/// UISearchTextField is the subclass of UITextField used in UISearchBar, and can also be used elsewhere (e.g. as the titleView of a UINavigationItem).
///
/// In addition to its text, a UISearchField can contain tokens. Tokens are discrete representations of non-textual content. Your app might use tokens to represent filters that are being applied in conjunction with the search field’s text. Tokens are always created by the application, and always occur contiguously before the search field’s text.
///
/// @note
/// Because the system drives selection and keyboard behaviors through the UITextInput protocol, and UISearchTextField supports selecting tokens, UISearchTextField assigns UITextPositions to tokens as well as text. If the current selection includes any tokens, their positions are part of the range returned by `UISearchTextField.selectedTextRange`. Use the `textualRange` property to obtain the range of the text field that excludes any tokens.
///
/// Tokens can be programatically selected by including their position in a range assigned to the `selectedTextRange` property. UISearchTextField does not support placing an insertion point before a token; attempting to do so will select the token instead.
UIKIT_CLASS_AVAILABLE_IOS_ONLY(13.0)
@interface UISearchTextField : UITextField

#pragma mark Search tokens

/// Simple access to the collection of tokens.
@property (nonatomic, copy) NSArray<UISearchToken *> *tokens;
- (void)insertToken:(UISearchToken *)token atIndex:(NSInteger)tokenIndex;
- (void)removeTokenAtIndex:(NSInteger)tokenIndex;

/// Returns the position of the provided token. To select a token, assign a UITextRange containing its position to the selectedTextRange property.
- (UITextPosition *)positionOfTokenAtIndex:(NSInteger)tokenIndex;

/// Returns the tokens which are contained within the provided range.
///
/// You can use this method to determine which tokens are included in the user’s current selection. The range may span more than one token or a mixture of tokens and text.
- (NSArray<UISearchToken *> *)tokensInRange:(UITextRange *)textRange;

/// The range that corresponds to the field’s text, exclusive of any tokens.
///
/// @see -[<UITextInput> positionWithinRange:atCharacterOffset:]
@property (readonly, nonatomic) UITextRange *textualRange;

/// Removes any text contained in the specified range, inserts the provided token at the specified index, and selects the newly-inserted token. Does not replace any tokens within the provided range. If the range intersects the marked text range, the marked text is committed.
///
/// This method is essentially a convenience wrapper around the more fundamental `text`, `tokens`, and `selectedTextRange` properties, providing the selection behavior the user will expect.
///
/// @note
/// Because this method does not remove any tokens in the provided range, the caller can pass the field’s selectedTextRange to convert the selected portion of the text into a token without first having to trim the range.
- (void)replaceTextualPortionOfRange:(UITextRange *)textRange withToken:(UISearchToken *)token atIndex:(NSUInteger)tokenIndex;

/// Set this to nil for tokens to use their default color.
@property (nonatomic, strong, null_resettable) UIColor *tokenBackgroundColor;

/// Whether the user can remove tokens through standard actions such as Delete and Cut.
///
/// The application can always remove tokens programmatically. If this property is true, the application must be prepared not only for tokens to be removed, but also to be re-added through Undo. Defaults to true.
@property (nonatomic) BOOL allowsDeletingTokens;

/// Whether the user can copy tokens to the pasteboard or drag them out of the text field.
///
/// To support copying tokens, this property must be true and the delegate must provide an item provider for the tokens to be copied. UISearchTextField always enables the Copy command if any plain text is selected, even if the selection also includes tokens and this property is false. Defaults to true.
@property (nonatomic) BOOL allowsCopyingTokens;

@end

/// An individual token in a UISearchTextField.
UIKIT_CLASS_AVAILABLE_IOS_ONLY(13.0)
@interface UISearchToken : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

+ (UISearchToken *)tokenWithIcon:(nullable UIImage *)icon text:(NSString *)text;

/// The object which this token represents.
///
/// The application can assign any object it wants to this property. UISearchTextField does not attempt to interpret this object.
///
/// @note
/// Because UISearchToken strongly references its representedObject, consider assigning a lightweight representation (such as NSManagedObjectID) instead of a complete model object to this property. The lifetime of a UISearchToken may be considerably longer than expected, especially if the token has been copied to a pasteboard.
@property (strong, nullable, nonatomic) id representedObject;
@end

@protocol UISearchTextFieldDelegate <UITextFieldDelegate>
@optional

/// Implements cut and copy of tokens.
///
/// To support drag and drop and the Cut and Copy commands, your delegate must implement this method and return an NSItemProvider for the requested token. The field’s textPasteDelegate is responsible for implementing pasting of tokens. Your delegate can provide a plain text representation for pasting in other contexts, but should register a custom type identifier so it can recognize and reconstruct the token when pasted into the same field.
///
/// This method will only be called if either of the field’s allowsCopyingTokens or allowsDeletingTokens properties is true.
- (NSItemProvider *)searchTextField:(UISearchTextField *)searchTextField itemProviderForCopyingToken:(UISearchToken *)token;

@end

/// A protocol that refines UITextPasteItem to support pasting of tokens.
///
/// Paste items vended by UISearchTextField conform to this protocol.
@protocol UISearchTextFieldPasteItem <UITextPasteItem>

/// Transforms this paste item into a token at the end of the search text field’s token array.
- (void)setSearchTokenResult:(UISearchToken *)token;

@end

NS_ASSUME_NONNULL_END

#endif // TARGET_OS_IOS

#else
#import <UIKitCore/UISearchTextField.h>
#endif
