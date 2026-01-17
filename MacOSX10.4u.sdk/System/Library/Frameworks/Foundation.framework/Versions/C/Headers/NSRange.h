/*	NSRange.h
	Copyright (c) 1994-2005, Apple, Inc. All rights reserved.
*/

#import <Foundation/NSValue.h>

@class NSString;

typedef struct _NSRange {
    unsigned int location;
    unsigned int length;
} NSRange;

typedef NSRange *NSRangePointer;

FOUNDATION_STATIC_INLINE NSRange NSMakeRange(unsigned int loc, unsigned int len) {
    NSRange r;
    r.location = loc;
    r.length = len;
    return r;
}

FOUNDATION_STATIC_INLINE unsigned int NSMaxRange(NSRange range) {
    return (range.location + range.length);
}

FOUNDATION_STATIC_INLINE BOOL NSLocationInRange(unsigned int loc, NSRange range) {
    return (loc - range.location < range.length);
}

FOUNDATION_STATIC_INLINE BOOL NSEqualRanges(NSRange range1, NSRange range2) {
    return (range1.location == range2.location && range1.length == range2.length);
}

FOUNDATION_EXPORT NSRange NSUnionRange(NSRange range1, NSRange range2);
FOUNDATION_EXPORT NSRange NSIntersectionRange(NSRange range1, NSRange range2);
FOUNDATION_EXPORT NSString *NSStringFromRange(NSRange range);
FOUNDATION_EXPORT NSRange NSRangeFromString(NSString *aString);

@interface NSValue (NSValueRangeExtensions)

+ (NSValue *)valueWithRange:(NSRange)range;
- (NSRange)rangeValue;

@end

