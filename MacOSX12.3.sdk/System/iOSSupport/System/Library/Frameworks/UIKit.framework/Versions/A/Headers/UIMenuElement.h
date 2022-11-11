#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIMenuElement.h>)
//
//  UIMenuElement.h
//  UIKit
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>

@class UIImage;

typedef NS_ENUM(NSInteger, UIMenuElementState) {
    UIMenuElementStateOff,
    UIMenuElementStateOn,
    UIMenuElementStateMixed
} NS_SWIFT_NAME(UIMenuElement.State) API_AVAILABLE(ios(13.0));

typedef NS_OPTIONS(NSUInteger, UIMenuElementAttributes) {
    UIMenuElementAttributesDisabled     = 1 << 0,
    UIMenuElementAttributesDestructive  = 1 << 1,
    UIMenuElementAttributesHidden       = 1 << 2
} NS_SWIFT_NAME(UIMenuElement.Attributes) API_AVAILABLE(ios(13.0));

NS_ASSUME_NONNULL_BEGIN

UIKIT_EXTERN API_AVAILABLE(ios(13.0)) NS_SWIFT_UI_ACTOR
@interface UIMenuElement : NSObject <NSCopying, NSSecureCoding>

/// The element's title.
@property (nonatomic, readonly) NSString *title;

/// The element's subtitle.
@property (nonatomic, nullable, copy) NSString *subtitle API_AVAILABLE(ios(15.0));

/// Image to be displayed alongside the element's title.
@property (nonatomic, nullable, readonly) UIImage *image;

- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UIMenuElement.h>
#endif
