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
 * NetInfo library entry points
 * Copyright (C) 1989 by NeXT, Inc.
 */

#ifndef __NI_HEADER__
#define __NI_HEADER__

#ifndef SUN_RPC
#define SUN_RPC 1
#endif

#include <rpc/rpc.h>
#include <netinfo/ni_prot.h>
#include <netinfo/nibind_prot.h>
typedef const char *ni_name_const;
#include <netinfo/ni_util.h>

/*
 * Define some shortcuts
 */
#define ninl_len ni_namelist_len
#define ninl_val ni_namelist_val

#define nipl_len ni_proplist_len
#define nipl_val ni_proplist_val

#define niil_len ni_idlist_len
#define niil_val ni_idlist_val

#define niel_len ni_entrylist_len
#define niel_val ni_entrylist_val

#define nipll_len ni_proplist_list_len
#define nipll_val ni_proplist_list_val

/*
 * Arg struct for ni_fancyopen
 */
typedef struct ni_fancyopenargs {
	int rtimeout; /* read timeout - 0 for default */
	int wtimeout; /* write timeout - 0 for default */
	int abort;    /* give up on timeout or failure? */
	int needwrite; /* need to do writes on this handle? */
} ni_fancyopenargs;


void *ni_new(void *, const char *);
void *ni_connect(struct sockaddr_in *, const char *);
ni_status ni_addrtag(void *, struct sockaddr_in *, ni_name *);
void ni_free(void *);
const char *ni_error(ni_status);

ni_status ni_statistics(void *, ni_proplist *);
ni_status ni_root(void *, ni_id *);
ni_status ni_self(void *, ni_id *);
ni_status ni_parent(void *, ni_id *, ni_index *);

ni_status ni_create(void *, ni_id *, ni_proplist, ni_id *, ni_index);
ni_status ni_destroy(void *, ni_id *, ni_id);

ni_status ni_read(void *, ni_id *, ni_proplist *);
ni_status ni_write(void *, ni_id *, ni_proplist);

ni_status ni_children(void *, ni_id *, ni_idlist *);
ni_status ni_list(void *, ni_id *, ni_name_const, ni_entrylist *);
ni_status ni_listall(void *, ni_id *, ni_proplist_list *);
ni_status ni_lookup(void *, ni_id *, ni_name_const, ni_name_const, 
		    ni_idlist *);
ni_status ni_lookupread(void *, ni_id *, ni_name_const, ni_name_const, 
			ni_proplist *);
ni_status ni_lookupprop(void *, ni_id *, ni_name_const, ni_namelist *);
ni_status ni_renameprop(void *, ni_id *, ni_index, ni_name_const);
ni_status ni_listprops(void *, ni_id *, ni_namelist *);

ni_status ni_createprop(void *, ni_id *, ni_property, ni_index);
ni_status ni_destroyprop(void *, ni_id *, ni_index);
ni_status ni_readprop(void *, ni_id *, ni_index, ni_namelist *);
ni_status ni_writeprop(void *, ni_id *, ni_index, ni_namelist);

ni_status ni_createname(void *, ni_id *, ni_index, ni_name_const, ni_index);
ni_status ni_destroyname(void *, ni_id *, ni_index, ni_index);
ni_status ni_readname(void *, ni_id *, ni_index, ni_index, ni_name *);
ni_status ni_writename(void *, ni_id *, ni_index, ni_index, ni_name_const);

ni_status ni_pathsearch(void *, ni_id *, ni_name_const);
ni_status ni_open(void *, ni_name_const, void **);
ni_status ni_fancyopen(void *, ni_name_const, void **, ni_fancyopenargs *);

ni_status ni_pwdomain(void *, ni_name *);

ni_status ni_resync(void *);

ni_status ni_setuser(void *, ni_name_const);
ni_status ni_setpassword(void *, ni_name_const);
void ni_setreadtimeout(void *, int);
void ni_setwritetimeout(void *, int);
void ni_setabort(void *, int);
void ni_needwrite(void *, int);

#endif __NI_HEADER__