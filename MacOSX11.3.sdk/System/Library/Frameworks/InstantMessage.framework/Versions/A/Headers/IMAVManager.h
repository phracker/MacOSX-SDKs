//
//  IMAVManager.h
//
//  Copyright (c) 2006 Apple Computer, Inc. All rights reserved.
//

/*! @header
    @discussion The IMAVManager API allows clients to share audio and video content through conferences
                with other buddies in Messages AV.
*/

#import <Foundation/Foundation.h>
#import <CoreVideo/CVPixelBuffer.h>
#import <CoreVideo/CVOpenGLBuffer.h>
#import <InstantMessage/IMService.h>
#import <InstantMessage/IMAVControl.h>

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

/*! @group Notifications */

/*! Received from IMService's custom notification center. Posted when Messages AV's input state has changed. This notification
    is relevant to the shared IMAVManager instance. The user information dictionary will not contain keys. Clients should call
    <tt>state</tt> to get the new state. */
extern NSString * const IMAVManagerStateChangedNotification NS_DEPRECATED_MAC(10_5, 10_9);

/*! Received from IMService's custom notification center. Posted when the selected document to be shared has been changed by
    the user during a running session. This notification is relevant to the shared IMAVManager instance. The user information
    dictionary will not contain keys. Clients should call <tt>URLToShare</tt> to get the new URL. This notification will not be
    sent when the IMAVManager's state first changes to IMAVRequested. */
extern NSString * const IMAVManagerURLToShareChangedNotification NS_DEPRECATED_MAC(10_5, 10_9);

/*! @group Constants */

/*! @enum       IMAVManagerState
    @abstract       These constants describe the current state of the IMAVManager (accessed using the <tt>state</tt> method).
                    <tt>IMAVPending</tt> indicates that frame callbacks will not be made, e.g. when a conference has not yet connected.
                    Clients may wish to defer certain actions until the state becomes <tt>IMAVRunning</tt>.
    @constant   IMAVInactive
                    Indicates that audio and video may not be sent to Messages AV, because the user has not chosen to begin a session.
    @constant   IMAVRequested
                    Indicates that the user has selected this client to begin Messages Theater. Clients should call
                    <tt>-[IMAVManager URLToShare]</tt> and open the corresponding file. Once opened, call
                    <tt>-[IMAVManager start]</tt> to begin the session.
    @constant   IMAVShuttingDown
                    Indicates that the IMAVManager is disconnecting from Messages AV, after a call to <tt>-stop</tt>.
    @constant   IMAVStartingUp
                    Indicates that the IMAVManager is connecting to Messages AV, after a call to <tt>-start</tt>.
    @constant   IMAVPending
                    Indicates that the IMAVManager is connected to Messages AV and ready to provide audio and video data, but
                    an AV chat is not currently running. No video frame call-backs will be made. If a client calls <tt>-start</tt>
                    before the user has connected an AV chat, the IMAVManager will go into this state. Once Messages AV begins a
                    conference, the state will change to <tt>IMAVRunning</tt>.
    @constant   IMAVRunning
                    Indicates that the client will receive video frame call-backs and that audio should be played into the specified
                    device for sharing with the active AV chat. Clients should defer the starting of any video (e.g., a QuickTime movie)
                    until the state reaches this value, rather than immediately after calling <tt>-[IMAVManager start]</tt>.
*/
enum {
    IMAVInactive        = 0,
    IMAVRequested       = 1,
    IMAVShuttingDown    = 2,
    IMAVStartingUp      = 3,
    IMAVPending         = 4,
    IMAVRunning         = 5
};
typedef NSUInteger IMAVManagerState NS_DEPRECATED_MAC(10_5, 10_9);

/*! @enum       IMVideoOptimizationOptions
    @abstract       These constants describe the content the video data source will provide to Messages to allow for optimization of
                    CPU and bandwidth usage.
    @constant   IMVideoOptimizationDefault
                    Indicates the default setting: shared video is played alongside the user's local video, and the video is full-motion.
    @constant   IMVideoOptimizationStills
                    Indicates that the shared video will remain unchanged for many sequential frames (such a photo slideshow), a hint that the
                    required bandwidth will be lower than that of full-motion video. Incorrectly setting this mask will result in poorer video quality.
    @constant   IMVideoOptimizationReplacement
                    Indicates that the user's local video should not be sent, instead devoting full CPU and bandwidth resources to the shared video.
*/
enum {
    IMVideoOptimizationDefault = 0,    
    IMVideoOptimizationStills = 1 << 0,
    IMVideoOptimizationReplacement = 1 << 1,
};
typedef NSUInteger IMVideoOptimizationOptions NS_DEPRECATED_MAC(10_5, 10_9);

/*! @class IMAVManager
    @abstract A shared object which manages the state and configuration of auxiliary audio/video input to Messages AV.
    @discussion The IMAVManager allows clients to provide audio and/or video to a running
                conference in Messages AV. Video is provided by supplying a delegate to receive periodic
                callbacks for individual frames, and audio is provided through an audio device and
                channel. The state of the shared IMAVManager allows clients to configure
                UI appropriately.
*/
@interface IMAVManager : NSObject { }

/*! 
    @method sharedManager
    @abstract Returns the shared instance of the IMAVManager.
    @result The shared manager.
*/
+ (IMAVManager *) sharedAVManager NS_DEPRECATED_MAC(10_5, 10_9);

/*! 
    @method state
    @abstract Returns the current state of the receiver.
    @result The current IMAVManagerState, as updated by Messages AV. See "Constants" in this document for possible values.
*/
- (IMAVManagerState) state NS_DEPRECATED_MAC(10_5, 10_9);

/*! 
 @method URLToShare
 @abstract Returns the URL of the document that has been chosen by the user and should be shared with iChat Theater.
 @result The URL of the document to be shared. Returns <tt>nil</tt> if the receiver's state is <tt>IMAVInactive</tt>.
*/
- (NSURL *) URLToShare NS_DEPRECATED_MAC(10_5, 10_9);

/*!
    @method setVideoDataSource:
    @abstract Sets the object which will provide video data to Messages AV. The delegate must implement appropriate methods described
              in the <tt>IMVideoDataSource</tt> informal protocol.
    @param dataSource Object to receive the callback methods. <tt>nil</tt> removes the data source. This object is not retained.
                      Any NSView (or subclass) may be used as well, providing basic functionality without the need for clients
                      to implement the frame callbacks.
*/
- (void) setVideoDataSource:(id)dataSource NS_DEPRECATED_MAC(10_5, 10_9);

/*! 
    @method videoDataSource
    @abstract Returns the current video data source.
    @result The data source, or <tt>nil</tt> if none is set.
*/
- (id) videoDataSource NS_DEPRECATED_MAC(10_5, 10_9);

/*! 
 @method setVideoOptimizationOptions:
 @abstract Describes the video content that will be provided by the data source.
 @param mode The options to use. See "Constants" in this document for possible values.
*/
- (void) setVideoOptimizationOptions:(IMVideoOptimizationOptions)options NS_DEPRECATED_MAC(10_5, 10_9);

/*! 
 @method videoOptimizationOptions
 @abstract Returns the current video optimization options.
 @result The current options. See "Constants" in this document for possible values.
*/
- (IMVideoOptimizationOptions) videoOptimizationOptions NS_DEPRECATED_MAC(10_5, 10_9);

/*!
    @method setNumberOfAudioChannels:
    @abstract Sets the number of audio channels that will be configured after calling <tt>start</tt>.
    @param count The number of channels. Pass zero to disable sending audio, 1 for mono sound, and 2 for stereo.
*/
- (void) setNumberOfAudioChannels:(NSInteger)count NS_DEPRECATED_MAC(10_5, 10_9);

/*! 
    @method numberOfAudioChannels
    @abstract Returns the number of audio channels that will be configured by the receiver.
    @result The number of channels.
*/
- (NSInteger) numberOfAudioChannels NS_DEPRECATED_MAC(10_5, 10_9);

/*! 
 @method audioDeviceUID
 @abstract Returns the UID of the device into which audio should be played, valid when the receiver's state is <tt>IMAVRunning</tt>.
 @result The UID of the device. The device is obtained by calling <tt>AudioHardwareGetProperty()</tt> with this value and the
         <tt>kAudioHardwarePropertyDeviceForUID</tt> property ID.
*/
- (NSString *) audioDeviceUID NS_DEPRECATED_MAC(10_5, 10_9);

/*! 
 @method audioDeviceChannels
 @abstract The channel numbers into which audio should be played on the output device.
 @result An array of NSNumbers identifying the channels to use. If two channels were requested, they correspond to the left and right channels, in that order.
*/
- (NSArray *) audioDeviceChannels NS_DEPRECATED_MAC(10_5, 10_9);

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_6

/*! 
 @method controlBar
 @abstract The control bar configured for use with an IMAVManager.
 @result The control bar.
 */
- (IMAVControlBar *) controlBar NS_DEPRECATED_MAC(10_5, 10_9);

#endif

/*! 
    @method start
    @abstract Requests to send audio and/or video Messages AV. Clients must have previously called <tt>setVideoDataSource:</tt>
              to send video, and <tt>setNumberOfAudioChannels:</tt> with a value greater than zero to send audio. The state will
              change to <tt>IMAVStartingUp</tt>, and then either to <tt>IMAVPending</tt> or <tt>IMAVRunning</tt>, depending on
              whether or not there is an active conference in Messages AV.
*/
- (void) start NS_DEPRECATED_MAC(10_5, 10_9);

/*! 
    @method stop
    @abstract Stops sending audio and/or video to Messages AV.
*/
- (void) stop NS_DEPRECATED_MAC(10_5, 10_9);

@end


/*!
    @protocol IMVideoDataSource
    @abstract An informal protocol to be adopted by objects passed to <tt>-[IMAVManager setVideoDataSource:]</tt>.
    @discussion The video data source provides frames to Messages for use in a running conference.
                The data source must either implement both <tt>getPixelBufferPixelFormat:</tt> and
                <tt>renderIntoPixelBuffer:forTime:</tt>, or both <tt>getOpenGLBufferContext:pixelFormat:</tt> and
                <tt>renderIntoOpenGLBuffer:onScreen:forTime:</tt>, based on whether CVPixelBuffers or
                CVOpenGLBuffers are preferred.
*/
@interface NSObject (IMVideoDataSource)

/*! 
    @method getPixelBufferPixelFormat:
    @abstract This method is optional. Called once after <tt>setVideoDataSource:</tt>, if implemented.
    @param pixelFormatOut The pixel format to be used for the CVPixelBufferRef instances passed to <tt>renderIntoPixelBuffer:forTime:</tt>.
*/
- (void) getPixelBufferPixelFormat:(OSType *)pixelFormatOut NS_DEPRECATED_MAC(10_5, 10_9);

/*! 
    @method renderIntoPixelBuffer:forTime:
    @abstract Called for each frame to be sent to Messages. This method will not be called on the main thread.
    @param buffer The pixel buffer to fill. The dimensions can vary: use <tt>CVPixelBufferGetWidth()</tt> and <tt>CVPixelBufferGetHeight()</tt> every time.
    @param timeStamp The frame time for which the buffer should be rendered.
    @result Return <tt>YES</tt> if the buffer was successfully filled with new frame data. Return <tt>NO</tt> if nothing has changed or an error was encountered.
*/
- (BOOL) renderIntoPixelBuffer:(CVPixelBufferRef)buffer forTime:(CVTimeStamp *)timeStamp NS_DEPRECATED_MAC(10_5, 10_9);

/*! 
    @method getOpenGLBufferContext:pixelFormat:
    @abstract This method is optional. Called once after <tt>setVideoDataSource:</tt>, if implemented.
    @param contextOut The OpenGL context to be used for the CVOpenGLBufferRef instances passed to <tt>renderIntoOpenGLBuffer:onScreen:forTime:</tt>.
    @param pixelFormatOut The OpenGL pixel format to be used for the CVOpenGLBufferRef instances passed to <tt>renderIntoOpenGLBuffer:onScreen:forTime:</tt>.
*/
- (void) getOpenGLBufferContext:(CGLContextObj *)contextOut pixelFormat:(CGLPixelFormatObj *)pixelFormatOut NS_DEPRECATED_MAC(10_5, 10_9);

/*! 
    @method renderIntoOpenGLBuffer:onScreen:forTime:
    @abstract Called for each frame to be sent to Messages. This method will not be called on the main thread.
    @param buffer The OpenGL buffer to fill. The receiver should call <tt>CVOpenGLBufferAttach()</tt>, then render.
    @param screenInOut The recommended virtual screen number to pass to <tt>CVOpenGLBufferAttach()</tt> for maximum efficiency. The
                       delegate may use a different screen number, but must write that value back into <i>screenInOut</i> before returning.
    @param timeStamp The frame time for which the buffer should be rendered.
    @result Return <tt>YES</tt> if the buffer was successfully filled with new frame data. Return <tt>NO</tt> if nothing has changed or an error was encountered.
*/
- (BOOL) renderIntoOpenGLBuffer:(CVOpenGLBufferRef)buffer onScreen:(int *)screenInOut forTime:(CVTimeStamp *)timeStamp NS_DEPRECATED_MAC(10_5, 10_9);

@end

#endif
