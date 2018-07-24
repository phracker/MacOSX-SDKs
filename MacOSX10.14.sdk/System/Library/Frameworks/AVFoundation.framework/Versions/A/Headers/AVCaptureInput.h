/*
    File:  AVCaptureInput.h
 
    Framework:  AVFoundation
 
    Copyright 2010-2018 Apple Inc. All rights reserved.
*/

#import <AVFoundation/AVBase.h>
#import <AVFoundation/AVMediaFormat.h>
#import <Foundation/Foundation.h>
#import <CoreMedia/CMFormatDescription.h>
#import <CoreMedia/CMSync.h>
#if TARGET_OS_OSX
    #import <CoreGraphics/CGDirectDisplay.h>
#endif

NS_ASSUME_NONNULL_BEGIN

#pragma mark AVCaptureInput

@class AVCaptureInputPort;
@class AVCaptureInputInternal;
@class AVTimedMetadataGroup;

/*!
 @class AVCaptureInput
 @abstract
    AVCaptureInput is an abstract class that provides an interface for connecting capture input sources to an AVCaptureSession.
 
 @discussion
    Concrete instances of AVCaptureInput representing input sources such as cameras can be added to instances of AVCaptureSession using the -[AVCaptureSession addInput:] method. An AVCaptureInput vends one or more streams of media data. For example, input devices can provide both audio and video data. Each media stream provided by an input is represented by an AVCaptureInputPort object. Within a capture session, connections are made between AVCaptureInput instances and AVCaptureOutput instances via AVCaptureConnection objects that define the mapping between a set of AVCaptureInputPort objects and a single AVCaptureOutput.
 */
API_AVAILABLE(macos(10.7), ios(4.0)) __WATCHOS_PROHIBITED __TVOS_PROHIBITED
@interface AVCaptureInput : NSObject
{
@private
    AVCaptureInputInternal *_inputInternal;
}

AV_INIT_UNAVAILABLE

/*!
 @property ports
 @abstract
    The ports owned by the receiver.
 
 @discussion
    The value of this property is an array of AVCaptureInputPort objects, each exposing an interface to a single stream of media data provided by an input.
 */
@property(nonatomic, readonly) NSArray<AVCaptureInputPort *> *ports;

@end


/*!
 @constant AVCaptureInputPortFormatDescriptionDidChangeNotification
 @abstract
    This notification is posted when the value of an AVCaptureInputPort instance's formatDescription property changes.
 
 @discussion
    The notification object is the AVCaptureInputPort instance whose format description changed.
 */
AVF_EXPORT NSString *const AVCaptureInputPortFormatDescriptionDidChangeNotification API_AVAILABLE(macos(10.7), ios(4.0)) __WATCHOS_PROHIBITED __TVOS_PROHIBITED;


#pragma mark - AVCaptureInputPort

@class AVCaptureInputPortInternal;

/*!
 @class AVCaptureInputPort
 @abstract
    An AVCaptureInputPort describes a single stream of media data provided by an AVCaptureInput and provides an interface for connecting that stream to AVCaptureOutput instances via AVCaptureConnection.
 
 @discussion
    Instances of AVCaptureInputPort cannot be created directly. An AVCaptureInput exposes its input ports via its ports property. Input ports provide information about the format of their media data via the mediaType and formatDescription properties, and allow clients to control the flow of data via the enabled property. Input ports are used by an AVCaptureConnection to define the mapping between inputs and outputs in an AVCaptureSession.
 */
API_AVAILABLE(macos(10.7), ios(4.0)) __WATCHOS_PROHIBITED __TVOS_PROHIBITED
@interface AVCaptureInputPort : NSObject
{
@private
    AVCaptureInputPortInternal *_internal;
}

AV_INIT_UNAVAILABLE

/*!
 @property input
 @abstract
    The input that owns the receiver.
 
 @discussion
    The value of this property is an AVCaptureInput instance that owns the receiver.
 */
@property(nonatomic, readonly) AVCaptureInput *input;

/*!
 @property mediaType
 @abstract
    The media type of the data provided by the receiver.
 
 @discussion
    The value of this property is a constant describing the type of media, such as AVMediaTypeVideo or AVMediaTypeAudio, provided by the receiver. Media type constants are defined in AVMediaFormat.h.
 */
@property(nonatomic, readonly) AVMediaType mediaType;

/*!
 @property formatDescription
 @abstract
    The format of the data provided by the receiver.
 
 @discussion
    The value of this property is a CMFormatDescription that describes the format of the media data currently provided by the receiver. Clients can be notified of changes to the format by observing the AVCaptureInputPortFormatDescriptionDidChangeNotification.
 */
@property(nonatomic, readonly, nullable) __attribute__((NSObject)) CMFormatDescriptionRef formatDescription;

/*!
 @property enabled
 @abstract
    Whether the receiver should provide data.
 
 @discussion
    The value of this property is a BOOL that determines whether the receiver should provide data to outputs when a session is running. Clients can set this property to fine tune which media streams from a given input will be used during capture. The default value is YES.
 */
@property(nonatomic, getter=isEnabled) BOOL enabled;

/*!
 @property clock
 @abstract
    Provides access to the "native" clock used by the input port.
 
 @discussion
    The clock is read-only.
 */
@property(nonatomic, readonly, nullable) __attribute__((NSObject)) CMClockRef clock API_AVAILABLE(macos(10.9), ios(7.0));

@end


#pragma mark - AVCaptureDeviceInput

@class AVCaptureDevice;
@class AVCaptureDeviceInputInternal;

/*!
 @class AVCaptureDeviceInput
 @abstract
    AVCaptureDeviceInput is a concrete subclass of AVCaptureInput that provides an interface for capturing media from an AVCaptureDevice.
 
 @discussion
    Instances of AVCaptureDeviceInput are input sources for AVCaptureSession that provide media data from devices connected to the system, represented by instances of AVCaptureDevice.
 */
API_AVAILABLE(macos(10.7), ios(4.0)) __WATCHOS_PROHIBITED __TVOS_PROHIBITED
@interface AVCaptureDeviceInput : AVCaptureInput
{
@private
    AVCaptureDeviceInputInternal *_internal;
}

/*!
 @method deviceInputWithDevice:error:
 @abstract
    Returns an AVCaptureDeviceInput instance that provides media data from the given device.
 
 @param device
    An AVCaptureDevice instance to be used for capture.
 @param outError
    On return, if the given device cannot be used for capture, points to an NSError describing the problem.
 @result
    An AVCaptureDeviceInput instance that provides data from the given device, or nil, if the device could not be used for capture.
 
 @discussion
    This method returns an instance of AVCaptureDeviceInput that can be used to capture data from an AVCaptureDevice in an AVCaptureSession. This method attempts to open the device for capture, taking exclusive control of it if necessary. If the device cannot be opened because it is no longer available or because it is in use, for example, this method returns nil, and the optional outError parameter points to an NSError describing the problem.
 */
+ (nullable instancetype)deviceInputWithDevice:(AVCaptureDevice *)device error:(NSError * _Nullable * _Nullable)outError;

/*!
 @method initWithDevice:error:
 @abstract
    Creates an AVCaptureDeviceInput instance that provides media data from the given device.
 
 @param device
    An AVCaptureDevice instance to be used for capture.
 @param outError
    On return, if the given device cannot be used for capture, points to an NSError describing the problem.
 @result
    An AVCaptureDeviceInput instance that provides data from the given device, or nil, if the device could not be used for capture.
 
 @discussion
    This method creates an instance of AVCaptureDeviceInput that can be used to capture data from an AVCaptureDevice in an AVCaptureSession. This method attempts to open the device for capture, taking exclusive control of it if necessary. If the device cannot be opened because it is no longer available or because it is in use, for example, this method returns nil, and the optional outError parameter points to an NSError describing the problem.
 */
- (nullable instancetype)initWithDevice:(AVCaptureDevice *)device error:(NSError * _Nullable * _Nullable)outError;

/*!
 @property device
 @abstract
    The device from which the receiver provides data.
 
 @discussion
    The value of this property is the AVCaptureDevice instance that was used to create the receiver.
 */
@property(nonatomic, readonly) AVCaptureDevice *device;

/*!
 @property unifiedAutoExposureDefaultsEnabled
 @abstract
    Specifies whether the source device should use the same default auto exposure behaviors for -[AVCaptureSession setSessionPreset:] and -[AVCaptureDevice setActiveFormat:].
 
 @discussion
    AVCaptureDevice's activeFormat property may be set two different ways. 1) You set it directly using one of the formats in the device's -formats array, or 2) the AVCaptureSession sets it on your behalf when you set the AVCaptureSession's sessionPreset property. Depending on the device and format, the default auto exposure behavior may be configured differently when you use one method or the other, resulting in non-uniform auto exposure behavior. Auto exposure defaults include min frame rate, max frame rate, and max exposure duration. If you wish to ensure that consistent default behaviors are applied to the device regardless of the API you use to configure the activeFormat, you may set the device input's unifiedAutoExposureDefaultsEnabled property to YES. Default value for this property is NO.
 
    Note that if you manually set the device's min frame rate, max frame rate, or max exposure duration, your custom values will override the device defaults regardless of whether you've set this property to YES.
 */
@property(nonatomic) BOOL unifiedAutoExposureDefaultsEnabled API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(macos, tvos, watchos);

@end


#pragma mark - AVCaptureScreenInput

@class AVCaptureScreenInputInternal;

/*!
 @class AVCaptureScreenInput
 @abstract
    AVCaptureScreenInput is a concrete subclass of AVCaptureInput that provides an interface for capturing media from a screen or portion thereof.
 
 @discussion
    Instances of AVCaptureScreenInput are input sources for AVCaptureSession that provide media data from one of the screens connected to the system, represented by CGDirectDisplayIDs.
 */
API_AVAILABLE(macos(10.7)) API_UNAVAILABLE(ios, watchos, tvos)
@interface AVCaptureScreenInput : AVCaptureInput
{
@private
    AVCaptureScreenInputInternal *_internal;
}

/*!
 @method init
 @abstract
    Creates an AVCaptureScreenInput instance that provides media data from the main display.
 
 @discussion
    This method creates an instance of AVCaptureScreenInput using the main display whose id is returned from CGMainDisplayID().
 */
- (instancetype)init;

+ (instancetype)new;

#if TARGET_OS_OSX

/*!
 @method initWithDisplayID:
 @abstract
    Creates an AVCaptureScreenInput instance that provides media data from the given display.
 
 @param displayID
    The id of the display from which to capture video. CGDirectDisplayID is defined in <CoreGraphics/CGDirectDisplay.h>
 @result
    An AVCaptureScreenInput instance that provides data from the given screen, or nil, if the screen could not be used for capture.
 
 @discussion
    This method creates an instance of AVCaptureScreenInput that can be used to capture data from a display in an AVCaptureSession. This method validates the displayID. If the display cannot be used because it is not available on the system, for example, this method returns nil.
 */
- (nullable instancetype)initWithDisplayID:(CGDirectDisplayID)displayID;

#endif // TARGET_OS_OSX

/*!
 @property minFrameDuration
 @abstract
    A property indicating the screen input's minimum frame duration.
 
 @discussion
    An AVCaptureScreenInput's minFrameDuration is the reciprocal of its maximum frame rate. This property may be used to request a maximum frame rate at which the input produces video frames. The requested rate may not be achievable due to overall bandwidth, so actual frame rates may be lower.
 */
@property(nonatomic) CMTime minFrameDuration;

/*!
 @property cropRect
 @abstract
    A property indicating the bounding rectangle of the screen area to be captured in pixels.
 
 @discussion
    By default, AVCaptureScreenInput captures the entire area of the displayID with which it is associated. To limit the capture rectangle to a subsection of the screen, set the cropRect property, which defines a smaller section of the screen in the screen's coordinate system. The origin (0,0) is the bottom-left corner of the screen.
 */
@property(nonatomic) CGRect cropRect;

/*!
 @property scaleFactor
 @abstract
    A property indicating the factor by which video buffers captured from the screen are to be scaled.
 
 @discussion
    By default, AVCaptureScreenInput captures the video buffers from the display at a scale factor of 1.0 (no scaling). Set this property to scale the buffers by a given factor. For instance, a 320x240 capture area with a scaleFactor of 2.0f produces video buffers at 640x480.
 */
@property(nonatomic) CGFloat scaleFactor;

/*!
 @property capturesMouseClicks
 @abstract
    A property indicating whether mouse clicks should be highlighted in the captured output.
 
 @discussion
    By default, AVCaptureScreenInput does not highlight mouse clicks in its captured output. If this property is set to YES, mouse clicks are highlighted (a circle is drawn around the mouse for the duration of the click) in the captured output.
 */
@property(nonatomic) BOOL capturesMouseClicks;

/*!
 @property capturesCursor
 @abstract
    A property indicating whether the cursor should be rendered to the captured output.
 
 @discussion
    By default, AVCaptureScreenInput draws the cursor in its captured output. If this property is set to NO, the captured output contains only the windows on the screen. Cursor is omitted. Note that cursor position and mouse button state at the time of capture is preserved in CMSampleBuffers emitted from AVCaptureScreenInput. See the inline documentation for kCMIOSampleBufferAttachmentKey_MouseAndKeyboardModifiers in <CoreMediaIO/CMIOSampleBuffer.h>
 */
@property(nonatomic) BOOL capturesCursor API_AVAILABLE(macos(10.8));

/*!
 @property removesDuplicateFrames
 @abstract
    A property indicating whether duplicate frames should be removed by the input.
 
 @discussion
    If this property is set to YES, AVCaptureScreenInput performs frame differencing and when it detects duplicate frames, it drops them. If set to NO, the captured output receives all frames from the input. Prior to 10.9 this value defaulted to YES. In 10.9 and later, it defaults to NO, as modern platforms support frame differencing in hardware-based encoders.
 
    As of 10.10, this property has been deprecated and is ignored. Clients wishing to re-create this functionality can use an AVCaptureVideoDataOutput and compare frame contents in their own code. If they wish to write a movie file, they can then pass the unique frames to an AVAssetWriterInput.
 */
@property(nonatomic) BOOL removesDuplicateFrames API_DEPRECATED("No longer supported.", macos(10.8, 10.10));

@end


#pragma mark - AVCaptureMetadataInput

@class AVCaptureMetadataInputInternal;

/*!
 @class AVCaptureMetadataInput
 @abstract
    AVCaptureMetadataInput is a concrete subclass of AVCaptureInput that provides a way for clients to supply AVMetadataItems to an AVCaptureSession.
 
 @discussion
    Instances of AVCaptureMetadataInput are input sources for AVCaptureSession that provide AVMetadataItems to an AVCaptureSession. AVCaptureMetadataInputs present one and only one AVCaptureInputPort, which currently may only be connected to an AVCaptureMovieFileOutput. The metadata supplied over the input port is provided by the client, and must conform to a client-supplied CMFormatDescription. The AVMetadataItems are supplied in an AVTimedMetadataGroup.
 */
API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos) __WATCHOS_PROHIBITED __TVOS_PROHIBITED
@interface AVCaptureMetadataInput : AVCaptureInput
{
@private
    AVCaptureMetadataInputInternal *_internal;
}

/*!
 @method metadataInputWithFormatDescription:clock:
 @abstract
    Returns an AVCaptureMetadataInput instance that allows a client to provide AVTimedMetadataGroups to an AVCaptureSession.
 
 @param desc
    A CMFormatDescription that defines the metadata to be supplied by the client. Throws an NSInvalidArgumentException if NULL is passed.
 @param clock
    A CMClock that provided the timebase for the supplied samples. Throws an NSInvalidArgumentException if NULL is passed.
 @result
    An AVCaptureMetadataInput instance.
 
 @discussion
    This method returns an instance of AVCaptureMetadataInput that can be used to capture AVTimedMetadataGroups supplied by the client to an AVCaptureSession.
 */
+ (instancetype)metadataInputWithFormatDescription:(CMMetadataFormatDescriptionRef)desc clock:(CMClockRef)clock;

/*!
 @method initWithFormatDescription:clock:
 @abstract
    Creates an AVCaptureMetadataInput instance that allows a client to provide AVTimedMetadataGroups to an AVCaptureSession.
 
 @param desc
    A CMFormatDescription that defines the metadata to be supplied by the client. Throws NSInvalidArgumentException if NULL is passed.
 @param clock
    A CMClock that provided the timebase for the supplied samples. Throws NSInvalidArgumentException if NULL is passed.
 @result
    An AVCaptureMetadataInput instance, or nil, if the device could not be used for capture.
 
 @discussion
    This method creates an instance of AVCaptureMetadataInput that can be used to capture AVTimedMetadataGroups supplied by the client to an AVCaptureSession.
 */
- (instancetype)initWithFormatDescription:(CMMetadataFormatDescriptionRef)desc clock:(CMClockRef)clock;

/*!
 @method appendTimedMetadataGroup:
 @abstract
    Provides metadata to the AVCaptureSession.
 
 @param metadata
    An AVTimedMetadataGroup of metadata. Will throw an exception if nil. In order to denote a period of no metadata, an empty AVTimedMetadataGroup should be passed.
 
 @discussion
    The provided AVTimedMetadataGroup will be provided to the AVCaptureSession. The group's presentation timestamp is expressed in the context of the clock supplied to the initializer. It is not required that the AVTimedMetadataGroup have a duration; an empty AVTimedMetadataGroup can be supplied to denote a period of no metadata.
 */
- (BOOL)appendTimedMetadataGroup:(AVTimedMetadataGroup *)metadata error:(NSError * _Nullable * _Nullable)outError;

@end

NS_ASSUME_NONNULL_END
