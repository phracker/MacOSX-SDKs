/*
 * Copyright (c) 1999-2001,2004 Apple Computer, Inc. All Rights Reserved.
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
 *
 * emmtype.h -- Data Structures for Elective Module Managers
 */

#ifndef _EMMTYPE_H_
#define _EMMTYPE_H_  1

#include <Security/cssmtype.h>

#ifdef __cplusplus
extern "C" {
#endif

#define CSSM_HINT_CALLBACK (1)

typedef uint32 CSSM_MANAGER_EVENT_TYPES;
#define CSSM_MANAGER_SERVICE_REQUEST 1
#define CSSM_MANAGER_REPLY 2

typedef struct cssm_manager_event_notification {
    CSSM_SERVICE_MASK DestinationModuleManagerType;
    CSSM_SERVICE_MASK SourceModuleManagerType;
    CSSM_MANAGER_EVENT_TYPES Event;
    uint32 EventId;
    CSSM_DATA EventData;
} CSSM_MANAGER_EVENT_NOTIFICATION, *CSSM_MANAGER_EVENT_NOTIFICATION_PTR;

#ifdef __cplusplus
}
#endif

#endif /* _EMMTYPE_H_ */
