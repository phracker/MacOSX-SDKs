#ifndef _IOKIT_CDB_IOSCSILIB_H_
#define _IOKIT_CDB_IOSCSILIB_H_

#include <sys/cdefs.h>

__BEGIN_DECLS
#include <CoreFoundation/CFPlugIn.h>
#if COREFOUNDATION_CFPLUGINCOM_SEPARATE
#include <CoreFoundation/CFPlugInCOM.h>
#endif

#include <IOKit/IOKitLib.h>
#include <IOKit/cdb/IOCDBLib.h>

#include <IOKit/scsi/scsi-device/SCSICommand.h>
#include <IOKit/scsi/scsi-device/SCSIDevice.h>
#include <IOKit/scsi/scsi-device/SCSIPublic.h>

/*
 * Beginning of real IOSCSILib stuff
 */

#define kIOSCSIDeviceClassName "IOSCSIDevice"

/*
 * kIOSCSIUserClientTypeID conforming plugins must provide the following
 * interfaces.
 *
 * IOKit/IOCFPlugIn.h:     kIOCFPlugInInterfaceID
 * IOKit/scsi/IOCDBLib.h:  kIOCDBDeviceInterfaceID
 * IOKit/scsi/IOCDBLib.h:  kIOCDBCommandInterfaceID
 * IOKit/scsi/IOSCSILib.h: kIOSCSIDeviceInterfaceID
 */

/* B4291228-0F0F-11D4-9126-0050E4C6426F */
#define kIOSCSIUserClientTypeID CFUUIDGetConstantUUIDWithBytes(NULL,	\
    0xB4, 0x29, 0x12, 0x28, 0x0F, 0x0F, 0x11, 0xD4,			\
    0x91, 0x26, 0x00, 0x50, 0xE4, 0xC6, 0x42, 0x6F)

/* 3408E48A-0F44-11D4-B9C4-0050E4C6426F */
#define kIOSCSIFactoryID CFUUIDGetConstantUUIDWithBytes(NULL,		\
    0x34, 0x08, 0xE4, 0x8A, 0x0F, 0x44, 0x11, 0xD4,			\
    0xB9, 0xC4, 0x00, 0x50, 0xE4, 0xC6, 0x42, 0x6F)

/* 7D61EA88-0F13-11D4-A7FF-0050E4C6426F */
#define kIOSCSIDeviceInterfaceID CFUUIDGetConstantUUIDWithBytes(NULL,	\
    0x7D, 0x61, 0xEA, 0x88, 0x0F, 0x13, 0x11, 0xD4,			\
    0xA7, 0xFF, 0x00, 0x50, 0xE4, 0xC6, 0x42, 0x6F)

typedef struct IOSCSIDeviceStruct {
    IUNKNOWN_C_GUTS;

    /* Completion plumbing */
    IOReturn (*createAsyncEventSource)(void *self, CFRunLoopSourceRef *source);
    CFRunLoopSourceRef (*getAsyncEventSource)(void *self);

    IOReturn (*createAsyncPort)(void *self, mach_port_t *port);
    mach_port_t (*getAsyncPort)(void *self);

    /* Basic IOSCSIDevice interface */
    IOReturn (*getInquiryData)(void *self,
                               void *inquiryBuffer,
                               UInt32 inquiryBufSize,
                               UInt32 *inquiryDataSize);

    IOReturn (*open)(void *self);
    IOReturn (*close)(void *self);

    /* Wrapper to return instances of the IOCDBCommand Interface */
    IOCDBCommandInterface ** (*allocCommand) (void *self);

    /* Abort all outstanding commands on this device */
    IOReturn (*abort)(void *self);
    
    /* Reset device (also aborts all outstanding commands) */
    IOReturn (*reset)(void *self);

    /* Queue management commands */
    IOReturn (*holdQueue)(void *self, UInt32 queueType);
    IOReturn (*releaseQueue)(void *self, UInt32 queueType);
    IOReturn (*flushQueue)(void *self, UInt32 queueType, IOReturn rc);
    IOReturn (*notifyIdle)(void *self,
                    void *target, IOCDBCallbackFunction callback, void *refcon);

    /* Target management commands: Command fails if not LUN 0 */
    IOReturn (*setTargetParms)(void *self, SCSITargetParms *targetParms);
    IOReturn (*getTargetParms)(void *self, SCSITargetParms *targetParms);

    /* Lun management commands */
    IOReturn (*setLunParms)(void *self, SCSILunParms *lunParms);
    IOReturn (*getLunParms)(void *self, SCSILunParms *lunParms);
} IOSCSIDeviceInterface;

__END_DECLS

#endif /* !_IOKIT_CDB_IOSCSILIB_H_ */
