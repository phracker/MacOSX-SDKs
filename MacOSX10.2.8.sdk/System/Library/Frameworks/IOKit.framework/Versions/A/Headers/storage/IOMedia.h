/*
 * Copyright (c) 1998-2000 Apple Computer, Inc. All rights reserved.
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

/*!
 * @header IOMedia
 * @abstract
 * This header contains the IOMedia class definition.
 */

#ifndef _IOMEDIA_H
#define _IOMEDIA_H

#include <IOKit/IOTypes.h>

/*!
 * @defined kIOMediaClass
 * @abstract
 * kIOMediaClass is the name of the IOMedia class.
 * @discussion
 * kIOMediaClass is the name of the IOMedia class.
 */

#define kIOMediaClass "IOMedia"

/*!
 * @defined kIOMediaContentKey
 * @abstract
 * kIOMediaContentKey is a property of IOMedia objects.  It has an OSString
 * value.
 * @discussion
 * The kIOMediaContentKey property contains a description of the media's
 * contents.  The description is the same as the hint at the time of the
 * object's creation, but it is possible that the description be overrided
 * by a client (which has probed the media and identified the content correctly)
 * of the media object.  It is more accurate than the hint for this reason.  The
 * string is formed in the likeness of Apple's "Apple_HFS" strings.
 */

#define kIOMediaContentKey "Content"
#define kIOMediaContent "Content" ///d:deprecated

/*!
 * @defined kIOMediaContentHintKey
 * @abstract
 * kIOMediaContentHintKey is a property of IOMedia objects.  It has an OSString
 * value.
 * @discussion
 * The kIOMediaContentHintKey property contains a hint of the media's contents.
 * The hint is set at the time of the object's creation, should the creator have
 * a clue as to what it may contain.  The hint string does not change for the
 * lifetime of the object and is formed in the likeness of Apple's "Apple_HFS"
 * strings.
 */

#define kIOMediaContentHintKey "Content Hint"

/*!
 * @defined kIOMediaEjectableKey
 * @abstract
 * kIOMediaEjectableKey is a property of IOMedia objects.  It has an OSBoolean
 * value.
 * @discussion
 * The kIOMediaEjectableKey property describes whether the media is ejectable
 * from the drive mechanism under software control.  Implies IOMediaRemovable
 * is also true.
 */

#define kIOMediaEjectableKey "Ejectable"
#define kIOMediaEjectable "Ejectable" ///d:deprecated

/*!
 * @defined kIOMediaLeafKey
 * @abstract
 * kIOMediaLeafKey is a property of IOMedia objects.  It has an OSBoolean value.
 * @discussion
 * The kIOMediaLeafKey property describes whether the media is a leaf, that is,
 * it is the deepest media object in this branch of the I/O Kit registry.
 */

#define kIOMediaLeafKey "Leaf"
#define kIOMediaLeaf "Leaf" ///d:deprecated

/*!
 * @defined kIOMediaPreferredBlockSizeKey
 * @abstract
 * kIOMediaPreferredBlockSizeKey is a property of IOMedia objects.  It has an
 * OSNumber value.
 * @discussion
 * The kIOMediaPreferredBlockSizeKey property describes the media's natural
 * block size in bytes.  This information is useful to clients that want to
 * optimize access to the media.
 */

#define kIOMediaPreferredBlockSizeKey "Preferred Block Size"

/*!
 * @defined kIOMediaRemovableKey
 * @abstract
 * kIOMediaRemovableKey is a property of IOMedia objects.  It has an OSBoolean
 * value.
 * @discussion
 * The kIOMediaRemovableKey property describes whether the media is removable
 * from the drive mechanism.
 */

#define kIOMediaRemovableKey "Removable"

/*!
 * @defined kIOMediaSizeKey
 * @abstract
 * kIOMediaSizeKey is a property of IOMedia objects.  It has an OSNumber value.
 * @discussion
 * The kIOMediaSizeKey property describes the total length of the media in
 * bytes.
 */

#define kIOMediaSizeKey "Size"
#define kIOMediaSize "Size" ///d:deprecated

/*!
 * @defined kIOMediaWholeKey
 * @abstract
 * kIOMediaWholeKey is a property of IOMedia objects.  It has an OSBoolean
 * value.
 * @discussion
 * The kIOMediaWholeKey property describes whether the media is whole, that is,
 * it represents the whole disk (the physical disk, or a virtual replica
 * thereof).
 */

#define kIOMediaWholeKey "Whole"

/*!
 * @defined kIOMediaWritableKey
 * @abstract
 * kIOMediaWritableKey is a property of IOMedia objects.  It has an OSBoolean
 * value.
 * @discussion
 * The kIOMediaWritableKey property describes whether the media is writable.
 */

#define kIOMediaWritableKey "Writable"
#define kIOMediaWritable "Writable" ///d:deprecated

/*!
 * @defined kIOMediaContentMaskKey
 * @abstract
 * kIOMediaContentMaskKey is a property of IOMedia clients.  It has an OSString
 * value.
 * @discussion
 * The kIOMediaContentMaskKey property must exist in all IOMedia clients that
 * drive new content (that is, produce new media objects).  When the client
 * matches against the provider media, the value of the client's
 * kIOMediaContentMaskKey property is used to replace the provider's
 * kIOMediaContentKey property.
 */

#define kIOMediaContentMaskKey "Content Mask"

/*!
 * @defined kIOMediaIconKey
 * @abstract
 * kIOMediaIconKey is a property of any object in the media stack.  It has an
 * OSDictionary value, with properties identical to the kIOIconKey definition.
 * @discussion
 * kIOMediaIconKey is a property of any object in the media stack that wishes
 * to override the default icon shown for the media objects in the stack.  It
 * is usually defined in a provider object below the media object.  It has an
 * OSDictionary value, with properties identical to the kIOIconKey definition,
 * that is, kCFBundleIdentifierKey and kIOBundleResourceFileKey.
 */

#define kIOMediaIconKey "IOMediaIcon"

/*!
 * @enum IOMediaAttributeMask
 * @discussion
 * The IOMediaAttributeMask bit mask describes various attributes of
 * the media object, such as its ejectability and its removability.
 * @constant kIOMediaAttributeEjectableMask
 * Indicates whether the media is ejectable from the drive mechanism
 * under software control.  Implies kIOMediaAttributeRemovableMask.
 * @constant kIOMediaAttributeRemovableMask
 * Indicates whether the media is removable from the drive mechanism.
 */

typedef UInt32 IOMediaAttributeMask;

#define kIOMediaAttributeEjectableMask 0x00000001UL
#define kIOMediaAttributeRemovableMask 0x00000002UL
#define kIOMediaAttributeReservedMask  0xFFFFFFFCUL

#endif /* !_IOMEDIA_H */
