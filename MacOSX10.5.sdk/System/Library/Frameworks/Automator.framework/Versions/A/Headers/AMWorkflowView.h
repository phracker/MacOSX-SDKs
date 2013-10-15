/*	
    AMWorkflowView.h
    Copyright (C) 2005-2006 Apple Computer, Inc. All rights reserved.    
    
    Public header file.
*/

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
	NSInteger _draggingIndex;
	NSRect _selectionRect;
	
	id _future;
	id _future2;
	id _future3;
	id _future4;
}

- (BOOL)isEditable;
- (void)setEditable:(BOOL)flag;

@end
