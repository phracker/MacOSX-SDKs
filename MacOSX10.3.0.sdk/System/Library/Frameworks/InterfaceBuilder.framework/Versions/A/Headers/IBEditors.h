// ================================================================================
//	**** PUBLIC HEADER ****
//
//	InterfaceBuilder.framework - IBEditors.h
//	Copyright (c) 2000 Apple Computer, Inc.
//	All rights reserved.
//
// ================================================================================

#import <InterfaceBuilder/IBSystem.h>
#import <AppKit/AppKit.h>

@class NSPasteboard;
@class NSWindow;

@protocol IBSelectionOwners <NSObject>
- (unsigned int)selectionCount;
- (NSArray *)selection;
@end

// --------------------------------------------------------------------------------
//	protocol IBEditors <IBSelectionOwners>
// --------------------------------------------------------------------------------

@protocol IBEditors <IBSelectionOwners>

/* Editing objects. */
- (id)initWithObject:(id)object inDocument:(id /*<IBDocuments>*/)document;
- (void)closeEditor;

/* Identifying objects. */
- (id)editedObject;
- (id /*<IBDocuments>*/)document;
- (NSWindow *)window;

/* Displaying objects. */
- (void)resetObject:(id)object;

/* Managing the selection. */
- (BOOL)wantsSelection;
- (void)selectObjects:(NSArray *)objects;
- (void)makeSelectionVisible:(BOOL)showIt;

/* Copying and pasting objects. */
- (BOOL)shouldCopySelection;
- (void)copySelection;
- (BOOL)shouldDeleteSelection;
- (void)deleteSelection;
- (BOOL)shouldPasteInSelection;
- (void)pasteInSelection;
- (BOOL)acceptsTypeFromPasteboard:(NSPasteboard *)pasteboard;

/* Opening and closing editors. */
- (id <IBEditors>)openSubeditorForObject:(id)object;
- (void)closeSubeditors;

/* Activating the editor. */
- (void)orderFront;
- (BOOL)activate;
- (void)validateEditing;

@end

IB_EXTERN NSString * const IBSelectionChangedNotification;    	// Object is Document
IB_EXTERN NSString * const IBAttributesChangedNotification;	// Object is object
