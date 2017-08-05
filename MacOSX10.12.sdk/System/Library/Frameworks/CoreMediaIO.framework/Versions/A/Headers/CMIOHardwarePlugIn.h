/*
     File:       CMIOHardwarePlugIn.h
 
     Contains:   API for the CFPlugIn that implements an CMIO driver for the DAL from user space
 
     Copyright:  © 2004-2010 by Apple Inc., all rights reserved.
*/

#if !defined(__CMIOHardwarePlugIn_h__)
#define __CMIOHardwarePlugIn_h__

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#pragma mark    Overview

/*!
    @header CMIOHardwarePlugIn
    This is the CFPlugIn interface presented by a DAL plug-in. The DAL will create only one instance of each interface. This instance is responsible for providing all required services on
    behalf of as many devices of the kind it implements.

    The Initialize method is called to allow the plug-in to set itself up. At this time any devices of it's kind and their streams can be presented to the system using
    CMIOHardwareDevicesCreated() and CMIOHardwareStreamsCreated(). The plug-in is also responsible for managing it's own notifications, and may install any CFRunLoopSources.

    Teardown() is called when the DAL is unloading itself and the plug-in should dispose of any devices and streams it has created using CMIOHardwareDevicesDied() and
    CMIOHardareStreamsDied().

    The rest of the methods in this interface correspond to the semantics of their similarly named counterparts in <CoreMediaIO/CMIOHardware.h>. The DAL basically passes these calls directly
    to the plug-in in this fashion.

    Plug-ins do not have to manage device or stream property listener procs. Instead, a plug-in can call CMIOHardwareDevicePropertyChanged() or CMIOHardwareStreamPropertyChanged() and
    the DAL will take care of calling all the appropriate listeners.
*/

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#pragma mark    Includes

#include <CoreMediaIO/CMIOHardware.h>

#include <CoreFoundation/CoreFoundation.h>
#if COREFOUNDATION_CFPLUGINCOM_SEPARATE
    #include <CoreFoundation/CFPlugInCOM.h>
#endif

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#if defined(__cplusplus)
extern "C"
{
#endif
    
#pragma pack(push, 4)

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#pragma mark    Types

/*!
    @typedef        CMIOHardwarePlugInInterface
    @abstract       Forward declaration of CMIOHardwarePlugInInterface.
*/
typedef struct CMIOHardwarePlugInInterface CMIOHardwarePlugInInterface;

/*!
    @typedef        CMIOHardwarePlugInRef
    @abstract       A reference to an CMIOHardwarePlugInInterface.
*/
typedef CMIOHardwarePlugInInterface**      CMIOHardwarePlugInRef;

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#pragma mark    Constants

/*!
    @defined        kCMIOHardwarePlugInTypeID
    @discussion     This is the UUID of the plug-in type (30010C1C-93BF-11D8-8B5B-000A95AF9C6A).
*/
#define kCMIOHardwarePlugInTypeID CFUUIDGetConstantUUIDWithBytes( NULL, 0x30, 0x01, 0x0C, 0x1C, 0x93, 0xBF, 0x11, 0xD8,  0x8B, 0x5B, 0x00, 0x0A, 0x95, 0xAF, 0x9C, 0x6A)

/*!
    @defined        kCMIOHardwarePlugInInterfaceID
    @discussion     This is the UUID of version 1 of the plug-in interface
                    (B89DFABA-93BF-11D8-8EA6-000A95AF9C6A).
*/
#define kCMIOHardwarePlugInInterfaceID CFUUIDGetConstantUUIDWithBytes( NULL, 0xB8, 0x9D, 0xFA, 0xBA, 0x93, 0xBF, 0x11, 0xD8, 0x8E, 0xA6, 0x00, 0x0A, 0x95, 0xAF, 0x9C, 0x6A)


//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#pragma mark    Plug-In Interface

/*!
    @interface      CMIOHardwarePlugInInterface
    @abstract       The CFPlugIn interface to a DAL plug-in.
    @discussion     In CFPlugIn terms, CMIOHardwarePlugInInterface is a subclass of IUnknown.
*/
struct  CMIOHardwarePlugInInterface
{

/*!
    @var            _reserved
    @abstract       A standard part of the IUnknown interface.
*/
    void*       _reserved;

/*!
    @method         QueryInterface
    @abstract       The IUnknown method for finding an interface on a CFPlugIn type.
    @param          self
                        The CFPlugIn type to query.
    @param          uuid
                        The UUID of the interface to find.
    @param          interface
                        The returned interface or NULL if none was found.
    @result         An error code indicating success of failure.
*/
    HRESULT
    (STDMETHODCALLTYPE *QueryInterface)(    void*   self,
                                            REFIID  uuid,
                                            LPVOID* interface);
/*!
    @method         AddRef
    @abstract       The IUnknown method for retaining a reference to a CFPlugIn type.
    @param          self
                        The CFPlugIn type to retain.
    @result         The resulting reference count after the new reference is added.
*/
    ULONG
    (STDMETHODCALLTYPE *AddRef)(    void*   self);

/*!
    @method         Release
    @abstract       The IUnknown method for releasing a reference to a CFPlugIn type.
    @param          self
                        The CFPlugIn type to release.
    @result         The resulting reference count after the reference has been removed.
*/
    ULONG
    (STDMETHODCALLTYPE *Release)(   void*   self);

/*!
    @method         Initialize
    @abstract       This method is called to initialize the instance of the plug-in.
    @discussion     As part of initialization, the plug-in should publish all the CMIOObjects
                    it knows about at the time.
    @param          self
                        The instance to initialize.
    @result         An OSStatus indicating success or failure.
*/
    OSStatus
    (*Initialize)(  CMIOHardwarePlugInRef  self);

/*!
    @method         InitializeWithObjectID
    @abstract       This method is called to initialize the instance of the plug-in.
    @discussion     As part of initialization, the plug-in should publish all the CMIOObjects
                    it knows about at the time. This method supersedes the Initialize method for
                    version 3 plug-ins so that an CMIOObjectID can be associated with the plug-in
                    right from the start.
    @param          self
                        The instance to initialize.
    @param          objectID
                        The CMIOObjectID the plug-in is to use to identify itself.
    @result         An OSStatus indicating success or failure.
*/
    OSStatus
    (*InitializeWithObjectID)(  CMIOHardwarePlugInRef  self,
                                CMIOObjectID           objectID);

/*!
    @method         Teardown
    @abstract       This method is called to tear down the instance of the plug-in.
    @param          self
                        The instance to tear down.
    @result         An OSStatus indicating success or failure.
*/
    OSStatus
    (*Teardown)(    CMIOHardwarePlugInRef  self);

/*!
    @method         ObjectShow
    @abstract       Prints to standard out a textural description of the CMIOObject.
    @param          self
                        The plug-in instance that owns the CMIOObject.
    @param          objectID
                        The CMIOObject to show.
*/
    void
    (*ObjectShow)(  CMIOHardwarePlugInRef  self,
                    CMIOObjectID           objectID);

/*!
    @method         ObjectHasProperty
    @abstract       Queries an CMIOObject about whether or not it has the given property.
    @param          self
                        The plug-in instance that owns the CMIOObject.
    @param          objectID
                        The CMIOObject to query.
    @param          address
                        An CMIOObjectPropertyAddress indicating which property is being
                        queried.
    @result         A Boolean indicating whether or not the CMIOObject has the given property.
*/
    Boolean
    (*ObjectHasProperty)(   CMIOHardwarePlugInRef              self,
                            CMIOObjectID                       objectID,
                            const CMIOObjectPropertyAddress*   address);

/*!
    @method         ObjectIsPropertySettable
    @abstract       Queries an CMIOObject about whether or not the given property can be set
                    using CMIOObjectSetPropertyData.
    @param          self
                        The plug-in instance that owns the CMIOObject.
    @param          objectID
                        The CMIOObject to query.
    @param          address
                        An CMIOObjectPropertyAddress indicating which property is being
                        queried.
    @param          isSettable
                        A Boolean indicating whether or not the property can be set.
    @result         An OSStatus indicating success or failure.
*/
    OSStatus
    (*ObjectIsPropertySettable)(    CMIOHardwarePlugInRef               self,
                                    CMIOObjectID                        objectID,
                                    const CMIOObjectPropertyAddress*    address,
                                    Boolean*                            isSettable);

/*!
    @method         ObjectGetPropertyDataSize
    @abstract       Queries an CMIOObject to find the size of the data for the given property.
    @param          self
                        The plug-in instance that owns the CMIOObject.
    @param          objectID
                        The CMIOObject to query.
    @param          address
                        An CMIOObjectPropertyAddress indicating which property is being
                        queried.
    @param          qualifierDataSize
                        A UInt32 indicating the size of the buffer pointed to by
                        qualifierData. Note that not all properties require qualification, in
                        which case this value will be 0.
    @param          qualifierData
                        A buffer of data to be used in determining the data of the property
                        being queried. Note that not all properties require qualification, in
                        which case this value will be NULL.
    @param          dataSize
                        A UInt32 indicating how many bytes the data for the given property
                        occupies.
    @result         An OSStatus indicating success or failure.
*/
    OSStatus
    (*ObjectGetPropertyDataSize)(   CMIOHardwarePlugInRef               self,
                                    CMIOObjectID                        objectID,
                                    const CMIOObjectPropertyAddress*    address,
                                    UInt32                              qualifierDataSize,
                                    const void*                         qualifierData,
                                    UInt32*                             dataSize);

/*!
    @method         ObjectGetPropertyData
    @abstract       Queries an CMIOObject to get the data of the given property and places it
                    in the provided buffer.
    @param          self
                        The plug-in instance that owns the CMIOObject.
    @param          objectID
                        The CMIOObject to query.
    @param          address
                        An CMIOObjectPropertyAddress indicating which property is being
                        queried.
    @param          qualifierDataSize
                        A UInt32 indicating the size of the buffer pointed to by
                        qualifierData. Note that not all properties require qualification, in
                        which case this value will be 0.
    @param          qualifierData
                        A buffer of data to be used in determining the data of the property
                        being queried. Note that not all properties require qualification, in
                        which case this value will be NULL.
    @param          dataSize
                        A UInt32 which indicates the size (in bytes) of the buffer pointed to by data.
    @param          dataUsed
                        A UInt32 which indicates how much (in bytes) of the buffer was used.
    @param          data
                        The buffer into which the CMIOObject will put the data for the given
                        property.
    @result         An OSStatus indicating success or failure.
*/
    OSStatus
    (*ObjectGetPropertyData)(   CMIOHardwarePlugInRef               self,
                                CMIOObjectID                        objectID,
                                const CMIOObjectPropertyAddress*    address,
                                UInt32                              qualifierDataSize,
                                const void*                         qualifierData,
                                UInt32                              dataSize,
                                UInt32*                             dataUsed,
                                void*                               data);

/*!
    @method         ObjectSetPropertyData
    @abstract       Tells an CMIOObject to change the value of the given property using the
                    provided data.
    @param          self
                        The plug-in instance that owns the CMIOObject.
    @param          objectID
                        The CMIOObject to change.
    @param          address
                        An CMIOObjectPropertyAddress indicating which property is being
                        changed.
    @param          qualifierDataSize
                        A UInt32 indicating the size of the buffer pointed to by
                        qualifierData. Note that not all properties require qualification, in
                        which case this value will be 0.
    @param          qualifierData
                        A buffer of data to be used in determining the data of the property
                        being queried. Note that not all properties require qualification, in
                        which case this value will be NULL.
    @param          dataSize
                        A UInt32 indicating the size of the buffer pointed to by data.
    @param          data
                        The buffer containing the data to be used to change the property's
                        value.
    @result         An OSStatus indicating success or failure.
*/
    OSStatus
    (*ObjectSetPropertyData)(   CMIOHardwarePlugInRef               self,
                                CMIOObjectID                        objectID,
                                const CMIOObjectPropertyAddress*    address,
                                UInt32                              qualifierDataSize,
                                const void*                         qualifierData,
                                UInt32                              dataSize,
                                const void*                         data);

    /*!
     @method         DeviceSuspend
     @abstract       Instructs the device to stop all of its streams and release any exclusive access
     @param          self
                         The plug-in instance that owns the CMIODevice.
     @param          device
                         The CMIODevice to suspend.
     @result         An OSStatus indicating success or failure.
     */
    OSStatus
    (*DeviceSuspend)(   CMIOHardwarePlugInRef   self,
                        CMIODeviceID            device);

    /*!
     @method         DeviceResume
     @abstract       Instructs the device that is is no longer suspended.  The device should try its best to restore its previous state.
     @param          self
                        The plug-in instance that owns the CMIODevice.
     @param          device
                         The CMIODevice to resume.
     @result         An OSStatus indicating success or failure.
     */
    OSStatus
    (*DeviceResume)(    CMIOHardwarePlugInRef   self,
                        CMIODeviceID            device);

    /*!
    @method         DeviceStartStream
    @abstract       Starts the given CMIOStream.
    @param          self
                        The plug-in instance that owns the CMIODevice.
    @param          device
                        The CMIODevice that owns the CMIOStream.
    @param          stream
                        The CMIOStream to start.
    @result         An OSStatus indicating success or failure.
*/
    OSStatus
    (*DeviceStartStream)(   CMIOHardwarePlugInRef   self,
                            CMIODeviceID            device,
                            CMIOStreamID            stream);

/*!
    @method         DeviceStopStream
    @abstract       Stops the given CMIOStream.
    @param          self
                        The plug-in instance that owns the CMIODevice.
    @param          device
                        The CMIODevice that owns the CMIOStream.
    @param          stream
                        The CMIOStream to stop.
    @result         An OSStatus indicating success or failure.
*/
    OSStatus
    (*DeviceStopStream)(    CMIOHardwarePlugInRef   self,
                            CMIODeviceID            device,
                            CMIOStreamID            stream);

/*!
    @function       DeviceProcessAVCCommand
    @abstract       Allows an AVC command to be sent to a device for processing. This is not intended to be a general purpose command interfaces, rather only for those devices which can
                    support the "AV/C Digital Interface Command Set GeneralSpecification Version 4.1" (1394 Trade Association Document 2001012). Devices indicate whether or not they can
                    process AVC commands via the kCMIODevicePropertyCanProcessAVCCommand property.
     @param          self
                        The plug-in instance that owns the CMIODevice.
    @param          device
                        The CMIODevice which should process the AVC command.
    @param          ioAVCCommand
                        The CMIODeviceAVCCommand to send to the device.
    @result         An OSStatus indicating success or failure of the command processing.  Note that this does NOT indicate the success/failure of the command itself (that is conveyed via
                    avcCommand.mAVCErrorResult), but rather only indicates whether or not the device is capable of processing AVC commands.
*/
    OSStatus
    (*DeviceProcessAVCCommand)( CMIOHardwarePlugInRef   self,
                                CMIODeviceID            device,
                                CMIODeviceAVCCommand*   ioAVCCommand);


/*!
    @function       DeviceProcessRS422Command
    @abstract       Allows an RS422 command to be sent to a device for processing. This is not intended to be a general purpose command interface, rather only for those devices which can
                    support the RS422 protocal as defined in (Do we need a separate .h file to define the commands?).  Devices indicate whether or not they can process RS422 commands via the
                    kCMIODevicePropertyCanProcessRS422Command property.
    @param          self
                        The plug-in instance that owns the CMIODevice.
    @param          device
                        The CMIODevice which should process the RS422 command.
    @param          ioRS422Command
                        The CMIODeviceRS422Command to send to the device.
    @result         An OSStatus indicating success or failure of the command processing.  Note that this does NOT indicate the success/failure of the command itself (that is conveyed via
                    avcCommand.mRS422ErrorResult), but rather only indicates whether or not the device is capable of processing RS422 commands.
*/
    OSStatus
    (*DeviceProcessRS422Command)(   CMIOHardwarePlugInRef   self,
                                    CMIODeviceID            device,
                                    CMIODeviceRS422Command* ioRS422Command);

/*!
    @method         StreamCopyBufferQueue
    @abstract       Gets the CMSimpleQueue of the specified CMIOStream.
    @param          self
                        The plug-in instance that owns the CMIOStream.
    @param          stream
                        The CMIOStream to create the CMSimpleQueue.
    @param          queueAlteredProc
                        Routine to be invoked when the stream alters the queue for insertions (input streams) and removals (output streams).
    @param          queueAlteredRefCon
                        The client refCon to pass back when the queue altered proc is invoked.
    @param          queue
                        The CMSimpleQueue to fill (for input streams) or to drain (for output streams).  If the call is successful, the client will need to release the queue when
                        done with it.
    @result         An OSStatus indicating success or failure.
*/
    OSStatus
    (*StreamCopyBufferQueue)(   CMIOHardwarePlugInRef               self,
                                CMIOStreamID                        stream,
                                CMIODeviceStreamQueueAlteredProc    queueAlteredProc,
                                void*                               queueAlteredRefCon,
                                CMSimpleQueueRef*                   queue);

/*!
    @function       StreamDeckPlay
    @abstract       Sends a generic deck play command to the specified CMIOStream, instructing its associated deck to play.
    @param          self
                        The plug-in instance that owns the CMIOStream.
    @param          stream
                        The CMIOStream whose deck controls are being manipulated.
    @result         An OSStatus indicating success or failure.
*/
    OSStatus
    (*StreamDeckPlay)(  CMIOHardwarePlugInRef   self,
                        CMIOStreamID            stream);
    
/*!
    @function       StreamDeckStop
    @abstract       Sends a generic deck stop command to the specified CMIOStream, instructing the associated deck to stop.
                    to wind at the specified speed.
    @param          self
                        The plug-in instance that owns the CMIOStream.
    @param          stream
                        The CMIOStream whose deck controls are being manipulated.
    @result         An OSStatus indicating success or failure.
*/
    OSStatus
    (*StreamDeckStop)(  CMIOHardwarePlugInRef   self,
                        CMIOStreamID            stream);
    
/*!
    @function       StreamDeckJog
    @abstract       Sends a generic deck jog command to the specified CMIOStream, instructing the associated deck to wind at the specified speed.
    @param          self
                        The plug-in instance that owns the CMIOStream.
    @param          stream
                        The CMIOStream whose deck controls are being manipulated.
    @param          speed
                        A number between -10 and +10 to specify the speed of movement of the associated deck.
    @result         An OSStatus indicating success or failure.
*/
    OSStatus
    (*StreamDeckJog)(   CMIOHardwarePlugInRef   self,
                        CMIOStreamID            stream,
                        SInt32 speed);
    
/*!
    @function       StreamDeckCueTo
    @abstract       Sends a generic deck cue-to command to the specified CMIOStream, instructing the associated deck to seek to a specific point.
    @param          self
                        The plug-in instance that owns the CMIOStream.
    @param          stream
                        The CMIOStream whose deck controls are being manipulated.
    @param          frameNumber
                        The desired frame number that the deck should cue to.
    @param          playOnCue
                        An indicator that the deck should start playing when the cue-to point is reached.
    @result         An OSStatus indicating success or failure.
*/
    OSStatus
    (*StreamDeckCueTo)( CMIOHardwarePlugInRef   self,
                        CMIOStreamID            stream,
                        Float64                 frameNumber,
                        Boolean                 playOnCue);
    
};

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#pragma mark    CMIOObject Functions

/*!
    @functiongroup  CMIOObject
*/

/*!
    @function       CMIOObjectCreate
    @abstract       Instantiates a new CMIOObject.
    @discussion     Newly instantiated CMIOObjects are not made available to the DAL's clients
                    until the object is published using CMIOObjectsPublishedAndDied().
    @param          owningPlugIn
                        The plug-in instance instantiating the new CMIOObject.
    @param          owningObjectID
                        The CMIOObjectID of the CMIOObject that owns the new CMIOObject.
    @param          classID
                        The ID of the class of the new CMIOObject.
    @param          objectID
                        On exit, the CMIOObjectID of the new CMIOObject.
    @result         An OSStatus indicating success or failure.
*/
extern OSStatus
CMIOObjectCreate(   CMIOHardwarePlugInRef   owningPlugIn,
                    CMIOObjectID            owningObjectID,
                    CMIOClassID             classID,
                    CMIOObjectID*           objectID)                                       AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER;

/*!
    @function       CMIOObjectsPublishedAndDied
    @abstract       Tell the DAL to publish some CMIOObjects and tear down others.
    @discussion     Note that all the objects must be owned by owningObjectID.
    @param          owningPlugIn
                        The plug-in instance that owns the CMIOObjects.
    @param          owningObjectID
                        The CMIOObjectID of the CMIOObject that owns the objects being published
                        or destroyed.
    @param          numberPublishedCMIOObjects
                        The number of items in the publishedCMIOObjects array.
    @param          publishedCMIOObjects
                        An array of CMIOObjectIDs for the CMIOObjects that are to be made
                        available to the DAL's clients.
    @param          numberDeadCMIOObjects
                        The number of items in the deadCMIOObjects array.
    @param          deadCMIOObjects
                        An array of CMIOObjectIDs for the CMIOObjects that are no longer
                        available.
    @result         An OSStatus indicating success or failure.
*/
extern OSStatus
CMIOObjectsPublishedAndDied(    CMIOHardwarePlugInRef   owningPlugIn,
                                CMIOObjectID            owningObjectID,
                                UInt32                  numberPublishedCMIOObjects,
                                const CMIOObjectID      publishedCMIOObjects[],
                                UInt32                  numberDeadCMIOObjects,
                                const CMIOObjectID      deadCMIOObjects[])                       AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER;

/*!
    @function       CMIOObjectPropertiesChanged
    @abstract       Tell the DAL that properties have changed on the given CMIOObject.
    @discussion     The DAL will take care of calling any registered listeners.
    @param          owningPlugIn
                        The plug-in instance that owns the CMIOObject whose properties have
                        changed.
    @param          objectID
                        The CMIOObjectID of the CMIOObject whose properties have changed.
    @param          numberAddresses
                        The number of items in the addresses array.
    @param          addresses
                        An array of CMIOObjectPropertyAddress structs indicating which properties
                        of the device have changed.
    @result         An OSStatus indicating success or failure.
*/
extern OSStatus
CMIOObjectPropertiesChanged(    CMIOHardwarePlugInRef           owningPlugIn,
                                CMIOObjectID                    objectID,
                                UInt32                          numberAddresses,
                                const CMIOObjectPropertyAddress addresses[])                  AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER;

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#pragma mark    CMIODevice Functions

/*!
    @functiongroup  CMIODevice
*/

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#pragma mark    CMIOStream Functions

/*!
    @functiongroup  CMIOStream
*/

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#pragma pack(pop)
    
#if defined(__cplusplus)
}
#endif

#endif  //  __CMIOHardwarePlugIn_h__
