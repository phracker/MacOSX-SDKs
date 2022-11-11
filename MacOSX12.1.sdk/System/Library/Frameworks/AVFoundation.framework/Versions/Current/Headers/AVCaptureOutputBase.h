#if !__has_include(<AVFCapture/AVCaptureOutputBase.h>)
/*
    File:  AVCaptureOutputBase.h
 
    Framework:  AVFoundation
 
    Copyright 2017-2021 Apple Inc. All rights reserved.
*/

#import <AVFoundation/AVBase.h>
#import <AVFoundation/AVMediaFormat.h>
#import <Foundation/Foundation.h>
#import <AVFoundation/AVCaptureSession.h>

NS_ASSUME_NONNULL_BEGIN

#pragma mark AVCaptureOutput

@class AVMetadataObject;
@class AVCaptureOutputInternal;

/*!
 @class AVCaptureOutput
 @abstract
    AVCaptureOutput is an abstract class that defines an interface for an output destination of an AVCaptureSession.
 
 @discussion
    AVCaptureOutput provides an abstract interface for connecting capture output destinations, such as files and video previews, to an AVCaptureSession.

    An AVCaptureOutput can have multiple connections represented by AVCaptureConnection objects, one for each stream of media that it receives from an AVCaptureInput. An AVCaptureOutput does not have any connections when it is first created. When an output is added to an AVCaptureSession, connections are created that map media data from that session's inputs to its outputs.

    Concrete AVCaptureOutput instances can be added to an AVCaptureSession using the -[AVCaptureSession addOutput:] and -[AVCaptureSession addOutputWithNoConnections:] methods.
 */
API_AVAILABLE(macos(10.7), ios(4.0), macCatalyst(14.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED
@interface AVCaptureOutput : NSObject
{
@private
    AVCaptureOutputInternal *_outputInternal;
}

AV_INIT_UNAVAILABLE

/*!
 @property connections
 @abstract
    The connections that describe the flow of media data to the receiver from AVCaptureInputs.

 @discussion
    The value of this property is an NSArray of AVCaptureConnection objects, each describing the mapping between the receiver and the AVCaptureInputPorts of one or more AVCaptureInputs.
 */
@property(nonatomic, readonly) NSArray<AVCaptureConnection *> *connections;

/*!
 @method connectionWithMediaType:
 @abstract
    Returns the first connection in the connections array with an inputPort of the specified mediaType.

 @param mediaType
    An AVMediaType constant from AVMediaFormat.h, e.g. AVMediaTypeVideo.

 @discussion
    This convenience method returns the first AVCaptureConnection in the receiver's connections array that has an AVCaptureInputPort of the specified mediaType. If no connection with the specified mediaType is found, nil is returned.
 */
- (nullable AVCaptureConnection *)connectionWithMediaType:(AVMediaType)mediaType API_AVAILABLE(ios(5.0), macCatalyst(14.0)) API_UNAVAILABLE(tvos);

/*!
 @method transformedMetadataObjectForMetadataObject:connection:
 @abstract
    Converts an AVMetadataObject's visual properties to the receiver's coordinates.

 @param metadataObject
    An AVMetadataObject originating from the same AVCaptureInput as the receiver.
 @param connection
    The receiver's connection whose AVCaptureInput matches that of the metadata object to be converted.
 @result
    An AVMetadataObject whose properties are in output coordinates.

 @discussion
    AVMetadataObject bounds may be expressed as a rect where {0,0} represents the top left of the picture area, and {1,1} represents the bottom right on an unrotated picture. Face metadata objects likewise express yaw and roll angles with respect to an unrotated picture. -transformedMetadataObjectForMetadataObject:connection: converts the visual properties in the coordinate space of the supplied AVMetadataObject to the coordinate space of the receiver. The conversion takes orientation, mirroring, and scaling into consideration. If the provided metadata object originates from an input source other than the preview layer's, nil will be returned.
 
    If an AVCaptureVideoDataOutput instance's connection's videoOrientation or videoMirrored properties are set to non-default values, the output applies the desired mirroring and orientation by physically rotating and or flipping sample buffers as they pass through it. AVCaptureStillImageOutput, on the other hand, does not physically rotate its buffers. It attaches an appropriate kCGImagePropertyOrientation number to captured still image buffers (see ImageIO/CGImageProperties.h) indicating how the image should be displayed on playback. Likewise, AVCaptureMovieFileOutput does not physically apply orientation/mirroring to its sample buffers -- it uses a QuickTime track matrix to indicate how the buffers should be rotated and/or flipped on playback.
 
    transformedMetadataObjectForMetadataObject:connection: alters the visual properties of the provided metadata object to match the physical rotation / mirroring of the sample buffers provided by the receiver through the indicated connection. I.e., for video data output, adjusted metadata object coordinates are rotated/mirrored. For still image and movie file output, they are not.
 */
- (nullable AVMetadataObject *)transformedMetadataObjectForMetadataObject:(AVMetadataObject *)metadataObject connection:(AVCaptureConnection *)connection API_AVAILABLE(macos(10.15), ios(6.0), macCatalyst(14.0)) API_UNAVAILABLE(tvos);

/*!
 @method metadataOutputRectOfInterestForRect:
 @abstract
    Converts a rectangle in the receiver's coordinate space to a rectangle of interest in the coordinate space of an AVCaptureMetadataOutput whose capture device is providing input to the receiver.
 
 @param rectInOutputCoordinates
    A CGRect in the receiver's coordinates.
 @result
    A CGRect in the coordinate space of the metadata output whose capture device is providing input to the receiver.
 
 @discussion
    AVCaptureMetadataOutput rectOfInterest is expressed as a CGRect where {0,0} represents the top left of the picture area, and {1,1} represents the bottom right on an unrotated picture. This convenience method converts a rectangle in the coordinate space of the receiver to a rectangle of interest in the coordinate space of an AVCaptureMetadataOutput whose AVCaptureDevice is providing input to the receiver. The conversion takes orientation, mirroring, and scaling into consideration. See -transformedMetadataObjectForMetadataObject:connection: for a full discussion of how orientation and mirroring are applied to sample buffers passing through the output.
 */
- (CGRect)metadataOutputRectOfInterestForRect:(CGRect)rectInOutputCoordinates API_AVAILABLE(macos(10.15), ios(7.0), macCatalyst(14.0)) API_UNAVAILABLE(tvos);

/*!
 @method rectForMetadataOutputRectOfInterest:
 @abstract
    Converts a rectangle of interest in the coordinate space of an AVCaptureMetadataOutput whose capture device is providing input to the receiver to a rectangle in the receiver's coordinates.
 
 @param rectInMetadataOutputCoordinates
    A CGRect in the coordinate space of the metadata output whose capture device is providing input to the receiver.
 @result
    A CGRect in the receiver's coordinates.
 
 @discussion
    AVCaptureMetadataOutput rectOfInterest is expressed as a CGRect where {0,0} represents the top left of the picture area, and {1,1} represents the bottom right on an unrotated picture. This convenience method converts a rectangle in the coordinate space of an AVCaptureMetadataOutput whose AVCaptureDevice is providing input to the coordinate space of the receiver. The conversion takes orientation, mirroring, and scaling into consideration. See -transformedMetadataObjectForMetadataObject:connection: for a full discussion of how orientation and mirroring are applied to sample buffers passing through the output.
 */
- (CGRect)rectForMetadataOutputRectOfInterest:(CGRect)rectInMetadataOutputCoordinates API_AVAILABLE(macos(10.15), ios(7.0), macCatalyst(14.0)) API_UNAVAILABLE(tvos);

@end


/*!
 @enum AVCaptureOutputDataDroppedReason
 @abstract
    Constants indicating the reason a capture data output dropped data.

 @constant AVCaptureOutputDataDroppedReasonNone
    No data was dropped.
 @constant AVCaptureOutputDataDroppedReasonLateData
    Data was dropped because alwaysDiscardsLate{VideoFrames | DepthData} is YES and the client was still processing previous data when the current data needed to be delivered.
 @constant AVCaptureOutputDataDroppedReasonOutOfBuffers
    Data was dropped because its pool of buffers ran dry. This is usually indicative that the client is holding onto data objects too long.
 @constant AVCaptureOutputDataDroppedReasonDiscontinuity
    Data was dropped because the device providing the data experienced a discontinuity, and an unknown number of data objects have been lost. This condition is typically caused by the system being too busy.
 */
typedef NS_ENUM(NSInteger, AVCaptureOutputDataDroppedReason) {
    AVCaptureOutputDataDroppedReasonNone          = 0,
    AVCaptureOutputDataDroppedReasonLateData      = 1,
    AVCaptureOutputDataDroppedReasonOutOfBuffers  = 2,
    AVCaptureOutputDataDroppedReasonDiscontinuity = 3,
} API_AVAILABLE(macos(10.15), ios(11.0), macCatalyst(14.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

NS_ASSUME_NONNULL_END

#else
#import <AVFCapture/AVCaptureOutputBase.h>
#endif
