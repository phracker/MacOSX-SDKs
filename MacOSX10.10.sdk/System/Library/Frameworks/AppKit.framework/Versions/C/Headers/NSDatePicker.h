/*
	NSDatePicker.h
	Application Kit
	Copyright (c) 2004-2014, Apple Inc.
	All rights reserved.
*/

#import <AppKit/NSControl.h>
#import <AppKit/NSDatePickerCell.h>


@class NSCalendar, NSLocale, NSTimeZone;

@interface NSDatePicker : NSControl
{
}

#pragma mark *** Appearance Control ***

@property NSDatePickerStyle datePickerStyle;

@property (getter=isBezeled) BOOL bezeled;

@property (getter=isBordered) BOOL bordered;

@property BOOL drawsBackground;

@property (copy) NSColor *backgroundColor;

@property (copy) NSColor *textColor;

#pragma mark *** Range Mode Control ***

@property NSDatePickerMode datePickerMode;

#pragma mark *** Date Presentation Control ***

@property NSDatePickerElementFlags datePickerElements;

@property (copy) NSCalendar *calendar;

@property (copy) NSLocale *locale;

@property (copy) NSTimeZone *timeZone;

#pragma mark *** Object Value Access ***

@property (copy) NSDate *dateValue;

@property NSTimeInterval timeInterval;

#pragma mark *** Constraints on Displayable/Selectable Range ***

@property (copy) NSDate *minDate;

@property (copy) NSDate *maxDate;

#pragma mark *** Delegate ***

@property (assign) id<NSDatePickerCellDelegate> delegate;

@end

