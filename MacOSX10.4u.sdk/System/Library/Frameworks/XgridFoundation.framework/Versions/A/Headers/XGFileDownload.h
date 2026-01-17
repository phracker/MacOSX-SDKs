//
//  XGFileDownload.h
//  GridFoundation
//
//  Copyright (c) 2004 Apple Computer, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class XGFileDownloadInternal;
@class XGFile;

/*!
	@header XGFileDownload.h
*/

/*!
	@class XGFileDownload
	@discussion A XGFileDownload downloads the content of an XGFile.  The content may
	be downloaded to a file on disk, to memory, or both.  The content and progress of
	the download is reported via the XGFileDownloadDelegate protocol.
*/
@interface XGFileDownload : NSObject
{
	@private
	XGFileDownloadInternal *_internal;
}

/*!
	@method initWithFile:delegate:
	@abstract Initializes a XGFileDownload object and starts the download.
	@param file The file to download. Must not be nil.
	@param delegate The delegate of the download.
	@result An initialized XGFileDownload object.
*/
- (id)initWithFile:(XGFile *)file delegate:(id)delegate;

/*!
	@method cancel
	@abstract Cancels the download and deletes the partially downloaded file, if any.
*/
- (void)cancel;

/*!
	@method setDestination:allowOverwrite:
	@abstract Sets the destination path of the downloaded file.
	@param path The destination path of the downloaded file.
	@param allowOverwrite Allows a file of the same path to be overwritten.
	@discussion This method can be called after the download is created or in response
	to the decideDestinationWithSuggestedFilename: delegate method. It should only be
	called once. If NO is passed for allowOverwrite and a file of the same path exists,
	a number will be appended to the filename to prevent the overwrite. Because of this,
	use the path passed with didCreateDestination: to determine the actual path of the
	downloaded file.
*/
- (void)setDestination:(NSString *)destination allowOverwrite:(BOOL)allowOverwrite;

/*!
	@method file
	@abstract Returns the file of the download.
	@result The file of the download.
*/
- (XGFile *)file;

/*!
	@method delegate
	@abstract Returns the delegate of the download.
	@result The delegate of the download.
*/
- (id)delegate;

/*!
	@method destination
	@abstract Returns the destionation of the download, or nil if no destination has been set.
	@result The destination of the download.
*/
- (NSString *)destination;

@end

/*!
	@protocol NSURLDownloadDelegate
	@discussion The XGFileDownloadDelegate delegate is used to receive the content data
	and report the progress of the download.
*/
@interface NSObject (XGFileDownloadDelegate)

/*!
	@method fileDownloadDidBegin:
	@abstract This method is called immediately after the download has started.
	@param fileDownload The download that just started downloading.
*/
- (void)fileDownloadDidBegin:(XGFileDownload *)fileDownload;

/*!
	@method fileDownload:didReceiveAttributes:
	@abstract This method is called when the download has loaded the attributes of the file.
	@param fileDownload The download that has received the attributes.
	@param data The received attributes.
	@discussion This method will be called once.
*/
- (void)fileDownload:(XGFileDownload *)fileDownload didReceiveAttributes:(NSDictionary *)attributes;

/*!
	@method fileDownload:decideDestinationWithSuggestedPath:
	@abstract This method is called when enough information has been loaded to decide a
	destination for the downloaded file.
	@param fileDownload The download that requests the download path.
	@param filename The suggested relative path for deciding the path of the downloaded file.
	@discussion Once the delegate has decided a path, it should call
	setDestination:allowOverwrite:. This delegate method will not be called if
	setDestination:allowOverwrite: has already been called.  If the destination is not
	set, or if the destination is set to nil, no file will be saved to disk.
*/
- (void)fileDownload:(XGFileDownload *)fileDownload decideDestinationWithSuggestedPath:(NSString *)path;

/*!
	@method fileDownload:didCreateDestination:
	@abstract This method is called if the download creates a downloaded file.
	@param fileDownload The download that created the downloaded file.
	@param path The path of the downloaded file.
*/
- (void)fileDownload:(XGFileDownload *)fileDownload didCreateDestination:(NSString *)destination;

/*!
	@method fileDownload:didReceiveData:
	@abstract This method is called when the download has loaded data.
	@param fileDownload The download that has received data.
	@param data The received data.
	@discussion This method will be called one or more times.  If the download is
	also being written to disk then this method will be called immediately after the
	data is written to disk.
*/
- (void)fileDownload:(XGFileDownload *)fileDownload didReceiveData:(NSData *)data;

/*!
	@method fileDownload:didFailWithError:
	@abstract This method is called when the download has failed. 
	@param fileDownload The download that ended in error.
	@param error The error caused the download to fail.
	@discussion This method is called when the download encounters a network or file
	I/O related error. This method or downloadDidFinish: will only be called once.
*/
- (void)fileDownload:(XGFileDownload *)fileDownload didFailWithError:(NSError *)error;

/*!
	@method fileDownloadDidFinish:
	@abstract This method is called when the download has finished downloading.
	@param fileDownload The download that has finished downloading.
	@discussion This method is called after all the data has been received and written
	to disk. This method or download:didFailWithError: will only be called once.
*/
- (void)fileDownloadDidFinish:(XGFileDownload *)fileDownload;

@end
