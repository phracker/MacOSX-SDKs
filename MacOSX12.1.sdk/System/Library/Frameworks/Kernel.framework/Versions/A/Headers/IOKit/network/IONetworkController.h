/*
 * Copyright (c) 1998-2008 Apple Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * The contents of this file constitute Original Code as defined in and
 * are subject to the Apple Public Source License Version 1.1 (the
 * "License").  You may not use this file except in compliance with the
 * License.  Please obtain a copy of the License at
 * http://www.apple.com/publicsource and read it before using this file.
 * 
 * This Original Code and all software distributed under the License are
 * distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE OR NON-INFRINGEMENT.  Please see the
 * License for the specific language governing rights and limitations
 * under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */

#ifndef _IONETWORKCONTROLLER_H
#define _IONETWORKCONTROLLER_H

/*! @defined kIONetworkControllerClass
    @abstract The name of the IONetworkController class. */

#define kIONetworkControllerClass   "IONetworkController"

/*! @defined kIOVendor
    @abstract A property of IONetworkController objects.
    @discussion The kIOVendor property is a property of IONetworkController objects.  It has an OSString value 	that describes the vendor of the network controller. */

#define kIOVendor                "IOVendor"

/*! @defined kIOModel
    @abstract A property of IONetworkController objects.
    @discussion The kIOModel property is a property of IONetworkController objects.  It has an OSString value that 	describes the model of the network controller. */

#define kIOModel                 "IOModel"

/*! @defined kIORevision
    @abstract A property of IONetworkController objects.
    @discussion The kIORevision property is a property of IONetworkController objects.  It has an OSString value 	that describes the revision level of the network controller. */

#define kIORevision              "IORevision"

/*! @defined kIOFeatures
    @abstract A property of IONetworkController objects.
    @discussion The kIOFeatures property is a property of IONetworkController objects. It has an OSNumber value 	that describes generic features defined by IONetworkController that are supported by the
        network controller. */

#define kIOFeatures              "IOFeatures"

/*! @defined kIOMediumDictionary
    @abstract A property of IONetworkController objects.
    @discussion The kIOMediumDictionary property is a property of IONetworkController
        objects.  It has an OSDictionary value that is a container for the
        collection of IONetworkMedium objects that represent the media
        types supported by the network controller.
        Each entry in the dictionary is a key/value pair consisting of
        the medium name, and a dictionary value that contains the
        properties for that medium entry. */

#define kIOMediumDictionary      "IOMediumDictionary"

/*! @defined kIODefaultMedium
    @abstract A property of IONetworkController objects.
    @discussion The kIODefaultMedium property is a property of IONetworkController
        objects.  It has an OSString value that describes the name of the
        default medium. This definition may change or disappear in the
        future. */

#define kIODefaultMedium         "IODefaultMedium"

/*! @defined kIOSelectedMedium
    @abstract A property of IONetworkController objects.
    @discussion The kIOSelectedMedium property is a property of IONetworkController
        objects.  It has an OSSymbol value that describes the name of the
        current selected medium. This name can be used as a key into the
        medium dictionary to gather additional information about the
        selected medium. */

#define kIOSelectedMedium         "IOSelectedMedium"

/*! @defined kIOActiveMedium
    @abstract A property of IONetworkController objects.
    @discussion The kIOActiveMedium property is a property of IONetworkController
        objects.  It has an OSSymbol value that describes the name of the
        active medium. This is the name of the medium where an active
        link has been established. This name can be used as a key into
        the medium dictionary to gather additional information about the
        active medium. */

#define kIOActiveMedium          "IOActiveMedium"

/*! @defined kIOLinkSpeed
    @abstract A property of IONetworkController objects.
    @discussion The kIOLinkSpeed property is a property of IONetworkController
        objects. It has an OSNumber value that describes the speed of the
    	link established over the active medium in bits per second. */

#define kIOLinkSpeed             "IOLinkSpeed"

/*! @defined kIOLinkStatus
    @abstract A property of IONetworkController objects.
    @discussion The kIOLinkStatus property is a property of IONetworkController
        objects. It has an OSNumber value that describes the current network
        link status. See IONetworkMedium for the definition of the link
        status bits. */

#define kIOLinkStatus            "IOLinkStatus"

/*! @defined kIOLinkData
    @abstract A property of IONetworkController objects.
    @discussion The kIOLinkData property is a property of IONetworkController
        objects. It has an OSData value that contains additional information
        describing the active link that was established.
        Its interpretation is not defined. */

#define kIOLinkData              "IOLinkData"

/*! @defined kIOPacketFilters
    @abstract A property of IONetworkController objects.
    @discussion The kIOPacketFilters property is a property of IONetworkController
        objects. It has an OSDictionary value that describes the entire
        set of packet filters supported by the controller. Each entry
        in the dictionary is a key/value pair consisting of the filter
        group name, and an OSNumber describing the set of supported
        filters for that group. */

#define kIOPacketFilters         "IOPacketFilters"

/*! @defined kIOMACAddress
    @abstract A property of IONetworkController objects.
    @discussion The kIOMACAddress property is a property of IONetworkController
        objects. It has an OSData value that describes the hardware
        MAC (media access controller) address, or station address,
        of the network controller. */

#define kIOMACAddress            "IOMACAddress"

/*! @defined kIOMaxPacketSize
    @abstract A property of IONetworkController objects.
    @discussion The kIOMaxPacketSize property is a property of IONetworkController
        objects. It has an OSNumber value that describes the maximum
        packet size supported by the controller. */

#define kIOMaxPacketSize         "IOMaxPacketSize"

/*! @defined kIOMinPacketSize
    @abstract A property of IONetworkController objects.
    @discussion The kIOMinPacketSize property is a property of IONetworkController
        objects. It has an OSNumber value that describes the minimum
        packet size supported by the controller. */

#define kIOMinPacketSize         "IOMinPacketSize"

/*! @defined kIONetworkFilterGroup
    @abstract The name assigned to the standard network filter group. */

#define kIONetworkFilterGroup    "IONetworkFilterGroup"

/*! @enum StandardPacketFilters
    @abstract All standard packet filters. 
    @discussion Each filter will allow the reception of certain class of packets
        depending on its destination MAC address.
    @constant kIOPacketFilterUnicast Reception of unicast packets.
    @constant kIOPacketFilterBroadcast Reception of broadcast packets.
    @constant kIOPacketFilterMulticast Reception of multicast packets
        addressed to a set of multicast addresses.
    @constant kIOPacketFilterMulticastAll Reception of all multicast
        packets.
    @constant kIOPacketFilterPromiscuous Reception of all packets.
    @constant kIOPacketFilterPromiscuousAll Reception of all packets,
        including bad packets. */

enum {
    kIOPacketFilterUnicast         = 0x1,
    kIOPacketFilterBroadcast       = 0x2,
    kIOPacketFilterMulticast       = 0x10,
    kIOPacketFilterMulticastAll    = 0x20,
    kIOPacketFilterPromiscuous     = 0x100,
    kIOPacketFilterPromiscuousAll  = 0x200
};

/*! @enum Network Feature Flags
    @abstract Feature flags returned by the getFeatures() method.
    @constant kIONetworkFeatureNoBSDWait Set this bit in the value
        returned by getFeatures() to disable the automatic wait for
        "IOBSD" resource by the IONetworkController::start() method. 
    @constant kIONetworkFeatureHardwareVlan Set this bit in the value
        returned by getFeatures() to indicate the controller supports hardware
        stripping and stuffing of 802.1q vlan tags.  If the controller supports
        this feature it must enable it when initializing so that all received
        packets delivered to higher layers have the tag stripped.  The controller
        should use setVlanTag() to provide the tag information out of band.
    @constant kIONetworkFeatureSoftwareVlan Set this bit in the value
        returned by getFeatures() to indicate that the controller can support software
        based vlan by transmitting and receiving packets 4 bytes longer that normal. 
    @constant kIONetworkFeatureMultiPages Set this bit if the driver is
	capable of handling packets coming down from the network stack that
	reside in virtually, but not in physically contiguous span of the
	external mbuf clusters.  In this case, the data area of a packet in
	the external mbuf cluster might cross one or more physical pages that
	are disjoint, depending on the interface MTU and the packet size.
	Such a use of larger than system page size clusters by the network
	stack is done for better system efficiency.  Drivers that utilize the
	IOMbufNaturalMemoryCursor with the getPhysicalSegmentsWithCoalesce
	interfaces and enumerate the list of vectors should set this flag
	for possible gain in performance during bulk data transfer.
    @constant kIONetworkFeatureTSOIPv4 Set this bit to advertise support
        for TCP/IPv4 segmentation offload.
    @constant kIONetworkFeatureTSOIPv6 Set this bit to advertise support
        for TCP/IPv6 segmentation offload.
    @constant kIONetworkFeatureTransmitCompletionStatus Set this bit to
        advertise the capability to report per-packet transmit completion status.
        See <code>IONetworkInterface::reportTransmitCompletionStatus</code>.
    @constant kIONetworkFeatureHWTimeStamp Set this bit to advertise
         the capability to compute per-packet timestamp in hardware.
    @constant kIONetworkFeatureHWTimeStamp Set this bit to advertise
        the capability to compute per-packet timestamp in software.
*/

enum {
    kIONetworkFeatureNoBSDWait                  = 0x001,
    kIONetworkFeatureHardwareVlan               = 0x002,
    kIONetworkFeatureSoftwareVlan               = 0x004,
    kIONetworkFeatureMultiPages                 = 0x008,
    kIONetworkFeatureTSOIPv4                    = 0x010,
    kIONetworkFeatureTSOIPv6                    = 0x020,
    kIONetworkFeatureTransmitCompletionStatus   = 0x040,
    kIONetworkFeatureHWTimeStamp                = 0x080,
    kIONetworkFeatureSWTimeStamp                = 0x100
};

#ifdef KERNEL
#ifdef __cplusplus

#include <IOKit/IOService.h>
#include <IOKit/IOWorkLoop.h>
#include <IOKit/network/IONetworkInterface.h>
#include <IOKit/network/IOKernelDebugger.h>

class  IOCommandGate;
class  IOOutputQueue;
class  IONetworkMedium;

/*! @typedef IOPacketBufferConstraints
    @discussion Constraint parameters, specified by a driver,
    for the data buffer in a packet mbuf. This is observed by
    allocatePacket() to satisfy the stated requirements.
    @field alignStart Starting address byte alignment.
    @field alignLength Buffer length byte alignment. */

typedef struct {
    UInt32  alignStart;
    UInt32  alignLength;
    UInt32  reserved[6];
} IOPacketBufferConstraints;

// Some frequently used alignment constants.
//
enum {
    kIOPacketBufferAlign1   = 1,
    kIOPacketBufferAlign2   = 2,
    kIOPacketBufferAlign4   = 4,
    kIOPacketBufferAlign8   = 8,
    kIOPacketBufferAlign16  = 16,
    kIOPacketBufferAlign32  = 32
};

/*!	@const gIONetworkFilterGroup
    @discussion gIONetworkFilterGroup is an OSSymbol object that contains
        the name of the standard network filter group as defined by
        kIONetworkFilterGroup. */

extern const OSSymbol *  gIONetworkFilterGroup;

/*! @class IONetworkController
    @abstract Implements the framework for a generic 
    network controller.
    @discussion A subclass of IONetworkController must provide
    additional functionality specific for a particular networking type.
    In addition, the driver must implement (override) a basic set of 
    hardware dependent methods to create a working driver.

    IONetworkController attaches itself to the data link layer (DLIL) via
    an IONetworkInterface object. A controller object without a companion
    interface is not accessible to the networking system. The controller
    interacts with DLIL by calling methods defined by the interface object.
    And conversely, DLIL will issue commands and packets to the controller
    through the interface object.

    IONetworkController will create an IOCommandGate and attach this
    event source to an IOWorkLoop object. All commands sent from the
    interface object are handled through the IOCommandGate object,
    which will serialize access to the controller. Outbound packets sent
    from the interface to the controller have no implicit serialization. 
    Drivers must implement an output function that is thread safe, or use
    an IOOutputQueue object which will provide a serialization model.

	Note: IONetworkController internally uses some private messaging constants
	in the sys_iokit | sub_iokit_networking range defined in 
	"IONetworkControllerPrivate.h".	If you create a client for your controller
	(for example an IOUserClient), and it overrides the IOService::message 
	method, your client may receive these messages.  It should ignore these 
	messages and pass them to super::message() 	
    */


class __exported IONetworkController : public IOService
{
    OSDeclareAbstractStructors( IONetworkController )

private:

    IOWorkLoop *             _workLoop;
    IOCommandGate *          _cmdGate;
    IOOutputQueue *          _outputQueue;
    OSSet *                  _clientSet;
    OSCollectionIterator *   _clientSetIter;
    OSObject *               _cmdClient;
    UInt32                   _alignStart;
    UInt32                   _alignLength;
    UInt32                   _alignPadding;
    bool                     _propertiesPublished;
    IOLock *                 _mediumLock;
    IODebuggerLockState      _debugLockState;
    SInt32                   _debugLockCount;
    OSNumber *               _linkStatus;
    OSNumber *               _linkSpeed;
    const OSData *           _lastLinkData;
    const OSSymbol *         _lastActiveMediumName;
    const OSSymbol *         _lastCurrentMediumName;
    mbuf_t                   _freeList;

    struct ExpansionData { };
    /*! @var reserved
        Reserved for future use.  (Internal use only)  */
    ExpansionData *	    _reserved;


    bool _broadcastEvent(UInt32 type, void * data = 0);

    static void debugRxHandler(IOService * handler,
                               void *      buffer,
                               UInt32 *    length,
                               UInt32      timeout);

    static void debugTxHandler(IOService * handler,
                               void *      buffer,
                               UInt32      length);

    static UInt32 debugLinkStatusHandler(IOService * handler);
    static bool debugSetModeHandler(IOService * handler, bool active);

    static IOReturn executeCommandAction(OSObject * owner,
                                         void *     arg0,
                                         void *     arg1,
                                         void *     arg2,
                                         void *     arg3);

    static IOReturn handleCommand(void * target,
                                  void * param0,
                                  void * param1,
                                  void * param2,
                                  void * param3);

public:

/*! @function init
    @abstract Initializes the IONetworkController object.
    @discussion Instance variables are initialized, then super::init()
    is called.
    @param properties A dictionary object containing a property table
        associated with this instance.
    @result Returns true on success, false otherwise. 
*/ 

    virtual bool init(OSDictionary * properties) APPLE_KEXT_OVERRIDE;

/*! @function start
    @abstract Starts the network controller.
    @discussion After the controller driver has successfully matched
    to a provider, this method is called to start the network controller. 
    IONetworkController will allocate resources and gather controller
    properties in its implementation. No I/O will be performed until
    the subclass tries to attach a client object. A driver must override
    this method, and call super::start() at the beginning of its own
    implementation. Then check the return value to make sure that its
    superclass was started successfully before proceeding. Tasks that
    are usually performed by a driver's start method are: resource
    allocation, hardware initialization, allocation of IOEventSources
    and attaching them to a workloop, publishing a medium dictionary,
    and finally, attaching an interface object when it is ready to
    handle client requests.
    @param provider The provider that the controller was matched
    (and attached) to.
    @result Returns true on success, false otherwise. 
*/

    virtual bool start(IOService * provider) APPLE_KEXT_OVERRIDE;

/*! @function stop
    @abstract Stops the network controller.
    @discussion The counterpart of start(). The controller has been
    instructed to stop running. The stop() method should release
    resources and undo actions performed by the start() method.
    Subclasses must override this method and call super::stop()
    at the end of its implementation.
    @param provider The provider that the controller was matched
    (and attached) to. */

    virtual void stop(IOService * provider) APPLE_KEXT_OVERRIDE;

/*! @function message
    @abstract Receives messages delivered from an attached provider.
    @discussion Handles the <code>kIOMessageDeviceSignaledWakeup</code> message
    from a provider identifying the IONetworkController as the wakeup source.
    @param type A type defined in <code>IOMessage.h</code>.
    @param provider The provider from which the message originates.
    @param argument An argument defined by the message type.
    @result An IOReturn code defined by the message type.
*/

    virtual IOReturn message(
        UInt32 type, IOService * provider, void * argument ) APPLE_KEXT_OVERRIDE;

/*! @typedef IONetworkController::Action
    @discussion Definition of a C function that can be called
    through executeCommand().
    @param target The first argument passed to action.
    @param param0 Action parameter 0.
    @param param1 Action parameter 1.
    @param param2 Action parameter 2.
    @param param3 Action parameter 3. */

    typedef IOReturn (*Action)(void * target, void * param0,
                                              void * param1,
                                              void * param2,
                                              void * param3);

/*! @function executeCommand
    @abstract Makes a C function call through the command gate.
    @discussion This method makes a call to a C function that will be synchronized 
    with the workloop thread, and any other threads that are called
    with the workloop's gate closed.
    @param client The client requesting the action. This parameter is not
    passed to the function.
    @param action Pointer to a C function to be executed.
    @param target The first parameter in the action callout.
    @param param0 Action parameter 0.
    @param param1 Action parameter 1.
    @param param2 Action parameter 2.
    @param param3 Action parameter 3.
    @result Returns the value returned by the action. 
*/

    virtual IOReturn executeCommand(OSObject * client,
                                    Action     action,
                                    void *     target,
                                    void *     param0 = 0,
                                    void *     param1 = 0,
                                    void *     param2 = 0,
                                    void *     param3 = 0);

/*! @function outputPacket
    @abstract Transmits an output packet.
    @discussion If an IOOutputQueue was created by createOutputQueue(),
    then this method will be called by the output queue object.
    Otherwise, an interface object will call this method directly when
    it receives an output packet from the data link layer.

    There is no upper limit on the number of mbufs, hence the number of
    memory fragments, in the mbuf chain provided. Drivers must be able to
    handle cases when the mbuf count might exceed the limit supported by their
    DMA engines, and perform coalescing to copy the various memory fragments
    into a lesser number of fragments. This complexity can be hidden from
    the driver when an IOMbufMemoryCursor is used, which is able to convert
    an mbuf chain into a physical address scatter-gather list that will not
    exceed a specified number of physically contiguous memory segments.
    See IOMbufMemoryCursor.

    The implementation in IONetworkController performs no useful action
    and will drop all packets. A driver must override this method and
    process the output packet provided. The implementation in the driver
    must not block, since this may cause the network stack to be reentered
    from an unsafe point.
    @param mbuf_t An mbuf chain containing the output packet to be sent on
    the network.
    @param param A parameter provided by the caller.
    @result Returns a return code defined by the caller. 
*/

    virtual UInt32 outputPacket(mbuf_t m, void * param);

/*! @function getFeatures
    @abstract Reports generic features supported by the controller and/or
    the driver.
    @result This method will always return 0. Subclasses may override
    this method and return a bit mask of all supported features. */

    virtual UInt32 getFeatures() const;

/*! @function newVendorString
    @result Returns a string describing the vendor of the network controller.
    The caller is responsible for releasing the string object returned. */

    virtual const OSString * newVendorString() const;

/*! @function newModelString
    @result Returns a string describing the model of the network controller.
    The caller is responsible for releasing the string object returned. */

    virtual const OSString * newModelString() const;

/*! @function newRevisionString
    @result Returns a string describing the hardware revision of the
    network controller. The caller is responsible for releasing the
    string object returned. */

    virtual const OSString * newRevisionString() const;

/*! @function getSelectedMedium
    @abstract Gets the current selected medium.
    @discussion If the driver has previously called setSelectedMedium() 
    to indicate its current media selection, then this method will return
    that medium object. Otherwise, the driver's property table is
    consulted and a default medium property is examined, and the
    corresponding entry in the medium dictionary is returned.
    @result Returns the current selected medium, the default medium, or 0. 
*/

    virtual const IONetworkMedium * getSelectedMedium() const;
	const IONetworkMedium * getCurrentMedium() const;

/*! @function getMediumDictionary
    @abstract Returns the medium dictionary published by the driver.
    @discussion Returns the medium dictionary published by the driver
    through publishMediumDictionary(). Use copyMediumDictionary() to
    create and get a copy of the medium dictionary.
    @result Returns the published medium dictionary, or 0 if the driver has not
    yet published a medium dictionary through publishMediumDictionary(). 
*/

    virtual const OSDictionary * getMediumDictionary() const;

/*! @function copyMediumDictionary
    @abstract Returns a copy of the medium dictionary published by the
    driver.
    @discussion The caller is responsible for releasing the dictionary
    object returned. Use getMediumDictionary() to get a reference to the
    published medium dictionary instead of creating a copy.
    @result Returns a copy of the medium dictionary, or 0 if the driver has not
    published a medium dictionary through publishMediumDictionary().
*/

    virtual OSDictionary * copyMediumDictionary() const;

/*! @function getOutputHandler
    @abstract Gets the address of the method designated to handle output 
    packets for the network controller.
    @result Returns a pointer to the outputPacket() method. 
*/

    virtual IOOutputAction getOutputHandler() const;

/*! @function doEnable
    @abstract Makes a synchronized call to enable() through executeCommand().
    @discussion Do not use this method, it may be removed in the future.
    See enable(). 
*/

    virtual IOReturn doEnable(IOService * client);

/*! @function doDisable
    @abstract Makes a synchronized call to disable() through executeCommand().
    @discussion Do not use this method, it may be removed in the future.
    See disable(). 
*/

    virtual IOReturn doDisable(IOService * client);

/*! @function getCommandGate
    @abstract Gets the IOCommandGate object created by IONetworkController.
    @discussion When IONetworkController is started, an IOCommandGate object
    is instantiated and attached to the workloop returned by getWorkLoop().
    This IOCommandGate object is used internally to synchronize client
    commands handled through executeCommand(). Subclasses that need an
    IOCommandGate should try to reuse the object returned by this method,
    rather than creating a new instance. See IOCommandGate documentation.
    @result Returns the IOCommandGate object created by IONetworkController. 
*/

    virtual IOCommandGate * getCommandGate() const;

/*! @function getHardwareAddress
    @abstract Gets the network controller's permanent hardware/station
    address. 
    @discussion This method call is synchronized by the workloop's gate.
    @param addr The buffer where the controller's hardware address should
           be stored.
    @param inOutAddrBytes The size of the address buffer provided by the
           client, and replaced by this method with the actual size of
           the hardware address in bytes.
    @result Returns kIOReturnSuccess on success, or an error otherwise. 
*/

    virtual IOReturn getHardwareAddress(void *   addr,
                                        UInt32 * inOutAddrBytes) = 0;

/*! @function setHardwareAddress
    @abstract Sets or changes the station address used by the network
    controller. 
    @discussion This method call is synchronized by the workloop's gate.
    @param addr The buffer containing the hardware address provided by
    the client.
    @param addrBytes The size of the address buffer provided by the
    client in bytes.
    @result Returns kIOReturnSuccess on success, or an error otherwise. 
*/

    virtual IOReturn setHardwareAddress(const void * addr,
                                        UInt32       addrBytes) = 0;

/*! @function enable
    @abstract Handles an enable request from a client.
    @discussion This method handles an enable request from a client. A client will call
    enable after it has opened the controller, and before it starts to use
    the controller to send and to receive packets over the network. The
    client object provided is typecasted using OSDynamicCast, and depending
    on whether the client is an IOKernelDebugger or an IONetworkInterface,
    then an overloaded enable method that takes a more specific argument
    type is called. If the client matches neither type, then
    kIOReturnBadArgument is returned. A driver has the option of overriding
    this base enable method, or the overloaded form. This method call is
    synchronized by the workloop's gate.
    @param client The client object requesting the enable.
    @result Returns the return value from the overloaded enable() method, or
    kIOReturnBadArgument if the client type is unknown. 
*/

    virtual IOReturn enable(IOService * client);

/*! @function disable
    @abstract Handles a disable request from a client.
    @discussion This method handles a disable request from a client. A client will call
    disable if it has previously enabled the controller, and it no longer
    needs to transport packets or perform I/O using the controller.
    The client object is typecasted using OSDynamicCast, and depending on
    whether the client is an IOKernelDebugger or an IONetworkInterface,
    then an overloaded disable method that takes a more specific argument
    type is called. If the client matches neither type, then
    kIOReturnBadArgument is returned. A driver has the option of overriding
    this base disable method, or the overloaded form. This method call is
    synchronized by the workloop's gate.
    @param client The client object requesting the disable.
    @result Returns the return from the overloaded disable() method, or
    kIOReturnBadArgument if the client type is unknown.
*/
    
    virtual IOReturn disable(IOService * client);

/*! @function setMaxPacketSize
    @abstract A client request to change the maximum packet size.
    @discussion This method call is synchronized by the workloop's gate.
    @param maxSize The new maximum packet size.
    @result Returns kIOReturnUnsupported. Drivers may override this method
    and return either kIOReturnSuccess to indicate that the new size
    was accepted and is in effect, or an error code to indicate failure. 
*/

    virtual IOReturn setMaxPacketSize(UInt32 maxSize);

/*! @function getMaxPacketSize
    @abstract Gets the maximum packet size supported by the controller.
    @param maxSize Pointer to the return value.
    @result Returns kIOReturnSuccess on success, or an error code otherwise. 
*/

    virtual IOReturn getMaxPacketSize(UInt32 * maxSize) const = 0;

/*! @function getMinPacketSize
    @abstract Gets the minimum packet size supported by the controller.
    @param minSize Pointer to the return value.
    @result Returns kIOReturnSuccess on success, or an error code otherwise. 
*/

    virtual IOReturn getMinPacketSize(UInt32 * minSize) const = 0;

/*! @function selectMedium
    @abstract A client request to change the medium selection.
    @discussion This method is called when a client issues a command
    for the controller to change its current medium selection.
    The implementation must call setSelectedMedium() after the change
    has occurred. This method call is synchronized by the workloop's
    gate.
    @param medium An entry from the published medium dictionary that
    represents the selection chosen by the client.
    @result Returns kIOReturnUnsupported. Drivers may override this method and
    return kIOReturnSuccess if the selection was successful,
    or an error code otherwise. 
*/

    virtual IOReturn selectMedium(const IONetworkMedium * medium);

/*! @function selectMediumWithName
    @abstract A client request to change the medium selection.
    @discussion This method is called when a client issues a command
    for the controller to change its current medium selection.
    This implementation will look for an entry in the medium
    dictionary published by the driver that is associated with the
    key given. If a match is found, then selectMedium() is called to
    perform the selection, otherwise an error is reported back to the
    client. Subclasses should override selectMedium() and not this
    method. This method call is synchronized by the workloop's gate.
    @param mediumName An OSSymbol object that describes the name of the
    new medium selected by the client.
    @result Returns the return from selectMedium() if a matching entry was found
    from the medium dictionary. Returns kIOReturnUnsupported if a medium
    dictionary does not exist, or kIOReturnBadArgument if the name given
    does not match any entry in the medium dictionary. 
*/

    virtual IOReturn selectMediumWithName(const OSSymbol * mediumName);

/*! @function getPacketFilters
    @abstract Gets the set of packet filters supported by the network 
    controller for the given filter group.
    @discussion A subclass must implement this method and report the
    set of filters that are supported for the given filter group.
    This method call is synchronized by the workloop's gate.
    @param group The name of the filter group.
    @param filters Pointer to the mask of supported filters returned by
    	this method.
    @result Returns kIOReturnSuccess on success, or an error to indicate a
    failure to discover the set of supported filters. 
*/

    virtual IOReturn getPacketFilters(const OSSymbol * group,
                                      UInt32 *         filters) const = 0;

/*! @function enablePacketFilter
    @abstract Enables one of the supported packet filters from the
    given filter group.
    @discussion A client will call this method to enable a supported filter
    from the filter group specified. If the client wishes to enable more
    than one filter, it must call this method multiple times to enable the
    desired set of filters. This method call is synchronized by the
    workloop's gate.
    @param group The name of the filter group containing the filter to be
    enabled.
    @param aFilter The filter to enable.
    @param enabledFilters All filters currently enabled by the client.
    @param options Optional flags for the enable request.
    @result Returns kIOReturnSuccess on success, or an error otherwise. 
*/

    virtual IOReturn enablePacketFilter(const OSSymbol * group,
                                        UInt32           aFilter,
                                        UInt32           enabledFilters,
                                        IOOptionBits     options = 0) = 0;

/*! @function disablePacketFilter
    @abstract Disables a packet filter that is currently enabled from the
    given filter group.
    @discussion After a supported filter has been successfully enabled,
    a client can call this method to disable that filter. This method call
    is synchronized by the workloop's gate.
    @param group The name of the filter group containing the filter to be
    disabled.
    @param aFilter The filter to disable.
    @param enabledFilters All filters currently enabled by the client.
    @param options Optional flags for the disable request.
    @result Returns kIOReturnSuccess on success, or an error otherwise. 
*/

    virtual IOReturn disablePacketFilter(const OSSymbol * group,
                                         UInt32           aFilter,
                                         UInt32           enabledFilters,
                                         IOOptionBits     options = 0) = 0;

/*! @function getOutputQueue
    @abstract Gets the IOOutputQueue object created by createOutputQueue().
    @result Returns a reference to the output queue object created by
    createOutputQueue(). 
*/

    virtual IOOutputQueue * getOutputQueue() const;

/*! @function getPacketBufferConstraints
    @abstract Gets the controller's packet buffer constraints.
    @discussion Called by start() to obtain the constraints on the
    memory buffer for each mbuf packet allocated through allocatePacket().
    Drivers can override this method to specify the buffer constraints
    imposed by their bus master hardware. Note that outbound packets,
    those that originate from the network stack, are not currently
    subject to the constraints reported here.
    @param constraints A pointer to an IOPacketBufferConstraints
    structure that this method is expected to initialize.
    See IOPacketBufferConstraints structure definition. 
*/

    virtual void getPacketBufferConstraints(
                    IOPacketBufferConstraints * constraints) const;

/*! @function allocatePacket
    @abstract Allocates a packet with a data buffer that is larger than
    or equal to the size specified.
    @discussion This method will always return a single mbuf unless the
    size requested (plus the alignment padding) is greater than MCLBYTES.
    The data buffer for the mbuf (or an mbuf chain) returned is aligned
    according to the constraints reported by getPacketBufferConstraints().
    The length fields in each mbuf returned are set by this method, thus
    allowing the mbuf to be passed directly to an IOMbufMemoryCursor object
    in order to convert the mbuf to a physical address scatter-gather list.
    @param size The minimum size of the data buffer for the mbuf
    packet allocated.
    @result Returns an mbuf packet, or 0 if allocation failed. 
*/

    virtual mbuf_t allocatePacket(UInt32 size);

/*! @function copyPacket
    @abstract Allocates a new packet, containing data copied from an
    existing source packet.
    @discussion The source packet is not modified by this method.
    @param m The source packet.
    @param size The number of bytes to copy. If set to 0, then the
    entire data buffer from the source packet is copied.
    @result Returns a new packet containing the same data as the source packet. 
*/

    virtual mbuf_t copyPacket(const mbuf_t m, UInt32 size = 0);

/*! @function replacePacket
    @abstract Allocates a new packet to replace an existing packet, the
    existing packet is then returned.
    @param mp A handle to the existing packet.
    @param size If size is 0, then the new packet shall have the same buffer
    size as the original packet that is being replaced. Otherwise, the new
    packet shall have the buffer size specified by this value.
    @result If packet allocation was successful, then a replacement will
    take place and the original packet will be returned. Otherwise, 0
    is returned, and the original packet will be left untouched.
*/

    virtual mbuf_t replacePacket(mbuf_t * mp, UInt32 size = 0);

/*! @function replaceOrCopyPacket
    @abstract A helper method that combines the functionality of
    copyPacket() and replacePacket() to process a packet containing
    a received frame.
    @discussion This method will either make a copy or replace the existing
    packet, whichever is more time efficient. Packets containing small frames
    are copied, otherwise they are replaced. If replaced, then the existing
    packet is returned, and a new packet with the same buffer size is created
    to take its place. If copied, the existing packet is left intact, while a
    copy is returned that will hold a copy of the data from the source packet.
    @param mp A handle to the existing packet that may be replaced.
    @param length The number of bytes received held in the packet.
        Must be greater than zero.
    @param replaced Pointer to a return value that is set to true to indicate
        that the existing packet was replaced, or false to indicate that the
        existing packet was not replaced, and a copy was created.
    @result Returns a replacement or a copy of the existing packet, or 0 if packet
    allocation failed. 
*/

    virtual mbuf_t replaceOrCopyPacket(mbuf_t * mp,
                                       UInt32   length,
                                       bool *   replaced);

    enum {
        kDelayFree = 0x01
    };

/*! @function freePacket
    @abstract Releases the packet given back to the free pool.
    @param mbuf_t The packet to be freed.
    @param options When kDelayFree option is set, then the packet
    provided to this function will be queued on the free packet queue.
    A subsequent call to releaseFreePackets() will release all queued
    packets by making a single BSD function call. Without the kDelayFree
    option, the packet provided will be released immediately. 
*/

    virtual void freePacket(mbuf_t, IOOptionBits options = 0);

/*! @function releaseFreePackets
    @abstract Releases all packets held in the free packet queue.
    @discussion The free packet queue is not protected by a lock. This
    function must be called in a single-threaded manner with respect to
    all calls to freePacket() with the kDelayFree option set.
    @result Returns the number of packets queued and released. 
*/

    virtual UInt32 releaseFreePackets();

/*! @enum TCP/IP Checksums
    @abstract TCP/IP checksums that may be supported by the
    hardware.
    @constant kChecksumFamilyTCPIP A value that describes the collection
    of TCP/IP checksums.
    @constant kChecksumIP An IP header checksum.
    @constant kChecksumTCP A TCP checksum that covers the TCP header and TCP
    data.
    @constant kChecksumUDP A UDP checksum that covers the UDP header and UDP
    data.
    @constant kChecksumTCPIPv6 A TCP checksum that covers the IPv6 pseudo header,
    TCP header and TCP data.
    @constant kChecksumUDPIPv6 A UDP checksum that covers the IPv6 pseudo header,
    UDP header and UDP data.
    @constant kChecksumTCPNoPseudoHeader A TCP checksum that covers the TCP
    header and the TCP data, but the pseudo header is not included in the
    checksum computation. A partial 16-bit checksum value must be provided
    to allow the protocol stacks to calculate and verify the final checksum.
    This type of checksum is not currently supported on the output path.
    @constant kChecksumUDPNoPseudoHeader A UDP checksum that covers the UDP
    header and the UDP data, but the pseudo header is not included in the
    checksum computation. A partial 16-bit checksum value must be provided
    to allow the protocol stacks to calculate and verify the final checksum.
    This type of checksum is not currently supported on the output path.
    @constant kChecksumTCPSum16 The hardware has a simple checksum engine
    that can perform a TCP style ones complement sum of 16-bit words over 
    a certain range of bytes in a packet. The hardware does not have the
    ability to scan for IP or TCP headers, and the driver must pass/get
    additional parameter(s) to or from the protocol stack to coordinate
    the checksumming effort. 
*/

    enum {
        kChecksumFamilyTCPIP         = 0x00000001,
        kChecksumIP                  = 0x0001,
        kChecksumTCP                 = 0x0002,
        kChecksumUDP                 = 0x0004,
        kChecksumTCPIPv6             = 0x0020,
        kChecksumUDPIPv6             = 0x0040,
        kChecksumTCPNoPseudoHeader   = 0x0100,
        kChecksumUDPNoPseudoHeader   = 0x0200,
        kChecksumTCPSum16            = 0x1000
    };

/*! @function getChecksumSupport
    @abstract Gets checksums that are supported by the network controller for
    the given checksum family.
    @discussion A network controller that is capable of inserting and verifying
    checksums on output and input packets, should override this method and
    advertise its capability in order to assist or offload the software checksum
    calculations performed by the protocol stacks.
    @param checksumMask A pointer to the mask of supported checksums returned
    by this method.
    @param checksumFamily A value that specifies the checksum family.
    @param isOutput Set to true to query the support for checksum insertion on
    output packets, or false to query the support for checksum verification
    on input packets. Controllers that have symmetric hardware checksum support 
    can return a fixed checksum mask value, and ignore this argument.
    @result Default return is kIOReturnUnsupported. Controllers that override
    this method must return kIOReturnSuccess. Any other return value will be
    interpretated as a lack of checksum support, regardless of the value
    returned through the first argument. 
*/

    virtual IOReturn getChecksumSupport( UInt32 * checksumMask,
                                         UInt32   checksumFamily,
                                         bool     isOutput );

/*! @function setChecksumResult
    @abstract Encodes a received packet with the checksum result reported
    by the hardware.
    @discussion A network controller that can verify the checksum(s) for a
    received packet, should call this method to encode the result on the
    packet, before passing it up towards the protocol stacks.
    @param packet An mbuf containing a packet that has been checksummed by
    the hardware.
    @param checksumFamily A value that specifies the checksum family.
    @param resultMask A mask of all checksums that were checked or computed.
    Setting a bit implies that the driver is able to report the result of
    the checksum computation, by asserting the validity of the checksum,
    or by returning a partial checksum value.
    @param validMask A mask of all checksums are were computed and verified
    by the hardware as valid. Certain types of checksum performed by the
    hardware are inheritely incomplete, and therefore should never be marked
    as valid. A checksum cannot be marked valid unless it has also been
    checked.
    @param param0 Optional parameter 0, defaults to 0.
    @param param1 Optional parameter 1, defaults to 0.
    @result Returns true if the checksum family is valid and the packet has been
    encoded with the checksum result provided, false otherwise. 
*/

    virtual bool setChecksumResult( mbuf_t  packet,
                                    UInt32  checksumFamily,
                                    UInt32  resultMask,
                                    UInt32  validMask,
                                    UInt32  param0 = 0,
                                    UInt32  param1 = 0 );

/*! @function getChecksumDemand
    @abstract Fetches the demand for hardware checksum computation and insertion
    for the given packet before it is transmitted on the network.
    @discussion A network controller that can insert a checksum for output
    packets must call this method to obtain the set of checksums that it must
    compute, and insert into the appropriate fields in the given output packet.
    @param packet An mbuf containing a packet that may be missing one or more
    checksums in the specified checksum family.
    @param checksumFamily A value that specifies the checksum family.
    @param demandMask A mask of all checksums that the hardware must compute
    and insert into the appropriate checksum fields in the packet.
    @param param0 Optional parameter 0, defaults to 0.
    @param param1 Optional parameter 1, defaults to 0. 
*/

    virtual void getChecksumDemand( const mbuf_t packet,
                                    UInt32       checksumFamily,
                                    UInt32 *     demandMask,
                                    void *       param0 = 0,
                                    void *       param1 = 0 );

/*! @function publishMediumDictionary
    @abstract Publishes a dictionary of IONetworkMedium objects to
    advertise the media selection supported by the network controller.
    @discussion Called by drivers to publish their medium dictionary.
    Each entry in the dictionary is an IONetworkMedium object that
    represents a single medium that is supported by the controller.
    This method will make a copy of the dictionary provided, then add
    the copy to the driver's property table. The dictionary provided
    can be released by the caller upon returning from this method.
    It is permissible to call this method multiple times, which may be
    necessary if the hardware's media capability changes dynamically.
    However, if the capability is static, which is often the case,
    then a driver will typically call this method only once from
    its start() method.

    Several methods depend on the presence of a medium dictionary.
    They should be called after the medium dictionary has been
    published. Those methods are:
        setSelectedMedium()
        getSelectedMedium()
        getMediumDictionary()
        copyMediumDictionary()

    @param mediumDict A dictionary of IONetworkMedium objects.
    @result Returns true if the dictionary is valid, and was successfully
    exported to the property table, false otherwise. 
*/

    virtual bool publishMediumDictionary(const OSDictionary * mediumDict);

/*! @function setSelectedMedium
    @abstract Designates an entry in the published medium dictionary as
    the current selected medium.
    @discussion After the driver has configured the hardware to select
    one of its supported media types, it must call this method to inform
    its parent about the change that has occurred. IONetworkController
    will update a property in the registry to reflect the current selection.
    @param medium A medium object representing the current selection.
    @result Returns true if the property table update was successful,
    false if the update failed, or if the medium provided does not match
    any entry from the published medium dictionary. 
*/

    virtual bool setSelectedMedium(const IONetworkMedium * medium);
    bool setCurrentMedium(const IONetworkMedium * medium);

/*! @function setLinkStatus
    @abstract Reports the link status and the active medium.
    @discussion Drivers must call this method when a link change is
    detected. IONetworkController will update the link status properties
    in the registry, and generate an event to inform the upper layers
    about the change.
    @param status Link status bits.
           See IONetworkMedium for the definition of the link status bits.
    @param activeMedium An object in the published medium dictionary
    	   that represents the active medium. This may not be the same as
    	   the selected medium. Set this to 0 if the link is inactive.
    @param speed Link speed in units of bits per second. If zero, then
           the link speed is taken from the medium object provided.
    @param data An OSData containing any additional link parameter that
           the driver wishes to publish to the registry.
    @result Returns true if all link properties were successfully updated,
    false otherwise. 
*/

    virtual bool setLinkStatus(
                           UInt32                  status,
                           const IONetworkMedium * activeMedium = 0,
                           UInt64                  speed        = 0,
                           OSData *                data         = 0);

/*! @function systemWillShutdown
    @abstract Handles system shutdown and restart notifications.
    @discussion Overrides <code>IOService::systemWillShutdown</code> in order
    to notify network clients that the power-managed controller should be disabled.
    As a result, drivers can expect their <code>disable</code> method to be called
    before system shutdown or restart. This implementation is synchronous and can
    block before calling <code>IOService::systemWillShutdown</code> and return.
    @param specifier
	<code>kIOMessageSystemWillPowerOff</code> or <code>kIOMessageSystemWillRestart</code>.
    @see //apple_ref/cpp/instm/IOService/systemWillShutdown/void/(IOOptionBits) IOService::systemWillShutdown
*/

    virtual void systemWillShutdown( IOOptionBits specifier ) APPLE_KEXT_OVERRIDE;

    /* Override IOService::setAggressiveness() */

    virtual IOReturn setAggressiveness(
            unsigned long type, unsigned long newLevel ) APPLE_KEXT_OVERRIDE;

protected:

/*! @function free
    @abstract Frees the IONetworkController object.
    @discussion Frees the IONetworkController object by releasing all
    allocated resources, followed by a call to super::free(). 
*/

    virtual void free() APPLE_KEXT_OVERRIDE;

/*! @function registerWithPolicyMaker
    @abstract Implemented by controller drivers to register with
    the power management policy-maker.
    @discussion Drivers that are able to power manage their hardware
    should override this method and register with the policy-maker
    provided by calling IOService::registerPowerDriver().
    IONetworkController will call this method before the initial
    attempt is made to attach a client.
    @param policyMaker The policy-maker chosen to manage power for
    this network controller.
    @result Returns kIOReturnSuccess on success, kIOReturnUnsupported if the
    driver does not support power management, or an appropriate error
    return code. The default return is kIOReturnUnsupported. */

    virtual IOReturn registerWithPolicyMaker(IOService * policyMaker);

/*! @function createWorkLoop
    @abstract Method called by IONetworkController prior to the initial
    getWorkLoop() call.
    @discussion Before IONetworkController calls getWorkLoop() in its
    start() method, it will call createWorkLoop() to make sure that a
    subclass that wants to create a workloop, will do so before its
    first use.
    @result Returns true to indicate success, false otherwise. Returning false
    will fail IONetworkController::start(). 
*/

    virtual bool createWorkLoop();

/*! @function prepare
    @abstract Prepares the controller before an IOService is created and
    attached as a client.
    @discussion This method is called by attachInterface() or
    attachDebuggerClient() to prepare the controller before the new client
    object is attached. This method will call publishProperties() to publish
    controller capabilities and properties that may be used by client objects.
    However, publishProperties() will be called only once, even if prepare()
    is called multiple times. This method call is synchronized by the
    workloop's gate.
    @result Returns kIOReturnSuccess on success, or an error code otherwise.
        Returning an error will fail the client attach. 
*/

    virtual IOReturn prepare();

/*! @function publishProperties
    @abstract Publishes controller properties and capabilities.
    @discussion Called by IONetworkController to discover controller
    properties, and publish them to the property table in the I/O Kit
    Registry. This method is called once by prepare().
    @result Returns true if all properties were discovered and published
    successfully, false otherwise. Returning false will prevent client
    objects from attaching to the controller, since a property that
    a client relies upon may be missing. */

    virtual bool publishProperties();

/*! @function getCommandClient
    @abstract Gets the command client object.
    @discussion Methods called on the workloop context to service a
    client request can call this method to get the client object that
    initiated the command.
    @result Returns the command client. If the caller is not running on the
    workloop thread, or if the thread does not have the workloop's gate
    closed, then 0 is returned. 
*/

    virtual OSObject * getCommandClient() const;

/*! @function handleOpen
    @abstract Handles a client open.
    @discussion This method handles a client open on the controller object. IOService
    calls this method with the arbitration lock held. Subclasses
    should not override this method.
    @param client The client that is attempting to open the controller.
    @param options Not used. See IOService.
    @param argument Not used. See IOService.
    @result Returns true to accept the client open, false to refuse it. 
*/

    virtual bool handleOpen(IOService *  client,
                            IOOptionBits options,
                            void *       argument) APPLE_KEXT_OVERRIDE;

/*! @function handleClose
    @abstract Handles a client close.
    @discussion This method handles a close from one of the client objects. IOService
    calls this method with the arbitration lock held. Subclasses
    should not override this method.
    @param client The client that is closing the controller.
    @param options Not used. See IOService. 
*/

    virtual void handleClose(IOService * client, IOOptionBits options) APPLE_KEXT_OVERRIDE;

/*! @function handleIsOpen
    @abstract Queries whether a client has an open on the controller.
    @discussion This method is always called by IOService with the
    arbitration lock held. Subclasses should not override this method.
    @result Returns true if the specified client, or any client if none (0) is
    specified, presently has an open on this object. 
*/

    virtual bool handleIsOpen(const IOService * client) const APPLE_KEXT_OVERRIDE;

/*! @function enable
    @abstract A request from an interface client to enable the controller.
    @discussion This method is called by an interface client to enable the controller.
    Upon receiving this command, the controller driver must bring up the
    hardware and become ready to transmit and receive packets. A driver
    should also delay the allocation of most runtime resources until this
    method is called in order to conserve system resources. This method call
    is synchronized by the workloop's gate.
    @param interface The interface client object that requested the enable.
    @result Returns kIOReturnUnsupported. Drivers that override this method must
    return kIOReturnSuccess on success, or an error code otherwise. 
*/

    virtual IOReturn enable(IONetworkInterface * interface);

/*! @function disable
    @abstract A request from an interface client to disable the controller.
    @discussion This method is called by an interface client to disable the controller.
    This method should stop the hardware and disable hardware interrupt
    sources. Any resources allocated by enable() should also be deallocated.
    This method call is synchronized by the workloop's gate.
    @param interface The interface object that requested the disable.
    @result kIOReturnUnsupported. Drivers that override this method must
    return Returns kIOReturnSuccess on success, or an error code otherwise. 
*/

    virtual IOReturn disable(IONetworkInterface * interface);

/*! @function attachInterface
    @abstract Attaches a new network interface client object.
    @discussion This method creates a new network interface object and attaches
    it as a client of the controller. The <code>createInterface()</code> method
    is used to allocate and to initialize the interface, followed by a call to
    <code>configureInterface()</code> to configure the interface. Subclasses
    may override those two methods to customize the new interface object.
    Before this method returns, <code>registerService()</code> is called on the
    interface to start matching, which will ultimately attach the interface
    to the networking stack.
    Drivers will typically call this method from their <code>start()</code>
    method after they are ready to process interface requests. This has the
    desirable effect of preventing the <code>busyState</code> at the IOService
    root from becoming zero before the interface object has completed matching,
    which then holds off the user process that is waiting for I/O Kit to become
    quiet before assigning BSD names to all interfaces. Drivers that are unable
    to trigger interface matching synchronously from their <code>start()</code>
    method should instead call <code>adjustBusy</code> to manually increment
    the <code>busyState</code>, then followed by a <code>busyState</code> 
    decrement after attaching and registering the interface, or after a
    reasonable timeout.
    @param interface Upon success (return value is <code>true</code>), the
    pointer to the interface object will be written to the argument provided.
    @param doRegister If true, start interface matching before returning.
    Drivers can pass <code>false</code> to postpone interface matching, then
    register the interface when ready.
    @result Returns <code>true</code> on success, <code>false</code> otherwise. 
*/

    virtual bool attachInterface(IONetworkInterface ** interface,
                                 bool                  doRegister = true);

/*! @function detachInterface
    @abstract Detaches an interface client object.
    @discussion This method will verify that the object provided is indeed
    an IONetworkInterface instance, and then call its terminate() method.
    Note that an interface object will close and detach from its 
    controller after the data link layer has removed all references to 
    all data structures exposed by the interface. The interface object
    should be released following this call.
    @param interface An interface object to be detached and terminated.
    @param sync If true, the interface is terminated synchronously.
           This may cause this method to block for an indeterminate
           amount of time. */

    virtual void detachInterface(IONetworkInterface * interface,
                                 bool                 sync = false);

/*! @function createInterface
    @abstract Creates a new network interface object.
    @discussion This method is called by attachInterface() to perform
    allocation and initialization of a new interface object. A subclass of
    IONetworkController must implement this method and return a matching
    interface object. For example, IOEthernetController's implementation
    will return an IOEthernetInterface object when createInterface() is
    called.
    @result Returns a newly allocated and initialized interface object. 
*/

    virtual IONetworkInterface * createInterface() = 0;

/*! @function configureInterface
    @abstract Configures a newly created network interface object.
    @discussion This method configures an interface object that was created by
    createInterface(). Subclasses can override this method to customize
    and examine the interface object that will be attached to the
    controller as a client.
    @param interface The interface object to be configured.
    @result Returns true if the operation was successful, false otherwise
    (this will cause attachInterface() to fail and return 0). 
*/

    virtual bool configureInterface(IONetworkInterface * interface);

/*! @function createOutputQueue
    @abstract Creates an IOOutputQueue to handle output packet queueing,
    and also to resolve contention for the controller's transmitter from
    multiple client threads.
    @discussion This method is called by start() to create an IOOutputQueue object to
    handle output packet queueing. The default implementation will always
    return 0, hence no output queue will be created. A driver may override
    this method and return a subclass of IOOutputQueue. IONetworkController
    will keep a reference to the queue created, and will release this
    object when IONetworkController is freed. Also see getOutputQueue().
    @result Returns a newly allocated and initialized IOOutputQueue object. 
*/

    virtual IOOutputQueue * createOutputQueue();

/*! @function enable
    @abstract An enable request from an IOKernelDebugger client.
    @discussion Drivers that provide debugging support may either override
    this method and set up the hardware to support the polled-mode send and
    receive methods, receivePacket() and sendPacket(), or override the base
    enable() and disable() methods that take an IOService argument.
    @param debugger The IOKernelDebugger client requesting the enable.
    @result Returns kIOReturnSuccess. Drivers must return kIOReturnSuccess
    on success, or an error otherwise. 
*/

    virtual IOReturn enable(IOKernelDebugger * debugger);

/*! @function disable
    @abstract A disable request from an IOKernelDebugger client.
    @discussion Drivers that provide debugging support may either override
    this method to disable support for the polled-mode send and receive
    methods, or override the base enable() and disable() methods that
    take an IOService argument.
    @param debugger The IOKernelDebugger client requesting the disable.
    @result Returns kIOReturnSuccess. Drivers must return kIOReturnSuccess
    on success, or an error otherwise. 
*/

    virtual IOReturn disable(IOKernelDebugger * debugger);

/*! @function attachDebuggerClient
    @abstract Attaches a new IOKernelDebugger client object.
    @discussion This method allocates an IOKernelDebugger object and attaches it as
    a client. Having a debugger client implies that the controller
    supports kernel debugging, and therefore must implement the two
    polled-mode methods that are called by the debugger client. See
    sendPacket() and receivePacket(). Only a single debugger client
    should be attached to each controller.
    @param debuggerP A handle that will return the new
           IOKernelDebugger object created.
    @result Returns true on success, false otherwise. 
*/

    virtual bool attachDebuggerClient(IOKernelDebugger ** debuggerP);

/*! @function detachDebuggerClient
    @abstract Detaches an IOKernelDebugger client object.
    @discussion This method detaches and terminates the IOKernelDebugger client object
    provided. A synchronous termination is issued, and this method will
    return after the debugger client has been terminated. The debugger
    client should be released following this call.
    @param debugger The IOKernelDebugger object to be detached and
           terminated. If the argument provided is NULL or is not an
           IOKernelDebugger, this method will return immediately. 
*/

    virtual void detachDebuggerClient(IOKernelDebugger * debugger);

/*! @function reserveDebuggerLock
    @abstract Takes the global debugger lock.
    @discussion This method should not be used. Instead, call the
    lock() method provided by IOKernelDebugger. 
*/

    void reserveDebuggerLock();

/*! @function releaseDebuggerLock
    @abstract Releases the global debugger lock.
    @discussion This method should not be used. Instead, call the
    unlock() method provided by IOKernelDebugger. 
*/

    void releaseDebuggerLock();

/*! @function receivePacket
    @abstract Debugger polled-mode receive handler.
    @discussion This method must be implemented by a driver that supports
    kernel debugging. After a debugger client has been attached through
    attachDebuggerClient(), this method will be called by the debugger
    client to poll for an incoming packet when the kernel debugger is active.
    This method may be called from the primary interrupt context, and the
    implementation must avoid any memory allocation, and must never block.
    The receivePacket() method in IONetworkController is used as a placeholder,
    it performs no useful action, and should not be called. A driver that
    attaches a debugger client must override this method.
    @param pkt Address of a receive buffer where the received packet should
           be stored. This buffer has room for 1518 bytes.
    @param pktSize Address where the number of bytes received must be
           recorded. Set this to zero if no packets were received during
           the timeout interval.
    @param timeout The maximum amount of time in milliseconds to poll for
           a packet to arrive before this method must return. 
*/ 

    virtual void receivePacket(void * pkt, UInt32 * pktSize, UInt32 timeout);

/*! @function sendPacket
    @abstract Debugger polled-mode transmit handler.
    @discussion This method must be implemented by a driver that supports
    kernel debugging. After a debugger client has been attached through
    attachDebuggerClient(), this method will be called by the debugger
    to send an outbound packet only when the kernel debugger is active.
    This method may be called from the primary interrupt context, and the
    implementation must avoid any memory allocation, and must never block.
    The sendPacket() method in IONetworkController is used as a placeholder,
    it performs no useful action, and should not be called. A driver that
    attaches a debugger client must override this method.
    @param pkt Pointer to a transmit buffer containing the packet to be
        sent on the network.
    @param pktSize The size of the transmit buffer in bytes. 
*/

    virtual void sendPacket(void * pkt, UInt32 pktSize);

/*! @function getDebuggerLinkStatus
    @abstract Debugger polled-mode link status handler.
    @discussion This method should be implemented by a driver that wishes to support
    early availability kernel debugging. After a debugger client has been attached through
    attachDebuggerClient(), this method will be called by the debugger
    to poll for link status availability only when the kernel debugger is active.
    This method may be called from the primary interrupt context. As a result, the
    implementation must avoid any memory allocation, not use spinlocks, and
    never block.

    The getDebuggerLinkStatus() method in IONetworkController is used as a placeholder
    and always reports that the link is up. A driver that attaches a debugger client 
    should override this method. The driver should do any setup required to make 
    sure the link is available for use. Prior to sending or receiving data, KDP will call this 
    function repeatedly until it indicates that the link is both valid and active 
    (kIONetworkLinkValid | kIONetworkLinkActive). 

    @result Link status bits. See IONetworkMedium for the definition of the link status bits.
*/
    virtual UInt32 getDebuggerLinkStatus(void);

/*! @function setDebuggerMode
    @abstract Set debugger mode for network drivers.
    @discussion This method should be implemented by a driver that wishes to be notified when
    entering or leaving KDP. After a debugger client has been attached through
    attachDebuggerClient(), this method will be called by the debugger
    to inform the driver that the kernel debugger is going active or inactive.
    This method may be called from the primary interrupt context. As a result, the
    implementation must avoid any memory allocation, not use spinlocks, and
    never block.

    The setDebuggerMode() method in IONetworkController is used as a placeholder
    and doesn't do anything. If a driver wishes to perform specific actions based upon whether
    or not the debugger is active or not, it should override this method. For example, drivers
    may wish to alter power management settings or perform other chipset reconfigurations based 
    upon the active debugger state.

    @param active Set to true if entering KDP and false if leaving KDP. 
    @result Returns true on success and false otherwise.
*/
    virtual bool setDebuggerMode(bool active);

    // Virtual function padding
    OSMetaClassDeclareReservedUsed( IONetworkController,  0); // getDebuggerLinkStatus
    OSMetaClassDeclareReservedUsed( IONetworkController,  1); // setDebuggerMode

    OSMetaClassDeclareReservedUnused( IONetworkController,  2);
    OSMetaClassDeclareReservedUnused( IONetworkController,  3);
    OSMetaClassDeclareReservedUnused( IONetworkController,  4);
    OSMetaClassDeclareReservedUnused( IONetworkController,  5);
    OSMetaClassDeclareReservedUnused( IONetworkController,  6);
    OSMetaClassDeclareReservedUnused( IONetworkController,  7);
    OSMetaClassDeclareReservedUnused( IONetworkController,  8);
    OSMetaClassDeclareReservedUnused( IONetworkController,  9);
    OSMetaClassDeclareReservedUnused( IONetworkController, 10);
    OSMetaClassDeclareReservedUnused( IONetworkController, 11);
    OSMetaClassDeclareReservedUnused( IONetworkController, 12);
    OSMetaClassDeclareReservedUnused( IONetworkController, 13);
    OSMetaClassDeclareReservedUnused( IONetworkController, 14);
    OSMetaClassDeclareReservedUnused( IONetworkController, 15);
    OSMetaClassDeclareReservedUnused( IONetworkController, 16);
    OSMetaClassDeclareReservedUnused( IONetworkController, 17);
    OSMetaClassDeclareReservedUnused( IONetworkController, 18);
    OSMetaClassDeclareReservedUnused( IONetworkController, 19);
    OSMetaClassDeclareReservedUnused( IONetworkController, 20);
    OSMetaClassDeclareReservedUnused( IONetworkController, 21);
    OSMetaClassDeclareReservedUnused( IONetworkController, 22);
    OSMetaClassDeclareReservedUnused( IONetworkController, 23);
    OSMetaClassDeclareReservedUnused( IONetworkController, 24);
    OSMetaClassDeclareReservedUnused( IONetworkController, 25);
    OSMetaClassDeclareReservedUnused( IONetworkController, 26);
    OSMetaClassDeclareReservedUnused( IONetworkController, 27);
    OSMetaClassDeclareReservedUnused( IONetworkController, 28);
    OSMetaClassDeclareReservedUnused( IONetworkController, 29);
    OSMetaClassDeclareReservedUnused( IONetworkController, 30);
    OSMetaClassDeclareReservedUnused( IONetworkController, 31);
};

#endif /* __cplusplus */
#endif /* KERNEL */
#endif /* !_IONETWORKCONTROLLER_H */
