/*
	NSDragging.h
	Application Kit
	Copyright (c) 1994-2005, Apple Computer, Inc.
	All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSGeometry.h>
#import <limits.h>

@class NSImage, NSPasteboard, NSWindow, NSURL, NSArray;

typedef unsigned int NSDragOperation;

enum {
    NSDragOperationNone		= 0,
    NSDragOperationCopy		= 1,
    NSDragOperationLink		= 2,
    NSDragOperationGeneric	= 4,
    NSDragOperationPrivate	= 8,
    NSDragOperationAll_Obsolete	= 15,
    NSDragOperationMove		= 16,
    NSDragOperationDelete	= 32,
    NSDragOperationEvery	= UINT_MAX
};

// NSDragOperationAll is deprecated - please use NSDragOperationEvery
#define NSDragOperationAll NSDragOperationAll_Obsolete

/* protocol for the sender argument of the messages sent to a drag destination.  The view or
   window that registered dragging types sends these messages as dragging is
   happening to find out details about that session of dragging.
 */
@protocol NSDraggingInfo
- (NSWindow *)draggingDestinationWindow;
- (NSDragOperation)draggingSourceOperationMask;
- (NSPoint)draggingLocation;
- (NSPoint)draggedImageLocation;
- (NSImage *)draggedImage;
- (NSPasteboard *)draggingPasteboard;
- (id)draggingSource;
- (int)draggingSequenceNumber;
- (void)slideDraggedImageTo:(NSPoint)screenPoint;
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_2
- (NSArray *)namesOfPromisedFilesDroppedAtDestination:(NSURL *)dropDestination;
#endif
@end


/* Methods implemented by an object that receives dragged images.  The
   destination view or window is sent these messages during dragging if it
   responds to them.
 */
@interface NSObject(NSDraggingDestination)
- (NSDragOperation)draggingEntered:(id <NSDraggingInfo>)sender;
- (NSDragOperation)draggingUpdated:(id <NSDraggingInfo>)sender; /* if the destination responded to draggingEntered: but not to draggingUpdated: the return value from draggingEntered: is used */
- (void)draggingExited:(id <NSDraggingInfo>)sender;
- (BOOL)prepareForDragOperation:(id <NSDraggingInfo>)sender;
- (BOOL)performDragOperation:(id <NSDraggingInfo>)sender;
- (void)concludeDragOperation:(id <NSDraggingInfo>)sender;
// draggingEnded: is not yet implemented
- (void)draggingEnded:(id <NSDraggingInfo>)sender;
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
/* the receiver of -wantsPeriodicDraggingUpdates should return NO if it does not require periodic -draggingUpdated messages (eg. not autoscrolling or otherwise dependent on draggingUpdated: sent while mouse is stationary) */
- (BOOL)wantsPeriodicDraggingUpdates;
#endif
@end


/* Methods implemented by an object that initiates a drag session.  The
   source app is sent these messages during dragging.  The first must be
   implemented, the others are sent if the source responds to them.
 */
@interface NSObject(NSDraggingSource)
- (NSDragOperation)draggingSourceOperationMaskForLocal:(BOOL)flag;
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_2
- (NSArray *)namesOfPromisedFilesDroppedAtDestination:(NSURL *)dropDestination;
#endif
- (void)draggedImage:(NSImage *)image beganAt:(NSPoint)screenPoint;
- (void)draggedImage:(NSImage *)image endedAt:(NSPoint)screenPoint operation:(NSDragOperation)operation;
- (void)draggedImage:(NSImage *)image movedTo:(NSPoint)screenPoint;
- (BOOL)ignoreModifierKeysWhileDragging;

// -draggedImage:endedAt:deposited: is deprecated.  Sources should instead implement -draggedImage:endedAt:operation:
- (void)draggedImage:(NSImage *)image endedAt:(NSPoint)screenPoint deposited:(BOOL)flag;
@end
