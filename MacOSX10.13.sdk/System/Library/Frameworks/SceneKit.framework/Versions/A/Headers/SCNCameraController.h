//
//  SCNCameraController.h
//
//  Copyright (c) 2013-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SceneKit/SceneKitTypes.h>

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

@protocol SCNCameraControllerDelegate <NSObject>

@optional
- (void)cameraInertiaWillStartForController:(SCNCameraController*)cameraController;
- (void)cameraInertiaDidEndForController:(SCNCameraController*)cameraController;

@end

API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0))
@interface SCNCameraController : NSObject

@property(nonatomic, assign) id<SCNCameraControllerDelegate> delegate;

@property(nonatomic, retain) SCNNode* pointOfView;
@property(nonatomic, assign) SCNInteractionMode interactionMode;

// The camera target in world space for orbit rotation.
@property(nonatomic, assign) SCNVector3 target;

// Automatically update the target in beginInteraction
@property(nonatomic, assign) BOOL automaticTarget;   //default to NO

// The up vector in world space used as reference for SCNInteractionModeFly and SCNInteractionModeOrbitTurntable camera modes.
// Default to UnitY(0, 1, 0).
@property(nonatomic, assign) SCNVector3 worldUp;

// Set to YES to enable inertia on endInteraction.
// Default to NO.
@property(nonatomic, assign) BOOL inertiaEnabled;

// The friction coefficient applied to the inertia.
// Default to 0.05.
@property(nonatomic, assign) float inertiaFriction;

// Returns YES if inertia is running.
@property(nonatomic, readonly, getter = isInertiaRunning) BOOL inertiaRunning;

// Minimum and maximum vertical view angles in degree for Fly mode and Turntable.
// The angle constraints is not enforced if both vertical angle properties values are set to 0.
// The angle constraints will not be enforced if the initial orientation is outside the given range.
// The minimum angle must be inferior to the maximum angle.
// Angles are in world space and between the range [-90, 90].
// Default value is 0.
// For example: set to minimum to 0 and maximum to 90 to only allow orbit around the top hemisphere.
@property(nonatomic, assign) float minimumVerticalAngle;
@property(nonatomic, assign) float maximumVerticalAngle;

// Minimum and maximum horizontal view angles in degree for Fly mode and Turntable.
// The angle constraints is not enforced if both horizontal angle properties values are set to 0.
// The angle constraints will not be enforced if the initial orientation is outside the given range.
// The minimum angle must be inferior to the maximum angle.
// Angles are in world space and between the range [-180, 180].
// Default value is 0.
@property(nonatomic, assign) float minimumHorizontalAngle;
@property(nonatomic, assign) float maximumHorizontalAngle;

// Translate the camera along the local X/Y/Z axis.
- (void)translateInCameraSpaceByX:(float)deltaX Y:(float)deltaY Z:(float)deltaX;

// Move the camera to a position where the bounding sphere of all nodes is fully visible.
// Also set the camera target has the center of the bounding sphere.
- (void)frameNodes:(NSArray<SCNNode*>*)nodes;

// Rotate delta is in degree.
- (void)rotateByX:(float)deltaX Y:(float)deltaY;

// Rotate the camera around the given screen space point. Delta is in degree.
- (void)rollBy:(float)delta aroundScreenPoint:(CGPoint)point viewport:(CGSize)viewport;

// Zoom by moving the camera along the axis by a screen space point.
- (void)dollyBy:(float)delta onScreenPoint:(CGPoint)point viewport:(CGSize)viewport;

// Rotate the camera around the axis from the camera position to the target.
// Delta is in degree.
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
