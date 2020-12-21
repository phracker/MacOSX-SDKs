#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UITextView.h>)
//
//  UITextView.h
//  UIKit
//
//  Copyright (c) 2007-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIScrollView.h>
#import <UIKit/UIStringDrawing.h>
#import <UIKit/UITextDragging.h>
#import <UIKit/UITextDropping.h>
#import <UIKit/UITextInput.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIDataDetectors.h>
#import <UIKit/UITextItemInteraction.h>
#import <UIKit/UIContentSizeCategoryAdjusting.h>
#import <UIKit/UITextPasteConfigurationSupporting.h>

NS_ASSUME_NONNULL_BEGIN

@class UIFont, UIColor, UITextView, NSTextContainer, NSLayoutManager, NSTextStorage, NSTextAttachment;

@protocol UITextViewDelegate <NSObject, UIScrollViewDelegate>

@optional

- (BOOL)textViewShouldBeginEditing:(UITextView *)textView;
- (BOOL)textViewShouldEndEditing:(UITextView *)textView;

- (void)textViewDidBeginEditing:(UITextView *)textView;
- (void)textViewDidEndEditing:(UITextView *)textView;

- (BOOL)textView:(UITextView *)textView shouldChangeTextInRange:(NSRange)range replacementText:(NSString *)text;
- (void)textViewDidChange:(UITextView *)textView;

- (void)textViewDidChangeSelection:(UITextView *)textView;

- (BOOL)textView:(UITextView *)textView shouldInteractWithURL:(NSURL *)URL inRange:(NSRange)characterRange interaction:(UITextItemInteraction)interaction API_AVAILABLE(ios(10.0));
- (BOOL)textView:(UITextView *)textView shouldInteractWithTextAttachment:(NSTextAttachment *)textAttachment inRange:(NSRange)characterRange interaction:(UITextItemInteraction)interaction API_AVAILABLE(ios(10.0));

- (BOOL)textView:(UITextView *)textView shouldInteractWithURL:(NSURL *)URL inRange:(NSRange)characterRange API_DEPRECATED_WITH_REPLACEMENT("textView:shouldInteractWithURL:inRange:interaction:", ios(7.0, 10.0));
- (BOOL)textView:(UITextView *)textView shouldInteractWithTextAttachment:(NSTextAttachment *)textAttachment inRange:(NSRange)characterRange API_DEPRECATED_WITH_REPLACEMENT("textView:shouldInteractWithTextAttachment:inRange:interaction:", ios(7.0, 10.0));

@end

UIKIT_EXTERN API_AVAILABLE(ios(2.0)) @interface UITextView : UIScrollView <UITextInput, UIContentSizeCategoryAdjusting>

@property(nullable,nonatomic,weak) id<UITextViewDelegate> delegate;

@property(null_resettable,nonatomic,copy) NSString *text;
@property(nullable,nonatomic,strong) UIFont *font;
@property(nullable,nonatomic,strong) UIColor *textColor;
@property(nonatomic) NSTextAlignment textAlignment;    // default is NSLeftTextAlignment
@property(nonatomic) NSRange selectedRange;
@property(nonatomic,getter=isEditable) BOOL editable API_UNAVAILABLE(tvos);
@property(nonatomic,getter=isSelectable) BOOL selectable API_AVAILABLE(ios(7.0)); // toggle selectability, which controls the ability of the user to select content and interact with URLs & attachments. On tvOS this also makes the text view focusable.
@property(nonatomic) UIDataDetectorTypes dataDetectorTypes API_AVAILABLE(ios(3.0)) API_UNAVAILABLE(tvos);

@property(nonatomic) BOOL allowsEditingTextAttributes API_AVAILABLE(ios(6.0)); // defaults to NO
@property(null_resettable,copy) NSAttributedString *attributedText API_AVAILABLE(ios(6.0));
@property(nonatomic,copy) NSDictionary<NSAttributedStringKey, id> *typingAttributes API_AVAILABLE(ios(6.0)); // automatically resets when the selection changes

- (void)scrollRangeToVisible:(NSRange)range;


// Presented when object becomes first responder.  If set to nil, reverts to following responder chain.  If
// set while first responder, will not take effect until reloadInputViews is called.
@property (nullable, readwrite, strong) UIView *inputView;             
@property (nullable, readwrite, strong) UIView *inputAccessoryView;

@property(nonatomic) BOOL clearsOnInsertion API_AVAILABLE(ios(6.0)); // defaults to NO. if YES, the selection UI is hidden, and inserting text will replace the contents of the field. changing the selection will automatically set this to NO.

// Create a new text view with the specified text container (can be nil) - this is the new designated initializer for this class
- (instancetype)initWithFrame:(CGRect)frame textContainer:(nullable NSTextContainer *)textContainer API_AVAILABLE(ios(7.0)) NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

// Get the text container for the text view
@property(nonatomic,readonly) NSTextContainer *textContainer API_AVAILABLE(ios(7.0));
// Inset the text container's layout area within the text view's content area
@property(nonatomic, assign) UIEdgeInsets textContainerInset API_AVAILABLE(ios(7.0));

// Convenience accessors (access through the text container)
@property(nonatomic,readonly) NSLayoutManager *layoutManager API_AVAILABLE(ios(7.0));
@property(nonatomic,readonly,strong) NSTextStorage *textStorage API_AVAILABLE(ios(7.0));

// Style for links
@property(null_resettable, nonatomic, copy) NSDictionary<NSAttributedStringKey,id> *linkTextAttributes API_AVAILABLE(ios(7.0));

// When turned on, this changes the rendering scale of the text to match the standard text scaling and preserves the original font point sizes when the contents of the text view are copied to the pasteboard.  Apps that show a lot of text content, such as a text viewer or editor, should turn this on and use the standard text scaling.
@property (nonatomic) BOOL usesStandardTextScaling API_AVAILABLE(ios(13.0));

@end

#if TARGET_OS_IOS

@interface UITextView () <UITextDraggable, UITextDroppable, UITextPasteConfigurationSupporting>
@end

#endif

UIKIT_EXTERN NSNotificationName const UITextViewTextDidBeginEditingNotification;
UIKIT_EXTERN NSNotificationName const UITextViewTextDidChangeNotification;
UIKIT_EXTERN NSNotificationName const UITextViewTextDidEndEditingNotification;

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UITextView.h>
#endif
