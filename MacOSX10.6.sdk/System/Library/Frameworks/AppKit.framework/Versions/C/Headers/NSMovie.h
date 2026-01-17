/*
        NSMovie.h
        Application Kit
        Copyright (c) 2000-2009, Apple Inc.
        All rights reserved.
*/

// Please note that NSMovie and NSMovieView are deprecated. These classes still exist in 32-bit, but only limited functionality for NSMovie is provided in 64-bit. This minimal functionality will allow you to correctly read and write archives containing NSMovie's in 64-bit. You can also access a QTMovie instance created from the movie data in the NSMovie archive (64-bit only). This is provided as a means for backwards compatibility only. Please transition to using QTMovie as soon as possible.

#import <Foundation/Foundation.h>

@class NSArray, NSPasteboard, NSURL;

#if __LP64__
@class QTMovie;
#endif

#if !__LP64__
@interface NSMovie : NSObject <NSCopying, NSCoding> {
#else
@interface NSMovie : NSObject <NSCoding> {
#endif

  @private
    void*    _movie;
    NSURL*   _url;
    struct {
	int dispose:1;
	int reserved:31;
    } _movieFlags;
    long     _reserved1;
    long     _reserved2;
}

#if !__LP64__

- (id) initWithMovie:(void* /*Movie*/)movie DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;			// When archived, saves contents
- (id) initWithURL:(NSURL*)url byReference:(BOOL)byRef DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;	// When archived, saves ref or contents
- (id) initWithPasteboard:(NSPasteboard*)pasteboard DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;

- (void*/*Movie*/)QTMovie DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
- (NSURL*)URL DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;

+ (NSArray*) movieUnfilteredFileTypes DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
+ (NSArray*) movieUnfilteredPasteboardTypes DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
+ (BOOL) canInitWithPasteboard:(NSPasteboard*)pasteboard DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;

#else

- (id) initWithMovie:(QTMovie*)movie;
- (QTMovie *)QTMovie;

#endif

@end

