/*
	NSDatePicker.h
	Application Kit
	Copyright (c) 2004-2005, Apple Computer, Inc.
	All rights reserved.
*/

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4

#import <AppKit/NSControl.h>
#import <AppKit/NSDatePickerCell.h>

@class NSCalendar, NSLocale, NSTimeZone;

@interface NSDatePicker : NSControl
{
}

#pragma mark *** Appearance Control ***

- (NSDatePickerStyle)datePickerStyle;
- (void)setDatePickerStyle:(NSDatePickerStyle)newStyle;

- (BOOL)isBezeled;
- (void)setBezeled:(BOOL)flag;

- (BOOL)isBordered;
- (void)setBordered:(BOOL)flag;

- (BOOL)drawsBackground;
- (void)setDrawsBackground:(BOOL)flag;

- (NSColor *)backgroundColor;
- (void)setBackgroundColor:(NSColor *)color;

- (NSColor *)textColor;
- (void)setTextColor:(NSColor *)color;

#pragma mark *** Range Mode Control ***

- (NSDatePickerMode)datePickerMode;
- (void)setDatePickerMode:(NSDatePickerMode)newMode;

#pragma mark *** Date Presentation Control ***

- (NSDatePickerElementFlags)datePickerElements;
- (void)setDatePickerElements:(unsigned)elementFlags;

- (NSCalendar *)calendar;
- (void)setCalendar:(NSCalendar *)newCalendar;

- (NSLocale *)locale;
- (void)setLocale:(NSLocale *)newLocale;

- (NSTimeZone *)timeZone;
- (void)setTimeZone:(NSTimeZone *)newTimeZone;

#pragma mark *** Object Value Access ***

- (NSDate *)dateValue;
- (void)setDateValue:(NSDate *)newStartDate;

- (NSTimeInterval)timeInterval;
- (void)setTimeInterval:(NSTimeInterval)newTimeInterval;

#pragma mark *** Constraints on Displayable/Selectable Range ***

- (NSDate *)minDate;
- (void)setMinDate:(NSDate *)date;

- (NSDate *)maxDate;
- (void)setMaxDate:(NSDate *)date;

#pragma mark *** Delegate ***

- (id)delegate;
- (void)setDelegate:(id)anObject;

@end

#endif
