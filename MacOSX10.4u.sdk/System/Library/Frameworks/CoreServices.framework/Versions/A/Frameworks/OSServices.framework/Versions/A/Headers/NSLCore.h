/*
     File:       NSLCore/NSLCore.h
 
     Contains:   Interface to API for using the NSL Manager
 
     Version:    NSLCore-138~445
 
     Copyright:  © 2000-2006 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __NSLCORE__
#define __NSLCORE__

#ifndef __CARBONCORE__
#include <CarbonCore/CarbonCore.h>
#endif


#include <AvailabilityMacros.h>

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

#pragma options align=mac68k


enum {
  kNSLMinSystemVersion          = 0x0900, /* equivalent to 9.0*/
  kNSLMinOTVersion              = 0x0130 /* equivalent to 1.3*/
};

enum {
  kNSLDefaultListSize           = 256   /* default list size for service and protocol lists*/
};

enum {
  kNSLURLDelimiter              = ','   /* delimits URL's within memory buffers*/
};


#define    kNSLErrorNoErr              {noErr, kNSLNoContext}      /* an initializer for the NSLError struct */

enum {
  kNSLNoContext                 = 0     /* the default context for NSLError structs*/
};

struct NSLError {
  OSStatus            theErr;
  UInt32              theContext;
};
typedef struct NSLError                 NSLError;
typedef NSLError *                      NSLErrorPtr;
enum {
                                        /* Constants to use with NSLPrepareRequest*/
                                        /* kNSLDuplicateSearchInProgress is not strictly an error.  The client is free to ignore*/
                                        /* this result, and nothing bad will happen if it does.  It is*/
                                        /* informational only.*/
  kNSLDuplicateSearchInProgress = 100,
  kNSLUserCanceled              = userCanceledErr, /* User hit cancel from the NSLStandardGetURL dialog */
                                        /* Invalid enumeratorRef  */
  kNSLInvalidEnumeratorRef      = 0     /* this is not an error; it is the equiv to a NULL ptr*/
};

typedef UInt16 NSLSearchState;
enum {
                                        /* State codes for notifiers.*/
  kNSLSearchStateBufferFull     = 1,
  kNSLSearchStateOnGoing        = 2,
  kNSLSearchStateComplete       = 3,
  kNSLSearchStateStalled        = 4,
  kNSLWaitingForContinue        = 5
};

typedef UInt32 NSLEventCode;
enum {
                                        /* Event codes*/
  kNSLServicesLookupDataEvent   = 6,
  kNSLNeighborhoodLookupDataEvent = 7,
  kNSLNewDataEvent              = 8,
  kNSLContinueLookupEvent       = 9
};


typedef UInt32                          NSLClientRef;
typedef UInt32                          NSLRequestRef;
typedef UInt32                          NSLOneBasedIndex;
typedef char *                          NSLPath;
typedef char *                          NSLServiceType;
typedef Handle                          NSLServicesList;
typedef unsigned char *                 NSLNeighborhood;
/*
   cstring which is a comma delimited list of protocols which can be used to
   create a NSLProtocolList internally
*/

/* the async information block for client<->manager interaction*/
struct NSLClientAsyncInfo {
  void *              clientContextPtr;       /* set by the client for its own use*/
  void *              mgrContextPtr;          /* set by NSL mgr; ptr to request object ptr*/
  char *              resultBuffer;
  long                bufferLen;
  long                maxBufferSize;
  UInt32              startTime;              /* when the search starts, to use with maxSearchTime to determine time-out condition*/
  UInt32              intStartTime;           /* used with alertInterval*/
  UInt32              maxSearchTime;          /* total time for search, in ticks (0 == no time limit)*/
  UInt32              alertInterval;          /* call client's notifier or return, every this many ticks ( 0 == don't use this param)*/
  UInt32              totalItems;             /* total number of tuples currently in buffer*/
  UInt32              alertThreshold;         /* call client's notifier or return, every this many items found ( 0 == don't use this param)*/
  NSLSearchState      searchState;
  NSLError            searchResult;
  NSLEventCode        searchDataType;         /* this is a data type code which allows the client's asyncNotifier to properly*/
                                              /* handle the data in resultBuffer.*/
};
typedef struct NSLClientAsyncInfo       NSLClientAsyncInfo;
typedef NSLClientAsyncInfo *            NSLClientAsyncInfoPtr;

/* the async information block plugin<->manager interaction*/
struct NSLPluginAsyncInfo {
  void *              mgrContextPtr;          /* set by NSL mgr; ptr to request object ptr*/
  void *              pluginContextPtr;       /* set/used by individual plugins*/
  void *              pluginPtr;              /* ptr to the plugin object waiting for continue lookup call*/
  char *              resultBuffer;           /* set by plugin to point at data*/
  long                bufferLen;
  long                maxBufferSize;
  UInt32              maxSearchTime;          /* total time for search, in ticks (0 == no time limit)*/
  UInt32              reserved1;
  UInt32              reserved2;
  UInt32              reserved3;
  NSLClientRef        clientRef;
  NSLRequestRef       requestRef;
  NSLSearchState      searchState;
  OSStatus            searchResult;
};
typedef struct NSLPluginAsyncInfo       NSLPluginAsyncInfo;
typedef NSLPluginAsyncInfo *            NSLPluginAsyncInfoPtr;

/* the manager asynchronous notifier routine.*/
typedef CALLBACK_API( void , NSLMgrNotifyProcPtr )(NSLPluginAsyncInfo * thePluginAsyncInfo);

/* the client asynchronous notifier routine.*/
typedef CALLBACK_API( void , NSLClientNotifyProcPtr )(NSLClientAsyncInfo * theClientAsyncInfo);
typedef STACK_UPP_TYPE(NSLMgrNotifyProcPtr)                     NSLMgrNotifyUPP;
typedef STACK_UPP_TYPE(NSLClientNotifyProcPtr)                  NSLClientNotifyUPP;
/*
 *  NewNSLMgrNotifyUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern NSLMgrNotifyUPP
NewNSLMgrNotifyUPP(NSLMgrNotifyProcPtr userRoutine)           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewNSLClientNotifyUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern NSLClientNotifyUPP
NewNSLClientNotifyUPP(NSLClientNotifyProcPtr userRoutine)     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeNSLMgrNotifyUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeNSLMgrNotifyUPP(NSLMgrNotifyUPP userUPP)               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeNSLClientNotifyUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeNSLClientNotifyUPP(NSLClientNotifyUPP userUPP)         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeNSLMgrNotifyUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokeNSLMgrNotifyUPP(
  NSLPluginAsyncInfo *  thePluginAsyncInfo,
  NSLMgrNotifyUPP       userUPP)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeNSLClientNotifyUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokeNSLClientNotifyUPP(
  NSLClientAsyncInfo *  theClientAsyncInfo,
  NSLClientNotifyUPP    userUPP)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
   this struct is a format for dealing with our internal data representation.  Typed data will be contiguous chunk of
   memory, with the first 4 bytes being a data "descriptor".
*/
struct NSLTypedData {
  unsigned long       dataType;
  unsigned long       lengthOfData;
/*  void*                           theData; */

};
typedef struct NSLTypedData             NSLTypedData;
typedef NSLTypedData *                  NSLTypedDataPtr;

#define kNSLDataType                'NSL_'
/*
   This is just a header at the beginning of a handle that stores our list of service types.
   Each service type is a pascal string, so each service type starts after the end of the
   previous one.
*/
struct NSLServicesListHeader {
  unsigned long       numServices;
  unsigned long       logicalLen;             /* length of all usable data in handle*/
/*  Ptr                             firstService; */

};
typedef struct NSLServicesListHeader    NSLServicesListHeader;
typedef NSLServicesListHeader *         NSLServicesListHeaderPtr;

/* some defs for common protocols*/

#define    kSLPProtocolType                    "SLP"
#define   kDNSProtocolType                    "DNS"
#define   kLDAPProtocolType                   "LDAP"
#define kNBPProtocolType                 "NBP"
#define kNSLDirectoryServiceProtocolType  "DirService"

/*
   general information from a plug-in.  Includes supported protocols, data types and services,
   as well as an info/comment string describing the function of the plug-in in human-readable
   form.  The offsets point to the beginning of each list of data returned, and the protocol
   data offset is the startOfData member of the struct
*/
struct NSLPluginData {
  long                reserved1;
  long                reserved2;
  long                reserved3;
  Boolean             supportsRegistration;
  Boolean             isPurgeable;
  UInt16              totalLen;               /* length of everything, including header*/
  UInt16              dataTypeOffset;
  UInt16              serviceListOffset;
  UInt16              protocolListOffset;
  UInt16              commentStringOffset;
/*  char*                           startOfData; */
                                              /* protocol data is first on the list*/
};
typedef struct NSLPluginData            NSLPluginData;
typedef NSLPluginData *                 NSLPluginDataPtr;

/*
  -----------------------------------------------------------------------------
    Finding out if the library is present and getting its version
  -----------------------------------------------------------------------------
*/

/*
 *  NSLLibraryVersion()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in NSLPPCLib 1.1 and later
 */
extern UInt32 
NSLLibraryVersion(void)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;




#define NSLLibraryPresent()        true
   

/*
  -----------------------------------------------------------------------------
    High level API calls: the following two calls are ALL an application needs
    to register/deregister its service.
    If you use these, you don't need to make any of the other calls to NSLAPI 
    (including NSLOpenNavigationAPI) 
  -----------------------------------------------------------------------------
*/

/* <--- error code from registration */
/* ---> urlToRegister is a null terminated url that has only legal characters defined for URLs.  Use HexEncodeText to encode*/
/*          portions of the url that have illegal characters */
/* ---> neighborhoodToRegisterIn is an optional parameter for explicitly defining a neighborhood to register in.
            If parameter is NULL, then the plugins will determine where to register the service */
/*
 *  NSLStandardRegisterURL()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in NSLPPCLib 1.1 and later
 */
extern NSLError 
NSLStandardRegisterURL(
  NSLPath           urlToRegister,
  NSLNeighborhood   neighborhoodToRegisterIn)       /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* <--- error code from registration */
/* ---> urlToRegister is a null terminated url that has only legal characters defined for URLs.  Use HexEncodeText to encode*/
/*          portions of the url that have illegal characters */
/* ---> neighborhoodToDeregisterIn is an optional parameter for explicitly defining a neighborhood to register in.
            If parameter is NULL, then the plugins will determine where to register the service */
/*
 *  NSLStandardDeregisterURL()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in NSLPPCLib 1.1 and later
 */
extern NSLError 
NSLStandardDeregisterURL(
  NSLPath           urlToDeregister,
  NSLNeighborhood   neighborhoodToDeregisterIn)       /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*-----------------------------------------------------------------------------*/

/*
 *  NSLHexEncodeText()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in NSLPPCLib 1.1 and later
 */
extern OSStatus 
NSLHexEncodeText(
  const char *  rawText,
  UInt16        rawTextLen,
  char *        newTextBuffer,
  UInt16 *      newTextBufferLen,
  Boolean *     textChanged)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  NSLHexDecodeText()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in NSLPPCLib 1.1 and later
 */
extern OSStatus 
NSLHexDecodeText(
  const char *  encodedText,
  UInt16        encodedTextLen,
  char *        decodedTextBuffer,
  UInt16 *      decodedTextBufferLen,
  Boolean *     textChanged)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
  -----------------------------------------------------------------------------
    Basic API Utility calls: sufficient to create, and parse data structures
  -----------------------------------------------------------------------------
*/

/*
 *  NSLMakeNewServicesList()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in NSLPPCLib 1.0 and later
 */
extern NSLServicesList 
NSLMakeNewServicesList(const char * initialServiceList)       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  NSLAddServiceToServicesList()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in NSLPPCLib 1.0 and later
 */
extern NSLError 
NSLAddServiceToServicesList(
  NSLServicesList   serviceList,
  NSLServiceType    serviceType)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  NSLDisposeServicesList()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in NSLPPCLib 1.0 and later
 */
extern void 
NSLDisposeServicesList(NSLServicesList theList)               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
    The name reflects the name of the Neighborhood, i.e. "apple.com." or "AppleTalk Zone One".
    The protocolList is a comma delimited list of protocols that the Neighborhood might exist in.
    If the user passes in NULL, then all protocols will be queried.  The result must be disposed
    of by the user by calling NSLFreeNeighborhood.
*/
/*
 *  NSLMakeNewNeighborhood()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in NSLPPCLib 1.0 and later
 */
extern NSLNeighborhood 
NSLMakeNewNeighborhood(
  const char *  name,
  const char *  protocolList)       /* can be NULL */         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* creates an exact copy of an existing neighborhood */
/*
 *  NSLCopyNeighborhood()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in NSLPPCLib 1.1 and later
 */
extern NSLNeighborhood 
NSLCopyNeighborhood(NSLNeighborhood neighborhood)             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  NSLFreeNeighborhood()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in NSLPPCLib 1.0 and later
 */
extern NSLNeighborhood 
NSLFreeNeighborhood(NSLNeighborhood neighborhood)             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  NSLGetNameFromNeighborhood()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in NSLPPCLib 1.0 and later
 */
extern void 
NSLGetNameFromNeighborhood(
  NSLNeighborhood   neighborhood,
  char **           name,
  long *            length)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
   create a block of formatted data, pointed to by newDataPtr.  This will be used
   in calls (typically request-related calls) for plug-ins that handle the NSL data type.
*/
/*
 *  NSLMakeServicesRequestPB()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in NSLPPCLib 1.0 and later
 */
extern OSStatus 
NSLMakeServicesRequestPB(
  NSLServicesList    serviceList,
  NSLTypedDataPtr *  newDataPtr)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* releases any storage created with MakeXXXPB calls, associated with TypedData.*/
/*
 *  NSLFreeTypedDataPtr()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in NSLPPCLib 1.0 and later
 */
extern NSLTypedDataPtr 
NSLFreeTypedDataPtr(NSLTypedDataPtr nslTypeData)              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
   utility function that returns whether a url was found, a pointer to the beginning
   of the url, and the length of the URL.
*/
/*
 *  NSLGetNextUrl()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in NSLPPCLib 1.0 and later
 */
extern Boolean 
NSLGetNextUrl(
  NSLClientAsyncInfoPtr   infoPtr,
  char **                 urlPtr,
  long *                  urlLength)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
   utility function that returns whether a Neighborhood was found, a pointer to the beginning
   of the Neighborhood, and the length of the Neighborhood.
*/
/*
 *  NSLGetNextNeighborhood()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in NSLPPCLib 1.0 and later
 */
extern Boolean 
NSLGetNextNeighborhood(
  NSLClientAsyncInfoPtr   infoPtr,
  NSLNeighborhood *       neighborhood,
  long *                  neighborhoodLength)                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
   NSLErrorToString:    convert a numeric error code to its string equivalent.  Caller must
                        have allocated sufficient space to store both strings.  (Max 255 chars each)
                                
                        The errorString parameter will return a textual explanation of what is wrong,
                        while the solutionString returns a possible solution to get around the problem
*/

/*
 *  NSLErrorToString()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in NSLPPCLib 1.0 and later
 */
extern OSStatus 
NSLErrorToString(
  NSLError   theErr,
  char *     errorString,
  char *     solutionString)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
  -----------------------------------------------------------------------------
    Basic API calls: sufficient to create simple requests, and receive answers
  -----------------------------------------------------------------------------
*/

/*
 *  NSLOpenNavigationAPI()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in NSLPPCLib 1.0 and later
 */
extern OSStatus 
NSLOpenNavigationAPI(NSLClientRef * newRef)                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  NSLCloseNavigationAPI()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in NSLPPCLib 1.0 and later
 */
extern void 
NSLCloseNavigationAPI(NSLClientRef theClient)                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
    NSLPrepareRequest:  creates an NSLRequestRef, sets up some internal data
    notifier is an NSLClientNotifyUPP that will be called when data is available, when the lookup has
    completed, or if an error occurs.  When the notifier is called, the cookie will be the NSLRequestRef.
    If notifier is NULL, then the NSLManager will assume that the request is made synchronously.  This
    should only be used while in a separate thread, so that the client app can still process events, etc.
    
    contextPtr is a void* which is passed as the contextPtr argument when the notifier is called.  
    
    upon exit:
    1) ref will contain a pointer to a NSLRequestRef which must be passed to all other functions
    which require a NSLRequestRef.
    2) infoPtr will point to a newly created ClientAsycnInfoPtr which will be disposed by the manager when the search is completed
    NOTE: Only one search can be running at a time per clientRef.
*/

/*
 *  NSLPrepareRequest()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in NSLPPCLib 1.0 and later
 */
extern NSLError 
NSLPrepareRequest(
  NSLClientNotifyUPP       notifier,
  void *                   contextPtr,
  NSLClientRef             theClient,
  NSLRequestRef *          ref,
  char *                   bufPtr,
  unsigned long            bufLen,
  NSLClientAsyncInfoPtr *  infoPtr)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
   NSLStartNeighborhoodLookup: looking for neighborhoods associated with or neighboring a particular neighborhood
    Passing in NULL for neighborhood will generate a list of a default neighborhood(s)
   
*/

/*
 *  NSLStartNeighborhoodLookup()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in NSLPPCLib 1.0 and later
 */
extern NSLError 
NSLStartNeighborhoodLookup(
  NSLRequestRef         ref,
  NSLNeighborhood       neighborhood,
  NSLClientAsyncInfo *  asyncInfo)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
   NSLStartServicesLookup: starts looking for entities if the specified type in the specified neighborhood
   
*/

/*
 *  NSLStartServicesLookup()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in NSLPPCLib 1.0 and later
 */
extern NSLError 
NSLStartServicesLookup(
  NSLRequestRef         ref,
  NSLNeighborhood       neighborhood,
  NSLTypedDataPtr       requestData,
  NSLClientAsyncInfo *  asyncInfo)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/* NSLContinueLookup:  continues a paused/outstanding lookup*/

/*
 *  NSLContinueLookup()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in NSLPPCLib 1.0 and later
 */
extern NSLError 
NSLContinueLookup(NSLClientAsyncInfo * asyncInfo)             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/* NSLCancelRequest: cancels an ongoing search*/

/*
 *  NSLCancelRequest()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in NSLPPCLib 1.0 and later
 */
extern NSLError 
NSLCancelRequest(NSLRequestRef ref)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
   NSLDeleteRequest: deletes info associated with this ref.  The ClientAsyncInfoPtr will no longer be valid
    This must be called when the client is no longer using this requestRef.
*/

/*
 *  NSLDeleteRequest()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in NSLPPCLib 1.0 and later
 */
extern NSLError 
NSLDeleteRequest(NSLRequestRef ref)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
  -----------------------------------------------------------------------------
   Utility API calls: use these accessors to manipulate NSL's typed data
  -----------------------------------------------------------------------------
*/

/* NSLParseServicesRequestPB provides the inverse of NSLMakeRequestPB, filling out the offsets found within newDataPtr*/
/* <--- returns an OSStatus if any errors occur parsing the data */
/* <--- newDataPtr is the construct passed to the plugin */
/* ---> serviceListPtr is the address of a pointer which will be set to point at the portion of the newDataPtr that holds the serviceList to be searched */
/* ---> serviceListLen is the length of the serviceListPtr data pointed to by serviceListPtr */
/*
 *  NSLParseServicesRequestPB()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in NSLPPCLib 1.0 and later
 */
extern OSStatus 
NSLParseServicesRequestPB(
  NSLTypedDataPtr   newDataPtr,
  char **           serviceListPtr,
  UInt16 *          serviceListLen)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/* NSLParseServiceRegistrationPB provides for breaking apart a registration request from a client to a plugin */
/* <--- returns an OSStatus if any errors occur parsing the data */
/* <--- newDataPtr is the construct passed to the plugin */
/* ---> neighborhoodPtr gets set to point at the portion of the newDataPtr that contains the neighborhood */
/* ---> neighborhoodLen is the length of the neighborhood pointed to by neighborhoodPtr */
/* ---> urlPtr is the address of a pointer which will be set to point at the portion of the newDataPtr that holds the url to be registered */
/* ---> urlLen is the length of the url data pointed to by urlPtr */
/*
 *  NSLParseServiceRegistrationPB()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in NSLPPCLib 1.1 and later
 */
extern OSStatus 
NSLParseServiceRegistrationPB(
  NSLTypedDataPtr    newDataPtr,
  NSLNeighborhood *  neighborhoodPtr,
  UInt16 *           neighborhoodLen,
  char **            urlPtr,
  UInt16 *           urlLen)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* NSLGetErrorStringsFromResource is obsolete in X.  It will ignore the fileSpecPtr */
/* and errorResID parameters and return the standard error strings. */
/* NSLGetErrorStringsFromResource makes a basic assumption: */
/* errorString and solutionString both point to valid memory of at least 256 bytes! */
/* <--- returns an OSStatus if any errors occur */
/* ---> theErr is an OSStatus to be matched against a resource list of errors */
/* ---> fileSpecPtr is a FSSpecPtr to the resource containing the list of errors */
/* ---> errorResID is the resourceID of the NSLI resource of the list of errors */
/* <--> errorString is a pointer to valid memory of at least 256 bytes which will be filled out by the error portion of the error string */
/* <--> solutionString is a pointer to valid memory of at least 256 bytes which will be filled out by the solution portion of the error string */
/*
 *  NSLGetErrorStringsFromResource()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in NSLPPCLib 1.1 and later
 */
extern OSStatus 
NSLGetErrorStringsFromResource(
  OSStatus        theErr,
  const FSSpec *  fileSpecPtr,
  SInt16          errorResID,
  char *          errorString,
  char *          solutionString)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* <--- Returns true if given service is in the given service list */
/* ---> serviceList is a valid NSLServicesList containing information about services to be searched */
/* ---> svcToFind is an NSLServiceType of a particular service to check if it is in the serviceList */
/*
 *  NSLServiceIsInServiceList()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in NSLPPCLib 1.1 and later
 */
extern Boolean 
NSLServiceIsInServiceList(
  NSLServicesList   serviceList,
  NSLServiceType    svcToFind)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* <--- returns an OSStatus if any errors occur parsing the data */
/* ---> svcString is the address of a pointer which will be set to point at the portion of theURL that holds the serviceType of theURL */
/* ---> svcLen is the length of the serviceType pointed to by svcString */
/*
 *  NSLGetServiceFromURL()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in NSLPPCLib 1.1 and later
 */
extern OSStatus 
NSLGetServiceFromURL(
  char *    theURL,
  char **   svcString,
  UInt16 *  svcLen)                                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* <--- returns the length of a Neighborhood data structure */
/* ---> neighborhood is a valid NSLNeighborhood */
/*
 *  NSLGetNeighborhoodLength()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in NSLPPCLib 1.1 and later
 */
extern long 
NSLGetNeighborhoodLength(NSLNeighborhood neighborhood)        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
  -------------------------------------------------------------------------------------
   Utility API calls: use these routines to separate plugin threads from client threads
  -------------------------------------------------------------------------------------
*/

/* this routine works the same as the Thread manager's routine NewThread, except */
/* that the thread is added to the NSL manager's thread list. */
/*
 *  NSLNewThread()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in NSLPPCLib 1.1 and later
 */
extern OSErr 
NSLNewThread(
  ThreadStyle          threadStyle,
  ThreadEntryProcPtr   threadEntry,
  void *               threadParam,
  Size                 stackSize,
  ThreadOptions        options,
  void **              threadResult,
  ThreadID *           threadMade)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* this routine works the same as the Thread manager's routine DisposeThread, except */
/* that the thread is removed from the NSL manager's thread list. */
/*
 *  NSLDisposeThread()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in NSLPPCLib 1.1 and later
 */
extern OSErr 
NSLDisposeThread(
  ThreadID   threadToDump,
  void *     threadResult,
  Boolean    recycleThread)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



#if OLDROUTINENAMES
typedef NSLClientAsyncInfo              ClientAsyncInfo;
typedef NSLPluginAsyncInfo              PluginAsyncInfo;
typedef NSLTypedData                    TypedData;
typedef NSLPluginData                   PluginData;
typedef NSLClientAsyncInfoPtr           ClientAsyncInfoPtr;
typedef NSLPluginAsyncInfoPtr           PluginAsyncInfoPtr;
typedef NSLTypedDataPtr                 TypedDataPtr;
typedef NSLPluginDataPtr                PluginDataPtr;

#endif  /* OLDROUTINENAMES */


#pragma options align=reset

#ifdef __cplusplus
}
#endif

#endif /* __NSLCORE__ */

