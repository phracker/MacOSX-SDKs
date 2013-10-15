/*
 * Copyright (c) 1998-2005 Apple Computer, Inc. All rights reserved.
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

#ifndef _IOMEDIABSDCLIENT_H
#define _IOMEDIABSDCLIENT_H

#include <sys/disk.h>

#ifdef KERNEL
#ifdef __cplusplus

/*
 * Kernel
 */

#include <sys/kernel_types.h>
#include <IOKit/storage/IOMedia.h>

/* DEPRECATED */ class  AnchorTable;
/* DEPRECATED */ class  MinorTable;
/* DEPRECATED */ struct MinorSlot;

/*
 * Class
 */

class IOMediaBSDClient : public IOService
{
    OSDeclareDefaultStructors(IOMediaBSDClient)

protected:

    struct ExpansionData { /* */ };
    ExpansionData * _expansionData;

private:

    AnchorTable * _anchors;              /* (table of anchors)                */
    UInt32        _reserved0064;         /* (reserved, do not use)            */
    UInt32        _reserved0096;         /* (reserved, do not use)            */
    MinorTable *  _minors;               /* (table of minors)                 */
    UInt32        _reserved0160;         /* (reserved, do not use)            */

protected:

    /*
     * Find the whole media that roots the given media tree.
     */

    virtual IOMedia * getWholeMedia( IOMedia * media,
                                     UInt32 *  slicePathSize = 0,
                                     char *    slicePath     = 0 );

    /*
     * Create bdevsw and cdevsw nodes for the given media object.
     */

    virtual bool createNodes(IOMedia * media);

    /*
     * Free all of this object's outstanding resources.
     */

    virtual void free();

public:

    /*
     * Obtain this object's provider.  We override the superclass's method to
     * return a more specific subclass of IOService -- IOMedia.   This method
     * method serves simply as a convenience to subclass developers.
     */

    virtual IOMedia * getProvider() const;

    /*
     * Initialize this object's minimal state.
     */

    virtual bool init(OSDictionary * properties  = 0);

    /*
     * This method is called once we have been attached to the provider object.
     */

    virtual bool start(IOService * provider);

    /*
     * This method is called when we are to terminate from the provider object.
     */

    virtual bool terminate(IOOptionBits options);

    /* DEPRECATED */ virtual AnchorTable * getAnchors();
    /* DEPRECATED */ virtual MinorTable *  getMinors();
    /* DEPRECATED */ virtual MinorSlot *   getMinor(UInt32 minorID);

    /*
     * Process a foreign ioctl.
     */

    virtual int ioctl(dev_t, u_long cmd, caddr_t data, int, proc_t);

    OSMetaClassDeclareReservedUsed(IOMediaBSDClient, 0);

    OSMetaClassDeclareReservedUnused(IOMediaBSDClient,  1);
    OSMetaClassDeclareReservedUnused(IOMediaBSDClient,  2);
    OSMetaClassDeclareReservedUnused(IOMediaBSDClient,  3);
    OSMetaClassDeclareReservedUnused(IOMediaBSDClient,  4);
    OSMetaClassDeclareReservedUnused(IOMediaBSDClient,  5);
    OSMetaClassDeclareReservedUnused(IOMediaBSDClient,  6);
    OSMetaClassDeclareReservedUnused(IOMediaBSDClient,  7);
    OSMetaClassDeclareReservedUnused(IOMediaBSDClient,  8);
    OSMetaClassDeclareReservedUnused(IOMediaBSDClient,  9);
    OSMetaClassDeclareReservedUnused(IOMediaBSDClient, 10);
    OSMetaClassDeclareReservedUnused(IOMediaBSDClient, 11);
    OSMetaClassDeclareReservedUnused(IOMediaBSDClient, 12);
    OSMetaClassDeclareReservedUnused(IOMediaBSDClient, 13);
    OSMetaClassDeclareReservedUnused(IOMediaBSDClient, 14);
    OSMetaClassDeclareReservedUnused(IOMediaBSDClient, 15);
};

#endif /* __cplusplus */
#endif /* KERNEL */
#endif /* !_IOMEDIABSDCLIENT_H */
