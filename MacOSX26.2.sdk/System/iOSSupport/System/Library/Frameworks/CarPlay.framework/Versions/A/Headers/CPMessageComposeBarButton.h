//
//  CPMessageComposeBarButton.h
//  CarPlay
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <CarPlay/CarPlay.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(macos, watchos)
@interface CPMessageComposeBarButton : CPBarButton

/**
Convenience initializer that creates a message compose button with a system-provided image.

@note This button type does not use a handler. Instead, tapping this button will activate Siri
 and launch into a compose message flow.
*/
- (instancetype)init;
+ (instancetype)new NS_SWIFT_UNAVAILABLE("-init");

/**
 Convenience initializer that creates a message compose button with a custom image.
 
 @note This button type does not use a handler. Instead, tapping this button will activate Siri
 and launch into a compose message flow.
 */
- (instancetype)initWithImage:(UIImage *)image;

@property (nullable, nonatomic, copy) NSString *title NS_UNAVAILABLE;

- (instancetype)initWithImage:(UIImage *)image
                      handler:(nullable CPBarButtonHandler)handler NS_UNAVAILABLE;
- (instancetype)initWithTitle:(NSString *)title
                      handler:(nullable CPBarButtonHandler)handler NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
