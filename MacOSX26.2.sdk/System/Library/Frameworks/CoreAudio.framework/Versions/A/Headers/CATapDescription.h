/*
	File:		CATapDescription.h
	Framework:	CoreAudio

	Copyright (c) 2014-2022 Apple Inc. All Rights Reserved.
*/
 
#ifdef __OBJC__

#ifndef CATapDescription_h
#define CATapDescription_h

#import <Foundation/NSString.h>
#import <Foundation/NSArray.h>
#import <Foundation/NSUUID.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @enum		CATapMuteBehavior
 @abstract	CATapMuteBehavior describes the playback behavior of the process being tapped. The default value is CATapUnmuted.
 @constant	CATapUnmuted
 	Audio is captured by the tap and also sent to the audio hardware
 @constant	CATapMuted
 	Audio is captured by the tap but no audio is sent from the process to the audio hardware
 @constant	CATapMutedWhenTapped
 	Audio is captured by the tap and also sent to the audio hardware until the tap is read by another audio client. 
 	For the duration of the read activity on the tap no audio is sent to the audio hardware.
*/
typedef NS_ENUM(NSInteger, CATapMuteBehavior) {
	CATapUnmuted = 0,
	CATapMuted = 1,
	CATapMutedWhenTapped = 2
} API_AVAILABLE(macos(13.0), ios(16.0));

//==================================================================================================
#pragma mark -
#pragma mark CATapDescription class.
/*!
    @class CATapDescription

    This class describes a tap object that contains an input stream.  The input stream is a mix of all of the specified processes output audio.
*/
API_AVAILABLE(macos(12.0), ios(15.0))
@interface CATapDescription : NSObject

- (instancetype)init;

/*! @method initStereoMixdownOfProcesses
	@abstract
        Mix all given process audio streams down to stereo.  Mono sources will be duplicated in
        both right and left channels.
	@param	processesObjectIDsToIncludeInTap
         An NSArray of NSNumbers where each NSNumber holds an AudioObjectID of the process object to include in the tap
*/
- (instancetype) initStereoMixdownOfProcesses:(NSArray<NSNumber*>*)processesObjectIDsToIncludeInTap NS_REFINED_FOR_SWIFT;

/*! @method initStereoGlobalTapButExcludeProcesses
	@abstract
        Mix all processes to a stereo stream except the given processes.  Mono sources will be
        duplicated in both right and left channels.
	@param	processesObjectIDsToExcludeFromTap
         An NSArray of NSNumbers where each NSNumber holds an AudioObjectID of the process object to exclude from the tap.
         All other processes that output audio will be included in the tap.
*/
- (instancetype) initStereoGlobalTapButExcludeProcesses:(NSArray<NSNumber*>*)processesObjectIDsToExcludeFromTap NS_REFINED_FOR_SWIFT;

/*! @method initMonoMixdownOfProcesses
	@abstract
        Mix all given process audio streams audio to mono.
	@param	processesObjectIDsToIncludeInTap
         An NSArray of NSNumbers where each NSNumber holds an AudioObjectID of the process object to include in the tap
 */
- (instancetype) initMonoMixdownOfProcesses:(NSArray<NSNumber*>*)processesObjectIDsToIncludeInTap NS_REFINED_FOR_SWIFT;

/*! @method initMonoGlobalTapButExcludeProcesses
	@abstract
        Mix all processes to a mono stream except the given processes
	@param	processesObjectIDsToExcludeFromTap
         An NSArray of NSNumbers where each NSNumber holds an AudioObjectID of the process object to exclude from the tap.
         All other processes that output audio will be included in the tap.
 */
- (instancetype) initMonoGlobalTapButExcludeProcesses:(NSArray<NSNumber*>*)processesObjectIDsToExcludeFromTap NS_REFINED_FOR_SWIFT;

/*! @method initWithProcesses:andDeviceUID:withStreams
	@abstract
         Mix all given process audio streams destined for the selected device stream
	@param	processesObjectIDsToIncludeInTap
         An NSArray of NSNumbers where each NSNumber holds an AudioObjectID of the process object to exclude from the tap.
         All other processes that output audio will be included in the tap.
	@param	deviceUID
         The device UID of the output device whose audio will be captured
	@param	stream
         NSInteger that represents the index of the stream on the device whose audio will be captured. The format of the tap
         will match the format of this stream.
 */
- (instancetype) initWithProcesses:(NSArray<NSNumber*>*)processesObjectIDsToIncludeInTap andDeviceUID:(NSString*) deviceUID withStream:(NSInteger) stream NS_REFINED_FOR_SWIFT;

/*! @method initExcludingProcesses:andDeviceUID:withStreams
	@abstract
         Mix all process audio streams destined for the selected device stream except the given processes
	@param	processesObjectIDsToExcludeFromTap
         An NSArray of NSNumbers where each NSNumber holds an AudioObjectID of the process object to exclude from the tap.
         All other processes that output audio will be included in the tap.
	@param	deviceUID
         The device UID of the output device whose audio will be captured
	@param	stream
         NSInteger that represents the index of the stream on the device whose audio will be captured. The format of the tap
         will match the format of this stream.
 */
- (instancetype) initExcludingProcesses:(NSArray<NSNumber*>*)processesObjectIDsToExcludeFromTap andDeviceUID:(NSString*) deviceUID withStream:(NSInteger) stream NS_REFINED_FOR_SWIFT;

/*!
 @property name
 @abstract Human readable name of this tap.
*/
@property (atomic, copy) NSString* name;

/*!
 @property UUID
 @abstract UID of this tap.
*/
@property (atomic, copy) NSUUID* UUID;

/*!	@property processes
 @abstract
 An NSArray of NSNumbers where each NSNumber holds the AudioObjectID of a process object to tap or exclude.
 */
@property (atomic, copy, readwrite) NSArray<NSNumber*>* processes NS_REFINED_FOR_SWIFT;

/*!	@property bundleIDs
 @abstract
 An Array of Strings where each String holds the bundle ID of a process to tap or exclude.
 */
@property (atomic, copy, readwrite) NSArray<NSString*>* bundleIDs
API_AVAILABLE(macos(26.0));

/*!	@property mono
 @abstract
 True if this description is a mono mixdown of channels.
 */
@property (atomic, readwrite, getter=isMono) BOOL mono;

/*!	@property exclusive
 @abstract
 True if this description should tap all processes except the process listed in the 'processes' property.
 */
@property (atomic, readwrite, getter=isExclusive) BOOL exclusive;

/*!	@property mixdown
 @abstract
 True if this description is a mono or stereo mix of the tapped device's channels.
 */
@property (atomic, readwrite, getter=isMixdown) BOOL mixdown;

/*!	@property privateTap
 @abstract
 True if this tap is only visible to the client process that created the tap.
 */
@property (atomic, readwrite, getter=isPrivate, setter=setPrivate:) BOOL privateTap;

/*!	@property processRestoreEnabled
 @abstract
 True if this tap should save tapped processes by bundle ID when they exit, and restore them to the tap when they start up again.
 */
@property (atomic, readwrite, getter=isProcessRestoreEnabled) BOOL processRestoreEnabled
API_AVAILABLE(macos(26.0));

/*!	@property muteBehavior
 @abstract
 Set the tap's mute behavior. See CATapMuteBehavior above.
 */
@property (atomic, readwrite, getter=isMuted) CATapMuteBehavior muteBehavior;

/*!	@property deviceUID
 @abstract
 An optional deviceUID that will have a value if this tap only taps a specific hardware device
 */
@property (atomic, copy, nullable) NSString* deviceUID;

/*!	@property stream
 @abstract
 An optional NSNumber that will have a value if this tap taps a specific device stream.
 The value represents the index of the hardware stream.
 */
@property (atomic, copy, nullable) NSNumber* stream NS_REFINED_FOR_SWIFT;

@end

NS_ASSUME_NONNULL_END

#endif /* CATapDescription_h */

#endif // __OBJC__

