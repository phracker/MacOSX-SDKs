/*
	File:		AVAudioEngine.h
	Framework:	AVFoundation
	
	Copyright (c) 2014 Apple Inc. All Rights Reserved.
*/

#import <AVFoundation/AVAudioTypes.h>
#import <AudioToolbox/MusicPlayer.h>

@class AVAudioFormat, AVAudioNode, AVAudioInputNode, AVAudioOutputNode, AVAudioMixerNode;

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
*/
NS_CLASS_AVAILABLE(10_10, 8_0)
@interface AVAudioEngine : NSObject {
@private
	void *_impl;
}

/*! @method init
	@abstract
		Initialize a new engine.
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
	@param node1 the source node
	@param node2 the destination node
	@param bus1 the output bus on the source node
	@param bus2 the input bus on the destination node
	@param format if non-null, the format of the source node's output bus is set to this
		format. In all cases, the format of the destination node's input bus is set to
		match that of the source node's output bus.
	@discussion
		Nodes have input and output buses (AVAudioNodeBus). Use this method to establish
		connections betweeen nodes. Connections are always one-to-one, never one-to-many or
		many-to-one.
	
		Note that any pre-existing connection(s) involving the source's output bus or the
		destination's input bus will be broken.
*/
- (void)connect:(AVAudioNode *)node1 to:(AVAudioNode *)node2 fromBus:(AVAudioNodeBus)bus1 toBus:(AVAudioNodeBus)bus2 format:(AVAudioFormat *)format;

/*!	@method connect:to:format:
	@abstract
		Establish a connection between two nodes
	@discussion
		This calls connect:to:fromBus:toBus:format:error: using bus 0 on the source node,
		and bus 0 on the destination node, except in the case of a destination which is a mixer,
		in which case the destination is the mixer's nextAvailableInputBus.
*/
- (void)connect:(AVAudioNode *)node1 to:(AVAudioNode *)node2 format:(AVAudioFormat *)format;

/*! @method disconnectNodeInput:bus:
	@abstract
		Remove a connection between two nodes.
	@param node the node whose input is to be disconnected
	@param bus the destination's input bus to disconnect
*/
- (void)disconnectNodeInput:(AVAudioNode *)node bus:(AVAudioNodeBus)bus;

/*!	@method disconnectNodeInput:
	@abstract
		Remove a connection between two nodes.
	@param node the node whose inputs are to be disconnected
	@discussion
		Connections are broken on each of the node's input busses.
*/
- (void)disconnectNodeInput:(AVAudioNode *)node;

/*! @method disconnectNodeOutput:bus:
	@abstract
		Remove a connection between two nodes.
	@param node the node whose output is to be disconnected
	@param bus the source's output bus to disconnect
*/
- (void)disconnectNodeOutput:(AVAudioNode *)node bus:(AVAudioNodeBus)bus;

/*!	@method disconnectNodeOutput:
	@abstract
		Remove a connection between two nodes.
	@param node the node whose outputs are to be disconnected
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
	
		Starts the audio hardware via the AVAudioInputNode and/or AVAudioOutputNode instances in
		the engine. Audio begins flowing through the engine.
	
		Reasons for potential failure include:
		
		1. There is problem in the structure of the graph. Input can't be routed to output or to a
			recording tap through converter type nodes.
		2. An AVAudioSession error.
		3. The driver failed to start the hardware.
*/
- (BOOL)startAndReturnError:(NSError **)outError;

/*!	@method pause
	@abstract
		Pause the engine.
	@discussion
		Stops the flow of audio through the engine, but does not deallocate the resources allocated
		by prepare. Resume the engine by invoking start again.
*/
- (void)pause;

/*!	@method reset
	@abstract reset
		Reset all of the nodes in the engine.
	@discussion
		This will reset all of the nodes in the engine. This is useful, for example, for silencing
		reverb and delay tails.
*/
- (void)reset;

/*! @method stop
	@abstract
		Stop the engine. Releases the resources allocated by prepare.
*/
- (void)stop;

/*! @property musicSequence
	@abstract
		The MusicSequence previously attached to the engine (if any).
 */
@property (nonatomic) MusicSequence musicSequence;

/*! @property outputNode
	@abstract
		The engine's singleton output node.
	@discussion
		Audio output is performed via an output node. The engine creates a singleton on demand when
		this property is first accessed. Connect another node to the input of the output node, or obtain
		a mixer that is connected there by default, using the "mainMixerNode" property.
 
		The AVAudioSesssion category and/or availability of hardware determine whether an app can
		perform output. Check the output format of output node (i.e. hardware format) for non-zero
		sample rate and channel count to see if output is enabled.
*/
@property (readonly, nonatomic) AVAudioOutputNode *outputNode;

/*! @property inputNode
	@abstract
		The engine's singleton input node.
	@discussion
		Audio input is performed via an input node. The engine creates a singleton on demand when
		this property is first accessed. To receive input, connect another node from the output of 
		the input node, or create a recording tap on it.
 
		The AVAudioSesssion category and/or availability of hardware determine whether an app can
		perform input. Check the input format of input node (i.e. hardware format) for non-zero
		sample rate and channel count to see if input is enabled.
*/
@property (readonly, nonatomic) AVAudioInputNode *inputNode;

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

@end

/*!	@constant AVAudioEngineConfigurationChangeNotification
	@abstract
		A notification generated on engine configuration changes.
	@discussion
		Register for this notification on your engine instances, as follows:
		
		[[NSNotificationCenter defaultCenter] addObserver: myObject 
			 selector:    @selector(handleInterruption:)
			 name:        AVAudioEngineConfigurationChangeNotification
			 object:      engine];

		When the engine's I/O unit observes a change to the audio input or output hardware's
		channel count or sample rate, the engine stops, uninitializes itself, and issues this 
		notification.	
*/
AVF_EXPORT
NSString *const AVAudioEngineConfigurationChangeNotification NS_AVAILABLE(10_10, 8_0);

