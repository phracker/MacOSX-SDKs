//
//  BETextSelectionTypes.h
//
//  Copyright © 2024 Apple Inc. All rights reserved.
//

#import <BrowserEngineKit/BEMacros.h>
#import <Foundation/Foundation.h>

typedef NS_ENUM(NSInteger, BEGestureType) {
    BEGestureTypeLoupe                          = 0,
    BEGestureTypeOneFingerTap                   = 1,
    BEGestureTypeDoubleTapAndHold               = 2,
    BEGestureTypeDoubleTap                      = 3,
    BEGestureTypeOneFingerDoubleTap             = 8,
    BEGestureTypeOneFingerTripleTap             = 9,
    BEGestureTypeTwoFingerSingleTap             = 10,
    BEGestureTypeTwoFingerRangedSelectGesture   = 11,
    BEGestureTypeIMPhraseBoundaryDrag           = 14,  // Used when adjusting marked text
    BEGestureTypeForceTouch                     = 15,
} BROWSERENGINE_TEXTINPUT_AVAILABILITY;

typedef NS_ENUM(NSInteger, BESelectionTouchPhase) {
    BESelectionTouchPhaseStarted,
    BESelectionTouchPhaseMoved,
    BESelectionTouchPhaseEnded,
    BESelectionTouchPhaseEndedMovingForward,
    BESelectionTouchPhaseEndedMovingBackward,
    BESelectionTouchPhaseEndedNotMoving
} BROWSERENGINE_TEXTINPUT_AVAILABILITY;

typedef NS_OPTIONS(NSUInteger, BESelectionFlags) {
    BESelectionFlagsNone    = 0,
    BEWordIsNearTap         = 1 << 0,
    BESelectionFlipped      = 1 << 1,
    BEPhraseBoundaryChanged = 1 << 2,
} BROWSERENGINE_TEXTINPUT_AVAILABILITY;
