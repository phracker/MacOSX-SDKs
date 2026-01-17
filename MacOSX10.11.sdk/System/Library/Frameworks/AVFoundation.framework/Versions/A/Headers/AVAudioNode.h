/*
	File:		AVAudioNode.h
	Framework:	AVFoundation
	
	Copyright (c) 2014-2015 Apple Inc. All Rights Reserved.
*/

#import <AVFoundation/AVAudioTypes.h>

NS_ASSUME_NONNULL_BEGIN

@class AVAudioEngine, AVAudioFormat, AVAudioInputNode, AVAudioMixerNode, AVAudioOutputNode, AVAudioPCMBuffer, AVAudioTime;

/*!	@typedef AVAudioNodeTapBlock
	@abstract A block that receives copies of the output of an AVAudioNode.
	@param buffer
		a buffer of audio captured from the output of an AVAudioNode
	@param when
		the time at which the buffer was captured
	@discussion
		CAUTION: This callback may be invoked on a thread other than the main thread.
*/
typedef void (^AVAudioNodeTapBlock)(AVAudioPCMBuffer *buffer, AVAudioTime *when);

/*!
	@class AVAudioNode
	@abstract Base class for an audio generation, processing, or I/O block.
	@discussion
		`AVAudioEngine` objects contain instances of various AVAudioNode subclasses. This
		base class provides certain common functionality.
		
		Nodes have input and output busses, which can be thought of as connection points.
		For example, an effect typically has one input bus and one output bus. A mixer
		typically has multiple input busses and one output bus.
		
		Busses have formats, expressed in terms of sample rate and channel count. When making
		connections between nodes, often the format must match exactly. There are exceptions
		(e.g. `AVAudioMixerNode` and `AVAudioOutputNode`).

		Nodes do not currently provide useful functionality until attached to an engine.
*/
NS_CLASS_AVAILABLE(10_10, 8_0)
@interface AVAudioNode : NSObject {
@protected
	void *_impl;
}
/*! @method reset
	@abstract Clear a unit's previous processing state.
*/
- (void)reset;

/*! @method inputFormatForBus:
	@abstract Obtain an input bus's format.
*/
- (AVAudioFormat *)inputFormatForBus:(AVAudioNodeBus)bus;

/*! @method outputFormatForBus:
	@abstract Obtain an output bus's format.
*/
- (AVAudioFormat *)outputFormatForBus:(AVAudioNodeBus)bus;

/*!	@method nameForInputBus:
	@abstract Return the name of an input bus.
*/
- (NSString *)nameForInputBus:(AVAudioNodeBus)bus;

/*!	@method nameForOutputBus:
	@abstract Return the name of an output bus.
*/
- (NSString *)nameForOutputBus:(AVAudioNodeBus)bus;

/*! @method installTapOnBus:bufferSize:format:block:
	@abstract Create a "tap" to record/monitor/observe the output of the node.
	@param bus
		the node output bus to which to attach the tap
	@param bufferSize
		the requested size of the incoming buffers. The implementation may choose another size.
	@param format
		If non-nil, attempts to apply this as the format of the specified output bus. This should
		only be done when attaching to an output bus which is not connected to another node; an
		error will result otherwise.
		The tap and connection formats (if non-nil) on the specified bus should be identical. 
		Otherwise, the latter operation will override any previously set format.
		Note that for AVAudioOutputNode, tap format must be specified as nil.
	@param tapBlock
		a block to be called with audio buffers
	
	@discussion
		Only one tap may be installed on any bus. Taps may be safely installed and removed while
		the engine is running.
		
		E.g. to capture audio from input node:
<pre>
AVAudioEngine *engine = [[AVAudioEngine alloc] init];
AVAudioInputNode *input = [engine inputNode];
AVAudioFormat *format = [input outputFormatForBus: 0];
[input installTapOnBus: 0 bufferSize: 8192 format: format block: ^(AVAudioPCMBuffer *buf, AVAudioTime *when) {
// ‘buf' contains audio captured from input node at time 'when'
}];
....
// start engine
</pre>
*/
- (void)installTapOnBus:(AVAudioNodeBus)bus bufferSize:(AVAudioFrameCount)bufferSize format:(AVAudioFormat * __nullable)format block:(AVAudioNodeTapBlock)tapBlock;

/*!	@method removeTapOnBus:
	@abstract Destroy a tap.
	@param bus
		the node output bus whose tap is to be destroyed
	@return
		YES for success.
*/
- (void)removeTapOnBus:(AVAudioNodeBus)bus;

/*!	@property engine
	@abstract The engine to which the node is attached (or nil).
*/
@property (nonatomic, readonly, nullable) AVAudioEngine *engine;

/*! @property numberOfInputs
	@abstract The node's number of input busses.
*/
@property (nonatomic, readonly) NSUInteger numberOfInputs;

/*! @property numberOfOutputs
	@abstract The node's number of output busses.
*/
@property (nonatomic, readonly) NSUInteger numberOfOutputs;

/*! @property lastRenderTime
	@abstract Obtain the time for which the node most recently rendered.
	@discussion
		Will return nil if the engine is not running or if the node is not connected to an input or
		output node.
*/
@property (nonatomic, readonly, nullable) AVAudioTime *lastRenderTime;

@end

NS_ASSUME_NONNULL_END
