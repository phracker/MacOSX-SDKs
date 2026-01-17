/*	
    AMWorkflowView.h
    Copyright (C) 2005-2006, 2014 Apple Inc. All rights reserved.    
    
    Public header file.
*/

#import <AppKit/AppKit.h>
#import <Automator/AMAttributesForAnalyzer.h>

NS_ASSUME_NONNULL_BEGIN

@class AMWorkflow;
@class AMWorkflowController;

@interface AMWorkflowView : NSView {
@private
	AMWorkflowController *_workflowController;
	NSMutableArray *_actionViewControllers;
	NSArray *_draggedActionViews;
	NSString *_messageString;
	AM_UNUSED_FOR_ANALYZER id _unused;
	id _variablesEditorController;
	AM_UNUSED_FOR_ANALYZER id _showWhenRunController;
	struct __AMWorkflowViewFlags {
		BOOL ignoreSubviewFrameChanges:1;
		BOOL editingEnabled:1;
        NSUInteger reserved:30;
    } _flags;
	NSUInteger _draggingIndex;
	NSRect _selectionRect;
	
	id _future[4];
}

@property (getter=isEditable) BOOL editable;

@property (nullable, strong) AMWorkflowController *workflowController;

@end

NS_ASSUME_NONNULL_END
