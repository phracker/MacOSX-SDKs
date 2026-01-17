#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UICalendarView.h>)
//
//  UICalendarView.h
//  UIKit
//
//  Copyright © 2022 Apple Inc. All rights reserved.
//

#import <UIKit/UIView.h>
#import <UIKit/UIFont.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

@protocol UICalendarViewDelegate;
@class UICalendarSelection, UICalendarViewDecoration;

UIKIT_EXTERN API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(watchos, tvos) NS_SWIFT_UI_ACTOR
@interface UICalendarView : UIView

/// The object that defines the delegate of the calendar view.
@property (nonatomic, weak, nullable) id<UICalendarViewDelegate> delegate;

/// The object that defines the selection behavior of the calendar view.
@property (nonatomic, strong, nullable) UICalendarSelection *selectionBehavior;

/// The backing locale of the calendar view. The default value is @c NSLocale.currentLocale
@property (nonatomic, strong, nonnull) NSLocale *locale;

/// The backing calendar of the calendar view. The default value is @c NSCalendar.currentCalendar
@property (nonatomic, copy, nonnull) NSCalendar *calendar;

/// The backing time zone of the calendar view. Default is nil
@property (nonatomic, strong, nullable) NSTimeZone *timeZone;

/// The font design of the calendar view. The default value is @c UIFontDescriptorSystemDesignDefault
@property (nonatomic, copy, nonnull) UIFontDescriptorSystemDesign fontDesign;

/// The available date range of the calendar view. The default is a date interval from @c NSDate.distantPast
/// to @c NSDate.distantFuture
@property (nonatomic, copy, nonnull) NSDateInterval *availableDateRange;

/// The date components representing the current visible date of the calendar view. The default value is the
/// NSDateComponents representation of the current date given the granularity of the displayed component.
/// The @c visibleDateComponents must also be a valid date within @c availableDateRange
///
/// @note If @c visibleDateComponents.calendar and @c UICalendarView.calendar are not equal,the input date components
///       will be converted to use @c UICalendarView.calendar upon assignment. UICalendarView will use
///       @c UICalendarView.calendar if @c visibleDateComponents.calendar is not explicitly marked, and may result
///       in incorrect dates if the dateComponents is not valid in @c UICalendarView.calendar.
@property (nonatomic, copy, nonnull) NSDateComponents *visibleDateComponents;

/// Sets the visible date components of the calendar view, with an option to animate the setting.
/// The @c visibleDateComponents must also be a valid date within @c availableDateRange
///
/// @note If @c visibleDateComponents.calendar and @c UICalendarView.calendar are not equal,the input date components
///       will be converted to use @c UICalendarView.calendar upon assignment. UICalendarView will use
///       @c UICalendarView.calendar if @c visibleDateComponents.calendar is not explicitly marked, and may result
///       in incorrect dates if the dateComponents is not valid in @c UICalendarView.calendar.
- (void)setVisibleDateComponents:(NSDateComponents *)dateComponents animated:(BOOL)animated;

#pragma mark - Decorations

/// Determines if we show date decorations. By default, this value returns @c YES, but you must also implement
/// the delegate method @c calendarView:decorationForDate: to show decorations.
@property (nonatomic, assign) BOOL wantsDateDecorations;

/// Reloads the decorations for the specified dates, with an option to animate the action.
/// Decorations are only available if you implement the delegate method @c calendarView:decorationForDate:
- (void)reloadDecorationsForDateComponents:(NSArray<NSDateComponents *> *)dates animated:(BOOL)animated;

@end

API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(watchos, tvos) NS_SWIFT_UI_ACTOR
@protocol UICalendarViewDelegate<NSObject>

@optional

/**
 *  @abstract Called when the calendar view is preparing decorations.
 *
 *  @param calendarView The @c UICalendarView
 *  @param dateComponents The date for which the decoration is prepared for.
 *
 *  @return A @c UICalendarViewDecoration to annotate the specific date. Return @c nil for no decoration.
 */
- (nullable UICalendarViewDecoration *)calendarView:(UICalendarView *)calendarView decorationForDateComponents:(NSDateComponents *)dateComponents;

/**
 *  @abstract Called when the visible date has changed from @c previousDateComponents from user interaction.
 *
 *  @param calendarView The @c UICalendarView
 *  @param previousDateComponents The previous date components before the visible date components changed.
 */
- (void)calendarView:(UICalendarView *)calendarView didChangeVisibleDateComponentsFrom:(NSDateComponents *)previousDateComponents API_AVAILABLE(ios(16.2));


@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UICalendarView.h>
#endif
