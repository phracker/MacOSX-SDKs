/*
	File:		AVAudioTime.h
	Framework:	AVFoundation
	
	Copyright (c) 2014-2015 Apple Inc. All Rights Reserved.
*/

#import <AVFAudio/AVAudioTypes.h>

NS_ASSUME_NONNULL_BEGIN

/*!
	@class AVAudioTime
	@abstract Represent a moment in time.
	@discussion
		AVAudioTime is used in AVAudioEngine to represent time. Instances are immutable.
		
		A single moment in time may be represented in two different ways:
		1. mach_absolute_time(), the system's basic clock. Commonly referred to as "host time."
		2. audio samples at a particular sample rate
		
		A single AVAudioTime instance may contain either or both representations; it might
		represent only a sample time, only a host time, or both.
		
Rationale for using host time:
[a] internally we are using AudioTimeStamp, which uses host time, and it seems silly to divide
[b] it is consistent with a standard system timing service
[c] we do provide conveniences to convert between host ticks and seconds (host time divided by
	frequency) so client code wanting to do what should be straightforward time computations can at 
	least not be cluttered by ugly multiplications and divisions by the host clock frequency.
*/

NS_SWIFT_SENDABLE API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0))
@interface AVAudioTime : NSObject {
@private
	AudioTimeStamp _ats;
	double _sampleRate;
	void *_reserved;
}

/*!	@method initWithAudioTimeStamp:sampleRate:
*/
- (instancetype)initWithAudioTimeStamp: (const AudioTimeStamp *)ts sampleRate: (double)sampleRate;

/*! @method initWithHostTime:
*/
- (instancetype)initWithHostTime:(uint64_t)hostTime;

/*! @method initWithSampleTime:atRate:
*/
- (instancetype)initWithSampleTime:(AVAudioFramePosition)sampleTime atRate:(double)sampleRate;

/*! @method initWithHostTime:sampleTime:atRate:
*/
- (instancetype)initWithHostTime:(uint64_t)hostTime sampleTime:(AVAudioFramePosition)sampleTime atRate:(double)sampleRate;

/*! @method timeWithAudioTimeStamp:sampleRate:
*/
+ (instancetype)timeWithAudioTimeStamp: (const AudioTimeStamp *)ts sampleRate: (double)sampleRate;

/*! @method timeWithHostTime:
*/
+ (instancetype)timeWithHostTime:(uint64_t)hostTime;

/*! @method timeWithSampleTime:atRate:
*/
+ (instancetype)timeWithSampleTime:(AVAudioFramePosition)sampleTime atRate:(double)sampleRate;

/*! @method timeWithHostTime:sampleTime:atRate:
*/
+ (instancetype)timeWithHostTime:(uint64_t)hostTime sampleTime:(AVAudioFramePosition)sampleTime atRate:(double)sampleRate;

/*!	@method hostTimeForSeconds:
	@abstract Convert seconds to host time.
*/
+ (uint64_t)hostTimeForSeconds:(NSTimeInterval)seconds;

/*!	@method secondsForHostTime:
	@abstract Convert host time to seconds.
*/
+ (NSTimeInterval)secondsForHostTime:(uint64_t)hostTime;

/*!	@method extrapolateTimeFromAnchor:
	@abstract Converts between host and sample time.
	@param anchorTime
		An AVAudioTime with a more complete AudioTimeStamp than that of the receiver (self).
	@return
		the extrapolated time
	@discussion
		If anchorTime is an AVAudioTime where both host time and sample time are valid,
		and self is another timestamp where only one of the two is valid, this method
		returns a new AVAudioTime copied from self and where any additional valid fields provided by
		the anchor are also valid.
 
		Note that the anchorTime must have both host and sample time valid, and self must have
		sample rate and at least one of host or sample time valid. Otherwise this method returns nil.

<pre>
// time0 has a valid audio sample representation, but no host time representation.
AVAudioTime *time0 = [AVAudioTime timeWithSampleTime: 0.0 atRate: 44100.0];
// anchor has a valid host time representation and sample time representation.
AVAudioTime *anchor = [player playerTimeForNodeTime: player.lastRenderTime];
// fill in valid host time representation
AVAudioTime *fullTime0 = [time0 extrapolateTimeFromAnchor: anchor];
</pre>
*/
- (nullable AVAudioTime *)extrapolateTimeFromAnchor:(AVAudioTime *)anchorTime;


/*! @property hostTimeValid
	@abstract Whether the hostTime property is valid.
*/
@property (nonatomic, readonly, getter=isHostTimeValid) BOOL hostTimeValid;

/*! @property hostTime
	@abstract The host time.
*/
@property (nonatomic, readonly) uint64_t hostTime;

/*! @property sampleTimeValid
	@abstract Whether the sampleTime and sampleRate properties are valid.
*/
@property (nonatomic, readonly, getter=isSampleTimeValid) BOOL sampleTimeValid;

/*!	@property sampleTime
	@abstract The time as a number of audio samples, as tracked by the current audio device.
*/
@property (nonatomic, readonly) AVAudioFramePosition sampleTime;

/*!	@property sampleRate
	@abstract The sample rate at which sampleTime is being expressed.
*/
@property (nonatomic, readonly) double sampleRate;

/*! @property audioTimeStamp
	@abstract The time expressed as an AudioTimeStamp structure.
	@discussion
		This may be useful for compatibility with lower-level CoreAudio and AudioToolbox API's.
*/
@property (readonly, nonatomic) AudioTimeStamp audioTimeStamp;


@end

NS_ASSUME_NONNULL_END
