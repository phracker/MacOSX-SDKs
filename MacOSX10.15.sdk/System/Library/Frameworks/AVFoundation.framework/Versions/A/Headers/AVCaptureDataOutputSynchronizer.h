/*
    File:  AVCaptureDataOutputSynchronizer.h
 
    Framework:  AVFoundation
 
    Copyright 2016-2017 Apple Inc. All rights reserved.
*/

#import <AVFoundation/AVCaptureOutput.h>
#import <CoreMedia/CMSampleBuffer.h>

NS_ASSUME_NONNULL_BEGIN

#pragma mark AVCaptureDataOutputSynchronizer

@class AVCaptureDataOutputSynchronizerInternal;
@class AVCaptureSynchronizedDataCollection;
@protocol AVCaptureDataOutputSynchronizerDelegate;

/*!
 @class AVCaptureDataOutputSynchronizer
 @abstract
    AVCaptureDataOutputSynchronizer synchronizes the delivery of data from multiple capture data outputs (AVCaptureVideoDataOutput, AVCaptureDepthDataOutput, AVCaptureMetadataOutput, AVCaptureAudioDataOutput) to a single delegate callback.

 @discussion
    AVCaptureDataOutputSynchronizer is initialized with an array of data outputs (AVCaptureVideoDataOutput, AVCaptureDepthDataOutput, AVCaptureMetadataOutput, or AVCaptureAudioDataOutput) from which you'd like to receive a single, synchronized delegate callback. The first output in the array acts as the master data output and determines when the synchronized callback is delivered. When data is received for the master data output, it is held until all other data outputs have received data with an equal or later presentation time stamp, or it has been determined that there is no data for a particular output at the master data output's pts. Once all other outputs are ready, a single delegate callback is sent with all the data aligned with the master data output's data. Separate delegate callbacks are sent for any other data received with presentation time stamps earlier than the next master data output time.

    For instance, if you specify a video data output as your first (master) output and a metadata output for detected faces as your second output, your data callback will not be called until there is face data ready for a video frame, or it is assured that there is no face metadata for that particular video frame.
 
    Note that the AVCaptureDataOutputSynchronizer overrides each data output's -setSampleBufferDelegate:queue:, -setDepthDataDelegate:queue:, or -setMetadataObjectsDelegate:queue: method call. -[AVCaptureVideoDataOutput alwaysDiscardsLateVideoFrames] and -[AVCaptureDepthDataOutput alwaysDiscardsLateDepthData] properties are honored.
 */
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos) __WATCHOS_PROHIBITED __TVOS_PROHIBITED
@interface AVCaptureDataOutputSynchronizer : NSObject
{
@private
    AVCaptureDataOutputSynchronizerInternal *_internal;
}

AV_INIT_UNAVAILABLE

/*!
 @method initWithDataOutputs:
 @abstract
    Instantiates an AVCaptureDataOutputSynchronizer from one or more capture data outputs.
 
 @param dataOutputs
    An array of capture data outputs where the first is the master.
 @result
    A newly initialized AVCaptureDataOutputSynchronizer instance.
 */
- (instancetype)initWithDataOutputs:(NSArray<AVCaptureOutput *> *)dataOutputs;

/*!
 @property dataOutputs
 @abstract
    The data outputs provided in the initializer method.
 */
@property(readonly, retain) NSArray<AVCaptureOutput *> *dataOutputs;

/*!
 @method setDelegate:queue:
 @abstract
    Sets the receiver's delegate that will accept synchronized data and the dispatch queue on which the delegate will be called.
 
 @param delegate
    An object conforming to the AVCaptureDataOutputSynchronizerDelegate protocol that will receive synchronized data from the provided data outputs.
 @param delegateCallbackQueue
    A dispatch queue on which all AVCaptureDataOutputSynchronizerDelegate methods will be called.
 
 @discussion
    AVCaptureDataOutputSynchronizer gathers data from its dataOutputs, and when it determines that all data has been received for a given timestamp, it calls the specified delegate on the specified delegateCallbackQueue. AVCaptureDataOutputSynchronizer overrides all the data outputs' delegates and callbacks. Data outputs under the control of AVCaptureDataOutputSynchronizer do not fire delegate callbacks. Delegate callbacks are restored to individual data outputs when you call this method with nil as your delegate and NULL as your delegateCallbackQueue.
 
    A serial dispatch queue must be used to guarantee that synchronized data will be delivered in order. The delegateCallbackQueue parameter may not be NULL, except when setting the delegate to nil.
 */
- (void)setDelegate:(nullable id<AVCaptureDataOutputSynchronizerDelegate>)delegate queue:(nullable dispatch_queue_t)delegateCallbackQueue;

/*!
 @property delegate
 @abstract
    The receiver's delegate.
 
 @discussion
    The value of this property is an object conforming to the AVCaptureDataOutputSynchronizerDelegate protocol that will receive synchronized data output. The delegate is set using the -setDelegate:queue: method. This property is key-value observable.
 */
@property(nullable, nonatomic, readonly) id<AVCaptureDataOutputSynchronizerDelegate> delegate;

/*!
 @property delegateCallbackQueue
 @abstract
    The dispatch queue on which all AVCaptureDataOutputSynchronizerDelegate methods will be called.
 
 @discussion
    The value of this property is a dispatch_queue_t. The queue is set using the -setDelegate:queue: method.
 */
@property(nullable, nonatomic, readonly) dispatch_queue_t delegateCallbackQueue;

@end


API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos) __WATCHOS_PROHIBITED __TVOS_PROHIBITED
@protocol AVCaptureDataOutputSynchronizerDelegate <NSObject>

@required
/*!
 @method captureOutputSynchronizer:didOutputSynchronizedData:
 @abstract
    Called when an AVCaptureDataOutputSynchronizer instance outputs synchronized data from one or more data outputs.
 
 @param captureOutputSynchronizer
    The AVCaptureDataOutputSynchronizer instance delivering synchronized data.
 @param synchronizedDataCollection
    A collection of synchronized data objects indexed by data output.
 
 @discussion
    The synchronized data collection only contains synchronized data for capture outputs with synchronized data ready.
 */
- (void)dataOutputSynchronizer:(AVCaptureDataOutputSynchronizer *)synchronizer didOutputSynchronizedDataCollection:(AVCaptureSynchronizedDataCollection *)synchronizedDataCollection;

@end


#pragma mark - AVCaptureSynchronizedDataCollection

@class AVCaptureSynchronizedData;
@class AVCaptureSynchronizedDataCollectionInternal;

/*!
 @class AVCaptureSynchronizedDataCollection
 @abstract
    A collection of AVCaptureSynchronizedData objects.
 
 @discussion
    AVCaptureDataOutputSynchronizer's -dataOutputSynchronizer:didOutputSynchronizedDataCollection: delegate method delivers a collection of AVCaptureSynchronizedData objects which can be iterated by use AVCaptureOutput. AVCaptureSynchronizedDataCollection supports object subscripting and fast enumeration of the data outputs as keys.
 */
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos) __WATCHOS_PROHIBITED __TVOS_PROHIBITED
@interface AVCaptureSynchronizedDataCollection : NSObject <NSFastEnumeration>
{
@private
    AVCaptureSynchronizedDataCollectionInternal *_internal;
}

AV_INIT_UNAVAILABLE

/*!
 @method synchronizedDataForCaptureOutput:
 @abstract
    Provides the synchronized data object for a given capture output.
 
 @param captureOutput
    The data output whose synchronized data you'd like to inspect.
 @result
    The synchronized data object associated with the provided output, or nil, if there is none.
 */
- (nullable AVCaptureSynchronizedData *)synchronizedDataForCaptureOutput:(AVCaptureOutput *)captureOutput;

/*!
 @method objectForKeyedSubscript:
 @abstract
    Method that provides support for object subscripting.
 
 @param key
    The data output whose synchronized data you'd like to inspect.
 @result
    The synchronized data object associated with the provided output, or nil, if there is none.
 
 @discussion
    AVCaptureSynchronizedDataCollection supports object subscripting. If you'd like to find the synchronized data for a given data output, simply:
        AVCaptureSynchronizedData *synchronizedData = synchronizedDataCollection[dataOutput];
 */
- (nullable AVCaptureSynchronizedData *)objectForKeyedSubscript:(AVCaptureOutput *)key;

/*!
 @property count
 @abstract
    The number of items in the collection.
 
 @discussion
    Returns the number of data output / synchronized data pairs present in the collection.
 */
@property(readonly) NSUInteger count;

@end


#pragma mark - AVCaptureSynchronizedData

@class AVCaptureSynchronizedDataInternal;

/*!
 @class AVCaptureSynchronizedData
 @abstract
    An abstract base class representing the data delivered by a data output through the AVCaptureDataOutputSynchronizer interface.
 
 @discussion
    AVCaptureDataOutputSynchronizer's -dataOutputSynchronizer:didOutputSynchronizedData: delegate callback delivers a dictionary of key/value pairs, with the keys being the AVCaptureOutput instances returning data, and the values being concrete subclasses of AVCaptureSynchronizedData.
 */
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos) __WATCHOS_PROHIBITED __TVOS_PROHIBITED
@interface AVCaptureSynchronizedData : NSObject
{
@private
    AVCaptureSynchronizedDataInternal *_synchronizedDataInternal;
}

AV_INIT_UNAVAILABLE

/*!
 @property timestamp
 @abstract
    The time at which this synchronized data was captured.
 
 @discussion
    Synchronized data is always clocked to the masterClock of the AVCaptureSession to which the data output is connected.
 */
@property(readonly) CMTime timestamp;

@end


#pragma mark - AVCaptureSynchronizedSampleBufferData

@class AVCaptureSynchronizedSampleBufferDataInternal;

/*!
 @class AVCaptureSynchronizedSampleBufferData
 @abstract
    An concrete subclass of AVCaptureSynchronizedData representing the data delivered by an AVCaptureVideoDataOutput or AVCaptureAudioDataOutput.

 @discussion
    Synchronized sample buffer data is valid for the duration of AVCaptureDataOutputSynchronizer's -dataOutputSynchronizer:didOutputSynchronizedData: delegate callback. To extend the sample buffer data beyond the callback, you must CFRetain it, and later call CFRelease when you're done with it.
 */
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos) __WATCHOS_PROHIBITED __TVOS_PROHIBITED
@interface AVCaptureSynchronizedSampleBufferData : AVCaptureSynchronizedData
{
@private
    AVCaptureSynchronizedSampleBufferDataInternal *_internal;
}

/*!
 @property sampleBuffer
 @abstract
    A sample buffer containing video or audio data.
 
 @discussion
    If sampleBufferWasDropped is YES, the returned sampleBuffer was dropped before it could be delivered to you, and thus this sample buffer is a shell containing metadata and format information, but no actual pixel data. This property is never NULL. If a data output has no data to return, it is simply not present in the dictionary of synchronized data returned by AVCaptureDataOutputSynchronizer's -dataOutputSynchronizer:didOutputSynchronizedData: delegate callback.
 */
@property(readonly) CMSampleBufferRef sampleBuffer;

/*!
 @property sampleBufferWasDropped
 @abstract
    YES if the sample buffer was dropped.
 
 @discussion
    AVCaptureVideoDataOutput has a delegate callback for dropped sample buffers. AVCaptureAudioDataOutput does not. Therefore, sampleBufferWasDropped may be YES for video, but never for audio.
 */
@property(readonly) BOOL sampleBufferWasDropped;

/*!
 @property droppedReason
 @abstract
    If sampleBufferWasDropped is YES, the reason for the drop, otherwise AVCaptureOutputDataDroppedReasonNone.
 
 @discussion
    AVCaptureOutputDataDroppedReasons are defined in AVCaptureOutputBase.h.
 */
@property(readonly) AVCaptureOutputDataDroppedReason droppedReason;

@end


#pragma mark - AVCaptureSynchronizedMetadataObjectData

@class AVCaptureSynchronizedMetadataObjectDataInternal;

/*!
 @class AVCaptureSynchronizedMetadataObjectData
 @abstract
    An concrete subclass of AVCaptureSynchronizedData representing the data delivered by an AVCaptureMetadataOutput.
 
 @discussion
    A single AVCaptureMetadataOutput may be configured to deliver multiple kinds of metadata objects (such as QRCodes and detected faces). AVCaptureSynchronizedMetadataObjectData's -metadataObjects array may contain multiple AVMetadataObject subclasses, depending on how the AVCaptureMetadataOutput was configured. All synchronized metadata objects share a common timestamp.
 */
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos) __WATCHOS_PROHIBITED __TVOS_PROHIBITED
@interface AVCaptureSynchronizedMetadataObjectData : AVCaptureSynchronizedData
{
@private
    AVCaptureSynchronizedMetadataObjectDataInternal *_internal;
}

/*!
 @property metadataObjects
 @abstract
    An array of AVMetadataObject subclasses.
 
 @discussion
    -metadataObjects is never nil. If no metadata objects are present for a given time, an empty array is returned.
 */
@property(readonly) NSArray<AVMetadataObject *> *metadataObjects;

@end


#pragma mark - AVCaptureSynchronizedDepthData

@class AVCaptureSynchronizedDepthDataInternal;

/*!
 @class AVCaptureSynchronizedDepthData
 @abstract
    An concrete subclass of AVCaptureSynchronizedData representing the data delivered by an AVCaptureDepthDataOutput.
 
 @discussion
    Depth data, like video, may be dropped if not serviced in a timely fashion.
 */
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos) __WATCHOS_PROHIBITED __TVOS_PROHIBITED
@interface AVCaptureSynchronizedDepthData : AVCaptureSynchronizedData
{
@private
    AVCaptureSynchronizedDepthDataInternal *_internal;
}

/*!
 @property depthData
 @abstract
    An instance of AVDepthData.
 
 @discussion
    If depthDataWasDropped is YES, the returned depthData was dropped before it could be delivered to you, and thus this AVDepthData is a shell containing format information and calibration data, but no actual pixel map data. This property is never nil. If a data output has no data to return, it is simply not present in the dictionary of synchronized data returned by AVCaptureDataOutputSynchronizer's -dataOutputSynchronizer:didOutputSynchronizedData: delegate callback.
 */
@property(readonly) AVDepthData *depthData;

/*!
 @property depthDataWasDropped
 @abstract
    YES if the depth data was dropped.
 
 @discussion
    If YES, inspect -droppedReason for the reason.
 */
@property(readonly) BOOL depthDataWasDropped;

/*!
 @property droppedReason
 @abstract
    If depthDataWasDropped is YES, the reason for the drop, otherwise AVCaptureOutputDataDroppedReasonNone.
 
 @discussion
    AVCaptureOutputDataDroppedReasons are defined in AVCaptureOutputBase.h.
 */
@property(readonly) AVCaptureOutputDataDroppedReason droppedReason;

@end

NS_ASSUME_NONNULL_END
