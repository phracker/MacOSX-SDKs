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
 * NetInfo binder protocol specification
 * Copyright (C) 1989 by NeXT, Inc.
 */

/* Preamble appearing on all generated output */
#ifndef NOPREAMBLE
%/*
% * Output of the RPC protocol compiler: DO NOT EDIT
% * Copyright (C) 1989 by NeXT, Inc.
% */
#endif

#ifdef RPC_HDR
%#ifndef NI_PROG
%#include <netinfo/ni_prot.h>
%#endif
#else
%#include <string.h>
#endif

const NIBIND_MAXREGS = 32;

struct nibind_addrinfo {
	unsigned udp_port;
	unsigned tcp_port;
};

struct nibind_registration {
	ni_name tag;
	nibind_addrinfo addrs;
};

union nibind_getregister_res switch (ni_status status) {
case NI_OK:
	nibind_addrinfo addrs;
default:
	void;
};

union nibind_listreg_res switch (ni_status status) {
case NI_OK:
	nibind_registration regs<NIBIND_MAXREGS>;
default:
	void;
};

struct nibind_clone_args {
	ni_name tag;
	ni_name master_name;
	unsigned master_addr;
	ni_name master_tag;
};
	
struct nibind_bind_args {
	unsigned client_addr;
	ni_name client_tag;
	ni_name server_tag;
};

program NIBIND_PROG {
	version NIBIND_VERS {
		void
		NIBIND_PING(void) = 0;

		ni_status
		NIBIND_REGISTER(nibind_registration) = 1;

		ni_status
		NIBIND_UNREGISTER(ni_name) = 2;

		nibind_getregister_res
		NIBIND_GETREGISTER(ni_name) = 3;

		nibind_listreg_res
		NIBIND_LISTREG(void) = 4;

		ni_status
		NIBIND_CREATEMASTER(ni_name) = 5;

		ni_status
		NIBIND_CREATECLONE(nibind_clone_args) = 6;

		ni_status
		NIBIND_DESTROYDOMAIN(ni_name) = 7;

		/*
		 * Answers only if the given binding is served
		 */
		void
		NIBIND_BIND(nibind_bind_args) = 8;
	} = 1;
} = 200100001;
