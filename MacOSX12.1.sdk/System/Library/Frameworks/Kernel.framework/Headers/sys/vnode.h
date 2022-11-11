/*
 * Copyright (c) 2000-2017 Apple Inc. All rights reserved.
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
 *	@(#)vnode.h	8.17 (Berkeley) 5/20/95
 */

#ifndef _VNODE_H_
#define _VNODE_H_

#include <stdint.h>
#include <sys/appleapiopts.h>
#include <sys/cdefs.h>
#include <sys/kernel_types.h>
#include <sys/param.h>
#include <sys/signal.h>

/*
 * The vnode is the focus of all file activity in UNIX.  There is a
 * unique vnode allocated for each active file, each current directory,
 * each mounted-on file, text file, and the root.
 */

/*
 * Vnode types.  VNON means no type.
 */
enum vtype      {
	/* 0 */
	VNON,
	/* 1 - 5 */
	VREG, VDIR, VBLK, VCHR, VLNK,
	/* 6 - 10 */
	VSOCK, VFIFO, VBAD, VSTR, VCPLX
};

/*
 * Vnode tag types.
 * These are for the benefit of external programs only (e.g., pstat)
 * and should NEVER be inspected by the kernel.
 */
enum vtagtype   {
	/* 0 */
	VT_NON,
	/* 1 reserved, overlaps with (CTL_VFS, VFS_NUMMNTOPS) */
	VT_UFS,
	/* 2 - 5 */
	VT_NFS, VT_MFS, VT_MSDOSFS, VT_LFS,
	/* 6 - 10 */
	VT_LOFS, VT_FDESC, VT_PORTAL, VT_NULL, VT_UMAP,
	/* 11 - 15 */
	VT_KERNFS, VT_PROCFS, VT_AFS, VT_ISOFS, VT_MOCKFS,
	/* 16 - 20 */
	VT_HFS, VT_ZFS, VT_DEVFS, VT_WEBDAV, VT_UDF,
	/* 21 - 25 */
	VT_AFP, VT_CDDA, VT_CIFS, VT_OTHER, VT_APFS,
	/* 26 - 27*/
	VT_LOCKERFS, VT_BINDFS,
};

#define HAVE_VT_LOCKERFS 1

/*
 * flags for VNOP_BLOCKMAP
 */
#define VNODE_READ      0x01
#define VNODE_WRITE     0x02
#define VNODE_BLOCKMAP_NO_TRACK 0x04 // APFS Fusion: Do not track this request
#define VNODE_CLUSTER_VERIFY 0x08 // Verification will be performed in the cluster layer


/* flags for VNOP_ALLOCATE */
#define PREALLOCATE             0x00000001      /* preallocate allocation blocks */
#define ALLOCATECONTIG  0x00000002      /* allocate contigious space */
#define ALLOCATEALL             0x00000004      /* allocate all requested space */
/* or no space at all */
#define FREEREMAINDER   0x00000008      /* deallocate allocated but */
/* unfilled blocks */
#define ALLOCATEFROMPEOF        0x00000010      /* allocate from the physical eof */
#define ALLOCATEFROMVOL         0x00000020      /* allocate from the volume offset */

/*
 * Token indicating no attribute value yet assigned. some user source uses this
 */
#define VNOVAL  (-1)



/*
 * Flags for ioflag.
 */
#define IO_UNIT         0x0001          /* do I/O as atomic unit */
#define IO_APPEND       0x0002          /* append write to end */
#define IO_SYNC         0x0004          /* do I/O synchronously */
#define IO_NODELOCKED   0x0008          /* underlying node already locked */
#define IO_NDELAY       0x0010          /* FNDELAY flag set in file table */
#define IO_NOZEROFILL   0x0020          /* F_SETSIZE fcntl uses to prevent zero filling */
#define IO_TAILZEROFILL 0x0040          /* zero fills at the tail of write */
#define IO_HEADZEROFILL 0x0080          /* zero fills at the head of write */
#define IO_NOZEROVALID  0x0100          /* do not zero fill if valid page */
#define IO_NOZERODIRTY  0x0200          /* do not zero fill if page is dirty */
#define IO_CLOSE        0x0400          /* I/O issued from close path */
#define IO_NOCACHE      0x0800          /* same effect as VNOCACHE_DATA, but only for this 1 I/O */
#define IO_RAOFF        0x1000          /* same effect as VRAOFF, but only for this 1 I/O */
#define IO_DEFWRITE     0x2000          /* defer write if vfs.defwrite is set */
#define IO_PASSIVE      0x4000          /* this I/O is marked as background I/O so it won't throttle Throttleable I/O */
#define IO_BACKGROUND IO_PASSIVE /* used for backward compatibility.  to be removed after IO_BACKGROUND is no longer
	                          * used by DiskImages in-kernel mode */
#define IO_NOAUTH       0x8000          /* No authorization checks. */
#define IO_NODIRECT     0x10000         /* don't use direct synchronous writes if IO_NOCACHE is specified */
#define IO_ENCRYPTED    0x20000         /* Retrieve encrypted blocks from the filesystem */
#define IO_RETURN_ON_THROTTLE   0x40000
#define IO_SINGLE_WRITER        0x80000
#define IO_SYSCALL_DISPATCH             0x100000        /* I/O was originated from a file table syscall */
#define IO_SWAP_DISPATCH                0x200000        /* I/O was originated from the swap layer */
#define IO_SKIP_ENCRYPTION              0x400000        /* Skips en(de)cryption on the IO. Must be initiated from kernel */
#define IO_EVTONLY                      0x800000        /* the i/o is being done on an fd that's marked O_EVTONLY */

/*
 * Component Name: this structure describes the pathname
 * information that is passed through the VNOP interface.
 */
struct componentname {
	/*
	 * Arguments to lookup.
	 */
	uint32_t        cn_nameiop;     /* lookup operation */
	uint32_t        cn_flags;       /* flags (see below) */
	void * cn_reserved1;    /* use vfs_context_t */
	void * cn_reserved2;    /* use vfs_context_t */
	/*
	 * Shared between lookup and commit routines.
	 */
	char    *cn_pnbuf;      /* pathname buffer */
	int     cn_pnlen;       /* length of allocated buffer */
	char    *cn_nameptr;    /* pointer to looked up name */
	int     cn_namelen;     /* length of looked up component */
	uint32_t        cn_hash;        /* hash value of looked up name */
	uint32_t        cn_consume;     /* chars to consume in lookup() */
};

/*
 * component name operations (for VNOP_LOOKUP)
 */
#define LOOKUP          0       /* perform name lookup only */
#define CREATE          1       /* setup for file creation */
#define DELETE          2       /* setup for file deletion */
#define RENAME          3       /* setup for file renaming */
#define OPMASK          3       /* mask for operation */

/*
 * component name operational modifier flags
 */
#define FOLLOW          0x00000040 /* follow symbolic links */

/*
 * component name parameter descriptors.
 */
#define ISDOTDOT        0x00002000 /* current component name is .. */
#define MAKEENTRY       0x00004000 /* entry is to be added to name cache */
#define ISLASTCN        0x00008000 /* this is last component of pathname */

/* The following structure specifies a vnode for creation */
struct vnode_fsparam {
	struct mount * vnfs_mp;         /* mount point to which this vnode_t is part of */
	enum vtype      vnfs_vtype;             /* vnode type */
	const char * vnfs_str;          /* File system Debug aid */
	struct vnode * vnfs_dvp;                        /* The parent vnode */
	void * vnfs_fsnode;                     /* inode */
	int(**vnfs_vops)(void *);               /* vnode dispatch table */
	int vnfs_markroot;                      /* is this a root vnode in FS (not a system wide one) */
	int vnfs_marksystem;            /* is  a system vnode */
	dev_t vnfs_rdev;                        /* dev_t  for block or char vnodes */
	off_t vnfs_filesize;            /* that way no need for getattr in UBC */
	struct componentname * vnfs_cnp; /* component name to add to namecache */
	uint32_t vnfs_flags;            /* flags */
};

#define VNFS_NOCACHE    0x01    /* do not add to name cache at this time */
#define VNFS_CANTCACHE  0x02    /* never add this instance to the name cache */
#define VNFS_ADDFSREF   0x04    /* take fs (named) reference */

#define VNCREATE_FLAVOR 0
#define VCREATESIZE sizeof(struct vnode_fsparam)




/*
 * Vnode attributes, new-style.
 *
 * The vnode_attr structure is used to transact attribute changes and queries
 * with the filesystem.
 *
 * Note that this structure may be extended, but existing fields must not move.
 */

#define VATTR_INIT(v)                   do {(v)->va_supported = (v)->va_active = 0ll; (v)->va_vaflags = 0; } while(0)
#define VATTR_SET_ACTIVE(v, a)          ((v)->va_active |= VNODE_ATTR_ ## a)
#define VATTR_SET_SUPPORTED(v, a)       ((v)->va_supported |= VNODE_ATTR_ ## a)
#define VATTR_IS_SUPPORTED(v, a)        ((v)->va_supported & VNODE_ATTR_ ## a)
#define VATTR_CLEAR_ACTIVE(v, a)        ((v)->va_active &= ~VNODE_ATTR_ ## a)
#define VATTR_CLEAR_SUPPORTED(v, a)     ((v)->va_supported &= ~VNODE_ATTR_ ## a)
#define VATTR_CLEAR_SUPPORTED_ALL(v)    ((v)->va_supported = 0)
#define VATTR_IS_ACTIVE(v, a)           ((v)->va_active & VNODE_ATTR_ ## a)
#define VATTR_ALL_SUPPORTED(v)          (((v)->va_active & (v)->va_supported) == (v)->va_active)
#define VATTR_INACTIVE_SUPPORTED(v)     do {(v)->va_active &= ~(v)->va_supported; (v)->va_supported = 0;} while(0)
#define VATTR_SET(v, a, x)              do { (v)-> a = (x); VATTR_SET_ACTIVE(v, a);} while(0)
#define VATTR_WANTED(v, a)              VATTR_SET_ACTIVE(v, a)
#define VATTR_RETURN(v, a, x)           do { (v)-> a = (x); VATTR_SET_SUPPORTED(v, a);} while(0)
#define VATTR_NOT_RETURNED(v, a)        (VATTR_IS_ACTIVE(v, a) && !VATTR_IS_SUPPORTED(v, a))

/*
 * Two macros to simplify conditional checking in kernel code.
 */
#define VATTR_IS(v, a, x)               (VATTR_IS_SUPPORTED(v, a) && (v)-> a == (x))
#define VATTR_IS_NOT(v, a, x)           (VATTR_IS_SUPPORTED(v, a) && (v)-> a != (x))

#define VNODE_ATTR_va_rdev              (1LL<< 0)       /* 00000001 */
#define VNODE_ATTR_va_nlink             (1LL<< 1)       /* 00000002 */
#define VNODE_ATTR_va_total_size        (1LL<< 2)       /* 00000004 */
#define VNODE_ATTR_va_total_alloc       (1LL<< 3)       /* 00000008 */
#define VNODE_ATTR_va_data_size         (1LL<< 4)       /* 00000010 */
#define VNODE_ATTR_va_data_alloc        (1LL<< 5)       /* 00000020 */
#define VNODE_ATTR_va_iosize            (1LL<< 6)       /* 00000040 */
#define VNODE_ATTR_va_uid               (1LL<< 7)       /* 00000080 */
#define VNODE_ATTR_va_gid               (1LL<< 8)       /* 00000100 */
#define VNODE_ATTR_va_mode              (1LL<< 9)       /* 00000200 */
#define VNODE_ATTR_va_flags             (1LL<<10)       /* 00000400 */
#define VNODE_ATTR_va_acl               (1LL<<11)       /* 00000800 */
#define VNODE_ATTR_va_create_time       (1LL<<12)       /* 00001000 */
#define VNODE_ATTR_va_access_time       (1LL<<13)       /* 00002000 */
#define VNODE_ATTR_va_modify_time       (1LL<<14)       /* 00004000 */
#define VNODE_ATTR_va_change_time       (1LL<<15)       /* 00008000 */
#define VNODE_ATTR_va_backup_time       (1LL<<16)       /* 00010000 */
#define VNODE_ATTR_va_fileid            (1LL<<17)       /* 00020000 */
#define VNODE_ATTR_va_linkid            (1LL<<18)       /* 00040000 */
#define VNODE_ATTR_va_parentid          (1LL<<19)       /* 00080000 */
#define VNODE_ATTR_va_fsid              (1LL<<20)       /* 00100000 */
#define VNODE_ATTR_va_filerev           (1LL<<21)       /* 00200000 */
#define VNODE_ATTR_va_gen               (1LL<<22)       /* 00400000 */
#define VNODE_ATTR_va_encoding          (1LL<<23)       /* 00800000 */
#define VNODE_ATTR_va_type              (1LL<<24)       /* 01000000 */
#define VNODE_ATTR_va_name              (1LL<<25)       /* 02000000 */
#define VNODE_ATTR_va_uuuid             (1LL<<26)       /* 04000000 */
#define VNODE_ATTR_va_guuid             (1LL<<27)       /* 08000000 */
#define VNODE_ATTR_va_nchildren         (1LL<<28)       /* 10000000 */
#define VNODE_ATTR_va_dirlinkcount      (1LL<<29)       /* 20000000 */
#define VNODE_ATTR_va_addedtime         (1LL<<30)       /* 40000000 */
#define VNODE_ATTR_va_dataprotect_class (1LL<<31)       /* 80000000 */
#define VNODE_ATTR_va_dataprotect_flags (1LL<<32)       /* 100000000 */
#define VNODE_ATTR_va_document_id       (1LL<<33)       /* 200000000 */
#define VNODE_ATTR_va_devid             (1LL<<34)       /* 400000000 */
#define VNODE_ATTR_va_objtype           (1LL<<35)       /* 800000000 */
#define VNODE_ATTR_va_objtag            (1LL<<36)       /* 1000000000 */
#define VNODE_ATTR_va_user_access       (1LL<<37)       /* 2000000000 */
#define VNODE_ATTR_va_finderinfo        (1LL<<38)       /* 4000000000 */
#define VNODE_ATTR_va_rsrc_length       (1LL<<39)       /* 8000000000 */
#define VNODE_ATTR_va_rsrc_alloc        (1LL<<40)       /* 10000000000 */
#define VNODE_ATTR_va_fsid64            (1LL<<41)       /* 20000000000 */
#define VNODE_ATTR_va_write_gencount    (1LL<<42)       /* 40000000000 */
#define VNODE_ATTR_va_private_size      (1LL<<43)       /* 80000000000 */
#define VNODE_ATTR_va_clone_id          (1LL<<44)       /* 100000000000 */
#define VNODE_ATTR_va_extflags          (1LL<<45)       /* 200000000000 */
#define VNODE_ATTR_va_recursive_gencount (1LL<<46)      /* 400000000000 */

#define VNODE_ATTR_BIT(n)       (VNODE_ATTR_ ## n)

/*
 * ALL of the attributes.
 */
#define VNODE_ATTR_ALL          (VNODE_ATTR_BIT(va_rdev) |              \
	                        VNODE_ATTR_BIT(va_nlink) |              \
	                        VNODE_ATTR_BIT(va_total_size) |         \
	                        VNODE_ATTR_BIT(va_total_alloc) |        \
	                        VNODE_ATTR_BIT(va_data_size) |          \
	                        VNODE_ATTR_BIT(va_data_alloc) |         \
	                        VNODE_ATTR_BIT(va_iosize) |             \
	                        VNODE_ATTR_BIT(va_uid) |                \
	                        VNODE_ATTR_BIT(va_gid) |                \
	                        VNODE_ATTR_BIT(va_mode) |               \
	                        VNODE_ATTR_BIT(va_flags) |              \
	                        VNODE_ATTR_BIT(va_acl) |                \
	                        VNODE_ATTR_BIT(va_create_time) |        \
	                        VNODE_ATTR_BIT(va_access_time) |        \
	                        VNODE_ATTR_BIT(va_modify_time) |        \
	                        VNODE_ATTR_BIT(va_change_time) |        \
	                        VNODE_ATTR_BIT(va_backup_time) |        \
	                        VNODE_ATTR_BIT(va_fileid) |             \
	                        VNODE_ATTR_BIT(va_linkid) |             \
	                        VNODE_ATTR_BIT(va_parentid) |           \
	                        VNODE_ATTR_BIT(va_fsid) |               \
	                        VNODE_ATTR_BIT(va_filerev) |            \
	                        VNODE_ATTR_BIT(va_gen) |                \
	                        VNODE_ATTR_BIT(va_encoding) |           \
	                        VNODE_ATTR_BIT(va_type) |               \
	                        VNODE_ATTR_BIT(va_name) |               \
	                        VNODE_ATTR_BIT(va_uuuid) |              \
	                        VNODE_ATTR_BIT(va_guuid) |              \
	                        VNODE_ATTR_BIT(va_nchildren) |          \
	                        VNODE_ATTR_BIT(va_dirlinkcount) |       \
	                        VNODE_ATTR_BIT(va_addedtime) |          \
	                        VNODE_ATTR_BIT(va_dataprotect_class) |  \
	                        VNODE_ATTR_BIT(va_dataprotect_flags) |  \
	                        VNODE_ATTR_BIT(va_document_id) |        \
	                        VNODE_ATTR_BIT(va_devid) |              \
	                        VNODE_ATTR_BIT(va_objtype) |            \
	                        VNODE_ATTR_BIT(va_objtag) |             \
	                        VNODE_ATTR_BIT(va_user_access) |        \
	                        VNODE_ATTR_BIT(va_finderinfo) |         \
	                        VNODE_ATTR_BIT(va_rsrc_length) |        \
	                        VNODE_ATTR_BIT(va_rsrc_alloc) |         \
	                        VNODE_ATTR_BIT(va_fsid64) |             \
	                        VNODE_ATTR_BIT(va_write_gencount) |     \
	                        VNODE_ATTR_BIT(va_private_size) |       \
	                        VNODE_ATTR_BIT(va_clone_id) |           \
	                        VNODE_ATTR_BIT(va_extflags) |           \
	                        VNODE_ATTR_BIT(va_recursive_gencount))

/*
 * Read-only attributes.
 */
#define VNODE_ATTR_RDONLY       (VNODE_ATTR_BIT(va_rdev) |              \
	                        VNODE_ATTR_BIT(va_nlink) |              \
	                        VNODE_ATTR_BIT(va_total_size) |         \
	                        VNODE_ATTR_BIT(va_total_alloc) |        \
	                        VNODE_ATTR_BIT(va_data_alloc) |         \
	                        VNODE_ATTR_BIT(va_iosize) |             \
	                        VNODE_ATTR_BIT(va_fileid) |             \
	                        VNODE_ATTR_BIT(va_linkid) |             \
	                        VNODE_ATTR_BIT(va_parentid) |           \
	                        VNODE_ATTR_BIT(va_fsid) |               \
	                        VNODE_ATTR_BIT(va_filerev) |            \
	                        VNODE_ATTR_BIT(va_gen) |                \
	                        VNODE_ATTR_BIT(va_name) |               \
	                        VNODE_ATTR_BIT(va_type) |               \
	                        VNODE_ATTR_BIT(va_nchildren) |          \
	                        VNODE_ATTR_BIT(va_dirlinkcount) |       \
	                        VNODE_ATTR_BIT(va_devid) |              \
	                        VNODE_ATTR_BIT(va_objtype) |            \
	                        VNODE_ATTR_BIT(va_objtag) |             \
	                        VNODE_ATTR_BIT(va_user_access) |        \
	                        VNODE_ATTR_BIT(va_finderinfo) |         \
	                        VNODE_ATTR_BIT(va_rsrc_length) |        \
	                        VNODE_ATTR_BIT(va_rsrc_alloc) |         \
	                        VNODE_ATTR_BIT(va_fsid64) |             \
	                        VNODE_ATTR_BIT(va_write_gencount) |     \
	                        VNODE_ATTR_BIT(va_private_size) |       \
	                        VNODE_ATTR_BIT(va_clone_id) |           \
	                        VNODE_ATTR_BIT(va_extflags) |           \
	                        VNODE_ATTR_BIT(va_recursive_gencount))

/*
 * Attributes that can be applied to a new file object.
 */
#define VNODE_ATTR_NEWOBJ       (VNODE_ATTR_BIT(va_rdev) |              \
	                        VNODE_ATTR_BIT(va_uid)	|               \
	                        VNODE_ATTR_BIT(va_gid) |                \
	                        VNODE_ATTR_BIT(va_mode) |               \
	                        VNODE_ATTR_BIT(va_flags) |              \
	                        VNODE_ATTR_BIT(va_acl) |                \
	                        VNODE_ATTR_BIT(va_create_time) |        \
	                        VNODE_ATTR_BIT(va_modify_time) |        \
	                        VNODE_ATTR_BIT(va_change_time) |        \
	                        VNODE_ATTR_BIT(va_encoding) |           \
	                        VNODE_ATTR_BIT(va_type) |               \
	                        VNODE_ATTR_BIT(va_uuuid) |              \
	                        VNODE_ATTR_BIT(va_guuid) |              \
	                        VNODE_ATTR_BIT(va_dataprotect_class) |  \
	                        VNODE_ATTR_BIT(va_dataprotect_flags) |  \
	                        VNODE_ATTR_BIT(va_document_id))

#include <sys/_types/_fsid_t.h>

struct vnode_attr {
	/* bitfields */
	uint64_t        va_supported;
	uint64_t        va_active;

	/*
	 * Control flags.  The low 16 bits are reserved for the
	 * ioflags being passed for truncation operations.
	 */
	int             va_vaflags;

	/* traditional stat(2) parameter fields */
	dev_t           va_rdev;        /* device id (device nodes only) */
	uint64_t        va_nlink;       /* number of references to this file */
	uint64_t        va_total_size;  /* size in bytes of all forks */
	uint64_t        va_total_alloc; /* disk space used by all forks */
	uint64_t        va_data_size;   /* size in bytes of the fork managed by current vnode */
	uint64_t        va_data_alloc;  /* disk space used by the fork managed by current vnode */
	uint32_t        va_iosize;      /* optimal I/O blocksize */

	/* file security information */
	uid_t           va_uid;         /* owner UID */
	gid_t           va_gid;         /* owner GID */
	mode_t          va_mode;        /* posix permissions */
	uint32_t        va_flags;       /* file flags */
	struct kauth_acl *va_acl;       /* access control list */

	/* timestamps */
	struct timespec va_create_time; /* time of creation */
	struct timespec va_access_time; /* time of last access */
	struct timespec va_modify_time; /* time of last data modification */
	struct timespec va_change_time; /* time of last metadata change */
	struct timespec va_backup_time; /* time of last backup */

	/* file parameters */
	uint64_t        va_fileid;      /* file unique ID in filesystem */
	uint64_t        va_linkid;      /* file link unique ID */
	uint64_t        va_parentid;    /* parent ID */
	uint32_t        va_fsid;        /* filesystem ID */
	uint64_t        va_filerev;     /* file revision counter */	/* XXX */
	uint32_t        va_gen;         /* file generation count */	/* XXX - relationship of
	                                 * these two? */
	/* misc parameters */
	uint32_t        va_encoding;    /* filename encoding script */

	enum vtype      va_type;        /* file type */
	char *          va_name;        /* Name for ATTR_CMN_NAME; MAXPATHLEN bytes */
	guid_t          va_uuuid;       /* file owner UUID */
	guid_t          va_guuid;       /* file group UUID */

	/* Meaningful for directories only */
	uint64_t        va_nchildren;     /* Number of items in a directory */
	uint64_t        va_dirlinkcount;  /* Real references to dir (i.e. excluding "." and ".." refs) */

	void *          va_reserved1;
	struct timespec va_addedtime;   /* timestamp when item was added to parent directory */

	/* Data Protection fields */
	uint32_t va_dataprotect_class;  /* class specified for this file if it didn't exist */
	uint32_t va_dataprotect_flags;  /* flags from NP open(2) to the filesystem */

	/* Document revision tracking */
	uint32_t va_document_id;

	/* Fields for Bulk args */
	uint32_t        va_devid;       /* devid of filesystem */
	uint32_t        va_objtype;     /* type of object */
	uint32_t        va_objtag;      /* vnode tag of filesystem */
	uint32_t        va_user_access; /* access for user */
	uint8_t         va_finderinfo[32];      /* Finder Info */
	uint64_t        va_rsrc_length; /* Resource Fork length */
	uint64_t        va_rsrc_alloc;  /* Resource Fork allocation size */
	fsid_t          va_fsid64;      /* fsid, of the correct type  */

	uint32_t va_write_gencount;     /* counter that increments each time the file changes */

	uint64_t va_private_size; /* If the file were deleted, how many bytes would be freed immediately */
	uint64_t va_clone_id;     /* If a file is cloned this is a unique id shared by all "perfect" clones */
	uint64_t va_extflags;     /* extended file/directory flags */
	uint64_t va_recursive_gencount; /* for dir-stats enabled directories */

	/* add new fields here only */
};


/*
 * Flags for va_vaflags.
 */
#define VA_UTIMES_NULL          0x010000        /* utimes argument was NULL */
#define VA_EXCLUSIVE            0x020000        /* exclusive create request */
#define VA_NOINHERIT            0x040000        /* Don't inherit ACLs from parent */
#define VA_NOAUTH               0x080000
#define VA_64BITOBJIDS          0x100000        /* fileid/linkid/parentid are 64 bit */
#define VA_REALFSID             0x200000        /* Return real fsid */
#define VA_USEFSID              0x400000        /* Use fsid from filesystem  */
#define VA_FILESEC_ACL          0x800000        /* ACL is interior to filesec */

/*
 *  Modes.  Some values same as Ixxx entries from inode.h for now.
 */
#define VSUID   0x800 /*04000*/	/* set user id on execution */
#define VSGID   0x400 /*02000*/	/* set group id on execution */
#define VSVTX   0x200 /*01000*/	/* save swapped text even after use */
#define VREAD   0x100 /*00400*/	/* read, write, execute permissions */
#define VWRITE  0x080 /*00200*/
#define VEXEC   0x040 /*00100*/

/*
 * Convert between vnode types and inode formats (since POSIX.1
 * defines mode word of stat structure in terms of inode formats).
 */
extern enum vtype       iftovt_tab[];
extern int              vttoif_tab[];
#define IFTOVT(mode)    (iftovt_tab[((mode) & S_IFMT) >> 12])
#define VTTOIF(indx)    (vttoif_tab[(int)(indx)])
#define MAKEIMODE(indx, mode)   (int)(VTTOIF(indx) | (mode))

/*
 * Flags to various vnode functions.
 */
#define SKIPSYSTEM      0x0001          /* vflush: skip vnodes marked VSYSTEM */
#define FORCECLOSE      0x0002          /* vflush: force file closeure */
#define WRITECLOSE      0x0004          /* vflush: only close writeable files */
#define SKIPSWAP        0x0008          /* vflush: skip vnodes marked VSWAP */
#define SKIPROOT        0x0010          /* vflush: skip root vnodes marked VROOT */

#define DOCLOSE         0x0008          /* vclean: close active files */

#define V_SAVE          0x0001          /* vinvalbuf: sync file first */
#define V_SAVEMETA      0x0002          /* vinvalbuf: leave indirect blocks */

#define REVOKEALL       0x0001          /* vnop_revoke: revoke all aliases */

/* VNOP_REMOVE/unlink flags */
#define VNODE_REMOVE_NODELETEBUSY                       0x0001 /* Don't delete busy files (Carbon) */
#define VNODE_REMOVE_SKIP_NAMESPACE_EVENT       0x0002 /* Do not upcall to userland handlers */
#define VNODE_REMOVE_NO_AUDIT_PATH              0x0004 /* Do not audit the path */
#define VNODE_REMOVE_DATALESS_DIR               0x0008 /* Special handling for removing a dataless directory without materialization */

/* VNOP_READDIR flags: */
#define VNODE_READDIR_EXTENDED    0x0001   /* use extended directory entries */
#define VNODE_READDIR_REQSEEKOFF  0x0002   /* requires seek offset (cookies) */
#define VNODE_READDIR_SEEKOFF32   0x0004   /* seek offset values should fit in 32 bits */
#define VNODE_READDIR_NAMEMAX     0x0008   /* For extended readdir, try to limit names to NAME_MAX bytes */

/* VNOP_CLONEFILE flags: */
#define VNODE_CLONEFILE_DEFAULT       0x0000
#define VNODE_CLONEFILE_NOOWNERCOPY   0x0001 /* Don't copy ownership information */


#define NULLVP  ((struct vnode *)NULL)

struct vnodeop_desc;

extern  int desiredvnodes;              /* number of vnodes desired */


/*
 * This structure is used to configure the new vnodeops vector.
 */
struct vnodeopv_entry_desc {
	struct vnodeop_desc *opve_op;   /* which operation this is */
	int (*opve_impl)(void *);               /* code implementing this operation */
};
struct vnodeopv_desc {
	/* ptr to the ptr to the vector where op should go */
	int(***opv_desc_vector_p)(void *);
	const struct vnodeopv_entry_desc *opv_desc_ops;   /* null terminated list */
};

/*!
 *  @function vn_default_error
 *  @abstract Default vnode operation to fill unsupported slots in vnode operation vectors.
 *  @return ENOTSUP
 */
int vn_default_error(void);

/*
 * A generic structure.
 * This can be used by bypass routines to identify generic arguments.
 */
struct vnop_generic_args {
	struct vnodeop_desc *a_desc;
	/* other random data follows, presumably */
};

#include <sys/vnode_if.h>

__BEGIN_DECLS

/*!
 *  @function vnode_create
 *  @abstract Create and initialize a vnode.
 *  @discussion Returns wth an iocount held on the vnode which must eventually be dropped with vnode_put().
 *  @param flavor Should be VNCREATE_FLAVOR.
 *  @param size  Size of the struct vnode_fsparam in "data".
 *  @param data  Pointer to a struct vnode_fsparam containing initialization information.
 *  @param vpp  Pointer to a vnode pointer, to be filled in with newly created vnode.
 *  @return 0 for success, error code otherwise.
 */
errno_t vnode_create(uint32_t flavor, uint32_t size, void  *data, vnode_t *vpp);


/*!
 *  @function vnode_addfsref
 *  @abstract Mark a vnode as being stored in a filesystem hash.
 *  @discussion Should only be called once on a vnode, and never if that vnode was created with VNFS_ADDFSREF.
 *  There should be a corresponding call to vnode_removefsref() when the vnode is reclaimed; VFS assumes that a
 *  n unused vnode will not be marked as referenced by a filesystem.
 *  @param vp The vnode to mark.
 *  @return Always 0.
 */
int     vnode_addfsref(vnode_t vp);

/*!
 *  @function vnode_removefsref
 *  @abstract Mark a vnode as no longer being stored in a filesystem hash.
 *  @discussion Should only be called once on a vnode (during a reclaim), and only after the vnode has either been created with VNFS_ADDFSREF or marked by vnode_addfsref().
 *  @param vp The vnode to unmark.
 *  @return Always 0.
 */
int     vnode_removefsref(vnode_t vp);

/*!
 *  @function vnode_hasdirtyblks
 *  @abstract Check if a vnode has dirty data waiting to be written to disk.
 *  @discussion Note that this routine is unsynchronized; it is only a snapshot and its result may cease to be true at the moment it is returned..
 *  @param vp The vnode to test.
 *  @return Nonzero if there are dirty blocks, 0 otherwise
 */
int     vnode_hasdirtyblks(vnode_t vp);

/*!
 *  @function vnode_hascleanblks
 *  @abstract Check if a vnode has clean buffers associated with it.
 *  @discussion Note that this routine is unsynchronized; it is only a snapshot and its result may cease to be true at the moment it is returned..
 *  @param vp The vnode to test.
 *  @return Nonzero if there are clean blocks, 0 otherwise.
 */
int     vnode_hascleanblks(vnode_t vp);

#define VNODE_ASYNC_THROTTLE    15
/*!
 *  @function vnode_waitforwrites
 *  @abstract Wait for the number of pending writes on a vnode to drop below a target.
 *  @param vp The vnode to monitor.
 *  @param output_target Max pending write count with which to return.
 *  @param slpflag Flags for msleep().
 *  @param slptimeout Frequency with which to force a check for completion; increments of 10 ms.
 *  @param msg String to pass  msleep() .
 *  @return 0 for success, or an error value from msleep().
 */
int     vnode_waitforwrites(vnode_t vp, int output_target, int slpflag, int slptimeout, const char *msg);

/*!
 *  @function vnode_startwrite
 *  @abstract Increment the count of pending writes on a vnode.
 *  @param vp The vnode whose count to increment.
 */
void    vnode_startwrite(vnode_t vp);

/*!
 *  @function vnode_startwrite
 *  @abstract Decrement the count of pending writes on a vnode .
 *  @discussion Also wakes up threads waiting for the write count to drop, as in vnode_waitforwrites.
 *  @param vp The vnode whose count to decrement.
 */
void    vnode_writedone(vnode_t vp);

/*!
 *  @function vnode_vtype
 *  @abstract Return a vnode's type.
 *  @param vp The vnode whose type to grab.
 *  @return The vnode's type.
 */
enum vtype      vnode_vtype(vnode_t vp);

/*!
 *  @function vnode_vid
 *  @abstract Return a vnode's vid (generation number), which is constant from creation until reclaim.
 *  @param vp The vnode whose vid to grab.
 *  @return The vnode's vid.
 */
uint32_t        vnode_vid(vnode_t vp);

/*!
 *  @function vnode_isonexternalstorage
 *  @abstract Return whether or not the storage device backing a vnode is external or not.
 *  @param vp The vnode whose physical location is to be determined.
 *  @return TRUE if storage device is external, FALSE if otherwise.
 */
boolean_t vnode_isonexternalstorage(vnode_t vp);

/*!
 *  @function vnode_mountedhere
 *  @abstract Returns a pointer to a mount placed on top of a vnode, should it exist.
 *  @param vp The vnode from whom to take the covering mount.
 *  @return Pointer to mount covering a vnode, or NULL if none exists.
 */
mount_t vnode_mountedhere(vnode_t vp);

/*!
 *  @function vnode_mount
 *  @abstract Get the mount structure for the filesystem that a vnode belongs to.
 *  @param vp The vnode whose mount to grab.
 *  @return The mount, directly.
 */
mount_t vnode_mount(vnode_t vp);

/*!
 *  @function vnode_specrdev
 *  @abstract Return the device id of the device associated with a special file.
 *  @param vp The vnode whose device id to extract--vnode must be a special file.
 *  @return The device id.
 */
dev_t   vnode_specrdev(vnode_t vp);

/*!
 *  @function vnode_fsnode
 *  @abstract Gets the filesystem-specific data associated with a vnode.
 *  @param vp The vnode whose data to grab.
 *  @return The filesystem-specific data, directly.
 */
void *  vnode_fsnode(vnode_t vp);

/*!
 *  @function vnode_clearfsnode
 *  @abstract Sets a vnode's filesystem-specific data to be NULL.
 *  @discussion This routine should only be called when a vnode is no longer in use, i.e. during a VNOP_RECLAIM.
 *  @param vp The vnode whose data to clear out.
 */
void    vnode_clearfsnode(vnode_t vp);

/*!
 *  @function vnode_isvroot
 *  @abstract Determine if a vnode is the root of its filesystem.
 *  @param vp The vnode to test.
 *  @return Nonzero if the vnode is the root, 0 if it is not.
 */
int     vnode_isvroot(vnode_t vp);

/*!
 *  @function vnode_issystem
 *  @abstract Determine if a vnode is marked as a System vnode.
 *  @param vp The vnode to test.
 *  @return Nonzero if the vnode is a system vnode, 0 if it is not.
 */
int     vnode_issystem(vnode_t vp);

/*!
 *  @function vnode_ismount
 *  @abstract Determine if there is currently a mount occurring which will cover this vnode.
 *  @discussion Note that this is only a snapshot; a mount may begin or end at any time.
 *  @param vp The vnode to test.
 *  @return Nonzero if there is a mount in progress, 0 otherwise.
 */
int     vnode_ismount(vnode_t vp);

/*!
 *  @function vnode_isreg
 *  @abstract Determine if a vnode is a regular file.
 *  @param vp The vnode to test.
 *  @return Nonzero if the vnode is of type VREG, 0 otherwise.
 */
int     vnode_isreg(vnode_t vp);

/*!
 *  @function vnode_isdir
 *  @abstract Determine if a vnode is a directory.
 *  @param vp The vnode to test.
 *  @return Nonzero if the vnode is of type VDIR, 0 otherwise.
 */
int     vnode_isdir(vnode_t vp);

/*!
 *  @function vnode_islnk
 *  @abstract Determine if a vnode is a symbolic link.
 *  @param vp The vnode to test.
 *  @return Nonzero if the vnode is of type VLNK, 0 otherwise.
 */
int     vnode_islnk(vnode_t vp);

/*!
 *  @function vnode_isfifo
 *  @abstract Determine if a vnode is a named pipe.
 *  @param vp The vnode to test.
 *  @return Nonzero if the vnode is of type VFIFO, 0 otherwise.
 */
int     vnode_isfifo(vnode_t vp);

/*!
 *  @function vnode_isblk
 *  @abstract Determine if a vnode is a block device special file.
 *  @param vp The vnode to test.
 *  @return Nonzero if the vnode is of type VBLK, 0 otherwise.
 */
int     vnode_isblk(vnode_t vp);

/*!
 *  @function vnode_ischr
 *  @abstract Determine if a vnode is a character device special file.
 *  @param vp The vnode to test.
 *  @return Nonzero if the vnode is of type VCHR, 0 otherwise.
 */
int     vnode_ischr(vnode_t vp);

/*!
 *  @function vnode_isswap
 *  @abstract Determine if a vnode is being used as a swap file.
 *  @param vp The vnode to test.
 *  @return Nonzero if the vnode is being used as swap, 0 otherwise.
 */
int     vnode_isswap(vnode_t vp);

/*!
 *  @function vnode_isnamedstream
 *  @abstract Determine if a vnode is a named stream.
 *  @param vp The vnode to test.
 *  @return Nonzero if the vnode is a named stream, 0 otherwise.
 */
int     vnode_isnamedstream(vnode_t vp);


/*!
 *  @function vnode_ismountedon
 *  @abstract Determine if a vnode is a block device on which a filesystem has been mounted.
 *  @discussion A block device marked as being mounted on cannot be opened.
 *  @param vp The vnode to test.
 *  @return Nonzero if the vnode is a block device on which an filesystem is mounted, 0 otherwise.
 */
int     vnode_ismountedon(vnode_t vp);

/*!
 *  @function vnode_setmountedon
 *  @abstract Set flags indicating that a block device vnode has been mounted as a filesystem.
 *  @discussion A block device marked as being mounted on cannot be opened.
 *  @param vp The vnode to set flags on, a block device.
 */
void    vnode_setmountedon(vnode_t vp);

/*!
 *  @function vnode_clearmountedon
 *  @abstract Clear flags indicating that a block device vnode has been mounted as a filesystem.
 *  @param vp The vnode to clear flags on, a block device.
 */
void    vnode_clearmountedon(vnode_t vp);

/*!
 *  @function vnode_isrecycled
 *  @abstract Check if a vnode is dead or in the process of being killed (recycled).
 *  @discussion This is only a snapshot: a vnode may start to be recycled, or go from dead to in use, at any time.
 *  @param vp The vnode to test.
 *  @return Nonzero if vnode is dead or being recycled, 0 otherwise.
 */
int     vnode_isrecycled(vnode_t vp);

/*!
 *  @function vnode_willberecycled
 *  @abstract Check if a vnode is marked for recycling when the last reference to it is released.
 *  @discussion This is only a snapshot: a vnode may start to be recycled, or go from dead to in use, at any time.
 *  @param vp The vnode to test.
 *  @return Nonzero if vnode is marked for recycling, 0 otherwise.
 */
int     vnode_willberecycled(vnode_t vp);

/*!
 *  @function vnode_isnocache
 *  @abstract Check if a vnode is set to not have its data cached in memory  (i.e. we write-through to disk and always read from disk).
 *  @param vp The vnode to test.
 *  @return Nonzero if vnode is set to not have data chached, 0 otherwise.
 */
int     vnode_isnocache(vnode_t vp);

/*!
 *  @function vnode_israge
 *  @abstract Check if a vnode is marked for rapid aging
 *  @param vp The vnode to test.
 *  @return Nonzero if vnode is marked for rapid aging, 0 otherwise
 */
int     vnode_israge(vnode_t vp);

/*!
 *  @function vnode_needssnapshots
 *  @abstract Check if a vnode needs snapshots events (regardless of its ctime status)
 *  @param vp The vnode to test.
 *  @return Nonzero if vnode needs snapshot events, 0 otherwise
 */
int     vnode_needssnapshots(vnode_t vp);

/*!
 *  @function vnode_setnocache
 *  @abstract Set a vnode to not have its data cached in memory (i.e. we write-through to disk and always read from disk).
 *  @param vp The vnode whose flags to set.
 */
void    vnode_setnocache(vnode_t vp);

/*!
 *  @function vnode_clearnocache
 *  @abstract Clear the flag on a vnode indicating that data should not be cached in memory (i.e. we write-through to disk and always read from disk).
 *  @param vp The vnode whose flags to clear.
 */
void    vnode_clearnocache(vnode_t vp);

/*!
 *  @function vnode_isnoreadahead
 *  @abstract Check if a vnode is set to not have data speculatively read in in hopes of future cache hits.
 *  @param vp The vnode to test.
 *  @return Nonzero if readahead is disabled, 0 otherwise.
 */
int     vnode_isnoreadahead(vnode_t vp);

/*!
 *  @function vnode_setnoreadahead
 *  @abstract Set a vnode to not have data speculatively read in in hopes of hitting in cache.
 *  @param vp The vnode on which to prevent readahead.
 */
void    vnode_setnoreadahead(vnode_t vp);

/*!
 *  @function vnode_clearnoreadahead
 *  @abstract Clear the flag indicating that a vnode should not have data speculatively read in.
 *  @param vp The vnode whose flag to clear.
 */
void    vnode_clearnoreadahead(vnode_t vp);

/*!
 *  @function vnode_isfastdevicecandidate
 *  @abstract Check if a vnode is a candidate to store on the fast device of a composite disk system
 *  @param vp The vnode which you want to test.
 *  @return Nonzero if the vnode is marked as a fast-device candidate
 */
int     vnode_isfastdevicecandidate(vnode_t vp);

/*!
 *  @function vnode_setfastdevicecandidate
 *  @abstract Mark a vnode as a candidate to store on the fast device of a composite disk system
 *  @discussion If the vnode is a directory, all its children will inherit this bit.
 *  @param vp The vnode which you want marked.
 */
void    vnode_setfastdevicecandidate(vnode_t vp);

/*!
 *  @function vnode_clearfastdevicecandidate
 *  @abstract Clear the status of a vnode being a candidate to store on the fast device of a composite disk system.
 *  @param vp The vnode whose flag to clear.
 */
void    vnode_clearfastdevicecandidate(vnode_t vp);

/*!
 *  @function vnode_isautocandidate
 *  @abstract Check if a vnode was automatically selected to be fast-dev candidate (see vnode_setfastdevicecandidate)
 *  @param vp The vnode which you want to test.
 *  @return Nonzero if the vnode was automatically marked as a fast-device candidate
 */
int     vnode_isautocandidate(vnode_t vp);

/*!
 *  @function vnode_setfastdevicecandidate
 *  @abstract Mark a vnode as an automatically selected candidate for storing on the fast device of a composite disk system
 *  @discussion If the vnode is a directory, all its children will inherit this bit.
 *  @param vp The vnode which you want marked.
 */
void    vnode_setautocandidate(vnode_t vp);

/*!
 *  @function vnode_clearautocandidate
 *  @abstract Clear the status of a vnode being an automatic candidate (see above)
 *  @param vp The vnode whose flag to clear.
 */
void    vnode_clearautocandidate(vnode_t vp);

/* left only for compat reasons as User code depends on this from getattrlist, for ex */

/*!
 *  @function vnode_settag
 *  @abstract Set a vnode filesystem-specific "tag."
 *  @discussion Sets a tag indicating which filesystem a vnode belongs to, e.g. VT_HFS, VT_UDF, VT_ZFS.  The kernel never inspects this data, though the filesystem tags are defined in vnode.h; it is for the benefit of user programs via getattrlist.
 *  @param vp The vnode whose tag to set.
 */
void    vnode_settag(vnode_t vp, int tag);

/*!
 *  @function vnode_tag
 *  @abstract Get the vnode filesystem-specific "tag."
 *  @discussion Gets the tag indicating which filesystem a vnode belongs to, e.g. VT_HFS, VT_UDF, VT_ZFS.  The kernel never inspects this data, though the filesystem tags are defined in vnode.h; it is for the benefit of user programs via getattrlist.
 *  @param vp The vnode whose tag to grab.
 *  @return The tag.
 */
int     vnode_tag(vnode_t vp);

/*!
 *  @function vnode_getattr
 *  @abstract Get vnode attributes.
 *  @discussion Desired attributes are set with VATTR_SET_ACTIVE and VNODE_ATTR* macros.  Supported attributes are determined after call with VATTR_IS_SUPPORTED.
 *  @param vp The vnode whose attributes to grab.
 *  @param vap Structure containing: 1) A list of requested attributes 2) Space to indicate which attributes are supported and being returned 3) Space to return attributes.
 *  @param ctx Context for authentication.
 *  @return 0 for success or an error code.
 */
int     vnode_getattr(vnode_t vp, struct vnode_attr *vap, vfs_context_t ctx);

/*
 * Utility function to deal with 32/64 bit fsid
 */
extern uint64_t vnode_get_va_fsid(struct vnode_attr *vap);

/*!
 *  @function vnode_setattr
 *  @abstract Set vnode attributes.
 *  @discussion Attributes to set are marked with VATTR_SET_ACTIVE and VNODE_ATTR* macros.  Attributes successfully set are determined after call with VATTR_IS_SUPPORTED.
 *  @param vp The vnode whose attributes to set.
 *  @param vap Structure containing: 1) A list of attributes to set 2) Space for values for those attributes 3) Space to indicate which attributes were set.
 *  @param ctx Context for authentication.
 *  @return 0 for success or an error code.
 */
int     vnode_setattr(vnode_t vp, struct vnode_attr *vap, vfs_context_t ctx);

/*!
 *  @function vfs_rootvnode
 *  @abstract Returns the root vnode with an iocount.
 *  @discussion Caller must vnode_put() the root node when done.
 *  @return Pointer to root vnode if successful; error code if there is a problem taking an iocount.
 */
vnode_t vfs_rootvnode(void);

/*!
 *  @function vnode_uncache_credentials
 *  @abstract Clear out cached credentials on a vnode.
 *  @discussion When we authorize an action on a vnode, we cache the credential that was authorized and the actions it was authorized for in case a similar request follows.  This function destroys that caching.
 *  @param vp The vnode whose cache to clear.
 */
void    vnode_uncache_credentials(vnode_t vp);

/*!
 *  @function vnode_setmultipath
 *  @abstract Mark a vnode as being reachable by multiple paths, i.e. as a hard link.
 *  @discussion "Multipath" vnodes can be reached through more than one entry in the filesystem, and so must be handled differently for caching and event notification purposes.  A filesystem should mark a vnode with multiple hardlinks this way.
 *  @param vp The vnode to mark.
 */
void    vnode_setmultipath(vnode_t vp);

/*!
 *  @function vnode_vfsmaxsymlen
 *  @abstract Determine the maximum length of a symbolic link for the filesystem on which a vnode resides.
 *  @param vp The vnode for which to get filesystem symlink size cap.
 *  @return Max symlink length.
 */
uint32_t  vnode_vfsmaxsymlen(vnode_t vp);

/*!
 *  @function vnode_vfsisrdonly
 *  @abstract Determine if the filesystem to which a vnode belongs is mounted read-only.
 *  @param vp The vnode for which to get filesystem writeability.
 *  @return Nonzero if the filesystem is read-only, 0 otherwise.
 */
int     vnode_vfsisrdonly(vnode_t vp);

/*!
 *  @function vnode_vfstypenum
 *  @abstract Get the "type number" of the filesystem to which a vnode belongs.
 *  @discussion This is an archaic construct; most filesystems are assigned a type number based on the order in which they are registered with the system.
 *  @param vp The vnode whose filesystem to examine.
 *  @return The type number of the fileystem to which the vnode belongs.
 */
int     vnode_vfstypenum(vnode_t vp);

/*!
 *  @function vnode_vfsname
 *  @abstract Get the name of the filesystem to which a vnode belongs.
 *  @param vp The vnode whose filesystem to examine.
 *  @param buf Destination for vfs name: should have size MFSNAMELEN or greater.
 */
void    vnode_vfsname(vnode_t vp, char *buf);

/*!
 *  @function vnode_vfs64bitready
 *  @abstract Determine if the filesystem to which a vnode belongs is marked as ready to interact with 64-bit user processes.
 *  @param vp The vnode whose filesystem to examine.
 *  @return Nonzero if filesystem is marked ready for 64-bit interactions; 0 otherwise.
 */
int     vnode_vfs64bitready(vnode_t vp);

/* These should move to private ... not documenting for now */
int     vfs_context_get_special_port(vfs_context_t, int, ipc_port_t *);
int     vfs_context_set_special_port(vfs_context_t, int, ipc_port_t);

/*!
 *  @function vfs_context_proc
 *  @abstract Get the BSD process structure associated with a vfs_context_t.
 *  @param ctx Context whose associated process to find.
 *  @return Process if available, NULL otherwise.
 */
proc_t  vfs_context_proc(vfs_context_t ctx);

/*!
 *  @function vfs_context_ucred
 *  @abstract Get the credential associated with a vfs_context_t.
 *  @discussion Succeeds if and only if the context has a thread, the thread has a task, and the task has a BSD proc.
 *  @param ctx Context whose associated process to find.
 *  @returns credential if process available; NULL otherwise
 */
kauth_cred_t    vfs_context_ucred(vfs_context_t ctx);

/*!
 *  @function vfs_context_pid
 *  @abstract Get the process id of the BSD process associated with a vfs_context_t.
 *  @param ctx Context whose associated process to find.
 *  @return Process id.
 */
int     vfs_context_pid(vfs_context_t ctx);


/*!
 *  @function vfs_context_issignal
 *  @abstract Get a bitfield of pending signals for the BSD process associated with a vfs_context_t.
 *  @discussion The bitfield is constructed using the sigmask() macro, in the sense of bits |= sigmask(SIGSEGV).
 *  @param ctx Context whose associated process to find.
 *  @return Bitfield of pending signals.
 */
int     vfs_context_issignal(vfs_context_t ctx, sigset_t mask);

/*!
 *  @function vfs_context_suser
 *  @abstract Determine if a vfs_context_t corresponds to the superuser.
 *  @param ctx Context to examine.
 *  @return 0 if context belongs to superuser, EPERM otherwise.
 */
int     vfs_context_suser(vfs_context_t ctx);

/*!
 *  @function vfs_context_is64bit
 *  @abstract Determine if a vfs_context_t corresponds to a 64-bit user process.
 *  @param ctx Context to examine.
 *  @return Nonzero if context is of 64-bit process, 0 otherwise.
 */
int     vfs_context_is64bit(vfs_context_t ctx);

/*!
 *  @function vfs_context_create
 *  @abstract Create a new vfs_context_t with appropriate references held.
 *  @discussion The context must be released with vfs_context_rele() when no longer in use.
 *  @param ctx Context to copy, or NULL to use information from running thread.
 *  @return The new context, or NULL in the event of failure.
 */
vfs_context_t vfs_context_create(vfs_context_t ctx);

/*!
 *  @function vfs_context_rele
 *  @abstract Release references on components of a context and deallocate it.
 *  @discussion A context should not be referenced after vfs_context_rele has been called.
 *  @param ctx Context to release.
 *  @return Always 0.
 */
int vfs_context_rele(vfs_context_t ctx);

/*!
 *  @function vfs_context_current
 *  @abstract Get the vfs_context for the current thread, or the kernel context if there is no context for current thread.
 *  @discussion Kexts should not use this function--it is preferred to use vfs_context_create(NULL) and vfs_context_rele(), which ensure proper reference counting of underlying structures.
 *  @return Context for current thread, or kernel context if thread context is unavailable.
 */
vfs_context_t vfs_context_current(void) __pure2;

/* Supported filesystem tags for vfs_[set|get]_thread_fs_private */
#define FS_PRIVATE_TAG_APFS (1)

/*!
 *  @function vfs_set_thread_fs_private
 *  @abstract Set the per-thread filesystem private data field.
 *  @discussion Allows a filesystem to store an implementation specific value in the thread struct.
 *  Note that this field is common to all filesystems thus re-entrancy should be taken into consideration.
 *  @param tag Filesystem identification tag.
 *  @param fs_private The value to be set.
 *  @return 0 for success, ENOTSUP if the filesystem tag is not supported.
 */
int vfs_set_thread_fs_private(uint8_t tag, uint64_t fs_private);

/*!
 *  @function vfs_get_thread_fs_private
 *  @abstract Return the per-thread filesystem private data field.
 *  @discussion Returns the per-thread value that was set by vfs_set_thread_fs_private().
 *  @param tag Filesystem identification tag.
 *  @param fs_private The stored per-thread value.
 *  @return 0 for success, ENOTSUP if the filesystem tag is not supported.
 */
int vfs_get_thread_fs_private(uint8_t tag, uint64_t *fs_private);

/*!
 *  @function vflush
 *  @abstract Reclaim the vnodes associated with a mount.
 *  @param mp The mount whose vnodes to kill.
 *  @param skipvp A specific vnode to not reclaim or to let interrupt an un-forced flush
 *  @param flags  Control which
 *  @discussion This function is used to clear out the vnodes associated with a mount as part of the unmount process.
 *  Its parameters can determine which vnodes to skip in the process and whether in-use vnodes should be forcibly reclaimed.
 *  Filesystems should call this function from their unmount code, because VFS code will always call it with SKIPROOT | SKIPSWAP | SKIPSYSTEM; filesystems
 *  must take care of such vnodes themselves.
 *       SKIPSYSTEM skip vnodes marked VSYSTEM
 *       FORCECLOSE force file closeure
 *       WRITECLOSE only close writeable files
 *       SKIPSWAP   skip vnodes marked VSWAP
 *       SKIPROOT   skip root vnodes marked VROOT
 *  @return 0 for success, EBUSY if vnodes were busy and FORCECLOSE was not set.
 */
int     vflush(struct mount *mp, struct vnode *skipvp, int flags);

/*!
 *  @function vnode_get
 *  @abstract Increase the iocount on a vnode.
 *  @discussion If vnode_get() succeeds, the resulting io-reference must be dropped with vnode_put().
 *  This function succeeds unless the vnode in question is dead or in the process of dying AND the current iocount is zero.
 *  This means that it can block an ongoing reclaim which is blocked behind some other iocount.
 *
 *  On success, vnode_get() returns with an iocount held on the vnode; this type of reference is intended to be held only for short periods of time (e.g.
 *  across a function call) and provides a strong guarantee about the life of the vnode; vnodes with positive iocounts cannot be
 *  recycled, and an iocount is required for any  operation on a vnode.  However, vnode_get() does not provide any guarantees
 *  about the identity of the vnode it is called on; unless there is a known existing iocount on the vnode at time the call is made,
 *  it could be recycled and put back in use before the vnode_get() succeeds, so the caller may be referencing a
 *  completely different vnode than was intended.  vnode_getwithref() and vnode_getwithvid()
 *  provide guarantees about vnode identity.
 *
 *  @return 0 for success, ENOENT if the vnode is dead and without existing io-reference.
 */
int     vnode_get(vnode_t);

/*!
 *  @function vnode_getwithvid
 *  @abstract Increase the iocount on a vnode, checking that the vnode is alive and has not changed vid (i.e. been recycled)
 *  @discussion If vnode_getwithvid() succeeds, the resulting io-reference must be dropped with vnode_put().
 *  This function succeeds unless the vnode in question is dead, in the process of dying, or has been recycled (and given a different vnode id).
 *  The intended usage is that a vnode is stored and its vid (vnode_vid(vp)) recorded while an iocount is held (example: a filesystem hash).  The
 *  iocount is then dropped, and time passes (perhaps locks are dropped and picked back up). Subsequently, vnode_getwithvid() is called to get an iocount,
 *  but we are alerted if the vnode has been recycled.
 *
 *  On success, vnode_getwithvid()  returns with an iocount held on the vnode; this type of reference is intended to be held only for short periods of time (e.g.
 *  across a function call) and provides a strong guarantee about the life of the vnode. vnodes with positive iocounts cannot be
 *  recycled. An iocount is required for any operation on a vnode.
 *  @return 0 for success, ENOENT if the vnode is dead, in the process of being reclaimed, or has been recycled and reused.
 */
int     vnode_getwithvid(vnode_t, uint32_t);


/*!
 *  @function vnode_getwithref
 *  @abstract Increase the iocount on a vnode on which a usecount (persistent reference) is held.
 *  @discussion If vnode_getwithref() succeeds, the resulting io-reference must be dropped with vnode_put().
 *  vnode_getwithref() will succeed on dead vnodes; it should fail with ENOENT on vnodes which are in the process of being reclaimed.
 *  Because it is only called with a usecount on the vnode, the caller is guaranteed that the vnode has not been
 *  reused for a different file, though it may now be dead and have deadfs vnops (which return errors like EIO, ENXIO, ENOTDIR).
 *  On success, vnode_getwithref() returns with an iocount held on the vnode; this type of reference is intended to be held only for short periods of time (e.g.
 *  across a function call) and provides a strong guarantee about the life of the vnode. vnodes with positive iocounts cannot be
 *  recycled. An iocount is required for any operation on a vnode.
 *  @return 0 for success, ENOENT if the vnode is dead, in the process of being reclaimed, or has been recycled and reused.
 */
int     vnode_getwithref(vnode_t vp);

/*!
 *  @function vnode_put
 *  @abstract Decrement the iocount on a vnode.
 *  @discussion vnode_put() is called to indicate that a vnode is no longer in active use.  It removes the guarantee that a
 *  vnode will not be recycled.  This routine should be used to release io references no matter how they were obtained.
 *  @param vp The vnode whose iocount to drop.
 *  @return Always 0.
 */
int     vnode_put(vnode_t vp);

/*!
 *  @function vnode_ref
 *  @abstract Increment the usecount on a vnode.
 *  @discussion If vnode_ref() succeeds, the resulting usecount must be released with vnode_rele(). vnode_ref() is called to obtain
 *  a persistent reference on a vnode.  This type of reference does not provide the same strong guarantee that a vnode will persist
 *  as does an iocount--it merely ensures that a vnode will not be reused to represent a different file.  However, a usecount may be
 *  held for extended periods of time, whereas an iocount is intended to be obtained and released quickly as part of performing a
 *  vnode operation.  A holder of a usecount must call vnode_getwithref()/vnode_put() in order to perform any operations on that vnode.
 *  @param vp The vnode on which to obtain a persistent reference.
 *  @return 0 for success; ENOENT if the vnode is dead or in the process of being recycled AND the calling thread is not the vnode owner.
 */
int     vnode_ref(vnode_t vp);

/*!
 *  @function vnode_rele
 *  @abstract Decrement the usecount on a vnode.
 *  @discussion vnode_rele() is called to relese a persistent reference on a vnode.  Releasing the last usecount
 *  opens the door for a vnode to be reused as a new file; it also triggers a VNOP_INACTIVE call to the filesystem,
 *  though that will not happen immediately if there are outstanding iocount references.
 *  @param vp The vnode whose usecount to drop.
 */
void    vnode_rele(vnode_t vp);

/*!
 *  @function vnode_isinuse
 *  @abstract Determine if the number of persistent (usecount) references on a vnode is greater than a given count.
 *  @discussion vnode_isinuse() compares a vnode's  usecount (corresponding to vnode_ref() calls) to its refcnt parameter
 *  (the number of references the caller expects to be on the vnode).  Note that "kusecount" references, corresponding
 *  to parties interested only in event notifications, e.g. open(..., O_EVTONLY), are not counted towards the total; the comparison is
 *  (usecount - kusecount > recnt).  It is
 *  also important to note that the result is only a snapshot; usecounts can change from moment to moment, and the result of vnode_isinuse
 *  may no longer be correct the very moment that the caller receives it.
 *  @param vp The vnode whose use-status to check.
 *  @param refcnt The threshold for saying that a vnode is in use.
 */
int     vnode_isinuse(vnode_t vp, int refcnt);

/*!
 *  @function vnode_recycle
 *  @abstract Cause a vnode to be reclaimed and prepared for reuse.
 *  @discussion Like all vnode KPIs, must be called with an iocount on the target vnode.
 *  vnode_recycle() will mark that vnode for reclaim when all existing references are dropped.
 *  @param vp The vnode to recycle.
 *  @return 1 if the vnode was reclaimed (i.e. there were no existing references), 0 if it was only marked for future reclaim.
 */
int     vnode_recycle(vnode_t vp);


#define VNODE_UPDATE_PARENT     0x01
#define VNODE_UPDATE_NAMEDSTREAM_PARENT VNODE_UPDATE_PARENT
#define VNODE_UPDATE_NAME       0x02
#define VNODE_UPDATE_CACHE      0x04
#define VNODE_UPDATE_PURGE      0x08
/*!
 *  @function vnode_update_identity
 *  @abstract Update vnode data associated with the vfs cache.
 *  @discussion The vfs namecache is central to tracking vnode-identifying data and to locating files on the system.  vnode_update_identity()
 *  is used to update vnode data associated with the cache. It can set a vnode's parent and/or name (also potentially set by vnode_create())
 *  or flush cache data.
 *  @param vp The vnode whose information to update.
 *  @param dvp Parent to set on the vnode if VNODE_UPDATE_PARENT is used.
 *  @param name Name to set in the cache for the vnode if VNODE_UPDATE_NAME is used.  The buffer passed in can be subsequently freed, as the cache
 *  does its own name storage.  String should be NULL-terminated unless length and hash value are specified.
 *  @param name_len Length of name, if known.  Passing 0 causes the cache to determine the length itself.
 *  @param name_hashval Hash value of name, if known.  Passing 0 causes the cache to hash the name itself.
 *  @param flags VNODE_UPDATE_PARENT: set parent.  VNODE_UPDATE_NAME: set name.  VNODE_UPDATE_CACHE: flush cache entries for hard links
 *  associated with this file.  VNODE_UPDATE_PURGE: flush cache entries for hard links and children of this file.
 */
void    vnode_update_identity(vnode_t vp, vnode_t dvp, const char *name, int name_len, uint32_t name_hashval, int flags);

/*!
 *  @function vn_bwrite
 *  @abstract System-provided implementation of "bwrite" vnop.
 *  @discussion This routine is available for filesystems which do not want to implement their own "bwrite" vnop.  It just calls
 *  buf_bwrite() without modifying its arguments.
 *  @param ap Standard parameters to a bwrite vnop.
 *  @return Results of buf_bwrite directly.
 */
int     vn_bwrite(struct vnop_bwrite_args *ap);

/*!
 *  @function vnode_authorize
 *  @abstract Authorize a kauth-style action on a vnode.
 *  @discussion Operations on dead vnodes are always allowed (though never do anything).
 *  @param vp Vnode on which to authorize action.
 *  @param dvp Parent of "vp," can be NULL.
 *  @param action Action to authorize, e.g. KAUTH_VNODE_READ_DATA.  See bsd/sys/kauth.h.
 *  @param ctx Context for which to authorize actions.
 *  @return EACCESS if permission is denied.  0 if operation allowed.  Various errors from lower layers.
 */
int     vnode_authorize(vnode_t vp, vnode_t dvp, kauth_action_t action, vfs_context_t ctx);


/*!
 *  @function vnode_authattr
 *  @abstract Given a vnode_attr structure, determine what kauth-style actions must be authorized in order to set those attributes.
 *  @discussion vnode_authorize requires kauth-style actions; if we want to set a vnode_attr structure on a vnode, we need to translate
 *  the set of attributes to a set of kauth-style actions.  This routine will return errors for certain obviously disallowed, or
 *  incoherent, actions.
 *  @param vp The vnode on which to authorize action.
 *  @param vap Pointer to vnode_attr struct containing desired attributes to set and their values.
 *  @param actionp Destination for set of actions to authorize
 *  @param ctx Context for which to authorize actions.
 *  @return 0 (and a result in "actionp" for success.  Otherwise, an error code.
 */
int     vnode_authattr(vnode_t vp, struct vnode_attr *vap, kauth_action_t *actionp, vfs_context_t ctx);

/*!
 *  @function vnode_authattr_new
 *  @abstract Initialize and validate file creation parameters with respect to the current context.
 *  @discussion vnode_authattr_new() will fill in unitialized values in the vnode_attr struct with defaults, and will validate the structure
 *  with respect to the current context for file creation.
 *  @param dvp The directory in which creation will occur.
 *  @param vap Pointer to vnode_attr struct containing desired attributes to set and their values.
 *  @param noauth If 1, treat the caller as the superuser, i.e. do not check permissions.
 *  @param ctx Context for which to authorize actions.
 *  @return KAUTH_RESULT_ALLOW for success, an error to indicate invalid or disallowed attributes.
 */
int     vnode_authattr_new(vnode_t dvp, struct vnode_attr *vap, int noauth, vfs_context_t ctx);

/*!
 *  @function vnode_close
 *  @abstract Close a file as opened with vnode_open().
 *  @discussion vnode_close() drops the refcount (persistent reference) picked up in vnode_open() and calls down to the filesystem with VNOP_CLOSE.  It should
 *  be called with both an iocount and a refcount on the vnode and will drop both.
 *  @param vp The vnode to close.
 *  @param flags Flags to close: FWASWRITTEN indicates that the file was written to.
 *  @param ctx Context against which to validate operation.
 *  @return 0 for success or an error from the filesystem.
 */
errno_t vnode_close(vnode_t vp, int flags, vfs_context_t ctx);

/*!
 *  @function vn_getpath
 *  @abstract Construct the path to a vnode.
 *  @discussion Paths to vnodes are not always straightforward: a file with multiple hard-links will have multiple pathnames,
 *  and it is sometimes impossible to determine a vnode's full path.  vn_getpath() will not enter the filesystem.
 *  @param vp The vnode whose path to obtain.
 *  @param pathbuf Destination for pathname; should be of size MAXPATHLEN
 *  @param len Destination for length of resulting path string.  Result will include NULL-terminator in count--that is, "len"
 *  will be strlen(pathbuf) + 1.
 *  @return 0 for success or an error code.
 */
int vn_getpath(struct vnode *vp, char *pathbuf, int *len);

/*!
 *  @function vnode_notify
 *  @abstract Send a notification up to VFS.
 *  @param vp Vnode for which to provide notification.
 *  @param vap Attributes for that vnode, to be passed to fsevents.
 *  @discussion Filesystem determines which attributes to pass up using
 *  vfs_get_notify_attributes(&vap).  The most specific events possible should be passed,
 *  e.g. VNODE_EVENT_FILE_CREATED on a directory rather than just VNODE_EVENT_WRITE, but
 *  a less specific event can be passed up if more specific information is not available.
 *  Will not reenter the filesystem.
 *  @return 0 for success, else an error code.
 */
int     vnode_notify(vnode_t vp, uint32_t events, struct vnode_attr *vap);

/*!
 *  @function vfs_get_notify_attributes
 *  @abstract Determine what attributes are required to send up a notification with vnode_notify().
 *  @param vap Structure to initialize and activate required attributes on.
 *  @discussion Will not reenter the filesystem.
 *  @return 0 for success, nonzero for error (currently always succeeds).
 */
int     vfs_get_notify_attributes(struct vnode_attr *vap);

/*
 * Flags for the vnode_lookup and vnode_open
 */
#define VNODE_LOOKUP_NOFOLLOW           0x01
#define VNODE_LOOKUP_NOCROSSMOUNT       0x02
#define VNODE_LOOKUP_CROSSMOUNTNOWAIT   0x04
/*!
 *  @function vnode_lookup
 *  @abstract Convert a path into a vnode.
 *  @discussion This routine is a thin wrapper around xnu-internal lookup routines; if successful,
 *  it returns with an iocount held on the resulting vnode which must be dropped with vnode_put().
 *  @param path Path to look up.
 *  @param flags VNODE_LOOKUP_NOFOLLOW: do not follow symbolic links.  VNODE_LOOKUP_NOCROSSMOUNT: do not cross mount points.
 *  @return Results 0 for success or an error code.
 */
errno_t vnode_lookup(const char *path, int flags, vnode_t *vpp, vfs_context_t ctx);


/*!
 *  @function vnode_open
 *  @abstract Open a file identified by a path--roughly speaking an in-kernel open(2).
 *  @discussion If vnode_open() succeeds, it returns with both an iocount and a usecount on the
 *  returned vnode. Both will be release once vnode_close is called.
 *  @param path Path to look up.
 *  @param fmode e.g. O_NONBLOCK, O_APPEND; see bsd/sys/fcntl.h.
 *  @param cmode Permissions with which to create file if it does not exist.
 *  @param flags Same as vnode_lookup().
 *  @param vpp Destination for vnode.
 *  @param ctx Context with which to authorize open/creation.
 *  @return 0 for success or an error code.
 */
errno_t vnode_open(const char *path, int fmode, int cmode, int flags, vnode_t *vpp, vfs_context_t ctx);

/*
 * exported vnode operations
 */

/*!
 *  @function vnode_iterate
 *  @abstract Perform an operation on (almost) all vnodes from a given mountpoint.
 *  @param mp Mount whose vnodes to operate on.
 *  @param flags
 *  VNODE_RELOAD			Mark inactive vnodes for recycle.
 *  VNODE_WAIT
 *  VNODE_WRITEABLE             Only examine vnodes with writes in progress.
 *  VNODE_WITHID			No effect.
 *  VNODE_NOLOCK_INTERNAL	No effect.
 *  VNODE_NODEAD			No effect.
 *  VNODE_NOSUSPEND		No effect.
 *  VNODE_ITERATE_ALL           No effect.
 *  VNODE_ITERATE_ACTIVE        No effect.
 *  VNODE_ITERATE_INACTIVE	No effect.
 *
 *  @param callout Function to call on each vnode.
 *  @param arg Argument which will be passed to callout along with each vnode.
 *  @return Zero for success, else an error code.  Will return 0 immediately if there are no vnodes hooked into the mount.
 *  @discussion Skips vnodes which are dead, in the process of reclaim, suspended, or of type VNON.
 */
int     vnode_iterate(struct mount *mp, int flags, int (*callout)(struct vnode *, void *), void *arg);

/*
 * flags passed into vnode_iterate
 */
#define VNODE_RELOAD                    0x01
#define VNODE_WAIT                              0x02
#define VNODE_WRITEABLE                 0x04
#define VNODE_WITHID                    0x08
#define VNODE_NOLOCK_INTERNAL   0x10
#define VNODE_NODEAD                    0x20
#define VNODE_NOSUSPEND                 0x40
#define VNODE_ITERATE_ALL               0x80
#define VNODE_ITERATE_ACTIVE    0x100
#define VNODE_ITERATE_INACTIVE  0x200

/*
 * return values from callback
 */
#define VNODE_RETURNED          0       /* done with vnode, reference can be dropped */
#define VNODE_RETURNED_DONE     1       /* done with vnode, reference can be dropped, terminate iteration */
#define VNODE_CLAIMED           2       /* don't drop reference */
#define VNODE_CLAIMED_DONE      3       /* don't drop reference, terminate iteration */

/*!
 *  @function vn_revoke
 *  @abstract Invalidate all references to a vnode.
 *  @discussion Reclaims the vnode, giving it deadfs vnops (though not halting operations which are already in progress).
 *  Also reclaims all aliased vnodes (important for devices).  People holding usecounts on the vnode, e.g. processes
 *  with the file open, will find that all subsequent operations but closing the file fail.
 *  @param vp The vnode to revoke.
 *  @param flags Unused.
 *  @param ctx Context against which to validate operation.
 *  @return 0 always.
 */
int     vn_revoke(vnode_t vp, int flags, vfs_context_t ctx);

/* namecache function prototypes */
/*!
 *  @function cache_lookup
 *  @abstract Check for a filename in a directory using the VFS name cache.
 *  @discussion cache_lookup() will flush negative cache entries and return 0 if the operation of the cn_nameiop is CREATE or RENAME.
 *  Often used from the filesystem during a lookup vnop.  The filesystem will be called to if there is a negative cache entry for a file,
 *  so it can make sense to initially check for negative entries (and possibly lush them).
 *  @param dvp Directory in which lookup is occurring.
 *  @param vpp Destination for vnode pointer.
 *  @param cnp Various data about lookup, e.g. filename and intended operation.
 *  @return ENOENT: the filesystem has previously added a negative entry with cache_enter() to indicate that there is no
 *  file of the given name in "dp."  -1: successfully found a cached vnode (vpp is set).  0: No data in the cache, or operation is CREATE/RENAME.
 */
int     cache_lookup(vnode_t dvp, vnode_t *vpp, struct componentname *cnp);

/*!
 *  @function cache_enter
 *  @abstract Add a (name,vnode) entry to the VFS namecache.
 *  @discussion Generally used to add a cache entry after a successful filesystem-level lookup or to add a
 *  negative entry after one which did not find its target.
 *  @param dvp Directory in which file lives.
 *  @param vp File to add to cache. A non-NULL vp is stored for rapid access; a NULL vp indicates
 *  that there is no such file in the directory and speeds future failed lookups.
 *  @param cnp Various data about lookup, e.g. filename and intended operation.
 */
void    cache_enter(vnode_t dvp, vnode_t vp, struct componentname *cnp);

/*!
 *  @function cache_purge
 *  @abstract Remove all data relating to a vnode from the namecache.
 *  @discussion Will flush all hardlinks to the vnode as well as all children (should any exist).  Logical
 *  to use when cached data about a vnode becomes invalid, for instance in an unlink.
 *  @param vp The vnode to purge.
 */
void    cache_purge(vnode_t vp);

/*!
 *  @function cache_purge_negatives
 *  @abstract Remove all negative cache entries which are children of a given vnode.
 *  @discussion Appropriate to use when negative cache information for a directory could have
 *  become invalid, e.g. after file creation.
 *  @param vp The vnode whose negative children to purge.
 */
void    cache_purge_negatives(vnode_t vp);


/*
 * Global string-cache routines.  You can pass zero for nc_hash
 * if you don't know it (add_name() will then compute the hash).
 * There are no flags for now but maybe someday.
 */
/*!
 *  @function vfs_addname
 *  @abstract Deprecated
 *  @discussion vnode_update_identity() and vnode_create() make vfs_addname() unnecessary for kexts.
 */
const char *vfs_addname(const char *name, uint32_t len, uint32_t nc_hash, uint32_t flags);

/*!
 *  @function vfs_removename
 *  @abstract Deprecated
 *  @discussion vnode_update_identity() and vnode_create() make vfs_addname() unnecessary for kexts.
 */
int   vfs_removename(const char *name);

/*!
 *  @function vcount
 *  @abstract Count total references to a given file, disregarding "kusecount" (event listener, as with O_EVTONLY) references.
 *  @discussion For a regular file, just return (usecount-kusecount); for device files, return the sum over all
 *  vnodes 'v' which reference that device of (usecount(v) - kusecount(v)).  Note that this is merely a snapshot and could be
 *  invalid by the time the caller checks the result.
 *  @param vp The vnode whose references to count.
 *  @return Count of references.
 */
int     vcount(vnode_t vp);

/*!
 *  @function vn_path_package_check
 *  @abstract Figure out if a path corresponds to a Mac OS X package.
 *  @discussion  Determines if the extension on a path is a known OS X extension type.
 *  @param vp Unused.
 *  @param path Path to check.
 *  @param pathlen Size of path buffer.
 *  @param component Set to index of start of last path component if the path is found to be a package. Set to -1 if
 *  the path is not a known package type.
 *  @return 0 unless some parameter was invalid, in which case EINVAL is returned.  Determine package-ness by checking
 *  what *component is set to.
 */
int vn_path_package_check(vnode_t vp, char *path, int pathlen, int *component);


/*!
 *  @function vn_rdwr
 *  @abstract Read from or write to a file.
 *  @discussion vn_rdwr() abstracts the details of constructing a uio and picking a vnode operation to allow
 *  simple in-kernel file I/O.
 *  @param rw UIO_READ for a read, UIO_WRITE for a write.
 *  @param vp The vnode on which to perform I/O.
 *  @param base Start of buffer into which to read or from which to write data.
 *  @param len Length of buffer.
 *  @param offset Offset within the file at which to start I/O.
 *  @param segflg What kind of address "base" is.   See uio_seg definition in sys/uio.h.  UIO_SYSSPACE for kernelspace, UIO_USERSPACE for userspace.
 *  UIO_USERSPACE32 and UIO_USERSPACE64 are in general preferred, but vn_rdwr will make sure that has the correct address sizes.
 *  @param ioflg Defined in vnode.h, e.g. IO_NOAUTH, IO_NOCACHE.
 *  @param cred Credential to pass down to filesystem for authentication.
 *  @param aresid Destination for amount of requested I/O which was not completed, as with uio_resid().
 *  @param p Process requesting I/O.
 *  @return 0 for success; errors from filesystem, and EIO if did not perform all requested I/O and the "aresid" parameter is NULL.
 */
int     vn_rdwr(enum uio_rw rw, struct vnode *vp, caddr_t base, int len, off_t offset, enum uio_seg segflg, int ioflg, kauth_cred_t cred, int *aresid, proc_t p);

/*!
 *  @function vnode_getname
 *  @abstract Get the name of a vnode from the VFS namecache.
 *  @discussion Not all vnodes have names, and vnode names can change (notably, hardlinks).  Use this routine at your own risk.
 *  The string is returned with a refcount incremented in the cache; callers must call vnode_putname() to release that reference.
 *  @param vp The vnode whose name to grab.
 *  @return The name, or NULL if unavailable.
 */
const char      *vnode_getname(vnode_t vp);

/*!
 *  @function vnode_putname
 *  @abstract Release a reference on a name from the VFS cache.
 *  @discussion Should be called on a string obtained with vnode_getname().
 *  @param name String to release.
 */
void    vnode_putname(const char *name);

/*!
 *  @function vnode_getparent
 *  @abstract Get an iocount on the parent of a vnode.
 *  @discussion A vnode's parent may change over time or be reclaimed, so vnode_getparent() may return different
 *  results at different times (e.g. a multiple-hardlink file). The parent is returned with an iocount which must
 *  subsequently be dropped with vnode_put().
 *  @param vp The vnode whose parent to grab.
 *  @return Parent if available, else NULL.
 */
vnode_t vnode_getparent(vnode_t vp);

/*!
 *  @function vnode_setdirty
 *  @abstract Mark the vnode as having data or metadata that needs to be written out during reclaim
 *  @discussion The vnode should be marked as dirty anytime a file system defers flushing of data or meta-data associated with it.
 *  @param vp the vnode to mark as dirty
 *  @return 0 if successful else an error code.
 */
int     vnode_setdirty(vnode_t vp);

/*!
 *  @function vnode_cleardirty
 *  @abstract Mark the vnode as clean i.e. all its data or metadata has been flushed
 *  @discussion The vnode should be marked as clean whenever the file system is done flushing data or meta-data associated with it.
 *  @param vp the vnode to clear as being dirty
 *  @return 0 if successful else an error code.
 */
int     vnode_cleardirty(vnode_t vp);

/*!
 *  @function vnode_isdirty
 *  @abstract Determine if a vnode is marked dirty.
 *  @discussion The vnode should be marked as clean whenever the file system is done flushing data or meta-data associated with it.
 *  @param vp the vnode to test.
 *  @return Non-zero if the vnode is dirty, 0 otherwise.
 */
int     vnode_isdirty(vnode_t vp);




/*!
 *  @function vnode_getbackingvnode
 *  @abstract If the input vnode is a NULLFS mirrored vnode, then return the vnode it wraps.
 *  @Used to un-mirror files, primarily for security purposes. On success, out_vp is always set to a vp with an iocount. The caller must release the iocount.
 *  @param in_vp The vnode being asked about
 *  @param out_vpp A pointer to the output vnode, unchanged on error
 *  @return 0 on Success, ENOENT if in_vp doesn't mirror anything, EINVAL on parameter errors.
 */
int vnode_getbackingvnode(vnode_t in_vp, vnode_t* out_vpp);

/*
 * Helper functions for implementing VNOP_GETATTRLISTBULK for a filesystem
 */

/*!
 *  @function vfs_setup_vattr_from_attrlist
 *  @abstract Setup a vnode_attr structure given an attrlist structure.
 *  @Used by a VNOP_GETATTRLISTBULK implementation to setup a vnode_attr structure from a attribute list. It also returns the fixed size of the attribute buffer required.
 *  @warning this forces new fork attr behavior, i.e. reinterpret forkattr bits as ATTR_CMNEXT
 *  @param alp Pointer to attribute list structure.
 *  @param vap Pointer to vnode_attr structure.
 *  @param obj_vtype Type of object - If VNON is passed, then the type is ignored and common, file and dir attrs are used to initialise the vattrs. If set to VDIR, only common and directory attributes are used. For all other types, only common and file attrbutes are used.
 *  @param attr_fixed_sizep Returns the fixed length required in the attrbute buffer for the object. NULL should be passed if it is not required.
 *  @param ctx vfs context of caller.
 *  @return error.
 */
errno_t vfs_setup_vattr_from_attrlist(struct attrlist *alp, struct vnode_attr *vap, enum vtype obj_vtype, ssize_t *attr_fixed_sizep, vfs_context_t ctx);

/*!
 *  @function vfs_attr_pack
 *  @abstract Pack a vnode_attr structure into a buffer in the same format as getattrlist(2).
 *  @Used by a VNOP_GETATTRLISTBULK implementation to pack data provided into a vnode_attr structure into a buffer the way getattrlist(2) does.
 *  @param vp If available, the vnode for which the attributes are being given, NULL if vnode is not available (which will usually be the case for a VNOP_GETATTRLISTBULK implementation.
 *  @param uio - a uio_t initialised with one iovec..
 *  @param alp - Pointer to an attrlist structure.
 *  @param options - options for call (same as options for getattrlistbulk(2)).
 *  @param vap Pointer to a filled in vnode_attr structure. Data from the vnode_attr structure will be used to copy and lay out the data in the required format for getatrlistbulk(2) by this function.
 *  @param fndesc Currently unused
 *  @param ctx vfs context of caller.
 *  @return error.
 */
errno_t vfs_attr_pack(vnode_t vp, uio_t uio, struct attrlist *alp, uint64_t options, struct vnode_attr *vap, void *fndesc, vfs_context_t ctx);

/*!
 *  @function vfs_attr_pack_ex
 *  @abstract Pack a vnode_attr structure into a buffer in the same format as getattrlist(2).
 *  @Used by a VNOP_GETATTRLISTBULK implementation to pack data provided into a vnode_attr structure into a buffer the way getattrlist(2) does.
 *  @param mp the mount structure for the filesystem the packing operation is happening on.
 *  @param vp If available, the vnode for which the attributes are being given, NULL if vnode is not available (which will usually be the case for a VNOP_GETATTRLISTBULK implementation.
 *  @param uio - a uio_t initialised with one iovec..
 *  @param alp - Pointer to an attrlist structure.
 *  @param options - options for call (same as options for getattrlistbulk(2)).
 *  @param vap Pointer to a filled in vnode_attr structure. Data from the vnode_attr structure will be used to copy and lay out the data in the required format for getatrlistbulk(2) by this function.
 *  @param fndesc Currently unused
 *  @param ctx vfs context of caller.
 *  @return error.
 */
errno_t vfs_attr_pack_ext(mount_t mp, vnode_t vp, uio_t uio, struct attrlist *alp, uint64_t options, struct vnode_attr *vap, void *fndesc, vfs_context_t ctx);


__END_DECLS


/*
 * Structure for vnode level IO compression stats
 */

#define IOCS_BUFFER_NUM_SIZE_BUCKETS         10
#define IOCS_BUFFER_MAX_BUCKET               9
#define IOCS_BUFFER_NUM_COMPRESSION_BUCKETS  7
#define IOCS_BLOCK_NUM_SIZE_BUCKETS          16

struct io_compression_stats {
	uint64_t uncompressed_size;
	uint64_t compressed_size;
	uint32_t buffer_size_compression_dist[IOCS_BUFFER_NUM_SIZE_BUCKETS][IOCS_BUFFER_NUM_COMPRESSION_BUCKETS];
	uint32_t block_compressed_size_dist[IOCS_BLOCK_NUM_SIZE_BUCKETS];
};
typedef struct io_compression_stats *io_compression_stats_t;

#define IOCS_SBE_PATH_LEN             128
#define IOCS_PATH_START_BYTES_TO_COPY 108
#define IOCS_PATH_END_BYTES_TO_COPY   20 /* Includes null termination */

#define IOCS_SYSCTL_LIVE                  0x00000001
#define IOCS_SYSCTL_STORE_BUFFER_RD_ONLY  0x00000002
#define IOCS_SYSCTL_STORE_BUFFER_MARK     0x00000004

struct iocs_store_buffer_entry {
	char     path_name[IOCS_SBE_PATH_LEN];
	struct io_compression_stats iocs;
};

#endif /* !_VNODE_H_ */
