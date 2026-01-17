/*
    File:  AVCaptureDepthDataOutput.h
 
    Framework:  AVFoundation
 
    Copyright 2016-2017 Apple Inc. All rights reserved.
*/

#import <AVFoundation/AVMediaFormat.h>
#import <AVFoundation/AVCaptureOutputBase.h>

NS_ASSUME_NONNULL_BEGIN

#pragma mark AVCaptureDepthDataOutput

@class AVDepthData;

@class AVCaptureDepthDataOutputInternal;
@protocol AVCaptureDepthDataOutputDelegate;

/*!
 @class AVCaptureDepthDataOutput
 @abstract
    AVCaptureDepthDataOutput is a concrete subclass of AVCaptureOutput that can be used to process depth data in a streaming fashion.
 
 @discussion
    Instances of AVCaptureDepthDataOutput capture AVDepthData objects expressing disparity/depth. Applications can access the frames with the captureOutput:didOutputDepthData:fromConnection: delegate method.
 
    AVCaptureDepthDataOutput always provides depth data in the format expressed by its source's -[AVCaptureDevice activeDepthDataFormat] property. If you wish to receive depth data in another format, you may choose from the -[AVCaptureDevice activeFormat]'s -[AVCaptureDeviceFormat supportedDepthDataFormats], and set it using -[AVCaptureDevice setActiveDepthDataFormat:].
 */
NS_CLASS_AVAILABLE_IOS(11_0) __TVOS_PROHIBITED __WATCHOS_PROHIBITED
@interface AVCaptureDepthDataOutput : AVCaptureOutput
{
@private
    AVCaptureDepthDataOutputInternal *_internal;
}

- (instancetype)init;

+ (instancetype)new;

/*!
 @method setDelegate:queue:
 @abstract
    Sets the receiver's delegate that receives captured depth data and the dispatch queue on which the delegate is called.
 
 @param delegate
    An object conforming to the AVCaptureDepthDataOutputDelegate protocol that receives depth data in a streaming fashion.
 @param callbackQueue
    A dispatch queue on which all delegate methods are called.
 
 @discussion
    The depth data output vends captured depth data to its delegate using the methods specified in the AVCaptureDepthOutputDelegate protocol. All delegate methods are called on the specified dispatch queue. If the callback queue is blocked when new depth data is captured, that depth data is automatically dropped at a time determined by the value of the alwaysDiscardsLateDepthData property. This allows clients to process existing depth data on the same queue without having to manage the potential memory usage increases that would otherwise occur when that processing is unable to keep up with the rate of incoming depth data.
 
    Clients who need to minimize the chances of depth data being dropped should provide a dedicated queue and not share it with other data outputs. Processing of depth data may be deferred to another queue, but beware that the depth data pixel buffer maps may come from a finite buffer pool, which may be starved if your deferred processing fails to keep up.
 
    A serial dispatch queue must be used to guarantee that depth data will be delivered in order. The callbackQueue parameter may not be NULL, except when setting the delegate to nil.
 */
- (void)setDelegate:(id<AVCaptureDepthDataOutputDelegate>)delegate callbackQueue:(dispatch_queue_t)callbackQueue;

/*!
 @property delegate
 @abstract
    The receiver's delegate.
 
 @discussion
    The value of this property is an object conforming to the AVCaptureDepthDataOutputDelegate protocol that receives depth data as it is captured. The delegate is set using the setDelegate:queue: method.
 */
@property(nonatomic, readonly) id<AVCaptureDepthDataOutputDelegate> delegate;

/*!
 @property delegateCallbackQueue
 @abstract
    The dispatch queue on which all delegate methods are called.
 
 @discussion
    The value of this property is a dispatch_queue_t. The queue is set using the setDelegate:queue: method.
 */
@property(nonatomic, readonly) dispatch_queue_t delegateCallbackQueue;

/*!
 @property alwaysDiscardsLateDepthData
 @abstract
    Specifies whether the receiver should always discard any depth data that is not processed before the next depth data is captured.
 
 @discussion
    When the value of this property is YES, the receiver will immediately discard depth data that are captured while the depthDataCallbackQueue is blocked. When the value of this property is NO, delegates will be allowed more time to process old depth data before new depth data are discarded, but application memory usage may increase as a result. The default value is YES.
 */
@property(nonatomic) BOOL alwaysDiscardsLateDepthData;

/*!
 @property filteringEnabled
 @abstract
    Specifies whether the depth data output should filter depth data to smooth out noise and fill invalid values.

 @discussion
    When the value of this property is YES, the receiver temporally filters the stream of AVDepthData objects to reduce noise, as well as fill invalid values. Invalid values (NaN) may be present in AVDepthData pixel buffer maps due to factors such as low light or lens occlusion. When filtering is enabled, the depth data output interpolates missing depth data values. Filtering should be disabled if you desire the raw depth data values. The default value is YES.
 */
@property(nonatomic, getter=isFilteringEnabled) BOOL filteringEnabled;

@end


/*!
 @protocol AVCaptureDepthDataOutputDelegate
 @abstract
    Defines an interface for delegates of AVCaptureDepthDataOutput to receive captured depth data and be notified of late depth data that were dropped.
 */
NS_AVAILABLE_IOS(11_0) __TVOS_PROHIBITED __WATCHOS_PROHIBITED
@protocol AVCaptureDepthDataOutputDelegate <NSObject>

@optional

/*!
 @method depthDataOutput:didOutputDepthData:timestamp:connection:
 @abstract
    Called whenever an AVCaptureDepthDataOutput instance outputs a new depth data object.
 
 @param output
    The AVCaptureDepthDataOutput instance vending the depth data.
 @param depthData
    An AVDepthData object containing the depth/disparity data.
 @param timestamp
    A CMTime indicating when the depth data was captured.
 @param connection
    The AVCaptureConnection through which the depth data is received.
 
 @discussion
    The delegate receives this message whenever the depth data output captures and outputs a new depth data object. This method is called on the dispatch queue specified by the output's delegateCallbackQueue property. This method is called frequently. Care must be taken to process the depth data quickly in order to prevent dropped depth data.
 
    Clients that need to reference the AVDepthData object outside of the scope of this method must retain it and then release it when they are finished with it (in a MRR app).
 
    Note that to maintain optimal performance, AVDepthData pixel buffer maps may be backed by a finite memory pool. If AVDepthData objects are held onto for too long, capture inputs will no longer be able to copy new depth data into memory, resulting in droppage. If your application is causing depth data drops by holding on to provided depth data objects for too long, consider copying the pixel buffer map data into a new pixel buffer so that the AVDepthData backing memory can be reused more quickly.
 */
- (void)depthDataOutput:(AVCaptureDepthDataOutput *)output didOutputDepthData:(AVDepthData *)depthData timestamp:(CMTime)timestamp connection:(AVCaptureConnection *)connection;

/*!
 @method depthDataOutput:didDropDepthData:timestamp:connection:reason:
 @abstract
    Called once for each depth data that is discarded.
 
 @param output
    The AVCaptureDepthDataOutput instance that dropped the depth data.
 @param depthData
    A depth data object containing information about the dropped depth, such as its native depth type. This depth data object produces nil CVPixelBuffers for depth / disparity as it has no backing depth map.
 @param timestamp
    A CMTime indicating when the depth data was captured.
 @param connection
    The AVCaptureConnection from which the dropped depth data object was received.
 @param reason
    The reason the depth data object was dropped.
 
 @discussion
    Delegates receive this message whenever a depth data object is dropped. This method is called once for each dropped depth data. The object passed to this delegate method will contain a shell of an AVDepthData that contains no actual depth data backing pixel buffer, as well as a presentation time stamp and a reason for the drop. This method will be called on the dispatch queue specified by the output's delegateCallbackQueue property. Because this method is called on the same dispatch queue that outputs depth data, it must be efficient to prevent further capture performance problems, such as additional drops.
  */
- (void)depthDataOutput:(AVCaptureDepthDataOutput *)output didDropDepthData:(AVDepthData *)depthData timestamp:(CMTime)timestamp connection:(AVCaptureConnection *)connection reason:(AVCaptureOutputDataDroppedReason)reason;

@end

NS_ASSUME_NONNULL_END
