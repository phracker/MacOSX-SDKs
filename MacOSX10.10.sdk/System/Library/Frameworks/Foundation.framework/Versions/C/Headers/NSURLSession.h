/*	NSURLSession.h
	Copyright (c) 2013-2014, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSURLRequest.h>
#import <Foundation/NSHTTPCookieStorage.h>

#include <Security/SecureTransport.h>

@class NSString;
@class NSURL;
@class NSError;
@class NSArray;
@class NSDictionary;
@class NSInputStream;
@class NSData;
@class NSOperationQueue;

@class NSURLCache;
@class NSURLResponse;
@class NSHTTPURLResponse;
@class NSHTTPCookie;
@class NSCachedURLResponse;
@class NSURLAuthenticationChallenge;
@class NSURLProtectionSpace;
@class NSURLCredential;
@class NSURLCredentialStorage;

/*

 NSURLSession is a replacement API for NSURLConnection.  It provides
 options that affect the policy of, and various aspects of the
 mechanism by which NSURLRequest objects are retrieved from the
 network.

 An NSURLSession may be bound to a delegate object.  The delegate is
 invoked for certain events during the lifetime of a session, such as
 server authentication or determining whether a resource to be loaded
 should be converted into a download.
 
 NSURLSession instances are threadsafe.

 The default NSURLSession uses a system provided delegate and is
 appropriate to use in place of existing code that uses
 +[NSURLConnection sendAsynchronousRequest:queue:completionHandler:]

 An NSURLSession creates NSURLSessionTask objects which represent the
 action of a resource being loaded.  These are analogous to
 NSURLConnection objects but provide for more control and a unified
 delegate model.
 
 NSURLSessionTask objects are always created in a suspended state and
 must be sent the -resume message before they will execute.

 Subclasses of NSURLSessionTask are used to syntactically
 differentiate between data and file downloads.

 An NSURLSessionDataTask receives the resource as a series of calls to
 the URLSession:dataTask:didReceiveData: delegate method.  This is type of
 task most commonly associated with retrieving objects for immediate parsing
 by the consumer.

 An NSURLSessionUploadTask differs from an NSURLSessionDataTask
 in how its instance is constructed.  Upload tasks are explicitly created
 by referencing a file or data object to upload, or by utilizing the
 -URLSession:task:needNewBodyStream: delegate message to supply an upload
 body.

 An NSURLSessionDownloadTask will directly write the response data to
 a temporary file.  When completed, the delegate is sent
 URLSession:downloadTask:didFinishDownloadingToURL: and given an opportunity 
 to move this file to a permanent location in its sandboxed container, or to
 otherwise read the file. If canceled, an NSURLSessionDownloadTask can
 produce a data blob that can be used to resume a download at a later
 time.
 
 */

@class NSURLSession;
@class NSURLSessionDataTask;                /* DataTask objects receive the payload through zero or more delegate messages */
@class NSURLSessionUploadTask;              /* UploadTask objects receive periodic progress updates but do not return a body */
@class NSURLSessionDownloadTask;            /* DownloadTask objects represent an active download to disk.  They can provide resume data when canceled. */
@class NSURLSessionConfiguration;
@protocol NSURLSessionDelegate;


/*

 NSURLSession is not available for i386 targets before Mac OS X 10.10.

 */

#if __OBJC2__
#define NSURLSESSION_AVAILABLE	10_9
#else
#define NSURLSESSION_AVAILABLE	10_10
#endif


FOUNDATION_EXPORT const int64_t NSURLSessionTransferSizeUnknown NS_AVAILABLE(NSURLSESSION_AVAILABLE, 7_0);    /* -1LL */

NS_CLASS_AVAILABLE(NSURLSESSION_AVAILABLE, 7_0)
@interface NSURLSession : NSObject

/*
 * The shared session uses the currently set global NSURLCache,
 * NSHTTPCookieStorage and NSURLCredentialStorage objects.
 */
+ (NSURLSession *)sharedSession;

/*
 * Customization of NSURLSession occurs during creation of a new session.
 * If you only need to use the convenience routines with custom
 * configuration options it is not necessary to specify a delegate.
 * If you do specify a delegate, the delegate will be retained until after
 * the delegate has been sent the URLSession:didBecomeInvalidWithError: message.
 */
+ (NSURLSession *)sessionWithConfiguration:(NSURLSessionConfiguration *)configuration;
+ (NSURLSession *)sessionWithConfiguration:(NSURLSessionConfiguration *)configuration delegate:(id <NSURLSessionDelegate>)delegate delegateQueue:(NSOperationQueue *)queue;

@property (readonly, retain) NSOperationQueue *delegateQueue;
@property (readonly, retain) id <NSURLSessionDelegate> delegate;
@property (readonly, copy) NSURLSessionConfiguration *configuration;

/*
 * The sessionDescription property is available for the developer to
 * provide a descriptive label for the session.
 */
@property (copy) NSString *sessionDescription;

/* -finishTasksAndInvalidate returns immediately and existing tasks will be allowed
 * to run to completion.  New tasks may not be created.  The session
 * will continue to make delegate callbacks until URLSession:didBecomeInvalidWithError:
 * has been issued. 
 *
 * -finishTasksAndInvalidate and -invalidateAndCancel do not
 * have any effect on the shared session singleton.
 */
- (void)finishTasksAndInvalidate;

/* -invalidateAndCancel acts as -finishTasksAndInvalidate, but issues
 * -cancel to all outstanding tasks for this session.  Note task 
 * cancellation is subject to the state of the task, and some tasks may
 * have already have completed at the time they are sent -cancel. 
 */
- (void)invalidateAndCancel;

- (void)resetWithCompletionHandler:(void (^)(void))completionHandler;    /* empty all cookies, cache and credential stores, removes disk files, issues -flushWithCompletionHandler:. Invokes completionHandler() on the delegate queue if not nil. */
- (void)flushWithCompletionHandler:(void (^)(void))completionHandler;    /* flush storage to disk and clear transient network caches.  Invokes completionHandler() on the delegate queue if not nil. */

- (void)getTasksWithCompletionHandler:(void (^)(NSArray *dataTasks, NSArray *uploadTasks, NSArray *downloadTasks))completionHandler; /* invokes completionHandler with outstanding data, upload and download tasks. */

/* 
 * NSURLSessionTask objects are always created in a suspended state and
 * must be sent the -resume message before they will execute.
 */

/* Creates a data task with the given request.  The request may have a body stream. */
- (NSURLSessionDataTask *)dataTaskWithRequest:(NSURLRequest *)request;

/* Creates a data task to retrieve the contents of the given URL. */
- (NSURLSessionDataTask *)dataTaskWithURL:(NSURL *)url;

/* Creates an upload task with the given request.  The body of the request will be created from the file referenced by fileURL */
- (NSURLSessionUploadTask *)uploadTaskWithRequest:(NSURLRequest *)request fromFile:(NSURL *)fileURL;

/* Creates an upload task with the given request.  The body of the request is provided from the bodyData. */
- (NSURLSessionUploadTask *)uploadTaskWithRequest:(NSURLRequest *)request fromData:(NSData *)bodyData;

/* Creates an upload task with the given request.  The previously set body stream of the request (if any) is ignored and the URLSession:task:needNewBodyStream: delegate will be called when the body payload is required. */
- (NSURLSessionUploadTask *)uploadTaskWithStreamedRequest:(NSURLRequest *)request;

/* Creates a download task with the given request. */
- (NSURLSessionDownloadTask *)downloadTaskWithRequest:(NSURLRequest *)request;

/* Creates a download task to download the contents of the given URL. */
- (NSURLSessionDownloadTask *)downloadTaskWithURL:(NSURL *)url;

/* Creates a download task with the resume data.  If the download cannot be successfully resumed, URLSession:task:didCompleteWithError: will be called. */
- (NSURLSessionDownloadTask *)downloadTaskWithResumeData:(NSData *)resumeData;

@end

/*
 * NSURLSession convenience routines deliver results to 
 * a completion handler block.  These convenience routines
 * are not available to NSURLSessions that are configured
 * as background sessions.
 *
 * Task objects are always created in a suspended state and 
 * must be sent the -resume message before they will execute.
 */
@interface NSURLSession (NSURLSessionAsynchronousConvenience)
/*
 * data task convenience methods.  These methods create tasks that
 * bypass the normal delegate calls for response and data delivery,
 * and provide a simple cancelable asynchronous interface to receiving
 * data.  Errors will be returned in the NSURLErrorDomain, 
 * see <Foundation/NSURLError.h>.  The delegate, if any, will still be
 * called for authentication challenges.
 */
- (NSURLSessionDataTask *)dataTaskWithRequest:(NSURLRequest *)request completionHandler:(void (^)(NSData *data, NSURLResponse *response, NSError *error))completionHandler NS_CLASS_AVAILABLE(NSURLSESSION_AVAILABLE, 7_0);
- (NSURLSessionDataTask *)dataTaskWithURL:(NSURL *)url completionHandler:(void (^)(NSData *data, NSURLResponse *response, NSError *error))completionHandler NS_CLASS_AVAILABLE(NSURLSESSION_AVAILABLE, 7_0);

/*
 * upload convenience method.
 */
- (NSURLSessionUploadTask *)uploadTaskWithRequest:(NSURLRequest *)request fromFile:(NSURL *)fileURL completionHandler:(void (^)(NSData *data, NSURLResponse *response, NSError *error))completionHandler NS_CLASS_AVAILABLE(NSURLSESSION_AVAILABLE, 7_0);
- (NSURLSessionUploadTask *)uploadTaskWithRequest:(NSURLRequest *)request fromData:(NSData *)bodyData completionHandler:(void (^)(NSData *data, NSURLResponse *response, NSError *error))completionHandler NS_CLASS_AVAILABLE(NSURLSESSION_AVAILABLE, 7_0);

/*
 * download task convenience methods.  When a download successfully
 * completes, the NSURL will point to a file that must be read or
 * copied during the invocation of the completion routine.  The file
 * will be removed automatically.
 */
- (NSURLSessionDownloadTask *)downloadTaskWithRequest:(NSURLRequest *)request completionHandler:(void (^)(NSURL *location, NSURLResponse *response, NSError *error))completionHandler NS_CLASS_AVAILABLE(NSURLSESSION_AVAILABLE, 7_0);
- (NSURLSessionDownloadTask *)downloadTaskWithURL:(NSURL *)url completionHandler:(void (^)(NSURL *location, NSURLResponse *response, NSError *error))completionHandler NS_CLASS_AVAILABLE(NSURLSESSION_AVAILABLE, 7_0);
- (NSURLSessionDownloadTask *)downloadTaskWithResumeData:(NSData *)resumeData completionHandler:(void (^)(NSURL *location, NSURLResponse *response, NSError *error))completionHandler NS_CLASS_AVAILABLE(NSURLSESSION_AVAILABLE, 7_0);

@end

typedef NS_ENUM(NSInteger, NSURLSessionTaskState) {
    NSURLSessionTaskStateRunning = 0,                     /* The task is currently being serviced by the session */
    NSURLSessionTaskStateSuspended = 1,
    NSURLSessionTaskStateCanceling = 2,                   /* The task has been told to cancel.  The session will receive a URLSession:task:didCompleteWithError: message. */
    NSURLSessionTaskStateCompleted = 3,                   /* The task has completed and the session will receive no more delegate notifications */
} NS_ENUM_AVAILABLE(NSURLSESSION_AVAILABLE, 7_0);

/*
 * NSURLSessionTask - a cancelable object that refers to the lifetime
 * of processing a given request.
 */
NS_CLASS_AVAILABLE(NSURLSESSION_AVAILABLE, 7_0)
@interface NSURLSessionTask : NSObject <NSCopying>

@property (readonly) NSUInteger taskIdentifier;		    /* an identifier for this task, assigned by and unique to the owning session */
@property (readonly, copy) NSURLRequest *originalRequest;
@property (readonly, copy) NSURLRequest *currentRequest;    /* may differ from originalRequest due to http server redirection */
@property (readonly, copy) NSURLResponse *response;	    /* may be nil if no response has been received */

/* Byte count properties may be zero if no body is expected, 
 * or NSURLSessionTransferSizeUnknown if it is not possible 
 * to know how many bytes will be transferred.
 */

/* number of body bytes already received */
@property (readonly) int64_t countOfBytesReceived;

/* number of body bytes already sent */
@property (readonly) int64_t countOfBytesSent;

/* number of body bytes we expect to send, derived from the Content-Length of the HTTP request */
@property (readonly) int64_t countOfBytesExpectedToSend;

/* number of byte bytes we expect to receive, usually derived from the Content-Length header of an HTTP response. */
@property (readonly) int64_t countOfBytesExpectedToReceive;

/*
 * The taskDescription property is available for the developer to
 * provide a descriptive label for the task.
 */
@property (copy) NSString *taskDescription;

/* -cancel returns immediately, but marks a task as being canceled.
 * The task will signal -URLSession:task:didCompleteWithError: with an
 * error value of { NSURLErrorDomain, NSURLErrorCancelled }.  In some 
 * cases, the task may signal other work before it acknowledges the 
 * cancelation.  -cancel may be sent to a task that has been suspended.
 */
- (void)cancel;

/*
 * The current state of the task within the session.
 */
@property (readonly) NSURLSessionTaskState state;

/*
 * The error, if any, delivered via -URLSession:task:didCompleteWithError:
 * This property will be nil in the event that no error occured.
 */
@property (readonly, copy) NSError *error;

/*
 * Suspending a task will prevent the NSURLSession from continuing to
 * load data.  There may still be delegate calls made on behalf of
 * this task (for instance, to report data received while suspending)
 * but no further transmissions will be made on behalf of the task
 * until -resume is sent.  The timeout timer associated with the task
 * will be disabled while a task is suspended. -suspend and -resume are
 * nestable. 
 */
- (void)suspend;
- (void)resume;

/*
 * Sets a scaling factor for the priority of the task. The scaling factor is a
 * value between 0.0 and 1.0 (inclusive), where 0.0 is considered the lowest
 * priority and 1.0 is considered the highest.
 *
 * The priority is a hint and not a hard requirement of task performance. The
 * priority of a task may be changed using this API at any time, but not all
 * protocols support this; in these cases, the last priority that took effect
 * will be used.
 *
 * If no priority is specified, the task will operate with the default priority
 * as defined by the constant NSURLSessionTaskPriorityDefault. Two additional
 * priority levels are provided: NSURLSessionTaskPriorityLow and
 * NSURLSessionTaskPriorityHigh, but use is not restricted to these.
 */
@property float priority NS_AVAILABLE(10_10, 8_0);

@end

FOUNDATION_EXPORT const float NSURLSessionTaskPriorityDefault NS_AVAILABLE(10_10, 8_0);
FOUNDATION_EXPORT const float NSURLSessionTaskPriorityLow NS_AVAILABLE(10_10, 8_0);
FOUNDATION_EXPORT const float NSURLSessionTaskPriorityHigh NS_AVAILABLE(10_10, 8_0);

/*
 * An NSURLSessionDataTask does not provide any additional
 * functionality over an NSURLSessionTask and its presence is merely
 * to provide lexical differentiation from download and upload tasks.
 */
@interface NSURLSessionDataTask : NSURLSessionTask
@end

/*
 * An NSURLSessionUploadTask does not currently provide any additional
 * functionality over an NSURLSessionDataTask.  All delgate messages
 * that may be sent referencing an NSURLSessionDataTask equally apply
 * to NSURLSessionUploadTasks.
 */
@interface NSURLSessionUploadTask : NSURLSessionDataTask
@end

/*
 * NSURLSessionDownloadTask is a task that represents a download to
 * local storage.
 */
@interface NSURLSessionDownloadTask : NSURLSessionTask

/* Cancel the download (and calls the superclass -cancel).  If
 * conditions will allow for resuming the download in the future, the
 * callback will be called with an opaque data blob, which may be used
 * with -downloadTaskWithResumeData: to attempt to resume the download.
 * If resume data cannot be created, the completion handler will be
 * called with nil resumeData.
 */
- (void)cancelByProducingResumeData:(void (^)(NSData *resumeData))completionHandler;

@end

/*
 * Configuration options for an NSURLSession.  When a session is
 * created, a copy of the configuration object is made - you cannot
 * modify the configuration of a session after it has been created.
 *
 * The shared session uses the global singleton credential, cache
 * and cookie storage objects.
 *
 * An ephemeral session has no persistent disk storage for cookies,
 * cache or credentials.
 *
 * A background session can be used to perform networking operations
 * on behalf of a suspended application, within certain constraints.
 */
NS_CLASS_AVAILABLE(NSURLSESSION_AVAILABLE, 7_0)
@interface NSURLSessionConfiguration : NSObject <NSCopying>

+ (NSURLSessionConfiguration *)defaultSessionConfiguration;
+ (NSURLSessionConfiguration *)ephemeralSessionConfiguration;
+ (NSURLSessionConfiguration *)backgroundSessionConfigurationWithIdentifier:(NSString *)identifier NS_AVAILABLE(10_10, 8_0);

/* identifier for the background session configuration */
@property (readonly, copy) NSString *identifier;

/* default cache policy for requests */
@property NSURLRequestCachePolicy requestCachePolicy;

/* default timeout for requests.  This will cause a timeout if no data is transmitted for the given timeout value, and is reset whenever data is transmitted. */
@property NSTimeInterval timeoutIntervalForRequest;

/* default timeout for requests.  This will cause a timeout if a resource is not able to be retrieved within a given timeout. */
@property NSTimeInterval timeoutIntervalForResource;

/* type of service for requests. */
@property NSURLRequestNetworkServiceType networkServiceType;

/* allow request to route over cellular. */
@property BOOL allowsCellularAccess;

/* allows background tasks to be scheduled at the discretion of the system for optimal performance. */
@property (getter=isDiscretionary) BOOL discretionary NS_AVAILABLE(10_10, 7_0);

/* The identifier of the shared data container into which files in background sessions should be downloaded.
 * App extensions wishing to use background sessions *must* set this property to a valid container identifier, or
 * the session will be invalidated upon creation.
 */
@property (copy) NSString *sharedContainerIdentifier NS_AVAILABLE(10_10, 8_0);

/* 
 * Allows the app to be resumed or launched in the background when tasks in background sessions complete
 * or when auth is required. This only applies to configurations created with +backgroundSessionConfigurationWithIdentifier:
 * and the default value is YES.
 */
@property BOOL sessionSendsLaunchEvents NS_AVAILABLE(NA, 7_0);

/* The proxy dictionary, as described by <CFNetwork/CFHTTPStream.h> */
@property (copy) NSDictionary *connectionProxyDictionary;

/* The minimum allowable versions of the TLS protocol, from <Security/SecureTransport.h> */
@property SSLProtocol TLSMinimumSupportedProtocol;

/* The maximum allowable versions of the TLS protocol, from <Security/SecureTransport.h> */
@property SSLProtocol TLSMaximumSupportedProtocol;

/* Allow the use of HTTP pipelining */
@property BOOL HTTPShouldUsePipelining;

/* Allow the session to set cookies on requests */
@property BOOL HTTPShouldSetCookies;

/* Policy for accepting cookies.  This overrides the policy otherwise specified by the cookie storage. */
@property NSHTTPCookieAcceptPolicy HTTPCookieAcceptPolicy;

/* Specifies additional headers which will be set on outgoing requests.
   Note that these headers are added to the request only if not already present. */
@property (copy) NSDictionary *HTTPAdditionalHeaders;

/* The maximum number of simultanous persistent connections per host */
@property NSInteger HTTPMaximumConnectionsPerHost;

/* The cookie storage object to use, or nil to indicate that no cookies should be handled */
@property (retain) NSHTTPCookieStorage *HTTPCookieStorage;

/* The credential storage object, or nil to indicate that no credential storage is to be used */
@property (retain) NSURLCredentialStorage *URLCredentialStorage;

/* The URL resource cache, or nil to indicate that no caching is to be performed */
@property (retain) NSURLCache *URLCache;

/* An optional array of Class objects which subclass NSURLProtocol.  
   The Class will be sent +canInitWithRequest: when determining if
   an instance of the class can be used for a given URL scheme.
   You should not use +[NSURLProtocol registerClass:], as that
   method will register your class with the default session rather
   than with an instance of NSURLSession. 
   Custom NSURLProtocol subclasses are not available to background
   sessions.
 */
@property (copy) NSArray *protocolClasses;

@end

/*
 * Disposition options for various delegate messages
 */
typedef NS_ENUM(NSInteger, NSURLSessionAuthChallengeDisposition) {
    NSURLSessionAuthChallengeUseCredential = 0,                     /* Use the specified credential, which may be nil */
    NSURLSessionAuthChallengePerformDefaultHandling = 1,            /* Default handling for the challenge - as if this delegate were not implemented; the credential parameter is ignored. */
    NSURLSessionAuthChallengeCancelAuthenticationChallenge = 2,     /* The entire request will be canceled; the credential parameter is ignored. */
    NSURLSessionAuthChallengeRejectProtectionSpace = 3,             /* This challenge is rejected and the next authentication protection space should be tried;the credential parameter is ignored. */
} NS_ENUM_AVAILABLE(NSURLSESSION_AVAILABLE, 7_0);


typedef NS_ENUM(NSInteger, NSURLSessionResponseDisposition) {
    NSURLSessionResponseCancel = 0,                                 /* Cancel the load, this is the same as -[task cancel] */
    NSURLSessionResponseAllow = 1,                                  /* Allow the load to continue */
    NSURLSessionResponseBecomeDownload = 2,                         /* Turn this request into a download */
} NS_ENUM_AVAILABLE(NSURLSESSION_AVAILABLE, 7_0);

/*
 * NSURLSessionDelegate specifies the methods that a session delegate
 * may respond to.  There are both session specific messages (for
 * example, connection based auth) as well as task based messages.
 */

/*
 * Messages related to the URL session as a whole
 */
@protocol NSURLSessionDelegate <NSObject>
@optional

/* The last message a session receives.  A session will only become
 * invalid because of a systemic error or when it has been
 * explicitly invalidated, in which case the error parameter will be nil.
 */
- (void)URLSession:(NSURLSession *)session didBecomeInvalidWithError:(NSError *)error;

/* If implemented, when a connection level authentication challenge
 * has occurred, this delegate will be given the opportunity to
 * provide authentication credentials to the underlying
 * connection. Some types of authentication will apply to more than
 * one request on a given connection to a server (SSL Server Trust
 * challenges).  If this delegate message is not implemented, the 
 * behavior will be to use the default handling, which may involve user
 * interaction. 
 */
- (void)URLSession:(NSURLSession *)session didReceiveChallenge:(NSURLAuthenticationChallenge *)challenge
                                             completionHandler:(void (^)(NSURLSessionAuthChallengeDisposition disposition, NSURLCredential *credential))completionHandler;

/* If an application has received an
 * -application:handleEventsForBackgroundURLSession:completionHandler:
 * message, the session delegate will receive this message to indicate
 * that all messages previously enqueued for this session have been
 * delivered.  At this time it is safe to invoke the previously stored
 * completion handler, or to begin any internal updates that will
 * result in invoking the completion handler.
 */
- (void)URLSessionDidFinishEventsForBackgroundURLSession:(NSURLSession *)session NS_AVAILABLE_IOS(7_0);

@end

/*
 * Messages related to the operation of a specific task.
 */
@protocol NSURLSessionTaskDelegate <NSURLSessionDelegate>
@optional

/* An HTTP request is attempting to perform a redirection to a different
 * URL. You must invoke the completion routine to allow the
 * redirection, allow the redirection with a modified request, or
 * pass nil to the completionHandler to cause the body of the redirection 
 * response to be delivered as the payload of this request. The default
 * is to follow redirections. 
 *
 * For tasks in background sessions, redirections will always be followed and this method will not be called.
 */
- (void)URLSession:(NSURLSession *)session task:(NSURLSessionTask *)task
                     willPerformHTTPRedirection:(NSHTTPURLResponse *)response
                                     newRequest:(NSURLRequest *)request
                              completionHandler:(void (^)(NSURLRequest *))completionHandler;

/* The task has received a request specific authentication challenge.
 * If this delegate is not implemented, the session specific authentication challenge
 * will *NOT* be called and the behavior will be the same as using the default handling
 * disposition. 
 */
- (void)URLSession:(NSURLSession *)session task:(NSURLSessionTask *)task
                            didReceiveChallenge:(NSURLAuthenticationChallenge *)challenge 
                              completionHandler:(void (^)(NSURLSessionAuthChallengeDisposition disposition, NSURLCredential *credential))completionHandler;

/* Sent if a task requires a new, unopened body stream.  This may be
 * necessary when authentication has failed for any request that
 * involves a body stream. 
 */
- (void)URLSession:(NSURLSession *)session task:(NSURLSessionTask *)task
                              needNewBodyStream:(void (^)(NSInputStream *bodyStream))completionHandler;

/* Sent periodically to notify the delegate of upload progress.  This
 * information is also available as properties of the task.
 */
- (void)URLSession:(NSURLSession *)session task:(NSURLSessionTask *)task
                                didSendBodyData:(int64_t)bytesSent
                                 totalBytesSent:(int64_t)totalBytesSent
                       totalBytesExpectedToSend:(int64_t)totalBytesExpectedToSend;

/* Sent as the last message related to a specific task.  Error may be
 * nil, which implies that no error occurred and this task is complete. 
 */
- (void)URLSession:(NSURLSession *)session task:(NSURLSessionTask *)task
                           didCompleteWithError:(NSError *)error;

@end

/*
 * Messages related to the operation of a task that delivers data
 * directly to the delegate.
 */
@protocol NSURLSessionDataDelegate <NSURLSessionTaskDelegate>
@optional
/* The task has received a response and no further messages will be
 * received until the completion block is called. The disposition
 * allows you to cancel a request or to turn a data task into a
 * download task. This delegate message is optional - if you do not
 * implement it, you can get the response as a property of the task.
 *
 * This method will not be called for background upload tasks (which cannot be converted to download tasks).
 */
- (void)URLSession:(NSURLSession *)session dataTask:(NSURLSessionDataTask *)dataTask
                                 didReceiveResponse:(NSURLResponse *)response
                                  completionHandler:(void (^)(NSURLSessionResponseDisposition disposition))completionHandler;

/* Notification that a data task has become a download task.  No
 * future messages will be sent to the data task.
 */
- (void)URLSession:(NSURLSession *)session dataTask:(NSURLSessionDataTask *)dataTask
                              didBecomeDownloadTask:(NSURLSessionDownloadTask *)downloadTask;

/* Sent when data is available for the delegate to consume.  It is
 * assumed that the delegate will retain and not copy the data.  As
 * the data may be discontiguous, you should use 
 * [NSData enumerateByteRangesUsingBlock:] to access it.
 */
- (void)URLSession:(NSURLSession *)session dataTask:(NSURLSessionDataTask *)dataTask
                                     didReceiveData:(NSData *)data;

/* Invoke the completion routine with a valid NSCachedURLResponse to
 * allow the resulting data to be cached, or pass nil to prevent
 * caching. Note that there is no guarantee that caching will be
 * attempted for a given resource, and you should not rely on this
 * message to receive the resource data.
 */
- (void)URLSession:(NSURLSession *)session dataTask:(NSURLSessionDataTask *)dataTask
                                  willCacheResponse:(NSCachedURLResponse *)proposedResponse 
                                  completionHandler:(void (^)(NSCachedURLResponse *cachedResponse))completionHandler;

@end

/*
 * Messages related to the operation of a task that writes data to a
 * file and notifies the delegate upon completion.
 */
@protocol NSURLSessionDownloadDelegate <NSURLSessionTaskDelegate>

/* Sent when a download task that has completed a download.  The delegate should 
 * copy or move the file at the given location to a new location as it will be 
 * removed when the delegate message returns. URLSession:task:didCompleteWithError: will
 * still be called.
 */
- (void)URLSession:(NSURLSession *)session downloadTask:(NSURLSessionDownloadTask *)downloadTask
                              didFinishDownloadingToURL:(NSURL *)location;

@optional
/* Sent periodically to notify the delegate of download progress. */
- (void)URLSession:(NSURLSession *)session downloadTask:(NSURLSessionDownloadTask *)downloadTask
                                           didWriteData:(int64_t)bytesWritten
                                      totalBytesWritten:(int64_t)totalBytesWritten
                              totalBytesExpectedToWrite:(int64_t)totalBytesExpectedToWrite;

/* Sent when a download has been resumed. If a download failed with an
 * error, the -userInfo dictionary of the error will contain an
 * NSURLSessionDownloadTaskResumeData key, whose value is the resume
 * data. 
 */
- (void)URLSession:(NSURLSession *)session downloadTask:(NSURLSessionDownloadTask *)downloadTask
                                      didResumeAtOffset:(int64_t)fileOffset
                                     expectedTotalBytes:(int64_t)expectedTotalBytes;

@end

/* Key in the userInfo dictionary of an NSError received during a failed download. */
FOUNDATION_EXPORT NSString * const NSURLSessionDownloadTaskResumeData NS_AVAILABLE(NSURLSESSION_AVAILABLE, 7_0);

/*
 * These methods will be removed.
 */
@interface NSURLSession (NSURLSessionDeprecated)

/* Use -dataTaskWithURL: instead */
- (NSURLSessionDataTask *)dataTaskWithHTTPGetRequest:(NSURL *)url NS_DEPRECATED(NSURLSESSION_AVAILABLE, NSURLSESSION_AVAILABLE, 7_0, 7_0);

/* Use -dataTaskWithURL:completionHandler: instead */
- (NSURLSessionDataTask *)dataTaskWithHTTPGetRequest:(NSURL *)url completionHandler:(void (^)(NSData *data, NSURLResponse *response, NSError *error))completionHandler NS_DEPRECATED(NSURLSESSION_AVAILABLE, NSURLSESSION_AVAILABLE, 7_0, 7_0);
@end

@interface NSURLSessionConfiguration (NSURLSessionDeprecated)
+ (NSURLSessionConfiguration *)backgroundSessionConfiguration:(NSString *)identifier NS_DEPRECATED(NSURLSESSION_AVAILABLE, 10_10, 7_0, 8_0, "Please use backgroundSessionConfigurationWithIdentifier: instead");
@end

