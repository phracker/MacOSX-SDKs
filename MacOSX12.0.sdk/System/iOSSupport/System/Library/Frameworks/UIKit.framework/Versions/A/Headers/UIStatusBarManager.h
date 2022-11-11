#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIStatusBarManager.h>)
//
//  UIStatusBarManager.h
//  UIKit
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <UIKit/UIWindowScene.h>

NS_ASSUME_NONNULL_BEGIN

UIKIT_EXTERN API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(tvos) NS_SWIFT_UI_ACTOR
@interface UIStatusBarManager : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@property (nonatomic, readonly) UIStatusBarStyle statusBarStyle;
@property (nonatomic, readonly, getter=isStatusBarHidden) BOOL statusBarHidden;
@property (nonatomic, readonly) CGRect statusBarFrame; // returns CGRectZero if the status bar is hidden

@end


@interface UIWindowScene (StatusBarManager)

@property (nonatomic, readonly, nullable) UIStatusBarManager *statusBarManager API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(tvos);

@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UIStatusBarManager.h>
#endif
