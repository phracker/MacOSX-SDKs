//
//  XGJob.h
//  GridFoundation
//
//  Copyright (c) 2004 Apple Computer, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <XgridFoundation/XGResource.h>

@class XGJobInternal;

/*!
	@header XGJob.h
 
	This header file describes the interface of an object which represents a remote
	Xgrid job. Instances of the XGJob class are obtained from a XGGrid instance.
*/


extern NSString * const XGJobSpecificationNameKey NS_DEPRECATED_MAC(10_4, 10_7);
extern NSString * const XGJobSpecificationTypeKey NS_DEPRECATED_MAC(10_4, 10_7);
extern NSString * const XGJobSpecificationSubmissionIdentifierKey NS_DEPRECATED_MAC(10_4, 10_7);
extern NSString * const XGJobSpecificationSchedulerParametersKey NS_DEPRECATED_MAC(10_4, 10_7);
extern NSString * const XGJobSpecificationGridIdentifierKey NS_DEPRECATED_MAC(10_4, 10_7);
extern NSString * const XGJobSpecificationDependsOnJobsKey NS_DEPRECATED_MAC(10_4, 10_7);
extern NSString * const XGJobSpecificationInputFilesKey NS_DEPRECATED_MAC(10_4, 10_7);
extern NSString * const XGJobSpecificationFileDataKey NS_DEPRECATED_MAC(10_4, 10_7);
extern NSString * const XGJobSpecificationIsExecutableKey NS_DEPRECATED_MAC(10_4, 10_7);
extern NSString * const XGJobSpecificationTaskPrototypesKey NS_DEPRECATED_MAC(10_4, 10_7);
extern NSString * const XGJobSpecificationInputFileMapKey NS_DEPRECATED_MAC(10_4, 10_7);
extern NSString * const XGJobSpecificationCommandKey NS_DEPRECATED_MAC(10_4, 10_7);
extern NSString * const XGJobSpecificationArgumentsKey NS_DEPRECATED_MAC(10_4, 10_7);
extern NSString * const XGJobSpecificationArgumentTypeKey NS_DEPRECATED_MAC(10_4, 10_7);
extern NSString * const XGJobSpecificationPathIdentifierKey NS_DEPRECATED_MAC(10_4, 10_7);
extern NSString * const XGJobSpecificationEnvironmentKey NS_DEPRECATED_MAC(10_4, 10_7);
extern NSString * const XGJobSpecificationInputStreamKey NS_DEPRECATED_MAC(10_4, 10_7);
extern NSString * const XGJobSpecificationTaskSpecificationsKey NS_DEPRECATED_MAC(10_4, 10_7);
extern NSString * const XGJobSpecificationTaskPrototypeIdentifierKey NS_DEPRECATED_MAC(10_4, 10_7);
extern NSString * const XGJobSpecificationDependsOnTasksKey NS_DEPRECATED_MAC(10_4, 10_7);
extern NSString * const XGJobSpecificationNotificationEmailKey NS_DEPRECATED_MAC(10_4, 10_7);
extern NSString * const XGJobSpecificationApplicationIdentifierKey NS_DEPRECATED_MAC(10_4, 10_7);
extern NSString * const XGJobSpecificationSchedulerHintsKey NS_DEPRECATED_MAC(10_4, 10_7);

extern NSString * const XGJobSpecificationARTSpecificationsKey NS_DEPRECATED_MAC(10_4, 10_7);
extern NSString * const XGJobSpecificationARTConditionsKey NS_DEPRECATED_MAC(10_4, 10_7);
extern NSString * const XGJobSpecificationARTDataKey NS_DEPRECATED_MAC(10_4, 10_7);
extern NSString * const XGJobSpecificationARTMinimumKey NS_DEPRECATED_MAC(10_4, 10_7);
extern NSString * const XGJobSpecificationARTMaximumKey NS_DEPRECATED_MAC(10_4, 10_7);
extern NSString * const XGJobSpecificationARTEqualKey NS_DEPRECATED_MAC(10_4, 10_7);

extern NSString * const XGJobSpecificationTypeTaskListValue NS_DEPRECATED_MAC(10_4, 10_7);

/*!
	@class XGJob
	@abstract This class provides a local interface to remote Xgrid jobs.
*/
@interface XGJob : XGResource
{
	XGJobInternal *_internal1;
}

/*!
    @method name
    @abstract Returns the name associated with the job.
    @result A string.
*/
- (NSString *)name NS_DEPRECATED_MAC(10_4, 10_7);

/*!
	@method applicationIdentifier
	@abstract Returns the applicationIdentifier of the job.
	@result The applicationIdentifier of the job.
	@discussion The applicationIdentifier is a identifier string set on the
	job by the application that submitted the job. The appliationIdentifier
	is not guaranteed to be unique.
*/
- (NSString *)applicationIdentifier NS_DEPRECATED_MAC(10_4, 10_7);

/*!
	@method applicationInfo
	@abstract Returns the applicationInfo of the job.
	@result The applicationInfo of the job.
	@discussion The applicationInfo is a dictionary set on the job by the
	application that submitted the job.
*/
- (NSDictionary *)applicationInfo NS_DEPRECATED_MAC(10_4, 10_7);

/*!
	@method activeCPUPower
	@abstract Returns the active CPU power of the job.
	@result The active CPU power of the job.
	@discussion The active CPU power of a job is the sum of the CPU power of each
	of the active processors running one of the job's tasks.
*/
- (float)activeCPUPower NS_DEPRECATED_MAC(10_4, 10_7);

/*!
	@method percentDone
	@abstract Returns the percentage of the job that has completed.
	@result The percent done, from 0.0 to 100.0.
*/
- (float)percentDone NS_DEPRECATED_MAC(10_4, 10_7);

/*!
	@method taskCount
	@abstract Returns the number of tasks that make up the job.
	@result The number of tasks.
*/
- (NSInteger)taskCount NS_DEPRECATED_MAC(10_4, 10_7);

/*!
	@method completedTaskCount
	@abstract Returns the number of tasks that have completed.
	@result The number of completed tasks.
*/
- (NSInteger)completedTaskCount NS_DEPRECATED_MAC(10_4, 10_7);

/*!
	@method dateSubmitted
	@abstract Returns the date the job was submitted.
	@result The submission date.
*/
- (NSDate *)dateSubmitted NS_DEPRECATED_MAC(10_4, 10_7);

/*!
	@method dateStarted
	@abstract Returns the date the job was started.
	@result The start date.
*/
- (NSDate *)dateStarted NS_DEPRECATED_MAC(10_4, 10_7);

/*!
	@method dateStopped
	@abstract Returns the date the job was stopped.
	@result The stop date.
*/
- (NSDate *)dateStopped NS_DEPRECATED_MAC(10_4, 10_7);

/*!
	@method performStopAction
	@abstract Attempts to stop the job represented by the receiver.
	@result An XGActionMonitor instance for tracking the action progress.
*/
- (XGActionMonitor *)performStopAction NS_DEPRECATED_MAC(10_4, 10_7);

/*!
	@method performRestartAction
	@abstract Attempts to restart the job represented by the receiver.
	@result An XGActionMonitor instance for tracking the action progress.
*/
- (XGActionMonitor *)performRestartAction NS_DEPRECATED_MAC(10_4, 10_7);

/*!
	@method performSuspendAction
	@abstract Attempts to suspend the job represented by the receiver.
	@result An XGActionMonitor instance for tracking the action progress.
*/
- (XGActionMonitor *)performSuspendAction NS_DEPRECATED_MAC(10_4, 10_7);

/*!
	@method performResumeAction
	@abstract Attempts to resume the job represented by the receiver.
	@result An XGActionMonitor instance for tracking the action progress.
*/
- (XGActionMonitor *)performResumeAction NS_DEPRECATED_MAC(10_4, 10_7);

/*!
	@method performGetOutputStreamsAction
	@abstract Attempts to retrieve a list of output streams for the job
	represented by the receiver.
	@result An XGActionMonitor instance for tracking the action progress.
*/
- (XGActionMonitor *)performGetOutputStreamsAction NS_DEPRECATED_MAC(10_4, 10_7);

/*!
	@method performGetOutputFilesAction
	@abstract Attempts to retrieve a list of output files for the job
	represented by the receiver.
	@result An XGActionMonitor instance for tracking the action progress.
*/
- (XGActionMonitor *)performGetOutputFilesAction NS_DEPRECATED_MAC(10_4, 10_7);

/*!
	@method performGetSpecificationAction
	@abstract Attempts to retrieve the specification used to submit the job
	represented by the reciever.
	@result An XGActionMonitor instance for tracking the action progress.
*/
- (XGActionMonitor *)performGetSpecificationAction NS_DEPRECATED_MAC(10_4, 10_7);

/*!
	@method performDeleteAction
	@abstract Attempts to delete the job represented by the receiver.
	@result An XGActionMonitor instance for tracking the action progress.
*/
- (XGActionMonitor *)performDeleteAction NS_DEPRECATED_MAC(10_4, 10_7);

@end
