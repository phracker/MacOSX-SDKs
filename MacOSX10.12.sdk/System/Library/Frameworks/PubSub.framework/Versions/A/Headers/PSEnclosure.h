/*
    PSEnclosure.h
    PubSub

    Copyright 2006, Apple Computer, Inc.  All rights reserved.
*/


#import <Foundation/NSObject.h>
@class NSString;
@class NSData;
@class NSURL;
@class NSError;


#if MAC_OS_X_VERSION_10_5 <= MAC_OS_X_VERSION_MAX_ALLOWED

@class PSEntry;


/*!
    @class      PSEnclosure
    @discussion A <code>PSEnclosure</code> object contains a link to an external resource such as a sound or image file  
                associated with an entry. An enclosure is similar to an attachment 
                in an email, but rather than include the file itself in the entry, only a link is provided. Each enclosure
                object is linked to a entry object.
                
                An enclosure object provides properties for retrieving information about the enclosure, such as its URL, length,
                and MIME type, as well as methods to download the file linked to in the enclosure. Invoke the <code>download:</code> method to
                begin downloading the enclosure's file. To check on the status of the download, register for the
                <code>PSEnclosureDownloadStateDidChangeNotification</code> notification. It is not recommended that you subclass <code>PSEnclosure</code>.
    @attribute 	Framework /System/Library/Frameworks/PubSub.framework
    @seealso 	//apple_ref/doc/uid/TP40004945 Publication Subscription Programming Guide
*/

NS_DEPRECATED(10_5, 10_9, NA, NA)
@interface PSEnclosure : NSObject {
    @private
    id _internal;
}


/*!
    @method     entry
    @abstract   The entry with which the enclosure is linked. (read-only)
    @discussion The inverse of the <code>enclosures</code> property of the <code>PSEntry</code> class.
                An enclosure follows a one-to-one relationship and can only be linked to a single entry. 

                This method attempts to communicate with the PubSubAgent process and causes the agent 
                to launch if it is not already running.  If PubSubAgent cannot be contacted, an exception 
                will be thrown with the name <code>PSException</code>.  To avoid problems, you should 
                always be prepared to catch an exception thrown by this method.
    @result     The entry associated with the enclosure.
*/
@property (readonly) PSEntry* entry;


/*! @property URL 
    @abstract A URL to the enclosure's location. (read-only) 
    @discussion The return value corresponds to the <code>'href'</code> attribute of the <link rel="enclosure"> element in Atom and to the <code>'url'</code> attribute of the <enclosure> element in RSS. */
@property (readonly, retain) NSURL * URL;


/*! @property MIMEType 
    @abstract The MIME type of the enclosure. (read-only) 
    @discussion The MIME type corresponds to the <code>'type'</code> attribute of the <link rel="enclosure"> element in Atom and to the <code>'type'</code> attribute of the <enclosure> element in RSS. */
@property (readonly, retain) NSString * MIMEType;



/*!
    @method     length
    @abstract   The length of the file in the enclosure. (read-only)
    @discussion The return value is initially parsed from the length attribute of a <link rel="enclosure"> element
                in Atom and the length attribute of <enclosure> in RSS.
                If this attribute does not exist in the feed, the return value is <code>0</code>.
                The value may change after downloading begins and the true length is
                received from the server.
    @result     The length, in bytes, of the file in the enclosure.
*/
@property (readonly) long long length;


typedef enum {
    PSEnclosureDownloadIsIdle NS_ENUM_DEPRECATED(10_5, 10_9, NA, NA),       // A download has not been requested
    PSEnclosureDownloadIsQueued NS_ENUM_DEPRECATED(10_5, 10_9, NA, NA),     // A download will commence sometime in the future 
    PSEnclosureDownloadIsActive NS_ENUM_DEPRECATED(10_5, 10_9, NA, NA),     // A download is currently active (check downloadProgress)
    PSEnclosureDownloadDidFinish NS_ENUM_DEPRECATED(10_5, 10_9, NA, NA),    // A download successfully finish
    PSEnclosureDownloadDidFail NS_ENUM_DEPRECATED(10_5, 10_9, NA, NA),      // A download failed (check downloadError)
    PSEnclosureDownloadWasDeleted NS_ENUM_DEPRECATED(10_5, 10_9, NA, NA)    // A download finished, but another application or the user removed the result
} PSEnclosureDownloadState NS_ENUM_DEPRECATED(10_5, 10_9, NA, NA);

/*
    @method     downloadState
    @abstract   The current state of the download. (read-only)
*/
@property (readonly) PSEnclosureDownloadState downloadState;


/*
    @method     downloadProgress
    @abstract   The fraction of the enclosure that has been downloaded. (read-only)
*/
@property (readonly) double downloadProgress;


/*
    @method     downloadError
    @abstract   The error, if any, from the last download attempt. (read-only)
    @discussion This is cleared to nil when <code>download:</code> is called again.
*/
@property (readonly) NSError * downloadError;


/*!
    @property downloadedPath 
    @abstract The path to the downloaded enclosure. (read-only)
    @discussion The method returns <code>nil</code> unless the download has completed.
*/
@property (readonly) NSString * downloadedPath;


/*
    @method     download:
    @abstract   Requests that the enclosure be downloaded.
    @discussion Downloading is an asynchronous operation so this method does not block. Because the operation is
                performed asynchronously, errors are more likely to show up later during the download then when the download is started.
                These can be accessed via the enclosure's <code>downloadError</code> property.
                If a download is currently in progress, this has no effect.
                If the enclosure has already been downloaded, this will re-download it if it's changed.
    @result     YES if the download begins, NO if the download cannot be started. If this method returns NO, the <code>error</code> 
                parameter is also set.
*/
- (BOOL) download: (NSError**)error;


/*
    @method     cancelDownload
    @abstract   Cancels any download currently in progress.
*/
- (void) cancelDownload;


/*
    @method     deleteDownload
    @abstract   Deletes the downloaded file located at <code>downloadedPath</code>.
*/
- (void) deleteDownload;


@end

extern NSString* const PSEnclosureDownloadStateDidChangeNotification NS_DEPRECATED(10_5, 10_9, NA, NA);

#endif
