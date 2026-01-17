/*
 * Copyright (c) 1998-2014 Apple Inc. All rights reserved.
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
 

#ifndef _IOKIT_UFI_STORAGE_SERVICES_H_
#define _IOKIT_UFI_STORAGE_SERVICES_H_

#if defined(KERNEL) && defined(__cplusplus)

#include <IOKit/IOTypes.h>
#include <IOKit/storage/IOBlockStorageDevice.h>
#include <IOKit/usb/IOUSBMassStorageUFISubclass.h>


class IOUFIStorageServices : public IOBlockStorageDevice
{
	
	OSDeclareDefaultStructors ( IOUFIStorageServices )

private:
	bool							fMediaChanged;
	bool							fMediaPresent;

protected:
	
    IOUSBMassStorageUFIDevice *		fProvider;

	UInt64							fMaxReadBlocks;
	UInt64							fMaxWriteBlocks;
	
	virtual bool	attach ( IOService * provider );
	virtual void	detach ( IOService * provider );
	
    // Reserve space for future expansion.
    struct IOUFIStorageServicesExpansionData { };
    IOUFIStorageServicesExpansionData *fIOUFIStorageServicesReserved;
	
public:

	virtual IOReturn 	message ( UInt32 type, IOService * provider, void * argument );

	static void 		AsyncReadWriteComplete ( void * 			clientData,
                                				 IOReturn			status,
                                				 UInt64 			actualByteCount );

    // Deprecated
    virtual IOReturn    doAsyncReadWrite (	IOMemoryDescriptor *	buffer,
											UInt32					block,
											UInt32					nblks,
											IOStorageCompletion		completion );
                                            
	virtual IOReturn	doAsyncReadWrite (  IOMemoryDescriptor *    buffer,
                                            UInt64                  block, 
                                            UInt64                  nblks,
                                            IOStorageAttributes *   attributes,
                                            IOStorageCompletion *   completion );

	virtual IOReturn	doSyncReadWrite ( 	IOMemoryDescriptor *	buffer,
											UInt32					block,
											UInt32					nblks );

    virtual IOReturn	doEjectMedia ( void );

    virtual IOReturn	doFormatMedia ( UInt64 byteCapacity );

    virtual UInt32		doGetFormatCapacities ( UInt64 *	capacities,
    											UInt32		capacitiesMaxCount ) const;

    virtual IOReturn	doSynchronizeCache ( void );
        
    virtual char *		getVendorString ( void );
    
    virtual char *		getProductString ( void );
    
    virtual char *		getRevisionString ( void );
    
    virtual char *		getAdditionalDeviceInfoString ( void );
    
    virtual IOReturn	reportBlockSize ( UInt64 * blockSize );
    
    virtual IOReturn	reportEjectability ( bool * isEjectable );
    
    virtual IOReturn	reportMediaState ( bool * mediaPresent, bool * changed );
    
    virtual IOReturn	reportMaxValidBlock ( UInt64 * maxBlock );
    
    virtual IOReturn	reportRemovability ( bool * isRemovable );
    
    virtual IOReturn	reportWriteProtection ( bool * isWriteProtected );

    virtual IOReturn	getWriteCacheState ( bool * enabled );
	
	virtual IOReturn	setWriteCacheState ( bool enabled );
    
	// Space reserved for future expansion.
    OSMetaClassDeclareReservedUnused( IOUFIStorageServices, 1 );
    OSMetaClassDeclareReservedUnused( IOUFIStorageServices, 2 );
    OSMetaClassDeclareReservedUnused( IOUFIStorageServices, 3 );
    OSMetaClassDeclareReservedUnused( IOUFIStorageServices, 4 );
    OSMetaClassDeclareReservedUnused( IOUFIStorageServices, 5 );
    OSMetaClassDeclareReservedUnused( IOUFIStorageServices, 6 );
    OSMetaClassDeclareReservedUnused( IOUFIStorageServices, 7 );
    OSMetaClassDeclareReservedUnused( IOUFIStorageServices, 8 );

};

#endif	/* defined(KERNEL) && defined(__cplusplus) */

#endif	/* _IOKIT_UFI_STORAGE_SERVICES_H_ */
