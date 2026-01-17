//
//  CPContact.h
//  CarPlay
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <CarPlay/CPButton.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface CPContact : NSObject <NSSecureCoding>

/**
 Initializes a new contact to be used with @c CPContactTemplate, with a name and image
 
 @param name The name to be displayed for this contact.
 @param image An image for this contact. The maximum image size in points is CPButtonMaximumImageSize; larger images will be scaled down.

 @note When providing an image, your app should provide a @c UIImage that is display-ready. If necessary for the image, provide
 light and dark styles by using an asset from your asset catalog, prepared with light and dark styles
 or by using @c UIImageAsset to combine two @c UIImage instances into a single image with
 both styles.

 UIImageAsset is used to combine multiple UIImages with different trait collections into a single UIImage.
 
 @discussion To properly size your list images, your app should consider the display scale of the car screen.
 See -[CPInterfaceController carTraitCollection].
 */
- (instancetype)initWithName:(NSString *)name
                       image:(UIImage *)image;

/**
 The name that will be displayed for this contact.
 */
@property (nonatomic, copy) NSString *name;

/**
 An image representing the contact.
 */
@property (nonatomic, strong) UIImage *image;

/**
 Action buttons that will be displayed when this @c CPContact is displayed in a @c CPContactTemplate.
 */
@property (nullable, nonatomic, copy) NSArray <__kindof CPButton *> *actions;

/**
 Optional text that will be displayed in addition to the contact name
 */
@property (nullable, nonatomic, copy) NSString *subtitle;

/**
 Optional text that will be displayed in addition to the contact name
*/
@property (nullable, nonatomic, copy) NSString *informativeText;

@end

API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface CPContactCallButton : CPButton

/**
 Create a contact button with a system-provided call image that, when tapped, calls your custom handler.
 
 @param handler A block that will be called when the user taps this button.
 */
- (instancetype)initWithHandler:(void (^ _Nullable)(__kindof CPButton *contactButton))handler;

- (instancetype)initWithImage:(UIImage *)image
                      handler:(void (^ _Nullable)(__kindof CPButton *contactButton))handler NS_UNAVAILABLE;

@end

API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface CPContactMessageButton : CPButton

/**
 Create a contact button that, when tapped, launches to Siri to compose a message to this entity.
 When tapped, this button does NOT call a handler in your app. Instead, it will launch to Siri.
 To compose a message, you must provide a phone OR email for this contact.
 
 @param phoneOrEmail A phone or email address for this contact. This will not be displayed in the button,
 but it is necessary for Siri to compose a message to this contact entity.
 */
- (instancetype)initWithPhoneOrEmail:(NSString *)phoneOrEmail;

@property (nonatomic, copy, readonly) NSString *phoneOrEmail;

@end

API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface CPContactDirectionsButton : CPButton

/**
 Create a contact button with a system-provided navigation directions image that, when tapped, calls your custom handler.
 
 @param handler A block that will be called when the user taps this button.
 */
- (instancetype)initWithHandler:(void (^ _Nullable)(__kindof CPButton *contactButton))handler;

- (instancetype)initWithImage:(UIImage *)image
                      handler:(void (^ _Nullable)(__kindof CPButton *contactButton))handler NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
