/*
 * Copyright (c) 1998-2007 Apple Inc. All rights reserved.
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

/*!
 * @header IOUSBHostInterface.h
 *
 * @brief Provides IOUSBHostInterface API
 */

#ifndef IOUSBHostFamily_IOUSBHostInterface_h
#define IOUSBHostFamily_IOUSBHostInterface_h

#include <IOKit/IOService.h>
#include <libkern/c++/OSData.h>

#include <IOKit/usb/IOUSBHostFamily.h>
#include <IOKit/usb/IOUSBHostDevice.h>

/*!
 * @class IOUSBHostInterface
 *
 * @abstract The object representing an interface of a device on the USB bus.
 *
 * @discussion This class provides functionality to find the pipes of an interface and to read the descriptors associated
 * with an interface. When an interface is open()ed,  all its pipes are created.
 */
class IOUSBHostInterface : public IOService
{
    OSDeclareDefaultStructors(IOUSBHostInterface)

public:
    static IOUSBHostInterface* withDescriptors(const StandardUSB::ConfigurationDescriptor* configurationDescriptor, const StandardUSB::InterfaceDescriptor* interfaceDescriptor);

protected:
    virtual bool initWithDescriptors(const StandardUSB::ConfigurationDescriptor* configurationDescriptor, const StandardUSB::InterfaceDescriptor* interfaceDescriptor);

    // Pad slots for future expansion
    OSMetaClassDeclareReservedUnused(IOUSBHostInterface, 0);
    OSMetaClassDeclareReservedUnused(IOUSBHostInterface, 1);
    OSMetaClassDeclareReservedUnused(IOUSBHostInterface, 2);
    OSMetaClassDeclareReservedUnused(IOUSBHostInterface, 3);
    OSMetaClassDeclareReservedUnused(IOUSBHostInterface, 4);
    OSMetaClassDeclareReservedUnused(IOUSBHostInterface, 5);
    OSMetaClassDeclareReservedUnused(IOUSBHostInterface, 6);
    OSMetaClassDeclareReservedUnused(IOUSBHostInterface, 7);
    OSMetaClassDeclareReservedUnused(IOUSBHostInterface, 8);
    OSMetaClassDeclareReservedUnused(IOUSBHostInterface, 9);

#pragma mark IOService overrides
public:
    virtual bool        attach(IOService* provider);
    virtual bool        start(IOService* provider);
    virtual bool        terminate(IOOptionBits options = 0);
    virtual void        stop(IOService* provider);
    virtual void        free();

    virtual bool compareProperty(OSDictionary* matching, const char* key);
    virtual bool compareProperty(OSDictionary* matching, const OSString* key);
    virtual bool matchPropertyTable(OSDictionary* table, SInt32* score);

    enum
    {
        kOpenOptionsSelectAlternateInterface = StandardUSBBit(16)
    };
    virtual bool        open(IOService* forClient, IOOptionBits options = 0, void* arg = 0);
    virtual void        close(IOService* forClient, IOOptionBits options = 0);
    
    virtual IOReturn    message(UInt32 type, IOService* provider,  void* argument = 0);

    virtual const char* stringFromReturn(IOReturn rtn);
    
protected:
    virtual IOReturn openGated(IOService* forClient, IOOptionBits options, void* arg);
    virtual IOReturn closeGated(IOService* forClient, IOOptionBits options);
    
    // Pad slots for IOService overrides
    OSMetaClassDeclareReservedUnused(IOUSBHostInterface, 10);
    OSMetaClassDeclareReservedUnused(IOUSBHostInterface, 11);
    OSMetaClassDeclareReservedUnused(IOUSBHostInterface, 12);
    OSMetaClassDeclareReservedUnused(IOUSBHostInterface, 13);
    OSMetaClassDeclareReservedUnused(IOUSBHostInterface, 14);
    OSMetaClassDeclareReservedUnused(IOUSBHostInterface, 15);
    OSMetaClassDeclareReservedUnused(IOUSBHostInterface, 16);
    OSMetaClassDeclareReservedUnused(IOUSBHostInterface, 17);
    OSMetaClassDeclareReservedUnused(IOUSBHostInterface, 18);
    OSMetaClassDeclareReservedUnused(IOUSBHostInterface, 19);
    
protected:
    IOCommandGate* _commandGate;
    IOWorkLoop*    _workLoop;

#pragma mark Power management
public:
    /*!
     * @brief Sets the desired idle policy for the device
     *
     * @discussion TODO talk about device idleness, largest deviceIdleTimeout wins etc
     *
     * @param deviceIdleTimeout The amount of time, in milliseconds, after all pipes are idle to wait before suspending the device.
     *
     * @return IOReturn result code
     */
    virtual IOReturn setIdlePolicy(uint32_t deviceIdleTimeout);
    
    /*!
     * @brief Returns the current device idle timeout.  See @link IOUSBHostInterface::setIdlePolicy @/link
     *
     * @return The amount of time, in milliseconds, after all pipes are idle to wait before suspending the device,
     */
    virtual uint32_t getIdlePolicy();
    
    // Public pad slots for power management
    OSMetaClassDeclareReservedUnused(IOUSBHostInterface, 20);
    OSMetaClassDeclareReservedUnused(IOUSBHostInterface, 21);
    OSMetaClassDeclareReservedUnused(IOUSBHostInterface, 22);
    OSMetaClassDeclareReservedUnused(IOUSBHostInterface, 23);
    OSMetaClassDeclareReservedUnused(IOUSBHostInterface, 24);
    OSMetaClassDeclareReservedUnused(IOUSBHostInterface, 25);
    OSMetaClassDeclareReservedUnused(IOUSBHostInterface, 26);
    OSMetaClassDeclareReservedUnused(IOUSBHostInterface, 27);
    OSMetaClassDeclareReservedUnused(IOUSBHostInterface, 28);
    OSMetaClassDeclareReservedUnused(IOUSBHostInterface, 29);
    
protected:
    // Protected pad slots for power management
    OSMetaClassDeclareReservedUnused(IOUSBHostInterface, 30);
    OSMetaClassDeclareReservedUnused(IOUSBHostInterface, 31);
    OSMetaClassDeclareReservedUnused(IOUSBHostInterface, 32);
    OSMetaClassDeclareReservedUnused(IOUSBHostInterface, 33);
    OSMetaClassDeclareReservedUnused(IOUSBHostInterface, 34);
    OSMetaClassDeclareReservedUnused(IOUSBHostInterface, 35);
    OSMetaClassDeclareReservedUnused(IOUSBHostInterface, 36);
    OSMetaClassDeclareReservedUnused(IOUSBHostInterface, 37);
    OSMetaClassDeclareReservedUnused(IOUSBHostInterface, 38);
    OSMetaClassDeclareReservedUnused(IOUSBHostInterface, 39);

protected:
    uint32_t _deviceIdleTimeout;
    
#pragma mark Descriptors
public:
    /*!
     * @brief Return the configuration descriptor in which this interface is defined
     *
     * @return Pointer to the configuration descriptor
     */
    virtual const StandardUSB::ConfigurationDescriptor* getConfigurationDescriptor();
    
    /*!
     * @brief Return the interface descriptor associated with this interface
     *
     * @return Pointer to the interface descriptor for this interface
     */
    virtual const StandardUSB::InterfaceDescriptor* getInterfaceDescriptor();
    
    /*!
     * @brief Return a string descriptor from the device
     *
     * @discussion This method is simply a convenience method to retieve the desired string descriptor.
     *
     * @param index  Descriptor index value.  Low byte of <code>wValue</code> of the GET_DESCRIPTOR control request described
     * in section 9.4.3 of the USB 2.0 specification.
     *
     * @param languageID  Descriptor language ID.  <code>wIndex</code> of the GET_DESCRIPTOR control request described in
     * section 9.4.3 of the USB 2.0 specification.
     *
     * @return Pointer to the descriptor if found
     */
    virtual const StandardUSB::StringDescriptor* getStringDescriptor(uint8_t index, uint16_t languageID = StandardUSB::kLanguageIDEnglishUS);
    
    // Public pad slots for descriptors
    OSMetaClassDeclareReservedUnused(IOUSBHostInterface, 40);
    OSMetaClassDeclareReservedUnused(IOUSBHostInterface, 41);
    OSMetaClassDeclareReservedUnused(IOUSBHostInterface, 42);
    OSMetaClassDeclareReservedUnused(IOUSBHostInterface, 43);
    OSMetaClassDeclareReservedUnused(IOUSBHostInterface, 44);
    OSMetaClassDeclareReservedUnused(IOUSBHostInterface, 45);
    OSMetaClassDeclareReservedUnused(IOUSBHostInterface, 46);
    OSMetaClassDeclareReservedUnused(IOUSBHostInterface, 47);
    OSMetaClassDeclareReservedUnused(IOUSBHostInterface, 48);
    OSMetaClassDeclareReservedUnused(IOUSBHostInterface, 49);
    
protected:
    virtual IOReturn getInterfaceDescriptorGated(const StandardUSB::InterfaceDescriptor*& result);
    
    // Protected pad slots for descriptors
    OSMetaClassDeclareReservedUnused(IOUSBHostInterface, 50);
    OSMetaClassDeclareReservedUnused(IOUSBHostInterface, 51);
    OSMetaClassDeclareReservedUnused(IOUSBHostInterface, 52);
    OSMetaClassDeclareReservedUnused(IOUSBHostInterface, 53);
    OSMetaClassDeclareReservedUnused(IOUSBHostInterface, 54);
    OSMetaClassDeclareReservedUnused(IOUSBHostInterface, 55);
    OSMetaClassDeclareReservedUnused(IOUSBHostInterface, 56);
    OSMetaClassDeclareReservedUnused(IOUSBHostInterface, 57);
    OSMetaClassDeclareReservedUnused(IOUSBHostInterface, 58);
    OSMetaClassDeclareReservedUnused(IOUSBHostInterface, 59);
    
#pragma mark Alternate setting and pipe management
public:
    /*!
     * @brief Select an alternate setting for this interface
     *
     * @discussion This method is used to select an alternate setting for the interface.  All open pipes will be closed and
     * the new alternate setting will be selected via SET_INTERFACE control request (see section 9.4.10 of the USB 2.0
     * specification).  If the alternate setting was successfully selected, the interface will be re-registered for matching
     *
     * @param bAlternateSetting Alternate interface number to activate
     *
     * @return IOReturn result code
     */
    virtual IOReturn selectAlternateSetting(uint8_t bAlternateSetting);
    
    /*!
     * @brief Return the pipe whose <code>bEndpointAddress</code> matches <code>address</code>
     *
     * @discussion This method will return the pipe whose <code>bEndpointAddress</code> matches <code>address</code>.  If
     * the pipe doesn't exist yet, but is part of the interface, it will first be created.  This method returns a
     * <code>retain()</code>ed object that must be <code>release()</code>ed by the caller.
     *
     * @param address Address of the pipe
     *
     * @return Pointer to a retain()ed IOUSBHostPipe object or NULL
     */
    virtual IOUSBHostPipe* copyPipe(uint8_t address);
    
    /*!
     * @brief Issue an aynchronous setup request on the default control pipe
     *
     * @discussion This method will issue an asynchronous control request on the defaul pipe.
     *
     * <pre>
     * @textblock
     * The following request types are reserved and cannot be made as generic control requests, the appropriate API call should be used instead.
     *
     *    (kRequestDirectionOut, kRequestTypeStandard, kRequestRecipientDevice), kDeviceRequestSetAddress Ñ reserved, this request cannot be sent by drivers.
     *    (kRequestDirectionOut, kRequestTypeStandard, kRequestRecipientDevice), kDeviceRequestSetConfiguration Ñ see setConfiguration().
     *    (kRequestDirectionOut, kRequestTypeStandard, kRequestRecipientInterface), kDeviceRequestSetInterface Ñ see IOUSBHostInterface::selectAlternateSetting().
     *    (kRequestDirectionOut, kRequestTypeStandard, kRequestRecipientEndpoint), kRequestRecipientEndpoint Ñ see IOUSBHostPipe::clearStall().
     *
     * @/textblock
     * </pre>
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
    virtual IOReturn deviceRequest(StandardUSB::DeviceRequest& request, void* dataBuffer, IOUSBHostCompletion* completion, uint32_t completionTimeoutMs = kUSBHostDefaultControlCompletionTimeoutMS);
    
    /*!
     * @brief Issue an aynchronous setup request on the default control pipe
     *
     * @discussion This method will issue an asynchronous control request on the defaul pipe.
     *
     * <pre>
     * @textblock
     * The following request types are reserved and cannot be made as generic control requests, the appropriate API call should be used instead.
     *
     *    (kRequestDirectionOut, kRequestTypeStandard, kRequestRecipientDevice), kDeviceRequestSetAddress Ñ reserved, this request cannot be sent by drivers.
     *    (kRequestDirectionOut, kRequestTypeStandard, kRequestRecipientDevice), kDeviceRequestSetConfiguration Ñ see setConfiguration().
     *    (kRequestDirectionOut, kRequestTypeStandard, kRequestRecipientInterface), kDeviceRequestSetInterface Ñ see IOUSBHostInterface::selectAlternateSetting().
     *    (kRequestDirectionOut, kRequestTypeStandard, kRequestRecipientEndpoint), kRequestRecipientEndpoint Ñ see IOUSBHostPipe::clearStall().
     *
     * @/textblock
     * </pre>
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
    virtual IOReturn deviceRequest(StandardUSB::DeviceRequest& request, IOMemoryDescriptor* dataBuffer, IOUSBHostCompletion* completion, uint32_t completionTimeoutMs = kUSBHostDefaultControlCompletionTimeoutMS);
    
    /*!
     * @brief Issue a synchronous setup request on the default control pipe.
     *
     * <pre>
     * @textblock
     * The following request types are reserved and cannot be made as generic control requests, the appropriate API call should be used instead.
     *
     *    (kRequestDirectionOut, kRequestTypeStandard, kRequestRecipientDevice), kDeviceRequestSetAddress Ñ reserved, this request cannot be sent by drivers.
     *    (kRequestDirectionOut, kRequestTypeStandard, kRequestRecipientDevice), kDeviceRequestSetConfiguration Ñ see setConfiguration().
     *    (kRequestDirectionOut, kRequestTypeStandard, kRequestRecipientInterface), kDeviceRequestSetInterface Ñ see IOUSBHostInterface::selectAlternateSetting().
     *    (kRequestDirectionOut, kRequestTypeStandard, kRequestRecipientEndpoint), kRequestRecipientEndpoint Ñ see IOUSBHostPipe::clearStall().
     *
     * @/textblock
     * </pre>
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
    virtual IOReturn deviceRequest(StandardUSB::DeviceRequest& request, void* dataBuffer, uint32_t& bytesTransferred, uint32_t completionTimeoutMs = kUSBHostDefaultControlCompletionTimeoutMS);
    
    /*!
     * @brief Issue a synchronous setup request on the default control pipe.
     *
     * <pre>
     * @textblock
     * The following request types are reserved and cannot be made as generic control requests, the appropriate API call should be used instead.
     *
     *    (kRequestDirectionOut, kRequestTypeStandard, kRequestRecipientDevice), kDeviceRequestSetAddress Ñ reserved, this request cannot be sent by drivers.
     *    (kRequestDirectionOut, kRequestTypeStandard, kRequestRecipientDevice), kDeviceRequestSetConfiguration Ñ see setConfiguration().
     *    (kRequestDirectionOut, kRequestTypeStandard, kRequestRecipientInterface), kDeviceRequestSetInterface Ñ see IOUSBHostInterface::selectAlternateSetting().
     *    (kRequestDirectionOut, kRequestTypeStandard, kRequestRecipientEndpoint), kRequestRecipientEndpoint Ñ see IOUSBHostPipe::clearStall().
     *
     * @/textblock
     * </pre>
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
    virtual IOReturn deviceRequest(StandardUSB::DeviceRequest& request, IOMemoryDescriptor* dataBuffer, uint32_t& bytesTransferred, uint32_t completionTimeoutMs = kUSBHostDefaultControlCompletionTimeoutMS);
    
    /*!
     * @brief Abort any requests made via the @link deviceRequest @\link methods
     *
     * @discussion This method will abort any requests made via the @link deviceRequest @\link methods.  It will not abort
     * requests made through other interface objects.
     *
     * @param options IOUSBHostIOSource::tAbortOptions
     *
     * @param withError IOReturn error value to return with the requests.
     *
     * @return IOReturn result code
     */
    IOReturn abortDeviceRequests(IOOptionBits options = IOUSBHostIOSource::kAbortAsynchronous, IOReturn withError = kIOReturnAborted);
    
    // Public pad slots for alternate setting and pipe management
    OSMetaClassDeclareReservedUnused(IOUSBHostInterface, 60);
    OSMetaClassDeclareReservedUnused(IOUSBHostInterface, 61);
    OSMetaClassDeclareReservedUnused(IOUSBHostInterface, 62);
    OSMetaClassDeclareReservedUnused(IOUSBHostInterface, 63);
    OSMetaClassDeclareReservedUnused(IOUSBHostInterface, 64);
    OSMetaClassDeclareReservedUnused(IOUSBHostInterface, 65);
    OSMetaClassDeclareReservedUnused(IOUSBHostInterface, 66);
    OSMetaClassDeclareReservedUnused(IOUSBHostInterface, 67);
    OSMetaClassDeclareReservedUnused(IOUSBHostInterface, 68);
    OSMetaClassDeclareReservedUnused(IOUSBHostInterface, 69);

protected:
    enum
    {
        kInitIORetries       = 3,
        kInitIORetryInterval = 100
    };
    
    virtual void updateMatchingProperties();
    
    virtual IOReturn selectAlternateSettingGated(uint8_t bAlternateSetting);
    
    virtual IOReturn copyPipeGated(uint8_t address, IOUSBHostPipe*& result);

    virtual void closePipes();
    virtual IOReturn closePipesGated();

    // Must be called on the command gate
    virtual void pipeLockLock();
    virtual void pipeLockUnlock();

    // Protected pad slots for alternate setting and pipe management
    OSMetaClassDeclareReservedUnused(IOUSBHostInterface, 70);
    OSMetaClassDeclareReservedUnused(IOUSBHostInterface, 71);
    OSMetaClassDeclareReservedUnused(IOUSBHostInterface, 72);
    OSMetaClassDeclareReservedUnused(IOUSBHostInterface, 73);
    OSMetaClassDeclareReservedUnused(IOUSBHostInterface, 74);
    OSMetaClassDeclareReservedUnused(IOUSBHostInterface, 75);
    OSMetaClassDeclareReservedUnused(IOUSBHostInterface, 76);
    OSMetaClassDeclareReservedUnused(IOUSBHostInterface, 77);
    OSMetaClassDeclareReservedUnused(IOUSBHostInterface, 78);
    OSMetaClassDeclareReservedUnused(IOUSBHostInterface, 79);
    
protected:
    IOUSBHostPipe*                      _pipeList[kUSBHostMaxPipes];
    
    bool _pipeLock;

    const StandardUSB::ConfigurationDescriptor* _configurationDescriptor;
    const StandardUSB::InterfaceDescriptor*     _interfaceDescriptor;
    IOUSBHostDevice*                            _device;
    
    uint32_t _debugLoggingMask;

#pragma mark Miscellaneous
public:
    /*!
     * @brief Return the parent/provider IOUSBHostDevice object of this interface.
     *
     * @return Pointer to the parent/provider IOUSBHostDevice object.
     */
    virtual IOUSBHostDevice* getDevice() const;
    
    /*!
     * @brief Return the current frame number of the USB bus
     *
     * @description This method will return the current frame number of the USB bus.  This is most useful for
     * scheduling future isochronous requests.
     *
     * @param theTime If not NULL, this will be updated with the current system time
     *
     * @return The current frame number
     */
    virtual uint64_t getFrameNumber(AbsoluteTime* theTime = NULL) const;
    
    /*!
     * @brief Return the current port status
     *
     * @discussion This method will return the current port status as a logical OR of bits described be @link USBDeviceInformationBits @\link
     *
     * @return port status
     */
    virtual uint32_t getPortStatus() const;

    /*!
     * @brief Allocate a buffer to be used for I/O
     *
     * @discussion The underlying host controller hardware may have alignment and fragmentation restrictions.  This
     * method will return a buffer which is guaranteed to meet the restrictions the host controller may have.
     *
     * @param options kIODirectionOut, kIODirectionIn to set the direction of the I/O transfer.
     *
     * @param capacity Size of the buffer to allocate
     *
     * @return Pointer to the newly allocated memory descriptor or NULL
     */
    virtual IOBufferMemoryDescriptor* createIOBuffer(IOOptionBits options, mach_vm_size_t capacity);
    
    // Public pad slots for miscellaneous
    OSMetaClassDeclareReservedUnused(IOUSBHostInterface, 80);
    OSMetaClassDeclareReservedUnused(IOUSBHostInterface, 81);
    OSMetaClassDeclareReservedUnused(IOUSBHostInterface, 82);
    OSMetaClassDeclareReservedUnused(IOUSBHostInterface, 83);
    OSMetaClassDeclareReservedUnused(IOUSBHostInterface, 84);
    OSMetaClassDeclareReservedUnused(IOUSBHostInterface, 85);
    OSMetaClassDeclareReservedUnused(IOUSBHostInterface, 86);
    OSMetaClassDeclareReservedUnused(IOUSBHostInterface, 87);
    OSMetaClassDeclareReservedUnused(IOUSBHostInterface, 88);
    OSMetaClassDeclareReservedUnused(IOUSBHostInterface, 89);

protected:
    // Protected pad slots for miscellaneous
    OSMetaClassDeclareReservedUnused(IOUSBHostInterface, 90);
    OSMetaClassDeclareReservedUnused(IOUSBHostInterface, 91);
    OSMetaClassDeclareReservedUnused(IOUSBHostInterface, 92);
    OSMetaClassDeclareReservedUnused(IOUSBHostInterface, 93);
    OSMetaClassDeclareReservedUnused(IOUSBHostInterface, 94);
    OSMetaClassDeclareReservedUnused(IOUSBHostInterface, 95);
    OSMetaClassDeclareReservedUnused(IOUSBHostInterface, 96);
    OSMetaClassDeclareReservedUnused(IOUSBHostInterface, 97);
    OSMetaClassDeclareReservedUnused(IOUSBHostInterface, 98);
    OSMetaClassDeclareReservedUnused(IOUSBHostInterface, 99);

protected:
    struct tExpansionData
    {
    };
    tExpansionData* _expansionData;
    
#pragma mark Deprecated
public:
    
    // virtual const IOUSBInterfaceDescriptor* FindNextAltInterface(const IOUSBInterfaceDescriptor* current,
    //                                                              IOUSBFindInterfaceRequest*      request) __attribute__((deprecated));
    // Replacement: StandardUSB::getNextInterfaceDescriptor

    // virtual IOUSBHostPipe* FindNextPipe(IOUSBHostPipe* current, IOUSBFindEndpointRequest* request) __attribute__((deprecated));
    // virtual IOUSBHostPipe* FindNextPipe(IOUSBHostPipe* current, IOUSBFindEndpointRequest* request, bool withRetain) __attribute__((deprecated));
    // Replacement: getInterfaceDescriptor and StandardUSB::getNextAssociatedDescriptorWithType to find an endpoint descriptor,
    // then use copyPipe to retrieve the pipe object

    // virtual const IOUSBDescriptorHeader* FindNextAssociatedDescriptor(const void* current, UInt8 type) __attribute__((deprecated));
    // Replacement: getInterfaceDescriptor and StandardUSB::getNextAssociatedDescriptorWithType

    // virtual IOReturn SetAlternateInterface(IOService* forClient, UInt16 alternateSetting) __attribute__((deprecated));
    // Replacement: selectAlternateSetting

    // virtual IOUSBHostPipe* GetPipeObj(UInt8 index) __attribute__((deprecated));
    // virtual IOUSBHostPipe* GetPipeObjRetain(UInt8 index) __attribute__((deprecated));
    // Replacement: copyPipe

    // virtual UInt8 GetConfigValue() __attribute__((deprecated));
    // Replacement: getConfigurationDescriptor

    // Deprecated.  Use getProvider
    // virtual IOUSBHostDevice* GetDevice() __attribute__((deprecated));

    // virtual UInt8 GetInterfaceNumber() __attribute__((deprecated));
    // virtual UInt8 GetAlternateSetting() __attribute__((deprecated));
    // virtual UInt8 GetNumEndpoints() __attribute__((deprecated));
    // virtual UInt8 GetInterfaceClass() __attribute__((deprecated));
    // virtual UInt8 GetInterfaceSubClass() __attribute__((deprecated));
    // virtual UInt8 GetInterfaceProtocol() __attribute__((deprecated));
    // virtual UInt8 GetInterfaceStringIndex() __attribute__((deprecated));
    // Replacement: getInterfaceDescriptor

    // virtual IOReturn DeviceRequest(IOUSBDevRequest* request, IOUSBCompletion* completion = 0) __attribute__((deprecated));
    // virtual IOReturn DeviceRequest(IOUSBDevRequestDesc* request, IOUSBCompletion* completion = 0) __attribute__((deprecated));
    // Replacement: deviceRequest

    // virtual IOReturn GetEndpointProperties(UInt8 alternateSetting, UInt8 endpointNumber, UInt8 direction, UInt8* transferType, UInt16* maxPacketSize, UInt8* interval) __attribute__((deprecated));
    // Replacement: StandardUSB::getEndpoint*

    // virtual IOReturn SetIdlePolicy(UInt32 deviceIdleTimeout, UInt32 ioIdleTimeout) __attribute__((deprecated));
    // Replacement: setIdlePolicy and IOUSBHostPope::setIdlePolicy

    // virtual void GetIdlePolicy(UInt32& deviceIdleTimeout, UInt32& ioIdleTimeout) __attribute__((deprecated));
    // Replacement: getIdlePolicy and IOUSBHostPipe::getIdlePolicy

    // IOBufferMemoryDescriptor* CreateIOBuffer(IOOptionBits options, mach_vm_size_t capacity) __attribute__((deprecated));
    // Replacement: createIOBuffer
};

#endif // IOUSBHostFamily_IOUSBHostInterface_h
