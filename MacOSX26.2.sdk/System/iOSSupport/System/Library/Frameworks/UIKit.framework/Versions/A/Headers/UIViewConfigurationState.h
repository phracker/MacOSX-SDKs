#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIViewConfigurationState.h>)
//
//  UIViewConfigurationState.h
//  UIKit
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <UIKit/UIConfigurationState.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

@class UITraitCollection;

UIKIT_EXTERN API_AVAILABLE(ios(14.0), tvos(14.0)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
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

@property (nonatomic, getter=isPinned) BOOL pinned API_AVAILABLE(ios(15.0), tvos(15.0)) API_UNAVAILABLE(watchos);

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIViewConfigurationState.h>
#endif
