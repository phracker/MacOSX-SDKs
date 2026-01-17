/*
 File:  AVPlayerItemMediaDataCollector.h

	Framework:  AVFoundation

	Copyright 2015-2016 Apple Inc. All rights reserved.

 */

#import <AVFoundation/AVBase.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class AVPlayerItemMediaDataCollectorInternal;

/*!
	@class			AVPlayerItemMediaDataCollector
	@abstract		AVPlayerItemMediaDataCollector is an abstract class encapsulating the common API for all AVPlayerItemMediaDataCollector subclasses.
	@discussion
		Instances of AVPlayerItemMediaDataCollector permit the collection of media data from an AVAsset during playback by an AVPlayer. As opposed to AVPlayerItemOutputs, AVPlayerItemMediaDataCollectors collect all media data across an AVPlayerItem's timebase, relevant to the specific collector being used. Attaching an AVPlayerItemMediaDataCollector may incur additional I/O accordingly.

		You manage an association of an AVPlayerItemMediaDataCollector instance with an AVPlayerItem as the source input using the AVPlayerItem methods:

		• addMediaDataCollector:
		• removeMediaDataCollector:
*/
API_AVAILABLE(macos(10.11.3), ios(9.3), tvos(9.3), watchos(2.3))
@interface AVPlayerItemMediaDataCollector : NSObject
{
@private
	AVPlayerItemMediaDataCollectorInternal *_collectorInternal;
}
@end

@protocol AVPlayerItemMetadataCollectorPushDelegate;
@class AVPlayerItemMetadataCollectorInternal;
@class AVDateRangeMetadataGroup;

/*!
	@class			AVPlayerItemMetadataCollector
	@abstract		A subclass of AVPlayerItemMediaDataCollector that provides AVMetadataGroups for an AVPlayerItem.
	@discussion
		This class can be used to inform clients of the current set of AVMetadataGroups on an AVPlayerItem, and when new AVMetadataGroups become available - e.g. in a Live HLS stream.
*/
API_AVAILABLE(macos(10.11.3), ios(9.3), tvos(9.3), watchos(2.3))
@interface AVPlayerItemMetadataCollector : AVPlayerItemMediaDataCollector
{
@private
	AVPlayerItemMetadataCollectorInternal *_metadataCollectorInternal;
}

/*!
	@method			initWithIdentifiers:classifyingLabels:
	@abstract		Returns an instance of AVPlayerItemMetadataCollector that can provide all available AVMetadataGroups matching a set of criteria.
	@param			identifiers
					A array of metadata identifiers indicating the metadata items that the output should provide. See AVMetadataIdentifiers.h for publicly defined metadata identifiers. Pass nil to include metadata with any identifier.
	@param			classifyingLabels
					If the metadata format supports labeling each metadata group with a string, supplying an array of group labels indicates that the output should provide metadata groups that match one of the supplied labels. Pass nil to include metadata with any (or no) classifying label.
	@result			An instance of AVPlayerItemMetadataCollector.
	@discussion
		Some metadata available in some formats - such as timed metadata embedded in HLS segments - is not available for collector output.
		The default init method can be used as an alternative to setting both identifiers and classifyingLabels to nil.
*/
- (instancetype)initWithIdentifiers:(nullable NSArray<NSString *> *)identifiers classifyingLabels:(nullable NSArray<NSString *> *)classifyingLabels;

/*!
	@method			setDelegate:queue:
	@abstract		Sets the receiver's delegate and a dispatch queue on which the delegate will be called.
	@param			delegate
					An object conforming to AVPlayerItemMetadataCollectorPushDelegate protocol.
	@param			delegateQueue
					A dispatch queue on which all delegate methods will be called.
*/
- (void)setDelegate:(nullable id <AVPlayerItemMetadataCollectorPushDelegate>)delegate queue:(nullable dispatch_queue_t)delegateQueue;

/*!
	@property		delegate
	@abstract		The receiver's delegate.
	@discussion
		The delegate is held using a zeroing-weak reference, so this property will have a value of nil after a delegate that was previously set has been deallocated.  This property is not key-value observable.
*/
@property (nonatomic, readonly, weak, nullable) id <AVPlayerItemMetadataCollectorPushDelegate> delegate;

/*!
	@property		delegateQueue
	@abstract		The dispatch queue on which messages are sent to the delegate.
	@discussion
		This property is not key-value observable.
*/
@property (nonatomic, readonly, nullable) dispatch_queue_t delegateQueue;

@end

@protocol AVPlayerItemMetadataCollectorPushDelegate <NSObject>

/*!
	@method			metadataCollector:didCollectDateRangeMetadataGroups:indexesOfNewGroup:indexesOfModifiedGroups:
	@abstract		A delegate callback that delivers the total set of AVDateRangeMetadataGroups for this collector.
	@param			metadataCollector
					The AVPlayerItemMetadataCollector source.
	@param			metadataGroups
					The set of all metadata groups meeting the criteria of the output.
	@param			indexesOfNewGroups
					Indexes of metadataGroups added since the last delegate invocation of this method.
	@param			indexesOfModifiedGroups
					Indexes of metadataGroups modified since the last delegate invocation of this method.
	@discussion
		This method will be invoked whenever new AVDateRangeMetadataGroups are added to metadataGroups or whenever any AVDateRangeMetadataGroups in metadataGroups have been modified since previous invocations. The initial invocation will have indexesOfNewGroup referring to every index in metadataGroups. Subsequent invocations may not contain all previously collected metadata groups if they no longer refer to a region in the AVPlayerItem's seekableTimeRanges.
*/
- (void)metadataCollector:(AVPlayerItemMetadataCollector *)metadataCollector didCollectDateRangeMetadataGroups:(NSArray<AVDateRangeMetadataGroup *> *)metadataGroups indexesOfNewGroups:(NSIndexSet *)indexesOfNewGroups indexesOfModifiedGroups:(NSIndexSet *)indexesOfModifiedGroups;

@end

NS_ASSUME_NONNULL_END
