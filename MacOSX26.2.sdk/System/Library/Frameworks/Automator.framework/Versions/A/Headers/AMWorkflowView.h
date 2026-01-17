/*	
    AMWorkflowView.h
    Copyright (C) 2005-2006, 2014 Apple Inc. All rights reserved.    
    
    Public header file.
*/

#import <AppKit/AppKit.h>
#import <Automator/AMAttributesForAnalyzer.h>

NS_ASSUME_NONNULL_BEGIN

API_UNAVAILABLE_BEGIN(ios)

@class AMWorkflow;
@class AMWorkflowController;

@interface AMWorkflowView : NSView
{
	@private
	__weak AMWorkflowController *_workflowController;
	NSMutableArray *_actionViewControllers;
	NSArray *_draggedActionViews;
	NSString *_messageString;
	AM_UNUSED_FOR_ANALYZER id _unused;
	id _variablesEditorController;
	AM_UNUSED_FOR_ANALYZER id _showWhenRunController;
	struct __AMWorkflowViewFlags
	{
		NSUInteger ignoreSubviewFrameChanges : 1;
		NSUInteger editingEnabled : 1;
		NSUInteger reserved : 30;
	} _flags;
	NSUInteger _draggingIndex;
	NSRect _selectionRect;

	id _future[4];
}

@property (getter=isEditable, atomic) BOOL editable;

// This property was labeled "strong" in 10.12, even though it was really implemented as "assign". In 10.13 and above, this is now labeled and correctly implemented as "weak".
@property (nullable, weak, nonatomic) AMWorkflowController *workflowController;

@end

API_UNAVAILABLE_END

NS_ASSUME_NONNULL_END
