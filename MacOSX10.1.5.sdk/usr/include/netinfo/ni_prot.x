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
 * NetInfo protocol specification
 * Copyright (C) 1989 by NeXT, Inc.
 */

/* Preamble appearing on all generated output */
#ifndef NOPREAMBLE
%/*
% * Output of the RPC protocol compiler: DO NOT EDIT
% * Copyright (C) 1989 by NeXT, Inc.
% */
#endif

#ifndef RPC_HDR
%#include <string.h>
#endif

const NI_NAME_MAXLEN = 65535;
const NI_NAMELIST_MAXLEN = 65535;
const NI_PROPLIST_MAXLEN = 65535;
const NI_IDLIST_MAXLEN = 1048576;

/*
 * Every object has a unique ID. One part of the ID identifies the object
 * itself. The other identifies the instance of the object. Every time
 * an object is written or an object is destroyed and then reallocated, 
 * its instance is incremented. 
 *
 * All read operations ignore the instance field. All write operations 
 * refuse to operate on the object if there is an instance mismatch.
 */

/*
 * Don't go through unnecessary overhead for xdr_ni_index using typedef
 * rpcgen needs an optimizer so we don't have to do this!
 */
#ifdef RPC_HDR
%typedef unsigned long ni_index;
#endif
#define ni_index unsigned long

struct ni_id {
	ni_index nii_object;
	ni_index nii_instance;
};


/*
 * Names are assumed to contain human-readable ASCII characters.
 */
typedef string ni_name<NI_NAME_MAXLEN>;


typedef ni_name ni_namelist<NI_NAMELIST_MAXLEN>;

/*
 * A property
 */
struct ni_property {
	ni_name nip_name;
	ni_namelist nip_val;
};

/*
 * A list of properties
 */
typedef ni_property ni_proplist<NI_PROPLIST_MAXLEN>;

/*
 * A list of IDs (yet another variable-length array)
 */
typedef ni_index ni_idlist<NI_IDLIST_MAXLEN>;


/*
 * A name object
 */
struct ni_object {
	ni_id nio_id;
	ni_proplist nio_props;
	ni_index nio_parent;
	ni_idlist nio_children;
};


/*
 * All operations return a status indicating either that the requested 
 * operation succeeded or why it failed.
 */
enum ni_status {
	NI_OK,		/* Operation succeeded */
	NI_BADID,	/* ID is invalid */
	NI_STALE,	/* Write attempted on stale version of object */
	NI_NOSPACE,	/* No space available for write operation */
	NI_PERM,	/* Permission denied */
	NI_NODIR,	/* No such directory */
	NI_NOPROP,	/* No such property */
	NI_NONAME,	/* No such name */
	NI_NOTEMPTY,	/* Cannot delete name object with children */
	NI_UNRELATED,	/* Object is not child of parent: cannot destroy */
	NI_SERIAL,	/* Serialization error */
	NI_NETROOT,	/* Hit network root domain */
	NI_NORESPONSE,	/* No response from remote parent */
	NI_RDONLY,	/* No writes allowed: all objects are read-only */
	NI_SYSTEMERR,	/* generic remote error */
	NI_ALIVE,	/* Can't regenerate: already in use */
	NI_NOTMASTER,	/* Operation makes no sense on clone */
	NI_CANTFINDADDRESS, /* Can't find address of server */
	NI_DUPTAG,	/* Duplicate domain tag: can't serve it */
	NI_NOTAG,	/* No such tag */
	NI_AUTHERROR,	/* Authentication error */
	NI_NOUSER,	/* No such user */
	NI_MASTERBUSY,	/* Master server is busy */
	NI_INVALIDDOMAIN,	/* Invalid Domain */
	NI_BADOP,	 /* Invalid operation on master */
	NI_FAILED = 9999	/* generic local error */
};

/*
 * Wrappers needed to handle arguments and results
 */
union ni_id_res switch (ni_status status) {
case NI_OK:
	ni_id id;
default:
	void;
};

struct ni_parent_stuff {
	ni_index object_id;
	ni_id self_id;
};

union ni_parent_res switch (ni_status status) {
case NI_OK:
	struct ni_parent_stuff stuff;
default:
	void;
};

struct ni_children_stuff {
	ni_idlist children;
	ni_id self_id;
};

union ni_children_res switch (ni_status status) {
case NI_OK:
	ni_children_stuff stuff;
default:
	void;
};

struct ni_entry {
	ni_index id;
	ni_namelist *names;
};

typedef ni_entry ni_entrylist<NI_IDLIST_MAXLEN>;

struct ni_list_stuff {
	ni_entrylist entries;
	ni_id self_id;
};

union ni_list_res switch (ni_status status) {
case NI_OK:
	ni_list_stuff stuff;
default:
	void;
};

struct ni_proplist_stuff {
	ni_id id;
	ni_proplist props;
};

struct ni_create_args {
	ni_id id;
	ni_proplist props;
	ni_index where;
	ni_id *target_id;
};

union ni_proplist_res switch (ni_status status) {
case NI_OK:
	ni_proplist_stuff stuff;
default:
	void;
};
	
struct ni_create_stuff {
	ni_id id;
	ni_id self_id;
};

union ni_create_res switch (ni_status status) {
case NI_OK:
	ni_create_stuff stuff;
default:
	void;
};

struct ni_destroy_args {
	ni_id parent_id;
	ni_id self_id;
};

struct ni_lookup_args {
	ni_id id;
	ni_name key;
	ni_name value;
};

struct ni_lookup_stuff {
	ni_idlist idlist;
	ni_id self_id;
};

union ni_lookup_res switch (ni_status status) {
case NI_OK:
	ni_lookup_stuff stuff;
default:
	void;
};


struct ni_name_args {
	ni_id id;
	ni_name name;
};

struct ni_createprop_args {
	ni_id id;
	ni_property prop;
	ni_index where;
};

struct ni_writeprop_args {
	ni_id id;
	ni_index prop_index;
	ni_namelist values;
};

struct ni_prop_args {
	ni_id id;
	ni_index prop_index;
};

struct ni_namelist_stuff {
	ni_namelist values;
	ni_id self_id;
};

union ni_namelist_res switch (ni_status status) {
case NI_OK:
	ni_namelist_stuff stuff;
default:
	void;
};

struct ni_propname_args {
	ni_id id;
	ni_index prop_index;
	ni_name name;
};

struct ni_createname_args {
	ni_id id;
	ni_index prop_index;
	ni_name name;
	ni_index where;
};

struct ni_nameindex_args {
	ni_id id;
	ni_index prop_index;
	ni_index name_index;
};

struct ni_writename_args {
	ni_id id;
	ni_index prop_index;
	ni_index name_index;
	ni_name name;
};

struct ni_readname_stuff {
	ni_id id;
	ni_name name;
};

union ni_readname_res switch (ni_status status) {
case NI_OK:
	ni_readname_stuff stuff;
default:
	void;
};

struct ni_binding {
	ni_name tag;
	unsigned addr;
};

union ni_rparent_res switch (ni_status status) {
case NI_OK:
	ni_binding binding;
default:
	void;
};

typedef struct ni_object_node *ni_object_list;
struct ni_object_node {
	ni_object object;
	ni_object_list next;
};

struct ni_readall_stuff {
	unsigned checksum;
	ni_index highestid;
	ni_object_list list;
};
	
union ni_readall_res switch (ni_status status) {
case NI_OK:
	ni_readall_stuff stuff;
default:
	void;
};

typedef ni_proplist ni_proplist_list<NI_IDLIST_MAXLEN>;

struct ni_listall_stuff {
	ni_id self_id;
	ni_proplist_list entries;
};

union ni_listall_res switch (ni_status status) {
case NI_OK:
	ni_listall_stuff stuff;
default:
	void;
};


program NI_PROG {
	version NI_VERS {
		void
		_NI_PING(void) = 0;
		/*
		 * Get various server statistics
		 */
		ni_proplist
		_NI_STATISTICS(void) = 1;

		/*
		 * Procedures dealing with nodes
		 */
		ni_id_res
		_NI_ROOT(void) = 2;

		ni_id_res
		_NI_SELF(ni_id) = 3;

		ni_parent_res
		_NI_PARENT(ni_id) = 4;	

		ni_create_res
		_NI_CREATE(ni_create_args) = 5;	

		ni_id_res
		_NI_DESTROY(ni_destroy_args) = 6; 

		ni_proplist_res
		_NI_READ(ni_id) = 7;

		ni_id_res
		_NI_WRITE(ni_proplist_stuff) = 8;

		ni_children_res
		_NI_CHILDREN(ni_id) = 9;

		ni_lookup_res
		_NI_LOOKUP(ni_lookup_args) = 10; 

		ni_list_res
		_NI_LIST(ni_name_args) = 11;

		/*
		 * Procedures dealing with properties
		 */
		ni_id_res
		_NI_CREATEPROP(ni_createprop_args) = 12; 
		
		ni_id_res
		_NI_DESTROYPROP(ni_prop_args) = 13; 

		ni_namelist_res
		_NI_READPROP(ni_prop_args) = 14;	

		ni_id_res
		_NI_WRITEPROP(ni_writeprop_args) = 15;

		ni_id_res
		_NI_RENAMEPROP(ni_propname_args) = 16;
		
		ni_namelist_res
		_NI_LISTPROPS(ni_id) = 17;

		/*
		 * Procedures dealing with names
		 */
		ni_id_res
		_NI_CREATENAME(ni_createname_args) = 18;

		ni_id_res
		_NI_DESTROYNAME(ni_nameindex_args) = 19;

		ni_readname_res
		_NI_READNAME(ni_nameindex_args) = 20;

		ni_id_res
		_NI_WRITENAME(ni_writename_args) = 21;

		/*
		 * Returns the address of this domain's remote parent
		 */
		ni_rparent_res
		_NI_RPARENT(void) = 22;

		/*
		 * List all properties of each subdirectory, not just
		 * just a single named property.
		 *
		 * WARNING: this routine is dangerous and may be
		 * removed from future implementations of the protocol.
		 * While it is good the the network in that there is
		 * less data on it because a lot is done in a single call, 
		 * it is bad for the server because it ties it up and locks 
		 * others out.
		 */
		ni_listall_res
		_NI_LISTALL(ni_id) = 23;

		/*
		 * Answers only if the given binding is served
		 */
		void
		_NI_BIND(ni_binding) = 24;
		
		/*
		 * Read the entire database if the checksum is different
		 * Implemented by master only.
		 */
		ni_readall_res
		_NI_READALL(unsigned) = 25;

		/*
		 * Informs server that master has crashed. Hands out
		 * latest checksum.
		 */
		void
		_NI_CRASHED(unsigned) = 26;

		/*
		 * If master, force clones to resync.
		 * If clone, resync with master.
		 */
		ni_status
		_NI_RESYNC(void) = 27; 


		/*
		 * Extra procedure added for performance
		 * Terminates on first hit, returns proplist
	 	 */
		ni_proplist_res
		_NI_LOOKUPREAD(ni_lookup_args) = 28;
	} = 2;
} = 200100000;
