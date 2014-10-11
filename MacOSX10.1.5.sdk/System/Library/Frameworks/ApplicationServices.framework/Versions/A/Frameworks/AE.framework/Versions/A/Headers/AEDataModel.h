/*
     File:       AE/AEDataModel.h
 
     Contains:   AppleEvent Data Model Interfaces.
 
     Version:    AppleEvents-116~3
 
     Copyright:  © 1996-2001 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __AEDATAMODEL__
#define __AEDATAMODEL__

#ifndef __MACTYPES__
#include <CarbonCore/MacTypes.h>
#endif

#ifndef __MIXEDMODE__
#include <CarbonCore/MixedMode.h>
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

/* Apple event descriptor types */
enum {
  typeBoolean                   = 'bool',
  typeChar                      = 'TEXT'
};

/* Preferred numeric Apple event descriptor types */
enum {
  typeSInt16                    = 'shor',
  typeSInt32                    = 'long',
  typeUInt32                    = 'magn',
  typeSInt64                    = 'comp',
  typeIEEE32BitFloatingPoint    = 'sing',
  typeIEEE64BitFloatingPoint    = 'doub',
  type128BitFloatingPoint       = 'ldbl',
  typeDecimalStruct             = 'decm'
};

/* Non-preferred Apple event descriptor types */
enum {
  typeSMInt                     = typeSInt16,
  typeShortInteger              = typeSInt16,
  typeInteger                   = typeSInt32,
  typeLongInteger               = typeSInt32,
  typeMagnitude                 = typeUInt32,
  typeComp                      = typeSInt64,
  typeSMFloat                   = typeIEEE32BitFloatingPoint,
  typeShortFloat                = typeIEEE32BitFloatingPoint,
  typeFloat                     = typeIEEE64BitFloatingPoint,
  typeLongFloat                 = typeIEEE64BitFloatingPoint,
  typeExtended                  = 'exte'
};

/* More Apple event descriptor types */
enum {
  typeAEList                    = 'list',
  typeAERecord                  = 'reco',
  typeAppleEvent                = 'aevt',
  typeEventRecord               = 'evrc',
  typeTrue                      = 'true',
  typeFalse                     = 'fals',
  typeAlias                     = 'alis',
  typeEnumerated                = 'enum',
  typeType                      = 'type',
  typeAppParameters             = 'appa',
  typeProperty                  = 'prop',
  typeFSS                       = 'fss ',
  typeFSRef                     = 'fsrf',
  typeFileURL                   = 'furl',
  typeKeyword                   = 'keyw',
  typeSectionH                  = 'sect',
  typeWildCard                  = '****',
  typeApplSignature             = 'sign',
  typeQDRectangle               = 'qdrt',
  typeFixed                     = 'fixd',
  typeProcessSerialNumber       = 'psn ',
  typeApplicationURL            = 'aprl',
  typeNull                      = 'null' /* null or nonexistent data */
};

/* New addressing modes for MacOS X */
enum {
  typeKernelProcessID           = 'kpid',
  typeMachPort                  = 'port'
};

/* Keywords for Apple event attributes */
enum {
  keyTransactionIDAttr          = 'tran',
  keyReturnIDAttr               = 'rtid',
  keyEventClassAttr             = 'evcl',
  keyEventIDAttr                = 'evid',
  keyAddressAttr                = 'addr',
  keyOptionalKeywordAttr        = 'optk',
  keyTimeoutAttr                = 'timo',
  keyInteractLevelAttr          = 'inte', /* this attribute is read only - will be set in AESend */
  keyEventSourceAttr            = 'esrc', /* this attribute is read only - returned as typeShortInteger */
  keyMissedKeywordAttr          = 'miss', /* this attribute is read only */
  keyOriginalAddressAttr        = 'from', /* new in 1.0.1 */
  keyAcceptTimeoutAttr          = 'actm' /* new for Mac OS X */
};

/* These bits are specified in the keyXMLDebugginAttr (an SInt32) */
enum {
  kAEDebugPOSTHeader            = (1 << 0), /* headers of the HTTP post we sent - typeChar */
  kAEDebugReplyHeader           = (1 << 1), /* headers returned by the server */
  kAEDebugXMLRequest            = (1 << 2), /* the XML request we sent */
  kAEDebugXMLResponse           = (1 << 3), /* the XML reply from the server */
  kAEDebugXMLDebugAll           = (long)0xFFFFFFFF /* everything! */
};

/* These values can be added as a parameter to the direct object of a
   SOAP message to specify the serialization schema.  If not
   specified, kSOAP1999Schema is the default. These should be added as
   typeType. */
enum {
  kSOAP1999Schema               = 'ss99',
  kSOAP2001Schema               = 'ss01'
};

enum {
                                        /* outgoing event attributes */
  keyUserNameAttr               = 'unam',
  keyUserPasswordAttr           = 'pass', /* not sent with the event */
  keyDisableAuthenticationAttr  = 'auth', /* When present and with a non zero value (that is, false, or integer 0), */
                                        /* AESend will not authenticate the user.  If not present, or with a non-zero*/
                                        /* value, AESend will prompt for authentication information from the user if the interaction level allows. */
  keyXMLDebuggingAttr           = 'xdbg', /* a bitfield of specifying which XML debugging data is to be returned with the event */
                                        /* Event class / id */
  kAERPCClass                   = 'rpc ', /* for outgoing XML events */
  kAEXMLRPCScheme               = 'RPC2', /* event ID: event should be sent to an XMLRPC endpoint */
  kAESOAPScheme                 = 'SOAP', /* event ID: event should be sent to a SOAP endpoint */
  kAESharedScriptHandler        = 'wscp', /* event ID: handler for incoming XML requests */
                                        /* these parameters exist as part of the direct object of the event for both incoming and outgoing requests */
  keyRPCMethodName              = 'meth', /* name of the method to call */
  keyRPCMethodParam             = 'parm', /* the list (or structure) of parameters */
                                        /* when keyXMLDebugginAttr so specifies, these additional parameters will be part of the reply. */
  keyAEPOSTHeaderData           = 'phed', /* what we sent to the server */
  keyAEReplyHeaderData          = 'rhed', /* what the server sent to us */
  keyAEXMLRequestData           = 'xreq', /* what we sent to the server */
  keyAEXMLReplyData             = 'xrep', /* what the server sent to us */
                                        /* additional parameters that can be specified in the direct object of the event */
  keyAdditionalHTTPHeaders      = 'ahed', /* list of additional HTTP headers (a list of 2 element lists) */
  keySOAPAction                 = 'sact', /* the SOAPAction header (required for SOAP messages) */
  keySOAPMethodNameSpace        = 'mspc', /* Optional namespace (defaults to m:) */
  keySOAPMethodNameSpaceURI     = 'mspu', /* Required namespace URI */
  keySOAPSchemaVersion          = 'ssch' /* Optional XML Schema version, defaults to kSOAP1999Schama */
};

/* 
   When serializing AERecords as SOAP structures, it is possible for
   to specify the namespace and type of the structure.  To do this,
   add a keySOAPStructureMetaData record to the top level of the
   record to be serialized.  If present, this will be used to specify
   the structure namespace.  This will produce a structure elment that
   looks like:

    <myStruct
        xmlns:myNamespace="http://myUri.org/xsd",
        xsi:type="myNamespace:MyStructType">
        ...
    </myStruct>

*/
enum {
  keySOAPStructureMetaData      = '/smd',
  keySOAPSMDNamespace           = 'ssns', /* "myNamespace"*/
  keySOAPSMDNamespaceURI        = 'ssnu', /* "http://myUri.org/xsd"*/
  keySOAPSMDType                = 'sstp' /* "MyStructType"*/
};


/*  Constants used for specifying the factoring of AEDescLists. */
enum {
  kAEDescListFactorNone         = 0,
  kAEDescListFactorType         = 4,
  kAEDescListFactorTypeAndSize  = 8
};

/* Constants used creating an AppleEvent */
enum {
                                        /* Constant for the returnID param of AECreateAppleEvent */
  kAutoGenerateReturnID         = -1,   /* AECreateAppleEvent will generate a session-unique ID */
                                        /* Constant for transaction ID’s */
  kAnyTransactionID             = 0     /* no transaction is in use */
};

/* Apple event manager data types */
typedef ResType                         DescType;
typedef FourCharCode                    AEKeyword;
#if OPAQUE_TOOLBOX_STRUCTS
typedef struct OpaqueAEDataStorageType*  AEDataStorageType;
#else
typedef Ptr                             AEDataStorageType;
#endif  /* OPAQUE_TOOLBOX_STRUCTS */

typedef AEDataStorageType *             AEDataStorage;
struct AEDesc {
  DescType            descriptorType;
  AEDataStorage       dataHandle;
};
typedef struct AEDesc                   AEDesc;
typedef AEDesc *                        AEDescPtr;
struct AEKeyDesc {
  AEKeyword           descKey;
  AEDesc              descContent;
};
typedef struct AEKeyDesc                AEKeyDesc;
/* a list of AEDesc's is a special kind of AEDesc */

typedef AEDesc                          AEDescList;
/* AERecord is a list of keyworded AEDesc's */
typedef AEDescList                      AERecord;
/* an AEDesc which contains address data */
typedef AEDesc                          AEAddressDesc;
/* an AERecord that contains an AppleEvent, and related data types */
typedef AERecord                        AppleEvent;
typedef AppleEvent *                    AppleEventPtr;
typedef SInt16                          AEReturnID;
typedef SInt32                          AETransactionID;
typedef FourCharCode                    AEEventClass;
typedef FourCharCode                    AEEventID;
typedef SInt8                           AEArrayType;
enum {
  kAEDataArray                  = 0,
  kAEPackedArray                = 1,
  kAEDescArray                  = 3,
  kAEKeyDescArray               = 4
};


enum {
  kAEHandleArray                = 2
};

union AEArrayData {
  short               kAEDataArray[1];
  char                kAEPackedArray[1];
  Handle              kAEHandleArray[1];
  AEDesc              kAEDescArray[1];
  AEKeyDesc           kAEKeyDescArray[1];
};
typedef union AEArrayData               AEArrayData;
typedef AEArrayData *                   AEArrayDataPointer;
/**************************************************************************
  These constants are used by AEMach and AEInteraction APIs.  They are not
  strictly part of the data format, but are declared here due to layering.
**************************************************************************/
typedef SInt16 AESendPriority;
enum {
  kAENormalPriority             = 0x00000000, /* post message at the end of the event queue */
  kAEHighPriority               = 0x00000001 /* post message at the front of the event queue (same as nAttnMsg) */
};


typedef SInt32 AESendMode;
enum {
  kAENoReply                    = 0x00000001, /* sender doesn't want a reply to event */
  kAEQueueReply                 = 0x00000002, /* sender wants a reply but won't wait */
  kAEWaitReply                  = 0x00000003, /* sender wants a reply and will wait */
  kAEDontReconnect              = 0x00000080, /* don't reconnect if there is a sessClosedErr from PPCToolbox */
  kAEWantReceipt                = 0x00000200, /* (nReturnReceipt) sender wants a receipt of message */
  kAENeverInteract              = 0x00000010, /* server should not interact with user */
  kAECanInteract                = 0x00000020, /* server may try to interact with user */
  kAEAlwaysInteract             = 0x00000030, /* server should always interact with user where appropriate */
  kAECanSwitchLayer             = 0x00000040, /* interaction may switch layer */
  kAEDontRecord                 = 0x00001000, /* don't record this event - available only in vers 1.0.1 and greater */
  kAEDontExecute                = 0x00002000, /* don't send the event for recording - available only in vers 1.0.1 and greater */
  kAEProcessNonReplyEvents      = 0x00008000 /* allow processing of non-reply events while awaiting synchronous AppleEvent reply */
};


/* Constants for timeout durations */
enum {
  kAEDefaultTimeout             = -1,   /* timeout value determined by AEM */
  kNoTimeOut                    = -2    /* wait until reply comes back, however long it takes */
};


/**************************************************************************
  These calls are used to set up and modify the coercion dispatch table.
**************************************************************************/
typedef CALLBACK_API( OSErr , AECoerceDescProcPtr )(const AEDesc *fromDesc, DescType toType, long handlerRefcon, AEDesc *toDesc);
typedef CALLBACK_API( OSErr , AECoercePtrProcPtr )(DescType typeCode, const void *dataPtr, Size dataSize, DescType toType, long handlerRefcon, AEDesc *result);
typedef STACK_UPP_TYPE(AECoerceDescProcPtr)                     AECoerceDescUPP;
typedef STACK_UPP_TYPE(AECoercePtrProcPtr)                      AECoercePtrUPP;
/*
 *  NewAECoerceDescUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern AECoerceDescUPP
NewAECoerceDescUPP(AECoerceDescProcPtr userRoutine);

/*
 *  NewAECoercePtrUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern AECoercePtrUPP
NewAECoercePtrUPP(AECoercePtrProcPtr userRoutine);

/*
 *  DisposeAECoerceDescUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeAECoerceDescUPP(AECoerceDescUPP userUPP);

/*
 *  DisposeAECoercePtrUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeAECoercePtrUPP(AECoercePtrUPP userUPP);

/*
 *  InvokeAECoerceDescUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern OSErr
InvokeAECoerceDescUPP(
  const AEDesc *   fromDesc,
  DescType         toType,
  long             handlerRefcon,
  AEDesc *         toDesc,
  AECoerceDescUPP  userUPP);

/*
 *  InvokeAECoercePtrUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern OSErr
InvokeAECoercePtrUPP(
  DescType        typeCode,
  const void *    dataPtr,
  Size            dataSize,
  DescType        toType,
  long            handlerRefcon,
  AEDesc *        result,
  AECoercePtrUPP  userUPP);

/* a AECoercionHandlerUPP is by default a AECoerceDescUPP.  If you are registering a 
    Ptr based coercion handler you will have to add a cast to AECoerceDescUPP from 
    your AECoercePtrUPP type.  A future release of the interfaces will fix this by
    introducing seperate Desc and Ptr coercion handler installation/remove/query routines. */
typedef AECoerceDescUPP                 AECoercionHandlerUPP;
/*
 *  AEInstallCoercionHandler()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
AEInstallCoercionHandler(
  DescType               fromType,
  DescType               toType,
  AECoercionHandlerUPP   handler,
  long                   handlerRefcon,
  Boolean                fromTypeIsDesc,
  Boolean                isSysHandler);


/*
 *  AERemoveCoercionHandler()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
AERemoveCoercionHandler(
  DescType               fromType,
  DescType               toType,
  AECoercionHandlerUPP   handler,
  Boolean                isSysHandler);



/*
 *  AEGetCoercionHandler()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
AEGetCoercionHandler(
  DescType                fromType,
  DescType                toType,
  AECoercionHandlerUPP *  handler,
  long *                  handlerRefcon,
  Boolean *               fromTypeIsDesc,
  Boolean                 isSysHandler);


/**************************************************************************
  The following calls provide for a coercion interface.
**************************************************************************/
/*
 *  AECoercePtr()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
AECoercePtr(
  DescType      typeCode,
  const void *  dataPtr,
  Size          dataSize,
  DescType      toType,
  AEDesc *      result);


/*
 *  AECoerceDesc()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
AECoerceDesc(
  const AEDesc *  theAEDesc,
  DescType        toType,
  AEDesc *        result);



/**************************************************************************
 The following calls apply to any AEDesc. Every 'result' descriptor is
 created for you, so you will be responsible for memory management
 (including disposing) of the descriptors so created.  
**************************************************************************/
/* because AEDescs are opaque under Carbon, this AEInitializeDesc provides a
   'clean' way of initializating them to be empty. */
/*
 *  AEInitializeDesc()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.4 and later
 *    Non-Carbon CFM:   not available
 */
extern void 
AEInitializeDesc(AEDesc * desc);



#ifdef __cplusplus
    inline void AEInitializeDescInline(AEDesc* d) { d->descriptorType = typeNull; d->dataHandle = NULL; };
#else
   #define AEInitializeDescInline(__d) do { AEDesc* d = __d; d->descriptorType = typeNull; d->dataHandle = NULL; } while (0)
#endif


/*
 *  AECreateDesc()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
AECreateDesc(
  DescType      typeCode,
  const void *  dataPtr,
  Size          dataSize,
  AEDesc *      result);


/*
 *  AEDisposeDesc()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
AEDisposeDesc(AEDesc * theAEDesc);


/*
 *  AEDuplicateDesc()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
AEDuplicateDesc(
  const AEDesc *  theAEDesc,
  AEDesc *        result);



/**************************************************************************
  The following calls apply to AEDescList. Since AEDescList is a subtype of
  AEDesc, the calls in the previous section can also be used for AEDescList.
  All list and array indices are 1-based. If the data was greater than
  maximumSize in the routines below, then actualSize will be greater than
  maximumSize, but only maximumSize bytes will actually be retrieved.
**************************************************************************/
/*
 *  AECreateList()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
AECreateList(
  const void *  factoringPtr,
  Size          factoredSize,
  Boolean       isRecord,
  AEDescList *  resultList);


/*
 *  AECountItems()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
AECountItems(
  const AEDescList *  theAEDescList,
  long *              theCount);


/*
 *  AEPutPtr()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
AEPutPtr(
  AEDescList *  theAEDescList,
  long          index,
  DescType      typeCode,
  const void *  dataPtr,
  Size          dataSize);


/*
 *  AEPutDesc()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
AEPutDesc(
  AEDescList *    theAEDescList,
  long            index,
  const AEDesc *  theAEDesc);


/*
 *  AEGetNthPtr()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
AEGetNthPtr(
  const AEDescList *  theAEDescList,
  long                index,
  DescType            desiredType,
  AEKeyword *         theAEKeyword,
  DescType *          typeCode,
  void *              dataPtr,
  Size                maximumSize,
  Size *              actualSize);


/*
 *  AEGetNthDesc()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
AEGetNthDesc(
  const AEDescList *  theAEDescList,
  long                index,
  DescType            desiredType,
  AEKeyword *         theAEKeyword,
  AEDesc *            result);


/*
 *  AESizeOfNthItem()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
AESizeOfNthItem(
  const AEDescList *  theAEDescList,
  long                index,
  DescType *          typeCode,
  Size *              dataSize);


/*
 *  AEGetArray()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
AEGetArray(
  const AEDescList *   theAEDescList,
  AEArrayType          arrayType,
  AEArrayDataPointer   arrayPtr,
  Size                 maximumSize,
  DescType *           itemType,
  Size *               itemSize,
  long *               itemCount);


/*
 *  AEPutArray()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
AEPutArray(
  AEDescList *         theAEDescList,
  AEArrayType          arrayType,
  const AEArrayData *  arrayPtr,
  DescType             itemType,
  Size                 itemSize,
  long                 itemCount);


/*
 *  AEDeleteItem()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
AEDeleteItem(
  AEDescList *  theAEDescList,
  long          index);



/**************************************************************************
 The following calls apply to AERecord. Since AERecord is a subtype of
 AEDescList, the calls in the previous sections can also be used for
 AERecord an AERecord can be created by using AECreateList with isRecord
 set to true. 
**************************************************************************/
/*************************************************************************
 AERecords can have an abitrary descriptorType.  This allows you to
 check if desc is truly an AERecord
************************************************************************/
/*
 *  AECheckIsRecord()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.4 and later
 *    Non-Carbon CFM:   not available
 */
extern Boolean 
AECheckIsRecord(const AEDesc * theDesc);


/*
  Note: The following #defines map “key” calls on AERecords into “param” calls on 
  AppleEvents.  Although no errors are currently returned if AERecords are 
  passed to “param” calls and AppleEvents to “key” calls, the behavior of 
  this type of API-mixing is not explicitly documented in Inside Macintosh.  
  It just happens that the “key” calls have the same functionality as their 
  “param” counterparts.  Since none of the “key” calls are currently available 
  in the PowerPC IntefaceLib, the #defines exploit the fact that “key” and 
  “param” routines can be used interchangeably, and makes sure that every 
  invokation of a “key” API becomes an invokation of a “param” API.
*/
#define AEPutKeyPtr(theAERecord, theAEKeyword, typeCode, dataPtr, dataSize) \
    AEPutParamPtr((theAERecord), (theAEKeyword), (typeCode), (dataPtr), (dataSize))
#define AEPutKeyDesc(theAERecord, theAEKeyword, theAEDesc) \
    AEPutParamDesc((theAERecord), (theAEKeyword), (theAEDesc))
#define AEGetKeyPtr(theAERecord, theAEKeyword, desiredType, typeCode, dataPtr, maxSize, actualSize) \
    AEGetParamPtr((theAERecord), (theAEKeyword), (desiredType), (typeCode), (dataPtr), (maxSize), (actualSize))
#define AEGetKeyDesc(theAERecord, theAEKeyword, desiredType, result) \
    AEGetParamDesc((theAERecord), (theAEKeyword), (desiredType), (result))
#define AESizeOfKeyDesc(theAERecord, theAEKeyword, typeCode, dataSize) \
    AESizeOfParam((theAERecord), (theAEKeyword), (typeCode), (dataSize))
#define AEDeleteKeyDesc(theAERecord, theAEKeyword) \
    AEDeleteParam((theAERecord), (theAEKeyword))
/**************************************************************************
  The following calls create and manipulate the AppleEvent data type.
**************************************************************************/
/*
 *  AECreateAppleEvent()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
AECreateAppleEvent(
  AEEventClass           theAEEventClass,
  AEEventID              theAEEventID,
  const AEAddressDesc *  target,
  AEReturnID             returnID,
  AETransactionID        transactionID,
  AppleEvent *           result);



/**************************************************************************
  The following calls are used to pack and unpack parameters from records
  of type AppleEvent. Since AppleEvent is a subtype of AERecord, the calls
  in the previous sections can also be used for variables of type
  AppleEvent. The next six calls are in fact identical to the six calls
  for AERecord.
**************************************************************************/
/*
 *  AEPutParamPtr()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
AEPutParamPtr(
  AppleEvent *  theAppleEvent,
  AEKeyword     theAEKeyword,
  DescType      typeCode,
  const void *  dataPtr,
  Size          dataSize);


/*
 *  AEPutParamDesc()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
AEPutParamDesc(
  AppleEvent *    theAppleEvent,
  AEKeyword       theAEKeyword,
  const AEDesc *  theAEDesc);


/*
 *  AEGetParamPtr()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
AEGetParamPtr(
  const AppleEvent *  theAppleEvent,
  AEKeyword           theAEKeyword,
  DescType            desiredType,
  DescType *          typeCode,
  void *              dataPtr,
  Size                maximumSize,
  Size *              actualSize);


/*
 *  AEGetParamDesc()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
AEGetParamDesc(
  const AppleEvent *  theAppleEvent,
  AEKeyword           theAEKeyword,
  DescType            desiredType,
  AEDesc *            result);


/*
 *  AESizeOfParam()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
AESizeOfParam(
  const AppleEvent *  theAppleEvent,
  AEKeyword           theAEKeyword,
  DescType *          typeCode,
  Size *              dataSize);


/*
 *  AEDeleteParam()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
AEDeleteParam(
  AppleEvent *  theAppleEvent,
  AEKeyword     theAEKeyword);




/**************************************************************************
 The following calls also apply to type AppleEvent. Message attributes are
 far more restricted, and can only be accessed through the following 5
 calls. The various list and record routines cannot be used to access the
 attributes of an event. 
**************************************************************************/
/*
 *  AEGetAttributePtr()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
AEGetAttributePtr(
  const AppleEvent *  theAppleEvent,
  AEKeyword           theAEKeyword,
  DescType            desiredType,
  DescType *          typeCode,
  void *              dataPtr,
  Size                maximumSize,
  Size *              actualSize);


/*
 *  AEGetAttributeDesc()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
AEGetAttributeDesc(
  const AppleEvent *  theAppleEvent,
  AEKeyword           theAEKeyword,
  DescType            desiredType,
  AEDesc *            result);


/*
 *  AESizeOfAttribute()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
AESizeOfAttribute(
  const AppleEvent *  theAppleEvent,
  AEKeyword           theAEKeyword,
  DescType *          typeCode,
  Size *              dataSize);


/*
 *  AEPutAttributePtr()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
AEPutAttributePtr(
  AppleEvent *  theAppleEvent,
  AEKeyword     theAEKeyword,
  DescType      typeCode,
  const void *  dataPtr,
  Size          dataSize);


/*
 *  AEPutAttributeDesc()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
AEPutAttributeDesc(
  AppleEvent *    theAppleEvent,
  AEKeyword       theAEKeyword,
  const AEDesc *  theAEDesc);



/**************************************************************************
 AppleEvent Serialization Support

    AESizeOfFlattenedDesc, AEFlattenDesc, AEUnflattenDesc
    
    These calls will work for all AppleEvent data types and between different
    versions of the OS (including between Mac OS 9 and X)
    
    Basic types, AEDesc, AEList and AERecord are OK, but AppleEvent records
    themselves may not be reliably flattened for storage.
**************************************************************************/
/*
   AEFlattenDesc
   Returns the amount of buffer space needed to flatten the
   AEDesc. Call this before AEFlattenDesc to make sure your
   buffer has enough room for the operation.
*/

/*
 *  AESizeOfFlattenedDesc()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.4 and later
 *    Non-Carbon CFM:   not available
 */
extern Size 
AESizeOfFlattenedDesc(const AEDesc * theAEDesc);


/*
   AEFlattenDesc
   Fills a buffer with a flattened representation of the
   AEDesc and returns the amount of buffer used in actualSize.
   If bufferSize was too small it returns errAEBufferTooSmall
   (-1741) and does not fill in any of the buffer. The resulting
   buffer is only useful with an AEUnflattenDesc call.
   
   Note: if you pass a NULL buffer pointer it returns noErr but
   fills in the actualSize field anyway.
*/

/*
 *  AEFlattenDesc()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.4 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
AEFlattenDesc(
  const AEDesc *  theAEDesc,
  Ptr             buffer,
  Size            bufferSize,
  Size *          actualSize);


/*
   AEUnflattenDesc
   Allocates an AEDesc (given a Null Desc) given a flattened
   data buffer. It assumes it was given a good buffer filled
   in by AEFlattenDesc. It returns paramErr if it discovers
   something fishy about the buffer.
*/

/*
 *  AEUnflattenDesc()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.4 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
AEUnflattenDesc(
  Ptr       buffer,
  AEDesc *  result);


/**************************************************************************
 The following calls are necessary to deal with opaque data in AEDescs, because the
 traditional way of dealing with a basic AEDesc has been to dereference the dataHandle
 directly.  This is not supported under Carbon.
**************************************************************************/
/*
        AEGetDescData no longer supports automatic coercion. If you'd like to
        coerce the descriptor use AECoerceDesc.
    */
/*
 *  AEGetDescData()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern OSErr 
AEGetDescData(
  const AEDesc *  theAEDesc,
  void *          dataPtr,
  Size            maximumSize);


/*
 *  AEGetDescDataSize()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern Size 
AEGetDescDataSize(const AEDesc * theAEDesc);


/*
 *  AEReplaceDescData()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern OSErr 
AEReplaceDescData(
  DescType      typeCode,
  const void *  dataPtr,
  Size          dataSize,
  AEDesc *      theAEDesc);



/**************************************************************************
  A AEEventHandler is installed to process an AppleEvent 
**************************************************************************/
typedef CALLBACK_API( OSErr , AEEventHandlerProcPtr )(const AppleEvent *theAppleEvent, AppleEvent *reply, long handlerRefcon);
typedef STACK_UPP_TYPE(AEEventHandlerProcPtr)                   AEEventHandlerUPP;
/*
 *  NewAEEventHandlerUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern AEEventHandlerUPP
NewAEEventHandlerUPP(AEEventHandlerProcPtr userRoutine);

/*
 *  DisposeAEEventHandlerUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeAEEventHandlerUPP(AEEventHandlerUPP userUPP);

/*
 *  InvokeAEEventHandlerUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern OSErr
InvokeAEEventHandlerUPP(
  const AppleEvent *  theAppleEvent,
  AppleEvent *        reply,
  long                handlerRefcon,
  AEEventHandlerUPP   userUPP);



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

#endif /* __AEDATAMODEL__ */

