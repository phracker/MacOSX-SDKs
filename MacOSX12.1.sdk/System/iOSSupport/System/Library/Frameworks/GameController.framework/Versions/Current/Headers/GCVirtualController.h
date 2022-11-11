//  
//  GCVirtualController.h
//  GameController
//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#import <TargetConditionals.h>


#if TARGET_OS_IPHONE
#import <GameController/GameController.h>

NS_ASSUME_NONNULL_BEGIN



/**
 GCVirtualControllerConfiguration
 
*/
API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(macos, tvos)
NS_SWIFT_NAME(GCVirtualController.Configuration)
@interface GCVirtualControllerConfiguration : NSObject
 
// The set of controller elements e.g. [GCInputDirectionPad, GCInputLeftShoulder,  etc...]
@property (nonatomic, strong) NSSet<NSString *> *elements;
   
@end


/**
 GCVirtualControllerElementConfiguration
 
*/
API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(macos, tvos)
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
 GCVirtualController
 
*/
API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(macos, tvos)
@interface GCVirtualController : NSObject

/**
 Create a virtual controller
 
 @see GCVirtualControllerConfiguration
 */
+(GCVirtualController *)virtualControllerWithConfiguration:(GCVirtualControllerConfiguration *)configuration;

+(instancetype)new NS_UNAVAILABLE;
-(instancetype)init NS_UNAVAILABLE;
-(instancetype)initWithConfiguration:(GCVirtualControllerConfiguration *)configuration NS_DESIGNATED_INITIALIZER;

-(void)connectWithReplyHandler:(void(^ _Nullable )(NSError * _Nullable error))reply NS_SWIFT_ASYNC_NAME(connect());

-(void)disconnect;


/**
 GCController is only available when GCVirtualController is connected
 */
@property (nonatomic, weak, readonly, nullable) GCController *controller;

-(void)updateConfigurationForElement:(NSString*)element configuration:( GCVirtualControllerElementConfiguration*(NS_NOESCAPE ^ _Nonnull )(GCVirtualControllerElementConfiguration * oldConfiguration))config ;

@end

NS_ASSUME_NONNULL_END

#endif
