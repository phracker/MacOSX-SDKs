#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UITextFormattingViewController.h>)
//
//  UITextFormattingViewController.h
//  UIKit
//
//  Copyright © 2022 Apple Inc. All rights reserved.
//
    
#import <UIKit/UIViewController.h>
#import <UIKit/UITextFormattingViewControllerConfiguration.h>
#import <UIKit/UITextFormattingViewControllerChangeValue.h>

@class UIFontPickerViewController;
@class UIColorPickerViewController;
@class UITextFormattingViewControllerFormattingDescriptor;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

@class UITextFormattingViewController;

#pragma mark - UITextFormattingViewControllerDelegate

UIKIT_EXTERN API_AVAILABLE(ios(18.0), visionos(26.0)) API_UNAVAILABLE(macCatalyst) API_UNAVAILABLE(watchos, tvos) NS_SWIFT_UI_ACTOR NS_REFINED_FOR_SWIFT
@protocol UITextFormattingViewControllerDelegate <NSObject>

/// Delegate method that will be invoked on any text formatting changes.
///
/// - Parameters:
///   - viewController: Text formatting controller in which action was performed.
///   - changeValue: Object describing the change made via view controller.
- (void)textFormattingViewController:(UITextFormattingViewController *)viewController didChangeValue:(UITextFormattingViewControllerChangeValue *)changeValue;

@optional

/// If implemented, text formatting will call this method before presenting font picker controller.
/// Use this method to make any presentation modifications or to prevent presentation altogether.
///
/// If you decide to prevent presentation of font picker via text formatting controller, you may present provided font picker yourself.
/// In this case, you will have to handle any font picker actions independently.
///
/// - Parameters:
///   - viewController: Text formatting controller that is attempting to present font picker controller
///   - fontPicker: Font picker controller that will be presented.
/// - Returns: Flag indicating if text formatting controller should present font picker.
- (BOOL)textFormattingViewController:(UITextFormattingViewController *)viewController shouldPresentFontPicker:(UIFontPickerViewController *)fontPicker;

/// If implemented, text formatting will call this method before presenting color picker controller.
/// Use this method to make any presentation modifications or to prevent presentation altogether.
///
/// You may decide to prevent presentation of color picker via text formatting controller.
/// In that case, you may present provided color picker controller yourself, but you will have to handle any actions in that controller separately.
///
/// - Parameters:
///   - viewController: Text formatting controller that is attempting to present font picker controller
///   - colorPicker: Color picker controller that will be presented.
/// - Returns: Flag indicating if text formatting controller should present font picker.
- (BOOL)textFormattingViewController:(UITextFormattingViewController *)viewController shouldPresentColorPicker:(UIColorPickerViewController *)colorPicker;

/// Informs the delegate that user has dismissed text formatting view controller.
- (void)textFormattingDidFinish:(UITextFormattingViewController *)viewController;

@end

#pragma mark - UITextFormattingViewController

/// A view controller that manages the interface for common text formatting options.
UIKIT_EXTERN API_AVAILABLE(ios(18.0), visionos(26.0)) API_UNAVAILABLE(macCatalyst) API_UNAVAILABLE(watchos, tvos) NS_SWIFT_UI_ACTOR
@interface UITextFormattingViewController : UIViewController

/// Current text formatting configuration object.
@property (nonatomic, readonly, copy) UITextFormattingViewControllerConfiguration *configuration;

/// Current formatting descriptor.
@property (nonatomic, nullable, copy) UITextFormattingViewControllerFormattingDescriptor *formattingDescriptor NS_REFINED_FOR_SWIFT;

/// Text formatting delegate.
@property (nullable, nonatomic, weak) id<UITextFormattingViewControllerDelegate> delegate NS_REFINED_FOR_SWIFT;

- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithNibName:(nullable NSString *)nibNameOrNil bundle:(nullable NSBundle *)nibBundleOrNil NS_UNAVAILABLE;
- (instancetype)initWithConfiguration:(UITextFormattingViewControllerConfiguration *)configuration NS_DESIGNATED_INITIALIZER;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UITextFormattingViewController.h>
#endif
