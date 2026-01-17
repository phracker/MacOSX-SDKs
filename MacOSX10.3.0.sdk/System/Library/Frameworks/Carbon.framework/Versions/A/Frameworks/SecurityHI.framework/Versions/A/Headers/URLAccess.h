/*
     File:       SecurityHI/URLAccess.h
 
     Contains:   URL Access Interfaces.
 
     Version:    SecurityHI-90~157
 
     Copyright:  © 1994-2003 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __URLACCESS__
#define __URLACCESS__

#ifndef __HITOOLBOX__
#include <HIToolbox/HIToolbox.h>
#endif


#include <AvailabilityMacros.h>

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

#pragma options align=mac68k

/* Data structures and types */
typedef struct OpaqueURLReference*      URLReference;
typedef UInt32 URLOpenFlags;
enum {
  kURLReplaceExistingFlag       = 1 << 0,
  kURLBinHexFileFlag            = 1 << 1, /* Binhex before uploading if necessary*/
  kURLExpandFileFlag            = 1 << 2, /* Use StuffIt engine to expand file if necessary*/
  kURLDisplayProgressFlag       = 1 << 3,
  kURLDisplayAuthFlag           = 1 << 4, /* Display auth dialog if guest connection fails*/
  kURLUploadFlag                = 1 << 5, /* Do an upload instead of a download*/
  kURLIsDirectoryHintFlag       = 1 << 6, /* Hint: the URL is a directory*/
  kURLDoNotTryAnonymousFlag     = 1 << 7, /* Don't try to connect anonymously before getting logon info*/
  kURLDirectoryListingFlag      = 1 << 8, /* Download the directory listing, not the whole directory*/
  kURLExpandAndVerifyFlag       = 1 << 9, /* Expand file and then verify using signature resource*/
  kURLNoAutoRedirectFlag        = 1 << 10, /* Do not automatically redirect to new URL*/
  kURLDebinhexOnlyFlag          = 1 << 11, /* Do not use Stuffit Expander - just internal debinhex engine*/
  kURLDoNotDeleteOnErrorFlag    = 1 << 12, /* Do not delete the downloaded file if an error or abort occurs.*/
                                        /* This flag applies to downloading only and should be used if*/
                                        /* interested in later resuming the download.*/
  kURLResumeDownloadFlag        = 1 << 13, /* The passed in file is partially downloaded, attempt to resume*/
                                        /* it.  Currently works for HTTP only.  If no FSSpec passed in,*/
                                        /* this flag will be ignored. Overriden by kURLReplaceExistingFlag. */
  kURLReservedFlag              = (unsigned long)(1 << 31) /* reserved for Apple internal use*/
};

typedef UInt32 URLState;
enum {
  kURLNullState                 = 0,
  kURLInitiatingState           = 1,
  kURLLookingUpHostState        = 2,
  kURLConnectingState           = 3,
  kURLResourceFoundState        = 4,
  kURLDownloadingState          = 5,
  kURLDataAvailableState        = 0x10 + kURLDownloadingState,
  kURLTransactionCompleteState  = 6,
  kURLErrorOccurredState        = 7,
  kURLAbortingState             = 8,
  kURLCompletedState            = 9,
  kURLUploadingState            = 10
};

typedef UInt32 URLEvent;
enum {
  kURLInitiatedEvent            = kURLInitiatingState,
  kURLResourceFoundEvent        = kURLResourceFoundState,
  kURLDownloadingEvent          = kURLDownloadingState,
  kURLAbortInitiatedEvent       = kURLAbortingState,
  kURLCompletedEvent            = kURLCompletedState,
  kURLErrorOccurredEvent        = kURLErrorOccurredState,
  kURLDataAvailableEvent        = kURLDataAvailableState,
  kURLTransactionCompleteEvent  = kURLTransactionCompleteState,
  kURLUploadingEvent            = kURLUploadingState,
  kURLSystemEvent               = 29,
  kURLPercentEvent              = 30,
  kURLPeriodicEvent             = 31,
  kURLPropertyChangedEvent      = 32
};

typedef unsigned long                   URLEventMask;
enum {
  kURLInitiatedEventMask        = 1 << (kURLInitiatedEvent - 1),
  kURLResourceFoundEventMask    = 1 << (kURLResourceFoundEvent - 1),
  kURLDownloadingMask           = 1 << (kURLDownloadingEvent - 1),
  kURLUploadingMask             = 1 << (kURLUploadingEvent - 1),
  kURLAbortInitiatedMask        = 1 << (kURLAbortInitiatedEvent - 1),
  kURLCompletedEventMask        = 1 << (kURLCompletedEvent - 1),
  kURLErrorOccurredEventMask    = 1 << (kURLErrorOccurredEvent - 1),
  kURLDataAvailableEventMask    = 1 << (kURLDataAvailableEvent - 1),
  kURLTransactionCompleteEventMask = 1 << (kURLTransactionCompleteEvent - 1),
  kURLSystemEventMask           = 1 << (kURLSystemEvent - 1),
  kURLPercentEventMask          = 1 << (kURLPercentEvent - 1),
  kURLPeriodicEventMask         = 1 << (kURLPeriodicEvent - 1),
  kURLPropertyChangedEventMask  = 1 << (kURLPropertyChangedEvent - 1),
  kURLAllBufferEventsMask       = kURLDataAvailableEventMask + kURLTransactionCompleteEventMask,
  kURLAllNonBufferEventsMask    = kURLInitiatedEventMask + kURLDownloadingMask + kURLUploadingMask + kURLAbortInitiatedMask + kURLCompletedEventMask + kURLErrorOccurredEventMask + kURLPercentEventMask + kURLPeriodicEventMask + kURLPropertyChangedEventMask,
  kURLAllEventsMask             = (long)0xFFFFFFFF
};


struct URLCallbackInfo {
  UInt32              version;
  URLReference        urlRef;
  const char *        property;
  UInt32              currentSize;
  EventRecord *       systemEvent;
};
typedef struct URLCallbackInfo          URLCallbackInfo;

/* authentication type flags*/
enum {
  kUserNameAndPasswordFlag      = 0x00000001
};

#define kURLURL                         "URLString"
#define kURLResourceSize                "URLResourceSize"
#define kURLLastModifiedTime            "URLLastModifiedTime"
#define kURLMIMEType                    "URLMIMEType"
#define kURLFileType                    "URLFileType"
#define kURLFileCreator                 "URLFileCreator"
#define kURLCharacterSet                "URLCharacterSet"
#define kURLResourceName                "URLResourceName"
#define kURLHost                        "URLHost"
#define kURLAuthType                    "URLAuthType"
#define kURLUserName                    "URLUserName"
#define kURLPassword                    "URLPassword"
#define kURLStatusString                "URLStatusString"
#define kURLIsSecure                    "URLIsSecure"
#define kURLCertificate                 "URLCertificate"
#define kURLTotalItems                  "URLTotalItems"
#define kURLConnectTimeout              "URLConnectTimeout"
/* http and https properties*/
#define kURLHTTPRequestMethod           "URLHTTPRequestMethod"
#define kURLHTTPRequestHeader           "URLHTTPRequestHeader"
#define kURLHTTPRequestBody             "URLHTTPRequestBody"
#define kURLHTTPRespHeader              "URLHTTPRespHeader"
#define kURLHTTPUserAgent               "URLHTTPUserAgent"
#define kURLHTTPRedirectedURL           "URLHTTPRedirectedURL"
#define kURLSSLCipherSuite              "URLSSLCipherSuite"




/*
 *  URLGetURLAccessVersion()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in URLAccessLib 1.0 and later
 */
extern OSStatus 
URLGetURLAccessVersion(UInt32 * returnVers)                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



#if TARGET_RT_MAC_CFM
#ifdef __cplusplus
    inline pascal Boolean URLAccessAvailable() { return ((URLGetURLAccessVersion != (void*)kUnresolvedCFragSymbolAddress) ); }
#else
    #define URLAccessAvailable()    ((URLGetURLAccessVersion != (void*)kUnresolvedCFragSymbolAddress) )
#endif
#elif TARGET_RT_MAC_MACHO
/* URL Access is always available on OS X */
#ifdef __cplusplus
    inline pascal Boolean URLAccessAvailable() { return true; }
#else
    #define URLAccessAvailable()    (true)
#endif
#endif  /*  */

typedef CALLBACK_API( OSStatus , URLNotifyProcPtr )(void *userContext, URLEvent event, URLCallbackInfo *callbackInfo);
typedef CALLBACK_API( OSStatus , URLSystemEventProcPtr )(void *userContext, EventRecord *event);
typedef STACK_UPP_TYPE(URLNotifyProcPtr)                        URLNotifyUPP;
typedef STACK_UPP_TYPE(URLSystemEventProcPtr)                   URLSystemEventUPP;
/*
 *  NewURLNotifyUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern URLNotifyUPP
NewURLNotifyUPP(URLNotifyProcPtr userRoutine)                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewURLSystemEventUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern URLSystemEventUPP
NewURLSystemEventUPP(URLSystemEventProcPtr userRoutine)       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeURLNotifyUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeURLNotifyUPP(URLNotifyUPP userUPP)                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeURLSystemEventUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeURLSystemEventUPP(URLSystemEventUPP userUPP)           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeURLNotifyUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern OSStatus
InvokeURLNotifyUPP(
  void *             userContext,
  URLEvent           event,
  URLCallbackInfo *  callbackInfo,
  URLNotifyUPP       userUPP)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeURLSystemEventUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern OSStatus
InvokeURLSystemEventUPP(
  void *             userContext,
  EventRecord *      event,
  URLSystemEventUPP  userUPP)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  URLSimpleDownload()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in URLAccessLib 1.0 and later
 */
extern OSStatus 
URLSimpleDownload(
  const char *        url,
  FSSpec *            destination,             /* can be NULL */
  Handle              destinationHandle,       /* can be NULL */
  URLOpenFlags        openFlags,
  URLSystemEventUPP   eventProc,               /* can be NULL */
  void *              userContext)             /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  URLDownload()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in URLAccessLib 1.0 and later
 */
extern OSStatus 
URLDownload(
  URLReference        urlRef,
  FSSpec *            destination,             /* can be NULL */
  Handle              destinationHandle,       /* can be NULL */
  URLOpenFlags        openFlags,
  URLSystemEventUPP   eventProc,               /* can be NULL */
  void *              userContext)             /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  URLSimpleUpload()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in URLAccessLib 1.0 and later
 */
extern OSStatus 
URLSimpleUpload(
  const char *        url,
  const FSSpec *      source,
  URLOpenFlags        openFlags,
  URLSystemEventUPP   eventProc,         /* can be NULL */
  void *              userContext)       /* can be NULL */    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  URLUpload()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in URLAccessLib 1.0 and later
 */
extern OSStatus 
URLUpload(
  URLReference        urlRef,
  const FSSpec *      source,
  URLOpenFlags        openFlags,
  URLSystemEventUPP   eventProc,         /* can be NULL */
  void *              userContext)       /* can be NULL */    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  URLNewReference()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in URLAccessLib 1.0 and later
 */
extern OSStatus 
URLNewReference(
  const char *    url,
  URLReference *  urlRef)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  URLDisposeReference()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in URLAccessLib 1.0 and later
 */
extern OSStatus 
URLDisposeReference(URLReference urlRef)                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  URLOpen()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in URLAccessLib 1.0 and later
 */
extern OSStatus 
URLOpen(
  URLReference   urlRef,
  FSSpec *       fileSpec,            /* can be NULL */
  URLOpenFlags   openFlags,
  URLNotifyUPP   notifyProc,          /* can be NULL */
  URLEventMask   eventRegister,
  void *         userContext)         /* can be NULL */       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  URLAbort()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in URLAccessLib 1.0 and later
 */
extern OSStatus 
URLAbort(URLReference urlRef)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  URLGetDataAvailable()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in URLAccessLib 1.0 and later
 */
extern OSStatus 
URLGetDataAvailable(
  URLReference   urlRef,
  Size *         dataSize)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  URLGetBuffer()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in URLAccessLib 1.0 and later
 */
extern OSStatus 
URLGetBuffer(
  URLReference   urlRef,
  void **        buffer,
  Size *         bufferSize)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  URLReleaseBuffer()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in URLAccessLib 1.0 and later
 */
extern OSStatus 
URLReleaseBuffer(
  URLReference   urlRef,
  void *         buffer)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  URLGetProperty()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in URLAccessLib 1.0 and later
 */
extern OSStatus 
URLGetProperty(
  URLReference   urlRef,
  const char *   property,
  void *         propertyBuffer,
  Size           bufferSize)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  URLGetPropertySize()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in URLAccessLib 1.0 and later
 */
extern OSStatus 
URLGetPropertySize(
  URLReference   urlRef,
  const char *   property,
  Size *         propertySize)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  URLSetProperty()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in URLAccessLib 1.0 and later
 */
extern OSStatus 
URLSetProperty(
  URLReference   urlRef,
  const char *   property,
  void *         propertyBuffer,
  Size           bufferSize)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  URLGetCurrentState()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in URLAccessLib 1.0 and later
 */
extern OSStatus 
URLGetCurrentState(
  URLReference   urlRef,
  URLState *     state)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  URLGetError()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in URLAccessLib 1.0 and later
 */
extern OSStatus 
URLGetError(
  URLReference   urlRef,
  OSStatus *     urlError)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  URLIdle()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in URLAccessLib 1.0 and later
 */
extern OSStatus 
URLIdle(void)                                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  URLGetFileInfo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in URLAccessLib 1.0 and later
 */
extern OSStatus 
URLGetFileInfo(
  StringPtr   fName,
  OSType *    fType,
  OSType *    fCreator)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



#pragma options align=reset

#ifdef __cplusplus
}
#endif

#endif /* __URLACCESS__ */

