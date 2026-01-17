/*	
    AMWorkflowView.h
    Copyright (C) 2005-2006 Apple Computer, Inc. All rights reserved.    
    
    Public header file.
*/

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

#import <Cocoa/Cocoa.h>

@class AMWorkflow;
@class AMWorkflowController;

@interface AMWorkflowView : NSView 
{	
@private
	AMWorkflowController *_workflowController;
	NSMutableArray *_actionViewControllers;
	NSArray *_draggedActionViews;
	NSString *_messageString;
	NSBezierPath *_messagePath;
	id _variablesEditorController;
	id _showWhenRunController;
	struct __AMWorkflowViewFlags {
		BOOL ignoreSubviewFrameChanges:1;
		BOOL editingEnabled:1;
        NSUInteger reserved:30;
    } _flags;
	NSUInteger _draggingIndex;
	NSRect _selectionRect;
	
	id _future[4];
}

- (BOOL)isEditable;
- (void)setEditable:(BOOL)flag;

@end

#endif
