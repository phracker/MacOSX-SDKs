//
//  IOUSBHostIOSource.h
//  IOUSBHostFamily
//
//  Created by Dan Wilson on 2/17/14.
//
//

/*!
 * @header IOUSBHostIOSource.h
 *
 * @brief Provides IOUSBHostIOSource API
 */

#ifndef IOUSBHostFamily_IOUSBHostIOSource_h
#define IOUSBHostFamily_IOUSBHostIOSource_h

#include <libkern/c++/OSObject.h>
#include <IOKit/IOCommandGate.h>
#include <IOKit/IOTimerEventSource.h>
#include <IOKit/IOMemoryDescriptor.h>
#include <IOKit/usb/IOUSBHostFamily.h>

class AppleUSBHostController;
class IOUSBHostDevice;
class AppleUSBHostRequestPool;

typedef void (*IOUSBHostCompletionAction)(void* owner, void* parameter, IOReturn status, uint32_t bytesTransferred);
struct IOUSBHostCompletion
{
    void* owner;
    IOUSBHostCompletionAction action;
    void* parameter;
};

/*!
 * @typedef IOUSBHostIsochronousFrame
 * @discussion Structure representing a single frame in an isochronous transfer.
 * @param status Completion status for this individual frame.  IOUSBHostFamily will initialize this to kIOReturnInvalid
 * and will update the field with a valid status code upon completion of the frame.
 * @param requestCount The number of bytes requested to transfer for this frame.  This field must be initialized by the caller
 * before this structure is submitted to IOUSBHostFamily.
 * @param completeCount The number of bytes actually transferred for this frame.  IOUSBHostFamily will update this field
 * upon completion of the frame.
 * @param timeStamp The observed AbsoluteTime for this frame's completion.
 */
struct IOUSBHostIsochronousFrame
{
    IOReturn     status;
    uint32_t     requestCount;
    uint32_t     completeCount;
    AbsoluteTime timeStamp;
};

typedef void (*IOUSBHostIsochronousCompletionAction)(void* owner, void* parameter, IOReturn status, IOUSBHostIsochronousFrame* frameList);
struct IOUSBHostIsochronousCompletion
{
    void* owner;
    IOUSBHostIsochronousCompletionAction action;
    void* parameter;
};

/*!
 * @class IOUSBHostIOSource
 *
 * @brief IOUSBHostIOSource object
 *
 * @discussion Provides the base class API for controlling pipe policy and performing I/O.
 */
class IOUSBHostIOSource : public OSObject
{
    friend class AppleUSBIORequest;
    friend class IOUSBHostInterface;

    OSDeclareAbstractStructors(IOUSBHostIOSource)

protected:
    virtual void free();
    
    virtual bool initWithOwners(AppleUSBHostController* controller, IOUSBHostDevice* device);
    
    // Pad slots for future expansion
    OSMetaClassDeclareReservedUnused(IOUSBHostIOSource, 0);
    OSMetaClassDeclareReservedUnused(IOUSBHostIOSource, 1);
    OSMetaClassDeclareReservedUnused(IOUSBHostIOSource, 2);
    OSMetaClassDeclareReservedUnused(IOUSBHostIOSource, 3);
    OSMetaClassDeclareReservedUnused(IOUSBHostIOSource, 4);
    OSMetaClassDeclareReservedUnused(IOUSBHostIOSource, 5);
    OSMetaClassDeclareReservedUnused(IOUSBHostIOSource, 6);
    OSMetaClassDeclareReservedUnused(IOUSBHostIOSource, 7);
    OSMetaClassDeclareReservedUnused(IOUSBHostIOSource, 8);
    OSMetaClassDeclareReservedUnused(IOUSBHostIOSource, 9);
    
public:
    /*!
     * @brief Return value for <code>getState()</code>
     *
     * @constant kStateReady The I/O source is idle and fully-functional.
     * @constant kStateRunningCompletions The I/O source is currently running completions.
     * @constant kStateAborting The I/O source is currently aborting all requests.
     * @constant kStateInactive The I/O source has been closed.
     */
    enum tState
    {
        kStateReady,
        kStateRunningCompletions,
        kStateAborting,
        kStateInactive
    };

    /*!
     * @brief Returns the current state of the I/O source.
     *
     * @return @link tState @/link
     */
    virtual tState getState();

    /*!
     * @brief Options for <code>abort()</code>
     *
     * @constant kAbortAsynchronous the abort should occur asynchronously.
     * @constant kAbortSynchronous the abort should occur synchronously.
     */
    enum tAbortOptions
    {
        kAbortAsynchronous = 0x0,
        kAbortSynchronous  = 0x1
    };

    /*!
     * @brief Abort pending I/O requests.
     *
     * @discussion This method will abort all pending I/O requests.  If <code>options</code> is  <code>kAbortSynchronous</code>
     * this method will block any new requests that are not submitted from one of the aborted request's callback until the abort
     * completes.
     *
     * @param options Whether the abort operation should be synchronous or not.
     *
     * @param withError Error code which will be passed to any request which hasn't successfully completed.
     *
     * @param forClient Service for which to abort requests.  If NULL, all requests will be aborted.  Only control endpoints can
     * specify a non-NULL value.
     *
     * @return IOReturn result code
     */
    virtual IOReturn abort(IOOptionBits options = kAbortAsynchronous, IOReturn withError = kIOReturnAborted, IOService* forClient = NULL);
    
    // Public pad slots for future expansion
    OSMetaClassDeclareReservedUnused(IOUSBHostIOSource, 10);
    OSMetaClassDeclareReservedUnused(IOUSBHostIOSource, 11);
    OSMetaClassDeclareReservedUnused(IOUSBHostIOSource, 12);
    OSMetaClassDeclareReservedUnused(IOUSBHostIOSource, 13);
    OSMetaClassDeclareReservedUnused(IOUSBHostIOSource, 14);
    OSMetaClassDeclareReservedUnused(IOUSBHostIOSource, 15);
    OSMetaClassDeclareReservedUnused(IOUSBHostIOSource, 16);
    OSMetaClassDeclareReservedUnused(IOUSBHostIOSource, 17);
    OSMetaClassDeclareReservedUnused(IOUSBHostIOSource, 18);
    OSMetaClassDeclareReservedUnused(IOUSBHostIOSource, 19);
    
protected:
    // Protected pad slots for future expansion
    OSMetaClassDeclareReservedUnused(IOUSBHostIOSource, 20);
    OSMetaClassDeclareReservedUnused(IOUSBHostIOSource, 21);
    OSMetaClassDeclareReservedUnused(IOUSBHostIOSource, 22);
    OSMetaClassDeclareReservedUnused(IOUSBHostIOSource, 23);
    OSMetaClassDeclareReservedUnused(IOUSBHostIOSource, 24);
    OSMetaClassDeclareReservedUnused(IOUSBHostIOSource, 25);
    OSMetaClassDeclareReservedUnused(IOUSBHostIOSource, 26);
    OSMetaClassDeclareReservedUnused(IOUSBHostIOSource, 27);
    OSMetaClassDeclareReservedUnused(IOUSBHostIOSource, 28);
    OSMetaClassDeclareReservedUnused(IOUSBHostIOSource, 29);
        
protected:
    struct tSynchronousParameter
    {
        uint32_t bytesTransferred;
        IOReturn status;
    };

    virtual void synchronousCompletion(void* parameter, IOReturn status, uint32_t bytesTransferred);
    virtual void synchronousIsochronousCompletion(void* parameter, IOReturn status, IOUSBHostIsochronousFrame* pFrames);

    virtual IOReturn getStateGated(tState& state);

    virtual IOReturn close();

    virtual IOReturn closeGated();

    virtual IOReturn abortGated(IOOptionBits options, IOReturn withError, IOService* forClient);

    virtual void timerCompletion(IOTimerEventSource* timer);

    AppleUSBHostController* _controller;
    IOUSBHostDevice*        _device;

    IOWorkLoop*              _workloop;
    IOCommandGate*           _commandGate;
    IOTimerEventSource*      _timer;
    AppleUSBHostRequestPool* _requestPool;

    tState                  _state;
    UInt32                  _outstandingIO;
    UInt32                  _completionRunning;
    
#pragma mark IO
public:
    /*!
     * @brief Issue an asynchronous I/O request on the source.
     *
     * @discussion This method is used to issue an asynchronous I/O request on a bulk or interrupt pipe.
     *
     * See IOUSBHostPipe::io and IOUSBHostStream::io for object-specific interface notes.
     *
     * @param dataBuffer Pointer to a valid memory descriptor to use as the backing store for the I/O.
     *
     * @param dataBufferLength Length of the request.  Must be >= <code>dataBuffer->getLength()</code>
     *
     * @param completion Pointer to a valid, non NULL, IOUSBHostCompletion object.  This will be copied and can therefore be stack-allocated.
     *
     * @param completionTimeoutMs Timeout of the request in milliseconds.  If 0, the request will never timeout.
     * Must be 0 for interrupt pipes and streams.
     *
     * @return IOReturn result code
     */
    virtual IOReturn io(IOMemoryDescriptor* dataBuffer, uint32_t dataBufferLength, IOUSBHostCompletion* completion, uint32_t completionTimeoutMs = 0);
    
    /*!
     * @brief Issue a synchronous I/O request on the source.
     *
     * @discussion This method is used to issue a synchronous I/O request on a bulk or interrupt pipe.  Although this
     * is a synchronous call, it is permitted to be called from the completion callback of an asynchronous request.
     *
     * See IOUSBHostPipe::io and IOUSBHostStream::io for object-specific interface notes.
     *
     * @param dataBuffer Pointer to the memory to be used for the I/O.
     *
     * @param dataBufferLength Length of the request.  Must be >= the amount of memory allocated to <code>dataBuffer</code>
     *
     * @param bytesTransferred Reference which will be updated with the bytes transferred during the request.
     *
     * @param completionTimeoutMs Timeout of the request in milliseconds.  If 0, the request will never timeout.
     * Must be 0 for interrupt pipes and streams.
     *
     * @return IOReturn result code
     */
    virtual IOReturn io(IOMemoryDescriptor* dataBuffer, uint32_t dataBufferLength, uint32_t& bytesTransferred, uint32_t completionTimeoutMs = 0);
    
    // Public pad slots for IO
    OSMetaClassDeclareReservedUnused(IOUSBHostIOSource, 30);
    OSMetaClassDeclareReservedUnused(IOUSBHostIOSource, 31);
    OSMetaClassDeclareReservedUnused(IOUSBHostIOSource, 32);
    OSMetaClassDeclareReservedUnused(IOUSBHostIOSource, 33);
    OSMetaClassDeclareReservedUnused(IOUSBHostIOSource, 34);
    OSMetaClassDeclareReservedUnused(IOUSBHostIOSource, 35);
    OSMetaClassDeclareReservedUnused(IOUSBHostIOSource, 36);
    OSMetaClassDeclareReservedUnused(IOUSBHostIOSource, 37);
    OSMetaClassDeclareReservedUnused(IOUSBHostIOSource, 38);
    OSMetaClassDeclareReservedUnused(IOUSBHostIOSource, 39);

protected:
    // Protected pad slots for IO
    OSMetaClassDeclareReservedUnused(IOUSBHostIOSource, 40);
    OSMetaClassDeclareReservedUnused(IOUSBHostIOSource, 41);
    OSMetaClassDeclareReservedUnused(IOUSBHostIOSource, 42);
    OSMetaClassDeclareReservedUnused(IOUSBHostIOSource, 43);
    OSMetaClassDeclareReservedUnused(IOUSBHostIOSource, 44);
    OSMetaClassDeclareReservedUnused(IOUSBHostIOSource, 45);
    OSMetaClassDeclareReservedUnused(IOUSBHostIOSource, 46);
    OSMetaClassDeclareReservedUnused(IOUSBHostIOSource, 47);
    OSMetaClassDeclareReservedUnused(IOUSBHostIOSource, 48);
    OSMetaClassDeclareReservedUnused(IOUSBHostIOSource, 49);
    
protected:
    struct tInternalDataTransferParameters
    {
        IOMemoryDescriptor*             dataBuffer;
        uint32_t                        dataBufferLength;
        uint32_t*                       bytesTransferred;
        IOUSBHostCompletion*            completion;
        uint32_t                        completionTimeoutMs;
        IOUSBHostIsochronousFrame*      frameList;
        uint32_t                        frameListCount;
        uint64_t                        firstFrameNumber;
        IOUSBHostIsochronousCompletion* isochronousCompletion;
    };
    
    virtual IOReturn ioGated(tInternalDataTransferParameters& parameters);
    
    struct tExpansionData
    {
    };
    
    tExpansionData* _expansionData;
    
#pragma mark Debug
    uint32_t                _debugLoggingMask;
};

#endif
