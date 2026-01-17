/*
        NSMovie.h
        Application Kit
        Copyright (c) 2000-2015, Apple Inc.
        All rights reserved.
*/

// Please note that NSMovie and NSMovieView are deprecated. These classes still exist in 32-bit, but only limited functionality for NSMovie is provided in 64-bit. This minimal functionality will allow you to correctly read and write archives containing NSMovie's in 64-bit. You can also access a QTMovie instance created from the movie data in the NSMovie archive (64-bit only). This is provided as a means for backwards compatibility only. Please transition to using QTMovie as soon as possible.

#import <Foundation/Foundation.h>

@class NSPasteboard, NSURL;

#if __LP64__
@class QTMovie;
#endif

#if !__LP64__
NS_CLASS_DEPRECATED_MAC(10_0, 10_5, "Use QTMovie instead")
@interface NSMovie : NSObject <NSCopying, NSCoding> {
#else
NS_CLASS_DEPRECATED_MAC(10_0, 10_5, "Use QTMovie instead")
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

- (id) initWithMovie:(void* /*Movie*/)movie NS_DEPRECATED_MAC(10_0, 10_5);			// When archived, saves contents
- (id) initWithURL:(NSURL*)url byReference:(BOOL)byRef NS_DEPRECATED_MAC(10_0, 10_5);	// When archived, saves ref or contents
- (id) initWithPasteboard:(NSPasteboard*)pasteboard NS_DEPRECATED_MAC(10_0, 10_5);

- (void*/*Movie*/)QTMovie NS_RETURNS_INNER_POINTER NS_DEPRECATED_MAC(10_0, 10_5);
- (NSURL*)URL NS_DEPRECATED_MAC(10_0, 10_5);

+ (NSArray<NSString *> *) movieUnfilteredFileTypes NS_DEPRECATED_MAC(10_0, 10_5);
+ (NSArray<NSString *> *) movieUnfilteredPasteboardTypes NS_DEPRECATED_MAC(10_0, 10_5);
+ (BOOL) canInitWithPasteboard:(NSPasteboard*)pasteboard NS_DEPRECATED_MAC(10_0, 10_5);

#else

- (id) initWithMovie:(QTMovie*)movie;
- (QTMovie *)QTMovie;

#endif

@end

