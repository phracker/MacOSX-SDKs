/*
	NSDatePickerCell.h
	Application Kit
	Copyright (c) 2004-2015, Apple Inc.
	All rights reserved.
*/

#import <Foundation/NSDate.h>
#import <AppKit/NSActionCell.h>


NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSUInteger, NSDatePickerStyle) {
    NSTextFieldAndStepperDatePickerStyle    = 0,
    NSClockAndCalendarDatePickerStyle       = 1,
    NSTextFieldDatePickerStyle              = 2
};

typedef NS_ENUM(NSUInteger, NSDatePickerMode) {
    NSSingleDateMode = 0,
    NSRangeDateMode = 1
};

typedef NS_OPTIONS(NSUInteger, NSDatePickerElementFlags) {
    /* Time Elements */
    NSHourMinuteDatePickerElementFlag       = 0x000c,
    NSHourMinuteSecondDatePickerElementFlag = 0x000e,
    NSTimeZoneDatePickerElementFlag	    = 0x0010,

    /* Date Elements */
    NSYearMonthDatePickerElementFlag	    = 0x00c0,
    NSYearMonthDayDatePickerElementFlag	    = 0x00e0,
    NSEraDatePickerElementFlag		    = 0x0100,
};

@class NSCalendar, NSLocale, NSTimeZone;
@protocol NSDatePickerCellDelegate;

@interface NSDatePickerCell : NSActionCell
{
@private
    NSTimeInterval _timeInterval;
    NSDate *_minDate;
    NSDate *_maxDate;
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
    } _dcFlags;
    id _delegate;
    NSCalendar *_calendar;
    NSLocale *_locale;
    NSTimeZone *_timeZone;
    NSColor *_backgroundColor;
    NSColor *_textColor;
    int _indexOfSelectedSubfield;
    int _reserved0;
    id _reserved1;
    id _reserved2;
    id _reserved3;
    id _reserved4;
}

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

@property (nullable, assign) id<NSDatePickerCellDelegate> delegate;

@end

@protocol NSDatePickerCellDelegate <NSObject>
@optional
- (void)datePickerCell:(NSDatePickerCell *)aDatePickerCell validateProposedDateValue:(NSDate * __nonnull *__nonnull)proposedDateValue timeInterval:(nullable NSTimeInterval *)proposedTimeInterval;
@end

NS_ASSUME_NONNULL_END

