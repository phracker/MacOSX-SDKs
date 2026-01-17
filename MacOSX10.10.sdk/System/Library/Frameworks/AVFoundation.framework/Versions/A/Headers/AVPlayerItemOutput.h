/*
    File:  AVPlayerItemOutput.h

	Framework:  AVFoundation
 
	Copyright 2011-2013 Apple Inc. All rights reserved.

*/

#import <AVFoundation/AVBase.h>
#import <Foundation/Foundation.h>
#import <CoreMedia/CMTime.h>
#import <CoreVideo/CVPixelBuffer.h>

#if ! TARGET_OS_IPHONE

#import <CoreVideo/CVHostTime.h>

#endif // ! TARGET_OS_IPHONE

/*!
	@class			AVPlayerItemOutput
	@abstract		AVPlayerItemOutput is an abstract class encapsulating the common API for all AVPlayerItemOutput subclasses.
	@discussion
		Instances of AVPlayerItemOutput permit the acquisition of individual samples from an AVAsset during playback by an AVPlayer. To provide graceful degradation of service across multiple AVPlayerItemOutput instances for a single source, all AVPlayerItemOutput subclasses only offer the current sample and/or any readily available future samples. All samples earlier than the current sample are automatically discarded by the AVPlayerItemOutput.
		
		You manage an association of an AVPlayerItemOutput instance with an AVPlayerItem as the source input using the AVPlayerItem methods:
		
		• addOutput:
		• removeOutput:
		
		When an AVPlayerItemOutput is associated with an AVPlayerItem, samples are provided for a media type in accordance with the rules for mixing, composition, or exclusion that the AVPlayer honors among multiple enabled tracks of that media type for its own rendering purposes. For example, video media will be composed according to the instructions provided via AVPlayerItem.videoComposition, if present.
 */

@class AVPlayerItemOutputInternal;

NS_CLASS_AVAILABLE(10_8, 6_0)
@interface AVPlayerItemOutput : NSObject
{
	@private
	AVPlayerItemOutputInternal *_outputInternal;
}

/*!
	@method			itemTimeForHostTime:
	@abstract		Convert a host time, expressed in seconds, to item time.
	@discussion
		Converts a host time value (for example a CADisplayLink timestamp, or the value returned by CACurrentMediaTime()) to the equivalent time on the item's timebase.
		
		Note: The Core Animation CADisplayLink timestamp property expresses the most recent, or previous, screen refresh time. You need to increment this timestamp by the CADisplayLink's duration property to find the next appropriate item time.
	@param			hostTimeInSeconds
					The timestamp value to convert to item time.
	@result			The equivalent item time.
 */

- (CMTime)itemTimeForHostTime:(CFTimeInterval)hostTimeInSeconds;

/*!
	@method			itemTimeForMachAbsoluteTime:
	@abstract		Convenience method to convert a Mach host time to item time.
	@discussion
		Converts Mach host time to the equivalent time on the item's timebase.
		mach_absolute_time() returns time awake since boot in system-specific rational units that can be queried by calling mach_timebase_info().
	@param			machAbsoluteTime
					The Mach host time to convert to item time.
	@result			The equivalent item time.
 */

- (CMTime)itemTimeForMachAbsoluteTime:(int64_t)machAbsoluteTime;

#if !TARGET_OS_IPHONE

/*!
	@method			itemTimeForCVTimeStamp:
	@abstract		Convenience method to convert a CoreVideo timestamp to the equivalent time on the item's timebase.
	@discussion
		Note: A CVDisplayLink provides a parameter inOutputTimestamp that expresses a future screen refresh time. You can use this value directly to find the next appropriate item time.
	@param			timestamp
					The CoreVideo timestamp value to convert to item time.
	@result			The equivalent item time.
 */

- (CMTime)itemTimeForCVTimeStamp:(CVTimeStamp)timestamp NS_AVAILABLE(10_8, NA);

#endif // !TARGET_OS_IPHONE

/*!
	@property		suppressesPlayerRendering
	@abstract		Indicates whether the output, when added to an AVPlayerItem, will be used in addition to normal rendering of media data by the player or instead of normal rendering.
	@discussion
		The default value is NO, indicating that the output will be used in addition to normal rendering. If you want to render the media data provided by the output yourself instead of allowing it to be rendered as in normally would be by AVPlayer, set suppressesPlayerRendering to YES.
 
		 Whenever any output is added to an AVPlayerItem that has suppressesPlayerRendering set to YES, the media data supplied to the output will not be rendered by AVPlayer. Other media data associated with the item but not provided to such an output is not affected. For example, if an output of class AVPlayerItemVideoOutput with a value of YES for suppressesPlayerRendering is added to an AVPlayerItem, video media for that item will not be rendered by the AVPlayer, while audio media, subtitle media, and other kinds of media, if present, will be rendered.
*/
@property (nonatomic, readwrite) BOOL suppressesPlayerRendering NS_AVAILABLE(10_8, 6_0);

@end

/*!
	@class			AVPlayerItemVideoOutput
	@abstract		A concrete subclass of AVPlayerItemOutput that vends video images as CVPixelBuffers.
	@discussion
		It is best to use a AVPlayerItemVideoOutput in conjunction with the services of a CVDisplayLink or CADisplayLink to accurately synchronize with screen device refreshes. For optimum efficiency there are opportunities to quiesce these services. Examples include when playback is paused or during playback of empty edits. Below is sample code that illustrates how you might quiesce a CVDisplayLink when used with a AVPlayerItemVideoOutput.


	(void)CVDisplayLinkCreateWithActiveCGDisplays( &myDisplayLink );
	CVDisplayLinkSetOutputCallback( myDisplayLink, myDisplayCallback, self );
	
	[myPlayerItem addOutput:myVideoOutput];
	[myVideoOutput setDelegate:self queue:myDispatchQueue];
	
	...
	
	static CVReturn myDisplayCallback ( CVDisplayLinkRef displayLink, 
										const CVTimeStamp *inNow, 
										const CVTimeStamp *inOutputTime, 
										CVOptionFlags flagsIn, 
										CVOptionFlags *flagsOut, 
										void *displayLinkContext )
	{
		MYObject *self = displayLinkContext;
	 
		CMTime outputItemTime = [[self myVideoOutput] itemTimeForCVTimeStamp:*inOutputTime];
		if ( [[self myVideoOutput] hasNewPixelBufferForItemTime:outputItemTime] ) {
			CVPixelBufferRef pixBuff = NULL;
			CMTime presentationItemTime = kCMTimeZero;
			self->myLastHostTime = inOutputTime->hostTime;
			pixBuff = [[self myVideoOutput] copyPixelBufferForItemTime:outputItemTime itemTimeForDisplay:&presentationItemTime];
	 
			// Use pixBuff here
			// presentationItemTime is the item time appropriate for
			// the next screen refresh
	
			CVBufferRelease( pixBuff );
		}
		else {
			CMTime elapsedTime = CMClockMakeHostTimeFromSystemUnits( inNow->hostTime - self->myLastHostTime );
			if ( CMTimeGetSeconds( elapsedTime ) > NON_QUIESCENT_PERIOD_IN_SECONDS ) {
				[[self myVideoOutput] requestNotificationOfMediaDataChangeWithAdvanceInterval:MY_STARTUP_TIME_IN_SECONDS];
				CVDisplayLinkStop( displayLink );
			}
		}
		return kCVReturnSuccess;
	}
	
	- (void)outputMediaDataWillChange:(AVPlayerItemOutput *)output
	{	
		// Start running again
		myLastHostTime = CVGetCurrentHostTime();
		CVDisplayLinkStart( myDisplayLink );
	}


 */
 
@protocol AVPlayerItemOutputPullDelegate;

@class AVPlayerItemVideoOutputInternal;

NS_CLASS_AVAILABLE(10_8, 6_0)
@interface AVPlayerItemVideoOutput : AVPlayerItemOutput
{
@private
	AVPlayerItemVideoOutputInternal *_videoOutputInternal;
}

/*!
	@method			initWithPixelBufferAttributes:
	@abstract		Returns an instance of AVPlayerItemVideoOutput, initialized with the specified pixel buffer attributes, for video image output.
	@param			pixelBufferAttributes
					The client requirements for output CVPixelBuffers, expressed using the constants in <CoreVideo/CVPixelBuffer.h>.
	@result			An instance of AVPlayerItemVideoOutput.
 */

- (instancetype)initWithPixelBufferAttributes:(NSDictionary *)pixelBufferAttributes;

/*!
	@method			hasNewPixelBufferForItemTime:
	@abstract		Query if any new video output is available for an item time.
	@discussion
		This method returns YES if there is available video output, appropriate for display, at the specified item time not marked as acquired. If you require multiple objects to acquire video output from the same AVPlayerItem, you should instantiate more than one AVPlayerItemVideoOutput and add each via addOutput:. Each AVPlayerItemVideoOutput maintains a separate record of client acquisition.
	@param			itemTime
					The item time to query.
	@result			A BOOL indicating if there is newer output.
 */

- (BOOL)hasNewPixelBufferForItemTime:(CMTime)itemTime;

/*!
	@method			copyPixelBufferForItemTime:itemTimeForDisplay:
	@abstract		Retrieves an image that is appropriate for display at the specified item time, and marks the image as acquired.
	@discussion
		The client is responsible for calling CVBufferRelease on the returned CVPixelBuffer when finished with it. 
		
		Typically you would call this method in response to a CVDisplayLink callback or CADisplayLink delegate invocation and if hasNewPixelBufferForItemTime: also returns YES. 
		
		The buffer reference retrieved from copyPixelBufferForItemTime:itemTimeForDisplay: may itself be NULL. A reference to a NULL pixel buffer communicates that nothing should be displayed for the supplied item time.
	@param			itemTime
					A CMTime that expresses a desired item time.
	@param			itemTimeForDisplay
					A CMTime pointer whose value will contain the true display deadline for the copied pixel buffer. Can be NULL.
 */

- (CVPixelBufferRef)copyPixelBufferForItemTime:(CMTime)itemTime itemTimeForDisplay:(CMTime *)outItemTimeForDisplay CF_RETURNS_RETAINED;

/*!
	@method			setDelegate:queue:
	@abstract		Sets the receiver's delegate and a dispatch queue on which the delegate will be called.
	@param			delegate
					An object conforming to AVPlayerItemOutputPullDelegate protocol.
	@param			delegateQueue
					A dispatch queue on which all delegate methods will be called.
 */

- (void)setDelegate:(id<AVPlayerItemOutputPullDelegate>)delegate queue:(dispatch_queue_t)delegateQueue;

/*!
	@method			requestNotificationOfMediaDataChangeWithAdvanceInterval:
	@abstract		Informs the receiver that the AVPlayerItemVideoOutput client is entering a quiescent state.
	@param			interval
					A wall clock time interval.
	@discussion
		Message this method before you suspend your use of a CVDisplayLink or CADisplayLink. The interval you provide will be used to message your delegate, in advance, that it should resume the display link. If the interval you provide is large, effectively requesting wakeup earlier than the AVPlayerItemVideoOutput is prepared to act, the delegate will be invoked as soon as possible. Do not use this method to force a delegate invocation for each sample.
 */
 
- (void)requestNotificationOfMediaDataChangeWithAdvanceInterval:(NSTimeInterval)interval;

/*!
	@property		delegate
	@abstract		The receiver's delegate.
 */
@property (nonatomic, readonly) id<AVPlayerItemOutputPullDelegate>delegate;

/*!
	@property		delegateQueue
	@abstract		The dispatch queue where the delegate is messaged.
 */

@property (nonatomic, readonly) dispatch_queue_t delegateQueue;

@end

/*!
	@protocol		AVPlayerItemOutputPullDelegate
	@abstract		Defines common delegate methods for objects participating in AVPlayerItemOutput pull sample output acquisition.
 */
 
 @protocol AVPlayerItemOutputPullDelegate <NSObject>
 
 @optional
 
 /*!
	@method			outputMediaDataWillChange:
	@abstract		A method invoked once, prior to a new sample, if the AVPlayerItemOutput sender was previously messaged requestNotificationOfMediaDataChangeWithAdvanceInterval:.
	@discussion
		This method is invoked once after the sender is messaged requestNotificationOfMediaDataChangeWithAdvanceInterval:.
  */

- (void)outputMediaDataWillChange:(AVPlayerItemOutput *)sender NS_AVAILABLE(10_8, 6_0);
 
 /*!
	@method			outputSequenceWasFlushed:
	@abstract		A method invoked when the output is commencing a new sequence.
	@discussion
		This method is invoked after any seeking and change in playback direction. If you are maintaining any queued future samples, copied previously, you may want to discard these after receiving this message.
  */

- (void)outputSequenceWasFlushed:(AVPlayerItemOutput *)output NS_AVAILABLE(10_8, 6_0);

@end


@protocol AVPlayerItemLegibleOutputPushDelegate;
@class AVPlayerItemLegibleOutputInternal;

/*!
	@class			AVPlayerItemLegibleOutput
	@abstract		A subclass of AVPlayerItemOutput that can vend media with a legible characteristic as NSAttributedStrings.
	@discussion
		An instance of AVPlayerItemLegibleOutput is typically initialized using the -init method.
 */
NS_CLASS_AVAILABLE(10_9, 7_0)
@interface AVPlayerItemLegibleOutput : AVPlayerItemOutput
{
@private
	AVPlayerItemLegibleOutputInternal *_legibleOutputInternal;
}

/*!
	@method			setDelegate:queue:
	@abstract		Sets the receiver's delegate and a dispatch queue on which the delegate will be called.
	@param			delegate
					An object conforming to AVPlayerItemLegibleOutputPushDelegate protocol.
	@param			delegateQueue
					A dispatch queue on which all delegate methods will be called.
	@discussion
		The delegate is held using a zeroing-weak reference, so it is safe to deallocate the delegate while the receiver still has a reference to it.
 */
- (void)setDelegate:(id <AVPlayerItemLegibleOutputPushDelegate>)delegate queue:(dispatch_queue_t)delegateQueue;

/*!
	@property		delegate
	@abstract		The receiver's delegate.
	@discussion
		The delegate is held using a zeroing-weak reference, so this property will have a value of nil after a delegate that was previously set has been deallocated.
 */
@property (nonatomic, readonly) id <AVPlayerItemLegibleOutputPushDelegate> delegate;

/*!
	@property		delegateQueue
	@abstract		The dispatch queue where the delegate is messaged.
 */
@property (nonatomic, readonly) dispatch_queue_t delegateQueue;

/*!
	@property		advanceIntervalForDelegateInvocation
	@abstract		Permits advance invocation of the associated delegate, if any.
	@discussion
		If it is possible, an AVPlayerItemLegibleOutput will message its delegate advanceIntervalForDelegateInvocation seconds earlier than otherwise. If the value you provide is large, effectively requesting provision of samples earlier than the AVPlayerItemLegibleOutput is prepared to act on them, the delegate will be invoked as soon as possible.
 */
@property (nonatomic, readwrite) NSTimeInterval advanceIntervalForDelegateInvocation;

@end


@interface AVPlayerItemLegibleOutput (AVPlayerItemLegibleOutput_NativeRepresentation)

/*!
	@method			initWithMediaSubtypesForNativeRepresentation:
	@abstract		Returns an instance of AVPlayerItemLegibleOutput with filtering enabled for AVPlayerItemLegibleOutputPushDelegate's legibleOutput:didOutputAttributedStrings:nativeSampleBuffers:forItemTime:.
	@param			subtypes
					NSArray of NSNumber FourCC codes, e.g. @[ [NSNumber numberWithUnsignedInt:'tx3g'] ]
	@result			An instance of AVPlayerItemLegibleOutput.
	@discussion
		Add media subtype FourCC number objects to the subtypes array to elect to receive that type as a CMSampleBuffer instead of an NSAttributedString.  Initializing an AVPlayerItemLegibleOutput using the -init method is equivalent to calling -initWithMediaSubtypesForNativeRepresentation: with an empty array, which means that all legible data, regardless of media subtype, will be delivered using NSAttributedString in a common format.
 
		If a media subtype for which there is no legible data in the current player item is included in the media subtypes array, no error will occur.  AVPlayerItemLegibleOutput will not vend closed caption data as CMSampleBuffers, so it is an error to include 'c608' in the media subtypes array.
 */	
- (instancetype)initWithMediaSubtypesForNativeRepresentation:(NSArray *)subtypes;	

@end


@interface AVPlayerItemLegibleOutput (AVPlayerItemLegibleOutput_TextStylingResolution)

/*!
 @constant		AVPlayerItemLegibleOutputTextStylingResolutionDefault
 @abstract		Specify this level of text styling resolution to receive attributed strings from an AVPlayerItemLegibleOutput that include the same level of styling information that AVFoundation would use itself to render text within an AVPlayerLayer. The text styling will accommodate user-level Media Accessibility settings.
 */
AVF_EXPORT NSString *const AVPlayerItemLegibleOutputTextStylingResolutionDefault NS_AVAILABLE(10_9, 7_0);

/*!
 @constant		AVPlayerItemLegibleOutputTextStylingResolutionSourceAndRulesOnly
 @abstract		Specify this level of text styling resolution to receive only the styling present in the source media and the styling provided via AVPlayerItem.textStyleRules.
 @discussion
	This level of resolution excludes styling provided by the user-level Media Accessibility settings. You would typically use it if you wish to override the styling specified in source media. If you do this, you are strongly encouraged to allow your custom styling in turn to be overriden by user preferences for text styling that are available as Media Accessibility settings.
 */
AVF_EXPORT NSString *const AVPlayerItemLegibleOutputTextStylingResolutionSourceAndRulesOnly NS_AVAILABLE(10_9, 7_0);

/*!
 @property		textStylingResolution
 @abstract		A string identifier indicating the degree of text styling to be applied to attributed strings vended by the receiver
 @discussion
	Valid values are AVPlayerItemLegibleOutputTextStylingResolutionDefault and AVPlayerItemLegibleOutputTextStylingResolutionSourceAndRulesOnly.  An NSInvalidArgumentException is raised if this property is set to any other value.  The default value is AVPlayerItemLegibleOutputTextStylingResolutionDefault, which indicates that attributed strings vended by the receiver will include the same level of styling information that would be used if AVFoundation were rendering the text via AVPlayerLayer.
 */
@property (nonatomic, copy) NSString *textStylingResolution;

@end


@protocol AVPlayerItemOutputPushDelegate;

/*!
	@protocol		AVPlayerItemLegibleOutputPushDelegate
	@abstract		Extends AVPlayerItemOutputPushDelegate to provide additional methods specific to attributed string output.
 */
@protocol AVPlayerItemLegibleOutputPushDelegate <AVPlayerItemOutputPushDelegate>

@optional

/*!
	@method			legibleOutput:didOutputAttributedStrings:nativeSampleBuffers:forItemTime:
	@abstract		A delegate callback that delivers new textual samples.
	@param			output
					The AVPlayerItemLegibleOutput source.
	@param			strings
					An NSArray of NSAttributedString, each containing both the run of text and descriptive markup.
	@param			nativeSamples
					An NSArray of CMSampleBuffer objects, for media subtypes included in the array passed in to -initWithMediaSubtypesForNativeRepresentation:
	@param			itemTime
					The item time at which the strings should be presented.
	@discussion
		For each media subtype in the array passed in to -initWithMediaSubtypesForNativeRepresentation:, the delegate will receive sample buffers carrying data in its native format via the nativeSamples parameter, if there is media data of that subtype in the media resource.  For all other media subtypes present in the media resource, the delegate will receive attributed strings in a common format via the strings parameter.  See <CoreMedia/CMTextMarkup.h> for the string attributes that are used in the attributed strings.
 */
- (void)legibleOutput:(AVPlayerItemLegibleOutput *)output didOutputAttributedStrings:(NSArray *)strings nativeSampleBuffers:(NSArray *)nativeSamples forItemTime:(CMTime)itemTime NS_AVAILABLE(10_9, 7_0);

@end


/*!
 @protocol		AVPlayerItemOutputPushDelegate
 @abstract		Defines common delegate methods for objects participating in AVPlayerItemOutput push sample output acquisition.
 */
@protocol AVPlayerItemOutputPushDelegate <NSObject>

@optional

/*!
	@method			outputSequenceWasFlushed:
	@abstract		A method invoked when the output is commencing a new sequence of media data.
	@discussion
		This method is invoked after any seeking and change in playback direction. If you are maintaining any queued future media data, received previously, you may want to discard these after receiving this message.
 */
- (void)outputSequenceWasFlushed:(AVPlayerItemOutput *)output;

@end

@protocol AVPlayerItemMetadataOutputPushDelegate;
@class AVPlayerItemMetadataOutputInternal;

/*!
	@class			AVPlayerItemMetadataOutput
	@abstract		A subclass of AVPlayerItemOutput that vends collections of metadata items carried in metadata tracks.
 
	@discussion
	Setting the value of suppressesPlayerRendering on an instance of AVPlayerItemMetadataOutput has no effect.
 */
NS_CLASS_AVAILABLE(10_10, 8_0)
@interface AVPlayerItemMetadataOutput : AVPlayerItemOutput
{
@private
	AVPlayerItemMetadataOutputInternal *_metadataOutputInternal;
}

/*!
	@method			initWithIdentifiers:
	@abstract		Creates an instance of AVPlayerItemMetadataOutput.
	@param			identifiers
	A array of metadata identifiers indicating the metadata items that the output should provide. See AVMetadataIdentifiers.h for publicly defined metadata identifiers. Pass nil to receive all of the timed metadata from all enabled AVPlayerItemTracks that carry timed metadata.
 */
- (instancetype)initWithIdentifiers:(NSArray *)identifiers;

/*!
	@method			setDelegate:queue:
	@abstract		Sets the receiver's delegate and a dispatch queue on which the delegate will be called.
	@param			delegate
	An object conforming to AVPlayerItemMetadataOutputPushDelegate protocol.
	@param			delegateQueue
	A dispatch queue on which all delegate methods will be called.
 */
- (void)setDelegate:(id<AVPlayerItemMetadataOutputPushDelegate>)delegate queue:(dispatch_queue_t)delegateQueue;

/*!
	@property		delegate
	@abstract		The receiver's delegate.
 */
@property (nonatomic, readonly) id<AVPlayerItemMetadataOutputPushDelegate> delegate;

/*!
	@property		delegateQueue
	@abstract		The dispatch queue on which messages are sent to the delegate.
 */

@property (nonatomic, readonly) dispatch_queue_t delegateQueue;

/*!
	@property		advanceIntervalForDelegateInvocation
	@abstract		Permits advance invocation of the associated delegate, if any.
	@discussion
	If it is possible, an AVPlayerItemMetadataOutput will message its delegate advanceIntervalForDelegateInvocation seconds earlier than otherwise. If the value you provide is large, effectively requesting provision of samples earlier than the AVPlayerItemMetadataOutput is prepared to act on them, the delegate will be invoked as soon as possible.
 */

@property (nonatomic, readwrite) NSTimeInterval advanceIntervalForDelegateInvocation;

@end

@class AVTimedMetadataGroup;
@class AVPlayerItemTrack;

/*!
	@protocol		AVPlayerItemMetadataOutputPushDelegate
	@abstract		Extends AVPlayerItemOutputPushDelegate to provide additional methods specific to metadata output.
 */
@protocol AVPlayerItemMetadataOutputPushDelegate <AVPlayerItemOutputPushDelegate>

@optional
/*!
	@method			metadataOutput:didOutputTimedMetadataGroup:fromPlayerItemTrack:
	@abstract		A delegate callback that delivers a new collection of metadata items.
	@param			output
	The AVPlayerItemMetadataOutput source.
	@param			groups
	An NSArray of AVTimedMetadataGroups that may contain metadata items with requested identifiers, according to the format descriptions associated with the underlying tracks.
	@param			track
	An instance of AVPlayerItemTrack that indicates the source of the metadata items in the group.
	@discussion
	Each group provided in a single invocation of this method will have timing that does not overlap with any other group in the array.
	Note that for some timed metadata formats carried by HTTP live streaming, the timeRange of each group must be reported as kCMTimeIndefinite, because its duration will be unknown until the next metadata group in the stream arrives. In these cases, the groups parameter will always contain a single group.
	Groups are typically packaged into arrays for delivery to your delegate according to the chunking or interleaving of the underlying metadata data.
	Note that if the item carries multiple metadata tracks containing metadata with the same metadata identifiers, this method can be invoked for each one separately, each with reference to the associated AVPlayerItemTrack.
 */

- (void)metadataOutput:(AVPlayerItemMetadataOutput *)output didOutputTimedMetadataGroups:(NSArray *)groups fromPlayerItemTrack:(AVPlayerItemTrack *)track NS_AVAILABLE(10_10, 8_0);

@end
