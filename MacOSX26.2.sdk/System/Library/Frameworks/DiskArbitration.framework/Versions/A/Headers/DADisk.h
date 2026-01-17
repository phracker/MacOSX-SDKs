/*
 * Copyright (c) 1998-2015 Apple Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */

#ifndef __DISKARBITRATION_DADISK__
#define __DISKARBITRATION_DADISK__

#include <CoreFoundation/CoreFoundation.h>
#include <IOKit/IOKitLib.h>

#include <DiskArbitration/DASession.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

CF_ASSUME_NONNULL_BEGIN
CF_IMPLICIT_BRIDGING_ENABLED

extern const CFStringRef kDADiskDescriptionVolumeKindKey       /* ( CFString     ) */ API_AVAILABLE(macos(10.4));
extern const CFStringRef kDADiskDescriptionVolumeMountableKey  /* ( CFBoolean    ) */ API_AVAILABLE(macos(10.4));
extern const CFStringRef kDADiskDescriptionVolumeNameKey       /* ( CFString     ) */ API_AVAILABLE(macos(10.4));
extern const CFStringRef kDADiskDescriptionVolumeNetworkKey    /* ( CFBoolean    ) */ API_AVAILABLE(macos(10.4));
extern const CFStringRef kDADiskDescriptionVolumePathKey       /* ( CFURL        ) */ API_AVAILABLE(macos(10.4));
extern const CFStringRef kDADiskDescriptionVolumeTypeKey       /* ( CFString     ) */ API_AVAILABLE(macos(10.11));
extern const CFStringRef kDADiskDescriptionVolumeUUIDKey      /* ( CFUUID       ) */ API_AVAILABLE(macos(10.4));
extern const CFStringRef kDADiskDescriptionMediaBlockSizeKey   /* ( CFNumber     ) */ API_AVAILABLE(macos(10.4));
extern const CFStringRef kDADiskDescriptionMediaBSDMajorKey    /* ( CFNumber     ) */ API_AVAILABLE(macos(10.4));
extern const CFStringRef kDADiskDescriptionMediaBSDMinorKey    /* ( CFNumber     ) */ API_AVAILABLE(macos(10.4));
extern const CFStringRef kDADiskDescriptionMediaBSDNameKey     /* ( CFString     ) */ API_AVAILABLE(macos(10.4));
extern const CFStringRef kDADiskDescriptionMediaBSDUnitKey     /* ( CFNumber     ) */ API_AVAILABLE(macos(10.4));
extern const CFStringRef kDADiskDescriptionMediaContentKey     /* ( CFString     ) */ API_AVAILABLE(macos(10.4));
extern const CFStringRef kDADiskDescriptionMediaEjectableKey   /* ( CFBoolean    ) */ API_AVAILABLE(macos(10.4));
extern const CFStringRef kDADiskDescriptionMediaIconKey        /* ( CFDictionary ) */ API_AVAILABLE(macos(10.4));
extern const CFStringRef kDADiskDescriptionMediaKindKey        /* ( CFString     ) */ API_AVAILABLE(macos(10.4));
extern const CFStringRef kDADiskDescriptionMediaLeafKey        /* ( CFBoolean    ) */ API_AVAILABLE(macos(10.4));
extern const CFStringRef kDADiskDescriptionMediaNameKey        /* ( CFString     ) */ API_AVAILABLE(macos(10.4));
extern const CFStringRef kDADiskDescriptionMediaPathKey        /* ( CFString     ) */ API_AVAILABLE(macos(10.4));
extern const CFStringRef kDADiskDescriptionMediaRemovableKey   /* ( CFBoolean    ) */ API_AVAILABLE(macos(10.4));
extern const CFStringRef kDADiskDescriptionMediaSizeKey        /* ( CFNumber     ) */ API_AVAILABLE(macos(10.4));
extern const CFStringRef kDADiskDescriptionMediaTypeKey        /* ( CFString     ) */ API_AVAILABLE(macos(10.4));
extern const CFStringRef kDADiskDescriptionMediaUUIDKey        /* ( CFUUID       ) */ API_AVAILABLE(macos(10.5));
extern const CFStringRef kDADiskDescriptionMediaWholeKey       /* ( CFBoolean    ) */ API_AVAILABLE(macos(10.4));
extern const CFStringRef kDADiskDescriptionMediaWritableKey    /* ( CFBoolean    ) */ API_AVAILABLE(macos(10.4));
extern const CFStringRef kDADiskDescriptionMediaEncryptedKey   /* ( CFBoolean    ) */ API_AVAILABLE(macos(10.14.4));
extern const CFStringRef kDADiskDescriptionMediaEncryptionDetailKey /* ( CFNumber ) */API_AVAILABLE(macos(10.14.4));

extern const CFStringRef kDADiskDescriptionDeviceGUIDKey       /* ( CFData       ) */ API_AVAILABLE(macos(10.4));
extern const CFStringRef kDADiskDescriptionDeviceInternalKey   /* ( CFBoolean    ) */ API_AVAILABLE(macos(10.4));
extern const CFStringRef kDADiskDescriptionDeviceModelKey      /* ( CFString     ) */ API_AVAILABLE(macos(10.4));
extern const CFStringRef kDADiskDescriptionDevicePathKey      /* ( CFString     ) */  API_AVAILABLE(macos(10.4));
extern const CFStringRef kDADiskDescriptionDeviceProtocolKey   /* ( CFString     ) */ API_AVAILABLE(macos(10.4));
extern const CFStringRef kDADiskDescriptionDeviceRevisionKey   /* ( CFString     ) */ API_AVAILABLE(macos(10.4));
extern const CFStringRef kDADiskDescriptionDeviceUnitKey       /* ( CFNumber     ) */ API_AVAILABLE(macos(10.4));
extern const CFStringRef kDADiskDescriptionDeviceVendorKey     /* ( CFString     ) */ API_AVAILABLE(macos(10.4));
extern const CFStringRef kDADiskDescriptionDeviceTDMLockedKey  /* ( CFBoolean    ) */ API_AVAILABLE(macos(10.14.4));

extern const CFStringRef kDADiskDescriptionBusNameKey          /* ( CFString     ) */  API_AVAILABLE(macos(10.4));
extern const CFStringRef kDADiskDescriptionBusPathKey          /* ( CFString     ) */  API_AVAILABLE(macos(10.4));

extern const CFStringRef kDADiskDescriptionFSKitPrefix         /* -- Key Prefix -- */  API_AVAILABLE(macos(14.4));

extern const CFStringRef kDADiskDescriptionRepairRunningKey               /* ( CFBoolean    ) */  API_AVAILABLE(macos(26.0));

#ifndef __DISKARBITRATIOND__

/*!
 * @typedef    DADiskRef
 * Type of a reference to DADisk instances.
 */

typedef struct CF_BRIDGED_TYPE( id ) __DADisk * DADiskRef;

/*!
 * @function   DADiskGetTypeID
 * @abstract   Returns the type identifier of all DADisk instances.
 */

extern CFTypeID DADiskGetTypeID( void ) API_AVAILABLE(macos(10.4));

/*!
 * @function   DADiskCreateFromBSDName
 * @abstract   Creates a new disk object.
 * @param      allocator The allocator object to be used to allocate memory.
 * @param      session   The DASession in which to contact Disk Arbitration.
 * @param      name      The BSD device name.
 * @result     A reference to a new DADisk.
 * @discussion
 * The caller of this function receives a reference to the returned object.  The
 * caller also implicitly retains the object and is responsible for releasing it
 * with CFRelease().
 */

extern DADiskRef __nullable DADiskCreateFromBSDName( CFAllocatorRef __nullable allocator, DASessionRef session, const char * name ) API_AVAILABLE(macos(10.4));

/*!
 * @function   DADiskCreateFromIOMedia
 * @abstract   Creates a new disk object.
 * @param      allocator The allocator object to be used to allocate memory.
 * @param      session   The DASession in which to contact Disk Arbitration.
 * @param      media     The I/O Kit media object.
 * @result     A reference to a new DADisk.
 * @discussion
 * The caller of this function receives a reference to the returned object.  The
 * caller also implicitly retains the object and is responsible for releasing it
 * with CFRelease().
 */

extern DADiskRef __nullable DADiskCreateFromIOMedia( CFAllocatorRef __nullable allocator, DASessionRef session, io_service_t media ) API_AVAILABLE(macos(10.4));

/*!
 * @function   DADiskCreateFromVolumePath
 * @abstract   Creates a new disk object.
 * @param      allocator The allocator object to be used to allocate memory.
 * @param      session   The DASession in which to contact Disk Arbitration.
 * @param      path      The BSD mount point.
 * @result     A reference to a new DADisk.
 * @discussion
 * The caller of this function receives a reference to the returned object.  The
 * caller also implicitly retains the object and is responsible for releasing it
 * with CFRelease().
 */

extern DADiskRef __nullable DADiskCreateFromVolumePath( CFAllocatorRef __nullable allocator, DASessionRef session, CFURLRef path ) API_AVAILABLE(macos(10.7));

/*!
 * @function   DADiskGetBSDName
 * @abstract   Obtains the BSD device name for the specified disk.
 * @param      disk The DADisk for which to obtain the BSD device name.
 * @result     The disk's BSD device name.
 * @discussion
 * The BSD device name can be used with opendev() to open the BSD device.
 */

extern const char * __nullable DADiskGetBSDName( DADiskRef disk ) API_AVAILABLE(macos(10.4));

/*!
 * @function   DADiskCopyIOMedia
 * @abstract   Obtains the I/O Kit media object for the specified disk.
 * @param      disk The DADisk for which to obtain the I/O Kit media object.
 * @result     The disk's I/O Kit media object.
 * @discussion
 * The caller of this function receives a reference to the returned object.  The
 * caller also implicitly retains the object and is responsible for releasing it
 * with IOObjectRelease().
 */

extern io_service_t DADiskCopyIOMedia( DADiskRef disk ) API_AVAILABLE(macos(10.4));

/*!
 * @function   DADiskCopyDescription
 * @abstract   Obtains the Disk Arbitration description of the specified disk.
 * @param      disk The DADisk for which to obtain the Disk Arbitration description.
 * @result     The disk's Disk Arbitration description.
 * @discussion
 * This function will contact Disk Arbitration to acquire the latest description
 * of the specified disk, unless this function is called on a disk object passed
 * within the context of a registered callback, in which case the description is
 * current as of that callback event.
 *
 * The caller of this function receives a reference to the returned object.  The
 * caller also implicitly retains the object and is responsible for releasing it
 * with CFRelease().
 */

extern CFDictionaryRef __nullable DADiskCopyDescription( DADiskRef disk ) API_AVAILABLE(macos(10.4));

/*!
 * @function   DADiskCopyWholeDisk
 * @abstract   Obtain the associated whole disk object for the specified disk.
 * @param      disk The disk object.
 * @result     The disk's associated whole disk object.
 * @discussion
 * The caller of this function receives a reference to the returned object.  The
 * caller also implicitly retains the object and is responsible for releasing it
 * with CFRelease().
 */

extern DADiskRef __nullable DADiskCopyWholeDisk( DADiskRef disk ) API_AVAILABLE(macos(10.4));

#endif /* !__DISKARBITRATIOND__ */

CF_IMPLICIT_BRIDGING_DISABLED
CF_ASSUME_NONNULL_END

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !__DISKARBITRATION_DADISK__ */
