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
  @header IOFireWireSBP2ORB
  Contains the class definition for IOFireWireSBP2ORB.
*/

#ifndef _IOKIT_IOFIREWIRESBP2ORB_H
#define _IOKIT_IOFIREWIRESBP2ORB_H

#include <IOKit/firewire/IOFireWireUnit.h>

#include <IOKit/IOBufferMemoryDescriptor.h>
#include <IOKit/IOUserClient.h>

// login option flags
enum
{
    kFWSBP2CommandCompleteNotify			= (1 << 0),
    kFWSBP2CommandTransferDataFromTarget	= (1 << 1),
    kFWSBP2CommandImmediate					= (1 << 2),
    
    kFWSBP2CommandNormalORB					= (1 << 5),
    kFWSBP2CommandReservedORB				= (1 << 6),
    kFWSBP2CommandVendorORB					= (1 << 7),
    kFWSBP2CommandDummyORB					= (1 << 8),
    kFWSBP2CommandCheckGeneration			= (1 << 9),
	
	kFWSBP2CommandFixedSize					= (1 << 10),
	kFWSBP2CommandVirtualORBs				= (1 << 11)     // handy for debugging
};

enum
{
    kFWSBP2MaxPageClusterSize = 0xf000
};

class IOFireWireSBP2ORB;
class IOFireWireSBP2LUN;
class IOFireWireSBP2Login;

/*!
    @class IOFireWireSBP2ORB
    @abstract Represents an SBP2 normal command ORB.  Supplies the APIs for configuring normal
    command ORBs.  This includes setting the command block and writing the page tables for I/O.
    The ORBs are executed using the submitORB method in IOFireWireSBP2Login.
*/

class IOFireWireSBP2ORB : public IOCommand
{
    OSDeclareDefaultStructors( IOFireWireSBP2ORB )

	friend class IOFireWireSBP2Login;
	friend class IOFireWireSBP2ManagementORB;
	
protected:
    
    typedef struct
    {
        UInt32		nextORBAddressHi;
        UInt32		nextORBAddressLo;
        UInt32		dataDescriptorHi;
        UInt32		dataDescriptorLo;
        UInt16		options;
        UInt16		dataSize;
        UInt32		commandBlock[1];  // will be variable sized
     } FWSBP2ORB;

    typedef struct
    {
        UInt16		segmentLength;
        UInt16		segmentBaseAddressHi;
        UInt32		segmentBaseAddressLo;
    } FWSBP2PTE;

private:

    OSMetaClassDeclareReservedUnused(IOFireWireSBP2ORB, 0);
    OSMetaClassDeclareReservedUnused(IOFireWireSBP2ORB, 1);
    OSMetaClassDeclareReservedUnused(IOFireWireSBP2ORB, 2);
    OSMetaClassDeclareReservedUnused(IOFireWireSBP2ORB, 3);
    OSMetaClassDeclareReservedUnused(IOFireWireSBP2ORB, 4);
    OSMetaClassDeclareReservedUnused(IOFireWireSBP2ORB, 5);
    OSMetaClassDeclareReservedUnused(IOFireWireSBP2ORB, 6);
    OSMetaClassDeclareReservedUnused(IOFireWireSBP2ORB, 7);
    OSMetaClassDeclareReservedUnused(IOFireWireSBP2ORB, 8);

protected:    

    virtual void deallocateBufferAddressSpace( void );
    virtual IOReturn allocateTimer( void );
    virtual void deallocateTimer( void );
    
    /*!
		@function deallocatePageTable
		@abstract Frees up memory allocated for the page table.
		@discussion	Frees all memory associated with the page table.  Undoes what allocatePageTable does. 
        Calling allocatePageTable again will automatically deallocate the existing page table before 
        allocating a new one, so this method is not used in most cases.
	*/
    
    virtual void deallocatePageTable( void );

protected:
	
    // IOFireWireSBP2Login methods
	virtual bool initWithLogin( IOFireWireSBP2Login * login );
    virtual void setNextORBAddress( FWAddress address );

public:

    /*!
		@function allocatePageTable
		@abstract Allocates memory for the page table.
		@discussion	Page table allocation is handle automatically by the ORB, except if the 
        kFWSBP2CommandFixedSize flags is set.  In this case we will fail to write a page table if we 
        need more page table space than we have already.  This method is exposed so these drivers 
        can preallocate as much page table as they need.  This is useful if your driver is part of 
        the paging path and cannot allow allocations to occur.
        @param entryCount number of entries of page table to be allocated.
	*/

    virtual IOReturn allocatePageTable( UInt32 entryCount );

protected:

    virtual bool isTimerSet( void );
    virtual void cancelTimer( void );
    
protected:
  
    // reserved for future use
    struct ExpansionData { };
    ExpansionData *reserved; 
       
    IOFireWireSBP2Login *	fLogin;
    IOFireWireSBP2LUN * 	fLUN;
    IOFireWireUnit *		fUnit;
    IOFireWireController *	fControl;
    void *					fUnused1;
    void *	  				fUnused2;

    UInt32			fCommandFlags;
    UInt32			fMaxPayloadSize;
    UInt32			fTimeoutDuration;
    UInt32			fGeneration;
    void *			fRefCon;
    
	//
    // orb
    //
	
	IOBufferMemoryDescriptor *	fORBDescriptor;
    FWSBP2ORB *					fORBBuffer;
	
    FWAddress 					fORBPseudoAddress;
    IOFWAddressSpace *			fORBPseudoAddressSpace;

    IOFWAddressSpace *			fORBPhysicalAddressSpace;
	IOPhysicalAddress			fORBPhysicalAddress;

	//
    // page table
    //
	
	UInt32						fPageTableSize;
    IOBufferMemoryDescriptor *	fPageTableDescriptor;

    IOFWAddressSpace *			fPageTablePhysicalAddressSpace;
	IOPhysicalAddress			fPageTablePhysicalAddress;
	
	IOFWAddressSpace *			fPageTablePseudoAddressSpace;   
	FWAddress					fPageTablePseudoAddress;

	//
    // buffers
    //
	
	IOFWAddressSpace *		fBufferAddressSpace;
    bool					fBufferAddressSpaceAllocated;
    IOMemoryDescriptor *	fBufferDescriptor;
    
	//
    // timer
    //
	
	IOFWDelayCommand *		fTimeoutCommand;
    bool					fTimeoutTimerSet;

    virtual IOReturn allocateResources( void );
    virtual void free( void );

    // orb timeout handler
    static void orbTimeoutStatic( void *refcon, IOReturn status, IOFireWireBus *bus, IOFWBusCommand *fwCmd );
    virtual void orbTimeout( IOReturn status, IOFireWireBus *bus, IOFWBusCommand *fwCmd );

	// login friend class wrappers
	virtual IOFireWireUnit * getFireWireUnit( void );
	virtual IOFireWireSBP2LUN * getFireWireLUN( void );
  	virtual void deallocateORB( void );
	virtual IOReturn allocateORB( UInt32 orbSize );
    virtual IOReturn removeORB( IOFireWireSBP2ORB * orb );
    virtual void prepareORBForExecution( void );
    virtual void startTimer( void );
    virtual void sendTimeoutNotification( IOFireWireSBP2ORB * orb );

public:
 
    /*! 
        @function release
        @abstract Primary implementation of the release mechanism.
        @discussion See OSObject.h for more information. 
        @param when When retainCount == when then call free(). 
    */
       
	virtual void release() const;

    /*! 
        @function getLogin
        @abstract Gets the login associated with this ORB.
        @discussion Returns the IOFireWireSBP2Login object associated with this ORB.
        @result Returns a pointer to an IOFireWireSBP2Login. 
    */
    
    virtual IOFireWireSBP2Login * getLogin( void );

    /*! 
        @function setCommandBuffersAsRanges
        @abstract Creates a page table from a list of ranges.
        @discussion Creates a page table with the given parameters. Any addresses mapped by this method 
        must remain valid until setCommandBuffers is called again or releaseCommandBuffers is called.  
        The SBP2 services do not release references to the command buffers just because the command 
        has completed.
        @param ranges An array of ranges representing the data to be transfered.
        @param withCount The number of ranges in the ranges array.
        @param withDirection An IODirection indicating the direction of data transfer.
        @param withTask The task that these adressses reside in.
        @param offset Offset in bytes into data to begin writing table at.
        @param length Number of bytes of data to map from offset.
        @result Returns KIOReturnSuccess if the page table was written successfully. 
    */
    
    virtual IOReturn setCommandBuffersAsRanges(  IOVirtualRange * ranges,
                                                 UInt32           withCount,
                                                 IODirection      withDirection,
                                                 task_t           withTask,
                                                 UInt32		offset = 0,
                                                 UInt32		length = 0 );
    /*! 
        @function setCommandBuffersAsRanges
        @abstract Creates a page table from a list of ranges.
        @discussion Creates a page table with the given parameters. Any addresses mapped by this method 
        must remain valid until setCommandBuffers is called again or releaseCommandBuffers is called.  
        The SBP2 services do not release references to the command buffers just because the command 
        has completed.
        @param memoryDescriptor IOMemoryDescriptor describe ranges to be written to a page table.
        @param offset Offset in bytes into data to begin writing table at.
        @param length Number of bytes of data to map from offset.
        @result Returns KIOReturnSuccess if the page table was written successfully. 
    */
    
    virtual IOReturn setCommandBuffers( IOMemoryDescriptor * memoryDescriptor, UInt32 offset = 0, 
																				UInt32 length = 0 );


    /*! 
        @function releaseCommandBuffers
        @abstract Releases SBP2's reference to the command buffers.
        @discussion When you create a page table with one of the variants of setCommandBuffers.  
        SBP2 holds on to a reference to the buffers until this method is called.  This means that 
        if a command completed and you manipulated the memory descriptor or released the buffers 
        without calling this method you could leave FW in an inconsistent state.  
        @result Returns KIOReturnSuccess if the page table was cleared successfully. 
    */

    virtual IOReturn releaseCommandBuffers( void );
    
    /*! 
        @function setCommandBlock
        @abstract Sets the command block portion of the ORB.
        @discussion Copys the data provided in the buffer to the command block portion of the ORB.
        @param buffer Pointer to buffer to copy command block from.
        @param length Number of bytes of data to copy.
        @result Returns KIOReturnSuccess if the command block was updated successfully. 
    */
    
    virtual IOReturn setCommandBlock( void * buffer, UInt32 length );
    
    /*! 
        @function setCommandBlock
        @abstract Sets the command block portion of the ORB.
        @discussion Copys the data provided in the buffer to the command block portion of the ORB.
        @param memory IOMemoryDescriptor representing the command block buffer.
        @result Returns KIOReturnSuccess if the command block was updated successfully. 
    */
    
    virtual IOReturn setCommandBlock( IOMemoryDescriptor * memory );
    
    /*! 
        @function getCommandBufferDescriptor
        @abstract Returns the memory descriptor representing the command buffer.
        @discussion Returns the IOMemoryDescriptor for the data mapped by setCommandBuffer variants.  
        Works for setCommandBuffersAsRanges too.
        @result Returns memory descriptor representing mapped data buffers. 
    */
    
	virtual IOMemoryDescriptor * getCommandBufferDescriptor( void );
	
    // accessors
    
    /*! 
        @function setCommandFlags
        @abstract Sets configuration flags for the ORB.
        @discussion Sets the configuration flags for the ORB.  These can be any of the following:
        kFWSBP2CommandCompleteNotify, kFWSBP2CommandTransferDataFromTarget, kFWSBP2CommandImmediate,
        kFWSBP2CommandNormalORB, kFWSBP2CommandReservedORB, kFWSBP2CommandVendorORB, 
        kFWSBP2CommandDummyORB, kFWSBP2CommandCheckGeneration, kFWSBP2CommandFixedSize, 
        or kFWSBP2CommandVirtualORBs.  Note that you will not recieve status of your ORB completing 
        unless kFWSBP2CommandCompleteNotify is set.
        @param flags The flags to be set.
    */
    
    virtual void setCommandFlags( UInt32 flags );

    /*! 
        @function getCommandFlags
        @abstract Gets configuration flags for the ORB.
        @discussion Returns the current configuration flags set on this ORB.
        @result Return The current ORB flags.
    */
    
    virtual UInt32 getCommandFlags( void );

    /*! 
        @function setMaxPayloadSize
        @abstract Sets max payload size for the ORB.
        @discussion This sets the maximum payload size for this ORB only.  This size is clipped by 
        the global max payload size set in the login object.
        @param maxPayloadSize The maximum payload size in bytes.
    */
    
    virtual void setMaxPayloadSize( UInt32 maxPayloadSize );

    /*! 
        @function getMaxPayloadSize
        @abstract Gets max payload size for the ORB.
        @discussion This gets the maximum payload size for this ORB only.
        @result Returns the maximum payload size in bytes.
    */
    
    virtual UInt32 getMaxPayloadSize( void );

    /*! 
        @function setCommandTimeout
        @abstract Sets the timeout of the ORB.
        @discussion This sets the timeout for the ORB in milliseconds. Note that ORBs without timeouts 
        can be "lost."  You will obviously not recieve timeout notification for timeouts of zero.  But 
        perhaps less obviously you will not recieve orb reset notification, which is really a sort of
        accelerated timeout notification for bus reset situations.  
        @param timeout The timeout duration in milliseconds.
    */
    
    virtual void setCommandTimeout( UInt32 timeout );
    
    /*! 
        @function getCommandTimeout
        @abstract Gets the timeout of the ORB.
        @discussion This method gets the timeout for this ORB in milliseconds.
        @result Returns the timeout for the orb in milliseconds.
    */
    
    virtual UInt32 getCommandTimeout( void );


    /*! 
        @function setCommandGeneration
        @abstract Sets the command generation.
        @discussion This sets the bus generation this ORB should be appended in.  It is only meaningful 
        when combined with the kFWSBP2CommandCheckGeneration flags above.
        @param gen The bus generation for command execution.
    */
    
    virtual void setCommandGeneration( UInt32 gen );
    
    /*! 
        @function getCommandGeneration
        @abstract Gets the command generation.
        @discussion This gets the bus generation this ORB should be appended in.
        @result Returns the bus generation for command execution.
    */
    
    virtual UInt32 getCommandGeneration( void );

    /*!
		@function setRefCon
		@abstract Sets the ORB refCon.
		@discussion Sets a user defined value on the ORB that can be retrieved later with the 
        method getRefCon.
        @param refCon a user defined value.
    */
    
    virtual void setRefCon( void * refCon );

    /*!
		@function getRefCon
		@abstract Returns the refCon set with setRefCon.
		@discussion Returns the user defined value previously stored in the ORB with setRefCon.
        @result Returns the previously stored user defined value.
	*/
    
    virtual void * getRefCon( void );

protected:    

    virtual void setToDummy( void );

public:	
    /*!
		@function getORBAddress
		@abstract Returns the FireWire address of this ORB.
		@discussion Returns the FireWire bus address of this ORB.  This is not the same as the Macintosh 
        address for the IOFireWireSBP2ORB.
        @result Returns the FireWire address of this ORB.
	*/
    
    virtual void getORBAddress( FWAddress * address );    
};
    
#endif