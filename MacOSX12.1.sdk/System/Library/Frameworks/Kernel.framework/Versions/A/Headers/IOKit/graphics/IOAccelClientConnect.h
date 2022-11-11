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

#ifndef _IOACCEL_CLIENT_CONNECT_H
#define _IOACCEL_CLIENT_CONNECT_H


/*
** The IOAccelerator service name
*/
#define kIOAcceleratorClassName "IOAccelerator"


/*
** IOAccelerator public client types.  Private client types start with
** kIOAccelNumClientTypes.
*/
enum eIOAcceleratorClientTypes {
        kIOAccelSurfaceClientType,
        kIOAccelNumClientTypes,
#ifndef _OPEN_SOURCE_
        kIOAccelSurface2ClientType = 0x20
#endif /* _OPEN_SOURCE_ */
};


#endif /* _IOACCEL_CLIENT_CONNECT_H */

