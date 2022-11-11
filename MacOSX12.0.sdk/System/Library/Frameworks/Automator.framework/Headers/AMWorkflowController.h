/*	
    AMWorkflowController.h
    Copyright (C) 2005-2006, 2014 Apple Inc. All rights reserved.    
    
    Public header file.
*/

#import <Foundation/Foundation.h>

#import <AppKit/NSController.h>

#import <Automator/AMAttributesForAnalyzer.h>

NS_ASSUME_NONNULL_BEGIN

API_UNAVAILABLE_BEGIN(ios)

@class AMAction;
@class AMWorkflow;
@class AMWorkflowView;

@protocol AMWorkflowControllerDelegate;

@interface AMWorkflowController : NSController
{
	@public
	AMWorkflowView *workflowView;

	@private
	AMWorkflow *_workflow;
	id _runner;
	AM_UNUSED_FOR_ANALYZER id _runnerInterface;
	AM_UNUSED_FOR_ANALYZER id _eventMonitor;
	__weak id<AMWorkflowControllerDelegate> _delegate;
	struct __AMWorkflowControllerFlags
	{
		NSUInteger shouldRunLocally : 1;
		NSUInteger isRunningLocally : 1;
		NSUInteger shouldDisplayProgressInMenuBar : 1;
		NSUInteger reserved : 29;
	} _flags;
	struct __AMWorkflowControllerDelegateRespondTo
	{
		NSUInteger workflowControllerDidAddWorkflow : 1;
		NSUInteger workflowControllerDidRemoveWorkflow : 1;
		NSUInteger workflowControllerWillRun : 1;
		NSUInteger workflowControllerWillStep : 1;
		NSUInteger workflowControllerWillStop : 1;
		NSUInteger workflowControllerWillPause : 1;
		NSUInteger workflowControllerDidRun : 1;
		NSUInteger workflowControllerDidStep : 1;
		NSUInteger workflowControllerDidStop : 1;
		NSUInteger workflowControllerDidPause : 1;
		NSUInteger workflowControllerWillRunAction : 1;
		NSUInteger workflowControllerDidRunAction : 1;
		NSUInteger workflowControllerDidError : 1;
		NSUInteger workflowControllerDidLogMessageOfTypeFromAction : 1;
		NSUInteger workflowControllerWillRunConversion : 1;
		NSUInteger workflowControllerDidRunConversion : 1;
		NSUInteger workflowControllerDidResumeWithAction : 1;
		NSUInteger reserved : 19;
	} _delegateRespondTo;

	AM_UNUSED_FOR_ANALYZER id _future;
	AM_UNUSED_FOR_ANALYZER id _future2;
	AM_UNUSED_FOR_ANALYZER id _future3;
	AM_UNUSED_FOR_ANALYZER id _future4;
}

@property (nullable, strong, nonatomic) AMWorkflow *workflow;
@property (nullable, strong, nonatomic) IBOutlet AMWorkflowView *workflowView;

// This property was previously "assign" in 10.12. It is now "weak" in 10.13 and above.
@property (nullable, weak, nonatomic) id<AMWorkflowControllerDelegate> delegate;

@property (readonly, nonatomic) BOOL canRun;
@property (readonly, nonatomic, getter=isRunning) BOOL running;
@property (readonly, nonatomic, getter=isPaused) BOOL paused;

- (IBAction)run:(id)sender;
- (IBAction)stop:(id)sender;

- (IBAction)pause:(id)sender;
- (IBAction)step:(id)sender;
- (IBAction)reset:(id)sender;

@end

@protocol AMWorkflowControllerDelegate <NSObject>

@optional
- (void)workflowControllerWillRun:(AMWorkflowController *)controller;
- (void)workflowControllerWillStop:(AMWorkflowController *)controller;
- (void)workflowControllerDidRun:(AMWorkflowController *)controller;
- (void)workflowControllerDidStop:(AMWorkflowController *)controller;
- (void)workflowController:(AMWorkflowController *)controller willRunAction:(AMAction *)action;
- (void)workflowController:(AMWorkflowController *)controller didRunAction:(AMAction *)action;
- (void)workflowController:(AMWorkflowController *)controller didError:(NSError *)error;

@end

// The AMWorkflowControllerDelegate protocol was introduced in 10.13, but but we are leaving these here for source compatibility with macOS 10.12 and below.
@interface NSObject (AMWorkflowControllerDelegate)

- (void)workflowControllerWillRun:(AMWorkflowController *)controller NS_DEPRECATED_MAC(10_4, 10_13, "Use AMWorkflowControllerDelegate protocol.");
- (void)workflowControllerWillStop:(AMWorkflowController *)controller NS_DEPRECATED_MAC(10_4, 10_13, "Use AMWorkflowControllerDelegate protocol.");
- (void)workflowControllerDidRun:(AMWorkflowController *)controller NS_DEPRECATED_MAC(10_4, 10_13, "Use AMWorkflowControllerDelegate protocol.");
- (void)workflowControllerDidStop:(AMWorkflowController *)controller NS_DEPRECATED_MAC(10_4, 10_13, "Use AMWorkflowControllerDelegate protocol.");
- (void)workflowController:(AMWorkflowController *)controller willRunAction:(AMAction *)action NS_DEPRECATED_MAC(10_4, 10_13, "Use AMWorkflowControllerDelegate protocol.");
- (void)workflowController:(AMWorkflowController *)controller didRunAction:(AMAction *)action NS_DEPRECATED_MAC(10_4, 10_13, "Use AMWorkflowControllerDelegate protocol.");
- (void)workflowController:(AMWorkflowController *)controller didError:(NSError *)error NS_DEPRECATED_MAC(10_4, 10_13, "Use AMWorkflowControllerDelegate protocol.");

@end

API_UNAVAILABLE_END

NS_ASSUME_NONNULL_END
