#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIUserActivity.h>)
//
//  UIUserActivity.h
//  UIKit
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

UIKIT_SWIFT_FORWARD_DECLARE(@class NSUserActivity)

API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@protocol UIUserActivityRestoring <NSObject>

- (void)restoreUserActivityState:(NSUserActivity *)userActivity;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIUserActivity.h>
#endif
