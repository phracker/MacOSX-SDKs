/*
    File:       CoreMIDI/MIDIThruConnection.h
 
    Contains:   Routines for creating MIDI play-through connections.
 
    Copyright:  (c) 2000-2015 by Apple Inc., all rights reserved.
 
    Bugs?:      For bug reports, consult the following page on
                the World Wide Web:
 
                    http://feedbackassistant.apple.com/
 
*/

#ifndef __MIDIThruConnection_h__
#define __MIDIThruConnection_h__

#include <CoreFoundation/CoreFoundation.h>
#include <CoreMIDI/MIDIServices.h>

CF_ASSUME_NONNULL_BEGIN

//  -----------------------------------------------------------------------------
/*!
    @header MIDIThruConnection.h

    This header defines functions to create MIDI play-through connections
    between the MIDI sources and destinations.  These connections may be
    persistent or transitory, owned by a client.
    
    By using connections instead of doing MIDI Thru operations themselves,
    the overhead of moving MIDI messages between the server and the client
    for thru-ing is reduced.
    
    The aim of these functions is to permit as flexible a set of transformations 
    as possible while keeping the API and data structures relatively simple.    
*/
//  -----------------------------------------------------------------------------

/// An opaque reference to a play-through connection.
typedef MIDIObjectRef MIDIThruConnectionRef;

/*!
    @struct         MIDIValueMap
    
    @abstract       A custom mapping function to transform MIDI 7-bit values,
                    as contained in note numbers, velocities, control values,
                    etc.  y = value[x], where x is the input MIDI value, y the
                    output.
*/
struct MIDIValueMap {
    UInt8           value[128];
};
typedef struct MIDIValueMap MIDIValueMap;

/*!
    @enum           MIDITransformType
    
    @abstract       Values specifying a type of MIDI transformation, as found in the transform member of MIDITransform.
    
    @constant   kMIDITransform_None
        no transformation (param unused)
    @constant   kMIDITransform_FilterOut
        filter out the specified event type (param unused)
    @constant   kMIDITransform_MapControl
        transform one control number to another; param is destination control number
    @constant   kMIDITransform_Add
        add param to values
    @constant   kMIDITransform_Scale
        multiple value by the fixed point number in param, which is in fixed point: bbbb.bbbb bbbb bbbb
    @constant   kMIDITransform_MinValue
        the value's minimum value is param
    @constant   kMIDITransform_MaxValue
        the value's maximum value is param
    @constant   kMIDITransform_MapValue
        transform the value using a map; param is the index of the map in the connection's array of maps.
*/
typedef CF_ENUM(UInt16, MIDITransformType) {
    kMIDITransform_None = 0,
    kMIDITransform_FilterOut = 1,
    kMIDITransform_MapControl = 2,
    kMIDITransform_Add = 8,
    kMIDITransform_Scale = 9,
    kMIDITransform_MinValue = 10,
    kMIDITransform_MaxValue = 11,
    kMIDITransform_MapValue = 12
};

enum {
    kMIDIThruConnection_MaxEndpoints = 8
};

/*!
    @enum       MIDITransformControlType
    
    @abstract   Specifies how control numbers are interpreted.

    @constant   kMIDIControlType_7Bit
        control numbers may be 0-127
    @constant   kMIDIControlType_14Bit
        control numbers may be 0-31
    @constant   kMIDIControlType_7BitRPN
        control numbers may be 0-16383
    @constant   kMIDIControlType_14BitRPN
    @constant   kMIDIControlType_7BitNRPN
    @constant   kMIDIControlType_14BitNRPN
*/
typedef CF_ENUM(UInt8, MIDITransformControlType) {
    kMIDIControlType_7Bit = 0,
    kMIDIControlType_14Bit = 1,
    kMIDIControlType_7BitRPN = 2,
    kMIDIControlType_14BitRPN = 3,
    kMIDIControlType_7BitNRPN = 4,
    kMIDIControlType_14BitNRPN = 5
};

/*!
    @struct     MIDITransform
    @abstract   Describes how a single type of MIDI event is transformed.

	This structure controls the transformation of various MIDI events other than control changes.

    @field      transform   The type of transformation to be applied to the event values.
    @field      param       An argument to the transformation method (see description of MIDITransformType).
*/
struct MIDITransform {
    MIDITransformType   transform;
    SInt16              param;
};
typedef struct MIDITransform MIDITransform;

/*!
    @struct     MIDIControlTransform
    @abstract   Describes a transformation of MIDI control change events.

	A single MIDIThruConnectionParams may describe any number of transformations to control
	events. It is important that multiple transformations are ordered correctly: filter out,
	remap, then alter values.
	
	All transformations are done internally using 14-bit values, so for example, when doing
	an add/min/max transform on a 7-bit control value, the parameter must be a 14-bit value.
	For example, to add 10 to a control value, param must be (10 << 7) = 1280.

	As per the MIDI specification, a number of controls are interpreted specially:

	Control | Function
	--------|---------
	32-63   | the LSBs of 0-31
	6/38    | data entry
	96, 97  | data increment, decrement
	98-101  | NRPN/RPN

    @field  controlType         The type of control specified by controlNumber
    @field  remappedControlType If transform is kMIDITransform_MapControl, the output control type
    @field  controlNumber       The control number to be affected.
    @field  transform           The type of transformation to be applied to the event values.
    @field  param               An argument to the transformation method (see description of MIDITransformType).
*/
struct MIDIControlTransform {
    MIDITransformControlType    controlType;
    MIDITransformControlType    remappedControlType;
    UInt16                      controlNumber;
    MIDITransformType           transform;
    SInt16                      param;
};
typedef struct MIDIControlTransform MIDIControlTransform;

/*!
    @struct     MIDIThruConnectionEndpoint
    @abstract   Describes a source or destination in a MIDIThruConnection.

	When creating one of these, you can leave uniqueID 0 if the endpoint exists and you are passing
	its MIDIEndpointRef.
	
	When obtaining one of these from CoreMIDI, endpointRef may be NULL if it doesn't exist, but the
	uniqueID will always be non-zero.

    @field  endpointRef     The endpoint specified as a MIDIEndpointRef.
    @field  uniqueID        The endpoint specified by its uniqueID.
*/
struct MIDIThruConnectionEndpoint {
    MIDIEndpointRef         endpointRef;
    MIDIUniqueID            uniqueID;
};
typedef struct MIDIThruConnectionEndpoint MIDIThruConnectionEndpoint;

/*!
    @struct     MIDIThruConnectionParams
    @abstract   Describes a set of MIDI routings and transformations.

	The remainder of the structure is variably-sized. It contains numControlTransform instances of
	MIDIControlTransform, followed by numMaps instances of MIDIValueMap.

    @field      version     Version of this structure; must be 0.
    @field      numSources  The number of valid sources in the following array.
    @field      sources     All MIDI generated by these sources is routed into this connection for processing
                            and distribution to destinations.
    @field      numDestinations The number of valid destinations in the following array.
    @field      destinations    All MIDI output from the connection is routed to these destinations.
    @field      channelMap      Maps each of the source 16 MIDI channels to channel 0-15 (1-16) or 0xFF when
                                MIDI from a channel is to be filtered out.
    @field      lowVelocity     Note events with a velocity less than this value are filtered out.
    @field      highVelocity    Note events with a velocity greater than this, if it is not 0, are filtered out.
    @field      lowNote         See highNote.
    @field      highNote        If highNote >= lowNote, then notes outside this range are filtered out.
                                If lowNote > highNote, then notes <i>inside</i> this range are filtered out.
                                This applies to note and polyphonic key pressure events.
                                These fields are ignored if a there is a MIDIValueMap applying to noteNumber.
    @field      noteNumber      Specifies how MIDI note numbers are transformed.
    @field      velocity        Specifies how MIDI note velocities are transformed.
    @field      keyPressure     Specifies how MIDI polyphonic key pressure events are transformed.
    @field      channelPressure Specifies how MIDI monophonic (channel) pressure events are transformed.
    @field      programChange   Specifies how MIDI program change events are transformed.
    @field      pitchBend       Specifies how MIDI pitch bend events are transformed.
    @field      filterOutSysEx  If 1, specifies that system-exclusive messages are to be filtered out.
    @field      filterOutMTC    If 1, specifies that MIDI Time Code messages are to be filtered out.
    @field      filterOutBeatClock  If 1, specifies the MIDI clock, play, stop, and resume messages are to
                                be filtered out.
    @field      filterOutTuneRequest    If 1, specifies that MIDI Tune Request messages are to be filtered out.
    @field      reserved2       Must be 0.
    @field      filterOutAllControls    If 1, specifies that all MIDI continuous control messages are to be filtered out.
    @field      numControlTransforms    The number of control transformations in the variable-length portion of the struct.
    @field      numMaps                 The number of MIDIValueMaps in the variable-length portion of the struct.
    @field      reserved3       Must be 0.
*/
struct MIDIThruConnectionParams {
    UInt32                      version;
    UInt32                      numSources;
    MIDIThruConnectionEndpoint  sources[kMIDIThruConnection_MaxEndpoints];
    UInt32                      numDestinations;
    MIDIThruConnectionEndpoint  destinations[kMIDIThruConnection_MaxEndpoints];
    
    UInt8                   channelMap[16];
    UInt8                   lowVelocity, highVelocity;
    UInt8                   lowNote, highNote;
    MIDITransform           noteNumber;
    MIDITransform           velocity;
    MIDITransform           keyPressure;
    MIDITransform           channelPressure;
    MIDITransform           programChange;
    MIDITransform           pitchBend;
    
    UInt8                   filterOutSysEx;
    UInt8                   filterOutMTC;
    UInt8                   filterOutBeatClock;
    UInt8                   filterOutTuneRequest;
    UInt8                   reserved2[3];
    UInt8                   filterOutAllControls;
    
    UInt16                  numControlTransforms;
    UInt16                  numMaps;
    UInt16                  reserved3[4];

    // remainder of structure is variable-length:
    //      MIDIControlTransform    controls[];
    //      MIDIValueMap            maps[];
};
typedef struct MIDIThruConnectionParams MIDIThruConnectionParams;

#ifdef CF_INLINE
/*!
    @defined    MIDIThruConnectionParamsSize
    @abstract   Returns the size of a MIDIThruConnectionParams.

	Accounts for the variable-length elements in the structure and returns its true
	size in bytes.
*/
CF_INLINE size_t MIDIThruConnectionParamsSize(const MIDIThruConnectionParams *ptr)
{
    return sizeof(MIDIThruConnectionParams) + ptr->numControlTransforms * sizeof(MIDIControlTransform)
	    + ptr->numMaps * sizeof(MIDIValueMap);
}
#else
#define MIDIThruConnectionParamsSize(ptr) \
    (sizeof(MIDIThruConnectionParams) + (ptr)->numControlTransforms * sizeof(MIDIControlTransform) \
    + (ptr)->numMaps * sizeof(MIDIValueMap))
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*!
    @function   MIDIThruConnectionParamsInitialize
    @abstract   Fills a MIDIThruConnectionParams with default values.
    @param      inConnectionParams  The struct to be initialized.

	This convenience function fills the connection structure with default values: no endpoints,
	no transformations (mostly zeroes except for the channel map). Then, just filling in the
	source and adding one destination will create a simple, unmodified thru connection.
*/
extern void
MIDIThruConnectionParamsInitialize(
                            MIDIThruConnectionParams *      inConnectionParams )
                                                                API_AVAILABLE(macos(10.2), ios(4.2));

/*!
    @function   MIDIThruConnectionCreate
    @abstract   Creates a thru connection.
    @param      inPersistentOwnerID
                    If null, then the connection is marked as owned by the client
                    and will be automatically disposed with the client.  if it is non-null, then it
                    should be a unique identifier, e.g. "com.mycompany.MyCoolProgram".
    @param      inConnectionParams
                    A MIDIThruConnectionParams contained in a CFDataRef.
    @param      outConnection
                    On successful return, a reference to the newly-created connection.
    @result     An OSStatus result code.
*/
extern OSStatus
MIDIThruConnectionCreate(   CFStringRef __nullable          inPersistentOwnerID,
                            CFDataRef                       inConnectionParams,
                            MIDIThruConnectionRef *         outConnection )
                                                                API_AVAILABLE(macos(10.2), ios(4.2));

/*!
    @function   MIDIThruConnectionDispose
    @abstract   Disposes a thru connection.
    @param      connection
                    The connection to be disposed
    @result     An OSStatus result code.
*/
extern OSStatus
MIDIThruConnectionDispose(  MIDIThruConnectionRef           connection )
                                                                API_AVAILABLE(macos(10.2), ios(4.2));

/*!
    @function   MIDIThruConnectionGetParams
    @abstract   Obtains a thru connection's MIDIThruConnectionParams.
    @param      connection
                    The connection to be disposed.
    @param      outConnectionParams
                    On successful return, the connection's MIDIThruConnectionParams in a CFDataRef
    @result     An OSStatus result code.

	The returned CFDataRef contains a MIDIThruConnectionParams structure. The caller is responsible
	for releasing it.
*/
extern OSStatus
MIDIThruConnectionGetParams(MIDIThruConnectionRef           connection,
                            CFDataRef __nonnull * __nonnull outConnectionParams )
                                                                API_AVAILABLE(macos(10.2), ios(4.2));

/*!
    @function   MIDIThruConnectionSetParams
    @abstract   Alters a thru connection's MIDIThruConnectionParams.
    @param      connection
                    The connection to be modified.
    @param      inConnectionParams
                    The connection's new MIDIThruConnectionParams in a CFDataRef
    @result     An OSStatus result code.
*/
extern OSStatus
MIDIThruConnectionSetParams(MIDIThruConnectionRef           connection,
                            CFDataRef                       inConnectionParams )
                                                                API_AVAILABLE(macos(10.2), ios(4.2));

/*!
    @function   MIDIThruConnectionFind
    @abstract   Returns all of the persistent thru connections created by a client.
    @param      inPersistentOwnerID
                    The ID of the owner whose connections are to be returned.
    @param      outConnectionList
                    On successful return, a CFDataRef containing an array of MIDIThruConnectionRef's.
    @result     An OSStatus result code.
*/
extern OSStatus
MIDIThruConnectionFind(     CFStringRef                     inPersistentOwnerID,
                            CFDataRef __nonnull * __nonnull outConnectionList )
                                                                API_AVAILABLE(macos(10.2), ios(4.2));

#ifdef __cplusplus
}
#endif

CF_ASSUME_NONNULL_END

#endif /* __MIDIThruConnection_h__ */
