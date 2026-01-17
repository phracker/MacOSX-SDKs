#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIWindowSceneStandardPlacement.h>)
//
//  UIWindowSceneStandardPlacement.h
//  UIKit
//
//  Copyright © 2023 Apple Inc. All rights reserved.
//

#import <UIKit/UIWindowScenePlacement.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

UIKIT_EXTERN
API_AVAILABLE(ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos)
/// The default placement scene placement provided by the system.
@interface UIWindowSceneStandardPlacement : UIWindowScenePlacement

/// Creates a standard placement.
+ (instancetype)standardPlacement;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIWindowSceneStandardPlacement.h>
#endif
