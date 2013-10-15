/*
     File:       ImageCapture/ICACamera.h
 
     Contains:   Digital still camera-specific selectors and structures
 
     Version:    ImageCaptureFramework-328~385
 
     Copyright:  © 2000-2006 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __ICACAMERA__
#define __ICACAMERA__


#include <AvailabilityMacros.h>

#if PRAGMA_ONCE
#pragma once
#endif

/*
   -------------------------------------------------------------------------
                                Selectors           
   -------------------------------------------------------------------------
*/
enum {
                                        /* Camera properties*/
                                        /* Refer to section 13 of the PIMA 15740 (PTP) specification for*/
                                        /* descriptions and usage notes for these standard properties*/
  kICAPropertyCameraBatteryLevel = '5001', /* UInt8   enum/range*/
  kICAPropertyCameraFunctionalMode = '5002', /* UInt16     enum*/
  kICAPropertyCameraImageSize   = '5003', /* CFString     enum/range*/
  kICAPropertyCameraCompressionSetting = '5004', /* UInt8   enum/range*/
  kICAPropertyCameraWhiteBalance = '5005', /* UInt16     enum*/
  kICAPropertyCameraRGBGain     = '5006', /* null terminated string enum/range*/
  kICAPropertyCameraFNumber     = '5007', /* UInt16     enum*/
  kICAPropertyCameraFocalLength = '5008', /* UInt32     enum/range*/
  kICAPropertyCameraFocusDistance = '5009', /* UInt16     enum/range*/
  kICAPropertyCameraFocusMode   = '500A', /* UInt16     enum*/
  kICAPropertyCameraExposureMeteringMode = '500B', /* UInt16     enum*/
  kICAPropertyCameraFlashMode   = '500C', /* UInt16     enum*/
  kICAPropertyCameraExposureTime = '500D', /* UInt32     enum/range*/
  kICAPropertyCameraExposureProgramMode = '500E', /* UInt16     enum*/
  kICAPropertyCameraExposureIndex = '500F', /* UInt16     enum/range*/
  kICAPropertyCameraExposureBiasCompensation = '5010', /* UInt16     enum/range*/
  kICAPropertyCameraDateTime    = '5011', /* null terminated string     none*/
  kICAPropertyCameraCaptureDelay = '5012', /* UInt32     enum/range*/
  kICAPropertyCameraStillCaptureMode = '5013', /* UInt16     enum*/
  kICAPropertyCameraContrast    = '5014', /* UInt8   enum/range*/
  kICAPropertyCameraSharpness   = '5015', /* UInt8   enum/range*/
  kICAPropertyCameraDigitalZoom = '5016', /* UInt8   enum/range*/
  kICAPropertyCameraEffectMode  = '5017', /* UInt16     enum*/
  kICAPropertyCameraBurstNumber = '5018', /* UInt16     enum/range*/
  kICAPropertyCameraBurstInterval = '5019', /* UInt16     enum/range*/
  kICAPropertyCameraTimelapseNumber = '501A', /* UInt16     enum/range*/
  kICAPropertyCameraTimelapseInterval = '501B', /* UInt32     enum/range*/
  kICAPropertyCameraFocusMeteringMode = '501C' /* UInt16     enum*/
};

enum {
                                        /* Refer to section 5.5.3 of the PTP spec*/
  kICAPropertyCameraStorageType = 'stor', /* UInt16*/
  kICAPropertyCameraFilesystemType = 'fsys', /* UInt16*/
  kICAPropertyCameraAccessCapability = 'acap', /* UInt16*/
  kICAPropertyCameraMaxCapacity = 'maxc', /* UInt64*/
  kICAPropertyCameraFreeSpaceInBytes = 'fres', /* UInt64*/
  kICAPropertyCameraFreeSpaceInImages = 'frei', /* UInt32*/
  kICAPropertyCameraStorageDescription = 'stod', /* null terminated string*/
  kICAPropertyCameraVolumeLabel = 'voll' /* null terminated string*/
};

enum {
                                        /* ICA specific*/
  kICAPropertyCameraIcon        = 'icon', /* ICAThumbnail*/
  kICAPropertyCameraSupportedMessages = 'msgs' /* array of OSTypes*/
};

enum {
                                        /* Values for kICAPropertyCameraStorageType*/
  kICAStorageFixedROM           = 0x0001,
  kICAStorageRemovableROM       = 0x0002,
  kICAStorageFixedRAM           = 0x0003,
  kICAStorageRemovableRAM       = 0x0004
};

enum {
                                        /* Values for kICAPropertyCameraFilesystemType*/
  kICAFileystemGenericFlat      = 0x0001,
  kICAFileystemGenericHierarchical = 0x0002,
  kICAFileystemDCF              = 0x0003
};

enum {
                                        /* Values for kICAPropertyCameraAccessCapability*/
  kICAAccessReadWrite           = 0x0000,
  kICAAccessReadOnly            = 0x0001,
  kICAAccessReadOnlyWithObjectDeletion = 0x0002
};

enum {
                                        /* Camera messages*/
  kICAMessageCameraCaptureNewImage = 'ccni',
  kICAMessageCameraDeleteOne    = 'del1',
  kICAMessageCameraDeleteAll    = 'dela',
  kICAMessageCameraSyncClock    = 'sclk',
  kICAMessageCameraUploadData   = 'load'
};



#endif /* __ICACAMERA__ */

