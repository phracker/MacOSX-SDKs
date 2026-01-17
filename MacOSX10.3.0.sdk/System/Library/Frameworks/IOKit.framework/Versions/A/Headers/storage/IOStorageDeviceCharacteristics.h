/*
 * Copyright (c) 1998-2001 Apple Computer, Inc. All rights reserved.
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

#ifndef _IOKIT_IO_STORAGE_DEVICE_CHARACTERISTICS_H_
#define _IOKIT_IO_STORAGE_DEVICE_CHARACTERISTICS_H_

#include <IOKit/storage/IOStorageProtocolCharacteristics.h>

//
//	Device Characteristics - Characteristics defined for devices.
//

/*!
@defined kIOPropertyDeviceCharacteristicsKey
@discussion This key is used to define Device Characteristics for a particular
device and it has an associated dictionary which lists the
device characteristics. The device characteristics are Command Set specific
and are listed in the header files for each command set.

Requirement: Mandatory

Example:
<pre>
@textblock
<dict>
	<key>Device Characteristics</key>
	<dict>
		<key>Vendor Name</key>
		<string>Apple</string>
		<key>Product Name</key>
		<string>iPod</string>
		<key>Product Revision Level</key>
		<string>1.0</string>
	</dict>
</dict>
@/textblock
</pre>
*/
#define kIOPropertyDeviceCharacteristicsKey			"Device Characteristics"


/*!
@defined kIOPropertyVendorNameKey
@discussion This key is used to define the Vendor Name for a particular device
and it has an associated string.

Requirement: Mandatory

Example:
<pre>
@textblock
<dict>
	<key>Device Characteristics</key>
	<dict>
		<key>Vendor Name</key>
		<string>Apple</string>
		<key>Product Name</key>
		<string>iPod</string>
		<key>Product Revision Level</key>
		<string>1.0</string>
	</dict>
</dict>
@/textblock
</pre>
*/
#define kIOPropertyVendorNameKey					"Vendor Name"


/*!
@defined kIOPropertyProductNameKey
@discussion This key is used to define the Product Name for a particular device
and it has an associated string.

Requirement: Mandatory

Example:
<pre>
@textblock
<dict>
	<key>Device Characteristics</key>
	<dict>
		<key>Vendor Name</key>
		<string>Apple</string>
		<key>Product Name</key>
		<string>iPod</string>
		<key>Product Revision Level</key>
		<string>1.0</string>
	</dict>
</dict>
@/textblock
</pre>
*/
#define kIOPropertyProductNameKey					"Product Name"


/*!
@defined kIOPropertyProductRevisionLevelKey
@discussion This key is used to define the Product Revision Level for a
particular device and it has an associated string.

Requirement: Mandatory

Example:
<pre>
@textblock
<dict>
	<key>Device Characteristics</key>
	<dict>
		<key>Vendor Name</key>
		<string>Apple</string>
		<key>Product Name</key>
		<string>iPod</string>
		<key>Product Revision Level</key>
		<string>1.0</string>
	</dict>
</dict>
@/textblock
</pre>
*/
#define kIOPropertyProductRevisionLevelKey			"Product Revision Level"


#endif	/* _IOKIT_IO_STORAGE_DEVICE_CHARACTERISTICS_H_ */