#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIInputViewController.h>)
//
//  UIInputViewController.h
//  UIKit
//
//  Copyright (c) 2014-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIViewController.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIInputView.h>
#import <UIKit/UITextInput.h>

NS_ASSUME_NONNULL_BEGIN

@class UILexicon;

NS_SWIFT_UI_ACTOR
@protocol UITextDocumentProxy <UIKeyInput>

@property (nullable, nonatomic, readonly) NSString *documentContextBeforeInput;
@property (nullable, nonatomic, readonly) NSString *documentContextAfterInput;
@property (nullable, nonatomic, readonly) NSString *selectedText API_AVAILABLE(ios(11.0));

// An app can store UITextInputMode in its document context, when user switches to the document, the host will pass the inputMode as documentInputMode to the UIInputViewController,
// which can switch to the inputMode and set primaryLanguage if it supports it.
@property (nullable, nonatomic, readonly) UITextInputMode *documentInputMode API_AVAILABLE(ios(10.0));

@property (nonatomic, readonly, copy) NSUUID *documentIdentifier API_AVAILABLE(ios(11.0));

- (void)adjustTextPositionByCharacterOffset:(NSInteger)offset;

// Setting marked text either replaces the existing marked text or, if none is present, inserts it in place of the current input location.
- (void)setMarkedText:(NSString *)markedText selectedRange:(NSRange)selectedRange API_AVAILABLE(ios(13.0));

// Unmark the currently marked text.
- (void)unmarkText API_AVAILABLE(ios(13.0));

@end

UIKIT_EXTERN API_AVAILABLE(ios(8.0)) NS_SWIFT_UI_ACTOR
@interface UIInputViewController : UIViewController <UITextInputDelegate>

@property (nullable, nonatomic, strong) UIInputView *inputView;

@property (nonatomic, readonly) id <UITextDocumentProxy> textDocumentProxy;

// The primary language of the UIInputViewController.  A BCP 47 language identifier such as en-US
// If specified, this will supersede any PrimaryLanguage in the Info.plist.
@property (nullable, nonatomic, copy) NSString *primaryLanguage;

// When this property is set to YES, the system dictation key, if provided, will be disabled. 
@property (nonatomic) BOOL hasDictationKey;

@property (nonatomic, readonly) BOOL hasFullAccess API_AVAILABLE(ios(11.0));
@property (nonatomic, readonly) BOOL needsInputModeSwitchKey API_AVAILABLE(ios(11.0));

- (void)dismissKeyboard;
- (void)advanceToNextInputMode;

// Launch inputMode list above the view when long pressing or swiping up from the view,
// Advance to nextInputMode when short tapping on the view.
// Example: [KeyboardButton addTarget:self action:@selector(handleInputModeListFromView:withEvent:) forControlEvents:UIControlEventAllTouchEvents].
- (void)handleInputModeListFromView:(nonnull UIView *)view withEvent:(nonnull UIEvent *)event API_AVAILABLE(ios(10.0));

// This will not provide a complete repository of a language's vocabulary.
// It is solely intended to supplement existing lexicons.
- (void)requestSupplementaryLexiconWithCompletion:(void (^)(UILexicon *))completionHandler;

@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UIInputViewController.h>
#endif
