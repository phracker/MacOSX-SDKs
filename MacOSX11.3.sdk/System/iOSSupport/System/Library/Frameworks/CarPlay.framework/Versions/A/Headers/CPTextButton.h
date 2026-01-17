//
//  CPTextButton.h
//  CarPlay
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <CarPlay/CPButton.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, CPTextButtonStyle) {
    /**
     A style that indicates a default action.
     */
    CPTextButtonStyleNormal = 0,
    /**
     A style that indicates the action will cancel and leave data unchanged.
     */
    CPTextButtonStyleCancel,
    /**
     A style that indicates the button will confirm an action.
     */
    CPTextButtonStyleConfirm,
} API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(macos, watchos, tvos);

API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface CPTextButton : NSObject

/**
 Create a button with text and a style that, when tapped, calls your custom handler.
 
 @param title A title that will appear in the button.
 @param textStyle A style that will be applied by the system for this button.
 @param handler A block that will be called when the user taps this button.
 */
- (instancetype)initWithTitle:(NSString *)title textStyle:(CPTextButtonStyle)textStyle handler:(void (^ _Nullable)(__kindof CPTextButton *contactButton))handler NS_DESIGNATED_INITIALIZER;

/**
 A custom title to display for this button, displayed only in templates that allow for custom titles.
 */
@property (nonatomic, copy) NSString *title;

/**
 A @c CPButtonTextStyle value indicating the style for this button, when displayed in a template
 that supports button styling, like the Information template.
 
 @discussion This value defaults to @c CPTextButtonStyleNormal.
 */
@property (nonatomic, assign) CPTextButtonStyle textStyle;

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
