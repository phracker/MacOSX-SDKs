/*
	File:  AVAssetReader.h

	Framework:  AVFoundation
 
	Copyright 2010 Apple Inc. All rights reserved.

*/

#import <AVFoundation/AVBase.h>
#import <Foundation/Foundation.h>
#import <CoreMedia/CMTime.h>
#import <CoreMedia/CMTimeRange.h>
#import <CoreMedia/CMSampleBuffer.h>

@class AVAsset;
@class AVAssetReaderOutput;
@class AVAssetReaderInternal;

/*!
 @enum AVAssetReaderStatus
 @abstract
	These constants are returned by the AVAssetReader status property to indicate whether it can successfully read
	samples from its asset.

 @constant	 AVAssetReaderStatusUnknown
	Indicates that the status of the asset reader is not currently known.
 @constant	 AVAssetReaderStatusReading
	Indicates that the asset reader is successfully reading samples from its asset.
 @constant	 AVAssetReaderStatusCompleted
	Indicates that the asset reader has successfully read all of the samples in its time range.
 @constant	 AVAssetReaderStatusFailed
	Indicates that the asset reader can no longer read samples from its asset because of an error. The error is described
	by the value of the asset reader's error property.
 @constant	 AVAssetReaderStatusCancelled
	Indicates that the asset reader can no longer read samples because reading was canceled with the cancelReading method.
 */
enum {
    AVAssetReaderStatusUnknown = 0,
    AVAssetReaderStatusReading,
    AVAssetReaderStatusCompleted,
    AVAssetReaderStatusFailed,
    AVAssetReaderStatusCancelled,
};
typedef NSInteger AVAssetReaderStatus;

/*!
 @class AVAssetReader
 @abstract
	AVAssetReader provides services for obtaining media data from an asset.
 
 @discussion
	Instances of AVAssetReader read media data from an instance of AVAsset, whether the asset is file-based or represents
	an assembly of media data from multiple sources, as is the case with AVComposition.
	
	Clients of AVAssetReader can read data from specific tracks of an asset and in specific formats by adding concrete
	instances of AVAssetReaderOutput to an AVAssetReader instance.
	
	AVAssetReaderTrackOutput, a concrete subclass of AVAssetReaderOutput, can either read the track's media samples in
	the format in which they are stored by the asset or convert the media samples to a different format.
	
	AVAssetReaderAudioMixOutput mixes multiple audio tracks of the asset after reading them, while
	AVAssetReaderVideoCompositionOutput composites multiple video tracks after reading them.
 */
NS_CLASS_AVAILABLE(10_7, 4_1)
@interface AVAssetReader : NSObject
{
@private
	AVAssetReaderInternal		*_priv;
}

/*!
 @method assetReaderWithAsset:error:
 @abstract
	Returns an instance of AVAssetReader for reading media data from the specified asset.

 @param asset
	The asset from which media data is to be read.
 @param outError
	On return, if initialization of the AVAssetReader fails, points to an NSError describing the nature of the failure.
 @result An instance of AVAssetReader.
 */
+ (AVAssetReader *)assetReaderWithAsset:(AVAsset *)asset error:(NSError **)outError;

/*!
 @method initWithAsset:error:
 @abstract
	Creates an instance of AVAssetReader for reading media data from the specified asset.

 @param asset
	The asset from which media data is to be read.
 @param outError
	On return, if initialization of the AVAssetReader fails, points to an NSError describing the nature of the failure.
 @result
	An instance of AVAssetReader.
 */
- (id)initWithAsset:(AVAsset *)asset error:(NSError **)outError;

/*!
 @property asset
 @abstract
	The asset from which the receiver's outputs read sample buffers.

 @discussion
	The value of this property is an AVAsset. Concrete instances of AVAssetReader that are created with specific
	AVAssetTrack instances must obtain those tracks from the asset returned by this property.
 */
@property (nonatomic, retain, readonly) AVAsset *asset;

/*!
 @property status
 @abstract
	The status of reading sample buffers from the receiver's asset.

 @discussion
	The value of this property is an AVAssetReaderStatus that indicates whether reading is in progress, has completed
	successfully, has been canceled, or has failed. Clients of AVAssetReaderOutput objects should check the value of this
	property after -[AVAssetReaderOutput copyNextSampleBuffer] returns NULL to determine why no more samples could be
	read. This property is thread safe.
 */
@property (readonly) AVAssetReaderStatus status;

/*!
 @property error
 @abstract
	If the receiver's status is AVAssetReaderStatusFailed, this describes the error that caused the failure.

 @discussion
	The value of this property is an NSError that describes what caused the receiver to no longer be able to read its
	asset. If the receiver's status is not AVAssetReaderStatusFailed, the value of this property is nil. This property
	is thread safe.
 */
@property (readonly) NSError *error;

/*!
 @property timeRange
 @abstract
	Specifies a range of time that may limit the temporal portion of the receiver's asset from which media data will be read.

 @discussion
	The intersection of the value of timeRange and CMTimeRangeMake(kCMTimeZero, asset.duration) will determine the time range
	of the asset from which media data will be read. The default value of timeRange is CMTimeRangeMake(kCMTimeZero, kCMTimePositiveInfinity).
	
	This property cannot be set after reading has started.
 */
@property (nonatomic) CMTimeRange timeRange;

/*!
 @property outputs
 @abstract
	The outputs from which clients of receiver can read media data.

 @discussion
	The value of this property is an NSArray containing concrete instances of AVAssetReaderOutput. Outputs can be added
	to the receiver using the addOutput: method.
 */
@property (nonatomic, readonly) NSArray *outputs;

/*!
 @method canAddOutput:
 @abstract
	Tests whether an output can be added to the receiver.

 @param output
	The AVAssetReaderOutput object to be tested.
 @result
	A BOOL indicating whether the output can be added to the receiver.

 @discussion
	An output that reads from a track of an asset other than the asset used to initialize the receiver cannot be added.
 */
- (BOOL)canAddOutput:(AVAssetReaderOutput *)output;

/*!
 @method addOutput:
 @abstract
	Adds an output to the receiver.

 @param output
	The AVAssetReaderOutput object to be added.

 @discussion
	Outputs are created with a reference to one or more AVAssetTrack objects. These tracks must be owned by the asset
	returned by the receiver's asset property.
	
	Outputs cannot be added after reading has started.
 */
- (void)addOutput:(AVAssetReaderOutput *)output;

/*!
 @method startReading
 @abstract
	Prepares the receiver for reading sample buffers from the asset.

 @result
	A BOOL indicating whether reading could be started.
 
 @discussion
	This method validates the entire collection of settings for outputs for tracks, for audio mixing, and for video
	composition and initiates reading from the receiver's asset.
	
	If this method returns NO, clients can determine the nature of the failure by checking the value of the status and
	error properties.
 */
- (BOOL)startReading;

/*!
 @method cancelReading
 @abstract
	Cancels any background work and prevents the receiver's outputs from reading more samples.

 @discussion
	Clients that want to stop reading samples from the receiver before reaching the end of its time range should call
	this method to stop any background read ahead operations that the may have been in progress.
 
	This method should not be called concurrently with any calls to -[AVAssetReaderOutput copyNextSampleBuffer].
 */
- (void)cancelReading;

@end
