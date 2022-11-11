#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIOpenURLContext.h>)
//
//  UIOpenURLContext.h
//  UIKit
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <UIKit/UIApplication.h>

@class UISceneOpenURLOptions;

NS_ASSUME_NONNULL_BEGIN

// This object is vended to your application by UIKit when there are URLs to open
UIKIT_EXTERN API_AVAILABLE(ios(13.0)) NS_SWIFT_UI_ACTOR
@interface UIOpenURLContext : NSObject
+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@property (nonatomic, readonly, copy) NSURL *URL;
@property (nonatomic, readonly, strong) UISceneOpenURLOptions *options;

@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UIOpenURLContext.h>
#endif
