//
//  GCDevice.h
//  GameController
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <GameController/GCProductCategories.h>

@class GCPhysicalInputProfile;
@class GCDeviceHaptics;
@protocol GCDevicePhysicalInput;


NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0))
@protocol GCDevice <NSObject>

/**
 The dispatch queue that element value change handlers are submitted on. The default queue is main, and setting this to any
 other queue will make value change handlers dispatch async on the given queue. This is useful if the main game loop
 of the application is not on main, or if input logic is handled on another thread from the main game loop.
 
 @see GCControllerAxisInput.valueChangedHandler
 @see GCControllerButtonInput.valueChangedHandler
 @see GCControllerButtonInput.pressedChangedHandler
 @see GCControllerDirectionPad.valueChangedHandler
 @see GCMotion.valueChangedHandler
 */
@property (nonatomic, strong) dispatch_queue_t handlerQueue API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0));

/**
 A vendor supplied name. May be nil, and is not guaranteed to be unique. This should not be used as a key in a dictionary,
 but simply as a way to present some basic information about the device in testing or to the user.
 */
@property (nonatomic, readonly, copy, nullable) NSString *vendorName API_AVAILABLE(macos(10.9), ios(7.0), tvos(9.0));

/**
 The product category the device belongs to. This is useful for setting appropriate UI elements based on what type of device is connected.
 
 @see GCProductCategories.h
 */
@property (nonatomic, readonly) NSString *productCategory API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0));

/**
 Gets the physical input profile for the device.

 @note This is equivalent to the controller's gamepad, microGamepad, or extendedGamepad instance.
 @see GCController.microGamepad
 @see GCController.extendedGamepad
*/
@property (nonatomic, strong, readonly) GCPhysicalInputProfile *physicalInputProfile API_DEPRECATED("Use the physicalInputProfile property on GCController instead.  For GCKeyboard, use the keyboardInput property.  For GCMouse, use the mouseInput property.", macos(11.0, 13.0), ios(14.0, 16.0), tvos(14.0, 16.0));



@end

NS_ASSUME_NONNULL_END
