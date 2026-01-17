//
//  TCControlLabel.h
//  TouchController
//

#if !TARGET_OS_OSX
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/// Defines the role for a control label. This determines the type of control on
/// the touch controller's associated GCController.
typedef NS_ENUM(NSInteger, TCControlLabelRole) {
    /// A label for a button input controller.
    TCControlLabelRoleButton,
    /// A label for a direction pad controller.
    TCControlLabelRoleDirectionPad,
} NS_SWIFT_NAME(TCControlLabel.Role) API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(macCatalyst, visionos);

/// A label you associate with a touch control and provides a semantic description.
__attribute__((visibility ("default")))
API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(macCatalyst, visionos)
@interface TCControlLabel : NSObject

/// Creates a pre-configured label for the "A" button.
@property (class, nonatomic, strong, readonly) TCControlLabel *buttonA;
/// Creates a pre-configured label for the "B" button.
@property (class, nonatomic, strong, readonly) TCControlLabel *buttonB;
/// Creates a pre-configured label for the "X" button.
@property (class, nonatomic, strong, readonly) TCControlLabel *buttonX;
/// Creates a pre-configured label for the "Y" button.
@property (class, nonatomic, strong, readonly) TCControlLabel *buttonY;
/// Creates a pre-configured label for the "Menu" button.
@property (class, nonatomic, strong, readonly) TCControlLabel *buttonMenu;
/// Creates a pre-configured label for the "Options" button.
@property (class, nonatomic, strong, readonly) TCControlLabel *buttonOptions;
/// Creates a pre-configured label for the left shoulder button.
@property (class, nonatomic, strong, readonly) TCControlLabel *buttonLeftShoulder;
/// Creates a pre-configured label for the left trigger button.
@property (class, nonatomic, strong, readonly) TCControlLabel *buttonLeftTrigger;
/// Creates a pre-configured label for the right shoulder button.
@property (class, nonatomic, strong, readonly) TCControlLabel *buttonRightShoulder;
/// Creates a pre-configured label for the right trigger button.
@property (class, nonatomic, strong, readonly) TCControlLabel *buttonRightTrigger;
/// Creates a pre-configured label for the left thumbstick.
@property (class, nonatomic, strong, readonly) TCControlLabel *leftThumbstick;
/// Creates a pre-configured label for the left thumbstick button.
@property (class, nonatomic, strong, readonly) TCControlLabel *leftThumbstickButton;
/// Creates a pre-configured label for the right thumbstick.
@property (class, nonatomic, strong, readonly) TCControlLabel *rightThumbstick;
/// Creates a pre-configured label for the right thumbstick button.
@property (class, nonatomic, strong, readonly) TCControlLabel *rightThumbstickButton;
/// Creates a pre-configured label for the direction pad.
@property (class, nonatomic, strong, readonly) TCControlLabel *directionPad;

- (instancetype)init NS_UNAVAILABLE;

/// Creates a new instance with the provided name and type.
///
/// - Parameters:
///   - name: The name of the control label. Corresponds to the input name on the game controller's physical input profile.
///   - role: The role of the control label. Corresponds to the type of the `GCControllerElement`on the `GCController`.
/// - Returns: A new `TCControlLabel` instance.
- (instancetype)initWithName:(NSString *)name role:(TCControlLabelRole)role;

/// The name of the control label that you use for lookup on a game controller instance.
@property (nonatomic, retain, readonly) NSString *name;
/// The type of the control label.
@property (nonatomic, assign, readonly) TCControlLabelRole role;

@end


NS_ASSUME_NONNULL_END
#endif
