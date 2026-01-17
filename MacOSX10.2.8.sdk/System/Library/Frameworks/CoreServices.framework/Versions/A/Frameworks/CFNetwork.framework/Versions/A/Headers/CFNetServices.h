/*
 *  CFNetServices.h
 *  CFNetwork
 *
 *  Copyright (c) 2002 Apple Computer, Inc. All rights reserved.
 *
 */

#ifndef __CFNETSERVICES__
#define __CFNETSERVICES__


#include <CoreFoundation/CFBase.h>
#include <CoreFoundation/CFStream.h>


#if defined(__cplusplus)
extern "C" {
#endif


/*
Network Services is composed of two objects, a Network Service and a Network Service Browser.  A Network
Service represents a single point service on the network.  Associated with a service is its name, type of
service, domain, port, and possibly protocol specific information (for legacy protocols).  Services can be
registered and resolved.  Registering a service advertises the service on the network, so other computers
can use the service.  Resolving a service performs a network lookup in order to find the computer which has
registered the service.  Lookup is contained by the services name, type of service, and the domain.  The
port and address of the registered service will be returned.  Services can be created or discovered.

Discovery of services takes place through the use of the Network Service Browser.  Given a domain and a
service type, the browser will search out those services on the network.  The returned services can then be
resolved and then used.

Service type values are keywords as registered with IANA.  A list of values may be retrieved from their
web site at <http://www.iana.org/assignments/port-numbers>.
*/


CF_EXPORT 
const SInt32 kCFStreamErrorDomainNetServices;

CF_EXPORT
const SInt32 kCFStreamErrorDomainMach;			/* Errors reported by mach.  See <mach/error.h> */


typedef enum {
    kCFNetServicesErrorUnknown		= -72000,
	kCFNetServicesErrorCollision	= -72001,
	kCFNetServicesErrorNotFound		= -72002,
	kCFNetServicesErrorInProgress	= -72003,
	kCFNetServicesErrorBadArgument	= -72004,
    kCFNetServicesErrorCancel		= -72005,
    kCFNetServicesErrorInvalid		= -72006
} CFNetServicesError;


/* Result bit flags passed to CFNetServiceBrowserClientCallBack */
enum {
	kCFNetServiceFlagMoreComing				= 1,	/* Client will get another callback briefly and shouldn't do costly screen updates (or such) */
	kCFNetServiceFlagIsDomain				= 2,	/* Result is a domain.  If off, the result is a service. */
	kCFNetServiceFlagIsRegistrationDomain	= 4,	/* The result domain is the default registration domain. */
    kCFNetServiceFlagRemove					= 8		/* The result item should be removed and not added. */
};


typedef struct {
    CFIndex version;
    void *info;
    void *(*retain)(void *info);
    void (*release)(void *info);
    CFStringRef (*copyDescription)(void *info);
} CFNetServiceClientContext;


typedef struct __CFNetService* CFNetServiceRef;
typedef void (*CFNetServiceClientCallBack)(CFNetServiceRef theService, CFStreamError* error, void* info);

typedef struct __CFNetServiceBrowser* CFNetServiceBrowserRef;
typedef void (*CFNetServiceBrowserClientCallBack)(CFNetServiceBrowserRef browser, CFOptionFlags flags, CFTypeRef domainOrService, CFStreamError* error, void* info);


CF_EXPORT
CFTypeID CFNetServiceGetTypeID(void);

CF_EXPORT
CFTypeID CFNetServiceBrowserGetTypeID(void);


/*
** CFNetServiceCreate
**
** Creates an instance of a Network Service.  Returns NULL on failure.
**
** alloc The CFAllocator which should be used to allocate memory for the service and its storage for
**		values. If this reference is not a valid CFAllocator, the behavior is undefined.
**
** domain The network domain in which it is registered or will be registered.  This value must be non-NULL.
**
** type The type of service being registered or resolved on the network.  This value must be non-NULL.
**
** name The name of the machine or application advertising the service.  If this value is not unique,
**		registering will eventually fail.  This value must be non-NULL.  This value is usually displayed in
**		a browser for the user.
**
** port The port on which the service is listening.  This must be non-zero for services which are to be
**		registered.
*/
CF_EXPORT
CFNetServiceRef CFNetServiceCreate(CFAllocatorRef	alloc,
								   CFStringRef		domain,
								   CFStringRef		type,
								   CFStringRef		name,
								   UInt32			port);


/*
** CFNetServiceGetDomain
**
** Query a Network Service for its domain.
**
** theService The Network Service to be queried.  Must be non-NULL.
*/
CF_EXPORT
CFStringRef CFNetServiceGetDomain(CFNetServiceRef theService);


/*
** CFNetServiceGetType
**
** Query a Network Service for its type.
**
** theService The Network Service to be queried.  Must be non-NULL.
*/
CF_EXPORT
CFStringRef CFNetServiceGetType(CFNetServiceRef theService);


/*
** CFNetServiceGetName
**
** Query a Network Service for its name.
**
** theService The Network Service to be queried.  Must be non-NULL.
*/
CF_EXPORT
CFStringRef CFNetServiceGetName(CFNetServiceRef theService);


/*
** CFNetServiceGetAddressing
**
** Query a Network Service for its addressing.  Returns NULL if the entity's addressing is not known (has
** not been resolved).  The array will contain a CFDataRef for each address resolved.  Each CFDataRef
** contains a struct sockaddr representing the address of the service.
**
** theService The Network Service to be queried.  Must be non-NULL.
*/
CF_EXPORT
CFArrayRef CFNetServiceGetAddressing(CFNetServiceRef theService);


/*
** CFNetServiceGetProtocolSpecificInformation
**
** Query a Network Service for its protocol specific information.  Returns NULL if there is no information.
** This field is primarily for legacy protocols which implement an extra level of ports or queues on an
** individual connection.  The use of this field is not suggested.
**
** theService The Network Service to be queried.  Must be non-NULL.
*/
CF_EXPORT
CFStringRef CFNetServiceGetProtocolSpecificInformation(CFNetServiceRef theService);


/*
** CFNetServiceSetProtocolSpecificInformation
**
** Set a Network Service's protocol specific information.  This field is primarily for legacy protocols
** which implement an extra level of ports or queues on an individual connection.  The use of this field is
** not suggested.
**
** theService The Network Service to be queried.  Must be non-NULL.
**
** theInfo The protocol specific information to be added.  Pass NULL to remove the information from the
**		service.
*/
CF_EXPORT
void CFNetServiceSetProtocolSpecificInformation(CFNetServiceRef theService, CFStringRef theInfo);


/*
** CFNetServiceRegister
**
** Registers the entity on the network.  This requires that the service has a domain, a type, a name, and
** an address.  If any of these are NULL, it will return FALSE.  The service is registered on the network
** until this function returns or is cancelled by calling CFNetServiceCancel.
**
** In synchronous mode, this function will block until there is an error, at which time it will return
** FALSE.  It will never return TRUE.
**
** In asynchronous mode, this function returns TRUE if the service contains all of the required attributes
** and the underlying network registration process can start.  It will return FALSE otherwise.
**
** theService The Network Service to register on the network.  Must be non-NULL.
**
** error A reference to an error struct which will be set to the error and domain of the error should one
**		occur.  If the value of error is not desired, set to NULL.
*/
CF_EXPORT
Boolean CFNetServiceRegister(CFNetServiceRef theService, CFStreamError* error);


/*
** CFNetServiceResolve
**
** Resolves the addressing for the given service.  This requires that the service has a domain, a type, and
** a name.  If any of these are NULL, it will return FALSE.
**
** In synchronous mode, this function blocks until the lookup fails, the lookup produces at least one
** result, or the lookup is cancelled by calling CFNetServiceCancel.  If lookup fails, FALSE is returned. 
** If lookup succeeds, TRUE is returned and the service's addressing will be set.
**
** In asynchronous mode, this function will return TRUE immediately if all the required attributes and
** underlying network lookup process can start.  It will return FALSE otherwise.
**
** theService The Network Service to resolve on the network.  Must be non-NULL.
**
** error A reference to an error struct which will be set to the error and domain of the error should one
**		occur.  If the value of error is not desired, set to NULL.
*/
CF_EXPORT
Boolean CFNetServiceResolve(CFNetServiceRef theService, CFStreamError* error);


/*
** CFNetServiceCancel
**
** Cancels an outstanding request for registration or resolution.
**
** theService The Network Service which is active.  Must be non-NULL.
*/
CF_EXPORT
void CFNetServiceCancel(CFNetServiceRef theService);


/*
** CFNetServiceSetClient
**
** Sets up the service to be used in asynchronous mode.  Notification of registration failure or resolution
** completion will occur through the given callback.  Once the client is set, the service must be scheduled
** on a runloop.  The client callback will be triggered via one of the scheduled run loops; It is the
** caller's responsibility to ensure that at least one of the scheduled run loops is being run.
**
** This call must be performed before calling CFNetServiceRegister or CFNetServiceResolve, otherwise it
** will return FALSE.  TRUE will be returned if the client could be set.
**
** theService The service to set up for asynchronous mode.  Must be non-NULL.
**
** clientCB Function pointer will be called upon registration failure or upon resolution completion.  In
**		the case of resolution, this callback may be called multiple times if there is more than one
**		address for a service.  Passing NULL will remove the client from the entity and cancel any
**		outstanding activity.
**
** clientContext Client contextual information to be used when calling clientCB.  Must be non-NULL.
*/
CF_EXPORT
Boolean CFNetServiceSetClient(CFNetServiceRef				theService,
							  CFNetServiceClientCallBack	clientCB,
							  CFNetServiceClientContext*	clientContext);


/*
** CFNetServiceScheduleWithRunLoop
**
** Schedule the given service on the given run loop and mode.
**
** theService The service which is set up for asynchronous mode.  Must be non-NULL.
**
** runLoop A reference to a runloop on which the service should be scheduled.  Must be non-NULL.
**
** runLoopMode The mode on which to schedule the service.  Must be non-NULL.
*/
CF_EXPORT
void CFNetServiceScheduleWithRunLoop(CFNetServiceRef	theService,
									 CFRunLoopRef		runLoop,
									 CFStringRef		runLoopMode);


/*
** CFNetServiceUnscheduleFromRunLoop
**
** Unschedule the given service from the given run loop and mode.
**
** theService The service which is set up for asynchronous mode.  Must be non-NULL.
**
** runLoop A reference to a runloop from which the service should be unscheduled.  Must be non-NULL.
**
** runLoopMode The mode from which to unschedule the service.  Must be non-NULL.
*/
CF_EXPORT
void CFNetServiceUnscheduleFromRunLoop(CFNetServiceRef	theService,
									   CFRunLoopRef		runLoop,
									   CFStringRef		runLoopMode);


/*
** CFNetServiceBrowserCreate
**
** Creates an instance of a browser object.  Returns NULL if the instance could not be created.
**
** alloc The CFAllocator which should be used to allocate memory for the browser and its storage for
**		values. If this reference is not a valid CFAllocator, the behavior is undefined.
**
** clientCB Function pointer that will be called as domains or services are found on the network.  Must be
**		non-NULL.
**
** clientContext Client ontextual information to be used when calling clientCB.  Must be non-NULL.
*/
CF_EXPORT
CFNetServiceBrowserRef CFNetServiceBrowserCreate(CFAllocatorRef						alloc,
												 CFNetServiceBrowserClientCallBack	clientCB,
												 CFNetServiceClientContext*			clientContext);


/*
** CFNetServiceBrowserInvalidate
**
** Invalidates the given browser object so that it may no longer be scheduled and callback never be called. **		This will also stop any searches currently in progress.
**
** browser Network Service Browser to invalidate.  Must be non-NULL.
*/
CF_EXPORT
void CFNetServiceBrowserInvalidate(CFNetServiceBrowserRef browser);


/*
** CFNetServiceBrowserSearchForDomains
**
** Starts a search for domains.  The browser will either try to find all domains or will search for just
** registration domains.  If there is already an outstanding search, it will return FALSE.
**
** In syncronous mode, this call blocks until the search is stopped.  It will return FALSE if there is an
** error performing the search.  It will return TRUE otherwise.
**
** In asynchronous mode, this call will return TRUE or FALSE depending if the underlying network search
** could be started.
**
** browser Network Service Browser to perform the search.  Must be non-NULL.
**
** registrationDomains FALSE if all domains wished to be discovered. TRUE if only registration domains are
**		to be discovered.
**
** error A reference to an error struct which will be set to the error and domain of the error should one
**		occur.  If the value of error is not desired, set to NULL.
*/
CF_EXPORT
Boolean CFNetServiceBrowserSearchForDomains(CFNetServiceBrowserRef	browser,
											Boolean					registrationDomains,
                                            CFStreamError* 			error);


/*
** CFNetServiceBrowserSearchForServices
**
** Starts a search for a service type on the given domain.  If there is already an outstanding search, it
** will return FALSE.
**
** In syncronous mode, this call blocks until the search is stopped.  It will return FALSE if there is an
** error performing the search or if there is some other error.  It will return TRUE otherwise.
**
** In asynchronous mode, this call will return TRUE or FALSE depending if the underlying network search
** could be instantiated.
**
** browser Network Service Browser to perform the search.  Must be non-NULL.
**
** domain Network domain to search in order to find the service.  Must be non-NULL.
**
** type Service type for which to search.  Must be non-NULL.
**
** error A reference to an error struct which will be set to the error and domain of the error should one
**		occur.  If the value of error is not desired, set to NULL.
*/
CF_EXPORT
Boolean CFNetServiceBrowserSearchForServices(CFNetServiceBrowserRef	browser,
											 CFStringRef				domain,
											 CFStringRef				type,
											 CFStreamError* 			error);
											  
							
/*
** CFNetServiceBrowserStopServiceSearch
**
** Stops an outstanding browser search.
**
** browser Network Service Browser performing the search.  Must be non-NULL.
** 
** error Error value to be returned in "error" in CFNetServiceBrowserStartServiceSearch if search is being
**		performed in synchronous mode.  In this case, a non-zero of the error field of the struct will
**		cause CFNetServiceBrowserStartServiceSearch to return FALSE.  In asynchronous mode, the client call
**		back will be called with this error.
*/
CF_EXPORT
void CFNetServiceBrowserStopSearch(CFNetServiceBrowserRef browser, CFStreamError* error);


/*
** CFNetServiceBrowserScheduleWithRunLoop
**
** Schedules the browser on a run loop and mode.  Use this to place the given browser into asynchronous
** mode.  The client callback will be triggered via one of the scheduled run loops; It is the caller's
** responsibility to ensure that at least one of the scheduled run loops is being run.
**
** browser Network Service Browser to schedule.  Must be non-NULL.
**
** runLoop A reference to a runloop on which the browser should be scheduled.  Must be non-NULL.
**
** runLoopMode The mode on which to schedule the browser.  Must be non-NULL.
*/
CF_EXPORT
void CFNetServiceBrowserScheduleWithRunLoop(CFNetServiceBrowserRef	browser,
										    CFRunLoopRef			runLoop,
										    CFStringRef				runLoopMode);


/*
** CFNetServiceBrowserUnscheduleFromRunLoop
**
** Unschedules the browser from a run loop and mode.
**
** browser Network Service Browser to unschedule.  Must be non-NULL.
**
** runLoop A reference to a runloop from which the browser should be unscheduled.  Must be non-NULL.
**
** runLoopMode The mode from which to unschedule the browser.  Must be non-NULL.
*/
CF_EXPORT
void CFNetServiceBrowserUnscheduleFromRunLoop(CFNetServiceBrowserRef	browser,
											  CFRunLoopRef				runLoop,
											  CFStringRef				runLoopMode);
                                              
                                              

#if defined(__cplusplus)
}
#endif


#endif /* __CFNETSERVICES__ */
