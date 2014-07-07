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
 * Lookup server protocol - Internal to NeXT
 * Copyright (C) 1989 by NeXT, Inc.
 * 
 * This server uses a protocol based upon XDR layered on top of 
 * a mach rpc call. There are three procedures defined in the "lookup.defs"
 * file. A "lookup_link" operation takes a procedure string name and returns a
 * number to be used in the other two calls. "lookup_all" takes a procedure
 * number and XDR'd arguments and returns XDR'd results. It returns the
 * entire list of entries. "lookup_one" has a similar calling convention,
 * but returns only a single entry.
 *
 * The syntax of calls described here in comments looks like this:
 *
 *		result_type procedure_name(arg_type1 arg1, arg_type2 arg2, ...)
 *
 *	The arguments are assumed to be XDR'd in sequence and a single XDR'd
 * 	result is returned.
 */
const _LU_MAXLUSTRLEN = 256;

const _LU_MAXGRP = 1024;
const _LU_MAXHNAMES = 32;
const _LU_MAXADDRS = 32;
const _LU_MAXNNAMES = 32;
const _LU_MAXPNAMES = 32;
const _LU_MAXSNAMES = 32;
const _LU_MAXRNAMES = 32;
const _LU_MAXPRNAMES = 32;
const _LU_MAXPRPROPS = 1024;
const _LU_MAX_BOOTPARAMS_KV = 32;
const _LU_MAXALIASMEMBERS = 4096;


typedef string _lu_string<_LU_MAXLUSTRLEN>;


/*
 * Calls available:
 *	int putpwpasswd(_lu_string long, _lu_string old, _lu_string new)
 * 	_lu_passwd * getpwuid(int uid)
 * 	_lu_passwd * getpwnam(_lu_string name)
 * 	_lu_passwd<> getpwent(void)
 */
struct _lu_passwd {
	_lu_string pw_name;
	_lu_string pw_passwd;
	int pw_uid;
	int pw_gid;
	int pw_change;
	_lu_string pw_class;
	_lu_string pw_gecos;
	_lu_string pw_dir;
	_lu_string pw_shell;
	int pw_expire;
};
typedef _lu_passwd *_lu_passwd_ptr;


/*
 * Calls available:
 * 	_lu_group * getgrgid(int gid)
 * 	_lu_group * getgrnam(_lu_string name)
 * 	_lu_group<> getgrent(void)
 */
struct _lu_group {
	_lu_string gr_name;
	_lu_string gr_passwd;
	int gr_gid;
	_lu_string gr_mem<_LU_MAXGRP>;
};
typedef _lu_group *_lu_group_ptr;

/*
 * Calls available:
 * 	_lu_hostent * gethostbyaddr(unsigned long addr) -- IP only
 * 	_lu_hostent * gethostbyname(_lu_string name)
 * 	_lu_hostent<> gethostent(void)
 */
struct _lu_hostent {
	_lu_string h_names<_LU_MAXHNAMES>;
	unsigned long h_addrs<_LU_MAXADDRS>; /* IP only */
};
typedef _lu_hostent *_lu_hostent_ptr;

/*
 * Calls available:
 * 	_lu_netent * getnetbyaddr(unsigned long addr) --IP only
 * 	_lu_netent * getnetbyname(_lu_string name)
 * 	_lu_netent<> getnetent(void)
 */
struct _lu_netent {
	_lu_string n_names<_LU_MAXNNAMES>;
	unsigned long n_net;	/* IP only */
};
typedef _lu_netent *_lu_netent_ptr;


/*
 * Calls available:
 * 	_lu_servent * getservbyport(int port, _lu_string proto)
 * 	_lu_servent * getservbyname(_lu_string name, _lu_string proto)
 * 	_lu_servent<> getservent(void)
 */
struct _lu_servent {
	_lu_string s_names<_LU_MAXSNAMES>;
	int s_port;
	_lu_string s_proto;
};
typedef _lu_servent *_lu_servent_ptr;

/*
 * Calls available:
 * 	_lu_protoent * getprotobynumber(int number)
 * 	_lu_protoent * getprotobyname(_lu_string name)
 * 	_lu_protoent<> getprotoent(void)
 */
struct _lu_protoent {
	_lu_string p_names<_LU_MAXPNAMES>;
	int p_proto;
};
typedef _lu_protoent *_lu_protoent_ptr;


/*
 * Calls available:
 * 	_lu_rpcent * getrpcbynumber(int number)
 * 	_lu_rpcent * getrpcbyname(_lu_string name)
 * 	_lu_rpcent<> getrpcent(void)
 */
struct _lu_rpcent {
	_lu_string r_names<_LU_MAXRNAMES>;
	int r_number;
};
typedef _lu_rpcent *_lu_rpcent_ptr;

/* 
 * Calls available:
 * 	_lu_fsent<> getfsent(void)
 * 	_lu_fsent * getfsbyname(_lu_string name)
 */
struct _lu_fsent {
	_lu_string fs_spec;
	_lu_string fs_file;
	_lu_string fs_vfstype;
	_lu_string fs_mntops;
	_lu_string fs_type;
	int fs_freq;
	int fs_passno;
};
typedef _lu_fsent *_lu_fsent_ptr;

/* 
 * Calls available:
 *	_lu_prdb_ent * prdb_getbyname
 * 	_lu_prdb_ent<> prdb_get(void)
 */
struct _lu_prdb_property {
	_lu_string pp_key;
	_lu_string pp_value;
};

struct _lu_prdb_ent {
	_lu_string pe_names<_LU_MAXPRNAMES>;
	_lu_prdb_property pe_props<_LU_MAXPRPROPS>;
};
typedef _lu_prdb_ent *_lu_prdb_ent_ptr;


/* 
 * Calls available:
 *	_lu_bootp_ent * bootp_getbyip(unsigned long addr)
 *	_lu_bootp_ent * bootp_getbyether(opaque bootp_enaddr[6])
 */
struct _lu_bootp_ent {
	_lu_string bootp_name;
	_lu_string bootp_bootfile;
	unsigned long bootp_ipaddr;
	opaque bootp_enaddr[6];
};
typedef _lu_bootp_ent *_lu_bootp_ent_ptr;

/*
 * Calls available:
 *	_lu_bootparams_ent * bootparams_getbyname(_lu_string name)
 *	_lu_bootparams_ent<> bootparams_getent(void)
 */
struct _lu_bootparams_ent {
	_lu_string bootparams_name;
	_lu_string bootparams_keyvalues<_LU_MAX_BOOTPARAMS_KV>;
};
typedef _lu_bootparams_ent *_lu_bootparams_ent_ptr;


/*
 * Calls available:
 *	_lu_aliasent * alias_getbyname(_lu_string name)
 *	_lu_aliasent<> alias_getent(void)
 */
struct _lu_aliasent {
	_lu_string alias_name;
	_lu_string alias_members<_LU_MAXALIASMEMBERS>;
	int alias_local;
};
typedef _lu_aliasent *_lu_aliasent_ptr;

/*
 * Calls available:
 *	int innetgr(_lu_innetgr_args args)
 *	_lu_netgrent<> getnetgrent(_lu_string group)
 */
struct _lu_innetgr_args {
	_lu_string group;
	_lu_string *host;
	_lu_string *user;
	_lu_string *domain;
};

struct _lu_netgrent{
	_lu_string ng_host;
	_lu_string ng_user;
	_lu_string ng_domain;
};

