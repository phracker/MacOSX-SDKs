/*
 * Copyright (c) 1999-2000 Apple Computer, Inc. All rights reserved.
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
/*
 * HISTORY
 *
 */

/* IOCFSerialize serializes CFObjects to a format suitable for passing
 * to the kernel. */

#ifndef __IOKIT_IOCFSERIALIZE_H
#define __IOKIT_IOCFSERIALIZE_H

#include <CoreFoundation/CFBase.h>
#include <CoreFoundation/CFData.h>

#if defined(__cplusplus)
extern "C" {
#endif

enum {
    kIOCFSerializeToBinary	= 0x00000001
};

CF_RETURNS_RETAINED
CFDataRef
IOCFSerialize( CFTypeRef object, CFOptionFlags options );

#if defined(__cplusplus)
}
#endif

#endif /* __IOKIT_IOCFSERIALIZE_H */
