/*
    File:       CMIOHardwareDevice.h

    Contains:   API for communicating with CoreMediaIO hardware

    Copyright:  © 2005-2018 by Apple Inc., all rights reserved.
*/


#if !defined(__CMIOHardwareDevice_h__)
#define __CMIOHardwareDevice_h__

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#pragma mark Overview
/*!
    @header CMIOHardwareDevice
    Instances of the CMIODevice class encapsulate individual media devices.
    
    CMIODevices contain at least one instance of the CMIOStream class, and may contain instances of the CMIOControl class or it's many subclasses.
*/

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#pragma mark Includes

#include <CoreMediaIO/CMIOHardwareObject.h>
#include <CoreMediaIO/CMIOHardwareStream.h>

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


#if defined(__cplusplus)
extern "C"
{
#endif
    
#pragma pack(push, 4)

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#pragma mark CMIODevice Types

/*!
    @typedef        CMIODeviceID
    @abstract       CMIODevice is the base class for all objects that represent a CMIO device.
    @discussion     CMIODevice is a subclass of CMIOObject. CMIODevices normally contain CMIOStreams and CMIOControls.
*/
typedef CMIOObjectID CMIODeviceID;

/*!
    @typedef        CMIODevicePropertyID
    @abstract       A CMIODevicePropertyID is an integer that identifies a specific piece of information about the object.
*/
typedef CMIOObjectPropertySelector CMIODevicePropertyID;


/*!
    @struct         CMIODeviceStreamConfiguration
    @abstract       This structure describes the list of streams and the number of channels in each stream.
    @field          mNumberStreams
                        The number of streams being described.
    @field          mNumberChannels
                        An array of UInt32's whose length is specified by mNumberStreams. Each element of the array corresponds to a stream and indicates the number of channels it has.
*/
struct CMIODeviceStreamConfiguration
{
    UInt32  mNumberStreams;
    UInt32  mNumberChannels[];
} API_AVAILABLE(macos(10.7));
typedef struct CMIODeviceStreamConfiguration CMIODeviceStreamConfiguration;


/*!
    @struct         CMIODeviceAVCCommand
    @abstract       This structure allows an AVC command to be sent to a device. This is not intended to be a general purpose command interfaces, rather only for those devices which can
                    support the "AV/C Digital Interface Command Set General Specification Version 4.1" (1394 Trade Association Document 2001012). Devices indicate whether or not they can
                    process AVC commands via the kCMIODevicePropertyCanProcessAVCCommand property.
    @field          mCommand
                        The buffer containing the AVC command bytes.
    @field          mCommandLength
                        The size (in bytes) of the mCommand buffer.
    @field          mResponse
                        The buffer for returning the response bytes.
    @field          mResponseLength
                        The size (in bytes) of the mResponse buffer.
    @field          mResponseUsed
                        The size (in bytes) of the actual number response bytes returned.
*/
struct CMIODeviceAVCCommand
{
    UInt8*  mCommand;
    UInt32  mCommandLength;
    UInt8*  mResponse;
    UInt32  mResponseLength;
    UInt32  mResponseUsed;
} API_AVAILABLE(macos(10.7));
typedef struct CMIODeviceAVCCommand CMIODeviceAVCCommand;

/*!
    @struct         CMIODeviceRS422Command
    @abstract       This structure allows an RS422 command to be sent to a device. This is not intended to be a general purpose command interface, rather only for those devices which can
                    support the RS422 protocol. Devices indicate whether or not they can process RS422 commands via the kCMIODevicePropertyCanProcessRS422Command property.
    @field          mCommand
                        The buffer containing the RS422 command bytes.
    @field          mCommandLength
                        The size (in bytes) of the mCommand buffer.
    @field          mResponse
                        The buffer for returning the response bytes.
    @field          mResponseLength
                        The size (in bytes) of the mResponse buffer.
    @field          mResponseUsed
                        The size (in bytes) of the actual number response bytes returned.
*/
struct CMIODeviceRS422Command
{
    UInt8*  mCommand;
    UInt32  mCommandLength;
    UInt8*  mResponse;
    UInt32  mResponseLength;
    UInt32  mResponseUsed;
} API_AVAILABLE(macos(10.7));
typedef struct CMIODeviceRS422Command CMIODeviceRS422Command;


/*!
    @typedef        CMIODeviceGetSMPTETimeProc
    @abstract       Clients register a CMIODeviceGetSMPTETimeProc to specify a routine for the a device to call when it needs SMPTE timecode information. Some devices require
                    external means known only to their client to provide SMPTE timecode information (for example, devices conforming to the HDV-1 standard do not provide SMPTE timecode
                    information in the HDV datastream); the HDV device driver may call a provided SMPTE timecode callback when it needs the data.
    @discussion     The SMPTE time callback is invoked by the device when it needs SMPTE timecode information. The callback should be very low latency, as it may be called on a real-time
                    thread; as such, it may need to rely on a private thread to obtain the values it returns. It is understood that the callback may be obtaining its values in a manner
                    asynchronous to when the device requires it, and as such, there will be jitter in the values; sometimes a value will be repeated, sometimes a value skipped, depending
                    upon the cadence of the threads involved.
    @param          refCon
                        A pointer to client data established when the proc was registered via setting the kCMIODevicePropertySMPTETimeCallback property.
    @param          frameNumber
                        The current frame count.
    @param          isDropFrame
                        True when the frame count is drop frame based (two frames of time code are dropped every minute, on the minute, except every tenth minute), false otherwise.
    @param          tolerance
                        The maximum amount of jitter expected in the frame count. Differences observed outside of this value are an indication of dropped data.
    @result         An OSStatus indicating success or failure.


*/
typedef OSStatus
(*CMIODeviceGetSMPTETimeProc)(void* refCon, UInt64* frameNumber, Boolean* isDropFrame, UInt32* tolerance);

/*!
    @struct         CMIODeviceSMPTETimeCallback
    @abstract       This structure allows a client to specify a CMIODeviceGetSMPTETimeProc and its associated private data via the kCMIODevicePropertySMPTETimeCallback property. 
    @field          mGetSMPTETimeProc
                        The CMIODeviceGetSMPTETimeProc to invoke when SMPTE timecode information is needed.
    @field          mRefCon
                        Client supplied private provided when the kCMIODevicePropertySMPTETimeCallback property was set.
*/
struct CMIODeviceSMPTETimeCallback
{
    CMIODeviceGetSMPTETimeProc  mGetSMPTETimeProc;
    void*                       mRefCon;
} API_AVAILABLE(macos(10.7));
typedef struct CMIODeviceSMPTETimeCallback CMIODeviceSMPTETimeCallback;


//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#pragma mark CMIODevice Constants

/*!
    @enum           CMIODevice Class Constants
    @abstract       Various constants related to CMIODevices.
    @discussion     
    @constant       kCMIODevicePropertyScopeInput
                        The CMIOObjectPropertyScope for properties that apply to the input signal paths of the CMIODevice.
    @constant       kCMIODevicePropertyScopeOutput
                        The CMIOObjectPropertyScope for properties that apply to the output signal paths of the CMIODevice.
    @constant       kCMIODevicePropertyScopePlayThrough
                        The CMIOObjectPropertyScope for properties that apply to the play through signal paths of the CMIODevice.
    @constant       kCMIODeviceClassID
                        The CMIOClassID that identifies the CMIODevice class.
    @constant       kCMIODeviceUnknown
                        The CMIOObjectID for a nonexistent CMIOObject.
*/
enum
{
    kCMIODevicePropertyScopeInput       = 'inpt',
    kCMIODevicePropertyScopeOutput      = 'outp',
    kCMIODevicePropertyScopePlayThrough = 'ptru',
    kCMIODeviceClassID                  = 'adev',
    kCMIODeviceUnknown                  = kCMIOObjectUnknown
};

/*!
    @enum           AVC Device Types
    @abstract       Constants for use with the kCMIODevicePropertyAVCDeviceType property.
    @discussion     
    @constant       kCMIOAVCDeviceType_Unknown
                        Though the device reports it has an AVC unit, no further information is known. 
    @constant       kCMIOAVCDeviceType_DV_NTSC
                        The device is DV NTSC.
    @constant       kCMIOAVCDeviceType_DV_PAL
                        The device is DV PAL.
    @constant       kCMIOAVCDeviceType_DVCPro_NTSC
                        The device is DVCPro NTSC.
    @constant       kCMIOAVCDeviceType_DVCPro_PAL
                        The device is DVCPro PAL.
    @constant       kCMIOAVCDeviceType_DVCPro50_NTSC
                        The device is DVCPro50 NTSC.
    @constant       kCMIOAVCDeviceType_DVCPro50_PAL
                        The device is DVCPro50 PAL.
    @constant       kCMIOAVCDeviceType_DVCPro100_NTSC
                        The device is DVCPro100 NTSC.
    @constant       kCMIOAVCDeviceType_DVCPro100_PAL
                        The device is DVCPro100 PAL.
    @constant       kCMIOAVCDeviceType_DVCPro100_720p
                        The device is DVCPro100 720p.
    @constant       kCMIOAVCDeviceType_DVCProHD_1080i50
                        The device is DVCProHD 1080i50.
    @constant       kCMIOAVCDeviceType_DVCProHD_1080i60
                        The device is DVCProHD 1080i.
    @constant       kCMIOAVCDeviceType_MPEG2
                        The device is MPEG2.
*/
enum
{
    kCMIOAVCDeviceType_Unknown          = 'unkn',
    kCMIOAVCDeviceType_DV_NTSC          = 'dvc ',
    kCMIOAVCDeviceType_DV_PAL           = 'dvcp',
    kCMIOAVCDeviceType_DVCPro_NTSC      = 'dvpn',
    kCMIOAVCDeviceType_DVCPro_PAL       = 'dvpp',
    kCMIOAVCDeviceType_DVCPro50_NTSC    = 'dv5n',
    kCMIOAVCDeviceType_DVCPro50_PAL     = 'dv5p',
    kCMIOAVCDeviceType_DVCPro100_NTSC   = 'dv1n',
    kCMIOAVCDeviceType_DVCPro100_PAL    = 'dv1p',
    kCMIOAVCDeviceType_DVCPro100_720p   = 'dvhp',
    kCMIOAVCDeviceType_DVCProHD_1080i50 = 'dvh5',
    kCMIOAVCDeviceType_DVCProHD_1080i60 = 'dvh6',
    kCMIOAVCDeviceType_MPEG2            = 'mpg2'
};

/*!
    @enum           AVC Tape Signal Mode Types
    @abstract       Constants for use with the kCMIODevicePropertyAVCDeviceSignalMode property
    @discussion     
    @constant       kCMIODeviceAVCSignalModeSD525_60
                        DVCR Std Defn 525/60
    @constant       kCMIODeviceAVCSignalModeSDL525_60
                        DVCR Std Defn L 525/60
    @constant       kCMIODeviceAVCSignalModeHD1125_60
                        DVCR High Defn 1125/60
    @constant       kCMIODeviceAVCSignalModeSD625_50
                        DVCR Std Defn 625/50
    @constant       kCMIODeviceAVCSignalModeSDL625_50
                        DVCR Std Defn L 625/50
    @constant       kCMIODeviceAVCSignalModeHD1250_50
                        DVCR High Defn 1250/50
    @constant       kCMIODeviceAVCSignalModeMPEG25Mbps_60
                        DVCR MPEG 25Mbps/60
    @constant       kCMIODeviceAVCSignalModeHDV1_60
                        HDV1 /60
    @constant       kCMIODeviceAVCSignalModeMPEG12Mbps_60
                        DVCR MPEG 12.5Mbps/60
    @constant       kCMIODeviceAVCSignalModeMPEG6Mbps_60
                        DVCR MPEG 6.25Mbps/60
    @constant       kCMIODeviceAVCSignalModeMPEG25Mbps_50
                        DVCR MPEG 25Mbps/50
    @constant       kCMIODeviceAVCSignalModeHDV1_50
                         HDV1 /50
    @constant       kCMIODeviceAVCSignalModeMPEG12Mbps_50
                        DVCR MPEG 12/5Mbps/50
    @constant       kCMIODeviceAVCSignalModeMPEG6Mbps_50
                        DVCR MPEG 6.25Mbps/50
    @constant       kCMIODeviceAVCSignalModeDVHS
                        D-VHS
    @constant       kCMIODeviceAVCSignalModeVHSNTSC
                        Analog VHS NTSC 525/60
    @constant       kCMIODeviceAVCSignalModeVHSMPAL
                        Analog VHS M-PAL 525/60
    @constant       kCMIODeviceAVCSignalModeVHSPAL
                        Analog VHS PAL 625/50
    @constant       kCMIODeviceAVCSignalModeVHSNPAL
                        Analog VHS N-PAL 625/50
    @constant       kCMIODeviceAVCSignalModeVHSSECAM
                        Analog VHS SECAM 625/50
    @constant       kCMIODeviceAVCSignalModeVHSMESECAM
                        Analog VHS ME-SECAM 625
    @constant       kCMIODeviceAVCSignalModeSVHS525_60
                        Analog S-VHS 525/60
    @constant       kCMIODeviceAVCSignalModeSVHS625_50
                        Analog S-VHS 625/50
    @constant       kCMIODeviceAVCSignalMode8mmNTSC
                        Analog 8mm NTSC
    @constant       kCMIODeviceAVCSignalMode8mmPAL
                        Analog 8mm PAL
    @constant       kCMIODeviceAVCSignalModeHi8NTSC
                        Analog Hi8 NTSC
    @constant       kCMIODeviceAVCSignalModeHi8PAL
                        Analog Hi8 PAL
    @constant       kCMIODeviceAVCSignalModeMicroMV12Mbps_60
                        MicroMV 12.5Mbps/60
    @constant       kCMIODeviceAVCSignalModeMicroMV6Mbps_60
                        MicroMV 6.25Mbps/60
    @constant       kCMIODeviceAVCSignalModeMicroMV12Mbps_50
                        MicroMV 12.5Mbps/50
    @constant       kCMIODeviceAVCSignalModeMicroMV6Mbps_50
                        MicroMV 6.25Mbps/50
    @constant       kCMIODeviceAVCSignalModeAudio
                        Audio
    @constant       kCMIODeviceAVCSignalModeHDV2_60
                        HDV2 /60
    @constant       kCMIODeviceAVCSignalModeHDV2_50
                        HDV2 /50
    @constant       kCMIODeviceAVCSignalModeDVCPro25_625_50
                        DVCPro25_625_50
    @constant       kCMIODeviceAVCSignalModeDVCPro25_525_60
                        DVCPro25_525_60
    @constant       kCMIODeviceAVCSignalModeDVCPro50_625_50
                        DVCPro50_625_50
    @constant       kCMIODeviceAVCSignalModeDVCPro50_525_60
                        DVCPro50_525_60
    @constant       kCMIODeviceAVCSignalModeDVCPro100_50
                        DVCPro100_50
    @constant       kCMIODeviceAVCSignalModeDVCPro100_60
                        DVCPro100_60
*/
enum
{
    kCMIODeviceAVCSignalModeSD525_60            = 0x00, 
    kCMIODeviceAVCSignalModeSDL525_60           = 0x04, 
    kCMIODeviceAVCSignalModeHD1125_60           = 0x08, 
    kCMIODeviceAVCSignalModeSD625_50            = 0x80, 
    kCMIODeviceAVCSignalModeSDL625_50           = 0x84, 
    kCMIODeviceAVCSignalModeHD1250_50           = 0x88, 
    kCMIODeviceAVCSignalModeMPEG25Mbps_60       = 0x10, 
    kCMIODeviceAVCSignalModeHDV1_60             = 0x10, 
    kCMIODeviceAVCSignalModeMPEG12Mbps_60       = 0x14, 
    kCMIODeviceAVCSignalModeMPEG6Mbps_60        = 0x18, 
    kCMIODeviceAVCSignalModeMPEG25Mbps_50       = 0x90, 
    kCMIODeviceAVCSignalModeHDV1_50             = 0x90, 
    kCMIODeviceAVCSignalModeMPEG12Mbps_50       = 0x94, 
    kCMIODeviceAVCSignalModeMPEG6Mbps_50        = 0x98, 
    kCMIODeviceAVCSignalModeDVHS                = 0x01, 
    kCMIODeviceAVCSignalModeVHSNTSC             = 0x05, 
    kCMIODeviceAVCSignalModeVHSMPAL             = 0x25, 
    kCMIODeviceAVCSignalModeVHSPAL              = 0xa5, 
    kCMIODeviceAVCSignalModeVHSNPAL             = 0xb5, 
    kCMIODeviceAVCSignalModeVHSSECAM            = 0xc5, 
    kCMIODeviceAVCSignalModeVHSMESECAM          = 0xd5, 
    kCMIODeviceAVCSignalModeSVHS525_60          = 0x0d, 
    kCMIODeviceAVCSignalModeSVHS625_50          = 0xed, 
    kCMIODeviceAVCSignalMode8mmNTSC             = 0x06, 
    kCMIODeviceAVCSignalMode8mmPAL              = 0x86, 
    kCMIODeviceAVCSignalModeHi8NTSC             = 0x0e, 
    kCMIODeviceAVCSignalModeHi8PAL              = 0x8e, 
    kCMIODeviceAVCSignalModeMicroMV12Mbps_60    = 0x24, 
    kCMIODeviceAVCSignalModeMicroMV6Mbps_60     = 0x28, 
    kCMIODeviceAVCSignalModeMicroMV12Mbps_50    = 0xA4, 
    kCMIODeviceAVCSignalModeMicroMV6Mbps_50     = 0xA8, 
    kCMIODeviceAVCSignalModeAudio               = 0x20, 
    kCMIODeviceAVCSignalModeHDV2_60             = 0x1A, 
    kCMIODeviceAVCSignalModeHDV2_50             = 0x9A, 
    kCMIODeviceAVCSignalModeDVCPro25_625_50     = 0xF8, 
    kCMIODeviceAVCSignalModeDVCPro25_525_60     = 0x78, 
    kCMIODeviceAVCSignalModeDVCPro50_625_50     = 0xF4, 
    kCMIODeviceAVCSignalModeDVCPro50_525_60     = 0x74, 
    kCMIODeviceAVCSignalModeDVCPro100_50        = 0xF0, 
    kCMIODeviceAVCSignalModeDVCPro100_60        = 0x70
};

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#pragma mark CMIODevice Properties

/*!
    @enum           CMIODevice Properties
    @abstract       CMIOObjectPropertySelector values that apply to CMIODevice objects.
    @discussion     CMIODevices have four scopes: kCMIOObjectPropertyScopeGlobal, kCMIODevicePropertyScopeInput, kCMIODevicePropertyScopeOutput, and kCMIODevicePropertyScopePlayThrough.
                    They have a master element and an element for each channel in each stream numbered according to the starting channel number of each stream.
    @constant       kCMIODevicePropertyPlugIn
                        The CMIOObjectID of the CMIOPlugIn that is hosting the device.
    @constant       kCMIODevicePropertyDeviceUID
                        A CFString that contains a persistent identifier for the CMIODevice. A CMIODevice's UID is persistent across boots. The content of the UID string is a black box
                        and may contain information that is unique to a particular instance of a CMIODevice's hardware or unique to the CPU. Therefore they are not suitable for passing
                        between CPUs or for identifying similar models of hardware. The caller is responsible for releasing the returned CFObject.
    @constant       kCMIODevicePropertyModelUID
                        A CFString that contains a persistent identifier for the model of a CMIODevice. The identifier is unique such that the identifier from two CMIODevices are equal
                        if and only if the two CMIODevices are the exact same model from the same manufacturer. Further, the identifier has to be the same no matter on what machine the
                        CMIODevice appears. The caller is responsible for releasing the returned CFObject.
    @constant       kCMIODevicePropertyTransportType
                        A UInt32 whose value indicates how the CMIODevice is connected to the CPU. Constants for some of the values for this property can be found in
                        <IOKit/audio/IOAudioTypes.h>.
    @constant       kCMIODevicePropertyDeviceIsAlive
                        A UInt32 where a value of 1 means the device is ready and available and 0 means the device is unusable and will most likely go away shortly.
    @constant       kCMIODevicePropertyDeviceHasChanged
                        The type of this property is a UInt32, but it's value has no meaning. This property exists so that clients can listen to it and be told when the configuration of the
                        CMIODevice has changed in ways that cannot otherwise be conveyed through other notifications. In response to this notification, clients should re-evaluate
                        everything they need to know about the device, particularly the layout and values of the controls.
    @constant       kCMIODevicePropertyDeviceIsRunning
                        A UInt32 where a value of 0 means the CMIODevice is not performing IO and a value of 1 means that it is.
    @constant       kCMIODevicePropertyDeviceIsRunningSomewhere
                        A UInt32 where 1 means that the CMIODevice is running in at least one process on the system and 0 means that it isn't running at all.
    @constant       kCMIODevicePropertyDeviceCanBeDefaultDevice
                        A UInt32 where 1 means that the CMIODevice is a possible selection for kCMIOHardwarePropertyDefaultInputDevice or kCMIOHardwarePropertyDefaultOutputDevice
                        depending on the scope.
    @constant       kCMIODevicePropertyHogMode
                        A pid_t indicating the process that currently owns exclusive access to the CMIODevice or a value of -1 indicating that the device is currently available to all
                        processes.
    @constant       kCMIODevicePropertyLatency
                        A UInt32 containing the number of frames of latency in the CMIODevice. Note that input and output latency may differ. Further, the CMIODevice's CMIOStreams
                        may have additional latency so they should be queried as well. If both the device and the stream say they have latency, then the total latency for the stream is the
                        device latency summed with the stream latency.
    @constant       kCMIODevicePropertyStreams
                        An array of CMIOStreamIDs that represent the CMIOStreams of the CMIODevice. Note that if a notification is received for this property, any cached
                        CMIOStreamIDs for the device become invalid and need to be re-fetched.
    @constant       kCMIODevicePropertyStreamConfiguration
                        This property returns the stream configuration of the device in a CMIODeviceStreamConfiguration which describes the list of streams and the number of channels in
                        each stream.
    @constant       kCMIODevicePropertyDeviceMaster
                        A pid_t indicating the process that currently owns exclusive rights to change operating properties of the device. A value of -1 indicating that the device is not
                        currently under the control of a master.
    @constant       kCMIODevicePropertyExcludeNonDALAccess
                        A UInt32 where a value of 0 means the CMIODevice can be accessed by means other than the DAL, and a value of 1 means that it can't.
                        For example, this could be set to 1 to prevent a QuickTime video digitizer component from accessing the device even when the DAL is not actively using it.
                        This property is ONLY present for devices whose kCMIODevicePropertyHogMode is NOT settable. 
                        IMPORTANT NOTE:  If there are multiple CMIOPlugIns which support a given device, setting this property to 1 might exclude it being accessed by the other
                        CMIOPlugIns as well.
    @constant       kCMIODevicePropertyClientSyncDiscontinuity
                        A Boolean that may be set by a client to direct the driver to flush its internal state. Some devices (such as HDV devices) require the driver's internal state
                        to be built up in order to start delivering buffers. A client manipulating a device in preparation for a task may build up internal state that is not to be a part of
                        the task. For example, moving an HDV device transport to queue up to a known SMPTE timecode in order to capture data from after that point; the internal state built-up
                        during the queing is not to be used in the actual capture session. In this case, the client would set this property to TRUE after the device has been queued and then
                        set to play.
    @constant       kCMIODevicePropertySMPTETimeCallback
                        A CMIODeviceSMPTETimeCallback structure that specifies a routine for the driver to call when it needs SMPTE timecode information. Some devices require external means
                        known only to their client to provide SMPTE timecode information (for example, devices conforming to the HDV-1 standard do not provide SMPTE timecode information in
                        the HDV datastream); the HDV device driver may call a provided SMPTE timecode callback when it needs the data.
    @constant       kCMIODevicePropertyCanProcessAVCCommand
                        A Boolean that indicates whether or not the device can process AVC commands. This property is never settable.
    @constant       kCMIODevicePropertyAVCDeviceType
                        A UInt32 that reports the AVC device type. This propery is only present for devices which conform to the AVC class.
    @constant       kCMIODevicePropertyAVCDeviceSignalMode
                        A UInt32 that reports the streaming modes of the AVC device. This propery is only present for devices which conform to the AVC class.
    @constant       kCMIODevicePropertyCanProcessRS422Command
                        A Boolean that indicates whether or not the device can process RS422 commands. This property is never settable.
    @constant       kCMIODevicePropertyLinkedCoreAudioDeviceUID
                        Some CMIODevices implement an audio engine as a separate device (such as the FireWire iSight). This property allows a CMIODevice to identify a linked CoreAudio
                        device by UID (CFStringRef)
    @constant       kCMIODevicePropertyVideoDigitizerComponents
                        An array of ComponentDescriptions of the video digitizers which control the device. A client which is using QuickTime's Sequence Grabber & CMIO's DAL can examine
                        this property to prune the list of video digitizers used, thus avoiding having a device represented in both domains. (Most devices which implement this property will
                        only report a single video digitizer, but it is possible that more than one might be reported.)
    @constant       kCMIODevicePropertySuspendedByUser
                        A UInt32 where a value of 0 indicates the device is not suspended due to a user action, and a value of 1 means that it is.
                        For example, the user might close the FireWire iSight's privacy iris or close the clamshell on a Mac Book or Mac Book Pro. While suspended the device still responds
                        to all requests just as if it was active, but the stream(s) will not provide/accept any data.
                        This property is never settable.
    @constant       kCMIODevicePropertyLinkedAndSyncedCoreAudioDeviceUID
                        Identical to kCMIODevicePropertyLinkedCoreAudioDeviceUID, except that it only returns a UID if the linked CoreAudio device shares the same hardware clock (CFStringRef)
    @constant       kCMIODevicePropertyIIDCInitialUnitSpace
                        A UInt32 which specifies the initial unit space for IIDC cameras as described in "IIDC 1394-based Digital Camera Specification Version 1.31" (1394 Trade Association
                        Document 2003017)." This property is never settable.
    @constant       kCMIODevicePropertyIIDCCSRData
                        A UInt32 which provides access to control and status registers for IIDC cameras. The qualifier contains a UInt32 that specifies the register to access.
                        If the register's offset is relative to the initial unit space, then the qualifier should be the value returned by kCMIODevicePropertyIIDCInitialUnitSpace + offset.
                        If the register's offset is relative to the initial register space, then the qualifier should be $F0000000 + offset.
                        Changes in this property never result in a property changed notification.
    @constant       kCMIODevicePropertyCanSwitchFrameRatesWithoutFrameDrops
                        A UInt32 where a value of 0 indicates the device's streams will drop frames when altering frame rates, and a value of 1 means that they won't.
    @constant       kCMIODevicePropertyLocation
                        A UInt32 indicating the location of the device (for values see kCMIODevicePropertyLocationUnknown, etc., below).
    @constant       kCMIODevicePropertyDeviceHasStreamingError
                        A UInt32 where 1 means that the CMIODevice failed to stream.
*/
enum
{
    kCMIODevicePropertyPlugIn                               = 'plug',
    kCMIODevicePropertyDeviceUID                            = 'uid ',
    kCMIODevicePropertyModelUID                             = 'muid',
    kCMIODevicePropertyTransportType                        = 'tran',
    kCMIODevicePropertyDeviceIsAlive                        = 'livn',
    kCMIODevicePropertyDeviceHasChanged                     = 'diff',
    kCMIODevicePropertyDeviceIsRunning                      = 'goin',
    kCMIODevicePropertyDeviceIsRunningSomewhere             = 'gone',
    kCMIODevicePropertyDeviceCanBeDefaultDevice             = 'dflt',
    kCMIODevicePropertyHogMode                              = 'oink',
    kCMIODevicePropertyLatency                              = 'ltnc',
    kCMIODevicePropertyStreams                              = 'stm#',
    kCMIODevicePropertyStreamConfiguration                  = 'slay',
    kCMIODevicePropertyDeviceMaster                         = 'pmnh',
    kCMIODevicePropertyExcludeNonDALAccess                  = 'ixna',
    kCMIODevicePropertyClientSyncDiscontinuity              = 'pmcs',
    kCMIODevicePropertySMPTETimeCallback                    = 'pmsc',
    kCMIODevicePropertyCanProcessAVCCommand                 = 'pmac',
    kCMIODevicePropertyAVCDeviceType                        = 'pmat',
    kCMIODevicePropertyAVCDeviceSignalMode                  = 'pmsm',
    kCMIODevicePropertyCanProcessRS422Command               = 'r422',
    kCMIODevicePropertyLinkedCoreAudioDeviceUID             = 'plud',
    kCMIODevicePropertyVideoDigitizerComponents             = 'vdig',
    kCMIODevicePropertySuspendedByUser                      = 'sbyu',
    kCMIODevicePropertyLinkedAndSyncedCoreAudioDeviceUID    = 'plsd',
    kCMIODevicePropertyIIDCInitialUnitSpace                 = 'iuns',
    kCMIODevicePropertyIIDCCSRData                          = 'csrd',
    kCMIODevicePropertyCanSwitchFrameRatesWithoutFrameDrops = 'frnd',
    kCMIODevicePropertyLocation                             = 'dloc',
    kCMIODevicePropertyDeviceHasStreamingError              = 'serr',
};

/*!
    @enum           kCMIODevicePropertyLocation Values
    @abstract       The kCMIODevicePropertyLocation returns an indication of the device's physical placement.
    @constant       kCMIODevicePropertyLocationUnknown
                        The device location is unknown.
    @constant       kCMIODevicePropertyLocationBuiltInDisplay
                        The device is located in the computer's built-in display.
    @constant       kCMIODevicePropertyLocationExternalDisplay
                        The device is located in an external display.
    @constant       kCMIODevicePropertyLocationExternalDevice
                        The device is an external to the computer and connected with a cable.
    @constant       kCMIODevicePropertyLocationExternalWirelessDevice
                        The device is an external to the computer and connected via a wireless protocol.
*/
enum
{
    kCMIODevicePropertyLocationUnknown = 0,
    kCMIODevicePropertyLocationBuiltInDisplay = 1,
    kCMIODevicePropertyLocationExternalDisplay = 2,
    kCMIODevicePropertyLocationExternalDevice = 3,
    kCMIODevicePropertyLocationExternalWirelessDevice = 4,
};

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#pragma mark CMIODevice Functions

/*!
    @functiongroup  CMIODevice
*/

/*!
    @function       CMIODeviceStartStream
    @abstract       Starts the indicated CMIOStream of the specified CMIODevice.
    @param          deviceID
                        The CMIODevice that owns the CMIOStream.
    @param          streamID
                        The CMIOStream to start.
    @result         An OSStatus indicating success or failure.
*/
extern OSStatus
CMIODeviceStartStream(  CMIODeviceID    deviceID,
                        CMIOStreamID    streamID) API_AVAILABLE(macos(10.7));

/*!
    @function       CMIODeviceStopStream
    @abstract       Stops the indicated CMIOStream.
    @param          deviceID
                        The CMIODevice that owns the CMIOStream.
    @param          streamID
                        The CMIOStream to stop.
    @result         An OSStatus indicating success or failure.
*/
extern OSStatus
CMIODeviceStopStream(   CMIODeviceID    deviceID,
                        CMIOStreamID    streamID) API_AVAILABLE(macos(10.7));

/*!
    @function       CMIODeviceProcessAVCCommand
    @abstract       Allows an AVC command to be sent to a device for processing. This is not intended to be a general purpose command interface, rather only for those devices which can
                    support the "AV/C Digital Interface Command Set General Specification Version 4.1" (1394 Trade Association Document 2001012). Devices indicate whether or not they can
                    process AVC commands via the kCMIODevicePropertyCanProcessAVCCommand property.
    @param          deviceID
                        The CMIODevice for which the command is intended.
    @param          ioAVCCommand
                        The CMIODeviceAVCCommand to send to the device.
    @result         An OSStatus indicating success or failure of the command processing.
*/
extern OSStatus
CMIODeviceProcessAVCCommand(    CMIODeviceID            deviceID,
                                CMIODeviceAVCCommand*   ioAVCCommand) API_AVAILABLE(macos(10.7));

/*!
    @function       CMIODeviceProcessRS422Command
    @abstract       Allows an RS422 command to be sent to a device for processing. This is not intended to be a general purpose command interface, rather only for those devices which can
                    support the RS422 protocol. Devices indicate whether or not they can process RS422 commands via the kCMIODevicePropertyCanProcessRS422Command property.
    @param          deviceID
                        The CMIODevice for which the command is intended.
    @param          ioRS422Command
                        The CMIODeviceRS422Command to send to the device.
    @result         An OSStatus indicating success or failure of the command processing.
*/
extern OSStatus
CMIODeviceProcessRS422Command(  CMIODeviceID            deviceID,
                                CMIODeviceRS422Command* ioRS422Command) API_AVAILABLE(macos(10.7));

#pragma pack(pop)
    
#if defined(__cplusplus)
}
#endif
#endif
