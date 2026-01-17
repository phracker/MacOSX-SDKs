/*==================================================================================================
 File:       CHHapticParameter.h
 
 Contains:   API for creating event and dynamic parameters
 
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

/*! @enum CHHapticEventParameterID
	@abstract
		Parameters used to modify individual haptic and/or audio events.
	@discussion
		Event parameters are specified as part of the creation of a CHHapticEvent or in an event definition in a haptic pattern.
 		The combination of Event parameters will determine the character of the haptic or audio event.

	@constant   CHHapticEventParameterIDHapticIntensity
		The perceived intensity (volume) of a haptic event.
 		Range: 0.0 (maximum attenuation) to 1.0 (no attenuation).
 
	@constant   CHHapticEventParameterIDHapticSharpness
		Depending on the event's signal content, this may map to frequency, frequency content (i.e., filtering),
 		or some other signal processing.
		Range: 0.0 (least sharp) to 1.0 (most sharp).

 	@constant	CHHapticEventParameterIDAttackTime
		The attack time adjuster for a Continuous event's envelope.
		Range: 0.0 to 1.0, with default: 0.0 (shortest attack time).  Higher values increase the time exponentially.
		Not all event types respond to this parameter.
 
	@constant	CHHapticEventParameterIDDecayTime
		The decay time adjuster for a Continuous event's envelope.
		Range: 0.0 to 1.0, with default: 0.0 (shortest decay time).  Higher values increase the time exponentially.
		For envelope decay to take effect, the `CHHapticEventParameterIDSustained` parameter must be set to 0.0.
 		Not all event types respond to this parameter.
 
	@constant	CHHapticEventParameterIDReleaseTime
		The release time adjuster for a Continuous event's envelope.
 		Range: 0.0 to 1.0, with default: 0.0 (shortest release time).  Higher values increase the time exponentially.
		Not all Continuous event types respond to this parameter.
 
	@constant	CHHapticEventParameterIDSustained
		A boolean (1.0 or 0.0) which indicates whether a Continuous event sustains for its specified duration
		(using an Attack/Release envelope) or whether the event ends when its envelope decay segment reaches its minimum
		(i.e., using an Attack/Decay envelope with no sustain).  Default: 1.0 (sustained, Attack/Release).
 
	@constant   CHHapticEventParameterIDAudioVolume
		The volume of an audio event.
		Range: 0.0 (maximum attenuation) to 1.0 (no attenuation).
 
	@constant	CHHapticEventParameterIDAudioPitch
		The pitch adjuster for audio events.
		Range: -1.0 (lowest pitch) to 1.0 (highest pitch).
 
	@constant   CHHapticEventParameterIDAudioPan
		The stereo panning for an audio event.
		Range: -1.0 (panned full left) to 1.0 (panned full right).  Default: 0.0 (panned center).
 
	@constant	CHHapticEventParameterIDAudioBrightness
		The high frequency content an audio event.
		Range: 0.0 (frequency content reduced the most) to 1.0 (no reduction of frequency content).  Default: 1.0.
*/

typedef NSString *CHHapticEventParameterID NS_TYPED_ENUM;

CH_EXPORT CHHapticEventParameterID CHHapticEventParameterIDHapticIntensity API_AVAILABLE(ios(13.0), macos(10.15));
CH_EXPORT CHHapticEventParameterID CHHapticEventParameterIDHapticSharpness API_AVAILABLE(ios(13.0), macos(10.15));

CH_EXPORT CHHapticEventParameterID CHHapticEventParameterIDAttackTime API_AVAILABLE(ios(13.0), macos(10.15));
CH_EXPORT CHHapticEventParameterID CHHapticEventParameterIDDecayTime API_AVAILABLE(ios(13.0), macos(10.15));
CH_EXPORT CHHapticEventParameterID CHHapticEventParameterIDReleaseTime API_AVAILABLE(ios(13.0), macos(10.15));
CH_EXPORT CHHapticEventParameterID CHHapticEventParameterIDSustained API_AVAILABLE(ios(13.0), macos(10.15));

CH_EXPORT CHHapticEventParameterID CHHapticEventParameterIDAudioVolume API_AVAILABLE(ios(13.0), macos(10.15));
CH_EXPORT CHHapticEventParameterID CHHapticEventParameterIDAudioPitch API_AVAILABLE(ios(13.0), macos(10.15));
CH_EXPORT CHHapticEventParameterID CHHapticEventParameterIDAudioPan API_AVAILABLE(ios(13.0), macos(10.15));
CH_EXPORT CHHapticEventParameterID CHHapticEventParameterIDAudioBrightness API_AVAILABLE(ios(13.0), macos(10.15));

/*!	@enum CHHapticDynamicParameterID
	@abstract
		Parameters used to dynamically modify all haptic or audio events within a pattern.
	@discussion
		Dynamic parameters are not tied to specific events; each dynamic parameter modifies (modulates) the
		effect of the corresponding event parameter for events which respond to the parameter.
 
		The CHHapticDynamicParameterIDHaptic types only affect haptic event types, and the CHHapticDynamicParameterIDAudio
		types only affect audio event types.  Not all CHHapticDynamicParameterIDs will have an effect on every CHHapticEventType.
 
	@constant   CHHapticDynamicParameterIDHapticIntensityControl
		Adjusts the intensity of all active and future haptic events.
		Range: 0.0 (event intensities reduced by the maximum amount) to 1.0 (no effect on event intensities).
 		Default: 1.0.
 
	@constant   CHHapticDynamicParameterIDHapticSharpnessControl
		This will adjust the frequency, frequency content (i.e., filtering), or other aspects of all active and future haptic events.
		Range: -1.0 (less sharp) to 1.0 (more sharp).  Default: 0.0 (no effect).
 
	@constant	CHHapticDynamicParameterIDHapticAttackTimeControl
		Adjusts the envelope attack time of all active and future haptic events.
		Range: -1.0 (event attacks shorter) to 1.0 (event attacks longer).  Default: 0.0 (no effect).
		Not all haptic event types respond to this parameter.
 
	@constant	CHHapticDynamicParameterIDHapticDecayTimeControl
 		Adjusts the envelope decay time of all active and future Transient haptic events.
		Range: -1.0 (event decays shorter) to 1.0 (event decays longer).  Default: 0.0 (no effect).
		Not all haptic event types respond to this parameter.

	@constant	CHHapticDynamicParameterIDHapticReleaseTimeControl
		Adjusts the envelope release time of all active and future Continuous haptic events.
		Range: -1.0 (event releases shorter) to 1.0 (event releases longer).  Default: 0.0 (no effect).
		Not all haptic event types respond to this parameter.

	@constant	CHHapticDynamicParameterIDAudioVolumeControl
		Adjusts the volume of all active and future audio events.
		Range: 0.0 (event intensities reduced by the maximum amount) to 1.0 (no effect).
		Default: 1.0.

	@constant	CHHapticDynamicParameterIDAudioPanControl
		Adjusts the panning of all active and future audio events.
		Range: -1.0 (events panned more left) to 1.0 (event panned more right).  Default: 0.0 (no effect).

	@constant	CHHapticDynamicParameterIDAudioBrightnessControl
		Adjusts the high frequency content of all active and future audio events.
		Range: -1.0 (more filtering) to 1.0 (less filtering).  Default: 0.0 (no effect).

	@constant	CHHapticDynamicParameterIDAudioPitchControl
		Adjusts the transposition of the audio event.
		Range: -1.0 to 1.0.  Negative values decrease pitch; positive values increase pitch.
 		Default: 0.0 (no effect).

	@constant	CHHapticDynamicParameterIDAudioAttackTimeControl
		Adjusts the envelope attack time of all active and future audio events.
		Range: -1.0 (event attacks shorter) to 1.0 (event attacks longer).  Default: 0.0 (no effect).
		Not all audio event types respond to this parameter.

	@constant	CHHapticDynamicParameterIDAudioDecayTimeControl
		Adjusts the envelope decay time of all active and future Transient audio events.
		Range: -1.0 (event decays shorter) to 1.0 (event decays longer).  Default: 0.0 (no effect).
		Not all audio event types respond to this parameter.

	@constant	CHHapticDynamicParameterIDAudioReleaseTimeControl
		Adjusts the envelope release time of all active and future Continuous audio events.
		Range: -1.0 (event releases shorter) to 1.0 (event releases longer).  Default: 0.0 (no effect).
		Not all audio event types respond to this parameter.
 */

typedef NSString *CHHapticDynamicParameterID NS_TYPED_ENUM;

CH_EXPORT CHHapticDynamicParameterID CHHapticDynamicParameterIDHapticIntensityControl API_AVAILABLE(ios(13.0), macos(10.15));
CH_EXPORT CHHapticDynamicParameterID CHHapticDynamicParameterIDHapticSharpnessControl API_AVAILABLE(ios(13.0), macos(10.15));
CH_EXPORT CHHapticDynamicParameterID CHHapticDynamicParameterIDHapticAttackTimeControl API_AVAILABLE(ios(13.0), macos(10.15));
CH_EXPORT CHHapticDynamicParameterID CHHapticDynamicParameterIDHapticDecayTimeControl API_AVAILABLE(ios(13.0), macos(10.15));
CH_EXPORT CHHapticDynamicParameterID CHHapticDynamicParameterIDHapticReleaseTimeControl API_AVAILABLE(ios(13.0), macos(10.15));

CH_EXPORT CHHapticDynamicParameterID CHHapticDynamicParameterIDAudioVolumeControl API_AVAILABLE(ios(13.0), macos(10.15));
CH_EXPORT CHHapticDynamicParameterID CHHapticDynamicParameterIDAudioPanControl API_AVAILABLE(ios(13.0), macos(10.15));
CH_EXPORT CHHapticDynamicParameterID CHHapticDynamicParameterIDAudioBrightnessControl API_AVAILABLE(ios(13.0), macos(10.15));
CH_EXPORT CHHapticDynamicParameterID CHHapticDynamicParameterIDAudioPitchControl API_AVAILABLE(ios(13.0), macos(10.15));
CH_EXPORT CHHapticDynamicParameterID CHHapticDynamicParameterIDAudioAttackTimeControl API_AVAILABLE(ios(13.0), macos(10.15));
CH_EXPORT CHHapticDynamicParameterID CHHapticDynamicParameterIDAudioDecayTimeControl API_AVAILABLE(ios(13.0), macos(10.15));
CH_EXPORT CHHapticDynamicParameterID CHHapticDynamicParameterIDAudioReleaseTimeControl API_AVAILABLE(ios(13.0), macos(10.15));

/*!
	@class CHHapticEventParameter
	@abstract
		A CHHapticEventParameter contains a CHHapticEventParameterID/value pair which helps determine the initial character
		of a haptic or audio event.
 */
CH_EXPORT API_AVAILABLE(ios(13.0), macos(10.15))
@interface CHHapticEventParameter : NSObject

/*!
	@property parameterID
		The ID of the event parameter to use.
 */
@property (readonly) CHHapticEventParameterID parameterID;

/*!
	@property value
		The value of the event parameter.
 */
@property (readwrite) float value;

- (nullable instancetype)init NS_UNAVAILABLE;
- (instancetype)initWithParameterID:(CHHapticEventParameterID)parameterID
							  value:(float)value NS_DESIGNATED_INITIALIZER;

@end

/*!	@class CHHapticDynamicParameter
	@abstract
		A CHHapticDynamicParameter contains a CHHapticDynamicParameterID/value pair which will modify (modulate) the ongoing character
		of a haptic or audio event.
	@discussion
		CHHapticDynamicParameters have a relative time property to allow specifying the time relationship between parameters in a pattern.
 */

CH_EXPORT API_AVAILABLE(ios(13.0), macos(10.15))
@interface CHHapticDynamicParameter : NSObject

/*!	@property parameterID
		The ID of the dynamic parameter to use.
 */
@property (readonly) CHHapticDynamicParameterID parameterID;

/*!	@property value
		The value of the parameter.
 */
@property (readwrite) float value;

/*!	@property relativeTime
		The time at which the parameter should be applied, relative to the start time for the pattern.
 */
@property (readwrite) NSTimeInterval relativeTime;

- (nullable instancetype)init NS_UNAVAILABLE;

/*! @method initWithParameterID:value:relativeTime
	@abstract
		Initialize a CHHapticDynamicParameter with a parameter ID, value, and relative time.
	@param parameterID
		The CHHapticDynamicParameterID for the desired parameter change.
	@param value
		The value for that parameter.
	@param time
		The time at which this parameter should be applied, relative to the start time of the pattern.
 */
- (instancetype)initWithParameterID:(CHHapticDynamicParameterID)parameterID
							  value:(float)value
					   relativeTime:(NSTimeInterval)time NS_DESIGNATED_INITIALIZER;
@end

/*!	@class CHHapticParameterCurveControlPoint
 	@abstract
 		A CHHapticParameterCurveControlPoint contains a time/value pair for a single control point within a CHHapticParameterCurve.
 	@discussion
 		The relativeTime property specifies the amount of time elapsed since the start of the CHHapticParameterCurve before the
 		value is reached.
 */
CH_EXPORT API_AVAILABLE(ios(13.0), macos(10.15))
@interface CHHapticParameterCurveControlPoint : NSObject

@property (readwrite) NSTimeInterval	relativeTime;
@property (readwrite) float 			value;

- (nullable instancetype)init NS_UNAVAILABLE;

/*! @method initWithRelativeTime:value
 	@abstract
 		Initialize a CHHapticParameterCurveControlPoint with a relative time and value.
 	@param value
 		The value of the associated parameter.
 	@param time
 		The time at which the associated parameter will reach this value, relative to the start time of the parameter curve.
 */
- (instancetype)initWithRelativeTime:(NSTimeInterval)time
							   value:(float)value NS_DESIGNATED_INITIALIZER;
@end


/*!	@class CHHapticParameterCurve
 	@abstract
 		A CHHapticParameterCurve is a set of CHHapticParameterCurveControlPoints which describe the control (inflection) points
 		for the parameter values to be applied to the associated pattern.
 	@discussion
 		The CHHapticParameterCurve generates an interpolated value output which passed through each control point at its
 		associated relative time.  These times will all be relative to the start time of the CHHapticParameterCurve within the
 		playing pattern.
 */
@interface CHHapticParameterCurve : NSObject

@property (readonly) CHHapticDynamicParameterID						parameterID;
@property (readwrite) NSTimeInterval									relativeTime;
@property (readonly)  NSArray<CHHapticParameterCurveControlPoint*> * controlPoints;

- (nullable instancetype)init NS_UNAVAILABLE;

/*! @method initWithParameterID:controlPoints:relativeTime
 	@abstract
 		Initialize a CHHapticParameterCurve with a parameter ID, time, and an array of CHHapticParameterCurveControlPoint.
 	@param parameterID
 		The CHHapticDynamicParameterID for the desired parameter.
	@param controlPoints
		An array of CHHapticParameterCurveControlPoints.
 	@param relativeTime
 		The time at which this parameter curve should start, relative to the start time of the CHHapticPattern to which this
 		parameter curve belongs.
 */
- (instancetype)initWithParameterID:(CHHapticDynamicParameterID)parameterID
					  controlPoints:(NSArray<CHHapticParameterCurveControlPoint *> *)controlPoints
					   relativeTime:(NSTimeInterval)relativeTime NS_DESIGNATED_INITIALIZER;

@end
NS_ASSUME_NONNULL_END

