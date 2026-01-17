/*!
	@file		AUAudioUnit.h
 	@framework	AudioUnit.framework
 	@copyright	(c) 2015 Apple, Inc. All rights reserved.

	@brief		Objective-C interfaces for hosting and implementing Audio Units.
*/

#if __OBJC2__

#import <AudioUnit/AUParameters.h>
#import <Foundation/NSExtensionRequestHandling.h>

// for AudioObjectID for setDeviceID:error:
#import <CoreAudio/AudioHardwareBase.h>

NS_ASSUME_NONNULL_BEGIN

// forward declarations
@class AVAudioFormat;
@class AUAudioUnitBusArray;
@class AUAudioUnitBus;
@class AUAudioUnitPreset;
@protocol AUAudioUnitFactory;

// =================================================================================================

/*!	@typedef	AUAudioUnitStatus
	@brief		A result code returned from an audio unit's render function.
*/
typedef OSStatus AUAudioUnitStatus;

/*!	@typedef	AUEventSampleTime
	@brief		Expresses time as a sample count.
	@discussion
		Sample times are normally positive, but hosts can propagate HAL sample times through audio
		units, and HAL sample times can be small negative numbers.
*/
typedef int64_t AUEventSampleTime;

/*!	@var		AUEventSampleTimeImmediate
	@brief		A special value of AUEventSampleTime indicating "immediately."
	@discussion
		Callers of AUScheduleParameterBlock and AUScheduleMIDIEventBlock can pass
		AUEventSampleTimeImmediate to indicate that the event should be rendered as soon as
		possible, in the next cycle. A caller may also add a small (less than 4096) sample frame
		offset to this constant. The base AUAudioUnit implementation translates this constant to a
		true AUEventSampleTime; subclasses will not see it.
*/
enum : AUEventSampleTime {
	AUEventSampleTimeImmediate = (AUEventSampleTime)0xffffffff00000000LL
};

/*!	@typedef	AUAudioFrameCount
	@brief		A number of audio sample frames.
	@discussion
		This is `uint32_t` for impedence-matching with the pervasive use of `UInt32` in AudioToolbox
		and C AudioUnit API's, as well as `AVAudioFrameCount`.
*/
typedef uint32_t AUAudioFrameCount;

/*!	@typedef	AUAudioChannelCount
	@brief		A number of audio channels.
	@discussion
		This is `uint32_t` for impedence-matching with the pervasive use of `UInt32` in AudioToolbox
		and C AudioUnit API's, as well as `AVAudioChannelCount`.
*/
typedef uint32_t AUAudioChannelCount;

// =================================================================================================

/*!	@enum		AUAudioUnitBusType
	@brief		Describes whether a bus array is for input or output.
*/
typedef NS_ENUM(NSInteger, AUAudioUnitBusType) {
	AUAudioUnitBusTypeInput		= 1,
	AUAudioUnitBusTypeOutput	= 2
};

// =================================================================================================

/*!	@typedef	AURenderPullInputBlock
	@brief		Block to supply audio input to AURenderBlock.
	@param actionFlags
		Pointer to action flags.
	@param timestamp
		The HAL time at which the input data will be rendered. If there is a sample rate conversion
		or time compression/expansion downstream, the sample time will not be valid.
	@param frameCount
		The number of sample frames of input requested.
	@param inputBusNumber
		The index of the input bus being pulled.
	@param inputData
		The input audio data.

		The caller must supply valid buffers in inputData's mBuffers' mData and mDataByteSize.
		mDataByteSize must be consistent with frameCount. This block may provide input in those
		specified buffers, or it may replace the mData pointers with pointers to memory which it
		owns and guarantees will remain valid until the next render cycle.
	@return
		An AUAudioUnitStatus result code. If an error is returned, the input data should be assumed 
		to be invalid.
*/
typedef AUAudioUnitStatus (^AURenderPullInputBlock)(AudioUnitRenderActionFlags *actionFlags, const AudioTimeStamp *timestamp, AUAudioFrameCount frameCount, NSInteger inputBusNumber, AudioBufferList *inputData);

/*!	@typedef	AURenderBlock
	@brief		Block to render the audio unit.
	@discussion
		All realtime operations are implemented using blocks to avoid ObjC method dispatching and
		the possibility of blocking.
	@param actionFlags
		Pointer to action flags.
	@param timestamp
		The HAL time at which the output data will be rendered. If there is a sample rate conversion
		or time compression/expansion downstream, the sample time will not have a defined
		correlation with the AudioDevice sample time.
	@param frameCount
		The number of sample frames to render.
	@param outputBusNumber
		The index of the output bus to render.
	@param outputData
		The output bus's render buffers and flags.

		The buffer pointers (outputData->mBuffers[x].mData) may be null on entry, in which case the
		block will render into memory it owns and modify the mData pointers to point to that memory.
		The block is responsible for preserving the validity of that memory until it is next called
		to render, or deallocateRenderResources is called.

		If, on entry, the mData pointers are non-null, the block will render into those buffers.
	@param pullInputBlock
		A block which the AU will call in order to pull for input data. May be nil for instrument
		and generator audio units (which do not have input busses).
	@return
		An `AUAudioUnitStatus` result code. If an error is returned, the output data should be assumed
		to be invalid.
*/
typedef AUAudioUnitStatus (^AURenderBlock)(AudioUnitRenderActionFlags *actionFlags, const AudioTimeStamp *timestamp, AUAudioFrameCount frameCount, NSInteger outputBusNumber, AudioBufferList *outputData, AURenderPullInputBlock __nullable pullInputBlock);

/*!	@typedef	AURenderObserver
	@brief		Block called when an audio unit renders.
	@discussion
		This block is called by the base class's AURenderBlock before and after each render cycle.
		The observer can distinguish between before and after using the PreRender and PostRender
		flags.
		
		The parameters are identical to those of AURenderBlock.
*/
typedef void (^AURenderObserver)(AudioUnitRenderActionFlags actionFlags, const AudioTimeStamp *timestamp, AUAudioFrameCount frameCount, NSInteger outputBusNumber);

/*!	@typedef	AUScheduleParameterBlock
	@brief		Block to schedule parameter changes.
	@discussion
		Not all parameters are rampable; check the parameter's flags.
	@param eventSampleTime
		The sample time (timestamp->mSampleTime) at which the parameter is to begin changing. When
		scheduling parameters during the render cycle (e.g. via a render observer) this time can be
		AUEventSampleTimeImmediate plus an optional buffer offset, in which case the event is
		scheduled at that position in the current render cycle.
	@param rampDurationSampleFrames
		The number of sample frames over which the parameter's value is to ramp, or 0 if the 
		parameter change should take effect immediately.
	@param parameterAddress
		The parameter's address.
	@param value
		The parameter's new value if the ramp duration is 0; otherwise, the value at the end
		of the scheduled ramp.
*/
typedef void (^AUScheduleParameterBlock)(AUEventSampleTime eventSampleTime, AUAudioFrameCount rampDurationSampleFrames, AUParameterAddress parameterAddress, AUValue value);

/*!	@typedef	AUScheduleMIDIEventBlock
	@brief		Block to schedule MIDI events.
	@param eventSampleTime
		The sample time (timestamp->mSampleTime) at which the MIDI event is to occur. When
		scheduling events during the render cycle (e.g. via a render observer) this time can be
		AUEventSampleTimeImmediate plus an optional buffer offset, in which case the event is
		scheduled at that position in the current render cycle.
	@param cable
		The virtual cable number.
	@param length
		The number of bytes of MIDI data in the provided event(s).
	@param midiBytes
		One or more valid MIDI 1.0 events, except sysex which must always be sent as the only event
		in the chunk. Also, running status is not allowed.
*/
typedef void (^AUScheduleMIDIEventBlock)(AUEventSampleTime eventSampleTime, uint8_t cable, NSInteger length, const uint8_t *midiBytes);

/*!	@typedef	AUHostMusicalContextBlock
	@brief		Block by which hosts provide musical tempo, time signature, and beat position.
	@param	currentTempo
		The current tempo in beats per minute.
	@param	timeSignatureNumerator
		The numerator of the current time signature.
	@param	timeSignatureDenominator
		The denominator of the current time signature.
	@param	currentBeatPosition
		The precise beat position of the beginning of the current buffer being rendered.
	@param	sampleOffsetToNextBeat
		The number of samples between the beginning of the buffer being rendered and the next beat
		(can be 0).
	@param	currentMeasureDownbeatPosition
		The beat position corresponding to the beginning of the current measure.
	@return
		YES for success.
	@discussion
		If the host app provides this block to an AUAudioUnit (as its musicalContextBlock), then
		the block may be called at the beginning of each render cycle to obtain information about
		the current render cycle's musical context.
		
		Any of the provided parameters may be null to indicate that the audio unit is not interested
		in that particular piece of information.
*/
typedef BOOL (^AUHostMusicalContextBlock)(double * __nullable currentTempo, double * __nullable timeSignatureNumerator, NSInteger * __nullable timeSignatureDenominator, double * __nullable currentBeatPosition, NSInteger * __nullable sampleOffsetToNextBeat, double * __nullable currentMeasureDownbeatPosition);

/*!	@enum		AUHostTransportState
	@brief		Flags describing the host's transport state.
	@constant	AUHostTransportStateChanged
		True if, since the callback was last called, there was a change to the state of, or
		discontinuities in, the host's transport. Can indicate such state changes as
		start/stop, or seeking to another position in the timeline.
	@constant	AUHostTransportStateMoving
		True if the transport is moving.
	@constant	AUHostTransportStateRecording
		True if the host is recording, or prepared to record. Can be true with or without the
		transport moving.
	@constant	AUHostTransportStateCycling
		True if the host is cycling or looping.
*/
typedef NS_OPTIONS(NSUInteger, AUHostTransportStateFlags) {
	AUHostTransportStateChanged			= 1,
	AUHostTransportStateMoving			= 2,
	AUHostTransportStateRecording		= 4,
	AUHostTransportStateCycling			= 8
};

/*!	@typedef	AUHostTransportStateBlock
	@brief		Block by which hosts provide information about their transport state.
	@param	transportStateFlags
		The current state of the transport.
	@param	currentSamplePosition
		The current position in the host's timeline, in samples at the audio unit's output sample
		rate.
	@param	cycleStartBeatPosition
		If cycling, the starting beat position of the cycle.
	@param	cycleEndBeatPosition
		If cycling, the ending beat position of the cycle.
	@discussion
		If the host app provides this block to an AUAudioUnit (as its transportStateBlock), then
		the block may be called at the beginning of each render cycle to obtain information about
		the current transport state.
		
		Any of the provided parameters may be null to indicate that the audio unit is not interested
		in that particular piece of information.
*/
typedef BOOL (^AUHostTransportStateBlock)(AUHostTransportStateFlags * __nullable transportStateFlags, double * __nullable currentSamplePosition, double * __nullable cycleStartBeatPosition, double * __nullable cycleEndBeatPosition);

// =================================================================================================

/*!	@class		AUAudioUnit
	@brief		An audio unit instance.
	@discussion
		AUAudioUnit is a host interface to an audio unit. Hosts can instantiate either version 2 or
		version 3 units with this class, and to some extent control whether an audio unit is
		instantiated in-process or in a separate extension process.
		
		Implementors of version 3 audio units can and should subclass AUAudioUnit. To port an
		existing version 2 audio unit easily, AUAudioUnitV2Bridge can be subclassed.
		
		These are the ways in which audio unit components can be registered:
		
		- (v2) Packaged into a component bundle containing an AudioComponents Info.plist entry,
		referring to an AudioComponentFactoryFunction. See AudioComponent.h.
		
		- (v2) AudioComponentRegister. Associates a component description with an
		AudioComponentFactoryFunction. See AudioComponent.h.
		
		- (v3) Packaged into an app extension containing an AudioComponents Info.plist entry.
		The principal class must conform to the AUAudioUnitFactory protocol, which will typically
		instantiate an AUAudioUnit subclass.

		- (v3) `+[AUAudioUnit registerSubclass:asComponentDescription:name:version:]`. Associates
		a component description with an AUAudioUnit subclass.
		
		A host need not be aware of the concrete subclass of AUAudioUnit that is being instantiated.
		`initWithComponentDescription:options:error:` ensures that the proper subclass is used.
		
		When using AUAudioUnit with a v2 audio unit, or the C AudioComponent and AudioUnit API's
		with a v3 audio unit, all major pieces of functionality are bridged between the
		two API's. This header describes, for each v3 method or property, the v2 equivalent.
*/
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface AUAudioUnit : NSObject

- (instancetype)init NS_UNAVAILABLE;

/*!	@method		initWithComponentDescription:options:error:
	@brief		Designated initializer.
	@param componentDescription
		A single AUAudioUnit subclass may implement multiple audio units, for example, an effect
		that can also function as a generator, or a cluster of related effects. The component
		description specifies the component which was instantiated.
	@param options
		Options for loading the unit in-process or out-of-process.
	@param outError
		Returned in the event of failure.
*/
- (nullable instancetype)initWithComponentDescription:(AudioComponentDescription)componentDescription options:(AudioComponentInstantiationOptions)options error:(NSError **)outError NS_DESIGNATED_INITIALIZER;

/*!	@method		initWithComponentDescription:error:
	@brief		Convenience initializer (omits options).
*/
- (nullable instancetype)initWithComponentDescription:(AudioComponentDescription)componentDescription error:(NSError **)outError;

/*!	@method	instantiateWithComponentDescription:options:completionHandler:
	@brief	Asynchronously create an AUAudioUnit instance.
	@param componentDescription
		The AudioComponentDescription of the audio unit to instantiate.
	@param options
		See the discussion of AudioComponentInstantiationOptions in AudioUnit/AudioComponent.h.
	@param completionHandler
		Called in a thread/dispatch queue context internal to the implementation. The client should
		retain the supplied AUAudioUnit.
	@discussion
		Certain types of AUAudioUnits must be instantiated asynchronously -- see 
		the discussion of kAudioComponentFlag_RequiresAsyncInstantiation in
		AudioUnit/AudioComponent.h.

		Note: Do not block the main thread while waiting for the completion handler to be called;
		this can deadlock.
*/
+ (void)instantiateWithComponentDescription:(AudioComponentDescription)componentDescription options:(AudioComponentInstantiationOptions)options completionHandler:(void (^)(AUAudioUnit * __nullable audioUnit, NSError * __nullable error))completionHandler;

/*!	@property	componentDescription
	@brief		The AudioComponentDescription with which the audio unit was created.
*/
@property (NS_NONATOMIC_IOSONLY, readonly) AudioComponentDescription componentDescription;

/*!	@property	component
	@brief		The AudioComponent which was found based on componentDescription when the
				audio unit was created.
*/
@property (NS_NONATOMIC_IOSONLY, readonly) AudioComponent component;

/*!	@property	componentName
	@brief		The unit's component's name.
	@discussion
		By convention, an audio unit's component name is its manufacturer's name, plus ": ",
		plus the audio unit's name. The audioUnitName and manufacturerName properties are derived
		from the component name.
*/
@property (NS_NONATOMIC_IOSONLY, readonly, copy, nullable) NSString *componentName;

/*!	@property	audioUnitName
	@brief		The audio unit's name.
*/
@property (NS_NONATOMIC_IOSONLY, readonly, copy, nullable) NSString *audioUnitName;

/*!	@property	manufacturerName
	@brief		The manufacturer's name.
*/
@property (NS_NONATOMIC_IOSONLY, readonly, copy, nullable) NSString *manufacturerName;

/*!	@property	componentVersion
	@brief		The unit's component's version.
*/
@property (NS_NONATOMIC_IOSONLY, readonly) uint32_t componentVersion;

/*!	@method		allocateRenderResourcesAndReturnError:
	@brief		Allocate resources required to render.
	@discussion
		Hosts must call this before beginning to render. Subclassers should call the superclass
		implementation.
		
		Bridged to the v2 API AudioUnitInitialize().
*/
- (BOOL)allocateRenderResourcesAndReturnError:(NSError **)outError;

/*!	@method		deallocateRenderResources
	@brief		Deallocate resources allocated by allocateRenderResourcesAndReturnError:
	@discussion
		Hosts should call this after finishing rendering. Subclassers should call the superclass
		implementation.
		
		Bridged to the v2 API AudioUnitUninitialize().
*/
- (void)deallocateRenderResources;

/*!	@property	renderResourcesAllocated
	@brief		returns YES if the unit has render resources allocated.
 */
@property (NS_NONATOMIC_IOSONLY, readonly) BOOL renderResourcesAllocated;

/*!	@method		reset
	@brief		Reset transitory rendering state to its initial state.
	@discussion
		Hosts should call this at the point of a discontinuity in the input stream being provided to
		an audio unit, for example, when seeking forward or backward within a track. In response,
		implementations should clear delay lines, filters, etc. Subclassers should call the
		superclass implementation.
		
		Bridged to the v2 API AudioUnitReset(), in the global scope.
*/
- (void)reset;

/*!	@property	inputBusses
	@brief		An audio unit's audio input connection points.
	@discussion
		Subclassers must override this property's getter. The implementation should return the same
		object every time it is asked for it, since clients can install KVO observers on it.
*/
@property (NS_NONATOMIC_IOSONLY, readonly) AUAudioUnitBusArray *inputBusses;

/*!	@property	outputBusses
	@brief		An audio unit's audio output connection points.
	@discussion
		Subclassers must override this property's getter. The implementation should return the same
		object every time it is asked for it, since clients can install KVO observers on it.
*/
@property (NS_NONATOMIC_IOSONLY, readonly) AUAudioUnitBusArray *outputBusses;

/*!	@property	renderBlock
	@brief		Block which hosts use to ask the unit to render.
	@discussion
		Before invoking an audio unit's rendering functionality, a host should fetch this block and
		cache the result. The block can then be called from a realtime context without the
		possibility of blocking and causing an overload at the Core Audio HAL level.
		
		This block will call a subclass' internalRenderBlock, providing all realtime events
		scheduled for the current render time interval, bracketed by calls to any render observers.

		Subclassers should override internalRenderBlock, not this property.
		
		Bridged to the v2 API AudioUnitRender().
*/
@property (NS_NONATOMIC_IOSONLY, readonly) AURenderBlock renderBlock;

/*!	@property	scheduleParameterBlock
	@brief		Block which hosts use to schedule parameters.
	@discussion
		As with renderBlock, a host should fetch and cache this block before beginning to render,
		if it intends to schedule parameters.
				
		The block is safe to call from any thread context, including realtime audio render
		threads.
		
		Subclassers should not override this; it is implemented in the base class and will schedule
		the events to be provided to the internalRenderBlock.
		
		Bridged to the v2 API AudioUnitScheduleParameters().
*/
@property (NS_NONATOMIC_IOSONLY, readonly) AUScheduleParameterBlock scheduleParameterBlock;

/*!	@method		tokenByAddingRenderObserver:
	@brief		Add a block to be called on each render cycle.
	@discussion
		The supplied block is called at the beginning and ending of each render cycle. It should
		not make any blocking calls.
		
		This method is implemented in the base class AUAudioUnit, and should not be overridden.
		
		Bridged to the v2 API AudioUnitAddRenderNotify().
	@param observer
		The block to call.
	@return
		A token to be used when removing the observer.
*/
- (NSInteger)tokenByAddingRenderObserver:(AURenderObserver)observer;

/*!	@method		removeRenderObserver:
	@brief		Remove an observer block added via tokenByAddingRenderObserver:
	@param token
		The token previously returned by tokenByAddingRenderObserver:

		Bridged to the v2 API AudioUnitRemoveRenderNotify().
*/
- (void)removeRenderObserver:(NSInteger)token;

/*!	@property	maximumFramesToRender
	@brief		The maximum number of frames which the audio unit can render at once.
	@discussion
		This must be set by the host before render resources are allocated. It cannot be changed
		while render resources are allocated.
		
		Bridged to the v2 property kAudioUnitProperty_MaximumFramesPerSlice.
*/
@property (NS_NONATOMIC_IOSONLY) AUAudioFrameCount maximumFramesToRender;

/*!	@property	parameterTree
	@brief		An audio unit's parameters, organized in a hierarchy.
	@return
		A parameter tree object, or nil if the unit has no parameters.
	@discussion
		Audio unit hosts can fetch this property to discover a unit's parameters. KVO notifications
		are issued on this member to notify the host of changes to the set of available parameters.
		
		AUAudioUnit has an additional pseudo-property, "allParameterValues", on which KVO
		notifications are issued in response to certain events where potentially all parameter
		values are invalidated (e.g. selection of a preset or setting fullState).
 
		Subclassers should implement the parameterTree getter to expose parameters to hosts. They
		should cache as much as possible and send KVO notifications on "parameterTree" when altering
		the structure of the tree or the static information (ranges, etc) of parameters.
		
		This is similar to the v2 properties kAudioUnitProperty_ParameterList and
		kAudioUnitProperty_ParameterInfo.
*/
@property (NS_NONATOMIC_IOSONLY, readonly, nullable) AUParameterTree *parameterTree;

/*!	@method		parametersForOverviewWithCount:
	@brief		Returns the audio unit's `count` most important parameters.
	@discussion
		This property allows a host to query an audio unit for some small number of parameters which
		are its "most important", to be displayed in a compact generic view.

		An audio unit subclass should return an array of NSNumbers representing the addresses
		of the `count` most important parameters.

		The base class returns an empty array regardless of count.
		
		Partially bridged to kAudioUnitProperty_ParametersForOverview (v2 hosts can use that
		property to access this v3 method of an audio unit).
*/
- (NSArray<NSNumber *> *)parametersForOverviewWithCount:(NSInteger)count;

@property (NS_NONATOMIC_IOSONLY, readonly) BOOL allParameterValues;	/// special pseudo-property for KVO

/*!	@property	musicDeviceOrEffect
	@brief		Specifies whether an audio unit responds to MIDI events.
	@discussion
		This is implemented in the base class and returns YES if the component type is music
		device or music effect.
*/
@property (NS_NONATOMIC_IOSONLY, readonly, getter=isMusicDeviceOrEffect) BOOL musicDeviceOrEffect;

/*!	@property	virtualMIDICableCount
	@brief		The number of virtual MIDI cables implemented by a music device or effect.
	@discussion
		A music device or MIDI effect can support up to 256 virtual MIDI cables of input; this
		property expresses the number of cables supported by the audio unit.
*/
@property (NS_NONATOMIC_IOSONLY, readonly) NSInteger virtualMIDICableCount;

/*!	@property	scheduleMIDIEventBlock
	@brief		Block used to schedule MIDI events.
	@discussion
		As with renderBlock, a host should fetch and cache this block before beginning to render,
		if it intends to schedule MIDI events.
		
		This is implemented in the base class. It is nil when musicDeviceOrEffect is NO.
		
		Subclassers should not override. When hosts schedule events via this block, they are
		delivered to the audio unit via the list of AURenderEvents delivered to
		internalRenderBlock.
		
		This bridged to the v2 API MusicDeviceMIDIEvent.
*/
@property (NS_NONATOMIC_IOSONLY, readonly, nullable) AUScheduleMIDIEventBlock scheduleMIDIEventBlock;

// ------------------------
// These properties and methods are generally optional.

/*!	@property	fullState
	@brief		A persistable snapshot of the audio unit's properties and parameters, suitable for
				saving as a user preset.
	@discussion
		Hosts may use this property to save and restore the state of an audio unit being used in a
		user preset or document. The audio unit should not persist transitory properties such as
		stream formats, but should save and restore all parameters and custom properties.
		
		The base class implementation of this property saves the values of all parameters 
		currently in the parameter tree. A subclass which dynamically produces multiple variants
		of the parameter tree needs to be aware that the serialization method does a depth-first
		preorder traversal of the tree.
		
		Bridged to the v2 property kAudioUnitProperty_ClassInfo.
*/
@property (NS_NONATOMIC_IOSONLY, copy, nullable) NSDictionary<NSString *, id> *fullState;

/*!	@property	fullStateForDocument
	@brief		A persistable snapshot of the audio unit's properties and parameters, suitable for
				saving in a user's document.
	@discussion
		This property is distinct from fullState in that some state is suitable for saving in user
		presets, while other state is not. For example, a synthesizer's master tuning setting could
		be considered global state, inappropriate for storing in reusable presets, but desirable
		for storing in a document for a specific live performance.
		
		Hosts saving documents should use this property. If the audio unit does not implement it,
		the base class simply sets/gets fullState.

		Bridged to the v2 property kAudioUnitProperty_ClassInfoFromDocument.
*/
@property (NS_NONATOMIC_IOSONLY, copy, nullable) NSDictionary<NSString *, id> *fullStateForDocument;

/*!	@property	factoryPresets
	@brief		A collection of presets provided by the audio unit's developer.
	@discussion
		A preset provides users of an audio unit with an easily-selectable, fine-tuned set of
		parameters provided by the developer. This property returns all of the available presets.
		
		Bridged to the v2 property kAudioUnitProperty_FactoryPresets.
*/
@property (NS_NONATOMIC_IOSONLY, readonly, copy, nullable) NSArray<AUAudioUnitPreset *> *factoryPresets;

/*!	@property	currentPreset
	@brief		The audio unit's last-selected preset.
	@discussion
		Hosts can let the user select a preset by setting this property. Note that when getting
		this property, it does not reflect whether parameters may have been modified since the
		preset was selected.
		
		Bridged to the v2 property kAudioUnitProperty_PresentPreset.
*/
@property (NS_NONATOMIC_IOSONLY, retain, nullable) AUAudioUnitPreset *currentPreset;

/*!	@property	latency
	@brief		The audio unit's processing latency, in seconds.
	@discussion
		This property reflects the delay between when an impulse in the unit's audio unit stream
		arrives in the input vs. output streams. This should reflect the delay due
		to signal processing (e.g. filters, FFT's, etc.), not delay or reverberation which is
		being applied as an effect.
		
		Note that a latency that varies with parameter settings, including bypass, is generally not
		useful to hosts. A host is usually only prepared to add delays before starting to render and
		those delays need to be fixed. A variable delay would introduce artifacts even if the host
		could track it. If an algorithm has a variable latency it should be adjusted upwards to some
		fixed latency within the audio unit. If for some reason this is not possible, then latency
		could be regarded as an unavoidable consequence of the algorithm and left unreported (i.e.
		with a value of 0).

		Bridged to the v2 property kAudioUnitProperty_Latency.
*/
@property (NS_NONATOMIC_IOSONLY, readonly) NSTimeInterval latency;

/*!	@property	tailTime
	@brief		The audio unit's tail time, in seconds.
	@discussion
		This property reflects the time interval between when the input stream ends or otherwise
		transitions to silence, and when the output stream becomes silent. Unlike latency, this
		should reflect the duration of a delay or reverb effect.
		
		Bridged to the v2 property kAudioUnitProperty_TailTime.
*/
@property (NS_NONATOMIC_IOSONLY, readonly) NSTimeInterval tailTime;

/*!	@property	renderQuality
	@brief		Provides a trade-off between rendering quality and CPU load.
	@discussion
		The range of valid values is 0-127.
		
		Bridged to the v2 property kAudioUnitProperty_RenderQuality.
*/
@property (NS_NONATOMIC_IOSONLY) NSInteger renderQuality;

/*!	@property	shouldBypassEffect
	@brief		Directs an effect to route input directly to output, without any processing.
	@discussion
		Bridged to the v2 property kAudioUnitProperty_BypassEffect.
*/
@property (NS_NONATOMIC_IOSONLY) BOOL shouldBypassEffect;

/*!	@property	canProcessInPlace
	@brief		Expresses whether an audio unit can process in place.
	@discussion
		In-place processing is the ability for an audio unit to transform an input signal to an
		output signal in-place in the input buffer, without requiring a separate output buffer.
		
		A host can express its desire to process in place by using null mData pointers in the output
		buffer list. The audio unit may process in-place in the input buffers. See the discussion of
		renderBlock.
		
		Partially bridged to the v2 property kAudioUnitProperty_InPlaceProcessing; in v3 it is not
		settable.
*/
@property (NS_NONATOMIC_IOSONLY, readonly) BOOL canProcessInPlace;

/*!	@property	renderingOffline
	@brief		Communicates to an audio unit that it is rendering offline.
	@discussion
		A host should use this property when using an audio unit in a context where there are 
		no realtime deadlines. An audio unit may respond by using a more expensive signal
		processing algorithm, or allowing itself to block at render time if data being generated on
		secondary work threads is not ready in time. (Normally, in a realtime thread, this
		data would have to be dropped).

		Bridged to the v2 property kAudioUnitProperty_OfflineRender.
*/
@property (NS_NONATOMIC_IOSONLY, getter=isRenderingOffline) BOOL renderingOffline;

/*!	@property	channelCapabilities
	@brief		Expresses valid combinations of input and output channel counts.
	@discussion
		Elements are NSNumber containing integers; [0]=input count, [1]=output count, [2]=2nd input
		count, [3]=2nd output count, etc.

		An input, output count of (2, 2) signifies that the audio unit can process 2 input channels
		to 2 output channels.
		
		Negative numbers (-1, -2) indicate *any* number of channels. (-1, -1) means any number
		of channels on input and output as long as they are the same. (-1, -2) means any number of
		channels on input or output, without the requirement that the counts are the same.
		
		A negative number less than -2 is used to indicate a total number of channels across every
		bus in that scope, regardless of how many channels are set on any particular bus. For
		example, (-16, 2) indicates that a unit can accept up to 16 channels of input across its
		input busses, but will only produce 2 channels of output.
		
		Zero on either side (though typically input) means "not applicable", because there are no
		elements on that side.

		Bridged to the v2 property kAudioUnitProperty_SupportedNumChannels.
*/
@property (NS_NONATOMIC_IOSONLY, readonly, copy, nullable) NSArray<NSNumber *> *channelCapabilities;

/*!	@property	musicalContextBlock
	@brief		A callback for the AU to call the host for musical context information.
	@discussion
		Note that an audio unit implementation accessing this property should cache it in
		realtime-safe storage before beginning to render.
		
		Bridged to the HostCallback_GetBeatAndTempo and HostCallback_GetMusicalTimeLocation
		callback members in kAudioUnitProperty_HostCallbacks.
*/
@property (NS_NONATOMIC_IOSONLY, copy, nullable) AUHostMusicalContextBlock musicalContextBlock;

/*!	@property	transportStateBlock
	@brief		A callback for the AU to call the host for transport state information.
	@discussion
		Note that an audio unit implementation accessing this property should cache it in
		realtime-safe storage before beginning to render.
		
		Bridged to the HostCallback_GetTransportState and HostCallback_GetTransportState2
		callback members in kAudioUnitProperty_HostCallbacks.
*/
@property (NS_NONATOMIC_IOSONLY, copy, nullable) AUHostTransportStateBlock transportStateBlock;

/*!	@property	contextName
	@brief		Information about the host context in which the audio unit is connected, for display
				in the audio unit's view.
	@discussion
		For example, a host could set "track 3" as the context, so that the audio unit's view could
		then display to the user "My audio unit on track 3".

		Bridged to the v2 property kAudioUnitProperty_ContextName.
*/
@property (NS_NONATOMIC_IOSONLY, copy, nullable) NSString *contextName;

@end

// =================================================================================================

/*!	@typedef	AUInputHandler
	@brief		Block to notify the client of an I/O unit that input is available.
	@param actionFlags
		Pointer to action flags.
	@param timestamp
		The HAL time at which the input data will be rendered. If there is a sample rate conversion
		or time compression/expansion downstream, the sample time will not be valid.
	@param frameCount
		The number of sample frames of input available.
	@param inputBusNumber
		The index of the input bus from which input is available.
	@discussion	The input data is obtained by calling the render block of the audio unit.
				The AUAudioUnit is not provided since it is not safe to message an Objective C object in a real time context.
*/
typedef void (^AUInputHandler)(AudioUnitRenderActionFlags *actionFlags, const AudioTimeStamp *timestamp, AUAudioFrameCount frameCount, NSInteger inputBusNumber);

/*!	@brief		Additional methods for audio units which can do input/output.
	@discussion	These methods will fail if the audio unit is not an input/output audio unit.
*/
@interface AUAudioUnit (AUAudioInputOutputUnit)

/*!	@property	canPerformInput
	@brief		Whether the I/O device can perform input.
*/
@property (nonatomic, readonly) BOOL canPerformInput;

/*!	@property	canPerformOutput
	@brief		Whether the I/O device can perform output.
*/
@property (nonatomic, readonly) BOOL canPerformOutput;

/*!	@property	inputEnabled
	@brief		Flag enabling audio input from the unit.
	@discussion	Input is disabled by default. This must be set to YES if input audio is desired. 
				Setting to YES will have no effect if canPerformInput is false.
*/
@property (nonatomic, getter=isInputEnabled) BOOL inputEnabled;

/*!	@property	outputEnabled
	@brief		Flag enabling audio output from the unit.
	@discussion	Output is enabled by default.
				Setting to YES will have no effect if canPerformOutput is false.
*/
@property (nonatomic, getter=isOutputEnabled) BOOL outputEnabled;

/*!	@property	outputProvider
	@brief		The block that the output unit will call to get audio to send to the output.
	@discussion	This block must be set if output is enabled.
*/
@property (nonatomic, copy, nullable) AURenderPullInputBlock outputProvider;

/*!	@property	inputHandler
	@brief		The block that the output unit will call to notify when input is available.
	@discussion	See discussion for AUInputHandler.
*/
@property (nonatomic, copy, nullable) AUInputHandler inputHandler;

/*!	@property	device
	@brief		Get the I/O hardware device.
*/
@property (nonatomic, readonly) AudioObjectID deviceID;

/*!	@method		setDeviceID:error:
	@brief		Set the I/O hardware device.
	@param deviceID
		The device to select.
	@param outError
		Returned in the event of failure.
*/
- (BOOL)setDeviceID:(AudioObjectID)deviceID error:(NSError **)outError;

/*!	@method		startHardwareAndReturnError:
	@brief		Starts the audio hardware.
	@param outError
		Returned in the event of failure.
*/
- (BOOL)startHardwareAndReturnError:(NSError **)outError;

/*!	@method		stopHardware
	@brief		Stops the audio hardware.
*/
- (void)stopHardware;

@end

// =================================================================================================

/*!	@class	AUAudioUnitBusArray
	@brief	Container for an audio unit's input or output busses.
	@discussion
		Hosts can observe a bus property across all busses by using KVO on this object, without
		having to observe it on each individual bus. (One could add listeners to individual busses,
		but that means one has to observe bus count changes and add/remove listeners in response.
		Also, NSArray's addObserver:toObjectsAtIndexes:forKeyPath:options:context: is problematic;
		it does not let the individual objects override the observation request, and so a bus which
		is proxying a bus in an extension process does not get the message.)

		Some audio units (e.g. mixers) support variable numbers of busses, via subclassing. When the
		bus count changes, a KVO notification is sent on "inputBusses" or "outputBusses," as
		appropriate.

		Subclassers should see also the AUAudioUnitBusImplementation category.
		
		The bus array is bridged to the v2 property kAudioUnitProperty_ElementCount.
*/
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface AUAudioUnitBusArray : NSObject <NSFastEnumeration>

- (instancetype)init NS_UNAVAILABLE;

/*!	@method		initWithAudioUnit:busType:busses:
	@brief		Initializes by making a copy of the supplied bus array.
*/
- (instancetype)initWithAudioUnit:(AUAudioUnit *)owner busType:(AUAudioUnitBusType)busType busses:(NSArray <AUAudioUnitBus *> *)busArray NS_DESIGNATED_INITIALIZER;

/*!	@method		initWithAudioUnit:busType:
	@brief		Initializes an empty bus array.
*/
- (instancetype)initWithAudioUnit:(AUAudioUnit *)owner busType:(AUAudioUnitBusType)busType;

/*!	@property	count
*/
@property (NS_NONATOMIC_IOSONLY, readonly) NSUInteger count;

/*!	@method		objectAtIndexedSubscript:
*/
- (AUAudioUnitBus *)objectAtIndexedSubscript:(NSUInteger)index;

/*!	@property	countChangeable
	@brief		Whether the array can have a variable number of busses.
	@discussion
		The base implementation returns false.
*/
@property (NS_NONATOMIC_IOSONLY, readonly, getter=isCountChangeable) BOOL countChangeable;

/*!	@property	setBusCount:error:
	@brief		Change the number of busses in the array.
*/
- (BOOL)setBusCount:(NSUInteger)count error:(NSError **)outError;

/*!	@method		addObserverToAllBusses:forKeyPath:options:context:
	@brief		Add a KVO observer for a property on all busses in the array.
*/
- (void)addObserverToAllBusses:(NSObject *)observer forKeyPath:(NSString *)keyPath options:(NSKeyValueObservingOptions)options context:(void * __nullable)context;

/*!	@method		removeObserverFromAllBusses:forKeyPath:context:
	@brief		Remove a KVO observer for a property on all busses in the array.
*/
- (void)removeObserverFromAllBusses:(NSObject *)observer forKeyPath:(NSString *)keyPath context:(void * __nullable)context;

/// The audio unit that owns the bus.
@property (NS_NONATOMIC_IOSONLY, readonly, assign) AUAudioUnit *ownerAudioUnit;

/// Which bus array this is (input or output).
@property (NS_NONATOMIC_IOSONLY, readonly) AUAudioUnitBusType busType;

@end

// =================================================================================================

/*!	@class	AUAudioUnitBus
	@brief	An input or output connection point on an audio unit.
*/
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface AUAudioUnitBus : NSObject

/*!	@property	format
	@brief		The audio format and channel layout of audio being transferred on the bus.
	@discussion
		Bridged to the v2 property kAudioUnitProperty_StreamFormat.
*/
@property (NS_NONATOMIC_IOSONLY, readonly) AVAudioFormat *format;

/*!	@property	setFormat:error:
	@brief		Sets the bus's audio format.
	@discussion
		Audio units can generally be expected to support AVAudioFormat's standard format
		(deinterleaved 32-bit float), at any sample rate. Channel counts can be more complex;
		see AUAudioUnit.channelCapabilities.
*/
- (BOOL)setFormat:(AVAudioFormat *)format error:(NSError **)outError;

/*!	@property	enabled
	@brief		Whether the bus is active.
	@discussion
		Hosts must enable input busses before using them. The reason for this is to allow a unit
		such as a mixer to be prepared to render a large number of inputs, but avoid the work
		of preparing to pull inputs which are not in use.
		
		Bridged to the v2 properties kAudioUnitProperty_MakeConnection and
		kAudioUnitProperty_SetRenderCallback.
*/
@property (NS_NONATOMIC_IOSONLY, getter=isEnabled) BOOL enabled;

/*!	@property	name
	@brief		A name for the bus. Can be set by host.
*/
@property (NS_NONATOMIC_IOSONLY, copy, nullable) NSString *name;

/*! @property   index
    @brief      The index of this bus in the containing array.
*/
@property (NS_NONATOMIC_IOSONLY, readonly) NSUInteger index;

/*! @property   busType
    @brief      The AUAudioUnitBusType.
 */
@property (NS_NONATOMIC_IOSONLY, readonly) AUAudioUnitBusType busType;

/*! @property   ownerAudioUnit
 @brief         The audio unit that owns the bus.
 */
@property (NS_NONATOMIC_IOSONLY, readonly, assign) AUAudioUnit *ownerAudioUnit;

/*!	@property	supportedChannelLayoutTags
	@discussion
		This is an array of NSNumbers representing AudioChannelLayoutTag.
*/
@property (NS_NONATOMIC_IOSONLY, readonly, copy, nullable) NSArray<NSNumber *> *supportedChannelLayoutTags;

/*!	@property	contextPresentationLatency
	@brief		Information about latency in the audio unit's processing context.
	@discussion
		This should not be confused with the audio unit's latency property, where the audio unit
		describes to the host any processing latency it introduces between its input and its output.
		
		A host may set this property to describe to the audio unit the presentation latency of its
		input and/or output audio data. Latency is described in seconds. A value of zero means
		either no latency or an unknown latency.
		
		A host should set this property on each active bus, since, for example, the audio routing
		path to each of multiple output busses may differ.
		
		For input busses:
			Describes how long ago the audio arriving on this bus was acquired. For instance, when
			reading from a file to the first audio unit in a chain, the input presentation latency
			is zero. For audio input from a device, this initial input latency is the presentation
			latency of the device itself, i.e. the device's safety offset and latency.
			
			A second chained audio unit's input presentation latency will be the input presentation
			latency of the first unit, plus the processing latency of the first unit.
			
		For output busses:
			Describes how long it will be before the output audio of an audio unit is presented. For
			instance, when writing to a file, the output presentation latency of the last audio unit
			in a chain is zero. When the audio from that audio unit is to be played to a device,
			then that initial presentation latency will be the presentation latency of the device
			itself, which is the I/O buffer size, plus the device's safety offset and latency
			
			A previous chained audio unit's output presentation latency is the last unit's
			presentation latency plus its processing latency.
			
		So, for a given audio unit anywhere within a mixing graph, the input and output presentation 
		latencies describe to that unit how long from the moment of generation it has taken for its 
		input to arrive, and how long it will take for its output to be presented.
		
		Bridged to the v2 property kAudioUnitProperty_PresentationLatency.
*/
@property (NS_NONATOMIC_IOSONLY) NSTimeInterval contextPresentationLatency;

@end

// =================================================================================================

/*!	@class	AUAudioUnitPreset
	@brief	A collection of parameter settings provided by the audio unit implementor, producing a
			useful sound or starting point.
*/
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface AUAudioUnitPreset : NSObject <NSSecureCoding>

/*!	@property	number
	@brief		The preset's unique numeric identifier.
*/
@property (NS_NONATOMIC_IOSONLY) NSInteger number;

/*!	@property	name
	@brief		The preset's name.
*/
@property (NS_NONATOMIC_IOSONLY, copy) NSString *name;
@end



NS_ASSUME_NONNULL_END

#endif // __OBJC2__
