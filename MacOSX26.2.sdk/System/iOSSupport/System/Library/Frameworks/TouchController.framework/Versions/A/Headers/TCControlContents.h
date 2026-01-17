//
//  TCControlContents.h
//  TouchController
//

#if !TARGET_OS_OSX
#import <Foundation/Foundation.h>
#import <Metal/Metal.h>

#import <TouchController/TCTouchController.h>
#import <TouchController/TCControlLabel.h>
#import <TouchController/TCControlContents.h>

@class TCControlImage;

NS_ASSUME_NONNULL_BEGIN

/// Defines the visual shape of a button.
typedef NS_ENUM(NSInteger, TCControlContentsButtonShape) {
    /// A circular button shape.
    TCControlContentsButtonShapeCircle,
    /// A rectangular button shape.
    TCControlContentsButtonShapeRect,
} NS_SWIFT_NAME(TCControlContents.ButtonShape) API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(macCatalyst, visionos);

/// Defines the direction of a direction pad visual.
typedef NS_ENUM(NSInteger, TCControlContentsDpadDirection) {
    /// The up direction.
    TCControlContentsDpadDirectionUp,
    /// The down direction.
    TCControlContentsDpadDirectionDown,
    /// The left direction.
    TCControlContentsDpadDirectionLeft,
    /// The right direction.
    TCControlContentsDpadDirectionRight,
} NS_SWIFT_NAME(TCControlContents.DpadDirection) API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(macCatalyst, visionos);

/// Defines the visual style of the individual up/down/left/right elements of a direction pad.
typedef NS_ENUM(NSInteger, TCControlContentsDpadElementStyle) {
    /// A circular direction pad style.
    TCControlContentsDpadElementStyleCircle,
    /// A pentagon direction pad style.
    TCControlContentsDpadElementStylePentagon,
} NS_SWIFT_NAME(TCControlContents.DpadElementStyle) API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(macCatalyst, visionos);

/// Represents the visual contents of a touch control.
__attribute__((visibility ("default")))
API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(macCatalyst, visionos)
@interface TCControlContents : NSObject

/// Creates a new instance with the specified images.
///
/// - Parameters:
///   - images: An array of `TCControlImage` objects to use for the contents.
/// - Returns: A new `TCControlContents` instance.
+ (instancetype)contentsWithImages:(NSArray<TCControlImage *> *)images;

/// The button contents for the specified system image name, size, and shape.
///
/// - Parameters:
///   - imageName: The name of the system image to use for the button.
///   - size: The size of the button in points.
///   - shape: The shape of the button.
///   - controller: The touch controller to create control contents for.
/// - Returns: The `TCControlContents` for the button.
+ (TCControlContents *)buttonContentsForSystemImageNamed:(NSString *)imageName size:(CGSize)size shape:(TCControlContentsButtonShape)shape controller:(TCTouchController *)controller;

/// The switch contents for the specified system image name, size, and shape.
///
/// - Parameters:
///   - imageName: The name of the system image to use for the switch button.
///   - size: The size of the switch button in points.
///   - shape: The shape of the switch button.
///   - controller: The touch controller to create control contents for.
/// - Returns: The `TCControlContents` for the switch button.
+ (TCControlContents *)switchedOnContentsForSystemImageNamed:(NSString *)imageName size:(CGSize)size shape:(TCControlContentsButtonShape)shape controller:(TCTouchController *)controller;

/// The thumbstick stick contents for the specified size.
///
/// - Parameters:
///   - size: The size of the thumbstick stick in points.
///   - controller: The touch controller to create control contents for.
/// - Returns: The `TCControlContents` for the thumbstick stick.
+ (TCControlContents *)thumbstickStickContentsOfSize:(CGSize)size controller:(TCTouchController *)controller NS_SWIFT_NAME(thumbstickStickContents(size:controller:));

/// The thumbstick background contents for the specified size.
///
/// - Parameters:
///   - size: The size of the thumbstick background in points.
///   - controller: The touch controller to create control contents for.
/// - Returns: The `TCControlContents` for the thumbstick background.
+ (TCControlContents *)thumbstickBackgroundContentsOfSize:(CGSize)size controller:(TCTouchController *)controller NS_SWIFT_NAME(thumbstickStickBackgroundContents(size:controller:));

/// The throttle indicator contents for the specified size.
///
/// - Parameters:
///   - size: The size of the throttle indicator in points.
///   - controller: The touch controller to create control contents for.
/// - Returns: The `TCControlContents` for the throttle indicator.
+ (TCControlContents *)throttleIndicatorContentsOfSize:(CGSize)size controller:(TCTouchController *)controller NS_SWIFT_NAME(throttleIndicatorContents(size:controller:));

/// The throttle background contents for the specified size.
///
/// - Parameters:
///   - size: The size of the throttle background in points.
///   - controller: The touch controller to create control contents for.
/// - Returns: The `TCControlContents` for the throttle background.
+ (TCControlContents *)throttleBackgroundContentsOfSize:(CGSize)size controller:(TCTouchController *)controller NS_SWIFT_NAME(throttleBackgroundContents(size:controller:));

/// The direction pad contents for the specified label, size, style, and direction.
///
/// - Parameters:
///   - label: The label for the direction pad.
///   - size: The size of the direction pad in points.
///   - style: The style of the direction pad.
///   - direction: The direction of the direction pad visual.
///   - controller: The touch controller to create control contents for.
/// - Returns: The `TCControlContents` for the direction pad.
+ (TCControlContents *)directionPadContentsForLabel:(TCControlLabel *)label size:(CGSize)size style:(TCControlContentsDpadElementStyle)style direction:(TCControlContentsDpadDirection)direction controller:(TCTouchController *)controller NS_SWIFT_NAME(directionPadContents(label:size:style:direction:controller:));

/// Not available. Use `contentsWithImages:` to create a `TCControlContents`.
- (instancetype)init NS_UNAVAILABLE;

/// The array of objects used to render the control.
@property (nonatomic, strong, readonly) NSArray<TCControlImage *> *images;

@end

NS_ASSUME_NONNULL_END
#endif
