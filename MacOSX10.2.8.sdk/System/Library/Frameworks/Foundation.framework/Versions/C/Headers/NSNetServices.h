/*	NSNetServices.h
        Copyright 2002, Apple, Inc. All rights reserved.
*/

#if MAC_OS_X_VERSION_10_2 <= MAC_OS_X_VERSION_MAX_ALLOWED

#import <Foundation/NSObject.h>

@class NSArray, NSDictionary, NSRunLoop, NSString;

FOUNDATION_EXPORT NSString * const NSNetServicesErrorCode;
FOUNDATION_EXPORT NSString * const NSNetServicesErrorDomain;

typedef enum {
    NSNetServicesUnknownError = -72000,
    NSNetServicesCollisionError = -72001,
    NSNetServicesNotFoundError	= -72002,
    NSNetServicesActivityInProgress = -72003,
    NSNetServicesBadArgumentError = -72004,
    NSNetServicesCancelledError = -72005,
    NSNetServicesInvalidError = -72006
} NSNetServicesError;


@interface NSNetService : NSObject {
@private
    void * _netService;
    id _delegate;
    void * _reserved;
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

//  These methods are provided for older clients to specify and retrieve information that is peculiar to a given protocol. They are primarily here for legacy support of older zeroconf-style clients and their use is discouraged.
- (NSString *)protocolSpecificInformation;
- (void)setProtocolSpecificInformation:(NSString *)specificInformation;

//  Returns an NSArray containing NSDatas, each of which contains a single struct sockaddr suitable for handing off to connect. In the event that no addresses have been resolved, an NSArray containing 0 elements is returned.
- (NSArray *)addresses;

//  publish advertises a given service on the network.  This method returns immediately, with success or failure indicated by the callbacks to the delegate.
- (void)publish;

//  resolve attempts to determine at least one address for a given service. This method returns immediately, with success or failure indicated by the callbacks to the delegate. 
- (void)resolve;

//  stop halts a currently running publish or resolve.
- (void)stop;
@end


@interface NSNetServiceBrowser : NSObject {
@private
    void * _netServiceBrowser;
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

//  Calling searchForAllDomains causes the delegate to receive messages regarding any domain visible to the host.  These may be domains in which it is not possible to register.
- (void)searchForAllDomains;

//  searchForRegistrationDomains causes the delegate to receive netServiceBrowser:didFindDomain: messages, but only with domains which the host may register a service on (i.e. domains which are available to interfaces connected to the computer). To be completely correct, a client publishing a service should search for registration domains first, collect all the registration domains it believes it needs, stop the search, and then register the service on those domains (note that this involves creating a separate NSNetService instance for each domain that the service will be published on).
- (void)searchForRegistrationDomains;

//  This starts a search for services of a specific type within a specific domain.  This will cause netServiceBrowser:foundService:moreComing: messages to be sent to the delegate.
- (void)searchForServicesOfType:(NSString *)type inDomain:(NSString *)domainString;

//  This halts the currently running search or resolution.
- (void)stop;
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

