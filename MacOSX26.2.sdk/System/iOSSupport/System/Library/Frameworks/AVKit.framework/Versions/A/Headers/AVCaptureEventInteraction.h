/*
	File:  AVCaptureEventInteraction.h
	
	Framework:  AVKit
	
	Copyright © 2022-2025 Apple Inc. All rights reserved.
	
	To report bugs, go to:  http://developer.apple.com/bugreporter/

 */


#import <Foundation/Foundation.h>

#if TARGET_OS_MACCATALYST
#import <AVKit/AVKitDefines.h>
#else
#import <AVKit/AVKitDefines.h>
#endif // TARGET_OS_MACCATALYST
#import <AVKit/AVCaptureEvent.h>
#import <UIKit/UIInteraction.h>


NS_ASSUME_NONNULL_BEGIN

// MARK: -

/*!
 * An object that registers handlers to respond to capture events from system hardware buttons.
 *
 * The system Camera app allows people to perform capture functions by pressing hardware buttons on their iOS device. UIKit apps can add similar functionality by using this type to register handlers that respond to interactions from device hardware.
 *
 * > Note:
 * > In SwiftUI, respond to capture events from hardware buttons using <doc://com.apple.documentation/documentation/swiftui/view/oncameracaptureevent(isenabled:action:)> and <doc://com.apple.documentation/documentation/swiftui/view/oncameracaptureevent(isenabled:primaryaction:secondaryaction:)> instead.
 *
 * The following example shows how to add a handler that captures a photo when a user presses a hardware button on their device.
 *
 * ```swift
 * class CameraViewController: UIViewController {
 *
 *     /// An object that manages the camera functionality.
 *     private let camera = CameraModel()
 *
 *     /// A capture event interaction to handle hardware button presses.
 *     private var eventInteraction: AVCaptureEventInteraction?
 *
 *     override func viewDidLoad() {
 *         super.viewDidLoad()
 *         // Configure the app to take a photo on hardware button press.
 *         configureHardwareInteraction()
 *     }
 *
 *     private func configureHardwareInteraction() {
 *         // Create a new capture event interaction with a handler that captures a photo.
 *         let interaction = AVCaptureEventInteraction { [weak self] event in
 *             // Capture a photo on "press up" of a hardware button.
 *             if event.phase == .ended {
 *                 self?.camera.capturePhoto()
 *             }
 *         }
 *         // Add the interaction to the view controller's view.
 *         view.addInteraction(interaction)
 *         eventInteraction = interaction
 *     }
 * }
 * ```
 *
 *
 * The event handler queries the capture event to determine its phase, and when the interaction ends, captures a photo.
 *
 * > Important:
 * > You can only use this API for capture use cases. The system sends capture events only to apps that actively use the camera. Backgrounded capture apps, and apps not performing capture, don't receive events.
 * >
 * > Adopting this API overrides default hardware button behavior, so apps must always respond appropriately to any events received. Failing to handle events results in a nonfunctional button that provides a poor user experience. If your app is temporarily unable to handle events, disable the interaction by setting its ``isEnabled`` property to `false`, which restores the system button behavior.
 */
API_AVAILABLE(ios(17.2)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(macos, tvos, watchos)
@interface AVCaptureEventInteraction : NSObject <UIInteraction>

AVKIT_INIT_UNAVAILABLE

/*!
 * Creates a capture event interaction with a handler that responds to presses of hardware buttons.
 *
 * - Parameter handler: An event handler the system calls when a person performs a primary or secondary capture event.
 */
- (instancetype)initWithEventHandler:(void (^)(AVCaptureEvent *event))handler NS_SWIFT_NAME(init(handler:));

/*!
 *	Creates a capture event interaction with handlers that respond independently to presses of hardware buttons.
 *
 * - Parameter primaryHandler: An event handler the system calls when a person performs a primary capture event.
 * - Parameter secondaryHandler: An event handler the system calls when a person performs a secondary capture event.
 */
- (instancetype)initWithPrimaryEventHandler:(void (^)(AVCaptureEvent *event))primaryHandler secondaryEventHandler:(void (^)(AVCaptureEvent *event))secondaryHandler NS_SWIFT_NAME(init(primary:secondary:));

/*!
 * A Boolean value that indicates whether this capture event interaction is in an enabled state.
 *
 * Set this value to `false` when your app can’t or won’t respond to the action callbacks to avoid non-interactive buttons or UI elements.
 */
@property (nonatomic, readwrite, getter=isEnabled) BOOL enabled;

/*!
 * A Boolean value that indicates whether the default sound is in a disabled state.
 *
 * If `true`, you must handle sound playback for capture events manually using the ``AVCaptureEvent/playSound:`` method.
 *
 * > Important: To use AirPods Camera Control, it must be available in your country or region. AirPods Camera Control is not currently available in the European Union.
 */
@property (class, nonatomic, readwrite) BOOL defaultCaptureSoundDisabled API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(visionos, macCatalyst) API_UNAVAILABLE(macos, tvos, watchos);

@end

NS_ASSUME_NONNULL_END
