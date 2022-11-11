#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIStoryboard.h>)
//
//  UIStoryboard.h
//  UIKit
//
//  Copyright 2011-2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>

@class UIViewController;

NS_ASSUME_NONNULL_BEGIN

typedef __kindof UIViewController *_Nullable (^UIStoryboardViewControllerCreator)(NSCoder *coder);

UIKIT_EXTERN API_AVAILABLE(ios(5.0)) NS_SWIFT_UI_ACTOR
@interface UIStoryboard : NSObject {
}

+ (UIStoryboard *)storyboardWithName:(NSString *)name bundle:(nullable NSBundle *)storyboardBundleOrNil;

- (nullable __kindof UIViewController *)instantiateInitialViewController;
- (nullable __kindof UIViewController *)instantiateInitialViewControllerWithCreator:(nullable NS_NOESCAPE UIStoryboardViewControllerCreator)block API_AVAILABLE(ios(13.0));
- (__kindof UIViewController *)instantiateViewControllerWithIdentifier:(NSString *)identifier;
- (__kindof UIViewController *)instantiateViewControllerWithIdentifier:(NSString *)identifier creator:(nullable NS_NOESCAPE UIStoryboardViewControllerCreator)block API_AVAILABLE(ios(13.0));

@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UIStoryboard.h>
#endif
