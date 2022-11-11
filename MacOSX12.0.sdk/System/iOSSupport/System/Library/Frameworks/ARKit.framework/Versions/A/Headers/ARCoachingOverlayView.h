//
//  ARCoachingOverlayView.h
//  ARKit
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <UIKit/UIKit.h>


NS_ASSUME_NONNULL_BEGIN

@class ARSession;

@protocol ARCoachingOverlayViewDelegate;
@protocol ARSessionProviding;

/**
 A value describing the context required for successful coaching
 */
API_AVAILABLE(ios(13.0))
typedef NS_ENUM(NSInteger, ARCoachingGoal) {
    /** Session requires normal tracking */
    ARCoachingGoalTracking,
    /** Session requires a horizontal plane */
    ARCoachingGoalHorizontalPlane,
    /** Session requires a vertical plane */
    ARCoachingGoalVerticalPlane,
    /** Session requires one plane of any type */
    ARCoachingGoalAnyPlane,
    /** Session requires geo tracking */
    ARCoachingGoalGeoTracking,
} NS_SWIFT_NAME(ARCoachingOverlayView.Goal);

/**
 A view that guides users through session initialization
 
 @discussion The view will use context aware messaging and animations to instruct the user on gathering required info for the AR session.
 */
API_AVAILABLE(ios(13.0))
@interface ARCoachingOverlayView : UIView

/**
 Specifies the delegate used for callbacks
 */
@property (nonatomic, weak, nullable) IBOutlet id<ARCoachingOverlayViewDelegate> delegate;

/**
 A provider of a session to use

 @discussion This property can be used to set the `session` when loading from a storyboard. Setting this property at runtime will also
 set the `session` property.
 */
@property (nonatomic, weak, nullable) IBOutlet NSObject<ARSessionProviding> *sessionProvider;

/**
 The session that the view uses to update coaching
 */
@property (nonatomic, strong, nullable) ARSession *session;

/**
 The coaching type used to resolve what messaging to display to the user while activated
 Defaults to `ARCoachingGoalTracking`
 */
@property (nonatomic, assign) ARCoachingGoal goal;

/**
 Whether or not the view should activate/deactivate automatically, depending on the current state of the session
 Defaults to `YES`
 
 @discussion When set to automatically activate, the view will transition to active when the session loses normal tracking for a set amount
 of time.
 When tracking resumes and other requirements (based on `goal`) are met, the view will deactivate.
 */
@property (nonatomic, assign) BOOL activatesAutomatically;

/**
 Whether or not the view is currently active.

 @see -[ARCoachingOverlayView setActive:animated:]
 */
@property (nonatomic, readonly) BOOL isActive;

/**
 Transition the view to either an activated or deactivated state
 
 @discussion On activation the view will check the current session, and if relocalization is needed it will present a modified UI with
 relocalization coaching and a reset button.
 
 On deactivation the view will become hidden
 @param active Whether the view should activate, or deactivate
 @param animated Whether the view animated to activated/deactivated states, or transitions instantly

 @see -[ARCoachingOverlayViewDelegate coachingOverlayViewDidTriggerReset:]
 */
- (void)setActive:(BOOL)active animated:(BOOL)animated;

@end

API_AVAILABLE(ios(13.0))
@protocol ARCoachingOverlayViewDelegate <NSObject>

@optional

/**
 This is called when the user taps the reset button in the relocalization state

 @discussion By default, when the relocalization reset button is tapped, the overlay will call run on the session using the current
 `configuration`, and the `ARSessionRunOptionResetTracking` and `ARSessionRunOptionRemoveExistingAnchors` options. The delegate may
 implement this method to override this behavior. The delegate is then responsible for resetting the session.
 
 @param coachingOverlayView The view currently active
 */
- (void)coachingOverlayViewDidRequestSessionReset:(ARCoachingOverlayView *)coachingOverlayView;

/**
 This is called when the view activate, either manually or automatically
 
 @discussion The Developer may hide their application UI in in this callback, and take other appropriate actions to allow
 `ARCoachingOverlayView` to take over the full screen.
 @param coachingOverlayView The view that will be activated
 */
- (void)coachingOverlayViewWillActivate:(ARCoachingOverlayView *)coachingOverlayView;

/**
 This is called when the view has been deactivated, either manually or automatically
 
 @param coachingOverlayView The view that was deactivated
 */
- (void)coachingOverlayViewDidDeactivate:(ARCoachingOverlayView *)coachingOverlayView;

@end

NS_ASSUME_NONNULL_END

