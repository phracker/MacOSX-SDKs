/*
 * Copyright (c) 1998-2009 Apple Inc. All rights reserved.
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

#ifndef _IOKIT_IO_STORAGE_PROTOCOL_CHARACTERISTICS_H_
#define _IOKIT_IO_STORAGE_PROTOCOL_CHARACTERISTICS_H_


/*
 *	Protocol Characteristics - Characteristics defined for protocols.
 */


/*!
@defined kIOPropertyProtocolCharacteristicsKey
@discussion This key is used to define Protocol Characteristics for a particular
protocol and it has an associated dictionary which lists the
protocol characteristics.

Requirement: Mandatory

Example:
<pre>
@textblock
<dict>
	<key>Protocol Characteristics</key>
	<dict>
		<key>Physical Interconnect</key>
		<string>ATAPI</string>
		<key>Physical Interconnect Location</key>
		<string>Internal</string>
	</dict>
</dict>
@/textblock
</pre>
*/
#define	kIOPropertyProtocolCharacteristicsKey		"Protocol Characteristics"


/*!
@defined kIOPropertySCSIInitiatorIdentifierKey
@discussion An identifier that will uniquely identify this SCSI Initiator for the
SCSI Domain.

Requirement: Mandatory for SCSI Parallel Interface, SAS,
and Fibre Channel Interface.

Example:
<pre>
@textblock
<dict>
	<key>Protocol Characteristics</key>
	<dict>
		<key>Physical Interconnect</key>
		<string>SCSI Parallel Interface</string>
		<key>Physical Interconnect Location</key>
		<string>Internal</string>
		<key>SCSI Initiator Identifier</key>
		<integer>7</integer>
	</dict>
</dict>
@/textblock
</pre>
*/
#define kIOPropertySCSIInitiatorIdentifierKey		"SCSI Initiator Identifier"


/*!
@defined kIOPropertySCSIDomainIdentifierKey
@discussion An identifier that will uniquely identify this SCSI Domain for the
Physical Interconnect type. This identifier is only guaranteed to be unique for
any given Physical Interconnect and is not guaranteed to be the same across
restarts or shutdowns.

Requirement: Mandatory for SCSI Parallel Interface and Fibre Channel Interface.

Example:
<pre>
@textblock
<dict>
	<key>Protocol Characteristics</key>
	<dict>
		<key>Physical Interconnect</key>
		<string>SCSI Parallel Interface</string>
		<key>Physical Interconnect Location</key>
		<string>Internal</string>
		<key>SCSI Domain Identifier</key>
		<integer>0</integer>
	</dict>
</dict>
@/textblock
</pre>
*/
#define kIOPropertySCSIDomainIdentifierKey			"SCSI Domain Identifier"


/*!
@defined kIOPropertySCSITargetIdentifierKey
@discussion This is the SCSI Target Identifier for a given SCSI Target Device.

Requirement: Mandatory for SCSI Parallel Interface and Fibre Channel Interface.

Example:
<pre>
@textblock
<dict>
	<key>Protocol Characteristics</key>
	<dict>
		<key>Physical Interconnect</key>
		<string>SCSI Parallel Interface</string>
		<key>Physical Interconnect Location</key>
		<string>Internal</string>
		<key>SCSI Target Identifier</key>
		<integer>3</integer>
	</dict>
</dict>
@/textblock
</pre>
*/
#define kIOPropertySCSITargetIdentifierKey			"SCSI Target Identifier"


/*!
@defined kIOPropertySCSILogicalUnitNumberKey
@discussion This key is the SCSI Logical Unit Number for the device server
controlled by the driver.

Requirement: Mandatory for SCSI Parallel Interface, SAS, and Fibre Channel Interface.

Example:
<pre>
@textblock
<dict>
	<key>Protocol Characteristics</key>
	<dict>
		<key>Physical Interconnect</key>
		<string>SCSI Parallel Interface</string>
		<key>Physical Interconnect Location</key>
		<string>Internal</string>
		<key>SCSI Logical Unit Number</key>
		<integer>2</integer>
	</dict>
</dict>
@/textblock
</pre>
*/
#define kIOPropertySCSILogicalUnitNumberKey			"SCSI Logical Unit Number"


/*!
@defined kIOPropertySASAddressKey
@discussion This key is the unique 64-bit SAS Address for the device server
node located at this port, or for the initiating host port.

Requirement: Mandatory for SAS.

Example:
<pre>
@textblock
<dict>
	<key>Protocol Characteristics</key>
	<dict>
		<key>Physical Interconnect</key>
		<string>SAS</string>
		<key>Physical Interconnect Location</key>
		<string>External</string>
		<key>SAS Address</key>
		<data>0011223344556677</data>
	</dict>
</dict>
@/textblock
</pre>

Example2:
<pre>
@textblock
<dict>
	<key>Controller Characteristics</key>
	<dict>
		<key>SAS Address</key>
		<data>0011223344556677</data>
	</dict>
</dict>
@/textblock
</pre>
*/
#define kIOPropertySASAddressKey					"SAS Address"


/*!
@defined kIOPropertyFibreChannelNodeWorldWideNameKey
@discussion This key is the unique 64-bit World Wide Name for the device server
node located at this port, or for the initiating host port.

Requirement: Mandatory for Fibre Channel Interface.

Example:
<pre>
@textblock
<dict>
	<key>Protocol Characteristics</key>
	<dict>
		<key>Physical Interconnect</key>
		<string>Fibre Channel Interface</string>
		<key>Physical Interconnect Location</key>
		<string>External</string>
		<key>Node World Wide Name</key>
		<data>0011223344556677</data>
	</dict>
</dict>
@/textblock
</pre>

Example2:
<pre>
@textblock
<dict>
	<key>Controller Characteristics</key>
	<dict>
		<key>Node World Wide Name</key>
		<data>0011223344556677</data>
	</dict>
</dict>
@/textblock
</pre>
*/
#define kIOPropertyFibreChannelNodeWorldWideNameKey		"Node World Wide Name"


/*!
@defined kIOPropertyFibreChannelPortWorldWideNameKey
@discussion This key is the unique 64-bit World Wide Name for the port.

Requirement: Mandatory for Fibre Channel Interface.

Example:
<pre>
@textblock
<dict>
	<key>Protocol Characteristics</key>
	<dict>
		<key>Physical Interconnect</key>
		<string>Fibre Channel Interface</string>
		<key>Physical Interconnect Location</key>
		<string>External</string>
		<key>Port World Wide Name</key>
		<data>0011223344556677</data>
	</dict>
</dict>
@/textblock
</pre>

Example2:
<pre>
@textblock
<dict>
	<key>Controller Characteristics</key>
	<dict>
		<key>Port World Wide Name</key>
		<data>0011223344556677</data>
	</dict>
</dict>
@/textblock
</pre>
*/
#define kIOPropertyFibreChannelPortWorldWideNameKey		"Port World Wide Name"


/*!
@defined kIOPropertyFibreChannelAddressIdentifierKey
@discussion This key is the 24-bit Address Identifier (S_ID or D_ID) as
defined in the FC-FS specification. It contains the address identifier
of the source or destination Nx_Port.

Note: This value can change. It is not a static value.

Requirement: Optional (only necessary for Fibre Channel Interface).

Example:
<pre>
@textblock
<dict>
	<key>Protocol Characteristics</key>
	<dict>
		<key>Physical Interconnect</key>
		<string>Fibre Channel Interface</string>
		<key>Physical Interconnect Location</key>
		<string>External</string>
		<key>Address Identifier</key>
		<data>001122</data>
	</dict>
</dict>
@/textblock
</pre>

Example2:
<pre>
@textblock
<dict>
	<key>Controller Characteristics</key>
	<dict>
		<key>Address Identifier</key>
		<data>001122</data>
	</dict>
</dict>
@/textblock
</pre>
*/
#define kIOPropertyFibreChannelAddressIdentifierKey		"Address Identifier"


/*!
@defined kIOPropertyFibreChannelALPAKey
@discussion This key is the 8-bit Arbitrated Loop Physical Address
(AL_PA) value as defined in the FC-AL-2 specification.

Note: This value can change. It is not a static value.

Requirement: Optional (only necessary for Fibre Channel Interface).

Example:
<pre>
@textblock
<dict>
	<key>Protocol Characteristics</key>
	<dict>
		<key>Physical Interconnect</key>
		<string>Fibre Channel Interface</string>
		<key>Physical Interconnect Location</key>
		<string>External</string>
		<key>AL_PA</key>
		<data>04</data>
	</dict>
</dict>
@/textblock
</pre>

Example2:
<pre>
@textblock
<dict>
	<key>Controller Characteristics</key>
	<dict>
		<key>AL_PA</key>
		<data>04</data>
	</dict>
</dict>
@/textblock
</pre>
*/
#define kIOPropertyFibreChannelALPAKey					"AL_PA"


/*!
@defined kIOPropertyPortStatusKey
@discussion This key is associated with the current port
status of the physical link. The port status is either
"Link Established", "No Link Established", or "Link Failed".

Note: This value can change when the port status changes. It
is not a static value.

Requirement: Optional for any interconnect.

Example:
<pre>
@textblock
<dict>
	<key>Controller Characteristics</key>
	<dict>
		<key>Port Status</key>
		<string>Link Established</string>
	</dict>
</dict>
@/textblock
</pre>
*/
#define kIOPropertyPortStatusKey						"Port Status"


/*!
@defined kIOPropertyPortSpeedKey
@discussion This key is associated with the current port
speed. The port speed can be any valid speed for the interconnect.

Note: This value can change. It is not a static value.

Requirement: Optional for any interconnect.

Example:
<pre>
@textblock
<dict>
	<key>Controller Characteristics</key>
	<dict>
		<key>Port Speed</key>
		<string>Automatic (1 Gigabit)</string>
	</dict>
</dict>
@/textblock
</pre>
*/
#define kIOPropertyPortSpeedKey							"Port Speed"


/*!
@defined kIOPropertyPortTopologyKey
@discussion This key is associated with the current port
topology. The port topology can be any valid topology for the interconnect.

Note: This value can change. It is not a static value.

Requirement: Optional for any interconnect.

Example:
<pre>
@textblock
<dict>
	<key>Controller Characteristics</key>
	<dict>
		<key>Port Topology</key>
		<string>Automatic (N_Port)</string>
	</dict>
</dict>
@/textblock
</pre>
*/
#define kIOPropertyPortTopologyKey						"Port Topology"


/*!
@defined kIOPropertyPortDescriptionKey
@discussion This key is associated with an human
readable port description. Examples include
"Channel A", "Port 1", etc.

Requirement: Optional for all interconnects.

Example:
<pre>
@textblock
<dict>
	<key>Controller Characteristics</key>
	<dict>
		<key>Port Description</key>
		<string>Channel A</string>
	</dict>
</dict>
@/textblock
</pre>
*/
#define kIOPropertyPortDescriptionKey					"Port Description"


/*!
@defined kIOPropertySCSIParallelSignalingTypeKey
@discussion This key is associated with the signaling type
used for this SCSI Parallel bus. Valid values include
"High Voltage Differential", "Low Voltage Differential",
and "Single Ended".

Requirement: Optional for SCSI Parallel Interface. Not
defined for any other physical interconnect.

Example:
<pre>
@textblock
<dict>
	<key>Controller Characteristics</key>
	<dict>
		<key>SCSI Parallel Signaling Type</key>
		<string>High Voltage Differential</string>
	</dict>
</dict>
@/textblock
</pre>
*/
#define kIOPropertySCSIParallelSignalingTypeKey			"SCSI Parallel Signaling Type"


/*!
@defined kIOPropertyFibreChannelCableDescriptionKey
@discussion This key is associated with the cabling type
used for this Fibre Channel port. Valid values include
"Copper" and "Fiber Optic".

Requirement: Optional for Fibre Channel Interface. Not
defined for any other physical interconnect.

Example:
<pre>
@textblock
<dict>
	<key>Controller Characteristics</key>
	<dict>
		<key>Fibre Channel Cabling Type</key>
		<string>Copper</string>
	</dict>
</dict>
@/textblock
</pre>
*/
#define kIOPropertyFibreChannelCableDescriptionKey		"Fibre Channel Cabling Type"


/*!
@defined kIOPropertyPhysicalInterconnectTypeKey
@discussion This key is used to define the Physical Interconnect to which
a device is attached.

Requirement: Mandatory.

Example:
<pre>
@textblock
<dict>
	<key>Protocol Characteristics</key>
	<dict>
		<key>Physical Interconnect</key>
		<string>SCSI Parallel Interface</string>
		<key>Physical Interconnect Location</key>
		<string>Internal</string>
	</dict>
</dict>
@/textblock
</pre>
*/
#define kIOPropertyPhysicalInterconnectTypeKey		"Physical Interconnect"


/*!
@defined kIOPropertyPhysicalInterconnectLocationKey
@discussion This key is used to define the Physical Interconnect
Location.

Requirement: Mandatory.

Example:
<pre>
@textblock
<dict>
	<key>Protocol Characteristics</key>
	<dict>
		<key>Physical Interconnect</key>
		<string>SCSI Parallel Interface</string>
		<key>Physical Interconnect Location</key>
		<string>Internal</string>
	</dict>
</dict>
@/textblock
</pre>
*/
#define kIOPropertyPhysicalInterconnectLocationKey	"Physical Interconnect Location"


/*!
@defined kIOPropertySCSIProtocolMultiInitKey
@discussion This protocol characteristics key is used to inform the system
that the protocol supports having multiple devices that act as initiators.

Requirement: Optional.

Example:
<pre>
@textblock
<dict>
	<key>Protocol Characteristics</key>
	<dict>
		<key>Physical Interconnect</key>
		<string>Fibre Channel Interface</string>
		<key>Physical Interconnect Location</key>
		<string>External</string>
		<key>Multiple Initiators</key>
		<string>True</string>
	</dict>
</dict>
@/textblock
</pre>
*/
#define kIOPropertySCSIProtocolMultiInitKey			"Multiple Initiators"


/*
 *	Values - Values for the characteristics defined above.
 */


/*!
@defined kIOPropertyInternalKey
@discussion This key defines the value of Internal for the key
kIOPropertyPhysicalInterconnectLocationKey. If the device is
connected to an internal bus, this key should be set.

Example:
<pre>
@textblock
<dict>
	<key>Protocol Characteristics</key>
	<dict>
		<key>Physical Interconnect</key>
		<string>ATA</string>
		<key>Physical Interconnect Location</key>
		<string>Internal</string>
	</dict>
</dict>
@/textblock
</pre>
*/
#define kIOPropertyInternalKey						"Internal"


/*!
@defined kIOPropertyExternalKey
@discussion This key defines the value of External for the key
kIOPropertyPhysicalInterconnectLocationKey. If the device is
connected to an external bus, this key should be set.

Example:
<pre>
@textblock
<dict>
	<key>Protocol Characteristics</key>
	<dict>
		<key>Physical Interconnect</key>
		<string>Fibre Channel Interface</string>
		<key>Physical Interconnect Location</key>
		<string>External</string>
	</dict>
</dict>
@/textblock
</pre>
*/
#define kIOPropertyExternalKey						"External"


/*!
@defined kIOPropertyInternalExternalKey
@discussion This key defines the value of Internal/External for the key
kIOPropertyPhysicalInterconnectLocationKey. If the device is connected
to a bus and it is indeterminate whether it is internal or external,
this key should be set.

Example:
<pre>
@textblock
<dict>
	<key>Protocol Characteristics</key>
	<dict>
		<key>Physical Interconnect</key>
		<string>SCSI Parallel Interface</string>
		<key>Physical Interconnect Location</key>
		<string>Internal/External</string>
	</dict>
</dict>
@/textblock
</pre>
*/
#define kIOPropertyInternalExternalKey				"Internal/External"


/*!
@defined kIOPropertyInterconnectFileKey
@discussion This key defines the value of File for the key
kIOPropertyPhysicalInterconnectLocationKey. If the device is a file
that is being represented as a storage device, this key should be set.

NOTE: This key should only be used when the Physical Interconnect is set to
Virtual Interface.

Example:
<pre>
@textblock
<dict>
	<key>Protocol Characteristics</key>
	<dict>
		<key>Physical Interconnect</key>
		<string>Virtual Interface</string>
		<key>Physical Interconnect Location</key>
		<string>File</string>
	</dict>
</dict>
@/textblock
</pre>
*/
#define kIOPropertyInterconnectFileKey						"File"


/*!
@defined kIOPropertyInterconnectRAMKey
@discussion This key defines the value of RAM for the key
kIOPropertyPhysicalInterconnectLocationKey. If the device is system memory
that is being represented as a storage device, this key should be set.

NOTE: This key should only be used when the Physical Interconnect is set to
Virtual Interface.

Example:
<pre>
@textblock
<dict>
	<key>Protocol Characteristics</key>
	<dict>
		<key>Physical Interconnect</key>
		<string>Virtual Interface</string>
		<key>Physical Interconnect Location</key>
		<string>RAM</string>
	</dict>
</dict>
@/textblock
</pre>
*/
#define kIOPropertyInterconnectRAMKey						"RAM"


/*!
@defined kIOPropertyPhysicalInterconnectTypeATA
@discussion This key defines the value of ATA for the key
kIOPropertyPhysicalInterconnectTypeKey. If the device is connected
to an ATA bus, this key should be set.

Example:
<pre>
@textblock
<dict>
	<key>Protocol Characteristics</key>
	<dict>
		<key>Physical Interconnect</key>
		<string>ATA</string>
		<key>Physical Interconnect Location</key>
		<string>Internal</string>
	</dict>
</dict>
@/textblock
</pre>
*/
#define kIOPropertyPhysicalInterconnectTypeATA				"ATA"


/*!
@defined kIOPropertyPhysicalInterconnectTypeSerialATA
@discussion This key defines the value of SATA for the key
kIOPropertyPhysicalInterconnectTypeKey. If the device is connected
to a SATA bus, this key should be set.

Example:
<pre>
@textblock
<dict>
	<key>Protocol Characteristics</key>
	<dict>
		<key>Physical Interconnect</key>
		<string>SATA</string>
		<key>Physical Interconnect Location</key>
		<string>Internal</string>
	</dict>
</dict>
@/textblock
</pre>
*/
#define kIOPropertyPhysicalInterconnectTypeSerialATA		"SATA"


/*!
@defined kIOPropertyPhysicalInterconnectTypeSerialAttachedSCSI
@discussion This key defines the value of SAS for the key
kIOPropertyPhysicalInterconnectTypeKey. If the device is connected
to a SAS bus, this key should be set.

Example:
<pre>
@textblock
<dict>
	<key>Protocol Characteristics</key>
	<dict>
		<key>Physical Interconnect</key>
		<string>SAS</string>
		<key>Physical Interconnect Location</key>
		<string>External</string>
	</dict>
</dict>
@/textblock
</pre>
*/
#define kIOPropertyPhysicalInterconnectTypeSerialAttachedSCSI	"SAS"


/*!
@defined kIOPropertyPhysicalInterconnectTypeATAPI
@discussion This key defines the value of ATAPI for the key
kIOPropertyPhysicalInterconnectTypeKey. If the device is connected
to an ATA bus and follows the ATAPI command specification, this key
should be set.

Example:
<pre>
@textblock
<dict>
	<key>Protocol Characteristics</key>
	<dict>
		<key>Physical Interconnect</key>
		<string>ATAPI</string>
		<key>Physical Interconnect Location</key>
		<string>Internal</string>
	</dict>
</dict>
@/textblock
</pre>
*/
#define kIOPropertyPhysicalInterconnectTypeATAPI			"ATAPI"


/*!
@defined kIOPropertyPhysicalInterconnectTypeUSB
@discussion This key defines the value of USB for the key
kIOPropertyPhysicalInterconnectTypeKey. If the device is connected
to a USB port, this key should be set.

Example:
<pre>
@textblock
<dict>
	<key>Protocol Characteristics</key>
	<dict>
		<key>Physical Interconnect</key>
		<string>USB</string>
		<key>Physical Interconnect Location</key>
		<string>External</string>
	</dict>
</dict>
@/textblock
</pre>
*/
#define kIOPropertyPhysicalInterconnectTypeUSB				"USB"


/*!
@defined kIOPropertyPhysicalInterconnectTypeFireWire
@discussion This key defines the value of USB for the key
kIOPropertyPhysicalInterconnectTypeKey. If the device is connected
to a FireWire port, this key should be set.

Example:
<pre>
@textblock
<dict>
	<key>Protocol Characteristics</key>
	<dict>
		<key>Physical Interconnect</key>
		<string>FireWire</string>
		<key>Physical Interconnect Location</key>
		<string>External</string>
	</dict>
</dict>
@/textblock
</pre>
*/
#define kIOPropertyPhysicalInterconnectTypeFireWire			"FireWire"


/*!
 @defined kIOPropertyPhysicalInterconnectTypeSecureDigital
 @discussion This key defines the value of Secure Digital for the key
 kIOPropertyPhysicalInterconnectTypeSecureDigital. If the device is a
 connected to a Secure Digital port and follows the Secure Digital 
 specification, this key should be set. 
 
 Example:
 <pre>
 @textblock
 <dict>
    <key>Protocol Characteristics</key>
    <dict>
        <key>Physical Interconnect</key>
        <string>Secure Digital</string>
        <key>Physical Interconnect Location</key>
        <string>Internal</string>
    </dict>
 </dict>
 @/textblock
 </pre>
 */
#define kIOPropertyPhysicalInterconnectTypeSecureDigital	"Secure Digital"


/*!
@defined kIOPropertyPhysicalInterconnectTypeSCSIParallel
@discussion This key defines the value of SCSI Parallel Interface for the key
kIOPropertyPhysicalInterconnectTypeKey. If the device is connected
to a SCSI Parallel port, this key should be set.

Example:
<pre>
@textblock
<dict>
	<key>Protocol Characteristics</key>
	<dict>
		<key>Physical Interconnect</key>
		<string>SCSI Parallel Interface</string>
		<key>Physical Interconnect Location</key>
		<string>External</string>
	</dict>
</dict>
@/textblock
</pre>
*/
#define kIOPropertyPhysicalInterconnectTypeSCSIParallel		"SCSI Parallel Interface"


/*!
@defined kIOPropertyPhysicalInterconnectTypeFibreChannel
@discussion This key defines the value of Fibre Channel Interface for the key
kIOPropertyPhysicalInterconnectTypeKey. If the device is connected
to a Fibre Channel port, this key should be set.

Example:
<pre>
@textblock
<dict>
	<key>Protocol Characteristics</key>
	<dict>
		<key>Physical Interconnect</key>
		<string>Fibre Channel Interface</string>
		<key>Physical Interconnect Location</key>
		<string>External</string>
	</dict>
</dict>
@/textblock
</pre>
*/
#define kIOPropertyPhysicalInterconnectTypeFibreChannel		"Fibre Channel Interface"


/*!
@defined kIOPropertyPhysicalInterconnectTypeVirtual
@discussion This key defines the value of Virtual Interface for the key
kIOPropertyPhysicalInterconnectTypeVirtual. If the device is being made to look
like a storage device, but is not such in actuality, such as a File or RAM, this
key should be set.

Example:
<pre>
@textblock
<dict>
	<key>Protocol Characteristics</key>
	<dict>
		<key>Physical Interconnect</key>
		<string>Virtual Interface</string>
		<key>Physical Interconnect Location</key>
		<string>File</string>
	</dict>
</dict>
@/textblock
</pre>
*/
#define kIOPropertyPhysicalInterconnectTypeVirtual		"Virtual Interface"


/*!
@defined kIOPropertyPortStatusLinkEstablishedKey
@discussion This key defines the value of Link Established for the key
kIOPropertyPortStatusKey.

Example:
<pre>
@textblock
<dict>
	<key>Controller Characteristics</key>
	<dict>
		<key>Port Status</key>
		<string>Link Established</string>
	</dict>
</dict>
@/textblock
</pre>
*/
#define kIOPropertyPortStatusLinkEstablishedKey			"Link Established"


/*!
@defined kIOPropertyPortStatusNoLinkEstablishedKey
@discussion This key defines the value of No Link Established for the key
kIOPropertyPortStatusKey.

Example:
<pre>
@textblock
<dict>
	<key>Controller Characteristics</key>
	<dict>
		<key>Port Status</key>
		<string>No Link Established</string>
	</dict>
</dict>
@/textblock
</pre>
*/
#define kIOPropertyPortStatusNoLinkEstablishedKey		"No Link Established"


/*!
@defined kIOPropertyPortStatusLinkFailedKey
@discussion This key defines the value of Link Failed for the key
kIOPropertyPortStatusKey.

Example:
<pre>
@textblock
<dict>
	<key>Controller Characteristics</key>
	<dict>
		<key>Port Status</key>
		<string>Link Failed</string>
	</dict>
</dict>
@/textblock
</pre>
*/
#define kIOPropertyPortStatusLinkFailedKey				"Link Failed"


/*!
@defined kIOPropertyPortSpeedAutomaticKey
@discussion This key defines the value of Automatic for the key
kIOPropertyPortSpeedKey. If the speed of the port is automatically
adjusted by the host/device and a definitive speed is not known,
this key should be used.

Note: This value can change. It is not a static value.

Requirement: Optional for any interconnect.

Example:
<pre>
@textblock
<dict>
	<key>Controller Characteristics</key>
	<dict>
		<key>Port Speed</key>
		<string>Automatic</string>
	</dict>
</dict>
@/textblock
</pre>
*/
#define kIOPropertyPortSpeedAutomaticKey				"Automatic"


/*!
@defined kIOPropertyPortSpeed1GigabitKey
@discussion This key defines the value of 1 Gigabit for the key
kIOPropertyPortSpeedKey. If the speed of the port is 1 Gigabit
per second and is not automatically determined (i.e. the user
configured the port to be exactly this speed),
this key should be used.

Note: This value can change. It is not a static value.

Requirement: Optional for any interconnect.

Example:
<pre>
@textblock
<dict>
	<key>Controller Characteristics</key>
	<dict>
		<key>Port Speed</key>
		<string>1 Gigabit</string>
	</dict>
</dict>
@/textblock
</pre>
*/
#define kIOPropertyPortSpeed1GigabitKey					"1 Gigabit"

/*!
@defined kIOPropertyPortSpeed1_5GigabitKey
@discussion This key defines the value of 1.5 Gigabit for the key
kIOPropertyPortSpeedKey. If the speed of the port is 1.5 Gigabits
per second and is not automatically determined (i.e. the user
configured the port to be exactly this speed),
this key should be used.

Note: This value can change. It is not a static value.

Requirement: Optional for any interconnect.

Example:
<pre>
@textblock
<dict>
	<key>Controller Characteristics</key>
	<dict>
		<key>Port Speed</key>
		<string>1.5 Gigabit</string>
	</dict>
</dict>
@/textblock
</pre>
*/
#define kIOPropertyPortSpeed1_5GigabitKey				"1.5 Gigabit"


/*!
@defined kIOPropertyPortSpeed2GigabitKey
@discussion This key defines the value of 2 Gigabit for the key
kIOPropertyPortSpeedKey. If the speed of the port is 2 Gigabits
per second and is not automatically determined (i.e. the user
configured the port to be exactly this speed),
this key should be used.

Note: This value can change. It is not a static value.

Requirement: Optional for any interconnect.

Example:
<pre>
@textblock
<dict>
	<key>Controller Characteristics</key>
	<dict>
		<key>Port Speed</key>
		<string>2 Gigabit</string>
	</dict>
</dict>
@/textblock
</pre>
*/
#define kIOPropertyPortSpeed2GigabitKey					"2 Gigabit"


/*!
@defined kIOPropertyPortSpeed3GigabitKey
@discussion This key defines the value of 3 Gigabit for the key
kIOPropertyPortSpeedKey. If the speed of the port is 3 Gigabits
per second and is not automatically determined (i.e. the user
configured the port to be exactly this speed),
this key should be used.

Note: This value can change. It is not a static value.

Requirement: Optional for any interconnect.

Example:
<pre>
@textblock
<dict>
	<key>Controller Characteristics</key>
	<dict>
		<key>Port Speed</key>
		<string>3 Gigabit</string>
	</dict>
</dict>
@/textblock
</pre>
*/
#define kIOPropertyPortSpeed3GigabitKey					"3 Gigabit"


/*!
@defined kIOPropertyPortSpeed4GigabitKey
@discussion This key defines the value of 4 Gigabit for the key
kIOPropertyPortSpeedKey. If the speed of the port is 4 Gigabits
per second and is not automatically determined (i.e. the user
configured the port to be exactly this speed),
this key should be used.

Note: This value can change. It is not a static value.

Requirement: Optional for any interconnect.

Example:
<pre>
@textblock
<dict>
	<key>Controller Characteristics</key>
	<dict>
		<key>Port Speed</key>
		<string>4 Gigabit</string>
	</dict>
</dict>
@/textblock
</pre>
*/
#define kIOPropertyPortSpeed4GigabitKey					"4 Gigabit"

/*!
@defined kIOPropertyPortSpeed6GigabitKey
@discussion This key defines the value of 6 Gigabit for the key
kIOPropertyPortSpeedKey. If the speed of the port is 6 Gigabits
per second and is not automatically determined (i.e. the user
configured the port to be exactly this speed),
this key should be used.

Note: This value can change. It is not a static value.

Requirement: Optional for any interconnect.

Example:
<pre>
@textblock
<dict>
	<key>Controller Characteristics</key>
	<dict>
		<key>Port Speed</key>
		<string>6 Gigabit</string>
	</dict>
</dict>
@/textblock
</pre>
*/
#define kIOPropertyPortSpeed6GigabitKey					"6 Gigabit"


/*!
@defined kIOPropertyPortSpeed8GigabitKey
@discussion This key defines the value of 8 Gigabit for the key
kIOPropertyPortSpeedKey. If the speed of the port is 8 Gigabits
per second and is not automatically determined (i.e. the user
configured the port to be exactly this speed),
this key should be used.

Note: This value can change. It is not a static value.

Requirement: Optional for any interconnect.

Example:
<pre>
@textblock
<dict>
	<key>Controller Characteristics</key>
	<dict>
		<key>Port Speed</key>
		<string>8 Gigabit</string>
	</dict>
</dict>
@/textblock
</pre>
*/
#define kIOPropertyPortSpeed8GigabitKey					"8 Gigabit"


/*!
@defined kIOPropertyPortSpeed10GigabitKey
@discussion This key defines the value of 10 Gigabit for the key
kIOPropertyPortSpeedKey. If the speed of the port is 10 Gigabits
per second and is not automatically determined (i.e. the user
configured the port to be exactly this speed),
this key should be used.

Note: This value can change. It is not a static value.

Requirement: Optional for any interconnect.

Example:
<pre>
@textblock
<dict>
	<key>Controller Characteristics</key>
	<dict>
		<key>Port Speed</key>
		<string>10 Gigabit</string>
	</dict>
</dict>
@/textblock
</pre>
*/
#define kIOPropertyPortSpeed10GigabitKey				"10 Gigabit"


/*!
@defined kIOPropertyPortSpeedAutomatic1GigabitKey
@discussion This key defines the value of Automatic (1 Gigabit)
for the key kIOPropertyPortSpeedKey. If the speed of the port is
1 Gigabit per second and is automatically determined by host
software, this key should be used.

Note: This value can change. It is not a static value.

Requirement: Optional for any interconnect.

Example:
<pre>
@textblock
<dict>
	<key>Controller Characteristics</key>
	<dict>
		<key>Port Speed</key>
		<string>Automatic (1 Gigabit)</string>
	</dict>
</dict>
@/textblock
</pre>
*/
#define kIOPropertyPortSpeedAutomatic1GigabitKey		"Automatic (1 Gigabit)"


/*!
@defined kIOPropertyPortSpeedAutomatic1_5GigabitKey
@discussion This key defines the value of Automatic (1.5 Gigabit) for the key
kIOPropertyPortSpeedKey. If the speed of the port is
1.5 Gigabits per second and is automatically determined by host
software, this key should be used.

Note: This value can change. It is not a static value.

Requirement: Optional for any interconnect.

Example:
<pre>
@textblock
<dict>
	<key>Controller Characteristics</key>
	<dict>
		<key>Port Speed</key>
		<string>Automatic (1.5 Gigabit)</string>
	</dict>
</dict>
@/textblock
</pre>
*/
#define kIOPropertyPortSpeedAutomatic1_5GigabitKey		"Automatic (1.5 Gigabit)"


/*!
@defined kIOPropertyPortSpeedAutomatic2GigabitKey
@discussion This key defines the value of Automatic (2 Gigabit)
for the key kIOPropertyPortSpeedKey. If the speed of the port is
2 Gigabits per second and is automatically determined by host
software, this key should be used.

Note: This value can change. It is not a static value.

Requirement: Optional for any interconnect.

Example:
<pre>
@textblock
<dict>
	<key>Controller Characteristics</key>
	<dict>
		<key>Port Speed</key>
		<string>Automatic (2 Gigabit)</string>
	</dict>
</dict>
@/textblock
</pre>
*/
#define kIOPropertyPortSpeedAutomatic2GigabitKey		"Automatic (2 Gigabit)"


/*!
@defined kIOPropertyPortSpeedAutomatic3GigabitKey
@discussion This key defines the value of Automatic (3 Gigabit)
for the key kIOPropertyPortSpeedKey. If the speed of the port is
3 Gigabits per second and is automatically determined by host
software, this key should be used.

Note: This value can change. It is not a static value.

Requirement: Optional for any interconnect.

Example:
<pre>
@textblock
<dict>
	<key>Controller Characteristics</key>
	<dict>
		<key>Port Speed</key>
		<string>Automatic (3 Gigabit)</string>
	</dict>
</dict>
@/textblock
</pre>
*/
#define kIOPropertyPortSpeedAutomatic3GigabitKey		"Automatic (3 Gigabit)"


/*!
@defined kIOPropertyPortSpeedAutomatic4GigabitKey
@discussion This key defines the value of Automatic (4 Gigabit)
for the key kIOPropertyPortSpeedKey. If the speed of the port is
4 Gigabits per second and is automatically determined by host
software, this key should be used.

Note: This value can change. It is not a static value.

Requirement: Optional for any interconnect.

Example:
<pre>
@textblock
<dict>
	<key>Controller Characteristics</key>
	<dict>
		<key>Port Speed</key>
		<string>Automatic (4 Gigabit)</string>
	</dict>
</dict>
@/textblock
</pre>
*/
#define kIOPropertyPortSpeedAutomatic4GigabitKey		"Automatic (4 Gigabit)"


/*!
@defined kIOPropertyPortSpeedAutomatic6GigabitKey
@discussion This key defines the value of Automatic (6 Gigabit)
for the key kIOPropertyPortSpeedKey. If the speed of the port is
6 Gigabits per second and is automatically determined by host
software, this key should be used.

Note: This value can change. It is not a static value.

Requirement: Optional for any interconnect.

Example:
<pre>
@textblock
<dict>
	<key>Controller Characteristics</key>
	<dict>
		<key>Port Speed</key>
		<string>Automatic (6 Gigabit)</string>
	</dict>
</dict>
@/textblock
</pre>
*/
#define kIOPropertyPortSpeedAutomatic6GigabitKey		"Automatic (6 Gigabit)"


/*!
@defined kIOPropertyPortSpeedAutomatic8GigabitKey
@discussion This key defines the value of Automatic (8 Gigabit)
for the key kIOPropertyPortSpeedKey. If the speed of the port is
8 Gigabits per second and is automatically determined by host
software, this key should be used.

Note: This value can change. It is not a static value.

Requirement: Optional for any interconnect.

Example:
<pre>
@textblock
<dict>
	<key>Controller Characteristics</key>
	<dict>
		<key>Port Speed</key>
		<string>Automatic (8 Gigabit)</string>
	</dict>
</dict>
@/textblock
</pre>
*/
#define kIOPropertyPortSpeedAutomatic8GigabitKey		"Automatic (8 Gigabit)"


/*!
@defined kIOPropertyPortSpeedAutomatic10GigabitKey
@discussion This key defines the value of Automatic (10 Gigabit)
for the key kIOPropertyPortSpeedKey. If the speed of the port is
10 Gigabits per second and is automatically determined by host
software, this key should be used.

Note: This value can change. It is not a static value.

Requirement: Optional for any interconnect.

Example:
<pre>
@textblock
<dict>
	<key>Controller Characteristics</key>
	<dict>
		<key>Port Speed</key>
		<string>Automatic (10 Gigabit)</string>
	</dict>
</dict>
@/textblock
</pre>
*/
#define kIOPropertyPortSpeedAutomatic10GigabitKey		"Automatic (10 Gigabit)"


/*!
@defined kIOPropertyPortTopologyAutomaticKey
@discussion This key defines the value of Automatic for the key
kIOPropertyPortTopologyKey. If the topology of the port is automatically
adjusted by the host/device and a definitive topology is not known,
this key should be used.

Note: This value can change. It is not a static value.

Requirement: Optional for any interconnect.

Example:
<pre>
@textblock
<dict>
	<key>Controller Characteristics</key>
	<dict>
		<key>Port Topology</key>
		<string>Automatic</string>
	</dict>
</dict>
@/textblock
</pre>
*/
#define kIOPropertyPortTopologyAutomaticKey				"Automatic"


/*!
@defined kIOPropertyPortTopologyNPortKey
@discussion This key defines the value of N_Port for the key
kIOPropertyPortTopologyKey. If the topology of the port is an N_Port,
this key should be used.

Note: This value can change. It is not a static value.

Requirement: Optional for any interconnect.

Example:
<pre>
@textblock
<dict>
	<key>Controller Characteristics</key>
	<dict>
		<key>Port Topology</key>
		<string>N_Port</string>
	</dict>
</dict>
@/textblock
</pre>
*/
#define kIOPropertyPortTopologyNPortKey					"N_Port"


/*!
@defined kIOPropertyPortTopologyNLPortKey
@discussion This key defines the value of NL_Port for the key
kIOPropertyPortTopologyKey. If the topology of the port is an NL_Port,
this key should be used.

Note: This value can change. It is not a static value.

Requirement: Optional for any interconnect.

Example:
<pre>
@textblock
<dict>
	<key>Controller Characteristics</key>
	<dict>
		<key>Port Topology</key>
		<string>NL_Port</string>
	</dict>
</dict>
@/textblock
</pre>
*/
#define kIOPropertyPortTopologyNLPortKey				"NL_Port"


/*!
@defined kIOPropertyPortTopologyAutomaticNPortKey
@discussion This key defines the value of Automatic (N_Port) for the key
kIOPropertyPortTopologyKey. If the topology of the port is
N_Port and is automatically determined by host software, this
key should be used.

Note: This value can change. It is not a static value.

Requirement: Optional for any interconnect.

Example:
<pre>
@textblock
<dict>
	<key>Controller Characteristics</key>
	<dict>
		<key>Port Topology</key>
		<string>Automatic (N_Port)</string>
	</dict>
</dict>
@/textblock
</pre>
*/
#define kIOPropertyPortTopologyAutomaticNPortKey		"Automatic (N_Port)"


/*!
@defined kIOPropertyPortTopologyAutomaticNLPortKey
@discussion This key defines the value of Automatic (NL_Port) for the key
kIOPropertyPortTopologyKey. If the topology of the port is
NL_Port and is automatically determined by host software, this
key should be used.

Note: This value can change. It is not a static value.

Requirement: Optional for any interconnect.

Example:
<pre>
@textblock
<dict>
	<key>Controller Characteristics</key>
	<dict>
		<key>Port Topology</key>
		<string>Automatic (NL_Port)</string>
	</dict>
</dict>
@/textblock
</pre>
*/
#define kIOPropertyPortTopologyAutomaticNLPortKey		"Automatic (NL_Port)"


/*!
@defined kIOPropertySCSIParallelSignalingTypeHVDKey
@discussion This key defines the value of High Voltage Differential for the key
kIOPropertySCSIParallelSignalingTypeKey. If the signaling type of the port is
High Voltage Differential, this key should be used.

Requirement: Optional for SCSI Parallel Interface interconnect.

Example:
<pre>
@textblock
<dict>
	<key>Controller Characteristics</key>
	<dict>
		<key>SCSI Parallel Signaling Type</key>
		<string>High Voltage Differential</string>
	</dict>
</dict>
@/textblock
</pre>
*/
#define kIOPropertySCSIParallelSignalingTypeHVDKey		"High Voltage Differential"


/*!
@defined kIOPropertySCSIParallelSignalingTypeLVDKey
@discussion This key defines the value of Low Voltage Differential for the key
kIOPropertySCSIParallelSignalingTypeKey. If the signaling type of the port is
Low Voltage Differential, this key should be used.

Requirement: Optional for SCSI Parallel Interface interconnect.

Example:
<pre>
@textblock
<dict>
	<key>Controller Characteristics</key>
	<dict>
		<key>SCSI Parallel Signaling Type</key>
		<string>Low Voltage Differential</string>
	</dict>
</dict>
@/textblock
</pre>
*/
#define kIOPropertySCSIParallelSignalingTypeLVDKey		"Low Voltage Differential"


/*!
@defined kIOPropertySCSIParallelSignalingTypeSEKey
@discussion This key defines the value of Single Ended for the key
kIOPropertySCSIParallelSignalingTypeKey. If the signaling type of the port is
Single Ended, this key should be used.

Requirement: Optional for SCSI Parallel Interface interconnect.

Example:
<pre>
@textblock
<dict>
	<key>Controller Characteristics</key>
	<dict>
		<key>SCSI Parallel Signaling Type</key>
		<string>Single Ended</string>
	</dict>
</dict>
@/textblock
</pre>
*/
#define kIOPropertySCSIParallelSignalingTypeSEKey		"Single Ended"


/*!
@defined kIOPropertyFibreChannelCableDescriptionCopperKey
@discussion This key defines the value of Copper for the key
kIOPropertyFibreChannelCableDescriptionKey. If the cabling is
Copper, this key should be used.

Requirement: Optional for Fibre Channel Interface interconnect.

Example:
<pre>
@textblock
<dict>
	<key>Controller Characteristics</key>
	<dict>
		<key>Fibre Channel Cabling Type</key>
		<string>Copper</string>
	</dict>
</dict>
@/textblock
</pre>
*/
#define kIOPropertyFibreChannelCableDescriptionCopperKey		"Copper"


/*!
@defined kIOPropertyFibreChannelCableDescriptionFiberOpticKey
@discussion This key defines the value of Fiber Optic for the key
kIOPropertyFibreChannelCableDescriptionKey. If the cabling is
Fiber Optic, this key should be used.

Requirement: Optional for Fibre Channel Interface interconnect.

Example:
<pre>
@textblock
<dict>
	<key>Controller Characteristics</key>
	<dict>
		<key>Fibre Channel Cabling Type</key>
		<string>Fiber Optic</string>
	</dict>
</dict>
@/textblock
</pre>
*/
#define kIOPropertyFibreChannelCableDescriptionFiberOpticKey	"Fiber Optic"


#endif	/* _IOKIT_IO_STORAGE_PROTOCOL_CHARACTERISTICS_H_ */
