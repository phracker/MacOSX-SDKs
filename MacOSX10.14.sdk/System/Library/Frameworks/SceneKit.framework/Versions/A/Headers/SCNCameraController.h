//
//  SCNCameraController.h
//  SceneKit
//
//  Copyright (c) 2017-2018 Apple Inc. All rights reserved.
//

#import <SceneKit/SceneKitTypes.h>

NS_ASSUME_NONNULL_BEGIN

@class SCNNode;
@class SCNCameraController;

// SCNInteractionMode specify the behavior of the camera relative to
// screen space interactions.
typedef NS_ENUM(NSInteger, SCNInteractionMode) {
    // Relative to up vector.
    SCNInteractionModeFly,
    SCNInteractionModeOrbitTurntable,            // rotate around target with absolute orientation from angles accumulation.
    // Up vector not taken into account.
    SCNInteractionModeOrbitAngleMapping,         // rotate around target by mapping 2D screen coordinates to spherical coordinates.
    SCNInteractionModeOrbitCenteredArcball,
    SCNInteractionModeOrbitArcball,              // rotate around target by mapping 2D screen coordinates to an half sphere.
    SCNInteractionModePan,                       // camera space translation on X/Y
    SCNInteractionModeTruck,                     // camera space translation on X/Z
} API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0))
@protocol SCNCameraControllerDelegate <NSObject>

@optional
- (void)cameraInertiaWillStartForController:(SCNCameraController *)cameraController;
- (void)cameraInertiaDidEndForController:(SCNCameraController *)cameraController;

@end

SCN_EXPORT API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0))
@interface SCNCameraController : NSObject

@property(nonatomic, assign, nullable) id <SCNCameraControllerDelegate> delegate;

@property(nonatomic, retain, nullable) SCNNode *pointOfView;
@property(nonatomic) SCNInteractionMode interactionMode;

// The camera target in world space for orbit rotation.
@property(nonatomic) SCNVector3 target;

// Automatically update the target in beginInteraction
// Defaults to NO
@property(nonatomic) BOOL automaticTarget;

// The up vector in world space used as reference for SCNInteractionModeFly and SCNInteractionModeOrbitTurntable camera modes.
// Defaults to (0, 1, 0).
@property(nonatomic) SCNVector3 worldUp;

// Set to YES to enable inertia on endInteraction.
// Defaults to NO.
@property(nonatomic) BOOL inertiaEnabled;

// The friction coefficient applied to the inertia.
// Defaults to 0.05.
@property(nonatomic) float inertiaFriction;

// Returns YES if inertia is running.
@property(nonatomic, readonly, getter=isInertiaRunning) BOOL inertiaRunning;

// Minimum and maximum vertical view angles in degrees for SCNInteractionModeFly and SCNInteractionModeOrbitTurntable.
// The angle constraints is not enforced if both vertical angle properties values are set to 0.
// The angle constraints will not be enforced if the initial orientation is outside the given range.
// The minimum angle must be inferior to the maximum angle.
// Angles are in world space and within the range [-90, 90].
// Defaults to 0.0.
// For example: set to minimum to 0 and maximum to 90 to only allow orbit around the top hemisphere.
@property(nonatomic) float minimumVerticalAngle;
@property(nonatomic) float maximumVerticalAngle;

// Minimum and maximum horizontal view angles in degrees for SCNInteractionModeFly and SCNInteractionModeOrbitTurntable.
// The angle constraints is not enforced if both horizontal angle properties values are set to 0.
// The angle constraints will not be enforced if the initial orientation is outside the given range.
// The minimum angle must be inferior to the maximum angle.
// Angles are in world space and within the range [-180, 180].
// Defaults to 0.0.
@property(nonatomic) float minimumHorizontalAngle;
@property(nonatomic) float maximumHorizontalAngle;

// Translate the camera along the local X/Y/Z axis.
- (void)translateInCameraSpaceByX:(float)deltaX Y:(float)deltaY Z:(float)deltaX;

// Move the camera to a position where the bounding sphere of all nodes is fully visible.
// Also set the camera target as the center of the bounding sphere.
- (void)frameNodes:(NSArray<SCNNode *> *)nodes;

// Rotate delta is in degrees.
- (void)rotateByX:(float)deltaX Y:(float)deltaY;

// Rotate the camera around the given screen space point. Delta is in degrees.
- (void)rollBy:(float)delta aroundScreenPoint:(CGPoint)point viewport:(CGSize)viewport;

// Zoom by moving the camera along the axis by a screen space point.
- (void)dollyBy:(float)delta onScreenPoint:(CGPoint)point viewport:(CGSize)viewport;

// Rotate the camera around the axis from the camera position to the target.
// Delta is in degrees.
- (void)rollAroundTarget:(float)delta;

// Zoom by moving the camera along the axis from the camera position to the target.
- (void)dollyToTarget:(float)delta;

// clear the camera roll if any
- (void)clearRoll;

// Stop current inertia.
- (void)stopInertia;

// Begin/Continue/End interaction using an input location relative to viewport.
// The behavior depends on the current interactionMode.
- (void)beginInteraction:(CGPoint)location withViewport:(CGSize)viewport;
- (void)continueInteraction:(CGPoint)location withViewport:(CGSize)viewport sensitivity:(CGFloat)sensitivity;
- (void)endInteraction:(CGPoint)location withViewport:(CGSize)viewport velocity:(CGPoint)velocity;

@end

NS_ASSUME_NONNULL_END
