//
//  IOUSBHostStream.h
//  IOUSBHostFamily
//
//  Created by Dan Wilson on 2/13/14.
//
//

#ifndef IOUSBHostFamily_IOUSBHostStream_h
#define IOUSBHostFamily_IOUSBHostStream_h

#include <IOKit/usb/IOUSBHostFamily.h>
#include <IOKit/usb/IOUSBHostIOSource.h>

class IOUSBHostPipe;

class IOUSBHostStream : public IOUSBHostIOSource
{
    OSDeclareDefaultStructors(IOUSBHostStream)

    friend class IOUSBHostPipe;

public:
    IOUSBHostStream* withOwnersAndStreamID(AppleUSBHostController* controller, IOUSBHostDevice* device, IOUSBHostPipe* pipe, uint32_t streamID);

    virtual void free();
    
    /*!
     * @brief Abort pending I/O requests
     *
     * @discussion See IOUSBHostIOSource::abort for documentation
     * 
     * A stream context must be set as non-active on the device via an out-of-band (class-defined) mechanism before this method is called.
     * A non-active stream will not be selected by the device to become the current stream on the endpoint.
     */
    virtual IOReturn abort(IOOptionBits options = kAbortAsynchronous, IOReturn withError = kIOReturnAborted, IOService* forClient = NULL);

    virtual IOUSBHostPipe* getPipe() const { return _pipe; }

    virtual uint32_t getStreamID() const { return _streamID; }
    
    /*!
     * @brief Issue an asynchronous I/O request
     *
     * @discussion See IOUSBHostIOSource::io for documentation
     *
     * @param completionTimeoutMs Must be 0 for streams
     */
    virtual IOReturn io(IOMemoryDescriptor* dataBuffer, uint32_t dataBufferLength, IOUSBHostCompletion* completion, uint32_t completionTimeoutMs = 0);
    
    /*!
     * @brief Issue a synchronous I/O request
     *
     * @discussion See IOUSBHostIOSource::io for documentation
     *
     * @param completionTimeoutMs Must be 0 for streams
     */
    virtual IOReturn io(IOMemoryDescriptor* dataBuffer, uint32_t dataBufferLength, uint32_t& bytesTransferred, uint32_t completionTimeoutMs = 0);

    // Public pad slots for future expansion
    OSMetaClassDeclareReservedUnused(IOUSBHostStream, 0);
    OSMetaClassDeclareReservedUnused(IOUSBHostStream, 1);
    OSMetaClassDeclareReservedUnused(IOUSBHostStream, 2);
    OSMetaClassDeclareReservedUnused(IOUSBHostStream, 3);
    OSMetaClassDeclareReservedUnused(IOUSBHostStream, 4);
    OSMetaClassDeclareReservedUnused(IOUSBHostStream, 5);
    OSMetaClassDeclareReservedUnused(IOUSBHostStream, 6);
    OSMetaClassDeclareReservedUnused(IOUSBHostStream, 7);
    OSMetaClassDeclareReservedUnused(IOUSBHostStream, 8);
    OSMetaClassDeclareReservedUnused(IOUSBHostStream, 9);

protected:
    virtual bool initWithOwnersAndStreamID(AppleUSBHostController* controller, IOUSBHostDevice* device, IOUSBHostPipe* pipe, uint32_t streamID);

    virtual IOReturn closeGated();

    virtual IOReturn abortGated(IOOptionBits options, IOReturn withError, IOService* forClient);

    // Protected pad slots for future expansion
    OSMetaClassDeclareReservedUnused(IOUSBHostStream, 10);
    OSMetaClassDeclareReservedUnused(IOUSBHostStream, 11);
    OSMetaClassDeclareReservedUnused(IOUSBHostStream, 12);
    OSMetaClassDeclareReservedUnused(IOUSBHostStream, 13);
    OSMetaClassDeclareReservedUnused(IOUSBHostStream, 14);
    OSMetaClassDeclareReservedUnused(IOUSBHostStream, 15);
    OSMetaClassDeclareReservedUnused(IOUSBHostStream, 16);
    OSMetaClassDeclareReservedUnused(IOUSBHostStream, 17);
    OSMetaClassDeclareReservedUnused(IOUSBHostStream, 18);
    OSMetaClassDeclareReservedUnused(IOUSBHostStream, 19);

protected:
    IOUSBHostPipe* _pipe;
    uint32_t       _streamID;
};

#endif
