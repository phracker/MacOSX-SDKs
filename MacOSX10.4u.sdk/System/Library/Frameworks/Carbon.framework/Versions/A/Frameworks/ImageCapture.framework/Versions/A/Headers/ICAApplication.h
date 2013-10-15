/*
     File:       ImageCapture/ICAApplication.h
 
     Contains:   General purpose Image Capture definitions
 
     Version:    ImageCaptureFramework-328~385
 
     Copyright:  © 2000-2006 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __ICAAPPLICATION__
#define __ICAAPPLICATION__

#include <IOKit/IOTypes.h>
#ifndef __CORESERVICES__
#include <CoreServices/CoreServices.h>
#endif


#include <AvailabilityMacros.h>

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

#pragma options align=mac68k

typedef struct OpaqueICAObject*         ICAObject;
typedef struct OpaqueICAProperty*       ICAProperty;
typedef struct OpaqueICAConnectionID*   ICAConnectionID;
typedef struct OpaqueICAEventDataCookie*  ICAEventDataCookie;
typedef struct OpaqueICAScannerSessionID*  ICAScannerSessionID;
/*
--------------- Defines --------------- 
*/
/* Error codes (Image Capture range = -9900...-9949)*/
enum {
  kICACommunicationErr          = -9900,
  kICADeviceNotFoundErr         = -9901,
  kICADeviceNotOpenErr          = -9902,
  kICAFileCorruptedErr          = -9903,
  kICAIOPendingErr              = -9904,
  kICAInvalidObjectErr          = -9905,
  kICAInvalidPropertyErr        = -9906,
  kICAIndexOutOfRangeErr        = -9907,
  kICAPropertyTypeNotFoundErr   = -9908,
  kICACannotYieldDevice         = -9909,
  kICADataTypeNotFoundErr       = -9910,
  kICADeviceMemoryAllocationErr = -9911,
  kICADeviceInternalErr         = -9912,
  kICADeviceInvalidParamErr     = -9913,
  kICADeviceAlreadyOpenErr      = -9914,
  kICADeviceLocationIDNotFoundErr = -9915,
  kICADeviceGUIDNotFoundErr     = -9916,
  kICADeviceIOServicePathNotFoundErr = -9917
};

/* ICAObject types and subtypes */
enum {
  kICADevice                    = 'icdv', /* Also creator of device library files */
  kICADeviceCamera              = 'cmra', /* Also file type of device library files */
  kICADeviceScanner             = 'scan', /* Also file type of device library files */
  kICADeviceMFP                 = 'mfp ', /* Also file type of device library files */
  kICADevicePhone               = 'phon',
  kICADevicePDA                 = 'pda ',
  kICADeviceOther               = 'doth',
  kICAList                      = 'objl',
  kICADirectory                 = 'dire',
  kICAFile                      = 'file',
  kICAFileImage                 = 'imag',
  kICAFileMovie                 = 'moov',
  kICAFileAudio                 = 'audo',
  kICAFileFirmware              = 'firm',
  kICAFileOther                 = 'othe'
};

/* ICAProperties */
enum {
  kICAProperty                  = 'prop', /* */
                                        /*    file properties */
                                        /* */
                                        /* for images, refer to 'Digital Still Camera Image File Format Standard' Exif Version 2.1 section 2.6.4. and 2.6.5.*/
  kICAPropertyImageWidth        = '0100', /* UInt32 */
  kICAPropertyImageHeight       = '0101', /* UInt32 */
  kICAPropertyImageBitDepth     = '0102', /* UInt32 */
  kICAPropertyImageDPI          = '011A', /* UInt32 */
  kICAPropertyImageExposureTime = '829A',
  kICAPropertyImageFNumber      = '829D',
  kICAPropertyImageDateOriginal = '9003', /* null terminated string (YYYYMMDDThhmmss.s) */
  kICAPropertyImageDateDigitized = '9004', /* null terminated string (YYYYMMDDThhmmss.s) */
  kICAPropertyImageShutterSpeed = '9201', /* */
  kICAPropertyImageAperture     = '9202', /* */
  kICAPropertyImageFlash        = '9209', /* UInt16*/
  kICAPropertyColorSpace        = 'A001', /* UInt16*/
  kICAPropertyImageFilename     = 'ifil', /* null terminated string */
  kICAPropertyImageSize         = 'isiz', /* UInt32 */
  kICAPropertyImageData         = 'idat', /* void * */
  kICAPropertyImageThumbnail    = 'thum', /* void * */
  kICAPropertyColorSyncProfile  = 'prof'
};

/* Messages */
enum {
  kICAMessageConnect            = 'open',
  kICAMessageDisconnect         = 'clos',
  kICAMessageReset              = 'rese',
  kICAMessageCheckDevice        = 'chkd',
  kICAMessageCameraReadClock    = 'rclk',
  kICAMessageGetLastButtonPressed = 'btn?'
};


/* Data type definitions, mapped to AppleEvent types */
enum {
  kICATypeUInt16                = 'ui16', /* UInt16 */
  kICATypeUInt32                = 'ui32', /* UInt32 */
  kICATypeUInt64                = 'ui64', /* UInt64 */
  kICATypeSInt16                = 'si16', /* SInt16 */
  kICATypeSInt32                = 'si32', /* SInt32 */
  kICATypeSInt64                = 'si64', /* SInt64 */
  kICATypeFixed                 = 'sing', /* typeIEEE32BitFloatingPoint */
  kICATypeBoolean               = 'bool', /* typeBoolean */
  kICATypeString                = 'TEXT', /* typeChar */
  kICATypeData                  = 'data', /* void * */
  kICATypeThumbnail             = 'thum' /* ICAThumbnail*/
};


/* Flags for PropertyInfo flag element */
enum {
  kICAFlagReadWriteAccess       = 1L << 0,
  kICAFlagReadAccess            = 1L << 1
};



/* Notification types (Refer to section 12.4 of PTP spec) */
enum {
  kICAEventCancelTransaction    = 'ecnt',
  kICAEventObjectAdded          = 'eoba',
  kICAEventObjectRemoved        = 'eobr',
  kICAEventStoreAdded           = 'esta',
  kICAEventStoreRemoved         = 'estr',
  kICAEventDeviceAdded          = 'edea',
  kICAEventDeviceRemoved        = 'eder',
  kICAEventDevicePropChanged    = 'edpc',
  kICAEventObjectInfoChanged    = 'eoic',
  kICAEventDeviceInfoChanged    = 'edic',
  kICAEventRequestObjectTransfer = 'erot',
  kICAEventStoreFull            = 'estf',
  kICAEventDeviceReset          = 'edvr',
  kICAEventStorageInfoChanged   = 'esic',
  kICAEventCaptureComplete      = 'ecpc',
  kICAEventUnreportedStatus     = 'eurs'
};


/* Used for partial reads via ICAGetPropertyData */
enum {
  kICAStartAtBeginning          = 0,
  kICAEntireLength              = -1
};


/* ICADownloadFile flags */
enum {
  kDeleteAfterDownload          = 0x00000001,
  kCreateCustomIcon             = 0x00000002,
  kAddMetaDataToFinderComment   = 0x00000004,
  kAdjustCreationDate           = 0x00000008,
  kSetFileTypeAndCreator        = 0x00000010, /*kEmbedColorSyncProfile   = 0x00000020,*/
  kRotateImage                  = 0x00000040,
  kDontEmbedColorSyncProfile    = 0x00000080
};


/* extended notification */
enum {
  kExtendedNotificationPB       = 'extd',
  kMessageGetEventData          = 'mged',
  kEventClassPTPStandard        = 'PTPs',
  kEventClassPTPVendor          = 'PTPv'
};


/* button types*/
enum {
  kICAButtonScan                = 'scan',
  kICAButtonCopy                = 'copy',
  kICAButtonEMail               = 'mail',
  kICAButtonWeb                 = 'web '
};


/*
--------------- Structures --------------- 
*/
struct ICAObjectInfo {
  OSType              objectType;             /* i.e. kICAFile*/
  OSType              objectSubtype;          /* i.e. kICAFileImage  */
};
typedef struct ICAObjectInfo            ICAObjectInfo;
 
 
struct ICAPropertyInfo {
  OSType              propertyType;
  OSType              dataType;
  UInt32              dataSize;
  UInt32              dataFlags;
};
typedef struct ICAPropertyInfo          ICAPropertyInfo;
 
 
struct ICAMessage {
  OSType              messageType;            /* <--  i.e. kICAMessageCameraCaptureNewImage */
  UInt32              startByte;              /* <-- */
  void *              dataPtr;                /* <-- */
  UInt32              dataSize;               /* <-- */
  OSType              dataType;               /* <-- */
};
typedef struct ICAMessage               ICAMessage;
 
 
struct ICAThumbnail {
  UInt32              width;
  UInt32              height;
  UInt32              dataSize;
  UInt8               data[1];                /* 8-bit RGB data (RGBRGBRGB...)*/
};
typedef struct ICAThumbnail             ICAThumbnail;
enum {
  kICAPBVersion                 = 0x00010000
};

/* 
--------------- Completion Procs --------------- 
*/
/*
   
   NOTE: the parameter for the completion proc (ICAHeader*) has to be casted to the appropriate type
   e.g. (ICAGetChildCountPB*), ...
   
*/

typedef struct ICAHeader                ICAHeader;
typedef CALLBACK_API_C( void , ICACompletion )(ICAHeader * pb);
/* 
--------------- ICAHeader --------------- 
*/
 
 
struct ICAHeader {
  OSErr               err;                    /* --> */
  UInt32              refcon;                 /* <-- */
};

/*
--------------- Object parameter blocks --------------- 
*/
 
 
struct ICAGetChildCountPB {
  ICAHeader           header;
  ICAObject           object;                 /* <-- */
  UInt32              count;                  /* --> */
};
typedef struct ICAGetChildCountPB       ICAGetChildCountPB;
 
 
struct ICAGetNthChildPB {
  ICAHeader           header;
  ICAObject           parentObject;           /* <-- */
  UInt32              index;                  /* <-- zero based */
  ICAObject           childObject;            /* --> */
  ICAObjectInfo       childInfo;              /* --> */
};
typedef struct ICAGetNthChildPB         ICAGetNthChildPB;
 
 
struct ICAGetObjectInfoPB {
  ICAHeader           header;
  ICAObject           object;                 /* <-- */
  ICAObjectInfo       objectInfo;             /* --> */
};
typedef struct ICAGetObjectInfoPB       ICAGetObjectInfoPB;
 
 
struct ICAGetParentOfObjectPB {
  ICAHeader           header;
  ICAObject           object;                 /* <-- */
  ICAObject           parentObject;           /* --> */
  ICAObjectInfo       parentInfo;             /* --> */
};
typedef struct ICAGetParentOfObjectPB   ICAGetParentOfObjectPB;
 
 
struct ICAGetRootOfObjectPB {
  ICAHeader           header;
  ICAObject           object;                 /* <-- */
  ICAObject           rootObject;             /* --> */
  ICAObjectInfo       rootInfo;               /* --> */
};
typedef struct ICAGetRootOfObjectPB     ICAGetRootOfObjectPB;
 
 
struct ICAGetObjectRefConPB {
  ICAHeader           header;
  ICAObject           object;                 /* <-- */
  UInt32              objectRefCon;           /* --> */
};
typedef struct ICAGetObjectRefConPB     ICAGetObjectRefConPB;
 
 
struct ICASetObjectRefConPB {
  ICAHeader           header;
  ICAObject           object;                 /* <-- */
  UInt32              objectRefCon;           /* <-- */
};
typedef struct ICASetObjectRefConPB     ICASetObjectRefConPB;
/*
--------------- Property parameter blocks --------------- 
*/
 
 
struct ICAGetPropertyCountPB {
  ICAHeader           header;
  ICAObject           object;                 /* <-- */
  UInt32              count;                  /* --> */
};
typedef struct ICAGetPropertyCountPB    ICAGetPropertyCountPB;
 
 
struct ICAGetNthPropertyPB {
  ICAHeader           header;
  ICAObject           object;                 /* <-- */
  UInt32              index;                  /* <-- zero based */
  ICAProperty         property;               /* --> */
  ICAPropertyInfo     propertyInfo;           /* --> */
};
typedef struct ICAGetNthPropertyPB      ICAGetNthPropertyPB;
 
 
struct ICAGetPropertyByTypePB {
  ICAHeader           header;
  ICAObject           object;                 /* <-- */
  OSType              propertyType;           /* <-- */
  ICAProperty         property;               /* --> */
  ICAPropertyInfo     propertyInfo;           /* --> */
};
typedef struct ICAGetPropertyByTypePB   ICAGetPropertyByTypePB;
 
 
struct ICAGetPropertyInfoPB {
  ICAHeader           header;
  ICAProperty         property;               /* <-- */
  ICAPropertyInfo     propertyInfo;           /* --> */
};
typedef struct ICAGetPropertyInfoPB     ICAGetPropertyInfoPB;
 
 
struct ICAGetPropertyDataPB {
  ICAHeader           header;
  ICAProperty         property;               /* <-- */
  UInt32              startByte;              /* <-- */
  UInt32              requestedSize;          /* <-- */
  void *              dataPtr;                /* <-> */
  UInt32              actualSize;             /* --> */
  OSType              dataType;               /* --> */
};
typedef struct ICAGetPropertyDataPB     ICAGetPropertyDataPB;
 
 
struct ICASetPropertyDataPB {
  ICAHeader           header;
  ICAProperty         property;               /* <-- */
  UInt32              startByte;              /* <-- */
  void *              dataPtr;                /* <-- */
  UInt32              dataSize;               /* <-- */
  OSType              dataType;               /* <-- */
};
typedef struct ICASetPropertyDataPB     ICASetPropertyDataPB;
 
 
struct ICAGetParentOfPropertyPB {
  ICAHeader           header;
  ICAProperty         property;               /* <-- */
  ICAObject           parentObject;           /* --> */
  ICAObjectInfo       parentInfo;             /* --> */
};
typedef struct ICAGetParentOfPropertyPB ICAGetParentOfPropertyPB;
 
 
struct ICAGetRootOfPropertyPB {
  ICAHeader           header;
  ICAProperty         property;               /* <-- */
  ICAObject           rootObject;             /* --> */
  ICAObjectInfo       rootInfo;               /* --> */
};
typedef struct ICAGetRootOfPropertyPB   ICAGetRootOfPropertyPB;
 
 
struct ICAGetPropertyRefConPB {
  ICAHeader           header;
  ICAProperty         property;               /* <-- */
  UInt32              propertyRefCon;         /* --> */
};
typedef struct ICAGetPropertyRefConPB   ICAGetPropertyRefConPB;
 
 
struct ICASetPropertyRefConPB {
  ICAHeader           header;
  ICAProperty         property;               /* <-- */
  UInt32              propertyRefCon;         /* <-- */
};
typedef struct ICASetPropertyRefConPB   ICASetPropertyRefConPB;
/*
--------------- Device parameter blocks --------------- 
*/
 
 
struct ICAGetDeviceListPB {
  ICAHeader           header;
  ICAObject           object;                 /* --> */
};
typedef struct ICAGetDeviceListPB       ICAGetDeviceListPB;
 
 
struct ICAObjectSendMessagePB {
  ICAHeader           header;
  ICAObject           object;                 /* <-- */
  ICAMessage          message;                /* <-- */
  UInt32              result;                 /* --> message specific result*/
};
typedef struct ICAObjectSendMessagePB   ICAObjectSendMessagePB;
 
 
struct ICARegisterEventNotificationPB {
  ICAHeader           header;
  ICAObject           object;                 /* <-> */
  OSType              notifyType;             /* <-> */
  ICACompletion       notifyProc;             /* <-- */
};
typedef struct ICARegisterEventNotificationPB ICARegisterEventNotificationPB;
 
 
struct ICAExtendedRegisterEventNotificationPB {
  ICAHeader           header;
  ICAObject           object;                 /* <-> */
  OSType              extd;                   /* <-- */
  ICACompletion       notifyProc;             /* <-- */

  UInt32              rawEventType;           /* -->*/
  OSType              eventType;              /* <->*/
  OSType              eventClass;             /* -->*/
  UInt32              eventDataSize;          /* -->*/
  ICAEventDataCookie  eventDataCookie;        /* -->*/
  ICAObject           deviceObject;           /* -->*/
};
typedef struct ICAExtendedRegisterEventNotificationPB ICAExtendedRegisterEventNotificationPB;
 
 
struct ICADownloadFilePB {
  ICAHeader           header;
  ICAObject           object;                 /* <-- */
  FSRef *             dirFSRef;               /* <-- */
  UInt32              flags;                  /* <-- */
  OSType              fileType;               /* <-- */
  OSType              fileCreator;            /* <-- */
  Fixed               rotationAngle;          /* <-- */
  FSRef *             fileFSRef;              /* --> can be NULL*/
};
typedef struct ICADownloadFilePB        ICADownloadFilePB;
 
 
struct ICACopyObjectPropertyDictionaryPB {
  ICAHeader           header;
  ICAObject           object;                 /* <-- */
  CFDictionaryRef *   theDict;                /* --> */
};
typedef struct ICACopyObjectPropertyDictionaryPB ICACopyObjectPropertyDictionaryPB;
/*
   
   NOTE: for all APIs - pass NULL as completion parameter to make a synchronous call 
   
*/
/*
--------------- Object functions --------------- 
*/

/*
 *  ICAGetChildCount()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSErr 
ICAGetChildCount(
  ICAGetChildCountPB *  pb,
  ICACompletion         completion)       /* can be NULL */   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ICAGetNthChild()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSErr 
ICAGetNthChild(
  ICAGetNthChildPB *  pb,
  ICACompletion       completion)       /* can be NULL */     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ICAGetObjectInfo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSErr 
ICAGetObjectInfo(
  ICAGetObjectInfoPB *  pb,
  ICACompletion         completion)       /* can be NULL */   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ICAGetParentOfObject()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSErr 
ICAGetParentOfObject(
  ICAGetParentOfObjectPB *  pb,
  ICACompletion             completion)       /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ICAGetRootOfObject()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSErr 
ICAGetRootOfObject(
  ICAGetRootOfObjectPB *  pb,
  ICACompletion           completion)       /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ICAGetObjectRefCon()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSErr 
ICAGetObjectRefCon(
  ICAGetObjectRefConPB *  pb,
  ICACompletion           completion)       /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ICASetObjectRefCon()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSErr 
ICASetObjectRefCon(
  ICASetObjectRefConPB *  pb,
  ICACompletion           completion)       /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
--------------- Property functions --------------- 
*/
/*
 *  ICAGetPropertyCount()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSErr 
ICAGetPropertyCount(
  ICAGetPropertyCountPB *  pb,
  ICACompletion            completion)       /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ICAGetNthProperty()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSErr 
ICAGetNthProperty(
  ICAGetNthPropertyPB *  pb,
  ICACompletion          completion)       /* can be NULL */  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ICAGetPropertyByType()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSErr 
ICAGetPropertyByType(
  ICAGetPropertyByTypePB *  pb,
  ICACompletion             completion)       /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ICAGetPropertyInfo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSErr 
ICAGetPropertyInfo(
  ICAGetPropertyInfoPB *  pb,
  ICACompletion           completion)       /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ICAGetPropertyData()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSErr 
ICAGetPropertyData(
  ICAGetPropertyDataPB *  pb,
  ICACompletion           completion)       /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ICASetPropertyData()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSErr 
ICASetPropertyData(
  ICASetPropertyDataPB *  pb,
  ICACompletion           completion)       /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ICAGetParentOfProperty()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSErr 
ICAGetParentOfProperty(
  ICAGetParentOfPropertyPB *  pb,
  ICACompletion               completion)       /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ICAGetRootOfProperty()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSErr 
ICAGetRootOfProperty(
  ICAGetRootOfPropertyPB *  pb,
  ICACompletion             completion)       /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ICAGetPropertyRefCon()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSErr 
ICAGetPropertyRefCon(
  ICAGetPropertyRefConPB *  pb,
  ICACompletion             completion)       /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ICASetPropertyRefCon()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSErr 
ICASetPropertyRefCon(
  ICASetPropertyRefConPB *  pb,
  ICACompletion             completion)       /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/* 
--------------- Device functions --------------- 
*/
/*
 *  ICAGetDeviceList()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSErr 
ICAGetDeviceList(
  ICAGetDeviceListPB *  pb,
  ICACompletion         completion)       /* can be NULL */   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ICAObjectSendMessage()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSErr 
ICAObjectSendMessage(
  ICAObjectSendMessagePB *  pb,
  ICACompletion             completion)       /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ICARegisterEventNotification()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSErr 
ICARegisterEventNotification(
  ICARegisterEventNotificationPB *  pb,
  ICACompletion                     completion)       /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;




/* 
------------------------------------------------ 
*/
/*
 *  ICADownloadFile()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.4 and later
 *    Non-Carbon CFM:   not available
 */
extern OSErr 
ICADownloadFile(
  ICADownloadFilePB *  pb,
  ICACompletion        completion)       /* can be NULL */    AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;



/*
 *  ICACopyObjectPropertyDictionary()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.4 and later
 *    Non-Carbon CFM:   not available
 */
extern OSErr 
ICACopyObjectPropertyDictionary(
  ICACopyObjectPropertyDictionaryPB *  pb,
  ICACompletion                        completion)       /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;



/* 
--- scanner support --------------------------------------------- 
*/
struct ICAScannerOpenSessionPB {
  ICAHeader           header;
  ICAObject           object;                 /* <-- */
  ICAScannerSessionID  sessionID;             /* --> */
};
typedef struct ICAScannerOpenSessionPB  ICAScannerOpenSessionPB;
 
 
struct ICAScannerCloseSessionPB {
  ICAHeader           header;
  ICAScannerSessionID  sessionID;             /* <-- */
};
typedef struct ICAScannerCloseSessionPB ICAScannerCloseSessionPB;
 
 
struct ICAScannerInitializePB {
  ICAHeader           header;
  ICAScannerSessionID  sessionID;             /* <-- */
};
typedef struct ICAScannerInitializePB   ICAScannerInitializePB;
 
 
struct ICAScannerGetParametersPB {
  ICAHeader           header;
  ICAScannerSessionID  sessionID;             /* <-- */
  CFMutableDictionaryRef  theDict;            /* --> */
};
typedef struct ICAScannerGetParametersPB ICAScannerGetParametersPB;
 
 
struct ICAScannerSetParametersPB {
  ICAHeader           header;
  ICAScannerSessionID  sessionID;             /* <-- */
  CFMutableDictionaryRef  theDict;            /* <-> */
};
typedef struct ICAScannerSetParametersPB ICAScannerSetParametersPB;
 
 
struct ICAScannerStatusPB {
  ICAHeader           header;
  ICAScannerSessionID  sessionID;             /* <-- */
  UInt32              status;                 /* --> */
};
typedef struct ICAScannerStatusPB       ICAScannerStatusPB;
 
 
struct ICAScannerStartPB {
  ICAHeader           header;
  ICAScannerSessionID  sessionID;             /* <-- */
};
typedef struct ICAScannerStartPB        ICAScannerStartPB;
 
 
/*
 *  ICAScannerOpenSession()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.6 and later
 *    Non-Carbon CFM:   not available
 */
extern OSErr 
ICAScannerOpenSession(
  ICAScannerOpenSessionPB *  pb,
  ICACompletion              completion)       /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  ICAScannerCloseSession()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.6 and later
 *    Non-Carbon CFM:   not available
 */
extern OSErr 
ICAScannerCloseSession(
  ICAScannerCloseSessionPB *  pb,
  ICACompletion               completion)       /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  ICAScannerInitialize()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.6 and later
 *    Non-Carbon CFM:   not available
 */
extern OSErr 
ICAScannerInitialize(
  ICAScannerInitializePB *  pb,
  ICACompletion             completion)       /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  ICAScannerGetParameters()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.6 and later
 *    Non-Carbon CFM:   not available
 */
extern OSErr 
ICAScannerGetParameters(
  ICAScannerGetParametersPB *  pb,
  ICACompletion                completion)       /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  ICAScannerSetParameters()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.6 and later
 *    Non-Carbon CFM:   not available
 */
extern OSErr 
ICAScannerSetParameters(
  ICAScannerSetParametersPB *  pb,
  ICACompletion                completion)       /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  ICAScannerStatus()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.6 and later
 *    Non-Carbon CFM:   not available
 */
extern OSErr 
ICAScannerStatus(
  ICAScannerStatusPB *  pb,
  ICACompletion         completion)       /* can be NULL */   AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  ICAScannerStart()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.6 and later
 *    Non-Carbon CFM:   not available
 */
extern OSErr 
ICAScannerStart(
  ICAScannerStartPB *  pb,
  ICACompletion        completion)       /* can be NULL */    AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


 
 
 
 
/* 
--- new APIs for Panther --------------------------------------------- 
*/

/* ICADeviceYield*/
enum {
  kICAMessageDeviceYield        = 'yiel'
};

 
 
/* ICAImportImage*/
enum {
  kICAAllowMultipleImages       = 0x00000001,
  kICADownloadAndReturnPathArray = 0x00000002
};

typedef CALLBACK_API_C( Boolean , ICAImportFilterProc )(CFDictionaryRef imageInfo, UInt32 refcon);
struct ICAImportImagePB {
  ICAHeader           header;                 /* <-- */
  ICAObject           deviceObject;           /* <-- */
  UInt32              flags;                  /* <-- */
  CFArrayRef          supportedFileTypes;     /* <-- */
  ICAImportFilterProc  filterProc;            /* <-- */
  CFArrayRef *        importedImages;         /* --> */
};
typedef struct ICAImportImagePB         ICAImportImagePB;
 
/*
 *  ICAImportImage()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern OSErr 
ICAImportImage(
  ICAImportImagePB *  pb,
  ICACompletion       completion)       /* can be NULL */     AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


 
 
/* ICACopyObjectThumbnail */
enum {
  kICAThumbnailFormatICA        = 'ica ',
  kICAThumbnailFormatJPEG       = 'jpeg',
  kICAThumbnailFormatTIFF       = 'tiff'
};

struct ICACopyObjectThumbnailPB {
  ICAHeader           header;                 /* <-- */
  ICAObject           object;                 /* <-- */
  OSType              thumbnailFormat;        /* <-- */
  CFDataRef *         thumbnailData;          /* --> */
};
typedef struct ICACopyObjectThumbnailPB ICACopyObjectThumbnailPB;
/*
 *  ICACopyObjectThumbnail()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern OSErr 
ICACopyObjectThumbnail(
  ICACopyObjectThumbnailPB *  pb,
  ICACompletion               completion)       /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


 
/* 
--- new APIs for Tiger --------------------------------------------- 
*/
 
/* Special device list objects */
enum {
  kICANetworkDeviceList         = 'netw',
  kICAManualConnectDeviceList   = 'manc'
};

 
/* Transport types */
/*
 *  kICAUSBTransportType
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kICAUSBTransportType                        AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/*
 *  kICAFireWireTransportType
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kICAFireWireTransportType                   AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/*
 *  kICABluetoothTransportType
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kICABluetoothTransportType                  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/*
 *  kICATCPIPTransportType
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kICATCPIPTransportType                      AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/*
 *  kICASCSITransportType
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kICASCSITransportType                       AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/*
 *  kICATWAINTransportType
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kICATWAINTransportType                      AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
 
/* Keys used for paramDictionary in ICALoadDeviceModulePB*/
/*
 *  kICADeviceModulePathKey
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kICADeviceModulePathKey                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/*
 *  kICATransportTypeKey
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kICATransportTypeKey                        AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/*
 *  kICABluetoothAddressKey
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kICABluetoothAddressKey                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/*
 *  kICAUSBLocationIDKey
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kICAUSBLocationIDKey                        AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/*
 *  kICAFireWireGUIDKey
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kICAFireWireGUIDKey                         AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/*
 *  kICAIOServicePathKey
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kICAIOServicePathKey                        AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/*
 *  kICAIPAddressKey
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kICAIPAddressKey                            AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/*
 *  kICAIPPortKey
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kICAIPPortKey                               AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/*
 *  kICAIPNameKey
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kICAIPNameKey                               AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/*
 *  kICAIPGUIDKey
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kICAIPGUIDKey                               AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/*
 *  kICATWAINDSPathKey
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kICATWAINDSPathKey                          AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
 
/* struct ICALoadDeviceModulePB
    Legal Key-Value pairs for populating paramDictionary:
            
    Key                             Value                               Comment
    
    kICADeviceModulePathKey         CFStringRef                         Path to the device module bundle that needs to be launched.
    kICATransportTypeKey            CFStringRef                         Should be one of the six predifined transport types.
    kICABluetoothAddressKey         CFStringRef                         Bluetooth device address string formatted as "00-11-22-33-44-55". 
    kICAUSBLocationIDKey            CFNumberRef (kCFNumberLongType)     32 bit USB location ID.
    kICAFireWireGUIDKey             CFNumberRef (kCFNumberLongLongType) 64 bit FireWire GUID.                                                               
    kICAIOServicePathKey            CFStringRef                         IO service path to the device obtained from the IO registry.
    kICAIPAddressKey                CFStringRef                         IP address of the device. This can be a host address ("camera.apple.com"),
                                                                        ipv4 address ('192.168.123.10") or ipv6 address ("3ff3:0000:0000:0000:0123:4567:89ab:cdef")
    kICAIPPortKey                   CFNumberRef (kCFNumberLongType)     IP port number of the device.
    kICAIPNameKey                   CFStringRef                         Human readable device name.
    kICAIPGUIDKey                   CFStringRef                         16 byte GUID string of the device formatted as "01234567-89ab-cdef-0123-456789abcdef".
    kICATWAINDSPathKey              CFStringRef                         Path to TWAIN DS bundle. */
 
/* ICALoadDeviceModule */
 
struct ICALoadDeviceModulePB {
  ICAHeader           header;                 /* <-> */
  CFDictionaryRef     paramDictionary;        /* <-- */
};
typedef struct ICALoadDeviceModulePB    ICALoadDeviceModulePB;
 
/*
 *  ICALoadDeviceModule()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern OSErr 
ICALoadDeviceModule(
  ICALoadDeviceModulePB *  pb,
  ICACompletion            completion)       /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


 
/* ICAUnloadDeviceModule */
 
struct ICAUnloadDeviceModulePB {
  ICAHeader           header;                 /* <-> */
  ICAObject           deviceObject;           /* <-- */
};
typedef struct ICAUnloadDeviceModulePB  ICAUnloadDeviceModulePB;
 
/*
 *  ICAUnloadDeviceModule()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern OSErr 
ICAUnloadDeviceModule(
  ICAUnloadDeviceModulePB *  pb,
  ICACompletion              completion)       /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


 
/* ICAUploadFile */
 
enum {
  kICAUploadFileAsIs            = 0x00000000,
  kICAUploadFileScaleToFit      = 0x00000001
};

 
struct ICAUploadFilePB {
  ICAHeader           header;
  ICAObject           parentObject;           /* <-- */
  FSRef *             fileFSRef;              /* <-- */
  UInt32              flags;                  /* <-- */
};
typedef struct ICAUploadFilePB          ICAUploadFilePB;
 
/*
 *  ICAUploadFile()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern OSErr 
ICAUploadFile(
  ICAUploadFilePB *  pb,
  ICACompletion      completion)       /* can be NULL */      AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


 
/* ICAOpenSession */
 
struct ICAOpenSessionPB {
  ICAHeader           header;                 /* <-> */
  ICAObject           deviceObject;           /* <-- */
  UInt32              sessionID;              /* --> */
};
typedef struct ICAOpenSessionPB         ICAOpenSessionPB;
 
/*
 *  ICAOpenSession()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern OSErr 
ICAOpenSession(
  ICAOpenSessionPB *  pb,
  ICACompletion       completion)       /* can be NULL */     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


 
/* ICACloseSession */
 
struct ICACloseSessionPB {
  ICAHeader           header;                 /* <-> */
  UInt32              sessionID;              /* <-- */
};
typedef struct ICACloseSessionPB        ICACloseSessionPB;
 
/*
 *  ICACloseSession()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern OSErr 
ICACloseSession(
  ICACloseSessionPB *  pb,
  ICACompletion        completion)       /* can be NULL */    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;



#pragma options align=reset

#ifdef __cplusplus
}
#endif

#endif /* __ICAAPPLICATION__ */

