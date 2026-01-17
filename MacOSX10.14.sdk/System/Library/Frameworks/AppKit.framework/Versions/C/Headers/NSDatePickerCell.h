/*
	NSDatePickerCell.h
	Application Kit
	Copyright (c) 2004-2018, Apple Inc.
	All rights reserved.
*/

#import <Foundation/NSDate.h>
#import <AppKit/NSActionCell.h>


NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSUInteger, NSDatePickerStyle) {
    NSDatePickerStyleTextFieldAndStepper    = 0,
    NSDatePickerStyleClockAndCalendar       = 1,
    NSDatePickerStyleTextField              = 2
};

typedef NS_ENUM(NSUInteger, NSDatePickerMode) {
    NSDatePickerModeSingle = 0,
    NSDatePickerModeRange = 1
};

typedef NS_OPTIONS(NSUInteger, NSDatePickerElementFlags) {
    /* Time Elements */
    NSDatePickerElementFlagHourMinute       = 0x000c,
    NSDatePickerElementFlagHourMinuteSecond = 0x000e,
    NSDatePickerElementFlagTimeZone	    = 0x0010,

    /* Date Elements */
    NSDatePickerElementFlagYearMonth	    = 0x00c0,
    NSDatePickerElementFlagYearMonthDay	    = 0x00e0,
    NSDatePickerElementFlagEra		    = 0x0100,
};

@class NSCalendar, NSLocale, NSTimeZone;
@protocol NSDatePickerCellDelegate;

@interface NSDatePickerCell : NSActionCell
{
@private
    NSTimeInterval _timeInterval APPKIT_IVAR;
    NSDate *_minDate APPKIT_IVAR;
    NSDate *_maxDate APPKIT_IVAR;
    struct __dateCellFlags {
        unsigned int elements:16;
        unsigned int controlStyle:3;
        unsigned int controlMode:2;
        unsigned int trackingHand:2;
        unsigned int reserved2:4;
        unsigned int drawsBackground:1;
        unsigned int digitsEntered:2;
        unsigned int forcesLeadingZeroes:1;
        unsigned int wrapsDateComponentArithmetic:1;
    } _dcFlags APPKIT_IVAR;
    __weak id<NSDatePickerCellDelegate> _delegate APPKIT_IVAR;
    NSCalendar *_calendar APPKIT_IVAR;
    NSLocale *_locale APPKIT_IVAR;
    NSTimeZone *_timeZone APPKIT_IVAR;
    NSColor *_backgroundColor APPKIT_IVAR;
    NSColor *_textColor APPKIT_IVAR;
    int _indexOfSelectedSubfield APPKIT_IVAR;
    int _reserved0 __unused APPKIT_IVAR;
    id _reserved1 APPKIT_IVAR;
    id _reserved2 APPKIT_IVAR;
    id _reserved3 APPKIT_IVAR;
    id _reserved4 APPKIT_IVAR;
}

- (instancetype)initTextCell:(NSString *)string NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;
- (instancetype)initImageCell:(nullable NSImage *)image NS_UNAVAILABLE;

#pragma mark *** Appearance Control ***

@property NSDatePickerStyle datePickerStyle;

@property BOOL drawsBackground;

@property (copy) NSColor *backgroundColor;

@property (copy) NSColor *textColor;

#pragma mark *** Range Mode Control ***

@property NSDatePickerMode datePickerMode;

#pragma mark *** Date Presentation Control ***

@property NSDatePickerElementFlags datePickerElements;

@property (nullable, copy) NSCalendar *calendar;

@property (nullable, copy) NSLocale *locale;

@property (nullable, copy) NSTimeZone *timeZone;

#pragma mark *** Object Value Access ***

@property (copy) NSDate *dateValue;

@property NSTimeInterval timeInterval;

#pragma mark *** Constraints on Displayable/Selectable Range ***

@property (nullable, copy) NSDate *minDate;

@property (nullable, copy) NSDate *maxDate;

#pragma mark *** Delegate ***

@property (nullable, weak) id<NSDatePickerCellDelegate> delegate;

@end

@protocol NSDatePickerCellDelegate <NSObject>
@optional
- (void)datePickerCell:(NSDatePickerCell *)datePickerCell validateProposedDateValue:(NSDate * __nonnull *__nonnull)proposedDateValue timeInterval:(nullable NSTimeInterval *)proposedTimeInterval;
@end

/* Deprecated legacy date picker style constants. Prefer to use NSDatePickerStyle values instead.
*/
static const NSDatePickerStyle NSTextFieldAndStepperDatePickerStyle NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSDatePickerStyleTextFieldAndStepper", 10_0, API_TO_BE_DEPRECATED) = NSDatePickerStyleTextFieldAndStepper;
static const NSDatePickerStyle NSClockAndCalendarDatePickerStyle NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSDatePickerStyleClockAndCalendar", 10_0, API_TO_BE_DEPRECATED) = NSDatePickerStyleClockAndCalendar;
static const NSDatePickerStyle NSTextFieldDatePickerStyle NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSDatePickerStyleTextField", 10_0, API_TO_BE_DEPRECATED) = NSDatePickerStyleTextField;

/* Deprecated legacy date picker mode constants. Prefer to use NSDatePickerMode values instead.
*/
static const NSDatePickerMode NSSingleDateMode NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSDatePickerModeSingle", 10_0, API_TO_BE_DEPRECATED) = NSDatePickerModeSingle;
static const NSDatePickerMode NSRangeDateMode NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSDatePickerModeRange", 10_0, API_TO_BE_DEPRECATED) = NSDatePickerModeRange;

/* Deprecated legacy date picker element flag constants. Prefer to use NSDatePickerElementFlags values instead.
*/
static const NSDatePickerElementFlags NSHourMinuteDatePickerElementFlag NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSDatePickerElementFlagHourMinute", 10_0, API_TO_BE_DEPRECATED) = NSDatePickerElementFlagHourMinute;
static const NSDatePickerElementFlags NSHourMinuteSecondDatePickerElementFlag NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSDatePickerElementFlagHourMinuteSecond", 10_0, API_TO_BE_DEPRECATED) = NSDatePickerElementFlagHourMinuteSecond;
static const NSDatePickerElementFlags NSTimeZoneDatePickerElementFlag NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSDatePickerElementFlagTimeZone", 10_0, API_TO_BE_DEPRECATED) = NSDatePickerElementFlagTimeZone;
static const NSDatePickerElementFlags NSYearMonthDatePickerElementFlag NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSDatePickerElementFlagYearMonth", 10_0, API_TO_BE_DEPRECATED) = NSDatePickerElementFlagYearMonth;
static const NSDatePickerElementFlags NSYearMonthDayDatePickerElementFlag NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSDatePickerElementFlagYearMonthDay", 10_0, API_TO_BE_DEPRECATED) = NSDatePickerElementFlagYearMonthDay;
static const NSDatePickerElementFlags NSEraDatePickerElementFlag NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSDatePickerElementFlagEra", 10_0, API_TO_BE_DEPRECATED) = NSDatePickerElementFlagEra;

NS_ASSUME_NONNULL_END

