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


extern NSString * const XGJobSpecificationNameKey;
extern NSString * const XGJobSpecificationTypeKey;
extern NSString * const XGJobSpecificationSubmissionIdentifierKey;
extern NSString * const XGJobSpecificationSchedulerParametersKey;
extern NSString * const XGJobSpecificationGridIdentifierKey;
extern NSString * const XGJobSpecificationDependsOnJobsKey;
extern NSString * const XGJobSpecificationInputFilesKey;
extern NSString * const XGJobSpecificationFileDataKey;
extern NSString * const XGJobSpecificationIsExecutableKey;
extern NSString * const XGJobSpecificationTaskPrototypesKey;
extern NSString * const XGJobSpecificationInputFileMapKey;
extern NSString * const XGJobSpecificationCommandKey;
extern NSString * const XGJobSpecificationArgumentsKey;
extern NSString * const XGJobSpecificationArgumentTypeKey;
extern NSString * const XGJobSpecificationPathIdentifierKey;
extern NSString * const XGJobSpecificationEnvironmentKey;
extern NSString * const XGJobSpecificationInputStreamKey;
extern NSString * const XGJobSpecificationTaskSpecificationsKey;
extern NSString * const XGJobSpecificationTaskPrototypeIdentifierKey;
extern NSString * const XGJobSpecificationDependsOnTasksKey;
extern NSString * const XGJobSpecificationNotificationEmailKey;
extern NSString * const XGJobSpecificationApplicationIdentifierKey;

extern NSString * const XGJobSpecificationTypeTaskListValue;

/*!
	@class XGJob
	@abstract This class provides a local interface to remote Xgrid jobs.
*/
@interface XGJob : XGResource
{
	XGJobInternal *_internal1;
}

/*!
	@method applicationIdentifier
	@abstract Returns the applicationIdentifier of the job.
	@result The applicationIdentifier of the job.
	@discussion The applicationIdentifier is a identifier string set on the
	job by the application that submitted the job. The appliationIdentifier
	is not guaranteed to be unique.
*/
- (NSString *)applicationIdentifier;

/*!
	@method applicationInfo
	@abstract Returns the applicationInfo of the job.
	@result The applicationInfo of the job.
	@discussion The applicationInfo is a dictionary set on the job by the
	application that submitted the job.
*/
- (NSDictionary *)applicationInfo;

/*!
	@method activeCPUPower
	@abstract Returns the active CPU power of the job.
	@result The active CPU power of the job.
	@discussion The active CPU power of a job is the sum of the CPU power of each
	of the active processors running one of the job's tasks.
*/
- (float)activeCPUPower;

/*!
	@method percentDone
	@abstract Returns the percentage of the job that has completed.
	@result The percent done, from 0.0 to 100.0.
*/
- (float)percentDone;

/*!
	@method taskCount
	@abstract Returns the number of tasks that make up the job.
	@result The number of tasks.
*/
- (int)taskCount;

/*!
	@method completedTaskCount
	@abstract Returns the number of tasks that have completed.
	@result The number of completed tasks.
*/
- (int)completedTaskCount;

/*!
	@method dateSubmitted
	@abstract Returns the date the job was submitted.
	@result The submission date.
*/
- (NSDate *)dateSubmitted;

/*!
	@method dateStarted
	@abstract Returns the date the job was started.
	@result The start date.
*/
- (NSDate *)dateStarted;

/*!
	@method dateStopped
	@abstract Returns the date the job was stopped.
	@result The stop date.
*/
- (NSDate *)dateStopped;

/*!
	@method performStopAction
	@abstract Attempts to stop the job represented by the receiver.
	@result An XGActionMonitor instance for tracking the action progress.
*/
- (XGActionMonitor *)performStopAction;

/*!
	@method performRestartAction
	@abstract Attempts to restart the job represented by the receiver.
	@result An XGActionMonitor instance for tracking the action progress.
*/
- (XGActionMonitor *)performRestartAction;

/*!
	@method performSuspendAction
	@abstract Attempts to suspend the job represented by the receiver.
	@result An XGActionMonitor instance for tracking the action progress.
*/
- (XGActionMonitor *)performSuspendAction;

/*!
	@method performResumeAction
	@abstract Attempts to resume the job represented by the receiver.
	@result An XGActionMonitor instance for tracking the action progress.
*/
- (XGActionMonitor *)performResumeAction;

/*!
	@method performGetOutputStreamsAction
	@abstract Attempts to retrieve a list of output streams for the job
	represented by the receiver.
	@result An XGActionMonitor instance for tracking the action progress.
*/
- (XGActionMonitor *)performGetOutputStreamsAction;

/*!
	@method performGetOutputFilesAction
	@abstract Attempts to retrieve a list of output files for the job
	represented by the receiver.
	@result An XGActionMonitor instance for tracking the action progress.
*/
- (XGActionMonitor *)performGetOutputFilesAction;

/*!
	@method performGetSpecificationAction
	@abstract Attempts to retrieve the specification used to submit the job
	represented by the reciever.
	@result An XGActionMonitor instance for tracking the action progress.
*/
- (XGActionMonitor *)performGetSpecificationAction;

/*!
	@method performDeleteAction
	@abstract Attempts to delete the job represented by the receiver.
	@result An XGActionMonitor instance for tracking the action progress.
*/
- (XGActionMonitor *)performDeleteAction;

@end
