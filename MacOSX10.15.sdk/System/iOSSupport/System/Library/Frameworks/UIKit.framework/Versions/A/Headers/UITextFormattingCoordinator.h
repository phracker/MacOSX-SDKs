#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UITextFormattingCoordinator.h>)
//
//  UITextFormattingCoordinator.h
//  UIKit
//
//  Copyright (c) 2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIFontPickerViewController.h>
#import <UIKit/UIResponder.h>

NS_ASSUME_NONNULL_BEGIN

@class UIWindowScene;

API_AVAILABLE(ios(13.0)) @protocol UITextFormattingCoordinatorDelegate <NSObject>
- (void)updateTextAttributesWithConversionHandler:(NS_NOESCAPE UITextAttributesConversionHandler _Nonnull)conversionHandler API_AVAILABLE(ios(13.0));
@end

UIKIT_EXTERN API_AVAILABLE(ios(13.0))
#if !TARGET_OS_WATCH && !TARGET_OS_TV
@interface UITextFormattingCoordinator : NSObject <UIFontPickerViewControllerDelegate>
#else
@interface UITextFormattingCoordinator : NSObject
#endif // !TARGET_OS_WATCH && !TARGET_OS_TV

@property(nullable, nonatomic, weak) id<UITextFormattingCoordinatorDelegate> delegate;
@property(class, readonly, getter=isFontPanelVisible) BOOL fontPanelVisible;

+ (instancetype)textFormattingCoordinatorForWindowScene:(UIWindowScene *)windowScene;

- (instancetype)initWithWindowScene:(UIWindowScene *)windowScene NS_DESIGNATED_INITIALIZER;
- (instancetype)init NS_UNAVAILABLE;

// Informs the paragraph and character formatting UI when text in a selection has changed attributes. `isMultiple:` means that the attributes spans multiple text runs.
- (void)setSelectedAttributes:(NSDictionary<NSAttributedStringKey, id> *)attributes
                   isMultiple:(BOOL)flag;

// iOS Mac only, toggle standard Font Panel visibility for macOS.
+ (void)toggleFontPanel:(id)sender;

@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UITextFormattingCoordinator.h>
#endif
