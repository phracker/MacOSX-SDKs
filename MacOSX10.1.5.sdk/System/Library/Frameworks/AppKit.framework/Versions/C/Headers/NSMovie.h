/*
        NSMovie.h
        Application Kit
        Copyright (c) 2000-2001, Apple Computer, Inc.
        All rights reserved.
*/

#import <Foundation/Foundation.h>

@class NSPasteboard;

@interface NSMovie : NSObject <NSCopying, NSCoding> {
  @private
    void*    _movie;
    NSURL*   _url;
    long     _reserved1;
    long     _reserved2;
    long     _reserved3;
}

- (id) initWithMovie:(void* /*Movie*/)movie;			// When archived, saves contents
- (id) initWithURL:(NSURL*)url byReference:(BOOL)byRef;	// When archived, saves ref or contents
- (id) initWithPasteboard:(NSPasteboard*)pasteboard;

- (void*/*Movie*/)QTMovie;
- (NSURL*)URL;

+ (NSArray*) movieUnfilteredFileTypes;
+ (NSArray*) movieUnfilteredPasteboardTypes;
+ (BOOL) canInitWithPasteboard:(NSPasteboard*)pasteboard;

@end
