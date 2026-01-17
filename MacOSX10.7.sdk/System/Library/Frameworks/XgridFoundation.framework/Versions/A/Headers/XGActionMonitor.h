//
//  XGActionMonitor.h
//  GridFoundation
//
//  Copyright (c) 2004 Apple Computer, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class XGActionMonitorInternal;
@class XGResource;

/*!
	@header XGActionMonitor.h
 
	This header file describes the interface to an object which allows you
	to initiate and monitor an action performed on a concrete instance of a 
	XGResource subclass.
*/

/*!
	@enum XGResourceAction
	@discussion All of the different actions that can be performed on resources.
	@constant XGResourceActionNone No action.
	@constant XGResourceActionStop The "stop" action.
	@constant XGResourceActionRestart The "restart" action.
	@constant XGResourceActionSuspend The "suspend" action.
	@constant XGResourceActionResume The "resume" action.
	@constant XGResourceActionDelete The "delete" action.
	@constant XGResourceActionRename The "rename" action.
	@constant XGResourceActionMakeDefault The "make default" action.
	@constant XGResourceActionSubmitJob The "submit job" action.
	@constant XGResourceActionGetOutputStreams The "get output streams" action.
	@constant XGResourceActionGetOutputFiles The "get output files" action.
	@constant XGResourceActionGetSpecification The "get specification" action.
*/
typedef enum {
	XGResourceActionNone = 0,
	XGResourceActionStop,
	XGResourceActionRestart,
	XGResourceActionSuspend,
	XGResourceActionResume,
	XGResourceActionDelete,
	XGResourceActionRename,
	XGResourceActionMakeDefault,
	XGResourceActionSubmitJob,
	XGResourceActionGetOutputStreams,
	XGResourceActionGetOutputFiles,
	XGResourceActionGetSpecification
} XGResourceAction NS_DEPRECATED_MAC(10_4, 10_7);

/*!
	@enum XGActionMonitorOutcome
	@discussion The outcome of the action.
	@constant XGActionMonitorOutcomeNone The action hasn't completed yet.
	@constant XGActionMonitorOutcomeSuccess The action succeeded.
	@constant XGActionMonitorOutcomeFailure The action failed.
*/
typedef enum {
	XGActionMonitorOutcomeNone = 0,
	XGActionMonitorOutcomeSuccess,
	XGActionMonitorOutcomeFailure
} XGActionMonitorOutcome NS_DEPRECATED_MAC(10_4, 10_7);

/*!
	@const XGActionMonitorResultsOutputStreamsKey
	@discussion The key used to retrieve the output streams from the results dictionary following
	a successful outcome to a XGResourceActionGetOutputStreams action.
*/
extern NSString * const XGActionMonitorResultsOutputStreamsKey NS_DEPRECATED_MAC(10_4, 10_7);

/*!
	@const XGActionMonitorResultsOutputFilesKey
	@discussion The key used to retrieve the output files from the results dictionary following
	a successful outcome to a XGResourceActionGetOutputFiles action.
*/
extern NSString * const XGActionMonitorResultsOutputFilesKey NS_DEPRECATED_MAC(10_4, 10_7);

/*!
	@class XGActionMonitor
	@discussion This class allows you to initiate and monitor an action performed on a
	resource. You normally do not instantiate this class directly, rather you obtain an
	instance from a performXXXAction method of a resource.  Action monitors obtained from
	a resource have alreadying had the performAction method called upon them.  If you
	create your own action monitors you must call performAction to initiate the action.
    Once an action monitor's action has either succeeded or failed the outcome of the action
	monitor changes.  Following a change in the outcome the results dictionary contains the
	result of the action, if any.
*/
@interface XGActionMonitor : NSObject
{
	@private
	XGActionMonitorInternal *_internal;
}

/*!
	@method actionMonitorWithResource:action:
	@abstract Returns an instance initialized with a resource and an action.
*/
+ (id)actionMonitorWithResource:(XGResource *)resource action:(XGResourceAction)action NS_DEPRECATED_MAC(10_4, 10_7);

/*!
	@method actionMonitorWithResource:action:
	@abstract Returns an instance initialized with a resource, action, and parameters.
*/
+ (id)actionMonitorWithResource:(XGResource *)resource action:(XGResourceAction)action parameters:(NSDictionary *)parameters NS_DEPRECATED_MAC(10_4, 10_7);

/*!
	@method initWithResource:action:parameters:
	@abstract Initializes a XGActionMonitor object.
	@param resource The resource upon which the action is to be performed.  Must not be nil.
	@param action The action to perform on the resource.
	@param parameters The parameters to perform the action with.
	@result An initialized XGActionMonitor object.
*/
- (id)initWithResource:(id)resource action:(XGResourceAction)action parameters:(NSDictionary *)parameters NS_DEPRECATED_MAC(10_4, 10_7);

/*!
	@method resource
	@abstract Returns the XGResource instance the monitored action is being performed on.
	@result The XGResource instance.
*/
- (XGResource *)resource NS_DEPRECATED_MAC(10_4, 10_7);

/*!
	@method action
	@abstract Returns the XGResourceAction being monitored.
	@result The XGResourceAction.
*/
- (XGResourceAction)action NS_DEPRECATED_MAC(10_4, 10_7);

/*!
	@method parameters
	@abstract Returns the parameters of the action being monitored.
	@result The parameters dictionary.
*/
- (NSDictionary *)parameters NS_DEPRECATED_MAC(10_4, 10_7);

/*!
	@method performAction
	@abstract Initates the action being monitored.
	@discussion This method does not need to be called on XGActionMonitor instances
	that are returned by XGResource performXXXAction methods.
*/
- (void)performAction NS_DEPRECATED_MAC(10_4, 10_7);

/*!
	@method outcome
	@abstract Returns the XGActionMonitorOutcome of the action being monitored.
	@result The XGActionMonitorOutcome.
*/
- (XGActionMonitorOutcome)outcome NS_DEPRECATED_MAC(10_4, 10_7);

/*!
	@method results
	@abstract Returns the results of the action being monitored.
	@result The results dictionary.
*/
- (NSDictionary *)results NS_DEPRECATED_MAC(10_4, 10_7);

/*!
	@method error
	@abstract Returns the NSError from the results dictionary, if any.
	@result The NSError instance.
*/
- (NSError *)error NS_DEPRECATED_MAC(10_4, 10_7);

/*!
	@method actionDidSucceed
	@abstract Returns whether or not the action succeeded.
	@result The success of the action.
*/
- (BOOL)actionDidSucceed NS_DEPRECATED_MAC(10_4, 10_7);

/*!
	@method actionDidFail
	@abstract Returns whether or not the action failed.
	@result The failure of the action.
*/
- (BOOL)actionDidFail NS_DEPRECATED_MAC(10_4, 10_7);

@end
