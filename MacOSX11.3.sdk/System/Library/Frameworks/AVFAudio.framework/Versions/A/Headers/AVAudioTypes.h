/*
	File:		AVAudioTypes.h
	Framework:	AVFoundation
	
	Copyright (c) 2014-2020 Apple Inc. All Rights Reserved.
*/

#ifndef __AVAudioTypes_h__
#define __AVAudioTypes_h__

#import <Foundation/Foundation.h>
#import <CoreAudioTypes/CoreAudioTypes.h>

/*! @typedef AVAudioFramePosition
	@abstract A position in an audio file or stream.
*/
typedef int64_t		AVAudioFramePosition;

/*!	@typedef AVAudioFrameCount
	@abstract A number of audio sample frames.
*/
typedef uint32_t	AVAudioFrameCount;

/*!	@typedef AVAudioPacketCount
	@abstract A number of packets of compressed audio data.
*/
typedef uint32_t	AVAudioPacketCount;

/*!	@typedef AVAudioChannelCount
	@abstract A number of audio channels.
	
	@discussion
		Rationale: making this a potentially larger-than-32-bit type like NSUInteger would open the
		door to a large set of runtime failures due to underlying implementations' use of UInt32.
*/
typedef uint32_t	AVAudioChannelCount;

/*! @typedef AVAudioNodeCompletionHandler
	@abstract Generic callback handler.
	@discussion
		Various AVAudioEngine objects issue callbacks to generic blocks of this type. In general
		the callback arrives on a non-main thread and it is the client's responsibility to handle it
		in a thread-safe manner.
*/
typedef void (^AVAudioNodeCompletionHandler)(void);

/*!	@typedef AVAudioNodeBus
	@abstract The index of a bus on an AVAudioNode.
	@discussion
		AVAudioNode objects potentially have multiple input and/or output busses.
		AVAudioNodeBus represents a bus as a zero-based index.
*/
typedef NSUInteger AVAudioNodeBus;



/*=============================================================================*/
/*!	@struct AVAudio3DPoint
    @abstract Struct representing a point in 3D space
    @discussion
        This struct is used by classes dealing with 3D audio such as `AVAudioMixing`
        and `AVAudioEnvironmentNode` and represents a point in 3D space.
*/
struct AVAudio3DPoint {
    float x;
    float y;
    float z;
};
typedef struct AVAudio3DPoint AVAudio3DPoint;

/*! @abstract Creates and returns an AVAudio3DPoint object
*/
NS_INLINE AVAudio3DPoint AVAudioMake3DPoint(float x, float y, float z) {
    AVAudio3DPoint p;
    p.x = x;
    p.y = y;
    p.z = z;
    return p;
}

/*!	@typedef AVAudio3DVector
    @abstract Struct representing a vector in 3D space
    @discussion
        This struct is used by classes dealing with 3D audio such as `AVAudioMixing`
        and `AVAudioEnvironmentNode`.
*/
typedef struct AVAudio3DPoint AVAudio3DVector;

/*! @abstract Creates and returns an AVAudio3DVector object
*/
NS_INLINE AVAudio3DVector AVAudioMake3DVector(float x, float y, float z) {
    AVAudio3DVector v;
    v.x = x;
    v.y = y;
    v.z = z;
    return v;
}

/*!	@struct AVAudio3DVectorOrientation
    @abstract Struct representing the orientation of the listener in 3D space
    @discussion
        Two orthogonal vectors describe the orientation of the listener. The forward
        vector points in the direction that the listener is facing. The up vector is orthogonal
        to the forward vector and points upwards from the listener's head.
*/
struct AVAudio3DVectorOrientation {
    AVAudio3DVector forward;
    AVAudio3DVector up;
};
typedef struct AVAudio3DVectorOrientation AVAudio3DVectorOrientation;

/*! @abstract Creates and returns an AVAudio3DVectorOrientation object
*/
NS_INLINE AVAudio3DVectorOrientation AVAudioMake3DVectorOrientation(AVAudio3DVector forward, AVAudio3DVector up) {
    AVAudio3DVectorOrientation o;
    o.forward = forward;
    o.up = up;
    return o;
}

/*!	@struct AVAudio3DAngularOrientation
    @abstract Struct representing the orientation of the listener in 3D space
    @discussion
        Three angles describe the orientation of a listener's head - yaw, pitch and roll.
 
        Yaw describes the side to side movement of the listener's head.
        The yaw axis is perpendicular to the plane of the listener's ears with its origin at the 
        center of the listener's head and directed towards the bottom of the listener's head. A 
        positive yaw is in the clockwise direction going from 0 to 180 degrees. A negative yaw is in 
        the counter-clockwise direction going from 0 to -180 degrees.
 
        Pitch describes the up-down movement of the listener's head.
        The pitch axis is perpendicular to the yaw axis and is parallel to the plane of the 
        listener's ears with its origin at the center of the listener's head and directed towards 
        the right ear. A positive pitch is the upwards direction going from 0 to 180 degrees. A 
        negative pitch is in the downwards direction going from 0 to -180 degrees.
 
        Roll describes the tilt of the listener's head.
        The roll axis is perpendicular to the other two axes with its origin at the center of the 
        listener's head and is directed towards the listener's nose. A positive roll is to the right 
        going from 0 to 180 degrees. A negative roll is to the left going from 0 to -180 degrees.
*/
struct AVAudio3DAngularOrientation {
    float yaw;
    float pitch;
    float roll;
};
typedef struct AVAudio3DAngularOrientation AVAudio3DAngularOrientation;

/*! @abstract Creates and returns an AVAudio3DAngularOrientation object
*/
NS_INLINE AVAudio3DAngularOrientation AVAudioMake3DAngularOrientation(float yaw, float pitch, float roll) {
    AVAudio3DAngularOrientation o;
    o.yaw = yaw;
    o.pitch = pitch;
    o.roll = roll;
    return o;
}

#endif // __AVAudioTypes_h__

