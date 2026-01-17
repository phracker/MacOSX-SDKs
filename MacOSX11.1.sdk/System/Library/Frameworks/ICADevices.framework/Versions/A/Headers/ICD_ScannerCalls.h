//------------------------------------------------------------------------------------------------------------------------------
//
//  ICD_ScannerCalls.h
//
//  Copyright (c) 2000-2010 Apple Inc. All rights reserved.
//
//  For bug reports, consult the following page onthe World Wide Web:
//  http://developer.apple.com/bugreporter/
//------------------------------------------------------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------------------------------------------------------

#include <CoreFoundation/CoreFoundation.h>
#include <IOBluetooth/Bluetooth.h>
#include <ICADevices/ICADevice.h>

#ifndef __AVAILABILITYMACROS__
#include <AvailabilityMacros.h>
#endif

API_UNAVAILABLE_BEGIN(ios)

//------------------------------------------------------------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif

#pragma pack(push, 2)

//------------------------------------------------------------------------------------------------------------------------------
/* DataTypes for _ICD_ReadFileData/_ICD_WriteFileData */

enum {
    kICS_FileData                 = 'file',
    kICS_MetaData                 = 'meta',
    kICS_ThumbnailData            = 'thum',     // Deprecated in 10.5
    kICS_ThumbnailDataFormatJPEG  = 'tjpg',     // Deprecated in 10.5
    kICS_ThumbnailDataFormatTIFF  = 'ttif',     // Deprecated in 10.5
    kICS_ThumbnailDataFormatPNG   = 'tpng'      // Deprecated in 10.5    
};

//------------------------------------------------------------------------------------------------------------------------------

typedef struct ScannerObjectInfo
{
    ICAObject		icaObject;			// Apple
    unsigned long	reserved;			// Apple
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
    UInt32          tag;                // Apple
} ScannerObjectInfo;

//------------------------------------------------------------------------------------------------------------------------------

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

//------------------------------------------------------------------------------------------------------------------------------

struct ICD_ScannerOpenSessionPB {
    ICDHeader               header;
    ICAObject           	object;                	/* <-- */
    ICAObjectInfo         	objectInfo;     	   	/* <-- */
    ICAConnectionID       	connectionID;        	/* <-- */
    ICAScannerSessionID  	sessionID;             	/* <-- */
};
typedef struct ICD_ScannerOpenSessionPB    ICD_ScannerOpenSessionPB;

//------------------------------------------------------------------------------------------------------------------------------

struct ICD_ScannerCloseSessionPB {
    ICDHeader               header;
    ICAObject           	object;                	/* <-- */
    ICAObjectInfo         	objectInfo;     	   	/* <-- */
    ICAConnectionID       	connectionID;        	/* <-- */
    ICAScannerSessionID  	sessionID;              /* <-- */
};
typedef struct ICD_ScannerCloseSessionPB    ICD_ScannerCloseSessionPB;

//------------------------------------------------------------------------------------------------------------------------------

struct ICD_ScannerInitializePB {
    ICDHeader             	header;
    ICAObject           	object;                	/* <-- */
    ICAObjectInfo         	objectInfo;     	   	/* <-- */
    ICAConnectionID       	connectionID;        	/* <-- */
    ICAScannerSessionID  	sessionID;             	/* <-- */
};
typedef struct ICD_ScannerInitializePB    ICD_ScannerInitializePB;

//------------------------------------------------------------------------------------------------------------------------------

struct ICD_ScannerGetParametersPB {
    ICDHeader         		header;
    ICAObject           	object;                	/* <-- */
    ICAObjectInfo         	objectInfo;     	   	/* <-- */
    ICAConnectionID       	connectionID;        	/* <-- */
    ICAScannerSessionID		sessionID;             	/* <-- */
    CFMutableDictionaryRef	theDict;               	/* <-> */
};
typedef struct ICD_ScannerGetParametersPB    ICD_ScannerGetParametersPB;

//------------------------------------------------------------------------------------------------------------------------------

struct ICD_ScannerSetParametersPB {
    ICDHeader          		header;
    ICAObject           	object;                	/* <-- */
    ICAObjectInfo         	objectInfo;     	   	/* <-- */
    ICAConnectionID       	connectionID;        	/* <-- */
    ICAScannerSessionID		sessionID;             	/* <-- */
    CFMutableDictionaryRef	theDict;               	/* <-> */
};
typedef struct ICD_ScannerSetParametersPB    ICD_ScannerSetParametersPB;

//------------------------------------------------------------------------------------------------------------------------------

struct ICD_ScannerStatusPB {
    ICDHeader               header;
    ICAObject           	object;                	/* <-- */
    ICAObjectInfo         	objectInfo;     	   	/* <-- */
    ICAConnectionID       	connectionID;        	/* <-- */
    ICAScannerSessionID  	sessionID;             	/* <-- */
    UInt32	  				status;             	/* --> */
};
typedef struct ICD_ScannerStatusPB    ICD_ScannerStatusPB;

//------------------------------------------------------------------------------------------------------------------------------

struct ICD_ScannerStartPB {
    ICDHeader           	header;
    ICAObject           	object;                	/* <-- */
    ICAObjectInfo         	objectInfo;     	   	/* <-- */
    ICAConnectionID       	connectionID;        	/* <-- */
    ICAScannerSessionID  	sessionID;             	/* <-- */
};
typedef struct ICD_ScannerStartPB    ICD_ScannerStartPB;

//------------------------------------------------------------------------------------------------------------------------------

typedef CALLBACK_API_C(ICAError, __ICD_ScannerOpenUSBDevice)
                                    (UInt32 locationID, ScannerObjectInfo* objectInfo);

typedef CALLBACK_API_C(ICAError, __ICD_ScannerOpenUSBDeviceWithIORegPath)
                                    (UInt32 locationID, io_string_t ioregPath, ScannerObjectInfo* objectInfo);

typedef CALLBACK_API_C(ICAError, __ICD_ScannerOpenFireWireDevice)
                                    (UInt64 guid, ScannerObjectInfo* objectInfo);

typedef CALLBACK_API_C(ICAError, __ICD_ScannerOpenFireWireDeviceWithIORegPath)
                                    (UInt64 guid, io_string_t ioregPath, ScannerObjectInfo* objectInfo);

typedef CALLBACK_API_C(ICAError, __ICD_ScannerOpenBluetoothDevice)
                                    (CFDictionaryRef params, ScannerObjectInfo* objectInfo);

typedef CALLBACK_API_C(ICAError, __ICD_ScannerOpenTCPIPDevice)
                                    (CFDictionaryRef params, ScannerObjectInfo* objectInfo);

typedef CALLBACK_API_C(ICAError, __ICD_ScannerOpenMassStorageDevice)
                                    (CFStringRef diskBSDName, DASessionRef daSession, ScannerObjectInfo* objectInfo);

typedef CALLBACK_API_C(ICAError, __ICD_ScannerCloseDevice)
                                    (ScannerObjectInfo* objectInfo);

typedef CALLBACK_API_C(ICAError, __ICD_ScannerPeriodicTask)
                                    (ScannerObjectInfo* objectInfo);

/* index is zero based */
typedef CALLBACK_API_C(ICAError, __ICD_ScannerGetObjectInfo)
                                    (const ScannerObjectInfo* parentInfo, UInt32 index, ScannerObjectInfo* newInfo);

typedef CALLBACK_API_C(ICAError, __ICD_ScannerCleanup)
                                    (ScannerObjectInfo* objectInfo);

typedef CALLBACK_API_C(ICAError, __ICD_ScannerGetPropertyData)
                                    (const ScannerObjectInfo* objectInfo, void* pb);

typedef CALLBACK_API_C(ICAError, __ICD_ScannerSetPropertyData)
                                    (const ScannerObjectInfo* objectInfo, const void* pb);

typedef CALLBACK_API_C(ICAError, __ICD_ScannerReadFileData)
                                    (const ScannerObjectInfo* objectInfo, UInt32 dataType, Ptr buffer, UInt32 offset, UInt32* length);

typedef CALLBACK_API_C(ICAError, __ICD_ScannerReadFileData64)
                                    (const ScannerObjectInfo* objectInfo, UInt32 dataType, Ptr buffer, UInt64 offset, UInt64* length);

typedef CALLBACK_API_C(ICAError, __ICD_ScannerWriteFileData)
                                    (const ScannerObjectInfo* parentInfo, const char* filename, UInt32 dataType, Ptr buffer, UInt32 offset, UInt32* length);

typedef CALLBACK_API_C(ICAError, __ICD_ScannerSendMessage)
                                    (const ScannerObjectInfo* objectInfo, ICD_ScannerObjectSendMessagePB* pb, ICDCompletion completion);

typedef CALLBACK_API_C(ICAError, __ICD_ScannerAddPropertiesToCFDictionary)
                                    (ScannerObjectInfo* objectInfo, CFMutableDictionaryRef dict);
// scanner specific
typedef CALLBACK_API_C(ICAError, __ICD_ScannerOpenSession)
                                    (const ScannerObjectInfo* deviceObjectInfo, ICD_ScannerOpenSessionPB* pb);

typedef CALLBACK_API_C(ICAError, __ICD_ScannerCloseSession)
                                    (const ScannerObjectInfo* deviceObjectInfo, ICD_ScannerCloseSessionPB* pb);

typedef CALLBACK_API_C(ICAError, __ICD_ScannerInitialize)
                                    (const ScannerObjectInfo* deviceObjectInfo, ICD_ScannerInitializePB* pb);

typedef CALLBACK_API_C(ICAError, __ICD_ScannerGetParameters)
                                    (const ScannerObjectInfo* deviceObjectInfo, ICD_ScannerGetParametersPB* pb);

typedef CALLBACK_API_C(ICAError, __ICD_ScannerSetParameters)
                                    (const ScannerObjectInfo* deviceObjectInfo, ICD_ScannerSetParametersPB* pb);

typedef CALLBACK_API_C(ICAError, __ICD_ScannerStatus)
                                    (const ScannerObjectInfo* deviceObjectInfo, ICD_ScannerStatusPB* pb);

typedef CALLBACK_API_C(ICAError, __ICD_ScannerStart)
                                    (const ScannerObjectInfo* deviceObjectInfo, ICD_ScannerStartPB* pb);

typedef CALLBACK_API_C(ICAError, __ICD_ScannerWriteDataToFile)
                                      (const ScannerObjectInfo* objectInfo, FILE* file, UInt32 offset, long* length);

typedef CALLBACK_API_C(ICAError, __ICD_ScannerWriteDataToFileDescriptor)
                                      (const ScannerObjectInfo* objectInfo, int fd, UInt32 offset, long* length);

typedef CALLBACK_API_C(ICAError, __ICD_ScannerWriteDataToFileDescriptor64)
                                      (const ScannerObjectInfo* objectInfo, int fd);

	
//------------------------------------------------------------------------------------------------------------------------------

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
    __ICD_ScannerWriteDataToFile                    f_ICD_ScannerWriteDataToFile;
    __ICD_ScannerOpenMassStorageDevice              f_ICD_ScannerOpenMassStorageDevice;
    __ICD_ScannerWriteDataToFileDescriptor          f_ICD_ScannerWriteDataToFileDescriptor;
    __ICD_ScannerWriteDataToFileDescriptor64        f_ICD_ScannerWriteDataToFileDescriptor64;	
} ICD_scanner_callback_functions;

extern ICD_scanner_callback_functions gICDScannerCallbackFunctions;

//------------------------------------------------------------------------------------------------------------------------------


// scanner related callBacks into the ICADevices.framework:
int ICD_ScannerMain (int argc, const char* argv[]);

ICAError ICDScannerGetStandardPropertyData(const ScannerObjectInfo* objectInfo, void* pb);

ICAError ICDScannerNewObjectInfoCreated(const ScannerObjectInfo* parentInfo, UInt32 index, ICAObject* newICAObject);

ICAError ICDScannerCopyDeviceInfoDictionary(const char*		deviceName,		// name of the device (from device's objectInfo)
                                         CFDictionaryRef*	theDict);		// this CFDictionaryRef contains information about the camera, e.g. the icon file,...

ICAError ICDScannerCreateICAThumbnailFromICNS( const char* fileName, void* thumbnail ) DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER;

//Use ICDSendNotification or ICDSendNotificationAndWaitForReply instead of ICDInitiateNotificationCallback
ICAError ICDScannerInitiateNotificationCallback(const void* pb)                   DEPRECATED_IN_MAC_OS_X_VERSION_10_6_AND_LATER;

ICAError ICDScannerCreateEventDataCookie(const ICAObject object, ICAEventDataCookie* cookie);

//------------------------------------------------------------------------------------------------------------------------------
// USB
ICAError ICDScannerConnectUSBDevice(UInt32 locationID);
ICAError ICDScannerConnectUSBDeviceWithIORegPath(UInt32 locationID, io_string_t ioregPath);

ICAError ICDScannerDisconnectUSBDevice(UInt32 locationID);
ICAError ICDScannerDisconnectUSBDeviceWithIORegPath(UInt32 locationID, io_string_t ioregPath);

//------------------------------------------------------------------------------------------------------------------------------
// FireWire
ICAError ICDScannerConnectFWDevice(UInt64 guid);
ICAError ICDScannerConnectFWDeviceWithIORegPath(UInt64 guid, io_string_t ioregPath);

ICAError ICDScannerDisconnectFWDevice(UInt64 guid);
ICAError ICDScannerDisconnectFWDeviceWithIORegPath(UInt64 guid, io_string_t ioregPath);

//------------------------------------------------------------------------------------------------------------------------------
// Bluetooth

ICAError ICDScannerConnectBluetoothDevice(CFDictionaryRef params);
ICAError ICDScannerDisconnectBluetoothDevice(CFDictionaryRef params);

//------------------------------------------------------------------------------------------------------------------------------
// TCP/IP

ICAError ICDScannerConnectTCPIPDevice(CFDictionaryRef params);
ICAError ICDScannerDisconnectTCPIPDevice(CFDictionaryRef params);

//------------------------------------------------------------------------------------------------------------------------------

#pragma pack(pop)

#ifdef __cplusplus
}
#endif

API_UNAVAILABLE_END
