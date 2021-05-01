#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIViewConfigurationState.h>)
//
//  UIViewConfigurationState.h
//  UIKit
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <UIKit/UIConfigurationState.h>

NS_ASSUME_NONNULL_BEGIN

@class UITraitCollection;

UIKIT_EXTERN API_AVAILABLE(ios(14.0), tvos(14.0), watchos(7.0))
@interface UIViewConfigurationState : NSObject <UIConfigurationState>

/// Returns a new instance with the specified trait collection.
- (instancetype)initWithTraitCollection:(UITraitCollection *)traitCollection NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@property (nonatomic, strong) UITraitCollection *traitCollection;

@property (nonatomic, getter=isDisabled) BOOL disabled;
@property (nonatomic, getter=isHighlighted) BOOL highlighted;
@property (nonatomic, getter=isSelected) BOOL selected;
@property (nonatomic, getter=isFocused) BOOL focused;

@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UIViewConfigurationState.h>
#endif
