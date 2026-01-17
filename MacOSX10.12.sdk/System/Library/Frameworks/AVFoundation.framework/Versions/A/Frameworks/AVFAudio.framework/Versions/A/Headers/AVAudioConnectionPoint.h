/*
	File:		AVAudioConnectionPoint.h
	Framework:	AVFoundation
	
	Copyright (c) 2015 Apple Inc. All Rights Reserved.
*/

#import <AVFAudio/AVAudioTypes.h>

NS_ASSUME_NONNULL_BEGIN

@class AVAudioNode;

/*! @class AVAudioConnectionPoint
	@abstract A representation of either a source or destination connection point in AVAudioEngine.
	@discussion
		AVAudioConnectionPoint describes either a source or destination connection point (node, bus)
		in AVAudioEngine's graph.
	
		Instances of this class are immutable.
*/
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface AVAudioConnectionPoint : NSObject {
@private
	AVAudioNode *_node;
	AVAudioNodeBus _bus;
	void *_reserved;
}

/*! @method initWithNode:bus:
	@abstract Create a connection point object.
	@param node the source or destination node
	@param bus the output or input bus on the node
	@discussion
		If the node is nil, this method fails (returns nil).
*/
- (instancetype)initWithNode:(AVAudioNode *)node bus:(AVAudioNodeBus)bus NS_DESIGNATED_INITIALIZER;

- (instancetype)init NS_UNAVAILABLE;

/*!	@property node
	@abstract Returns the node in the connection point.
*/
@property (nonatomic, readonly, weak) AVAudioNode *node;

/*!	@property bus
	@abstract Returns the bus on the node in the connection point.
*/
@property (nonatomic, readonly) AVAudioNodeBus bus;

@end

NS_ASSUME_NONNULL_END

