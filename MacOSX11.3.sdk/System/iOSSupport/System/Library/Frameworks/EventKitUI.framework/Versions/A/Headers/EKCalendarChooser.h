//
//  EKCalendarChooser.h
//  EventKitUI
//
//  Copyright 2009-2010 Apple Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <EventKitUI/EventKitUIDefines.h>
#import <EventKit/EventKit.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, EKCalendarChooserSelectionStyle) {
    EKCalendarChooserSelectionStyleSingle,
    EKCalendarChooserSelectionStyleMultiple
};

typedef NS_ENUM(NSInteger, EKCalendarChooserDisplayStyle) {
    EKCalendarChooserDisplayAllCalendars,
    EKCalendarChooserDisplayWritableCalendarsOnly
};

@protocol EKCalendarChooserDelegate;


EVENTKITUI_EXTERN @interface EKCalendarChooser : UIViewController

- (id)initWithSelectionStyle:(EKCalendarChooserSelectionStyle)selectionStyle
                displayStyle:(EKCalendarChooserDisplayStyle)displayStyle
                  eventStore:(EKEventStore *)eventStore;

// variant to only show calendars for events or reminders.
- (id)initWithSelectionStyle:(EKCalendarChooserSelectionStyle)style 
                displayStyle:(EKCalendarChooserDisplayStyle)displayStyle
                  entityType:(EKEntityType)entityType
                  eventStore:(EKEventStore *)eventStore;

@property(nonatomic, readonly) EKCalendarChooserSelectionStyle    selectionStyle;

@property(nonatomic, weak, nullable) id<EKCalendarChooserDelegate>        delegate;

// When used in a navigation controller (presented modally), you can enable
// the done/cancel buttons and get informed when pressed via the delegate.
@property(nonatomic) BOOL showsDoneButton;
@property(nonatomic) BOOL showsCancelButton;

// Regardless of whether the chooser allows you to select one or multiple
// calendars, the selection is always expressed as a set.
@property(nonatomic, copy) NSSet<EKCalendar *> *selectedCalendars;

@end

@protocol EKCalendarChooserDelegate <NSObject>
@optional

// Called whenever the selection is changed by the user
- (void)calendarChooserSelectionDidChange:(EKCalendarChooser *)calendarChooser;

// These are called when the corresponding button is pressed to dismiss the
// controller. It is up to the recipient to dismiss the chooser.
- (void)calendarChooserDidFinish:(EKCalendarChooser *)calendarChooser;
- (void)calendarChooserDidCancel:(EKCalendarChooser *)calendarChooser;

@end

NS_ASSUME_NONNULL_END
