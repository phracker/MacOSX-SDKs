#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIContentUnavailableConfigurationState.h>)
//
//  UIContentUnavailableConfigurationState.h
//  UIKit
//
//  Copyright © 2023 Apple Inc. All rights reserved.
//

#import <UIKit/UIConfigurationState.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

@class UITraitCollection;

UIKIT_EXTERN API_AVAILABLE(ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@interface UIContentUnavailableConfigurationState : NSObject <UIConfigurationState>

- (instancetype)initWithTraitCollection:(UITraitCollection *)traitCollection NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/// The trait collection.
@property (nonatomic, strong) UITraitCollection *traitCollection;

/// The search text. Default is the search bar text of the view controller's search controller.
@property (nonatomic, strong, nullable) NSString *searchText;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIContentUnavailableConfigurationState.h>
#endif
