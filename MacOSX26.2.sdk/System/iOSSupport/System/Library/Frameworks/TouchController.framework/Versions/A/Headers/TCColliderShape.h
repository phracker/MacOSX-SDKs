//
//  TCColliderShape.h
//  TouchController
//

#if !TARGET_OS_OSX
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/// Defines the shape of a control collider.
typedef NS_ENUM(NSInteger, TCColliderShape) {
    /// A circular collider.
    TCColliderShapeCircle,
    /// A rectangular collider.
    TCColliderShapeRect,
    /// A collider representing the left side of the view the touch controller is embedded in. Useful for thumbsticks and delta controls, so the user can easily hit the control without looking closely.
    TCColliderShapeLeftSide,
    /// A collider representing the right side of the view the touch controller is embedded in. Useful for thumbsticks and delta controls, so the user can easily hit the control without looking closely.
    TCColliderShapeRightSide,
} API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(macCatalyst, visionos);

NS_ASSUME_NONNULL_END
#endif
