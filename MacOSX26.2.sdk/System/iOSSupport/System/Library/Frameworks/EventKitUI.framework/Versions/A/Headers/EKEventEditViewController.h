//
//  EKEventEditViewController.h
//  EventKitUI
//
//  Copyright 2009-2010 Apple Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <EventKit/EventKit.h>
#import <EventKitUI/EventKitUIDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class EKEventStore, EKEvent;

/*!
    @enum       EKEventEditViewAction
    @abstract   Represents actions that should cause the edit view controller to be dismissed
 
    @constant   EKEventEditViewActionCanceled    The Cancel button was pressed, or the Done button was pressed, but the event was not dirty.
    @constant   EKEventEditViewActionSaved       The event was saved.
    @constant   EKEventEditViewActionDeleted     The event was deleted, either by the user or by another calendar store.
*/

typedef NS_ENUM(NSInteger, EKEventEditViewAction) {
    EKEventEditViewActionCanceled,
    EKEventEditViewActionSaved,
    EKEventEditViewActionDeleted,
    
    // going away, use spelling above
    EKEventEditViewActionCancelled = EKEventEditViewActionCanceled
};

/*!
    @class      EKEventEditViewController
    @abstract   View controller to create/edit events.
    @discussion You can present this view controller to create a new event or edit an existing
                event. You should present it modally. To create a new event, you can either pass
                nil for the event parameter or pass a partially constructed event. If the event
                you pass has no calendar set, the default calendar as set in Settings will be used.
*/
@protocol EKEventEditViewDelegate;

#ifdef __APPLE_BLEACH_SDK__
NS_EXTENSION_UNAVAILABLE_IOS("EventKitUI is not supported in extensions")
#endif
EVENTKITUI_CLASS_AVAILABLE(4_0)
@interface EKEventEditViewController : UINavigationController

@property(nonatomic, weak, nullable) id<EKEventEditViewDelegate>  editViewDelegate;

/*!
    @property   eventStore
    @abstract   The event store to use to save events.
    @discussion You must set this before presenting the view controller.
*/
@property(nonatomic, retain, null_unspecified) EKEventStore   *eventStore;

/*!
    @property   event
    @abstract   The event to edit.
    @discussion You must set this before presenting the view controller. You can leave
                it set to nil and a new event will be created for you. If you pass an event
                here and it does not belong to the event store (if set) an exception will be
                raised.
*/
@property(nonatomic, retain, nullable) EKEvent *event;

/*!
    @method     cancelEditing
    @abstract   Ends the editing session discarding any changes to the event.
    @discussion This method simulates the user tapping the Cancel button. The delegate will not 
                receive the eventEditViewController:didCompleteWithAction: message, so you are
                responsible for dismissing the controller after calling this method.
 */
- (void)cancelEditing;

@end

/*!
    @enum       EKEventEditViewDelegate
    @abstract   Delegate protocol for event edit view controller.
*/

#ifdef __APPLE_BLEACH_SDK__
NS_EXTENSION_UNAVAILABLE_IOS("EventKitUI is not supported in extensions")
#endif
@protocol EKEventEditViewDelegate <NSObject>
@required

/*!
    @method     eventEditViewController:didCompleteWithAction:
    @abstract   Called to let delegate know the controller is done editing.
    @discussion When the user presses Cancel, presses Done, or deletes the event, this method
                is called. Your delegate is responsible for dismissing the controller. If the editing
                session is terminated programmatically using cancelEditing, 
                this method will not be called.
 
    @param      controller          the controller in question
    @param      action              the action that is causing the dismissal
*/
- (void)eventEditViewController:(EKEventEditViewController *)controller didCompleteWithAction:(EKEventEditViewAction)action;

@optional

/*!
    @method     eventEditViewControllerDefaultCalendarForNewEvents:
    @abstract   Allows you to supply your own default calendar for new events.
    @discussion This delegate method allows you to control what the editor chooses for the default calendar
                if it needs to fill in a calendar. This might be necessary if you either don't pass an initial
                event to the view controller, or you do, but you did not supply a calendar. In these cases, we
                we set the calendar to a default. If this is not implemented by the delegate, the controller
                will use the store's defaultCalendarForNewEvents.
*/

- (EKCalendar *)eventEditViewControllerDefaultCalendarForNewEvents:(EKEventEditViewController *)controller;


@end

NS_ASSUME_NONNULL_END
