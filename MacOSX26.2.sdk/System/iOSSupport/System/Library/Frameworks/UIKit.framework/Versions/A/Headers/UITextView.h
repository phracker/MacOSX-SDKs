#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UITextView.h>)
//
//  UITextView.h
//  UIKit
//
//  Copyright (c) 2007-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIFindInteraction.h>
#import <UIKit/UIScrollView.h>
#import <UIKit/UIStringDrawing.h>
#import <UIKit/UITextDragging.h>
#import <UIKit/UITextDropping.h>
#import <UIKit/UITextInput.h>
#import <UIKit/UITextSearching.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIDataDetectors.h>
#import <UIKit/UITextItemInteraction.h>
#import <UIKit/UIContentSizeCategoryAdjusting.h>
#import <UIKit/UILetterformAwareAdjusting.h>
#import <UIKit/UITextPasteConfigurationSupporting.h>
#import <UIKit/UIInputSuggestion.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

@class UIFindInteraction, UIFont, UIColor, UIMenu, UIMenuElement, UITextView, NSTextContainer, NSTextLayoutManager, NSLayoutManager, NSTextStorage, NSTextAttachment, UITextItem, UITextItemMenuConfiguration, NSTextRange, UITextFormattingViewController, UITextFormattingViewControllerConfiguration, UIWritingToolsCoordinator;
@protocol UIEditMenuInteractionAnimating, UIContextMenuInteractionAnimating;

API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@protocol UITextViewDelegate <NSObject, UIScrollViewDelegate>

@optional

- (BOOL)textViewShouldBeginEditing:(UITextView *)textView;
- (BOOL)textViewShouldEndEditing:(UITextView *)textView;

- (void)textViewDidBeginEditing:(UITextView *)textView;
- (void)textViewDidEndEditing:(UITextView *)textView;

- (BOOL)textView:(UITextView *)textView shouldChangeTextInRange:(NSRange)range replacementText:(NSString *)text API_DEPRECATED_WITH_REPLACEMENT("-textView:shouldChangeTextInRanges:replacementText:", ios(2.0, API_TO_BE_DEPRECATED));
/**
 * @abstract Asks the delegate if the text at the specified `ranges` should be replaced with `text`.
 *
 * @discussion If this method returns YES then the text view will, at its own discretion, choose any one of the specified `ranges` of text and replace it with the specified `replacementText` before deleting the text at the other ranges. If the delegate does not implement this method then the `textView:shouldChangeTextInRange:replacementText:` method will be called and passed the union range instead. If the delegate also does not implement that method then YES is assumed.
 *
 * @param textView                  The text view asking the delegate
 * @param ranges                       The ranges of the text that should be deleted before replacing
 * @param replacementText   The replacement text
 *
 * @return Returns true if the text at the `ranges` should be replaced.
 */
- (BOOL)textView:(UITextView *)textView shouldChangeTextInRanges:(NSArray<NSValue *> *)ranges replacementText:(NSString *)text API_AVAILABLE(ios(26.0), tvos(26.0), visionos(26.0), watchos(26.0));

- (void)textViewDidChange:(UITextView *)textView;

- (void)textViewDidChangeSelection:(UITextView *)textView;

/**
 * @abstract Asks the delegate for the menu to be shown for the specified text range.
 *
 * @param textView                     The text view requesting the menu.
 * @param range                            The text range for which the menu is presented for.
 * @param suggestedActions   The actions and commands that the system suggests.
 *
 * @return Return a UIMenu describing the desired menu hierarchy. Return @c nil to present the default system menu.
 */
- (nullable UIMenu *)textView:(UITextView *)textView editMenuForTextInRange:(NSRange)range suggestedActions:(NSArray<UIMenuElement *> *)suggestedActions API_UNAVAILABLE(watchos) API_DEPRECATED_WITH_REPLACEMENT("-textView:editMenuForTextInRanges:suggestedActions:", ios(16.0, API_TO_BE_DEPRECATED));

/**
 * @abstract Asks the delegate for the menu to be shown for the specified text ranges.
 *
 * @discussion If the delegate does not implement this method then the `textView:editMenuForTextInRange:suggestedActions:` method will be called and passed the union range instead. If the delegate also does not implement that method then `nil` is assumed.
 *
 * @param textView                     The text view requesting the menu.
 * @param ranges                          The text ranges for which the menu is presented for.
 * @param suggestedActions   The actions and commands that the system suggests.
 *
 * @return Return a UIMenu describing the desired menu hierarchy. Return @c nil to present the default system menu.
 */
- (nullable UIMenu *)textView:(UITextView *)textView editMenuForTextInRanges:(NSArray<NSValue *> *)ranges suggestedActions:(NSArray<UIMenuElement *> *)suggestedActions API_AVAILABLE(ios(26.0), tvos(26.0), visionos(26.0), watchos(26.0));

/**
 * @abstract Called when the text view is about to present the edit menu.
 *
 * @param textView      The text view displaying the menu.
 * @param animator      Appearance animator. Add animations to this object to run them alongside the appearance transition.
 */
- (void)textView:(UITextView *)textView willPresentEditMenuWithAnimator:(id<UIEditMenuInteractionAnimating>)animator API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos);

/**
 * @abstract Called when the text view is about to dismiss the edit menu.
 *
 * @param textView      The text view displaying the menu.
 * @param animator      Dismissal animator. Add animations to this object to run them alongside the dismissal transition.
 */
- (void)textView:(UITextView *)textView willDismissEditMenuWithAnimator:(id<UIEditMenuInteractionAnimating>)animator API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos);

/**
 * Asks the delegate for the action to be performed when interacting with a text item. If a nil action is provided, the text view
 * will request a menu to be presented on primary action if possible.
 *
 * @param textView  The text view requesting the primary action.
 * @param textItem  The text item for performing said action.
 * @param defaultAction The default action for the text item. Return this to perform the default action.
 *
 * @return Return a UIAction to be performed when the text item is interacted with. Return @c nil to prevent the action from being performed.
 */
- (nullable UIAction *)textView:(UITextView *)textView primaryActionForTextItem:(UITextItem *)textItem defaultAction:(UIAction *)defaultAction API_AVAILABLE(ios(17.0)) API_UNAVAILABLE(tvos, watchos);

/**
 * Asks the delegate for the menu configuration to be performed when interacting with a text item.
 *
 * @param textView  The text view requesting the menu.
 * @param textItem  The text item for performing said action.
 * @param defaultMenu  The default menu for the specified text item.
 *
 * @return Return a menu configuration to be presented when the text item is interacted with. Return @c nil to prevent the menu from being presented.
 */
- (nullable UITextItemMenuConfiguration *)textView:(UITextView *)textView menuConfigurationForTextItem:(UITextItem *)textItem defaultMenu:(UIMenu *)defaultMenu API_AVAILABLE(ios(17.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos) ;

/**
 * Informs the delegate that a text item menu is about to be presented with the specified animator.
 *
 * @param textView  The text view showing the menu.
 * @param textItem  The text item for performing said action.
 * @param animator  Appearance animator. Add animations to this object to run them alongside the appearance transition.
 */
- (void)textView:(UITextView *)textView textItemMenuWillDisplayForTextItem:(UITextItem *)textItem animator:(id<UIContextMenuInteractionAnimating>)animator API_AVAILABLE(ios(17.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos);

/**
 * Informs the delegate that a text item menu is about to be dismissed with the specified animator.
 *
 * @param textView  The text view showing the menu.
 * @param textItem  The text item for performing said action.
 * @param animator  Dismissal animator. Add animations to this object to run them alongside the dismissal transition.
 */
- (void)textView:(UITextView *)textView textItemMenuWillEndForTextItem:(UITextItem *)textItem animator:(id<UIContextMenuInteractionAnimating>)animator API_AVAILABLE(ios(17.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos);

/**
 * @abstract Informs the delegate that Writing Tools will begin manipulating the text view
 *
 * @param textView  The text view interacting with Writing Tools
 */
- (void)textViewWritingToolsWillBegin:(UITextView *)textView API_AVAILABLE(ios(18.0), visionos(2.4)) API_UNAVAILABLE(tvos, watchos);

/**
 * @abstract Informs the delegate that Writing Tools has finished manipulating the text view
 *
 * @param textView  The text view interacting with Writing Tools
 */
- (void)textViewWritingToolsDidEnd:(UITextView *)textView API_AVAILABLE(ios(18.0), visionos(2.4)) API_UNAVAILABLE(tvos, watchos);

/**
 * @abstract Allows the delegate to specify ranges of text to be ignored by Writing Tools
 *
 * @param textView  The text view interacting with Writing Tools
 * @param enclosingRange
 *
 * @return Return an array of ranges in the attributed substring of the textView storage with the enclosing range representing portions of text to be ignored by Writing Tools when evaluating the text for proofreading, summarization, rewrites, and so forth.
 */
- (NSArray<NSValue *> *)textView:(UITextView *)textView writingToolsIgnoredRangesInEnclosingRange:(NSRange)enclosingRange API_AVAILABLE(ios(18.0), visionos(2.4)) API_UNAVAILABLE(tvos, watchos);


- (BOOL)textView:(UITextView *)textView shouldInteractWithURL:(NSURL *)URL inRange:(NSRange)characterRange interaction:(UITextItemInteraction)interaction API_DEPRECATED("Replaced by primaryActionForTextItem: and menuConfigurationForTextItem: for additional customization options.", ios(10.0, 17.0), visionos(1.0, 1.0)) API_UNAVAILABLE(watchos);
- (BOOL)textView:(UITextView *)textView shouldInteractWithTextAttachment:(NSTextAttachment *)textAttachment inRange:(NSRange)characterRange interaction:(UITextItemInteraction)interaction API_DEPRECATED("Replaced by primaryActionForTextItem: and menuConfigurationForTextItem: for additional customization options.", ios(10.0, 17.0), visionos(1.0, 1.0)) API_UNAVAILABLE(watchos);

- (BOOL)textView:(UITextView *)textView shouldInteractWithURL:(NSURL *)URL inRange:(NSRange)characterRange API_DEPRECATED_WITH_REPLACEMENT("textView:shouldInteractWithURL:inRange:interaction:", ios(7.0, 10.0)) API_UNAVAILABLE(visionos, watchos);
- (BOOL)textView:(UITextView *)textView shouldInteractWithTextAttachment:(NSTextAttachment *)textAttachment inRange:(NSRange)characterRange API_DEPRECATED_WITH_REPLACEMENT("textView:shouldInteractWithTextAttachment:inRange:interaction:", ios(7.0, 10.0)) API_UNAVAILABLE(visionos, watchos);

/**
 * @abstract Informs the delegate that text formatting controller is about to be presented.
 *
 * @param viewController  The text formatting controller that is being presented.
 */
- (void)textView:(UITextView *)textView willBeginFormattingWithViewController:(UITextFormattingViewController *)viewController API_AVAILABLE(ios(18.0), visionos(26.0)) API_UNAVAILABLE(macCatalyst) API_UNAVAILABLE(watchos, tvos);

/**
 * @abstract Informs the delegate that text formatting controller has been presented.
 *
 * @param viewController  The text formatting controller that is being presented.
 */
- (void)textView:(UITextView *)textView didBeginFormattingWithViewController:(UITextFormattingViewController *)viewController API_AVAILABLE(ios(18.0), visionos(26.0)) API_UNAVAILABLE(macCatalyst) API_UNAVAILABLE(watchos, tvos);

/**
 * @abstract Informs the delegate that text formatting controller is about to be dismissed.
 *
 * @param viewController  The text formatting controller that is being presented.
 */
- (void)textView:(UITextView *)textView willEndFormattingWithViewController:(UITextFormattingViewController *)viewController API_AVAILABLE(ios(18.0), visionos(26.0)) API_UNAVAILABLE(macCatalyst) API_UNAVAILABLE(watchos, tvos);

/**
 * @abstract Informs the delegate that text formatting controller has been dismissed.
 *
 * @param viewController  The text formatting controller that is being presented.
 */
- (void)textView:(UITextView *)textView didEndFormattingWithViewController:(UITextFormattingViewController *)viewController API_AVAILABLE(ios(18.0), visionos(26.0)) API_UNAVAILABLE(macCatalyst) API_UNAVAILABLE(watchos, tvos);

/// Tells the delegate when the keyboard delivers an input suggestion.
///
/// - Parameters:
///   - textView: The text view that is currently the first responder.
///   - inputSuggestion: The input suggestion that the user or system selected.
- (void)textView:(UITextView *)textView insertInputSuggestion:(UIInputSuggestion *)inputSuggestion NS_SWIFT_NAME(textView(_:insertInputSuggestion:)) API_AVAILABLE(ios(18.4)) API_UNAVAILABLE(tvos, watchos, visionos, macCatalyst);

@end

/// The type of border around the text view.
typedef NS_ENUM(NSInteger, UITextViewBorderStyle) {
    /// The text view does not display a border.
    UITextViewBorderStyleNone,

    /// Displays a rounded-style border for the text view.
    UITextViewBorderStyleRoundedRect API_AVAILABLE(visionos(1.0)) API_UNAVAILABLE(ios, watchos),
} API_AVAILABLE(ios(17.0), visionos(1.0)) API_UNAVAILABLE(watchos);

UIKIT_EXTERN API_AVAILABLE(ios(2.0)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@interface UITextView : UIScrollView <UITextInput, UIContentSizeCategoryAdjusting, UILetterformAwareAdjusting>

@property(nullable,nonatomic,weak) id<UITextViewDelegate> delegate;

@property(null_resettable,nonatomic,copy) NSString *text;
@property(nullable,nonatomic,strong) UIFont *font;
@property(nullable,nonatomic,strong) UIColor *textColor;
@property(nonatomic) NSTextAlignment textAlignment;    // default is NSLeftTextAlignment
/// A union of all the `selectedRanges`.
@property(nonatomic) NSRange selectedRange API_DEPRECATED_WITH_REPLACEMENT("selectedRanges", ios(2.0, API_TO_BE_DEPRECATED));
/**
 * The `NSRange`s of the selection. In most cases, there will only be a single selected range. For cases where bidirectional text is selected, there may be multiple discontiguous ranges. These selected ranges will always be in the normal form, which means they are sorted in ascending order and there are no overlaps. The selected ranges will always be converted to its normal form when they are set. There will always be at least one selected range in this array. So if this array is set to an empty array then the selection will be cleared and a single selected range will be left behind where the length will be 0 and the location will be the location at the end of the selection.
 */
@property(nonatomic, copy, nonnull) NSArray<NSValue *> *selectedRanges API_AVAILABLE(ios(26.0), tvos(26.0), visionos(26.0), watchos(26.0)) NS_REFINED_FOR_SWIFT;

@property(nonatomic,getter=isEditable) BOOL editable API_UNAVAILABLE(tvos);
// Toggle selectability, which controls the ability of the user to select content and interact with URLs & attachments. On tvOS this also makes the text view focusable.
// By default, text item interaction follows selectable if the text item methods on UITextViewDelegate are not implemented; otherwise, they follow the result of the specified delegate methods.
@property(nonatomic,getter=isSelectable) BOOL selectable API_AVAILABLE(ios(7.0));
@property(nonatomic) UIDataDetectorTypes dataDetectorTypes API_AVAILABLE(ios(3.0)) API_UNAVAILABLE(tvos);

@property(nonatomic) BOOL allowsEditingTextAttributes API_AVAILABLE(ios(6.0)); // defaults to NO
@property(null_resettable,copy) NSAttributedString *attributedText API_AVAILABLE(ios(6.0));
@property(nonatomic,copy) NSDictionary<NSAttributedStringKey, id> *typingAttributes API_AVAILABLE(ios(6.0)); // automatically resets when the selection changes

- (void)scrollRangeToVisible:(NSRange)range;


// Presented when object becomes first responder.  If set to nil, reverts to following responder chain.  If
// set while first responder, will not take effect until reloadInputViews is called.
@property (nullable, readwrite, strong) UIView *inputView;             
@property (nullable, readwrite, strong) UIView *inputAccessoryView API_UNAVAILABLE(visionos);

@property(nonatomic) BOOL clearsOnInsertion API_AVAILABLE(ios(6.0)); // defaults to NO. if YES, the selection UI is hidden, and inserting text will replace the contents of the field. changing the selection will automatically set this to NO.

// Create a new text view with the specified text container (can be nil).
// This initializer will follow the NSTextContainer's usage of TextKit 2 (NSTextLayoutManager) or TextKit 1 (NSLayoutManager).
// If a nil NSTextContainer is specified, TextKit 2 will be used.
- (instancetype)initWithFrame:(CGRect)frame textContainer:(nullable NSTextContainer *)textContainer API_AVAILABLE(ios(7.0)) NS_DESIGNATED_INITIALIZER;

// From iOS 16 onwards, UITextViews are, by default, created with a TextKit 2 NSTextLayoutManager managing text layout (see the .textLayoutManager property). They will dynamically 'fall back' to a TextKit 1 NSLayoutManager if TextKit 1 features are used (notably, if the .layoutManager property is accessed).
// This convenience initializer can be used to specify TextKit 1 by default if you know code in your app relies on that. This avoids inefficiencies associated with the needless creation of a NSTextLayoutManager and the subsequent fallback.
+ (instancetype)textViewUsingTextLayoutManager:(BOOL)usingTextLayoutManager API_AVAILABLE(ios(16.0), tvos(16.0)) API_UNAVAILABLE(watchos);

- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

// Get the text container for the text view
@property(nonatomic, readonly) NSTextContainer *textContainer API_AVAILABLE(ios(7.0));
// Inset the text container's layout area within the text view's content area
@property(nonatomic, assign) UIEdgeInsets textContainerInset API_AVAILABLE(ios(7.0));

// This property accesses the TextKit 2 NSTextLayoutManager. You should generally prefer to use it over the TextKit 1 .layoutManager property if it exists. This property will return nil if TextKit 1 is in use.
@property(nonatomic, nullable, readonly) NSTextLayoutManager *textLayoutManager API_AVAILABLE(ios(16.0), tvos(16.0)) API_UNAVAILABLE(watchos);

// To ensure compatibility with older code, accessing the .layoutManager of a UITextView - or its .textContainer's .layoutManager - will cause a UITextView that's using TextKit 2 to 'fall back' to TextKit 1, and return a newly created NSLayoutManager. After this happens, .textLayoutManager will return nil - and _any TextKit 2 objects you may have cached will cease functioning_. Be careful about this if you are intending to be using TextKit 2!
@property(nonatomic, readonly) NSLayoutManager *layoutManager API_AVAILABLE(ios(7.0));

// The textual contents of the text view.
@property(nonatomic, readonly, strong) NSTextStorage *textStorage API_AVAILABLE(ios(7.0));

// Style for links
@property(null_resettable, nonatomic, copy) NSDictionary<NSAttributedStringKey,id> *linkTextAttributes API_AVAILABLE(ios(7.0));

// When turned on, this changes the rendering scale of the text to match the standard text scaling and preserves the original font point sizes when the contents of the text view are copied to the pasteboard.  Apps that show a lot of text content, such as a text viewer or editor, should turn this on and use the standard text scaling.
@property (nonatomic) BOOL usesStandardTextScaling API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos);

/// If `findInteractionEnabled` is set to true, returns this text view's built-in find interaction. Otherwise, nil.
@property (nonatomic, nullable, readonly) UIFindInteraction *findInteraction API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(watchos, tvos);

/// Enables this text view's built-in find interaction.
@property (nonatomic, readwrite, getter=isFindInteractionEnabled) BOOL findInteractionEnabled API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(watchos, tvos);


/// The border style for the text field.
@property (nonatomic) UITextViewBorderStyle borderStyle API_AVAILABLE(ios(17.0), visionos(1.0)) API_UNAVAILABLE(watchos);

// Text Highlight
// Attributes for NSTextHighlightStyleAttributeName rendering. It is consulted when the corresponding NSTextHighlightColorSchemeAttributeName is NSTextHighlightColorSchemeDefault. NSForegroundColorAttributeName overrides the text color, and NSBackgroundColorAttributeName specifies the highlight color rendered with drawTextHighlightBackground(for textRange:, origin:). When NSForegroundColorAttributeName is missing, it uses the text color specified by the document content. When NSBackgroundColorAttributeName is not specified, it is derived from NSForegroundColorAttributeName. By default, it returns a dictionary with tintColor for NSForegroundColorAttributeName.
@property (nonatomic, copy, null_resettable) NSDictionary<NSAttributedStringKey, id> *textHighlightAttributes API_AVAILABLE(ios(18.0), tvos(18.0), visionos(2.0)) API_UNAVAILABLE(watchos);

// Renders the text highlight background for NSTextHighlightStyleAttributeName in textRange. origin specifies the coordinate origin in the NSTextContainer coordinate system of the rendering context.
- (void)drawTextHighlightBackgroundForTextRange:(NSTextRange *)textRange origin:(CGPoint)origin API_AVAILABLE(ios(18.0), tvos(18.0), visionos(2.0)) API_UNAVAILABLE(watchos);

/**
 * @abstract Convenience for tracking whether Writing Tools is active
 *
 * @return Returns @c YES while Writing Tools is interacting with the receiver (after @c -textViewWritingToolsWillBegin: completes until @c -textViewWritingToolsDidEnd: completes)
 */
@property(nonatomic,readonly,getter=isWritingToolsActive) BOOL writingToolsActive API_AVAILABLE(ios(18.0), visionos(2.4)) API_UNAVAILABLE(tvos, watchos);

// Also see UITextInputTraits.h
@property UIWritingToolsBehavior writingToolsBehavior API_AVAILABLE(ios(18.0), visionos(2.4)) API_UNAVAILABLE(tvos, watchos);

// WARNING: UITextView does not support UIWritingToolsResultOptionsTable and will throw an exception for this value
@property UIWritingToolsResultOptions allowedWritingToolsResultOptions API_AVAILABLE(ios(18.0), visionos(2.4)) API_UNAVAILABLE(tvos, watchos);

@property(nonatomic,readonly) Class subclassForWritingToolsCoordinator API_AVAILABLE(ios(18.2), visionos(2.4)) API_UNAVAILABLE(tvos, watchos); // Asserts this is actually a subclass of UIWritingToolsCoordinator
@property(nonatomic,readonly) UIWritingToolsCoordinator *writingToolsCoordinator API_AVAILABLE(ios(18.2), visionos(2.4)) API_UNAVAILABLE(tvos, watchos);

/// For text views that have flag `allowsEditingTextAttributes` set,
/// this configuration will be used for `UITextFormattingViewController`
/// when its presentation is requested.
/// 
/// It has a non-nil default value.
@property(nonatomic, nullable, readwrite, copy) UITextFormattingViewControllerConfiguration *textFormattingConfiguration API_AVAILABLE(ios(18.0), visionos(26.0)) API_UNAVAILABLE(macCatalyst) API_UNAVAILABLE(watchos, tvos);

@end

#if TARGET_OS_IOS

@interface UITextView () <UITextDraggable, UITextDroppable, UITextPasteConfigurationSupporting, UIFindInteractionDelegate, UITextSearching>
@end

#endif

@interface UITextView (UIInteractionStateRestorable)

// Note that the interaction state of a UITextView does _not_ encode the
// textual content of the field. It should be saved separately, and restored
// _before_ the interaction state.
// Currently, this encodes selection (and/or cursor position), scroll position,
// and first responder status.
// The object returned here will be a plist type, so can e.g. be stored in
// an NSUserActivity's userInfo dictionary.
@property (nonatomic, copy) id interactionState API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(watchos);

@end

UIKIT_EXTERN NSNotificationName const UITextViewTextDidBeginEditingNotification API_UNAVAILABLE(watchos) NS_SWIFT_NONISOLATED;
UIKIT_EXTERN NSNotificationName const UITextViewTextDidChangeNotification API_UNAVAILABLE(watchos) NS_SWIFT_NONISOLATED;
UIKIT_EXTERN NSNotificationName const UITextViewTextDidEndEditingNotification API_UNAVAILABLE(watchos) NS_SWIFT_NONISOLATED;

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UITextView.h>
#endif
