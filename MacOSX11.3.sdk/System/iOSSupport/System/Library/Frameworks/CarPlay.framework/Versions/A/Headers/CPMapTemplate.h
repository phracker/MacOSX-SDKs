//
//  CPMapTemplate.h
//  CarPlay
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//


#import <CarPlay/CPBarButtonProviding.h>
#import <CarPlay/CPMapButton.h>
#import <CarPlay/CPNavigationAlert.h>
#import <CarPlay/CPNavigationSession.h>
#import <CarPlay/CPTemplate.h>
#import <CarPlay/CPTrip.h>
#import <CarPlay/CPTripPreviewTextConfiguration.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_OPTIONS(NSInteger, CPPanDirection) {
    CPPanDirectionNone = 0,
    CPPanDirectionLeft = 1 << 0,
    CPPanDirectionRight = 1 << 1,
    CPPanDirectionUp = 1 << 2,
    CPPanDirectionDown = 1 << 3,
} API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(macos, watchos, tvos);

typedef NS_OPTIONS(NSInteger, CPManeuverDisplayStyle) {
    CPManeuverDisplayStyleDefault,
    CPManeuverDisplayStyleLeadingSymbol,
    CPManeuverDisplayStyleTrailingSymbol,
    CPManeuverDisplayStyleSymbolOnly,
    CPManeuverDisplayStyleInstructionOnly
} API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(macos, watchos, tvos);

typedef NS_ENUM(NSUInteger, CPTimeRemainingColor) {
    CPTimeRemainingColorDefault = 0,
    CPTimeRemainingColorGreen,
    CPTimeRemainingColorOrange,
    CPTimeRemainingColorRed,
} API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(macos, watchos, tvos);

typedef NS_ENUM(NSUInteger, CPTripEstimateStyle) {
    CPTripEstimateStyleLight = 0,
    CPTripEstimateStyleDark
} API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(macos, watchos, tvos);

@protocol CPMapTemplateDelegate;

API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface CPMapTemplate : CPTemplate <CPBarButtonProviding>

/**
 Background color to use when displaying guidance. The system will automatically determine if the provided
 color meets contrast requirements. If the provided color does not meet contrast requirements, the system
 default will be used. Font color will automatically be adjusted by the system to correspond with this color.
 Alpha values will be ignored.
 */
@property (nonatomic, strong) UIColor *guidanceBackgroundColor;

/**
 The style used to display trip estimates during active navigation. If not set, will update automatically with changes to UIUserInterfaceStyle.
 */
@property (nonatomic, assign) CPTripEstimateStyle tripEstimateStyle;

/**
 An array of bar buttons to be displayed on the trailing bottom corner of the map template.
 @note The map template may display a maximum of 4 buttons. Setting more than 4 buttons to this
 property will only display the first 4 buttons.
 */
@property (nonatomic, strong) NSArray<CPMapButton *> *mapButtons;

/**
 * Display a preview for a trip. Used to provide an overview for the upcoming trip or can show multiple trip options,
 * such as for search results. Trip previews can appear over an active navigation session. Number of trips will be
 * limited to 12.
 */
- (void)showTripPreviews:(NSArray<CPTrip *> *)tripPreviews textConfiguration:(nullable CPTripPreviewTextConfiguration *)textConfiguration;

/**
* Display a preview for a trip. Used to provide an overview for the upcoming trip or can show multiple trip options,
* such as for search results. Trip previews can appear over an active navigation session. Number of trips will be
* limited to 12. Optionally provide a CPTrip object from the list of trips to be selected when initially presented.
*/
- (void)showTripPreviews:(NSArray<CPTrip *> *)tripPreviews selectedTrip:(nullable CPTrip *)selectedTrip textConfiguration:(nullable CPTripPreviewTextConfiguration *)textConfiguration API_AVAILABLE(ios(14.0));

/**
 * Display the route choices for a single trip. Trip previews can appear over an active navigation session.
 */
- (void)showRouteChoicesPreviewForTrip:(CPTrip *)tripPreview textConfiguration:(nullable CPTripPreviewTextConfiguration *)textConfiguration;

/**
 * Stop displaying any currently shown trip previews.
 */
- (void)hideTripPreviews;

/**
 * Updates the arrival time, time remaining and distance remaining estimates for a trip preview or actively navigating trip with the default color for time remaining.
 */
- (void)updateTravelEstimates:(CPTravelEstimates *)estimates forTrip:(CPTrip *)trip;

/**
 * Updates the arrival time, time remaining and distance remaining estimates for a trip preview or actively navigating trip with a specified color for time remaining.
 */
- (void)updateTravelEstimates:(CPTravelEstimates *)estimates forTrip:(CPTrip *)trip withTimeRemainingColor:(CPTimeRemainingColor)timeRemainingColor;

/**
 * Begins guidance for a trip.
 @return CPNavigationSession maintain a reference to the navigation session to perform guidance updates
 */
- (CPNavigationSession *)startNavigationSessionForTrip:(CPTrip *)trip;

/**
 Automatically shows and hides the navigation bar. Defaults to YES.
 */
@property (nonatomic, assign) BOOL automaticallyHidesNavigationBar;

/**
 Hides the map buttons when hiding the navigation bar. Defaults to YES.
 */
@property (nonatomic, assign) BOOL hidesButtonsWithNavigationBar;

@property (nullable, nonatomic, weak) id<CPMapTemplateDelegate> mapDelegate;


#pragma mark - Panning

/**
 Shows the panning interface on the map interface if not already visible.

 When showing the panning interface, a maximum of two mapButtons will be visible.
 If more than two mapButtons are visible when the template transitions to panning mode,
 the system will hide one or more map buttons beginning from the end of the mapButtons array.

 @note The system will not provide a button to dismiss the UI. You are required to provide
 a button in the map template navigation bar that will dismiss the panning interface.
 */
- (void)showPanningInterfaceAnimated:(BOOL)animated;

/**
 Dismisses the panning interface on the map interface if it is visible.
 @note When dismissing the panning interface, mapButtons previously hidden by the system will no longer be hidden.
 */
- (void)dismissPanningInterfaceAnimated:(BOOL)animated;

/**
 Returns YES when the panning interface is visible.
 */
@property (nonatomic, readonly, getter=isPanningInterfaceVisible) BOOL panningInterfaceVisible;

#pragma mark - Navigation Alerts

/**
 The currently-visible navigation alert, if any.
 */
@property (nullable, nonatomic, readonly, strong) CPNavigationAlert *currentNavigationAlert;

/**
 Display a navigation alert on this map template. Your @c CPMapTemplateDelegate will be notified
 of navigation alert lifecycle events.

 @param navigationAlert The navigation alert to display.
 @param animated YES to animate the presentation of this alert, or NO to display it immediately.

 @warning If a navigation alert is already visible, this method has no effect.
 You must dismiss the currently-visible navigation alert before presenting a new alert.
 */
- (void)presentNavigationAlert:(CPNavigationAlert *)navigationAlert animated:(BOOL)animated;

/**
 Dismiss the currently-visible navigation alert on this map template.

 @param animated Whether the dismissal should be animated (YES) or not (NO).
 @param completion A block invoked after the alert has been dismissed. The BOOL argument
 in the completion block indicates whether any visible alert was dismissed (YES) or
 if no action was taken because there was no alert to dismiss (NO).
 */
- (void)dismissNavigationAlertAnimated:(BOOL)animated completion:(void (^)(BOOL dismissed))completion;

@end

API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(macos, watchos, tvos)
@protocol CPMapTemplateDelegate <NSObject>
@optional

#pragma mark - Notification Policy
/**
 Determines if the maneuver should be presented as a notification when the app is in the background.
 @return YES if the maneuver should appear as a notification, otherwise NO
 */
- (BOOL)mapTemplate:(CPMapTemplate *)mapTemplate shouldShowNotificationForManeuver:(CPManeuver *)maneuver;

/**
 Determines if the updated distance remaining for the maneuver should be presented as a notification when the app is in the background.
  @return YES if the updated estimates should appear in the notification, otherwise NO
 */
- (BOOL)mapTemplate:(CPMapTemplate *)mapTemplate shouldUpdateNotificationForManeuver:(CPManeuver *)maneuver withTravelEstimates:(CPTravelEstimates *)travelEstimates;

/**
 Determines if the navigation alert should be presented as a notification when the app is in the background.
  @return YES if the alert should appear as a notification, otherwise NO
 */
- (BOOL)mapTemplate:(CPMapTemplate *)mapTemplate shouldShowNotificationForNavigationAlert:(CPNavigationAlert *)navigationAlert;

#pragma mark - Panning
/**
 This will be called when the pan interface appears on the map interface.
 */
- (void)mapTemplateDidShowPanningInterface:(CPMapTemplate *)mapTemplate;

/**
 This will be called when the pan interface will disappear on the map interface.
 */
- (void)mapTemplateWillDismissPanningInterface:(CPMapTemplate *)mapTemplate;

/**
 This will be called when the pan interface disappears on the map interface.
 */
- (void)mapTemplateDidDismissPanningInterface:(CPMapTemplate *)mapTemplate;

/**
 Called when a pan button is pressed/selected for an extended duration.
 */
- (void)mapTemplate:(CPMapTemplate *)mapTemplate panBeganWithDirection:(CPPanDirection)direction;

/**
 Called when a pan button is released after an extended duration.
 */
- (void)mapTemplate:(CPMapTemplate *)mapTemplate panEndedWithDirection:(CPPanDirection)direction;

/**
 Called when a pan button is pressed/selected momentarily.
 */
- (void)mapTemplate:(CPMapTemplate *)mapTemplate panWithDirection:(CPPanDirection)direction;

/**
 Called when a pan gesture begins. May not be called when connected to some CarPlay systems.
 */
- (void)mapTemplateDidBeginPanGesture:(CPMapTemplate *)mapTemplate;

/**
 Called when a pan gesture changes. May not be called when connected to some CarPlay systems.
 */
- (void)mapTemplate:(CPMapTemplate *)mapTemplate didUpdatePanGestureWithTranslation:(CGPoint)translation velocity:(CGPoint)velocity;

/**
 Called when a pan gesture ends. May not be called when connected to some CarPlay systems.
 */
- (void)mapTemplate:(CPMapTemplate *)mapTemplate didEndPanGestureWithVelocity:(CGPoint)velocity;

#pragma mark - Alerts

/**
 Called when the map interface is about to display a navigation alert.
 */
- (void)mapTemplate:(CPMapTemplate *)mapTemplate willShowNavigationAlert:(CPNavigationAlert *)navigationAlert;

/**
 Called when the map interface has displayed a navigation alert.

 To take action in response to button presses on the navigation alert, see -[CPAlertAction handler].
 */
- (void)mapTemplate:(CPMapTemplate *)mapTemplate didShowNavigationAlert:(CPNavigationAlert *)navigationAlert;

/**
 Called when the map interface is preparing to dismiss a navigation alert.
 */
- (void)mapTemplate:(CPMapTemplate *)mapTemplate willDismissNavigationAlert:(CPNavigationAlert *)navigationAlert dismissalContext:(CPNavigationAlertDismissalContext)dismissalContext;

/**
 Called when the map interface has completed dismissal of a navigation alert.
 */
- (void)mapTemplate:(CPMapTemplate *)mapTemplate didDismissNavigationAlert:(CPNavigationAlert *)navigationAlert dismissalContext:(CPNavigationAlertDismissalContext)dismissalContext;


#pragma mark - Trips

/**
 Called when the user has selected a route choice to preview.
 */
- (void)mapTemplate:(CPMapTemplate *)mapTemplate selectedPreviewForTrip:(CPTrip *)trip usingRouteChoice:(CPRouteChoice *)routeChoice;

/**
 Called when the user has selected a route choice to navigate.
 */
- (void)mapTemplate:(CPMapTemplate *)mapTemplate startedTrip:(CPTrip *)trip usingRouteChoice:(CPRouteChoice *)routeChoice;

/**
 Called when navigation has been canceled by the system.
 
 @note In CarPlay systems that have native navigation, it is expected that only either the native navigation or the iPhone
 can be actively navigating. When navigation begins in the native system, all CarPlay supported navigation
 apps that are actively navigating will need to end their navigation session.
 */
- (void)mapTemplateDidCancelNavigation:(CPMapTemplate *)mapTemplate;

#pragma mark - Display Style
/**
 Changes the visual layout of the maneuver.
 @return a CPManeuverDisplayStyle value representing the style to be used for displaying the maneuver
 */
- (CPManeuverDisplayStyle)mapTemplate:(CPMapTemplate *)mapTemplate displayStyleForManeuver:(CPManeuver *)maneuver;

@end

NS_ASSUME_NONNULL_END
