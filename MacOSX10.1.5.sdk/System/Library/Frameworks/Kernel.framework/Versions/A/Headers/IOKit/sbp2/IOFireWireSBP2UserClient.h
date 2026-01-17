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

#ifndef _IOKIT_IOFIREWIRESBP2USERCLIENT_H
#define _IOKIT_IOFIREWIRESBP2USERCLIENT_H

#include <IOKit/IOUserClient.h>

#include <IOKit/firewire/IOFireWireController.h>

#include <IOKit/sbp2/IOFireWireSBP2UserClientCommon.h>
#include <IOKit/sbp2/IOFireWireSBP2LUN.h>

class IOFireWireSBP2UserClient : public IOUserClient
{
    OSDeclareDefaultStructors(IOFireWireSBP2UserClient)

protected:

    static IOExternalMethod 		sMethods[kIOFWSBP2UserClientNumCommands];
    static IOExternalAsyncMethod 	sAsyncMethods[kIOFWSBP2UserClientNumAsyncCommands];

    bool					fOpened;
	bool					fStarted;
    IOFireWireSBP2Login * 	fLogin;
    task_t					fTask;
	
    IOFireWireSBP2LUN *		fProviderLUN;
    OSAsyncReference		fMessageCallbackAsyncRef;
    OSAsyncReference		fLoginCallbackAsyncRef;
    OSAsyncReference		fLogoutCallbackAsyncRef;
    OSAsyncReference		fUnsolicitedStatusNotifyAsyncRef;
    OSAsyncReference		fStatusNotifyAsyncRef;
    OSAsyncReference		fFetchAgentResetAsyncRef;
	OSAsyncReference		fFetchAgentWriteAsyncRef;
	
    virtual IOExternalMethod * getTargetAndMethodForIndex(IOService **target, UInt32 index);
    virtual IOExternalAsyncMethod * getAsyncTargetAndMethodForIndex(IOService **target, UInt32 index);

public:

    static IOFireWireSBP2UserClient* withTask( task_t owningTask );

    virtual bool init( OSDictionary * dictionary = 0 );
    virtual bool start( IOService * provider );

    virtual IOReturn clientClose( void );
    virtual IOReturn clientDied( void );

	// IOFireWireSBP2ManagementORB friend class wrappers
	virtual void flushAllManagementORBs( void );

    /////////////////////////////////////////////////
    // IOFireWireSBP2LUN

    virtual IOReturn open( void *, void *, void *, void *, void *, void * );
	virtual IOReturn openWithSessionRef( IOFireWireSessionRef sessionRef, void *, void *, void *, void *, void * );
	virtual IOReturn getSessionRef( IOFireWireSessionRef * sessionRef, void *, void *, void *, void *, void * );
    virtual IOReturn close( void *, void *, void *, void *, void *, void * );

    // callbacks
    virtual IOReturn setMessageCallback( OSAsyncReference asyncRef, void * callback, 
												void * refCon, void *, void *, void *, void * );
    virtual IOReturn message( UInt32 type, IOService * provider, void * arg );

    /////////////////////////////////////////////////
    // IOFireWireSBP2Login
    
    virtual IOReturn setLoginCallback( OSAsyncReference asyncRef, void * callback, void * refCon, 
																void *, void *, void *, void * );
	virtual IOReturn setLogoutCallback( OSAsyncReference asyncRef, void * callback, void * refCon, 
																	void *, void *, void *, void * );
    virtual IOReturn setUnsolicitedStatusNotify( OSAsyncReference asyncRef, void * callback, void * refCon,
                                                 void *, void *, void *, void * );
    virtual IOReturn setStatusNotify( OSAsyncReference asyncRef, void * callback, void * refCon, 
																	void *, void *, void *, void * );
    virtual IOReturn createLogin( IOFireWireSBP2Login ** outLoginRef, void *, void *, void *, void *, void * );
    virtual IOReturn releaseLogin( IOFireWireSBP2Login* loginRef, void *, void *, void *, void *, void * );
    virtual IOReturn submitLogin( IOFireWireSBP2Login * loginRef, void *, void *, void *, void *, void * );
    virtual IOReturn submitLogout( IOFireWireSBP2Login * loginRef, void *, void *, void *, void *, void * );
    virtual IOReturn setLoginFlags( IOFireWireSBP2Login * loginRef, UInt32 loginFlags, void *, 
																				void *, void *, void * );
    virtual IOReturn getMaxCommandBlockSize( IOFireWireSBP2Login * loginRef, UInt32 * blockSize, 
																	void *, void *, void *, void * );
    virtual IOReturn getLoginID( IOFireWireSBP2Login * loginRef, UInt32 * loginID, void *,
																			void *, void *, void * );
    virtual IOReturn setReconnectTime( IOFireWireSBP2Login * loginRef, UInt32 time, void *, 
																			void *, void *, void * );
    virtual IOReturn setMaxPayloadSize( IOFireWireSBP2Login * loginRef, UInt32 size, void *, 
																			void *, void *, void * );
    
	virtual IOReturn submitFetchAgentReset( OSAsyncReference asyncRef, IOFireWireSBP2Login * loginRef, void * refCon, void * callback,  void *, void *, void * );
	virtual IOReturn setFetchAgentWriteCompletion( OSAsyncReference asyncRef, void * refCon, void * callback,  void *, void *, void *, void * );
	virtual IOReturn ringDoorbell( IOFireWireSBP2Login * loginRef, void *, void *,  void *, void *, void * );
	virtual IOReturn enableUnsolicitedStatus( IOFireWireSBP2Login * loginRef, void *, void *,  void *, void *, void * );
	virtual IOReturn setBusyTimeoutRegisterValue( IOFireWireSBP2Login * loginRef, UInt32 timeout, void *,  void *, void *, void * );
    virtual IOReturn setPassword( IOFireWireSBP2Login * loginRef, vm_address_t buffer, 
									  IOByteCount length, void *, void *, void * );

	// callbacks
	
	static void staticLoginCallback( void * refCon, FWSBP2LoginCompleteParamsPtr params );
    virtual void loginCallback( FWSBP2LoginCompleteParamsPtr params );

	static void staticLogoutCallback( void * refCon, FWSBP2LogoutCompleteParamsPtr params );
    virtual void logoutCallback( FWSBP2LogoutCompleteParamsPtr params );

	static void staticStatusNotify( void * refCon, FWSBP2NotifyParams * params );
    virtual void statusNotify( FWSBP2NotifyParams * params );

	static void staticUnsolicitedNotify( void * refCon, FWSBP2NotifyParams * params );
    virtual void unsolicitedNotify( FWSBP2NotifyParams * params );

	static void staticFetchAgentWriteComplete( void * refCon, IOReturn status, IOFireWireSBP2ORB * orb );
	virtual void fetchAgentWriteComplete( IOReturn status, IOFireWireSBP2ORB * orb );

    static void staticFetchAgentResetComplete( void * refCon, IOReturn status );
    virtual void fetchAgentResetComplete( IOReturn status );
	
    /////////////////////////////////////////////////
    // IOFireWireSBP2ORB

    virtual IOReturn createORB( IOFireWireSBP2ORB ** outORBRef, void *, void *, void *, void *, void * );
    virtual IOReturn releaseORB( IOFireWireSBP2ORB * ORBRef, void *, void *, void *, void *, void * );
	virtual IOReturn submitORB( IOFireWireSBP2ORB * ORBRef, void *, void *, void *, void *, void * );
    virtual IOReturn setCommandFlags( IOFireWireSBP2ORB * ORBRef, UInt32 flags, void *, void *, void *, void * );
    virtual IOReturn setORBRefCon( IOFireWireSBP2ORB * ORBRef, UInt32 refCon, void *, void *, void *, void * );
    virtual IOReturn setMaxORBPayloadSize( IOFireWireSBP2ORB * ORBRef, UInt32 maxPayloadSize, void *, void *, void *, void * );
    virtual IOReturn setCommandTimeout( IOFireWireSBP2ORB * ORBRef, UInt32 timeout, void *, void *, void *, void * );
    virtual IOReturn setCommandGeneration( IOFireWireSBP2ORB * ORBRef, UInt32 gen, void *, void *, void *, void * );
    virtual IOReturn setToDummy( IOFireWireSBP2ORB * ORBRef, void *, void *, void *, void *, void * );
    virtual IOReturn setCommandBuffersAsRanges( IOFireWireSBP2ORB * ORBRef, vm_address_t ranges, 
												IOByteCount withCount, IODirection withDirection, 
												IOByteCount offset, IOByteCount length );
    virtual IOReturn releaseCommandBuffers( IOFireWireSBP2ORB * ORBRef, void *, void *, 
											void *, void *, void * );
    virtual IOReturn setCommandBlock( IOFireWireSBP2ORB * ORBRef, vm_address_t buffer, 
									  IOByteCount length, void *, void *, void * );
	
	// LSI workaround
    virtual IOReturn LSIWorkaroundSetCommandBuffersAsRanges
				( IOFireWireSBP2ORB * ORBRef, vm_address_t ranges, IOByteCount withCount, 
						IODirection withDirection, IOByteCount offset, IOByteCount length );
	virtual IOReturn LSIWorkaroundSyncBuffersForOutput( IOFireWireSBP2ORB * ORBRef, void *, void *,
														void *, void *, void * );
	virtual IOReturn LSIWorkaroundSyncBuffersForInput( IOFireWireSBP2ORB * ORBRef, void *, void *,
													   void *, void *, void * );
															
    /////////////////////////////////////////////////
    // IOFireWireSBP2MgmtORB

    virtual IOReturn createMgmtORB( IOFireWireSBP2ManagementORB ** outORBRef, void *, void *, 
																	void *, void *, void * );
    virtual IOReturn releaseMgmtORB( IOFireWireSBP2ManagementORB * ORBRef, void *, void *, 
																	void *, void *, void * );
    virtual IOReturn setMgmtORBCallback( OSAsyncReference asyncRef, IOFireWireSBP2ManagementORB * ORBRef, 
												void * refCon, void * callback,	 void *, void *, void * );
    virtual IOReturn submitMgmtORB( IOFireWireSBP2ManagementORB * ORBRef, void *, void *, 
																		void *, void *, void * );	
	virtual IOReturn setMgmtORBCommandFunction( IOFireWireSBP2ManagementORB * ORBRef, 
													UInt32 function, void *, void *, void *, void * );
	virtual IOReturn setMgmtORBManageeORB( IOFireWireSBP2ManagementORB * ORBRef, IOFireWireSBP2ORB * orb, 
													void *, void *, void *, void * );
	virtual IOReturn setMgmtORBManageeLogin( IOFireWireSBP2ManagementORB * ORBRef, 
											IOFireWireSBP2Login * login, void *, void *, void *, void * );
	virtual IOReturn setMgmtORBResponseBuffer( IOFireWireSBP2ManagementORB * ORBRef, vm_address_t buf,
												IOByteCount len, void *, void *, void * );

	// callbacks
    static void staticMgmtORBCallback( void * refCon, IOReturn status, IOFireWireSBP2ManagementORB * orb );
    virtual void mgmtORBCallback( IOReturn status, IOFireWireSBP2ManagementORB * orb );
	
	// IOFireWireSBP2MgmtORB friend class wrappers
	virtual void setMgmtORBAsyncCallbackReference( IOFireWireSBP2ManagementORB * orb, void * asyncRef );    
	virtual void getMgmtORBAsyncCallbackReference( IOFireWireSBP2ManagementORB * orb, void * asyncRef );


};

#endif