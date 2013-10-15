//
//  XGFile.h
//  GridFoundation
//
//  Copyright (c) 2004 Apple Computer, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <XgridFoundation/XGResource.h>

@class XGFileInternal;
@class XGJob;

/*!
	@header XGFile.h
 
	This header describes the interface of an object which represents a file
	managed by a remote Xgrid controller.
 
	Instances of XGFile can be used to initialize XGFileDownload objects. 
*/

/*!
	@enum XGFileType
	@discussion The type of file.
	@constant XGFileTypeNone No file type.
	@constant XGFileTypeRegular The file is regular.
	@constant XGFileTypeStream The file is a stream.
*/
typedef enum {
	XGFileTypeNone = 0,
	XGFileTypeRegular,
	XGFileTypeStream
} XGFileType NS_DEPRECATED_MAC(10_4, 10_7);

/*!
	@const XGFileStandardOutputPath
	@discussion The standard output stream has this path.
*/
extern NSString * const XGFileStandardOutputPath NS_DEPRECATED_MAC(10_4, 10_7);

/*!
	@const XGFileStandardErrorPath
	@discussion The standard error stream has this path.
*/
extern NSString * const XGFileStandardErrorPath NS_DEPRECATED_MAC(10_4, 10_7);

/*!
	@class XGFile
 
	@abstract This class is an immutable, inactive representation of a file
	associated with a job managed by an Xgrid controller.  Instances of this
	class are obtained by performing a "get output" type of action on a resource
	and retrieving the files from the results dictionary of the action monitor.
*/
@interface XGFile : NSObject
{
	@private
	XGFileInternal *_internal;
}

/*!
	@method job
	@abstract Returns the XGJob instance associated with the receiver.
	@result The XGJob instance.
*/
- (XGJob *)job NS_DEPRECATED_MAC(10_4, 10_7);

/*!
	@method taskIdentifier
	@abstract Returns the identifier of the task associated with the receiver.
	@result The task identifier.
*/
- (NSString *)taskIdentifier NS_DEPRECATED_MAC(10_4, 10_7);

/*!
	@method type
	@abstract Returns the XGFileType of the receiver.
	@result The file type.
*/
- (XGFileType)type NS_DEPRECATED_MAC(10_4, 10_7);

/*!
	@method path
	@abstract Returns the path of the receiver.
	@result The path.
*/
- (NSString *)path NS_DEPRECATED_MAC(10_4, 10_7);

@end
