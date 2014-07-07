/*	NSDateFormatter.h
	Copyright (c) 1995-2003, Apple, Inc. All rights reserved.
*/

#import <Foundation/NSFormatter.h>

@class NSString;

@interface NSDateFormatter : NSFormatter {
@private
    NSString *_format;
    BOOL _naturalLanguage;
    char _unused[3];
    int _reserved;
}

- (id)initWithDateFormat:(NSString *)format allowNaturalLanguage:(BOOL)flag;
- (NSString *)dateFormat;
- (BOOL)allowsNaturalLanguage;

@end

