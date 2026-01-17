/*
 * Copyright (c) 2000 Apple Computer, Inc. All rights reserved.
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

#ifndef _IOACCEL_SURFACE_CONTROL_H
#define _IOACCEL_SURFACE_CONTROL_H

#include <IOKit/graphics/IOAccelSurfaceConnect.h>

#define IOACCEL_SURFACE_CONTROL_REV	5

typedef struct IOAccelConnectStruct *IOAccelConnect;


/* Create an accelerated surface and attach it to a CGS surface */
IOReturn IOAccelCreateSurface( io_service_t service, UInt32 wid, eIOAccelSurfaceModeBits modebits, IOAccelConnect *connect );
 
/* Fix surface size & scaling */
IOReturn IOAccelSetSurfaceScale( IOAccelConnect connect, IOOptionBits options,
                                    IOAccelSurfaceScaling * scaling, UInt32 scalingSize );

/* Detach an an accelerated surface from a CGS surface and destroy it*/
IOReturn IOAccelDestroySurface( IOAccelConnect connect );

/* Change the visible region of the accelerated surface */
IOReturn IOAccelSetSurfaceShape( IOAccelConnect connect, IOAccelDeviceRegion *region, eIOAccelSurfaceShapeBits options );
IOReturn IOAccelSetSurfaceFramebufferShape( IOAccelConnect connect, IOAccelDeviceRegion *rgn,
                                            eIOAccelSurfaceShapeBits options, UInt32 framebufferIndex );

/* Block until the last visible region change applied to an accelerated surface is complete */
IOReturn IOAccelWaitForSurface( IOAccelConnect connect );

/* Get the back buffer of the surface.  Supplies client virtual address. */
IOReturn IOAccelLockSurface( IOAccelConnect connect, IOAccelSurfaceInformation * info, UInt32 infoSize );

/* Release the lock on the surface's vram */
IOReturn IOAccelUnlockSurface( IOAccelConnect connect );

IOReturn IOAccelQueryLockSurface( IOAccelConnect connect );
IOReturn IOAccelWriteLockSurface( IOAccelConnect connect, IOAccelSurfaceInformation * info, UInt32 infoSize );
IOReturn IOAccelWriteUnlockSurface( IOAccelConnect connect );
IOReturn IOAccelReadLockSurface( IOAccelConnect connect, IOAccelSurfaceInformation * info, UInt32 infoSize );
IOReturn IOAccelReadUnlockSurface( IOAccelConnect connect );

/* Flush surface to visible region */
IOReturn IOAccelFlushSurface( IOAccelConnect connect, IOOptionBits options );
IOReturn IOAccelFlushSurfaceOnFramebuffers( IOAccelConnect connect, IOOptionBits options, UInt32 framebufferMask );


/* Read surface back buffer */
IOReturn IOAccelReadSurface( IOAccelConnect connect, IOAccelSurfaceReadData * parameters );

#endif /* _IOACCEL_SURFACE_CONTROL_H */

