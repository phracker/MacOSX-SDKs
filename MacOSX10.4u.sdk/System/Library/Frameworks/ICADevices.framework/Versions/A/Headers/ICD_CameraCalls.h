/*
 	File:       ICADevices/ICA_CameraCalls.h

 	Contains:   Camera module related interfaces

 	Copyright:  © 2000-2004 by Apple Computer, Inc., all rights reserved.

 
  	Bugs?:      For bug reports, consult the following page on
                the World Wide Web:

  	http://developer.apple.com/bugreporter/

*/
 
#ifndef __ICD_CameraCalls__
#define __ICD_CameraCalls__

#include <Carbon/Carbon.h>
#include <CoreFoundation/CoreFoundation.h>
#import <IOBluetooth/Bluetooth.h>

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
    kICD_FileData                 = 'file',
    kICD_ThumbnailData            = 'thum',
    kICD_MetaData                 = 'meta',
    kICD_ThumbnailDataFormatJPEG  = 'tjpg',
    kICD_ThumbnailDataFormatTIFF  = 'ttif'
};

/* flags */
enum
{
	hasChildrenMask    = 0x00000001,
	hasThumbnailMask   = 0x00000002,
    fileLockedMask     = 0x00000004,
    rawImageFormatMask = 0x00000008
};

typedef struct ObjectInfo
{
    ICAObject		icaObject;			// Apple
    UInt32			reserved;			// Apple	
    ICAObjectInfo 	icaObjectInfo;		// vendor
    UInt32			uniqueID;			// vendor
    UInt32			thumbnailSize;		// vendor
    UInt32			dataSize;			// vendor
    UInt32 			dataWidth;			// vendor
    UInt32 			dataHeight;			// vendor
    UInt8			name[32];			// vendor
    UInt8			creationDate[20];	// vendor
    UInt32			flags;				// vendor
    Ptr				privateData;		// vendor
    UInt64			uniqueIDFireWire;	// vendor
} ObjectInfo;

struct ICD_GetPropertyDataPB {
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
typedef struct ICD_GetPropertyDataPB    ICD_GetPropertyDataPB;

struct ICD_SetPropertyDataPB {
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
typedef struct ICD_SetPropertyDataPB    ICD_SetPropertyDataPB;



struct ICD_ObjectSendMessagePB {
    ICDHeader                       header;

    ICAObject                       object;                     /* <-- */
    ICAObjectInfo                   objectInfo;     		    /* <-- */
    ICAConnectionID            	  	connectionID;               /* <-- */
    ICAMessage                      message;                    /* <-- */
    UInt32                          totalDataSize;              /* <-- */
    UInt32                      	result;                     /* --> */
};
typedef struct ICD_ObjectSendMessagePB  ICD_ObjectSendMessagePB;


typedef CALLBACK_API_C(OSErr, __ICD_OpenUSBDevice)(UInt32 locationID, ObjectInfo * objectInfo);
    
typedef CALLBACK_API_C(OSErr, __ICD_OpenUSBDeviceWithIORegPath)(UInt32 locationID, io_string_t ioregPath, ObjectInfo * objectInfo);
    
typedef CALLBACK_API_C(OSErr, __ICD_OpenFireWireDevice)(UInt64 guid, ObjectInfo * objectInfo);

typedef CALLBACK_API_C(OSErr, __ICD_OpenFireWireDeviceWithIORegPath)(UInt64 guid, io_string_t ioregPath, ObjectInfo * objectInfo);

typedef CALLBACK_API_C(OSErr, __ICD_OpenBluetoothDevice)(CFDictionaryRef params, ObjectInfo * objectInfo);

typedef CALLBACK_API_C(OSErr, __ICD_OpenTCPIPDevice)(CFDictionaryRef params, ObjectInfo * objectInfo);

typedef CALLBACK_API_C(OSErr, __ICD_CloseDevice)(ObjectInfo * objectInfo);
        
typedef CALLBACK_API_C(OSErr, __ICD_PeriodicTask)(ObjectInfo * objectInfo);
    
typedef CALLBACK_API_C(OSErr, __ICD_GetObjectInfo)(const ObjectInfo * parentInfo,
                            UInt32				index,		/* index is zero based */
                            ObjectInfo *		newInfo);
                            
typedef CALLBACK_API_C(OSErr, __ICD_Cleanup)(ObjectInfo * objectInfo);
                                
typedef CALLBACK_API_C(OSErr, __ICD_GetPropertyData)(const ObjectInfo * objectInfo,
                            ICD_GetPropertyDataPB	* pb);
                            
typedef CALLBACK_API_C(OSErr, __ICD_SetPropertyData)(const ObjectInfo * objectInfo,
                            const ICD_SetPropertyDataPB	* pb);
                            
typedef CALLBACK_API_C(OSErr, __ICD_ReadFileData)(const ObjectInfo *	objectInfo,
                            UInt32			dataType,
                            Ptr				buffer,
                            UInt32			offset,
                            UInt32 *		length);
    
typedef CALLBACK_API_C(OSErr, __ICD_WriteFileData)(const ObjectInfo *	parentInfo,
                            const char *    filename,
                            UInt32			dataType,
                            Ptr             buffer,
                            UInt32			offset,
                            UInt32 *		length);
    
typedef CALLBACK_API_C(OSErr, __ICD_SendMessage)(const ObjectInfo * objectInfo,
                            ICD_ObjectSendMessagePB * pb,
                            ICDCompletion           completion);
                            
typedef CALLBACK_API_C(OSErr, __ICD_AddPropertiesToCFDictionary)(ObjectInfo * 			objectInfo,
                                                                CFMutableDictionaryRef  dict);

// camera related callBacks into the ICADevices.framework:

int ICD_main (int argc, const char * argv[]);

                                  
OSErr ICDGetStandardPropertyData(const ObjectInfo * objectInfo,
                                 ICD_GetPropertyDataPB	* pb);


OSErr ICDNewObjectInfoCreated(const ObjectInfo * parentInfo,
                              UInt32			 index,
                              ICAObject*		 newICAObject);



typedef CALLBACK_API_C( void , ICDNewObjectCreatedCompletion )(const ObjectInfo * info);

OSErr ICDNewObjectCreated(const ObjectInfo * 				parentInfo,
                          const ObjectInfo * 				objectInfo,
                          ICDNewObjectCreatedCompletion     completion);


OSErr ICDCopyDeviceInfoDictionary(const char*		deviceName,		// name of the device (from device's objectInfo)
                                  CFDictionaryRef*	theDict);		// this CFDictionaryRef contains information about the camera, e.g. the icon file,...


OSErr ICDCreateICAThumbnailFromICNS(const char*		fileName,		// filename for .icns icon file (this file has to contain the 48*48 icon - 'huge 32 bit data')
                                    ICAThumbnail*	thumbnail);		// pointer to ICAThumbnail
                                                                    // NOTE: you have to allocate and prefill the ICAThumbnail
                                                                    //       malloc(sizeof(ICAThumbnail)+9215);
                                                                    //         width & height -> 48
                                                                    //		   dataSize       -> 9216  (= 48*48*4)


OSErr ICDInitiateNotificationCallback(const ICAExtendedRegisterEventNotificationPB * pb);


OSErr ICDCreateEventDataCookie(const ICAObject object,
                               ICAEventDataCookie * cookie);

// ----------------------------------------------------
// USB
OSErr ICDConnectUSBDevice(UInt32 locationID);
OSErr ICDConnectUSBDeviceWithIORegPath(UInt32 	  locationID,
                                       io_string_t ioregPath);

OSErr ICDDisconnectUSBDevice(UInt32 locationID);
OSErr ICDDisconnectUSBDeviceWithIORegPath(UInt32 locationID,
                                          io_string_t ioregPath);

// ----------------------------------------------------
// FireWire
OSErr ICDConnectFWDevice(UInt64 guid);
OSErr ICDConnectFWDeviceWithIORegPath(UInt64 guid,
                                      io_string_t ioregPath);
OSErr ICDDisconnectFWDevice(UInt64 guid);
OSErr ICDDisconnectFWDeviceWithIORegPath(UInt64 guid,
                                         io_string_t ioregPath);

// ----------------------------------------------------
// Bluetooth

OSErr ICDConnectBluetoothDevice(CFDictionaryRef params);
OSErr ICDDisconnectBluetoothDevice(CFDictionaryRef params);

// ----------------------------------------------------
// TCP/IP

OSErr ICDConnectTCPIPDevice(CFDictionaryRef params);
OSErr ICDDisconnectTCPIPDevice(CFDictionaryRef params);
                          
// ----------------------------------------------------
OSErr ICDStatusChanged (ICAObject	object,							// deprecated - use ICDInitiateNotificationCallback instead
                        OSType		message);


// callback functions
typedef struct ICD_callback_functions
{
    __ICD_OpenUSBDevice  					f_ICD_OpenUSBDevice;
    __ICD_CloseDevice 						f_ICD_CloseDevice;
    __ICD_PeriodicTask						f_ICD_PeriodicTask;
    __ICD_GetObjectInfo						f_ICD_GetObjectInfo;
    __ICD_Cleanup							f_ICD_Cleanup;
    __ICD_GetPropertyData					f_ICD_GetPropertyData;
    __ICD_SetPropertyData					f_ICD_SetPropertyData;
    __ICD_ReadFileData						f_ICD_ReadFileData;
    __ICD_WriteFileData						f_ICD_WriteFileData;
    __ICD_SendMessage						f_ICD_SendMessage;
    __ICD_AddPropertiesToCFDictionary	 	f_ICD_AddPropertiesToCFDictionary;
    __ICD_OpenFireWireDevice  				f_ICD_OpenFireWireDevice;
    __ICD_OpenUSBDeviceWithIORegPath		f_ICD_OpenUSBDeviceWithIORegPath;
    __ICD_OpenFireWireDeviceWithIORegPath	f_ICD_OpenFireWireDeviceWithIORegPath;
    __ICD_OpenBluetoothDevice               f_ICD_OpenBluetoothDevice;
    __ICD_OpenTCPIPDevice                   f_ICD_OpenTCPIPDevice;
} ICD_callback_functions;
extern ICD_callback_functions gICDCallbackFunctions;


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
