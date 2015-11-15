

//==============================================================================
//
//  IOUSBMassStorageInterfaceNub.h
//  IOUSBMassStorageDriver
//
//  Created on 02/02/15.
//  Copyright (c) 2015 Apple Inc. All rights reserved.
//
//==============================================================================


//==============================================================================
//
//  IOUSBMassStorageInterfaceNub Class
//
//==============================================================================

#ifndef __IOUSBMassStorageDriver__IOUSBMassStorageInterfaceNub__
#define __IOUSBMassStorageDriver__IOUSBMassStorageInterfaceNub__

/*!
 @header IOUSBMassStorageInterfaceNub
 @discussion This file contains definitions for the IOUSBMassStorageInterfaceNub
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


//==============================================================================
//
//  Definitions
//
//==============================================================================

#define kUSBMassStorageTraceID  "USB Mass Storage Trace ID"

//==============================================================================
//
//  Constants
//
//==============================================================================

enum
{
    
    kUSBMassStorageInterfaceNubPowerStateOff    = 0,
    kUSBMassStorageInterfaceNubPowerStateOn     = 1,
    kUSBMassStorageInterfaceNubNumPowerStates
    
};


//==============================================================================
//
//  Forward Declarations
//
//==============================================================================

class   IOUSBHostInterface;
class   IOUSBMassStorageDriverNub;


//==============================================================================
//
//  Class Declaration
//
//==============================================================================

class IOUSBMassStorageInterfaceNub : public IOService
{
    
    OSDeclareDefaultStructors ( IOUSBMassStorageInterfaceNub )
    
public:
    
    /*! @function probe
     @abstract IOService probe() method subclass.
     During an IOService object's instantiation, probes a matched service to see
     if it can be used.
     @discussion See IOService.h for details.
     @param provider The registered IOService object that matches a driver
     personality's matching dictionary.
     @param score Pointer to the current driver's probe score, which is used to
     order multiple matching drivers in the same match category. It defaults to
     the value of the <code>IOProbeScore</code> property in the drivers property
     table, or <code>kIODefaultProbeScore</code> if none is specified. The
     <code>probe</code> method may alter the score to affect start order.
     @result An IOService instance or zero when the probe is unsuccessful. In
     almost all cases the value of <code>this</code> is returned on success. If
     another IOService object is returned, the probed instance is detached and
     freed, and the returned instance is used in its stead for
     <code>start</code>.
     */
    
    virtual IOService * probe ( IOService * provider, SInt32 * score ) override;
    
    /*!
     @function start
     @abstract IOService start() method subclass.
     Called during an the object's instantiation. It starts the IOService object
     that has been selected to run on the provider.
     @discussion See IOService.h for details.
     @result <code>true</code> if the start was successful; <code>false</code>
     otherwise (which will cause the instance to be detached and usually freed).
     */
    
    virtual bool start ( IOService * provider ) override;
    
    /*!
     @function stop
     @abstract IOService stop() method subclass.
     Called before object is detached & it is destroyed.
     @discussion See IOService.h for details.
     */
    
    virtual void stop ( IOService * provider ) override;
    
    /*! @function terminate
     @abstract IOService terminate() method subclass.
     Makes an IOService object inactive and begins its destruction.
     @discussion See IOService.h for details.
     */
    
    virtual bool terminate ( IOOptionBits options = 0 ) override;
    
    /*! @function open
     @abstract IOService open() method subclass.
     Requests active access to a provider.
     @discussion See IOService.h for details.
     @param forClient Designates the client of the provider requesting the open.
     @param options Options for the open. The provider family may implement
     options for open; IOService defines only <code>kIOServiceSeize</code> to
     request the device be withdrawn from its current owner.
     @result <code>true</code> if the open was successful; <code>false</code>
     otherwise.
     */
    
    virtual bool open ( IOService *     forClient,
                       IOOptionBits    options = 0,
                       void *          arg = 0      ) override;
    
    /*! @function handleOpen
     @abstract IOService handleOpen() method subclass.
     @discussion See IOService.h for details.
     @param forClient Designates the client of the provider requesting the open.
     @param options Options for the open, may be interpreted by the implementor
     of <code>handleOpen</code>.
     @result <code>true</code>if the open was successful; <code>false</code>
     otherwise.
     */
    
    virtual bool handleOpen ( IOService *       forClient,
                              IOOptionBits      options,
                              void *            arg        ) override;
    
    /*! @function close
     @abstract IOService close() method subclass.
     Releases active access to a provider.
     @discussion See IOService.h for details.
     @param forClient Designates the client of the provider requesting the
     close.
     @param options Options available for the close. The provider family may
     implement options for close; IOService defines none.
     @param arg Family specific arguments which are ignored by IOService.
     */
    
    virtual void close ( IOService *        forClient,
                         IOOptionBits       options = 0 ) override;
    
    /*! @function handleClose
     @abstract IOService handleClose() method subclass.
     @discussion See IOService.h for details.
     @param forClient Designates the client of the provider requesting the
     close.
     @param options Options for the close, may be interpreted by the implementor
     of @link handleOpen handleOpen@/link.
     */
    
    virtual void handleClose ( IOService *      client,
                               IOOptionBits     options ) override;
    
    /*! @function free
     @abstract IOService free() method subclass.
     Frees data structures that were allocated when power management was
     initialized on this service.
     @discussion See IOService.h for details.
     */
    
    virtual void free ( void ) override;
    
    /*!
     @function matchPropertyTable
     @abstract Allows a registered IOService object to implement family specific matching.
     @discussion All matching on an IOService object will call this method to allow a family writer to implement matching in addition to the generic methods provided by IOService. The implementer should examine the matching dictionary passed to see if it contains properties the family understands for matching, and use them to match with the IOService object if so. Note that since matching is also carried out by other parts of the I/O Kit, the matching dictionary may contain properties the family does not understand - these should not be considered matching failures.
     @param table The dictionary of properties to be matched against.
     @param score Pointer to the current driver's probe score, which is used to order multiple matching drivers in the same match category. It defaults to the value of the <code>IOProbeScore</code> property in the drivers property table, or <code>kIODefaultProbeScore</code> if none is specified.
     @result <code>false</code> if the family considers the matching dictionary does not match in properties it understands; <code>true</code> otherwise. */
    
    virtual bool matchPropertyTable ( OSDictionary *    table,
                                      SInt32 *          score  ) override;
    
protected:
    
    bool IsUSBHostDeviceInternal ( void );
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
    
protected:
    
    u_int64_t       fUSBMassStorageTraceID;
    
    // Device information
    OSDictionary *  fDeviceInfo;
    u_int32_t       fLocationID;
    u_int16_t       fVendorID;
    u_int16_t       fProductID;
    u_int16_t       fDeviceIDBCD;
    u_int8_t        fInterfaceClass;
    u_int8_t        fDeviceSubClass;
    u_int8_t        fDeviceProtocol;
    u_int8_t        fNumConfigurations;
    u_int8_t        fCurrentConfiguration;
    u_int8_t        fInterfaceNumber;
    char            fUSBVendorString [ 256 ];
    char            fUSBProductString [ 256 ];
    char            fUSBSerialNumberString [ 256 ];
    
    bool                        fInitialized;
    bool                        fTerminated;
    
    IOUSBMassStorageDriverNub * fIOUSBMassStorageDriverNub;
    IOUSBHostInterface *        fIOUSBHostInterface;
    
    unsigned long               fProposedPowerState;
    unsigned long               fCurrentPowerState;
    bool                        fWaitingForPMTransition;
    
    u_int32_t                   fResetCount;
    
    bool                        fDissallowUASP;
    
    /*! @function CheckForAndEnableUAS
     @abstract Enables UASP if supported.
     @discussion Looks for an alternate interface which supports the UASP protocol. If 
     found that alternate interface gets set.
     */
    
    virtual void            CheckForAndEnableUAS ( void );
    
public:
    
    IOUSBHostInterface *    GetIOUSBHostInterface ( void );
    void                    ClampPowerState ( unsigned long newLevel );
    
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

#endif /* defined(__IOUSBMassStorageDriver__IOUSBMassStorageInterfaceNub__) */

