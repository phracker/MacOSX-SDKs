/*
        NSTrackingArea.h
        Application Kit
        Copyright (c) 2006-2007, Apple Inc.
        All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSObjCRuntime.h>
#import <Foundation/NSGeometry.h>

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

@class NSDictionary;

/* Type of tracking area.  You must specify one or more type from this list in the NSTrackingAreaOptions argument of -initWithRect:options:owner:userInfo: */
enum {
    NSTrackingMouseEnteredAndExited     = 0x01, // owner receives mouseEntered when mouse enters area, and mouseExited when mouse leaves area
    NSTrackingMouseMoved                = 0x02,	// owner receives mouseMoved while mouse is within area.  Note that mouseMoved events do not contain userInfo 
    NSTrackingCursorUpdate 		= 0x04,	// owner receives cursorUpdate when mouse enters area.  Cursor is set appropriately when mouse exits area
};

/* When tracking area is active.  You must specify one of the following in the NSTrackingAreaOptions argument of -initWithRect:options:owner:userInfo: */
enum {
    NSTrackingActiveWhenFirstResponder 	= 0x10,	// owner receives mouseEntered/Exited, mouseMoved, or cursorUpdate when view is first responder
    NSTrackingActiveInKeyWindow         = 0x20, // owner receives mouseEntered/Exited, mouseMoved, or cursorUpdate when view is in key window
    NSTrackingActiveInActiveApp 	= 0x40,	// owner receives mouseEntered/Exited, mouseMoved, or cursorUpdate when app is active
    NSTrackingActiveAlways 		= 0x80,	// owner receives mouseEntered/Exited or mouseMoved regardless of activation.  Not supported for NSTrackingCursorUpdate.
};
    
/* Behavior of tracking area.  These values are used in NSTrackingAreaOptions.  You may specify any number of the following in the NSTrackingAreaOptions argument of -initWithRect:options:owner:userInfo: */
enum {
    NSTrackingAssumeInside              = 0x100,    // If set, generate mouseExited event when mouse leaves area (same as assumeInside argument in deprecated addtrackingArea:owner:userData:assumeInside:)
    NSTrackingInVisibleRect             = 0x200,    // If set, tracking occurs in visibleRect of view and rect is ignored
    NSTrackingEnabledDuringMouseDrag    = 0x400     // If set, mouseEntered events will be generated as mouse is dragged.  If not set, mouseEntered events will be generated as mouse is moved, and on mouseUp after a drag.  mouseExited events are paired with mouseEntered events so their delivery is affected indirectly.  That is, if a mouseEntered event is generated and the mouse subsequently moves out of the trackingArea, a mouseExited event will be generated whether the mouse is being moved or dragged, independent of this flag.
}; 

typedef NSUInteger NSTrackingAreaOptions;

@interface NSTrackingArea : NSObject <NSCopying, NSCoding>
{
@private
    NSRect _rect;
    __weak id _owner;
    NSDictionary * _userInfo;
    NSTrackingAreaOptions _options;
    NSInteger _privateFlags;
    void *_reserved;
}
- (NSTrackingArea *)initWithRect:(NSRect)rect options:(NSTrackingAreaOptions)options owner:(id)owner userInfo:(NSDictionary *)userInfo;
- (NSRect)rect;
- (NSTrackingAreaOptions)options;
- (id)owner;
- (NSDictionary *)userInfo;
@end
#endif
