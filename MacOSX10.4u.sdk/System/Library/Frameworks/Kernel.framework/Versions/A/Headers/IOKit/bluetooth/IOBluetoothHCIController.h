/*
	File:		IOBluetoothHCIController.h
	Contains:	Bluetooth HCI Transport base class.
	Copyright:	© 2002 by Apple Computer, Inc. All rights reserved.
*/


#pragma once

//====================================================================================================
// Imports
//====================================================================================================

#import <IOKit/IOService.h>
#import <IOKit/system.h>
#import <IOKit/system.h>
#import <kern/thread_call.h>

#include <IOKit/pwr_mgt/RootDomain.h>

#import <IOKit/bluetooth/Bluetooth.h>

#import <IOKit/bluetooth/IOBluetoothTypes.h>
#import <IOKit/bluetooth/IOBluetoothInternal.h>

//====================================================================================================
// Forward declarations
//====================================================================================================

class OSSet;
class IOWorkLoop;
class IOCommandGate;
class IOWorkQueue;
class IOBluetoothDevice;
class IOBluetoothHCIRequest;
class IOBluetoothHCIController;
class IOBluetoothACLMemoryDescriptor;
class IOTimerEventSource;
class IOBluetoothInactivityTimerEventSource;

//====================================================================================================
// defines, typdefs, etc.
//====================================================================================================

#define kNoReturnParam					NULL

typedef UInt32 HCIDataHandlerType;
enum HCIDataHandlerTypes
{
	kTransportDataTypeHCIEvents,
	kTransportDataTypeACL,
	kTransportDataTypeSCO
};

typedef IOReturn (*IOBluetoothIncomingDataAction) ( IOBluetoothHCIController *hciController,  UInt8 *inDataPtr, UInt32 inDataSize, UInt32 inSequenceNumber );
typedef IOReturn (*IOBluetoothHCIControllerDataHandler) ( void * contextPtr, const UInt8 * data, UInt32 dataSize );

typedef struct HCIDataHandler	HCIDataHandler;
struct HCIDataHandler
{
	IOBluetoothHCIControllerDataHandler		procPtr;
	void * 									contextPtr;
};

typedef struct HCIEventNotificationListener	HCIEventNotificationListener;
struct HCIEventNotificationListener
{
	task_t				owningTask;		// Used to ID these things when adding/removing them from our listener pool.
	mach_port_t			port;			// Mach port to send out the notificaton.
	void * 				refCon;			// RefCon for the port's use.
};

#define POWER_STATE_CHANGE_IN_PROGRESS()	( mCurrentInternalPowerState != mPendingInternalPowerState )
#define	IS_POWERING_DOWN()	( POWER_STATE_CHANGE_IN_PROGRESS() && ( mPendingInternalPowerState == kIOBluetoothHCIControllerInternalPowerStateOff ) )


//====================================================================================================
// Callback structure for data:
//====================================================================================================

typedef struct SendDataContext
{
	// Data sent:
	IOMemoryDescriptor *memoryDescriptorPointer;
	
	// Referece to the device that sent the data:
	IOBluetoothDevice *devicePointer;
	void *devicePointerContextInfo0;
	void *devicePointerContextInfo1;
	
	// And the controller that received it:
	IOBluetoothHCIController *hciController;
	void *controllerPointerContextInfo0;
	void *controllerPointerContextInfo1;
	
	// ReturnValue:
	IOReturn sendingWasSuccessful;
} SendDataContext;

//====================================================================================================
// IOBluetoothHCIController
//====================================================================================================

class IOBluetoothHCIController : public IOService
{
	// We don't make many friends, but at least we have a few...

    friend class IOBluetoothHCIPacketLogUserClient;
    friend class IOBluetoothSerialManager;
    friend class IOBluetoothHCIUserClient;
    friend class IOBluetoothDevice;
    
	// IOKit stuff.
	
    OSDeclareDefaultStructors( IOBluetoothHCIController )

protected:

	IOWorkLoop *					mWorkLoop;
	IOCommandGate *					mCommandGate;
	IOWorkQueue *					mWorkQueue;
	IOTimerEventSource *			mTimerEventSource;
	Boolean							mShouldRunInactivityTimer;
	
	// Data and request queue stuff.
	
	HCIEventNotificationListener*	mHCIEventListenersList;
	size_t							mHCIEventListenersListSize;
 	HCIDataHandler*					mHCIEventDataHandlerList;
	size_t							mHCIEventDataHandlerListSize;
	HCIDataHandler*					mACLDataHandlerList;
	size_t							mACLDataHandlerListSize;
	HCIDataHandler*					mSCODataHandlerList;
	size_t							mSCODataHandlerListSize;
	
	IOBluetoothHCIRequest *	 		mBusyQueueHead;
	IOBluetoothHCIRequest *	 		mWaitQueueHead;
	IOBluetoothHCIRequest **		mHCIRequestList;

    IOBluetoothDevice *				mDeviceListHead;
	
	OSSet *							mPacketLogClients;
	UInt8 *							mPacketLogBuffer;
	UInt32							mPacketLogBufferSize;
   
	uint8_t *						mEventDataBuffer;			// Events without matching requests will use this.
	size_t							mEventDataBufferSize;
	
    // This keeps track of the ACL packets we actually sent:
    BluetoothHCIBufferSize			mHCIBufferSize;
    UInt16							mNumOutstandingACLPackets;
    
    OSArray *						mAllowedIncomingL2CAPChannels;
    
    UInt32							mNextAvailableSequenceNumber;
    UInt32							mCurrentlyExecutingSequenceNumber;
    UInt16							mActiveConnections;
	
	// Packet Queue description:
	typedef struct QueuePacketHolder {
		IOMemoryDescriptor								*memDescriptor;	// The data we need to send
		SendDataContext *								contextPtr;		// Context pointer for the sent data.
		IOBluetoothDevice *								inTargetDevice;	// The device that enqueued the data.
		struct QueuePacketHolder						*next;			// The next block in the queue.
	} QueuePacketHolder;
    QueuePacketHolder *mACLQueueHead, *mACLQueueTail;
	
	// Counters to limit the number of packets in the queue (we do not want to go out of memory)
	UInt32 mNumberOfPacketsInQueue;

	// The allowed RFCOMM channels
    OSArray *mAllowedIncomingRFCOMMChannels;
    
	IOBluetoothHCIControllerInternalPowerState	mCurrentInternalPowerState;
	IOBluetoothHCIControllerInternalPowerState	mPendingInternalPowerState;
	Boolean										mAsyncPowerStateChangeInProgress;
	UInt32										mPendingPowerStateChangeOptions;
	IOBluetoothHCIControllerPowerOptions		mControllerPowerOptions;
	Boolean										mIgnorePowerStateChanges;
	
	Boolean										mHardwareSetupComplete;
	
	IOBluetoothHCIControllerConfigState		mControllerConfigState;
	IOBluetoothHCIControllerConfigState		mPreviousControllerConfigState;
	
	IOBluetoothHCIControllerFeatureFlags	mControllerFeatureFlags;

	// Overrides.

	bool 				start( IOService * provider );

	bool		 		init( OSDictionary* dictionary );

    virtual void		free();
    
    static IOReturn		initHardwareAction(	OSObject	*owner,
                                            void		*arg1,
                                            void		*arg2,
                                            void		*arg3,
                                            void		*arg4 );
                                            
    virtual bool		initHardware( IOService * provider );
	
    static IOReturn		setupHardwareAction(	OSObject	*owner,
												void		*arg1,
												void		*arg2,
												void		*arg3,
												void		*arg4 );
                                                    
	virtual IOReturn	setupHardware( IOService* provider );

    virtual void		hardwareSetupComplete( IOReturn status );
    
	virtual	void		setConfigState( IOBluetoothHCIControllerConfigState configState );

#if !(defined(__ppc__) && defined(KPI_10_4_0_PPC_COMPAT))
	virtual	bool		terminate( IOOptionBits options = 0 );
#endif

	virtual bool		willTerminate( IOService * provider, IOOptionBits options );

#if !(defined(__ppc__) && defined(KPI_10_4_0_PPC_COMPAT))
	virtual bool		didTerminate( IOService * provider, IOOptionBits options, bool * defer );
#endif
	
	void 				stop( IOService * provider );
	
	IOReturn			newUserClient(	task_t 				owningTask,
										void *				securityID,
										UInt32 				type,
										IOUserClient **		handler );
	
	uint32_t			CountExistingHCIControllers();


	// Our protected custom stuff.
	
    static IOReturn		DetachUserClientsAction(	OSObject *owner,
                                                    void *arg1,
                                                    void *arg2,
                                                    void *arg3,
                                                    void *arg4 );

    virtual void		DetachUserClients();
	
    static IOReturn		setPropertiesAction( OSObject	*owner, 
                                             void		*arg1, 
                                             void		*arg2, 
                                             void		*arg3, 
                                             void		*arg4 );
                                            
    virtual IOReturn	setPropertiesWL( OSObject * properties );

    static IOReturn		AddPacketLogUserClientAction(	OSObject *owner, 
                                                        void *arg1, 
                                                        void *arg2, 
                                                        void *arg3, 
                                                        void *arg4 );

    virtual IOReturn	AddPacketLogUserClient( IOBluetoothHCIPacketLogUserClient *newPacketLogUserClient );

    virtual void		PacketLogClientClosed( IOBluetoothHCIPacketLogUserClient *packetLogClient );
	
    virtual void		LogPacket( UInt8 packetType, void *packetData, UInt32 packetSize );

	virtual	void		DesyncIncomingData( IOBluetoothIncomingDataAction action, UInt8 *inDataPtr, UInt32 inDataSize );
    
	static	void		DesyncIncomingDataAction( IOBluetoothHCIController *hciController, IOBluetoothIncomingDataAction action, void *inDataPtr, UInt32 inDataSize, UInt32 sequenceNumber );
	
    virtual void		SynchronizePacketSequence( UInt32 sequenceNumber );
    
    virtual IOReturn	AddDevice( IOBluetoothDevice *inDevice );
    
    virtual IOReturn	RemoveDevice( IOBluetoothDevice *inDevice );
    
    virtual IOReturn	CreateDeviceFromConnectionResults( BluetoothHCIEventConnectionCompleteResults *connectionResults );
    
    virtual IOReturn	DestroyDeviceWithDisconnectionResults( BluetoothHCIEventDisconnectionCompleteResults *disconnectionResults );
    
    virtual IOReturn	DestroyDevice( IOBluetoothDevice *inDevice );
    
    virtual IOReturn	DestroyAllDevices();

    virtual void		FlushDeviceACLPackets( IOBluetoothDevice *inDevice );
    
    virtual void		DecrementOutstandingACLPackets( UInt16 delta );
    
    virtual void		ProcessFlushOccurredEvent( BluetoothHCIEventFlushOccurredResults *inFlushResults );
    
    virtual void		ProcessNumCompletedPacketsEvent( UInt8 *inDataPtr );
    
    virtual void		ProcessHCIControllerResetEvent();
    
    virtual IOReturn	DispatchIncomingACLData( UInt8 *inDataPtr, UInt32 inDataSize );

	// Common methods for L2CAP and RFCOMM channel managment:
	virtual void		MergeChannelDescription(OSDictionary *destination , OSDictionary *source);
	virtual void		RemoveChannelRestrictions(OSDictionary *toChange , OSDictionary *removeRule, const char *key);
	virtual Boolean		IsAllowedDevice(OSDictionary *description , IOBluetoothDevice *device);
	virtual void		RemoveAllRules();

	// L2CAP channel managment methods:
    virtual void		RemoveAllowedIncomingL2CAPChannel( OSObject *channelID );
	virtual IOReturn 	AddAllowedIncomingL2CAPChannel( OSDictionary *channelDescription );
	virtual OSDictionary *GetIncomingL2CAPChannelDescription( OSNumber *psmNumber );

	// L2CAP channel accessory methods:
    virtual void		AddAllowedIncomingL2CAPChannel( BluetoothL2CAPPSM incomingPSM );
    virtual void		AddAllowedIncomingL2CAPChannel( OSNumber *psmNumber );
    virtual void 		RemoveAllowedIncomingL2CAPChannel( BluetoothL2CAPPSM incomingPSM );

	// RFCOMM channel managment methods:
	virtual OSDictionary *GetIncomingRFCOMMChannelDescription( OSNumber *channelIDNumber );
	virtual IOReturn 	AddAllowedIncomingRFCOMMChannel( OSDictionary *channelDescription );
    virtual void		RemoveAllowedIncomingRFCOMMChannel( OSObject *channelID );

	// RFCOMM channel accessory methods:
    virtual void		AddAllowedIncomingRFCOMMChannel( BluetoothRFCOMMChannelID incomingChannelID );
    virtual void		AddAllowedIncomingRFCOMMChannel( OSNumber *channelIDNumber );
    virtual void		AddSecureIncomingRFCOMMChannel( BluetoothRFCOMMChannelID incomingChannelID );
    virtual void		AddSecureIncomingRFCOMMChannel( OSNumber *channelIDNumber );
    virtual void 		RemoveAllowedIncomingRFCOMMChannel( BluetoothRFCOMMChannelID incomingChannelID );
		
	virtual IOReturn	TransferACLPacketToHW(IOMemoryDescriptor *memDescriptor,
													SendDataContext *								contextPtr);
	
	// ACL Packet queue:
	virtual IOReturn	EnqueuePacket(	IOMemoryDescriptor	*memDescriptor,
										SendDataContext		*contextPtr,
										IOBluetoothDevice	*inTargetDevice);
										
	virtual IOReturn	DequeuePacket();
	
	virtual IOReturn	RemoveAllPacketsBelongingTo(IOBluetoothDevice	*inTargetDevice);

public:

    // IOWorkLoop and IOCommandGate accessors
    
    virtual IOWorkLoop *getWorkLoop() const;
    
    virtual IOCommandGate *getCommandGate() const;
    
    virtual IOReturn setProperties( OSObject * properties );

	// Subclasses must implement these for it to be a working transport
	// in the Bluetooth Family world.
	
	virtual	IOReturn	SendHCIRequest(	UInt8 * 					buffer,
										IOByteCount					bufferSize  );

	static	IOReturn	SendACLCompletedAction ( OSObject *owner, void *arg1, void *arg2, void *arg3, void *arg4, void *arg5, void *arg6 );
	
	virtual	void		SendACLCompleted(	SendDataContext	*contextPtr);
		
	virtual	IOReturn	SendACLData(	IOMemoryDescriptor						*memDescriptor,
										SendDataContext *						contextPtr  );

	virtual	IOReturn	GetTransportInfo( BluetoothTransportInfo *	infoStruct );
	
	static	IOReturn	SendSCOCompletedAction ( OSObject *owner, void *arg1, void *arg2, void *arg3, void *arg4, void *arg5, void *arg6 );
	
	// Override to do something custom with the data. Otherwise, the registered data handler
	// will get a peek at it.
	
    // The ProcessXXXData() functions are safe to be called from anywhere.
    // They call ProcessXXXDataWL() on the workloop using ProcessXXXDataAction()
    
	virtual	void	 	ProcessEventData( UInt8 * inDataPtr, UInt32 inDataSize );
		
	virtual	void	 	ProcessACLData( UInt8 * data, UInt32 dataSize );
	
	virtual	void	 	ProcessSCOData( UInt8 * data, UInt32 dataSize, UInt32 inMissingData, AbsoluteTime inTimestamp, Boolean copyData );
    
	virtual	void	 	ProcessEventDataWL( UInt8 * inDataPtr, UInt32 inDataSize, UInt32 sequenceNumber );
		
	virtual	void	 	ProcessACLDataWL( UInt8 * data, UInt32 dataSize, UInt32 sequenceNumber );
	
	virtual	void	 	ProcessSCODataWL( UInt8 * data, UInt32 dataSize, UInt32 inMissingData, AbsoluteTime inTimestamp, Boolean copyData );
    
	static	IOReturn	ProcessEventDataAction( IOBluetoothHCIController *	hciController,
												UInt8 *						incomingDataPtr,
												UInt32						inDataSize,
												UInt32						inSequenceNumber );
		
	static	IOReturn	ProcessACLDataAction(	IOBluetoothHCIController *	hciController,
												UInt8 *						incomingDataPtr,
												UInt32						inDataSize,
												UInt32						inSequenceNumber );
	
	// The following is only a "ghost" call and exists only to make the compiler happy, its implementation 
	// does not do anything.
	static	IOReturn	ProcessSCODataAction( IOBluetoothHCIController *	hciController,
												UInt8 *						incomingDataPtr,
												UInt32						inDataSize,
												UInt32						inMissingData,
												UInt32						inTimestampHi,
												UInt32						inTimestampLo,
												Boolean						inCopyData );
												
	static	IOReturn	ProcessSCODataActionAT( IOBluetoothHCIController *	hciController,
												UInt8 *						incomingDataPtr,
												UInt32						inDataSize,
												UInt32						inMissingData,
												AbsoluteTime*				inTimestamp,
												Boolean						inCopyData );

	// Data processing helpers.

    virtual bool		GetCompleteCodeForCommand(	BluetoothHCICommandOpCode	inOpCode,
                                                    BluetoothHCIEventCode		*outEventCode );
                                                    
	virtual	bool		GetOpCodeAndEventCode(	UInt8 * 						inDataPtr,
												BluetoothHCICommandOpCode * 	outOpCode,
												BluetoothHCIEventCode * 		eventCode,
                                                BluetoothHCIEventStatus *		outStatus,
                                                BluetoothDeviceAddress *		outDeviceAddress,
                                                BluetoothConnectionHandle *		outConnectionHandle );
									
	virtual	IOReturn	FindConnectionCompleteType( BluetoothHCICommandOpCode *		outOpCode );
													
	virtual	IOReturn	HandleSpecialOpcodes( BluetoothHCICommandOpCode opCode );

	// This is a hook for other interested parties to get HCI event notifications. When a user client is created,
	// that mach_port_t will be passed on to us via these calls so that their port will get HCI events that aren't
	// specifically tied to a requst object, but occur due to requests they make.
	
	virtual	IOReturn	AddHCIEventNotification( task_t inOwningTask, mach_port_t inPort, void * refCon );
	
	virtual	void		BroadcastEventNotification(	BluetoothHCIRequestID		inID,
													BluetoothHCIEventCode		inEventCode,
													IOReturn					eventStatus,
													UInt8 *						inDataToSendPtr, 
													IOByteCount 				inDataSize,
                                                    BluetoothHCICommandOpCode	inOpCode );
												
	virtual void		BroadcastConfigStateChangeNotification(	IOBluetoothHCIControllerConfigState oldState,
																IOBluetoothHCIControllerConfigState newState );
																
	virtual IOReturn	RemoveHCIEventNotification( task_t inOwningTask );

	// This is a hook for other interested parties to get data from transports. They will register itself
	// with these to receive the raw data from the transport, bypassing HCI code.
	
	virtual	IOReturn	AddDataClient(	HCIDataHandlerType		 			inType,
										IOBluetoothHCIControllerDataHandler inProcPtr,
										void * 								inContextPtr );
										
	virtual IOReturn	NotifyDataClients( HCIDataHandlerType inType, UInt8 * inDataPtr, UInt32 inDataSize );
	
	virtual IOReturn	RemoveDataClient( HCIDataHandlerType inType, IOBluetoothHCIControllerDataHandler inProcPtr );

	// Request creation, deletion and other data processing stuff.

	virtual	IOReturn 	HCIRequestCreate(	BluetoothHCIRequestID * 			outRequestID,
											bool 								inDoAsyncNotify 	= TRUE,
											UInt32 								inTimeout 			= 5,
											BluetoothHCIRequestCallbackInfo * 	inCallbackInfo 		= NULL,
											task_t								inTaskID			= 0,
											UInt32								inControlFlags		= 0 );
											
	virtual	IOReturn	HCIRequestDelete( task_t inTask, BluetoothHCIRequestID inID );
	
	virtual	IOReturn 	LookupRequest( BluetoothHCIRequestID inID, IOBluetoothHCIRequest ** outRequestPtr );

    virtual IOReturn	PrepareRequestForNewCommand(	BluetoothHCIRequestID			inID,
                                                        const BluetoothDeviceAddress *	inDeviceAddress,
                                                        BluetoothConnectionHandle		inConnectionHandle );
                                                        
	virtual	IOReturn	EnqueueRequest( IOBluetoothHCIRequest * inRequestPtr );

	virtual	IOReturn	FindQueuedRequest(	BluetoothHCICommandOpCode	opCode,
                                            BluetoothDeviceAddress *	inDeviceAddress,
                                            BluetoothConnectionHandle	inConnectionHandle,
                                            Boolean						inUseAttributes,
                                            IOBluetoothHCIRequest **	outRequestPtr );

	virtual	IOReturn	DequeueRequest( IOBluetoothHCIRequest * inRequestPtr );

	virtual	IOReturn 	EnqueueWaitRequest( IOBluetoothHCIRequest * inRequestPtr );

	virtual	IOReturn	FindQueuedWaitRequest( BluetoothHCICommandOpCode opCode, IOBluetoothHCIRequest ** outRequestPtr );

	virtual IOReturn	DequeueWaitRequest( IOBluetoothHCIRequest * inRequestPtr );

	virtual	IOReturn	AbortRequest( IOBluetoothHCIRequest * inRequestPtr );

	virtual	IOReturn	FindNextExpiringRequest( BluetoothHCICommandOpCode opCode, IOBluetoothHCIRequest ** outRequestPtr );
	
	virtual	IOReturn	ProcessWaitingRequests();
	
	inline	IOBluetoothHCIRequest*	GetNextWaitRequest() { return( mWaitQueueHead ); }

	inline	IOBluetoothHCIRequest*	GetNextBusyRequest() { return( mBusyQueueHead ); }
			
	virtual	void		TakeAHexDump( const void *inData, UInt32 inDataSize );
			
	virtual	IOReturn	DumpStats();
        
	virtual IOBluetoothHCIControllerPowerOptions		GetControllerPowerOptions();
	virtual IOBluetoothHCIControllerInternalPowerState	GetControllerPowerState();
	virtual IOReturn	WaitForControllerPowerState( IOBluetoothHCIControllerInternalPowerState powerState );
	
	virtual IOReturn	RequestPowerStateChange( IOBluetoothHCIControllerInternalPowerState newPowerState );

	virtual IOReturn	SendHCIRequestFormatted( BluetoothHCIRequestID		inID, 
												 BluetoothHCICommandOpCode 	inOpCode,
												 IOByteCount				outResultsSize, 
												 void *						outResultsPtr,
												 const char *				inFormat, 
												 ... );

	static	void		RequestExpired( OSObject *owner, IOTimerEventSource *sender );

	// Misc stuff.
	
			IOReturn	DisposeRequestsForTaskID( task_t inTaskID );
	
			IOReturn	KillAllPendingRequests( Boolean destroy );
                        void	SendingRequest( IOBluetoothHCIRequest *requestPtr );
                        void	DecrementActiveConnections(  );

	virtual	void	ActiveConnectionsInProgress( );
	virtual	void	AllConnectionsGone( );
			
	virtual IOReturn	SendRawHCICommand(	BluetoothHCIRequestID	inID,
											char * 		 			buffer,
											IOByteCount				bufferSize );
	
	// Vendor Specific stuff.

	virtual	IOReturn	VendorCommand(	BluetoothHCIRequestID	 			inID, 
										BluetoothHCIVendorCommandSelector	inSelector,
										UInt8 *								inCommandData,
										IOByteCount							inCommandDataSize,
										IOByteCount 						outBufferSize,
										UInt8 * 							outBuffer );

	// IOBluetoothDevice object management
    
    virtual IOBluetoothDevice *	FindDeviceWithHandle( BluetoothConnectionHandle inConnectionHandle );
    
    virtual IOBluetoothDevice * FindDeviceWithAddress( const BluetoothDeviceAddress *inDeviceAddress );

    virtual IOReturn	SendACLPacket(	IOBluetoothACLMemoryDescriptor				*memDescriptor,
                                        SendDataContext *								contextPtr,
                                        IOBluetoothDevice *						inTargetDevice = NULL );
                                        

    // API for the serial manager to open a new connection

    virtual IOBluetoothDevice *OpenDeviceConnection( const BluetoothDeviceAddress *inDeviceAddress );

    static IOReturn OpenDeviceConnectionAction(	OSObject	*owner,
                                                void 		*arg1,
                                                void		*arg2,
                                                void		*arg3,
                                                void		*arg4 );
                                                
    virtual IOBluetoothDevice *OpenDeviceConnectionWL( const BluetoothDeviceAddress *inDeviceAddress );

    // API to track the secure state of RFCOMM channels
    virtual Boolean IsSecureIncomingRFCOMMChannel( BluetoothRFCOMMChannelID incomingChannelID );
    virtual Boolean IsSecureIncomingRFCOMMChannel( OSNumber *channelIDNumber );
        
	// API to track allowed incoming L2CAP and RFCOMM channels given a device:
	virtual Boolean IsAllowedIncomingL2CAPChannelForDevice( BluetoothL2CAPPSM incomingPSM, IOBluetoothDevice *device );
	virtual Boolean IsAllowedIncomingRFCOMMChannelForDevice( BluetoothRFCOMMChannelID incomingChannelID, IOBluetoothDevice *device );

	// Enabled state for RFCOMM channels:
	virtual void IOBluetoothHCIController::SetEnabledIncomingRFCOMMChannel( OSNumber *channelIDNumber, bool ShouldBeEnabled);
	virtual void IOBluetoothHCIController::SetEnabledIncomingRFCOMMChannel( BluetoothRFCOMMChannelID incomingChannelID, bool ShouldBeEnabled);

    virtual Boolean ShouldRunInactivityTimer();
    virtual void	SetRunInactivityTimer( Boolean shouldRun );

	//============================

	// From here on out, we implement each of the commands in the HCI spec. You can work around
	// hardware bugs by overriding any of these functions if necessary.
	
	
	// Link Control Commands.
																				
	virtual IOReturn	BluetoothHCIInquiry(	BluetoothHCIRequestID	 		inID, 
												BluetoothLAP					inLAP, 
												BluetoothHCIInquiryLength		inInquiryLength, 
												BluetoothHCIResponseCount		inMaxResponseCount, 
												BluetoothHCIInquiryResults *	outResults );

	virtual IOReturn	BluetoothHCIInquiryCancel( BluetoothHCIRequestID		 inID );

	virtual IOReturn	BluetoothHCIPeriodicInquiryMode(	BluetoothHCIRequestID	 	inID, 
															BluetoothHCIInquiryLength	inMaxPeriodLength, 
															BluetoothHCIInquiryLength	inMinPeriodLength, 
															BluetoothLAP				inLAP, 
															BluetoothHCIInquiryLength	inInquiryLength, 
															BluetoothHCIResponseCount	inMaxResponses,
                                                            BluetoothHCIInquiryResults *	outResults );

	virtual IOReturn	BluetoothHCIExitPeriodicInquiryMode( BluetoothHCIRequestID	inID );

	virtual IOReturn	BluetoothHCICreateConnection(	BluetoothHCIRequestID						inID, 
														const BluetoothDeviceAddress *				inAddressPtr, 
														BluetoothPacketType							inPacketType, 
														BluetoothPageScanRepetitionMode				inPageScanRepetitionMode, 
														BluetoothPageScanMode						inPageScanMode, 
														BluetoothClockOffset						inClockOffset, 
														BluetoothAllowRoleSwitch					inAllowRoleSwitch, 
														BluetoothHCIEventConnectionCompleteResults *outConnectionHandle );

	virtual IOReturn	BluetoothHCIDisconnect( BluetoothHCIRequestID			inID, 
												BluetoothConnectionHandle	 	inConnectionHandle, 
												BluetoothReasonCode				inReason,
                                                BluetoothHCIEventDisconnectionCompleteResults *	outResults );

	virtual IOReturn	BluetoothHCIAddSCOConnection(	BluetoothHCIRequestID		inID, 
														BluetoothConnectionHandle	inACLConnectionHandle, 
														BluetoothPacketType 		inPacketType );

	virtual IOReturn	BluetoothHCIAcceptConnectionRequest(	BluetoothHCIRequestID				inID, 
																const BluetoothDeviceAddress *		inAddressPtr, 
																BluetoothRole						inRole );

	virtual IOReturn	BluetoothHCIRejectConnectionRequest(	BluetoothHCIRequestID			inID, 
																const BluetoothDeviceAddress *	inAddressPtr, 
																BluetoothReasonCode				inReason );

	virtual IOReturn	BluetoothHCILinkKeyRequestReply(	BluetoothHCIRequestID			inID, 
															const BluetoothDeviceAddress *	inAddressPtr, 
															const BluetoothKey *			inKeyPtr,
															BluetoothDeviceAddress *		outAddress );

	virtual IOReturn	BluetoothHCILinkKeyRequestNegativeReply( 	BluetoothHCIRequestID			inID, 
																	const BluetoothDeviceAddress *	inAddressPtr,
																	BluetoothDeviceAddress *		outAddress );

	virtual IOReturn	BluetoothHCIPINCodeRequestReply(	BluetoothHCIRequestID				inID, 
															const BluetoothDeviceAddress *		inAddressPtr, 
															IOByteCount							inPINCodeSize, 
															const BluetoothPINCode *			inPINCode,
															BluetoothDeviceAddress *		outAddress );

	virtual IOReturn	BluetoothHCIPINCodeRequestNegativeReply(	BluetoothHCIRequestID			inID, 
																	const BluetoothDeviceAddress *	inAddressPtr,
																	BluetoothDeviceAddress *		outAddress );

	virtual IOReturn	BluetoothHCIChangeConnectionPacketType( BluetoothHCIRequestID		inID, 
																BluetoothConnectionHandle	inConnectionHandle, 
																BluetoothPacketType			inPacketType );

	virtual IOReturn	BluetoothHCIAuthenticationRequested(	BluetoothHCIRequestID		inID, 
																BluetoothConnectionHandle	inConnectionHandle );

	virtual IOReturn	BluetoothHCISetEncryptionEnable(	BluetoothHCIRequestID		inID, 
															BluetoothConnectionHandle	inConnectionHandle, 
															BluetoothEncryptionEnable	inEncryptionEnable );

	virtual IOReturn	BluetoothHCIChangeConnectionLinkKey(	BluetoothHCIRequestID		inID, 
																BluetoothConnectionHandle	inConnectionHandle );

	virtual IOReturn	BluetoothHCIMasterLinkKey(	BluetoothHCIRequestID	inID, 
													BluetoothKeyFlag		inKeyFlag );

	virtual IOReturn	BluetoothHCIRemoteNameRequest(	BluetoothHCIRequestID						inID, 
														const BluetoothDeviceAddress *				inAddressPtr, 
														BluetoothPageScanRepetitionMode 			inPageScanRepetitionMode, 
														BluetoothPageScanMode						inPageScanMode, 
														BluetoothClockOffset						inClockOffset,
														BluetoothHCIEventRemoteNameRequestResults *	outName );

	virtual IOReturn	BluetoothHCIReadRemoteSupportedFeatures(	BluetoothHCIRequestID			inID, 
																	BluetoothConnectionHandle		inConnectionHandle,
																	BluetoothHCISupportedFeatures *	outFeatures );

	virtual IOReturn	BluetoothHCIReadRemoteVersionInformation(	BluetoothHCIRequestID		inID, 
																	BluetoothConnectionHandle	inConnectionHandle, 
																	BluetoothHCIVersionInfo *	outVersionInfo );

	virtual IOReturn	BluetoothHCIReadClockOffset(	BluetoothHCIRequestID		inID, 
														BluetoothConnectionHandle	inConnectionHandle,
														BluetoothClockOffset *		outClockOffset );

	// Link Policy commands.
	
	virtual	IOReturn	BluetoothHCIHoldMode(	BluetoothHCIRequestID	 		inID,
												BluetoothConnectionHandle		inConnectionHandle,
												BluetoothHCIModeInterval		inHoldModeMaxInterval,
												BluetoothHCIModeInterval		inHoldModeMinInterval );
												
	virtual	IOReturn	BluetoothHCISniffMode(	BluetoothHCIRequestID	 		inID,
												BluetoothConnectionHandle		inConnectionHandle,
												BluetoothHCIModeInterval		inSniffModeMaxInterval,
												BluetoothHCIModeInterval		inSniffModeMinInterval,
												BluetoothHCISniffAttemptCount	inSniffAttemptCount,
												BluetoothHCISniffTimeout		inSniffModeTimeout );
												
	virtual	IOReturn	BluetoothHCIExitSniffMode(	BluetoothHCIRequestID	 	inID,
													BluetoothConnectionHandle	inConnectionHandle );

	virtual	IOReturn	BluetoothHCIParkMode(	BluetoothHCIRequestID	 			inID,
												BluetoothConnectionHandle			inConnectionHandle,
												BluetoothHCIParkModeBeaconInterval	inMaxInterval,
												BluetoothHCIParkModeBeaconInterval	inMinInterval );
												
	virtual	IOReturn	BluetoothHCIExitParkMode(	BluetoothHCIRequestID	 		inID,
													BluetoothConnectionHandle		inConnectionHandle );
													
	virtual	IOReturn	BluetoothHCIQualityOfServiceSetup(	BluetoothHCIRequestID	 					inID,
															BluetoothConnectionHandle					inConnectionHandle,
															BluetoothHCIQualityOfServiceSetupParams * 	inSetupPtr );
		
	virtual	IOReturn	BluetoothHCIRoleDiscovery(	BluetoothHCIRequestID			inID, 
													BluetoothConnectionHandle		inConnectionHandle,
													BluetoothHCIRoleInfo  *			outRoleInfo );
																
	virtual	IOReturn	BluetoothHCISwitchRole(	BluetoothHCIRequestID		inID, 
												BluetoothDeviceAddress * 	inAddressPtr,
												BluetoothHCIRole			inNewRole );
																							
	virtual	IOReturn	BluetoothHCIReadLinkPolicySettings(	BluetoothHCIRequestID					inID, 
															BluetoothConnectionHandle				inConnectionHandle,
															BluetoothHCILinkPolicySettingsInfo  *	outSettingsInfo );
															
	virtual	IOReturn	BluetoothHCIWriteLinkPolicySettings(	BluetoothHCIRequestID				inID,
																BluetoothConnectionHandle			inConnectionHandle,
																BluetoothHCILinkPolicySettings		inSettings,
																BluetoothConnectionHandle *			outConnectionHandle );
																																					
	// Host controller and baseband commands.

	virtual	IOReturn	BluetoothHCISetEventMask(	BluetoothHCIRequestID	inID,
													BluetoothSetEventMask *	inMask );
											
	virtual	IOReturn	BluetoothHCIReset( BluetoothHCIRequestID	inID );

	virtual	IOReturn	BluetoothHCISetEventFilter( BluetoothHCIRequestID	inID );

	virtual	IOReturn	BluetoothHCIFlush(	BluetoothHCIRequestID	 	inID,
											BluetoothConnectionHandle	inHandle );

	virtual	IOReturn	BluetoothHCIReadPINType(	BluetoothHCIRequestID	inID,
													BluetoothPINType *		outType );

	virtual	IOReturn	BluetoothHCIWritePINType(	BluetoothHCIRequestID	inID,
													BluetoothPINType		inType );

	virtual	IOReturn	BluetoothHCICreateNewUnitKey( BluetoothHCIRequestID	inID );

	virtual	IOReturn	BluetoothHCIReadStoredLinkKey(	BluetoothHCIRequestID					inID,
														BluetoothDeviceAddress *				targetDevice,
														BluetoothHCIReadStoredLinkKeysFlag * 	inFlags,
														BluetoothHCIStoredLinkKeysInfo *		outKeysInfo );

	virtual	IOReturn	BluetoothHCIWriteStoredLinkKey( BluetoothHCIRequestID				inID,
														IOItemCount 						inNumKeysToWrite,
														BluetoothDeviceAddress				inDeviceAddresses[],
														BluetoothKey						inLinkKeys[],
														BluetoothHCINumLinkKeysToWrite * 	outNumKeysWritten );

	virtual	IOReturn	BluetoothHCIDeleteStoredLinkKey(	BluetoothHCIRequestID					inID,
															BluetoothDeviceAddress	*				targetDevice,
															BluetoothHCIDeleteStoredLinkKeyFlag *	inFlag,
															BluetoothHCINumLinkKeysDeleted *		outNumDeleted );

	virtual	IOReturn	BluetoothHCIReadLocalName(	BluetoothHCIRequestID	inID,
													BluetoothDeviceName		name );

	virtual	IOReturn	BluetoothHCIChangeLocalName( BluetoothHCIRequestID		inID,
													 BluetoothDeviceName		newName );

	virtual	IOReturn	BluetoothHCIReadConnectionAcceptTimeout( 	BluetoothHCIRequestID					inID,
																	BluetoothHCIConnectionAcceptTimeout *	outTimeout );

	virtual	IOReturn	BluetoothHCIWriteConnectionAcceptTimeout(	BluetoothHCIRequestID					inID,
																	BluetoothHCIConnectionAcceptTimeout		inTimeout );

	virtual	IOReturn	BluetoothHCIReadPageTimeout(	BluetoothHCIRequestID	 	inID,
														BluetoothHCIPageTimeout * 	outDataPtr );

	virtual	IOReturn	BluetoothHCIWritePageTimeout(	BluetoothHCIRequestID	 	inID,
														BluetoothHCIPageTimeout 	inTimeout );

	virtual	IOReturn	BluetoothHCIReadScanEnable( BluetoothHCIRequestID	 			inID,
													BluetoothHCIPageScanEnableState *	outState );

	virtual	IOReturn	BluetoothHCIWriteScanEnable( 	BluetoothHCIRequestID				inID,
														BluetoothHCIPageScanEnableState		inState  );

	virtual	IOReturn	BluetoothHCIReadPageScanActivity(	BluetoothHCIRequestID 		inID,
															BluetoothHCIScanActivity *	outActivityInfo );

	virtual	IOReturn	BluetoothHCIWritePageScanActivity(	BluetoothHCIRequestID	 	inID,
															BluetoothHCIScanActivity *	inActivityInfo );

	virtual	IOReturn	BluetoothHCIReadInquiryScanActivity(	BluetoothHCIRequestID 		inID,
																BluetoothHCIScanActivity *	outActivityInfo );

	virtual	IOReturn	BluetoothHCIWriteInquiryScanActivity(	BluetoothHCIRequestID	 	inID,
																BluetoothHCIScanActivity *	inActivityInfo );

	virtual	IOReturn	BluetoothHCIReadAuthenticationEnable(	BluetoothHCIRequestID	 			inID,
																BluetoothHCIAuthenticationEnable *	outAuthenticationState );
	
	virtual	IOReturn	BluetoothHCIWriteAuthenticationEnable(	BluetoothHCIRequestID	 			inID,
																BluetoothHCIAuthenticationEnable	inAuthenticationState );
																
	virtual	IOReturn	BluetoothHCIReadEncryptionMode(	BluetoothHCIRequestID	 		inID,
														BluetoothHCIEncryptionMode *	outEncryptionState );

	virtual	IOReturn	BluetoothHCIWriteEncryptionMode(	BluetoothHCIRequestID		 	inID,
															BluetoothHCIEncryptionMode		inEncryptionMode );

	virtual	IOReturn	BluetoothHCIReadClassOfDevice(	BluetoothHCIRequestID		inID,
														BluetoothClassOfDevice *	outClassOfDevice );
																	
	virtual	IOReturn	BluetoothHCIWriteClassOfDevice(	BluetoothHCIRequestID		inID,
														BluetoothClassOfDevice		inClassOfDevice );
																	
	virtual	IOReturn	BluetoothHCIReadVoiceSetting(	BluetoothHCIRequestID	 	inID,
														BluetoothHCIVoiceSetting *	outVoiceSetting );

	virtual	IOReturn	BluetoothHCIWriteVoiceSetting(	BluetoothHCIRequestID		inID,
														BluetoothHCIVoiceSetting	inVoiceSetting );

	virtual	IOReturn	BluetoothHCIReadAutomaticFlushTimeout(	BluetoothHCIRequestID	 				inID,
																BluetoothConnectionHandle				inConnectionHandle,
																BluetoothHCIAutomaticFlushTimeoutInfo *	outAutomaticFlushTimeoutInfo );


	virtual	IOReturn	BluetoothHCIWriteAutomaticFlushTimeout(	BluetoothHCIRequestID					inID,
																BluetoothHCIAutomaticFlushTimeoutInfo *	inAutomaticFlushTimeoutInfo,
																BluetoothConnectionHandle *				outConnectionHandle );

	virtual	IOReturn	BluetoothHCIReadNumBroadcastRetransmissions(	BluetoothHCIRequestID	 					inID,
																		BluetoothHCINumBroadcastRetransmissions *	outNumRetrans );
																				
	virtual	IOReturn	BluetoothHCIWriteNumBroadcastRetransmissions(	BluetoothHCIRequestID					inID,
																		BluetoothHCINumBroadcastRetransmissions	inNumRetrans );
																				
	virtual	IOReturn	BluetoothHCIReadHoldModeActivity(	BluetoothHCIRequestID	 		inID,
															BluetoothHCIHoldModeActivity *	outState );
																	
	virtual	IOReturn	BluetoothHCIWriteHoldModeActivity(	BluetoothHCIRequestID			inID,
															BluetoothHCIHoldModeActivity	inState );

	virtual	IOReturn	BluetoothHCIReadTransmitPowerLevel(	BluetoothHCIRequestID	 				inID,
															BluetoothConnectionHandle				inHandle,
															BluetoothHCITransmitPowerLevelType		inType,
															BluetoothHCITransmitPowerLevelInfo *	outLevelInfo );

	virtual	IOReturn	BluetoothHCIReadSCOFlowControlEnable(	BluetoothHCIRequestID	 		inID,
																BluetoothHCIFlowControlState *	outState );
																		
	virtual	IOReturn	BluetoothHCIWriteSCOFlowControlEnable(	BluetoothHCIRequestID			inID,
																BluetoothHCIFlowControlState	inState );

	virtual	IOReturn	BluetoothHCISetHostControllerToHostFlowControl(	BluetoothHCIRequestID			inID,
																		BluetoothHCIFlowControlState	inState );

	virtual	IOReturn	BluetoothHCIHostBufferSize(	BluetoothHCIRequestID	 	inID,
													BluetoothHCIBufferSize * 	inSize );

	virtual	IOReturn	BluetoothHCIHostNumberOfCompletePackets( BluetoothHCIRequestID inID );

	virtual	IOReturn	BluetoothHCIReadLinkSupervisionTimeout(	BluetoothHCIRequestID 					inID,
																BluetoothConnectionHandle				inHandle,
																BluetoothHCILinkSupervisionTimeout *	outInfo );
																			
	virtual	IOReturn	BluetoothHCIWriteLinkSupervisionTimeout(	BluetoothHCIRequestID 					inID,
																	BluetoothHCILinkSupervisionTimeout *	inInfo,
																	BluetoothConnectionHandle *				outHandle );

	virtual	IOReturn	BluetoothHCIReadNumberOfSupportedIAC(	BluetoothHCIRequestID 		inID,
																BluetoothHCISupportedIAC *	outNumSupported );
																		
	virtual	IOReturn	BluetoothHCIReadCurrentIACLAP(	BluetoothHCIRequestID inID );

	virtual	IOReturn	BluetoothHCIWriteCurrentIACLAP(	BluetoothHCIRequestID inID );

	virtual	IOReturn	BluetoothHCIReadPageScanPeriodMode(	BluetoothHCIRequestID 				inID,
															BluetoothHCIPageScanPeriodMode *	outMode );
																		
	virtual	IOReturn	BluetoothHCIWritePageScanPeriodMode(	BluetoothHCIRequestID 			inID,
																BluetoothHCIPageScanPeriodMode	inMode );
																		
	virtual	IOReturn	BluetoothHCIReadPageScanMode(	BluetoothHCIRequestID 		inID,
														BluetoothHCIPageScanMode *	outMode );
																
	virtual	IOReturn	BluetoothHCIWritePageScanMode(	BluetoothHCIRequestID 		inID,
														BluetoothHCIPageScanMode	inMode );
																	
	// Informational commands.
	
	virtual	IOReturn	BluetoothHCIReadLocalVersionInformation( BluetoothHCIRequestID		inID,
																 BluetoothHCIVersionInfo *	outVersionInfo );

	virtual	IOReturn	BluetoothHCIReadLocalSupportedFeatures( BluetoothHCIRequestID				inID,
																BluetoothHCISupportedFeatures	 *	outFeatures );

	virtual	IOReturn	BluetoothHCIReadBufferSize( BluetoothHCIRequestID	 	inID,
													BluetoothHCIBufferSize * 	outSize );

	virtual	IOReturn	BluetoothHCIReadCountryCode(	BluetoothHCIRequestID	 	inID,
														BluetoothHCICountryCode * 	outCountryCode );

	virtual	IOReturn	BluetoothHCIReadDeviceAddress(	BluetoothHCIRequestID	 	inID, 
														BluetoothDeviceAddress *	outAddress );

	// Status commands.
	
	virtual	IOReturn	BluetoothHCIReadFailedContactCounter(	BluetoothHCIRequestID	 			inID,
																BluetoothConnectionHandle			inConnectionHandle,
																BluetoothHCIFailedContactInfo *		outFailedContactCount );
																
	virtual	IOReturn	BluetoothHCIResetFailedContactCounter(	BluetoothHCIRequestID	 	inID,
																BluetoothConnectionHandle	inConnectionHandle );
																
	virtual	IOReturn	BluetoothHCIGetLinkQuality(	BluetoothHCIRequestID	 		inID,
													BluetoothConnectionHandle		inConnectionHandle,
													BluetoothHCILinkQualityInfo *	outLinkQualityInfo );
																
	virtual	IOReturn	BluetoothHCIReadRSSI(	BluetoothHCIRequestID	 	inID,
												BluetoothConnectionHandle	inConnectionHandle,
												BluetoothHCIRSSIInfo *		outRSSIInfo );
	
	// Testing Commands.

	virtual	IOReturn	BluetoothHCIReadLoopbackMode(	BluetoothHCIRequestID	 	inID,
														BluetoothHCILoopbackMode *	inLoopbackMode );

	virtual	IOReturn	BluetoothHCIWriteLoopbackMode(	BluetoothHCIRequestID		inID, 
														BluetoothHCILoopbackMode	inLoopbackMode );

	virtual	IOReturn	BluetoothHCIEnableDeviceUnderTestMode( BluetoothHCIRequestID	inID );
	
	virtual IOBluetoothHCIControllerFeatureFlags	GetControllerFeatureFlags();

protected:

	// Power managment functions:

	virtual bool		configurePM(IOService *provider);

	virtual	IOReturn	setPowerState( unsigned long powerStateOrdinal, IOService* whatDevice );
	static	IOReturn	setPowerStateAction( OSObject *owner, void *arg1, void *arg2, void *arg3, void *arg4 );
	virtual	IOReturn	setPowerStateWL( unsigned long powerStateOrdinal, IOService* whatDevice );
    
	virtual void		UpdatePowerStateProperty( IOBluetoothHCIControllerInternalPowerState powerState );
	
	virtual void		SetControllerPowerOptions( IOBluetoothHCIControllerPowerOptions controllerPowerOptions );
	virtual IOReturn	PerformPowerStateChange(	IOBluetoothHCIControllerInternalPowerState oldPowerState,
													IOBluetoothHCIControllerInternalPowerState newPowerState,
													UInt32 powerStateOptions,
													UInt32 *microsecondsUntilComplete );
	virtual void		CompletePowerStateChange();
	
	virtual void		SetControllerFeatureFlags( IOBluetoothHCIControllerFeatureFlags featureFlags );

protected:

	// HCI Command Enqueueing:
	typedef struct HCICommandHolder {
		HCICommandHolder								*next;			// Next holder in the list;
		IOBluetoothHCIRequest 							*requestPtr;	// Request for this command
	} HCICommandHolder;

	// Enablers for future Changes.

    typedef struct ExpansionData 
	{
		HCICommandHolder	*mCommandQueueHead, *mCommandQueueTail;

		// Max number of HCI command allowed;
		UInt8				mNumberOfCommandsAllowedByHardware;
		UInt8				mNumConfiguredHIDDevices;
		UInt8				mControllerSleepFlags;
		IONotifier*			mSleepWakeNotifier;

		// AFH support:
		// the mask for the channels to use:
		UInt8				mMaskByte[10];

		// AirPort changes notifications:
		IONotifier *				mAirPortDriver;
		IONotifier *				mAirPortPCI;
		Boolean						mProcessingConnectionRequest;
		Boolean						mWaitingForCompletedACLPacketsToSleep;

        // SCO Support
		UInt8				mNumSCOConnections;
		UInt8				*mSCOPacketBuffer;
		UInt16				mNumBufferedSCOBytes;
		AbsoluteTime		mBufferedSCOPacketTimestamp;
		
		// Repository for the packets when logging at boot
		OSArray				*mRepositoryForBoot;
		UInt16				mMaxNumberOfBootPackets;
		
		IOService			*mOverriddenControllerProvider;
		
		size_t				mHCIRequestListSize;
		uint32_t			mNewRequestIndex;
		
		IOBluetoothInactivityTimerEventSource	*mIdleTimer;
		Boolean				mIgnoreIdleTimer;

		// New Airport notifications:
		IONotifier *				mIO80211Interface;
	} ExpansionData;

	ExpansionData*		mExpansionData;
	
#define mCommandQueueHead						IOBluetoothHCIController::mExpansionData->mCommandQueueHead
#define mCommandQueueTail						IOBluetoothHCIController::mExpansionData->mCommandQueueTail
#define mNumberOfCommandsAllowedByHardware		IOBluetoothHCIController::mExpansionData->mNumberOfCommandsAllowedByHardware
#define	mNumConfiguredHIDDevices				IOBluetoothHCIController::mExpansionData->mNumConfiguredHIDDevices
#define mControllerSleepFlags					IOBluetoothHCIController::mExpansionData->mControllerSleepFlags
#define mSleepWakeNotifier						IOBluetoothHCIController::mExpansionData->mSleepWakeNotifier

#define mMaskByte								IOBluetoothHCIController::mExpansionData->mMaskByte
#define mAirPortDriver							IOBluetoothHCIController::mExpansionData->mAirPortDriver
#define mAirPortPCI								IOBluetoothHCIController::mExpansionData->mAirPortPCI
#define mProcessingConnectionRequest			IOBluetoothHCIController::mExpansionData->mProcessingConnectionRequest
#define mWaitingForCompletedACLPacketsToSleep   IOBluetoothHCIController::mExpansionData->mWaitingForCompletedACLPacketsToSleep

#define	mNumSCOConnections						IOBluetoothHCIController::mExpansionData->mNumSCOConnections
#define mSCOPacketBuffer						IOBluetoothHCIController::mExpansionData->mSCOPacketBuffer
#define mNumBufferedSCOBytes					IOBluetoothHCIController::mExpansionData->mNumBufferedSCOBytes
#define mBufferedSCOPacketTimestamp				IOBluetoothHCIController::mExpansionData->mBufferedSCOPacketTimestamp
#define mRepositoryForBoot						IOBluetoothHCIController::mExpansionData->mRepositoryForBoot
#define mMaxNumberOfBootPackets					IOBluetoothHCIController::mExpansionData->mMaxNumberOfBootPackets
#define mOverriddenControllerProvider			IOBluetoothHCIController::mExpansionData->mOverriddenControllerProvider
#define mHCIRequestListSize						IOBluetoothHCIController::mExpansionData->mHCIRequestListSize
#define mNewRequestIndex						IOBluetoothHCIController::mExpansionData->mNewRequestIndex
#define mIdleTimer								IOBluetoothHCIController::mExpansionData->mIdleTimer
#define mIgnoreIdleTimer						IOBluetoothHCIController::mExpansionData->mIgnoreIdleTimer
#define mIO80211Interface						IOBluetoothHCIController::mExpansionData->mIO80211Interface

	enum {
		kIOBluetoothHCIControllerSleepFlagInquiryScanWasEnabled	= 0x01
	};

	
private:

	// Command Packet Queue:
	virtual IOReturn	EnqueueRequestForController( IOBluetoothHCIRequest *requestPtr );	// Was OSMetaClassDeclareReservedUnused(	IOBluetoothHCIController,  0 )
	virtual IOReturn	DequeueAndSendRequests();											// Was OSMetaClassDeclareReservedUnused(	IOBluetoothHCIController,  1 )
	virtual IOReturn	RemoveAllRequestsFromQueue();										// Was OSMetaClassDeclareReservedUnused(	IOBluetoothHCIController,  2 )

	// New Device creation upon connection:
	IOReturn CreateDeviceFromConnectionResults( BluetoothHCIEventConnectionCompleteResults *connectionResults, bool isInitiator);

	// Expanded version of OpenDeviceConnection MUST BE CALLED IN THE WORKLOOP
    virtual IOBluetoothDevice *OpenDeviceConnection( const BluetoothDeviceAddress *inDeviceAddress, BluetoothHCIPageTimeout pageTimeoutValue, bool  authenticationRequired);

	static	IOReturn sleepWakeHandler( void *target, void *refCon,
					UInt32 messageType, IOService *service, void *messageArgument, vm_size_t argSize );
	static	IOReturn	restartShutdownAction( OSObject *owner, void *arg1, void *arg2, void *arg3, void *arg4 );

public:	
	virtual	IOReturn 	restartShutdownWL( UInt32 messageType, void *reserved);
	
	// AFH support:
	virtual	UInt8 *rangeForChannel(UInt16 channel);
	virtual IOReturn handleAirPortChangesChannelWL(IOService *serviceForAirport);

        // Version of stop in the workloop
        virtual void stopWL( IOService * provider );
        
private:
	static bool staticAirPortDriverNotification(void *us, void *unused, IOService * yourDevice);
	static IOReturn handleAirPortChangesChannelAction( OSObject *owner, void *castMeToServiceForAirport, void *arg2, void *arg3, void *arg4, void *arg5, void *arg6 );

	// Expansion slots:
	OSMetaClassDeclareReservedUsed(	IOBluetoothHCIController,  0 );
	OSMetaClassDeclareReservedUsed(	IOBluetoothHCIController,  1 );
	OSMetaClassDeclareReservedUsed(	IOBluetoothHCIController,  2 );
	OSMetaClassDeclareReservedUsed(	IOBluetoothHCIController,  3 );
	OSMetaClassDeclareReservedUsed(	IOBluetoothHCIController,  4 );
	OSMetaClassDeclareReservedUsed(	IOBluetoothHCIController,  5 );

	OSMetaClassDeclareReservedUsed(	IOBluetoothHCIController,  6 );
	OSMetaClassDeclareReservedUsed(	IOBluetoothHCIController,  7 );
	OSMetaClassDeclareReservedUsed(	IOBluetoothHCIController,  8 );

	OSMetaClassDeclareReservedUsed(	IOBluetoothHCIController,  9 );
	virtual void SetNumSCOConnections( UInt8 numSCOConnections );
	
	OSMetaClassDeclareReservedUsed(	IOBluetoothHCIController,  10 );
	virtual void UpdateSCOConnections( UInt8 numSCOConnections );
	
	OSMetaClassDeclareReservedUsed(	IOBluetoothHCIController,  11 );
	virtual IOBluetoothDevice *FindDeviceWithSCOHandle( BluetoothConnectionHandle inConnectionHandle );
	
	OSMetaClassDeclareReservedUsed(	IOBluetoothHCIController,  12 );
	virtual IOReturn SendSCOData(	IOMemoryDescriptor	*scoDataDescriptor,
									SendDataContext		*scoDataContext );

protected:
	OSMetaClassDeclareReservedUsed(	IOBluetoothHCIController,  13 );
	virtual	void	SendSCOCompleted( SendDataContext *contextPtr, AbsoluteTime timestamp );

	OSMetaClassDeclareReservedUsed(	IOBluetoothHCIController,  14 );
	virtual IOReturn DispatchIncomingSCOData( UInt8 *inDataPtr, UInt32 inDataSize, UInt32 inMissingData, AbsoluteTime inTimestamp );
        
        OSMetaClassDeclareReservedUsed(	IOBluetoothHCIController,  15 );
        virtual bool willTerminateWL( IOService * provider, IOOptionBits options );

protected:

#if !(defined(__ppc__) && defined(KPI_10_4_0_PPC_COMPAT))
	OSMetaClassDeclareReservedUsed(	IOBluetoothHCIController,  16 );
	virtual bool shouldOverrideExistingController( IOBluetoothHCIController *controller );

	static void idleTimerFired( OSObject *owner, IOTimerEventSource *timerEventSource );
	
	OSMetaClassDeclareReservedUsed(	IOBluetoothHCIController,  17 );
	virtual void handleIdleTimeout();

	static IOReturn IOBluetoothHCIController::terminateAction(	OSObject	*owner, 
														void		*arg1, 
														void		*arg2, 
														void		*arg3, 
														void		*arg4 );
	
	OSMetaClassDeclareReservedUsed(	IOBluetoothHCIController,  18 );
	virtual IOReturn terminateWL( IOOptionBits options );

	// Support for dynamic channel width
	OSMetaClassDeclareReservedUsed(	IOBluetoothHCIController,  19 );
	virtual	UInt8 *rangeForChannel(UInt16 channel, SInt16 width);
#endif
	
private:
#if (defined(__ppc__) && defined(KPI_10_4_0_PPC_COMPAT))
	OSMetaClassDeclareReservedUnused(	IOBluetoothHCIController,  16 );
	OSMetaClassDeclareReservedUnused(	IOBluetoothHCIController,  17 );
	OSMetaClassDeclareReservedUnused(	IOBluetoothHCIController,  18 );
	OSMetaClassDeclareReservedUnused(	IOBluetoothHCIController,  19 );
#endif

	OSMetaClassDeclareReservedUnused(	IOBluetoothHCIController,  20 );
	OSMetaClassDeclareReservedUnused(	IOBluetoothHCIController,  21 );
	OSMetaClassDeclareReservedUnused(	IOBluetoothHCIController,  22 );
	OSMetaClassDeclareReservedUnused(	IOBluetoothHCIController,  23 );
	OSMetaClassDeclareReservedUnused(	IOBluetoothHCIController,  24 );
	OSMetaClassDeclareReservedUnused(	IOBluetoothHCIController,  25 );
	OSMetaClassDeclareReservedUnused(	IOBluetoothHCIController,  26 );
	OSMetaClassDeclareReservedUnused(	IOBluetoothHCIController,  27 );
	OSMetaClassDeclareReservedUnused(	IOBluetoothHCIController,  28 );
	OSMetaClassDeclareReservedUnused(	IOBluetoothHCIController,  29 );
	OSMetaClassDeclareReservedUnused(	IOBluetoothHCIController,  30 );
	OSMetaClassDeclareReservedUnused(	IOBluetoothHCIController,  31 );
	OSMetaClassDeclareReservedUnused(	IOBluetoothHCIController,  32 );
	OSMetaClassDeclareReservedUnused(	IOBluetoothHCIController,  33 );
	OSMetaClassDeclareReservedUnused(	IOBluetoothHCIController,  34 );
	OSMetaClassDeclareReservedUnused(	IOBluetoothHCIController,  35 );
	OSMetaClassDeclareReservedUnused(	IOBluetoothHCIController,  36 );
	OSMetaClassDeclareReservedUnused(	IOBluetoothHCIController,  37 );
	OSMetaClassDeclareReservedUnused(	IOBluetoothHCIController,  38 );
	OSMetaClassDeclareReservedUnused(	IOBluetoothHCIController,  39 );
	OSMetaClassDeclareReservedUnused(	IOBluetoothHCIController,  40 );
	OSMetaClassDeclareReservedUnused(	IOBluetoothHCIController,  41 );
	OSMetaClassDeclareReservedUnused(	IOBluetoothHCIController,  42 );
	OSMetaClassDeclareReservedUnused(	IOBluetoothHCIController,  43 );
	OSMetaClassDeclareReservedUnused(	IOBluetoothHCIController,  44 );
	OSMetaClassDeclareReservedUnused(	IOBluetoothHCIController,  45 );
	OSMetaClassDeclareReservedUnused(	IOBluetoothHCIController,  46 );
	OSMetaClassDeclareReservedUnused(	IOBluetoothHCIController,  47 );
	OSMetaClassDeclareReservedUnused(	IOBluetoothHCIController,  48 );
	OSMetaClassDeclareReservedUnused(	IOBluetoothHCIController,  49 );
	OSMetaClassDeclareReservedUnused(	IOBluetoothHCIController,  50 );
	OSMetaClassDeclareReservedUnused(	IOBluetoothHCIController,  51 );
	OSMetaClassDeclareReservedUnused(	IOBluetoothHCIController,  52 );
	OSMetaClassDeclareReservedUnused(	IOBluetoothHCIController,  53 );
	OSMetaClassDeclareReservedUnused(	IOBluetoothHCIController,  54 );
	OSMetaClassDeclareReservedUnused(	IOBluetoothHCIController,  55 );
	OSMetaClassDeclareReservedUnused(	IOBluetoothHCIController,  56 );
	OSMetaClassDeclareReservedUnused(	IOBluetoothHCIController,  57 );
	OSMetaClassDeclareReservedUnused(	IOBluetoothHCIController,  58 );
	OSMetaClassDeclareReservedUnused(	IOBluetoothHCIController,  59 );
	OSMetaClassDeclareReservedUnused(	IOBluetoothHCIController,  60 );
	OSMetaClassDeclareReservedUnused(	IOBluetoothHCIController,  61 );
	OSMetaClassDeclareReservedUnused(	IOBluetoothHCIController,  62 );
	OSMetaClassDeclareReservedUnused(	IOBluetoothHCIController,  63 );
};
