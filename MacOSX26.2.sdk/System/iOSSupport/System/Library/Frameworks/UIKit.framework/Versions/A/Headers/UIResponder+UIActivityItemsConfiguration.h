#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIResponder+UIActivityItemsConfiguration.h>)
//
//  UIResponder+UIActivityItemsConfiguration.h
//  UIKit
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <UIKit/UIResponder.h>
#import <UIKit/UIActivityItemsConfigurationReading.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(tvos, watchos)
@interface UIResponder (UIActivityItemsConfiguration) <UIActivityItemsConfigurationProviding>

@property (nonatomic, strong, nullable) id<UIActivityItemsConfigurationReading> activityItemsConfiguration API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos) API_UNAVAILABLE(tvos);

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIResponder+UIActivityItemsConfiguration.h>
#endif
