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
} API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos);

typedef NS_OPTIONS(NSUInteger, UIMenuElementAttributes) {
    UIMenuElementAttributesDisabled     = 1 << 0,
    UIMenuElementAttributesDestructive  = 1 << 1,
    UIMenuElementAttributesHidden       = 1 << 2,
    
    /// Indicates that the menu should remain presented after firing
    /// the element's action rather than dismissing as it normally does.
    /// This attribute has no effect on Mac Catalyst.
    UIMenuElementAttributesKeepsMenuPresented API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(watchos) = 1 << 3
} API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos);

/// Possible repeat behaviors for a menu element.
typedef NS_ENUM(NSInteger, UIMenuElementRepeatBehavior) {
    /// Automatically uses the appropriate repeat behavior for this element.
    UIMenuElementRepeatBehaviorAutomatic = 0,
    /// The element should be allowed to repeat.
    UIMenuElementRepeatBehaviorRepeatable,
    /// The element should not be repeatable.
    UIMenuElementRepeatBehaviorNonRepeatable,
} API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(watchos) NS_SWIFT_NAME(UIMenuElement.RepeatBehavior);

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

UIKIT_EXTERN API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@interface UIMenuElement : NSObject <NSCopying, NSSecureCoding>

/// The element's title.
@property (nonatomic, readonly) NSString *title;

/// The element's subtitle.
@property (nonatomic, nullable, copy) NSString *subtitle API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(watchos);

/// Image to be displayed alongside the element's title.
@property (nonatomic, nullable, readonly) UIImage *image;

- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIMenuElement.h>
#endif
