#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIContentUnavailableView.h>)
//
//  UIContentUnavailableView.h
//  UIKit
//
//  Copyright © 2023 Apple Inc. All rights reserved.
//

#import <UIKit/UIContentConfiguration.h>
#import <UIKit/UIView.h>
#import <UIKit/UIContentUnavailableConfiguration.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

UIKIT_EXTERN API_AVAILABLE(ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@interface UIContentUnavailableView : UIView <UIContentView>

- (instancetype)initWithConfiguration:(UIContentUnavailableConfiguration *)configuration NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

- (instancetype)initWithFrame:(CGRect)frame NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/// The content unavailable configuration.
@property (nonatomic, copy) UIContentUnavailableConfiguration *configuration;

/// Whether the content can scroll. Default is NO.
@property (nonatomic, getter=isScrollEnabled) BOOL scrollEnabled;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIContentUnavailableView.h>
#endif
