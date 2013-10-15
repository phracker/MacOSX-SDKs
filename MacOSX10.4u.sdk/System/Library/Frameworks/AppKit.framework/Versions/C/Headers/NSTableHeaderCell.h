/*
        NSTableHeaderCell.h
        Application Kit
        Copyright (c) 1995-2004, Apple Computer, Inc.
        All rights reserved.
*/
#import <AppKit/NSTextFieldCell.h>

@interface NSTableHeaderCell : NSTextFieldCell {
/*All instance variables are private*/
}

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3

- (void)drawSortIndicatorWithFrame:(NSRect)cellFrame inView:(NSView *)controlView ascending:(BOOL)ascending priority:(int)priority;
    // Draws a sorting indicator given a cellFrame.  If priority is 0, this is the primary sort indicator.  If ascending is YES, a "^" indicator will be drawn.  Override this routine to customimze the sorting UI.

- (NSRect)sortIndicatorRectForBounds:(NSRect)theRect;
    // Returns the location to display the sorting indicator given the cellFrame.
    
#endif

@end
