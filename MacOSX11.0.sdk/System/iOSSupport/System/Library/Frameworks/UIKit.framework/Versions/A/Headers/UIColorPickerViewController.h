#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIColorPickerViewController.h>)
//
//  UIColorPickerViewController.h
//  UIKit
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIViewController.h>

NS_ASSUME_NONNULL_BEGIN

@class UIColorPickerViewController;

UIKIT_EXTERN API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, tvos)
@protocol UIColorPickerViewControllerDelegate <NSObject>

@optional

/// Called when the `selectedColor` changes.
- (void)colorPickerViewControllerDidSelectColor:(UIColorPickerViewController *)viewController;

/// In presentations (except popovers) the color picker shows a close button. If the close button is tapped,
/// the view controller is dismissed and `colorPickerViewControllerDidFinish:` is called. Can be used to
/// animate alongside the dismissal.
- (void)colorPickerViewControllerDidFinish:(UIColorPickerViewController *)viewController;

@end

UIKIT_EXTERN API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, tvos)
@interface UIColorPickerViewController : UIViewController

@property (nullable, weak, nonatomic) id<UIColorPickerViewControllerDelegate> delegate;

/// Sets the selected color on the color picker and is updated when the user changes the selection.
/// Does support KVO.
@property (strong, nonatomic) UIColor *selectedColor;

/// Controls whether the color picker shows an alpha slider or not.
///
/// If set to `NO` users are only able to pick fully opaque colors.
@property (nonatomic) BOOL supportsAlpha;

- (instancetype)initWithNibName:(nullable NSString *)nibNameOrNil bundle:(nullable NSBundle *)nibBundleOrNil NS_UNAVAILABLE;
- (instancetype)init NS_DESIGNATED_INITIALIZER;

@end
NS_ASSUME_NONNULL_END


#else
#import <UIKitCore/UIColorPickerViewController.h>
#endif
