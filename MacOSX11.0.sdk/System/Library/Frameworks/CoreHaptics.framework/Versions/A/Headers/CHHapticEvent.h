/*==================================================================================================
 File:       CHHapticEvent.h
 
 Contains:   API for creating haptic events
 
 Copyright:  (c) 2018 by Apple, Inc., all rights reserved.
 
 Bugs?:      For bug reports, consult the following page on
 the World Wide Web:
 
 http://developer.apple.com/bugreporter/
 
 ==================================================================================================*/

#import <Foundation/NSArray.h>
#import <Foundation/NSDate.h>
#import <Foundation/NSObject.h>
#import <Foundation/NSObjCRuntime.h>

#define CH_EXPORT __attribute__((visibility("default"))) extern

NS_ASSUME_NONNULL_BEGIN

@class CHHapticEventParameter;

/*! @enum CHHapticEventType
	@abstract
		Types of haptic and audio events.
 
 	@constant   CHHapticEventTypeHapticTransient
		An event which generates a haptic with a fixed length, such as a tap.  Transient events will complete on their own.  If a duration longer than the
 		haptic is provided, the pattern containing the event will be "padded" out to the duration specified.
 
 	@constant   CHHapticEventTypeHapticContinuous
		An event which generates a haptic of arbitrary length.  The event can behave as either Transient or Continuous depending on the value
 		of the CHHapticEventParameterIDSustained parameter.  These events also include an AR or ADR gain envelope that may be controlled via Event or
 		Dynamic parameters.
		See `CHHapticEventParameterIDAttackTime`, `CHHapticEventParameterIDDecayTime`, and `CHHapticEventParameterIDReleaseTime`.

 	@constant   CHHapticEventTypeAudioContinuous
		An event which generates an audio signal.  The event can behave as either Transient or Continuous depending on the value of the
		CHHapticEventParameterIDSustained parameter.  These events also include an AR or ADR gain envelope that may be controlled via Event or
 		Dynamic parameters.
		See `CHHapticEventParameterIDAttackTime`, `CHHapticEventParameterIDDecayTime`, and `CHHapticEventParameterIDReleaseTime`.

 	@constant   CHHapticEventTypeAudioCustom
		An event which generates an audio signal using a client-supplied waveform (see `CHHapticEngine(registerAudioResource:options:error)`).
		Currently, these behave as Transient events (i.e., no looping or enveloping).
 */

typedef NSString *CHHapticEventType NS_TYPED_ENUM;

CH_EXPORT
CHHapticEventType CHHapticEventTypeHapticTransient API_AVAILABLE(ios(13.0), macos(10.15), tvos(14.0), macCatalyst(13.0)) API_UNAVAILABLE(watchos);
CH_EXPORT
CHHapticEventType CHHapticEventTypeHapticContinuous API_AVAILABLE(ios(13.0), macos(10.15), tvos(14.0), macCatalyst(13.0)) API_UNAVAILABLE(watchos);
CH_EXPORT
CHHapticEventType CHHapticEventTypeAudioContinuous API_AVAILABLE(ios(13.0), macos(10.15), tvos(14.0), macCatalyst(13.0)) API_UNAVAILABLE(watchos);
CH_EXPORT
CHHapticEventType CHHapticEventTypeAudioCustom API_AVAILABLE(ios(13.0), macos(10.15), tvos(14.0), macCatalyst(13.0)) API_UNAVAILABLE(watchos);

/*!	@typedef CHHapticAudioResourceID
	@abstract
		Identifier for registered, client-loaded audio data which can be used as custom event types
 		(see `CHHapticEngine(registerAudioResource:options:error)`).
 */
typedef NSUInteger	CHHapticAudioResourceID;

/*!	@class CHHapticEvent
	@abstract
		The description of a single haptic/audio event, plus optional Event parameters which modify the event.
	@discussion
		CHHapticEvents have a relative time property to allow specifying the time relationship between events in a pattern.
 */
CH_EXPORT API_AVAILABLE(ios(13.0), macos(10.15), tvos(14.0), macCatalyst(13.0)) API_UNAVAILABLE(watchos)
@interface CHHapticEvent : NSObject

/*!	@property type
		The type of event.
 */
@property (readonly) CHHapticEventType type;

/*!	@property eventParameters
		NSArray of Event parameters.  Can be empty.
 */
@property (readonly) NSArray<CHHapticEventParameter *> *eventParameters;

/*!	@property relativeTime
		The relative time for this event versus the start time of the pattern.  Units are seconds.
 */
@property (readwrite) NSTimeInterval relativeTime;

/*!	@property duration
		The duration for this event.  Units are seconds.  If unset (0.0), Continuous event types will have no fixed end.
 */
@property (readwrite) NSTimeInterval duration;

- (nullable instancetype)init NS_UNAVAILABLE;

/*! @method initWithEventType:parameters:relativeTime
	@abstract
		Initialize a new CHHapticEvent.  This can only be used to create Transient event types (which do not require a duration).
	@param type
		The type of event.
	@param eventParams
		An NSArray of Event parameters.  Can be empty.
	@param time
		The relative time for this event versus the other events in the CHHapticPattern.
 */
- (instancetype)initWithEventType:(CHHapticEventType)type
					   parameters:(NSArray<CHHapticEventParameter *> *)eventParams
					 relativeTime:(NSTimeInterval)time;

/*! @method initWithEventType:parameters:relativeTime:duration
	@abstract
		Initialize a new CHHapticEvent, providing a duration.
	@param type
		The type of event.
	@param eventParams
		An NSArray of Event parameters.  Can be empty.
	@param time
		The relative time for this event versus the other events in the CHHapticPattern.
 	@param duration
 		For Continuous event types, the length of time before the event playback begins its release.
 		For Transient event types, the logical length of the event (used to determine pattern end and loop points).
 */
- (instancetype)initWithEventType:(CHHapticEventType)type
					   parameters:(NSArray<CHHapticEventParameter *> *)eventParams
					 relativeTime:(NSTimeInterval)time
						 duration:(NSTimeInterval)duration
;

/*! @method initWithAudioResourceID:parameters:relativeTime
	@abstract
		Initialize a new CHHapticEvent using a previously-loaded audio resource.
	@param resID
		A previously-registered audio resource ID (see `CHHapticEngine(registerAudioResource:options:error)`).
	@param eventParams
		An NSArray of Event parameters.  Can be empty.
	@param time
		The relative time for this event versus the other events in the CHHapticPattern.
 */
- (instancetype)initWithAudioResourceID:(CHHapticAudioResourceID)resID
							 parameters:(NSArray<CHHapticEventParameter *> *)eventParams
						   relativeTime:(NSTimeInterval)time;

/*! @method initWithAudioResourceID:parameters:relativeTime:duration
	@abstract
		Initialize a new CHHapticEvent using a previously-loaded audio resource.
	@param resID
		A previously-registered audio resource ID (see `CHHapticEngine(registerAudioResource:options:error)`).
	@param eventParams
		An NSArray of Event parameters.  Can be empty.
	@param time
		The relative time for this event versus the other events in the CHHapticPattern.
	@param duration
		The duration of this event in seconds.
 	@discussion
		If the specified duration is less than the duration of the audio resource, its playback will be truncated.  If it
		is greater, its playback will be padded with silence.  If zero, it will be ignored.
 */
- (instancetype)initWithAudioResourceID:(CHHapticAudioResourceID)resID
							 parameters:(NSArray<CHHapticEventParameter *> *)eventParams
						   relativeTime:(NSTimeInterval)time
							   duration:(NSTimeInterval)duration;

@end

NS_ASSUME_NONNULL_END

