#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIDragPreviewParameters.h>)
//
//  UIDragPreviewParameters.h
//  UIKit
//
//  Copyright © 2017-2018 Apple Inc. All rights reserved.
//

#import <UIKit/UIPreviewParameters.h>

NS_ASSUME_NONNULL_BEGIN

UIKIT_EXTERN API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, tvos) NS_SWIFT_UI_ACTOR
@interface UIDragPreviewParameters : UIPreviewParameters

@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UIDragPreviewParameters.h>
#endif
