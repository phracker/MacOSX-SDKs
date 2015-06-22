/*
 * Copyright (c) 1998-2006 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 *
 * The contents of this file constitute Original Code as defined in and
 * are subject to the Apple Public Source License Version 1.2 (the
 * "License").  You may not use this file except in compliance with the
 * License.  Please obtain a copy of the License at
 * http://www.apple.com/publicsource and read it before using this file.
 *
 * This Original Code and all software distributed under the License are
 * distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 *
 * @APPLE_LICENSE_HEADER_END@
 */

/*!
 * @header IOUSBHostPipe.h
 *
 * @brief Provides IOUSBHostPipe API
 */
#ifndef IOUSBHostFamily_IOUSBHostPipe_h
#define IOUSBHostFamily_IOUSBHostPipe_h

#include <IOKit/IOService.h>
#include <IOKit/IOMemoryDescriptor.h>

#include <IOKit/usb/StandardUSB.h>
#include <IOKit/usb/IOUSBHostFamily.h>
#include <IOKit/usb/IOUSBHostIOSource.h>
#include <IOKit/usb/IOUSBHostStream.h>

class IOUSBHostInterface;
class AppleUSBHostController;

/*!
 * @class IOUSBHostPipe
 *
 * @brief IOUSBHostPipe object
 *
 * @discussion Provides the API for controlling pipe policy and performing I/O.
 */
class IOUSBHostPipe : public IOUSBHostIOSource
{
    friend class IOUSBHostInterface;
    friend class IOUSBHostDevice;
    friend class AppleUSBHostController;
    friend class AppleUSBIORequest;

    OSDeclareDefaultStructors(IOUSBHostPipe)

public:
    static IOUSBHostPipe* withDescriptorsAndOwners(const StandardUSB::EndpointDescriptor* descriptor, const StandardUSB::SuperSpeedEndpointCompanionDescriptor* companionDescriptor,
                                                   AppleUSBHostController* controller, IOUSBHostDevice* device, IOUSBHostInterface* interface, UInt8 speed, tUSBHostDeviceAddress address);

protected:
    virtual bool initWithDescriptorsAndOwners(const StandardUSB::EndpointDescriptor* descriptor, const StandardUSB::SuperSpeedEndpointCompanionDescriptor* companionDescriptor,
                                              AppleUSBHostController* controller, IOUSBHostDevice* device, IOUSBHostInterface* interface, UInt8 speed, tUSBHostDeviceAddress address);
    
#pragma mark IOUSBHostIOSource overrides
public:
    virtual void free();
    
    /*!
     * @brief Abort pending I/O requests.
     *
     * @discussion See IOUSBHostIOSource::abort for documentation
     */
    virtual IOReturn abort(IOOptionBits options = kAbortAsynchronous, IOReturn withError = kIOReturnAborted, IOService* forClient = NULL);
    
protected:
    virtual IOReturn closeGated();
    
    virtual IOReturn abortGated(IOOptionBits options, IOReturn withError, IOService* forClient);

    UInt8               _speed;
    IOUSBHostInterface* _interface;

#pragma mark Descriptors and policies
public:
    /*!
     * @methodgroup Descriptors and Policies
     */
    
    /*!
     * @brief Options for <code>getEndpointDescriptor()</code> and <code>getSuperSpeedEndpointCompanionDescriptor()</code>
     *
     * @discussion
     * @constant kGetEndpointDescriptorOriginal - Original descriptor as returned as part of the configuration descriptor.
     * @constant kGetEndpointDescriptorCurrentPolicy - Descriptor controlling the current endpoint policy.  This may differ from
     * kGetEndpointDescriptorOriginal if <code>adjustPipe()</code> has been called.
     */
    enum tGetEndpointDescriptorOptions
    {
        kGetEndpointDescriptorOriginal = 0,
        kGetEndpointDescriptorCurrentPolicy
    };
    
    /*!
     * @brief This method will return an endpoint descriptor associated with the pipe.
     *
     * @param type The desired endpoint descriptor type to return.  See @link //apple_ref/cpp/tag/IOUSBHostPipe/tGetEndpointDescriptorOptions
     * IOUSBHostPipe::tGetEndpointDescriptorOptions @/link for more details.
     *
     * @return If successful a pointer to the endpoint descriptor is returned.  Otherwise, NULL is returned.
     */
    virtual const StandardUSB::EndpointDescriptor* getEndpointDescriptor(tGetEndpointDescriptorOptions type = kGetEndpointDescriptorCurrentPolicy);
    
    /*!
     * @brief This method will return the Super-Speed endpoint companion descriptor associated with the pipe.
     *
     * @param type The desired endpoint descriptor type to return. See @link //apple_ref/cpp/tag/IOUSBHostPipe/tGetEndpointDescriptorOptions
     * IOUSBHostPipe::tGetEndpointDescriptorOptions @/link for more details.
     *
     * @return If successful a pointer to the companion descriptor is returned.  Otherwise, NULL is returned.
     */
    virtual const StandardUSB::SuperSpeedEndpointCompanionDescriptor* getSuperSpeedEndpointCompanionDescriptor(tGetEndpointDescriptorOptions type = kGetEndpointDescriptorCurrentPolicy);
    
    /*!
     * @brief This method is used to change the amount of bandwidth currently allocated to the pipe.
     *
     * @discussion This method is only valid for interrupt and isochronous endpoints.  There is only a finite amount of
     * bandwith available for interrupt and isochronous endpoints on the USB bus TODO
     *
     * @param endpointDescriptor Pointer to an endpoint descriptor describing the bandwidth request
     *
     * @param companionDescriptor Pointer to a companion descriptor describing the bandwidth request
     *
     * @return IOReturn result code
     */
    virtual IOReturn adjustPipe(const StandardUSB::EndpointDescriptor* endpointDescriptor, const StandardUSB::SuperSpeedEndpointCompanionDescriptor* companionDescriptor);
    
    /*!
     * @brief Set the idle policy of the pipe
     *
     * @discussion TODO Detailed discussion about idling.  This method is only valid for interrupt and bulk endpoints.
     *
     * @param idleTimeoutMs The time, in milliseconds, after which if no I/O has completed the IOUSBHostPipe is consider idle.
     *
     * @return IOReturn result code
     */
    virtual IOReturn setIdlePolicy(uint32_t idleTimeoutMs);
    
    /*!
     * @brief Get the idle policy of the pipe
     *
     * @discussion This method is only valid for interrupt and bulk endpoints.
     *
     * @return The current idle timeout in milliseconds
     */
    virtual uint32_t getIdlePolicy();
    
    /*!
     * @brief Clear the halt condition of the pipe.
     *
     * @discussion  This method will abort all pending I/O, clear the halted condition, and reset the data toggle for the pipe.
     * In general, this must be done after a non-control I/O call returns or completes with an error condition.  This method
     * will also clear the transaction translator if this is a 'split' pipe as described in section 11.17.5 of the 
     * USB 2.0 specification.
     *
     * @param withRequest If true the USB device request: CLEAR_FEATURE::ENDPOINT_HALT for this endnpoint request will be
     * issued on the default pipe.  See section 9.4.1 of the USB 2.0 specification for more details.
     *
     * @return IOReturn result code
     */
    virtual IOReturn clearStall(bool withRequest);
    
protected:
    virtual IOReturn adjustPipeGated(const StandardUSB::EndpointDescriptor* endpointDescriptor, const StandardUSB::SuperSpeedEndpointCompanionDescriptor* companionDescriptor);
    
    virtual IOReturn setIdlePolicyGated(uint32_t idleTimeoutMs);
    virtual IOReturn getIdlePolicyGated(uint32_t& result);
    
    virtual IOReturn clearStallGated(bool withRequest);
    
    const StandardUSB::EndpointDescriptor*                    _descriptor;
    const StandardUSB::SuperSpeedEndpointCompanionDescriptor* _companionDescriptor;

    StandardUSB::EndpointDescriptor                    _currentPolicyDescriptor;
    StandardUSB::SuperSpeedEndpointCompanionDescriptor _currentPolicyCompanionDescriptor;

    // Cached values
    UInt32 _maxPacketSize;
    UInt32 _burstSize;

    UInt32 _ioIdleTimeout;

#pragma mark Control requests
public:
    /*!
     * @methodgroup Control Requests
     */
    
    /*!
     * @brief Issue an asynchronous control request on the pipe.
     *
     * @discussion This method will issue an asynchronous control request on the pipe.  A trivial example is provided below:
     *
     * <pre>
     * @textblock
     * uint8_t                    dataBuffer[4];
     * IOReturn                   result;
     * StandardUSB::DeviceRequest request;
     * IOUSBHostCompletion        completion;
     *
     * request.bmRequestType = makeDeviceRequestbmRequestType(kRequestDirectionIn, kRequestTypeClass, kRequestRecipientInterface);
     * request.bRequest      = 0x12;
     * request.wValue        = 0x3456;
     * request.wIndex        = 0x7890;
     * request.wLength       = sizeof(uint32_t);
     *
     * completion.owner     = this;
     * completion.action    = OSMemberFunctionCast(IOUSBHostCompletionAction, this, &MyDriver::controlRequestComplete);
     * completion.parameter = NULL;
     *
     * result = _controlPipe->controlRequest(this, request, &dataBuffer, &completion, 1000);<br>
     *
     * ...
     *
     * void MyDriver::controlRequestComplete(void* parameter, IOReturn status, uint32_t bytesTransferred)
     * {
     *     if(status == kIOReturnSuccess)
     *     {
     *         IOLog("received %u bytes\n", bytesTransferred);
     *     }
     *
     * @/textblock
     * </pre>
     *
     * @param forClient The object issuing the request (generally the <code>this</code> pointer).
     *
     * @param request Reference to a valid StandardUSB::DeviceRequest object.  This will be copied and can therefore be stack-allocated.
     *
     * @param dataBuffer Pointer to the memory to be used for the I/O.
     *
     * @param completion Pointer to a valid, non NULL, IOUSBHostCompletion object.  This will be copied and can therefore be stack-allocated.
     *
     * @param completionTimeoutMs Time-out of the request in milliseconds.  If 0, the request will never time-out.
     *
     * @return IOReturn result code
     */
    virtual IOReturn controlRequest(IOService* forClient, StandardUSB::DeviceRequest& request, void* dataBuffer, IOUSBHostCompletion* completion, uint32_t completionTimeoutMs);
    
    /*!
     * @brief Issue an asynchronous control request on the pipe.
     *
     * @discussion This method will issue an asynchronous control request on the pipe.  This method differs from
     * @link //apple_ref/cpp/instm/IOUSBHostPipe/controlRequest/IOReturn/(IOService*,StandardUSB::DeviceRequest%26,void*,IOUSBHostCompletion*,uint32_t) @/link
     * in that it takes an IOMemoryDescriptor instead of a void * for <code>dataBuffer</code>.
     *
     * @param forClient The object issuing the request (generally the <code>this</code> pointer).
     *
     * @param request Reference to a valid StandardUSB::DeviceRequest object.  This will be copied and can therefore be stack-allocated.
     *
     * @param dataBuffer Pointer to an IOMemoryDescriptor for the memory to be used for the I/O.
     *
     * @param completion Pointer to a valid, non NULL, IOUSBHostCompletion object.  This will be copied and can therefore be stack-allocated.
     *
     * @param completionTimeoutMs Time-out of the request in milliseconds.  If 0, the request will never time-out.
     *
     * @return IOReturn result code
     */
    virtual IOReturn controlRequest(IOService* forClient, StandardUSB::DeviceRequest& request, IOMemoryDescriptor* dataBuffer, IOUSBHostCompletion* completion, uint32_t completionTimeoutMs);
    
    /*!
     * @brief Issue a synchronous control request on the pipe.
     *
     * @discussion This method will issue a synchronous control request on the pipe. A trivial example is provided below:
     *
     * <pre>
     * @textblock
     * uint8_t                    dataBuffer[4];
     * uint32_t                   bytesTransferred;
     * IOReturn                   result;
     * StandardUSB::DeviceRequest request;
     *
     * request.bmRequestType = makeDeviceRequestbmRequestType(kRequestDirectionIn, kRequestTypeClass, kRequestRecipientInterface);
     * request.bRequest      = 0x12;
     * request.wValue        = 0x3456;
     * request.wIndex        = 0x7890;
     * request.wLength       = sizeof(uint32_t);
     *
     * result = _controlPipe->controlRequest(this, request, &dataBuffer, bytesTransferred, 1000);
     * if(result == kIOReturnSuccess)
     * {
     *     IOLog("received %u bytes\n", bytesTransferred);
     * }
     * @/textblock
     * </pre>
     *
     * @param forClient The object issuing the request (generally the <code>this</code> pointer).
     *
     * @param request Reference to a valid StandardUSB::DeviceRequest object.  This will be copied and can therefore be stack-allocated.
     *
     * @param dataBuffer Pointer to the memory to be used for the I/O.
     *
     * @param bytesTransferred Reference which will be updated with the bytes transferred during the request.
     *
     * @param completionTimeoutMs Time-out of the request in milliseconds.  If 0, the request will never time-out.
     *
     * @return IOReturn result code
     */
    virtual IOReturn controlRequest(IOService* forClient, StandardUSB::DeviceRequest& request, void* dataBuffer, uint32_t& bytesTransferred, uint32_t completionTimeoutMs);
    
    /*!
     * @brief Issue a synchronous control request on the pipe.
     *
     * @discussion This method will issue a synchronous control request on the pipe.  This method differs from
     * @link //apple_ref/cpp/instm/IOUSBHostPipe/controlRequest/IOReturn/(IOService*,StandardUSB::DeviceRequest%26,void*,uint32_t%26,uint32_t) @/link
     * in that it takes an IOMemoryDescriptor instead of a void * for <code>dataBuffer</code>.
     *
     * @param forClient The object issuing the request (generally the <code>this</code> pointer).
     *
     * @param request Reference to a valid StandardUSB::DeviceRequest object.  This will be copied and can therefore be stack-allocated.
     *
     * @param dataBuffer Pointer to an IOMemoryDescriptor for the memory to be used for the I/O.
     *
     * @param bytesTransferred Reference which will be updated with the bytes transferred during the request.
     *
     * @param completionTimeoutMs Time-out of the request in milliseconds.  If 0, the request will never time-out.
     *
     * @return IOReturn result code
     */
    virtual IOReturn controlRequest(IOService* forClient, StandardUSB::DeviceRequest& request, IOMemoryDescriptor* dataBuffer, uint32_t& bytesTransferred, uint32_t completionTimeoutMs);

protected:
    struct tInternalControlRequestParameters
    {
        IOService*                  forClient;
        StandardUSB::DeviceRequest* request;
        void*                       rawBuffer;
        IOMemoryDescriptor*         descriptorBuffer;
        uint32_t*                   bytesTransferred;
        IOUSBHostCompletion*        completion;
        uint32_t                    completionTimeoutMs;
    };
    virtual IOReturn controlRequestGated(tInternalControlRequestParameters& parameters);

    static void rawBufferControlRequestCompletion(void* target, void* parameter, IOReturn status, uint32_t bytesTransferred);

#pragma mark IO
public:
    /*!
     * @methodgroup I/O
     *
     * @discussion All I/O calls will synchronize with the workloop.  Furthermore, all completion callbacks will also
     * synchronize with the workloop.  Therefore, when using the asynchronous I/O methods it is most performant to make
     * subsequent calls from completion callback as the workloop lock will already be owned.
     */
    
    /*!
     * @brief Issue an asynchronous I/O request
     *
     * @discussion See IOUSBHostIOSource::io for documentation

     * @param completionTimeoutMs Must be 0 for interrupt endpoints.
     */
    virtual IOReturn io(IOMemoryDescriptor* dataBuffer, uint32_t dataBufferLength, IOUSBHostCompletion* completion, uint32_t completionTimeoutMs = 0);
    
    /*!
     * @brief Issue a synchronous I/O request
     *
     * @discussion See IOUSBHostIOSource::io for documentation
     *
     * @param completionTimeoutMs Must be 0 for interrupt endpoints.
     */
    virtual IOReturn io(IOMemoryDescriptor* dataBuffer, uint32_t dataBufferLength, uint32_t& bytesTransferred, uint32_t completionTimeoutMs = 0);
    
    /*!
     * @brief Issue an I/O request to an isochronous pipe.
     *
     * @discussion This method is used to issue isochronout I/O requests.  To ensure minimal latency the
     * IOUSBHostIsochronousFrame::status and IOUSBHostIsochronousFrame::completeCount fields of <code>frameList</code> are
     * updated at interrupt time.  In the case of an asynchronous call, this allows software to peek at the frame list and
     * detect completed frames prior to receiving the completion callback.
     *
     * @param dataBuffer Pointer to a valid memory descriptor to be used as the backing store for the I/O.
     *
     * @param frameList Pointer to the frame list describing the request.  See <link>IOUSBHostIsochronousFrame</link> for
     * information regarding structure initialization requirements and usage.
     *
     * @param frameListCount Number of elements in <code>frameList</code>.
     *
     * @param firstFrameNumber Frame number which this request should begin on.  The current frame number can be queried via
     * <code>IOUSHostDevice::getFrameNumber()</code> or <code>IOUSBHostInterface::getFrameNumber()</code> .  If 0, the request
     * will be enqueued on the next available frame.
     *
     * @param completion To create a synchronous I/O request, this parameter must be NULL.  For an asynchronous request this
     * paramater must be properly filled out prior to calling this method.  If not NULL, this parameter will be copied and
     * can therefore be stack-allocated.
     *
     * @return IOReturn result code
     */
    virtual IOReturn io(IOMemoryDescriptor* dataBuffer, IOUSBHostIsochronousFrame* frameList, uint32_t frameListCount, uint64_t firstFrameNumber = 0, IOUSBHostIsochronousCompletion* completion = NULL);
    
protected:
    virtual IOReturn isochronousIoGated(tInternalDataTransferParameters& parameters);
    
#pragma mark Streams
public:
    /*!
     * @methodgroup Streams
     */
    
    /*!
     * @brief Enable streams for the IOUSBHostPipe
     * 
     * @discussion This method changes the operational mode of the IOUSBHostPipe to allow streaming endpoint
     * transfers, and must be called before copyStream will return any IOUSBHostStream objects.
     *
     * @return IOReturn result code.  An error will be returned if the pipe, device, or underlying host
     * controller does not support streams.
     */
    virtual IOReturn enableStreams();
    
    /*!
     * @brief Disable streams for the IOUSBHostPipe
     *
     * @discussion This method changes the operational mode of the IOUSBHostPipe to disable streaming endpoint
     * transfers.  Calling this method will synchronously abort any outstanding calls on existing IOUSBHostStream
     * objects, and therefore all stream contexts should first be set as non-active on the device via an out-of-band
     * (class-defined) mechanism.
     *
     * @return IOReturn result code.  An error will be returned if streams were not enabled for this IOUSBHostPipe.
     */
    virtual IOReturn disableStreams();
    
    /*!
     * @brief Return the stream associated with <code>streamID</code>
     *
     * @discussion This method will return the stream associated with <code>streamID</code>.  If the stream
     * doesn't exist yet it will be created.  This method returns a <code>retain()</code>ed object that must
     * be <code>release()</code>ed by the caller.  <code>IOUSBHostPipe::enableStreams</code> must be called before
     * this method will return a stream object.
     *
     * @param streamID Stream ID in the range of 1 to <code>max</code>, where <code>max</code> can be retrieved
     * by calling <code>StandardUSB::getEndpointMaxStreams</code> with the endpoint descriptors.
     *
     * @return Pointer to a retain()ed IOUSBHostStream object or NULL.  NULL may be returned if either the device
     * or the underlying host controller do not support that stream ID.
     */
    virtual IOUSBHostStream* copyStream(uint32_t streamID);
    
protected:
    virtual IOReturn enableStreamsGated();
    
    virtual IOReturn disableStreamsGated();
    
    virtual IOReturn copyStreamGated(uint32_t streamID, IOUSBHostStream*& result);

    IOUSBHostStream** _streamArray;
    bool              _streamsEnabled;
    
#pragma mark Miscellaneous
public:
    virtual uint8_t getSpeed() const;
    
    virtual tUSBHostDeviceAddress getDeviceAddress() const;
    
protected:
    struct tRawBufferControlRequestCompletionParameter
    {
        IOMemoryDescriptor* memoryDescriptor;
        IOUSBHostCompletion clientCompletion;
    };

#pragma mark Deprecated
public:
    enum tPipeAbortOptions
    {
        kIOUSBPipeAbortAsync = 0,
        kIOUSBPipeAbortSync  = 1
    };

    enum tUSBPipeState
    {
        kUSBPipeStateReady,
        kUSBPipeStateRunningCompletions,
        kUSBPipeStateAborting,
        kUSBPipeStateInactive
    };

    /*!
     * @brief This method is deprecated. Please use copyStream instead.
     * Return the stream associated with <code>streamID</code>
     *
     * @discussion This method will return the stream associated with <code>streamID</code>.  If the stream
     * doesn't exist yet it will be created.  This method returns a <code>retain()</code>ed object that must
     * be <code>release()</code>ed by the caller.  <code>IOUSBHostPipe::enableStreams</code> must be called before
     * this method will return a stream object.
     *
     * @param streamID Stream ID in the range of 1 to <code>max</code>, where <code>max</code> can be retrieved
     * by calling <code>StandardUSB::getEndpointMaxStreams</code> with the endpoint descriptors.
     *
     * @return Pointer to a retain()ed IOUSBHostStream object or NULL.  NULL may be returned if either the device
     * or the underlying host controller do not support that stream ID.
     */
    virtual IOUSBHostStream* getStream(uint32_t streamID) __attribute__((deprecated));
    
    // IOUSBHostPipe::tUSBPipeState GetPipeState() __attribute__((deprecated));
    // Replacement: getState

    // virtual IOReturn Abort(IOOptionBits options = kIOUSBPipeAbortAsync, IOReturn withError = kIOReturnAborted) __attribute__((deprecated));
    // Replacement: abort

    // virtual IOReturn Reset(void) __attribute__((deprecated));
    // virtual IOReturn ClearStall(void) __attribute__((deprecated));
    // Replacement: clearStall(false)

    // virtual IOReturn ClearPipeStall(bool withDeviceRequest = false) __attribute__((deprecated));
    // Replacement: clearStall

    // virtual IOReturn Read(IOMemoryDescriptor* buffer,
    //                       IOUSBCompletion*    completion = 0,
    //                       UInt32*             bytesRead = 0) __attribute__((deprecated));
    // virtual IOReturn Read(IOMemoryDescriptor* buffer,
    //                       UInt64 frameStart, UInt32 numFrames, IOUSBIsocFrame* frameList,
    //                       IOUSBIsocCompletion* completion = 0) __attribute__((deprecated));
    // virtual IOReturn Read(IOMemoryDescriptor* buffer,
    //                       UInt32              noDataTimeout,
    //                       UInt32              completionTimeout,
    //                       IOUSBCompletion*    completion = 0,
    //                       UInt32*             bytesRead = 0) __attribute__((deprecated));
    // virtual IOReturn Read(IOMemoryDescriptor* buffer,
    //                       UInt64 frameStart, UInt32 numFrames, IOUSBLowLatencyIsocFrame* frameList,
    //                       IOUSBLowLatencyIsocCompletion*       completion = 0, UInt32 updateFrequency = 0) __attribute__((deprecated));
    // virtual IOReturn Read(IOMemoryDescriptor* buffer,
    //                       UInt32              noDataTimeout,
    //                       UInt32              completionTimeout,
    //                       IOByteCount         reqCount,
    //                       IOUSBCompletion*    completion = 0,
    //                       UInt32*             bytesRead = 0) __attribute__((deprecated));
    // virtual IOReturn Read(IOMemoryDescriptor*           buffer,
    //                       UInt32                        noDataTimeout,
    //                       UInt32                        completionTimeout,
    //                       IOByteCount                   reqCount,
    //                       IOUSBCompletionWithTimeStamp* completion = 0,
    //                       UInt32*                       bytesRead = 0) __attribute__((deprecated));
    // virtual IOReturn Write(IOMemoryDescriptor* buffer,
    //                        IOUSBCompletion*    completion = 0) __attribute__((deprecated));
    // virtual IOReturn Write(IOMemoryDescriptor* buffer,
    //                        UInt64 frameStart, UInt32 numFrames, IOUSBIsocFrame* frameList,
    //                        IOUSBIsocCompletion* completion = 0) __attribute__((deprecated));
    // virtual IOReturn Write(IOMemoryDescriptor* buffer,
    //                        UInt32              noDataTimeout,
    //                        UInt32              completionTimeout,
    //                        IOUSBCompletion*    completion = 0) __attribute__((deprecated));
    // virtual IOReturn Write(IOMemoryDescriptor* buffer,
    //                        UInt32              noDataTimeout,
    //                        UInt32              completionTimeout,
    //                        IOByteCount         reqCount,
    //                        IOUSBCompletion*    completion = 0) __attribute__((deprecated));
    // virtual IOReturn Write(IOMemoryDescriptor* buffer,
    //                        UInt64 frameStart, UInt32 numFrames, IOUSBLowLatencyIsocFrame* frameList,
    //                        IOUSBLowLatencyIsocCompletion* completion = 0, UInt32 updateFrequency = 0) __attribute__((deprecated));
    // Replacement: io

    // virtual IOReturn ControlRequest(IOUSBDevRequestDesc* request, IOUSBCompletion* completion = NULL,
    //                                 UInt32 noDataTimeout = kUSBHostDefaultControlNoDataTimeoutMS, UInt32 completionTimeout = kUSBHostDefaultControlCompletionTimeoutMS) __attribute__((deprecated));
    // virtual IOReturn ControlRequest(IOUSBDevRequest* request, IOUSBCompletion* completion = NULL) __attribute__((deprecated));
    // virtual IOReturn ControlRequest(IOUSBDevRequestDesc* request, UInt32 noDataTimeout, UInt32 completionTimeout, IOUSBCompletion* completion = 0) __attribute__((deprecated));
    // virtual IOReturn ControlRequest(IOUSBDevRequest* request, UInt32 noDataTimeout, UInt32 completionTimeout, IOUSBCompletion* completion = 0) __attribute__((deprecated));
    // Replacement: controlRequest

    // virtual const AppleUSBHostController::Endpoint* GetEndpoint() __attribute__((deprecated));
    // virtual const StandardUSB::EndpointDescriptor* GetEndpointDescriptor(tGetEndpointDescriptorOptions type = kGetEndpointDescriptorOriginal) __attribute__((deprecated));
    // virtual const StandardUSB::SuperSpeedEndpointCompanionDescriptor* GetEndpointCompanionDescriptor(tGetEndpointDescriptorOptions type = kGetEndpointDescriptorOriginal) __attribute__((deprecated));
    // virtual UInt8 GetDirection() __attribute__((deprecated));
    // virtual UInt8 GetType() __attribute__((deprecated));
    // virtual UInt8            GetEndpointNumber() __attribute__((deprecated));
    // virtual UInt16           GetMaxPacketSize() __attribute__((deprecated));
    // virtual UInt16           GetBurstSize() __attribute__((deprecated));
    // virtual UInt8            GetInterval() __attribute__((deprecated));
    // Replacement: getEndpointDescriptor and getEndpointCompanionDescriptor

    // virtual tUSBHostDeviceAddress GetAddress() __attribute__((deprecated));
    // Replacement: getDeviceAddress
    
    // virtual UInt8            GetSpeed() __attribute__((deprecated));
    // Replacement: getSpeed
    
    // virtual IOReturn GetPipeStatus(void) __attribute__((deprecated));
    // Replacement: none

    // virtual IOReturn SetPipePolicy(UInt16 maxPacketSize, UInt8 maxInterval) __attribute__((deprecated));
    // Replacement: adjustPipe

    // virtual void OverrideIdlePolicy(bool override, UInt32 ioIdleTimeout = 0) __attribute__((deprecated));
    // Replacement: setIdlePolicy

    // virtual void GetIdlePolicy(UInt32& ioIdleTimeout) __attribute__((deprecated));
    // Replacement: setIdlePolicy

    // virtual IOReturn Read(UInt32              streamID,
    //                       IOMemoryDescriptor* buffer,
    //                       UInt32              noDataTimeout,
    //                       UInt32              completionTimeout,
    //                       IOByteCount         reqCount,
    //                       IOUSBCompletion*    completion = 0,
    //                       IOByteCount*        bytesRead = 0) __attribute__((deprecated));
    // virtual IOReturn Write(UInt32              streamID,
    //                        IOMemoryDescriptor* buffer,
    //                        UInt32              noDataTimeout,
    //                        UInt32              completionTimeout,
    //                        IOByteCount         reqCount,
    //                        IOUSBCompletion*    completion = 0) __attribute__((deprecated));
    // virtual IOReturn Abort(UInt32 streamID, IOOptionBits options, IOReturn withError) __attribute__((deprecated));
    // virtual UInt32 GetConfiguredStreams(void) __attribute__((deprecated));
    // Replacement: copyStream and IOUSBHostStream interfaces

    // virtual UInt32 SupportsStreams(void) __attribute__((deprecated));
    // Replacement: StandardUSB::getEndpointMaxStreams

    // virtual IOReturn CreateStreams(UInt32 maxStreams) __attribute__((deprecated));
    // Replacement: enableStreams
    
    // virtual const StandardUSB::SuperSpeedEndpointCompanionDescriptor* GetSuperSpeedEndpointCompanionDescriptor(tGetEndpointDescriptorOptions type = kGetEndpointDescriptorOriginal) __attribute__((deprecated));
    // Replacement: getSuperSpeedEndpointCompanionDescriptor

    // virtual UInt8 GetMaxBurst() __attribute__((deprecated));
    // virtual UInt8 GetMult() __attribute__((deprecated));
    // virtual UInt16 GetBytesPerInterval() __attribute__((deprecated));
    // Replacement: StandardUSB::getEndpoint*
};

#endif // IOUSBHostFamily_IOUSBHostPipe_h
