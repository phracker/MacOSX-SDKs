/*
        NSParagraphStyle.h
        Copyright (c) 1994-2001, Apple Computer, Inc.  All rights reserved.

	NSParagraphStyle and NSMutableParagraphStyle hold paragraph style information
	NSTextTab holds information about a single tab stop
*/

#import <Foundation/NSObject.h>
#import <AppKit/NSText.h>

typedef enum _NSTextTabType {
    NSLeftTabStopType = 0,
    NSRightTabStopType,		/* ??? Doesn't work yet */
    NSCenterTabStopType,	/* ??? Doesn't work yet */
    NSDecimalTabStopType	/* ??? Doesn't work yet */
} NSTextTabType;

typedef enum _NSLineBreakMode {		/* What to do with long lines */
    NSLineBreakByWordWrapping = 0,     	/* Wrap at word boundaries, default */
    NSLineBreakByCharWrapping,		/* Wrap at character boundaries */
    NSLineBreakByClipping,		/* Simply clip */
    NSLineBreakByTruncatingHead,	/* Truncate at head of line: "...wxyz" ??? Doesn't work yet */
    NSLineBreakByTruncatingTail,	/* Truncate at tail of line: "abcd..." ??? Doesn't work yet */
    NSLineBreakByTruncatingMiddle	/* Truncate middle of line:  "ab...yz" ??? Doesn't work yet */
} NSLineBreakMode;

@interface NSTextTab : NSObject <NSCopying, NSCoding> {
    /*All instance variables are private*/
    struct {
	NSTextTabType type:8;
        unsigned int refCount:24;
    } _flags;
    float _location;
    unsigned int _reserved;
}
- (id)initWithType:(NSTextTabType)type location:(float)loc;
- (float)location;
- (NSTextTabType)tabStopType;
@end

@interface NSParagraphStyle : NSObject <NSCopying, NSMutableCopying, NSCoding> {
    /*All instance variables are private*/
    float _lineSpacing;
    float _paragraphSpacing;
    float _headIndent;
    float _tailIndent;
    float _firstLineHeadIndent;
    float _minimumLineHeight;
    float _maximumLineHeight;
    NSArray *_tabStops;
    struct {
	NSTextAlignment alignment:4;
        NSLineBreakMode lineBreakMode:4;
        unsigned int tabStopsIsMutable:1;
        unsigned int refCount:23;
    } _flags;
    unsigned int _reserved1;
    unsigned int _reserved2;
}

+ (NSParagraphStyle *)defaultParagraphStyle;

- (float)lineSpacing;		/* "Leading": distance between the bottom of one line fragment and top of next (applied between lines in the same container). Can't be negative. This value is included in the line fragment heights in layout manager. */
- (float)paragraphSpacing; 	/* Distance between the bottom of this paragraph and top of next. */
- (NSTextAlignment)alignment;

/* The following values are relative to the appropriate margin (depending on the paragraph direction) */
   
- (float)headIndent;		/* Distance from margin to front edge of paragraph */
- (float)tailIndent;		/* Distance from margin to back edge of paragraph; if negative or 0, from other margin */
- (float)firstLineHeadIndent;	/* Distance from margin to edge appropriate for text direction */
- (NSArray *)tabStops;		/* Distance from margin to tab stops */

- (float)minimumLineHeight;	/* Line height is the distance from bottom of descenders to top of ascenders; basically the line fragment height. Does not include lineSpacing (which is added after this computation). */
- (float)maximumLineHeight;	/* 0 implies no maximum. */ 

- (NSLineBreakMode)lineBreakMode;

@end

@interface NSMutableParagraphStyle : NSParagraphStyle

- (void)setLineSpacing:(float)aFloat;
- (void)setParagraphSpacing:(float)aFloat;
- (void)setAlignment:(NSTextAlignment)alignment;
- (void)setFirstLineHeadIndent:(float)aFloat;
- (void)setHeadIndent:(float)aFloat;
- (void)setTailIndent:(float)aFloat;
- (void)setLineBreakMode:(NSLineBreakMode)mode;
- (void)setMinimumLineHeight:(float)aFloat;
- (void)setMaximumLineHeight:(float)aFloat;
- (void)addTabStop:(NSTextTab *)anObject;
- (void)removeTabStop:(NSTextTab *)anObject;
- (void)setTabStops:(NSArray *)array;
- (void)setParagraphStyle:(NSParagraphStyle *)obj;

@end
