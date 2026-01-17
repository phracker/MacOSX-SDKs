//
//  TCTouchController.h
//  TouchController
//

#if !TARGET_OS_OSX
#import <Foundation/Foundation.h>

#import <Metal/Metal.h>
#import <GameController/GameController.h>

#import <TouchController/TCControl.h>

@class TCButton;
@class TCButtonDescriptor;

@class TCSwitch;
@class TCSwitchDescriptor;

@class TCThumbstick;
@class TCThumbstickDescriptor;

@class TCDirectionPad;
@class TCDirectionPadDescriptor;

@class TCTouchpad;
@class TCTouchpadDescriptor;

@class TCThrottle;
@class TCThrottleDescriptor;

@class TCTouchControllerDescriptor;

NS_ASSUME_NONNULL_BEGIN

__attribute__((visibility ("default"))) extern NSString *const TCGameControllerProductCategoryTouchController API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(macCatalyst, visionos);

/// An object that allows you to create and customize on-screen touch controls for a game that uses Metal.
///
/// The controller exposes controls through a <doc://com.apple.documentation/documentation/gamecontroller/gccontroller>
/// instance, and enables seamless integration with the <doc://com.apple.documentation/documentation/gamecontroller>
/// framework.
///
/// This class manages the lifecycle of touch controls, handles user interaction, renders the controls using Metal,
/// and provides a `GCController` instance that reflects the state of the on-screen controls.
__attribute__((visibility ("default")))
API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(macCatalyst, visionos)
@interface TCTouchController : NSObject

/// Whether touch controllers are supported for the device.
///
/// Attempting to create a touch controller on an unsupported device will result in a fatal error.
@property (class, nonatomic, readonly, getter=isSupported) BOOL supported;

/// The Metal device the touch control uses for rendering the touch controls.
@property (nonatomic, readonly) id<MTLDevice> device;

/// An array containing all the touch controls managed by this controller.
@property (nonatomic, readonly) NSArray<id<TCControl>> *controls;

/// An array containing all the button controls managed by this controller.
@property (nonatomic, readonly) NSArray<TCButton *> *buttons;

/// An array containing all the switch controls managed by this controller.
@property (nonatomic, readonly) NSArray<TCSwitch *> *switches;

/// An array containing all the thumbstick controls managed by this controller.
@property (nonatomic, readonly) NSArray<TCThumbstick *> *thumbsticks;

/// An array containing all the direction pad controls managed by this controller.
@property (nonatomic, readonly) NSArray<TCDirectionPad *> *directionPads;

/// An array containing all the throttle controls managed by this controller.
@property (nonatomic, readonly) NSArray<TCThrottle *> *throttles;

/// An array containing all the touchpad controls managed by this controller.
@property (nonatomic, readonly) NSArray<TCTouchpad *> *touchpads;

/// The size of the view the touch controller's drawable is embedded in, in points.
@property (nonatomic, readwrite, assign) CGSize size;

/// The size of the drawable to which the touch controller's contents be drawn, in native pixels.
@property (nonatomic, readwrite, assign) CGSize drawableSize;

/// Creates a new instance with the provided descriptor.
///
/// - Parameters:
///   - descriptor: The `TCTouchControllerDescriptor` containing the configuration for the touch controller.
/// - Returns: A new `TCTouchController` instance.
- (instancetype)initWithDescriptor:(TCTouchControllerDescriptor *)descriptor;

/// Automatically lays out the provided control labels, creating them if needed.
///
/// - Parameters:
///   - labels: An array of `TCControlLabel` objects to be laid out.
- (void)automaticallyLayoutControlsForLabels:(NSArray<TCControlLabel *> *)labels;

// MARK: Layout

/// Creates a new button control with the provided descriptor, and adds it to the touch controller.
///
/// - Parameters:
///   - descriptor: The `TCButtonDescriptor` containing the configuration for the button.
/// - Returns: A new `TCButton` instance.
- (TCButton *)addButtonWithDescriptor:(TCButtonDescriptor *)descriptor NS_SWIFT_NAME(addButton(descriptor:));

/// Creates a new switch control with the provided descriptor, and adds it to the touch controller.
///
/// - Parameters:
///   - descriptor: The `TCSwitchDescriptor` containing the configuration for the switch.
/// - Returns: A new `TCSwitch` instance.
- (TCSwitch *)addSwitchWithDescriptor:(TCSwitchDescriptor *)descriptor NS_SWIFT_NAME(addSwitch(descriptor:));

/// Creates a new thumbstick control with the provided descriptor, and adds it to the touch controller.
///
/// - Parameters:
///   - descriptor: The `TCThumbstickDescriptor` containing the configuration for the thumbstick.
/// - Returns: A new `TCThumbstick` instance.
- (TCThumbstick *)addThumbstickWithDescriptor:(TCThumbstickDescriptor *)descriptor NS_SWIFT_NAME(addThumbstick(descriptor:));

/// Creates a new direction pad control with the provided descriptor, and adds it to the touch controller.
///
/// - Parameters:
///   - descriptor: The `TCDirectionPadDescriptor` containing the configuration for the direction pad.
/// - Returns: A new `TCDirectionPad` instance.
- (TCDirectionPad *)addDirectionPadWithDescriptor:(TCDirectionPadDescriptor *)descriptor NS_SWIFT_NAME(addDirectionPad(descriptor:));

/// Creates a new throttle control with the provided descriptor, and adds it to the touch controller.
///
/// - Parameters:
///   - descriptor: The `TCThrottleDescriptor` containing the configuration for the throttle.
/// - Returns: A new `TCThrottle` instance.
- (TCThrottle *)addThrottleWithDescriptor:(TCThrottleDescriptor *)descriptor NS_SWIFT_NAME(addThrottle(descriptor:));

/// Creates a new touchpad control with the provided descriptor, and adds it to the touch controller.
///
/// - Parameters:
///   - descriptor: The `TCTouchpadDescriptor` containing the configuration for the touchpad.
/// - Returns: A new `TCTouchpad` instance.
- (TCTouchpad *)addTouchpadWithDescriptor:(TCTouchpadDescriptor *)descriptor NS_SWIFT_NAME(addTouchpad(descriptor:));

/// Removes all controls from the touch controller.
- (void)removeAllControls;

/// Removes the control from the touch controller.
- (void)removeControl:(id<TCControl>)control;

// MARK: User Interaction

/// The control at the specified point, if any.
///
/// - Parameters:
///   - point: The point to check for a control.
/// - Returns: The control at the specified point, or `nil` if no control is found.
- (nullable id<TCControl>)controlAtPoint:(CGPoint)point;

/// Handles a touch began event at the specified point.
///
/// - Parameters:
///   - point: The point where the touch began.
///   - index: An integer representing a unique index for the touch
/// - Returns: `YES` if the touch was handled by a control; otherwise `NO`.
- (BOOL)handleTouchBeganAtPoint:(CGPoint)point index:(NSInteger)index;

/// Handles a touch moved event at the specified point.
///
/// - Parameters:
///   - point: The point where the touch moved to.
///   - index: An integer representing a unique index for the touch
/// - Returns: `YES` if the touch was handled by a control, `NO` otherwise.
- (BOOL)handleTouchMovedAtPoint:(CGPoint)point index:(NSInteger)index;

/// Handles a touch ended event at the specified point.
///
/// - Parameters:
///   - point: The point where the touch ended.
///   - index: An integer representing a unique index for the touch
/// - Returns: `YES` if the touch was handled by a control, `NO` otherwise.
- (BOOL)handleTouchEndedAtPoint:(CGPoint)point index:(NSInteger)index;

// MARK: Rendering

/// Renders the touch controls using the provided Metal render command encoder.
///
/// - Parameters:
///   - encoder: The `MTLRenderCommandEncoder` to use for rendering.
- (void)renderUsingRenderCommandEncoder:(id<MTLRenderCommandEncoder>)encoder;

// MARK: Game Controller

/// A Boolean value that indicates whether the touch controller is connected to the Game Controller framework.
@property (nonatomic, assign, readonly, getter=isConnected) BOOL connected;

/// Connects the touch controller to the app, allowing its controls to be drawn and an associated `GCController` to be created.
- (void)connect;

/// Disconnects the touch controller from the app, preventing its controls from being drawn.
- (void)disconnect;

/// The game controller instance associated with this touch controller.
@property (nonatomic, strong, readonly) GCController *controller;

@end

NS_ASSUME_NONNULL_END
#endif
