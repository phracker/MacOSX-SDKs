//
//  XGGrid.h
//  GridFoundation
//
//  Copyright (c) 2004 Apple Computer, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <XgridFoundation/XGResource.h>

@class XGGridInternal;
@class XGJob;

/*!
	@header XGGrid.h
 
	This header file describes the interface of an object which represents a remote
	Xgrid grid. A grid is a collection of jobs. Instances of the XGGrid
	class are obtained from a XGController instance.
*/

/*!
	@class XGGrid
	@abstract This class provides a local interface to remote Xgrid grids.
*/
@interface XGGrid : XGResource
{
	@private
	XGGridInternal *_internal1;
}

/*!
	@method isDefault
	@abstract Returns YES if the receiver is the default grid.
	@result YES or NO.
*/
- (BOOL)isDefault;

/*!
	@method jobs
	@abstract Returns an array of the jobs associated with the receiver.
	@result An array of XGJobs.
*/
- (NSArray *)jobs;

/*!
	@method jobForIdentifier:
	@abstract Returns the job with the specified identifier, or nil if the
	controller does not manage the job with the specified identifier.
	@param identifier The identifier of the job.
	@result An XGJob instance, or nil.
*/
- (XGJob *)jobForIdentifier:(NSString *)identifier;

@end
