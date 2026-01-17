/*
 * Copyright (c) 2001 Apple Computer, Inc. All rights reserved.
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


#ifndef _IOKIT_IOPCCARDEJECTDEVICE_H
#define _IOKIT_IOPCCARDEJECTDEVICE_H

/*! @header IOPCCardEjectDevice
    @abstract An IOService based virtual class for supporting software-controlled PC Card ejection mechanisms.
 */

#define kIOPCCardEjectCategory "IOPCCardEjectController"

/*! @class IOPCCardEjectController
    @abstract Skeleton class for supporting software-controlled PC Card ejection mechanisms.
    @discussion  This is an optional skeleton class that you may subclass if you wish to support a software-controlled PC Card ejection mechanism and/or software-controlled card socket ejection buttons.  There should be an instance of your subclassed driver attached to the CardBus Controller's provider for each socket.  The CardBus bridge driver, IOPCCardBridge, uses the matching category "IOPCCardEjectController" to find this driver and call it.  This class is both responsible for receiving external requests for ejections, such as platform-specific eject buttons, and for the execution of the actual software initiated ejection.
*/

class IOPCCardEjectController : public IOService
{
    OSDeclareDefaultStructors(IOPCCardEjectController);

protected:
    struct ExpansionData	{ };
    ExpansionData *		reserved;
    
public:
    bool			start(IOService * provider);
    void			stop(IOService * provider);

    /*! @function requestCardEjection
     *  @abstract Makes a request for a card to be ejected.
     *  @discussion This method is used to start a request for a card ejection by routing Card Services EjectCard call to the driver(s) for this socket.  Normally, this would be called after an external event was detected, such as a platform-specific PC Card eject button press.
     *  @result Returns true if the ejection request was accepted by all drivers and the ejection was successful.
     */    
    virtual bool		requestCardEjection();

    /*! @function ejectCard
     *  @abstract Physically ejects a card from its socket.
     *  @discussion This method is called to initiate the physical ejection of a card.  It is called by its peer, the IOPCCardBridge driver, after the bridge driver has terminated the socket's driver(s) and the socket has been powered down.  
     *  @result Returns kIOReturnSuccess if the card is ejected.
     */    
    virtual IOReturn		ejectCard();

    OSMetaClassDeclareReservedUnused(IOPCCardEjectController,  0);
    OSMetaClassDeclareReservedUnused(IOPCCardEjectController,  1);
    OSMetaClassDeclareReservedUnused(IOPCCardEjectController,  2);
    OSMetaClassDeclareReservedUnused(IOPCCardEjectController,  3);
    OSMetaClassDeclareReservedUnused(IOPCCardEjectController,  4);
    OSMetaClassDeclareReservedUnused(IOPCCardEjectController,  5);
    OSMetaClassDeclareReservedUnused(IOPCCardEjectController,  6);
    OSMetaClassDeclareReservedUnused(IOPCCardEjectController,  7);
    OSMetaClassDeclareReservedUnused(IOPCCardEjectController,  8);
    OSMetaClassDeclareReservedUnused(IOPCCardEjectController,  9);
    OSMetaClassDeclareReservedUnused(IOPCCardEjectController, 10);
    OSMetaClassDeclareReservedUnused(IOPCCardEjectController, 11);
    OSMetaClassDeclareReservedUnused(IOPCCardEjectController, 12);
    OSMetaClassDeclareReservedUnused(IOPCCardEjectController, 13);
    OSMetaClassDeclareReservedUnused(IOPCCardEjectController, 14);
    OSMetaClassDeclareReservedUnused(IOPCCardEjectController, 15);
};


#endif /* ! _IOKIT_IOPCCARDEJECTDEVICE_H */
