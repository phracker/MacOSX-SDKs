#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIDocumentMenuViewController.h>)
//
//  UIDocumentMenuViewController.h
//  UIKit
//
//  Copyright (c) 2014-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIViewController.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIDocumentPickerViewController.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSUInteger, UIDocumentMenuOrder) {
    UIDocumentMenuOrderFirst,
    UIDocumentMenuOrderLast
} API_DEPRECATED("", ios(8.0, 11.0)) API_UNAVAILABLE(tvos);

API_DEPRECATED("UIDocumentMenuDelegate is deprecated. Use UIDocumentPickerViewController directly.", ios(8.0, 13.0))
API_UNAVAILABLE(tvos) NS_SWIFT_UI_ACTOR
@protocol UIDocumentMenuDelegate <NSObject>

- (void)documentMenu:(UIDocumentMenuViewController *)documentMenu didPickDocumentPicker:(UIDocumentPickerViewController *)documentPicker;
@optional
- (void)documentMenuWasCancelled:(UIDocumentMenuViewController *)documentMenu;

@end

UIKIT_EXTERN API_DEPRECATED("UIDocumentMenuViewController is deprecated. Use UIDocumentPickerViewController directly.", ios(8.0, 11.0))
API_UNAVAILABLE(tvos) NS_SWIFT_UI_ACTOR
@interface UIDocumentMenuViewController : UIViewController

- (instancetype)initWithDocumentTypes:(NSArray <NSString *> *)allowedUTIs inMode:(UIDocumentPickerMode)mode NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithURL:(NSURL *)url inMode:(UIDocumentPickerMode)mode NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

- (void)addOptionWithTitle:(NSString *)title image:(nullable UIImage *)image order:(UIDocumentMenuOrder)order handler:(void (^)(void))handler;

@property (nullable, nonatomic, weak) id<UIDocumentMenuDelegate> delegate;

@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UIDocumentMenuViewController.h>
#endif
