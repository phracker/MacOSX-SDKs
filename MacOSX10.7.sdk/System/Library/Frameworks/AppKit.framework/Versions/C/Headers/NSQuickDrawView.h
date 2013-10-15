/*
        NSQuickDrawView.h
        Application Kit
        Copyright (c) 1999-2011, Apple Inc.
        All rights reserved.
*/

/* QuickDraw is deprecated for 32-bit apps, and doesn't exist in 64-bit. */

#if !__LP64__
#import <AppKit/NSView.h>

@interface NSQuickDrawView : NSView
{
@private
    void*  _qdPort;
    void*  _savePort;
    BOOL   _synchToView;
}

- (void*) qdPort NS_DEPRECATED_MAC(10_0, 10_4);

@end
#endif /* !__LP64__ */
