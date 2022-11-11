//
//  CPBarButton.h
//  CarPlay
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Specifies the style used to display a @c CPBarButton.
 */
typedef NS_ENUM(NSInteger, CPBarButtonStyle) {
    CPBarButtonStyleNone,   // The button will be displayed with no additional styling.
    CPBarButtonStyleRounded // The button will be displayed with a rounded background.
} API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(macos, watchos, tvos);

/**
 Specifies the type of a @c CPBarButton.
 */
typedef NS_ENUM(NSUInteger, CPBarButtonType) {
    CPBarButtonTypeText,
    CPBarButtonTypeImage
} API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(macos, watchos, tvos) API_DEPRECATED_WITH_REPLACEMENT("-[CPBarButton initWithImage:handler:] or -[CPBarButton initWithTitle:handler:]", ios(12.0, 14.0));

/**
 A button for placement in a navigation bar.
 */
API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface CPBarButton : NSObject <NSSecureCoding>

typedef void (^CPBarButtonHandler) (CPBarButton *);

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/**
 Convenience initializer that creates a bar button that renders with an image.
 */
- (instancetype)initWithImage:(UIImage *)image
                      handler:(nullable CPBarButtonHandler)handler API_AVAILABLE(ios(14.0));

/**
 Convenience initializer that creates a bar button that displays a text label.
 */
- (instancetype)initWithTitle:(NSString *)title
                      handler:(nullable CPBarButtonHandler)handler API_AVAILABLE(ios(14.0));

/**
 A Boolean value indicating whether the button is enabled.

 @discussion Set the value of this property to @c YES to enable the button or @c NO to disable it. The default value of this property is @c YES.
 */
@property (nonatomic, assign, getter=isEnabled) BOOL enabled;

/**
 The style used to display this button.
 
 Defaults to @c CPBarButtonStyleNone.
 */
@property (nonatomic, assign) CPBarButtonStyle buttonStyle API_AVAILABLE(ios(14.0));

/**
 The image displayed on the button.

 @discussion Animated images are not supported. If an animated image is assigned, only the first image will be used.
 
 @note If both an image and title are specified, the title will take precedence.
 To use an image, ensure that the button's title is nil.
 */
@property (nullable, nonatomic, strong) UIImage *image;

/**
 The title displayed on the button.
 
 @note If both an image and title are specified, the title will take precedence.
 To use an image, ensure that the button's title is nil.
 */
@property (nullable, nonatomic, copy) NSString *title;

#pragma mark - Deprecated

- (instancetype)initWithType:(CPBarButtonType)type handler:(nullable CPBarButtonHandler)handler API_DEPRECATED_WITH_REPLACEMENT("-[CPBarButton initWithImage:handler:] or -[CPBarButton buttonWithTitle:handler:]", ios(12.0, 14.0));

@property (nonatomic, readonly) CPBarButtonType buttonType API_DEPRECATED_WITH_REPLACEMENT("-[CPBarButton initWithImage:handler:] or -[CPBarButton initWithTitle:handler:]", ios(12.0, 14.0));

@end

NS_ASSUME_NONNULL_END
