/*	NSDateFormatter.h
	Copyright 1995-2001, Apple, Inc. All rights reserved.
*/

#import <Foundation/NSFormatter.h>

@class NSString;

@interface NSDateFormatter : NSFormatter {
@private
    NSString *_format;
    BOOL _naturalLanguage;
    int _reserved;
}

- (id)initWithDateFormat:(NSString *)format allowNaturalLanguage:(BOOL)flag;
- (NSString *)dateFormat;
- (BOOL)allowsNaturalLanguage;

@end

