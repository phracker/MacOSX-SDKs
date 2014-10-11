#ifndef _IOFWDVCLIENT_H
#define _IOFWDVCLIENT_H
// UserClient commands
enum {
    kAVCCommand = 0,
    kDVReadStart,
    kDVReadStop,
    kDVReadExit,
    kDVWriteStart,
    kDVWriteStop,
    kDVSetWriteSignalMode,
    kDVGetNumOutputFrames,
    kDVSetNumOutputFrames,
    kDVGetDeviceTime,
    kDVMethods
};

#define kDVKernelDriverName		"IOFWDV"
#define kDVNumOutputFrames 20

typedef struct _IOFWDVSharedVars {
    UInt32			fVersion;
    volatile UInt32 fReader;
    volatile UInt32 fWriter;
    volatile UInt32 fDroppedFrames;
    volatile UInt32 fStatus;
    volatile UInt32 fFrameSize[kDVNumOutputFrames];
    volatile UInt8 fFrameStandard[kDVNumOutputFrames];
} IOFWDVSharedVars;

typedef struct _IOFWDVWriteGroupSharedData {
    volatile UInt32	fTimeStamp;		// Taken at end of block transmit
    UInt32			fDataOffset;	// into DCL data buffer
} IOFWDVWriteGroupSharedData;

typedef struct _IOFWDVWriteSharedData {
    UInt32 						fNumGroups;		// Number of blocks in DCL program
    UInt32 						fGroupSize;		// Number of data packets in DCL group
    UInt32						fAlignedPacketSize;	// Total packet size (offset from one to next)
    UInt32						fPacketDataSize;	// Size of DV data in packet
    IOFWDVWriteGroupSharedData	fGroupData[0];	// One for each group
} IOFWDVWriteSharedData;

enum {
    kDVRunning = 0,
    kDVStopped = 1,
    kDVWriteOverrun = 2,
    kDVReadOverrun = 3
};

#endif _IOFWDVCLIENT_H

