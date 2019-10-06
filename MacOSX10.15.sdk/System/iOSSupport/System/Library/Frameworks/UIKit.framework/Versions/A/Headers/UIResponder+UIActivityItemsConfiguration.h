#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIResponder+UIActivityItemsConfiguration.h>)
//
//  UIResponder+UIActivityItemsConfiguration.h
//  UIKit
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <UIKit/UIResponder.h>

NS_ASSUME_NONNULL_BEGIN

@protocol UIActivityItemsConfigurationReading;

API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(tvos, watchos)
@interface UIResponder (UIActivityItemsConfiguration)

@property (nonatomic, strong, nullable) id<UIActivityItemsConfigurationReading> activityItemsConfiguration API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(tvos, watchos);

@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UIResponder+UIActivityItemsConfiguration.h>
#endif
