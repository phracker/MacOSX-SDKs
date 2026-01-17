/*
	File:		IOBluetoothHCIRequest.h
	Contains:	Bluetooth Host Controller request object.
	Copyright:	© 2002 by Apple Computer, Inc. All rights reserved.
*/

#pragma once

#import <IOKit/IOService.h>
#import <IOKit/system.h>

#import <IOKit/bluetooth/Bluetooth.h>


class IOCommandGate;
class IOTimerEventSource;
class IOBluetoothHCIController;

// Forward declaration to avoid the need to include IOBluetoothHCIUserLibShared.h
typedef struct	BluetoothHCINotificationMessage;

//===========================================================================================================================
// enums, macros, etc.
//===========================================================================================================================

enum
{
	kMaxHCIBufferLength	= 512
};

typedef UInt8	BluetoothHCIRequestState;
enum BluetoothHCIRequestStates
{
	kHCIRequestStateIdle		= 0,		// Doing nothing - neither waiting nor busy.
	kHCIRequestStateWaiting		= 1,		// On the wait queue - request has not been processed in any way.
	kHCIRequestStateBusy		= 2,		// On the busy queue - request is sent and is currently processing
};


//===========================================================================================================================
// IOBluetoothHCIRequest
//===========================================================================================================================

class IOBluetoothHCIRequest : public OSObject
{
    OSDeclareDefaultStructors( IOBluetoothHCIRequest )

	UInt8								mPrivateResultsBuffer[kMaxHCIBufferLength*4];	// Just in case they didn't give a results ptr.
	IOByteCount							mPrivateResultsSize;							// Result size.
	BluetoothHCITransportID				mTransportID;									// Transport ID to use for this request.
	UInt8								mState;											// Busy, waiting, idle.
	bool								mAsyncNotify;
	task_t								mOwningTaskID;
	BluetoothHCIRequestCallbackInfo		mCallbackInfo;									// When this request is complete, call this.
	BluetoothHCICommandOpCode			mOpCode;
    BluetoothDeviceAddress				mDeviceAddress;
    BluetoothConnectionHandle			mConnectionHandle;
	BluetoothHCINotificationMessage *	mNotificationMessage;
	IOByteCount							mNotificationMessageSize;
		
	
public:

	IOBluetoothHCIRequest *				mNextBusy;									// Points to next request element on busy queue.
	IOBluetoothHCIRequest *				mNextWait;									// Points to next request element on wait queue.
	IOBluetoothHCIRequest *				mNextAllocated;								// Points to next allocated request element.
	IOBluetoothHCIRequest *				mPreviousAllocated;							// Points to next allocated request element.
	BluetoothHCIRequestID				mID;										// For internal identification.
	UInt8								mCommandBuffer[kMaxHCIBufferLength];		// Built-up HCI Command to send to the transport.
	IOByteCount							mCommandBufferSize;							// Size of command buffer.
	
	UInt8 *								mResultsPtr;								// Result ptr, provided by object creator.
	IOByteCount							mResultsSize;								// Result size.
	
	IOCommandGate *						mCommandGate;
    IOTimerEventSource *				mTimer;	
	IOBluetoothHCIController *			mHCIController;
    IOReturn							mStatus;									// Success/failure code of request.
	UInt32								mTimeout;									// Timeout for request to complete, in milliseconds.
	UInt32								mControlFlags;
	
public:

	bool							init( IOCommandGate *commandGate, IOBluetoothHCIController *hciController );
	void							free();
	
	static IOBluetoothHCIRequest *	Create( IOCommandGate *commandGate, IOBluetoothHCIController *hciController, bool async = TRUE, UInt32 timeout = 5, UInt32 controlFlags = 0 );
	static IOReturn					Dispose( IOBluetoothHCIRequest * inObject );

	
	// Called when a request is started on a transport, and completed.
	
	IOReturn					Start();
	void						Complete();

	// Accessors for object members.

	void						SetState( BluetoothHCIRequestState inState );
	BluetoothHCIRequestState	GetState() { return( mState ); }

	void						SetHCIStatus( BluetoothHCIStatus inStatus ) { mStatus = inStatus; }
	BluetoothHCIStatus			GetHCIStatus() { return( mStatus ); }

	void						SetID( BluetoothHCIRequestID inID ) { mID = inID; }
	BluetoothHCIRequestID		GetID() { return( mID ); }

	void								SetCallbackInfo( BluetoothHCIRequestCallbackInfo * inInfo );
	BluetoothHCIRequestCallbackInfo *	GetCallbackInfo() { return( &mCallbackInfo ); }
	
	void						SetOwningTaskID( task_t inTaskID ) { mOwningTaskID = inTaskID; }
	task_t						GetOwningTaskID() { return( mOwningTaskID ); }
	
	void *						GetCommandBuffer();
	
	BluetoothHCICommandOpCode	GetCommandOpCode();
	void						SetCommandOpCode( BluetoothHCICommandOpCode inOpCode ) { mOpCode = inOpCode; }
    
    BluetoothDeviceAddress *	GetDeviceAddress() { return &mDeviceAddress; }
    void						SetDeviceAddress( const BluetoothDeviceAddress *inDeviceAddress ) { if ( inDeviceAddress != NULL ) memcpy( &mDeviceAddress, inDeviceAddress, sizeof( BluetoothDeviceAddress ) ); }
    void						ClearDeviceAddress() { bzero( &mDeviceAddress, sizeof( BluetoothDeviceAddress ) ); }
    Boolean						CompareDeviceAddress( const BluetoothDeviceAddress *inDeviceAddress );
    
    BluetoothConnectionHandle	GetConnectionHandle() { return mConnectionHandle; }
    void						SetConnectionHandle( BluetoothConnectionHandle inConnectionHandle ) { mConnectionHandle = inConnectionHandle; }
    void						ClearConnectionHandle() { mConnectionHandle = kBluetoothConnectionHandleNone; }
	
	void						SetTimeout( UInt32 inTimeout ) { mTimeout = inTimeout; }	// in milliseconds
	UInt32						GetTimeout() { return( mTimeout ); }
    
    static void 				timerFired( OSObject *owner, IOTimerEventSource *sender );
    void						handleTimeout();
	
	void						CopyDataIntoResultsPtr( UInt8 * inDataPtr, IOByteCount inSize );
	void						SetParamPtrAndSize( UInt8 paramNumber, UInt8 * inParamPtr, IOByteCount inSize );
	
	void						SetResultsBufferPtrAndSize( UInt8 * resultsBuffer, IOByteCount inSize );
	void						SetResultsDataSize( IOByteCount inCount );
	UInt8 *						GetResultsBuffer();
	IOByteCount					GetResultsBufferSize();
	
	void *						GetNotificationRefCon() { return( mCallbackInfo.asyncIDRefCon ); }
	
	void						SetDoAsyncNotify( bool inAsyncNotify ) { mAsyncNotify = inAsyncNotify; }
	Boolean						IsSynchronous() { return !mAsyncNotify; }
	
	void						SetControlFlags( UInt32 controlFlags ) { mControlFlags = controlFlags; }
	UInt32						GetControlFlags() { return mControlFlags; }
};
