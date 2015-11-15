/*
 * Copyright (c) 2009 Apple Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */
/*
     File:       DVComponentGlue/IsochronousDataHandler.h
 
     Contains:   Component Manager based Isochronous Data Handler
 
     Copyright:  © 1997-2006 by Apple Computer, Inc., all rights reserved.
*/

#ifndef __ISOCHRONOUSDATAHANDLER__
#define __ISOCHRONOUSDATAHANDLER__

#ifndef __CORESERVICES__
#include <CoreServices/CoreServices.h>
#endif

#ifndef __MOVIESFORMAT__
#include <QuickTime/MoviesFormat.h>
#endif

#ifndef __QUICKTIMECOMPONENTS__
#include <QuickTime/QuickTimeComponents.h>
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

enum {
  kIDHComponentType             = 'ihlr', /* Component type*/
  kIDHSubtypeDV                 = 'dv  ', /* Subtype for DV (over FireWire)*/
  kIDHSubtypeFireWireConference = 'fwc ' /* Subtype for FW Conference*/
};


/* Version of Isochronous Data Handler API*/
enum {
  kIDHInterfaceVersion1         = 0x0001 /* Initial relase (Summer '99)*/
};


/* atom types*/

enum {
  kIDHDeviceListAtomType        = 'dlst',
  kIDHDeviceAtomType            = 'devc', /* to be defined elsewhere*/
  kIDHIsochServiceAtomType      = 'isoc',
  kIDHIsochModeAtomType         = 'mode',
  kIDHDeviceIDType              = 'dvid',
  kIDHDefaultIOType             = 'dfio',
  kIDHIsochVersionAtomType      = 'iver',
  kIDHUniqueIDType              = 'unid',
  kIDHNameAtomType              = 'name',
  kIDHUseCMPAtomType            = 'ucmp',
  kIDHIsochMediaType            = 'av  ',
  kIDHDataTypeAtomType          = 'dtyp',
  kIDHDataSizeAtomType          = 'dsiz', /* ??? packet size vs. buffer size*/
  kIDHDataBufferSizeAtomType    = 'dbuf', /* ??? packet size vs. buffer size*/
  kIDHDataIntervalAtomType      = 'intv',
  kIDHDataIODirectionAtomType   = 'ddir',
  kIDHSoundMediaAtomType        = 'soun',
  kIDHSoundTypeAtomType         = 'type',
  kIDHSoundChannelCountAtomType = 'ccnt',
  kIDHSoundSampleSizeAtomType   = 'ssiz',
  kIDHSoundSampleRateAtomType   = 'srat', /* same as video out... (what does this comment mean?)*/
  kIDHVideoMediaAtomType        = 'vide',
  kIDHVideoDimensionsAtomType   = 'dimn',
  kIDHVideoResolutionAtomType   = 'resl',
  kIDHVideoRefreshRateAtomType  = 'refr',
  kIDHVideoPixelTypeAtomType    = 'pixl',
  kIDHVideoDecompressorAtomType = 'deco',
  kIDHVideoDecompressorTypeAtomType = 'dety',
  kIDHVideoDecompressorContinuousAtomType = 'cont',
  kIDHVideoDecompressorComponentAtomType = 'cmpt'
};

/* I/O Flags */
enum {
  kIDHDataTypeIsInput           = 1L << 0,
  kIDHDataTypeIsOutput          = 1L << 1,
  kIDHDataTypeIsInputAndOutput  = 1L << 2
};


/* Permission Flags */
enum {
  kIDHOpenForReadTransactions   = 1L << 0,
  kIDHOpenForWriteTransactions  = 1L << 1,
  kIDHOpenWithExclusiveAccess   = 1L << 2,
  kIDHOpenWithHeldBuffers       = 1L << 3, /* IDH will hold buffer until ReleaseBuffer()*/
  kIDHCloseForReadTransactions  = 1L << 4,
  kIDHCloseForWriteTransactions = 1L << 5
};


/*
   Errors 
    These REALLY need to be moved into Errors.h
   ¥¥¥Êneeds officially assigned numbers
*/
enum {
  kIDHErrDeviceDisconnected     = -14101,
  kIDHErrInvalidDeviceID        = -14102,
  kIDHErrDeviceInUse            = -14104,
  kIDHErrDeviceNotOpened        = -14105,
  kIDHErrDeviceBusy             = -14106,
  kIDHErrDeviceReadError        = -14107,
  kIDHErrDeviceWriteError       = -14108,
  kIDHErrDeviceNotConfigured    = -14109,
  kIDHErrDeviceList             = -14110,
  kIDHErrCompletionPending      = -14111,
  kIDHErrDeviceTimeout          = -14112,
  kIDHErrInvalidIndex           = -14113,
  kIDHErrDeviceCantRead         = -14114,
  kIDHErrDeviceCantWrite        = -14115,
  kIDHErrCallNotSupported       = -14116
};




/* Holds Device Identification...*/
typedef UInt32                          IDHDeviceID;
enum {
  kIDHInvalidDeviceID           = 0,
  kIDHDeviceIDEveryDevice       = (long)0xFFFFFFFF
};

/* Values for 5 bit STYPE part of CIP header*/
enum {
  kIDHDV_SD                     = 0,
  kIDHDV_SDL                    = 1,
  kIDHDV_HD                     = 2,
  kIDHDVCPro_25                 = 0x1E,
  kIDHDVCPro_50                 = 0x1D
};

/*  Isoch Interval Atom Data*/
struct IDHIsochInterval {
  SInt32              duration;
  TimeScale           scale;
};
typedef struct IDHIsochInterval         IDHIsochInterval;
/* Need to fix this.  For now, cast this as a FWReferenceID*/
typedef struct OpaquePsuedoID*          PsuedoID;
/*
   Isoch Device Status
    This is atom-like, but isnÕt an atom
*/
struct IDHDeviceStatus {
  UInt32              version;
  Boolean             physicallyConnected;
  Boolean             readEnabled;
  Boolean             writeEnabled;
  Boolean             exclusiveAccess;
  UInt32              currentBandwidth;
  UInt32              currentChannel;
  PsuedoID            localNodeID;            /*¥¥¥Êmay go in atoms */
  SInt16              inputStandard;          /* One of the QT input standards*/
  Boolean             deviceActive;
  UInt8               inputFormat;            /* Expected STYPE of data from device*/
  UInt32              outputFormats;          /* Bitmask for supported STYPE values, if version > 0x200*/
};
typedef struct IDHDeviceStatus          IDHDeviceStatus;
/*
   Isochronous Data Handler Events
    
*/
typedef UInt32 IDHEvent;
enum {
  kIDHEventInvalid              = 0,
  kIDHEventDeviceAdded          = 1L << 0, /* A new device has been added to the bus*/
  kIDHEventDeviceRemoved        = 1L << 1, /* A device has been removed from the bus*/
  kIDHEventDeviceChanged        = 1L << 2, /* Some device has changed state on the bus*/
  kIDHEventReadEnabled          = 1L << 3, /* A client has enabled a device for read*/
  kIDHEventFrameDropped         = 1L << 4, /* software failed to keep up with isoc data flow*/
  kIDHEventReadDisabled         = 1L << 5, /* A client has disabled a device from read*/
  kIDHEventWriteEnabled         = 1L << 6, /* A client has enabled a device for write*/
  kIDHEventReserved2            = 1L << 7, /* Reserved for future use*/
  kIDHEventWriteDisabled        = 1L << 8, /* A client has disabled a device for write*/
  kIDHEventEveryEvent           = (unsigned long)0xFFFFFFFF
};


typedef UInt32                          IDHNotificationID;
struct IDHEventHeader {
  IDHDeviceID         deviceID;               /* Device which generated event*/
  IDHNotificationID   notificationID;
  IDHEvent            event;                  /* What the event is*/
};
typedef struct IDHEventHeader           IDHEventHeader;



/*
   IDHGenericEvent
    An IDH will often have to post events from at interrupt time.  Since memory
    allocation cannot occur from the interrupt handler, the IDH can preallocate
    storage needed for handling the event by creating some IDHGenericEvent items.
    Subsequently, when an event is generated, the type of event (specified in the
    IDHEventHeader) will dictate how the IDHGenericEvent should be interpretted.
    
    IMPORTANT NOTE : This means that a specific event structure can NEVER be greater
    than the size of the generic one.
    
*/
struct IDHGenericEvent {
  IDHEventHeader      eventHeader;
  UInt32              pad[4];
};
typedef struct IDHGenericEvent          IDHGenericEvent;
/*
   IDHDeviceConnectionEvent
    For kIDHEventDeviceAdded or kIDHEventDeviceRemoved events.
*/
struct IDHDeviceConnectionEvent {
  IDHEventHeader      eventHeader;
};
typedef struct IDHDeviceConnectionEvent IDHDeviceConnectionEvent;
/*
   IDHDeviceIOEnableEvent
    For kIDHEventReadEnabled, kIDHEventReadDisabled, kIDHEventWriteEnabled, or
    kIDHEventWriteDisabled.
*/
struct IDHDeviceIOEnableEvent {
  IDHEventHeader      eventHeader;
};
typedef struct IDHDeviceIOEnableEvent   IDHDeviceIOEnableEvent;
/*
   IDHDeviceFrameDroppedEvent
    For kIDHEventFrameDropped
*/
struct IDHDeviceFrameDroppedEvent {
  IDHEventHeader      eventHeader;
  UInt32              totalDropped;
  UInt32              newlyDropped;
};
typedef struct IDHDeviceFrameDroppedEvent IDHDeviceFrameDroppedEvent;
typedef CALLBACK_API_C( OSStatus , IDHNotificationProcPtr )(IDHGenericEvent *event, void *userData);

typedef IDHNotificationProcPtr          IDHNotificationProc;
typedef STACK_UPP_TYPE(IDHNotificationProcPtr)                  IDHNotificationUPP;
struct IDHParameterBlock {
  UInt32              reserved1;
  UInt16              reserved2;
  void *              buffer;
  ByteCount           requestedCount;
  ByteCount           actualCount;
  IDHNotificationUPP  completionProc;
  void *              refCon;
  OSErr               result;
};
typedef struct IDHParameterBlock        IDHParameterBlock;
struct IDHResolution {
  UInt32              x;
  UInt32              y;
};
typedef struct IDHResolution            IDHResolution;
struct IDHDimension {
  Fixed               x;
  Fixed               y;
};
typedef struct IDHDimension             IDHDimension;

/*
 *  IDHGetDeviceList()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in DVComponentGlue.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   in IDHLib 1.0 and later
 */
extern ComponentResult 
IDHGetDeviceList(
  ComponentInstance   idh,
  QTAtomContainer *   deviceList);


/*
 *  IDHGetDeviceConfiguration()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in DVComponentGlue.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   in IDHLib 1.0 and later
 */
extern ComponentResult 
IDHGetDeviceConfiguration(
  ComponentInstance   idh,
  QTAtomSpec *        configurationID);


/*
 *  IDHSetDeviceConfiguration()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in DVComponentGlue.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   in IDHLib 1.0 and later
 */
extern ComponentResult 
IDHSetDeviceConfiguration(
  ComponentInstance   idh,
  const QTAtomSpec *  configurationID);


/*
 *  IDHGetDeviceStatus()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in DVComponentGlue.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   in IDHLib 1.0 and later
 */
extern ComponentResult 
IDHGetDeviceStatus(
  ComponentInstance   idh,
  const QTAtomSpec *  configurationID,
  IDHDeviceStatus *   status);


/*
 *  IDHGetDeviceClock()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in DVComponentGlue.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   in IDHLib 1.0 and later
 */
extern ComponentResult 
IDHGetDeviceClock(
  ComponentInstance   idh,
  Component *         clock);


/*
 *  IDHOpenDevice()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in DVComponentGlue.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   in IDHLib 1.0 and later
 */
extern ComponentResult 
IDHOpenDevice(
  ComponentInstance   idh,
  UInt32              permissions);


/*
 *  IDHCloseDevice()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in DVComponentGlue.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   in IDHLib 1.0 and later
 */
extern ComponentResult 
IDHCloseDevice(ComponentInstance idh);


/*
 *  IDHRead()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in DVComponentGlue.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   in IDHLib 1.0 and later
 */
extern ComponentResult 
IDHRead(
  ComponentInstance    idh,
  IDHParameterBlock *  pb);


/*
 *  IDHWrite()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in DVComponentGlue.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   in IDHLib 1.0 and later
 */
extern ComponentResult 
IDHWrite(
  ComponentInstance    idh,
  IDHParameterBlock *  pb);


/*
 *  IDHNewNotification()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in DVComponentGlue.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   in IDHLib 1.0 and later
 */
extern ComponentResult 
IDHNewNotification(
  ComponentInstance    idh,
  IDHDeviceID          deviceID,
  IDHNotificationUPP   notificationProc,
  void *               userData,
  IDHNotificationID *  notificationID);


/*
 *  IDHNotifyMeWhen()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in DVComponentGlue.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   in IDHLib 1.0 and later
 */
extern ComponentResult 
IDHNotifyMeWhen(
  ComponentInstance   idh,
  IDHNotificationID   notificationID,
  IDHEvent            events);


/*
 *  IDHCancelNotification()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in DVComponentGlue.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   in IDHLib 1.0 and later
 */
extern ComponentResult 
IDHCancelNotification(
  ComponentInstance   idh,
  IDHNotificationID   notificationID);


/*
 *  IDHDisposeNotification()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in DVComponentGlue.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   in IDHLib 1.0 and later
 */
extern ComponentResult 
IDHDisposeNotification(
  ComponentInstance   idh,
  IDHNotificationID   notificationID);


/*
 *  IDHReleaseBuffer()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in DVComponentGlue.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   in IDHLib 1.0 and later
 */
extern ComponentResult 
IDHReleaseBuffer(
  ComponentInstance    idh,
  IDHParameterBlock *  pb);


/*
 *  IDHCancelPendingIO()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in DVComponentGlue.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   in IDHLib 1.0 and later
 */
extern ComponentResult 
IDHCancelPendingIO(
  ComponentInstance    idh,
  IDHParameterBlock *  pb);


/*
 *  IDHGetDeviceControl()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in DVComponentGlue.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   in IDHLib 1.0 and later
 */
extern ComponentResult 
IDHGetDeviceControl(
  ComponentInstance    idh,
  ComponentInstance *  deviceControl);


/*
 *  IDHUpdateDeviceList()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in DVComponentGlue.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   in IDHLib 1.0 and later
 */
extern ComponentResult 
IDHUpdateDeviceList(
  ComponentInstance   idh,
  QTAtomContainer *   deviceList);


/*
 *  IDHGetDeviceTime()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in DVComponentGlue.framework
 *    CarbonLib:        in CarbonLib 1.4 and later
 *    Non-Carbon CFM:   not available
 */
extern ComponentResult 
IDHGetDeviceTime(
  ComponentInstance   idh,
  TimeRecord *        deviceTime);


/*
 *  IDHSetFormat()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in DVComponentGlue.framework
 *    CarbonLib:        in CarbonLib 1.5 and later
 *    Non-Carbon CFM:   not available
 */
extern ComponentResult 
IDHSetFormat(
  ComponentInstance   idh,
  UInt32              format);


/*
 *  IDHGetFormat()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in DVComponentGlue.framework
 *    CarbonLib:        in CarbonLib 1.5 and later
 *    Non-Carbon CFM:   not available
 */
extern ComponentResult 
IDHGetFormat(
  ComponentInstance   idh,
  UInt32 *            format);



/*
 *  NewIDHNotificationUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in DVComponentGlue.framework
 *    CarbonLib:        in CarbonLib 1.4 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern IDHNotificationUPP
NewIDHNotificationUPP(IDHNotificationProcPtr userRoutine);

/*
 *  DisposeIDHNotificationUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in DVComponentGlue.framework
 *    CarbonLib:        in CarbonLib 1.4 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeIDHNotificationUPP(IDHNotificationUPP userUPP);

/*
 *  InvokeIDHNotificationUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in DVComponentGlue.framework
 *    CarbonLib:        in CarbonLib 1.4 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern OSStatus
InvokeIDHNotificationUPP(
  IDHGenericEvent *   event,
  void *              userData,
  IDHNotificationUPP  userUPP);


/* selectors for component calls */
enum {
    kIDHGetDeviceListSelect                    = 0x0001,
    kIDHGetDeviceConfigurationSelect           = 0x0002,
    kIDHSetDeviceConfigurationSelect           = 0x0003,
    kIDHGetDeviceStatusSelect                  = 0x0004,
    kIDHGetDeviceClockSelect                   = 0x0005,
    kIDHOpenDeviceSelect                       = 0x0006,
    kIDHCloseDeviceSelect                      = 0x0007,
    kIDHReadSelect                             = 0x0008,
    kIDHWriteSelect                            = 0x0009,
    kIDHNewNotificationSelect                  = 0x000A,
    kIDHNotifyMeWhenSelect                     = 0x000B,
    kIDHCancelNotificationSelect               = 0x000C,
    kIDHDisposeNotificationSelect              = 0x000D,
    kIDHReleaseBufferSelect                    = 0x000E,
    kIDHCancelPendingIOSelect                  = 0x000F,
    kIDHGetDeviceControlSelect                 = 0x0010,
    kIDHUpdateDeviceListSelect                 = 0x0011,
    kIDHGetDeviceTimeSelect                    = 0x0012,
    kIDHSetFormatSelect                        = 0x0013,
    kIDHGetFormatSelect                        = 0x0014
};


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

#endif /* __ISOCHRONOUSDATAHANDLER__ */

