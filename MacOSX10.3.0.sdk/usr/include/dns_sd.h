/*
 * Copyright (c) 2003 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 *
 * The contents of this file constitute Original Code as defined in and
 * are subject to the Apple Public Source License Version 1.2 (the
 * "License").  You may not use this file except in compliance with the
 * License.  Please obtain a copy of the License at
 * http://www.apple.com/publicsource and read it before using this file.
 *
 * This Original Code and all software distributed under the License are
 * distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE OR NON-INFRINGEMENT.  Please see the
 * License for the specific language governing rights and limitations
 * under the License.
 *
 * @APPLE_LICENSE_HEADER_END@
 */

#ifndef _DNS_SD_H
#define _DNS_SD_H

#include <sys/types.h>
#include <sys/socket.h>
#include <stdint.h>
#include <netinet/in.h>


/* DNSServiceRef, DNSRecordRef
 *
 * Opaque internal data types.
 * Note: client is responsible for serializing access to these structures if
 * they are shared between concurrent threads.
 */

typedef struct _DNSServiceRef_t *DNSServiceRef;
typedef struct _DNSRecordRef_t *DNSRecordRef;

/* General flags used in functions defined below */
enum
    {
    kDNSServiceFlagsMoreComing          = 1,
    kDNSServiceFlagsFinished            = 0,  /* i.e. bit not set */
    /* MoreComing indicates to a Browse callback that another result is
     * queued.  Applications should not update their UI to display browse
     * results when the MoreComing flag is set, instead deferring the update
     * until the callback's flag is Finished. */

    kDNSServiceFlagsAdd                 = 2,
    kDNSServiceFlagsDefault             = 4,
    kDNSServiceFlagsRemove              = 0,  /* i.e. bit not set */
    /* Flags for domain enumeration and browse reply callbacks.
     * "Default" applies only to enumeration and is only valid in
     * conjuction with "Add" 
     */

    kDNSServiceFlagsNoAutoRename        = 8,
    kDNSServiceFlagsAutoRename          = 0,  /* i.e. bit not set */
    /* Flag for specifying renaming behavior on name conflict when registering
     * non-shared records. NoAutorename is only valid if a name is explicitly
     * specified when registering a service (ie the default name is not used.)
     */


    kDNSServiceFlagsShared              = 16,
    kDNSServiceFlagsUnique              = 32,
    /* Flag for registering individual records on a connected
     * DNSServiceRef.  Shared indicates that there may be multiple records 
     * with this name on the network (e.g. PTR records).  Unique indicates that the
     * record's name is to be unique on the network (e.g. SRV records).
     */

    kDNSServiceFlagsBrowseDomains       = 64,
    kDNSServiceFlagsRegistrationDomains = 128
    /* Flags for specifying domain enumeration type in DNSServiceEnumerateDomains.
     * BrowseDomains enumerates domains recommended for browsing, RegistrationDomains
     * enumerates domains recommended for registration.
     */
    };

/* possible error code values */
enum
    {
    kDNSServiceErr_NoError             = 0,
    kDNSServiceErr_Unknown             = -65537,       /* 0xFFFE FFFF */
    kDNSServiceErr_NoSuchName          = -65538,
    kDNSServiceErr_NoMemory            = -65539,
    kDNSServiceErr_BadParam            = -65540,
    kDNSServiceErr_BadReference        = -65541,
    kDNSServiceErr_BadState            = -65542,
    kDNSServiceErr_BadFlags            = -65543,
    kDNSServiceErr_Unsupported         = -65544,
    kDNSServiceErr_NotInitialized      = -65545,
    kDNSServiceErr_AlreadyRegistered   = -65547,
    kDNSServiceErr_NameConflict        = -65548,
    kDNSServiceErr_Invalid             = -65549,
    kDNSServiceErr_Incompatible        = -65551,        /* client library incompatible with daemon */
    kDNSServiceErr_BadinterfaceIndex   = -65552
    /* mDNS Error codes are in the range
     * FFFE FF00 (-65792) to FFFE FFFF (-65537) */
    };
    

/* Maximum length, in bytes, of a domain name represented as an escaped C-String */
#define kDNSServiceMaxDomainName 1005


typedef uint32_t DNSServiceFlags;
typedef int32_t DNSServiceErrorType;


/*********************************************************************************************
 *
 * Unix Domain Socket access, DNSServiceRef deallocation, and data processing functions
 *
 *********************************************************************************************/


/* DNSServiceRefSockFD()
 *
 * Access underlying Unix domain socket for an initialized DNSServiceRef.
 * The DNS Service Discovery implmementation uses this socket to communicate between 
 * the client and the mDNSResponder daemon.  The application MUST NOT directly read from
 * or write to this socket.  Access to the socket is provided so that it can be used as a
 * run loop source, or in a select() loop: when data is available for reading on the socket, 
 * DNSServiceProcessResult() should be called, which will extract the daemon's reply from 
 * the socket, and pass it to the appropriate application callback.  By using a run loop or
 * select(), results from the daemon can be processed asynchronously.  Without using these
 * constructs, DNSServiceProcessResult() will block until the response from the daemon arrives.
 * The client is responsible for ensuring that the data on the socket is processed in a timely
 * fashion - the daemon may terminate its connection with a client that does not clear its
 * socket buffer.
 *
 * sdRef:            A DNSServiceRef initialized by any of the DNSService calls.
 * 
 * return value:    The DNSServiceRef's underlying socket descriptor, or -1 on 
 *                  error.
 */
 
int DNSServiceRefSockFD(DNSServiceRef sdRef);

/* DNSServiceProcessResult()
 *
 * Read a reply from the daemon, calling the appropriate application callback.  This call will
 * block until the daemon's response is received.  Use DNSServiceRefSockFD() in 
 * conjunction with a run loop or select() to determine the presence of a response from the
 * server before calling this function to process the reply without blocking.  Call this function
 * at any point if it is acceptable to block until the daemon's response arrives.  Note that the
 * client is responsible for ensuring that DNSServiceProcessResult() is called whenever there is
 * a reply from the daemon - the daemon may terminate its connection with a client that does not
 * process the daemon's responses.
 *
 * sdRef:           A DNSServiceRef initialized by any of the DNSService calls
 *                  that take a callback parameter.
 *
 * return value:    Returns kDNSServiceErr_NoError on success, otherwise returns
 *                  an error code indicating the specific failure that occurred.
 */

DNSServiceErrorType DNSServiceProcessResult(DNSServiceRef sdRef);

/* DNSServiceRefDeallocate()
 *
 * Terminate a connection with the daemon and free memory associated with the DNSServiceRef.
 * Any services or records registered with this DNSServiceRef will be deregistered. Any
 * Browse, Resolve, or Query operations called with this reference will be terminated.  
 *
 * Note: If the reference's underlying socket is used in a run loop or select() call, it should 
 * be removed BEFORE DNSServiceRefDeallocate() is called, as this function closes the reference's 
 * socket. 
 *
 * Note: If the reference was initialized with DNSServiceCreateConnection(), any DNSRecordRefs
 * created via this reference will be invalidated by this call - the resource records are 
 * deregistered, and their DNSRecordRefs may not be used in subsequent functions.  Similarly,
 * if the reference was initialized with DNSServiceRegister, and an extra resource record was
 * added to the service via DNSServiceAddRecord(), the DNSRecordRef created by the Add() call 
 * is invalidated when this function is called - the DNSRecordRef may not be used in subsequent
 * functions.
 * 
 * Note: This call is to be used only with the DNSServiceRef defined by this API.  It is
 * not compatible with dns_service_discovery_ref objects defined in the legacy Mach-based 
 * DNSServiceDiscovery.h API.
 *
 * sdRef:           A DNSServiceRef initialized by any of the DNSService calls.
 *
 */

void DNSServiceRefDeallocate(DNSServiceRef sdRef); 


/*********************************************************************************************
 * 
 * Domain Enumeration
 *
 *********************************************************************************************/

/* DNSServiceEnumerateDomains()
 * 
 * Asynchronously enumerate domains available for browsing and registration.
 * Currently, the only domain returned is "local.", but other domains will be returned in future.
 *
 * The enumeration MUST be cancelled via DNSServiceRefDeallocate() when no more domains
 * are to be found.
 *
 *
 * DNSServiceDomainEnumReply Callback Parameters:
 *
 * sdRef:           The DNSServiceRef initialized by DNSServiceEnumerateDomains().
 *
 * flags:           Possible values are:
 *                  1 (MoreComing)
 *                  2 (Add/Remove)
 *                  4 (Add Default)
 *
 * interfaceIndex:  Specifies the interface on which the domain exists.  (The index for a given 
 *                  interface is determined via the if_nametoindex() family of calls.)  
 *
 * errorCode:       Will be kDNSServiceErr_NoError (0) on success, otherwise indicates 
 *                  the failure that occurred (other parameters are undefined if errorCode is nonzero).
 *
 * replyDomain:     The name of the domain.
 *
 * context:         The context pointer passed to DNSServiceEnumerateDomains.
 * 
 */

typedef void (*DNSServiceDomainEnumReply)
    (
    DNSServiceRef                       sdRef,
    DNSServiceFlags                     flags,
    uint32_t                            interfaceIndex,
    DNSServiceErrorType                 errorCode,
    const char                          *replyDomain,  
    void                                *context       
    );
    
/* DNSServiceEnumerateDomains() Parameters:
 *
 *
 * sdRef:           A pointer to an uninitialized sdRef.  May be passed to 
 *                  DNSServiceRefDeallocate() to cancel the enumeration.
 *
 * flags:           Possible values are:
 *                  0 (BrowseDomains) to enumerate domains recommended for browsing.
 *                  32 (RegistrationDomains) to enumerate domains recommended for registration.
 *
 * interfaceIndex:  If non-zero, specifies the interface on which to look for domains.
 *                  (the index for a given interface is determined via the if_nametoindex()
 *                  family of calls.)  Most applications will pass 0 to enumerate domains on 
 *                  all interfaces.  
 * 
 * callBack:        The function to be called when a domain is found or the call asynchronously 
 *                  fails.
 *
 * context:         An application context pointer which is passed to the callback function 
 *                  (may be NULL).
 *
 * return value:    Returns kDNSServiceErr_NoError on succeses (any subsequent, asynchronous
 *                  errors are delivered to the callback), otherwise returns an error code indicating 
 *                  the error that occurred (the callback is not invoked and the DNSServiceRef
 *                  is not initialized.)
 */
 
DNSServiceErrorType DNSServiceEnumerateDomains
    (
    DNSServiceRef                       *sdRef,
    DNSServiceFlags                     flags,
    uint32_t                            interfaceIndex,
    DNSServiceDomainEnumReply           callBack,
    void                                *context  /* may be NULL */
    );

/*********************************************************************************************
 *
 *  Service Registration
 *
 *********************************************************************************************/
 
/* Register a service that is discovered via Browse() and Resolve() calls.
 *
 *
 * DNSServiceRegisterReply() Callback Parameters:
 * 
 * sdRef:           The DNSServiceRef initialized by DNSServiceRegister().
 *
 * flags:           Currently unused, reserved for future use.
 *
 * errorCode:       Will be kDNSServiceErr_NoError on success, otherwise will 
 *                  indicate the failure that occurred (including name conflicts, if the
 *                  kDNSServiceFlagsNoAutoRenameOnConflict flag was passed to the
 *                  callout.)  Other parameters are undefined if errorCode is nonzero.
 *
 * name:            The service name registered (if the application did not specify a name in 
 *                  DNSServiceRegister(), this indicates what name was automatically chosen).
 *
 * regtype:         The type of service registered, as it was passed to the callout.
 *
 * domain:          The domain on which the service was registered (if the application did not
 *                  specify a domain in DNSServiceRegister(), this indicates the default domain
 *                  on which the service was registered).
 *
 * context:         The context pointer that was passed to the callout.
 *
 */
 
typedef void (*DNSServiceRegisterReply)
    (
    DNSServiceRef                       sdRef,
    DNSServiceFlags                     flags,
    DNSServiceErrorType                 errorCode,
    const char                          *name,     
    const char                          *regtype,  
    const char                          *domain,   
    void                                *context  
    );
    
/* DNSServiceRegister()  Parameters:
 *
 * sdRef:           A pointer to an uninitialized sdRef.  If this call succeeds, the reference
 *                  may be passed to 
 *                  DNSServiceRefDeallocate() to deregister the service.
 *        
 * interfaceIndex:  If non-zero, specifies the interface on which to register the service
 *                  (the index for a given interface is determined via the if_nametoindex()
 *                  family of calls.)  Most applications will pass 0 to register on all 
 *                  available interfaces.  Pass -1 to register a service only on the local 
 *                  machine (service will not be visible to remote hosts.)
 *
 * flags:           Indicates the renaming behavior on name conflict (most applications
 *                  will pass 0).  See flag definitions above for details.
 *
 * name:            If non-NULL, specifies the service name to be registered.  
 *                  Most applications will not specify a name, in which case the 
 *                  computer name is used (this name is communicated to the client via 
 *                  the callback).
 *
 * regtype:         The service type followed by the protocol, separated by a dot 
 *                  (e.g. "_ftp._tcp").  The transport protocol must be "_tcp" or "_udp".
 *
 * domain:          If non-NULL, specifies the domain on which to advertise the service.
 *                  Most applications will not specify a domain, instead automatically 
 *                  registering in the default domain(s).
 *
 * host:            If non-NULL, specifies the SRV target host name.  Most applications
 *                  will not specify a host, instead automatically using the machine's
 *                  default host name(s).  Note that specifying a non-NULL host does NOT 
 *                  create an address record for that host - the application is responsible 
 *                  for ensuring that the appropriate address record exists, or creating it
 *                  via DNSServiceRegisterRecord().
 *
 * port:            The port on which the service accepts connections.  Pass 0 for a 
 *                  "placeholder" service (i.e. a service that will not be discovered by 
 *                  browsing, but will cause a name conflict if another client tries to 
 *                  register that same name.)  Most clients will not use placeholder services.
 *
 * txtLen:          The length of the txtRecord, in bytes.  Must be zero if the txtRecord is NULL.
 *
 * txtRecord:       The txt record rdata.  May be NULL.  Note that a non-NULL txtRecord 
 *                  MUST be a properly formatted DNS TXT record, i.e. <length byte> <data> 
 *                  <length byte> <data> ...
 *
 * callBack:        The function to be called when the registration completes or asynchronously
 *                  fails.  The client MAY pass NULL for the callback -  The client will NOT be notified 
 *                  of the default values picked on its behalf, and the client will NOT be notified of any
 *                  asynchronous errors (e.g. out of memory errors, etc.) that may prevent the registration 
 *                  of the service.  The client may NOT pass the NoAutoRename flag if the callback is NULL.
 *                  The client may still deregister the service at any time via DNSServiceRefDeallocate().
 *
 * context:         An application context pointer which is passed to the callback function 
 *                  (may be NULL).
 *
 * return value:    Returns kDNSServiceErr_NoError on succeses (any subsequent, asynchronous
 *                  errors are delivered to the callback), otherwise returns an error code indicating 
 *                  the error that occurred (the callback is never invoked and the DNSServiceRef
 *                  is not initialized.)
 *
 */

DNSServiceErrorType DNSServiceRegister
    (
    DNSServiceRef                       *sdRef,
    DNSServiceFlags                     flags,
    uint32_t                            interfaceIndex,
    const char                          *name,         /* may be NULL */
    const char                          *regtype,  
    const char                          *domain,       /* may be NULL */
    const char                          *host,         /* may be NULL */
    uint16_t                            port,
    uint16_t                            txtLen,
    const void                          *txtRecord,    /* may be NULL */
    DNSServiceRegisterReply             callBack,      /* may be NULL */
    void                                *context       /* may be NULL */
    );
    
/* DNSServiceAddRecord()
 *
 * Add a record to a registered service.  The name of the record will be the same as the
 * registered service's name.
 * The record can later be updated or deregistered by passing the RecordRef initialized 
 * by this function to DNSServiceUpdateRecord() or DNSServiceRemoveRecord().
 *
 * 
 * Parameters;
 *
 * sdRef:           A DNSServiceRef initialized by DNSServiceRegister().
 * 
 * RecordRef:       A pointer to an uninitialized DNSRecordRef.  Upon succesfull completion of this 
 *                  call, this ref may be passed to DNSServiceUpdateRecord() or DNSServiceRemoveRecord().
 *                  If the above DNSServiceRef is passed to DNSServiceRefDeallocate(), RecordRef is also
 *                  invalidated and may not be used further.
 *
 * flags:           Currently ignored, reserved for future use.
 *
 * rrtype:          The type of the record (e.g. TXT, SRV, etc), as defined in nameser.h.
 *
 * rdlen:           The length, in bytes, of the rdata.
 *
 * rdata:           The raw rdata to be contained in the added resource record.
 *
 * ttl:             The time to live of the resource record, in seconds.
 *
 * return value:    Returns kDNSServiceErr_NoError on success, otherwise returns an
 *                  error code indicating the error that occurred (the RecordRef is not initialized).
 */

DNSServiceErrorType DNSServiceAddRecord
    (
    DNSServiceRef                       sdRef,
    DNSRecordRef                        *RecordRef,
    DNSServiceFlags                     flags,
    uint16_t                            rrtype,
    uint16_t                            rdlen,
    const void                          *rdata,
    uint32_t                            ttl
    );

/* DNSServiceUpdateRecord
 *
 * Update a registered resource record.  The record must either be:
 *   - The primary txt record of a service registered via DNSServiceRegister()
 *   - A record added to a registered service via DNSServiceAddRecord()
 *   - An individual record registered by DNSServiceRegisterRecord()
 *
 *
 * Parameters:
 *
 * sdRef:           A DNSServiceRef that was initialized by DNSServiceRegister()
 *                  or DNSServiceCreateConnection().
 *
 * RecordRef:       A DNSRecordRef initialized by DNSServiceAddRecord, or NULL to update the
 *                  service's primary txt record.
 *
 * flags:           Currently ignored, reserved for future use.
 *
 * rdlen:           The length, in bytes, of the new rdata.
 *
 * rdata:           The new rdata to be contained in the updated resource record.
 *
 * ttl:             The time to live of the updated resource record, in seconds.
 *
 * return value:    Returns kDNSServiceErr_NoError on success, otherwise returns an
 *                  error code indicating the error that occurred.
 */

DNSServiceErrorType DNSServiceUpdateRecord
    (
    DNSServiceRef                       sdRef,
    DNSRecordRef                        RecordRef,     /* may be NULL */
    DNSServiceFlags                     flags,
    uint16_t                            rdlen,
    const void                          *rdata,
    uint32_t                            ttl
    );

/* DNSServiceRemoveRecord
 *
 * Remove a record previously added to a service record set via DNSServiceAddRecord(), or deregister 
 * an record registered individually via DNSServiceRegisterRecord().
 *
 * Parameters:
 *
 * sdRef:           A DNSServiceRef initialized by DNSServiceRegister() (if the
 *                  record being removed was registered via DNSServiceAddRecord()) or by
 *                  DNSServiceCreateConnection() (if the record being removed was registered via
 *                  DNSServiceRegisterRecord()).
 *
 * recordRef:       A DNSRecordRef initialized by a successful call to DNSServiceAddRecord() 
 *                  or DNSServiceRegisterRecord().
 *   
 * flags:           Currently ignored, reserved for future use.
 *
 * return value:    Returns kDNSServiceErr_NoError on success, otherwise returns an
 *                  error code indicating the error that occurred.
 */

DNSServiceErrorType DNSServiceRemoveRecord
    (
    DNSServiceRef                 sdRef,
    DNSRecordRef                  RecordRef,
    DNSServiceFlags               flags
    );


/*********************************************************************************************
 *
 *  Service Discovery
 *
 *********************************************************************************************/


/* Browse for instances of a service.
 *
 *
 * DNSServiceBrowseReply() Parameters:
 *
 * sdRef:           The DNSServiceRef initialized by DNSServiceBrowse().
 *
 * flags:           Possible values are MoreComing and Add/Remove.  See flag definitions
 *                  for details.
 *
 * interfaceIndex:  The interface on which the service is advertised.  This index should
 *                  be passed to DNSServiceResolve() when resolving the service. 
 *
 * errorCode:       Will be kDNSServiceErr_NoError (0) on success, otherwise will 
 *                  indicate the failure that occurred.  Other parameters are undefined if
 *                  the errorCode is nonzero.
 *
 * serviceName:     The service name discovered.
 *
 * regtype:         The service type, as passed in to DNSServiceBrowse().
 *
 * domain:          The domain on which the service was discovered (if the application did not
 *                  specify a domain in DNSServicBrowse(), this indicates the domain on which the
 *                  service was discovered.)
 *
 * context:         The context pointer that was passed to the callout.
 *
 */

typedef void (*DNSServiceBrowseReply)
    (
    DNSServiceRef                       sdRef,
    DNSServiceFlags                     flags,
    uint32_t                            interfaceIndex,
    DNSServiceErrorType                 errorCode,
    const char                          *serviceName,  
    const char                          *regtype,    
    const char                          *replyDomain,  
    void                                *context  
    );
    
/* DNSServiceBrowse() Parameters:
 *
 * sdRef:           A pointer to an uninitialized sdRef.  May be passed to 
 *                  DNSServiceRefDeallocate() to terminate the browse.
 *
 * flags:           Currently ignored, reserved for future use.
 *
 * interfaceIndex:  If non-zero, specifies the interface on which to browse for services
 *                  (the index for a given interface is determined via the if_nametoindex()
 *                  family of calls.)  Most applications will pass 0 to browse on all available
 *                  interfaces.  Pass -1 to only browse for services provided on the local host.
 *
 * regtype:         The service type being browsed for followed by the protocol, separated by a  
 *                  dot (e.g. "_ftp._tcp").  The transport protocol must be "_tcp" or "_udp".
 *
 * domain:          If non-NULL, specifies the domain on which to browse for services.
 *                  Most applications will not specify a domain, instead browsing on the 
 *                  default domain(s).
 *
 * callBack:        The function to be called when an instance of the service being browsed for 
 *                  is found, or if the call asynchronously fails.
 *
 * context:         An application context pointer which is passed to the callback function 
 *                  (may be NULL).
 *
 * return value:    Returns kDNSServiceErr_NoError on succeses (any subsequent, asynchronous
 *                  errors are delivered to the callback), otherwise returns an error code indicating 
 *                  the error that occurred (the callback is not invoked and the DNSServiceRef
 *                  is not initialized.)
 */

DNSServiceErrorType DNSServiceBrowse
    (
    DNSServiceRef                       *sdRef,
    DNSServiceFlags                     flags,
    uint32_t                            interfaceIndex,
    const char                          *regtype,   
    const char                          *domain,    /* may be NULL */
    DNSServiceBrowseReply               callBack,
    void                                *context    /* may be NULL */
    );

/* DNSServiceResolve()
 *
 * Resolve a service name discovered via DNSServiceBrowse() to a target host name, port number, and
 * txt record.
 *
 * Note: Applications should NOT use DNSServiceResolve() solely for txt record monitoring - use 
 * DNSServiceQueryRecord() instead, as it is more efficient for this task.
 *
 * Note: When the desired results have been returned, the client MUST terminate the resolve by calling
 * DNSServiceRefDeallocate().
 *
 * Note: DNSServiceResolve() behaves correctly for typical services that have a single SRV record and
 * a single TXT record (the TXT record may be empty.)  To resolve non-standard services with multiple
 * SRV or TXT records, DNSServiceQueryRecord() should be used.
 *
 * DNSServiceResolveReply Callback Parameters:
 *
 * sdRef:           The DNSServiceRef initialized by DNSServiceResolve().
 *
 * flags:           Currently unused, reserved for future use.
 *
 * interfaceIndex:  The interface on which the service was resolved.   
 *
 * errorCode:       Will be kDNSServiceErr_NoError (0) on success, otherwise will 
 *                  indicate the failure that occurred.  Other parameters are undefined if
 *                  the errorCode is nonzero.
 *
 * fullname:        The full service domain name, in the form <servicename>.<protocol>.<domain>.
 *                  (Any literal dots (".") are escaped with a backslash ("\."), and literal
 *                  backslashes are escaped with a second backslash ("\\"), e.g. a web server
 *                  named "Dr. Pepper" would have the fullname  "Dr\.\032Pepper._http._tcp.local.").
 *                  This is the appropriate format to pass to standard system DNS APIs such as 
 *                  res_query(), or to the special-purpose functions included in this API that
 *                  take fullname parameters.
 * 
 * hosttarget:      The target hostname of the machine providing the service.  This name can 
 *                  be passed to functions like gethostbyname() to identify the host's IP address.
 *
 * port:            The port number on which connections are accepted for this service.
 *
 * txtLen:          The length of the txt record, in bytes.
 *
 * txtRecord:       The service's primary txt record, in standard txt record format.
 *
 
 * context:         The context pointer that was passed to the callout.
 *
 */

typedef void (*DNSServiceResolveReply)
    (
    DNSServiceRef                       sdRef,
    DNSServiceFlags                     flags,
    uint32_t                            interfaceIndex,
    DNSServiceErrorType                 errorCode,
    const char                          *fullname,    
    const char                          *hosttarget,
    uint16_t                            port,
    uint16_t                            txtLen,
    const char                          *txtRecord,
    void                                *context  
    );
  
/* DNSServiceResolve() Parameters
 *
 * sdRef:           A pointer to an uninitialized sdRef.  May be passed to 
 *                  DNSServiceRefDeallocate() to terminate the resolve.
 *
 * flags:           Currently ignored, reserved for future use.
 *
 * interfaceIndex:  The interface on which to resolve the service.  The client should
 *                  pass the interface on which the servicename was discovered, i.e. 
 *                  the interfaceIndex passed to the DNSServiceBrowseReply callback,
 *                  or 0 to resolve the named service on all available interfaces.
 *
 * name:            The servicename to be resolved.
 *
 * regtype:         The service type being resolved followed by the protocol, separated by a  
 *                  dot (e.g. "_ftp._tcp").  The transport protocol must be "_tcp" or "_udp". 
 *
 * domain:          The domain on which the service is registered, i.e. the domain passed
 *                  to the DNSServiceBrowseReply callback.
 *
 * callBack:        The function to be called when a result is found, or if the call 
 *                  asynchronously fails.
 *
 * context:         An application context pointer which is passed to the callback function 
 *                  (may be NULL).
 *
 * return value:    Returns kDNSServiceErr_NoError on succeses (any subsequent, asynchronous
 *                  errors are delivered to the callback), otherwise returns an error code indicating 
 *                  the error that occurred (the callback is never invoked and the DNSServiceRef
 *                  is not initialized.)
 */


DNSServiceErrorType DNSServiceResolve
    (
    DNSServiceRef                       *sdRef,
    DNSServiceFlags                     flags,
    uint32_t                            interfaceIndex,
    const char                          *name,     
    const char                          *regtype,  
    const char                          *domain,   
    DNSServiceResolveReply              callBack,
    void                                *context  /* may be NULL */
    );


/*********************************************************************************************
 *
 *  Special Purpose Calls (most applications will not use these)
 *
 *********************************************************************************************/

/* DNS Naming Conventions:
 *
 * The following functions refer to resource records by their full domain name, unlike the above
 * functions which divide the name into servicename/regtype/domain fields.  In the above functions,
 * a dot (".") is considered to be a literal dot in the servicename field (e.g. "Dr. Pepper") and 
 * a label separator in the regtype ("_ftp._tcp") or domain ("apple.com") fields.  Literal dots in 
 * the domain field would be escaped with a backslash, and literal backslashes would be escaped with
 * a second backslash (this is generally not an issue, as domain names on  the Internet today almost 
 * never use characters other than letters, digits, or hyphens, and the dots are label separators.)
 * Furthermore, this is transparent to the caller, so long as the fields are passed between functions 
 * without manipulation.  However, the following, special-purpose calls use a single, full domain name.  
 * As such, all dots are considered to be label separators, unless escaped, and all backslashes are 
 * considered to be escape characters, unless preceded by a second backslash.  For example, the name 
 * "Dr. Smith \ Dr. Johnson" could be passed literally as a service name parameter in the above calls, 
 * but in the special purpose call, the dots and backslash would have to be escaped 
 * (e.g. "Dr\. Smith \\ Dr\. Johnson._ftp._tcp.apple.com" for an ftp service on the apple.com domain.)
 */

/* DNSServiceConstructFullName()
 *
 * Concatenate a three-part domain name (as returned by the above callbacks) into a properly-escaped
 * full domain name.  Note that callbacks in the above functions ALREADY ESCAPE strings where necessary.
 *
 * Parameters:
 *
 * fullName:        A pointer to a buffer that where the resulting full domain name is to be written.
 *                  The buffer must be kDNSServiceDiscoveryMaxDomainName (1005) bytes in length to 
 * 		            accommodate the longest legal domain name without buffer overrun.
 *
 * service:         The service name - any dots or slashes must NOT be escaped.
 *                  May be NULL (to construct a PTR record name, e.g.
 *                  "_ftp._tcp.apple.com").
 *
 * regtype:         The service type followed by the protocol, separated by a dot 
 *                  (e.g. "_ftp._tcp"). 
 *
 * domain:          The domain name, e.g. "apple.com".  Any literal dots or backslashes
 *                  must be escaped.
 *
 * return value:    Returns 0 on success, -1 on error.
 *
 */
 
int DNSServiceConstructFullName 
    (
    char                            *fullName,
    const char                      *service,      /* may be NULL */
    const char                      *regtype,
    const char                      *domain
    );
    
/* DNSServiceCreateConnection()
 *
 * Create a connection to the daemon allowing efficient registration of
 * multiple individual records.
 *
 *
 * Parameters:
 *
 * sdRef:           A pointer to an uninitialized DNSServiceRef.  Deallocating
 *                  the reference (via DNSServiceRefDeallocate()) severs the
 *                  connection and deregisters all records registered on this connection.
 *
 * return value:    Returns kDNSServiceErr_NoError on success, otherwise returns
 *                  an error code indicating the specific failure that occurred (in which
 *                  case the DNSServiceRef is not initialized).
 */

DNSServiceErrorType DNSServiceCreateConnection(DNSServiceRef *sdRef);


/* DNSServiceRegisterRecord
 *
 * Register an individual resource record on a connected DNSServiceRef.  
 *
 * Note that name conflicts occurring for records registered via this call must be handled
 * by the client in the callback.
 *
 *
 * DNSServiceRegisterRecordReply() parameters:
 *
 * sdRef:           The connected DNSServiceRef initialized by
 *                  DNSServiceDiscoveryConnect().
 * 
 * RecordRef:       The DNSRecordRef initialized by DNSServiceRegisterRecord().  If the above
 *                  DNSServiceRef is passed to DNSServiceRefDeallocate(), this DNSRecordRef is
 *                  invalidated, and may not be used further.
 *
 * flags:           Currently unused, reserved for future use.
 *
 * errorCode:       Will be kDNSServiceErr_NoError on success, otherwise will 
 *                  indicate the failure that occurred (including name conflicts.)
 *                  Other parameters are undefined if errorCode is nonzero.
 *
 * context:         The context pointer that was passed to the callout.
 *
 */
 
 typedef void (*DNSServiceRegisterRecordReply)
    (
    DNSServiceRef                       sdRef,
    DNSRecordRef                        RecordRef,
    DNSServiceFlags                     flags,
    DNSServiceErrorType                 errorCode,
    void                                *context  
    );

 
/* DNSServiceRegisterRecord() Parameters:         
 *
 * sdRef:           A DNSServiceRef initialized by DNSServiceCreateConnection().
 *
 * RecordRef:       A pointer to an uninitialized DNSRecordRef.  Upon succesfull completion of this 
 *                  call, this ref may be passed to DNSServiceUpdateRecord() or DNSServiceRemoveRecord().
 *                  (To deregister ALL records registered on a single connected DNSServiceRef 
 *                  and deallocate each of their corresponding DNSServiceRecordRefs, call
 *                  DNSServiceRefDealloocate()).
 *
 * flags:           Possible values are Shared/Unique (see flag type definitions for details).
 * 
 * interfaceIndex:  If non-zero, specifies the interface on which to register the record
 *                  (the index for a given interface is determined via the if_nametoindex()
 *                  family of calls.)  Passing 0 causes the record to be registered on all interfaces.
 *                  Passing -1 causes the record to only be visible on the local host.
 *
 * fullname:        The full domain name of the resource record.
 *
 * rrtype:          The numerical type of the resource record (e.g. PTR, SRV, etc), as defined 
 *                  in nameser.h.
 *
 * rrclass:         The class of the resource record, as defined in nameser.h (usually 1 for the 
 *                  Internet class).
 *
 * rdlen:           Length, in bytes, of the rdata.
 *
 * rdata:           A pointer to the raw rdata, as it is to appear in the DNS record.
 *
 * ttl:             The time to live of the resource record, in seconds.
 *
 * callBack:        The function to be called when a result is found, or if the call 
 *                  asynchronously fails (e.g. because of a name conflict.)
 *
 * context:         An application context pointer which is passed to the callback function 
 *                  (may be NULL).
 *
 * return value:    Returns kDNSServiceErr_NoError on succeses (any subsequent, asynchronous
 *                  errors are delivered to the callback), otherwise returns an error code indicating 
 *                  the error that occurred (the callback is never invoked and the DNSRecordRef is
 *                  not initialized.)
 */
 

DNSServiceErrorType DNSServiceRegisterRecord
    (
    DNSServiceRef                       sdRef,
    DNSRecordRef                        *RecordRef,
    DNSServiceFlags                     flags,
    uint32_t                            interfaceIndex,
    const char                          *fullname,   
    uint16_t                            rrtype,
    uint16_t                            rrclass,
    uint16_t                            rdlen,
    const void                          *rdata,
    uint32_t                            ttl,
    DNSServiceRegisterRecordReply       callBack,
    void                                *context    /* may be NULL */
    );


/* DNSServiceQueryRecord
 *
 * Query for an arbitrary DNS record.
 *
 *
 * DNSServiceQueryRecordReply() Callback Parameters:
 *
 * sdRef:           The DNSServiceRef initialized by DNSServiceQueryRecord().
 * 
 * flags:           Possible values are Finished/MoreComing.
 *
 * interfaceIndex:  The interface on which the query was resolved (the index for a given 
 *                  interface is determined via the if_nametoindex() family of calls).
 *
 * errorCode:       Will be kDNSServiceErr_NoError on success, otherwise will 
 *                  indicate the failure that occurred.  Other parameters are undefined if 
 *                  errorCode is nonzero.
 *
 * fullname:        The resource record's full domain name.
 *
 * rrtype:          The resource record's type (e.g. PTR, SRV, etc) as defined in nameser.h.
 *
 * rrclass:         The class of the resource record, as defined in nameser.h (usually 1).
 *
 * rdlen:           The length, in bytes, of the resource record rdata.
 *
 * rdata:           The raw rdata of the resource record.
 *
 * ttl:             The resource record's time to live, in seconds.
 *
 * context:         The context pointer that was passed to the callout.
 *
 */

typedef void (*DNSServiceQueryRecordReply)
    (
    DNSServiceRef                       DNSServiceRef,
    DNSServiceFlags                     flags,
    uint32_t                            interfaceIndex,
    DNSServiceErrorType                 errorCode,
    const char                          *fullname,    
    uint16_t                            rrtype,
    uint16_t                            rrclass,
    uint16_t                            rdlen,
    const void                          *rdata,
    uint32_t                            ttl,
    void                                *context  
    );

/* DNSServiceQueryRecord() Parameters:
 *
 * sdRef:           A pointer to an uninitialized DNSServiceRef.
 *
 * flags:           Currently unused, reserved for future use.
 * 
 * interfaceIndex:  If non-zero, specifies the interface on which to issue the query
 *                  (the index for a given interface is determined via the if_nametoindex()
 *                  family of calls.)  Passing 0 causes the name to be queried for on all 
 *                  interfaces.  Passing -1 causes the name to be queried for only on the
 *                  local host.
 *
 * fullname:        The full domain name of the resource record to be queried for.
 *
 * rrtype:          The numerical type of the resource record to be queried for (e.g. PTR, SRV, etc)
 *                  as defined in nameser.h.
 *
 * rrclass:         The class of the resource record, as defined in nameser.h 
 *                  (usually 1 for the Internet class).
 *
 * callBack:        The function to be called when a result is found, or if the call 
 *                  asynchronously fails.
 *
 * context:         An application context pointer which is passed to the callback function 
 *                  (may be NULL).
 *
 * return value:    Returns kDNSServiceErr_NoError on succeses (any subsequent, asynchronous
 *                  errors are delivered to the callback), otherwise returns an error code indicating 
 *                  the error that occurred (the callback is never invoked and the DNSServiceRef
 *                  is not initialized.)
 */
 
DNSServiceErrorType DNSServiceQueryRecord
    (
    DNSServiceRef                       *sdRef,
    DNSServiceFlags                     flags,
    uint32_t                            interfaceIndex,
    const char                          *fullname,     
    uint16_t                            rrtype,
    uint16_t                            rrclass,
    DNSServiceQueryRecordReply          callBack,
    void                                *context  /* may be NULL */
    );

/* DNSServiceReconfirmRecord
 *
 * Instruct the daemon to verify the validity of a resource record that appears to 
 * be out of date (e.g. because tcp connection to a service's target failed.)  
 * Causes the record to be flushed from the daemon's cache (as well as all other 
 * daemons' caches on the network) if the record is determined to be invalid.
 *
 * Parameters:
 *
 * flags:           Currently unused, reserved for future use.
 *
 * fullname:        The resource record's full domain name.
 *
 * rrtype:          The resource record's type (e.g. PTR, SRV, etc) as defined in nameser.h.
 *
 * rrclass:         The class of the resource record, as defined in nameser.h (usually 1).
 *
 * rdlen:           The length, in bytes, of the resource record rdata.
 *
 * rdata:           The raw rdata of the resource record.
 *
 */
 
void DNSServiceReconfirmRecord
    (
    DNSServiceFlags                    flags,
    uint32_t                           interfaceIndex,
    const char                         *fullname,   
    uint16_t                           rrtype,
    uint16_t                           rrclass,
    uint16_t                           rdlen,
    const void                         *rdata
    );


#endif  // _DNS_SD_H

