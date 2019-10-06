#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIUserActivity.h>)
//
//  UIUserActivity.h
//  UIKit
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

UIKIT_SWIFT_FORWARD_DECLARE(@class NSUserActivity)

API_AVAILABLE(ios(8.0)) @protocol UIUserActivityRestoring <NSObject>

- (void)restoreUserActivityState:(NSUserActivity *)userActivity;

@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UIUserActivity.h>
#endif
