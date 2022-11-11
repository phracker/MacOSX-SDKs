//
// SCStream.h
// ScreenCaptureKit
//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AppKit/AppKit.h>
#import <ScreenCaptureKit/SCShareableContent.h>
#import <CoreMedia/CMSampleBuffer.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @typedef SCFrameStatus
 @abstract SCFrameStatus denotes the status of frame sample buffer.
 @constant SCFrameStatusComplete new frame was generated.
 @constant SCFrameStatusIdle new frame was not generated because the display did not change.
 @constant SCFrameStatusBlank new frame was not generated because the display has gone blank.
 @constant SCFrameStatusSuspended new frame was not generated because updates haves been suspended
 @constant SCFrameStatusStarted new frame that is indicated as the first frame sent after the stream has started.
 @constant SCFrameStatusStopped the stream was stopped.
*/
typedef NS_ENUM(NSInteger, SCFrameStatus) {
    SCFrameStatusComplete,
    SCFrameStatusIdle,
    SCFrameStatusBlank,
    SCFrameStatusSuspended,
    SCFrameStatusStarted,
    SCFrameStatusStopped
};

/*!
 @typedef SCStreamOutputType
 @constant SCStreamOutputTypeScreen screen sample output type.
 @discussion
    SCStreamOutputTypeScreen is a screen capture sample buffer. This sample buffer that is wrapping a CVPixelBuffer that is backed by an IOSurface. The width and height of the sample buffer is what is definied in the SCStreamConfiguration for width and height. The sample buffer will be called back on the provided queue when adding a SCStreamOutput. The pixel format of the sample buffer will be what is defined in the SCStreamConfiguration. In the case of mulitiple window capture, the width and height will be that of the display passed in for the filter. The background color of multiwindow sample buffers will be default black and can be set through the SCStreamConfiguration.
*/
typedef NS_ENUM(NSInteger, SCStreamOutputType) {
    SCStreamOutputTypeScreen
};

/*!
 @abstract SCContentFilter
 @discussion SCContentFilter is a object that determines the exact content to be captured in the SCStream. It can be filtered through displays, windows, excluded windows or applications.
*/
API_AVAILABLE(macos(12.3))
@interface SCContentFilter : NSObject
/*!
 @abstract initWithDesktopIndependentWindow:
 @param window the independent SCWindow you wish to capture
 @discussion this method will create a SCContentFilter that captures just the independent window passed in.
*/
- (instancetype)initWithDesktopIndependentWindow:(SCWindow *)window;

/*!
 @abstract initWithDisplay:excludingWindows
 @param display the SCDisplay you wish to capture
 @param excluded the SCWindow(s) you wish to exclude from the passed in SCDisplay
 @discussion this method will create a SCContentFilter that captures the SCDisplay, excluding the passed in excluded SCWindow(s)
*/
- (instancetype)initWithDisplay:(SCDisplay *)display excludingWindows:(NSArray<SCWindow *>*)excluded;

/*!
 @abstract initWithDisplay:includingWindows
 @param display the SCDisplay you wish to capture
 @param includedWindows a set of SCWindows you wish to capture
 @discussion this method will create a SCContentFilter that captures a group of SCWindows
*/
- (instancetype)initWithDisplay:(SCDisplay *)display includingWindows:(NSArray<SCWindow *>*)includedWindows;

/*!
 @abstract initWithDisplay:includingApplications:exceptingWindows
 @param display the SCDisplay you wish to capture
 @param applications the NSSet of SCRunningApplications that you wish to capture
 @param exceptingWindows the NSSet of SCWindows that you wish to be an exception to the filter
 @discussion This method creates a SCContentFilter that captures all windows owned by the passed in SCRunningApplications. Any windows that are an exception to the filter will not be shown if their owning application is in the provided list and will be shown otherwise.
*/
- (instancetype)initWithDisplay:(SCDisplay *)display includingApplications:(NSArray<SCRunningApplication *>*)applications exceptingWindows:(NSArray<SCWindow *>*)exceptingWindows;

/*!
 @abstract initWithDisplay:excludingApplications:exceptingWindows
 @param display the SCDisplay you wish to capture
 @param applications the NSSet of SCRunningApplications that you do not wish to capture
 @param exceptingWindows the NSSet of SCWindows that you wish to be an exception to the filter
 @discussion This method creates a SCContentFilter that captures all windows not owned by the passed in SCRunningApplications. Any windows that are an exception to the filter will be shown if their owning application is in the provided list and will not be shown otherwise.
*/
- (instancetype)initWithDisplay:(SCDisplay *)display excludingApplications:(NSArray<SCRunningApplication *>*)applications exceptingWindows:(NSArray<SCWindow *>*)exceptingWindows;

@end

/*!
 @abstract SCStreamConfiguration
 @discussion SCStreamConfiguration is an object that encapsulates the SCStream properties such as output width, height, pixelformat and others.
*/
API_AVAILABLE(macos(12.3))
@interface SCStreamConfiguration : NSObject
/*!
 @abstract SCStreamProperty for output width as measured as points
 */
@property(nonatomic, assign) size_t width;

/*!
 @abstract SCStreamProperty for output height as measured as points
 */
@property(nonatomic, assign) size_t height;

/*!
 @abstract SCStreamProperty that specifies the desired minimum time in seconds between frame updates, allowing you to throttle the rate at which updates are received. 
 */
@property(nonatomic, assign) CMTime minimumFrameInterval;

/*!
 @abstract SCStreamProperty for output pixel format. Supported pixel formats are:
 'BGRA': Packed Little Endian ARGB8888
 'l10r': Packed Little Endian ARGB2101010
 '420v': 2-plane "video" range YCbCr 4:2:0
 '420f': 2-plane "full" range YCbCr 4:2:0
 See https://developer.apple.com/documentation/coregraphics/1455170-cgdisplaystreamcreate
 */
@property(nonatomic, assign) OSType pixelFormat;

/*!
 @abstract SCStreamProperty for output to be always scaled to fit into the provided width and height. For use for independent window capture. When true, the output scales up and down. When false, the output only scales down.
 */
@property(nonatomic, assign) BOOL scalesToFit;

/*!
 @abstract SCStreamProperty that specifies whether the cursor should appear in the stream.  By default the cursor is visible.
 */
@property(nonatomic, assign) BOOL showsCursor;

/*!
 @abstract SCStreamProperty for background color. By default the background color is clear.
 */
@property(nonatomic, assign) CGColorRef backgroundColor;

/*!
 @abstract SCStreamProperty that specifies that the display stream only samples a subset of the display’s framebuffer.  if not set, then the entire display is streamed. The rectangle is specified in points in the display’s logical coordinate system. Not used for independent window capture
 */
@property(nonatomic, assign) CGRect sourceRect;

/*!
 @abstract SCStreamProperty that specifies that the display stream outputs the frame data into a subset of the output IOSurface object.  If not set then the entire output surface is used. The rectangle is specified in points in the surface’s coordinate system. Not used for independent window capture
 */
@property(nonatomic, assign) CGRect destinationRect;

/*!
 @abstract SCStreamProperty that specifies the number of frames to keep in the queue.  If not set the default value is 3 frames.  Specifying more frames uses more memory, but may allow you to process frame data without stalling the display stream and should not exceed 8 frames.
 */
@property(nonatomic, assign) NSInteger queueDepth;

/*!
 @abstract SCStreamProperty that specifies the YCbCr matrix applied to the output surface.  The value must be one of the strings specified in https://developer.apple.com/documentation/coregraphics/quartz_display_services/display_stream_ycbcr_to_rgb_conversion_matrix_options. Should only be used if your pixel format is 420v or 420f.
 */
@property(nonatomic, assign) CFStringRef colorMatrix;

/*!
 @abstract SCStreamProperty that specifies the color space of the output buffer.  If not set the output buffer uses the same color space as the display. The value must be one of the strings specified in
 https://developer.apple.com/documentation/coregraphics/cgcolorspace/color_space_names.
 */
@property(nonatomic, assign) CFStringRef colorSpaceName;
/*!
 @abstract Creates an SCStreamConfiguration with default values for all properties.
 */
- (instancetype)init;
@end

/*!
 @abstract SCStream
 @discussion SCStream is the object that takes in an SCContentFilter and sets up a contentstream that gives the calling application back the screen captures based on the contentfilter and settings
*/
API_AVAILABLE(macos(12.3))
@protocol SCStreamDelegate;

API_AVAILABLE(macos(12.3))
typedef NSString * SCStreamFrameInfo NS_TYPED_ENUM;
/*!
 @key SCStreamFrameInfoStatus
 @abstract The key for the CFDictionary attached to the CMSampleBuffer that denotes the frames SCFrameStatus
 */
extern SCStreamFrameInfo const SCStreamFrameInfoStatus API_AVAILABLE(macos(12.3));

/*!
 @key SCStreamFrameInfoDisplayTime
 @abstract The key for the CFDictionary attached to the CMSampleBuffer for the mach absolute time when the event occurred. For a frame event, this is when the frame was displayed by the window server.
 */
extern SCStreamFrameInfo const SCStreamFrameInfoDisplayTime API_AVAILABLE(macos(12.3));

/*!
 @key SCStreamFrameInfoScaleFactor
 @abstract The key for the CFDictionary attached to the CMSampleBuffer for the display resolution associated with the frame. Display resolution is the pixel to point scaling factor. It should be in the range of [1, 4].
 */
extern SCStreamFrameInfo const SCStreamFrameInfoScaleFactor API_AVAILABLE(macos(12.3));

/*!
 @key SCStreamFrameInfoContentScale
 @abstract The key for the CFDictionary attached to the CMSampleBuffer for the content scale associated with the frame. Content scale is the scaling factor from original content size to its size in surface.
 */
extern SCStreamFrameInfo const SCStreamFrameInfoContentScale API_AVAILABLE(macos(12.3));

/*!
 @key SCStreamFrameInfoContentRect
 @abstract The key for the CFDictionary attached to the CMSampleBuffer for the content rect associated with the frame. Content rect is the size and location of content in points in surface.
 */
extern SCStreamFrameInfo const SCStreamFrameInfoContentRect API_AVAILABLE(macos(12.3));

/*!
 @key SCStreamFrameInfoDirtyRects
 @abstract The key for the CFDictionary attached to the CMSampleBuffer for an array of rectangles that is the union of both rectangles that were redrawn and rectangles that were moved. This is an array of CGRect in NSValue.
 */
extern SCStreamFrameInfo const SCStreamFrameInfoDirtyRects API_AVAILABLE(macos(12.3));

@protocol SCStreamOutput;
API_AVAILABLE(macos(12.3))
@interface SCStream : NSObject
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;
/*!
 @abstract initWithFilter:configuration:delegate:
 @param contentFilter the requested content filter to be captured
 @param streamConfig the requested stream configuration to be applied to the SCStream
 @param delegate the SCStream delegate object
 @discussion this method create a SCStream object that has the particular output settings for the content stream
*/
- (instancetype)initWithFilter:(SCContentFilter *)contentFilter configuration:(SCStreamConfiguration *)streamConfig delegate:(id<SCStreamDelegate> _Nullable)delegate;

/*!
 @abstract addStreamOutput:type:sampleHandlerQueue:error:
 @param output an object that adheres to the SCStreamOutput protocol that will recieved the frames and call its delegte frame call back on its sample handler queue
 @param type the SCStreamOutput type
 @param sampleHandlerQueue the return queue for the sample handler
 @param error the error pertaining to the add stream output
 @discussion An SCStreamOutput protocol object instance can only be added to a session using -addStreamOutput: Returns a BOOL denoting if the remove was successful
*/
- (BOOL)addStreamOutput:(id<SCStreamOutput>)output type:(SCStreamOutputType)type sampleHandlerQueue:(dispatch_queue_t _Nullable)sampleHandlerQueue error:(NSError **)error NS_SWIFT_ASYNC_NAME (addStreamOutput(_:type:sampleHandlerQueue:)) NS_SWIFT_NAME (addStreamOutput(_:type:sampleHandlerQueue:));

/*!
 @abstract removeStreamOutput:type:error:
 @param output an object that adheres to the SCStreamOutput protocol that will recieved the frames and call its delegte frame call back on its sample handler queue
 @param type the SCStreamOutput type
 @param error the error pertaining to the removing stream output
 @discussion An SCStreamOutput protocol object instance can only be removed to a session using -addStreamOutput: Returns a BOOL denoting if the remove was successful
*/

- (BOOL)removeStreamOutput:(id<SCStreamOutput>)output type:(SCStreamOutputType)type error:(NSError **)error NS_SWIFT_ASYNC_NAME(removeStreamOutput(_:type:)) NS_SWIFT_NAME(removeStreamOutput(_:type:));

/*!
 @abstract updateContentFilter:completionHandler:
 @param contentFilter the requested content filter to be updated
 @param completionHandler the handler to be called when the function completes
 @discussion this method will update the content filter for a content stream. A completion handler will be called when the update is complete with an error denoting if the update has failed.
*/
- (void)updateContentFilter:(SCContentFilter *)contentFilter completionHandler:(nullable void (^)(NSError *_Nullable error))completionHandler NS_SWIFT_ASYNC_NAME(updateContentFilter(_:)) NS_SWIFT_NAME(updateContentFilter(_:completionHandler:));

/*!
 @abstract updateConfiguration:completionHandler:
 @param streamConfig the requested content filter to be updated
 @param completionHandler the handler to be called when the function completes
 @discussion this method will update the stream configuration for a content stream. A completion handler will be called when the update is complete with an error denoting if the update has failed.
*/
- (void)updateConfiguration:(SCStreamConfiguration *)streamConfig completionHandler:(nullable void (^)(NSError *_Nullable error))completionHandler NS_SWIFT_ASYNC_NAME(updateConfiguration(_:)) NS_SWIFT_NAME(updateConfiguration(_:completionHandler:));

/*!
 @abstract startCaptureWithFrameHandler:completionHandler:
 @param completionHandler the handler to be called when the function completes
 @discussion this method starts the content stream. The handler will be called when the content stream start has completed with an error denoting if the start has failed.
*/
- (void)startCaptureWithCompletionHandler:(nullable void (^)(NSError *_Nullable error))completionHandler;

/*!
 @abstract stopWithCompletionHandler:
 @param completionHandler the handler to be called when the function completes
 @discussion this method stops the content stream. The handler will be called when the content stream stop has completed with an error denoting if the stop has failed.
*/
- (void)stopCaptureWithCompletionHandler:(nullable void (^)(NSError *_Nullable error))completionHandler;

@end

API_AVAILABLE(macos(12.3))
@protocol SCStreamOutput <NSObject>
@optional
/*!
 @abstract stream:didOutputSampleBuffer:ofType:
 @param sampleBuffer the sample buffer
 @param type the sample buffer type
 @discussion protocol method for passing back screen sample buffers
*/
- (void)stream:(SCStream *)stream didOutputSampleBuffer:(CMSampleBufferRef)sampleBuffer ofType:(SCStreamOutputType)type;
@end
/*!
 @abstract SCStreamDelegate
 @discussion SCStreamDelegate is the object that adheres to the SCStream delegate call backs
*/
API_AVAILABLE(macos(12.3))
@protocol SCStreamDelegate <NSObject>
@optional
/*!
 @abstract stream:didStopStreamWithError:
 @param stream the SCStream object
 @param error the error denoted by the stopping of the stream
 @discussion notifies the delegate that the stream has stopped and the error associated with it
*/
- (void)stream:(SCStream *)stream didStopWithError:(NSError *)error;

@end

NS_ASSUME_NONNULL_END
