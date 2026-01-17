/*
     File:       WebServicesCore/WSTypes.h
 
     Contains:   WebServicesCore Method Invocation API
 
     Version:    WebServices-26~604
 
     Copyright:  © 2002-2006 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __WSTYPES__
#define __WSTYPES__

#ifndef __CORESERVICES__
#include <CoreServices/CoreServices.h>
#endif


/*
    WSTypes
 */
/*
    WebServicesCore error codes
 */

#include <AvailabilityMacros.h>

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

#pragma options align=mac68k

#if PRAGMA_ENUM_ALWAYSINT
    #pragma enumsalwaysint on
#endif

enum {
  errWSInternalError            = -65793L, /* An internal framework error */
  errWSTransportError           = -65794L, /* A network error occured */
  errWSParseError               = -65795L, /* The server response wasn't valid XML */
  errWSTimeoutError             = -65796L /* The invocation timed out */
};


/*
 *  WSTypeID
 *  
 *  Discussion:
 *    Internally, WebServicesCore uses the following enumeration when
 *    serializing between CoreFoundation and XML types. Because CFTypes
 *    are defined at runtime, it isn't always possible to produce a
 *    static mapping to a particular CFTypeRef.  This enum and
 *    associated API allows for static determination of the expected
 *    serialization.
 */
enum WSTypeID {

  /*
   * No mapping is known for this type
   */
  eWSUnknownType                = 0,

  /*
   * CFNullRef
   */
  eWSNullType                   = 1,

  /*
   * CFBooleanRef
   */
  eWSBooleanType                = 2,

  /*
   * CFNumberRef for 8, 16, 32 bit integers
   */
  eWSIntegerType                = 3,

  /*
   * CFNumberRef for long double real numbers
   */
  eWSDoubleType                 = 4,

  /*
   * CFStringRef
   */
  eWSStringType                 = 5,

  /*
   * CFDateRef
   */
  eWSDateType                   = 6,

  /*
   * CFDataRef
   */
  eWSDataType                   = 7,

  /*
   * CFArrayRef
   */
  eWSArrayType                  = 8,

  /*
   * CFDictionaryRef
   */
  eWSDictionaryType             = 9
};
typedef enum WSTypeID WSTypeID;

typedef CALLBACK_API( void *, WSClientContextRetainCallBackProcPtr )(void * info);
typedef CALLBACK_API( void , WSClientContextReleaseCallBackProcPtr )(void * info);
typedef CALLBACK_API( CFStringRef , WSClientContextCopyDescriptionCallBackProcPtr )(void * info);

/*
 *  WSClientContext
 *  
 *  Discussion:
 *    Several calls in WebServicesCore take a callback with an optional
 *    context pointer.  The context is copied and the info pointer
 *    retained.  When the callback is made, the info pointer is passed
 *    to the callback.
 */
struct WSClientContext {

  /*
   * set to zero (0)
   */
  CFIndex             version;

  /*
   * info pointer to be passed to the callback
   */
  void *              info;

  /*
   * callback made on the info pointer. This field may be NULL.
   */
  WSClientContextRetainCallBackProcPtr  retain;

  /*
   * callback made on the info pointer. This field may be NULL.
   */
  WSClientContextReleaseCallBackProcPtr  release;

  /*
   * callback made on the info pointer. This field may be NULL.
   */
  WSClientContextCopyDescriptionCallBackProcPtr  copyDescription;
};
typedef struct WSClientContext          WSClientContext;
/*
    Web Service protocol types.  These constant strings specify the type
    of web service method invocation created.  These are passed to
    WSMethodInvocationCreate.

    For information on these service types, see:

    XML-RPC:    <http://www.xml-rpc.com/spec/>
    SOAP 1.1:   <http://www.w3.org/TR/SOAP/>
    SOAP 1.2:   <http://www.w3.org/2002/ws/>
*/
extern CFStringRef kWSXMLRPCProtocol;
extern CFStringRef kWSSOAP1999Protocol;
extern CFStringRef kWSSOAP2001Protocol;


/*
 *  WSGetWSTypeIDFromCFType()
 *  
 *  Discussion:
 *    Returns the WSTypeID associated with CFTypeRef.  There is not a
 *    one to one mapping between CFTypeID and WSTypesID therefore an
 *    actual instance of a CFType must be passed.
 *  
 *  Mac OS X threading:
 *    Thread safe
 *  
 *  Parameters:
 *    
 *    ref:
 *      a CFTypeRef object
 *  
 *  Result:
 *    the WSTypeID used in serializing the object.  If no WSTypeID
 *    matches, eWSUnknownType is returned.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern WSTypeID 
WSGetWSTypeIDFromCFType(CFTypeRef ref)                        AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  WSGetCFTypeIDFromWSTypeID()
 *  
 *  Discussion:
 *    Returns the CFTypeID that is associated with a given WSTypeID. 
 *    CFTypeIDs are only valid during a particular instance of a
 *    process and should not be used as static values.
 *  
 *  Mac OS X threading:
 *    Thread safe
 *  
 *  Parameters:
 *    
 *    typeID:
 *      a WSTypeID constant
 *  
 *  Result:
 *    a CFTypeID, or 0 if not found
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFTypeID 
WSGetCFTypeIDFromWSTypeID(WSTypeID typeID)                    AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;



#if PRAGMA_ENUM_ALWAYSINT
    #pragma enumsalwaysint reset
#endif

#pragma options align=reset

#ifdef __cplusplus
}
#endif

#endif /* __WSTYPES__ */

