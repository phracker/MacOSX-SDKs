/*
 * Copyright (c) 2004 Apple Computer, Inc. All rights reserved.
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

#ifndef _MEMBERSHIP_H_
#define _MEMBERSHIP_H_

#include <uuid/uuid.h>
#include <ntsid.h>

#define ID_TYPE_UID 0
#define ID_TYPE_GID 1

__BEGIN_DECLS

int mbr_uid_to_uuid(uid_t id, uuid_t uu);
int mbr_gid_to_uuid(gid_t id, uuid_t uu);
int mbr_uuid_to_id( const uuid_t uu, uid_t* id, int* id_type);
int mbr_sid_to_uuid( const nt_sid_t* sid, uuid_t uu);
int mbr_uuid_to_sid( const uuid_t uu, nt_sid_t* sid);

int mbr_check_membership(uuid_t user, uuid_t group, int* ismember);

__END_DECLS

#endif /* !_MEMBERSHIP_H_ */
