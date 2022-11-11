/*
 * Copyright (c) 2000-2021 Apple Inc. All rights reserved.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_START@
 *
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. The rights granted to you under the License
 * may not be used to create, or enable the creation or redistribution of,
 * unlawful or unlicensed copies of an Apple operating system, or to
 * circumvent, violate, or enable the circumvention or violation of, any
 * terms of an Apple operating system software license agreement.
 *
 * Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this file.
 *
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_END@
 */
/* Copyright (c) 1995 NeXT Computer, Inc. All Rights Reserved */
/*
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Mike Karels at Berkeley Software Design, Inc.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)sysctl.h	8.1 (Berkeley) 6/2/93
 */
/*
 * NOTICE: This file was modified by SPARTA, Inc. in 2005 to introduce
 * support for mandatory and extensible security protections.  This notice
 * is included in support of clause 2.2 (b) of the Apple Public License,
 * Version 2.0.
 */

#ifndef _SYS_SYSCTL_H_
#define _SYS_SYSCTL_H_

/*
 * These are for the eproc structure defined below.
 */
#include <sys/cdefs.h>

#include <sys/appleapiopts.h>
#include <libkern/sysctl.h>
#include <os/base.h>

#include <sys/proc.h>
#include <sys/vm.h>

/*
 * Definitions for sysctl call.  The sysctl call uses a hierarchical name
 * for objects that can be examined or modified.  The name is expressed as
 * a sequence of integers.  Like a file path name, the meaning of each
 * component depends on its place in the hierarchy.  The top-level and kern
 * identifiers are defined here, and other identifiers are defined in the
 * respective subsystem header files.
 */

#define CTL_MAXNAME     12      /* largest number of components supported */

/*
 * Each subsystem defined by sysctl defines a list of variables
 * for that subsystem. Each name is either a node with further
 * levels defined below it, or it is a leaf of some particular
 * type given below. Each sysctl level defines a set of name/type
 * pairs to be used by sysctl(1) in manipulating the subsystem.
 *
 * When declaring new sysctl names, use the CTLFLAG_LOCKED flag in the
 * type to indicate that all necessary locking will be handled
 * within the sysctl.
 *
 * Any sysctl defined without CTLFLAG_LOCKED is considered legacy
 * and will be protected by a global mutex.
 *
 * Note:	This is not optimal, so it is best to handle locking
 *		yourself, if you are able to do so.  A simple design
 *		pattern for use to avoid in a single function known
 *		to potentially be in the paging path ot doing a DMA
 *		to physical memory in a user space process is:
 *
 *			lock
 *			perform operation vs. local buffer
 *			unlock
 *			SYSCTL_OUT(rey, local buffer, length)
 *
 *		...this assumes you are not using a deep call graph
 *		or are unable to pass a local buffer address as a
 *		parameter into your deep call graph.
 *
 *		Note that very large user buffers can fail the wire
 *		if to do so would require more physical pages than
 *		are available (the caller will get an ENOMEM error,
 *		see sysctl_mem_hold() for details).
 */
struct ctlname {
	char    *ctl_name;      /* subsystem name */
	int     ctl_type;       /* type of name */
};

#define CTLTYPE             0xf             /* Mask for the type */
#define CTLTYPE_NODE        1               /* name is a node */
#define CTLTYPE_INT         2               /* name describes an integer */
#define CTLTYPE_STRING      3               /* name describes a string */
#define CTLTYPE_QUAD        4               /* name describes a 64-bit number */
#define CTLTYPE_OPAQUE      5               /* name describes a structure */
#define CTLTYPE_STRUCT      CTLTYPE_OPAQUE  /* name describes a structure */

#define CTLFLAG_RD          0x80000000      /* Allow reads of variable */
#define CTLFLAG_WR          0x40000000      /* Allow writes to the variable */
#define CTLFLAG_RW          (CTLFLAG_RD|CTLFLAG_WR)
#define CTLFLAG_NOLOCK      0x20000000      /* XXX Don't Lock */
#define CTLFLAG_ANYBODY     0x10000000      /* All users can set this var */
#define CTLFLAG_SECURE      0x08000000      /* Permit set only if securelevel<=0 */
#define CTLFLAG_MASKED      0x04000000      /* deprecated variable, do not display */
#define CTLFLAG_NOAUTO      0x02000000      /* do not auto-register */
#define CTLFLAG_KERN        0x01000000      /* valid inside the kernel */
#define CTLFLAG_LOCKED      0x00800000      /* node will handle locking itself */
#define CTLFLAG_OID2        0x00400000      /* struct sysctl_oid has version info */
#define CTLFLAG_EXPERIMENT 0x00100000 /* Allows writing w/ the trial experiment entitlement. */

/*
 * USE THIS instead of a hardwired number from the categories below
 * to get dynamically assigned sysctl entries using the linker-set
 * technology. This is the way nearly all new sysctl variables should
 * be implemented.
 *
 * e.g. SYSCTL_INT(_parent, OID_AUTO, name, CTLFLAG_RW, &variable, 0, "");
 *
 * Note that linker set technology will automatically register all nodes
 * declared like this on kernel initialization, UNLESS they are defined
 * in I/O-Kit. In this case, you have to call sysctl_register_oid()
 * manually - just like in a KEXT.
 */
#define OID_AUTO              (-1)
#define OID_AUTO_START        100 /* conventional */

#define SYSCTL_HANDLER_ARGS \
	(struct sysctl_oid *oidp __unused, void *arg1 __unused, int arg2 __unused, \
	struct sysctl_req *req)


/*
 * This describes the access space for a sysctl request.  This is needed
 * so that we can use the interface from the kernel or from user-space.
 */
struct sysctl_req {
	struct proc     *p;
	int             lock;
	user_addr_t     oldptr;         /* pointer to user supplied buffer */
	size_t          oldlen;         /* user buffer length (also returned) */
	size_t          oldidx;         /* total data iteratively copied out */
	int             (*oldfunc)(struct sysctl_req *, const void *, size_t);
	user_addr_t     newptr;         /* buffer containing new value */
	size_t          newlen;         /* length of new value */
	size_t          newidx;         /* total data iteratively copied in */
	int             (*newfunc)(struct sysctl_req *, void *, size_t);
};

SLIST_HEAD(sysctl_oid_list, sysctl_oid);

#define SYSCTL_OID_VERSION      1       /* current OID structure version */

/*
 * This describes one "oid" in the MIB tree.  Potentially more nodes can
 * be hidden behind it, expanded by the handler.
 *
 * NOTES:	We implement binary comparibility between CTLFLAG_OID2 and
 *		pre-CTLFLAG_OID2 structure in sysctl_register_oid() and in
 *		sysctl_unregister_oid() using the fact that the fields up
 *		to oid_fmt are unchanged, and that the field immediately
 *		following is on an alignment boundary following a pointer
 *		type and is also a pointer.  This lets us get the previous
 *		size of the structure, and the copy-cut-off point, using
 *		the offsetof() language primitive, and these values  are
 *		used in conjunction with the fact that earlier and future
 *		statically compiled sysctl_oid structures are declared via
 *		macros.  This lets us overload the macros so that the addition
 *		of the CTLFLAG_OID2 in newly compiled code containing sysctl
 *		node declarations, subsequently allowing us to to avoid
 *		changing the KPI used for non-static (un)registration in
 *		KEXTs.
 *
 *		Non CTLFLAG_OID2 based sysctls are deprecated and unavailable
 *		to non Intel platforms.
 *
 *		This depends on the fact that people declare SYSCTLs,
 *		rather than declaring sysctl_oid structures.  All new code
 *		should avoid declaring struct sysctl_oid's directly without
 *		the macros; the current risk for this is limited to losing
 *		your description field and ending up with a malloc'ed copy,
 *		as if it were a legacy binary static declaration via SYSCTL;
 *		in the future, we may deprecate access to a named structure
 *		type in third party code.  Use the macros, or our code will
 *		end up with compile errors when that happens.
 *
 *		Please try to include a long description of the field in any
 *		new sysctl declarations (all the macros support this).  This
 *		field may be the only human readable documentation your users
 *		get for your sysctl.
 */
struct sysctl_oid {
	struct sysctl_oid_list * OS_PTRAUTH_SIGNED_PTR("sysctl_oid.oid_parent") oid_parent;
	SLIST_ENTRY(sysctl_oid) oid_link;
	int             oid_number;
	int             oid_kind;
	void            *oid_arg1;
	int             oid_arg2;
	const char      *oid_name;
	int             (*oid_handler)SYSCTL_HANDLER_ARGS;
	const char      *oid_fmt;
	const char      *oid_descr; /* offsetof() field / long description */
	int             oid_version;
	int             oid_refcnt;
};

#define SYSCTL_IN(r, p, l) (r->newfunc)(r, p, l)
#define SYSCTL_OUT(r, p, l) (r->oldfunc)(r, p, l)

typedef int (* sysctl_handler_t) SYSCTL_HANDLER_ARGS;

__BEGIN_DECLS

/* old interface */
int sysctl_handle_int SYSCTL_HANDLER_ARGS;
int sysctl_handle_long SYSCTL_HANDLER_ARGS;
int sysctl_handle_quad SYSCTL_HANDLER_ARGS;
int sysctl_handle_int2quad SYSCTL_HANDLER_ARGS;
int sysctl_handle_string SYSCTL_HANDLER_ARGS;
int sysctl_handle_opaque SYSCTL_HANDLER_ARGS;
/* new interface */
int sysctl_io_number(struct sysctl_req *req, long long bigValue, size_t valueSize, void *pValue, int *changed);
int sysctl_io_string(struct sysctl_req *req, char *pValue, size_t valueSize, int trunc, int *changed);
int sysctl_io_opaque(struct sysctl_req *req, void *pValue, size_t valueSize, int *changed);

/*
 * These functions are used to add/remove an oid from the mib.
 */
void sysctl_register_oid(struct sysctl_oid *oidp);
void sysctl_unregister_oid(struct sysctl_oid *oidp);

#define nvram_osenvironment "osenvironment"
void sysctl_set_osenvironment(unsigned int size, const void* value);
void sysctl_unblock_osenvironment(void);

/* Deprecated */
void sysctl_register_fixed(void) __deprecated;

__END_DECLS

/* Declare an oid to allow child oids to be added to it. */
#define SYSCTL_DECL(name)                                       \
	extern struct sysctl_oid_list sysctl_##name##_children

/*
 * Macros to define sysctl entries.  Which to use?  Pure data that are
 * returned without modification, SYSCTL_<data type> is for you, like
 * SYSCTL_QUAD for a 64-bit value.  When you want to run a handler of your
 * own, SYSCTL_PROC.
 *
 * parent:	parent in name hierarchy (e.g. _kern for "kern")
 * nbr:		ID.  Almost certainly OID_AUTO ("pick one for me") for you.
 * name:	name for this particular item (e.g. "thesysctl" for "kern.thesysctl")
 * kind/access: Control flags (CTLFLAG_*).  Some notable options include:
 *                      CTLFLAG_ANYBODY:        non-root users allowed
 *                      CTLFLAG_MASKED:	        don't show in sysctl listing in userland
 *                      CTLFLAG_LOCKED:		does own locking (no additional protection needed)
 *                      CTLFLAG_KERN:		valid inside kernel (best avoided generally)
 *                      CTLFLAG_WR:		"new" value accepted
 * a1, a2:	entry-data, passed to handler (see specific macros)
 * Format String: Tells "sysctl" tool how to print data from this entry.
 *	                "A" - string
 *	                "I" - list of integers. "IU" - list of unsigned integers. space-separated.
 *	                "-" - do not print
 *	                "L" - longs, as ints with I
 *			"P" - pointer
 *                      "Q" - quads
 *                      "S","T" - clock info, see sysctl.c in system_cmds (you probably don't need this)
 * Description: unused
 */


/* This constructs a "raw" MIB oid. */
#define SYSCTL_STRUCT_INIT(parent, nbr, name, kind, a1, a2, fn, fmt, desc) {    \
	    .oid_parent     = &sysctl_##parent##_children,                      \
	    .oid_number     = nbr,                                              \
	    .oid_kind       = (int)(kind | CTLFLAG_OID2),                       \
	    .oid_arg1       = a1,                                               \
	    .oid_arg2       = (int)(a2),                                        \
	    .oid_name       = #name,                                            \
	    .oid_handler    = fn,                                               \
	    .oid_fmt        = fmt,                                              \
	    .oid_descr      = desc,                                             \
	    .oid_version    = SYSCTL_OID_VERSION,                               \
	}

#define __SYSCTL_OID(parent, nbr, name, kind, a1, a2, handler, fmt, descr) \
	struct sysctl_oid sysctl_##parent##_##name = SYSCTL_STRUCT_INIT(\
	    parent, nbr, name, kind, a1, a2, handler, fmt, descr)

#define SYSCTL_OID(parent, nbr, name, kind, a1, a2, handler, fmt, descr) \
	__SYSCTL_OID(parent, nbr, name, kind, a1, a2, handler, fmt, descr)

/* This constructs a node from which other oids can hang. */
#define SYSCTL_NODE(parent, nbr, name, access, handler, descr)                  \
	struct sysctl_oid_list sysctl_##parent##_##name##_children;             \
	SYSCTL_OID(parent, nbr, name, CTLTYPE_NODE|access,                      \
	    &sysctl_##parent##_##name##_children, 0, handler, "N", descr)

/* Oid for a string.  len can be 0 to indicate '\0' termination. */
#define SYSCTL_STRING(parent, nbr, name, access, arg, len, descr) \
	SYSCTL_OID(parent, nbr, name, CTLTYPE_STRING|access, \
	    arg, len, sysctl_handle_string, "A", descr)

#define SYSCTL_COMPAT_INT(parent, nbr, name, access, ptr, val, descr) \
	SYSCTL_OID(parent, nbr, name, CTLTYPE_INT|access, \
	    ptr, val, sysctl_handle_int, "I", descr)

#define SYSCTL_COMPAT_UINT(parent, nbr, name, access, ptr, val, descr) \
	SYSCTL_OID(parent, nbr, name, CTLTYPE_INT|access, \
	    ptr, val, sysctl_handle_int, "IU", descr)

/* Oid for an int.  If ptr is NULL, val is returned. */
#define SYSCTL_INT(parent, nbr, name, access, ptr, val, descr) \
	SYSCTL_OID(parent, nbr, name, CTLTYPE_INT|access, \
	    ptr, val, sysctl_handle_int, "I", descr); \
	_Static_assert(__builtin_constant_p(ptr) || sizeof(*(ptr)) == sizeof(int), \
	    "must be integer sized");

/* Oid for an unsigned int.  If ptr is NULL, val is returned. */
#define SYSCTL_UINT(parent, nbr, name, access, ptr, val, descr) \
	SYSCTL_OID(parent, nbr, name, CTLTYPE_INT|access, \
	    ptr, val, sysctl_handle_int, "IU", descr); \
	_Static_assert(__builtin_constant_p(ptr) || sizeof(*(ptr)) == sizeof(unsigned int), \
	    "must be integer sized");

/* Oid for a long.  The pointer must be non NULL. */
#define SYSCTL_LONG(parent, nbr, name, access, ptr, descr) \
	SYSCTL_OID(parent, nbr, name, CTLTYPE_INT|access, \
	    ptr, 0, sysctl_handle_long, "L", descr); \
	_Static_assert(__builtin_constant_p(ptr) || sizeof(*(ptr)) == sizeof(long), \
	    "must be long sized");

/* Oid for a unsigned long.  The pointer must be non NULL. */
#define SYSCTL_ULONG(parent, nbr, name, access, ptr, descr) \
	SYSCTL_OID(parent, nbr, name, CTLTYPE_INT|access, \
	    ptr, 0, sysctl_handle_long, "LU", descr); \
	_Static_assert(__builtin_constant_p(ptr) || sizeof(*(ptr)) == sizeof(unsigned long), \
	    "must be long sized");

/* Oid for a quad.  The pointer must be non NULL. */
#define SYSCTL_QUAD(parent, nbr, name, access, ptr, descr) \
	SYSCTL_OID(parent, nbr, name, CTLTYPE_QUAD|access, \
	    ptr, 0, sysctl_handle_quad, "Q", descr); \
	_Static_assert(__builtin_constant_p(ptr) || sizeof(*(ptr)) == sizeof(long long), \
	    "must be long long sized");

/* Oid for an opaque object.  Specified by a pointer and a length. */
#define SYSCTL_OPAQUE(parent, nbr, name, access, ptr, len, fmt, descr) \
	SYSCTL_OID(parent, nbr, name, CTLTYPE_OPAQUE|access, \
	        ptr, len, sysctl_handle_opaque, fmt, descr)

/* Oid for a struct.  Specified by a pointer and a type. */
#define SYSCTL_STRUCT(parent, nbr, name, access, ptr, type, descr) \
	SYSCTL_OID(parent, nbr, name, CTLTYPE_OPAQUE|access, \
	    ptr, sizeof(struct type), sysctl_handle_opaque, \
	    "S," #type, descr)

/*
 * Oid for a procedure.  Specified by a pointer and an arg.
 * CTLTYPE_* macros can determine how the "sysctl" tool deals with
 * input (e.g. converting to int).
 */
#define SYSCTL_PROC(parent, nbr, name, access, ptr, arg, handler, fmt, descr) \
	SYSCTL_OID(parent, nbr, name, access, \
	    ptr, arg, handler, fmt, descr)

/*
 * The EXPERIMENT macros below expose values for on-device experimentation (A/B testing) via Trial.
 * These values will be set shortly after boot by the KRExperiments framework based on any
 * active experiments on the device.
 * Values exposed via these macros are still normal sysctls and can be set by the superuser in the
 * development or debug kernel. However, on the release kernel they can ONLY be set by processes
 * with the com.apple.private.write-kr-experiment-factors entitlement.
 * In addition, for numeric types, special macros are provided that enforce a valid range for the value (inclusive)
 * to ensure that an errant experiment can't set a totally unexpected value. These macros also track which
 * values have been modified via sycstl(3) so that they can be inspected with the showexperiments lldb macro.
 */

struct experiment_spec {
	void *ptr; /* ptr to numeric experiment factor. */
	uint64_t min_value; /* Min value that can be set via sysctl(3) (inclusive). */
	uint64_t max_value; /* Max value that can be set via sysctl(3) (inclusive). */
	uint64_t original_value; /* First value that was overwritten via sysctl(3). */
	_Atomic bool modified; /* Has this value ever been overwritten via sysctl(3)? */
};

/*
 * The handlers for the numeric types can be easily parameterized by type.
 * So they're defined via an X macro.
 */
#define experiment_factor_numeric_types \
    X(uint, unsigned int) \
    X(int, int) \
    X(ulong, unsigned long) \
    X(long, long) \
    X(uint64, uint64_t) \
    X(int64, int64_t)

#define X(experiment_factor_typename, _) \
int experiment_factor_##experiment_factor_typename##_handler SYSCTL_HANDLER_ARGS;

experiment_factor_numeric_types
#undef X

#define __EXPERIMENT_FACTOR_SPEC(parent, name, p, min, max) \
	struct experiment_spec experiment_##parent##_##name = { \
	        .ptr = p, \
	        .min_value = min, \
	        .max_value = max, \
	        .original_value = 0, \
	        .modified = false \
	}

#define EXPERIMENT_FACTOR_UINT(parent, name, ptr, min, max, descr) \
	__EXPERIMENT_FACTOR_SPEC(parent, name, ptr, min, max); \
	_Static_assert(sizeof(*(ptr)) == sizeof(unsigned int), "must be integer sized"); \
	SYSCTL_PROC(parent, OID_AUTO, name, CTLTYPE_INT | CTLFLAG_RW | CTLFLAG_ANYBODY | CTLFLAG_EXPERIMENT, &experiment_##parent##_##name, 1, &experiment_factor_uint_handler, "IU", descr);

#define EXPERIMENT_FACTOR_INT(parent, name, ptr, min, max, descr) \
	__EXPERIMENT_FACTOR_SPEC(parent, name, ptr, min, max); \
	_Static_assert(sizeof(*(ptr)) == sizeof(int), "must be integer sized"); \
	SYSCTL_PROC(parent, OID_AUTO, name, CTLTYPE_INT | CTLFLAG_RW | CTLFLAG_ANYBODY | CTLFLAG_EXPERIMENT, &experiment_##parent##_##name, 1, &experiment_factor_int_handler, "I", descr);

#define EXPERIMENT_FACTOR_ULONG(parent, name, ptr, min, max, descr) \
	__EXPERIMENT_FACTOR_SPEC(parent, name, ptr, min, max); \
	_Static_assert(sizeof(*(ptr)) == sizeof(unsigned long), "must be long sized"); \
	SYSCTL_PROC(parent, OID_AUTO, name, CTLTYPE_INT | CTLFLAG_RW | CTLFLAG_ANYBODY | CTLFLAG_EXPERIMENT, &experiment_##parent##_##name, 1, &experiment_factor_ulong_handler, "LU", descr);

#define EXPERIMENT_FACTOR_LONG(parent, name, ptr, min, max, descr) \
	__EXPERIMENT_FACTOR_SPEC(parent, name, ptr, min, max); \
	_Static_assert(sizeof(*(ptr)) == sizeof(long), "must be long sized"); \
	SYSCTL_PROC(parent, OID_AUTO, name, CTLTYPE_INT | CTLFLAG_RW | CTLFLAG_ANYBODY | CTLFLAG_EXPERIMENT, &experiment_##parent##_##name, 1, &experiment_factor_long_handler, "L", descr);

#define EXPERIMENT_FACTOR_UINT64(parent, name, ptr, min, max, descr) \
	__EXPERIMENT_FACTOR_SPEC(parent, name, ptr, min, max); \
	_Static_assert(sizeof(*(ptr)) == sizeof(uint64_t), "must be 8 bytes"); \
	SYSCTL_PROC(parent, OID_AUTO, name, CTLTYPE_INT | CTLFLAG_RW | CTLFLAG_ANYBODY | CTLFLAG_EXPERIMENT, &experiment_##parent##_##name, 1, &experiment_factor_uint64_handler, "QU", descr);

#define EXPERIMENT_FACTOR_INT64(parent, name, ptr, min, max, descr) \
	__EXPERIMENT_FACTOR_SPEC(parent, name, ptr, min, max); \
	_Static_assert(sizeof(*(ptr)) == sizeof(int64_t), "must be 8 bytes"); \
	SYSCTL_PROC(parent, OID_AUTO, name, CTLTYPE_INT | CTLFLAG_RW | CTLFLAG_ANYBODY | CTLFLAG_EXPERIMENT, &experiment_##parent##_##name, 1, &experiment_factor_int64_handler, "Q", descr);

/*
 * Calls an user provided handler to read / write this factor.
 * Entitlement checking will still be done by sysctl, but it's the callers responsibility to validate any new values.
 * This factor will not be printed out via the showexperiments lldb macro.
 */
#define EXPERIMENT_FACTOR_PROC(parent, name, access, ptr, arg, handler, fmt, descr) \
	_Static_assert(arg != 1, "arg can not be 1"); \
	SYSCTL_PROC(parent, OID_AUTO, name, access | CTLFLAG_ANYBODY | CTLFLAG_EXPERIMENT, ptr, arg, handler, fmt, descr);


extern struct sysctl_oid_list sysctl__children;
SYSCTL_DECL(_kern);
SYSCTL_DECL(_sysctl);
SYSCTL_DECL(_vm);
SYSCTL_DECL(_vfs);
SYSCTL_DECL(_net);
SYSCTL_DECL(_debug);
SYSCTL_DECL(_hw);
SYSCTL_DECL(_machdep);
SYSCTL_DECL(_user);
#if DEVELOPMENT || DEBUG
SYSCTL_DECL(_debug_test);
#endif /* DEVELOPMENT || DEBUG */



#ifndef SYSCTL_SKMEM_UPDATE_FIELD

#define SYSCTL_SKMEM 0
#define SYSCTL_SKMEM_UPDATE_FIELD(field, value)
#define SYSCTL_SKMEM_UPDATE_AT_OFFSET(offset, value)
#define SYSCTL_SKMEM_INT(parent, oid, sysctl_name, access, ptr, offset, descr) \
	SYSCTL_INT(parent, oid, sysctl_name, access, ptr, 0, descr)

#define SYSCTL_SKMEM_TCP_INT(oid, sysctl_name, access, variable_type,   \
	    variable_name, initial_value, descr)           \
	variable_type variable_name = initial_value;                                            \
	SYSCTL_SKMEM_INT(_net_inet_tcp, oid, sysctl_name, access,                       \
	                                 &variable_name, 0, descr)

#else /* SYSCTL_SKMEM_UPDATE_FIELD */
#define SYSCTL_SKMEM 1
#endif /* SYSCTL_SKMEM_UPDATE_FIELD */





#ifdef SYSCTL_DEF_ENABLED
/*
 * Top-level identifiers
 */
#define CTL_UNSPEC      0               /* unused */
#define CTL_KERN        1               /* "high kernel": proc, limits */
#define CTL_VM          2               /* virtual memory */
#define CTL_VFS         3               /* file system, mount type is next */
#define CTL_NET         4               /* network, see socket.h */
#define CTL_DEBUG       5               /* debugging parameters */
#define CTL_HW          6               /* generic cpu/io */
#define CTL_MACHDEP     7               /* machine dependent */
#define CTL_USER        8               /* user-level */
#define CTL_MAXID       9               /* number of valid top-level ids */

#define CTL_NAMES { \
	{ 0, 0 }, \
	{ "kern", CTLTYPE_NODE }, \
	{ "vm", CTLTYPE_NODE }, \
	{ "vfs", CTLTYPE_NODE }, \
	{ "net", CTLTYPE_NODE }, \
	{ "debug", CTLTYPE_NODE }, \
	{ "hw", CTLTYPE_NODE }, \
	{ "machdep", CTLTYPE_NODE }, \
	{ "user", CTLTYPE_NODE }, \
}

/*
 * CTL_KERN identifiers
 */
#define KERN_OSTYPE              1      /* string: system version */
#define KERN_OSRELEASE           2      /* string: system release */
#define KERN_OSREV               3      /* int: system revision */
#define KERN_VERSION             4      /* string: compile time info */
#define KERN_MAXVNODES           5      /* int: max vnodes */
#define KERN_MAXPROC             6      /* int: max processes */
#define KERN_MAXFILES            7      /* int: max open files */
#define KERN_ARGMAX              8      /* int: max arguments to exec */
#define KERN_SECURELVL           9      /* int: system security level */
#define KERN_HOSTNAME           10      /* string: hostname */
#define KERN_HOSTID             11      /* int: host identifier */
#define KERN_CLOCKRATE          12      /* struct: struct clockrate */
#define KERN_VNODE              13      /* struct: vnode structures */
#define KERN_PROC               14      /* struct: process entries */
#define KERN_FILE               15      /* struct: file entries */
#define KERN_PROF               16      /* node: kernel profiling info */
#define KERN_POSIX1             17      /* int: POSIX.1 version */
#define KERN_NGROUPS            18      /* int: # of supplemental group ids */
#define KERN_JOB_CONTROL        19      /* int: is job control available */
#define KERN_SAVED_IDS          20      /* int: saved set-user/group-ID */
#define KERN_BOOTTIME           21      /* struct: time kernel was booted */
#define KERN_NISDOMAINNAME      22      /* string: YP domain name */
#define KERN_DOMAINNAME         KERN_NISDOMAINNAME
#define KERN_MAXPARTITIONS      23      /* int: number of partitions/disk */
#define KERN_KDEBUG                     24      /* int: kernel trace points */
#define KERN_UPDATEINTERVAL     25      /* int: update process sleep time */
#define KERN_OSRELDATE          26      /* int: OS release date */
#define KERN_NTP_PLL            27      /* node: NTP PLL control */
#define KERN_BOOTFILE           28      /* string: name of booted kernel */
#define KERN_MAXFILESPERPROC    29      /* int: max open files per proc */
#define KERN_MAXPROCPERUID      30      /* int: max processes per uid */
#define KERN_DUMPDEV            31      /* dev_t: device to dump on */
#define KERN_IPC                32      /* node: anything related to IPC */
#define KERN_DUMMY              33      /* unused */
#define KERN_PS_STRINGS 34      /* int: address of PS_STRINGS */
#define KERN_USRSTACK32 35      /* int: address of USRSTACK */
#define KERN_LOGSIGEXIT 36      /* int: do we log sigexit procs? */
#define KERN_SYMFILE            37      /* string: kernel symbol filename */
#define KERN_PROCARGS           38
/* 39 was KERN_PCSAMPLES... now obsolete */
#define KERN_NETBOOT            40      /* int: are we netbooted? 1=yes,0=no */
/* 41 was KERN_PANICINFO : panic UI information (deprecated) */
#define KERN_SYSV               42      /* node: System V IPC information */
#define KERN_AFFINITY           43      /* xxx */
#define KERN_TRANSLATE          44      /* xxx */
#define KERN_CLASSIC            KERN_TRANSLATE  /* XXX backwards compat */
#define KERN_EXEC               45      /* xxx */
#define KERN_CLASSICHANDLER     KERN_EXEC /* XXX backwards compatibility */
#define KERN_AIOMAX             46      /* int: max aio requests */
#define KERN_AIOPROCMAX         47      /* int: max aio requests per process */
#define KERN_AIOTHREADS         48      /* int: max aio worker threads */
#ifdef __APPLE_API_UNSTABLE
#define KERN_PROCARGS2          49
#endif /* __APPLE_API_UNSTABLE */
#define KERN_COREFILE           50      /* string: corefile format string */
#define KERN_COREDUMP           51      /* int: whether to coredump at all */
#define KERN_SUGID_COREDUMP     52      /* int: whether to dump SUGID cores */
#define KERN_PROCDELAYTERM      53      /* int: set/reset current proc for delayed termination during shutdown */
#define KERN_SHREG_PRIVATIZABLE 54      /* int: can shared regions be privatized ? */
/* 55 was KERN_PROC_LOW_PRI_IO... now deprecated */
#define KERN_LOW_PRI_WINDOW     56      /* int: set/reset throttle window - milliseconds */
#define KERN_LOW_PRI_DELAY      57      /* int: set/reset throttle delay - milliseconds */
#define KERN_POSIX              58      /* node: posix tunables */
#define KERN_USRSTACK64         59      /* LP64 user stack query */
#define KERN_NX_PROTECTION      60      /* int: whether no-execute protection is enabled */
#define KERN_TFP                61      /* Task for pid settings */
#define KERN_PROCNAME           62      /* setup process program  name(2*MAXCOMLEN) */
#define KERN_THALTSTACK         63      /* for compat with older x86 and does nothing */
#define KERN_SPECULATIVE_READS  64      /* int: whether speculative reads are disabled */
#define KERN_OSVERSION          65      /* for build number i.e. 9A127 */
#define KERN_SAFEBOOT           66      /* are we booted safe? */
/*	67 was KERN_LCTX (login context) */
#define KERN_RAGEVNODE          68
#define KERN_TTY                69      /* node: tty settings */
#define KERN_CHECKOPENEVT       70      /* spi: check the VOPENEVT flag on vnodes at open time */
#define KERN_THREADNAME         71      /* set/get thread name */
#define KERN_MAXID              72      /* number of valid kern ids */
/*
 * Don't add any more sysctls like this.  Instead, use the SYSCTL_*() macros
 * and OID_AUTO. This will have the added benefit of not having to recompile
 * sysctl(8) to pick up your changes.
 */

#if COUNT_SYSCALLS && defined(KERNEL)
#define KERN_COUNT_SYSCALLS (KERN_OSTYPE + 1000)        /* keep called count for each bsd syscall */
#endif

#if defined(__LP64__)
#define KERN_USRSTACK KERN_USRSTACK64
#else
#define KERN_USRSTACK KERN_USRSTACK32
#endif


/* KERN_RAGEVNODE types */
#define KERN_RAGE_PROC          1
#define KERN_RAGE_THREAD        2
#define KERN_UNRAGE_PROC        3
#define KERN_UNRAGE_THREAD      4

/* KERN_OPENEVT types */
#define KERN_OPENEVT_PROC     1
#define KERN_UNOPENEVT_PROC   2

/* KERN_TFP types */
#define KERN_TFP_POLICY                 1

/* KERN_TFP_POLICY values . All policies allow task port for self */
#define KERN_TFP_POLICY_DENY            0       /* Deny Mode: None allowed except privileged */
#define KERN_TFP_POLICY_DEFAULT         2       /* Default  Mode: related ones allowed and upcall authentication */

/* KERN_KDEBUG types */
#define KERN_KDEFLAGS         1
#define KERN_KDDFLAGS         2
#define KERN_KDENABLE         3
#define KERN_KDSETBUF         4
#define KERN_KDGETBUF         5
#define KERN_KDSETUP          6
#define KERN_KDREMOVE         7
#define KERN_KDSETREG         8
#define KERN_KDGETREG         9
#define KERN_KDREADTR         10
#define KERN_KDPIDTR          11
#define KERN_KDTHRMAP         12
/* Don't use 13 as it is overloaded with KERN_VNODE */
#define KERN_KDPIDEX          14
#define KERN_KDSETRTCDEC      15 /* obsolete */
#define KERN_KDGETENTROPY     16 /* obsolete */
#define KERN_KDWRITETR        17
#define KERN_KDWRITEMAP       18
#define KERN_KDTEST           19
/* 20 unused */
#define KERN_KDREADCURTHRMAP  21
#define KERN_KDSET_TYPEFILTER 22
#define KERN_KDBUFWAIT        23
#define KERN_KDCPUMAP         24
#define KERN_KDCPUMAP_EXT     25
#define KERN_KDSET_EDM        26
#define KERN_KDGET_EDM        27
#define KERN_KDWRITETR_V3     28

#define CTL_KERN_NAMES { \
	{ 0, 0 }, \
	{ "ostype", CTLTYPE_STRING }, \
	{ "osrelease", CTLTYPE_STRING }, \
	{ "osrevision", CTLTYPE_INT }, \
	{ "version", CTLTYPE_STRING }, \
	{ "maxvnodes", CTLTYPE_INT }, \
	{ "maxproc", CTLTYPE_INT }, \
	{ "maxfiles", CTLTYPE_INT }, \
	{ "argmax", CTLTYPE_INT }, \
	{ "securelevel", CTLTYPE_INT }, \
	{ "hostname", CTLTYPE_STRING }, \
	{ "hostid", CTLTYPE_INT }, \
	{ "clockrate", CTLTYPE_STRUCT }, \
	{ "vnode", CTLTYPE_STRUCT }, \
	{ "proc", CTLTYPE_STRUCT }, \
	{ "file", CTLTYPE_STRUCT }, \
	{ "profiling", CTLTYPE_NODE }, \
	{ "posix1version", CTLTYPE_INT }, \
	{ "ngroups", CTLTYPE_INT }, \
	{ "job_control", CTLTYPE_INT }, \
	{ "saved_ids", CTLTYPE_INT }, \
	{ "boottime", CTLTYPE_STRUCT }, \
	{ "nisdomainname", CTLTYPE_STRING }, \
	{ "maxpartitions", CTLTYPE_INT }, \
	{ "kdebug", CTLTYPE_INT }, \
	{ "update", CTLTYPE_INT }, \
	{ "osreldate", CTLTYPE_INT }, \
	{ "ntp_pll", CTLTYPE_NODE }, \
	{ "bootfile", CTLTYPE_STRING }, \
	{ "maxfilesperproc", CTLTYPE_INT }, \
	{ "maxprocperuid", CTLTYPE_INT }, \
	{ "dumpdev", CTLTYPE_STRUCT }, /* we lie; don't print as int */ \
	{ "ipc", CTLTYPE_NODE }, \
	{ "dummy", CTLTYPE_INT }, \
	{ "dummy", CTLTYPE_INT }, \
	{ "usrstack", CTLTYPE_INT }, \
	{ "logsigexit", CTLTYPE_INT }, \
	{ "symfile",CTLTYPE_STRING },\
	{ "procargs",CTLTYPE_STRUCT },\
	{ "dummy", CTLTYPE_INT },               /* deprecated pcsamples */ \
	{ "netboot", CTLTYPE_INT }, \
	{ "dummy", CTLTYPE_INT },               /* deprecated: panicinfo */ \
	{ "sysv", CTLTYPE_NODE }, \
	{ "dummy", CTLTYPE_INT }, \
	{ "dummy", CTLTYPE_INT }, \
	{ "exec", CTLTYPE_NODE }, \
	{ "aiomax", CTLTYPE_INT }, \
	{ "aioprocmax", CTLTYPE_INT }, \
	{ "aiothreads", CTLTYPE_INT }, \
	{ "procargs2",CTLTYPE_STRUCT }, \
	{ "corefile",CTLTYPE_STRING }, \
	{ "coredump", CTLTYPE_INT }, \
	{ "sugid_coredump", CTLTYPE_INT }, \
	{ "delayterm", CTLTYPE_INT }, \
	{ "shreg_private", CTLTYPE_INT }, \
	{ "proc_low_pri_io", CTLTYPE_INT }, \
	{ "low_pri_window", CTLTYPE_INT }, \
	{ "low_pri_delay", CTLTYPE_INT }, \
	{ "posix", CTLTYPE_NODE }, \
	{ "usrstack64", CTLTYPE_QUAD }, \
	{ "nx", CTLTYPE_INT }, \
	{ "tfp", CTLTYPE_NODE }, \
	{ "procname", CTLTYPE_STRING }, \
	{ "threadsigaltstack", CTLTYPE_INT }, \
	{ "speculative_reads_disabled", CTLTYPE_INT }, \
	{ "osversion", CTLTYPE_STRING }, \
	{ "safeboot", CTLTYPE_INT }, \
	{ "dummy", CTLTYPE_INT },               /* deprecated: lctx */ \
	{ "rage_vnode", CTLTYPE_INT }, \
	{ "tty", CTLTYPE_NODE },        \
	{ "check_openevt", CTLTYPE_INT }, \
	{ "thread_name", CTLTYPE_STRING } \
}

/*
 * CTL_VFS identifiers
 */
#define CTL_VFS_NAMES { \
	{ "vfsconf", CTLTYPE_STRUCT } \
}

/*
 * KERN_PROC subtypes
 */
#define KERN_PROC_ALL           0       /* everything */
#define KERN_PROC_PID           1       /* by process id */
#define KERN_PROC_PGRP          2       /* by process group id */
#define KERN_PROC_SESSION       3       /* by session of pid */
#define KERN_PROC_TTY           4       /* by controlling tty */
#define KERN_PROC_UID           5       /* by effective uid */
#define KERN_PROC_RUID          6       /* by real uid */
#define KERN_PROC_LCID          7       /* by login context id */

/*
 * KERN_VFSNSPACE subtypes
 */
#define KERN_VFSNSPACE_HANDLE_PROC              1
#define KERN_VFSNSPACE_UNHANDLE_PROC    2



/*
 * KERN_IPC identifiers
 */
#define KIPC_MAXSOCKBUF         1       /* int: max size of a socket buffer */
#define KIPC_SOCKBUF_WASTE      2       /* int: wastage factor in sockbuf */
#define KIPC_SOMAXCONN          3       /* int: max length of connection q */
#define KIPC_MAX_LINKHDR        4       /* int: max length of link header */
#define KIPC_MAX_PROTOHDR       5       /* int: max length of network header */
#define KIPC_MAX_HDR            6       /* int: max total length of headers */
#define KIPC_MAX_DATALEN        7       /* int: max length of data? */
#define KIPC_MBSTAT             8       /* struct: mbuf usage statistics */
#define KIPC_NMBCLUSTERS        9       /* int: maximum mbuf clusters */
#define KIPC_SOQLIMITCOMPAT     10      /* int: socket queue limit */

/*
 * CTL_VM identifiers
 */
#define VM_METER        1               /* struct vmmeter */
#define VM_LOADAVG      2               /* struct loadavg */
/*
 * Note: "3" was skipped sometime ago and should probably remain unused
 * to avoid any new entry from being accepted by older kernels...
 */
#define VM_MACHFACTOR   4               /* struct loadavg with mach factor*/
#define VM_SWAPUSAGE    5               /* total swap usage */
#define VM_MAXID        6               /* number of valid vm ids */

#define CTL_VM_NAMES { \
	{ 0, 0 }, \
	{ "vmmeter", CTLTYPE_STRUCT }, \
	{ "loadavg", CTLTYPE_STRUCT }, \
	{ 0, 0 }, /* placeholder for "3" (see comment above) */ \
	{ "dummy", CTLTYPE_INT }, \
	{ "swapusage", CTLTYPE_STRUCT } \
}

struct xsw_usage {
	u_int64_t       xsu_total;
	u_int64_t       xsu_avail;
	u_int64_t       xsu_used;
	u_int32_t       xsu_pagesize;
	boolean_t       xsu_encrypted;
};

#ifdef __APPLE_API_PRIVATE
/* Load average structure.  Use of fixpt_t assume <sys/types.h> in scope. */
/* XXX perhaps we should protect fixpt_t, and define it here (or discard it) */
struct loadavg {
	fixpt_t ldavg[3];
	long    fscale;
};
extern struct loadavg averunnable;
#define LSCALE  1000            /* scaling for "fixed point" arithmetic */

#endif /* __APPLE_API_PRIVATE */


/*
 * CTL_HW identifiers
 */
#define HW_MACHINE       1              /* string: machine class (deprecated: use HW_PRODUCT) */
#define HW_MODEL         2              /* string: specific machine model (deprecated: use HW_TARGET) */
#define HW_NCPU          3              /* int: number of cpus */
#define HW_BYTEORDER     4              /* int: machine byte order */
#define HW_PHYSMEM       5              /* int: total memory */
#define HW_USERMEM       6              /* int: non-kernel memory */
#define HW_PAGESIZE      7              /* int: software page size */
#define HW_DISKNAMES     8              /* strings: disk drive names */
#define HW_DISKSTATS     9              /* struct: diskstats[] */
#define HW_EPOCH        10              /* int: 0 for Legacy, else NewWorld */
#define HW_FLOATINGPT   11              /* int: has HW floating point? */
#define HW_MACHINE_ARCH 12              /* string: machine architecture */
#define HW_VECTORUNIT   13              /* int: has HW vector unit? */
#define HW_BUS_FREQ     14              /* int: Bus Frequency */
#define HW_CPU_FREQ     15              /* int: CPU Frequency */
#define HW_CACHELINE    16              /* int: Cache Line Size in Bytes */
#define HW_L1ICACHESIZE 17              /* int: L1 I Cache Size in Bytes */
#define HW_L1DCACHESIZE 18              /* int: L1 D Cache Size in Bytes */
#define HW_L2SETTINGS   19              /* int: L2 Cache Settings */
#define HW_L2CACHESIZE  20              /* int: L2 Cache Size in Bytes */
#define HW_L3SETTINGS   21              /* int: L3 Cache Settings */
#define HW_L3CACHESIZE  22              /* int: L3 Cache Size in Bytes */
#define HW_TB_FREQ      23              /* int: Bus Frequency */
#define HW_MEMSIZE      24              /* uint64_t: physical ram size */
#define HW_AVAILCPU     25              /* int: number of available CPUs */
#define HW_TARGET       26              /* string: model identifier */
#define HW_PRODUCT      27              /* string: product identifier */
#define HW_MAXID        28              /* number of valid hw ids */

#define CTL_HW_NAMES { \
	{ 0, 0 }, \
	{ "machine", CTLTYPE_STRING },          /* Deprecated: use hw.product */ \
	{ "model", CTLTYPE_STRING },            /* Deprecated: use hw.target */ \
	{ "ncpu", CTLTYPE_INT }, \
	{ "byteorder", CTLTYPE_INT }, \
	{ "physmem", CTLTYPE_INT }, \
	{ "usermem", CTLTYPE_INT }, \
	{ "pagesize", CTLTYPE_INT }, \
	{ "disknames", CTLTYPE_STRUCT }, \
	{ "diskstats", CTLTYPE_STRUCT }, \
	{ "epoch", CTLTYPE_INT }, \
	{ "floatingpoint", CTLTYPE_INT }, \
	{ "machinearch", CTLTYPE_STRING }, \
	{ "vectorunit", CTLTYPE_INT }, \
	{ "busfrequency", CTLTYPE_INT }, \
	{ "cpufrequency", CTLTYPE_INT }, \
	{ "cachelinesize", CTLTYPE_INT }, \
	{ "l1icachesize", CTLTYPE_INT }, \
	{ "l1dcachesize", CTLTYPE_INT }, \
	{ "l2settings", CTLTYPE_INT }, \
	{ "l2cachesize", CTLTYPE_INT }, \
	{ "l3settings", CTLTYPE_INT }, \
	{ "l3cachesize", CTLTYPE_INT }, \
	{ "tbfrequency", CTLTYPE_INT }, \
	{ "memsize", CTLTYPE_QUAD }, \
	{ "availcpu", CTLTYPE_INT }, \
	{ "target", CTLTYPE_STRING }, \
	{ "product", CTLTYPE_STRING }, \
}

/*
 * XXX This information should be moved to the man page.
 *
 * These are the support HW selectors for sysctlbyname.  Parameters that are byte counts or frequencies are 64 bit numbers.
 * All other parameters are 32 bit numbers.
 *
 *   hw.memsize                - The number of bytes of physical memory in the system.
 *
 *   hw.ncpu                   - The maximum number of processors that could be available this boot.
 *                               Use this value for sizing of static per processor arrays; i.e. processor load statistics.
 *
 *   hw.activecpu              - The number of processors currently available for executing threads.
 *                               Use this number to determine the number threads to create in SMP aware applications.
 *                               This number can change when power management modes are changed.
 *
 *   hw.physicalcpu            - The number of physical processors available in the current power management mode.
 *   hw.physicalcpu_max        - The maximum number of physical processors that could be available this boot
 *
 *   hw.logicalcpu             - The number of logical processors available in the current power management mode.
 *   hw.logicalcpu_max         - The maximum number of logical processors that could be available this boot
 *
 *   hw.tbfrequency            - This gives the time base frequency used by the OS and is the basis of all timing services.
 *                               In general is is better to use mach's or higher level timing services, but this value
 *                               is needed to convert the PPC Time Base registers to real time.
 *
 *   hw.cpufrequency           - These values provide the current, min and max cpu frequency.  The min and max are for
 *   hw.cpufrequency_max       - all power management modes.  The current frequency is the max frequency in the current mode.
 *   hw.cpufrequency_min       - All frequencies are in Hz.
 *
 *   hw.busfrequency           - These values provide the current, min and max bus frequency.  The min and max are for
 *   hw.busfrequency_max       - all power management modes.  The current frequency is the max frequency in the current mode.
 *   hw.busfrequency_min       - All frequencies are in Hz.
 *
 *   hw.cputype                - These values provide the mach-o cpu type and subtype.  A complete list is in <mach/machine.h>
 *   hw.cpusubtype             - These values should be used to determine what processor family the running cpu is from so that
 *                               the best binary can be chosen, or the best dynamic code generated.  They should not be used
 *                               to determine if a given processor feature is available.
 *   hw.cputhreadtype          - This value will be present if the processor supports threads.  Like hw.cpusubtype this selector
 *                               should not be used to infer features, and only used to name the processors thread architecture.
 *                               The values are defined in <mach/machine.h>
 *
 *   hw.byteorder              - Gives the byte order of the processor.  4321 for big endian, 1234 for little.
 *
 *   hw.pagesize               - Gives the size in bytes of the pages used by the processor and VM system.
 *
 *   hw.cachelinesize          - Gives the size in bytes of the processor's cache lines.
 *                               This value should be use to control the strides of loops that use cache control instructions
 *                               like dcbz, dcbt or dcbst.
 *
 *   hw.l1dcachesize           - These values provide the size in bytes of the L1, L2 and L3 caches.  If a cache is not present
 *   hw.l1icachesize           - then the selector will return and error.
 *   hw.l2cachesize            -
 *   hw.l3cachesize            -
 *
 *   hw.nperflevels            - Number of core types in the system. See the parameters below, which can be used to get
 *                             - information associated with a specific perf level.
 *
 *   The following parameters apply to perflevel N, where N is a number between 0 and the number of core types in the system minus one.
 *   perflevel 0 always refers to the highest performance core type in the system.
 *
 *   hw.perflevelN.physicalcpu      - The number of physical processors available in the current power management mode.
 *   hw.perflevelN.physicalcpumax   - The maximum number of physical processors that could be available this boot.
 *   hw.perflevelN.logicalcpu       - The number of logical processors available in the current power management mode.
 *   hw.perflevelN.logicalcpumax    - The maximum number of logical processors that could be available this boot.
 *
 *   hw.perflevelN.l1dcachesize     - These values provide the size in bytes of the L1, L2 and L3 caches.  If a cache is not present
 *   hw.perflevelN.l1icachesize     - then the selector will return and error.
 *   hw.perflevelN.l2cachesize      -
 *   hw.perflevelN.l3cachesize      -
 *
 *   hw.perflevelN.cpusperl2        - These values provide the number of CPUs of the same type that share L2 and L3 caches.
 *   hw.perflevelN.cpusperl3        - If a cache is not present then the selector will return and error.
 *
 *   hw.perflevelN.l2perflevels     - These values provide a bitmap, where bit  number of CPUs of the same type that share L2 and L3 caches.
 *   hw.perflevelN.l3perflevels     - If a cache is not present then the selector will return and error.
 *
 *   hw.packages               - Gives the number of processor packages.
 *
 * These are the selectors for optional processor features for specific processors.  Selectors that return errors are not support
 * on the system.  Supported features will return 1 if they are recommended or 0 if they are supported but are not expected to help .
 * performance.  Future versions of these selectors may return larger values as necessary so it is best to test for non zero.
 *
 * For PowerPC:
 *
 *   hw.optional.floatingpoint - Floating Point Instructions
 *   hw.optional.altivec       - AltiVec Instructions
 *   hw.optional.graphicsops   - Graphics Operations
 *   hw.optional.64bitops      - 64-bit Instructions
 *   hw.optional.fsqrt         - HW Floating Point Square Root Instruction
 *   hw.optional.stfiwx        - Store Floating Point as Integer Word Indexed Instructions
 *   hw.optional.dcba          - Data Cache Block Allocate Instruction
 *   hw.optional.datastreams   - Data Streams Instructions
 *   hw.optional.dcbtstreams   - Data Cache Block Touch Steams Instruction Form
 *
 * For x86 Architecture:
 *
 *   hw.optional.floatingpoint     - Floating Point Instructions
 *   hw.optional.mmx               - Original MMX vector instructions
 *   hw.optional.sse               - Streaming SIMD Extensions
 *   hw.optional.sse2              - Streaming SIMD Extensions 2
 *   hw.optional.sse3              - Streaming SIMD Extensions 3
 *   hw.optional.supplementalsse3  - Supplemental Streaming SIMD Extensions 3
 *   hw.optional.x86_64            - 64-bit support
 */


/*
 * CTL_USER definitions
 */
#define USER_CS_PATH             1      /* string: _CS_PATH */
#define USER_BC_BASE_MAX         2      /* int: BC_BASE_MAX */
#define USER_BC_DIM_MAX          3      /* int: BC_DIM_MAX */
#define USER_BC_SCALE_MAX        4      /* int: BC_SCALE_MAX */
#define USER_BC_STRING_MAX       5      /* int: BC_STRING_MAX */
#define USER_COLL_WEIGHTS_MAX    6      /* int: COLL_WEIGHTS_MAX */
#define USER_EXPR_NEST_MAX       7      /* int: EXPR_NEST_MAX */
#define USER_LINE_MAX            8      /* int: LINE_MAX */
#define USER_RE_DUP_MAX          9      /* int: RE_DUP_MAX */
#define USER_POSIX2_VERSION     10      /* int: POSIX2_VERSION */
#define USER_POSIX2_C_BIND      11      /* int: POSIX2_C_BIND */
#define USER_POSIX2_C_DEV       12      /* int: POSIX2_C_DEV */
#define USER_POSIX2_CHAR_TERM   13      /* int: POSIX2_CHAR_TERM */
#define USER_POSIX2_FORT_DEV    14      /* int: POSIX2_FORT_DEV */
#define USER_POSIX2_FORT_RUN    15      /* int: POSIX2_FORT_RUN */
#define USER_POSIX2_LOCALEDEF   16      /* int: POSIX2_LOCALEDEF */
#define USER_POSIX2_SW_DEV      17      /* int: POSIX2_SW_DEV */
#define USER_POSIX2_UPE         18      /* int: POSIX2_UPE */
#define USER_STREAM_MAX         19      /* int: POSIX2_STREAM_MAX */
#define USER_TZNAME_MAX         20      /* int: POSIX2_TZNAME_MAX */
#define USER_MAXID              21      /* number of valid user ids */

#define CTL_USER_NAMES { \
	{ 0, 0 }, \
	{ "cs_path", CTLTYPE_STRING }, \
	{ "bc_base_max", CTLTYPE_INT }, \
	{ "bc_dim_max", CTLTYPE_INT }, \
	{ "bc_scale_max", CTLTYPE_INT }, \
	{ "bc_string_max", CTLTYPE_INT }, \
	{ "coll_weights_max", CTLTYPE_INT }, \
	{ "expr_nest_max", CTLTYPE_INT }, \
	{ "line_max", CTLTYPE_INT }, \
	{ "re_dup_max", CTLTYPE_INT }, \
	{ "posix2_version", CTLTYPE_INT }, \
	{ "posix2_c_bind", CTLTYPE_INT }, \
	{ "posix2_c_dev", CTLTYPE_INT }, \
	{ "posix2_char_term", CTLTYPE_INT }, \
	{ "posix2_fort_dev", CTLTYPE_INT }, \
	{ "posix2_fort_run", CTLTYPE_INT }, \
	{ "posix2_localedef", CTLTYPE_INT }, \
	{ "posix2_sw_dev", CTLTYPE_INT }, \
	{ "posix2_upe", CTLTYPE_INT }, \
	{ "stream_max", CTLTYPE_INT }, \
	{ "tzname_max", CTLTYPE_INT } \
}



/*
 * CTL_DEBUG definitions
 *
 * Second level identifier specifies which debug variable.
 * Third level identifier specifies which stucture component.
 */
#define CTL_DEBUG_NAME          0       /* string: variable name */
#define CTL_DEBUG_VALUE         1       /* int: variable value */
#define CTL_DEBUG_MAXID         20


#if (CTL_MAXID != 9) || (KERN_MAXID != 72) || (VM_MAXID != 6) || (HW_MAXID != 28) || (USER_MAXID != 21) || (CTL_DEBUG_MAXID != 20)
#error Use the SYSCTL_*() macros and OID_AUTO instead!
#endif





#endif /* SYSCTL_DEF_ENABLED */


#endif  /* !_SYS_SYSCTL_H_ */
