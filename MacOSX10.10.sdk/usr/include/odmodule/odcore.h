/*
 * Copyright (c) 2009-2013 Apple Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */

#if !defined(__ODCORE_H)
#define __ODCORE_H

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <CoreFoundation/CoreFoundation.h>
#include <Security/Authorization.h>
#include <xpc/xpc.h>

#include <odmodule/odtypes.h>
#include <odmodule/odmodule.h>
#include <odmodule/odmoduleconfig.h>
#include <odmodule/odrequest.h>
#include <odmodule/odconnection.h>
#include <odmodule/odcredential.h>

/*!
    @header     odcore
    @abstract   definitions public for module development
    @discussion various functions useful for module development
                od_node_t is a client node (tracked via ODNode objects)
                od_nodeconfig_t is an internal node config object

                modules should never retain objects across requests as it can lead to leaks
                retains/releases should be paired (i.e., releases should be called before return from a request)
*/

extern const char *kODKeyPredicateList;    // is a sublist of predicates
extern const char *kODKeyPredicateRecordType;
extern const char *kODKeyPredicateStdRecordType;
extern const char *kODKeyPredicateStdAttribute;
extern const char *kODKeyPredicateOperator;
extern const char *kODKeyPredicateMatchType;
extern const char *kODKeyPredicateValueList;
extern const char *kODKeyPredicateEquality;

// predicate operators
extern const char *kODPredicateOperatorAnd;
extern const char *kODPredicateOperatorOr;
extern const char *kODPredicateOperatorNot;

// function and attribute are mutually exclusive
extern const char *kODKeyPredicateAttribute;
extern const char *kODKeyPredicateFunction;

// used for auth modules in additional info dictionary
extern const char *kODKeyModuleAuthUserDetails;
extern const char *kODKeyModuleConnectionInfo;
extern const char *kODKeyModuleSessionCredentials;
__BEGIN_DECLS


/*!
    @function   log_level_enabled
    @abstract   check if a particular log level is enabled to prevent expensive calculations
*/
bool
log_level_enabled(eODLogLevel level);

/*!
 @function   od_retain_internal
 @abstract   retain an object (internal reference)
 */
OD_NOTHROW
void
od_retain_internal(od_object_t object);

/*!
 @function   od_release_internal
 @abstract   release an object (internal reference)
 */
OD_NOTHROW
void
od_release_internal(od_object_t object);
/*!
 @function   od_retain
 @abstract   retain an object
 */
OD_NOTHROW
void
od_retain(od_object_t object);

#if OS_OBJECT_USE_OBJC_RETAIN_RELEASE
#undef od_retain
#define od_retain(object) ({ od_object_t _o = (object); \
_od_object_validate(_o); (void)[_o retain]; })
#endif // OS_OBJECT_USE_OBJC_RETAIN_RELEASE

/*!
    @function   od_release
    @abstract   release an object
*/
OD_NOTHROW
void
od_release(od_object_t object);
#if OS_OBJECT_USE_OBJC_RETAIN_RELEASE
#undef od_release
#define od_release(object) ({ od_object_t _o = (object); \
_od_object_validate(_o); [_o release]; })
#endif // OS_OBJECT_USE_OBJC_RETAIN_RELEASE

#pragma mark -
#pragma mark od_context_t
/*!
 @function	odcontext_create
 @abstract   used to create general context information
 @discussion Requests are not persistent, so the context will be added to the od_node_t object associated
 with the request.  When a context is released, it will be removed from the underlying node's
 context list.
 */
OD_WARN_RESULT
od_context_t
odcontext_create(od_request_t request, od_connection_t connection, void *context, od_context_dealloc_fn_t context_dealloc);
/*!
    @function	odcontext_get_identifier
    @abstract   get the identifier of a context, usually to store in a response
    @discussion get the identifier of a context, usually to store in a response
*/
void
odcontext_get_identifier(od_context_t context, uuid_t uuid);

/*!
    @function	odcontext_get_data
    @abstract   returned data is only valid for as long as the context is retained
    @discussion ensure the context is retained until this data is no longer needed, failure to do so could
				cause the data to become deallocated before the client is done.
*/
OD_WARN_RESULT
void *
odcontext_get_data(od_context_t context);

#pragma mark -
#pragma mark Utility functions

/*!
    @function   od_cstr_from_cfstring
    @abstract   get a C string from a CF String as UTF8
    @discussion get a C string from a CF String as UTF8
    @param      inCFStr the CFString to extract
    @param      ioCStr must be freed if it is non-NULL
    @result     a constant C string that should not be freed as it may be internal storage from the CFString
*/
OD_WARN_RESULT OD_NOTHROW
const char *
od_cstr_from_cfstring(CFStringRef inCFStr, char **ioCStr);

/*!
    @function	od_cstr_from_cfstring_or_cfdata
    @abstract   fetches a standard C-string from a CFDataRef or CFStringRef passed to APIs
    @discussion fetches a standard C-string from a CFDataRef or CFStringRef passed to APIs
    @param      value is a CFDataRef or CFStringRef to extract the string from
    @result     a pointer to a char string that must be freed
*/
OD_WARN_RESULT OD_NOTHROW
char *
od_cstr_from_cfstring_or_cfdata(CFTypeRef value);

/*!
 @function   xpctype_to_cftype
 @abstract   Convert xpc_object_t to CFTypeRef
 @param      xpc_obj is the source object
 @result     is a retained CFTypeRef
 */
CF_RETURNS_RETAINED CFTypeRef
xpctype_to_cftype(xpc_object_t xpc_obj);

/*!
 @function   cfctype_to_xpctype
 @abstract   Convert xpc_object_t to xpc_object_t
 @param      cfType is the source object
 @result     is a retained xpc_object_t
 */
XPC_RETURNS_RETAINED
xpc_object_t
cftype_to_xpctype(CFTypeRef cfType);

/*!
 @function   xpc_array_append_cftype
 @abstract   convert a cftype to xpc_object_t and append to array
 @param      xarray is the xpc_array to append to
 @param      cfType is the source object
 */
void
xpc_array_append_cftype(xpc_object_t xarray, CFTypeRef cfType);

/*!
 @function   xpc_dictionary_set_cftype
 @abstract   convert a CFTypeRef to xpc_object_t and insert in xpc_dictionary
 @param      xdict is the xpc_dictionary being modified
 @param      key is the key name
 @param      value is the CFTypeRef value.
 */
void
xpc_dictionary_set_cftype(xpc_object_t xdict, const char *key, CFTypeRef value);

/*!
 @function   CFArrayAppendServer
 @abstract   Append a server configuration to array of servers
 @param      array is the array being modified
 @param      hostname is the server name
 @param      port is the portnumber
 @param      writeable is a bool
 */
void
CFArrayAppendServer(CFMutableArrayRef array, CFStringRef hostname, int port, bool writeable);

/*!
 @function   od_predicate_create_ldapfilter
 @abstract   convert an Open Directory predicate to an LDAP filter
 @param      predicate is an xpc_object_t of type XPC_TYPE_DICTIONARY
 @result     returns a string that must be freed by caller
 */
char *
od_predicate_create_ldapfilter(xpc_object_t predicate);

__END_DECLS

#endif
