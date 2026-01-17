#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIDragPreviewParameters.h>)
//
//  UIDragPreviewParameters.h
//  UIKit
//
//  Copyright © 2017-2018 Apple Inc. All rights reserved.
//

#import <UIKit/UIPreviewParameters.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

UIKIT_EXTERN API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, tvos) NS_SWIFT_UI_ACTOR
@interface UIDragPreviewParameters : UIPreviewParameters

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIDragPreviewParameters.h>
#endif
