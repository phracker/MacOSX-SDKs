/*
    NSEvent.h
    Application Kit
    Copyright (c) 1994-2007, Apple Inc.
    All rights reserved.
*/

#import <ApplicationServices/ApplicationServices.h>
#import <Foundation/NSObject.h>
#import <Foundation/NSDate.h>
#import <Foundation/NSGeometry.h>
#import <IOKit/hidsystem/IOLLEvent.h>
#import <limits.h>

@class NSGraphicsContext, NSWindow, NSTrackingArea;

enum {        /* various types of events */
    NSLeftMouseDown             = 1,            
    NSLeftMouseUp               = 2,
    NSRightMouseDown            = 3,
    NSRightMouseUp              = 4,
    NSMouseMoved                = 5,
    NSLeftMouseDragged          = 6,
    NSRightMouseDragged         = 7,
    NSMouseEntered              = 8,
    NSMouseExited               = 9,
    NSKeyDown                   = 10,
    NSKeyUp                     = 11,
    NSFlagsChanged              = 12,
    NSAppKitDefined             = 13,
    NSSystemDefined             = 14,
    NSApplicationDefined        = 15,
    NSPeriodic                  = 16,
    NSCursorUpdate              = 17,
    NSScrollWheel               = 22,
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
    NSTabletPoint               = 23,
    NSTabletProximity           = 24,
#endif
    NSOtherMouseDown            = 25,
    NSOtherMouseUp              = 26,
    NSOtherMouseDragged         = 27
};
typedef NSUInteger NSEventType;

enum {                    /* masks for the types of events */
    NSLeftMouseDownMask         = 1 << NSLeftMouseDown,
    NSLeftMouseUpMask           = 1 << NSLeftMouseUp,
    NSRightMouseDownMask        = 1 << NSRightMouseDown,
    NSRightMouseUpMask          = 1 << NSRightMouseUp,
    NSMouseMovedMask            = 1 << NSMouseMoved,
    NSLeftMouseDraggedMask      = 1 << NSLeftMouseDragged,
    NSRightMouseDraggedMask     = 1 << NSRightMouseDragged,
    NSMouseEnteredMask          = 1 << NSMouseEntered,
    NSMouseExitedMask           = 1 << NSMouseExited,
    NSKeyDownMask               = 1 << NSKeyDown,
    NSKeyUpMask                 = 1 << NSKeyUp,
    NSFlagsChangedMask          = 1 << NSFlagsChanged,
    NSAppKitDefinedMask         = 1 << NSAppKitDefined,
    NSSystemDefinedMask         = 1 << NSSystemDefined,
    NSApplicationDefinedMask    = 1 << NSApplicationDefined,
    NSPeriodicMask              = 1 << NSPeriodic,
    NSCursorUpdateMask          = 1 << NSCursorUpdate,
    NSScrollWheelMask           = 1 << NSScrollWheel,
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
    NSTabletPointMask           = 1 << NSTabletPoint,
    NSTabletProximityMask       = 1 << NSTabletProximity,
#endif
    NSOtherMouseDownMask        = 1 << NSOtherMouseDown,
    NSOtherMouseUpMask          = 1 << NSOtherMouseUp,
    NSOtherMouseDraggedMask     = 1 << NSOtherMouseDragged,
    NSAnyEventMask              = NSUIntegerMax
};

NS_INLINE NSUInteger NSEventMaskFromType(NSEventType type) { return (1 << type); }

/* Device-independent bits found in event modifier flags */
enum {
    NSAlphaShiftKeyMask         = 1 << 16,
    NSShiftKeyMask              = 1 << 17,
    NSControlKeyMask            = 1 << 18,
    NSAlternateKeyMask          = 1 << 19,
    NSCommandKeyMask            = 1 << 20,
    NSNumericPadKeyMask         = 1 << 21,
    NSHelpKeyMask               = 1 << 22,
    NSFunctionKeyMask           = 1 << 23,
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
    NSDeviceIndependentModifierFlagsMask    = 0xffff0000UL
#endif
};

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
/* pointer types for NSTabletProximity events or mouse events with subtype NSTabletProximityEventSubtype*/
enum {        
    NSUnknownPointingDevice     = NX_TABLET_POINTER_UNKNOWN,
    NSPenPointingDevice         = NX_TABLET_POINTER_PEN,
    NSCursorPointingDevice      = NX_TABLET_POINTER_CURSOR,
    NSEraserPointingDevice      = NX_TABLET_POINTER_ERASER
};
typedef NSUInteger NSPointingDeviceType;

/* button masks for NSTabletPoint events or mouse events with subtype NSTabletPointEventSubtype */
enum {
    NSPenTipMask                = NX_TABLET_BUTTON_PENTIPMASK,
    NSPenLowerSideMask          = NX_TABLET_BUTTON_PENLOWERSIDEMASK,
    NSPenUpperSideMask          = NX_TABLET_BUTTON_PENUPPERSIDEMASK
};
#endif

@interface NSEvent : NSObject <NSCopying, NSCoding> {
    /*All instance variables are private*/
    NSEventType _type;
    NSPoint _location;
    unsigned int _modifierFlags;
    NSInteger _WSTimestamp;
    NSTimeInterval _timestamp;
    NSInteger _windowNumber;
    NSWindow *_window;
    NSGraphicsContext* _context;
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
            NSString *keys;
            NSString *unmodKeys;
            unsigned short keyCode;
            BOOL isARepeat;
#if __LP64__
            int reserved[6];
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
    } _data;
    void *_eventRef;
#if __LP64__
    void *reserved1;
    void *reserved2;
#endif
}


/* these messages are valid for all events */
- (NSEventType)type;
- (NSUInteger)modifierFlags;
- (NSTimeInterval)timestamp;
- (NSWindow *)window;
- (NSInteger)windowNumber;
- (NSGraphicsContext*)context;

/* these messages are valid for all mouse down/up/drag events */
- (NSInteger)clickCount;
- (NSInteger)buttonNumber;    // for NSOtherMouse events, but will return valid constants for NSLeftMouse and NSRightMouse
/* these messages are valid for all mouse down/up/drag and enter/exit events */
- (NSInteger)eventNumber;

/* These messages are valid for all mouse down/up/drag events */
/* These messages are also valid for NSTabletPoint events on 10.4 or later */
- (float)pressure;
- (NSPoint)locationInWindow;

/* these messages are valid for scroll wheel events and mouse move/drag events */
- (CGFloat)deltaX;    
- (CGFloat)deltaY;    
- (CGFloat)deltaZ;    // 0 for most scroll wheel and mouse events

/* these messages are valid for keyup and keydown events */
- (NSString *)characters;
- (NSString *)charactersIgnoringModifiers;
  /* the chars that would have been generated, regardless of modifier keys (except shift) */
- (BOOL)isARepeat;
/* this message is valid for keyup, keydown and flagschanged events */
- (unsigned short)keyCode;        /* device-independent key number */

/* these messages are valid for enter and exit events */
- (NSInteger)trackingNumber;
- (void *)userData;
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5
/* -trackingArea returns the NSTrackingArea that generated this event.  It is possible for there to be no trackingArea associated with the event in some cases where the event corresponds to a trackingRect installed with -[NSView addTrackingRect:owner:userData:assumeInside:], in which case nil is returned. */
- (NSTrackingArea *)trackingArea; 
#endif

/* this message is valid for kit, system, and app-defined events */
/* this message is also valid for mouse events on 10.4 or later */
- (short)subtype;

/* these messages are valid for kit, system, and app-defined events */
- (NSInteger)data1;
- (NSInteger)data2;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

/* -eventRef and +eventWithEventRef:  are valid for all events */
/* -eventRef returns an EventRef corresponding to the NSEvent.  The EventRef is retained by the NSEvent, so will be valid as long as the NSEvent is valid, and will be released when the NSEvent is freed.  You can use RetainEvent to extend the lifetime of the EventRef, with a corresponding ReleaseEvent when you are done with it.  If there is no EventRef corresponding to the NSEvent, -eventRef will return NULL.
*/
- (const void * /* EventRef */)eventRef;
/* +eventWithEventRef: returns an autoreleased NSEvent corresponding to the EventRef.  The EventRef is retained by the NSEvent and will be released when the NSEvent is freed.  If there is no NSEvent corresponding to the EventRef, +eventWithEventRef will return nil.
*/
+ (NSEvent *)eventWithEventRef:(const void * /* EventRef */)eventRef;

/* -CGEvent returns an autoreleased CGEventRef corresponding to the NSEvent.  If there is no CGEventRef corresponding to the NSEvent, -CGEvent will return NULL.
*/
- (CGEventRef)CGEvent;

/* +eventWithCGEvent: returns an autoreleased NSEvent corresponding to the CGEventRef.  The CGEventRef is retained by the NSEvent and will be released when the NSEvent is freed.  If there is no NSEvent corresponding to the CGEventRef, +eventWithEventRef will return nil.
*/
+ (NSEvent *)eventWithCGEvent:(CGEventRef)cgEvent;

/* Enable or disable coalescing of mouse movement events, including mouse moved, mouse dragged, and tablet events.  Coalescing is enabled by default.
*/
+ (void)setMouseCoalescingEnabled:(BOOL)flag;
+ (BOOL)isMouseCoalescingEnabled;

#endif

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
/* this message is valid for mouse events with subtype NSTabletPointEventSubtype or NSTabletProximityEventSubtype, and for NSTabletPoint and NSTabletProximity events */
- (NSUInteger)deviceID;

/* these messages are valid for mouse events with subtype NSTabletPointEventSubtype, and for NSTabletPoint events */
/* absolute x coordinate in tablet space at full tablet resolution */
- (NSInteger)absoluteX; 
/* absolute y coordinate in tablet space at full tablet resolution */
- (NSInteger)absoluteY;               
/* absolute z coordinate in tablet space at full tablet resolution */
- (NSInteger)absoluteZ;     
/* mask indicating which buttons are pressed.*/
- (NSUInteger)buttonMask;  
/* range is -1 to 1 for both axes */
- (NSPoint)tilt;     
/* device rotation in degrees */
- (float)rotation;       
/* tangential pressure on the device; range is -1 to 1 */
- (float)tangentialPressure;  
/* NSArray of 3 vendor defined shorts */
- (id)vendorDefined;    

/* these messages are valid for mouse events with subtype NSTabletProximityEventSubtype, and  for NSTabletProximity events */
/* vendor defined, typically USB vendor ID */
- (NSUInteger)vendorID;
/* vendor defined tablet ID */
- (NSUInteger)tabletID;
/* index of the device on the tablet.  Usually 0, except for tablets that support multiple concurrent devices */
- (NSUInteger)pointingDeviceID;
/* system assigned unique tablet ID */
- (NSUInteger)systemTabletID;
/* vendor defined pointing device type */
- (NSUInteger)vendorPointingDeviceType; 
/* vendor defined serial number of pointing device */
- (NSUInteger)pointingDeviceSerialNumber; 
/* vendor defined unique ID */
- (unsigned long long)uniqueID;    
/* mask representing capabilities of device */
- (NSUInteger)capabilityMask;    
/* mask representing capabilities of device */
- (NSPointingDeviceType)pointingDeviceType;
/* YES - entering; NO - leaving */
- (BOOL)isEnteringProximity;    

#endif

/* used for initial delay and periodic behavior in tracking loops */
+ (void)startPeriodicEventsAfterDelay:(NSTimeInterval)delay withPeriod:(NSTimeInterval)period;
+ (void)stopPeriodicEvents;

/* apps will rarely create these objects */
+ (NSEvent *)mouseEventWithType:(NSEventType)type location:(NSPoint)location modifierFlags:(NSUInteger)flags timestamp:(NSTimeInterval)time windowNumber:(NSInteger)wNum context:(NSGraphicsContext*)context eventNumber:(NSInteger)eNum clickCount:(NSInteger)cNum pressure:(float)pressure;
+ (NSEvent *)keyEventWithType:(NSEventType)type location:(NSPoint)location modifierFlags:(NSUInteger)flags timestamp:(NSTimeInterval)time windowNumber:(NSInteger)wNum context:(NSGraphicsContext*)context characters:(NSString *)keys charactersIgnoringModifiers:(NSString *)ukeys isARepeat:(BOOL)flag keyCode:(unsigned short)code;
+ (NSEvent *)enterExitEventWithType:(NSEventType)type location:(NSPoint)location modifierFlags:(NSUInteger)flags timestamp:(NSTimeInterval)time windowNumber:(NSInteger)wNum context:(NSGraphicsContext*)context eventNumber:(NSInteger)eNum trackingNumber:(NSInteger)tNum userData:(void *)data;
+ (NSEvent *)otherEventWithType:(NSEventType)type location:(NSPoint)location modifierFlags:(NSUInteger)flags timestamp:(NSTimeInterval)time windowNumber:(NSInteger)wNum context:(NSGraphicsContext*)context subtype:(short)subtype data1:(NSInteger)d1 data2:(NSInteger)d2;

// global mouse coordinates
+ (NSPoint)mouseLocation;

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


enum {        /* event subtypes for NSAppKitDefined events */
    NSWindowExposedEventType            = 0,
    NSApplicationActivatedEventType     = 1,
    NSApplicationDeactivatedEventType   = 2,
    NSWindowMovedEventType              = 4,
    NSScreenChangedEventType            = 8,
    NSAWTEventType                      = 16
};

enum {        /* event subtypes for NSSystemDefined events */
    NSPowerOffEventType             = 1
};


#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
enum {        /* event subtypes for mouse events */
    NSMouseEventSubtype             = NX_SUBTYPE_DEFAULT,
    NSTabletPointEventSubtype       = NX_SUBTYPE_TABLET_POINT,
    NSTabletProximityEventSubtype   = NX_SUBTYPE_TABLET_PROXIMITY
};
#endif

