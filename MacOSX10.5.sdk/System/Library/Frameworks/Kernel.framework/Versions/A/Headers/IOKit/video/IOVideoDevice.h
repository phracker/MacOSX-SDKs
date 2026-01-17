/*
 *  Copyright 2006 Apple Computer, Inc. All rights reserved.
 *
 */
#if !defined(__IOKIT_IOVIDEODEVICE_H)
#define __IOKIT_IOVIDEODEVICE_H

#include <IOKit/IOService.h>
#include <IOKit/stream/IOStream.h>

#include <IOKit/video/IOVideoStream.h>

class IOVideoDevice : public IOService
{
    OSDeclareDefaultStructors(IOVideoDevice);

protected:
    OSArray *               _streams;       // IOStreams for this device.

public:
    virtual void free(void);
    
    // Streams
    virtual int getStreamCount(void);
    virtual IOVideoStream *getStream(int streamIndex);
    
    virtual IOReturn startStream(IOVideoStream *stream);
    virtual IOReturn stopStream(IOVideoStream *stream);
    virtual IOReturn suspendStream(IOVideoStream *stream);
    
    virtual IOReturn setStreamMode(IOVideoStream *stream, IOStreamMode mode);

    virtual IOReturn startStream(int streamIndex);
    virtual IOReturn stopStream(int streamIndex);
    virtual IOReturn suspendStream(int streamIndex);
    
    virtual IOReturn createStreams(void);
    virtual IOReturn addStream(IOVideoStream *stream);
    virtual IOReturn removeStream(int streamIndex);

    virtual IOReturn releaseStreams(void);
    
    // Control methods
    // XXX
    
    // Property methods
    // XXX
};

#endif /* __IOKIT_IOVIDEODEVICE_H */
