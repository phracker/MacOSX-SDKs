/*
        NSStringDrawing.h
        Copyright (c) 1994-2001, Apple Computer, Inc.  All rights reserved.

        Methods to deal with NSString drawing, measuring
   
*/

#import <Foundation/NSString.h>
#import <AppKit/NSAttributedString.h>

@interface NSString(NSStringDrawing)

- (NSSize)sizeWithAttributes:(NSDictionary *)attrs;
- (void)drawAtPoint:(NSPoint)point withAttributes:(NSDictionary *)attrs;
- (void)drawInRect:(NSRect)rect withAttributes:(NSDictionary *)attrs;

@end

@interface NSAttributedString(NSStringDrawing)

- (NSSize)size;
- (void)drawAtPoint:(NSPoint)point;
- (void)drawInRect:(NSRect)rect;

@end
