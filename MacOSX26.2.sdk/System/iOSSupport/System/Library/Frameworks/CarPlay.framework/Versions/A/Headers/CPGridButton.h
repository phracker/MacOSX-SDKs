//
//  CPGridButton.h
//  CarPlay
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

/**
 @c CPMessageGridItemConfiguration encapsulates the message configuration options for the grid item.
 */
API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(macos, watchos)
@interface CPMessageGridItemConfiguration : NSObject

/**
 Initialize a @c CPMessageGridItemConfiguration for use in a @c CPListTemplate.

 @param conversationIdentifier A value meaningful to your app to identify this conversation.
 This identifier is not directly displayed to the user; rather, when the user selects this grid item,
 SiriKit will pass this identifier back to your app for your own use.
 @param unread  A Boolean value indicating whether the item shows an unread indicator. The default value of this property is @c NO.

*/
- (instancetype)initWithConversationIdentifier:(NSString *)conversationIdentifier
                                        unread:(BOOL)unread;

@property (nonatomic, getter=isUnread) BOOL unread;

@property (nonatomic, readonly) NSString *conversationIdentifier;

@end


API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(macos, watchos)
@interface CPGridButton : NSObject <NSSecureCoding>

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/**
 Initialize a button with a title and image.

 @param titleVariants An array of title variants for this button, arranged from most to least preferred. You must provide at least one title.
 @param image The image displayed on the button. It must be non-nil for the button to be displayed.
 @param handler A block to execute when the user selects the button. The block has no return value and takes the selected button as its only parameter.

 The image must be non-nil and the title must be a non-zero length string for the button to be displayed.
 
 @discussion To properly size your images, your app should size them to the display scale of the car screen.
 See -[CPInterfaceController carTraitCollection].
 */
- (instancetype)initWithTitleVariants:(NSArray <NSString *> *)titleVariants image:(UIImage *)image handler:(void (^ _Nullable)(CPGridButton *gridButton))handler;

/**
 Initialize a button with a title, image, and message configuration.
 */
- (instancetype)initWithTitleVariants:(NSArray <NSString *> *)titleVariants
                                image:(UIImage *)image
                 messageConfiguration:(nullable CPMessageGridItemConfiguration *)messageConfiguration
                              handler:(void (^ _Nullable)(CPGridButton *gridButton))handler NS_SWIFT_NAME(init(titleVariants:image:messageConfiguration:handler:)) API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(macos, watchos) NS_DESIGNATED_INITIALIZER;
/**
 A Boolean value indicating whether the button is enabled.

 @discussion Set the value of this property to @c YES to enable the button or @c NO to disable it. The default value of this property is @c YES.
 */
@property (nonatomic, assign, getter=isEnabled) BOOL enabled;

@property (nonatomic, readonly, nullable) CPMessageGridItemConfiguration *messageConfiguration API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(macos, watchos);

/**
 The image displayed on the button.

 @discussion Animated images are not supported. If an animated image is assigned, only the first image will be used.
 To properly size your list images, your app should size them to the display scale of the car screen.
 See -[CPInterfaceController carTraitCollection].
 */
@property (nonatomic, readonly) UIImage *image;

- (void)updateImage:(UIImage *)image API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(macos, watchos);

/**
 An array of title variants for this button, arranged from most to least preferred.
 The system will select a title from your list of provided variants that fits the available space.
 The variant strings should be provided as localized, displayable content.
 */
@property (nonatomic, readonly) NSArray <NSString *> *titleVariants;

- (void)updateTitleVariants:(NSArray <NSString *> *)titleVariants API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(macos, watchos);

@end

NS_ASSUME_NONNULL_END
