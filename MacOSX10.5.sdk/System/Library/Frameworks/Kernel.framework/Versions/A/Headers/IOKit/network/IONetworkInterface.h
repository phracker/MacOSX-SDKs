/*
 * Copyright (c) 1998-2000 Apple Computer, Inc. All rights reserved.
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
/*
 * Copyright (c) 1999 Apple Computer, Inc.  All rights reserved. 
 *
 * IONetworkInterface.h
 *
 * HISTORY
 * 8-Jan-1999       Joe Liu (jliu) created.
 */

#ifndef _IONETWORKINTERFACE_H
#define _IONETWORKINTERFACE_H


/*! @defined kIONetworkInterfaceClass
    @abstract The name of the IONetworkInterface class. 
*/

#define kIONetworkInterfaceClass     "IONetworkInterface"

/*! @defined kIONetworkData
    @abstract A property of IONetworkInterface
        objects. 
    @discussion The kIONetworkData property has an OSDictionary value and is a container for the
        set of IONetworkData objects managed by the interface.
        Each entry in the dictionary is a key/value pair consisting of
        the network data name, and an OSDictionary describing the
        contents of the network data. 
*/

#define kIONetworkData            "IONetworkData"

/*! @defined kIOInterfaceType
    @abstract A property of IONetworkInterface objects.
    @discussion The kIOInterfaceType property has an OSNumber value that specifies the type of
        network interface that this interface represents. The type
        constants are defined in bsd/net/if_types.h. 
*/

#define kIOInterfaceType          "IOInterfaceType"

/*! @defined kIOMaxTransferUnit
    @abstract A property of IONetworkInterface objects.
    @discussion The kIOMaxTransferUnit property has an OSNumber value that specifies the maximum
        transfer unit for the interface in bytes.
*/

#define kIOMaxTransferUnit        "IOMaxTransferUnit"

/*! @defined kIOMediaAddressLength
    @abstract A property of IONetworkInterface objects.
    @discussion The kIOMediaAddressLength property has an OSNumber value that specifies the size of the
        media address in bytes. 
*/

#define kIOMediaAddressLength     "IOMediaAddressLength"

/*! @defined kIOMediaHeaderLength
    @abstract A property of IONetworkInterface objects.
    @discussion The kIOMediaHeaderLength property has an OSNumber value that specifies the size of the
        media header in bytes. 
*/

#define kIOMediaHeaderLength      "IOMediaHeaderLength"

/*! @defined kIOInterfaceFlags
    @abstract A property of IONetworkInterface objects.
    @discussion The kIOInterfaceFlags property has an OSNumber value that specifies the current value
        of the interface flags. The flag constants are defined in
        bsd/net/if.h. 
*/

#define kIOInterfaceFlags         "IOInterfaceFlags"

/*! @defined kIOInterfaceExtraFlags
    @abstract A property of IONetworkInterface objects.
    @discussion The kIOInterfaceExtraFlags property has an OSNumber value that specifies the current
        value of the interface extra flags. The extra flag constants are
        defined in bsd/net/if.h. 
*/

#define kIOInterfaceExtraFlags    "IOInterfaceExtraFlags"

/*! @defined kIOInterfaceUnit
    @abstract A property of IONetworkInterface objects.
    @discussion The kIOInterfaceUnit property has an OSNumber value that describes the unit number
        assigned to the interface object. 
*/

#define kIOInterfaceUnit          "IOInterfaceUnit"

/*! @defined kIOInterfaceState
    @abstract A property of IONetworkInterface objects.
    @discussion The kIOInterfaceState property has an OSNumber value that describes the current state
        of the interface object. This property is not exported to BSD via
        the ifnet structure. 
*/

#define kIOInterfaceState         "IOInterfaceState"

/*! @defined kIOInterfaceNamePrefix
    @abstract A property of IONetworkInterface objects.
    @discussion The kIOInterfaceNamePrefix property has an OSString value that describes the string
        prefix for the BSD name assigned to the interface. 
*/

#define kIOInterfaceNamePrefix    "IOInterfaceNamePrefix"

/*! @defined kIOPrimaryInterface
    @abstract A property of IONetworkInterface objects.
    @discussion The kIOInterfaceNamePrefix property has an OSBoolean value that describes whether the
        interface is the primary or the built-in network interface. 
*/

#define kIOPrimaryInterface       "IOPrimaryInterface"

/*! @defined kIOBuiltin
    @abstract kIOBuiltin is a property of IONetworkInterface
        objects. It has an OSBoolean value.
    @discussion The kIOBuiltin property describes whether the
        interface is built-in. 
*/

#define kIOBuiltin       "IOBuiltin"

/*! @defined kIOLocation
    @abstract kIOLocation is a property of IONetworkInterface
        objects. It has an OSString value.
    @discussion The kIOLocation property describes the physical 
        location of built-in interfaces. 
*/

#define kIOLocation       "IOLocation"

/*! @enum InterfaceObjectStates
    @discussion Constants used to encode the state of the interface object.
   @constant kIONetworkInterfaceRegisteredState The interface object has
        registered with the data link layer.
    @constant kIONetworkInterfaceOpenedState One or more clients have an
        open on the interface object.
    @constant kIONetworkInterfaceDisabledState The interface is temporarily
        unable to service its clients. This will occur when the network
        controller that is servicing the interface has entered a low power
        state that renders it unusable. 
*/

enum {
    kIONetworkInterfaceRegisteredState  = 0x1,
    kIONetworkInterfaceOpenedState      = 0x2,
    kIONetworkInterfaceDisabledState    = 0x4
};

/*
 * Kernel
 */
#if defined(KERNEL) && defined(__cplusplus)

#include <IOKit/IOService.h>
#include <IOKit/network/IONetworkData.h>
#include <IOKit/network/IONetworkStats.h>
#include <IOKit/network/IONetworkMedium.h>
#include <net/kpi_interface.h>

class  IONetworkController;
class  IONetworkStack;
class  IOCommandGate;

/*! @typedef IOOutputAction
    @discussion Prototype for an output packet handler that will process
    all outbound packets sent to the interface from the data link layer.
    An output handler is registered with the interface by calling
    registerOutputHandler().
    @param m A packet mbuf.
    @param param A parameter for the output request. */

typedef UInt32 (OSObject::*IOOutputAction)(mbuf_t, void * param);

/*! @typedef BPF_FUNC
    @discussion Prototype for the BPF tap handler. This will disappear
    when the correct DLIL header file is included. */

typedef int (*BPF_FUNC)(struct ifnet *, struct mbuf *);

// Network event types recognized by inputEvent().
//
enum {
    /* DLIL defined event, argument must be a pointer to a
       kern_event_msg structure. */
    kIONetworkEventTypeDLIL      = 0xff000001,

    /* Link up event, no argument */
    kIONetworkEventTypeLinkUp    = 0xff000002,

    /* Link down event, no argument */
    kIONetworkEventTypeLinkDown  = 0xff000003
};

/*! @class IONetworkInterface
    @abstract Abstract class that manages the connection between an IONetworkController and the data link interface layer.
    @discussion An IONetworkInterface object manages the connection between
    an IONetworkController and the data link interface layer (DLIL).
    All interactions between the controller and DLIL must go through an
    interface object. Any data structures that are required by DLIL for a
    particular interface type shall be allocated and mantained by the
    interface object. IONetworkInterface is an abstract class that must be
    extended by a concrete subclass to specialize for a particular network
    type.

    Although most drivers will allocate a single interface object,
    it is possible for multiple interfaces to be attached to a single
    controller. This controller driver will be responsible for arbitrating
    access among its multiple interface clients.
    
    IONetworkInterface also maintains a dictionary of IONetworkData
    objects containing statistics structures. Controller drivers can
    ask for a particular data object by name and update the
    statistics counters within directly. This dictionary is added to
    the interface's property table and is visible outside of the kernel. 
*/

class IONetworkInterface : public IOService
{
    OSDeclareAbstractStructors( IONetworkInterface )

    friend class IONetworkStack;

private:
    IONetworkController *    _controller;
    ifnet_t					_backingIfnet;
    IORecursiveLock *        _ifLock;
    OSSet *                  _clientSet;
    OSNumber *               _stateBits;
	bpf_packet_func                 _inputFilterFunc;
    bpf_packet_func                 _outputFilterFunc;
	OSObject *               _outTarget;
    IOOutputAction           _outAction;
    UInt32                   _clientVar[4];
    OSDictionary *           _dataDict;
    mbuf_t            _inputQHead;
    mbuf_t            _inputQTail;
    UInt32                   _inputQCount;

    struct ExpansionData {
        thread_call_t   powerChangeThreadCall;
        IOSimpleLock *  powerChangeNoticeLock;
        queue_head_t    powerChangeNoticeList;
		int				unit;
		int				type;
		int				mtu;
		int				flags;
		int				eflags;
		int				addrlen;
		int				hdrlen;
		IONetworkStats  driverStats;
		IONetworkStats  lastDriverStats;
		struct ifnet_stat_increment_param inputDeltas;
		IOLock			*detachLock;
    };

    /*! @var reserved
        Reserved for future use.  (Internal use only)  */
    ExpansionData *          _reserved;
	void _syncFromBackingIfnet() const;
	void _syncToBackingIfnet();

    bool _syncNetworkDataDict();
    bool _setInterfaceProperty(UInt32   value,
                               UInt32   mask,
                               UInt32   bytes,
                               void *   addr,
                               char *   name);

    SInt32 syncSIOCSIFMEDIA(IONetworkController * ctlr, struct ifreq * ifr);
    SInt32 syncSIOCGIFMEDIA(IONetworkController * ctlr, struct ifreq * ifr, UInt32 cmd);
    SInt32 syncSIOCSIFMTU(IONetworkController * ctlr, struct ifreq * ifr);
	
    static int  performGatedCommand(void *, void *, void *, void *, void *);
    static errno_t  ioctl_shim(ifnet_t ifp, u_int32_t cmd, void * data);
    static errno_t  set_bpf_tap_shim(ifnet_t ifn, bpf_tap_mode mode, bpf_packet_func func);
    static int  output_shim(ifnet_t ifp, mbuf_t);
	void DLIL_INPUT(mbuf_t m_head);
	static void  detach_shim(ifnet_t ifp);
    static void powerChangeHandler(void *, void *, void *, void *, void *);

public:

/*! @function isPrimaryInterface
    @abstract Queries whether the interface object provided represents
    the "primary" network interface for the system.
    @result Returns true if the interface provided is the primary inteface,
    false otherwise. 
*/

    virtual bool isPrimaryInterface() const;

/*! @function init
    @abstract Initializes an IONetworkInterface object.
    @discussion Initializes instance variables, and allocates resources.
    @param controller A network controller object that will service
    the interface object being initialized.
    @result Returns true on success, false otherwise. 
*/

    virtual bool init( IONetworkController * controller );

/*! @function isRegistered
    @abstract Returns true if the interface has been registered with
    the data link layer.
    @discussion Once registered, the interface will be assigned a
    BSD name (such as en0), and a kIOBSDNameKey property is added to the
    property table containing this name. Calling this method performs
    the same function as checking for the kIONetworkInterfaceRegisteredState
    bit in the value returned by getInterfaceState().
    @result Returns true if interface is registered. Returns false if the data link layer
    has no references to this network interface, which implies that either the
    interface has yet to attach to the data link layer, or the interface has
    been detached. 
*/

    virtual bool isRegistered() const;

/*! @function getInterfaceState
    @abstract Reports the current state of the interface object by returning
    the interface state flags.
    @result Returns the interface state flags. 
*/

    virtual UInt32 getInterfaceState() const;

/*! @function matchPropertyTable
    @abstract Overrides the implementation in IOService to
    implement family-specific matching.
    @discussion When the gIOLocationMatchKey property is present in the
    dictionary provided, then fail the match unless the kIOBSDNameKey property
    is found. This is to prevent a premature match when hunting for a root
    device for BSD. The presence of the kIOBSDNameKey property indicates that
    the interface has registered with BSD, and is a valid candidate for
    matching against the gIOLocationMatchKey property. If the
    gIOLocationMatchKey property is absent, then this method will always
    return true.
    @param table The dictionary of properties to match against.
    @param score Pointer to the current driver's probe score, not used.
    @result Returns true for a positive match, false otherwise. 
*/

    virtual bool matchPropertyTable( OSDictionary * table,
                                     SInt32       * score );

/*! @function getController
    @abstract Returns the provider, an IONetworkController object, that
    is servicing this interface object.
    @discussion This is the same controller object that was supplied as
    an argument to the init() method.
    @result Returns the IONetworkController object that is providing service to
    this interface object. 
*/

    virtual IONetworkController * getController() const;

/*! @function inputPacket
    @abstract Submits a single packet received from the network to the data link layer.
    @discussion This method is called by the network controller to submit a single packet
    received from the network to the data link layer.  The packet received by this method may be added to an input
    queue on the interface object, which the controller can use to postpone
    the packet handoff to the upper layers, until all received packets have
    been transferred to the input queue. A subsequent call to flushInputQueue(),
    will transfer the entire contents of the queue to the data link layer,
    by making a single call to dlil_input(). Other methods that can be used
    to manage the input queue are flushInputQueue() and clearInputQueue().
    This input queue is not protected by a lock. Access to the queue by the
    controller must be serialized, otherwise its use must be avoided.
    @param m The mbuf containing the received packet.
    @param length Specify the size of the received packet in the mbuf.
           The mbuf length fields are updated with this value. If zero,
           then the mbuf length fields are not updated.
    @param options Options defined by inputPacket() that the caller
           can use to specify this method call.
    @param param A parameter provided by the caller. Not used by
           IONetworkInterface.
    @result Returns the number of packets that were submitted to the data link layer,
            or 0 if the packet was queued. 
*/

    virtual UInt32 inputPacket(mbuf_t,
                               UInt32        length  = 0,
                               IOOptionBits  options = 0,
                               void *        param   = 0);

/*! @enum InputOptionQueuePacket
    @discussion The option bits that can be specified
    in the options argument when calling inputPacket().
    @constant kInputOptionQueuePacket Keep the packet provided in the
    input packet queue. No packets are sent to the data link layers,
    and the caller's thread will not venture outside the interface
    object. Calls to inputPacket() must be serialized. 
*/

    enum {
        kInputOptionQueuePacket = 0x1
    };

/*! @function flushInputQueue
    @abstract Sends all packets held in the input queue to the data
    link layer.
    @discussion Remove all packets from the input queue and
    send them to the data link layer by calling dlil_input(). This
    method should be used in connection with the inputPacket() method,
    to flush the input queue after inputPacket() was used to queue up
    some number of received packets. See inputPacket() and clearInputQueue().
    @result Returns the number of packets that were submitted to the data link layer.
            May be zero if the queue was empty. 
*/

    virtual UInt32 flushInputQueue();

/*! @function clearInputQueue
    @abstract Removes and discards all packets in the input queue.
    @discussion This method removes all packets from the input queue and
    releases them back to the free mbuf pool. Also see flushInputQueue().
    @result Returns the number of packets freed. 
*/

    virtual UInt32 clearInputQueue();

/*! @function inputEvent
    @abstract Sends an event to the data link layer.
    @discussion This method can be used by the network controller to
    send an event to the data link layer.
    @param type A constant describing the event type.
    @param data Data associated with the event.
    @result Returns true if the event was delivered, false if the event type
    specified is invalid, or if the event delivery was unsuccesful. 
*/

    virtual bool inputEvent(UInt32 type, void * data);

/*! @function registerOutputHandler
    @abstract Registers a target/action to handle output packets.
    @discussion The interface object will forward all output packets,
    received from the data link layer, to the output handler registered
    through this method. The default target and action are set by the init()
    method to the controller, and the handler returned by the controller's
    getOutputHandler() method. Once the interface becomes registered with
    the data link layer, this method will return false and will reject any
    further changes.
    @param target Target object that implements the output handler.
    @param action The function that will process output packets.
    @result Returns true if the target/action provided was accepted,
    false otherwise. 
*/

    virtual bool registerOutputHandler(OSObject *      target,
                                       IOOutputAction  action);

/*! @function getNamePrefix
    @abstract Returns a string containing the prefix to use when
    creating a BSD name for this interface.
    @discussion The BSD name for each interface object is generated by
    concatenating a string returned by this method, with an unique
    unit number assigned by IONetworkStack.
    A concrete subclass of IONetworkInterface must implement this method
    and enforce a consistent name for all of its instances.
    @result Returns a pointer to a constant C string.
*/

    virtual const char * getNamePrefix() const = 0;

/*! @function getInterfaceType
    @abstract Gets the interface type.
    @discussion This method returns the value in the if_type field in the ifnet structure.
    @result Returns a constant defined in bsd/net/if_types.h header file
    that describes the interface type. 
*/

    virtual UInt8  getInterfaceType() const;

/*! @function getMaxTransferUnit
    @abstract Gets the maximum transfer unit for this interface.
    @discussion This method returns the value in the if_mtu field in the ifnet structure.
    @result Returns the interface MTU size in bytes. 
*/

    virtual UInt32 getMaxTransferUnit() const;

/*! @function getFlags
    @abstract Gets the value of the interface flags.
    @discussion This method returns the value in the if_flags field in the ifnet structure.
    @result Returns the value of the interface flags. 
*/

    virtual UInt16 getFlags() const;

/*! @function getExtraFlags
    @abstract Gets the value of the interface extra flags.
    @discussion This method returns the value in the if_eflags field in the ifnet structure.
    @result Returns the value of the interface extra flags. 
*/

    virtual UInt32 getExtraFlags() const;

/*! @function getMediaAddressLength
    @abstract Gets the size of the media (MAC-layer) address.
    @discussion This method returns the value in the if_addrlen field in the ifnet structure.
    @result Returns the size of the media address in bytes. 
*/

    virtual UInt8  getMediaAddressLength() const;

/*! @function getMediaHeaderLength
    @abstract Gets the size of the media header.
    @discussion This method returns the value in the if_hdrlen field in the ifnet structure.
    @result Returns the size of the media header in bytes. 
*/

    virtual UInt8  getMediaHeaderLength() const;

/*! @function getUnitNumber
    @abstract Gets the unit number assigned to this interface object.
    @discussion This method returns the value in the if_unit field in the ifnet structure.
    @result Returns the assigned interface unit number. 
*/

    virtual UInt16 getUnitNumber() const;

/*! @function addNetworkData
    @abstract Adds an IONetworkData object to a dictionary managed by
    the interface.
    @param aData An IONetworkData object to be added to a dictionary
    managed by the interface. This object is retained by the dictionary.
    @result Returns true if the operation was successful, false otherwise. 
*/

    virtual bool addNetworkData(IONetworkData * aData);

/*! @function removeNetworkData
    @abstract Removes an entry from the IONetworkData dictionary
    managed by the interface.
    @discussion This method removes an entry from the IONetworkData dictionary
    managed by the interface. The removed object is released.
    @param aKey A unique OSSymbol identifying the IONetworkData object
           to be removed from the dictionary.
    @result Returns true if the operation was successful, false otherwise. 
*/

    virtual bool removeNetworkData(const OSSymbol * aKey);

/*! @function removeNetworkData
    @abstract Removes an entry from the IONetworkData dictionary
    managed by the interface.
    @discussion This method removes an entry from the IONetworkData dictionary
    managed by the interface. The removed object is released.
    @param aKey A unique string identifying the IONetworkData object
           to be removed from the dictionary.
    @result Returns true if the operation was successful, false otherwise. 
*/

    virtual bool removeNetworkData(const char * aKey);

/*! @function getNetworkData
    @abstract Gets an IONetworkData object from the interface that is
    associated with the given key.
    @param aKey The unique string identifying the IONetworkData object to be
    returned to caller.
    @result Returns a reference to the matching IONetworkData object,
    or 0 if no match was found.
*/

    virtual IONetworkData * getNetworkData(const char * aKey) const;

/*! @function getNetworkData
    @abstract Gets an IONetworkData object from the interface that is
    associated with the given key.
    @param aKey The unique OSSymbol identifying the IONetworkData object to be
    returned to caller.
    @result Returns a reference to the matching IONetworkData object,
    or 0 if no match was found. 
*/

    virtual IONetworkData * getNetworkData(const OSSymbol * aKey) const;

/*! @function setProperties
    @abstract Handles a request to set network interface properties from
    kernel or non-kernel clients. 
    @discussion For non-kernel clients, the preferred
    access mechanism is through a user client connection.
    @param properties An OSDictionary containing a collection of
    properties.
    @result Returns kIOReturnUnsupported if the interface did not
    recognize any of the properties provided. Otherwise, the return
    code will be kIOReturnSuccess to indicate no errors, or an
    IOReturn error code to indicate that an error occurred while
    handling one of the properties. 
*/

    virtual IOReturn setProperties( OSObject * properties );

    // FIXME - Compatibility methods (to be removed)
    IONetworkData * getParameter(const char * aKey) const;
	bool setExtendedFlags(UInt32 flags, UInt32 clear = 0);

protected:

/*! @function setInterfaceType
    @abstract Sest the interface type.
    @discussion Both the if_type field in the ifnet structure, and the
    kIOInterfaceType property are updated with the value provided.
    @param type A constant defined in bsd/net/if_types.h header file
    that describes the interface type.
    @result Returns true if the update was successful, false otherwise. 
*/

    virtual bool setInterfaceType(UInt8 type);

/*! @function setMaxTransferUnit
    @abstract Sets the maximum transfer unit for this interface.
    @discussion Both the if_mtu field in the ifnet structure, and the
    kIOMaxTransferUnit property are updated with the value provided.
    @param mtu The interface MTU size in bytes.
    @result Returns true if the update was successful, false otherwise. 
*/

    virtual bool setMaxTransferUnit(UInt32 mtu);

/*! @function setFlags
    @abstract Performs a read-modify-write operation on the current
    interface flags value.
    @discussion See bsd/net/if.h header file for the definition of the
    flag constants. Both the if_flags field in the ifnet structure, and
    the kIOInterfaceFlags property are updated with the value provided.
    @param flags The bits that should be set.
    @param clear The bits that should be cleared. If 0, then non
    of the flags are cleared and the result is formed by OR'ing the
    original flags value with the new flags.
    @result Returns true if the update was successful, false otherwise. 
*/

    virtual bool setFlags(UInt16 flags, UInt16 clear = 0);

/*! @function setExtraFlags
    @abstract Performs a read-modify-write operation on the current
    interface extra flags value.
    @discussion See bsd/net/if.h header file for the definition of the
    extra flag constants. Both the if_eflags field in the ifnet structure,
    and the kIOInterfaceExtraFlags property are updated with the value
    provided.
    @param flags The bits that should be set.
    @param flags The bits that should be set.
    @param clear The bits that should be cleared. If 0, then non
    of the flags are cleared and the result is formed by OR'ing the
    original flags with the new flags.
    @result Returns true if the update was successful, false otherwise. 
*/

    virtual bool setExtraFlags(UInt32 flags, UInt32 clear = 0);

/*! @function setMediaAddressLength
    @abstract Sets the size of the media (MAC-layer) address.
    @discussion Both the if_addrlen field in the ifnet structure, and the
    kIOMediaAddressLength property are updated with the value provided.
    @param length The size of the media address in bytes.
    @result Returns true if the update was successful, false otherwise.
*/

    virtual bool setMediaAddressLength(UInt8 length);

/*! @function setMediaHeaderLength
    @abstract Sets the size of the media header.
    @discussion Both the if_hdrlen field in the ifnet structure, and the
    kIOMediaHeaderLength property are updated with the value provided.
    @param length The size of the media header in bytes.
    @result Returns true if the update was successful, false otherwise. 
*/

    virtual bool setMediaHeaderLength(UInt8 length);

/*! @function setUnitNumber
    @abstract Assigns a unique unit number to this interface.
    @discussion This method is called by IONetworkStack before the
    interface is registered with the data link layer, to assign a
    unique unit number to the interface object. Both the if_unit field
    in the ifnet structure, and the kIOInterfaceUnit property are updated
    with the value provided.
    @param unit The unit number assigned to this interface object.
    @result Returns true if the update was successful, false otherwise. 
*/

    virtual bool setUnitNumber(UInt16 unit);

/*! @function free
    @abstract Frees the IONetworkInterface object.
    @discussion Resource allocated by init() are released, and
    clearInputQueue() is called to ensure that the input queue is empty.
*/

    virtual void free();

/*! @function handleOpen
    @abstract Handles a client open on the interface.
    @discussion This method is called by IOService::open() with the
    arbitration lock held, and must return true to accept the client open.
    This method will in turn call handleClientOpen() to qualify the client
    requesting the open. Since the controller is opened by the interface
    in a lazy fashion, the interface may also perform an open on the
    controller before this method returns. If the controller was opened,
    then controllerDidOpen() is called to notify interested subclasses.
    Subclasses should not override this method.
    @param client The client object that requested the open.
    @param options Options passed to IOService::open().
    @param argument Argument passed to IOService::open().
    @result Returns true to accept the client open, false otherwise. 
*/

    virtual bool handleOpen(IOService *  client,
                            IOOptionBits options,
                            void *       argument);

/*! @function handleClose
    @abstract Handles a client close on the interface.
    @discussion This method is called by IOService::close() with the
    arbitration lock held. This method will in turn call handleClientClose()
    to notify interested subclasses about the client close. If this represents
    the last close, then the interface will also close the controller before
    this method returns. The controllerWillClose() method will be called before
    closing the controller. Subclasses should not override this method.
    @param client The client object that requested the close.
    @param options Options passed to IOService::close().
*/

    virtual void handleClose(IOService * client, IOOptionBits options);

/*! @function handleIsOpen
    @abstract Queries whether a client has an open on the interface.
    @discussion This method is always called by IOService with the
    arbitration lock held. Subclasses should not override this method.
    @result Returns true if the specified client, or any client if none (0) is
    specified, presently has an open on this object. 
*/

    virtual bool handleIsOpen(const IOService * client) const;

/*! @function lock
    @abstract Takes the network interface lock.
    @discussion This method takes the recursive lock that protects the interface
    state. All updates to the interface state and to the ifnet structure
    must be performed while holding this lock. This call must be balanced
    by a subsequent call to unlock(). 
*/

    virtual void lock();

/*! @function unlock
    @abstract Releases the network interface lock.
    @discussion This method releases the recursive lock that protects the interface
    state to balance a previous lock() call. 
*/

    virtual void unlock();

/*! @function controllerDidOpen
    @abstract Sends a notification that the interface has opened the network
    controller.
    @discussion This method is called by handleOpen() to notify subclasses that the
    controller has been opened. The open on the controller is done when
    the interface receives the initial open request from a client.
    Subclasses can override this method and inspect the controller before
    allowing the client open. The implementation in the subclass must first
    call the method in super and check the return value. This method is
    called with our arbitration lock held, hence issuing I/O to the
    controller must be avoided to eliminate the possibility of a
    deadlock.
    @param controller The controller that was opened.
    @result Must return true in order for handleOpen() to accept 
    the client open. If the return is false, then the controller will be
    closed and the client open will be refused. 
*/

    virtual bool controllerDidOpen(IONetworkController * controller);

/*! @function controllerWillClose
    @abstract Sends a notification that the interface will close the network
    controller.
    @discussion This method is called by handleClose() after receiving a close from the
    last client, and just before the controller is closed. Subclasses
    can override this method to perform any cleanup action before the 
    controller is closed. This method is called with our arbitration lock
    held, hence issuing I/O to the controller must be avoided to eliminate
    the possibility of a deadlock.
    @param controller The controller that is about to be closed. 
*/

    virtual void controllerWillClose(IONetworkController * controller);

/*! @function performCommand
    @abstract Handles an ioctl command sent to the network interface.
    @discussion This method handles socket ioctl commands sent to the
    network interface from DLIL.
    IONetworkInterface handles commands that are common for all network
    interface types. A subclass of IONetworkInterface may override this
    method to override the command handling in IONetworkInterface, or
    to extend the command processing to handle additional commands,
    and then call super for any commands not handled in the subclass.
    The ioctl commands handled by IONetworkInterface are
        SIOCGIFMTU (Get interface MTU size),
        SIOCSIFMTU (Set interface MTU size),
        SIOCSIFMEDIA (Set media), and
        SIOCGIFMEDIA (Get media and link status).
    @param controller The controller object.
    @param cmd The ioctl command code.
    @param arg0 Command argument 0. Generally a pointer to an ifnet structure
        associated with the interface.
    @param arg1 Command argument 1.
    @result Returns a BSD return value defined in bsd/sys/errno.h. 
*/

    virtual SInt32 performCommand(IONetworkController * controller,
                                  UInt32                cmd,
                                  void *                arg0,
                                  void *                arg1);

/*! @function getIfnet
    @abstract Gets the ifnet structure allocated by the interface object.
    @discussion Reveal the interface's ifnet_t.  The ifnet_t is managed
		primarily by IONetworkInterface, however this method can be called
		when the sub-class needs to call interface KPI functions directly.
    @result Returns the ifnet_t object that is attached to the datalink layer.
*/

    virtual ifnet_t getIfnet() const ;

/*! @function initIfnet
    @abstract Initializes the ifnet structure given.
    @discussion A concrete subclass must override this method and initialize
    the ifnet structure given. The implementation in the subclass must call
    super before it returns, to allow IONetworkInterface to complete the
    initialization, and to insert the BSD shim functions implemented in
    IONetworkInterface to the appropriate function pointer fields in the
    ifnet structure. IONetworkInterface will call this method during its
    init() method. Subclasses are encouraged to use the ifnet accessor
    methods to update the ifnet structure when possible, since this will
    ensure that properties in the registry will also be updated to reflect
    any changes made.
    @param ifp Pointer to an ifnet structure obtained earlier through
               the getIfnet() method call.
    @result Returns true on success, false otherwise. 
*/

    virtual bool initIfnet(struct ifnet * ifp);

/*! @function handleClientOpen
    @abstract Handles a client open on the interface.
    @discussion This method is called by handleOpen() to handle an open from a client object.
    Unlike handleOpen(), subclasses may override this method to catch an open
    request from a client. This method is called with the arbitration lock held.
    @param client The client object requesting the open.
    @param options Options passed to IONetworkInterface::handleOpen().
    @param argument Argument passed to IONetworkInterface::handleOpen().
    @result Returns true to accept the client open, false to refuse it. 
*/

    virtual bool handleClientOpen(IOService *  client,
                                  IOOptionBits options,
                                  void *       argument);

/*! @function handleClientClose
    @abstract Handles a client close on the interface.
    @discussion This method is called by handleClose() to handle a close from a client object.
    Unlike handleClose(), subclasses may override this method to catch a close
    reuqest from a client. This method is called with the arbitration lock held.
    @param client The client object requesting the close.
    @param options Options passed to IONetworkInterface::handleClose(). 
*/

    virtual void handleClientClose(IOService *  client,
                                   IOOptionBits options);

/*! @function newUserClient
    @abstract Creates a connection for a non kernel client.
    @discussion This method creates a new IOUserClient to service a connection to a
    non kernel client.
    @param owningTask The mach task requesting the connection.
    @param security_id A token representing the access level for the task.
    @param type A constant specifying the type of connection to be created.
    An IONetworkUserClient object is created if the type specified is
    kIONetworkUserClientTypeID.
    @param handler The IOUserClient object returned.
    @result Returns kIOReturnSuccess if an IONetworkUserClient was created,
    kIOReturnNoMemory for a memory allocation error, or
    kIOReturnBadArgument if the type specified is unknown. 
*/

    virtual IOReturn newUserClient(task_t           owningTask,
                                   void *           security_id,
                                   UInt32           type,
                                   IOUserClient **  handler);

/*! @function setInterfaceState
    @abstract Updates the interface object state flags.
    @discussion The kIOInterfaceState property is updated with the value
    provided.
    @param flags The bits that should be set.
    @param clear The bits that should be cleared.
    @result Returns the resulting interface state flags following any changes
    made by this method. 
*/

    virtual UInt32 setInterfaceState( UInt32 set, UInt32 clear = 0 );

/*! @function powerStateWillChangeTo
    @abstract Handles a notification that the network controller servicing
    this interface object is about to transition to a new power state.
    @discussion This method will call the controllerWillChangePowerState() method
    on the controller's work loop context to prepare for the power state change.
    Subclasses should not override this method.
    @param flags Flags that describe the capability of the controller in the new
    power state.
    @param stateNumber An index to a state in the network controller's
    power state array that the controller is switching to.
    @param policyMaker A reference to the network controller's policy-maker,
    and is also the originator of this notification.
    @result The return will always be IOPMAckImplied to indicate that the
    preparation for the power change has already completed when this method
    returns. 
*/

    virtual IOReturn powerStateWillChangeTo( IOPMPowerFlags  flags,
                                             UInt32          stateNumber,
                                             IOService *     policyMaker );

/*! @function powerStateDidChangeTo
    @abstract Handles a notification that the network controller servicing
    this interface object has transitioned to a new power state.
    @discussion This method will call the controllerDidChangePowerState() method
    on the controller's work loop context to prepare for the power state change.
    Subclasses should not override this method.
    @param flags Flags that describe the capability of the controller in the new
    power state.
    @param stateNumber An index to a state in the network controller's
    power state array that the controller has switched to.
    @param policyMaker A reference to the network controller's policy-maker,
    and is also the originator of this notification.
    @result The return will always be IOPMAckImplied to indicate that the
    preparation for the power change has already completed when this method
    returns. 
*/

    virtual IOReturn powerStateDidChangeTo( IOPMPowerFlags  flags,
                                            UInt32          stateNumber,
                                            IOService *     policyMaker );

/*! @function controllerWillChangePowerState
    @abstract Handles a notification that the network controller servicing
    this interface object is about to transition to a new power state.
    @param controller The network controller object.
    @param flags Flags that describe the capability of the controller in the new
    power state.
    @param stateNumber An index to a state in the network controller's
    power state array that the controller is switching to.
    @param policyMaker A reference to the network controller's policy-maker,
    and is also the originator of this notification.
    @result The return value is always kIOReturnSuccess. 
*/

    virtual IOReturn controllerWillChangePowerState(
                               IONetworkController * controller,
                               IOPMPowerFlags        flags,
                               UInt32                stateNumber,
                               IOService *           policyMaker);

/*! @function controllerDidChangePowerState
    @abstract Handles a notification that the network controller servicing
    this interface object has transitioned to a new power state.
    @param controller The network controller object.
    @param flags Flags that describe the capability of the controller in the new
    power state.
    @param stateNumber An index to a state in the network controller's
    power state array that the controller has switched to.
    @param policyMaker A reference to the network controller's policy-maker,
    and is also the originator of this notification.
    @result The return value is always kIOReturnSuccess. 
*/

    virtual IOReturn controllerDidChangePowerState(
                               IONetworkController * controller,
                               IOPMPowerFlags        flags,
                               UInt32                stateNumber,
                               IOService *           policyMaker);

public:
    /* Override IOService::willTerminate() */

    virtual bool willTerminate( IOService *  provider,
                                IOOptionBits options );

    /* Override IOService::serializeProperties() */

    virtual bool serializeProperties( OSSerialize * s ) const;

/*! @function attachToDataLinkLayer
    @abstract Attaches the network interface to the data link layer.
    @discussion This function is called by the family to attach the network
    interface managed by an IONetworkInterface to the data link layer. This
    call occurs after the interface initialization and setup, including the
    assignment of an interface unit number. Prior to the data link attach,
    services provided by an IONetworkInterface will be inaccessible to BSD
    networking, though the object can be found in the I/O Kit Registry.
    Subclasses can extend this function to perform additional work that is
    specific to a type of interface.
    @param options Options for the attach call. None are currently defined.
    @param parameter Parameter for the attach call. Not currently used.
    @result Returns kIOReturnSuccess on success. 
*/

    virtual IOReturn attachToDataLinkLayer( IOOptionBits options,
                                            void *       parameter );

    OSMetaClassDeclareReservedUsed(IONetworkInterface, 0);

/*! @function detachFromDataLinkLayer
    @abstract Detaches the network interface from the data link layer.
    @discussion This function is called by the family to detach the network
    interface managed by an IONetworkInterface from the data link layer.
    This call is made when the interface is terminated, before the last close.
    Subclasses can extend this function to perform additional work that is
    specific to a type of interface.
    @param options Options for the detach call. None are currently defined.
    @param parameter Parameter for the detach call. Not currently used. 
*/

    virtual void detachFromDataLinkLayer( IOOptionBits options,
                                          void *       parameter );

    OSMetaClassDeclareReservedUsed(IONetworkInterface, 1);

protected:
		/*! @function feedInputPacketTap
		@abstract Feed received packets to the BPF
		@discussion This function is called by the family for each inbound packet
		to feed it to the BPF function.  Interface classes can override if they
		need to provide class specific functionality or modifications to the BPF tap.
		@param mbuf Pointer to the packet.
		*/
		virtual void feedPacketInputTap(mbuf_t);
	
	OSMetaClassDeclareReservedUsed( IONetworkInterface,  2);
	/*! @function feedOutputPacketTap
		@abstract Feed sent packets to the BPF
		@discussion This function is called by the family for each outbound packet
		to feed it to the BPF function.  Interface classes can override if they
		need to provide class specific functionality or modifications to the BPF tap.
		@param mbuf Pointer to the packet.
		*/
	virtual void feedPacketOutputTap(mbuf_t);
	
	OSMetaClassDeclareReservedUsed( IONetworkInterface,  3);
	
	virtual bool initIfnetParams(struct ifnet_init_params *params);
    OSMetaClassDeclareReservedUsed( IONetworkInterface,  4);
	
public:
    // Virtual function padding
	OSMetaClassDeclareReservedUnused( IONetworkInterface,  5);
	OSMetaClassDeclareReservedUnused( IONetworkInterface,  6);
    OSMetaClassDeclareReservedUnused( IONetworkInterface,  7);
    OSMetaClassDeclareReservedUnused( IONetworkInterface,  8);
    OSMetaClassDeclareReservedUnused( IONetworkInterface,  9);
    OSMetaClassDeclareReservedUnused( IONetworkInterface, 10);
    OSMetaClassDeclareReservedUnused( IONetworkInterface, 11);
    OSMetaClassDeclareReservedUnused( IONetworkInterface, 12);
    OSMetaClassDeclareReservedUnused( IONetworkInterface, 13);
    OSMetaClassDeclareReservedUnused( IONetworkInterface, 14);
    OSMetaClassDeclareReservedUnused( IONetworkInterface, 15);
};

#endif /* defined(KERNEL) && defined(__cplusplus) */

#endif /* !_IONETWORKINTERFACE_H */
