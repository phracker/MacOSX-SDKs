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
 * @header IOPartitionScheme
 * @abstract
 * This header contains the IOPartitionScheme class definition.
 */

#ifndef _IOPARTITIONSCHEME_H
#define _IOPARTITIONSCHEME_H

/*!
 * @defined kIOPartitionSchemeClass
 * @abstract
 * kIOPartitionSchemeClass is the name of the IOPartitionScheme class.
 * @discussion
 * kIOPartitionSchemeClass is the name of the IOPartitionScheme class.
 */

#define kIOPartitionSchemeClass "IOPartitionScheme"

/*!
 * @defined kIOMediaPartitionIDKey
 * @abstract
 * kIOMediaPartitionIDKey is property of IOMedia objects.  It has an OSNumber
 * value.
 * @discussion
 * The kIOMediaPartitionIDKey property is placed into each IOMedia instance
 * created via the partition scheme.  It is an ID that differentiates one 
 * partition from the other (within a given scheme).  It is typically an index
 * into the on-disk partition table.
 */

#define kIOMediaPartitionIDKey "Partition ID"
#define kIOMediaPartitionID "Partition ID" ///d:deprecated

#endif /* !_IOPARTITIONSCHEME_H */
