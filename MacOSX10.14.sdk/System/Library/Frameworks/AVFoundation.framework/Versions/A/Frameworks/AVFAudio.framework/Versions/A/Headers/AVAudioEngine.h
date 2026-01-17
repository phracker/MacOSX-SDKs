/*
	File:		AVAudioEngine.h
	Framework:	AVFoundation
	
	Copyright (c) 2014-2015 Apple Inc. All Rights Reserved.
*/

#import <AVFAudio/AVAudioTypes.h>
#import <AVFAudio/AVAudioBuffer.h>
#import <AVFAudio/AVAudioConnectionPoint.h>
#import <AVFAudio/AVAudioIONode.h>
#import <AVFAudio/AVAudioTime.h>

#if __has_include(<AudioToolbox/MusicPlayer.h>)
#define AVAUDIOENGINE_HAVE_MUSICPLAYER 1
#import <AudioToolbox/MusicPlayer.h>
#endif

#if __has_include(<AudioToolbox/AUAudioUnit.h>) && __OBJC2__
#define AVAUDIOENGINE_HAVE_AUAUDIOUNIT 1
#import <AudioToolbox/AUAudioUnit.h>
#endif

NS_ASSUME_NONNULL_BEGIN

@class AVAudioFormat, AVAudioNode, AVAudioInputNode, AVAudioOutputNode, AVAudioMixerNode;

/*! @enum AVAudioEngineManualRenderingError
    @abstract 
		Error codes that could be returned from AVAudioEngine manual rendering mode methods,
		e.g. `enableManualRenderingMode:format:maximumFrameCount:error:` and
		`renderOffline:toBuffer:error:`.
		Note that this is not a comprehensive list, and the underlying audio units could
		return other error codes (e.g. see kAudioUnitErr_* in AudioToolbox/AUComponent.h) from these
		methods as applicable.
 
		AVAudioEngineManualRenderingErrorInvalidMode
			The operation cannot be performed because the engine is either not in manual 
			rendering mode or the right variant of it.

		AVAudioEngineManualRenderingErrorInitialized
			The operation cannot be performed because the engine is initialized (i.e. not stopped).

 		AVAudioEngineManualRenderingErrorNotRunning
			The operation cannot be performed because the engine is not running (i.e. not started).
*/
typedef NS_ENUM(OSStatus, AVAudioEngineManualRenderingError) {
	AVAudioEngineManualRenderingErrorInvalidMode = -80800,
	AVAudioEngineManualRenderingErrorInitialized = -80801,
	AVAudioEngineManualRenderingErrorNotRunning  = -80802
} API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));

/*! @enum AVAudioEngineManualRenderingStatus
    @abstract 
		Status codes returned from the render call to the engine operating in manual rendering mode.
 
		AVAudioEngineManualRenderingStatusError
			An error occurred when rendering and no data was returned. See the returned error code
			for the description of the error.
 
		AVAudioEngineManualRenderingStatusSuccess
			All of the requested data was returned successfully.

		AVAudioEngineManualRenderingStatusInsufficientDataFromInputNode
			Applicable only to the input node, when it provides input data for rendering
			(see `AVAudioInputNode(setManualRenderingInputPCMFormat:inputBlock:)`).
			Indicates that not enough input data was returned by the input node to satisfy the
			render request at the current time. The output buffer may contain data rendered by other
			active sources in the engine's processing graph.
 
 		AVAudioEngineManualRenderingStatusCannotDoInCurrentContext
			The operation could not be performed now, but the client could retry later if needed.
			This is usually to guard a realtime render operation (e.g. rendering through
			`manualRenderingBlock`) when a reconfiguration of the engine's internal state 
			is in progress.
*/
typedef NS_ENUM(NSInteger, AVAudioEngineManualRenderingStatus) {
	AVAudioEngineManualRenderingStatusError = -1,
	AVAudioEngineManualRenderingStatusSuccess = 0,
	AVAudioEngineManualRenderingStatusInsufficientDataFromInputNode = 1,
	AVAudioEngineManualRenderingStatusCannotDoInCurrentContext = 2
} API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));

/*! @enum AVAudioEngineManualRenderingMode
    @abstract 
		By default, the engine is connected to an audio device and automatically renders in realtime. 
		It can also be configured to operate in manual rendering mode, i.e. not connected to an 
		audio device and rendering in response to requests from the client.
 
		AVAudioEngineManualRenderingModeOffline
			The engine operates in an offline mode without any realtime constraints.
 
		AVAudioEngineManualRenderingModeRealtime
			The engine operates under realtime constraints, i.e. it will not make any blocking call 
			(e.g. calling libdispatch, blocking on a mutex, allocating memory etc.) while rendering.
			Note that only the block based render mechanism can be used in this mode
			(see `AVAudioEngine(manualRenderingBlock)`.
*/
typedef NS_ENUM(NSInteger, AVAudioEngineManualRenderingMode) {
	AVAudioEngineManualRenderingModeOffline = 0,
	AVAudioEngineManualRenderingModeRealtime = 1
} API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));

/*!	@typedef AVAudioEngineManualRenderingBlock
	@abstract 
		Block to render the engine when operating in manual rendering mode
	@param numberOfFrames
		The number of PCM sample frames to be rendered
	@param outBuffer
		The PCM buffer to which the engine must render the audio. 
		The buffer pointers (outBuffer->mBuffers[x].mData) may be null on entry, in which case
		the block will render into a memory it owns and modify the mData pointers to point to that
		memory. The block is responsible for preserving the validity of that memory until it is next
		called to render, or `AVAudioEngine(stop)` is called.
	@param outError
		On exit, if an error occurs during rendering, a description of the error (see
		`AVAudioEngineManualRenderingError` for the possible errors)
	@return
		One of the status codes from `AVAudioEngineManualRenderingStatus`. Irrespective of the
		returned status code, on exit, the output buffer's mDataByteSize 
		(outBuffer->mBuffers[x].mDataByteSize) will indicate the number of PCM data bytes rendered by
		the engine.
 	@discussion
		Use this if you want to render the engine from a realtime context when it is operating in
		the manual rendering mode. See `AVAudioEngine(manualRenderingBlock)` for details.
*/
typedef AVAudioEngineManualRenderingStatus (^AVAudioEngineManualRenderingBlock)(AVAudioFrameCount numberOfFrames, AudioBufferList *outBuffer, OSStatus * __nullable outError) API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));

/*!
	@class AVAudioEngine
	@discussion
		An AVAudioEngine contains a group of connected AVAudioNodes ("nodes"), each of which performs
		an audio signal generation, processing, or input/output task.
		
		Nodes are created separately and attached to the engine.

		The engine supports dynamic connection, disconnection and removal of nodes while running,
		with only minor limitations:
		- all dynamic reconnections must occur upstream of a mixer
		- while removals of effects will normally result in the automatic connection of the adjacent
			nodes, removal of a node which has differing input vs. output channel counts, or which
			is a mixer, is likely to result in a broken graph.
 
		By default, the engine is connected to an audio device and automatically renders in realtime. 
		It can also be configured to operate in manual rendering mode, i.e. not connected to an
		audio device and rendering in response to requests from the client, normally at or
		faster than realtime rate.
*/
OS_EXPORT API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0))
@interface AVAudioEngine : NSObject {
@private
	void *_impl;
}

/*! @method init
	@abstract
		Initialize a new engine.
	@discussion
		On creation, the engine is by default connected to an audio device and automatically renders 
		in realtime. It can be configured to operate in manual rendering mode through 
		`enableManualRenderingMode:format:maximumFrameCount:error:`.
*/
- (instancetype)init;

/*!	@method attachNode:
	@abstract
		Take ownership of a new node.
	@param node
		The node to be attached to the engine.
	@discussion
		To support the instantiation of arbitrary AVAudioNode subclasses, instances are created
		externally to the engine, but are not usable until they are attached to the engine via
		this method. Thus the idiom, without ARC, is:

<pre>
// when building engine:
AVAudioNode *_player;	// member of controller class (for example)
...
_player = [[AVAudioPlayerNode alloc] init];
[engine attachNode: _player];
...
// when destroying engine (without ARC)
[_player release];
</pre>
*/
- (void)attachNode:(AVAudioNode *)node;

/*!	@method detachNode:
	@abstract
		Detach a node previously attached to the engine.
	@discussion
		If necessary, the engine will safely disconnect the node before detaching it.
*/
- (void)detachNode:(AVAudioNode *)node;

/*! @method connect:to:fromBus:toBus:format:
	@abstract
		Establish a connection between two nodes.
	@param node1 
		The source node
	@param node2 
		The destination node
	@param bus1 
		The output bus on the source node
	@param bus2 
		The input bus on the destination node
	@param format 
		If non-nil, the format of the source node's output bus is set to this
		format. In all cases, the format of the destination node's input bus is set to
		match that of the source node's output bus.
	@discussion
		Nodes have input and output buses (AVAudioNodeBus). Use this method to establish
		one-to-one connections betweeen nodes. Connections made using this method are always
		one-to-one, never one-to-many or many-to-one.
	
		Note that any pre-existing connection(s) involving the source's output bus or the
		destination's input bus will be broken.
*/
- (void)connect:(AVAudioNode *)node1 to:(AVAudioNode *)node2 fromBus:(AVAudioNodeBus)bus1 toBus:(AVAudioNodeBus)bus2 format:(AVAudioFormat * __nullable)format;

/*!	@method connect:to:format:
	@abstract
		Establish a connection between two nodes
	@discussion
		This calls connect:to:fromBus:toBus:format: using bus 0 on the source node,
		and bus 0 on the destination node, except in the case of a destination which is a mixer,
		in which case the destination is the mixer's nextAvailableInputBus.
*/
- (void)connect:(AVAudioNode *)node1 to:(AVAudioNode *)node2 format:(AVAudioFormat * __nullable)format;

/*! @method connect:toConnectionPoints:fromBus:format:
	@abstract
		Establish connections between a source node and multiple destination nodes.
	@param sourceNode 
		The source node
	@param destNodes 
		An array of AVAudioConnectionPoint objects specifying destination
		nodes and busses
	@param sourceBus 
		The output bus on source node
	@param format 
		If non-nil, the format of the source node's output bus is set to this
		format. In all cases, the format of the destination nodes' input bus is set to
		match that of the source node's output bus
	@discussion
		Use this method to establish connections from a source node to multiple destination nodes.
		Connections made using this method are either one-to-one (when a single destination
		connection is specified) or one-to-many (when multiple connections are specified), but 
		never many-to-one.

		To incrementally add a new connection to a source node, use this method with an array
		of AVAudioConnectionPoint objects comprising of pre-existing connections (obtained from
		`outputConnectionPointsForNode:outputBus:`) and the new connection.
 
		Note that any pre-existing connection involving the destination's input bus will be 
		broken. And, any pre-existing connection on source node which is not a part of the
		specified destination connection array will also be broken.

		Also note that when the output of a node is split into multiple paths, all the paths
		must render at the same rate until they reach a common mixer.
		In other words, starting from the split node until the common mixer node where all split 
		paths terminate, you cannot have:
			- any AVAudioUnitTimeEffect
			- any sample rate conversion
*/
- (void)connect:(AVAudioNode *)sourceNode toConnectionPoints:(NSArray<AVAudioConnectionPoint *> *)destNodes fromBus:(AVAudioNodeBus)sourceBus format:(AVAudioFormat * __nullable)format API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0));

/*! @method disconnectNodeInput:bus:
	@abstract
		Remove a connection between two nodes.
	@param node 
		The node whose input is to be disconnected
	@param bus 
		The destination's input bus to disconnect
*/
- (void)disconnectNodeInput:(AVAudioNode *)node bus:(AVAudioNodeBus)bus;

/*!	@method disconnectNodeInput:
	@abstract
		Remove a connection between two nodes.
	@param node 
		The node whose inputs are to be disconnected
	@discussion
		Connections are broken on each of the node's input busses.
*/
- (void)disconnectNodeInput:(AVAudioNode *)node;

/*! @method disconnectNodeOutput:bus:
	@abstract
		Remove a connection between two nodes.
	@param node 
		The node whose output is to be disconnected
	@param bus 
		The source's output bus to disconnect
*/
- (void)disconnectNodeOutput:(AVAudioNode *)node bus:(AVAudioNodeBus)bus;

/*!	@method disconnectNodeOutput:
	@abstract
		Remove a connection between two nodes.
	@param node 
		The node whose outputs are to be disconnected
	@discussion
		Connections are broken on each of the node's output busses.
*/
- (void)disconnectNodeOutput:(AVAudioNode *)node;

/*!	@method prepare
	@abstract
		Prepare the engine for starting.
	@discussion
		This method preallocates many of the resources the engine requires in order to start.
		It can be used to be able to start more responsively.
*/
- (void)prepare;

/*! @method startAndReturnError:
	@abstract
		Start the engine.
	@return
		YES for success
	@discussion
		Calls prepare if it has not already been called since stop.
	
		When the engine is rendering to/from an audio device, starts the audio hardware via the
		AVAudioInputNode and/or AVAudioOutputNode instances in the engine. Audio begins to flow 
		through the engine.
		Reasons for potential failure to start in this mode include:
		1. There is problem in the structure of the graph. Input can't be routed to output or to a
			recording tap through converter type nodes.
		2. An AVAudioSession error.
		3. The driver failed to start the hardware.
 
		In manual rendering mode, prepares the engine to render when requested by the client.
*/
- (BOOL)startAndReturnError:(NSError **)outError;

/*!	@method pause
	@abstract
		Pause the engine.
	@discussion
		When the engine is rendering to/from an audio device, stops the audio hardware and the flow
		of audio through the engine. When operating in this mode, it is recommended that the engine
		be paused or stopped (as applicable) when not in use, to minimize power consumption.

		Pausing the engine does not deallocate the resources allocated by prepare. Resume the
		engine by invoking start again.
*/
- (void)pause;

/*!	@method reset
	@abstract reset
		Reset all of the nodes in the engine.
	@discussion
		This will reset all of the nodes in the engine. This is useful, for example, for silencing
		reverb and delay tails.
 
		In manual rendering mode, the render timeline is reset to a sample time of zero.
*/
- (void)reset;

/*! @method stop
	@abstract
		When the engine is rendering to/from an audio device, stops the audio hardware and the
		engine. When operating in this mode, it is recommended that the engine be paused or stopped
		 (as applicable) when not in use, to minimize power consumption.
 
		Stopping the engine releases the resources allocated by prepare.
*/
- (void)stop;

/*! @method inputConnectionPointForNode:inputBus:
	@abstract 
		Get connection information on a node's input bus.
	@param node 
		The node whose input connection is being queried.
	@param bus 
		The node's input bus on which the connection is being queried.
	@return	
		An AVAudioConnectionPoint object with connection information on the node's
		specified input bus.
	@discussion
		Connections are always one-to-one or one-to-many, never many-to-one.
 
		Returns nil if there is no connection on the node's specified input bus.
*/
- (AVAudioConnectionPoint * __nullable)inputConnectionPointForNode:(AVAudioNode *)node inputBus:(AVAudioNodeBus)bus API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0));

/*! @method outputConnectionPointsForNode:outputBus:
	@abstract
		Get connection information on a node's output bus.
	@param node 
		The node whose output connections are being queried.
	@param bus 
		The node's output bus on which connections are being queried.
	@return
		An array of AVAudioConnectionPoint objects with connection information on the node's
		specified output bus.
	@discussion
		Connections are always one-to-one or one-to-many, never many-to-one.
 
		Returns an empty array if there are no connections on the node's specified output bus.
*/
- (NSArray<AVAudioConnectionPoint *> *)outputConnectionPointsForNode:(AVAudioNode *)node outputBus:(AVAudioNodeBus)bus API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0));

#if AVAUDIOENGINE_HAVE_MUSICPLAYER
/*! @property musicSequence
	@abstract
		The MusicSequence previously attached to the engine (if any).
 */
@property (nonatomic, nullable) MusicSequence musicSequence;
#endif

/*! @property outputNode
	@abstract
		The engine's singleton output node.
	@discussion
		Audio output is performed via an output node. The engine creates a singleton on demand when
		this property is first accessed. Connect another node to the input of the output node, or
		obtain a mixer that is connected there by default, using the "mainMixerNode" property.
 
		When the engine is rendering to/from an audio device, the AVAudioSesssion category and/or
		availability of hardware determine whether an app can perform output. Check the output
		format of output node (i.e. hardware format) for non-zero sample rate and channel count to
		see if output is enabled. 
		Trying to perform output through the output node when it is not enabled or available will 
		cause the engine to throw an error (when possible) or an exception.
 
		In manual rendering mode, the output format of the output node will determine the
		render format of the engine. It can be changed through
		`enableManualRenderingMode:format:maximumFrameCount:error:`.
*/
@property (readonly, nonatomic) AVAudioOutputNode *outputNode;

/*! @property inputNode
	@abstract
		The engine's singleton input node.
	@discussion
		Audio input is performed via an input node. The engine creates a singleton on demand when
		this property is first accessed. To receive input, connect another node from the output of 
		the input node, or create a recording tap on it.
 
		When the engine is rendering to/from an audio device, the AVAudioSesssion category and/or
		availability of hardware determine whether an app can perform input (e.g. input hardware is
		not available on tvos). Check for the input node's input format (i.e. hardware format) for
		non-zero sample rate and channel count to see if input is enabled.
		Trying to perform input through the input node when it is not enabled or available will 
		cause the engine to throw an error (when possible) or an exception.

		In manual rendering mode, the input node can be used to synchronously supply data to
		the engine while it is rendering (see 
		`AVAudioInputNode(setManualRenderingInputPCMFormat:inputBlock:)`.
*/
@property (readonly, nonatomic) AVAudioInputNode *inputNode  API_AVAILABLE(macos(10.10), ios(8.0), watchos(4.0), tvos(11.0));


/*! @property mainMixerNode
	@abstract
		The engine's optional singleton main mixer node.
	@discussion
		The engine will construct a singleton main mixer and connect it to the outputNode on demand,
		when this property is first accessed. You can then connect additional nodes to the mixer.
		
		By default, the mixer's output format (sample rate and channel count) will track the format 
		of the output node. You may however make the connection explicitly with a different format.
*/
@property (readonly, nonatomic) AVAudioMixerNode *mainMixerNode;

/*! @property running
	@abstract
		The engine's running state.
*/
@property (readonly, nonatomic, getter=isRunning) BOOL running;

/*! @property autoShutdownEnabled
	@abstract
		When auto shutdown is enabled, the engine can start and stop the audio hardware dynamically,
		to conserve power. This is the enforced behavior on watchOS and can be optionally enabled on
		other platforms.
	@discussion
		To conserve power, it is advised that the client pause/stop the engine when not in use.
		But when auto shutdown is enabled, the engine will stop the audio hardware if it was running 
		idle for a certain duration, and restart it later when required.
		Note that, because this operation is dynamic, it may affect the start times of the source 
		nodes (e.g. `AVAudioPlayerNode`), if the engine has to resume from its shutdown state.
 
		On watchOS, auto shutdown is always enabled. On other platforms, it is disabled by
		default, but the client can enable it if needed.
 
		This property is applicable only when the engine is rendering to/from an audio device. If
		the value is changed when the engine is in manual rendering mode, it will take effect
		whenever the engine is switched to render to/from the audio device.
*/
@property (nonatomic, getter=isAutoShutdownEnabled) BOOL autoShutdownEnabled API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0)) API_UNAVAILABLE(watchos);

#pragma mark -
#pragma mark Manual Rendering Mode

/*!	@method enableManualRenderingMode:format:maximumFrameCount:error:
	@abstract
		Set the engine to operate in manual rendering mode with the specified render format and
		maximum frame count.
	@param format
		The format of the output PCM audio data from the engine
	@param maximumFrameCount
		The maximum number of PCM sample frames the engine will be asked to produce in any single
		render call
 	@param outError
		On exit, if the engine cannot switch to the manual rendering mode, a description of the
		error (see `AVAudioEngineManualRenderingError` for the possible errors)
	@return
		YES for success
	@discussion
		Use this method to configure the engine to render in response to requests from the client.
 
		The engine must be in a stopped state before calling this method.
		The render format must be a PCM format and match the format of the buffer to which
		the engine is asked to render (see `renderOffline:toBuffer:error:`).
 
		The input data in manual rendering mode can be supplied through the source nodes, e.g.
		`AVAudioPlayerNode`, `AVAudioInputNode` etc.
 
 		When switching to manual rendering mode, the engine:
		1. Switches the input and output nodes to manual rendering mode. Their input and output
		   formats may change.
		2. Removes any taps previously installed on the input and output nodes.
		3. Maintains all the engine connections as is.

		Reasons for potential failure when switching to manual rendering mode include:
		- Engine is not in a stopped state.
*/
- (BOOL)enableManualRenderingMode:(AVAudioEngineManualRenderingMode)mode format:(AVAudioFormat *)pcmFormat maximumFrameCount:(AVAudioFrameCount)maximumFrameCount error:(NSError **)outError API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));

/*!	@method disableManualRenderingMode
	@abstract
		Set the engine to render to/from an audio device.
	@discussion
 		When disabling the manual rendering mode, the engine:
		1. Stops and resets itself (see `stop` and `reset`).
		2. Switches the output/input nodes to render to/from an audio device. Their input and
		   output formats may change.
		3. Removes any taps previously installed on the input and output nodes.
		4. Maintains all the engine connections as is.
 
		Calling this method when the engine is already rendering to/from an audio device has no 
		effect.
*/
- (void)disableManualRenderingMode API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));

/*!	@method renderOffline:toBuffer:error:
	@abstract
		Render call to the engine operating in the offline manual rendering mode
	@param numberOfFrames
		The number of PCM sample frames to be rendered
	@param buffer
		The PCM buffer to which the engine must render the audio
	@param outError
		On exit, if an error occurs during rendering, a description of the error (see
		`AVAudioEngineManualRenderingError` for the possible errors)
	@return
		One of the status codes from `AVAudioEngineManualRenderingStatus`. Irrespective of the
		returned status code, on exit, the output buffer's frameLength will indicate the number of
		PCM samples rendered by the engine
	@discussion
		The engine must be in the offline manual rendering mode 
		(`AVAudioEngineManualRenderingModeOffline`) and started before calling this method.
 
		The format of the buffer must match the render format set through 
		`enableManualRenderingMode:format:maximumFrameCount:error:`. The buffer capacity must be
		greater than or equal to the number of samples asked to render.
		On exit, the buffer's frameLength will indicate the number of PCM samples rendered by the 
		engine.
 
 		The engine's timeline in manual rendering mode starts at a sample time of zero, and is in
		terms of the render format's sample rate. Resetting the engine (see `reset`) will reset the
		timeline back to zero.
 
 		When rendering in `AVAudioEngineManualRenderingModeRealtime`, this ObjC render method 
		must not be used, an error is returned otherwise. Use the block based render call
		(`manualRenderingBlock`) in that mode instead.
*/
- (AVAudioEngineManualRenderingStatus)renderOffline:(AVAudioFrameCount)numberOfFrames toBuffer:(AVAudioPCMBuffer *)buffer error:(NSError **)outError API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0)) __attribute__((swift_error(nonnull_error)));

/*!	@property manualRenderingBlock
	@abstract
		Block to render the engine operating in manual rendering mode
	@discussion
		This block based render call must be used to render the engine when operating in
		`AVAudioEngineManualRenderingModeRealtime`. In this mode, the engine operates under
		realtime constraints and will not make any blocking call (e.g. calling libdispatch, blocking 
		on a mutex, allocating memory etc.) while rendering. 
 
		Before invoking the rendering functionality, client must fetch this block and cache the
		result. The block can then be called from a realtime context, without any possibility of 
		blocking.
 
		When rendering in `AVAudioEngineManualRenderingModeOffline`, either this block based render
		call or	`renderOffline:toBuffer:error:` ObjC method can be used.
		All the rules outlined in `renderOffline:toBuffer:error:` are applicable here as well.
*/
@property (readonly, nonatomic) AVAudioEngineManualRenderingBlock manualRenderingBlock API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));

/*! @property isInManualRenderingMode
	@abstract
		Whether or not the engine is operating in manual rendering mode, i.e. not connected
		to an audio device and rendering in response to the requests from the client
*/
@property (readonly, nonatomic) BOOL isInManualRenderingMode API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));

/*! @property manualRenderingMode
	@abstract
		The manual rendering mode configured on the engine
	@discussion
		This property is meaningful only when the engine is operating in manual rendering mode,
		i.e. when `isInManualRenderingMode` returns true.
*/
@property (readonly, nonatomic) AVAudioEngineManualRenderingMode manualRenderingMode API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));

/*! @property manualRenderingFormat
	@abstract
		The render format of the engine in manual rendering mode.
	@discussion
		Querying this property when the engine is not in manual rendering mode will return an
		invalid format, with zero sample rate and channel count.
*/
@property (readonly, nonatomic) AVAudioFormat *manualRenderingFormat API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));

/*! @property manualRenderingMaximumFrameCount
	@abstract
		The maximum number of PCM sample frames the engine can produce in any single render call in 
		the manual rendering mode.
	@discussion
		Querying this property when the engine is not in manual rendering mode will return zero.
*/
@property (readonly, nonatomic) AVAudioFrameCount manualRenderingMaximumFrameCount API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));

/*! @property manualRenderingSampleTime
	@abstract
		Indicates where the engine is on its render timeline in manual rendering mode.
	@discussion
		The timeline in manual rendering mode starts at a sample time of zero, and is in terms
		of the render format's sample rate. Resetting the engine (see `reset`) will reset the
		timeline back to zero.
*/
@property (readonly, nonatomic) AVAudioFramePosition manualRenderingSampleTime API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));

#if AVAUDIOENGINE_HAVE_AUAUDIOUNIT
/*! @method connectMIDI:to:format:block:
    @abstract
        Establish a MIDI only connection between two nodes.
    @param sourceNode
        The source node.
    @param destinationNode
        The destination node.
    @param format
        If non-nil, the format of the source node's output bus is set to this format.
        In all cases, the format of the source nodes' output bus has to match with the
        destination nodes' output bus format.
        Although the output bus of the source is not in use, the format needs to be set
        in order to be able to use the sample rate for MIDI event timing calculations.
    @param tapBlock
        If non-nil, this block is called from the source node's `AUMIDIOutputEventBlock`
        on the realtime thread. The host can tap the MIDI data of the source node through
        this block. May be nil.
    @discussion
        Use this method to establish a MIDI only connection between a source node and a
        destination node that has MIDI input capability.

        The source node can only be a AVAudioUnit node of type `kAudioUnitType_MIDIProcessor`.
        The destination node types can be `kAudioUnitType_MusicDevice`,
        `kAudioUnitType_MusicEffect` or `kAudioUnitType_MIDIProcessor`.

        Note that any pre-existing MIDI connection involving the destination will be broken.

        Any client installed block on the source node's audio unit `AUMIDIOutputEventBlock`
        will be overwritten when making the MIDI connection.
 */
- (void)connectMIDI:(AVAudioNode *)sourceNode to:(AVAudioNode *)destinationNode format:(AVAudioFormat * __nullable)format block:(AUMIDIOutputEventBlock __nullable)tapBlock API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));

/*! @method connectMIDI:toNodes:format:block:
    @abstract
        Establish a MIDI only connection between a source node and multiple destination nodes.
    @param sourceNode
        The source node.
    @param destinationNodes
        An array of AVAudioNodes specifying destination nodes.
    @param format
        If non-nil, the format of the source node's output bus is set to this format.
        In all cases, the format of the source nodes' output bus has to match with the
        destination nodes' output bus format.
        Although the output bus of the source is not in use, the format needs to be set
        in order to be able to use the sample rate for MIDI event timing calculations.
    @param tapBlock
        If non-nil, this block is called from the source node's `AUMIDIOutputEventBlock`
        on the realtime thread. The host can tap the MIDI data of the source node through
        this block. May be nil.
    @discussion
        Use this method to establish a MIDI only connection between a source node and
        multiple destination nodes.

        The source node can only be a AVAudioUnit node of type `kAudioUnitType_MIDIProcessor`.
        The destination node types can be `kAudioUnitType_MusicDevice`,
        `kAudioUnitType_MusicEffect` or `kAudioUnitType_MIDIProcessor`.

        MIDI connections made using this method are either one-to-one (when a single
        destination connection is specified) or one-to-many (when multiple connections are
        specified), but never many-to-one.

        Note that any pre-existing connection involving the destination will be broken.

        Any client installed block on the source node's audio unit `AUMIDIOutputEventBlock`
        will be overwritten when making the MIDI connection.
 */
- (void)connectMIDI:(AVAudioNode *)sourceNode toNodes:(NSArray<AVAudioNode *> *)destinationNodes format:(AVAudioFormat * __nullable)format block:(AUMIDIOutputEventBlock __nullable)tapBlock API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));

/*! @method disconnectMIDI:from:
    @abstract
        Remove a MIDI connection between two nodes.
    @param sourceNode
        The node whose MIDI output is to be disconnected.
    @param destinationNode
        The node whose MIDI input is to be disconnected.
    @discussion
        If a tap block is installed on the source node, it will be removed when the last
        connection from the source node is removed.
 */
- (void)disconnectMIDI:(AVAudioNode *)sourceNode from:(AVAudioNode *)destinationNode API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));

/*! @method disconnectMIDI:fromNodes:
    @abstract
        Remove a MIDI connection between one source node and multiple destination nodes.
    @param sourceNode
        The node whose MIDI output is to be disconnected.
    @param destinationNodes
        An array of AVAudioNodes specifying nodes whose MIDI input is to be disconnected.
    @discussion
        If a tap block is installed on the source node, it will be removed when the last
        connection from the source node is removed.
 */
- (void)disconnectMIDI:(AVAudioNode *)sourceNode fromNodes:(NSArray<AVAudioNode *> *)destinationNodes API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));

/*! @method disconnectMIDIInput:
    @abstract
        Disconnects all input MIDI connections of this node.
    @param node
        The node whose MIDI input is to be disconnected.
*/
- (void)disconnectMIDIInput:(AVAudioNode *)node API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));

/*! @method disconnectMIDIOutput:
    @abstract
        Disconnects all output MIDI connections of this node.
    @param node
        The node whose MIDI outputs are to be disconnected.
*/
- (void)disconnectMIDIOutput:(AVAudioNode *)node API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));

#endif // AVAUDIOENGINE_HAVE_AUAUDIOUNIT

@end // AVAudioEngine

/*!	@constant AVAudioEngineConfigurationChangeNotification
	@abstract
		A notification generated on engine configuration changes when rendering to/from an audio
		device.
	@discussion
		Register for this notification on your engine instances, as follows:
		
		[[NSNotificationCenter defaultCenter] addObserver: myObject 
			 selector:    @selector(handleInterruption:)
			 name:        AVAudioEngineConfigurationChangeNotification
			 object:      engine];

		When the engine's I/O unit observes a change to the audio input or output hardware's
		channel count or sample rate, the engine stops itself (see `AVAudioEngine(stop)`), and
		issues this notification.
		The nodes remain attached and connected with previously set formats. However, the app 
		must reestablish connections if the connection formats need to change (e.g. in an 
		input node chain, connections must follow the hardware sample rate, while in an output only
		chain, the output node supports rate conversion).
 
		Note that the engine must not be deallocated from within the client's notification handler
		because the callback happens on an internal dispatch queue and can deadlock while trying to 
		synchronously teardown the engine.
*/
AVF_EXPORT
NSString *const AVAudioEngineConfigurationChangeNotification API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0));

NS_ASSUME_NONNULL_END
