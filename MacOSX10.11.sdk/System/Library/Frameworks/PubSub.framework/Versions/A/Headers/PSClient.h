/*
    PSClient.h
    PubSub

    Copyright 2006, Apple Computer, Inc.  All rights reserved.
*/


#import <Foundation/NSObject.h>
@class NSArray;
@class NSString;
@class NSDate;
@class NSURL;


#if MAC_OS_X_VERSION_10_5 <= MAC_OS_X_VERSION_MAX_ALLOWED

#import <PubSub/PSEnclosure.h>

@class PSFeed;
@class PSEntry;
@class PSFeedSettings;


/*!
    @class      PSClient
    @discussion A <code>PSClient</code> object represents a client of the API that has its own set of feeds.
                PSClient is the backbone of the Publication Subscription framework.
                To subscribe to feeds, your application must use a client object. You can then
                add feeds to the PubSub Database with the <code>addFeed:</code> and <code>addFeedWithURL:</code> methods.
                Similarly, you can unsubscribe from a feed with the <code>removeFeed:</code> method.
                It is not recommended that you subclass <code>PSClient</code>.
    @attribute 	Framework /System/Library/Frameworks/PubSub.framework
    @seealso 	//apple_ref/doc/uid/TP40004945 Publication Subscription Programming Guide		
*/
NS_DEPRECATED(10_5, 10_9, NA, NA)
@interface PSClient : NSObject 
{
    @private
    id _internal;
}


/*!
    @method   applicationClient
    @abstract Creates the default instance for the current application.
    @result   A client object for the current application.
*/
+ (PSClient*) applicationClient;


/*!
    @method     clientForBundleIdentifier:
    @abstract   Creates a client for the specified bundle identifier.
    @param      bundleIdentifier	The bundle identifier of the client you want to inspect.
    @result     A client object for the specified bundle identifier.
    @discussion This method should be used by applications that want to inspect the subscriptions of other applications
                or by a suite of applications that want to use a shared subscription client. If you need to create a client
                for the current application, use <code>applicationClient</code> instead.
*/
+ (PSClient*) clientForBundleIdentifier:(NSString *)bundleIdentifier;


/*!
    @method     allClientBundleIdentifiers:
    @abstract   Returns a list of the bundle identifiers for the clients that have registered with the PubSub Agent.
    @result     An array of string objects containing the bundle identifiers of the clients registered with the PubSub Agent.
    @discussion This method should be used by applications that want to inspect the subscriptions
                of another application or construct a set of all subscribed
                feeds. However, the results may not be complete, because this method does not
                return the bundle identifiers of private clients.
*/
+ (NSArray*) allClientBundleIdentifiers;


/*!
    @property   settings
    @abstract   The feed settings of the client.
    @discussion If the settings have not been modified, returns the default settings.

                This property attempts to communicate with the PubSubAgent process and causes the agent 
                to launch if it is not already running.  If PubSubAgent cannot be contacted, an exception 
                will be thrown with the name <code>PSException</code>.  To avoid problems, you should 
                always be prepared to catch an exception thrown by this property.
*/
@property (retain) PSFeedSettings * settings;


/*!
    @property   dateLastUpdated
    @abstract   The date and time associated with the most recent feed-change notification delivered to the receiver's delegate.
    @discussion If no notifications have been sent at the time this method was called, it returns the date and time that the receiver
                was created. Because feeds and entries can change when
                a client isn't running, store the value from <code>dateLastUpdated</code> when your application quits, and pass
                that value to <code>sendChangesSinceDate:</code> to retrieve any notifications that would have been called while
                your application was not running.                
*/
@property (readonly) NSDate * dateLastUpdated;


/*!
    @method     sendChangesSinceDate:
    @abstract   Calls the delegate methods and sends the corresponding notifications that would have been called if the client had been running since the specified date.
    @param      dateLastUpdated  The date after which you want changes sent.
    @discussion Some clients may choose to associate their data with various
                Publication Subscription instances.  Since feeds and articles can change when
                a client isn't running, <code>dateLastUpdated</code> and <code>sendChangesSinceDate:</code>
                are needed to maintain a synchronized state. The typical date passed
                to this method is the value that was returned by the <code>dateLastUpdated</code> method just
                before the application quit.
*/
- (void) sendChangesSinceDate:(NSDate *)dateLastUpdated;


/*!
    @method     addFeed:
    @abstract   Subscribes the client to the given feed.
    @param      feed  The existing feed object to subscribe to. 
    @result     <code>YES</code> on success; <code>NO</code> if an immediate error occurred.
    @discussion A feed object may only belong to one client, so if the given feed has already
                been added to any other client, this method will fail. Instead, create
                a new feed object with the same URL as the existing one or use <code>addFeedWithURL:</code>.
*/
- (BOOL) addFeed: (PSFeed*)feed;


/*!
    @method     addFeedWithURL:
    @abstract   Subscribes the client to the feed at the given URL.
    @param      url  The URL of the feed. Must be an <code>HTTP</code>, <code>HTTPS</code>, or <code>FEED</code> protocol.
    @result     The subscribed feed, or <code>nil</code> if an error occurred.
    @discussion This method creates a subscribed feed from the given URL.
                If a feed with this URL is already subscribed, this method returns a feed object from the existing data in the PubSub Database.
*/
- (PSFeed *) addFeedWithURL: (NSURL*)url;


/*!
    @method     removeFeed:
    @abstract   Unsubscribes the client from a feed.
    @param      feed  The feed to be removed.
    @result     <code>YES</code> if the client is unsubscribed; <code>NO</code> if an error occurred.
*/
- (BOOL) removeFeed:(PSFeed *)feed;


/*!
    @method     feedWithURL:
    @abstract   Returns the subscribed feed with the given URL.
    @param url  The URL of the feed.
    @result     The feed from the given URL.
*/
- (PSFeed *) feedWithURL: (NSURL*)url;


/*!
    @property   feeds
    @abstract   An array of all the feeds subscribed to by the client.
    @discussion The ordering of the feeds in the array is undefined.
*/
@property (readonly) NSArray * feeds;


/*!
    @method     feedWithIdentifier:
    @abstract   Returns the feed with the specified identifier.
    @param      identifier  The unique string associated with a feed.
    @result     The feed associated with the specified identifier, or <code>nil</code> if the client isn't subscribed to the feed associated with this identifier.
    @discussion Feed identifiers are persistent, unique, and unchangeable, so they provide a way for your application
                to establish a persistent reference to an feed.
                This method considers only feeds subscribed to by this client.
*/
- (PSFeed *) feedWithIdentifier: (NSString*)identifier;


/*!
    @method     entryWithIdentifier:
    @abstract   Returns the entry with the given identifier.
    @param      identifier  The unique string associated with a entry.
    @result     The entry associated with the specified identifier, or <code>nil</code> if the identifier is not in a subscribed feed.
    @discussion Entry identifiers are persistent, unique, and unchangeable, so they provide a way for your application
                to establish a persistent reference to an entry.
                This method considers only entries in feeds subscribed to by this client.
*/
- (PSEntry *) entryWithIdentifier: (NSString*)identifier;


/*! @property signature 
    @abstract The application bundle identifier associated with the <code>PSClient</code> instance. 
    @discussion  */
@property (readonly, retain) NSString * signature;


/*! @property isPrivate 
    @abstract A Boolean value that indicates whether the client instance is private. 
    @discussion A private <code>PSClient</code> instance can be accessed only by an application process whose bundle identifier matches the signature of the <code>PSClient</code>. */
@property (getter=isPrivate, setter=setPrivate:) BOOL isPrivate;



/*!
    @property   delegate
    @abstract   The delegate of the client.
    @discussion The delegate should implement the <code>PSClientDelegate</code> informal protocol.
*/
@property (assign) id delegate;

@end


@interface NSObject (PSClientDelegate)

- (void) feedDidBeginRefresh:(PSFeed *)feed;
- (void) feedDidEndRefresh:(PSFeed *)feed;

- (void) feed:(PSFeed *)feed didAddEntries:(NSArray *)entries;
- (void) feed:(PSFeed *)feed didRemoveEntriesWithIdentifiers:(NSArray *)identifiers;
- (void) feed:(PSFeed *)feed didUpdateEntries:(NSArray *)entries;
- (void) feed:(PSFeed *)feed didChangeFlagsInEntries:(NSArray *)entries;

- (void) enclosure:(PSEnclosure *)enclosure downloadStateDidChange:(PSEnclosureDownloadState)state;

@end

#endif
