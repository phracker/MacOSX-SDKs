//
//  XGResource.h
//  GridFoundation
//
//  Copyright (c) 2004 Apple Computer, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <XgridFoundation/XGActionMonitor.h>

@class XGConnection;
@class XGController;
@class XGResourceInternal;

/*!
	@header XGResource.h
 
	This header file describes the interface to an object which represents a remote
	resource managed by and Xgrid controller. The XGResource class is abstract.
*/

/*!
	@enum XGResourceState
*/
typedef enum {
	XGResourceStateUninitialized = 0,
	XGResourceStateOffline,
	XGResourceStateConnecting,
	XGResourceStateUnavailable,
	XGResourceStateAvailable,
	XGResourceStateWorking,
	XGResourceStatePending,
	XGResourceStateStarting,
	XGResourceStateStagingIn,
	XGResourceStateRunning,
	XGResourceStateSuspended,
	XGResourceStateStagingOut,
	XGResourceStateCanceled,
	XGResourceStateFailed,
	XGResourceStateFinished
} XGResourceState;

/*!
	@class XGResource
	@discussion This is the base class of all objects that represent a (remote)
	grid resource. You never deal with instances of XGResource, only subclasses.
	The XGResource interface exposes the concept of "updating" whereby the local
	(proxy) object updates it's internal state to match the remote resource the
	object represents.
*/
@interface XGResource : NSObject
{
	@private
	XGResourceInternal *_internal;
}

/*!
	@method controller
	@abstract Returns the XGController instance responsible for the resource
	represented by the receiver.
	@result The responsible XGController instance.
*/
- (XGController *)controller;

/*!
	@method connection
	@abstract Returns the connection associated with the receiver's controller.
	@result The receiver's connection.
*/
- (XGConnection *)connection;

/*!
	@method isUpdating
	@abstract Returns YES if the receiver is in the process of updating.
	@result Whether or not the receiver is updating.
*/
- (BOOL)isUpdating;

/*!
	@method isUpdated
	@abstract Returns YES if the receiver has successfully updated at least once
	since the connection opened.
	@result Whether or not the receiver is updated.
*/
- (BOOL)isUpdated;

/*!
	@method state
	@abstract Returns the state of the receiver.
	@result The state of the receiver.
*/
- (XGResourceState)state;

/*!
	@method identifier
	@abstract Returns the unique identifier of the receiver's resource.
	@result The unique identifier of the receiver's resource.
	@discussion The identifier is a unique string assigned to the resouce by the
	Xgrid controller.  All resources managed by a particular Xgrid controller are
	guaranteed to have a unique identifier, but no guarantee of uniqueness is made
	between multiple Xgrid controllers.
*/
- (NSString *)identifier;

/*!
	@method performAction:withParameters:
	@abstract Causes the receiver to attempt to perform the action. 
	@param action The action to perform.
	@param parameters The parameters to include with the action request.
	@result An XGActionMonitor instance initialized to monitor the action.
	@discussion The returned XGActionMonitor object may be used to monitor the
	progress, success, or failure of the action. The parameters are
	specific to the action being taken, and may be nil.
*/
- (XGActionMonitor *)performAction:(XGResourceAction)action withParameters:(NSDictionary *)parameters;

/*!
	@method actionMonitors
	@abstract Returns the XGActionMonitor instances currently monitoring an action
	for the receiver.
	@result The array of XGActionMonitor instances.
*/
- (NSArray *)actionMonitors;

@end
