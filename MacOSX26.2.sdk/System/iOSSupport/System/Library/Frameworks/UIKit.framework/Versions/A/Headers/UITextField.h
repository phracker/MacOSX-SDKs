#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UITextField.h>)
//
//  UITextField.h
//  UIKit
//
//  Copyright (c) 2005-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIControl.h>
#import <UIKit/UIFont.h>
#import <UIKit/UIStringDrawing.h>
#import <UIKit/UITextDragging.h>
#import <UIKit/UITextDropping.h>
#import <UIKit/UITextInput.h>
#import <UIKit/UIContentSizeCategoryAdjusting.h>
#import <UIKit/UILetterformAwareAdjusting.h>
#import <UIKit/UITextPasteConfigurationSupporting.h>
#import <UIKit/UIInputSuggestion.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

@class UIImage, UIImageView, UILabel, UIColor, UIButton;
@class UITextInputTraits;
@class UITextSelectionView;
@class UITextInteractionAssistant;
@class UIPopoverController;
@protocol UITextFieldDelegate;
@protocol UITextSelecting;

typedef NS_ENUM(NSInteger, UITextBorderStyle) {
    UITextBorderStyleNone,
    UITextBorderStyleLine,
    UITextBorderStyleBezel,
    UITextBorderStyleRoundedRect
} API_UNAVAILABLE(watchos);

typedef NS_ENUM(NSInteger, UITextFieldViewMode) {
    UITextFieldViewModeNever,
    UITextFieldViewModeWhileEditing,
    UITextFieldViewModeUnlessEditing,
    UITextFieldViewModeAlways
} API_UNAVAILABLE(watchos);

typedef NS_ENUM(NSInteger, UITextFieldDidEndEditingReason) {
    UITextFieldDidEndEditingReasonCommitted,
    UITextFieldDidEndEditingReasonCancelled UIKIT_AVAILABLE_TVOS_ONLY(10_0)
} API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(watchos);

UIKIT_EXTERN API_AVAILABLE(ios(2.0)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@interface UITextField : UIControl <UITextInput, NSCoding, UIContentSizeCategoryAdjusting, UILetterformAwareAdjusting>

@property(nullable, nonatomic,copy)   NSString               *text;                 // default is nil
@property(nullable, nonatomic,copy)   NSAttributedString     *attributedText API_AVAILABLE(ios(6.0)); // default is nil
@property(nullable, nonatomic,strong) UIColor                *textColor;            // default is nil. use opaque black
@property(nullable, nonatomic,strong) UIFont                 *font;                 // default is nil. use system font 12 pt
@property(nonatomic)        NSTextAlignment         textAlignment;        // default is NSLeftTextAlignment
@property(nonatomic)        UITextBorderStyle       borderStyle;          // default is UITextBorderStyleNone. If set to UITextBorderStyleRoundedRect, custom background images are ignored.
@property(nonatomic,copy)   NSDictionary<NSAttributedStringKey,id> *defaultTextAttributes API_AVAILABLE(ios(7.0)); // applies attributes to the full range of text. Unset attributes act like default values.

@property(nullable, nonatomic,copy)   NSString               *placeholder;          // default is nil. string is drawn 70% gray
@property(nullable, nonatomic,copy)   NSAttributedString     *attributedPlaceholder API_AVAILABLE(ios(6.0)); // default is nil
@property(nonatomic)        BOOL                    clearsOnBeginEditing; // default is NO which moves cursor to location clicked. if YES, all text cleared
@property(nonatomic)        BOOL                    adjustsFontSizeToFitWidth; // default is NO. if YES, text will shrink to minFontSize along baseline
@property(nonatomic)        CGFloat                 minimumFontSize;      // default is 0.0. actual min may be pinned to something readable. used if adjustsFontSizeToFitWidth is YES
@property(nullable, nonatomic,weak)   id<UITextFieldDelegate> delegate;             // default is nil. weak reference
@property(nullable, nonatomic,strong) UIImage                *background;           // default is nil. draw in border rect. image should be stretchable
@property(nullable, nonatomic,strong) UIImage                *disabledBackground;   // default is nil. ignored if background not set. image should be stretchable

@property(nonatomic,readonly,getter=isEditing) BOOL editing;
@property(nonatomic) BOOL allowsEditingTextAttributes API_AVAILABLE(ios(6.0)); // default is NO. allows editing text attributes with style operations and pasting rich text
@property(nullable, nonatomic,copy) NSDictionary<NSAttributedStringKey,id> *typingAttributes API_AVAILABLE(ios(6.0)); // automatically resets when the selection changes

// You can supply custom views which are displayed at the left or right
// sides of the text field. Uses for such views could be to show an icon or
// a button to operate on the text in the field in an application-defined
// manner.
// 
// A very common use is to display a clear button on the right side of the
// text field, and a standard clear button is provided.

@property(nonatomic)        UITextFieldViewMode  clearButtonMode; // sets when the clear button shows up. default is UITextFieldViewModeNever

@property(nullable, nonatomic,strong) UIView              *leftView;        // e.g. magnifying glass
@property(nonatomic)        UITextFieldViewMode  leftViewMode;    // sets when the left view shows up. default is UITextFieldViewModeNever

@property(nullable, nonatomic,strong) UIView              *rightView;       // e.g. bookmarks button
@property(nonatomic)        UITextFieldViewMode  rightViewMode;   // sets when the right view shows up. default is UITextFieldViewModeNever

// drawing and positioning overrides

- (CGRect)borderRectForBounds:(CGRect)bounds;
- (CGRect)textRectForBounds:(CGRect)bounds;
- (CGRect)placeholderRectForBounds:(CGRect)bounds;
- (CGRect)editingRectForBounds:(CGRect)bounds;
- (CGRect)clearButtonRectForBounds:(CGRect)bounds;
- (CGRect)leftViewRectForBounds:(CGRect)bounds;
- (CGRect)rightViewRectForBounds:(CGRect)bounds;

- (void)drawTextInRect:(CGRect)rect API_DEPRECATED("This method is no longer called.", ios(2.0, 15.0), visionos(1.0, 1.0)) API_UNAVAILABLE(watchos);
- (void)drawPlaceholderInRect:(CGRect)rect;

// Presented when object becomes first responder.  If set to nil, reverts to following responder chain.  If
// set while first responder, will not take effect until reloadInputViews is called.
@property (nullable, readwrite, strong) UIView *inputView;             
@property (nullable, readwrite, strong) UIView *inputAccessoryView API_UNAVAILABLE(visionos);

@property(nonatomic) BOOL clearsOnInsertion API_AVAILABLE(ios(6.0)); // defaults to NO. if YES, the selection UI is hidden, and inserting text will replace the contents of the field. changing the selection will automatically set this to NO.

@end

#if TARGET_OS_IOS

@interface UITextField () <UITextDraggable, UITextDroppable, UITextPasteConfigurationSupporting>
@end

#endif

@interface UITextField (UIInteractionStateRestorable)

// Note that the interaction state of a UITextField does _not_ encode the
// textual content of the field. It should be saved separately, and restored
// _before_ the interaction state.
// Currently, this encodes selection (and/or cursor position), and first
// responder status.
// The object returned here will be a plist type, so can e.g. be stored in
// an NSUserActivity's userInfo dictionary.
@property (nonatomic, copy) id interactionState API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(watchos);

@end


@interface UIView (UITextField)
- (BOOL)endEditing:(BOOL)force;    // use to make the view or any subview that is the first responder resign (optionally force)
@end

API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@protocol UITextFieldDelegate <NSObject>

@optional

- (BOOL)textFieldShouldBeginEditing:(UITextField *)textField;        // return NO to disallow editing.
- (void)textFieldDidBeginEditing:(UITextField *)textField;           // became first responder
- (BOOL)textFieldShouldEndEditing:(UITextField *)textField;          // return YES to allow editing to stop and to resign first responder status. NO to disallow the editing session to end
- (void)textFieldDidEndEditing:(UITextField *)textField;             // may be called if forced even if shouldEndEditing returns NO (e.g. view removed from window) or endEditing:YES called
- (void)textFieldDidEndEditing:(UITextField *)textField reason:(UITextFieldDidEndEditingReason)reason API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(watchos); // if implemented, called in place of textFieldDidEndEditing:

- (BOOL)textField:(UITextField *)textField shouldChangeCharactersInRange:(NSRange)range replacementString:(NSString *)string API_DEPRECATED_WITH_REPLACEMENT("-textField:shouldChangeCharactersInRanges:replacementString:", ios(2.0, API_TO_BE_DEPRECATED));   // return NO to not change text
/**
 * @abstract Asks the delegate if the text at the specified `ranges` should be replaced with `string`.
 *
 * @discussion If this method returns YES then the text field will, at its own discretion, choose any one of the specified `ranges` of text and replace it with the specified `replacementString` before deleting the text at the other ranges.
 *
 * @param textField                       The text field asking the delegate
 * @param ranges                             The ranges of the text that should be deleted before replacing
 * @param replacementString     The replacement string
 *
 * @return Returns YES if the text at the `ranges` should be replaced.
 */
- (BOOL)textField:(UITextField *)textField shouldChangeCharactersInRanges:(NSArray<NSValue *> *)ranges replacementString:(NSString *)string API_AVAILABLE(ios(26.0), tvos(26.0), visionos(26.0), watchos(26.0));

- (void)textFieldDidChangeSelection:(UITextField *)textField API_AVAILABLE(ios(13.0), tvos(13.0)) API_UNAVAILABLE(watchos);

- (BOOL)textFieldShouldClear:(UITextField *)textField;               // called when clear button pressed. return NO to ignore (no notifications)
- (BOOL)textFieldShouldReturn:(UITextField *)textField;              // called when 'return' key pressed. return NO to ignore.

/**
 * @abstract Asks the delegate for the menu to be shown for the specified text range.
 *
 * @param textField                   The text field requesting the menu.
 * @param range                            The characters range for which the menu is presented for.
 * @param suggestedActions   The actions and commands that the system suggests.
 *
 * @return Return a UIMenu describing the desired menu hierarchy. Return @c nil to present the default system menu.
 */
- (nullable UIMenu *)textField:(UITextField *)textField editMenuForCharactersInRange:(NSRange)range suggestedActions:(NSArray<UIMenuElement *> *)suggestedActions API_UNAVAILABLE(watchos) API_DEPRECATED_WITH_REPLACEMENT("-textField:editMenuForCharactersInRanges:suggestedActions", ios(16.0, API_TO_BE_DEPRECATED));

/**
 * @abstract Asks the delegate for the menu to be shown for the specified `ranges`.
 *
 * @param textField                   The text field requesting the menu.
 * @param ranges                          The text ranges for which the menu is presented for.
 * @param suggestedActions   The actions and commands that the system suggests.
 *
 * @return Return a UIMenu describing the desired menu hierarchy. Return @c nil to present the default system menu.
 */
- (nullable UIMenu *)textField:(UITextField *)textField editMenuForCharactersInRanges:(NSArray<NSValue *> *)ranges suggestedActions:(NSArray<UIMenuElement *> *)suggestedActions API_AVAILABLE(ios(26.0), tvos(26.0), visionos(26.0), watchos(26.0));

/**
 * @abstract Called when the text field is about to present the edit menu.
 *
 * @param textField    The text field displaying the menu.
 * @param animator      Appearance animator. Add animations to this object to run them alongside the appearance transition.
 */
- (void)textField:(UITextField *)textField willPresentEditMenuWithAnimator:(id<UIEditMenuInteractionAnimating>)animator API_AVAILABLE(ios(16.0))  API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos);

/**
 * @abstract Called when the text field is about to dismiss the edit menu.
 *
 * @param textField    The text field displaying the menu.
 * @param animator      Dismissal animator. Add animations to this object to run them alongside the dismissal transition.
 */
- (void)textField:(UITextField *)textField willDismissEditMenuWithAnimator:(id<UIEditMenuInteractionAnimating>)animator API_AVAILABLE(ios(16.0))  API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos);

/// Tells the delegate when the keyboard delivers an input suggestion.
///
/// - Parameters:
///   - textField: The text field that is currently the first responder.
///   - inputSuggestion: The input suggestion that the user or system selected.
- (void)textField:(UITextField *)textField insertInputSuggestion:(UIInputSuggestion *)inputSuggestion API_AVAILABLE(ios(18.4)) API_UNAVAILABLE(macCatalyst, watchos, tvos, visionos, macos) NS_SWIFT_NAME(textField(_:insertInputSuggestion:));

@end

UIKIT_EXTERN NSNotificationName const UITextFieldTextDidBeginEditingNotification API_UNAVAILABLE(watchos) NS_SWIFT_NONISOLATED;
UIKIT_EXTERN NSNotificationName const UITextFieldTextDidEndEditingNotification API_UNAVAILABLE(watchos) NS_SWIFT_NONISOLATED;
UIKIT_EXTERN NSNotificationName const UITextFieldTextDidChangeNotification API_UNAVAILABLE(watchos) NS_SWIFT_NONISOLATED;

UIKIT_EXTERN NSString *const UITextFieldDidEndEditingReasonKey API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(watchos) NS_SWIFT_NONISOLATED;

NS_HEADER_AUDIT_END(nullability, sendability)


#else
#import <UIKitCore/UITextField.h>
#endif
