/*
 * Copyright (c) 1999 Apple Computer, Inc. All rights reserved.
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
/* 
 * Copyright (c) 1988 NeXT, Inc.
 *
 * HISTORY
 *  04-May-90 Created
 */

#ifndef __MONITOR_HEADER__
#define __MONITOR_HEADER__

extern void monstartup (char *lowpc, char *highpc);

extern void monitor (char *lowpc, char *highpc, char *buf, int bufsiz, int cntsiz);

extern void moncontrol (int mode);

extern void monoutput (const char *filename);

extern void moninit (void);

extern void monreset (void);

#endif	/* __MONITOR_HEADER__ */
