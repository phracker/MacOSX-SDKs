//  
//  GCVirtualController.h
//  GameController
//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>


@class UIBezierPath;

NS_ASSUME_NONNULL_BEGIN

/**
 *  @class GCVirtualControllerConfiguration
 */
API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(macos, tvos) API_UNAVAILABLE(visionos)
NS_SWIFT_NAME(GCVirtualController.Configuration)
@interface GCVirtualControllerConfiguration : NSObject
 
/**
 The set of controller elements to be made available on \c GCVirtualController instances created with this configuration. e.g. [GCInputDirectionPad, GCInputLeftShoulder,  etc...]
 */
@property (nonatomic, strong) NSSet<NSString *> *elements;
   
/**
  Defaults to false, indicating that the default system touch control elements will be drawn using a touchable full-screen overlay. When set to true,
  the application is responsible for drawing its own control UI and should call \c -setValue: and \c -setPosition: methods on the \c GCVirtualController
  in response to touch or other events, which will then be translated into \c GCController events.
 */
@property (nonatomic, getter=isHidden) BOOL hidden API_AVAILABLE(ios(17.0));

@end


/**
 *  @class GCVirtualControllerElementConfiguration
 */
API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(macos, tvos) API_UNAVAILABLE(visionos)
NS_SWIFT_NAME(GCVirtualController.ElementConfiguration)
@interface GCVirtualControllerElementConfiguration : NSObject

/**
 A Boolean value that determines whether the element is hidden
 */
@property (nonatomic, getter=isHidden) BOOL hidden;

/**
 Path that defines custom element image
 Only supported for button elements
 */
@property (nonatomic, strong, nullable) UIBezierPath* path;

/**
 A Boolean value that determines if the thumbstick is acting as a touchpad
 Only supported for thumbsticks
 */
@property (nonatomic) BOOL actsAsTouchpad;

@end



/**
 *  @class GCVirtualController
 */
API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(macos, tvos) API_UNAVAILABLE(visionos)
@interface GCVirtualController : NSObject

/**
 Create a virtual controller
 
 @see GCVirtualControllerConfiguration
 */
+ (GCVirtualController *)virtualControllerWithConfiguration:(GCVirtualControllerConfiguration *)configuration;

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;
- (instancetype)initWithConfiguration:(GCVirtualControllerConfiguration *)configuration NS_DESIGNATED_INITIALIZER;

- (void)connectWithReplyHandler:(nullable void(^)(NSError * _Nullable error))reply NS_SWIFT_ASYNC_NAME(connect());
- (void)disconnect;


/**
 GCController is only available when GCVirtualController is connected
 */
@property (nonatomic, readonly, nullable) GCController *controller;

/**
  Changes the GCVirtualControllerElementConfiguration on a per element basis. Only applicable when the GCVirtualController is not hidden and its
  UI is being drawn by the system.
 */
- (void)updateConfigurationForElement:(NSString *)element configuration:(NS_NOESCAPE GCVirtualControllerElementConfiguration* (^)(GCVirtualControllerElementConfiguration *oldConfiguration))config;

/**
  Sets the value for a GCControllerButton element. Values are clamped to the range (0.0 - 1.0).
 */
- (void)setValue:(CGFloat)value forButtonElement:(NSString *)element API_AVAILABLE(ios(17.0));

/**
  Sets the (x,y) position for a GCControllerDirectionPad element (D-Pads as well as Joysticks). X and Y values are clamped to the range (-1.0 - 1.0).
 */
- (void)setPosition:(CGPoint)position forDirectionPadElement:(NSString *)element API_AVAILABLE(ios(17.0));

@end

NS_ASSUME_NONNULL_END
