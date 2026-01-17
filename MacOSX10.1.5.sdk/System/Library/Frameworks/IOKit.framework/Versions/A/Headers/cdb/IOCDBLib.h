/*! @header IOCDBLib.h
    @discussion This header defines the primary SCSI CDB Device CFPlugIn interfaces for MacOSX.  See also IOCFPlugIn.h for the instantiation APIs and IOKitLib.h for the rendezvous mechansims.  It is assumed that the developer has discovered the device by navigating the registry and then establishes a connection and created an IOCFPlugInInterface using the IOCreatePlugInInterfaceForService API.  Once the  IOCFPlugInInterface has been created all IOCDBLib conforming devices mst provide the IOCDBDeviceInterface and the IOCDBCommandInterface interfaces.  They can be retreived using the standard QueryInterface API, see file:/System/Documentation/Developer/ReleaseNotes/CFBundleAndCFPlugIn.html.  Please see the plugin documentation for reference counting conventions.

*/
#ifndef _IOKIT_CDB_IOCDBLIB_H_
#define _IOKIT_CDB_IOCDBLIB_H_

#include <sys/cdefs.h>

__BEGIN_DECLS
#include <CoreFoundation/CoreFoundation.h>
#if COREFOUNDATION_CFPLUGINCOM_SEPARATE
#include <CoreFoundation/CFPlugInCOM.h>
#endif

#include <IOKit/IOTypes.h>
#include <IOKit/IOReturn.h>

#include <IOKit/cdb/CDBCommand.h>

/* 784E1034-10AA-11D4-B07F-0050E4C6426F */
/*! @defined kIOCDBDeviceInterfaceID
    @discussion Interface ID for the IOCDBDeviceInterface. */
#define kIOCDBDeviceInterfaceID CFUUIDGetConstantUUIDWithBytes(NULL,	\
    0x78, 0x4E, 0x10, 0x34, 0x10, 0xAA, 0x11, 0xD4,			\
     0xB0, 0x7F, 0x00, 0x50, 0xE4, 0xC6, 0x42, 0x6F)

/* 855B8DDC-0F13-11D4-B520-0050E4C6426F */
/*! @defined kIOCDBCommandInterfaceID
    @discussion Interface ID for the IOCDBCommandInterface. */
#define kIOCDBCommandInterfaceID CFUUIDGetConstantUUIDWithBytes(NULL,	\
    0x85, 0x5B, 0x8D, 0xDC, 0x0F, 0x13, 0x11, 0xD4,			\
    0xB5, 0x20, 0x00, 0x50, 0xE4, 0xC6, 0x42, 0x6F)

/*! @typedef IOCDBCallbackFunction
    @discussion Type and arguments of callout C function that is used when a completion routine is called, see IOCDBLib.h:setCallback().
    @param target void * pointer to your data, often a pointer to an object.
    @param result completion result of desired operation
    @param refcon void * pointer to more data.
    @param sender interface instance sending the completion routine.
*/
typedef void (*IOCDBCallbackFunction)
                (void *target, IOReturn result, void *refcon, void *sender);

typedef struct IOCDBCommandStruct {
    IUNKNOWN_C_GUTS;

    // Set the data pointers
    IOReturn (*setPointers)(void *cmd,
                            IOVirtualRange *sgList,
                            int sgEntries,
                            UInt32 transferCount,
                            Boolean isWrite);
    void (*getPointers)(void *cmd,
                        IOVirtualRange **outSGList,
                        int *outSGEntries,
                        UInt32 *outTransferCount,
                        Boolean *outIsWrite);

    /* Set command timeout (mS) */
    IOReturn (*setTimeout)(void *cmd, UInt32 timeoutMS);		
    void (*getTimeout)(void *cmd, UInt32 *outTimeoutMS);

    /* Set async callback routine. No args = 0 indicates synchronous call. */
    IOReturn (*setCallback)(void *cmd,
                            void *target,
                            IOCDBCallbackFunction callback,
                            void *refcon);
    void (*getCallback)(void *cmd,
                        void **outTarget,
                        IOCDBCallbackFunction *outCallback,
                        void **outRefcon);

    /* Set CDB information. (Generic CDB version) */
    IOReturn (*setCDB)(void *cmd, CDBInfo *cdbInfo);
    void (*getCDB)(void *cmd, CDBInfo *cdbInfo);

    /* Helper wrapper for normal case. */
    IOReturn (*setAndExecuteCommand)(void *cmd,
                                 CDBInfo *cdbInfo,
                                 UInt32 transferCount,
                                 IOVirtualRange *sgList,
                                 int sgEntries,
                                 Boolean isWrite,
                                 UInt32 timeoutMS,
                                 void *target,
                                 IOCDBCallbackFunction callback,
                                 void *refcon,
                                 UInt32 *sequenceNumber);

    IOReturn (*execute)(void *cmd, UInt32 *sequenceNumber);

    /* Get unique sequence number assigned to command. */
    UInt32 (*getSequenceNumber)(void *cmd);

    // Abort a running command
    void (*abort)(void *cmd, UInt32 sequenceNumber);

    /*
     * Get CDB results, 
     * pointer should point to memory big enough to contain results.
     */
    IOReturn (*getResults)(void *cmd, void *cdbResults);

    /*
     * Get Sense data, 
     * pointer should point to memory big enough to contain results.
     */
    void (*getSenseData)(void *cmd, void *senseDataP);

} IOCDBCommandInterface;

/*! @struct IOCDBDeviceInterface
    @abstract Basic interface for all 'Command Descriptor Block (CDB)' devices, like SCSI, ATAPI and SBP2.  
    @discussion After rendezvous with a device in the IORegistry you can create an instance of this interface as a proxy to the IOService.  Once you have this interface, or one of its subclasses, you can create an IOCDBCommandInterface (qv) through which you can then issue actual commands.
*/

typedef struct IOCDBDeviceStruct {
    IUNKNOWN_C_GUTS;

/*! @function createAsyncEventSource
    @abstract Create a run loop source for delivery of all asynchronous notifications on this device.
    @discussion The Mac OS X kernel does not spawn a thread to callback to the client.  Instead it deliveres completion notifications on a mach port, see createAsyncPort.  This routine wraps that port with the appropriate routing code so that the completion notifications can be automatically routed through the clients CFRunLoop.
    @param self Pointer to Pointer to an IOCDBDeviceInterface for one IOService.
    @param source Pointer to a CFRunLoopSourceRef to return the newly created run loop event source.
    @result Returns kIOReturnSuccess if successful or a kern_return_t if failed.
*/
    IOReturn (*createAsyncEventSource)(void *self, CFRunLoopSourceRef *source);

/*! @function getAsyncEventSource
    @abstract Return the CFRunLoopSourceRef for this IOService instance.
    @result Returns the run loop source if one has been created, 0 otherwise.
*/
    CFRunLoopSourceRef (*getAsyncEventSource)(void *self);


/*! @function createAsyncPort
    @abstract Create and register a mach_port_t for asynchronous communications.
    @discussion The Mac OS X kernel does not spawn a thread to callback to the client.  Instead it deliveres completion notifications on this mach port.  After receiving a message on this port the client is obliged to call the IOKitLib.h: IODispatchCalloutFromMessage() function for decoding the notification message.
    @param self Pointer to Pointer to an IOCDBDeviceInterface for one IOService.
    @param port Pointer to a mach_port_t to return the newly created port.
    @result Returns kIOReturnSuccess if successful or a kern_return_t if failed.
*/
    IOReturn (*createAsyncPort)(void *self, mach_port_t *port);

/*! @function getAsyncPort
    @abstract Return the mach_port_t port for this IOService instance.
    @result Returns the port if one exists, 0 otherwise.
*/
    mach_port_t (*getAsyncPort)(void *self);

    /* Basic IOCDBDevice interface */
/*! @function getInquiryData
    @abstract Get the cached INQUIRY command results.
    @discussion When a CDB style device is discovered by IOKit an INQUIRY command  is immediately issued on it.  The results of this inquiry is stored for later access and for device matching.  This function returns those previously cached results.  Can be called without a specifically opened IOService.
    @param self Pointer to Pointer to an IOCDBDeviceInterface for one IOService.
    @param inquiryBuffer Pointer to buffer for results.
    @param inquiryBufSize Size of inquiryBuffer.
    @param inquiryDataSize Actual size of returned buffer.
    @result Returns kIOReturnSuccess if successful.
*/
    IOReturn (*getInquiryData)(void *self,
                               void *inquiryBuffer,
                               UInt32 inquiryBufSize,
                               UInt32 *inquiryDataSize);

/*! @function open
    @abstract Open up the IOCDBDevice for exclusive access.
    @discussion Before the client can issue CDB commands upon a CDB based device it must have succeeded in opening the device.  This establishes an exclusive link between the clients task and the actual device.  
    @param self Pointer to Pointer to an IOCDBDeviceInterface for one IOService.
    @result Returns kIOReturnExclusiveAccess if some other task has the device opened already, kIOReturnError if the connection with the kernel can not be established or kIOReturnSuccess if successful.
*/
    IOReturn (*open)(void *self);
    
/*! @function close
    @abstract Close the task's connection to the IOCDBDevice.
    @discussion Release the clients exclusive access to the IOCDBDevice.  Also aborts all outstanding asynchronous commands with kIOReturnAborted result.  Does not return until all task references are cleared, it is always considered safe to release any resources associated with this device after calling close().  However it should be noted that it is cleaner to be certain that no commands are outstanding before closing a device.
    @param self Pointer to Pointer to an IOCDBDeviceInterface for one IOService.
    @result Returns kIOReturnSuccess if successful, some other mach error if the connection is no longer valid.
*/
    IOReturn (*close)(void *self);

/*! @function allocCommand
    @abstract Wrapper to return instances of the IOCDBCommand Interface.
    @discussion Wraps the QueryInterface(kIOCDBCommandInterfaceID, ppv) call.  
    @param self Pointer to Pointer to an IOCDBDeviceInterface for one IOService.
    @result Returns a pointer to a pointer to an IOCDBCommandInterface if successful, 0 otherwise.
*/
    IOCDBCommandInterface ** (*allocCommand) (void *self);

/*! @function abort
    @abstract Aborts all outstanding commands on this device.
    @discussion For each outstanding commend on this device for this client attempt to abort it.  This call returns immediately but the actual abort request could take some time or even be ignored if it has started executing.  See IOCDBCommandInterface::abort.  
    @param self Pointer to Pointer to an IOCDBDeviceInterface for one IOService.
    @result Returns kIOReturnSuccess if successful, some other mach error if the connection is no longer valid.
*/
    IOReturn (*abort)(void *self);

/*! @function reset
    @abstract Reset device (also aborts all outstanding commands).
    @discussion Reset a device, however the actual results of a reset depends on the type of device which is opened.  For instance a SCSI based CDB device would actually issue a reset for all of the lun's on that device.  See the appropriate device documentation for details.
    @param self Pointer to Pointer to an IOCDBDeviceInterface for one IOService.
    @result Returns kIOReturnSuccess if successful, some other mach error if the connection is no longer valid.
*/
    IOReturn (*reset)(void *self);
} IOCDBDeviceInterface;

__END_DECLS

#endif /* !_IOKIT_CDB_IOCDBLIB_H_ */
