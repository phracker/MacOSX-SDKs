// ================================================================================
//	**** PUBLIC HEADER ****
//
//	InterfaceBuilder.framework - IBApplicationAdditions.h
//	Copyright (c) 1995-2000 Apple Computer, Inc.
//	All rights reserved.
//
// ================================================================================

#import <InterfaceBuilder/IBDocuments.h>
#import <InterfaceBuilder/IBEditors.h>

@protocol IB

/* Find a document given an object */

- (id <IBDocuments>) documentForObject:(id)object;

/* Returns the active document (i.e., the document containing the current
 * selection), or nil if there is no active document. */

- (id <IBDocuments>)activeDocument;

/* Returns the object which owns the current selection, or nil if there
 * is no current selection. */

- (id <IBEditors>)selectionOwner;

/* Convenience method: returns the currently selected object, or nil if there
 * is no selection or if there is more than one selected object. */

- (id)selectedObject;

/* Returns YES if we are testing the interface; NO otherwise. */

- (BOOL)isTestingInterface;

@end

/* The notification object is the document of the interface we're testing. */
IB_EXTERN NSString * const IBWillBeginTestingInterfaceNotification;
IB_EXTERN NSString * const IBDidBeginTestingInterfaceNotification;
IB_EXTERN NSString * const IBWillEndTestingInterfaceNotification;
IB_EXTERN NSString * const IBDidEndTestingInterfaceNotification;
