/*
 File:       ICADevices/ICA_ScannerCalls.h

 Contains:   Scanner module related interfaces

 Copyright:  © 2000-2002 by Apple Computer, Inc., all rights reserved.


 Bugs?:      For bug reports, consult the following page on
 the World Wide Web:

 http://developer.apple.com/bugreporter/

 */

#ifndef __ICD_ScannerCalls__
#define __ICD_ScannerCalls__

#include <Carbon/Carbon.h>
#include <CoreFoundation/CoreFoundation.h>
#include <IOBluetooth/Bluetooth.h>

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


/* DataTypes for _ICD_ReadFileData/_ICD_WriteFileData */
enum {
    kICS_FileData		= 'file',
    kICS_ThumbnailData	= 'thum',
    kICS_MetaData		= 'meta'
};

typedef struct ScannerObjectInfo
{
    ICAObject		icaObject;			// Apple
    UInt32			reserved;			// Apple
    ICAObjectInfo 	icaObjectInfo;		// vendor
    UInt32			uniqueID;			// vendor
    UInt64			uniqueIDFireWire;	// vendor
    UInt32			thumbnailSize;		// vendor
    UInt32			dataSize;			// vendor
    UInt32 			dataWidth;			// vendor
    UInt32 			dataHeight;			// vendor
    UInt8			name[32];			// vendor
    UInt8			creationDate[20];	// vendor
    UInt32			flags;				// vendor
    Ptr				privateData;		// vendor
} ScannerObjectInfo;

struct ICD_ScannerGetPropertyDataPB {
    ICDHeader                       header;

    ICAObject                       parentObject;               /* <-- */
    ICAObjectInfo                   parentObjectInfo;           /* <-- */
    ICAConnectionID            	  	connectionID;               /* <-- */
    ICAProperty                     property;                   /* <-- */
    ICAPropertyInfo               	propertyInfo;               /* <-- */
    UInt32                          startByte;                  /* <-- */
    UInt32                          requestedSize;              /* <-- */

    void *                          dataPtr;                    /* <-> */

    UInt32                          actualSize;                 /* --> */
    OSType                          dataType;                   /* --> */
};
typedef struct ICD_ScannerGetPropertyDataPB    ICD_ScannerGetPropertyDataPB;

struct ICD_ScannerSetPropertyDataPB {
    ICDHeader                       header;

    ICAObject                       parentObject;               /* <-- */
    ICAObjectInfo                   parentObjectInfo;           /* <-- */
    ICAConnectionID            	  	connectionID;               /* <-- */
    ICAProperty                     property;                   /* <-- */
    ICAPropertyInfo               	propertyInfo;               /* <-- */
    UInt32                          startByte;                  /* <-- */
    void *                          dataPtr;                    /* <-- */
    UInt32                          dataSize;                   /* <-- */
    UInt32                          totalDataSize;              /* <-- */
    OSType                          dataType;                   /* <-- */
};
typedef struct ICD_ScannerSetPropertyDataPB    ICD_ScannerSetPropertyDataPB;



struct ICD_ScannerObjectSendMessagePB {
    ICDHeader                       header;

    ICAObject                       object;                     /* <-- */
    ICAObjectInfo                   objectInfo;     		    /* <-- */
    ICAConnectionID            	  	connectionID;               /* <-- */
    ICAMessage                      message;                    /* <-- */
    UInt32                          totalDataSize;              /* <-- */
    UInt32                      	result;                     /* --> */
};
typedef struct ICD_ScannerObjectSendMessagePB  ICD_ScannerObjectSendMessagePB;

struct ICD_ScannerOpenSessionPB {
    ICDHeader               header;
    ICAObject           	object;                	/* <-- */
    ICAObjectInfo         	objectInfo;     	   	/* <-- */
    ICAConnectionID       	connectionID;        	/* <-- */
    ICAScannerSessionID  	sessionID;             	/* <-- */
};
typedef struct ICD_ScannerOpenSessionPB    ICD_ScannerOpenSessionPB;

struct ICD_ScannerCloseSessionPB {
    ICDHeader               header;
    ICAObject           	object;                	/* <-- */
    ICAObjectInfo         	objectInfo;     	   	/* <-- */
    ICAConnectionID       	connectionID;        	/* <-- */
    ICAScannerSessionID  	sessionID;              /* <-- */
};
typedef struct ICD_ScannerCloseSessionPB    ICD_ScannerCloseSessionPB;

struct ICD_ScannerInitializePB {
    ICDHeader             	header;
    ICAObject           	object;                	/* <-- */
    ICAObjectInfo         	objectInfo;     	   	/* <-- */
    ICAConnectionID       	connectionID;        	/* <-- */
    ICAScannerSessionID  	sessionID;             	/* <-- */
};
typedef struct ICD_ScannerInitializePB    ICD_ScannerInitializePB;

struct ICD_ScannerGetParametersPB {
    ICDHeader         		header;
    ICAObject           	object;                	/* <-- */
    ICAObjectInfo         	objectInfo;     	   	/* <-- */
    ICAConnectionID       	connectionID;        	/* <-- */
    ICAScannerSessionID		sessionID;             	/* <-- */
    CFMutableDictionaryRef	theDict;               	/* <-> */
};
typedef struct ICD_ScannerGetParametersPB    ICD_ScannerGetParametersPB;

struct ICD_ScannerSetParametersPB {
    ICDHeader          		header;
    ICAObject           	object;                	/* <-- */
    ICAObjectInfo         	objectInfo;     	   	/* <-- */
    ICAConnectionID       	connectionID;        	/* <-- */
    ICAScannerSessionID		sessionID;             	/* <-- */
    CFMutableDictionaryRef	theDict;               	/* <-> */
};
typedef struct ICD_ScannerSetParametersPB    ICD_ScannerSetParametersPB;

struct ICD_ScannerStatusPB {
    ICDHeader               header;
    ICAObject           	object;                	/* <-- */
    ICAObjectInfo         	objectInfo;     	   	/* <-- */
    ICAConnectionID       	connectionID;        	/* <-- */
    ICAScannerSessionID  	sessionID;             	/* <-- */
    UInt32	  				status;             	/* --> */
};
typedef struct ICD_ScannerStatusPB    ICD_ScannerStatusPB;

struct ICD_ScannerStartPB {
    ICDHeader           	header;
    ICAObject           	object;                	/* <-- */
    ICAObjectInfo         	objectInfo;     	   	/* <-- */
    ICAConnectionID       	connectionID;        	/* <-- */
    ICAScannerSessionID  	sessionID;             	/* <-- */
};
typedef struct ICD_ScannerStartPB    ICD_ScannerStartPB;


typedef CALLBACK_API_C(OSErr, __ICD_ScannerOpenUSBDevice)(UInt32 locationID,
                                                          ScannerObjectInfo * objectInfo);

typedef CALLBACK_API_C(OSErr, __ICD_ScannerOpenUSBDeviceWithIORegPath)(UInt32 locationID,
                                                          io_string_t ioregPath,
                                                          ScannerObjectInfo * objectInfo);

typedef CALLBACK_API_C(OSErr, __ICD_ScannerOpenFireWireDevice)(UInt64 guid,
                                                               ScannerObjectInfo * objectInfo);

typedef CALLBACK_API_C(OSErr, __ICD_ScannerOpenFireWireDeviceWithIORegPath)(UInt64 guid,
                                                               io_string_t ioregPath,
                                                               ScannerObjectInfo * objectInfo);

typedef CALLBACK_API_C(OSErr, __ICD_ScannerOpenBluetoothDevice)(CFDictionaryRef     params,
                                                                ScannerObjectInfo*  objectInfo);

typedef CALLBACK_API_C(OSErr, __ICD_ScannerOpenTCPIPDevice)(CFDictionaryRef     params,
                                                            ScannerObjectInfo*  objectInfo);

typedef CALLBACK_API_C(OSErr, __ICD_ScannerCloseDevice)(ScannerObjectInfo * objectInfo);

typedef CALLBACK_API_C(OSErr, __ICD_ScannerPeriodicTask)(ScannerObjectInfo * objectInfo);

typedef CALLBACK_API_C(OSErr, __ICD_ScannerGetObjectInfo)(const ScannerObjectInfo * parentInfo,
                                                          UInt32			 index,		/* index is zero based */
                                                          ScannerObjectInfo *		 newInfo);

typedef CALLBACK_API_C(OSErr, __ICD_ScannerCleanup)(ScannerObjectInfo * objectInfo);

typedef CALLBACK_API_C(OSErr, __ICD_ScannerGetPropertyData)(const ScannerObjectInfo * objectInfo,
                                                            ICD_ScannerGetPropertyDataPB	* pb);

typedef CALLBACK_API_C(OSErr, __ICD_ScannerSetPropertyData)(const ScannerObjectInfo * objectInfo,
                                                            const ICD_ScannerSetPropertyDataPB	* pb);

typedef CALLBACK_API_C(OSErr, __ICD_ScannerReadFileData)(const ScannerObjectInfo *	objectInfo,
                                                         UInt32			dataType,
                                                         Ptr			buffer,
                                                         UInt32			offset,
                                                         UInt32 *		length);

typedef CALLBACK_API_C(OSErr, __ICD_ScannerWriteFileData)(const ScannerObjectInfo *	parentInfo,
                                                          const char *  filename,
                                                          UInt32		dataType,
                                                          Ptr			buffer,
                                                          UInt32		offset,
                                                          UInt32 *		length);

typedef CALLBACK_API_C(OSErr, __ICD_ScannerSendMessage)(const ScannerObjectInfo * 			objectInfo,
                                                        ICD_ScannerObjectSendMessagePB *	pb,
                                                        ICDCompletion           		completion);

typedef CALLBACK_API_C(OSErr, __ICD_ScannerAddPropertiesToCFDictionary)(ScannerObjectInfo * 	objectInfo,
                                                                        CFMutableDictionaryRef	dict);
// scanner specific
typedef CALLBACK_API_C(OSErr, __ICD_ScannerOpenSession)(const ScannerObjectInfo * 	deviceObjectInfo,
                                                        ICD_ScannerOpenSessionPB *	pb);

typedef CALLBACK_API_C(OSErr, __ICD_ScannerCloseSession)(const ScannerObjectInfo * 		deviceObjectInfo,
                                                         ICD_ScannerCloseSessionPB *	pb);

typedef CALLBACK_API_C(OSErr, __ICD_ScannerInitialize)(const ScannerObjectInfo * 	deviceObjectInfo,
                                                       ICD_ScannerInitializePB *	pb);

typedef CALLBACK_API_C(OSErr, __ICD_ScannerGetParameters)(const ScannerObjectInfo * 	deviceObjectInfo,
                                                          ICD_ScannerGetParametersPB *	pb);

typedef CALLBACK_API_C(OSErr, __ICD_ScannerSetParameters)(const ScannerObjectInfo * 	deviceObjectInfo,
                                                          ICD_ScannerSetParametersPB *	pb);

typedef CALLBACK_API_C(OSErr, __ICD_ScannerStatus)(const ScannerObjectInfo *	deviceObjectInfo,
                                                   ICD_ScannerStatusPB *		pb);

typedef CALLBACK_API_C(OSErr, __ICD_ScannerStart)(const ScannerObjectInfo * deviceObjectInfo,
                                                  ICD_ScannerStartPB *		pb);

// callback functions
typedef struct ICD_Scannerscanner_callback_functions
{
    __ICD_ScannerOpenUSBDevice  					f_ICD_ScannerOpenUSBDevice;
    __ICD_ScannerOpenUSBDeviceWithIORegPath			f_ICD_ScannerOpenUSBDeviceWithIORegPath;
    __ICD_ScannerCloseDevice 						f_ICD_ScannerCloseDevice;
    __ICD_ScannerPeriodicTask						f_ICD_ScannerPeriodicTask;
    __ICD_ScannerGetObjectInfo						f_ICD_ScannerGetObjectInfo;
    __ICD_ScannerCleanup							f_ICD_ScannerCleanup;
    __ICD_ScannerGetPropertyData					f_ICD_ScannerGetPropertyData;
    __ICD_ScannerSetPropertyData					f_ICD_ScannerSetPropertyData;
    __ICD_ScannerReadFileData						f_ICD_ScannerReadFileData;
    __ICD_ScannerWriteFileData						f_ICD_ScannerWriteFileData;
    __ICD_ScannerSendMessage						f_ICD_ScannerSendMessage;
    __ICD_ScannerAddPropertiesToCFDictionary 		f_ICD_ScannerAddPropertiesToCFDictionary;
    __ICD_ScannerOpenFireWireDevice  				f_ICD_ScannerOpenFireWireDevice;
    __ICD_ScannerOpenFireWireDeviceWithIORegPath	f_ICD_ScannerOpenFireWireDeviceWithIORegPath;

    __ICD_ScannerOpenSession						f_ICD_ScannerOpenSession;
    __ICD_ScannerCloseSession						f_ICD_ScannerCloseSession;
    __ICD_ScannerInitialize							f_ICD_ScannerInitialize;
    __ICD_ScannerGetParameters						f_ICD_ScannerGetParameters;
    __ICD_ScannerSetParameters						f_ICD_ScannerSetParameters;
    __ICD_ScannerStatus								f_ICD_ScannerStatus;
    __ICD_ScannerStart								f_ICD_ScannerStart;
    __ICD_ScannerOpenBluetoothDevice                f_ICD_ScannerOpenBluetoothDevice;
    __ICD_ScannerOpenTCPIPDevice                    f_ICD_ScannerOpenTCPIPDevice;
} ICD_scanner_callback_functions;
extern ICD_scanner_callback_functions gICDScannerCallbackFunctions;


// scanner related callBacks into the ICADevices.framework:
int ICD_ScannerMain (int argc, const char * argv[]);

OSErr ICDScannerGetStandardPropertyData(const ScannerObjectInfo * objectInfo,
                                        ICD_ScannerGetPropertyDataPB	* pb);

OSErr ICDScannerNewObjectInfoCreated(const ScannerObjectInfo * parentInfo,
                                     UInt32			 index,
                                     ICAObject*		 newICAObject);

OSErr ICDScannerCopyDeviceInfoDictionary(const char*		deviceName,		// name of the device (from device's objectInfo)
                                         CFDictionaryRef*	theDict);		// this CFDictionaryRef contains information about the camera, e.g. the icon file,...

OSErr ICDScannerCreateICAThumbnailFromICNS(const char*		fileName,		// filename for .icns icon file (this file has to contain the 48*48 icon - 'huge 32 bit data')
                                           ICAThumbnail*	thumbnail);		// pointer to ICAThumbnail
                                                                      // NOTE: you have to allocate and prefill the ICAThumbnail
                                                                      //       malloc(sizeof(ICAThumbnail)+9215);
                                                                      //         width & height -> 48
                                                                      //		 dataSize       -> 9216  (= 48*48*4)


OSErr ICDScannerInitiateNotificationCallback(const ICAExtendedRegisterEventNotificationPB * pb);

OSErr ICDScannerCreateEventDataCookie(const ICAObject object,
                                      ICAEventDataCookie * cookie);


// ----------------------------------------------------
// USB
OSErr ICDScannerConnectUSBDevice(UInt32 locationID);
OSErr ICDScannerConnectUSBDeviceWithIORegPath(UInt32 	  locationID,
                                              io_string_t ioregPath);

OSErr ICDScannerDisconnectUSBDevice(UInt32 locationID);
OSErr ICDScannerDisconnectUSBDeviceWithIORegPath(UInt32 locationID,
                                                 io_string_t ioregPath);

// ----------------------------------------------------
// FireWire
OSErr ICDScannerConnectFWDevice(UInt64 guid);
OSErr ICDScannerConnectFWDeviceWithIORegPath(UInt64 guid,
                                             io_string_t ioregPath);
OSErr ICDScannerDisconnectFWDevice(UInt64 guid);
OSErr ICDScannerDisconnectFWDeviceWithIORegPath(UInt64 guid,
                                                io_string_t ioregPath);

// ----------------------------------------------------
// Bluetooth

OSErr ICDScannerConnectBluetoothDevice(CFDictionaryRef params);
OSErr ICDScannerDisconnectBluetoothDevice(CFDictionaryRef params);

// ----------------------------------------------------
// TCP/IP

OSErr ICDScannerConnectTCPIPDevice(CFDictionaryRef params);
OSErr ICDScannerDisconnectTCPIPDevice(CFDictionaryRef params);
                          
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

#endif
