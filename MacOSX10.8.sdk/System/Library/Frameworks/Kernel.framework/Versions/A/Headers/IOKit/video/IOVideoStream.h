/*
	File:		IOVideoStream.h

	Contains:	

	Copyright:	© 2006-2010 by Apple Inc., all rights reserved.
*/

#ifndef __IOKIT_IOVIDEOSTREAM_H
#define __IOKIT_IOVIDEOSTREAM_H

#include <IOKit/stream/IOStream.h>

class IOVideoDevice;

class IOVideoStream : public IOStream
{
// Construction/Destruction
							OSDeclareDefaultStructors(IOVideoStream);

protected:
    IOStreamMode			mStreamMode;
    
public:
    static IOVideoStream*	withBuffers(OSArray* buffers, IOStreamMode mode = kIOStreamModeOutput, IOItemCount queueLength = 0, OSDictionary* properties = 0);    
    virtual bool			initWithBuffers(OSArray* buffers, IOStreamMode mode = kIOStreamModeOutput, IOItemCount queueLength = 0, OSDictionary* properties = 0);

    virtual IOVideoDevice*	getDevice(void);	// Returns provider cast to an IOVideoDevice
    
    virtual IOStreamMode	getStreamMode(void);
    virtual IOReturn		setStreamMode(IOStreamMode mode);

	virtual IOReturn		startStream(void);
    virtual IOReturn		stopStream(void);
    virtual IOReturn		suspendStream(void);

// Future Expansion
public:
    OSMetaClassDeclareReservedUnused(IOVideoStream, 0);
    OSMetaClassDeclareReservedUnused(IOVideoStream, 1);
    OSMetaClassDeclareReservedUnused(IOVideoStream, 2);
    OSMetaClassDeclareReservedUnused(IOVideoStream, 3);
    OSMetaClassDeclareReservedUnused(IOVideoStream, 4);
    OSMetaClassDeclareReservedUnused(IOVideoStream, 5);
    OSMetaClassDeclareReservedUnused(IOVideoStream, 6);
    OSMetaClassDeclareReservedUnused(IOVideoStream, 7);
    OSMetaClassDeclareReservedUnused(IOVideoStream, 8);
    OSMetaClassDeclareReservedUnused(IOVideoStream, 9);
    OSMetaClassDeclareReservedUnused(IOVideoStream, 10);
    OSMetaClassDeclareReservedUnused(IOVideoStream, 11);
    OSMetaClassDeclareReservedUnused(IOVideoStream, 12);
    OSMetaClassDeclareReservedUnused(IOVideoStream, 13);
    OSMetaClassDeclareReservedUnused(IOVideoStream, 14);
    OSMetaClassDeclareReservedUnused(IOVideoStream, 15);
    OSMetaClassDeclareReservedUnused(IOVideoStream, 16);
    OSMetaClassDeclareReservedUnused(IOVideoStream, 17);
    OSMetaClassDeclareReservedUnused(IOVideoStream, 18);
    OSMetaClassDeclareReservedUnused(IOVideoStream, 19);
    OSMetaClassDeclareReservedUnused(IOVideoStream, 20);
    OSMetaClassDeclareReservedUnused(IOVideoStream, 21);
    OSMetaClassDeclareReservedUnused(IOVideoStream, 22);
    OSMetaClassDeclareReservedUnused(IOVideoStream, 23);
    OSMetaClassDeclareReservedUnused(IOVideoStream, 24);
    OSMetaClassDeclareReservedUnused(IOVideoStream, 25);
    OSMetaClassDeclareReservedUnused(IOVideoStream, 26);
    OSMetaClassDeclareReservedUnused(IOVideoStream, 27);
    OSMetaClassDeclareReservedUnused(IOVideoStream, 28);
    OSMetaClassDeclareReservedUnused(IOVideoStream, 29);
    OSMetaClassDeclareReservedUnused(IOVideoStream, 30);
    OSMetaClassDeclareReservedUnused(IOVideoStream, 31);

protected:
    struct ExpansionData {};
    ExpansionData			*mReserved;
};

#endif
