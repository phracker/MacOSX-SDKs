/*
    NSEvent.h
    Application Kit
    Copyright (c) 1994-2018, Apple Inc.
    All rights reserved.
*/

#import <AppKit/NSTouch.h>
#import <ApplicationServices/ApplicationServices.h>
#import <Foundation/NSObjCRuntime.h>
#import <Foundation/NSObject.h>
#import <Foundation/NSDate.h>
#import <Foundation/NSGeometry.h>
#import <Foundation/NSSet.h>
#import <IOKit/hidsystem/IOLLEvent.h>
#import <limits.h>

NS_ASSUME_NONNULL_BEGIN

@class NSGraphicsContext, NSWindow, NSTrackingArea;

typedef NS_ENUM(NSUInteger, NSEventType) {        /* various types of events */
    NSEventTypeLeftMouseDown             = 1,
    NSEventTypeLeftMouseUp               = 2,
    NSEventTypeRightMouseDown            = 3,
    NSEventTypeRightMouseUp              = 4,
    NSEventTypeMouseMoved                = 5,
    NSEventTypeLeftMouseDragged          = 6,
    NSEventTypeRightMouseDragged         = 7,
    NSEventTypeMouseEntered              = 8,
    NSEventTypeMouseExited               = 9,
    NSEventTypeKeyDown                   = 10,
    NSEventTypeKeyUp                     = 11,
    NSEventTypeFlagsChanged              = 12,
    NSEventTypeAppKitDefined             = 13,
    NSEventTypeSystemDefined             = 14,
    NSEventTypeApplicationDefined        = 15,
    NSEventTypePeriodic                  = 16,
    NSEventTypeCursorUpdate              = 17,
    NSEventTypeScrollWheel               = 22,
    NSEventTypeTabletPoint               = 23,
    NSEventTypeTabletProximity           = 24,
    NSEventTypeOtherMouseDown            = 25,
    NSEventTypeOtherMouseUp              = 26,
    NSEventTypeOtherMouseDragged         = 27,
    /* The following event types are available on some hardware on 10.5.2 and later */
    NSEventTypeGesture NS_ENUM_AVAILABLE_MAC(10_5)       = 29,
    NSEventTypeMagnify NS_ENUM_AVAILABLE_MAC(10_5)       = 30,
    NSEventTypeSwipe   NS_ENUM_AVAILABLE_MAC(10_5)       = 31,
    NSEventTypeRotate  NS_ENUM_AVAILABLE_MAC(10_5)       = 18,
    NSEventTypeBeginGesture NS_ENUM_AVAILABLE_MAC(10_5)  = 19,
    NSEventTypeEndGesture NS_ENUM_AVAILABLE_MAC(10_5)    = 20,
    
#if __LP64__
    NSEventTypeSmartMagnify NS_ENUM_AVAILABLE_MAC(10_8) = 32,
#endif
    NSEventTypeQuickLook NS_ENUM_AVAILABLE_MAC(10_8) = 33,
    
#if __LP64__
    NSEventTypePressure NS_ENUM_AVAILABLE_MAC(10_10_3) = 34,
    NSEventTypeDirectTouch NS_ENUM_AVAILABLE_MAC(10_10) = 37,
#endif
};

static const NSEventType NSLeftMouseDown 	NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSEventTypeLeftMouseDown", 10_0, 10_12) = NSEventTypeLeftMouseDown;
static const NSEventType NSLeftMouseUp 		NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSEventTypeLeftMouseUp", 10_0, 10_12) = NSEventTypeLeftMouseUp;
static const NSEventType NSRightMouseDown 	NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSEventTypeRightMouseDown", 10_0, 10_12) = NSEventTypeRightMouseDown;
static const NSEventType NSRightMouseUp		NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSEventTypeRightMouseUp", 10_0, 10_12) = NSEventTypeRightMouseUp;
static const NSEventType NSMouseMoved 		NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSEventTypeMouseMoved", 10_0, 10_12) = NSEventTypeMouseMoved;
static const NSEventType NSLeftMouseDragged	NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSEventTypeLeftMouseDragged", 10_0, 10_12) = NSEventTypeLeftMouseDragged;
static const NSEventType NSRightMouseDragged 	NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSEventTypeRightMouseDragged", 10_0, 10_12) = NSEventTypeRightMouseDragged;
static const NSEventType NSMouseEntered 	NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSEventTypeMouseEntered", 10_0, 10_12) = NSEventTypeMouseEntered;
static const NSEventType NSMouseExited 		NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSEventTypeMouseExited", 10_0, 10_12) = NSEventTypeMouseExited;
static const NSEventType NSKeyDown 		NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSEventTypeKeyDown", 10_0, 10_12) = NSEventTypeKeyDown;
static const NSEventType NSKeyUp 		NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSEventTypeKeyUp", 10_0, 10_12) = NSEventTypeKeyUp;
static const NSEventType NSFlagsChanged 	NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSEventTypeFlagsChanged", 10_0, 10_12) = NSEventTypeFlagsChanged;
static const NSEventType NSAppKitDefined 	NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSEventTypeAppKitDefined", 10_0, 10_12) = NSEventTypeAppKitDefined;
static const NSEventType NSSystemDefined 	NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSEventTypeSystemDefined", 10_0, 10_12) = NSEventTypeSystemDefined;
static const NSEventType NSApplicationDefined	NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSEventTypeApplicationDefined", 10_0, 10_12) = NSEventTypeApplicationDefined;
static const NSEventType NSPeriodic 		NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSEventTypePeriodic", 10_0, 10_12) = NSEventTypePeriodic;
static const NSEventType NSCursorUpdate 	NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSEventTypeCursorUpdate", 10_0, 10_12) = NSEventTypeCursorUpdate;
static const NSEventType NSScrollWheel 		NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSEventTypeScrollWheel", 10_0, 10_12) = NSEventTypeScrollWheel;
static const NSEventType NSTabletPoint 		NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSEventTypeTabletPoint", 10_0, 10_12) = NSEventTypeTabletPoint;
static const NSEventType NSTabletProximity 	NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSEventTypeTabletProximity", 10_0, 10_12) = NSEventTypeTabletProximity;
static const NSEventType NSOtherMouseDown	NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSEventTypeOtherMouseDown", 10_0, 10_12) = NSEventTypeOtherMouseDown;
static const NSEventType NSOtherMouseUp 	NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSEventTypeOtherMouseUp", 10_0, 10_12) = NSEventTypeOtherMouseUp;
static const NSEventType NSOtherMouseDragged 	NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSEventTypeOtherMouseDragged", 10_0, 10_12) = NSEventTypeOtherMouseDragged;


// For APIs introduced in Mac OS X 10.6 and later, this type is used with NS*Mask constants to indicate the events of interest.
typedef NS_OPTIONS(unsigned long long, NSEventMask) { /* masks for the types of events */
    NSEventMaskLeftMouseDown        = 1 << NSEventTypeLeftMouseDown,
    NSEventMaskLeftMouseUp           = 1 << NSEventTypeLeftMouseUp,
    NSEventMaskRightMouseDown        = 1 << NSEventTypeRightMouseDown,
    NSEventMaskRightMouseUp          = 1 << NSEventTypeRightMouseUp,
    NSEventMaskMouseMoved            = 1 << NSEventTypeMouseMoved,
    NSEventMaskLeftMouseDragged      = 1 << NSEventTypeLeftMouseDragged,
    NSEventMaskRightMouseDragged     = 1 << NSEventTypeRightMouseDragged,
    NSEventMaskMouseEntered          = 1 << NSEventTypeMouseEntered,
    NSEventMaskMouseExited           = 1 << NSEventTypeMouseExited,
    NSEventMaskKeyDown               = 1 << NSEventTypeKeyDown,
    NSEventMaskKeyUp                 = 1 << NSEventTypeKeyUp,
    NSEventMaskFlagsChanged          = 1 << NSEventTypeFlagsChanged,
    NSEventMaskAppKitDefined         = 1 << NSEventTypeAppKitDefined,
    NSEventMaskSystemDefined         = 1 << NSEventTypeSystemDefined,
    NSEventMaskApplicationDefined    = 1 << NSEventTypeApplicationDefined,
    NSEventMaskPeriodic              = 1 << NSEventTypePeriodic,
    NSEventMaskCursorUpdate          = 1 << NSEventTypeCursorUpdate,
    NSEventMaskScrollWheel           = 1 << NSEventTypeScrollWheel,
    NSEventMaskTabletPoint           = 1 << NSEventTypeTabletPoint,
    NSEventMaskTabletProximity       = 1 << NSEventTypeTabletProximity,
    NSEventMaskOtherMouseDown        = 1 << NSEventTypeOtherMouseDown,
    NSEventMaskOtherMouseUp          = 1 << NSEventTypeOtherMouseUp,
    NSEventMaskOtherMouseDragged     = 1 << NSEventTypeOtherMouseDragged,
    /* The following event masks are available on some hardware on 10.5.2 and later */
    NSEventMaskGesture NS_ENUM_AVAILABLE_MAC(10_5)          = 1 << NSEventTypeGesture,
    NSEventMaskMagnify NS_ENUM_AVAILABLE_MAC(10_5)          = 1 << NSEventTypeMagnify,
    NSEventMaskSwipe NS_ENUM_AVAILABLE_MAC(10_5)            = 1U << NSEventTypeSwipe,
    NSEventMaskRotate NS_ENUM_AVAILABLE_MAC(10_5)           = 1 << NSEventTypeRotate,
    NSEventMaskBeginGesture NS_ENUM_AVAILABLE_MAC(10_5)     = 1 << NSEventTypeBeginGesture,
    NSEventMaskEndGesture NS_ENUM_AVAILABLE_MAC(10_5)       = 1 << NSEventTypeEndGesture,
    
#if __LP64__
    /* Note: You can only use these event masks on 64 bit. In other words, you cannot setup a local, nor global, event monitor for these event types on 32 bit. Also, you cannot search the event queue for them (nextEventMatchingMask:...) on 32 bit.
     */
    NSEventMaskSmartMagnify NS_ENUM_AVAILABLE_MAC(10_8) = 1ULL << NSEventTypeSmartMagnify,
    NSEventMaskPressure NS_ENUM_AVAILABLE_MAC(10_10_3) = 1ULL << NSEventTypePressure,
    NSEventMaskDirectTouch NS_ENUM_AVAILABLE_MAC(10_12_2) = 1ULL << NSEventTypeDirectTouch,
#endif
    
    NSEventMaskAny              = NSUIntegerMax,
    
};

static const NSEventMask NSLeftMouseDownMask 		NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSEventMaskLeftMouseDown", 10_0, 10_12) = NSEventMaskLeftMouseDown;
static const NSEventMask NSLeftMouseUpMask 		NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSEventMaskLeftMouseUp", 10_0, 10_12) = NSEventMaskLeftMouseUp;
static const NSEventMask NSRightMouseDownMask	 	NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSEventMaskRightMouseDown", 10_0, 10_12) = NSEventMaskRightMouseDown;
static const NSEventMask NSRightMouseUpMask 		NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSEventMaskRightMouseUp", 10_0, 10_12) = NSEventMaskRightMouseUp;
static const NSEventMask NSMouseMovedMask 		NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSEventMaskMouseMoved", 10_0, 10_12) = NSEventMaskMouseMoved;
static const NSEventMask NSLeftMouseDraggedMask 	NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSEventMaskLeftMouseDragged", 10_0, 10_12) = NSEventMaskLeftMouseDragged;
static const NSEventMask NSRightMouseDraggedMask 	NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSEventMaskRightMouseDragged", 10_0, 10_12) = NSEventMaskRightMouseDragged;
static const NSEventMask NSMouseEnteredMask 		NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSEventMaskMouseEntered", 10_0, 10_12) = NSEventMaskMouseEntered;
static const NSEventMask NSMouseExitedMask 		NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSEventMaskMouseExited", 10_0, 10_12) = NSEventMaskMouseExited;
static const NSEventMask NSKeyDownMask 			NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSEventMaskKeyDown", 10_0, 10_12) = NSEventMaskKeyDown;
static const NSEventMask NSKeyUpMask 			NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSEventMaskKeyUp", 10_0, 10_12) = NSEventMaskKeyUp;
static const NSEventMask NSFlagsChangedMask 		NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSEventMaskFlagsChanged", 10_0, 10_12) = NSEventMaskFlagsChanged;
static const NSEventMask NSAppKitDefinedMask 		NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSEventMaskAppKitDefined", 10_0, 10_12) = NSEventMaskAppKitDefined;
static const NSEventMask NSSystemDefinedMask 		NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSEventMaskSystemDefined", 10_0, 10_12) = NSEventMaskSystemDefined;
static const NSEventMask NSApplicationDefinedMask 	NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSEventMaskApplicationDefined", 10_0, 10_12) = NSEventMaskApplicationDefined;
static const NSEventMask NSPeriodicMask 		NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSEventMaskPeriodic", 10_0, 10_12) = NSEventMaskPeriodic;
static const NSEventMask NSCursorUpdateMask 		NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSEventMaskCursorUpdate", 10_0, 10_12) = NSEventMaskCursorUpdate;
static const NSEventMask NSScrollWheelMask 		NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSEventMaskScrollWheel", 10_0, 10_12) = NSEventMaskScrollWheel;
static const NSEventMask NSTabletPointMask 		NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSEventMaskTabletPoint", 10_0, 10_12) = NSEventMaskTabletPoint;
static const NSEventMask NSTabletProximityMask	 	NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSEventMaskTabletProximity", 10_0, 10_12) = NSEventMaskTabletProximity;
static const NSEventMask NSOtherMouseDownMask 		NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSEventMaskOtherMouseDown", 10_0, 10_12) = NSEventMaskOtherMouseDown;
static const NSEventMask NSOtherMouseUpMask 		NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSEventMaskOtherMouseUp", 10_0, 10_12) = NSEventMaskOtherMouseUp;
static const NSEventMask NSOtherMouseDraggedMask 	NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSEventMaskOtherMouseDragged", 10_0, 10_12) = NSEventMaskOtherMouseDragged;
static const NSEventMask NSAnyEventMask			NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSEventMaskAny", 10_0, 10_12) = NSUIntegerMax;

#if __LP64__
NS_INLINE NSEventMask NSEventMaskFromType(NSEventType type) { return (1UL << type); }
#else
NS_INLINE NSEventMask NSEventMaskFromType(NSEventType type) { return (1 << type); }
#endif

/* Device-independent bits found in event modifier flags */
typedef NS_OPTIONS(NSUInteger, NSEventModifierFlags) {
    NSEventModifierFlagCapsLock           = 1 << 16, // Set if Caps Lock key is pressed.
    NSEventModifierFlagShift              = 1 << 17, // Set if Shift key is pressed.
    NSEventModifierFlagControl            = 1 << 18, // Set if Control key is pressed.
    NSEventModifierFlagOption             = 1 << 19, // Set if Option or Alternate key is pressed.
    NSEventModifierFlagCommand            = 1 << 20, // Set if Command key is pressed.
    NSEventModifierFlagNumericPad         = 1 << 21, // Set if any key in the numeric keypad is pressed.
    NSEventModifierFlagHelp               = 1 << 22, // Set if the Help key is pressed.
    NSEventModifierFlagFunction           = 1 << 23, // Set if any function key is pressed.
    
    // Used to retrieve only the device-independent modifier flags, allowing applications to mask off the device-dependent modifier flags, including event coalescing information.
    NSEventModifierFlagDeviceIndependentFlagsMask    = 0xffff0000UL
};

static const NSEventModifierFlags NSAlphaShiftKeyMask         NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSEventModifierFlagCapsLock", 10_0, 10_12) = NSEventModifierFlagCapsLock;
static const NSEventModifierFlags NSShiftKeyMask              NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSEventModifierFlagShift", 10_0, 10_12) = NSEventModifierFlagShift;
static const NSEventModifierFlags NSControlKeyMask            NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSEventModifierFlagControl", 10_0, 10_12) = NSEventModifierFlagControl;
static const NSEventModifierFlags NSAlternateKeyMask          NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSEventModifierFlagOption", 10_0, 10_12) = NSEventModifierFlagOption;
static const NSEventModifierFlags NSCommandKeyMask            NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSEventModifierFlagCommand", 10_0, 10_12) = NSEventModifierFlagCommand;
static const NSEventModifierFlags NSNumericPadKeyMask         NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSEventModifierFlagNumericPad", 10_0, 10_12) = NSEventModifierFlagNumericPad;
static const NSEventModifierFlags NSHelpKeyMask               NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSEventModifierFlagHelp", 10_0, 10_12) = NSEventModifierFlagHelp;
static const NSEventModifierFlags NSFunctionKeyMask           NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSEventModifierFlagFunction", 10_0, 10_12) = NSEventModifierFlagFunction;
static const NSEventModifierFlags NSDeviceIndependentModifierFlagsMask    NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSEventModifierFlagDeviceIndependentFlagsMask", 10_0, 10_12) = NSEventModifierFlagDeviceIndependentFlagsMask;

/* pointer types for NSEventTypeTabletProximity events or mouse events with subtype NSEventSubtypeTabletProximity*/
typedef NS_ENUM(NSUInteger, NSPointingDeviceType) {        
    NSPointingDeviceTypeUnknown     = NX_TABLET_POINTER_UNKNOWN,
    NSPointingDeviceTypePen         = NX_TABLET_POINTER_PEN,
    NSPointingDeviceTypeCursor      = NX_TABLET_POINTER_CURSOR,
    NSPointingDeviceTypeEraser      = NX_TABLET_POINTER_ERASER
};

static const NSPointingDeviceType NSUnknownPointingDevice     NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSPointingDeviceTypeUnknown", 10_0, 10_12) = NSPointingDeviceTypeUnknown;
static const NSPointingDeviceType NSPenPointingDevice         NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSPointingDeviceTypePen", 10_0, 10_12) = NSPointingDeviceTypePen;
static const NSPointingDeviceType NSCursorPointingDevice      NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSPointingDeviceTypeCursor", 10_0, 10_12) = NSPointingDeviceTypeCursor;
static const NSPointingDeviceType NSEraserPointingDevice      NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSPointingDeviceTypeEraser", 10_0, 10_12) = NSPointingDeviceTypeEraser;

/* button masks for NSEventTypeTabletPoint events or mouse events with subtype NSEventSubtypeTabletPoint */
typedef NS_OPTIONS(NSUInteger, NSEventButtonMask) {
    NSEventButtonMaskPenTip                = NX_TABLET_BUTTON_PENTIPMASK,
    NSEventButtonMaskPenLowerSide          = NX_TABLET_BUTTON_PENLOWERSIDEMASK,
    NSEventButtonMaskPenUpperSide          = NX_TABLET_BUTTON_PENUPPERSIDEMASK
};

static const NSEventButtonMask NSPenTipMask                NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSEventButtonMaskPenTip", 10_0, 10_12) = NSEventButtonMaskPenTip;
static const NSEventButtonMask NSPenLowerSideMask          NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSEventButtonMaskPenLowerSide", 10_0, 10_12) = NSEventButtonMaskPenLowerSide;
static const NSEventButtonMask NSPenUpperSideMask          NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSEventButtonMaskPenUpperSide", 10_0, 10_12) = NSEventButtonMaskPenUpperSide;

typedef NS_OPTIONS(NSUInteger, NSEventPhase) {
    NSEventPhaseNone        = 0, // event not associated with a phase.
    NSEventPhaseBegan       = 0x1 << 0,
    NSEventPhaseStationary  = 0x1 << 1,
    NSEventPhaseChanged     = 0x1 << 2,
    NSEventPhaseEnded       = 0x1 << 3,
    NSEventPhaseCancelled   = 0x1 << 4,
    NSEventPhaseMayBegin    = 0x1 << 5,
} NS_ENUM_AVAILABLE_MAC(10_7);

typedef NS_ENUM(NSInteger, NSEventGestureAxis) {
    NSEventGestureAxisNone = 0,
    NSEventGestureAxisHorizontal,
    NSEventGestureAxisVertical
} NS_ENUM_AVAILABLE_MAC(10_7);

typedef NS_OPTIONS(NSUInteger, NSEventSwipeTrackingOptions) {
    NSEventSwipeTrackingLockDirection = 0x1 << 0, // Clamp gestureAmount to 0 if the user starts to swipe in the opposite direction than they started.
    NSEventSwipeTrackingClampGestureAmount = 0x1 << 1  // Don't allow gestureAmount to go beyond +/-1.0
} NS_ENUM_AVAILABLE_MAC(10_7);

typedef NS_ENUM(short, NSEventSubtype) {
    /* event subtypes for NSEventTypeAppKitDefined events */
    NSEventSubtypeWindowExposed            = 0,
    NSEventSubtypeApplicationActivated     = 1,
    NSEventSubtypeApplicationDeactivated   = 2,
    NSEventSubtypeWindowMoved              = 4,
    NSEventSubtypeScreenChanged            = 8,
    
    /* event subtypes for NSEventTypeSystemDefined events */
    NSEventSubtypePowerOff             = 1,
    
    /* event subtypes for mouse events */
    NSEventSubtypeMouseEvent        = NX_SUBTYPE_DEFAULT,
    NSEventSubtypeTabletPoint       = NX_SUBTYPE_TABLET_POINT,
    NSEventSubtypeTabletProximity   = NX_SUBTYPE_TABLET_PROXIMITY,
    NSEventSubtypeTouch  NS_ENUM_AVAILABLE_MAC(10_6)             = NX_SUBTYPE_MOUSE_TOUCH
};

static const NSEventSubtype NSWindowExposedEventType            NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSEventSubtypeWindowExposed", 10_0, 10_12) = NSEventSubtypeWindowExposed;
static const NSEventSubtype NSApplicationActivatedEventType     NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSEventSubtypeApplicationActivated", 10_0, 10_12) = NSEventSubtypeApplicationActivated;
static const NSEventSubtype NSApplicationDeactivatedEventType   NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSEventSubtypeApplicationDeactivated", 10_0, 10_12) = NSEventSubtypeApplicationDeactivated;
static const NSEventSubtype NSWindowMovedEventType              NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSEventSubtypeWindowMoved", 10_0, 10_12) = NSEventSubtypeWindowMoved;
static const NSEventSubtype NSScreenChangedEventType            NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSEventSubtypeScreenChanged", 10_0, 10_12) = NSEventSubtypeScreenChanged;
static const NSEventSubtype NSAWTEventType                      NS_ENUM_DEPRECATED_MAC(10_10, 10_12, "This subtype no longer exists") = (NSEventSubtype)16;
static const NSEventSubtype NSPowerOffEventType             NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSEventSubtypePowerOff", 10_0, 10_12) = NSEventSubtypePowerOff;
static const NSEventSubtype NSMouseEventSubtype             NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSEventSubtypeMouseEvent", 10_0, 10_12) = NSEventSubtypeMouseEvent;
static const NSEventSubtype NSTabletPointEventSubtype       NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSEventSubtypeTabletPoint", 10_0, 10_12) = NSEventSubtypeTabletPoint;
static const NSEventSubtype NSTabletProximityEventSubtype   NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSEventSubtypeTabletProximity", 10_0, 10_12) = NSEventSubtypeTabletProximity;
static const NSEventSubtype NSTouchEventSubtype             NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSEventSubtypeTouch", 10_0, 10_12) = NSEventSubtypeTouch;


// NSPressureBehavior - The pressure gesture behavior that describes how a pressure gesture behaves and progresses
// In general, pressure gestures begin when stage reaches 1 and end when stage reaches 0. This corresponds to the simultaneously generated mouse down/up events.
typedef NS_ENUM(NSInteger, NSPressureBehavior) {
    NSPressureBehaviorUnknown = -1,
    
    // The default primary behavior when otherwise not explicitly configured. In 10.10.3 the default is NSPressureBehaviorPrimaryDeepClick.
    NSPressureBehaviorPrimaryDefault = 0,
    
    // Variable pressure with a small dynamic range after mouseDown.
    // Mouse events: LeftMouse
    // # of Stages: 1
    // Allowed stage transitions: 1->0
    // Actuations: mouseDown, mouseUp
    // stageTransition: NO
    NSPressureBehaviorPrimaryClick = 1,
    
    // Variable pressure with a large dynamic range after mouseDown suitable for drawing and general pressure use.
    // Mouse events: LeftMouse
    // # of Stages: 1
    // Allowed stage transitions: 1->0
    // Actuations: mouseDown, mouseUp
    // stageTransition: NO
    NSPressureBehaviorPrimaryGeneric = 2,
    
    // Variable pressure after mouseDown suitable for controlling speed. Used by NSAcceleratorButton
    // Mouse events: LeftMouse
    // # of Stages: 1
    // Allowed stage transitions: 1->0
    // Actuations: mouseDown, mouseUp
    // stageTransition: NO
    NSPressureBehaviorPrimaryAccelerator = 3,
    
    // Toggle between stages 1 and 2 until drag or mouse up (e.g. Force Click)
    // Mouse events: LeftMouse
    // # of Stages: 2 (stage 2 is disabled once dragging starts)
    // Allowed stage transitions: 1->0, 1->2, 2->1, 2->0
    // Actuations: mouseDown, mouseUp, 1->2, 2->1
    // stageTransition: into and release from stage 2
    NSPressureBehaviorPrimaryDeepClick = 5,
    
    // Toggle between stages 1 and 2 until mouse up (e.g. Force Click)
    // Mouse events: LeftMouse
    // # of Stages: 2
    // Allowed stage transitions: 1->0, 1->2, 2->1, 2->0
    // Actuations: mouseDown, mouseUp, 1->2, 2->1
    // stageTransition: into and release from stage 2
    NSPressureBehaviorPrimaryDeepDrag = 6,
    
}NS_ENUM_AVAILABLE_MAC(10_10_3);

@interface NSEvent : NSObject <NSCopying, NSCoding> {
    /*All instance variables are private*/
    NSEventType _type APPKIT_IVAR;
    NSPoint _location APPKIT_IVAR;
    unsigned int _modifierFlags APPKIT_IVAR;
    id _WSTimestamp APPKIT_IVAR;
    NSTimeInterval _timestamp APPKIT_IVAR;
    NSInteger _windowNumber APPKIT_IVAR;
    __weak NSWindow *_window APPKIT_IVAR;
    NSGraphicsContext* _context APPKIT_IVAR;
    union {
        struct {
            int eventNumber;
            int clickCount;
            float pressure;
#if __LP64__
            CGFloat deltaX;
            CGFloat deltaY;
            int subtype;
            short buttonNumber;
            short reserved1;
            int reserved2[3];
#endif
        } mouse;
        struct {
            __unsafe_unretained NSString *keys;
            __unsafe_unretained NSString *unmodKeys;
            unsigned short keyCode;
            BOOL isARepeat;
#if __LP64__
            int eventFlags;
            int reserved[5];
#endif
        } key;
        struct {
            int eventNumber;
            NSInteger trackingNumber;
            void *userData;
#if __LP64__
            int reserved[6];
#endif
        } tracking;
        struct {
            CGFloat deltaX;
            CGFloat deltaY;
            CGFloat deltaZ; 
#if __LP64__
            short subtype;
            short reserved1;
            int reserved2[6];
#endif
        } scrollWheel;
        struct {
            CGFloat deltaX;
            CGFloat deltaY;
            CGFloat deltaZ; 
#if __LP64__
            int reserved[7];
#endif
        } axisGesture;
        struct {
            short subtype;
            BOOL gestureEnded;
            BOOL reserved;
            int value;
            float percentage;
#if __LP64__
            int reserved2[7];
#endif
        } miscGesture;
        struct {
            int subtype;
            NSInteger data1;
            NSInteger data2;
#if __LP64__
            int reserved[6];
#endif
        } misc;
#if __LP64__
        int tabletPointData[14];
        int tabletProximityData[14];
#endif
    } _data APPKIT_IVAR;
    void *_eventRef APPKIT_IVAR;
#if __LP64__
    void *reserved1 APPKIT_IVAR;
    void *reserved2 APPKIT_IVAR;
#endif
}


/* these messages are valid for all events */
@property (readonly) NSEventType type;
@property (readonly) NSEventModifierFlags modifierFlags;
@property (readonly) NSTimeInterval timestamp;
@property (readonly, nullable, weak) NSWindow *window;
@property (readonly) NSInteger windowNumber;
@property (nullable, readonly, strong) NSGraphicsContext *context NS_DEPRECATED_MAC(10_0, 10_12, "This method always returns nil. If you need access to the current drawing context, use [NSGraphicsContext currentContext] inside of a draw operation.");

/* these messages are valid for all mouse down/up/drag events */
@property (readonly) NSInteger clickCount;
@property (readonly) NSInteger buttonNumber;    // for NSOtherMouse events, but will return valid constants for NSLeftMouse and NSRightMouse
/* these messages are valid for all mouse down/up/drag and enter/exit events */
@property (readonly) NSInteger eventNumber;

/* -pressure is valid for all mouse down/up/drag events, and is also valid for NSEventTypeTabletPoint events on 10.4 or later and NSEventTypePressure on 10.10.3 or later */
@property (readonly) float pressure;
/* -locationInWindow is valid for all mouse-related events */
@property (readonly) NSPoint locationInWindow;

/* these messages are valid for scroll wheel events and mouse move/drag events.  As of 10.5.2, deltaX and deltaY are also valid for swipe events.  A non-0 deltaX will represent a horizontal swipe, -1 for swipe right and 1 for swipe left.  A non-0 deltaY will represent a vertical swipe, -1 for swipe down and 1 for swipe up. As of 10.7, the preferred methods for scroll wheel events are scrollingDeltaX and scrollingDeltaY defined below.
*/
@property (readonly) CGFloat deltaX;    
@property (readonly) CGFloat deltaY;    
@property (readonly) CGFloat deltaZ;    // 0 for most scroll wheel and mouse events

/* This message is valid for NSEventTypeScrollWheel events. A generic scroll wheel issues rather coarse scroll deltas. Some Apple mice and trackpads provide much more precise delta. This method determines the resolution of the scrollDeltaX and scrollDeltaY values.
*/
@property (readonly) BOOL hasPreciseScrollingDeltas NS_AVAILABLE_MAC(10_7);

/* The following two message are the preferred API for accessing NSEventTypeScrollWheel deltas. When -hasPreciseScrollDeltas reutrns NO, multiply the returned value by line or row height. When -hasPreciseScrollDeltas returns YES, scroll by the returned value (in points). 
*/
@property (readonly) CGFloat scrollingDeltaX NS_AVAILABLE_MAC(10_7);
@property (readonly) CGFloat scrollingDeltaY NS_AVAILABLE_MAC(10_7);

/* This message is valid for NSEventTypeScrollWheel events. With the Magic Mouse and some trackpads, the user can flick thier finger resulting in a stream of scroll events that dissipate over time. The location of these scroll wheel events changes as the user moves the cursor. AppKit latches these scroll wheel events to the view that is under the cursor when the flick occurs. A custom view can use this method to recognize these momentum scroll events and further route the event to the appropriate sub component.
*/
@property (readonly) NSEventPhase momentumPhase NS_AVAILABLE_MAC(10_7);

/* valid for NSEventScrollWheel events. The user may choose to change the scrolling behavior such that it feels like they are moving the content instead of the scroll bar. To accomplish this, deltaX/Y and scrollingDeltaX/Y are automatically inverted for NSEventScrollWheel events according to the user's preferences. However, for some uses, the behavior should not respect the user preference. This method allows you to determine when the event has been inverted and compensate by multiplying -1 if needed. 
*/
@property (getter=isDirectionInvertedFromDevice, readonly) BOOL directionInvertedFromDevice NS_AVAILABLE_MAC(10_7);

/* these messages are valid for keyup and keydown events */
@property (nullable, readonly, copy) NSString *characters;
@property (nullable, readonly, copy) NSString *charactersIgnoringModifiers;
  /* the chars that would have been generated, regardless of modifier keys (except shift) */
@property (getter=isARepeat, readonly) BOOL ARepeat;
/* this message is valid for keyup, keydown and flagschanged events */
@property (readonly) unsigned short keyCode;        /* device-independent key number */

/* these messages are valid for enter and exit events */
@property (readonly) NSInteger trackingNumber;
@property (nullable, readonly) void *userData NS_RETURNS_INNER_POINTER;
/* -trackingArea returns the NSTrackingArea that generated this event.  It is possible for there to be no trackingArea associated with the event in some cases where the event corresponds to a trackingRect installed with -[NSView addTrackingRect:owner:userData:assumeInside:], in which case nil is returned. */
@property (nullable, readonly, strong) NSTrackingArea *trackingArea NS_AVAILABLE_MAC(10_5); 

/* this message is valid for kit, system, and app-defined events */
/* this message is also valid for mouse events on 10.4 or later */
@property (readonly) NSEventSubtype subtype;

/* these messages are valid for kit, system, and app-defined events */
@property (readonly) NSInteger data1;
@property (readonly) NSInteger data2;


/* -eventRef and +eventWithEventRef:  are valid for all events */
/* -eventRef returns an EventRef corresponding to the NSEvent.  The EventRef is retained by the NSEvent, so will be valid as long as the NSEvent is valid, and will be released when the NSEvent is freed.  You can use RetainEvent to extend the lifetime of the EventRef, with a corresponding ReleaseEvent when you are done with it.  If there is no EventRef corresponding to the NSEvent, -eventRef will return NULL.
*/
@property (nullable, readonly) const void * /* EventRef */eventRef NS_RETURNS_INNER_POINTER NS_AVAILABLE_MAC(10_5);
/* +eventWithEventRef: returns an autoreleased NSEvent corresponding to the EventRef.  The EventRef is retained by the NSEvent and will be released when the NSEvent is freed.  If there is no NSEvent corresponding to the EventRef, +eventWithEventRef will return nil.
*/
+ (nullable NSEvent *)eventWithEventRef:(const void * /* EventRef */)eventRef NS_AVAILABLE_MAC(10_5);

/* -CGEvent returns an autoreleased CGEventRef corresponding to the NSEvent.  If there is no CGEventRef corresponding to the NSEvent, -CGEvent will return NULL.
*/
@property (nullable, readonly) CGEventRef CGEvent NS_AVAILABLE_MAC(10_5);

/* +eventWithCGEvent: returns an autoreleased NSEvent corresponding to the CGEventRef.  The CGEventRef is retained by the NSEvent and will be released when the NSEvent is freed.  If there is no NSEvent corresponding to the CGEventRef, +eventWithEventRef will return nil.
*/
+ (nullable NSEvent *)eventWithCGEvent:(CGEventRef)cgEvent NS_AVAILABLE_MAC(10_5);

/* Enable or disable coalescing of mouse movement events, including mouse moved, mouse dragged, and tablet events.  Coalescing is enabled by default.
*/
@property (class, getter=isMouseCoalescingEnabled) BOOL mouseCoalescingEnabled NS_AVAILABLE_MAC(10_5);


/* This message is valid for events of type NSEventTypeMagnify, on 10.5.2 or later */
@property (readonly) CGFloat magnification NS_AVAILABLE_MAC(10_5);       // change in magnification.   This value should be added to the current scaling of an item to get the new scale factor.

/* this message is valid for mouse events with subtype NSEventSubtypeTabletPoint or NSEventSubtypeTabletProximity, and for NSEventTypeTabletPoint and NSEventTypeTabletProximity events */
@property (readonly) NSUInteger deviceID;

/* this message is valid for valid for mouse events with subtype NSEventSubtypeTabletPoint, and for NSEventTypeTabletPoint events.  On 10.5.2 or later, it is also valid for NSEventTypeRotate events. */
@property (readonly) float rotation;       // In degrees.  For NSEventTypeTabletPoint, this is rotation of the pen.  For NSEventTypeRotate, it is rotation on the track pad.

/* these messages are valid for mouse events with subtype NSEventSubtypeTabletPoint, and for NSEventTypeTabletPoint events */
/* absolute x coordinate in tablet space at full tablet resolution */
@property (readonly) NSInteger absoluteX; 
/* absolute y coordinate in tablet space at full tablet resolution */
@property (readonly) NSInteger absoluteY;               
/* absolute z coordinate in tablet space at full tablet resolution */
@property (readonly) NSInteger absoluteZ;     
/* mask indicating which buttons are pressed.*/
@property (readonly) NSEventButtonMask buttonMask;
/* range is -1 to 1 for both axes */
@property (readonly) NSPoint tilt;     
/* tangential pressure on the device; range is -1 to 1 */
@property (readonly) float tangentialPressure;  
/* NSArray of 3 vendor defined shorts */
@property (readonly, strong) id vendorDefined;    

/* these messages are valid for mouse events with subtype NSEventSubtypeTabletProximity, and  for NSEventTypeTabletProximity events */
/* vendor defined, typically USB vendor ID */
@property (readonly) NSUInteger vendorID;
/* vendor defined tablet ID */
@property (readonly) NSUInteger tabletID;
/* index of the device on the tablet.  Usually 0, except for tablets that support multiple concurrent devices */
@property (readonly) NSUInteger pointingDeviceID;
/* system assigned unique tablet ID */
@property (readonly) NSUInteger systemTabletID;
/* vendor defined pointing device type */
@property (readonly) NSUInteger vendorPointingDeviceType; 
/* vendor defined serial number of pointing device */
@property (readonly) NSUInteger pointingDeviceSerialNumber; 
/* vendor defined unique ID */
@property (readonly) unsigned long long uniqueID;    
/* mask representing capabilities of device */
@property (readonly) NSUInteger capabilityMask;    
/* mask representing capabilities of device */
@property (readonly) NSPointingDeviceType pointingDeviceType;
/* YES - entering; NO - leaving */
@property (getter=isEnteringProximity, readonly) BOOL enteringProximity;    


- (NSSet<NSTouch *> *)touchesMatchingPhase:(NSTouchPhase)phase inView:(nullable NSView *)view NS_AVAILABLE_MAC(10_6);

/* Only valid for NSEventTypeGesture events. Equivalent to [event touchesMatchingPhase:NSTouchPhaseAny inView:nil] */
- (NSSet <NSTouch *> *)allTouches NS_AVAILABLE_MAC(10_12);

/* Only valid for NSEventTypeGesture events. Equivalent to [event touchesMatchingPhase:NSTouchPhaseAny inView:view] */
- (NSSet <NSTouch *> *)touchesForView:(NSView *)view NS_AVAILABLE_MAC(10_12);

/* An array of auxiliary NSTouch’s for the touch events that did not get delivered for a given main touch. This also includes an auxiliary version of the main touch itself. Only valid for NSEventTypeDirectTouch events.
*/
- (NSArray <NSTouch *> *)coalescedTouchesForTouch:(NSTouch *)touch NS_AVAILABLE_MAC(10_12_2);

/* The phase of a gesture scroll event. A gesture phrase are all the events that begin with a NSEventPhaseBegan and end with either a NSEventPhaseEnded or NSEventPhaseCancelled. All the gesture events are sent to the view under the cursor when the NSEventPhaseBegan occurred.  A gesture scroll event starts with a NSEventPhaseBegan phase and ends with a NSPhaseEnded. Legacy scroll wheel events (say from a Mighty Mouse) and momentum scroll wheel events have a phase of NSEventPhaseNone.
    Valid for NSEventTypeScrollWheel
*/
@property (readonly) NSEventPhase phase NS_AVAILABLE_MAC(10_7);

/* This message is valid for NSEventTypePressure events. Pressure gesture events go through multiple stages.
*/
@property (readonly) NSInteger stage NS_AVAILABLE_MAC(10_10_3);

/* This message is valid for NSEventTypePressure events. Positive stageTransition describes approaching the next stage of the pressure gesture. Negative stageTransition describes approaching release of the current stage.
*/
@property (readonly) CGFloat stageTransition NS_AVAILABLE_MAC(10_10_3);

/* This message is valid for Mouse events. The event mask describing the various events that you may also get during this event sequence. Useful for determining if the input device issuing this mouse event can also simultaneously issue NSEventTypePressure events.
*/
@property (readonly) NSEventMask associatedEventsMask NS_AVAILABLE_MAC(10_10_3);

/* this message is valid for NSEventTypePressure events */
@property (readonly) NSPressureBehavior pressureBehavior NS_AVAILABLE_MAC(10_11);

/* Returns the user's preference about using gesture scrolls as a way to track fluid swipes. This value is determined by the Mouse / Trackpad preference panel for the current user. Generally, NSScrollView will check this for you. However, if your app is not using an NSScrollView, or your NSResponder can receive scrollWheel messages without first being sent to an NSScrollView, then you should check this preference before calling -trackSwipeEventWithOptions:dampenAmountThresholdMin:max:usingHandler:
*/
@property (class, readonly, getter=isSwipeTrackingFromScrollEventsEnabled) BOOL swipeTrackingFromScrollEventsEnabled NS_AVAILABLE_MAC(10_7);

/* This method allows easy tracking and UI feedback of scroll events as fluid swipes. Fluid swipes are tracked not only to the end of the physical gesture phase by the user, but also to the completion of any UI animation that should be performed. Using this method allows your implementation to maintain a consistent fluid feel with other applications. Any gesture amount outside of the supplied minimum and maximum dampen amount is pre-dampened for you to provide an elastic feel.

   The trackingHandler has the following parameters:
       gestureAmount: the amount of gesture that you should display in the UI. This may be a fractional amount. Note: Upon completion, the gesture amount will animate to one of the following values: -1, 0, 1.
       phase: the phase of the physical gesture as performed by the user. When the phase is either NSPhaseEnded, or NSPhaseCancelled, the use has physically ended the gesture successfully or not, respectively. Your handler will continue to be called with updated progress values to complete the fluid swipe animation with a phase of NSPhaseNone.
       isComplete: Signifies the swipe and animation are complete and you should tear down any temporary animation objects. The trackingHandler is released and will not be called further.
      *stop: A pointer to a BOOL allowing you to cancel further use of this trackingHandler by setting its value to YES. The trackingHandler is released appropriately.

   Note: This method returns immediately and tracking is performed asynchronously.

   Valid for Scroll events with a phase of NSEventPhaseBegan or NSEventPhaseChanged
*/
- (void)trackSwipeEventWithOptions:(NSEventSwipeTrackingOptions)options dampenAmountThresholdMin:(CGFloat)minDampenThreshold max:(CGFloat)maxDampenThreshold usingHandler:(void (^)(CGFloat gestureAmount, NSEventPhase phase, BOOL isComplete, BOOL *stop))trackingHandler NS_AVAILABLE_MAC(10_7);

/* used for initial delay and periodic behavior in tracking loops */
+ (void)startPeriodicEventsAfterDelay:(NSTimeInterval)delay withPeriod:(NSTimeInterval)period;
+ (void)stopPeriodicEvents;

/* apps will rarely create these objects */
+ (nullable NSEvent *)mouseEventWithType:(NSEventType)type location:(NSPoint)location modifierFlags:(NSEventModifierFlags)flags timestamp:(NSTimeInterval)time windowNumber:(NSInteger)wNum context:(nullable NSGraphicsContext* __unused)unusedPassNil eventNumber:(NSInteger)eNum clickCount:(NSInteger)cNum pressure:(float)pressure;
+ (nullable NSEvent *)keyEventWithType:(NSEventType)type location:(NSPoint)location modifierFlags:(NSEventModifierFlags)flags timestamp:(NSTimeInterval)time windowNumber:(NSInteger)wNum context:(nullable NSGraphicsContext* __unused)unusedPassNil characters:(NSString *)keys charactersIgnoringModifiers:(NSString *)ukeys isARepeat:(BOOL)flag keyCode:(unsigned short)code;
+ (nullable NSEvent *)enterExitEventWithType:(NSEventType)type location:(NSPoint)location modifierFlags:(NSEventModifierFlags)flags timestamp:(NSTimeInterval)time windowNumber:(NSInteger)wNum context:(nullable NSGraphicsContext* __unused)unusedPassNil eventNumber:(NSInteger)eNum trackingNumber:(NSInteger)tNum userData:(nullable void *)data;
+ (nullable NSEvent *)otherEventWithType:(NSEventType)type location:(NSPoint)location modifierFlags:(NSEventModifierFlags)flags timestamp:(NSTimeInterval)time windowNumber:(NSInteger)wNum context:(nullable NSGraphicsContext* __unused)unusedPassNil subtype:(short)subtype data1:(NSInteger)d1 data2:(NSInteger)d2;

// global mouse coordinates
@property (class, readonly) NSPoint mouseLocation;

/* modifier keys currently down.  This returns the state of devices combined with synthesized events at the moment, independent of which events have been delivered via the event stream. */
@property (class, readonly) NSEventModifierFlags modifierFlags NS_AVAILABLE_MAC(10_6);

/* mouse buttons currently down.  Returns indices of the mouse buttons currently down.  1 << 0 corresponds to leftMouse, 1 << 1 to rightMouse, and 1 << n, n >= 2 to other mouse buttons.  This returns the state of devices combined with synthesized events at the moment, independent of which events have been delivered via the event stream, so this method is not suitable for tracking. */
@property (class, readonly) NSUInteger pressedMouseButtons NS_AVAILABLE_MAC(10_6);

/* the time in which a second click must occur in order to be considered a doubleClick.  This is a system value so overrides will have no effect. */
@property (class, readonly) NSTimeInterval doubleClickInterval   NS_AVAILABLE_MAC(10_6);
/* the time for which a key must be held down in order to generate the first key repeat event.  This is a system value so overrides will have no effect. */
@property (class, readonly) NSTimeInterval keyRepeatDelay        NS_AVAILABLE_MAC(10_6);
/* the time between subsequent key repeat events.  This is a system value so overrides will have no effect. */
@property (class, readonly) NSTimeInterval keyRepeatInterval     NS_AVAILABLE_MAC(10_6);

/*
   API for monitoring events in other processes, or in your own process. For either +addGlobal or +addLocal, pass an event mask specifying which events you wish to monitor, and a block that will be called with the event to monitor.

   Use +addGlobal to install an event monitor that receives copies of events posted to other applications. Events are delivered asynchronously to your app and you can only observe the event; you cannot modify or otherwise prevent the event from being delivered to its original target application. Key-related events may only be monitored if accessibility is enabled or if your application is trusted for accessibility access (see AXIsProcessTrusted in AXUIElement.h). Note that your handler will not be called for events that are sent to your own application.

   Use +addLocal to install an event monitor that receives events before they are dispatched by -[NSApplication sendEvent:]. In this case, your block should either return a valid NSEvent (which may be the same as the incoming NSEvent, or may be a newly created NSEvent) to cause the event to be dispatched, or it may return nil to stop dispatching of the event. Note that your handler will not be called for events that are consumed by nested event-tracking loops such as control tracking, menu tracking, or window dragging; only events that are dispatched through -[NSApplication sendEvent:] will be passed to your handler.

   In either case, the return value of the API is a retained NSObject. You typically do not need to retain and release the event monitor yourself, since the implementation will retain it while needed.
   
   To remove the event monitor, under both garbage collection and non-GC, pass the return value from the +add API to +removeMonitor.
*/
+ (nullable id)addGlobalMonitorForEventsMatchingMask:(NSEventMask)mask handler:(void (^)(NSEvent*))block NS_AVAILABLE_MAC(10_6);
+ (nullable id)addLocalMonitorForEventsMatchingMask:(NSEventMask)mask handler:(NSEvent* __nullable (^)(NSEvent*))block NS_AVAILABLE_MAC(10_6);
+ (void)removeMonitor:(id)eventMonitor NS_AVAILABLE_MAC(10_6);

@end


/* Unicodes we reserve for function keys on the keyboard,  OpenStep reserves the range 0xF700-0xF8FF for this purpose.  The availability of various keys will be system dependent. */
enum {
    NSUpArrowFunctionKey        = 0xF700,
    NSDownArrowFunctionKey      = 0xF701,
    NSLeftArrowFunctionKey      = 0xF702,
    NSRightArrowFunctionKey     = 0xF703,
    NSF1FunctionKey             = 0xF704,
    NSF2FunctionKey             = 0xF705,
    NSF3FunctionKey             = 0xF706,
    NSF4FunctionKey             = 0xF707,
    NSF5FunctionKey             = 0xF708,
    NSF6FunctionKey             = 0xF709,
    NSF7FunctionKey             = 0xF70A,
    NSF8FunctionKey             = 0xF70B,
    NSF9FunctionKey             = 0xF70C,
    NSF10FunctionKey            = 0xF70D,
    NSF11FunctionKey            = 0xF70E,
    NSF12FunctionKey            = 0xF70F,
    NSF13FunctionKey            = 0xF710,
    NSF14FunctionKey            = 0xF711,
    NSF15FunctionKey            = 0xF712,
    NSF16FunctionKey            = 0xF713,
    NSF17FunctionKey            = 0xF714,
    NSF18FunctionKey            = 0xF715,
    NSF19FunctionKey            = 0xF716,
    NSF20FunctionKey            = 0xF717,
    NSF21FunctionKey            = 0xF718,
    NSF22FunctionKey            = 0xF719,
    NSF23FunctionKey            = 0xF71A,
    NSF24FunctionKey            = 0xF71B,
    NSF25FunctionKey            = 0xF71C,
    NSF26FunctionKey            = 0xF71D,
    NSF27FunctionKey            = 0xF71E,
    NSF28FunctionKey            = 0xF71F,
    NSF29FunctionKey            = 0xF720,
    NSF30FunctionKey            = 0xF721,
    NSF31FunctionKey            = 0xF722,
    NSF32FunctionKey            = 0xF723,
    NSF33FunctionKey            = 0xF724,
    NSF34FunctionKey            = 0xF725,
    NSF35FunctionKey            = 0xF726,
    NSInsertFunctionKey         = 0xF727,
    NSDeleteFunctionKey         = 0xF728,
    NSHomeFunctionKey           = 0xF729,
    NSBeginFunctionKey          = 0xF72A,
    NSEndFunctionKey            = 0xF72B,
    NSPageUpFunctionKey         = 0xF72C,
    NSPageDownFunctionKey       = 0xF72D,
    NSPrintScreenFunctionKey    = 0xF72E,
    NSScrollLockFunctionKey     = 0xF72F,
    NSPauseFunctionKey          = 0xF730,
    NSSysReqFunctionKey         = 0xF731,
    NSBreakFunctionKey          = 0xF732,
    NSResetFunctionKey          = 0xF733,
    NSStopFunctionKey           = 0xF734,
    NSMenuFunctionKey           = 0xF735,
    NSUserFunctionKey           = 0xF736,
    NSSystemFunctionKey         = 0xF737,
    NSPrintFunctionKey          = 0xF738,
    NSClearLineFunctionKey      = 0xF739,
    NSClearDisplayFunctionKey   = 0xF73A,
    NSInsertLineFunctionKey     = 0xF73B,
    NSDeleteLineFunctionKey     = 0xF73C,
    NSInsertCharFunctionKey     = 0xF73D,
    NSDeleteCharFunctionKey     = 0xF73E,
    NSPrevFunctionKey           = 0xF73F,
    NSNextFunctionKey           = 0xF740,
    NSSelectFunctionKey         = 0xF741,
    NSExecuteFunctionKey        = 0xF742,
    NSUndoFunctionKey           = 0xF743,
    NSRedoFunctionKey           = 0xF744,
    NSFindFunctionKey           = 0xF745,
    NSHelpFunctionKey           = 0xF746,
    NSModeSwitchFunctionKey     = 0xF747
};

NS_ASSUME_NONNULL_END
