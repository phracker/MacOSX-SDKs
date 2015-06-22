

//==============================================================================
//
//  IOUSBMassStorageDriverNub.h
//  IOUSBMassStorageDriver
//
//  Created on 02/02/15.
//  Copyright (c) 2015 Apple Inc. All rights reserved.
//
//==============================================================================


//==============================================================================
//
//  IOUSBMassStorageDriverNub Class
//
//==============================================================================

#ifndef __IOUSBMassStorageDriver__IOUSBMassStorageDriverNub__
#define __IOUSBMassStorageDriver__IOUSBMassStorageDriverNub__

/*!
 @header IOUSBMassStorageDriverNub
 @discussion This file contains definitions for the IOUSBMassStorageDriverNub
 class
 */


//==============================================================================
//
//  Includes
//
//==============================================================================

// Generic IOKit headers
#include <IOKit/IOService.h>
#include <IOKit/IOWorkLoop.h>

// USB-specific includes
#include <IOKit/usb/IOUSBHostPipe.h>


//==============================================================================
//
//  Constants
//
//==============================================================================

enum
{
    
    kUSBMassStorageDriverNubPowerStateOff   = 0,
    kUSBMassStorageDriverNubPowerStateOn    = 1,
    kUSBMassStorageDriverNubNumPowerStates
    
};

enum
{
    kUSBPipeUsageCommand        = 0x01,
    kUSBPipeUsageStatus         = 0x02,
    kUSBPipeUsageDataIn         = 0x03,
    kUSBPipeUsageDataOut        = 0x04
};

enum
{
    kUSBStatusPipeIndex         = 0,
    kUSBDataInPipeIndex         = 1,
    kUSBDataOutPipeIndex        = 2,
    kUSBNumberOfUASPipes        = 3
};

#define kMinStreamID                1
#define kUSBFirstUASPipeID          kUSBPipeUsageStatus
#define kUSBMaxUASQueueDepth        32
#define kUSBDefaultUASQueueDepth    32


//==============================================================================
//
//  Forward Declarations
//
//==============================================================================

class   IOUSBMassStorageInterfaceNub;
class   IOUSBMassStorageDriver;


//==============================================================================
//
//  Class Declaration
//
//==============================================================================

class IOUSBMassStorageDriverNub : public IOService
{
    
    OSDeclareDefaultStructors ( IOUSBMassStorageDriverNub )
    
public:
    
    /*!
     @function probe
     @abstract IOService probe() method subclass.
     During an IOService object's instantiation, probes a matched service to see if it can be used.
     @discussion See IOService.h for details.
     @param provider The registered IOService object that matches a driver personality's matching dictionary.
     @param score Pointer to the current driver's probe score, which is used to order multiple matching drivers in the same match category. It defaults to the value of the <code>IOProbeScore</code> property in the drivers property table, or <code>kIODefaultProbeScore</code> if none is specified. The <code>probe</code> method may alter the score to affect start order.
     @result An IOService instance or zero when the probe is unsuccessful. In almost all cases the value of <code>this</code> is returned on success. If another IOService object is returned, the probed instance is detached and freed, and the returned instance is used in its stead for <code>start</code>.
     */
    
    virtual IOService * probe ( IOService * provider, SInt32 * score ) override;
    
    /*!
     @function attach
     @abstract IOService attach() method subclass.
     Attaches an IOService client to a provider in the I/O Registry.
     @discussion See IOService.h for details.
     @result <code>false</code> if the provider is inactive or on a resource
     failure; otherwise <code>true</code>.
     */
    
    virtual bool attach ( IOService * provider ) override;
    
    /*!
     @function detach
     @abstract IOService detach() method subclass.
     Detaches an IOService client from a provider in the I/O Registry.
     @discussion See IOService.h for details.
     @param provider The IOService object to detach from.
     */
    
    virtual void detach ( IOService * provider ) override;
    
    /*!
     @function start
     @abstract IOService start() method subclass.
     Called during an the object's instantiation. It starts the IOService object that has been selected to run on the provider.
     @discussion See IOService.h for details.
     @result <code>true</code> if the start was successful; <code>false</code> otherwise (which will cause the instance to be detached and usually freed).
     */
    
    virtual bool start ( IOService * provider ) override;
    
    /*!
     @function stop
     @abstract IOService stop() method subclass.
     Called before object is detached & it is destroyed.
     @discussion See IOService.h for details.
     */
    
    virtual void stop ( IOService * provider ) override;
    
    /*! @function requestTerminate
     @abstract IOService requestTerminate() method subclass.
     Passes a termination up the stack.
     @discussion See IOService.h for details.
     @param provider The terminated provider of this object.
     @param options Options originally passed to terminate, plus <code>kIOServiceRecursing</code>.
     @result <code>true</code> if this object should be terminated now that its provider has been.
     */
    
    virtual bool requestTerminate ( IOService * provider, IOOptionBits options ) override;
    
    /*!
     @function terminate
     @abstract IOService terminate() method subclass.
        Makes an IOService object inactive and begins its destruction.
     @discussion See IOService.h for details.
     */
    
    virtual bool terminate ( IOOptionBits options = 0 ) override;
    
    /*! @function willTerminate
     @abstract IOService terminate() method subclass.
     Passes a termination up the stack.
     @discussion See IOService.h for details.
     @param provider The terminated provider of this object.
     @param options Options originally passed to terminate.
     @result <code>true</code>. */
    
    virtual bool willTerminate ( IOService * provider, IOOptionBits options ) override;
    
    /*!
     @function open
     @abstract IOService open() method subclass.
     Requests active access to a provider.
     @discussion See IOService.h for details.
     @param forClient Designates the client of the provider requesting the open.
     @param options Options for the open. The provider family may implement options for open; IOService defines only <code>kIOServiceSeize</code> to request the device be withdrawn from its current owner.
     @result <code>true</code> if the open was successful; <code>false</code> otherwise. */
    
    virtual bool open ( IOService *     forClient,
                        IOOptionBits    options = 0,
                        void *          arg = 0      ) override;
    
    /*!
     @function close
     @abstract IOService close() method subclass.
     Releases active access to a provider.
     @discussion See IOService.h for details.
     @param forClient Designates the client of the provider requesting the close.
     @param options Options available for the close. The provider family may implement options for close; IOService defines none.
     @param arg Family specific arguments which are ignored by IOService.
     */
    
    virtual void close ( IOService *        forClient,
                         IOOptionBits       options = 0 ) override;
    
    /*!
     @function free
     @abstract IOService free() method subclass.
     Frees data structures that were allocated when power management was initialized on this service.
     @discussion See IOService.h for details.
     */
    
    virtual void free ( void ) override;
    
    /*!
     @function getWorkLoop
     @abstract IOService getWorkLoop() method subclass.
     @discussion See IOService.h for details.
     @result The current work loop.
     */
    
    virtual IOWorkLoop * getWorkLoop ( ) const override;
    
    /*!
     @function matchPropertyTable
     @abstract Allows a registered IOService object to implement family specific matching.
     @discussion All matching on an IOService object will call this method to allow a family writer to implement matching in addition to the generic methods provided by IOService. The implementer should examine the matching dictionary passed to see if it contains properties the family understands for matching, and use them to match with the IOService object if so. Note that since matching is also carried out by other parts of the I/O Kit, the matching dictionary may contain properties the family does not understand - these should not be considered matching failures.
     @param table The dictionary of properties to be matched against.
     @param score Pointer to the current driver's probe score, which is used to order multiple matching drivers in the same match category. It defaults to the value of the <code>IOProbeScore</code> property in the drivers property table, or <code>kIODefaultProbeScore</code> if none is specified.
     @result <code>false</code> if the family considers the matching dictionary does not match in properties it understands; <code>true</code> otherwise. */
    
    virtual bool matchPropertyTable ( OSDictionary *    table,
                                      SInt32 *          score  ) override;
    
    /*!
     @function retain
     @abstract Retains a reference to the object.
     @discussion This function increments the reference count of the receiver by 1. If you need to maintain a reference to an object outside the context in which you received it, you should always retain it immediately.
     */
    
    virtual void retain ( void ) const APPLE_KEXT_OVERRIDE;
    
    /*!
     @function release
     @abstract Releases a reference to the object, freeing it immediately if the reference count drops to zero.
     @discussion This function decrements the reference count of the receiver by 1. If the reference count drops to zero, the object is immediately freed using <code>@link //apple_ref/cpp/instm/OSObject/free/virtualvoid/() free@/link</code>.
     */
    
    virtual void release ( void ) const APPLE_KEXT_OVERRIDE;
    
protected:
    
    /*!
     @function InitializePowerManagement
     @abstract Subclasses call this method to initialize power management.
     @discussion Subclasses call this method to initialize power management.
     @param provider The provider to be joined to in the power management tree.
     */
    
    virtual void InitializePowerManagement ( IOService * provider );
    
public:
    
    virtual IOReturn setPowerState ( unsigned long      powerStateOrdinal,
                             IOService *        whatDevice         ) override;
    
    bool DidWakeFromHibernationOrStandby ( void );
    
protected:
    
    u_int64_t                       fUSBMassStorageTraceID;
    
    // Device information
    OSDictionary *                  fDeviceInfo;
    u_int16_t                       fVendorID;
    u_int16_t                       fProductID;
    u_int8_t                        fCurrentConfiguration;
    u_int8_t                        fInterfaceNumber;
    u_int8_t                        fDeviceProtocol;
    
    UInt32                          fFlags;
    
    bool                            fInitialized;
    bool                            fTerminated;

    bool                            fReattachInProgress;
    
    IOService *                     fAppleUSBHostPort;
    IOUSBMassStorageInterfaceNub *  fIOUSBMassStorageInterfaceNub;
    
    bool                            fResetInProgress;
    uint64_t                        fResetTimeStamp;
    
    IOWorkLoop *                    fWorkLoop;
    IOCommandGate *                 fCommandGate;
    
    unsigned long                   fCurrentPowerState;
    
    // UMC Pipes
    IOUSBHostPipe *                 fInterruptPipe;
    IOUSBHostPipe *                 fBulkOnlyOutPipe;
    IOUSBHostPipe *                 fBulkOnlyInPipe;
    
    // UAS Pipes
    IOUSBHostPipe *                 fCommandPipe;
    IOUSBHostPipe *                 fStatusPipe;
    IOUSBHostPipe *                 fDataOutPipe;
    IOUSBHostPipe *                 fDataInPipe;
    
    // UAS Streams
    uint8_t                         fNumStreams;
    IOUSBHostStream *               fStream [ kUSBNumberOfUASPipes ] [ kMinStreamID + kUSBMaxUASQueueDepth ];
    
public:
    
    IOUSBMassStorageInterfaceNub * GetIOUSBMassStorageInterfaceNub ( void );
    
    IOReturn ResetDevice ( void );
    IOReturn WaitForTerminationGated ( void );
    IOReturn WaitForResetCompletionGated ( void );
    void Reattach ( void );
    
    void FindPipeStreams ( IOUSBHostPipe *                          hostPipe,
                           const StandardUSB::EndpointDescriptor *  endpointDescriptor,
                           UInt8                                    pipeIndex           );
    
    IOUSBHostPipe * GetInterruptPipe ( void );
    IOUSBHostPipe * GetBulkOnlyOutPipe ( void );
    IOUSBHostPipe * GetBulkOnlyInPipe ( void );
    
    IOUSBHostPipe * GetCommandPipe ( void );
    IOUSBHostPipe * GetStatusPipe ( void );
    IOUSBHostPipe * GetDataOutPipe ( void );
    IOUSBHostPipe * GetDataInPipe ( void );

    IOUSBHostStream * GetStream ( UInt8 pipeIndex, UInt8 tag );

    void ReleasePipes ( void );
    
    uint8_t GetNumberOfSupportedStreams ( void );
    IOReturn EnableStreams ( void );
    
    bool GetResetStatus ( uint64_t * timestamp = NULL );
    bool GetReattachStatus ( void );
    
    virtual bool AttachToInterimParent ( void );
    virtual bool DetachFromInterimParent ( void );
    
protected:
    
    IOReturn FindUSBPipes ( void );
    IOReturn FindUMCPipes ( void );
    IOReturn FindUASPipes ( void );
    void ResetTimeOut ( void );
    
private:
    
    static bool sCompareIOProperty ( IOService *        object,
                                     OSDictionary *     table,
                                     char *             propertyKeyName,
                                     bool *             matches          );
    
};


//==============================================================================
//
//  End Of File
//
//==============================================================================

#endif /* defined(__IOUSBMassStorageDriver__IOUSBMassStorageDriverNub__) */

