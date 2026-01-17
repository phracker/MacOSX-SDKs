#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIEventAttributionView.h>)
//
//  UIEventAttributionView.h
//  UIKit
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <UIKit/UIKitDefines.h>
#import <UIKit/UIView.h>

NS_ASSUME_NONNULL_BEGIN

UIKIT_EXTERN API_AVAILABLE(ios(14.5)) API_UNAVAILABLE(watchos, tvos) @interface UIEventAttributionView : UIView

@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UIEventAttributionView.h>
#endif
