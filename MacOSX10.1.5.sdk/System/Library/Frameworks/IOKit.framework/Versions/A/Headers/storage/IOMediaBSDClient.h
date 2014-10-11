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

#ifndef _IOMEDIABSDCLIENT_H
#define _IOMEDIABSDCLIENT_H

#include <sys/ioctl.h>
#include <sys/types.h>

/*
 * Definitions
 *
 * ioctl                        description
 * ---------------------------- ------------------------------------------------
 * DKIOCEJECT                   eject media
 *
 * DKIOCGETBLOCKSIZE            get media's preferred block size
 * DKIOCSETBLOCKSIZE            set media's preferred block size
 * DKIOCGETBLOCKCOUNT           get media's block count
 * DKIOCGETFIRMWAREPATH         get media's firmware path
 *
 * DKIOCISFORMATTED             is media formatted?
 * DKIOCISWRITABLE              is media writable?
 *
 * DKIOCGETMAXBLOCKCOUNTREAD    get maximum block count for reads
 * DKIOCGETMAXBLOCKCOUNTWRITE   get maximum block count for writes
 * DKIOCGETMAXSEGMENTCOUNTREAD  get maximum physical segment count for reads
 * DKIOCGETMAXSEGMENTCOUNTWRITE get maximum physical segment count for writes
 */

typedef struct
{
    char path[128];
} dk_firmware_path_t;

#define DKIOCEJECT                   _IO('d', 21)

#define DKIOCGETBLOCKSIZE            _IOR('d', 24, u_int32_t)
#define DKIOCSETBLOCKSIZE            _IOW('d', 24, u_int32_t)
#define DKIOCGETBLOCKCOUNT           _IOR('d', 25, u_int64_t)
#define DKIOCGETBLOCKCOUNT32         _IOR('d', 25, u_int32_t)
#define DKIOCGETFIRMWAREPATH         _IOR('d', 28, dk_firmware_path_t)

#define DKIOCISFORMATTED             _IOR('d', 23, u_int32_t)
#define DKIOCISWRITABLE              _IOR('d', 29, u_int32_t)

#define DKIOCGETMAXBLOCKCOUNTREAD    _IOR('d', 64, u_int64_t)
#define DKIOCGETMAXBLOCKCOUNTWRITE   _IOR('d', 65, u_int64_t)
#define DKIOCGETMAXSEGMENTCOUNTREAD  _IOR('d', 66, u_int64_t)
#define DKIOCGETMAXSEGMENTCOUNTWRITE _IOR('d', 67, u_int64_t)

/*
 * Kernel
 */

#if defined(KERNEL) && defined(__cplusplus)

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
     * This method is called before we are detached from the provider object.
     */

    virtual void stop(IOService * provider);

    /* DEPRECATED */ virtual AnchorTable * getAnchors();
    /* DEPRECATED */ virtual MinorTable *  getMinors();
    /* DEPRECATED */ virtual MinorSlot *   getMinor(UInt32 minorID);

    /*
     * Process a foreign ioctl.
     */

    virtual int ioctl(dev_t, u_long cmd, caddr_t data, int, struct proc *);

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

#endif /* defined(KERNEL) && defined(__cplusplus) */

#endif /* !_IOMEDIABSDCLIENT_H */
