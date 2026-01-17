// ================================================================================
//	**** PUBLIC HEADER ****
//
//	InterfaceBuilder.framework - IBViewResourceDragging.h
//	Copyright (c) 1995-2001 Apple Computer, Inc.
//	All rights reserved.
//
// ================================================================================

#import <InterfaceBuilder/IBSystem.h>
#import <AppKit/NSView.h>

@class NSPasteboard;

/*
 * `object' is typically either a view, cell or a formatter.
 *
 * All of the coordinates passed to these delegate methods
 * are in view coordinates.
 *
 * To use the resource dragging code delegate make an object that will hang around
 * forever (ie not created and destroyed each time). Make sure this object implements
 * the IBViewResourceDraggingDelegates protocol.
 * then register this object with +[NSView registerViewResourceDraggingDelegate:] method
 * below. (IBViewResourceDraggingDelegates informal protocol)
 *
 */
@protocol IBViewResourceDraggingDelegates
- (NSArray *)viewResourcePasteboardTypes;
- (BOOL)acceptsViewResourceFromPasteboard:(NSPasteboard *)pasteboard forObject:(id)object atPoint:(NSPoint)point;
- (void)depositViewResourceFromPasteboard:(NSPasteboard *)pasteboard onObject:(id)object atPoint:(NSPoint)point;
- (BOOL)shouldDrawConnectionFrame;
@end

@interface NSView (IBViewResourceDraggingDelegates)
+ (void)registerViewResourceDraggingDelegate:(id <IBViewResourceDraggingDelegates>)delegate;
+ (void)unregisterViewResourceDraggingDelegate:(id <IBViewResourceDraggingDelegates>)delegate;
+ (NSArray *)registeredViewResourceDraggingDelegates;
+ (NSArray *)acceptedViewResourcePasteboardTypes;
@end

/* Notifications. */
IB_EXTERN NSString *const IBViewResourceDraggingDelegatesRegistryDidChangeNotification;
