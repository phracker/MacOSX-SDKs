#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIConfigurationState.h>)
//
//  UIConfigurationState.h
//  UIKit
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class UITraitCollection;

typedef NSString * UIConfigurationStateCustomKey NS_TYPED_EXTENSIBLE_ENUM API_AVAILABLE(ios(14.0), tvos(14.0), watchos(7.0));

UIKIT_EXTERN API_AVAILABLE(ios(14.0), tvos(14.0), watchos(7.0))
@protocol UIConfigurationState <NSObject, NSCopying, NSSecureCoding>

/// Returns a new instance with the specified trait collection.
- (instancetype)initWithTraitCollection:(UITraitCollection *)traitCollection;

@property (nonatomic, strong) UITraitCollection *traitCollection;

/// Returns the custom state for the specified key.
- (nullable id)customStateForKey:(UIConfigurationStateCustomKey)key;
/// Sets the custom state for the specified key.
- (void)setCustomState:(nullable id)customState forKey:(UIConfigurationStateCustomKey)key;

- (nullable id)objectForKeyedSubscript:(UIConfigurationStateCustomKey)key;
- (void)setObject:(nullable id)obj forKeyedSubscript:(UIConfigurationStateCustomKey)key;

@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UIConfigurationState.h>
#endif
