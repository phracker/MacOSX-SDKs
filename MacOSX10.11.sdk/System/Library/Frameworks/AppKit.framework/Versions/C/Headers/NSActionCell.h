/*
        NSActionCell.h
	Application Kit
	Copyright (c) 1994-2015, Apple Inc.
	All rights reserved.
*/

#import <AppKit/NSCell.h>

NS_ASSUME_NONNULL_BEGIN

@interface NSActionCell : NSCell
{
    /*All instance variables are private*/
    NSInteger	_tag;        
    id		_target;     
    SEL		_action;     
    id		_controlView; // this was always private, but it isn't used for storage of the control view now either.  Please use the accessors -[NSCell controlView] and -[NSCell setControlView:].      
}

@property (nullable, weak) id target; // Target is weak for zeroing-weak compatible objects in apps linked on 10.10 or later. Otherwise the behavior of this property is 'assign’.
@property (nullable) SEL action;
@property NSInteger tag;

@end

NS_ASSUME_NONNULL_END
