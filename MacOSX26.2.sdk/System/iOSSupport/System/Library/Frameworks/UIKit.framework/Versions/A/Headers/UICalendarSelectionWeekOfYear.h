#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UICalendarSelectionWeekOfYear.h>)
//
//  UICalendarSelectionWeekOfYear.h
//  UIKit
//
//  Copyright © 2023 Apple Inc. All rights reserved.
//

#import <UIKit/UICalendarSelection.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

@protocol UICalendarSelectionWeekOfYearDelegate;

UIKIT_EXTERN API_AVAILABLE(ios(18.0)) API_UNAVAILABLE(watchos, tvos) NS_SWIFT_UI_ACTOR
@interface UICalendarSelectionWeekOfYear : UICalendarSelection

/// The currently selected week of year in the Calendar view. The components must include `[.yearForWeekOfYear, .weekOfYear]`.
@property (nonatomic, nullable, copy) NSDateComponents *selectedWeekOfYear;

/// Sets the dates to display in the calendar, with an option to animate the setting.
- (void)setSelectedWeekOfYear:(nullable NSDateComponents *)selectedWeekOfYear animated:(BOOL)animated;

/// The object that acts as the delegate of the calendar view selection
@property (nonatomic, weak, nullable, readonly) id<UICalendarSelectionWeekOfYearDelegate> delegate;

/// Creates a new multi-date selection with the specified delegate.
- (instancetype)initWithDelegate:(nullable id<UICalendarSelectionWeekOfYearDelegate>)delegate;

@end

API_AVAILABLE(ios(18.0)) API_UNAVAILABLE(watchos, tvos) NS_SWIFT_UI_ACTOR
@protocol UICalendarSelectionWeekOfYearDelegate <NSObject>

/**
 *  @abstract Called after the user selects a week of year in the calendar view.
 *
 *  @param selection The @c UICalendarSelectionWeekOfYear
 *  @param dateComponents The date that was selected by the user.
 */
- (void)weekOfYearSelection:(UICalendarSelectionWeekOfYear *)selection didSelectWeekOfYear:(nullable NSDateComponents *)weekOfYearComponents;

@optional

/**
 *  @abstract Determines if a week of year is selectable. Dates that are not selectable will be disabled in the calendar view.
 *
 *  @param selection The @c UICalendarSelectionWeekOfYear
 *  @param dateComponents The date to be checked by selection.
 *
 *  @return YES if the date can be selected, NO otherwise.
 */
- (BOOL)weekOfYearSelection:(UICalendarSelectionWeekOfYear *)selection canSelectWeekOfYear:(nullable NSDateComponents *)weekOfYearComponents;

@end


NS_HEADER_AUDIT_END(nullability, sendability)


#else
#import <UIKitCore/UICalendarSelectionWeekOfYear.h>
#endif
