//
//  CPListImageRowItemCondensedElement.h
//  CarPlay
//
//  Copyright © 2025 Apple Inc. All rights reserved.
//

#import <CarPlay/CPListImageRowItemElement.h>
#import <CarPlay/CPTemplate.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(macos, watchos)
/**
 Types of shape used to draw a condensed row element.
 */
typedef NS_ENUM(NSInteger, CPListImageRowItemCondensedElementShape) {
    /**
     The list item will render an element with a circular image.
     */
    CPListImageRowItemCondensedElementShapeCircular NS_SWIFT_NAME(circular),

    /**
     The list item will render an element with a rounded rectangle image.
     */
    CPListImageRowItemCondensedElementShapeRoundedRectangle NS_SWIFT_NAME(roundedRectangle),
} NS_SWIFT_NAME(CPListImageRowItemCondensedElement.Shape);

API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(macos, watchos)
CARPLAY_TEMPLATE_UI_ACTOR
@interface CPListImageRowItemCondensedElement: CPListImageRowItemElement

/**
 Initialize a list image row condensed element with an image, an image shape, a title, subtitle and a system symbol name.
 
 @param image The image associated to the element.
 @param imageShape The @c CPListImageRowItemCondensedElementShape shape being applied on the image.
 @param title The title of the element.
 @param subtitle The subtitle of the element.
 @param accessorySymbolName The system symbol used as an accessory view.
 */
- (instancetype)initWithImage:(UIImage *)image
                   imageShape:(CPListImageRowItemCondensedElementShape)imageShape
                        title:(NSString *)title
                     subtitle:(nullable NSString *)subtitle
          accessorySymbolName:(nullable NSString *)accessorySymbolName;

/**
 The title associated with this element.
 */
@property (nonatomic, copy) NSString *title;

/**
 The subtitle associated with this element.
 */
@property (nonatomic, copy, nullable) NSString *subtitle;

/**
 The name of the system symbol image to use as accessory.
 */
@property (nonatomic, copy, nullable) NSString *accessorySymbolName;

/**
 Shape used to draw the image of the element.
 */
@property (nonatomic, assign, readonly) CPListImageRowItemCondensedElementShape imageShape;

@end

NS_ASSUME_NONNULL_END
