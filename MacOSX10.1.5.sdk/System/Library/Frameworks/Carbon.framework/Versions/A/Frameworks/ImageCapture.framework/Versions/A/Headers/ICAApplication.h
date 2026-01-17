/*
     File:       ImageCapture/ICAApplication.h
 
     Contains:   General purpose Image Capture definitions
 
     Version:    ImageCapture-84.1~4
 
     Copyright:  © 2000-2001 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __ICAAPPLICATION__
#define __ICAAPPLICATION__

#ifndef __MACTYPES__
#include <CarbonCore/MacTypes.h>
#endif

#ifndef __FILES__
#include <CarbonCore/Files.h>
#endif

#ifndef __CFDICTIONARY__
#include <CoreFoundation/CFDictionary.h>
#endif




#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if PRAGMA_STRUCT_ALIGN
    #pragma options align=mac68k
#elif PRAGMA_STRUCT_PACKPUSH
    #pragma pack(push, 2)
#elif PRAGMA_STRUCT_PACK
    #pragma pack(2)
#endif

typedef struct OpaqueICAObject*         ICAObject;
typedef struct OpaqueICAProperty*       ICAProperty;
typedef struct OpaqueICAConnectionID*   ICAConnectionID;
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
  kICAPropertyTypeNotFoundErr   = -9908
};

/* ICAObject types and subtypes */
enum {
  kICADevice                    = 'icdv', /* Also creator of device library files */
  kICADeviceCamera              = 'cmra', /* Also file type of device library files */
  kICADeviceScanner             = 'scan', /* Also file type of device library files */
  kICADeviceMFP                 = 'mfp ', /* Also file type of device library files */
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
  kICAMessageCheckDevice        = 'chkd'
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
  kSetFileTypeAndCreator        = 0x00000010,
  kEmbedColorSyncProfile        = 0x00000020,
  kRotateImage                  = 0x00000040
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

  ICAObject           object;                 /* <-- */
  OSType              notifyType;             /* <-- */
  ICACompletion       notifyProc;             /* <-- */
};
typedef struct ICARegisterEventNotificationPB ICARegisterEventNotificationPB;
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
 *    Non-Carbon CFM:   in ImageCaptureLib 1.0 and later
 */
extern OSErr 
ICAGetChildCount(
  ICAGetChildCountPB *  pb,
  ICACompletion         completion);      /* can be NULL */


/*
 *  ICAGetNthChild()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in ImageCaptureLib 1.0 and later
 */
extern OSErr 
ICAGetNthChild(
  ICAGetNthChildPB *  pb,
  ICACompletion       completion);      /* can be NULL */


/*
 *  ICAGetObjectInfo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in ImageCaptureLib 1.0 and later
 */
extern OSErr 
ICAGetObjectInfo(
  ICAGetObjectInfoPB *  pb,
  ICACompletion         completion);      /* can be NULL */


/*
 *  ICAGetParentOfObject()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in ImageCaptureLib 1.0 and later
 */
extern OSErr 
ICAGetParentOfObject(
  ICAGetParentOfObjectPB *  pb,
  ICACompletion             completion);      /* can be NULL */


/*
 *  ICAGetRootOfObject()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in ImageCaptureLib 1.0 and later
 */
extern OSErr 
ICAGetRootOfObject(
  ICAGetRootOfObjectPB *  pb,
  ICACompletion           completion);      /* can be NULL */


/*
 *  ICAGetObjectRefCon()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in ImageCaptureLib 1.0 and later
 */
extern OSErr 
ICAGetObjectRefCon(
  ICAGetObjectRefConPB *  pb,
  ICACompletion           completion);      /* can be NULL */


/*
 *  ICASetObjectRefCon()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in ImageCaptureLib 1.0 and later
 */
extern OSErr 
ICASetObjectRefCon(
  ICASetObjectRefConPB *  pb,
  ICACompletion           completion);      /* can be NULL */



/*
--------------- Property functions --------------- 
*/
/*
 *  ICAGetPropertyCount()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in ImageCaptureLib 1.0 and later
 */
extern OSErr 
ICAGetPropertyCount(
  ICAGetPropertyCountPB *  pb,
  ICACompletion            completion);      /* can be NULL */


/*
 *  ICAGetNthProperty()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in ImageCaptureLib 1.0 and later
 */
extern OSErr 
ICAGetNthProperty(
  ICAGetNthPropertyPB *  pb,
  ICACompletion          completion);      /* can be NULL */


/*
 *  ICAGetPropertyByType()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in ImageCaptureLib 1.0 and later
 */
extern OSErr 
ICAGetPropertyByType(
  ICAGetPropertyByTypePB *  pb,
  ICACompletion             completion);      /* can be NULL */


/*
 *  ICAGetPropertyInfo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in ImageCaptureLib 1.0 and later
 */
extern OSErr 
ICAGetPropertyInfo(
  ICAGetPropertyInfoPB *  pb,
  ICACompletion           completion);      /* can be NULL */


/*
 *  ICAGetPropertyData()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in ImageCaptureLib 1.0 and later
 */
extern OSErr 
ICAGetPropertyData(
  ICAGetPropertyDataPB *  pb,
  ICACompletion           completion);      /* can be NULL */


/*
 *  ICASetPropertyData()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in ImageCaptureLib 1.0 and later
 */
extern OSErr 
ICASetPropertyData(
  ICASetPropertyDataPB *  pb,
  ICACompletion           completion);      /* can be NULL */


/*
 *  ICAGetParentOfProperty()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in ImageCaptureLib 1.0 and later
 */
extern OSErr 
ICAGetParentOfProperty(
  ICAGetParentOfPropertyPB *  pb,
  ICACompletion               completion);      /* can be NULL */


/*
 *  ICAGetRootOfProperty()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in ImageCaptureLib 1.0 and later
 */
extern OSErr 
ICAGetRootOfProperty(
  ICAGetRootOfPropertyPB *  pb,
  ICACompletion             completion);      /* can be NULL */


/*
 *  ICAGetPropertyRefCon()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in ImageCaptureLib 1.0 and later
 */
extern OSErr 
ICAGetPropertyRefCon(
  ICAGetPropertyRefConPB *  pb,
  ICACompletion             completion);      /* can be NULL */


/*
 *  ICASetPropertyRefCon()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in ImageCaptureLib 1.0 and later
 */
extern OSErr 
ICASetPropertyRefCon(
  ICASetPropertyRefConPB *  pb,
  ICACompletion             completion);      /* can be NULL */



/* 
--------------- Device functions --------------- 
*/
/*
 *  ICAGetDeviceList()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in ImageCaptureLib 1.0 and later
 */
extern OSErr 
ICAGetDeviceList(
  ICAGetDeviceListPB *  pb,
  ICACompletion         completion);      /* can be NULL */


/*
 *  ICAObjectSendMessage()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in ImageCaptureLib 1.0 and later
 */
extern OSErr 
ICAObjectSendMessage(
  ICAObjectSendMessagePB *  pb,
  ICACompletion             completion);      /* can be NULL */


/*
 *  ICARegisterEventNotification()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in ImageCaptureLib 1.0 and later
 */
extern OSErr 
ICARegisterEventNotification(
  ICARegisterEventNotificationPB *  pb,
  ICACompletion                     completion);      /* can be NULL */




/* 
------------------------------------------------ 
*/
/*
 *  ICADownloadFile()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.4 and later
 *    Non-Carbon CFM:   in ImageCaptureLib 1.0 and later
 */
extern OSErr 
ICADownloadFile(
  ICADownloadFilePB *  pb,
  ICACompletion        completion);      /* can be NULL */



/*
 *  ICACopyObjectPropertyDictionary()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.4 and later
 *    Non-Carbon CFM:   in ImageCaptureLib 1.0 and later
 */
extern OSErr 
ICACopyObjectPropertyDictionary(
  ICACopyObjectPropertyDictionaryPB *  pb,
  ICACompletion                        completion);      /* can be NULL */



#if PRAGMA_STRUCT_ALIGN
    #pragma options align=reset
#elif PRAGMA_STRUCT_PACKPUSH
    #pragma pack(pop)
#elif PRAGMA_STRUCT_PACK
    #pragma pack()
#endif

#ifdef __cplusplus
}
#endif

#endif /* __ICAAPPLICATION__ */

