#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIActionSheet.h>)
//
//  UIActionSheet.h
//  UIKit
//
//  Copyright 2010-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UITextField.h>
#import <UIKit/UIView.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

@protocol UIActionSheetDelegate;
@class UILabel, UIToolbar, UITabBar, UIWindow, UIBarButtonItem, UIPopoverController;

typedef NS_ENUM(NSInteger, UIActionSheetStyle) {
    UIActionSheetStyleAutomatic        = -1,       // take appearance from toolbar style otherwise uses 'default'
    UIActionSheetStyleDefault          = UIBarStyleDefault,
    UIActionSheetStyleBlackTranslucent = UIBarStyleBlackTranslucent,
    UIActionSheetStyleBlackOpaque      = UIBarStyleBlackOpaque ,
} API_DEPRECATED("UIActionSheet is deprecated. Use UIAlertController with a preferredStyle of UIAlertControllerStyleActionSheet instead.", ios(2.0, 13.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(visionos, watchos);

UIKIT_EXTERN API_DEPRECATED("UIActionSheet is deprecated. Use UIAlertController with a preferredStyle of UIAlertControllerStyleActionSheet instead", ios(2.0, 8.3)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(visionos, watchos) NS_SWIFT_UI_ACTOR
@interface UIActionSheet : UIView

- (instancetype)initWithTitle:(nullable NSString *)title delegate:(nullable id<UIActionSheetDelegate>)delegate cancelButtonTitle:(nullable NSString *)cancelButtonTitle destructiveButtonTitle:(nullable NSString *)destructiveButtonTitle otherButtonTitles:(nullable NSString *)otherButtonTitles, ... NS_REQUIRES_NIL_TERMINATION;

@property(nullable,nonatomic,weak) id<UIActionSheetDelegate> delegate;
@property(nonatomic,copy) NSString *title;
@property(nonatomic) UIActionSheetStyle actionSheetStyle; // default is UIActionSheetStyleAutomatic. ignored if alert is visible

// adds a button with the title. returns the index (0 based) of where it was added. buttons are displayed in the order added except for the
// destructive and cancel button which will be positioned based on HI requirements. buttons cannot be customized.
- (NSInteger)addButtonWithTitle:(nullable NSString *)title;    // returns index of button. 0 based.
- (nullable NSString *)buttonTitleAtIndex:(NSInteger)buttonIndex;
@property(nonatomic,readonly) NSInteger numberOfButtons;
@property(nonatomic) NSInteger cancelButtonIndex;      // if the delegate does not implement -actionSheetCancel:, we pretend this button was clicked on. default is -1
@property(nonatomic) NSInteger destructiveButtonIndex;        // sets destructive (red) button. -1 means none set. default is -1. ignored if only one button

@property(nonatomic,readonly) NSInteger firstOtherButtonIndex;	// -1 if no otherButtonTitles or initWithTitle:... not used
@property(nonatomic,readonly,getter=isVisible) BOOL visible;

// show a sheet animated. you can specify either a toolbar, a tab bar, a bar button item or a plain view. We do a special animation if the sheet rises from
// a toolbar, tab bar or bar button item and we will automatically select the correct style based on the bar style. if not from a bar, we use
// UIActionSheetStyleDefault if automatic style set
- (void)showFromToolbar:(UIToolbar *)view;
- (void)showFromTabBar:(UITabBar *)view;
- (void)showFromBarButtonItem:(UIBarButtonItem *)item animated:(BOOL)animated API_AVAILABLE(ios(3.2));
- (void)showFromRect:(CGRect)rect inView:(UIView *)view animated:(BOOL)animated API_AVAILABLE(ios(3.2));
- (void)showInView:(UIView *)view;

// hides alert sheet or popup. use this method when you need to explicitly dismiss the alert.
// it does not need to be called if the user presses on a button
- (void)dismissWithClickedButtonIndex:(NSInteger)buttonIndex animated:(BOOL)animated;

@end


API_UNAVAILABLE(tvos, watchos) NS_SWIFT_UI_ACTOR
@protocol UIActionSheetDelegate <NSObject>
@optional

// Called when a button is clicked. The view will be automatically dismissed after this call returns
- (void)actionSheet:(UIActionSheet *)actionSheet clickedButtonAtIndex:(NSInteger)buttonIndex API_DEPRECATED("Use UIAlertController instead.", ios(2.0, 8.3)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(visionos, watchos);

// Called when we cancel a view (eg. the user clicks the Home button). This is not called when the user clicks the cancel button.
// If not defined in the delegate, we simulate a click in the cancel button
- (void)actionSheetCancel:(UIActionSheet *)actionSheet API_DEPRECATED("Use UIAlertController instead.", ios(2.0, 8.3)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(visionos, watchos);

- (void)willPresentActionSheet:(UIActionSheet *)actionSheet API_DEPRECATED("Use UIAlertController instead.", ios(2.0, 8.3)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(visionos, watchos);  // before animation and showing view
- (void)didPresentActionSheet:(UIActionSheet *)actionSheet API_DEPRECATED("Use UIAlertController instead.", ios(2.0, 8.3)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(visionos, watchos);  // after animation

- (void)actionSheet:(UIActionSheet *)actionSheet willDismissWithButtonIndex:(NSInteger)buttonIndex API_DEPRECATED("Use UIAlertController instead.", ios(2.0, 8.3)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(visionos, watchos); // before animation and hiding view
- (void)actionSheet:(UIActionSheet *)actionSheet didDismissWithButtonIndex:(NSInteger)buttonIndex API_DEPRECATED("Use UIAlertController instead.", ios(2.0, 8.3)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(visionos, watchos);  // after animation

@end

NS_HEADER_AUDIT_END(nullability, sendability)


#else
#import <UIKitCore/UIActionSheet.h>
#endif
