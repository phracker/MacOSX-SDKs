/*
 * Copyright (c) 1998-2003 Apple Computer, Inc. All rights reserved.
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


#ifndef _IO_ATA_BLOCKSTORAGE_DEVICE_H_
#define _IO_ATA_BLOCKSTORAGE_DEVICE_H_

#include <IOKit/IOTypes.h>
#include <IOKit/ata/IOATACommand.h>
#include <IOKit/storage/IOBlockStorageDevice.h>

class IOATABlockStorageDriver;

class IOATABlockStorageDevice : public IOBlockStorageDevice
{
	
	OSDeclareDefaultStructors ( IOATABlockStorageDevice )
	
	
protected:
	
	
	IOATABlockStorageDriver *     fProvider;
	
	// binary compatibility instance variable expansion
	struct ExpansionData
	{
		OSSet *		fClients;
	};
	ExpansionData * reserved;
	
	#define fClients			reserved->fClients
	
	virtual bool		attach ( IOService * provider );
	virtual void		detach ( IOService * provider );

    virtual bool		handleOpen ( IOService * client, IOOptionBits options, void * access );
	virtual void		handleClose ( IOService * client, IOOptionBits options );
    virtual bool		handleIsOpen ( const IOService * client ) const;
	
public:
	
	//-----------------------------------------------------------------------
	// Override setProperties for turning off APM features on powerbooks.
	
    virtual IOReturn	setProperties ( OSObject * properties );
	
	
	virtual IOReturn	doAsyncReadWrite ( 	IOMemoryDescriptor *	buffer,
											UInt32					block,
											UInt32					nblks,
											IOStorageCompletion		completion );
	
	virtual IOReturn	doSyncReadWrite ( 	IOMemoryDescriptor *	buffer,
											UInt32					block,
											UInt32					nblks );
	
    virtual IOReturn	doEjectMedia ( void );
	
    virtual IOReturn	doFormatMedia ( UInt64 byteCapacity );
	
    virtual UInt32		doGetFormatCapacities ( UInt64 *	capacities,
    											UInt32		capacitiesMaxCount ) const;
	
    virtual IOReturn	doLockUnlockMedia ( bool doLock );
	
    virtual IOReturn	doSynchronizeCache ( void );
        
    virtual char *		getVendorString ( void );
    
    virtual char *		getProductString ( void );
    
    virtual char *		getRevisionString ( void );
    
    virtual char *		getAdditionalDeviceInfoString ( void );
    
    virtual IOReturn	reportBlockSize ( UInt64 * blockSize );
    
    virtual IOReturn	reportEjectability ( bool * isEjectable );
    
    virtual IOReturn	reportLockability ( bool * isLockable );
    
    virtual IOReturn	reportMediaState ( bool * mediaPresent, bool * changed );
    
    virtual IOReturn	reportPollRequirements ( 	bool * pollIsRequired,
    												bool * pollIsExpensive );
    
    virtual IOReturn	reportMaxReadTransfer ( UInt64 blockSize, UInt64 * max );
    
    virtual IOReturn	reportMaxValidBlock ( UInt64 * maxBlock );
    
    virtual IOReturn	reportMaxWriteTransfer ( UInt64 blockSize, UInt64 * max );
    
    virtual IOReturn	reportRemovability ( bool * isRemovable );
    
    virtual IOReturn	reportWriteProtection ( bool * isWriteProtected );
	
	virtual IOReturn	getWriteCacheState ( bool * enabled );
	virtual IOReturn	setWriteCacheState ( bool enabled );
	
	/* Added with 10.1.4 */
	OSMetaClassDeclareReservedUsed ( IOATABlockStorageDevice, 1 )
	
	virtual IOReturn	sendSMARTCommand ( IOATACommand * command );
	
	
	// Binary Compatibility reserved method space
	OSMetaClassDeclareReservedUnused ( IOATABlockStorageDevice, 2 );
	OSMetaClassDeclareReservedUnused ( IOATABlockStorageDevice, 3 );
	OSMetaClassDeclareReservedUnused ( IOATABlockStorageDevice, 4 );
	OSMetaClassDeclareReservedUnused ( IOATABlockStorageDevice, 5 );
	OSMetaClassDeclareReservedUnused ( IOATABlockStorageDevice, 6 );
	OSMetaClassDeclareReservedUnused ( IOATABlockStorageDevice, 7 );
	OSMetaClassDeclareReservedUnused ( IOATABlockStorageDevice, 8 );
	OSMetaClassDeclareReservedUnused ( IOATABlockStorageDevice, 9 );
	OSMetaClassDeclareReservedUnused ( IOATABlockStorageDevice, 10 );
	OSMetaClassDeclareReservedUnused ( IOATABlockStorageDevice, 11 );
	OSMetaClassDeclareReservedUnused ( IOATABlockStorageDevice, 12 );
	OSMetaClassDeclareReservedUnused ( IOATABlockStorageDevice, 13 );
	OSMetaClassDeclareReservedUnused ( IOATABlockStorageDevice, 14 );
	OSMetaClassDeclareReservedUnused ( IOATABlockStorageDevice, 15 );
	OSMetaClassDeclareReservedUnused ( IOATABlockStorageDevice, 16 );
	
};

#endif /* !_IO_ATA_BLOCKSTORAGE_DEVICE_H_ */
