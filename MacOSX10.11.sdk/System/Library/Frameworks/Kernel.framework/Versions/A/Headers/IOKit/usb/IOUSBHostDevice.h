/*
 * Copyright (c) 1998-2007 Apple Inc. All rights reserved.
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

#ifndef IOUSBHostFamily_IOUSBHostDevice_h
#define IOUSBHostFamily_IOUSBHostDevice_h

#include <IOKit/usb/StandardUSB.h>
#include <IOKit/usb/IOUSBHostFamily.h>
#include <IOKit/usb/IOUSBHostPipe.h>
#include <IOKit/IOBufferMemoryDescriptor.h>
#include <IOKit/IOWorkLoop.h>
#include <IOKit/IOCommandGate.h>
#include <IOKit/pwr_mgt/RootDomain.h>
#include <kern/thread_call.h>

// The following are definitions for errata properties needed for different devices.  This
// should be but in the dictionary of the IOUSBHostDevice in question.  This can be achieved
// by using the AppleUSBHostMergeProperties class and having an IOProviderMergeProperties dictionary
// with the required properties.

// This property allows a device to specify a configuration value of 0 in its configuration
// descriptor.  This does not follow the spec, but we will allow it in order to get the device
// to work.  The property should be a Boolean
//
#define kAllowConfigValueOfZero         "kAllowZeroConfigValue"
#define kAllowNumConfigsOfZero          "kAllowZeroNumConfigs"

#define kUSBHostDeviceForceSuspend "kUSBHostDeviceForceSuspend"

class AppleUSBHostController;
class IOUSBHostInterface;
class AppleUSBHostDeviceIdler;
class AppleUSBHostRequestCompleter;
class AppleUSBHostSynchronousRequestCompleter;
class AppleUSBHostPort;
class AppleUSBHostDescriptorCache;
class AppleUSBHostResources;

/*!
    @class IOUSBHostDevice
    @abstract The IOService object representing a device on the USB bus.
    @discussion This class provides functionality to configure a device and to create
        IOUSBHostInterface objects to represent the interfaces of the device.
 */

/*!
 * @class IOUSBHostDevice
 *
 * @brief The IOService object representing a device on the USB bus.
 *
 * @discussion  This class provides functionality to configure a device and to create IOUSBHostInterface objects to 
 * represent the interfaces of the device.
 */
class IOUSBHostDevice : public IOService
{
    friend class AppleUSBHostController;
    friend class IOUSBHostInterface;
    friend class IOUSBHostIOSource;
    friend class IOUSBHostPipe;
    friend class IOUSBHostStream;
    friend class AppleUSBIORequest;
    friend class AppleUSBHostDeviceIdler;

    OSDeclareDefaultStructors(IOUSBHostDevice)

public:
    /*!
     * @brief Powerstates supported by an IOUSBHostDevice
     *
     * @constant kPowerStateOff The device has been powered off and is likely in the process of terminating
     * @constant kPowerStateSuspended The device is suspended.  All I/O has been paused and the bus will be
     * suspended once its AppleUSBHostPort power parent enters the suspend state.
     * @constant kPowerStateOn The device is powered on and I/O is possible.
     * @constant kPowerStateCount Number of possible power states 
     */
    enum tPowerState
    {
        kPowerStateOff = 0,
        kPowerStateSuspended,
        kPowerStateOn,
        kPowerStateCount
    };

    /*!
     * @brief Factory method for creating an IOUSBHostDevice object
     *
     * @param controller Controller to which the USB device is attached
     *
     * @param speed Speed at which the device enumerated
     *
     * @param address Address that was assigned during enumeration
     *
     * @return Pointer to an IOUSBHostDevice object is successful
     */
    static IOUSBHostDevice* withController(AppleUSBHostController* controller, UInt8 speed, tUSBHostDeviceAddress address);

protected:
    virtual bool initWithController(AppleUSBHostController* controller, UInt8 speed, tUSBHostDeviceAddress address);
    
    // Pad slots for future expansion
    OSMetaClassDeclareReservedUnused(IOUSBHostDevice, 0);
    OSMetaClassDeclareReservedUnused(IOUSBHostDevice, 1);
    OSMetaClassDeclareReservedUnused(IOUSBHostDevice, 2);
    OSMetaClassDeclareReservedUnused(IOUSBHostDevice, 3);
    OSMetaClassDeclareReservedUnused(IOUSBHostDevice, 4);
    OSMetaClassDeclareReservedUnused(IOUSBHostDevice, 5);
    OSMetaClassDeclareReservedUnused(IOUSBHostDevice, 6);
    OSMetaClassDeclareReservedUnused(IOUSBHostDevice, 7);
    OSMetaClassDeclareReservedUnused(IOUSBHostDevice, 8);
    OSMetaClassDeclareReservedUnused(IOUSBHostDevice, 9);
    
#pragma mark IOService overrides
public:
    virtual bool attach(IOService* provider);
    virtual bool start(IOService* provider);
    virtual bool terminate(IOOptionBits options = 0);
    virtual void stop(IOService* provider);
    virtual void free(void);

    virtual bool compareProperty(OSDictionary* matching, const char* key);
    virtual bool compareProperty(OSDictionary* matching, const OSString* key);
    virtual bool matchPropertyTable(OSDictionary* table, SInt32* score);

    virtual bool open(IOService* forClient, IOOptionBits options = 0, void* arg = 0);
    virtual bool handleOpen(IOService* forClient, IOOptionBits options, void* arg);
    virtual bool handleIsOpen(const IOService* forClient) const;
    virtual void close(IOService* forClient, IOOptionBits options = 0);
    virtual void handleClose(IOService* forClient, IOOptionBits options);
    
    virtual IOReturn message(UInt32 type, IOService* provider,  void* argument = 0);

    virtual const char* stringFromReturn(IOReturn rtn);

protected:
    virtual IOReturn terminateGated(IOOptionBits options = 0);
    
    virtual IOReturn openGated(IOService* forClient, IOOptionBits options, void* arg);
    virtual IOReturn closeGated(IOService* forClient, IOOptionBits options);

    // Protected pad slots for IOService overrides
    OSMetaClassDeclareReservedUnused(IOUSBHostDevice, 10);
    OSMetaClassDeclareReservedUnused(IOUSBHostDevice, 11);
    OSMetaClassDeclareReservedUnused(IOUSBHostDevice, 12);
    OSMetaClassDeclareReservedUnused(IOUSBHostDevice, 13);
    OSMetaClassDeclareReservedUnused(IOUSBHostDevice, 14);
    OSMetaClassDeclareReservedUnused(IOUSBHostDevice, 15);
    OSMetaClassDeclareReservedUnused(IOUSBHostDevice, 16);
    OSMetaClassDeclareReservedUnused(IOUSBHostDevice, 17);
    OSMetaClassDeclareReservedUnused(IOUSBHostDevice, 18);
    OSMetaClassDeclareReservedUnused(IOUSBHostDevice, 19);
    
protected:
    int32_t                                  _terminationPending;
    AppleUSBHostResources*                   _resources;
    AppleUSBHostController*                  _controller;
    AppleUSBHostPort*                        _port;
    OSSet*                                   _clients;
    IOWorkLoop*                              _workLoop;
    IOCommandGate*                           _commandGate;
    
#pragma mark Power management
public:
    /*!
     * @methodgroup Power management
     *
     * @discussion The following mthods should be considered private and should not be called by client drivers.
     * In general the below methods are overriden IOService power methods used internally to implement idling
     * and maintain proper device state.
     */
    virtual void          registerPowerService();
    virtual IOReturn      addPowerChild(IOService* theChild);
    virtual IOReturn      removePowerChild(IOPowerConnection* theChild);
    virtual IOReturn      powerStateWillChangeTo(IOPMPowerFlags capabilities, unsigned long stateNumber, IOService* whatDevice);
    virtual IOReturn      setPowerState(unsigned long stateNumber, IOService* whatDevice);
    virtual IOReturn      powerStateDidChangeTo(IOPMPowerFlags capabilities, unsigned long stateNumber, IOService* whatDevice);
    virtual unsigned long initialPowerStateForDomainState(IOPMPowerFlags domainState);
    virtual void          PMstop(void);
    virtual IOReturn      forcePower(tPowerState powerState, bool clamp, uint32_t timeoutMs = 0);
    
    /*!
     * @brief Allocate bus current in addition to the bMaxPower value specified by the configuration descriptor
     *
     * @discussion Some hosts are able to source more than the standard-defined bus current to attached devices, or
     * may use less current than defined in the bMaxPower field of the configuration descriptor.
     *
     * Devices can use this interface to request more or less bus current.  The parameters passed in are abolute values
     * of current required for operation in kPowerStateOn and kPowerStateSuspended IOUSBHostDevice power levels, and
     * override the bMaxPower field in the configuration descriptor.  For example, if bMaxPower indicates the device
     * requires 500mA to operate, then a request for 1000mA will double the allocated power for the device.
     *
     * A setConfiguration(0) call to unconfigure the device will reset these overrides.
     *
     * The parameters are passed by reference, and may be modified by the software stack before being returned.
     * If more bus current is being requested than is available, the value may be reduced to stay within system limits.
     *
     * @param wakeUnits The number of extra mA requested when the device is in kPowerStateOn
     *
     * @param sleepUnits The number of extra mA requested when the device is in kPowerStateSuspended
     *
     * @return IOReturn kIOReturnSuccess if the device's allocation amounts were updated
     */
    virtual IOReturn allocateDownstreamBusCurrent(uint32_t& wakeUnits, uint32_t& sleepUnits);
    
    enum tIdleAssertion
    {
        kIdleAssertionInhibit = 0,
        kIdleAssertionPermit
    };
    virtual IOReturn idleAssertion(IOService* forService, tIdleAssertion assertion);

    // Public pad slots for power management
    OSMetaClassDeclareReservedUnused(IOUSBHostDevice, 20);
    OSMetaClassDeclareReservedUnused(IOUSBHostDevice, 21);
    OSMetaClassDeclareReservedUnused(IOUSBHostDevice, 22);
    OSMetaClassDeclareReservedUnused(IOUSBHostDevice, 23);
    OSMetaClassDeclareReservedUnused(IOUSBHostDevice, 24);
    OSMetaClassDeclareReservedUnused(IOUSBHostDevice, 25);
    OSMetaClassDeclareReservedUnused(IOUSBHostDevice, 26);
    OSMetaClassDeclareReservedUnused(IOUSBHostDevice, 27);
    OSMetaClassDeclareReservedUnused(IOUSBHostDevice, 28);
    OSMetaClassDeclareReservedUnused(IOUSBHostDevice, 29);

protected:
    static IOPMPowerState  _sPowerStates[kPowerStateCount];
    static const OSSymbol* _sPowerStateSymbols[kPowerStateCount];
    
    virtual void     powerChangeDone(unsigned long stateNumber);
    virtual IOReturn powerStateWillChangeToGated(IOPMPowerFlags capabilities, unsigned long stateNumber, IOService* whatDevice);
    virtual IOReturn setPowerStateGated(unsigned long stateNumber, IOService* whatDevice);
    virtual IOReturn powerStateDidChangeToGated(IOPMPowerFlags capabilities, unsigned long stateNumber, IOService* whatDevice);
    virtual IOReturn forcePowerGated(tPowerState powerState, bool clamp, uint32_t timeoutMs);
    virtual void     addPowerChildThreadCall(thread_call_t threadCall);
    virtual IOReturn addPowerChildGated(void);

    virtual void     pmStopThreadCall(thread_call_t threadCall);

    virtual IOReturn allocateDownstreamBusCurrentGated(uint32_t& wakeUnits, uint32_t& sleepUnits);

    virtual IOReturn updateIdlePolicy(bool asynchronous = false);
    virtual void updateIdlePolicyAsync(thread_call_t threadCall);
    virtual IOReturn updateIdlePolicyGated();

    // Protected pad slots for power management
    OSMetaClassDeclareReservedUnused(IOUSBHostDevice, 30);
    OSMetaClassDeclareReservedUnused(IOUSBHostDevice, 31);
    OSMetaClassDeclareReservedUnused(IOUSBHostDevice, 32);
    OSMetaClassDeclareReservedUnused(IOUSBHostDevice, 33);
    OSMetaClassDeclareReservedUnused(IOUSBHostDevice, 34);
    OSMetaClassDeclareReservedUnused(IOUSBHostDevice, 35);
    OSMetaClassDeclareReservedUnused(IOUSBHostDevice, 36);
    OSMetaClassDeclareReservedUnused(IOUSBHostDevice, 37);
    OSMetaClassDeclareReservedUnused(IOUSBHostDevice, 38);
    OSMetaClassDeclareReservedUnused(IOUSBHostDevice, 39);
    
protected:
    bool                    _allowUpdateIdlePolicy;
    bool                    _forcePowerInProgress;
    IOLock*                 _powerChildrenLock;
    OSSet*                  _powerChildren;
    OSSet*                  _activePowerChildren;
    IOPMDriverAssertionID   _externalDevicePowerAssertion;
    tPowerState             _currentPowerState;
    bool                    _powerOffPending;

#pragma mark Descriptors
public:
    /*!
     * @brief Store the provided descriptor in the set of cached descriptors.
     *
     * @discussion This method will store the provided descriptor in the set of caced descriptors.  Internally,
     * the cache is an OSDictionary containing OSSets indexted by the bDescriptorType field.  There can only be
     * one cached descriptor in the set with identical <code>bDescriptorType</code>, <code>index</code>, and 
     * <code>languageID</code>.  The descriptor is copied into the cache.
     *
     * @param descriptor Pointer to the descriptor to cache
     *
     * @param length Length of the descriptor, if 0 the length will be extracted from the descriptor itself.
     *
     * @param index Descriptor index value.  Low byte of <code>wValue</code> of the SET_DESCRIPTOR control request described
     * in section 9.4.8 of the USB 2.0 specification.
     *
     * @param languageID Descriptor language ID.  <code>wIndex</code> of the SET_DESCRIPTOR control request described in 
     * section 9.4.8 of the USB 2.0 specification.
     *
     * @return IOReturn result code
     */
    virtual IOReturn cacheDescriptor(const StandardUSB::Descriptor* descriptor, uint16_t length = 0, uint8_t index = 0, uint16_t languageID = 0);
    
    /*!
     * @brief Search the cache for the descriptor
     *
     * @discussion This method will search the descriptor cache for the descriptor that matches the input arguments.  If
     * the descriptor is not in the cache, a device request will be issued to retrieve the descriptor from the USB device.
     * If the device request is successful, the resulting descriptor will be added to the cache.
     *
     * @param type <bDescriptorType> of the descriptor to find.
     *
     * @param length Reference to a uint16_t which will be updated with the length of the descriptor
     *
     * @param index Descriptor index value.  Low byte of <code>wValue</code> of the GET_DESCRIPTOR control request described
     * in section 9.4.3 of the USB 2.0 specification.
     *
     * @param languageID Descriptor language ID.  <code>wIndex</code> of the GET_DESCRIPTOR control request described in
     * section 9.4.3 of the USB 2.0 specification.
     *
     * @param requestType tDeviceRequestType to be used for the GET_DESCRIPTOR control request
     *
     * @param requestRecipient tDeviceRequestRecipient to be used for the GET_DESCRIPTOR control request
     *
     * @return Pointer to the descriptor if found.
     */
    virtual const StandardUSB::Descriptor* getDescriptor(uint8_t type,
                                                         uint16_t& length,
                                                         uint8_t index = 0,
                                                         uint16_t languageID = 0,
                                                         tDeviceRequestType requestType = kRequestTypeStandard,
                                                         tDeviceRequestRecipient requestRecipient = kRequestRecipientDevice);
    
    // Retrieve and cache the entire length of standard descriptor types
    // TODO: We are handing out pointers to cached descriptors, which could theoretically be invalidated
    // TODO: We might want to make it so cached descriptors can't be replaced or removed by anyone but us
    /*!
     * @brief Return the device descriptor
     *
     * @discussion This method is simply a convenience method to retrieve the device descriptor.  Internally this method
     * simply calls @link getDescriptor @/link.
     *
     * @return Pointer to the device descriptor if found.
     */
    virtual const StandardUSB::DeviceDescriptor* getDeviceDescriptor();

    /*!
     * @brief Return the configuration descriptor with the specified index
     *
     * @discussion This method is simply a convenience method to retrieve the configuration descriptor.  Internally this method
     * simply calls @link getDescriptor @/link.
     *
     * @param index  Descriptor index value.  Low byte of <code>wValue</code> of the GET_DESCRIPTOR control request described
     * in section 9.4.3 of the USB 2.0 specification.
     *
     * @return Pointer to the configuration descriptor if found
     */
    virtual const StandardUSB::ConfigurationDescriptor* getConfigurationDescriptor(uint8_t index);

    /*!
     * @brief Return the configuration descriptor with the specified <code>bConfigurationValue</code>
     *
     * @discussion This method will iterate through all configuration descriptors by index looking for the one whose
     * <code>bConfigurationValue</code> matches the input value.
     *
     * @param bConfigurationValue Value to match
     *
     * @return Pointer to the configuration descriptor if found
     */
    virtual const StandardUSB::ConfigurationDescriptor* getConfigurationDescriptorWithValue(uint8_t bConfigurationValue);
    
    /*!
     * @brief Return the currently selected configuration descriptor
     *
     * @discussion This method will return the configuration descriptor currently selected by a successful setConfiguration call
     *
     * @return Pointer to the configuration descriptor if found, or NULL if the device is not configured
     */
    virtual const StandardUSB::ConfigurationDescriptor* getConfigurationDescriptor();

    /*!
     * @brief Return the capability descriptors of the device
     *
     * @discussion This method will attempt to return the Binary Device Object Store descriptors described in section
     * 9.6.2 of the USB 3.1 specification.
     *
     * @return Pointer to the BOS descriptor if found
     */
    virtual const StandardUSB::BOSDescriptor* getCapabilityDescriptors();

    /*!
     * @brief Return a string descriptor from the device
     *
     * @discussion This method is simply a convenience method to retieve the desired string descriptor.  Internally this method
     * simply calls @link getDescriptor @/link.
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
    OSMetaClassDeclareReservedUnused(IOUSBHostDevice, 40);
    OSMetaClassDeclareReservedUnused(IOUSBHostDevice, 41);
    OSMetaClassDeclareReservedUnused(IOUSBHostDevice, 42);
    OSMetaClassDeclareReservedUnused(IOUSBHostDevice, 43);
    OSMetaClassDeclareReservedUnused(IOUSBHostDevice, 44);
    OSMetaClassDeclareReservedUnused(IOUSBHostDevice, 45);
    OSMetaClassDeclareReservedUnused(IOUSBHostDevice, 46);
    OSMetaClassDeclareReservedUnused(IOUSBHostDevice, 47);
    OSMetaClassDeclareReservedUnused(IOUSBHostDevice, 48);
    OSMetaClassDeclareReservedUnused(IOUSBHostDevice, 49);

protected:
    virtual IOReturn cacheDescriptorGated(const StandardUSB::Descriptor* descriptor, uint16_t length, uint8_t index, uint16_t languageID);
    
    struct tDescriptorSelectors
    {
        uint8_t                 index;
        uint16_t                languageID;
        tDeviceRequestType      requestType;
        tDeviceRequestRecipient requestRecipient;
    };
    virtual IOReturn getDescriptorGated(uint8_t type, uint16_t& length, tDescriptorSelectors& selectors, const StandardUSB::Descriptor*& result);
    
    // Protected pad slots for descriptors
    OSMetaClassDeclareReservedUnused(IOUSBHostDevice, 50);
    OSMetaClassDeclareReservedUnused(IOUSBHostDevice, 51);
    OSMetaClassDeclareReservedUnused(IOUSBHostDevice, 52);
    OSMetaClassDeclareReservedUnused(IOUSBHostDevice, 53);
    OSMetaClassDeclareReservedUnused(IOUSBHostDevice, 54);
    OSMetaClassDeclareReservedUnused(IOUSBHostDevice, 55);
    OSMetaClassDeclareReservedUnused(IOUSBHostDevice, 56);
    OSMetaClassDeclareReservedUnused(IOUSBHostDevice, 57);
    OSMetaClassDeclareReservedUnused(IOUSBHostDevice, 58);
    OSMetaClassDeclareReservedUnused(IOUSBHostDevice, 59);

protected:
    bool                         _getDescriptorInProgress;
    AppleUSBHostDescriptorCache* _descriptorCache;
    
#pragma mark Configuration, interface, and pipe management
public:
    /*!
     * @brief Select a new configuration for the device
     *
     * @discussion This method will select a new configuration for a device.  If the device was previously configured all
     * child interfaces will be terminated prior to setting the new configuration.  This method will send the SET_CONFIGURATION
     * request to the device as described by section 9.4.7 of the USB 2.0 specification.
     *
     * @param bConfigurationValue Configuration to select
     *
     * @param matchInterfaces If true, any interfaces within the new configuration will be registered for matching.
     *
     * @return IOReturn result code
     */
    virtual IOReturn setConfiguration(uint8_t bConfigurationValue, bool matchInterfaces = true);
    
    /*!
     * @brief Factory method to create IOUSBHostPipe objects
     *
     * @param descriptor Endpoint descriptor for this pipe (used to decide direction, bandwidth requirements, etc).
     *
     * @param companionDescriptor Companion descriptor for the endpint
     *
     * @param interface Interface to which the endpoint belongs
     *
     * @return Pointer to the newly created IOUSBHostPipe object
     */
    virtual IOUSBHostPipe* createPipe(const StandardUSB::EndpointDescriptor* descriptor, const StandardUSB::SuperSpeedEndpointCompanionDescriptor* companionDescriptor, IOUSBHostInterface* interface);
    
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
    virtual IOReturn deviceRequest(IOService* forClient, StandardUSB::DeviceRequest& request, void* dataBuffer, IOUSBHostCompletion* completion, uint32_t completionTimeoutMs = kUSBHostDefaultControlCompletionTimeoutMS);

    /*!
     * @brief Issue an aynchronous setup request on the default control pipe
     *
     * @discussion This method will issue an asynchronous control request on the defaul pipe.
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
    virtual IOReturn deviceRequest(IOService* forClient, StandardUSB::DeviceRequest& request, IOMemoryDescriptor* dataBuffer, IOUSBHostCompletion* completion, uint32_t completionTimeoutMs = kUSBHostDefaultControlCompletionTimeoutMS);
    
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
    virtual IOReturn deviceRequest(IOService* forClient, StandardUSB::DeviceRequest& request, void* dataBuffer, uint32_t& bytesTransferred, uint32_t completionTimeoutMs = kUSBHostDefaultControlCompletionTimeoutMS);

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
    virtual IOReturn deviceRequest(IOService* forClient, StandardUSB::DeviceRequest& request, IOMemoryDescriptor* dataBuffer, uint32_t& bytesTransferred, uint32_t completionTimeoutMs = kUSBHostDefaultControlCompletionTimeoutMS);

    /*!
     * @brief Abort device requests made via the @link deviceRequest @\link methods by <code>forClient</code>
     *
     * @discussion This method will abort any requests made via the @link deviceRequest @\link methods.  It will not abort
     * requests made through other interface objects.
     *
     * @param forClient Client which issued the requests
     *
     * @param options IOUSBHostIOSource::tAbortOptions
     *
     * @param withError IOReturn error value to return with the requests.
     *
     * @return IOReturn result code
     */
    virtual IOReturn abortDeviceRequests(IOService* forClient = NULL, IOOptionBits options = IOUSBHostIOSource::kAbortAsynchronous, IOReturn withError = kIOReturnAborted);
    
    // Public pad slots for configuration, interface, and pipe management
    OSMetaClassDeclareReservedUnused(IOUSBHostDevice, 60);
    OSMetaClassDeclareReservedUnused(IOUSBHostDevice, 61);
    OSMetaClassDeclareReservedUnused(IOUSBHostDevice, 62);
    OSMetaClassDeclareReservedUnused(IOUSBHostDevice, 63);
    OSMetaClassDeclareReservedUnused(IOUSBHostDevice, 64);
    OSMetaClassDeclareReservedUnused(IOUSBHostDevice, 65);
    OSMetaClassDeclareReservedUnused(IOUSBHostDevice, 66);
    OSMetaClassDeclareReservedUnused(IOUSBHostDevice, 67);
    OSMetaClassDeclareReservedUnused(IOUSBHostDevice, 68);
    OSMetaClassDeclareReservedUnused(IOUSBHostDevice, 69);

protected:
    virtual IOReturn setConfigurationGated(uint8_t bConfigurationValue, bool matchInterfaces);
    
    virtual IOReturn createPipeGated(const StandardUSB::EndpointDescriptor* descriptor, const StandardUSB::SuperSpeedEndpointCompanionDescriptor* companionDescriptor, IOUSBHostInterface* interface, IOUSBHostPipe*& result);

    virtual IOReturn deviceRequest(IOService* forClient, StandardUSB::DeviceRequest& request,
                                   void* rawBuffer, IOMemoryDescriptor* descriptorBuffer,
                                   uint32_t& bytesTransferred, IOUSBHostCompletion* completion,
                                   uint32_t completionTimeoutMs);

    virtual IOReturn internalDeviceRequest(IOService* forClient, StandardUSB::DeviceRequest& request,
                                           void* rawBuffer, IOMemoryDescriptor* descriptorBuffer,
                                           uint32_t& bytesTransferred, IOUSBHostCompletion* completion,
                                           uint32_t completionTimeoutMs);
    
    virtual IOReturn internalDeviceRequestGated(IOUSBHostPipe::tInternalControlRequestParameters& parameters);

    virtual IOReturn abortDeviceRequestsGated(IOService* forClient, IOOptionBits options, IOReturn withError);
    
    // Protected pad slots for configuration, interface, and pipe management
    OSMetaClassDeclareReservedUnused(IOUSBHostDevice, 70);
    OSMetaClassDeclareReservedUnused(IOUSBHostDevice, 71);
    OSMetaClassDeclareReservedUnused(IOUSBHostDevice, 72);
    OSMetaClassDeclareReservedUnused(IOUSBHostDevice, 73);
    OSMetaClassDeclareReservedUnused(IOUSBHostDevice, 74);
    OSMetaClassDeclareReservedUnused(IOUSBHostDevice, 75);
    OSMetaClassDeclareReservedUnused(IOUSBHostDevice, 76);
    OSMetaClassDeclareReservedUnused(IOUSBHostDevice, 77);
    OSMetaClassDeclareReservedUnused(IOUSBHostDevice, 78);
    OSMetaClassDeclareReservedUnused(IOUSBHostDevice, 79);

#pragma mark Miscellaneous
public:
    /*!
     * @brief Return the device's address
     *
     * @return Current address of the device
     */
    virtual tUSBHostDeviceAddress getAddress() const;
    
    /*!
     * @brief Return the device's speed
     *
     * @return The enumerated speed of the device:
     * @constant kUSBHostConnectionSpeedLow
     * @constant kUSBHostConnectionSpeedFull
     * @constant kUSBHostConnectionSpeedHigh
     * @constant kUSBHostConnectionSpeedSuper
     */
    virtual uint8_t getSpeed() const;
    
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
    virtual uint64_t getFrameNumber(AbsoluteTime* theTime = NULL);
    
    /*!
     * @brief Reset and re-emerate the device
     *
     * @discussion This function will reset and re-enumerate the USB device.  The current IOUSBHostDevice object and all
     * of its children will be terminated.  A new IOUSBHostDevice object will be created and registered if the reset
     * is successful and the previous object has finished terminating.  This function may not be called from the port
     * workloop thread.
     *
     * @return IOReturn result code
     */
    virtual IOReturn reset();
    
    /*!
     * @brief Return the current port status
     *
     * @discussion This method will return the current port status as a logical OR of bits described by @link tUSBHostPortStatus @\link
     *
     * @return port status
     */
    virtual uint32_t getPortStatus();
    
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
    OSMetaClassDeclareReservedUnused(IOUSBHostDevice, 80);
    OSMetaClassDeclareReservedUnused(IOUSBHostDevice, 81);
    OSMetaClassDeclareReservedUnused(IOUSBHostDevice, 82);
    OSMetaClassDeclareReservedUnused(IOUSBHostDevice, 83);
    OSMetaClassDeclareReservedUnused(IOUSBHostDevice, 84);
    OSMetaClassDeclareReservedUnused(IOUSBHostDevice, 85);
    OSMetaClassDeclareReservedUnused(IOUSBHostDevice, 86);
    OSMetaClassDeclareReservedUnused(IOUSBHostDevice, 87);
    OSMetaClassDeclareReservedUnused(IOUSBHostDevice, 88);
    OSMetaClassDeclareReservedUnused(IOUSBHostDevice, 89);

protected:
    // Protected pad slots for miscellaneous
    OSMetaClassDeclareReservedUnused(IOUSBHostDevice, 90);
    OSMetaClassDeclareReservedUnused(IOUSBHostDevice, 91);
    OSMetaClassDeclareReservedUnused(IOUSBHostDevice, 92);
    OSMetaClassDeclareReservedUnused(IOUSBHostDevice, 93);
    OSMetaClassDeclareReservedUnused(IOUSBHostDevice, 94);
    OSMetaClassDeclareReservedUnused(IOUSBHostDevice, 95);
    OSMetaClassDeclareReservedUnused(IOUSBHostDevice, 96);
    OSMetaClassDeclareReservedUnused(IOUSBHostDevice, 97);
    OSMetaClassDeclareReservedUnused(IOUSBHostDevice, 98);
    OSMetaClassDeclareReservedUnused(IOUSBHostDevice, 99);

public:
    // Removed legacy methods
    
    // virtual UInt16 GetbcdUSB() __attribute__((deprecated));
    // Replacement: USBToHost16(getDeviceDescriptor()->bcdUSB);
    
    // virtual UInt8  GetDeviceClass() __attribute__((deprecated));
    // Replacement: getDeviceDescriptor()->bDeviceClass;
    
    // virtual UInt8  GetDeviceSubClass() __attribute__((deprecated));
    // Replacement: getDeviceDescriptor()->bDeviceSubClass
    
    // virtual UInt8  GetProtocol() __attribute__((deprecated));
    // Replacement: getDeviceDescriptor()->bDeviceProtocol
    
    // virtual UInt8  GetMaxPacketSize() __attribute__((deprecated));
    // Replacement: getDeviceDescriptor->bMaxPacketSize0
    
    // virtual UInt16 GetVendorID() __attribute__((deprecated));
    // Replacement: USBToHost16(getDeviceDescriptor()->idVendor)
    
    // virtual UInt16 GetProductID() __attribute__((deprecated));
    // Replacement: USBToHost16(getDeviceDescriptor()->idProduct)
    
    // virtual UInt16 GetDeviceRelease() __attribute__((deprecated));
    // Replacement: USBToHost16(getDeviceDescriptor()->bcdDevice)

    // virtual UInt8  GetNumConfigurations() __attribute__((deprecated));
    // Replacement: getDeviceDescriptor()->bNumConfigurations
    
    // virtual UInt8  GetManufacturerStringIndex() __attribute__((deprecated));
    // Replacement: getDeviceDescriptor()->iManufacturer
    
    // virtual UInt8  GetProductStringIndex() __attribute__((deprecated));
    // Replacement: getDeviceDescriptor()->iProduct

    // virtual UInt8  GetSerialNumberStringIndex() __attribute__((deprecated));
    // Replacement: getDeviceDescriptor()->iSerialNumber
    
    // virtual IOReturn FindNextInterfaceDescriptor(const IOUSBConfigurationDescriptor* configDescIn,
    //                                              const IOUSBInterfaceDescriptor*     intfDesc,
    //                                              const IOUSBFindInterfaceRequest*    request,
    //                                              IOUSBInterfaceDescriptor**          descOut) __attribute__((deprecated));
    // Replacement:
    // ConfigurationDescriptor* confDesc = getConfigurationDescriptor(1);
    // InterfaceDescriptor* intDesc = NULL;
    // while((intDesc = getNextInterfaceDescriptor(confDesc, intDesc)) != NULL)
    // {
    //     if(intDesc->bInterfaceClass == kMyClass)
    //     {
    //         break;
    //     }
    // }
    
    // virtual const IOUSBConfigurationDescriptor* GetCachedConfigurationDescriptor(UInt8 configIndex) __attribute__((deprecated));
    // virtual const IOUSBConfigurationDescriptor* GetFullConfigurationDescriptor(UInt8 configIndex) __attribute__((deprecated));
    // Replacement: getConfigurationDescriptor(configIndex)
    
    // virtual IOReturn GetConfigurationDescriptor(UInt8 configValue, void* data, UInt32 len) __attribute__((deprecated));
    // Replacement: getConfigurationDescriptorWithValue(configValue)


    // virtual IOUSBHostInterface* FindNextInterface(IOUSBHostInterface*        current,
    //                                               IOUSBFindInterfaceRequest* request) __attribute__((deprecated));
    // virtual OSIterator* CreateInterfaceIterator(IOUSBFindInterfaceRequest* request) __attribute__((deprecated));
    // Replacement:
    // OSIterator* iterator = _device->getChildIterator(gIOServicePlane);
    // OSObject* candidate = NULL;
    // while(iterator != NULL && (candidate = iterator->getNextObject()) != NULL)
    // {
    //     IOUSBHostInterface* interfaceCandidate = OSDynamicCast(IOUSBHostInterface, candidate);
    //     if(   interfaceCandidate != NULL
    //        && interfaceCandidate->getInterfaceDescriptor()->bInterfaceClass == kUSBHubClass)
    //     {
    //         _interface = interfaceCandidate;
    //         break;
    //     }
    // }
    // OSSafeReleaseNULL(iterator);
    
    // virtual IOReturn SetConfiguration(IOService* forClient, UInt8 configNumber, bool startMatchingInterfaces = true) __attribute__((deprecated));
    // Replacement: setConfiguration(configNumber, startMatchingInterfaces)

    // No longer supported.
    // Use getSpeed instead.
    // virtual UInt8 GetSpeed(void) __attribute__((deprecated));

    // virtual AppleUSBHostController* GetBus(void) __attribute__((deprecated));
    // Use getFrameNumber and createIOBuffer instead.

    // No longer supported.
    // Use allocateDownstreamBusCurrent instead.
    // virtual UInt32 GetBusPowerAvailable(void) __attribute__((deprecated));

    // virtual IOReturn DeviceRequest(IOUSBDevRequest* request,
    //                                IOUSBCompletion* completion = 0) __attribute__((deprecated));
    // virtual IOReturn DeviceRequest(IOUSBDevRequestDesc* request,
    //                                IOUSBCompletion*     completion = 0) __attribute__((deprecated));
    // virtual IOReturn DeviceRequest(IOUSBDevRequest* request,
    //                                UInt32           noDataTimeout,
    //                                UInt32           completionTimeout,
    //                                IOUSBCompletion* completion = 0) __attribute__((deprecated));
    // virtual IOReturn DeviceRequest(IOUSBDevRequestDesc* request,
    //                                UInt32               noDataTimeout,
    //                                UInt32               completionTimeout,
    //                                IOUSBCompletion*     completion = 0) __attribute__((deprecated));
    // Replacment:
    // deviceRequest(...)
    
    // virtual IOReturn GetConfiguration(UInt8* configNumber) __attribute__((deprecated));
    // Replacment:
    // uint8_t configNumber  = 0;
    // StandardUSB::DeviceRequest request;
    // request.bmRequestType = makeDeviceRequestbmRequestType(kRequestDirectionIn, kRequestTypeStandard, kRequestRecipientDevice);
    // request.bRequest      = kDeviceRequestGetConfiguration;
    // request.wValue        = 0;
    // request.wIndex        = 0;
    // request.wLength       = sizeof(configNumber);
    //
    // uint32_t bytesTransferred = 0;
    //    
    // deviceRequest(this, request, &configNumber, bytesTransferred, kUSBHostStandardRequestCompletionTimeout);
    
    // virtual IOReturn GetDeviceStatus(USBStatus* status) __attribute__((deprecated));
    // Replacement:
    // uint16_t status       = 0;
    // StandardUSB::DeviceRequest request;
    // request.bmRequestType = makeDeviceRequestbmRequestType(kRequestDirectionIn, kRequestTypeStandard, kRequestRecipientDevice);
    // request.bRequest      = kDeviceRequestGetStatus;
    // request.wValue        = 0;
    // request.wIndex        = 0;
    // request.wLength       = sizeof(status);
    //
    // uint32_t bytesTransferred = 0;
    //
    // deviceRequest(this, request, &status, bytesTransferred, kUSBHostStandardRequestCompletionTimeout);
    
    // virtual IOUSBHostPipe* GetPipeZero() __attribute__((deprecated));
    // virtual IOUSBHostPipe* getPipeZero() __attribute__((deprecated));
    // Replacement: none.  Use deviceRequest(...) and abortDeviceRequests(...) interfaces to interact with the default endpoint

    // virtual IOReturn GetStringDescriptor(UInt8 index, char* buf, int maxLen, UInt16 lang = 0x409) __attribute__((deprecated));
    // Replacement: getStringDescriptor(index, languageID)
    // Use sys/utfconv.h to extract UTF strings from string descriptors:
    // char stringBuffer[256] = { 0 };
    // size_t utf8len = 0;
    // const StringDescriptor* stringDescriptor = getStringDescriptor(index);
    // if(   stringDescriptor != NULL
    //    && stringDescriptor->bLength > StandardUSB::kDescriptorSize)
    // {
    //     utf8_encodestr(reinterpret_cast<const u_int16_t*>(stringDescriptor->bString), stringDescriptor->bLength - kDescriptorSize,
    //                    reinterpret_cast<u_int8_t*>(stringBuffer), &utf8len, sizeof(stringBuffer), '/', UTF_LITTLE_ENDIAN);
    // }

    // virtual const IOUSBDescriptorHeader* FindNextDescriptor(const void* cur, UInt8 descType) __attribute__((deprecated));
    // Replacement: StandardUSB::getNextDescriptor(getConfigurationDescriptor(currentConfig), cur, descType)

    // virtual IOReturn SuspendDevice(bool suspend) __attribute__((deprecated));
    // Replacement: forcePower(kPowerStateSuspended, false) or forcePower(kPowerStateOn, false)

    // virtual IOReturn ReEnumerateDevice(UInt32 options) __attribute__((deprecated));
    // Replacement: reset()

    // virtual IOReturn GetDeviceInformation(UInt32* info) __attribute__((deprecated));
    // Replacement: getPortStatus()

    // virtual UInt32 RequestExtraPower(UInt32 type, UInt32 requestedPower) __attribute__((deprecated));
    // virtual IOReturn ReturnExtraPower(UInt32 type, UInt32 returnedPower) __attribute__((deprecated));
    // TODO: Replacement

    // virtual tUSBHostDeviceAddress GetAddress(void) __attribute__((deprecated));
    // Replacement: getAddress()
    
    // virtual IOReturn ResetDevice() __attribute__((deprecated));
    // virtual UInt32 GetExtraPowerAllocated(UInt32 type) __attribute__((deprecated));
    // virtual void ForceIdlePolicy(UInt32 deviceIdleTimeout, UInt32 ioIdleTimeout) __attribute__((deprecated));
    // void SetBusPowerAvailable(UInt32 newPower) __attribute__((deprecated));
    // Replacement: none

protected:
    enum
    {
        kClientsDefaultCapacity          = 16,
        kPowerChildrenDefaultCapacity    = 16,
        kSetConfigurationIORetries       = 3,
        kSetConfigurationIORetryInterval = 100
    };

    AppleUSBHostRequestCompleter*            _requestCompleter;
    AppleUSBHostSynchronousRequestCompleter* _synchronousRequestCompleter;
    AppleUSBHostDeviceIdler*                 _deviceIdler;
    tUSBHostDeviceAddress                    _address;
    IOUSBHostPipe*                           _pipeZero;
    UInt8                                    _speed;
    StandardUSB::EndpointDescriptor          _endpointZero;
    IOBufferMemoryDescriptor**               _configList;
    uint32_t                                 _configListCount;
    uint8_t                                  _currentConfigValue;
    bool                                     _setConfigurationInProgress;
    uint32_t                                 _configurationBusCurrent; // mA
    uint32_t                                 _allocatedWakeBusCurrent; // mA
    uint32_t                                 _allocatedSleepBusCurrent;// mA
    uint32_t                                 _pendingCloseCount;
    
    uint32_t _debugLoggingMask;

    struct tExpansionData
    {
    };

    tExpansionData* _expansionData;

private:
    enum
    {
        kForcePowerTimeoutMs  = 1000ULL,      // Milliseconds
        kSuspendDeviceTimeout = 1000ULL,      // Milliseconds
        kTerminationTimeout   = 5000ULL       // Milliseconds
    };
};

#endif // IOUSBHostFamily_IOUSBHostDevice_h
