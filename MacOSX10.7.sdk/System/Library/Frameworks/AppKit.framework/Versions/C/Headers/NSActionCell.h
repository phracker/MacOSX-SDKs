/*
        NSActionCell.h
	Application Kit
	Copyright (c) 1994-2011, Apple Inc.
	All rights reserved.
*/

#import <AppKit/NSCell.h>

@interface NSActionCell : NSCell
{
    /*All instance variables are private*/
    NSInteger	_tag;        
    id		_target;     
    SEL		_action;     
    id		_controlView; // this was always private, but it isn't used for storage of the control view now either.  Please use the accessors -[NSCell controlView] and -[NSCell setControlView:].      
}

- (id)target;
- (void)setTarget:(id)anObject;
- (SEL)action;
- (void)setAction:(SEL)aSelector;
- (NSInteger)tag;
- (void)setTag:(NSInteger)anInt;

@end
