/*	
    NSURLDownload.h
    Copyright (C) 2003-2005, Apple Computer, Inc. All rights reserved.    
    
    Public header file.
*/

// Note: To use the APIs described in these headers, you must perform
// a runtime check for Foundation-462.1 or later.
#import <AvailabilityMacros.h>
#if defined(MAC_OS_X_VERSION_10_2) && (MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_2)

#import <Foundation/NSObject.h>

@class NSError;
@class NSString;
@class NSData;
@class NSURLAuthenticationChallenge;
@class NSURLDownloadInternal;
@class NSURLRequest;
@class NSURLResponse;

/*!
    @class NSURLDownload
    @discussion A NSURLDownload loads a request and saves the downloaded data to a file. The progress of the download
    is reported via the NSURLDownloadDelegate protocol. Note: The word "download" is used to refer to the process
    of loading data off a network, decoding the data if necessary and saving the data to a file.
*/
@interface NSURLDownload : NSObject
{
    @private
    NSURLDownloadInternal *_internal;
}

/*!
    @method canResumeDownloadDecodedWithEncodingMIMEType:
    @abstract Returns whether or not NSURLDownload can resume a download that was decoded with a given encoding MIME type.
    @param MIMEType The encoding MIME type.
    @description canResumeDownloadDecodedWithEncodingMIMEType: returns whether or not NSURLDownload can resume a download
    that was decoded with a given encoding MIME type.  NSURLDownload cannot resume a download that was partially decoded
    in the gzip format for example. In order to ensure that a download can be later resumed,
    canResumeDownloadDecodedWithEncodingMIMEType: should be used when download:shouldDecodeSourceDataOfMIMEType: is called.
*/
+ (BOOL)canResumeDownloadDecodedWithEncodingMIMEType:(NSString *)MIMEType;

/*!
    @method initWithRequest:delegate:
    @abstract Initializes a NSURLDownload object and starts the download.
    @param request The request to download. Must not be nil.
    @param delegate The delegate of the download.
    @result An initialized NSURLDownload object.
*/
- (id)initWithRequest:(NSURLRequest *)request delegate:(id)delegate;

/*!
    @method initWithResumeData:delegate:path:
    @abstract Initializes a NSURLDownload object for resuming a previous download.
    @param resumeData The resume data from the previous download.
    @param delegate The delegate of the download.
    @param path The path of the incomplete downloaded file.
    @result An initialized NSURLDownload object.
*/
- (id)initWithResumeData:(NSData *)resumeData delegate:(id)delegate path:(NSString *)path;

/*!
    @method cancel
    @abstract Cancels the download and deletes the downloaded file.
*/
- (void)cancel;

/*!
    @method setDestination:allowOverwrite:
    @abstract Sets the destination path of the downloaded file.
    @param path The destination path of the downloaded file.
    @param allowOverwrite Allows a file of the same path to be overwritten.
    @discussion This method can be called after the download is created or in response to the
    decideDestinationWithSuggestedFilename: delegate method. It should only be called once.
    If NO is passed for allowOverwrite and a file of the same path exists, a number will be
    appended to the filename to prevent the overwrite. Because of this, use the path
    passed with didCreateDestination: to determine the actual path of the downloaded file.
*/
- (void)setDestination:(NSString *)path allowOverwrite:(BOOL)allowOverwrite;

/*!
    @method request
    @abstract Returns the request of the download.
    @result The request of the download.
*/
- (NSURLRequest *)request;

/*!
    @method resumeData
    @abstract Returns the resume data of a download that is incomplete.
    @result The resume data.
    @description resumeData returns the resume data of a download that is incomplete. This data represents the necessary
    state information that NSURLDownload needs to resume a download. The resume data can later be used when initializing
    a download with initWithResumeData:delegate:path:. Non-nil is returned if resuming the download seems possible.
    Non-nil is returned if the download was cancelled or ended in error after some but not all data has been received.
    The protocol of the download as well as the server must support resuming for non-nil to be returned.
    In order to later resume a download, be sure to call setDeletesFileUponFailure: with NO.
*/
- (NSData *)resumeData;

/*!
    @method setDeletesFileUponFailure:
    @abstract Sets whether or not the downloaded file should be deleted upon failure.
    @param deletesFileUponFailure The value of deletesFileUponFailure.
    @description To allow the download to be resumed in case the download ends prematurely,
    deletesFileUponFailure must be set to NO as soon as possible to prevent the downloaded file
    from being deleted.
*/
- (void)setDeletesFileUponFailure:(BOOL)deletesFileUponFailure;

/*!
    @method deletesFileUponFailure
    @abstract Returns whether or not the downloaded file should be deleted upon failure.
    @result The value of deletesFileUponFailure. deletesFileUponFailure is YES by default.
*/
- (BOOL)deletesFileUponFailure;

@end

/*!
    @protocol NSURLDownloadDelegate
    @discussion The NSURLDownloadDelegate delegate is used to report the progress of the download.
*/
@interface NSObject (NSURLDownloadDelegate)

/*!
    @method downloadDidBegin:
    @abstract This method is called immediately after the download has started.
    @param download The download that just started downloading.
*/
- (void)downloadDidBegin:(NSURLDownload *)download;

/*!
    @method download:willSendRequest:redirectResponse:
    @abstract This method is called if the download must load another request because the previous
    request was redirected.
    @param download The download that will send the request.
    @param request The request that will be used to continue loading.
    @result The request to be used; either the request parameter or a replacement. If nil is returned,
    the download is cancelled.
    @discussion This method gives the delegate an opportunity to inspect the request
    that will be used to continue loading the request, and modify it if necessary.
*/
- (NSURLRequest *)download:(NSURLDownload *)download willSendRequest:(NSURLRequest *)request redirectResponse:(NSURLResponse *)redirectResponse;

/*!
    @method download:didReceiveAuthenticationChallenge:
    @abstract Start authentication for a given challenge
    @param download The download that needs authentication.
    @param challenge The NSURLAuthenticationChallenge for which to start authentication.
    @discussion Call useCredential:forAuthenticationChallenge:,
    continueWithoutCredentialForAuthenticationChallenge: or cancel on
    the connection sender when done.
*/
- (void)download:(NSURLDownload *)download didReceiveAuthenticationChallenge:(NSURLAuthenticationChallenge *)challenge;

/*!
    @method download:didCancelAuthenticationChallenge:
    @abstract Cancel authentication for a given request
    @param download The download that's cancelling
    @param challenge The NSURLAuthenticationChallenge to cancel authentication for
*/
- (void)download:(NSURLDownload *)download didCancelAuthenticationChallenge:(NSURLAuthenticationChallenge *)challenge;

/*!
    @method download:didReceiveResponse:
    @abstract This method is called when the download has received a response from the server.
    @param download The download that now has a NSURLResponse available for inspection.
    @param response The NSURLResponse object for the given download.
    @discussion In some rare cases, multiple responses may be received for a single download.
    This occurs with multipart/x-mixed-replace, or "server push". In this case, the client
    should assume that each new response resets progress so far for the resource back to 0,
    and should check the new response for the expected content length.
*/
- (void)download:(NSURLDownload *)download didReceiveResponse:(NSURLResponse *)response;

/*!
    @method download:willResumeWithResponse:fromByte:
    @abstract This method is called when the download has received a response from the server after attempting to
    resume a download.
    @param download The download that now has a NSURLResponse available for inspection.
    @param response The NSURLResponse object for the given download.
    @param startingByte The number of bytes from where the download will resume. 0 indicates that the download will
    restart from the beginning.
    @discussion download:willResumeWithResponse:fromByte: is called instead of download:didReceiveResponse:
    when a download is initialized with initWithResumeData:delegate:path:.
*/
- (void)download:(NSURLDownload *)download willResumeWithResponse:(NSURLResponse *)response fromByte:(long long)startingByte;

/*!
    @method download:didReceiveDataOfLength:
    @abstract This method is called when the download has loaded data.
    @param download The download that has received data.
    @param length The length of the received data.
    @discussion This method will be called one or more times.
*/
- (void)download:(NSURLDownload *)download didReceiveDataOfLength:(unsigned)length;

/*!
    @method download:shouldDecodeSourceDataOfMIMEType:
    @abstract This method is called if the download detects that the downloading file is encoded.
    @param download The download that has detected that the downloading file is encoded.
    @param mimeType A MIME type expressing the encoding type.
    @result Return YES to decode the file, NO to not decode the file.
    @discussion An encoded file is encoded in MacBinary, BinHex or gzip format. This method may be
    called more than once if the file is encoded multiple times. This method is not called if the
    download is not encoded.
*/
- (BOOL)download:(NSURLDownload *)download shouldDecodeSourceDataOfMIMEType:(NSString *)encodingType;

/*!
    @method download:decideDestinationWithSuggestedFilename:
    @abstract This method is called when enough information has been loaded to decide a destination
    for the downloaded file.
    @param download The download that requests the download path.
    @param filename The suggested filename for deciding the path of the downloaded file. The filename is either
    derived from the last path component of the URL and the MIME type or if the download was encoded,
    it is the filename specified in the encoding.
    @discussion Once the delegate has decided a path, it should call setDestination:allowOverwrite:.
    The delegate may respond immediately or later. This method is not called if
    setDestination:allowOverwrite: has already been called.
*/
- (void)download:(NSURLDownload *)download decideDestinationWithSuggestedFilename:(NSString *)filename;

/*!
    @method download:didCreateDestination:
    @abstract This method is called after the download creates the downloaded file.
    @param download The download that created the downloaded file.
    @param path The path of the downloaded file.
*/
- (void)download:(NSURLDownload *)download didCreateDestination:(NSString *)path;

/*!
    @method downloadDidFinish:
    @abstract This method is called when the download has finished downloading.
    @param download The download that has finished downloading.
    @discussion This method is called after all the data has been received and written to disk.
    This method or download:didFailWithError: will only be called once.
*/
- (void)downloadDidFinish:(NSURLDownload *)download;

/*!
    @method download:didFailWithError:
    @abstract This method is called when the download has failed. 
    @param download The download that ended in error.
    @param error The error caused the download to fail.
    @discussion This method is called when the download encounters a network or file I/O related error.
    This method or downloadDidFinish: will only be called once.
*/
- (void)download:(NSURLDownload *)download didFailWithError:(NSError *)error;

@end

#endif
