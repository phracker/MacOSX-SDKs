

//==============================================================================
//
//  IOUSBMassStorageDriver.h
//  IOUSBMassStorageDriver
//
//  Created on 02/02/15.
//  Copyright (c) 2015 Apple Inc. All rights reserved.
//
//==============================================================================


//==============================================================================
//
//  IOUSBMassStorageDriver Class
//
//==============================================================================

#ifndef __IOUSBMassStorageDriver__IOUSBMassStorageDriver__
#define __IOUSBMassStorageDriver__IOUSBMassStorageDriver__

/*!
 @header IOUSBMassStorageDriver
 @discussion This file contains definitions for the IOUSBMassStorageDriver class
 */


//==============================================================================
//
//  Includes
//
//==============================================================================

// Local includes
#include "IOUSBMassStorageInterfaceNub.h"

// USB-specific includes
#include <IOKit/usb/StandardUSB.h>
#include <IOKit/usb/IOUSBHostPipe.h>

// Generic IOKit headers
#include <IOKit/IOService.h>
#include <IOKit/IOWorkLoop.h>

// SCSI Protocol headers
#include <IOKit/scsi/IOSCSIProtocolServices.h>


//==============================================================================
//
//  Definitions
//
//==============================================================================

#define kIOPropertyIOUnitKey                "IOUnit"
#define kIOUSBMassStorageCharacteristics    "USB Mass Storage Characteristics"

//------------------------------------------------------------------------------
// Default timeout values
//------------------------------------------------------------------------------

enum
{
    kUSB1SecondInMiliSeconds        = 1000,
    kDefaultReadTimeoutDuration     = 30000,
    kDefaultWriteTimeoutDuration    = 30000
};


//==============================================================================
//
//  Constants
//
//==============================================================================

//------------------------------------------------------------------------------
// IOUSBMassStorageDriver power states.
//------------------------------------------------------------------------------

enum
{
    
    kIOUSBMassStorageDriverPowerStateOff        = 0,
    kIOUSBMassStorageDriverPowerStateOn         = 1,
    kIOUSBMassStorageDriverNumPowerStates
    
};

//------------------------------------------------------------------------------
// IOUSBMassStorageDriver default transfer counts.
//------------------------------------------------------------------------------

enum
{
    kDefaultMaximumByteCountRead            = 131072,
    kDefaultMaximumByteCountWrite           = 131072,
    kDefaultMaximumByteCountReadUSB3        = 1048576,
    kDefaultMaximumByteCountWriteUSB3       = 1048576
};

//------------------------------------------------------------------------------
// Supported USB Mass Storage subclasses.
//------------------------------------------------------------------------------

enum
{
    kUSBStorageRBCSubclass              = 1,
    kUSBStorageSFF8020iSubclass         = 2,
    kUSBStorageQIC157Subclass           = 3,
    kUSBStorageUFISubclass              = 4,
    kUSBStorageSFF8070iSubclass         = 5,
    kUSBStorageSCSITransparentSubclass  = 6
};

//------------------------------------------------------------------------------
// Supported USB Mass Storage transport protocols.
//------------------------------------------------------------------------------

enum
{
    kProtocolControlBulkInterrupt   = 0x00,
    kProtocolControlBulk            = 0x01,
    kProtocolBulkOnly               = 0x50,
    kProtocolUSBAttachedSCSI        = 0x62
};

//------------------------------------------------------------------------------
// USB Mass Storage commands.
//------------------------------------------------------------------------------

enum
{
    kUSBMassStorageBO_ReportMaxLUN  = 0xFE,
    kUSBMassStorageBO_ResetBODevice = 0xFF
};

//------------------------------------------------------------------------------
// Definitions for the Bulk Only Protocol Command Block Wrapper (CBW).
//------------------------------------------------------------------------------

enum
{
    
    // CBW general struture definitions
    kCommandBlockWrapperSignature   = OSSwapHostToBigConstInt32 ( 'USBC' ),
    kByteCountOfCBW                 = 31,
    
    // CBW LUN related definitions
    kCBWLUNMask                     = 0x0F,
    
    kCBWFlagsDataOut                = 0x00,
    kCBWFlagsDataIn                 = 0x80
    
};

//------------------------------------------------------------------------------
// Definitions for the Bulk Only Protocol Command Status Wrapper (CSW).
//------------------------------------------------------------------------------

enum
{
    
    // CSW general struture definitions
    kCommandStatusWrapperSignature  = OSSwapHostToBigConstInt32 ( 'USBS' ),
    kByteCountOfCSW                 = 13,
    
    // CSW status definitions
    kCSWCommandNoError              = 0x00, // No error occurred
    kCSWCommandFailedError          = 0x01, // An error occurred (probably a bad command or parameter )
    kCSWPhaseError                  = 0x02, // A transfer was performed in the wrong sequence
    kCSWTagError                    = 0xFF  // A transfer was performed in the wrong sequence
    
};

//------------------------------------------------------------------------------
// Definitions for booting support.
//------------------------------------------------------------------------------

enum
{
    kUSBDAddressLength = 10
};

//------------------------------------------------------------------------------
// Definitions for Bulk Only state machine.
//------------------------------------------------------------------------------

// Bulk Only State Machine States
enum
{
    
    kBulkOnlySendingCommand,
    kBulkOnlyWaitingForDataTransfer,
    kBulkOnlyWaitingForStatus,
    kBulkOnlyWaitingForStatus2ndTime,
    kBulkOnlyCheckingCBWStatus,
    kBulkOnlyCheckingBulkOnlyStall,
    kBulkOnlyClearingBulkOnlyStall,
    kBulkOnlyCheckingBulkOnlyStallPostCSW,
    kBulkOnlyWaitingForResetToComplete,
    kBulkOnlyClearingBulkIn,
    kBulkOnlyClearingBulkOut
    
};


//==============================================================================
//
//  Structures
//
//==============================================================================

//------------------------------------------------------------------------------
// Structures for the Bulk Only Protocol Command Block Wrapper (CBW)
//------------------------------------------------------------------------------

#pragma pack(push,1)

struct StorageBulkOnlyCBW
{
    UInt32      cbwSignature;
    UInt32      cbwTag;
    UInt32      cbwTransferLength;
    UInt8       cbwFlags;
    UInt8       cbwLUN;                 // Bits 0-3: LUN, 4-7: Reserved
    UInt8       cbwCDBLength;           // Bits 0-4: CDB Length, 5-7: Reserved
    UInt8       cbwCDB[16];
};
typedef struct      StorageBulkOnlyCBW      StorageBulkOnlyCBW;

struct StorageBulkOnlyCSW
{
    UInt32      cswSignature;
    UInt32      cswTag;
    UInt32      cswDataResidue;
    UInt8       cswStatus;
};
typedef struct      StorageBulkOnlyCSW      StorageBulkOnlyCSW;

struct BulkOnlyRequestBlock
{
    SCSITaskIdentifier      request;
    IOUSBHostCompletion     boCompletion;
    UInt32                  currentState;
    StorageBulkOnlyCBW      boCBW;
    StorageBulkOnlyCSW      boCSW;
    IOMemoryDescriptor *    boPhaseDesc;
    UInt8                   boGetStatusBuffer[2];   // 2 bytes as specified in the USB spec
};
typedef struct      BulkOnlyRequestBlock    BulkOnlyRequestBlock;

#pragma pack(pop)


//==============================================================================
//
//  Forward Declarations
//
//==============================================================================

class   IOUSBMassStorageDriverNub;


//==============================================================================
//
//  Class Declaration
//
//==============================================================================

class IOUSBMassStorageDriver : public IOSCSIProtocolServices
{
    
    OSDeclareDefaultStructors ( IOUSBMassStorageDriver )
    
public:
    
    /*! @function init
     @abstract IOService init() method subclass.
     Initializes generic IOService data structures.
     @discussion See IOService.h for details.
     */
    
    virtual bool init ( OSDictionary * dictionary = 0 ) override;
    
    /*! @function attach
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
    
    /*! @function open
     @abstract IOService open() method subclass.
     Requests active access to a provider.
     @discussion See IOService.h for details.
     @param forClient Designates the client of the provider requesting the open.
     @param options Options for the open. The provider family may implement
     options for open; IOService defines only <code>kIOServiceSeize</code> to
     request the device be withdrawn from its current owner.
     @result <code>true</code> if the open was successful; <code>false</code>
     otherwise. */
    
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
    
    /*! @function terminate
     @abstract IOService terminate() method subclass.
     Makes an IOService object inactive and begins its destruction.
     @discussion See IOService.h for details.
     */
    
    virtual bool terminate ( IOOptionBits options = 0 ) override;
    
    /*! @function willTerminate
     @abstract IOService willTerminate() method subclass.
     Passes a termination up the stack.
     @discussion See IOService.h for details.
     @param provider The terminated provider of this object.
     @param options Options originally passed to terminate.
     @result <code>true</code>.
     */
    
    virtual bool willTerminate ( IOService *    provider,
                                 IOOptionBits   options   ) override;
    
    /*! @function free
     @abstract IOService free() method subclass.
     Frees data structures that were allocated when power management was
     initialized on this service.
     @discussion See IOService.h for details.
     */
    
    virtual void free ( void ) override;
    
protected:
    
    /*!
     @function SendSCSICommand
     @abstract IOSCSIProtocolServices method used to send SCSITasks on the wire.
     @discussion See IOSCSIProtocolServices.h for details.
     @param request A valid SCSITaskIdentifier representing the command to send
     on the wire.
     @param serviceResponse Pointer to a SCSIServiceResponse value returned to
     the caller.
     @param taskStatus Pointer to a SCSITaskStatus value returned to the caller.
     @result False if no more commands can be processed at this time, otherwise
     true.
     */
    
    virtual bool SendSCSICommand ( SCSITaskIdentifier       request,
                                   SCSIServiceResponse *    serviceResponse,
                                   SCSITaskStatus *         taskStatus       ) override;
    
    /*!
     @function AbortSCSICommand
     @abstract IOSCSIProtocolServices method used to abort SCSITasks.
     @discussion See IOSCSIProtocolServices.h for details.
     @param request A valid SCSITaskIdentifier representing the command to be
     aborted.
     @result A valid SCSIServiceResponse.
     */
    
    virtual SCSIServiceResponse AbortSCSICommand ( SCSITaskIdentifier request ) override;
    
    /*!
     @function InitializePowerManagement
     @abstract Subclasses call this method to initialize power management.
     @discussion Subclasses call this method to initialize power management.
     In the protocol services layer, this method calls the protocol interface layer
     to initialize power management state variables and then registers the protocol
     layer driver with the power manager with two(2) states, ON and OFF. Subclasses may
     override this behavior.
     @param provider The provider to be joined to in the power management tree.
     */
    virtual void InitializePowerManagement ( IOService * provider ) override;
    
    /*!
     @function HandlePowerChange
     @abstract The HandlePowerChange method is pure virtual and is left to each protocol or
     application layer driver to implement. It is guaranteed to be called on its
     own thread of execution and can make synchronous or asynchronous calls.
     @discussion The HandlePowerChange method is pure virtual and is left to each protocol or
     application layer driver to implement. It is guaranteed to be called on its
     own thread of execution and can make synchronous or asynchronous calls.
     Subclasses must override this method. Third party subclasses shouldn't need to override
     this method but can to alter the default behavior.
     */
    
    virtual void HandlePowerChange ( void ) override;
    
public:
    
    /*!
     @function IsProtocolServiceSupported
     @abstract IOSCSIProtocolServices method used to return true if the
     specified feature is supported by the protocol layer.
     @discussion See IOSCSIProtocolServices.h for details.
     @param feature A valid SCSIProtocolFeature.
     @param serviceValue A pointer to a value for the protocol feature.
     @result True if the requested service is supported, otherwise false.
     */
    
    virtual bool IsProtocolServiceSupported ( SCSIProtocolFeature   feature,
                                              void *                serviceValue ) override;
    
    /*!
     @function HandleProtocolServiceFeature
     @abstract IOSCSIProtocolServices method used to instruct the Protocol
     Services driver to perform the necessary tasks for the indicated feature.
     @discussion See IOSCSIProtocolServices.h for details.
     @param feature A valid SCSIProtocolFeature.
     @param serviceValue A pointer to a value for the protocol feature.
     @result True if successful, otherwise false.
     */
    
    virtual bool HandleProtocolServiceFeature ( SCSIProtocolFeature     feature,
                                                void *                  serviceValue ) override;
    
protected:
    
    bool                        fInitialized;
    bool                        fTerminated;
    IOUSBMassStorageDriverNub * fIOUSBMassStorageDriverNub;
    IOWorkLoop *                fWorkLoop;
    thread_call_t               fResetDeviceThread;
    uint8_t                     fConsecutiveResetCount;
    
    UInt32                      fRequiredMaxBusStall;
    
    IOMemoryDescriptor *        fBulkOnlyCBWMemoryDescriptor;
    IOMemoryDescriptor *        fBulkOnlyCSWMemoryDescriptor;
    
    const StandardUSB::InterfaceDescriptor *    fInterfaceDescriptor;
    
    IOUSBHostPipe *             fPotentiallyStalledPipe;
    
private:
    
    BulkOnlyRequestBlock        fBulkOnlyCommandRequestBlock;
    bool                        fBulkOnlyCommandRequestInUse;
    UInt8                       fMaxLogicalUnitNumber;
    StandardUSB::DeviceRequest  fUSBDeviceRequest;
    
    OSSet *                     fClients;
    
    UInt8                       fPreferredSubclass;
    UInt8                       fPreferredProtocol;
    bool                        fKnownCSWTagMismatchIssues;
    bool                        fUseStandardUSBReset;
    bool                        fPortSuspendResumeForPMEnabled;
    bool                        fAutonomousSpinDownWorkAround;
    UInt32                      fPostDeviceResetCoolDownInterval;
    UInt64                      fUSBMassStorageTraceID;
    
public:
    
    void ResetDeviceAsync ( void );
    void ResetDevice ( void );
    
protected:
    
    IOUSBMassStorageInterfaceNub * GetIOUSBMassStorageInterfaceNub ( void );
    IOUSBHostInterface * GetIOUSBHostInterface ( void );
    IOUSBHostDevice * GetIOUSBHostDevice ( void );
    IOUSBHostPipe * GetBulkOnlyOutPipe ( void );
    IOUSBHostPipe * GetBulkOnlyInPipe ( void );
    virtual void BeginProvidedServices ( void );
    void AcceptSCSITaskGated ( bool * accepted );
    virtual void CompleteSCSICommand ( SCSITaskIdentifier   request,
                                       IOReturn             status   );
    void CompleteSCSICommandGated ( SCSITaskIdentifier      request,
                                    SCSIServiceResponse *   serviceResponse,
                                    SCSITaskStatus *        taskStatus       );
    void AbortCurrentSCSITask ( void );
    virtual IOReturn GetEndpointStatus ( IOUSBHostPipe *        thePipe,
                                         void *                 endpointStatus,
                                         IOUSBHostCompletion *  completion      );
    IOReturn ClearFeatureEndpointStall ( IOUSBHostPipe *        thePipe );
    IOReturn ClearPipeStall ( bool flags );
    void WaitForCommandCompletionGated ( void );
    
protected:
    
    UInt32      fBulkOnlyCommandTag;
    
    virtual IOReturn SendSCSICommandForBulkOnlyProtocol ( SCSITaskIdentifier request );
    
    void BulkOnlyUSBCompletion ( void *     parameter,
                                 IOReturn   status,
                                 uint32_t   bytesTransferred );
    IOReturn BulkOnlySendCBWPacket ( BulkOnlyRequestBlock *     boRequestBlock,
                                     UInt32                     nextExecutionState );
    IOReturn BulkOnlyTransferData ( BulkOnlyRequestBlock *  boRequestBlock,
                                    UInt32                  nextExecutionState );
    IOReturn BulkOnlyReceiveCSWPacket ( BulkOnlyRequestBlock *  boRequestBlock,
                                        UInt32                  nextExecutionState );
    IOReturn ResetBulkOnlyDevice ( BulkOnlyRequestBlock *   boRequestBlock,
                                   UInt32                   nextExecutionState );
    
};


//==============================================================================
//
//  End Of File
//
//==============================================================================

#endif /* defined(__IOUSBMassStorageDriver__IOUSBMassStorageDriver__) */

