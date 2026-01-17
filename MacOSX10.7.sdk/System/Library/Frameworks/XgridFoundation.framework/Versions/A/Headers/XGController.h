//
//  XGController.h
//  GridFoundation
//
//  Copyright (c) 2004 Apple Computer, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <XgridFoundation/XGResource.h>

@class XGConnection;
@class XGControllerInternal;
@class XGGrid;

/*!
	@header XGController.h
 
	This header file describes the interface of an object which represents a remote
	Xgrid controller. Instances of the XGController class are created by an
	Xgrid client using an XGConnection instance, or one of the convenience creators.
*/

/*!
	@const XGControllerWillDeallocNotification
	@discussion This notification gets posted from the controller's dealloc method.
*/	
extern NSString * const XGControllerWillDeallocNotification NS_DEPRECATED_MAC(10_4, 10_7); 

/*!
	@class XGController
 
	@abstract This class provides a local interface to remote Xgrid controllers.
 
	@discussion Instances of this class each connect to an individual controller.
	The association between an instance and a remote Xgrid controller is
	represented by the instance's connection property.  Instances of XGController
	automatically keep themselves up-to-date by monitoring changes to the
	controller they are connected to.  Instances can have predicate strings set
	which cause the controller to selectively filter which properties get updated.
	If a property predicate string is set to "FALSE" then that property will not
	be updated at all.
*/
@interface XGController : XGResource
{
	@private
	XGControllerInternal *_internal1;
}

/*!
	@method initWithConnection:
	@abstract The designated initializer.
	@param connection The connection to be used by the receiver.
	@result An initialized instance.
*/
- (id)initWithConnection:(XGConnection *)connection NS_DEPRECATED_MAC(10_4, 10_7);

/*!
	@method setJobsPredicateString:
	@abstract Sets the predicate string used to filter jobs.
	@param predicateString The predicate string used to filter jobs.
*/
- (void)setJobsPredicateString:(NSString *)predicateString NS_DEPRECATED_MAC(10_4, 10_7);

/*!
	@method jobsPredicateString
	@abstract Returns the predicate string used to filter jobs.
	@result A predicate string.
*/
- (NSString *)jobsPredicateString NS_DEPRECATED_MAC(10_4, 10_7);

/*!
	@method grids
	@abstract Returns an array of the grids lists managed by the controller.
	@result An array of XGGrids.
*/
- (NSArray *)grids NS_DEPRECATED_MAC(10_4, 10_7);

/*!
	@method gridForIdentifier:
	@abstract Returns the grid with the specified identifier, or nil if the
	controller does not manage the grid with the specified identifier.
	@param identifier The identifier of the grid.
	@result An XGGrid instance, or nil.
*/
- (XGGrid *)gridForIdentifier:(NSString *)identifier NS_DEPRECATED_MAC(10_4, 10_7);

/*!
	@method defaultGrid
	@abstract Returns the default grid, or nil if there is no default grid.
	@result An XGGrid instance, or nil.
*/
- (XGGrid *)defaultGrid NS_DEPRECATED_MAC(10_4, 10_7);

/*!
	@method performSubmitJobActionWithJobSpecification:gridIdentifier:
	@abstract Attempts to submit a job to the specified grid, or the default grid if no grid is specified.
	@result An XGActionMontior instance for tracking the action progress.
*/
- (id)performSubmitJobActionWithJobSpecification:(NSDictionary *)jobSpecification gridIdentifier:(NSString *)gridIdentifier NS_DEPRECATED_MAC(10_4, 10_7);

@end

/*!
	@protocol XGControllerCreation
	@abstract Convenience creation methods.
*/
@interface XGController (XGControllerCreation)

/*!
	@method controllerWithNetService:
	@abstract Returns an instance initialized with a connection to the specified
	net service.
*/
+ (id)controllerWithNetService:(NSNetService *)netService NS_DEPRECATED_MAC(10_4, 10_7);

/*!
	@method controllerWithHostname:portnumber:
	@abstract Returns an instance initialized with a connection to the specified
	hostname and portnumber.
*/
+ (id)controllerWithHostname:(NSString *)hostname portnumber:(UInt32)portnumber NS_DEPRECATED_MAC(10_4, 10_7);

/*!
    @method privateController
    @abstract Returns an instance initialized with a connection to a private
    controller.  This controller is shared by all clients running in the current
    user context, and has its own private agent.
*/
+ (id)privateController NS_DEPRECATED_MAC(10_4, 10_7);

/*!
    @method defaultController
    @abstract Returns an instance initialized with a connection to the default
    controller.  If no default controller has been set then this is equivalent
    to calling +privateController.
*/
+ (id)defaultController NS_DEPRECATED_MAC(10_4, 10_7);

@end
