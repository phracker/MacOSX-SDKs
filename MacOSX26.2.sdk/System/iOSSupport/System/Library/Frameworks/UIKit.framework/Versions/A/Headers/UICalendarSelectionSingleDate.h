#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UICalendarSelectionSingleDate.h>)
//
//  UICalendarSelectionSingleDate.h
//  UIKit
//
//  Copyright © 2022 Apple Inc. All rights reserved.
//

#import <UIKit/UICalendarSelection.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

@protocol UICalendarSelectionSingleDateDelegate;

UIKIT_EXTERN API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(watchos, tvos) NS_SWIFT_UI_ACTOR
@interface UICalendarSelectionSingleDate : UICalendarSelection

/// The object that acts as the delegate of the calendar view selection
@property (nonatomic, weak, nullable, readonly) id<UICalendarSelectionSingleDateDelegate> delegate;

/// The currently selected dates in the Calendar view. If this property is @c nil then nothing in the calendar
/// view is currently selected. The default value is @c nil.
@property (nonatomic, copy, nullable) NSDateComponents *selectedDate;

/// Sets the selected date to be displayed in the calendar, with an option to animate the setting.
- (void)setSelectedDate:(nullable NSDateComponents *)selectedDate animated:(BOOL)animated;

/// Creates a new single selection with the specified delegate.
- (instancetype)initWithDelegate:(nullable id<UICalendarSelectionSingleDateDelegate>)delegate;

@end

API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(watchos, tvos) NS_SWIFT_UI_ACTOR
@protocol UICalendarSelectionSingleDateDelegate <NSObject>

/**
 *  @abstract Called after the user selects a date in the calendar view.
 *
 *  @param selection The @c UICalendarSelectionMultiDate
 *  @param dateComponents The date that was selected by the user. @c dateComponents can be @c nil when the selected date is deselected by the user.
 */
- (void)dateSelection:(UICalendarSelectionSingleDate *)selection didSelectDate:(nullable NSDateComponents *)dateComponents;

@optional

/**
 *  @abstract Determines if a date is selectable. Dates that are not selectable will be disabled in the calendar view.
 *            By default, @c dateSelection:canSelectDate: returns YES if dateComponents is non-nil.
 *
 *  @param selection The @c UICalendarSelectionMultiDate
 *  @param dateComponents The date to be checked by selection; a @c nil date represents a deselected date.
 *
 *  @return YES if the date can be selected, NO otherwise.
 */
- (BOOL)dateSelection:(UICalendarSelectionSingleDate *)selection canSelectDate:(nullable NSDateComponents *)dateComponents;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UICalendarSelectionSingleDate.h>
#endif
