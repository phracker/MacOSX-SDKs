//------------------------------------------------------------------------------------------------------------------------------
//
//  ImageCapture/ICAApplication.h
//
//  Copyright (c) 2004-2007 Apple Inc. All rights reserved.
//
//------------------------------------------------------------------------------------------------------------------------------

#pragma once

#ifndef __ICAAPPLICATION__
#define __ICAAPPLICATION__

//------------------------------------------------------------------------------------------------------------------------------

#ifndef	__IOKIT_IOTYPES_H
#include <IOKit/IOTypes.h>
#endif

#ifndef __CORESERVICES__
#include <CoreServices/CoreServices.h>
#endif

#ifndef __AVAILABILITYMACROS__
#include <AvailabilityMacros.h>
#endif

//------------------------------------------------------------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif

#pragma pack(push, 2)

//------------------------------------------------------------------------------------------------------------------------------
/*!
    @header
        ICAApplication.h
    @discussion
      ICAApplication.h defines structures and functions that are used by clients of Image Capture framework. 
*/

//------------------------------------------------------------------------------------------------------------------------------

typedef OSErr ICAError;

//------------------------------------------------------------------------------------------------------ Parameter block version
/*!
    @enum Parameter block version
    @discussion
        Parameter block version.
    @constant kICAPBVersion
        Version 1 parameter block.
*/
enum
{
    kICAPBVersion = 0x00010000
};

//------------------------------------------------------------------------------------------------------------------ Error codes
// Image Capture error code range = -9900 to -9949
/*!
    @enum Error codes
    @discussion
        Definition of error codes returned by Image Capture framework
    @constant kICACommunicationErr
        An error occurred in communication between different components of Image Capture framework.
    @constant kICADeviceNotFoundErr
        The specified device is not found.
    @constant kICADeviceNotOpenErr
        The specified device is not open.
    @constant kICAFileCorruptedErr
        Encountered a corrupt file.
    @constant kICAIOPendingErr
        There is a pending I/O.
    @constant kICAInvalidObjectErr
        The specified object is invalid.
    @constant kICAInvalidPropertyErr
        The specified property is invalid.
    @constant kICAIndexOutOfRangeErr
        The specified index is out of range.
    @constant kICAPropertyTypeNotFoundErr
        A property with the specified property type is not found.
    @constant kICACannotYieldDevice
        The device module cannot yield the specified device to the requestor.
    @constant kICADataTypeNotFoundErr
        Data with the specified data type is not found.
    @constant kICADeviceMemoryAllocationErr
        The device module encountered a memory allocation error.
    @constant kICADeviceInternalErr
        The device module encountered an unspecifed error.
    @constant kICADeviceInvalidParamErr
        At least one of the parameters passed to the device module is invalid.
    @constant kICADeviceAlreadyOpenErr  
        The specified device is already open.
    @constant kICADeviceLocationIDNotFoundErr
        The specified USB Location ID is not found.
    @constant kICADeviceGUIDNotFoundErr
        The specified FireWire GUID is not found.
    @constant kICADeviceIOServicePathNotFoundErr
        The specified IOService path is not found.
    @constant kICAFrameworkInternalErr
        Image Capture Framework encountered an error.
    @constant kICAExtensionInternalErr
        Image Capture Extension encountered an error.
    @constant kICAInvalidSessionErr
        The specified session is not valid.
*/
enum
{
    kICACommunicationErr                = -9900,
    kICADeviceNotFoundErr               = -9901,
    kICADeviceNotOpenErr                = -9902,
    kICAFileCorruptedErr                = -9903,
    kICAIOPendingErr                    = -9904,
    kICAInvalidObjectErr                = -9905,
    kICAInvalidPropertyErr              = -9906,
    kICAIndexOutOfRangeErr              = -9907,
    kICAPropertyTypeNotFoundErr         = -9908,
    kICACannotYieldDevice               = -9909,
    kICADataTypeNotFoundErr             = -9910,
    kICADeviceMemoryAllocationErr       = -9911,
    kICADeviceInternalErr               = -9912,
    kICADeviceInvalidParamErr           = -9913,
    kICADeviceAlreadyOpenErr            = -9914,
    kICADeviceLocationIDNotFoundErr     = -9915,
    kICADeviceGUIDNotFoundErr           = -9916,
    kICADeviceIOServicePathNotFoundErr  = -9917,
    kICADeviceUnsupportedErr            = -9918,
    kICAFrameworkInternalErr            = -9919,
    kICAExtensionInternalErr            = -9920,
    kICAInvalidSessionErr               = -9921
};

//------------------------------------------------------------------------------------------------- ICAObject types and subtypes
/*!
    @enum ICAObject types and subtypes
    @discussion
        Definition of ICAObject types and subtypes
    @constant kICADevice
        Object is a device supported by Image Capture framework.
    @constant kICADeviceCamera
        Object is a camera.
    @constant kICADeviceScanner
        Object is a scanner.
    @constant kICADeviceMFP
        Object is a multi-function peripheral.
    @constant kICADevicePhone
        Object is a camera phone.
    @constant kICADevicePDA
        Object is a personal digital assistant.
    @constant kICADeviceOther
        Object is a device supported by Image Capture framework, but of unknown subtype.
    @constant kICAList
        Object is a device list.
    @constant kICADirectory
        Object is a directory.
    @constant kICAFile
        Object is a file.
    @constant kICAFileImage
        Object is an image file.
    @constant kICAFileMovie
        Object is a movie file.
    @constant kICAFileAudio
        Object is an audio file.
    @constant kICAFileFirmware
        Object is a firmware file.
    @constant kICAFileOther
        Object is a generic file.
*/
enum
{
    kICADevice                            = 'icdv',
    kICADeviceCamera                      = 'cmra',
    kICADeviceScanner                     = 'scan',
    kICADeviceMFP                         = 'mfp ',
    kICADevicePhone                       = 'phon',
    kICADevicePDA                         = 'pda ',
    kICADeviceOther                       = 'doth',
    kICAList                              = 'objl',	
    kICADirectory                         = 'dire',
    kICAFile                              = 'file',
    kICAFileImage                         = 'imag',
    kICAFileMovie                         = 'moov',
    kICAFileAudio                         = 'audo',
    kICAFileFirmware                      = 'firm',
    kICAFileOther                         = 'othe'
};

//------------------------------------------------------------------------------------------------------------ ICAProperty types
/*!
    @enum ICAProperty types
    @discussion
        Definition of ICAProperties
    @constant kICAProperty
        Generic property type; for images, refer to 'Digital Still Camera Image File Format Standard' Exif Version 2.1 section 2.6.4. and 2.6.5.
    @constant kICAPropertyImageWidth
        Image width. 
    @constant kICAPropertyImageHeight
        Image height.
    @constant kICAPropertyImageBitDepth
        Image bit-depth.
    @constant kICAPropertyImageDPI
        Image DPI.
    @constant kICAPropertyImageExposureTime
        Image exposure time.
    @constant kICAPropertyImageFNumber
        Image f-Number.
    @constant kICAPropertyImageDateOriginal
        Original date & time of an object; value associated with this property is a null-terminated string conforming to format "YYYY:MM:DD hh:mm:ss".
    @constant kICAPropertyImageDateDigitized
        Digitized date & time of an object; value associated with this property is a null-terminated string conforming to format "YYYY:MM:DD hh:mm:ss".
    @constant kICAPropertyImageShutterSpeed
        Shutter speed used to capture an image.
    @constant kICAPropertyImageAperture
        Aperture used to capture an image.
    @constant kICAPropertyImageFlash
        Indicates whether flash was used to capture an image.
    @constant kICAPropertyColorSpace
        Color space used to represent an image.
    @constant kICAPropertyImageFilename
        Filename of an image.
    @constant kICAPropertyImageSize
        Size of an image in bytes. 
    @constant kICAPropertyImageData
        Data of an image.
    @constant kICAPropertyImageThumbnail
        Thumbnail of an image.
    @constant kICAPropertyColorSyncProfile
        ColorSync profile associated with an image.
*/  
enum
{
    kICAProperty                          = 'prop',
    kICAPropertyImageWidth                = '0100',
    kICAPropertyImageHeight               = '0101',
    kICAPropertyImageBitDepth             = '0102',
    kICAPropertyImageDPI                  = '011A',
    kICAPropertyImageExposureTime         = '829A',
    kICAPropertyImageFNumber              = '829D',
    kICAPropertyImageDateOriginal         = '9003',
    kICAPropertyImageDateDigitized        = '9004',
    kICAPropertyImageShutterSpeed         = '9201',
    kICAPropertyImageAperture             = '9202',
    kICAPropertyImageFlash                = '9209',
    kICAPropertyColorSpace                = 'A001',
    kICAPropertyImageFilename             = 'ifil',
    kICAPropertyImageSize                 = 'isiz',
    kICAPropertyImageData                 = 'idat',
    kICAPropertyImageThumbnail            = 'thum',
    kICAPropertyColorSyncProfile          = 'prof'
};

//------------------------------------------------------------------------------------------------------------------- Data types
/*!
    @enum Data types
    @discussion
        Definition of data types; these are mapped to AppleEvent types.
    @constant kICATypeUInt8
        UInt8.
    @constant kICATypeUInt16
        UInt16.
    @constant kICATypeUInt32
        UInt32.
    @constant kICATypeUInt64
        UInt64.
    @constant kICATypeSInt16
        SInt16.
    @constant kICATypeSInt32
        SInt32.
    @constant kICATypeSInt64
        SInt64.
    @constant kICATypeFloat
        float.
    @constant kICATypeFixed
        IEEE 32-bit floating point.
    @constant kICATypeBoolean
        Boolean.
    @constant kICATypeString
        Char string.
    @constant kICATypeData
        void *.
    @constant kICATypeThumbnail
        ICAThumbnail.
*/
enum
{
    kICATypeUInt8                         = 'ui08',
    kICATypeUInt16                        = 'ui16',
    kICATypeUInt32                        = 'ui32',
    kICATypeUInt64                        = 'ui64',
    kICATypeSInt16                        = 'si16',
    kICATypeSInt32                        = 'si32',
    kICATypeSInt64                        = 'si64',
    kICATypeFloat                         = 'floa',
    kICATypeFixed                         = 'sing',
    kICATypeBoolean                       = 'bool',
    kICATypeString                        = 'TEXT',
    kICATypeData                          = 'data',
    kICATypeThumbnail                     = 'thum'
};

//----------------------------------------------------------------------------------------------------- PropertyInfo flag values
/*!
    @enum PropertyInfo flag values
    @discussion
        Values for PropertyInfo flag.
    @constant kICAFlagReadWriteAccess
        Access for read and write.
    @constant kICAFlagReadAccess
        Access for read only.
*/
enum
{
    kICAFlagReadWriteAccess               = 1L << 0,
    kICAFlagReadAccess                    = 1L << 1
};

//---------------------------------------------------------------------------------------------------- Image Capture event types
/*!
    @enum Image Capture event types
    @discussion
        Image Capture event types (Refer to section 12.4 of PTP spec for PTP-specific events).
        These are deprecated in 10.5.
    @constant kICAEventCancelTransaction
        Cancel transaction.
    @constant kICAEventObjectAdded
        A new object has been added.
    @constant kICAEventObjectRemoved
        An object has been removed.
    @constant kICAEventStoreAdded
        A new storage has been added.
    @constant kICAEventStoreRemoved
        A storage has been removed.
    @constant kICAEventDeviceAdded
        A new device has been added.
    @constant kICAEventDeviceRemoved
        A device has been removed.
    @constant kICAEventDevicePropChanged
        Device property has changed.
    @constant kICAEventObjectInfoChanged
        Object information has changed.
    @constant kICAEventDeviceInfoChanged
        Device information has changed.
    @constant kICAEventRequestObjectTransfer
        Requesting transfer of an object.
    @constant kICAEventStoreFull
        Store is full.
    @constant kICAEventDeviceReset
        Device has been reset.
    @constant kICAEventStorageInfoChanged
        Storage information has changed.
    @constant kICAEventCaptureComplete
        Image capture has been completed.
    @constant kICAEventUnreportedStatus
        Unreported status.
    @constant kExtendedNotificationPB
        Indicates the event notification uses extended notification parameter block.
*/
enum
{
    kICAEventCancelTransaction            = 'ecnt',
    kICAEventObjectAdded                  = 'eoba',
    kICAEventObjectRemoved                = 'eobr',
    kICAEventStoreAdded                   = 'esta',
    kICAEventStoreRemoved                 = 'estr',
    kICAEventDeviceAdded                  = 'edea',
    kICAEventDeviceRemoved                = 'eder',
    kICAEventDevicePropChanged            = 'edpc',
    kICAEventObjectInfoChanged            = 'eoic',
    kICAEventDeviceInfoChanged            = 'edic',
    kICAEventRequestObjectTransfer        = 'erot',
    kICAEventStoreFull                    = 'estf',
    kICAEventDeviceReset                  = 'edvr',
    kICAEventStorageInfoChanged           = 'esic',
    kICAEventCaptureComplete              = 'ecpc',
    kICAEventUnreportedStatus             = 'eurs',
    kICAExtendedNotificationPB            = 'extd',
    kExtendedNotificationPB               = 'extd'
};

//-------------------------------------------------------------------------------------------------- Image Capture event classes
/*!
    @enum Event class returned in extended event notifications
    @discussion
        Event class returned in extended event notifications.
        Deprecated in 10.5
    @constant kICAEventClassPTPStandard
        PTP standard event.
    @constant kICAEventClassPTPVendor
        PTP vendor-specific event.
    @constant kEventClassPTPStandard
        PTP standard event. Deprecated in 10.5. Use kICAEventClassPTPStandard instead.
    @constant kEventClassPTPVendor
        PTP vendor-specific event. Deprecated in 10.5. Use kICAEventClassPTPVendor instead.
*/
enum
{
    kICAEventClassPTPStandard             = 'PTPs',
    kICAEventClassPTPVendor               = 'PTPv',
    kEventClassPTPStandard                = 'PTPs',
    kEventClassPTPVendor                  = 'PTPv'
};

//----------------------------------------------------------------------------------------------------------------- Button types
/*!
    @enum Button types
    @discussion
        Buttons types associated with buttons on a scanner.
    @constant kICAButtonScan
        Scan button.
    @constant kICAButtonCopy
        Copy button.
    @constant kICAButtonEMail
        Email button.
    @constant kICAButtonWeb
        Web button.
*/
enum
{
    kICAButtonScan                        = 'scan',
    kICAButtonCopy                        = 'copy',
    kICAButtonEMail                       = 'mail',
    kICAButtonWeb                         = 'web '
};

//------------------------------------------------------------------------ Flags associated with Image Capture PassThru commands
/*!
    @enum Flags associated with Image Capture PassThru commands.
    @discussion
        Flag values that can be used in ICAUploadFilePB parameter block.
    @constant kICACameraPassThruSend
        Use this constant when sending data to a device using a pass-through command.
    @constant kICACameraPassThruReceive
        Use this constant when receiving data from a device using a pass-through command.
    @constant kICACameraPassThruNotUsed
        Use this constant when using a pass-through command that doesn't involve sending or receiving data.
*/
enum
{
    kICACameraPassThruSend                = 0,
    kICACameraPassThruReceive             = 1,
    kICACameraPassThruNotUsed             = 2
};

//---------------------------------------------------------------------------------------------------------- ICAPTPPassThroughPB
/*!
    @struct ICAPTPPassThroughPB
    @field commandCode
        PTP command code (including vendor specific) <--
    @field resultCode
        PTP response code -->
    @field numOfInputParams
        Number of valid parameters to be sent to device <--
    @field numOfOutputParams
        Number of valid parameters expected from device <--
    @field params
        PTP parameters (command specific / optional) <->
    @field dataUsageMode
        One of (kICACameraPassThruSend, kICACameraPassThruReceive, kICACameraPassThruNotUsed) <--
    @field flags
        Not used currently
    @field dataSize
        Size of data block <->
    @field data
        Data block <->
*/
typedef struct ICAPTPPassThroughPB
{
    UInt32	commandCode;
    UInt32	resultCode;
    UInt32	numOfInputParams;
    UInt32	numOfOutputParams;
    UInt32	params[4];
    UInt32	dataUsageMode;
    UInt32	flags;
    UInt32	dataSize;
    UInt8	data[1];
} ICAPTPPassThroughPB;

//----------------------------------------------------------------------------------------------------------- ICAPTPEventDataset
/*!
    @struct ICAPTPEventDataset
    @field dataLength
        Data length in bytes
    @field containerType
        PTP container type
    @field eventCode
        PTP event code
    @field transactionID
        PTP transaction ID
    @field params
        PTP params. The number of params should be (dataLength - 12)/4
*/
typedef struct ICAPTPEventDataset
{
    UInt32  dataLength;
    UInt16  containerType;		// should be 0x0004 for event
    UInt16  eventCode;
    UInt32  transactionID;
    UInt32  params[3];			// up to 3 params. # of params = (dataLength - 12)/4
} ICAPTPEventDataset;

//------------------------------------------------------------------------------------- Keys used in object property dictionary
/* Keys used in object property dictionary */
#pragma mark -
#pragma mark TODO: document the data types of values for these keys

// Keys returned by ICACopyObjectDictionary() for deviceList object returned by ICAGetDeviceList()

extern const CFStringRef kICADevicesArrayKey                        AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

extern const CFStringRef kICAObjectKey                              AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern const CFStringRef kICAObjectNameKey                          AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern const CFStringRef kICAUSBVendorIDKey                         AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern const CFStringRef kICAUSBProductIDKey                        AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern const CFStringRef kICADeviceTypeKey                          AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern const CFStringRef kICAExecutableArchitectureKey              AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern const CFStringRef kICARemoteDeviceKey                        AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern const CFStringRef kICADeviceSharedKey                        AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern const CFStringRef kICADeviceWebSharedKey                     AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern const CFStringRef kICADeviceUsedKey                          AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern const CFStringRef kICABonjourServiceTypeKey                  AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern const CFStringRef kICABonjourServiceNameKey                  AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern const CFStringRef kICABonjourTXTRecordKey                    AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern const CFStringRef kICADeviceCapabilitiesKey                  AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern const CFStringRef kICALockStatusKey                          AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

extern const CFStringRef kICADataPropertyKey                        AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern const CFStringRef kICADataTypeKey                            AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern const CFStringRef kICADataSizeKey                            AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern const CFStringRef kICAThumbnailPropertyKey                   AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern const CFStringRef kICAThumbnailSizeKey                       AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern const CFStringRef kICARawKey                                 AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

extern const CFStringRef kICAMediaHeightKey                         AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// value is a number
extern const CFStringRef kICAMediaWidthKey                          AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// value is a number
extern const CFStringRef kICACreationDateStringKey                  AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern const CFStringRef kICAModificationDateStringKey              AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern const CFStringRef kMetaDataDictionaryKey                     AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern const CFStringRef kICAMediaDurationInSecondsKey              AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

extern const CFStringRef kICADeviceTypeCamera                       AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern const CFStringRef kICADeviceTypeScanner                      AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/*
    In addition to the above, the following keys may also be present in the object property dictionay:
    
        kICAUSBLocationIDKey
        kICAFireWireGUIDKey
*/

/* Transport types */
extern const CFStringRef kICAUSBTransportType                       AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
extern const CFStringRef kICAFireWireTransportType                  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
extern const CFStringRef kICABluetoothTransportType                 AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
extern const CFStringRef kICATCPIPTransportType                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
extern const CFStringRef kICASCSITransportType                      AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
extern const CFStringRef kICATWAINTransportType                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Keys used for paramDictionary in ICALoadDeviceModulePB*/
extern const CFStringRef kICAManualConnectDeviceRefKey              AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;
extern const CFStringRef kICADeviceBrowserDeviceRefKey              AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern const CFStringRef kICADeviceModulePathKey                    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
extern const CFStringRef kICADeviceIconPathKey                      AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern const CFStringRef kICATransportTypeKey                       AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
extern const CFStringRef kICABluetoothAddressKey                    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
extern const CFStringRef kICAUSBLocationIDKey                       AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
extern const CFStringRef kICAFireWireGUIDKey                        AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
extern const CFStringRef kICAIOServicePathKey                       AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
extern const CFStringRef kICAIPAddressKey                           AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
extern const CFStringRef kICAIPPortKey                              AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
extern const CFStringRef kICAIPNameKey                              AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
extern const CFStringRef kICAIPGUIDKey                              AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
extern const CFStringRef kICATWAINDSPathKey                         AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

//-------------------------------------------------------------------------------------------------------------------- ICAHeader
/*!
    @struct ICAHeader
    @discussion
        This is the first field in all parameter blocks used by APIs defined in ICAApplication.h.
        Type of parameter passed to a callback function used by APIs defined in ICAApplication.h.
        The parameter for the completion proc should to be casted to an appropriate type such as ICAGetChildCountPB* for it to be useful.
    @field err
        Error returned by an API. -->
    @field refcon
        An arbitrary refcon value passed to the callback. <--
*/
typedef struct ICAHeader {
    ICAError            err;
    unsigned long       refcon;
} ICAHeader;

//--------------------------------------------------------------------------------------------------------------- Callback procs

typedef CALLBACK_API_C( void , ICACompletion )(ICAHeader* pb);

typedef CALLBACK_API_C( Boolean , ICAImportFilterProc )(CFDictionaryRef imageInfo, unsigned long refcon);

typedef CALLBACK_API_C( void , ICANotificationProc )(CFStringRef notificationType, CFDictionaryRef notificationDictionary);

//------------------------------------------------------------------------------------------------------------------- Object IDs

typedef UInt32        ICAObject;
typedef UInt32        ICAProperty;
typedef UInt32        ICAConnectionID;
typedef UInt32        ICASessionID;
typedef ICASessionID  ICAScannerSessionID;
typedef UInt32        ICAEventDataCookie;

#pragma mark -
#pragma mark General APIs
//--------------------------------------------------------------------------------------------------------------- ICAImportImage
/*!
    @enum ImportImage flags.
    @discussion
        Flag values that can be used in ICAImportImagePB parameter block.
    @constant kICAAllowMultipleImages
        Use this constant to allow users to select multiple images in the Import Image dialog.
    @constant kICADownloadAndReturnPathArray
        Use this constant to download the images to a temporary location and return an array of paths to the downloaded images.
*/
enum
{
    kICAAllowMultipleImages               = 0x00000001,
    kICADownloadAndReturnPathArray        = 0x00000002
};

/*!
    @struct ICAImportImagePB
    @field header
        See description for ICAHeader.  <->
    @field deviceObject
        Object ID of a camera or scanner device. Set this to NULL to ge the default behavior: (a) if no device is connected, a panel saying that there’s no device connected is displayed, (b) if a single device is connected, an appropriate user interface to access that device will be displayed, (c) if several devices are connected, a device selector panel will be displayed. <--
    @field flags
        One or more flags (combined with an OR operator) defined in ImportImage flags enum. <--
    @field supportedFileTypes
        An array of file extension strings such as "jpg", "tif", etc., that are of interest to the calling application. Set to NULL to display all files. <--
    @field filterProc
        Specify a filter proc to that will be called for each file before it is displayed in the user interface. <--
    @field importedImages
        Returns an array of CFDataRefs for the imported images if the kICADownloadAndReturnPathArray flag is not specified. Otherwise returns an array of CFStringRefs holding the paths of the images that are downloaded. -->
*/
typedef struct ICAImportImagePB {
    ICAHeader           header;
    ICAObject           deviceObject;
    UInt32              flags;
    CFArrayRef          supportedFileTypes;
    ICAImportFilterProc filterProc;
    CFArrayRef*         importedImages;
} ICAImportImagePB;

/*!
    @function ICAImportImage
    @abstract
        This API displays a Common User Interface panel similar to the user interface of Image Capture Application. This allows the user to work a camera or a scanner.
    @discussion
        Use this API to add Image Capture support to an application.

<pre>
@textblock
        Example:
        
        void ImportImage()
        {
            OSErr             err;
            ICAImportImagePB  pb = {};

            pb.deviceObject       = 0;
            pb.flags              = 0;
            pb.supportedFileTypes = (CFArrayRef)[NSArray arrayWithObjects: @"tif", @"tiff", @"jpg", NULL];
            
            err = ICAImportImage(&pb, NULL);

            if ( noErr != err )
            {
                // handle error
            }
            else
            {
                // Process the importedImages array
                // pb.importedImages   // CFArrayRef *
            }
        }
@/textblock
</pre>

    @param pb
        A pointer to an <code><b>ICAImportImagePB</b></code> parameter block.
    @param completion
        A pointer to a completion routine that will be invoked at the completion of <code><b>ICAImportImage</b></code> function. Set this parameter to <code><b>NULL</b></code> to invoke this API synchronously. 
    @result
        Returns an error code defined in ICAApplication.h
*/
extern ICAError 
ICAImportImage(
    ICAImportImagePB* pb,
    ICACompletion     completion
)                                                                                     AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

//--------------------------------------------------------------------------------------------------------- ICAShowDeviceBrowser
/*!
    @function ICAShowDeviceBrowser
    @abstract
        Use this API to display a device browser user interface from any Image Capture client application.
    @discussion
        The device browser user interface allows the user to do the following:
          - enable and disable sharing of locally connected cameras and scanners.
          - connect to or disconnect from cameras and scanners shared by other computers.
          - configure WiFi capable cameras for use over the WiFi network.
    @param options
        Set options to NULL to display the device browser with default settings. <--
        This parameter is intended for future use.
    @result
        Returns an error code defined in ICAApplication.h
*/
extern ICAError
ICAShowDeviceBrowser(
    CFDictionaryRef options
)                                                                                     AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

//---------------------------------------------------------------------------------------------- ICARegisterForEventNotification
/* Function prototype for an Image Capture notification callback proc
   This function will be called with a notificationDictionary that may
   contain one or more key-value pairs as defined below:
   
    Key                                 Value Type        Comments
    
    kICANotificationICAObjectKey        CFNumberRef       An object associated with the notification.
    kICANotificationDeviceICAObjectKey  CFNumberRef       A device object associated with the notification.
    kICANotificationClassKey            CFStringRef       See below.
    kICANotificationTypeKey             CFStringRef       See below.
    kICANotificationRawEventKey         CFNumberRef       The unprocesssed event code sent by a device.
    kICANotificationDataKey             CFDataRef         Data associated with the event.
    kICANotificationDataSizeKey         CFNumberRef       Size of data associated with the event. This is used if the data is
                                                          not sent with the notification. [Needed for backward compatiblity with pre-Leopard device modules].
    kICANotificationDataCookieKey       CFNumberRef       A token identifying the data associated with this event.
                                                          This data can be retrieved by calling ICAObjectSendMessage with messageType set to kICAMessageGetEventData, dataType set to value of kICANotificationDataCookieKeyand dataSize set to value of kICANotificationDataSizeKey.
                                          
    The following keys are present if the value of kICANotificationDataKey represents image data. The values of these
    keys are CFNumbers representing the width, height, bytes per row, start row, and number of rows of the image:
    
    kICANotificationImageKey              CFDictionaryRef A dictionary that describes an Image associated
                                                          with the notification.
    kICANotificationImageDataKey          CFDataRef       Image data
    kICANotificationImageWidthKey         CFNumberRef     Image width in pixels
    kICANotificationImageHeightKey        CFNumberRef     Image height in pixels
    kICANotificationImageBytesPerRowKey   CFNumberRef     Bytes per row in image
    kICANotificationImageStartRowKey      CFNumberRef     Starting row number of the image.
    kICANotificationImageNumberOfRowsKey  CFNumberRef     Number of rows of image data sent in this notification.
*/
typedef CALLBACK_API_C( void , ICANotification )(CFStringRef notificationType, CFDictionaryRef notificationDictionary);

// Possible values for kICANotificationTypeKey:

extern const CFStringRef  kICANotificationTypeObjectAdded               AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern const CFStringRef  kICANotificationTypeObjectRemoved             AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern const CFStringRef  kICANotificationTypeObjectInfoChanged         AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

extern const CFStringRef  kICANotificationTypeStoreAdded                AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern const CFStringRef  kICANotificationTypeStoreRemoved              AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern const CFStringRef  kICANotificationTypeStoreFull                 AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern const CFStringRef  kICANotificationTypeStoreInfoChanged          AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

extern const CFStringRef  kICANotificationTypeDeviceAdded               AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern const CFStringRef  kICANotificationTypeDeviceRemoved             AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

extern const CFStringRef  kICANotificationTypeDeviceInfoChanged         AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern const CFStringRef  kICANotificationTypeDevicePropertyChanged     AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern const CFStringRef  kICANotificationTypeDeviceWasReset            AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

extern const CFStringRef  kICANotificationTypeCaptureComplete           AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern const CFStringRef  kICANotificationTypeRequestObjectTransfer     AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern const CFStringRef  kICANotificationTypeTransactionCanceled       AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

extern const CFStringRef  kICANotificationTypeUnreportedStatus          AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern const CFStringRef  kICANotificationTypeProprietary               AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

extern const CFStringRef  kICANotificationTypeDeviceConnectionProgress  AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern const CFStringRef  kICANotificationTypeDownloadProgressStatus    AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern const CFStringRef  kICANotificationTypeScanProgressStatus        AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern const CFStringRef  kICANotificationTypeScannerSessionClosed      AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern const CFStringRef  kICANotificationTypeScannerScanDone           AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern const CFStringRef  kICANotificationTypeScannerPageDone           AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern const CFStringRef  kICANotificationTypeScannerButtonPressed      AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

// Possible keys in the notification dictionary:

extern const CFStringRef  kICAErrorKey                                  AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern const CFStringRef  kICARefconKey                                 AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

extern const CFStringRef  kICANotificationICAObjectKey                  AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern const CFStringRef  kICANotificationDeviceICAObjectKey            AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern const CFStringRef  kICANotificationDeviceListICAObjectKey        AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern const CFStringRef  kICANotificationClassKey                      AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern const CFStringRef  kICANotificationTypeKey                       AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern const CFStringRef  kICANotificationRawEventKey                   AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern const CFStringRef  kICANotificationDataKey                       AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern const CFStringRef  kICANotificationDataSizeKey                   AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern const CFStringRef  kICANotificationDataCookieKey                 AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

extern const CFStringRef  kICANotificationImageKey                      AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern const CFStringRef  kICANotificationImageWidthKey                 AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern const CFStringRef  kICANotificationImageHeightKey                AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern const CFStringRef  kICANotificationImageBytesPerRowKey           AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern const CFStringRef  kICANotificationImageStartRowKey              AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern const CFStringRef  kICANotificationImageNumberOfRowsKey          AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern const CFStringRef  kICANotificationImageDataKey                  AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern const CFStringRef  kICANotificationImageDataSizeKey              AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern const CFStringRef  kICANotificationDataIsBigEndianKey            AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

extern const CFStringRef  kICANotificationScannerDocumentNameKey        AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern const CFStringRef  kICANotificationScannerButtonTypeKey          AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

extern const CFStringRef  kICANotificationNumerOfImagesRemainingKey                   AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern const CFStringRef  kICANotificationPercentDownloadedKey                        AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

// Possible values in the notification dictionary:
// ...

// Possible values for kICANotificationClassKey
extern const CFStringRef  kICANotificationClassPTPStandard                            AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern const CFStringRef  kICANotificationClassPTPVendor                              AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern const CFStringRef  kICANotificationClassProprietary                            AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

// Device Properties

extern const CFStringRef kICADevicePropUndefined                                      AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern const CFStringRef kICADevicePropBatteryLevel                                   AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern const CFStringRef kICADevicePropFunctionalMode                                 AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern const CFStringRef kICADevicePropImageSize                                      AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern const CFStringRef kICADevicePropCompressionSetting                             AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern const CFStringRef kICADevicePropWhiteBalance                                   AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern const CFStringRef kICADevicePropRGBGain                                        AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern const CFStringRef kICADevicePropFNumber                                        AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern const CFStringRef kICADevicePropFocalLength                                    AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern const CFStringRef kICADevicePropFocusDistance                                  AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern const CFStringRef kICADevicePropFocusMode                                      AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern const CFStringRef kICADevicePropExposureMeteringMode                           AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern const CFStringRef kICADevicePropFlashMode                                      AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern const CFStringRef kICADevicePropExposureTime                                   AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern const CFStringRef kICADevicePropExposureProgramMode                            AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern const CFStringRef kICADevicePropExposureIndex                                  AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern const CFStringRef kICADevicePropExposureBiasCompensation                       AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern const CFStringRef kICADevicePropDateTime                                       AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern const CFStringRef kICADevicePropCaptureDelay                                   AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern const CFStringRef kICADevicePropStillCaptureMode                               AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern const CFStringRef kICADevicePropContrast                                       AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern const CFStringRef kICADevicePropSharpness                                      AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern const CFStringRef kICADevicePropDigitalZoom                                    AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern const CFStringRef kICADevicePropEffectMode                                     AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern const CFStringRef kICADevicePropBurstNumber                                    AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern const CFStringRef kICADevicePropBurstInterval                                  AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern const CFStringRef kICADevicePropTimelapseNumber                                AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern const CFStringRef kICADevicePropTimelapseInterval                              AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern const CFStringRef kICADevicePropFocusMeteringMode                              AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern const CFStringRef kICADevicePropUploadURL                                      AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern const CFStringRef kICADevicePropArtist                                         AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern const CFStringRef kICADevicePropCopyrightInfo                                  AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/*!
    @struct ICARegisterForEventNotificationPB
    @discussion
        Use this parameter structure to specify a set of events associated with an object
        about which notifications should be sent to the specified notification function.
    @field header
        See description for ICAHeader. <->
    @field objectOfInterest
        An object about which notifications are requested. <--
    @field eventsOfInterest
        An array of notification types of interest. <--
    @field notificationProc
        A callback function to receive the notifications. <--
    @field options
        Set options to NULL. This parameter is intended for future use. <--
*/

typedef struct ICARegisterForEventNotificationPB {
    ICAHeader           header;
    ICAObject           objectOfInterest;
    CFArrayRef          eventsOfInterest;
    ICANotification     notificationProc;
    CFDictionaryRef     options;
} ICARegisterForEventNotificationPB;

/*!
    @function ICARegisterForEventNotification
    @abstract
        Use this API to register with Image Capture framework to receive
        notification about events of interest.
    @param params
        A pointer to ICARegisterForEventNotificationPB struct <--
    @param completionProc
        A pointer to a completion routine that will be invoked at the completion of
        this function. Set this parameter to NULL to invoke this API synchronously. 
    @result
        Returns an error code defined in ICAApplication.h
*/
extern ICAError
ICARegisterForEventNotification(
    ICARegisterForEventNotificationPB*	params,
    ICACompletion                       completionProc
)                                                                                     AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

//---------------------------------------------------------------------------------------------------------- ICASendNotification
// This parameter block is used with 'ICDSendNotification' and 'ICDSendNotificationAndWaitForReply' APIs defined
// in ICADevices.framework

typedef struct ICASendNotificationPB
{
    ICAHeader               header;
    CFMutableDictionaryRef  notificationDictionary;
    UInt32                  replyCode;
} ICASendNotificationPB;

extern ICAError ICASendNotification( ICASendNotificationPB* pb );
extern ICAError ICASendNotificationAndWaitForReply( ICASendNotificationPB* pb );

#pragma mark -
#pragma mark Object related APIs
//------------------------------------------------------------------------------------------------------------- ICAGetDeviceList
/*!
    @struct ICAGetDeviceListPB
    @field header
        See description for ICAHeader. <-->
    @field object
        The device list object, if ICAGetDeviceList returns successfully. -->
*/
typedef struct ICAGetDeviceListPB {
    ICAHeader           header;
    ICAObject           object;
} ICAGetDeviceListPB;

/*!
    @function ICAGetDeviceList
    @abstract
        Fetches the object at the top of the object heirarchy.
    @discussion
        Image Capture framework presents cameras and scanners, their contents and their capabilities as a heirarchy of objects and their properties. The device list object is at the top of the heirarchy of objects. The <b><code>ICAGetDeviceList</b></code> function fetches this object in the <code><b>object</b></code> field of parameter <code><b>pb</b></code>. Children of the device list object can be accessed by passing the device list object to functions <code><b>ICAGetChildCount()</b></code> and <code>ICAGetNthChild()</code>.
        
<pre>
@textblock
        Example:
        
        ICAObject GetDeviceList()
        {
            ICAGetDeviceListPB getDeviceListPB  = {};
            ICAObject          deviceList       = 0;
            OSErr              err;
            
            err = ICAGetDeviceList( &getDeviceListPB, nil );
            
            if ( noErr == err )
            {
                deviceList = getDeviceListPB.object;
            }
            
            return deviceList;
        }
@/textblock
</pre>

    @param pb
        A pointer to an <code><b>ICAGetDeviceListPB</b></code> parameter block.
    @param completion
        A pointer to a completion routine that will be invoked at the completion of <code><b>ICAGetDeviceList</b></code> function. Set this parameter to <code><b>NULL</b></code> to invoke this API synchronously. 
    @result
        Returns an error code defined in ICAApplication.h
*/
extern ICAError 
ICAGetDeviceList(
    ICAGetDeviceListPB* pb,
    ICACompletion       completion
)                                                                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

//---------------------------------------------------------------------------------------------- ICACopyObjectPropertyDictionary
/*!
    @struct ICACopyObjectPropertyDictionaryPB
    @field header
        See description for ICAHeader. <->
    @field object
        An object whose properties are being requested. <--
    @field theDict
        A dictionary to hold the properties. This must be released by the caller. -->
*/
typedef struct ICACopyObjectPropertyDictionaryPB {
    ICAHeader           header;
    ICAObject           object;
    CFDictionaryRef*    theDict;
} ICACopyObjectPropertyDictionaryPB;

/*!
    @function ICACopyObjectPropertyDictionary
    @abstract
        Use this API to get a CFDictionaryRef containing all the properties for an object specified in the object field of the ICACopyObjectPropertyDictionaryPB struct.
    @discussion
        This API is the preferred way to get to any ICAObject related property data.
        
<pre>
@textblock
        Example:
        
        void  CopyObjectPropertyDictionary()
        {
            OSErr                             err;
            ICACopyObjectPropertyDictionaryPB pb = {};

            pb.object = <#ICAObject object#>;
            err = ICACopyObjectPropertyDictionary( &pb, NULL );

            if ( noErr != err)
            {
                // handle error
            }
            else
            {
                // Make sure to release the returned dictionary
                // pb.theDict   // CFDictionaryRef *
            }
        }
        
@/textblock
</pre>

    @param pb
        A pointer to an <code><b>ICACopyObjectPropertyDictionaryPB</b></code> parameter block.
    @param completion
        A pointer to a completion routine that will be invoked at the completion of <code><b>ICACopyObjectPropertyDictionary</b></code> function. Set this parameter to <code><b>NULL</b></code> to invoke this API synchronously. 
    @result
        Returns an error code defined in ICAApplication.h
*/
extern ICAError 
ICACopyObjectPropertyDictionary(
    ICACopyObjectPropertyDictionaryPB*  pb,
    ICACompletion                       completion
)                                                                                     AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;

//------------------------------------------------------------------------------------------------------- ICACopyObjectThumbnail
/*!
    @enum Thumbnail formats.
    @discussion
        Format alues that can be used in ICACopyObjectThumbnailPB parameter block.
    @constant kICAThumbnailFormatICA
        Use this constant to receive a thumbnail in ICAThumbnail structure.  Deprecated in 10.5.
    @constant kICAThumbnailFormatJPEG
        Use this constant to receive a thumbnail in JPEG format.
    @constant kICAThumbnailFormatTIFF
        Use this constant to receive a thumbnail in TIFF format.
    @constant kICAThumbnailFormatPNG
        Use this constant to receive a thumbnail in PNG format.
*/
enum 
{
    kICAThumbnailFormatICA                = 'ica ',
    kICAThumbnailFormatJPEG               = 'jpeg',
    kICAThumbnailFormatTIFF               = 'tiff',
    kICAThumbnailFormatPNG                = 'png '
};

/*!
    @struct ICACopyObjectThumbnailPB
    @field header
        See description for ICAHeader. <->
    @field object
        An object whose thumbail is being requested. <--
    @field thumbnailFormat
        One of the format values defined above. <--
    @field thumbnailData
        A pointer to a CFDataRef holding the thumbnail data. The returned CFDataRef must be released by the caller. -->
*/
typedef struct ICACopyObjectThumbnailPB {
    ICAHeader           header;
    ICAObject           object;
    OSType              thumbnailFormat;
    CFDataRef*          thumbnailData;
} ICACopyObjectThumbnailPB;

/*!
    @function ICACopyObjectThumbnail
    @abstract
        Use this API to get a thumbnail associated with an object.
    @discussion
        This is the recommended way to get the thumbnail of an object. Getting the thumbnail using ICAGetPropertyData is deprecaed in 10.5.
        
<pre>
@textblock
        Example:
        
        void CopyObjectThumbnail()
        {
            OSErr                     err;
            ICACopyObjectThumbnailPB  pb = {};

            pb.object          = <#ICAObject object#>;
            pb.thumbnailFormat = <#OSType thumbnailFormat#>;
            
            err = ICACopyObjectThumbnail( &pb, NULL );

            if ( noErr != err )
            {
                // handle error
            }
            else
            {
                // Make sure to release the thumbnailData
                // pb.thumbnailData   // CFDataRef *
            }
        }
@/textblock
</pre>

    @param pb
        A pointer to an <code><b>ICACopyObjectThumbnailPB</b></code> parameter block.
    @param completion
        A pointer to a completion routine that will be invoked at the completion of <code><b>ICACopyObjectThumbnail</b></code> function. Set this parameter to <code><b>NULL</b></code> to invoke this API synchronously. 
    @result
        Returns an error code defined in ICAApplication.h
*/
extern ICAError 
ICACopyObjectThumbnail(
    ICACopyObjectThumbnailPB* pb,
    ICACompletion             completion
)                                                                                     AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

//------------------------------------------------------------------------------------------------------------ ICACopyObjectData
/*!
    @struct ICACopyObjectDataPB
    @field header
        See description for ICAHeader.  <->
    @field object
        A file object.  <--
    @field startByte
        Starting byte offset of the data in the file object.  <--
    @field requestedSize
        Requested data size in bytes. <--
    @field data
        A pointer to CFDataRef in which the data will be returned. -->
        It is the responsibility fo the caller to release this object. 
*/
typedef struct ICACopyObjectDataPB {
    ICAHeader           header;
    ICAObject           object;
    size_t              startByte;
    size_t              requestedSize;
    CFDataRef*          data;
} ICACopyObjectDataPB;

/*!
    @function ICACopyObjectData
    @abstract
        Use this API to get a copy of data associated with a file object.
    @discussion
        Use this API to get a copy of data associated with a file object. This API should be used in place of ICAGetPropertyData.
    @param params
        A pointer to ICACopyObjectDataPB struct <--
    @param completionProc
        A pointer to a completion routine that will be invoked at the completion of
        this function. Set this parameter to NULL to invoke this API synchronously. 
    @result
        Returns an error code defined in ICAApplication.h
*/
extern ICAError 
ICACopyObjectData(
    ICACopyObjectDataPB*  params,
    ICACompletion         completionProc
)                                                                                     AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

//--------------------------------------------------------------------------------------------------------- ICAObjectSendMessage
/*!
    @struct ICAMessage
    @field messageType
        A message type. e.g., kICAMessageCameraCaptureNewImage. <--
    @field startByte
        Offset in dataPtr from where data access for read/write should occur. <--
    @field dataPtr
        A pointer to a data buffer. <--
    @field dataSize
        Size of data. <--
    @field dataType
        Type of data. <--
*/
typedef struct ICAMessage {
    OSType              messageType;
    UInt32              startByte;
    void *              dataPtr;
    UInt32              dataSize;
    OSType              dataType;
} ICAMessage;

/*!
    @enum ICAMessage types
    @discussion
        Definition of ICAMessage types.
    @constant kICAMessageConnect
        Connect to device.
    @constant kICAMessageDisconnect
        Disconnect device.
    @constant kICAMessageReset
        Reset device.
    @constant kICAMessageCheckDevice
        Check device.
    @constant kICAMessageCameraReadClock
        Read clock from device.
    @constant kICAMessageGetLastButtonPressed
        Get last button pressed on the device (scanner).
    @constant kICAMessageGetEventData
        Get data associated with an event.
    @constant kMessageGetEventData
        Get data associated with an event. This is deprecated in favor of kICAMessageGetEventData.
    @constant kICAMessageDeviceYield
        Yield device. Image Capture framework yields a device so that the sender of the message can directly communicate with the device.
*/
enum
{
    kICAMessageConnect                    = 'open',
    kICAMessageDisconnect                 = 'clos',	
    kICAMessageReset                      = 'rese',	
    kICAMessageCheckDevice                = 'chkd',
    kICAMessageCameraReadClock            = 'rclk',
    kICAMessageGetLastButtonPressed       = 'btn?',
    kMessageGetEventData                  = 'mged',       // Deprecated in 10.5
    kICAMessageGetEventData               = 'mged',
    kICAMessageDeviceYield                = 'yiel',
    kICAMessageCameraPassThrough          = 'pass'
};

/*!
    @struct ICAObjectSendMessagePB
    @field header
        See description for ICAHeader. <-->
    @field object
        A target object for the message sent by ICAObjectSendMessage. <--
    @field message
        One of the messages define above. <--
    @field result
        A message specific result is returned here. -->
*/
typedef struct ICAObjectSendMessagePB {
    ICAHeader           header;
    ICAObject           object;
    ICAMessage          message;
    UInt32              result;
} ICAObjectSendMessagePB;

/*!
    @function ICAObjectSendMessage
    @abstract
        Use this API to send a message to a device object.
    @discussion
        Use this API to send a message to a device object. All devices do not respond to all the messages defined above.
    @param pb
        A pointer to an <code><b>ICAObjectSendMessagePB</b></code> parameter block.
    @param completion
        A pointer to a completion routine that will be invoked at the completion of <code><b>ICAObjectSendMessage</b></code> function. Set this parameter to <code><b>NULL</b></code> to invoke this API synchronously. 
    @result
        Returns an error code defined in ICAApplication.h
*/
extern ICAError 
ICAObjectSendMessage(
    ICAObjectSendMessagePB* pb,
    ICACompletion           completion
)                                                                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

//-------------------------------------------------------------------------------------------------------------- ICADownloadFile
/*!
    @enum Flag to use with ICADownloadFile
    @discussion
        Use any combination of these values when downloading a file.
    @constant kDeleteAfterDownload
        Delete file after a successful download.
    @constant kCreateCustomIcon
        Create a custom icon for Finder.
    @constant kAddMetaDataToFinderComment
        Add basic metadata to finder comment field.
    @constant kAdjustCreationDate
        Set creation date of the downloaded file same as the creation date for the file as reported by the device.
    @constant kSetFileTypeAndCreator
        Set 4-char file type and creator code.
    @constant kRotateImage
        Rotate the image.
    @constant kDontEmbedColorSyncProfile
        Embed ColorSync profile to the image if one was not already embedded.
*/
enum
{
    kDeleteAfterDownload                  = 0x00000001,
    kCreateCustomIcon                     = 0x00000002,
    kAddMetaDataToFinderComment           = 0x00000004,
    kAdjustCreationDate                   = 0x00000008,
    kSetFileTypeAndCreator                = 0x00000010,
    //kEmbedColorSyncProfile              = 0x00000020,
    kRotateImage                          = 0x00000040,
    kDontEmbedColorSyncProfile            = 0x00000080
};  

/*!
    @struct ICADownloadFilePB
    @field header
        See description for ICAHeader. <->
    @field object
        The file object. <--
    @field dirFSRef
        FSRef of destination directiory. <--
    @field flags 
        Any combination of flag values defined above. <--
    @field fileType
        Four-char code indicating the type of file. <--
    @field fileCreator
        Four-char code indicating with the creator of the file. <--
    @field rotationAngle
        Rotation angle in steps of 90 degress. <--
    @field fileFSRef
        A pointer to FSRef struct to hold the FSRef of downloaded file. Set this to NULL if the FSRef of downloaded file is not of interest. --> 
*/
typedef struct ICADownloadFilePB {
    ICAHeader           header;
    ICAObject           object;
    FSRef *             dirFSRef;
    UInt32              flags;
    OSType              fileType;
    OSType              fileCreator;
    Fixed               rotationAngle;
    FSRef *             fileFSRef;
} ICADownloadFilePB;

/*!
    @function ICADownloadFile
    @abstract
        Use this API to download a file to disk. 
    @discussion
      This API is a convenient way to download a file to disk. To receive the image data in memory use ICACopyObjectData. Using ICAGetPropertyData is not recommend for this purpose since ICAGetPropertyData is Deprecated in 10.5.

<pre>
@textblock
        Example:
        
        void DownloadFile()
        {
            OSErr             err;
            ICADownloadFilePB pb = {};

            pb.flags         = <#UInt32 flags#>;
            pb.rotationAngle = <#Fixed rotationAngle#>;
            pb.object        = <#ICAObject object#>;
            pb.fileCreator   = <#OSType fileCreator#>;
            pb.dirFSRef      = <#FSRef * dirFSRef#>;
            pb.fileType      = <#OSType fileType#>;
            
            err = ICADownloadFile( &pb, NULL );

            if ( noErr != err )
            {
                // handle error
            }
            else
            {
                // pb.fileFSRef   // FSRef *
            }
        }
@/textblock
</pre>

    @param pb
        A pointer to an <code><b>ICADownloadFilePB</b></code> parameter block.
    @param completion
        A pointer to a completion routine that will be invoked at the completion of <code><b>ICADownloadFile</b></code> function. Set this parameter to <code><b>NULL</b></code> to invoke this API synchronously. 
    @result
        Returns an error code defined in ICAApplication.h
*/
extern ICAError 
ICADownloadFile(
    ICADownloadFilePB*  pb,
    ICACompletion       completion
)                                                                                     AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;

//---------------------------------------------------------------------------------------------------------------- ICAUploadFile
/*!
    @enum Upload file option flags.
    @discussion
        Flag values that can be used in ICAUploadFilePB parameter block.
    @constant kICAUploadFileAsIs
        Use this constant to upload a file as is.
    @constant kICAUploadFileScaleToFit
        Use this constant to upload a file after scaling to fit a specified bounding rect.
*/
enum
{
    kICAUploadFileAsIs                    = 0x00000000,
    kICAUploadFileScaleToFit              = 0x00000001
};  

/*!
    @struct ICAUploadFilePB
    @field header
        See description for ICAHeader. <->
    @field parentObject <->
        An ICAObject corresponding to a folder on the device. The device will store the uploaded file inside this folder if possible.
    @field fileFSRef <--
        An FSRef for the file to be uploaded to the device.
    @field flags <--
        One of the flags defined above.
*/
typedef struct ICAUploadFilePB {
    ICAHeader           header;
    ICAObject           parentObject;
    FSRef*              fileFSRef;
    UInt32              flags;
} ICAUploadFilePB;

/*!
    @function ICAUploadFile
    @abstract
        Use this API to upload a file to a device that supports this capability.
    @discussion
        The device choses an appropriate destination location for the uploaded image and sends a kICANotificationTypeObjectAdded notification.
        
<pre>
@textblock
        Example:
        
        void  UploadFile()
        {
            OSErr           err;
            ICAUploadFilePB pb = {};

            pb.fileFSRef    = <#FSRef * fileFSRef#>;
            pb.flags        = <#UInt32 flags#>;
            pb.parentObject = <#ICAObject parentObject#>;
            
            err = ICAUploadFile( &pb, NULL );

            if ( noErr != err )
            {
                // handle error
            }
            else
            {
                // no return value(s)
            }
        }
@/textblock
</pre>

    @param pb
        A pointer to an <code><b>ICAUploadFilePB</b></code> parameter block.
    @param completion
        A pointer to a completion routine that will be invoked at the completion of <code><b>ICAUploadFile</b></code> function. Set this parameter to <code><b>NULL</b></code> to invoke this API synchronously. 
    @result
        Returns an error code defined in ICAApplication.h
*/
extern ICAError 
ICAUploadFile(
    ICAUploadFilePB*  pb,
    ICACompletion     completion
)                                                                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

#pragma mark -
#pragma mark Device related APIs
//---------------------------------------------------------------------------------------------------------- ICALoadDeviceModule
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


/*!
    @struct ICALoadDeviceModulePB
    @field header
        See description for ICAHeader. <->
    @field paramDictionary <--
        A parameter dictionary with sufficient key-value pairs to load a device module. This dictionary itself or the information provided in this dictionary will be sent to the device module.
*/
typedef struct ICALoadDeviceModulePB {
    ICAHeader           header;
    CFDictionaryRef     paramDictionary;
} ICALoadDeviceModulePB;

/*!
    @function ICALoadDeviceModule
    @abstract
        Use this API to load a device module.
    @discussion
        Typically, connecting a FireWire or an USB device will automatically load an appropriate device module. This API is needed only for loading a device module manually for devices that do not use a hot-plug interface, such as Bluetooth, SCSI, or TCP/IP.
    @param pb
        A pointer to an <code><b>ICALoadDeviceModulePB</b></code> parameter block.
    @param completion
        A pointer to a completion routine that will be invoked at the completion of <code><b>ICALoadDeviceModule</b></code> function. Set this parameter to <code><b>NULL</b></code> to invoke this API synchronously. 
    @result
        Returns an error code defined in ICAApplication.h
*/
extern ICAError 
ICALoadDeviceModule(
    ICALoadDeviceModulePB*  pb,
    ICACompletion           completion
)                                                                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

//--------------------------------------------------------------------------------------------------------- ICAUnloadDeviceModule
/*!
    @struct ICAUnloadDeviceModulePB
    @field header
        See description for ICAHeader. <->
    @field deviceObject <--
        A device ICAObject.
*/
typedef struct ICAUnloadDeviceModulePB {
    ICAHeader           header;
    ICAObject           deviceObject;
} ICAUnloadDeviceModulePB;

/*!
    @function ICAUnloadDeviceModule
    @abstract
        Uset this API to unload a device module.
    @discussion
        The device module providing this object will be unloaded, if this is the last device object provided by the device module.
    @param pb
        A pointer to an <code><b>ICAUnloadDeviceModulePB</b></code> parameter block.
    @param completion
        A pointer to a completion routine that will be invoked at the completion of <code><b>ICAUnloadDeviceModule</b></code> function. Set this parameter to <code><b>NULL</b></code> to invoke this API synchronously. 
    @result
        Returns an error code defined in ICAApplication.h
*/
extern ICAError 
ICAUnloadDeviceModule(
    ICAUnloadDeviceModulePB*  pb,
    ICACompletion             completion
)                                                                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

//--------------------------------------------------------------------------------------------------------------- ICAOpenSession
/*!
    @struct ICAOpenSessionPB
    @field header
        See description for ICAHeader. <->
    @field deviceObject
        A camera object. <--
    @field sessionID
        A session ID of the opened session. -->
*/
typedef struct ICAOpenSessionPB {
    ICAHeader           header;
    ICAObject           deviceObject;
    ICASessionID        sessionID;
} ICAOpenSessionPB;

/*!
    @function ICAOpenSession
    @abstract
        Use this API to open a session on a camera device. For a scanner device use the ICAScannerOpenSession API.
    @discussion
        This API gets a session ID for a open session on a camera device. Since access to cameras is generally not be session-based, this API generall will not fail. If the camera has open session, the device module controlling the camera will continue to control it during fast-user-switching.
    @param pb
        A pointer to an <code><b>ICAOpenSessionPB</b></code> parameter block.
    @param completion
        A pointer to a completion routine that will be invoked at the completion of <code><b>ICAOpenSession</b></code> function. Set this parameter to <code><b>NULL</b></code> to invoke this API synchronously. 
    @result
        Returns an error code defined in ICAApplication.h
*/
extern ICAError 
ICAOpenSession(
    ICAOpenSessionPB* pb,
    ICACompletion     completion
)                                                                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

//-------------------------------------------------------------------------------------------------------------- ICACloseSession
/*!
    @struct ICACloseSessionPB
    @field header
        See description for ICAHeader. <->
    @field sessionID
        A session ID of the session to be closed. <--
*/
typedef struct ICACloseSessionPB {
    ICAHeader           header;
    ICASessionID        sessionID;
} ICACloseSessionPB;

/*!
    @function ICACloseSession
    @abstract
        Use this API to close a session on a camera device. For a scanner device use the ICAScannerCloseSession API.
    @discussion
        This API closes an open session on a camera device. If the camera does not have any open sessions, the device module controlling the camera is free to give it up during fast-user-switching.
    @param pb
        A pointer to an <code><b>ICACloseSessionPB</b></code> parameter block.
    @param completion
        A pointer to a completion routine that will be invoked at the completion of <code><b>ICACloseSession</b></code> function. Set this parameter to <code><b>NULL</b></code> to invoke this API synchronously. 
    @result
        Returns an error code defined in ICAApplication.h
*/
extern ICAError 
ICACloseSession(
    ICACloseSessionPB*  pb,
    ICACompletion       completion
)                                                                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

//-------------------------------------------------------------------------------------------------------- ICAScannerOpenSession
/*!
    @struct ICAScannerOpenSessionPB
    @field header
        See description for ICAHeader. <->
    @field object
        A scanner object. <--
    @field sessionID
        A session ID of the opened session. -->
*/
typedef struct ICAScannerOpenSessionPB {
    ICAHeader            header;
    ICAObject            object;
    ICAScannerSessionID  sessionID;
} ICAScannerOpenSessionPB;

/*!
    @function ICAScannerOpenSession
    @abstract
        Use this API to open a session on a scanner device. For a camera device use the ICAOpenSession API.
    @discussion
        For a given scanner, this API returns a unique session ID that allows you to work with the device. This API will fail, if a session is already open.
    @param pb
        A pointer to an <code><b>ICAScannerOpenSessionPB</b></code> parameter block.
    @param completion
        A pointer to a completion routine that will be invoked at the completion of <code><b>ICAScannerOpenSession</b></code> function. Set this parameter to <code><b>NULL</b></code> to invoke this API synchronously. 
    @result
        Returns an error code defined in ICAApplication.h
*/
extern ICAError 
ICAScannerOpenSession(
    ICAScannerOpenSessionPB*  pb,
    ICACompletion             completion
)                                                                                     AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

//------------------------------------------------------------------------------------------------------- ICAScannerCloseSession
/*!
    @struct ICAScannerCloseSessionPB
    @field header
        See description for ICAHeader. <->
    @field sessionID
        A session ID of the session to be closed. <--
*/
typedef struct ICAScannerCloseSessionPB {
    ICAHeader           header;
    ICAScannerSessionID sessionID;
} ICAScannerCloseSessionPB;

/*!
    @function ICAScannerCloseSession
    @abstract
        Use this API to close a session on a scanner device. For a camera device use the ICACloseSession API.
    @discussion
        This API closes an open session, allowing other clients to work with the scanner.
    @param pb
        A pointer to an <code><b>ICAScannerCloseSessionPB</b></code> parameter block.
    @param completion
        A pointer to a completion routine that will be invoked at the completion of <code><b>ICAScannerCloseSession</b></code> function. Set this parameter to <code><b>NULL</b></code> to invoke this API synchronously. 
    @result
        Returns an error code defined in ICAApplication.h
*/
extern ICAError 
ICAScannerCloseSession(
    ICAScannerCloseSessionPB* pb,
    ICACompletion             completion
)                                                                                     AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

//--------------------------------------------------------------------------------------------------------- ICAScannerInitialize
/*!
    @struct ICAScannerInitializePB
    @field header
        See description for ICAHeader. <->
    @field sessionID
        A session ID of the scanner to be initialized. <--
*/
typedef struct ICAScannerInitializePB {
    ICAHeader           header;
    ICAScannerSessionID sessionID;
} ICAScannerInitializePB;

/*!
    @function ICAScannerInitialize
    @abstract
        Use this API to initialize a scanner device.
    @discussion
        After opening a session on a scanner device, use this API to set an initial state for the scanner.
    @param pb
        A pointer to an <code><b>ICAScannerInitializePB</b></code> parameter block.
    @param completion
        A pointer to a completion routine that will be invoked at the completion of <code><b>ICAScannerInitialize</b></code> function. Set this parameter to <code><b>NULL</b></code> to invoke this API synchronously. 
    @result
        Returns an error code defined in ICAApplication.h
*/
extern ICAError 
ICAScannerInitialize(
    ICAScannerInitializePB* pb,
    ICACompletion           completion
)                                                                                     AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

//------------------------------------------------------------------------------------------------------ ICAScannerGetParameters
/*!
    @struct ICAScannerGetParametersPB
    @field header
        See description for ICAHeader. <->
    @field sessionID
        A session ID of the scanner whose parameters are being fetched. <--
    @field theDict
        A dictionary containing the parameters. -->
*/
typedef struct ICAScannerGetParametersPB {
    ICAHeader               header;
    ICAScannerSessionID     sessionID;
    CFMutableDictionaryRef  theDict;
} ICAScannerGetParametersPB;

/*!
    @function ICAScannerGetParameters
    @abstract
        Use this API to get information about the scanner such as resolution, scanning area, etc.
    @discussion
        Use this API to get information about the scanner such as resolution, scanning area, etc.
    @param pb
        A pointer to an <code><b>ICAScannerGetParametersPB</b></code> parameter block.
    @param completion
        A pointer to a completion routine that will be invoked at the completion of <code><b>ICAScannerGetParameters</b></code> function. Set this parameter to <code><b>NULL</b></code> to invoke this API synchronously. 
    @result
        Returns an error code defined in ICAApplication.h
*/
extern ICAError 
ICAScannerGetParameters(
    ICAScannerGetParametersPB*  pb,
    ICACompletion               completion
)                                                                                     AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

//------------------------------------------------------------------------------------------------------ ICAScannerSetParameters
/*!
    @struct ICAScannerSetParametersPB
    @field header
        See description for ICAHeader. <->
    @field sessionID
        A session ID of the scanner whose parameters are being set. <--
    @field theDict
        A dictionary containing the parameters. <--
*/
typedef struct ICAScannerSetParametersPB {
    ICAHeader               header;
    ICAScannerSessionID     sessionID;
    CFMutableDictionaryRef  theDict;
} ICAScannerSetParametersPB;

/*!
    @function ICAScannerSetParameters
    @abstract
        Use this API to specify scan parameters that will be used when a scan is initiated via an ICAScannerStart.
    @discussion
        Use this API to specify scan parameters that will be used when a scan is initiated via an ICAScannerStart.
    @param pb
        A pointer to an <code><b>ICAScannerSetParametersPB</b></code> parameter block.
    @param completion
        A pointer to a completion routine that will be invoked at the completion of <code><b>ICAScannerSetParameters</b></code> function. Set this parameter to <code><b>NULL</b></code> to invoke this API synchronously. 
    @result
        Returns an error code defined in ICAApplication.h
*/
extern ICAError 
ICAScannerSetParameters(
    ICAScannerSetParametersPB*  pb,
    ICACompletion               completion
)                                                                                     AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

//------------------------------------------------------------------------------------------------------------- ICAScannerStatus
/*!
    @struct ICAScannerStatusPB
    @field header
        See description for ICAHeader. <->
    @field sessionID
        A session ID of the scanner whose status is being fetched. <--
    @field status
        A status value. -->
*/
typedef struct ICAScannerStatusPB {
    ICAHeader           header;
    ICAScannerSessionID sessionID;
    UInt32              status;
} ICAScannerStatusPB;

/*!
    @function ICAScannerStatus
    @abstract
        Use this API to get information about the current status of the scanner.
    @discussion
        Use this API to get information about the current status of the scanner.
    @param pb
        A pointer to an <code><b>ICAScannerStatusPB</b></code> parameter block.
    @param completion
        A pointer to a completion routine that will be invoked at the completion of <code><b>ICAScannerStatus</b></code> function. Set this parameter to <code><b>NULL</b></code> to invoke this API synchronously. 
    @result
        Returns an error code defined in ICAApplication.h
*/
extern ICAError 
ICAScannerStatus(
    ICAScannerStatusPB* pb,
    ICACompletion       completion
)                                                                                     AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

//-------------------------------------------------------------------------------------------------------------- ICAScannerStart
/*!
    @struct ICAScannerStartPB
    @field header
        See description for ICAHeader. <->
    @field sessionID
        A session ID of the scanner that should start scanning. <--
*/
typedef struct ICAScannerStartPB {
    ICAHeader           header;
    ICAScannerSessionID sessionID;
} ICAScannerStartPB;

/*!
    @function ICAScannerStart
    @abstract
        Use this API start a scan based on the parameters that were specified in a previous ICAScannerSetParameters call.
    @discussion
        Use this API start a scan based on the parameters that were specified in a previous ICAScannerSetParameters call.
    @param pb
        A pointer to an <code><b>ICAScannerStartPB</b></code> parameter block.
    @param completion
        A pointer to a completion routine that will be invoked at the completion of <code><b>ICAScannerStart</b></code> function. Set this parameter to <code><b>NULL</b></code> to invoke this API synchronously. 
    @result
        Returns an error code defined in ICAApplication.h
*/
extern ICAError 
ICAScannerStart(
    ICAScannerStartPB*  pb,
    ICACompletion       completion
)                                                                                     AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

#pragma mark -
#pragma mark Deprecated APIs
//----------------------------------------------------------------------------------------------------------------- ICAThumbnail
/*!
    @struct ICAThumbnail
    @discussion
        This type is deprecated. Use ICACopyObjectThumbnail call to receive thumbnail in JPG, TIFF or PNG format.
    @field width
        Thumbnail width in pixels.
    @field height
        Thumbnail height in pixels.
    @field dataSize
        Thumbnail size in bytes. This should be 3*height*width for thumbnails without alpha channel and should be 4*height*width for thumbnails with alpha channel.
        The alpha channel is always stored at the end of the buffer. 
    @field data
        Thumbnail buffer of 8-bit RGB data (RGBRGBRGB...)
*/
typedef struct ICAThumbnail {
    UInt32              width;
    UInt32              height;
    UInt32              dataSize;
    UInt8               data[1];
} ICAThumbnail                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;

//------------------------------------------------------------------------------------------------------------- ICAGetChildCount
/*!
    @struct ICAGetChildCountPB
    @field header
        See description for ICAHeader. <-->
    @field object
        An object whose number of children is being requested by calling ICAGetChildCount. <--
    @field count
        Number of children returned by ICAGetChildCount, if successful. Should check err field in header before using the value returned in count. -->
*/
typedef struct ICAGetChildCountPB {
    ICAHeader           header;
    ICAObject           object;
    UInt32              count;
} ICAGetChildCountPB                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;

/*!
    @function ICAGetChildCount
    @abstract
        Fetches the number of children of an object. This API is deprecated in 10.5.
    @discussion
        Image Capture framework presents cameras and scanners, their contents and their capabilities as a heirarchy of objects and their properties. The <code><b>ICAGetChildCount</b></code> function fetches the number of children of the object specified in the <code><b>object</b></code> field of paramter <code><b>pb</b></code>.

<pre>
@textblock
        Example:
        
        UInt32 GetNumberOfDevices ()
        {
            ICAGetChildCountPB getChildCountPB;
            OSErr              err;
            
            memset(&getChildCountPB, 0, sizeof(ICAGetChildCountPB));
            getChildCountPB.object = GetDeviceList();
            err = ICAGetChildCount(&getChildCountPB, nil);
            
            return getChildCountPB.count;
        }
@/textblock
</pre>

    @param pb
        A pointer to an <code><b>ICAGetChildCountPB</b></code> parameter block.
    @param completion
        A pointer to a completion routine that will be invoked at the completion of <code><b>ICAGetChildCount</b></code> function. Set this parameter to <code><b>NULL</b></code> to invoke this API synchronously. 
    @result
        Returns an error code defined in ICAApplication.h
*/
extern ICAError 
ICAGetChildCount(
    ICAGetChildCountPB* pb,
    ICACompletion       completion
)                                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;

//------------------------------------------------------------------------------------------------------------- ICAGetChildCount
/*!
    @struct ICAObjectInfo
    @field objectType
        An object type, e.g., kICAFile.
    @field objectSubtype
        An object subtype, e.g., kICAFileImage.
*/
typedef struct ICAObjectInfo {
    OSType              objectType;
    OSType              objectSubtype;
} ICAObjectInfo;

/*!
    @struct ICAGetNthChildPB
    @field header
        See description for ICAHeader. <-->
    @field parentObject
        An object whose child is being accessed. <--
    @field index
        A zero based index in to the children of 'parentObject'. <--
    @field childObject
        Child object, if ICAGetNthChild returns successfully. -->
    @field childInfo
        Object information for 'childObject', if ICAGetNthChild returns successfully. -->
*/
typedef struct ICAGetNthChildPB {
    ICAHeader           header;
    ICAObject           parentObject;
    UInt32              index;
    ICAObject           childObject;
    ICAObjectInfo       childInfo;
} ICAGetNthChildPB                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;

/*!
    @function ICAGetNthChild
    @abstract
        Fetches the child of a given object at a given index. This API is deprecated in 10.5.
    @discussion
        Image Capture framework presents cameras and scanners, their contents and their capabilities as a heirarchy of objects and their properties. The <code><b>ICAGetNthChild</b></code> function fetches the child object of an object specifed in the <code><b>parentObject</b></code> field of the parameter <code><b>pb</b></code> at the index specified in the <code><b>index</b></code> field of the parameter <code><b>pb</b></code>. The index is zero-based. The function also returns the ICAObjectInfo for the child object in the <code><b>childInfo</b></code> field of the parameter <code><b>pb</b></code>.

<pre>
@textblock
        Example:
        
        ICAObject GetFirstDevice () {
            ICAGetNthChildPB getNthChildPB;
            ICAObject        firstDevice = NULL;
            OSErr            err;
            UInt32           count;
            
            count = GetNumberOfDevices();
            if (count > 0)
            {
                memset(&getNthChildPB, 0, sizeof(ICAGetNthChildPB));
                getNthChildPB.parentObject = Get_Device_List();
                getNthChildPB.index = 0;
                err = ICAGetNthChild (&getNthChildPB, nil);
                if (noErr == err)
                {
                    firstDevice = getNthChildPB.childObject;
                }
            }
            return firstDevice;
        }
@/textblock
</pre>

    @param pb
        A pointer to an <code><b>ICAGetNthChildPB</b></code> parameter block.
    @param completion
        A pointer to a completion routine that will be invoked at the completion of <code><b>ICAGetNthChild</b></code> function. Set this parameter to <code><b>NULL</b></code> to invoke this API synchronously. 
    @result
        Returns an error code defined in ICAApplication.h
*/
extern ICAError 
ICAGetNthChild(
    ICAGetNthChildPB* pb,
    ICACompletion     completion
)                                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;

//------------------------------------------------------------------------------------------------------------- ICAGetObjectInfo
/*!
    @struct ICAGetObjectInfoPB
    @field header
        See description for ICAHeader. <-->
    @field object
        An object whose information is being requested by calling ICAGetObjectInfo. <--
    @field objectInfo
        Object information for 'object', if ICAGetObjectInfo returns successfully. -->
*/
typedef struct ICAGetObjectInfoPB {
    ICAHeader           header;
    ICAObject           object;
    ICAObjectInfo       objectInfo;
} ICAGetObjectInfoPB                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;

/*!
    @function ICAGetObjectInfo
    @abstract
        Use this API to get information about an object. This API is deprecated in 10.5.
    @discussion
        Use this API to get information about an object. This API is deprecated in 10.5.
    @param pb
        A pointer to an <code><b>ICAGetObjectInfoPB</b></code> parameter block.
    @param completion
        A pointer to a completion routine that will be invoked at the completion of <code><b>ICAGetObjectInfo</b></code> function. Set this parameter to <code><b>NULL</b></code> to invoke this API synchronously. 
    @result
        Returns an error code defined in ICAApplication.h
*/
extern ICAError 
ICAGetObjectInfo(
    ICAGetObjectInfoPB* pb,
    ICACompletion       completion
)                                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;

//--------------------------------------------------------------------------------------------------------- ICAGetParentOfObject
/*!
    @struct ICAGetParentOfObjectPB
    @field header
        See description for ICAHeader. <-->
    @field object
        An object whose parent is being accessed by calling ICAGetParentOfObject. <--
    @field parentObject
        Parent object, if ICAGetParentOfObject returns successfully. -->
    @field parentInfo
        Object information for the parent object, if ICAGetParentOfObject returns successfully. -->
*/
typedef struct ICAGetParentOfObjectPB {
    ICAHeader           header;
    ICAObject           object;
    ICAObject           parentObject;
    ICAObjectInfo       parentInfo;
} ICAGetParentOfObjectPB                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;

/*!
    @function ICAGetParentOfObject
    @abstract
        Use this API to get an object's parent object and its information. This API is deprecated in 10.5.
    @discussion
        Use this API to get an object's parent object and its information. This API is deprecated in 10.5.
    @param pb
        A pointer to an <code><b>ICAGetParentOfObjectPB</b></code> parameter block.
    @param completion
        A pointer to a completion routine that will be invoked at the completion of <code><b>ICAGetParentOfObject</b></code> function. Set this parameter to <code><b>NULL</b></code> to invoke this API synchronously. 
    @result
        Returns an error code defined in ICAApplication.h
*/
extern ICAError 
ICAGetParentOfObject(
    ICAGetParentOfObjectPB* pb,
    ICACompletion           completion
)                                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;

//----------------------------------------------------------------------------------------------------------- ICAGetRootOfObject
/*!
    @struct ICAGetRootOfObjectPB
    @field header
        See description for ICAHeader. <-->
    @field object
        An object whose parent is being accessed by calling ICAGetRootOfObject. <--
    @field rootObject
        Root object of the object hierarchy, if ICAGetRootOfObject returns successfully. -->
    @field rootInfo
        Object information for the root object, if ICAGetRootOfObject returns successfully. -->
*/
typedef struct ICAGetRootOfObjectPB {
    ICAHeader           header;
    ICAObject           object;
    ICAObject           rootObject;
    ICAObjectInfo       rootInfo;
} ICAGetRootOfObjectPB                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;

/*!
    @function ICAGetRootOfObject
    @abstract
        Use this API to get an object's root object (in the object hierarchy) and its information. This API is deprecated in 10.5.
    @discussion
        Use this API to get an object's root object (in the object hierarchy) and its information. This API is deprecated in 10.5.
    @param pb
        A pointer to an <code><b>ICAGetRootOfObjectPB</b></code> parameter block.
    @param completion
        A pointer to a completion routine that will be invoked at the completion of <code><b>ICAGetRootOfObject</b></code> function. Set this parameter to <code><b>NULL</b></code> to invoke this API synchronously. 
    @result
        Returns an error code defined in ICAApplication.h
*/
extern ICAError 
ICAGetRootOfObject(
    ICAGetRootOfObjectPB* pb,
    ICACompletion         completion
)                                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;

//----------------------------------------------------------------------------------------------------------- ICAGetObjectRefCon
/*!
    @struct ICAGetObjectRefConPB
    @field header
        See description for ICAHeader. <-->
    @field object
        An object whose associated refcon value is being accessed by calling ICAGetObjectRefCon. <--
    @field objectRefCon
        The refcon value. -->
*/
typedef struct ICAGetObjectRefConPB {
    ICAHeader           header;
    ICAObject           object;
    unsigned long       objectRefCon;
} ICAGetObjectRefConPB                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;

/*!
    @function ICAGetObjectRefCon
    @abstract
        Use this API to get an arbitrary refcon associated with an object. This API is deprecated in 10.5.
    @discussion
        Use this API to get an arbitrary refcon associated with an object. This API is deprecated in 10.5.
    @param pb
        A pointer to an <code><b>ICAGetObjectRefConPB</b></code> parameter block.
    @param completion
        A pointer to a completion routine that will be invoked at the completion of <code><b>ICAGetObjectRefCon</b></code> function. Set this parameter to <code><b>NULL</b></code> to invoke this API synchronously. 
    @result
        Returns an error code defined in ICAApplication.h
*/
extern ICAError 
ICAGetObjectRefCon(
    ICAGetObjectRefConPB* pb,
    ICACompletion         completion
)                                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;

//----------------------------------------------------------------------------------------------------------- ICASetObjectRefCon
/*!
    @struct ICASetObjectRefConPB
    @field header
        See description for ICAHeader. <-->
    @field object
        An object whose associated refcon value is being set by calling ICASetObjectRefCon. <--
    @field objectRefCon
        The refcon value. <--
*/
typedef struct ICASetObjectRefConPB {
    ICAHeader           header;
    ICAObject           object;
    unsigned long       objectRefCon;
} ICASetObjectRefConPB                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;

/*!
    @function ICASetObjectRefCon
    @abstract
        Use this API to set an arbitrary refcon for an object. This API is deprecated in 10.5.
    @discussion
        Use this API to set an arbitrary refcon for an object. This API is deprecated in 10.5.
    @param pb
        A pointer to an <code><b>ICASetObjectRefConPB</b></code> parameter block.
    @param completion
        A pointer to a completion routine that will be invoked at the completion of <code><b>ICASetObjectRefCon</b></code> function. Set this parameter to <code><b>NULL</b></code> to invoke this API synchronously. 
    @result
        Returns an error code defined in ICAApplication.h
*/
extern ICAError 
ICASetObjectRefCon(
    ICASetObjectRefConPB* pb,
    ICACompletion         completion
)                                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;

//---------------------------------------------------------------------------------------------------------- ICAGetPropertyCount
/*!
    @struct ICAGetPropertyCountPB
    @field header
        See description for ICAHeader. <-->
    @field object
        An object whose number of properties is being requested by calling ICAGetPropertyCount. <--
    @field count
        Number of properties returned by ICAGetPropertyCount, if successful. Should check err field in header before using the value returned in count. -->
*/
typedef struct ICAGetPropertyCountPB {
    ICAHeader           header;
    ICAObject           object;
    UInt32              count;
} ICAGetPropertyCountPB                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;

/*!
    @function ICAGetPropertyCount
    @abstract
        Use this API to get the number of properties an object has. This API is deprecated in 10.5.
    @discussion
        Use this API to get the number of properties an object has. This API is deprecated in 10.5.
    @param pb
        A pointer to an <code><b>ICAGetPropertyCountPB</b></code> parameter block.
    @param completion
        A pointer to a completion routine that will be invoked at the completion of <code><b>ICAGetPropertyCount</b></code> function. Set this parameter to <code><b>NULL</b></code> to invoke this API synchronously. 
    @result
        Returns an error code defined in ICAApplication.h
*/
extern ICAError 
ICAGetPropertyCount(
    ICAGetPropertyCountPB*  pb,
    ICACompletion           completion
)                                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;

//------------------------------------------------------------------------------------------------------------ ICAGetNthProperty
/*!
    @struct ICAPropertyInfo
    @field propertyType
        A property type.
    @field dataType
        A property subtype.
    @field dataSize
        Size of data associated with the property.
    @field dataFlags
        Reserved.
*/
typedef struct ICAPropertyInfo {
    OSType              propertyType;
    OSType              dataType;
    UInt32              dataSize;
    UInt32              dataFlags;
} ICAPropertyInfo;

/*!
    @struct ICAGetNthPropertyPB
    @field header
        See description for ICAHeader. <-->
    @field object
        An object whose property is being fetched. <--
    @field index
        A zero based index in to the properties of 'object'. <--
    @field property
        Property, if ICAGetNthProperty returns successfully. -->
    @field propertyInfo
        Property information for 'property', if ICAGetNthProperty returns successfully. -->
*/
typedef struct ICAGetNthPropertyPB {
      ICAHeader           header;
      ICAObject           object;
      UInt32              index;
      ICAProperty         property;
      ICAPropertyInfo     propertyInfo;
} ICAGetNthPropertyPB                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;

/*!
    @function ICAGetNthProperty
    @abstract
        Use this API to get an object's specific property and its information. This API is deprecated in 10.5.
    @discussion
        Use this API to get an object's specific property and its information. This API is deprecated in 10.5.
    @param pb
        A pointer to an <code><b>ICAGetNthPropertyPB</b></code> parameter block.
    @param completion
        A pointer to a completion routine that will be invoked at the completion of <code><b>ICAGetNthProperty</b></code> function. Set this parameter to <code><b>NULL</b></code> to invoke this API synchronously. 
    @result
        Returns an error code defined in ICAApplication.h
*/
extern ICAError 
ICAGetNthProperty(
    ICAGetNthPropertyPB*  pb,
    ICACompletion         completion
)                                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;

//--------------------------------------------------------------------------------------------------------- ICAGetPropertyByType
/*!
    @struct ICAGetPropertyByTypePB
    @field header
        See description for ICAHeader. <-->
    @field object
        An object whose property is being fetched. <--
    @field propertyType
        The type of property being fetched. <--
    @field property
        Property, if ICAGetPropertyByType returns successfully. -->
    @field propertyInfo
        Property information for 'property', if ICAGetPropertyByType returns successfully. -->
*/
typedef struct ICAGetPropertyByTypePB {
    ICAHeader           header;
    ICAObject           object;
    OSType              propertyType;
    ICAProperty         property;
    ICAPropertyInfo     propertyInfo;
} ICAGetPropertyByTypePB                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;

/*!
    @function ICAGetPropertyByType
    @abstract
        Use this API to get an object's property by type and its information. This API is deprecated in 10.5.
    @discussion
        Use this API to get an object's property by type and its information. This API is deprecated in 10.5.
    @param pb
        A pointer to an <code><b>ICAGetPropertyByTypePB</b></code> parameter block.
    @param completion
        A pointer to a completion routine that will be invoked at the completion of <code><b>ICAGetPropertyByType</b></code> function. Set this parameter to <code><b>NULL</b></code> to invoke this API synchronously. 
    @result
        Returns an error code defined in ICAApplication.h
*/
extern ICAError 
ICAGetPropertyByType(
    ICAGetPropertyByTypePB* pb,
    ICACompletion           completion
)                                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;

//----------------------------------------------------------------------------------------------------------- ICAGetPropertyInfo
/*!
    @struct ICAGetPropertyInfoPB
    @field header
        See description for ICAHeader. <-->
    @field property
        Property whose information is being fetched. <--
    @field propertyInfo
        Property information for 'property', if ICAGetPropertyInfo returns successfully. -->
*/
typedef struct ICAGetPropertyInfoPB {
    ICAHeader           header;
    ICAProperty         property;
    ICAPropertyInfo     propertyInfo;
} ICAGetPropertyInfoPB                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;

/*!
    @function ICAGetPropertyInfo
    @abstract
        Use this API to get information about a property. This API is deprecated in 10.5.
    @discussion
        Use this API to get information about a property. This API is deprecated in 10.5.
    @param pb
        A pointer to an <code><b>ICAGetPropertyInfoPB</b></code> parameter block.
    @param completion
        A pointer to a completion routine that will be invoked at the completion of <code><b>ICAGetPropertyInfo</b></code> function. Set this parameter to <code><b>NULL</b></code> to invoke this API synchronously. 
    @result
        Returns an error code defined in ICAApplication.h
*/
extern ICAError 
ICAGetPropertyInfo(
    ICAGetPropertyInfoPB* pb,
    ICACompletion         completion
)                                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;

//------------------------------------------------------------------------------------------------------- ICAGetParentOfProperty
/*!
    @struct ICAGetParentOfPropertyPB
    @field header
        See description for ICAHeader. <-->
    @field property
        A property whose parent is being fetched. <--
    @field parentObject
        Parent object, if ICAGetParentOfProperty returns successfully. -->
    @field parentInfo
        Information about 'parentObject', if ICAGetParentOfProperty returns successfully. -->
*/
typedef struct ICAGetParentOfPropertyPB {
    ICAHeader           header;
    ICAProperty         property;
    ICAObject           parentObject;
    ICAObjectInfo       parentInfo;
} ICAGetParentOfPropertyPB                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;

/*!
    @function ICAGetParentOfProperty
    @abstract
        Uset this API to get a property's parent object and its information. This API is deprecated in 10.5.
    @discussion
        Uset this API to get a property's parent object and its information. This API is deprecated in 10.5.
    @param pb
        A pointer to an <code><b>ICAGetParentOfPropertyPB</b></code> parameter block.
    @param completion
        A pointer to a completion routine that will be invoked at the completion of <code><b>ICAGetParentOfProperty</b></code> function. Set this parameter to <code><b>NULL</b></code> to invoke this API synchronously. 
    @result
        Returns an error code defined in ICAApplication.h
*/
extern ICAError 
ICAGetParentOfProperty(
    ICAGetParentOfPropertyPB* pb,
    ICACompletion             completion
)                                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;

//--------------------------------------------------------------------------------------------------------- ICAGetRootOfProperty
/*!
    @struct ICAGetRootOfPropertyPB
    @field header
        See description for ICAHeader. <-->
    @field property
        A property whose parent is being fetched. <--
    @field rootObject
        Root object of the hierarchy in which the parent object of property is found, if ICAGetRootOfProperty returns successfully. -->
    @field rootInfo
        Information about 'rootObject', if ICAGetRootOfProperty returns successfully. -->
*/
typedef struct ICAGetRootOfPropertyPB {
    ICAHeader           header;
    ICAProperty         property;
    ICAObject           rootObject;
    ICAObjectInfo       rootInfo;
} ICAGetRootOfPropertyPB                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;

/*!
    @function ICAGetRootOfProperty
    @abstract
        Uset this API to get a property's root object (in the object hierarchy) and its information. This API is deprecated in 10.5.
    @discussion
        Uset this API to get a property's root object (in the object hierarchy) and its information. This API is deprecated in 10.5.
    @param pb
        A pointer to an <code><b>ICAGetRootOfPropertyPB</b></code> parameter block.
    @param completion
        A pointer to a completion routine that will be invoked at the completion of <code><b>ICAGetRootOfProperty</b></code> function. Set this parameter to <code><b>NULL</b></code> to invoke this API synchronously. 
    @result
        Returns an error code defined in ICAApplication.h
*/
extern ICAError 
ICAGetRootOfProperty(
    ICAGetRootOfPropertyPB* pb,
    ICACompletion           completion
)                                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;

//----------------------------------------------------------------------------------------------------------- ICAGetPropertyData
/*!
    @enum Flag for reading property data
    @discussion
        Use one of these values when reading property data using partial reads.
    @constant kICAStartAtBeginning
        Start reading from the beginning.
    @constant kICAEntireLength
        Read all data.
*/
enum
{
    kICAStartAtBeginning                  = 0,
    kICAEntireLength                      = -1						   
};

/*!
    @struct ICAGetPropertyDataPB
    @field header
        See description for ICAHeader. <-->
    @field property
        Property whose data is being fetched. <--
    @field startByte
        Offset into 'dataPtr' from where the fetched data should be written. <--
    @field requestedSize
        Requested size of data in bytes. <--
    @field dataPtr
        A buffer to receive the data. <--
    @field actualSize
        Actual size of data written to dataPtr. -->
    @field dataType
        Type of data fetched. -->
*/
typedef struct ICAGetPropertyDataPB {
    ICAHeader           header;
    ICAProperty         property;
    UInt32              startByte;
    UInt32              requestedSize;
    void *              dataPtr;
    UInt32              actualSize;
    OSType              dataType;
} ICAGetPropertyDataPB                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;

/*!
    @function ICAGetPropertyData
    @abstract
        Use this API to get data associated with a property. This API is deprecated in 10.5. Use one of the ICACopy* APIs instead.
    @discussion
        Use this API to get data associated with a property. This API is deprecated in 10.5. Use one of the ICACopy* APIs instead.
    @param pb
        A pointer to an <code><b>ICAGetPropertyDataPB</b></code> parameter block.
    @param completion
        A pointer to a completion routine that will be invoked at the completion of <code><b>ICAGetPropertyData</b></code> function. Set this parameter to <code><b>NULL</b></code> to invoke this API synchronously. 
    @result
        Returns an error code defined in ICAApplication.h
*/
extern ICAError 
ICAGetPropertyData(
    ICAGetPropertyDataPB* pb,
    ICACompletion         completion
)                                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;

//----------------------------------------------------------------------------------------------------------- ICASetPropertyData
/*!
    @struct ICASetPropertyDataPB
    @field header
        See description for ICAHeader. <-->
    @field property
        Property whose data is being fetched. <--
    @field startByte
        Offset into 'dataPtr' from where the data being sent is found. <--
    @field dataPtr
        A buffer holding data being sent. <--
    @field dataSize
        Size of data sent in dataPtr. <--
    @field dataType
        Type of data sent. <--
*/
typedef struct ICASetPropertyDataPB {
    ICAHeader           header;
    ICAProperty         property;
    UInt32              startByte;
    void *              dataPtr;
    UInt32              dataSize;
    OSType              dataType;
} ICASetPropertyDataPB                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;

/*!
    @function ICASetPropertyData
    @abstract
        Use this API to set data for a property. This API is deprecated in 10.5.
    @discussion
        Use this API to set data for a property. This API is deprecated in 10.5.
    @param pb
        A pointer to an <code><b>ICASetPropertyDataPB</b></code> parameter block.
    @param completion
        A pointer to a completion routine that will be invoked at the completion of <code><b>ICASetPropertyData</b></code> function. Set this parameter to <code><b>NULL</b></code> to invoke this API synchronously. 
    @result
        Returns an error code defined in ICAApplication.h
*/
extern ICAError 
ICASetPropertyData(
    ICASetPropertyDataPB* pb,
    ICACompletion         completion
)                                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;

//--------------------------------------------------------------------------------------------------------- ICAGetPropertyRefCon
/*!
    @struct ICAGetPropertyRefConPB
    @field header
        See description for ICAHeader. <-->
    @field property
        A property whos associated refcon value is being fetched. <--
    @field propertyRefCon
        The refcon value, if ICAGetPropertyRefCon returns successfully. -->
*/
typedef struct ICAGetPropertyRefConPB {
    ICAHeader           header;
    ICAProperty         property;
    UInt32              propertyRefCon;
} ICAGetPropertyRefConPB                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;

/*!
    @function ICAGetPropertyRefCon
    @abstract
        Use this API to get an arbitrary refcon associated with a property. This API is deprecated in 10.5.
    @discussion
        Use this API to get an arbitrary refcon associated with a property. This API is deprecated in 10.5.
    @param pb
        A pointer to an <code><b>ICAGetPropertyRefConPB</b></code> parameter block.
    @param completion
        A pointer to a completion routine that will be invoked at the completion of <code><b>ICAGetPropertyRefCon</b></code> function. Set this parameter to <code><b>NULL</b></code> to invoke this API synchronously. 
    @result
        Returns an error code defined in ICAApplication.h
*/
extern ICAError 
ICAGetPropertyRefCon(
    ICAGetPropertyRefConPB* pb,
    ICACompletion           completion
)                                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;

//--------------------------------------------------------------------------------------------------------- ICASetPropertyRefCon
/*!
    @struct ICASetPropertyRefConPB
    @field header
        See description for ICAHeader. <-->
    @field property
        A property whos associated refcon value is being set. <--
    @field propertyRefCon
        The refcon value. <--
*/
typedef struct ICASetPropertyRefConPB {
    ICAHeader           header;
    ICAProperty         property;
    UInt32              propertyRefCon;
} ICASetPropertyRefConPB                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;

/*!
    @function ICASetPropertyRefCon
    @abstract
        Use this API to set an arbitrary refcon for a property. This API is deprecated in 10.5.
    @discussion
        Use this API to set an arbitrary refcon for a property. This API is deprecated in 10.5.
    @param pb
        A pointer to an <code><b>ICASetPropertyRefConPB</b></code> parameter block.
    @param completion
        A pointer to a completion routine that will be invoked at the completion of <code><b>ICASetPropertyRefCon</b></code> function. Set this parameter to <code><b>NULL</b></code> to invoke this API synchronously. 
    @result
        Returns an error code defined in ICAApplication.h
*/
extern ICAError 
ICASetPropertyRefCon(
    ICASetPropertyRefConPB* pb,
    ICACompletion           completion
)                                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;

//------------------------------------------------------------------------------------------------- ICARegisterEventNotification
/*!
    @struct ICARegisterEventNotificationPB
    @discussion
        Use this parameter block to receive basic notifications.
    @field header
        See description for ICAHeader. <-->
    @field object
        An object about which notifications are requested. <->
    @field notifyType
        Notification type of interest. <->
    @field notifyProc
        A callback function to receive the notifications. <--
*/
typedef struct ICARegisterEventNotificationPB {
    ICAHeader           header;
    ICAObject           object;
    OSType              notifyType;
    ICACompletion       notifyProc;
} ICARegisterEventNotificationPB              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;

/*!
    @function ICARegisterEventNotification
    @abstract
        This API is deprecated in 10.5. Use ICARegisterForEventNotification API instead.
    @discussion
        This API is deprecated in 10.5. Use ICARegisterForEventNotification API instead.
    @param pb
        A pointer to an <code><b>ICARegisterEventNotificationPB</b></code> parameter block.
    @param completion
        A pointer to a completion routine that will be invoked at the completion of <code><b>ICARegisterEventNotification</b></code> function. Set this parameter to <code><b>NULL</b></code> to invoke this API synchronously. 
    @result
        Returns an error code defined in ICAApplication.h
*/
extern ICAError 
ICARegisterEventNotification(
    ICARegisterEventNotificationPB* pb,
    ICACompletion                   completion
)                                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;
 
/*!
    @struct ICAExtendedRegisterEventNotificationPB
    @discussion
        Use this parameter block with the 'extd' field set to kExtendedNotificationPB to receive detailed (extended) notifications. This parameter block is passed back with event notifications to the callback function. 
    @field header
        See description for ICAHeader. <->
    @field object
        An object about which notifications are requested. <->
    @field extd
        Set this to kExtendedNotificationPB. 
    @field notifyProc
        A callback function to receive the notifications. <--
    @field rawEventType
        Type of event that occurred. This could be vendor-specific.
    @field eventType
        Type of ImageCapture supported event that occurred. Refer to "Image Capture event types". <->
    @field eventClass
        Set to one of the following: 'kICAEventClassPTPStandard', 'kICAEventClassPTPStandard or any vendor-specific value. -->
    @field eventDataSize
        This is non-zero if there is additional data associated with this event. Additional event data can be fetched by calling ICAObjectSendMessage with messageType set to 'kICAMessageGetEventData', dataType set to value of eventDataCookie and dataSize set to value of eventDataSize. -->
    @field eventDataCookie
        A token identifying the additional data associated with this event. Additional event data can be fetched by calling ICAObjectSendMessage with messageType set to 'kICAMessageGetEventData', dataType set to value of eventDataCookie and dataSize set to value of eventDataSize. -->
    @field deviceObject
        Device object associated with the event. -->
*/
typedef struct ICAExtendedRegisterEventNotificationPB {
    ICAHeader           header;
    ICAObject           object;
    OSType              extd;
    ICACompletion       notifyProc;
    UInt32              rawEventType;
    OSType              eventType;
    OSType              eventClass;
    UInt32              eventDataSize;
    ICAEventDataCookie  eventDataCookie;
    ICAObject           deviceObject;
} ICAExtendedRegisterEventNotificationPB      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;

//------------------------------------------------------------------------------------------------------------------------------

#pragma pack(pop)

#ifdef __cplusplus
}
#endif

//------------------------------------------------------------------------------------------------------------------------------

#endif /* __ICAAPPLICATION__ */

//------------------------------------------------------------------------------------------------------------------------------
