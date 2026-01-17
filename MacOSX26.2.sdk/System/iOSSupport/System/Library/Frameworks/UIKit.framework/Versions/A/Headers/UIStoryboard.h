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

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

typedef __kindof UIViewController *_Nullable (^UIStoryboardViewControllerCreator)(NSCoder *coder) API_UNAVAILABLE(watchos);

UIKIT_EXTERN API_AVAILABLE(ios(5.0)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR API_DEPRECATED("Loading Interface Builder products will not be supported in a future version of visionOS.", visionos(1.0, 1.0))
@interface UIStoryboard : NSObject {
}

+ (UIStoryboard *)storyboardWithName:(NSString *)name bundle:(nullable NSBundle *)storyboardBundleOrNil;

- (nullable __kindof UIViewController *)instantiateInitialViewController;
- (nullable __kindof UIViewController *)instantiateInitialViewControllerWithCreator:(nullable NS_NOESCAPE UIStoryboardViewControllerCreator)block API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos);
- (__kindof UIViewController *)instantiateViewControllerWithIdentifier:(NSString *)identifier;
- (__kindof UIViewController *)instantiateViewControllerWithIdentifier:(NSString *)identifier creator:(nullable NS_NOESCAPE UIStoryboardViewControllerCreator)block API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos);

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIStoryboard.h>
#endif
