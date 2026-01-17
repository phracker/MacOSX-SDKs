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
/*
 * @OSF_COPYRIGHT@
 */

/*
 * Mach MIG Subsystem Interfaces
 */

#ifndef	_MACH_MIG_H_
#define _MACH_MIG_H_

#include <mach/port.h>
#include <mach/message.h>
#include <mach/kern_return.h>

/*
 * Definition for MIG-generated server stub routines.  These routines
 * unpack the request message, call the server procedure, and pack the
 * reply message.
 */
typedef void	(*mig_stub_routine_t) (mach_msg_header_t *InHeadP,
				       mach_msg_header_t *OutHeadP);

typedef mig_stub_routine_t mig_routine_t;

/*
 * Definition for MIG-generated server routine.  This routine takes a
 * message, and returns the appropriate stub function for handling that
 * message.
 */
typedef mig_routine_t (*mig_server_routine_t) (mach_msg_header_t *InHeadP);

/*
 * Generic definition for implementation routines.  These routines do
 * the real work associated with this request.  This generic type is
 * used for keeping the pointers in the subsystem array.
 */
typedef kern_return_t   (*mig_impl_routine_t)(void);

typedef struct mig_routine_descriptor {
	mig_stub_routine_t	 stub_routine;	/* Unmarshalling function   */
	mach_msg_size_t		 max_reply_msg; /* Max size for this reply  */
} mig_routine_descriptor;
typedef mig_routine_descriptor  *mig_routine_descriptor_t;

typedef struct mig_subsystem {
	mig_server_routine_t	 server;	/* server routine	    */
	mach_msg_id_t		 start;		/* Min routine number	    */
	mach_msg_id_t		 end;		/* Max routine number + 1   */
	mach_msg_size_t		 max_reply;	/* Max reply message size   */
	mach_msg_size_t		 max_request;	/* Max request msg size     */
	mig_routine_descriptor   routine[1];	/* Routine descriptor array */
} *mig_subsystem_t;


#endif /* _MACH_MIG_H_ */
