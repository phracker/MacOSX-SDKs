/*
 * Copyright (c) 1999 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * Portions Copyright (c) 1999 Apple Computer, Inc.  All Rights
 * Reserved.  This file contains Original Code and/or Modifications of
 * Original Code as defined in and that are subject to the Apple Public
 * Source License Version 1.1 (the "License").  You may not use this file
 * except in compliance with the License.  Please obtain a copy of the
 * License at http://www.apple.com/publicsource and read it before using
 * this file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE OR NON- INFRINGEMENT.  Please see the
 * License for the specific language governing rights and limitations
 * under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */
/*
 * Lookup protocol definitions - internal to NeXT
 * Copyright (C) 1989 by NeXT, Inc.
 */

/*
 * the port to lookupd is obtained through the (internal)
 * _lookupd_port() syscall instead of through the nameserver
 * with LOOKUP_SERVER_NAME as "C Library Lookup"
 */

#define UNIT_SIZE 4

typedef struct unit {
	char data[UNIT_SIZE];
} unit;

#define MAX_INLINE_UNITS 4095
#define MAX_LOOKUP_NAMELEN 256
#define MAX_INLINE_DATA (MAX_INLINE_UNITS * sizeof(unit))

typedef char lookup_name[MAX_LOOKUP_NAMELEN];
typedef unit inline_data[MAX_INLINE_UNITS];
typedef char *ooline_data;
