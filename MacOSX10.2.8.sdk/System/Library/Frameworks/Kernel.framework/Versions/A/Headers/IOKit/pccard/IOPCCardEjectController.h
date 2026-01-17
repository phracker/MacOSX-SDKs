/*
 * Copyright (c) 2001 Apple Computer, Inc. All rights reserved.
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


#ifndef _IOKIT_IOPCCARDEJECTDEVICE_H
#define _IOKIT_IOPCCARDEJECTDEVICE_H

#define kIOPCCardEjectCategory "IOPCCardEjectController"

class IOPCCardEjectController : public IOService
{
    OSDeclareDefaultStructors(IOPCCardEjectController);

protected:
    struct ExpansionData	{ };
    ExpansionData *		reserved;
    
public:
    bool			start(IOService * provider);
    void			stop(IOService * provider);

    virtual bool		requestCardEjection();
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
