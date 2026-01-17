/*
 *  IOVideoStream.h
 *  IOVideoFamily
 *
 *  Copyright 2006 Apple Computer, Inc. All rights reserved.
 *
 */

#ifndef __IOKIT_IOVIDEOSTREAM_H
#define __IOKIT_IOVIDEOSTREAM_H

#include <IOKit/stream/IOStream.h>

class IOVideoDevice;


class IOVideoStream : public IOStream
{
    OSDeclareDefaultStructors(IOVideoStream);

protected:
    IOStreamMode                 _streamMode;
    
public:
    
    /*!
    @functiongroup Creating IOVideoStream objects
     */
    
    /*!
    @function withBuffers
     @param buffers
     @param properties
     */
    
    static IOVideoStream *withBuffers(OSArray *buffers, IOStreamMode mode = kIOStreamModeOutput, IOItemCount queueLength = 0, OSDictionary *properties = 0);
    
    
    virtual bool initWithBuffers(OSArray *buffers, IOStreamMode mode = kIOStreamModeOutput, IOItemCount queueLength = 0, OSDictionary *properties = 0);

    // Returns provider cast to an IOVideoDevice.
    virtual IOVideoDevice *         getDevice(void);
    
    virtual IOStreamMode            getStreamMode(void);
    virtual IOReturn                setStreamMode(IOStreamMode mode);

    
    virtual IOReturn startStream(void);
    virtual IOReturn stopStream(void);
    virtual IOReturn suspendStream(void);
};

#endif /* !__IOKIT_IOVIDEOSTREAM_H */