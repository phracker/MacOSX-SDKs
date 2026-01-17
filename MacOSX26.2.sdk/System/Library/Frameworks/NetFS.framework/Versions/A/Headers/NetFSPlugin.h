/*
 *  NetFSPlugin.h
 *
 *  Copyright (c) 2008-2009 Apple Inc. All rights reserved.
 */

#include <NetFS/NetFS.h>
#include <CoreFoundation/CFPlugInCOM.h>

API_UNAVAILABLE_BEGIN(ios, tvos, watchos)

/* NetFS Type UUID: 02FE7D14-4E91-481E-946C-CE233C798CC0 */
#define kNetFSTypeID (CFUUIDGetConstantUUIDWithBytes(NULL, 0x02, 0xfe, 0x7d, 0x14, 0x4e, 0x91, 0x48, 0x1e, 0x94, 0x6c, 0xce, 0x23, 0x3c, 0x79, 0x8c, 0xc0))

/* NetFS Interface UUID: 8F34B6C4-F2E4-4ECD-8625-E5665811DE37 */
#define kfs_NetFSMountInterfaceID_V1 (CFUUIDGetConstantUUIDWithBytes(NULL, 0x8f, 0x34, 0xb6, 0xc4, 0xf2, 0xe4, 0x4e, 0xcd, 0x86, 0x25, 0xe5, 0x66, 0x58, 0x11, 0xde, 0x37))

typedef struct NetFSMountInterface_V1 {
    IUNKNOWN_C_GUTS;
    netfsError (*CreateSessionRef)(void **out_SessionRef);
    netfsError (*GetServerInfo)(CFURLRef in_URL,
		void *in_SessionRef, CFDictionaryRef in_GetInfoOptions,
		CFDictionaryRef *out_ServerParms);
    netfsError (*ParseURL)(CFURLRef in_URL, CFDictionaryRef *out_URLParms);
    netfsError (*CreateURL)(CFDictionaryRef in_URLParms, CFURLRef *out_URL);
    netfsError (*OpenSession)(CFURLRef in_URL,
		void *in_SessionRef,
		CFDictionaryRef in_OpenOptions,
		CFDictionaryRef *out_SessionInfo);
    netfsError (*EnumerateShares)(void *in_SessionRef,
		CFDictionaryRef in_EnumerateOptions,
		CFDictionaryRef *out_Sharepoints);
    netfsError (*Mount)(void *in_SessionRef,
		CFURLRef in_URL,
		CFStringRef in_Mountpoint,
		CFDictionaryRef in_MountOptions,
		CFDictionaryRef *out_MountInfo);
    netfsError (*Cancel)(void *in_SessionRef);
    netfsError (*CloseSession)(void *in_SessionRef);
    netfsError (*GetMountInfo)(CFStringRef in_mountpoint, CFDictionaryRef *out_MountInfo);
} NetFSMountInterface_V1;

typedef struct {
    void *_interface;
    CFUUIDRef _factoryID;
    UInt32 _refCount;
} NetFSInterface;

NETFS_EXPORT ULONG NetFSInterface_AddRef(void *);
NETFS_EXPORT ULONG NetFSInterface_Release(void *);
NETFS_EXPORT NetFSInterface *NetFS_CreateInterface(CFUUIDRef factoryID, void *interfaceFTbl);

/* this cannot be called from a plugin! */
NETFS_EXPORT HRESULT NetFSQueryInterface(void *, REFIID iid, LPVOID *ppv);

API_UNAVAILABLE_END

