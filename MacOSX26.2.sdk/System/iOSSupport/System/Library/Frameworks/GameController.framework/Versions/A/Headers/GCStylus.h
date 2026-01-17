//  
//  GCStylus.h
//  GameController
//
//  Copyright © 2025 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <GameController/GCExtern.h>
#import <GameController/GCDevice.h>


@class GCDeviceHaptics;
@protocol GCDevicePhysicalInput;

NS_ASSUME_NONNULL_BEGIN

/**
 *  A notification that posts after a stylus accessory connects to the device.
 *
 *  Use this constant with `NSNotificationCenter` to listen for stylus
 *  connection events.
 *
 *  Connections of stylus accessories will be reflected in the `styli` array
 *  of the `GCStylus` class when the notification posts.
 *
 *  The `object` property of the notification will contain the `GCStylus` that
 *  was connected.
 */
GAMECONTROLLER_EXPORT NSString * const GCStylusDidConnectNotification API_AVAILABLE(visionos(26.0)) API_UNAVAILABLE(macos, ios, tvos);

/**
 *  A notification that posts after a stylus accessory disconnects from the
 *  device.
 *
 *  Use this constant with `NSNotificationCenter` to listen for stylus
 *  disconnection events.
 *
 *  The `object` property of the notification will contain the `GCStylus` that
 *  was disconnected.
 */
GAMECONTROLLER_EXPORT NSString * const GCStylusDidDisconnectNotification API_AVAILABLE(visionos(26.0)) API_UNAVAILABLE(macos, ios, tvos);


/**
 *  An object that represents a physical stylus connected to the device.
 *
 *  Use the `styli` property to get the currently connect stylus accessories
 *  when your application starts.  Register for `GCStylusDidConnectNotification`
 *  and `GCStylusDidDisconnectNotification` to get notified when a stylus
 *  connects of disconnects while your application is running.
 *
 *  ```
 *  // Register for notifications
 *  NotificationCenter.default.addObserver(self, selector: #selector(stylus(didConnect:)), name: NSNotification.Name.GCStylusDidConnect, object: nil)
 *  NotificationCenter.default.addObserver(self, selector: #selector(stylus(didDisconnect:)), name: NSNotification.Name.GCStylusDidConnect, object: nil)
 *
 *  // Query current stylus devices
 *  for stylus in GCStylus.styluses {
 *      ...
 *  }
 *
 *  // Later, handle connection
 *  @objc func stylus(didConnect notification: Notification) {
 *      guard let stylus = notification.object as? GCStylus else { return }
 *      ...
 *  }
 *  ```
 *
 *  Check the `productCategory` to determine the type of stylus.  A spatial
 *  stylus - capable of 6DoF tracking by Apple Vision Pro - has a
 *  `GCProductCategorySpatialStylus` category.
 *
 *  Use the `input` property to get the input profile of the stylus.  A spatial
 *  stylus includes a pressure sensitive tip and an input cluster composed of
 *  two buttons.
 *
 *    - The primary button (`GCInputStylusPrimaryButton`) is the front button
 *      (closest to the stylus tip) in the input cluster of the stylus.  This
 *      button is frequently used grab virtual objects.
 *
 *    - The secondary button (`GCInputStylusSecondaryButton`) is the middle
 *      button in the input cluster.  It can measures pressure/force levels.
 *      It's intended to be used for controlling in-air drawing, selection,
 *      and generic interactions.
 *
 *    - The tip is also represented as a button (`GCInputStylusTip`).
 *
 *  ```
 *  guard let input = stylus.input else { return }
 *  input.inputStateQueueDepth = 20
 *  input.inputStateAvailableHandler = { input in
 *      // This block will be enqueued for execution when the state of
 *      // any stylus input changes.
 *
 *      // Iterate through all input state changes since last execution of
 *      // the block.
 *      while let nextState = input.nextInputState() {
 *          // Use the value of `pressedInput.isPressed` for binary
 *          // interactions, such as object selection.
 *          let primaryButtonPressed = nextState.buttons[.stylusPrimaryButton]?.pressedInput.isPressed
 *          let secondaryButtonPressed = nextState.buttons[.stylusSecondaryButton]?.pressedInput.isPressed
 *          // Use the normalized press value for analog actions such as
 *          // controlling virtual ink flow.
 *          let secondaryButtonPressure = nextState.buttons[.stylusSecondaryButton]?.pressedInput.value
 *          let tipPressure = nextState.buttons[.stylusTip]?.pressedInput.value
 *
 *          ...
 *      }
 *  }
 *  ```
 *
 *  Use the `haptics` property to get the haptics profile of the stylus.  A
 *  spatial stylus may optionally support haptic feedback to a single
 *  locality - `GCHapticsLocalityDefault`.
 */
API_AVAILABLE(visionos(26.0)) API_UNAVAILABLE(macos, ios, tvos)
@interface GCStylus : NSObject <GCDevice>



/**
 *  Gets the input profile for the stylus.
 *
 *  The input profile is represented as an object conforming to the
 *  `GCDevicePhysicalInput` protocol.  Use this object to discover available
 *  inputs on the stylus, including buttons and pressure sensors, and get
 *  notified when the state of those inputs change.
 */
@property (readonly, strong, nullable) id<GCDevicePhysicalInput> input;

/**
 *  Gets the haptics profile for the stylus, if supported.
 *
 *  The haptics profile is represented as a `GCDeviceHaptics` instance, from
 *  which you can create `CHHapticEngine` instances targeting the haptic
 *  actuator(s) in the accessory.
 *
 *  Not all stylus accessories support haptic feedback.  If the accessory
 *  does not support haptic feedback, this property is `nil`.
 *
 *  @note
 *  Haptics are a drain on the accessory's battery, and can be distracting when
 *  used excessively. Use haptic feedback judiciously and in response to
 *  meaningful user interactions.
 */
@property (readonly, strong, nullable) GCDeviceHaptics *haptics;

@end


@interface GCStylus (Discovery)

/**
 * Get the collection of stylus accessories currently connected to the device.
 *
 * This property returns an array of all currently connected stylus accessories.
 * The array is empty when no stylus accessories are connected.  The array
 * updates automatically as stylus accessories connect and disconnect.
 *
 * To be notified when the array changes, register for the 
 * `GCStylusDidConnectNotification` and `GCStylusDidDisconnectNotification`.
 */
@property (readonly, class) NSArray<GCStylus*> *styli;

@end

NS_ASSUME_NONNULL_END
