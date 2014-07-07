// ================================================================================
//	**** PUBLIC HEADER ****
//
//	InterfaceBuilder.framework - IBDefines.h 
//	Copyright (c) 2000 Apple Computer, Inc.
//	All rights reserved.
//
// ================================================================================

#import <Foundation/Foundation.h>

#define IB_BIG_SIZE (10000)

// --------------------------------------------------------------------------------

enum IBKnobPosition {
    IBNoKnobPosition = -1,
    IBBottomLeftKnobPosition = 0,
    IBMiddleLeftKnobPosition,
    IBTopLeftKnobPosition,
    IBTopMiddleKnobPosition,
    IBTopRightKnobPosition,
    IBMiddleRightKnobPosition,
    IBBottomRightKnobPosition,
    IBBottomMiddleKnobPosition
};
typedef enum IBKnobPosition IBKnobPosition;

// --------------------------------------------------------------------------------

typedef struct _IBInset {
    float	left;
    float	top;
    float	right;
    float	bottom;
} IBInset;

