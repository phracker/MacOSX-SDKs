/*
        NSOpenGLView.h
        Application Kit
        Copyright (c) 2000-2005, Apple Computer, Inc.
        All rights reserved.
*/

#import <AppKit/NSView.h>

@class NSOpenGLContext, NSOpenGLPixelFormat;

@interface NSOpenGLView : NSView {
  @private
    NSOpenGLContext*     _openGLContext;
    NSOpenGLPixelFormat* _pixelFormat;
    unsigned long        _reserved1;
    unsigned long        _reserved2;
    unsigned long        _reserved3;
}

+ (NSOpenGLPixelFormat*)defaultPixelFormat;

- (id)initWithFrame:(NSRect)frameRect pixelFormat:(NSOpenGLPixelFormat*)format;

- (void)setOpenGLContext:(NSOpenGLContext*)context;
- (NSOpenGLContext*)openGLContext;
- (void)clearGLContext;

- (void)update;		// moved or resized
- (void)reshape;	// scrolled, moved or resized

- (void)setPixelFormat:(NSOpenGLPixelFormat*)pixelFormat;
- (NSOpenGLPixelFormat*)pixelFormat;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3
- (void)prepareOpenGL;
#endif
@end
