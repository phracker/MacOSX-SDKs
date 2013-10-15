/*
        NSQuickDrawView.h
        Application Kit
        Copyright (c) 1999-2005, Apple Computer, Inc.
        All rights reserved.
*/

#import <AppKit/NSView.h>

@interface NSQuickDrawView : NSView
{
@private
    void*  _qdPort;
    void*  _savePort;
    BOOL   _synchToView;
}

- (void*) qdPort;

@end
