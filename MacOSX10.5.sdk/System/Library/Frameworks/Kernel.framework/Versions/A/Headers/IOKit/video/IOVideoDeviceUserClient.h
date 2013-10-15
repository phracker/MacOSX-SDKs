/*
 *  IOVideoDeviceUserClient.h
 *  IOVideoFamily
 *
 *  Copyright 2006 Apple Computer, Inc. All rights reserved.
 *
 */

#if !defined( __IOKIT_IOVIDEODEVICEUSERCLIENT_H )
#define __IOKIT_IOVIDEODEVICEUSERCLIENT_H


#include <IOKit/IOUserClient.h>

#include <IOKit/stream/IOStreamShared.h>

#include <IOKit/video/IOVideoDevice.h>

class IOVideoDeviceUserClient : public IOUserClient
{
    OSDeclareDefaultStructors( IOVideoDeviceUserClient )
    
protected:
    IOVideoDevice * _owner;
    task_t     _task;
    
public:
        virtual bool initWithTask(
                                  task_t owningTask, void * securityToken, UInt32 type,
                                  OSDictionary * properties);
    virtual bool initWithTask(
                              task_t owningTask, void * securityToken, UInt32 type);
    
    virtual IOReturn clientClose( void );
    virtual IOReturn clientDied( void );
    
    virtual IOService * getService( void );
    
#if 0
    virtual IOReturn registerNotificationPort(
                                              mach_port_t port, UInt32 type, UInt32 refCon );
#endif
    
    virtual IOReturn connectClient( IOUserClient * client );
    
    virtual IOExternalMethod * getTargetAndMethodForIndex(
                                                          IOService ** targetP, UInt32 index );
    
#if 0
    virtual IOExternalTrap *
        getTargetAndTrapForIndex( IOService **targetP, UInt32 index );
    
    virtual IOReturn clientMemoryForType( UInt32 type,
                                          IOOptionBits * options,
                                          IOMemoryDescriptor ** memory );
#endif
    
    virtual bool start( IOService * provider );
    virtual IOReturn setProperties( OSObject * properties );
    
    
protected:
    virtual IOReturn openMethod( void );
    virtual IOReturn closeMethod( void );
    virtual IOReturn startMethod( int streamIndex );
    virtual IOReturn stopMethod( int streamIndex );
    virtual IOReturn suspendMethod( int streamIndex );
    virtual IOReturn getModeMethod( int streamIndex, UInt32 * mode );
    virtual IOReturn setModeMethod( int streamIndex, UInt32 mode );
    
#if 0
    virtual IOReturn userTrap( UInt32 token );
    virtual IOReturn userSyncTrap( UInt32 token );
#endif
    
};

#endif /* ! __IOKIT_IOVIDEODEVICEUSERCLIENT_H */

