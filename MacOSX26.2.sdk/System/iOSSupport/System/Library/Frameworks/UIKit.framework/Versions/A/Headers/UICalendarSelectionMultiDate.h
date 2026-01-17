#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UICalendarSelectionMultiDate.h>)
//
//  UICalendarSelectionMultiDate.h
//  UIKit
//
//  Copyright © 2022 Apple Inc. All rights reserved.
//

#import <UIKit/UICalendarSelection.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

@protocol UICalendarSelectionMultiDateDelegate;

UIKIT_EXTERN API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(watchos, tvos) NS_SWIFT_UI_ACTOR
@interface UICalendarSelectionMultiDate : UICalendarSelection

/// The currently selected dates in the Calendar view.
@property (nonatomic, copy) NSArray<NSDateComponents *> *selectedDates;

/// Sets the dates to display in the calendar, with an option to animate the setting.
- (void)setSelectedDates:(NSArray<NSDateComponents *> *)selectedDates animated:(BOOL)animated;

/// The object that acts as the delegate of the calendar view selection
@property (nonatomic, weak, nullable, readonly) id<UICalendarSelectionMultiDateDelegate> delegate;

/// Creates a new multi-date selection with the specified delegate.
- (instancetype)initWithDelegate:(nullable id<UICalendarSelectionMultiDateDelegate>)delegate;

@end

API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(watchos, tvos) NS_SWIFT_UI_ACTOR
@protocol UICalendarSelectionMultiDateDelegate <NSObject>

/**
 *  @abstract Called after the user selects a date in the calendar view.
 *
 *  @param selection The @c UICalendarSelectionMultiDate
 *  @param dateComponents The date that was selected by the user.
 */
- (void)multiDateSelection:(UICalendarSelectionMultiDate *)selection didSelectDate:(NSDateComponents *)dateComponents;

/**
 *  @abstract Called after the user removes selection from one of hte selected dates the calendar view.
 *
 *  @param selection The @c UICalendarSelectionMultiDate
 *  @param dateComponents The date that was deselected by the user.
 */
- (void)multiDateSelection:(UICalendarSelectionMultiDate *)selection didDeselectDate:(NSDateComponents *)dateComponents;

@optional

/**
 *  @abstract Determines if a date is selectable. Dates that are not selectable will be disabled in the calendar view.
 *
 *  @param selection The @c UICalendarSelectionMultiDate
 *  @param dateComponents The date to be checked by selection.
 *
 *  @return YES if the date can be selected, NO otherwise.
 */
- (BOOL)multiDateSelection:(UICalendarSelectionMultiDate *)selection canSelectDate:(NSDateComponents *)dateComponents;

/**
 *  @abstract Determines if a date can be deselected.
 *
 *  @param selection The @c UICalendarSelectionMultiDate
 *  @param dateComponents The date to be checked by selection.
 *
 *  @return YES if the date can be deselected, NO otherwise.
 */
- (BOOL)multiDateSelection:(UICalendarSelectionMultiDate *)selection canDeselectDate:(NSDateComponents *)dateComponents;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UICalendarSelectionMultiDate.h>
#endif
