/*	NSNetServices.h
        Copyright (c) 2002-2005, Apple, Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSDate.h>

#if MAC_OS_X_VERSION_10_2 <= MAC_OS_X_VERSION_MAX_ALLOWED

@class NSArray, NSData, NSDictionary, NSInputStream, NSOutputStream, NSRunLoop, NSString;

FOUNDATION_EXPORT NSString * const NSNetServicesErrorCode;
FOUNDATION_EXPORT NSString * const NSNetServicesErrorDomain;

typedef enum {
    NSNetServicesUnknownError = -72000,
    NSNetServicesCollisionError = -72001,
    NSNetServicesNotFoundError	= -72002,
    NSNetServicesActivityInProgress = -72003,
    NSNetServicesBadArgumentError = -72004,
    NSNetServicesCancelledError = -72005,
    NSNetServicesInvalidError = -72006,
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
    NSNetServicesTimeoutError = -72007,
#endif
} NSNetServicesError;


@interface NSNetService : NSObject {
@private
    id _netService;
    id _delegate;
    id * _reserved;
}

//  Designated initializer
//  This is the "publishing appropriate" initializer. Use this initializer if you wish to publish service availability on the network.
- (id)initWithDomain:(NSString *)domain type:(NSString *)type name:(NSString *)name port:(int)port;

//  This is the "resolution appropriate" initializer. If you know the domain, type, and name of the service you wish to connect to, you can instantiate an NSNetService using this initializer and call resolve: on the result. This initializer passes an invalid port number on to the designated initializer. In the event that publish: is called on an NSNetService initialized with this method, an NSNetServicesBadArgumentError will be sent in the error dictionary to your delegate's netService:didNotPublish: method.
- (id)initWithDomain:(NSString *)domain type:(NSString *)type name:(NSString *)name;

//  Delegation methods
//  The delegate is not retained.
- (id)delegate;
- (void)setDelegate:(id)delegate;

//  Run loop maintenance
//  Although it is possible to remove an NSNetService completely from any run loops and then attempt actions on them, it is an error to do so - this is a completely asynchronous API.
- (void)scheduleInRunLoop:(NSRunLoop *)aRunLoop forMode:(NSString *)mode;
- (void)removeFromRunLoop:(NSRunLoop *)aRunLoop forMode:(NSString *)mode;

//  Accessor methods for service
- (NSString *)domain;
- (NSString *)type;
- (NSString *)name;

//  Returns an NSArray containing NSDatas, each of which contains a single struct sockaddr suitable for handing off to connect. In the event that no addresses have been resolved, an NSArray containing 0 elements is returned.
- (NSArray *)addresses;

//  publish advertises a given service on the network.  This method returns immediately, with success or failure indicated by the callbacks to the delegate.
- (void)publish;

//  stop halts a currently running publish or resolve.
- (void)stop;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
//  getInputStream:outputStream: retrieves streams from the NSNetService object directly. Your delegate callbacks (if available) will not be called. Returns YES if the streams requested are created successfully. Returns NO if for any reason the stream could not be created.
- (BOOL)getInputStream:(NSInputStream **)inputStream outputStream:(NSOutputStream **)outputStream;

//  starts a resolve for the NSNetService of a finite duration. If your delegate is called before the timeout expires, the resolve can be considered successful. If the resolve times out, your netService:didNotResolve: callback will be called with the appropriate error dictionary.
- (void)resolveWithTimeout:(NSTimeInterval)timeout;

//  Allows the developer to use an NSData containing arbitrary bytes as the TXT record. Returns YES if the data is successfully set as the TXT record. Returns NO if it cannot be set.
- (BOOL)setTXTRecordData:(NSData *)recordData;
- (NSData *)TXTRecordData;

//  These calls control whether an NSNetService will watch for TXT record updates, notification of which would be delivered to the delegate on the netServiceDidUpdateTXTRecord: method in the NSNetServiceDelegateMethods category.
- (void)startMonitoring;
- (void)stopMonitoring;

//  Applications may wish to know the host name of the computer offering the remote service. This method will return the host name of the machine or nil if a successful resolve has not yet occurred.
- (NSString *)hostName;

//  TXT record data can be presented either as an NSData or an NSDictionary of key-value pairs. It's very useful to be able to convert between the two. NSNetService provides a pair of class methods to do this conversion. Each returns nil in the event that the conversion cannot take place.
//  It's important to note that these routines are not general archiving/plist flattening routines. The keys are expressed as NSStrings in UTF8 encoding, and the values are NSDatas. The caller is responsible for interpreting these as the types appropriate to the keys.
+ (NSDictionary *)dictionaryFromTXTRecordData:(NSData *)txtData;
+ (NSData *)dataFromTXTRecordDictionary:(NSDictionary *)txtDictionary;
#endif

@end

@interface NSNetService (NSDeprecated)

//  These methods are provided for clients to specify and retrieve information that is peculiar to a given protocol.
//  -protocolSpecificInformation returns nil if a resolve has not been performed or if setProtocolSpecificInformation has not been called.
//  In Mac OS X 10.4 "Tiger" these methods are deprecated in favor of the setTXTRecordData variant above.
- (NSString *)protocolSpecificInformation;
- (void)setProtocolSpecificInformation:(NSString *)specificInformation;

//  resolve attempts to determine at least one address for a given service. This method returns immediately, with success or failure indicated by the callbacks to the delegate.
//  In Mac OS X 10.4 "Tiger", this call is deprecated in favor of -resolveWithTimeout: in order to reduce the amount of network traffic on the local link.
- (void)resolve;

@end

@interface NSNetServiceBrowser : NSObject {
@private
    id _netServiceBrowser;
    id _delegate;
    void * _reserved;
}

//  Initializer
- (id)init;

//  delegation.  The delegate is not retained.
- (id)delegate;
- (void)setDelegate:(id)delegate;

//  Run loop maintenance
- (void)scheduleInRunLoop:(NSRunLoop *)aRunLoop forMode:(NSString *)mode;
- (void)removeFromRunLoop:(NSRunLoop *)aRunLoop forMode:(NSString *)mode;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
//  searchForBrowsableDomains causes the delegate to receive netServiceBrowser:didFindDomain: messages, but only with domains which the host is able to see based on network configuration. There may be more than one browsable domain, and the delgate will receive a netServiceBrowser:didFindDomain: message for each.
- (void)searchForBrowsableDomains;
#endif

//  searchForRegistrationDomains causes the delegate to receive netServiceBrowser:didFindDomain: messages, but only with domains which the host may register a service on (i.e. domains which are available to interfaces connected to the computer). To be completely correct, a client publishing a service should search for registration domains first, collect all the registration domains it believes it needs, stop the search, and then register the service on those domains (note that this involves creating a separate NSNetService instance for each domain that the service will be published on).
- (void)searchForRegistrationDomains;

//  This starts a search for services of a specific type within a specific domain.  This will cause netServiceBrowser:foundService:moreComing: messages to be sent to the delegate.
- (void)searchForServicesOfType:(NSString *)type inDomain:(NSString *)domainString;

//  This halts the currently running search or resolution.
- (void)stop;
@end

@interface NSNetServiceBrowser (NSDeprecated)

//  Calling searchForAllDomains causes the delegate to receive messages regarding any domain visible to the host.  These may be domains in which it is not possible to register. This method is deprecated as of Mac OS X 10.4 "Tiger". Clients should use -searchForBrowsableDomains or -searchForRegistrationDomains.
- (void)searchForAllDomains;

@end


@interface NSObject (NSNetServiceDelegateMethods)
//  Called to notify the delegate object that the publishing was able to start successfully. The delegate will not receive this message if the underlying network layer was not ready to begin a publication.
- (void)netServiceWillPublish:(NSNetService *)sender;

//  Called to notify the delegate object that the resolution was able to start successfully.
- (void)netServiceWillResolve:(NSNetService *)sender;

//  Called to notify the delegate object that an error occurred, supplying a numeric error code. This may be called long after a netServiceWillPublish: message has been delivered to the delegate.
- (void)netService:(NSNetService *)sender didNotPublish:(NSDictionary *)errorDict;

//  Called to inform the delegate that an address was resolved.  The delegate should use [aNetService addresses] to find out what the addresses may be in order to connect to the discovered service. The NSNetService may get resolved more than once - a DNS rotary may yield different IP addresses on different resolution requests.  Truly robust clients may wish resolve again on error, or resolve more than once.
- (void)netServiceDidResolveAddress:(NSNetService *)sender;

//  Called to inform the delegate that an error occurred during resolution of a given NSNetService.
- (void)netService:(NSNetService *)sender didNotResolve:(NSDictionary *)errorDict;

//  Called to inform the delegate that a previously running publication or resolution request has been stopped.
- (void)netServiceDidStop:(NSNetService *)sender;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
//  Called to inform the delegate that the TXT record associated with the sending NSNetService object has updated.
- (void)netService:(NSNetService *)sender didUpdateTXTRecordData:(NSData *)data;

//  Called to inform the delegate that the NSNetService was successfully published
- (void)netServiceDidPublish:(NSNetService *)sender;
#endif
@end


@interface NSObject (NSNetServiceBrowserDelegateMethods)
//  Each time the service is about to try to search, the delegate will receive this message. The delegate will not receive this message if the underlying network layer was not in a state to begin a search. In this case, the delegate will receive the netServiceBrowser:didNotSearch: message.
- (void)netServiceBrowserWillSearch:(NSNetServiceBrowser *)aNetServiceBrowser;

//  Each time the NSNetServiceBrowser finds a domain it sends one of these messages to its delegate.  Presumably the delegate will accumulate these on behalf of something that will be displaying them to the user for a choice to be made.
- (void)netServiceBrowser:(NSNetServiceBrowser *)aNetServiceBrowser didFindDomain:(NSString *)domainString moreComing:(BOOL)moreComing;

 //  For service searching:
- (void)netServiceBrowser:(NSNetServiceBrowser *)aNetServiceBrowser didFindService:(NSNetService *)aNetService moreComing:(BOOL)moreComing;

//  For determining reasons for not being able to search:
- (void)netServiceBrowser:(NSNetServiceBrowser *)aNetServiceBrowser didNotSearch:(NSDictionary *)errorDict;

//  Called when the NSNetServiceBrowser has been told to stop searching.
- (void)netServiceBrowserDidStopSearch:(NSNetServiceBrowser *)aNetServiceBrowser;

- (void)netServiceBrowser:(NSNetServiceBrowser *)aNetServiceBrowser didRemoveDomain:(NSString *)domainString moreComing:(BOOL)moreComing;

- (void)netServiceBrowser:(NSNetServiceBrowser *)aNetServiceBrowser didRemoveService:(NSNetService *)aNetService moreComing:(BOOL)moreComing;
@end

#endif

