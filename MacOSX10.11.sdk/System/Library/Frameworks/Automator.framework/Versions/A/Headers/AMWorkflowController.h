/*	
    AMWorkflowController.h
    Copyright (C) 2005-2006, 2014 Apple Inc. All rights reserved.    
    
    Public header file.
*/

#import <Foundation/Foundation.h>
#import <Automator/AMAttributesForAnalyzer.h>

NS_ASSUME_NONNULL_BEGIN

@class AMAction;
@class AMWorkflow;
@class AMWorkflowView;

@interface AMWorkflowController : NSController 
{
@public
	IBOutlet AMWorkflowView *workflowView;
	
@private
	AMWorkflow			*_workflow;
	id					_runner;
	id					_runnerInterface;
	AM_UNUSED_FOR_ANALYZER id	_eventMonitor;
	id					_delegate;
	struct __AMWorkflowControllerFlags {
		NSUInteger shouldRunLocally:1;
		NSUInteger isRunningLocally:1;
		NSUInteger shouldDisplayProgressInMenuBar:1;
        NSUInteger reserved:29;
    } _flags;
	struct __AMWorkflowControllerDelegateRespondTo {
		NSUInteger workflowControllerDidAddWorkflow:1;
		NSUInteger workflowControllerDidRemoveWorkflow:1;
        NSUInteger workflowControllerWillRun:1;
		NSUInteger workflowControllerWillStep:1;
		NSUInteger workflowControllerWillStop:1;
		NSUInteger workflowControllerWillPause:1;
        NSUInteger workflowControllerDidRun:1;
		NSUInteger workflowControllerDidStep:1;
		NSUInteger workflowControllerDidStop:1;
		NSUInteger workflowControllerDidPause:1;
        NSUInteger workflowControllerWillRunAction:1;
        NSUInteger workflowControllerDidRunAction:1;
		NSUInteger workflowControllerDidError:1;
		NSUInteger workflowControllerDidLogMessageOfTypeFromAction:1;
		NSUInteger workflowControllerWillRunConversion:1;
		NSUInteger workflowControllerDidRunConversion:1;
		NSUInteger workflowControllerDidResumeWithAction:1;
        NSUInteger reserved:19;
    } _delegateRespondTo;
	
	id _future;
	AM_UNUSED_FOR_ANALYZER id _future2;
	AM_UNUSED_FOR_ANALYZER id _future3;
	AM_UNUSED_FOR_ANALYZER id _future4;
}

@property (nullable, strong) AMWorkflow *workflow;
@property (nullable, strong) AMWorkflowView *workflowView;
@property (nullable, assign) id delegate;

@property (readonly) BOOL canRun;
@property (getter=isRunning, readonly) BOOL running;

- (IBAction)run:(id)sender;
- (IBAction)stop:(id)sender;

@property (getter=isPaused, readonly) BOOL paused;
- (IBAction)pause:(id)sender;
- (IBAction)step:(id)sender;
- (IBAction)reset:(id)sender;

@end

//================================================================================
//	AMWorkflowControllerDelegate protocol
//================================================================================

@interface NSObject(AMWorkflowControllerDelegate)
- (void)workflowControllerWillRun:(AMWorkflowController *)controller;
- (void)workflowControllerWillStop:(AMWorkflowController *)controller;
- (void)workflowControllerDidRun:(AMWorkflowController *)controller;
- (void)workflowControllerDidStop:(AMWorkflowController *)controller;
- (void)workflowController:(AMWorkflowController *)controller willRunAction:(AMAction *)action;
- (void)workflowController:(AMWorkflowController *)controller didRunAction:(AMAction *)action;
- (void)workflowController:(AMWorkflowController *)controller didError:(NSError *)error;
@end

NS_ASSUME_NONNULL_END
