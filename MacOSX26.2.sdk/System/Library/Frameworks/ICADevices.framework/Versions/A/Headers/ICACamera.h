/*------------------------------------------------------------------------------------------------------------------------------
 *
 *  ImageCapture/ICACamera.h
 *
 *  Copyright (c) 2000-2006 Apple Computer, Inc. All rights reserved.
 *
 *  For bug reports, consult the following page onthe World Wide Web:
 *  http://developer.apple.com/bugreporter/
 *
 *----------------------------------------------------------------------------------------------------------------------------*/

#pragma once

#ifndef __ICACAMERA__
#define __ICACAMERA__

//------------------------------------------------------------------------------------------------------------------------------

#ifndef __AVAILABILITYMACROS__
#include <AvailabilityMacros.h>
#endif

API_UNAVAILABLE_BEGIN(ios)

//------------------------------------------------------------------------------------------------------------------------------
/*!
    @header ICACamera.h
    @discussion
        ICACamera.h defines digital still cameras specific constants used with the Image Capture framework APIs. 
*/

//-------------------------------------------------------------------------------------------------------- Constant Descriptions

/*! 
    @enum Fields in StorageInfo Dataset 
    @discussion
        Refer to section 5.5.3 of the PIMA 15740 (PTP) specification for descriptions and usage notes.
    @constant kICAPropertyCameraStorageType
        Storage type. <BR>Data type: UInt16.
    @constant kICAPropertyCameraFilesystemType
        File system type. <BR>Data type: UInt16.
    @constant kICAPropertyCameraAccessCapability
        Access capability. <BR>Data type: UInt16.
    @constant kICAPropertyCameraMaxCapacity
        Total storage capacity in bytes. <BR>Data type: UInt64.
    @constant kICAPropertyCameraFreeSpaceInBytes
        Free space available on storage in bytes. <BR>Data type: UInt64.
    @constant kICAPropertyCameraFreeSpaceInImages
        Number of images that may still be captured in to this store based on the current image capture settings on the camera. <BR>Data type: UInt32.
    @constant kICAPropertyCameraStorageDescription
        Storage description. <BR>Data type: null terminated string.
    @constant kICAPropertyCameraVolumeLabel
        Volume label. <BR>Data type: null terminated string.
  */
enum {
  kICAPropertyCameraStorageType         = 'stor',
  kICAPropertyCameraFilesystemType      = 'fsys',
  kICAPropertyCameraAccessCapability    = 'acap',
  kICAPropertyCameraMaxCapacity         = 'maxc',
  kICAPropertyCameraFreeSpaceInBytes    = 'fres',
  kICAPropertyCameraFreeSpaceInImages   = 'frei',
  kICAPropertyCameraStorageDescription  = 'stod',
  kICAPropertyCameraVolumeLabel         = 'voll'
};

/*!
    @enum Values for kICAPropertyCameraStorageType 
    @discussion
        Values for kICAPropertyCameraStorageType.
    @constant kICAStorageUndefined
        Undefined.
    @constant kICAStorageFixedROM
        Fixed ROM.
    @constant kICAStorageRemovableROM
        Removable ROM.
    @constant kICAStorageFixedRAM
        Fixed RAM.
    @constant kICAStorageRemovableRAM
        Removable RAM.
  */
enum {
  kICAStorageUndefined          = 0x0000,
  kICAStorageFixedROM           = 0x0001,
  kICAStorageRemovableROM       = 0x0002,
  kICAStorageFixedRAM           = 0x0003,
  kICAStorageRemovableRAM       = 0x0004
};

/*!
    @enum Values for kICAPropertyCameraFilesystemType 
    @discussion
        Values for kICAPropertyCameraFilesystemType.
    @constant kICAFileystemUndefined
        Undefined.
    @constant kICAFileystemGenericFlat
        Generic flat.
    @constant kICAFileystemGenericHierarchical
        Generic hierarchical.
    @constant kICAFileystemDCF
        DCF-conformant.
  */
enum {
  kICAFileystemUndefined            = 0x0000,
  kICAFileystemGenericFlat          = 0x0001,
  kICAFileystemGenericHierarchical  = 0x0002,
  kICAFileystemDCF                  = 0x0003
};

/*! 
    @enum Values for kICAPropertyCameraAccessCapability 
    @discussion
        Values for kICAPropertyCameraAccessCapability.
    @constant kICAAccessReadWrite
        Read-write.
    @constant kICAAccessReadOnly
        Read-only without object deletion.
    @constant kICAAccessReadOnlyWithObjectDeletion
        Read-only with object deletion.
  */
enum {
  kICAAccessReadWrite                   = 0x0000,
  kICAAccessReadOnly                    = 0x0001,
  kICAAccessReadOnlyWithObjectDeletion  = 0x0002
};

/*!
    @enum Standard camera properties
    @discussion
        Refer to section 13 of the PIMA 15740 (PTP) specification for descriptions and usage notes for these standard properties.
    @constant kICAPropertyCameraBatteryLevel
        Battery level. <BR>Property data type: UInt8; Property desc forms: Enum/Range.
    @constant kICAPropertyCameraFunctionalMode
        Functional mode. <BR>Property data type: UInt16; Property desc forms: Enum.
    @constant kICAPropertyCameraImageSize
        Image size. <BR>Property data type: CFString; Property desc forms: Enum/Range.
    @constant kICAPropertyCameraCompressionSetting
        Compression setting. <BR>Property data type: UInt8; Property desc forms: Enum/Range.
    @constant kICAPropertyCameraWhiteBalance
        White balance. <BR>Property data type: UInt16; Property desc forms: Enum.
    @constant kICAPropertyCameraRGBGain
        RGB gain. <BR>Property data type: null terminated string; Property desc forms: Enum/Range.
    @constant kICAPropertyCameraFNumber
        F-number. <BR>Property data type: UInt8; Property desc forms: Enum/Range.
    @constant kICAPropertyCameraFocalLength
        Focal length. <BR>Property data type: UInt32; Property desc forms: Enum/Range.
    @constant kICAPropertyCameraFocusDistance
        Focus distance. <BR>Property data type: UInt16; Property desc forms: Enum.
    @constant kICAPropertyCameraFocusMode
        Focus mode. <BR>Property data type: UInt16; Property desc forms: Enum.
    @constant kICAPropertyCameraExposureMeteringMode
        Exposure Metering mode. <BR>Property data type: UInt16; Property desc forms: Enum.
    @constant kICAPropertyCameraFlashMode
        Flash mode. <BR>Property data type: UInt16; Property desc forms: Enum.
    @constant kICAPropertyCameraExposureTime
        Exposure time. <BR>Property data type: UInt32; Property desc forms: Enum/Range.
    @constant kICAPropertyCameraExposureProgramMode
        Exposure program mode. <BR>Property data type: UInt16; Property desc forms: Enum.
    @constant kICAPropertyCameraExposureIndex
        Exposure index. <BR>Property data type: UInt16; Property desc forms: Enum/Range.
    @constant kICAPropertyCameraExposureBiasCompensation
        Exposure bias compensation. <BR>Property data type: UInt16; Property desc forms: Enum/Range.
    @constant kICAPropertyCameraDateTime
        Date & time. <BR>Property data type: null terminated string; Property desc forms: none.
    @constant kICAPropertyCameraCaptureDelay
        Capture delay. <BR>Property data type: UInt32; Property desc forms: Enum/Range.
    @constant kICAPropertyCameraStillCaptureMode
        Still capture mode. <BR>Property data type: UInt16; Property desc forms: Enum.
    @constant kICAPropertyCameraContrast
        Contrast. <BR>Property data type: UInt8; Property desc forms: Enum/Range.
    @constant kICAPropertyCameraSharpness
        Sharpness. <BR>Property data type: UInt8; Property desc forms: Enum/Range.
    @constant kICAPropertyCameraDigitalZoom
        Digital zoom. <BR>Property data type: UInt8; Property desc forms: Enum/Range.
    @constant kICAPropertyCameraEffectMode
        Effect mode. <BR>Property data type: UInt16; Property desc forms: Enum.
    @constant kICAPropertyCameraBurstNumber
        Burst number. <BR>Property data type: UInt16; Property desc forms: Enum/Range.
    @constant kICAPropertyCameraBurstInterval
        Burst interval. <BR>Property data type: UInt16; Property desc forms: Enum/Range.
    @constant kICAPropertyCameraTimelapseNumber
        Timelapse number. <BR>Property data type: UInt16; Property desc forms: Enum/Range.
    @constant kICAPropertyCameraTimelapseInterval
        Timelapse interval. <BR>Property data type: UInt32; Property desc forms: Enum/Range.
    @constant kICAPropertyCameraFocusMeteringMode
        Focus metering mode. <BR>Property data type: UInt16; Property desc forms: Enum.
    @constant kICAPropertyCameraUploadURL
        Upload URL. <BR>Property data type: null terminated string; Property desc forms: none.
    @constant kICAPropertyCameraArtist
        Artist. <BR>Property data type: null terminated string; Property desc forms: none.
    @constant kICAPropertyCameraCopyrightInfo
        Copyright info. <BR>Property data type: null terminated string; Property desc forms: none.
  */
enum
{
	kICAPropertyCameraBatteryLevel				= '5001',
	kICAPropertyCameraFunctionalMode			= '5002',
	kICAPropertyCameraImageSize					= '5003',
	kICAPropertyCameraCompressionSetting		= '5004',
	kICAPropertyCameraWhiteBalance				= '5005',
	kICAPropertyCameraRGBGain					= '5006',
	kICAPropertyCameraFNumber					= '5007',
	kICAPropertyCameraFocalLength				= '5008',
	kICAPropertyCameraFocusDistance				= '5009',
	kICAPropertyCameraFocusMode					= '500A',
	kICAPropertyCameraExposureMeteringMode		= '500B',
	kICAPropertyCameraFlashMode					= '500C',
	kICAPropertyCameraExposureTime				= '500D',
	kICAPropertyCameraExposureProgramMode		= '500E',
	kICAPropertyCameraExposureIndex				= '500F',
	kICAPropertyCameraExposureBiasCompensation	= '5010',
	kICAPropertyCameraDateTime					= '5011',
	kICAPropertyCameraCaptureDelay				= '5012',
	kICAPropertyCameraStillCaptureMode			= '5013',
	kICAPropertyCameraContrast					= '5014',
	kICAPropertyCameraSharpness					= '5015',
	kICAPropertyCameraDigitalZoom				= '5016',
	kICAPropertyCameraEffectMode				= '5017',
	kICAPropertyCameraBurstNumber				= '5018',
	kICAPropertyCameraBurstInterval				= '5019',
	kICAPropertyCameraTimelapseNumber			= '501A',
	kICAPropertyCameraTimelapseInterval			= '501B',
	kICAPropertyCameraFocusMeteringMode			= '501C',
    kICAPropertyCameraUploadURL                 = '501D',
    kICAPropertyCameraArtist                    = '501E',
    kICAPropertyCameraCopyrightInfo             = '501F'
};

/*!
    @enum ImageCapture framework specific camera properties 
    @discussion
        ImageCapture framework specific camera properties.
    @constant kICAPropertyCameraIcon
        Camera icon in ICAThumbnail format.
    @constant kICAPropertyCameraSupportedMessages
        Messages supported/understood by the camera.
  */
enum
{
	kICAPropertyCameraIcon						= 'icon',
	kICAPropertyCameraSupportedMessages			= 'msgs'
};

/*!
    @enum Camera messages 
    @discussion
        Messages that can be sent to digital still cameras.
    @constant kICAMessageCameraCaptureNewImage
        Capture a new image using the camera.
    @constant kICAMessageCameraDeleteOne
        Delete one image stored in the camera.
    @constant kICAMessageCameraDeleteAll
        Delete all images stored in the camera.
    @constant kICAMessageCameraSyncClock
        Synchronize camera's clock with the computer's clock.
    @constant kICAMessageCameraUploadData
        Upload data to the camera.
  */
enum
{
	kICAMessageCameraCaptureNewImage			= 'ccni',
    kICAMessageCameraDeleteOne          		= 'del1',
    kICAMessageCameraDeleteAll   				= 'dela',
    kICAMessageCameraSyncClock   				= 'sclk',
    kICAMessageCameraUploadData   				= 'load',
};

/*!
    @enum Camera capabilities 
    @discussion
        Capabilities of digital still cameras.
    @constant kICAMessageCameraCaptureNewImage
        Can capture a new image using the camera.
    @constant kICAMessageCameraDeleteOne
        Can delete one image stored in the camera.
    @constant kICAMessageCameraDeleteAll
        Can delete all images stored in the camera.
    @constant kICAMessageCameraSyncClock
        Can synchronize camera's clock with the computer's clock.
    @constant kICAMessageCameraUploadData
        Can upload data to the camera.
  */
enum
{
	kICACapabilityCanCameraCaptureNewImage      = 'ccni',
    kICACapabilityCanCameraDeleteOne            = 'del1',
    kICACapabilityCanCameraDeleteAll            = 'dela',
    kICACapabilityCanCameraSyncClock            = 'sclk',
    kICACapabilityCanCameraUploadData           = 'load',
    kICACapabilityMayStoreNewImagesInTempStore  = 'temp',
    kICACapabilityMessageCameraSupportsApplePTP = 'aptp'
};

//------------------------------------------------------------------------------------------------------------------------------

#endif /* __ICACAMERA__ */

API_UNAVAILABLE_END
