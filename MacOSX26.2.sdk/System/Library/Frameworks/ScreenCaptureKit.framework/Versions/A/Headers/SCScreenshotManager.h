//
//  SCScreenshotManager.h
//  ScreenCaptureKit
//
//  Copyright © 2023 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <ScreenCaptureKit/ScreenCaptureKit.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @typedef SCScreenshotDisplayIntent
 @abstract Client can use SCScreenshotDisplayIntent to specifiy rendering of the screenshot
 @constant SCScreenshotDisplayIntentCanonical using this will specify the screenshot to be rendered on the canonical display
 @constant SCScreenshotDisplayIntentLocal using this wil specifiy the screenshot to be rendered on the local display
*/
API_AVAILABLE(macos(26.0), macCatalyst(26.0));
typedef NS_ENUM(NSInteger, SCScreenshotDisplayIntent) {
    SCScreenshotDisplayIntentCanonical,
    SCScreenshotDisplayIntentLocal
} NS_SWIFT_NAME(SCScreenshotConfiguration.DisplayIntent);;

/*!
 @typedef SCScreenshotDynamicRange
 @abstract Client can use SCScreenshotDynamicRange to specifiy the images to return to them
 @constant SCScreenshotDynamicRangeSDR using this will return an SDR CGimage to the client
 @constant SCScreenshotDynamicRangeHDR using this will return an HDR CGimage to the client
 @constant SCScreenshotDynamicRangeSDRAndHDR using this will return both SDR and HDR CGimage versions to the client
*/
API_AVAILABLE(macos(26.0), macCatalyst(26.0));
 typedef NS_ENUM(NSInteger, SCScreenshotDynamicRange) {
      SCScreenshotDynamicRangeSDR NS_SWIFT_NAME(sdr),
      SCScreenshotDynamicRangeHDR NS_SWIFT_NAME(hdr),
      SCScreenshotDynamicRangeSDRAndHDR NS_SWIFT_NAME(bothSDRAndHDR)
 } NS_SWIFT_NAME(SCScreenshotConfiguration.DynamicRange);

/*!
 @abstract SCScreenshotConfiguration
 @discussion SCScreenshotConfiguration is an object that the SCScreenshot properties such as output width, height, and others.
*/
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(26.0), macCatalyst(26.0));
@interface SCScreenshotConfiguration : NSObject
/*!
 @abstract SCScreenshotProperty for output width as measured in pixels. Default is the width of the content being captured.
 */
@property(nonatomic, assign) NSInteger width;

/*!
 @abstract SCScreenshotProperty for output height as measured in pixels. Default is the height of the content being captured.
 */
@property(nonatomic, assign) NSInteger height;

/*!
 @abstract SCScreenshotProperty that specifies whether the cursor should appear in the screenshot.  By default the cursor is visible.
 */
@property(nonatomic, assign) BOOL showsCursor;

/*!
 @abstract SCScreenshotProperty that specifies that the screenshot only samples a subset of the frame input. If not set, then the entire screenshot will be captured. The rectangle is specified in points in the display’s logical coordinate system.
 */
@property(nonatomic, assign) CGRect sourceRect;

/*!
 @abstract SCScreenshotProperty that specifies that the screenshot outputs into a subset of the output CGimage.If not set then the output surface is used. The rectangle is specified in pixels in the display's coordinate system.
 */
@property(nonatomic, assign) CGRect destinationRect;

/*!
 @abstract SCScreenshotProperty to ignore framing on windows (will ignore shadows).
 */
@property(nonatomic, assign) BOOL ignoreShadows;

/*!
 @abstract SCScreenshotProperty to ignore framing on windows in the display bounded sharing case (will ignore shadows).
 */
@property(nonatomic, assign) BOOL ignoreClipping;

/*!
 @abstract SCScreenshotProperty to show the child windows of the applications and windows being captured.  Child windows are included by default.
 */
@property(nonatomic, assign) BOOL includeChildWindows;

/*!
 @abstract Specifies the render type of the screenshot.
 */
@property(nonatomic, assign) SCScreenshotDisplayIntent displayIntent;

/*!
 @abstract Specifies the CGImage to return to the client.
 */
@property(nonatomic, assign) SCScreenshotDynamicRange dynamicRange;

/*!
 @abstract Specifies the screenshot file format.
 */
@property(nonatomic, assign) UTType *contentType;

/*!
 @abstract Specifies output URL to save the screenshot.  If the imageOutputURL is nil, then the file will not be saved.
 */
@property(nullable, nonatomic, strong) NSURL *fileURL;

/*!
  @abstract an array of UTTypes that corresponds to the file formats that are supported. ScreenCaptureKit can save the CGImage into heic, jpeg, and png
 */
@property(class, readonly) NSArray<UTType *> *supportedContentTypes;
@end

/*!
 @abstract SCScreenshotOutput
 @discussion SCScreenshotOutput is an object that contains the CGImages requested by the client.
*/
API_AVAILABLE(macos(26.0), macCatalyst(26.0));
@interface SCScreenshotOutput : NSObject
/*!
 @abstract SCScreenshotOutput property that denotes the SDR CGimage.  The output CGImage uses the same color space as the display
 */
@property (nonatomic, strong, nullable) CGImageRef sdrImage __attribute__((NSObject));
/*!
 @abstract SCScreenshotOutput property that denotes the HDR CGimage.  The output CGImage uses the extended sRGB color space.
 */
@property (nonatomic, strong, nullable) CGImageRef hdrImage __attribute__((NSObject));

/*!
 @abstract SCScreenshotOutput property to specify the location where the image was saved.  If a fileURL in the screenshot configuration was not specified, then the fileURL will be nil
 */
@property (nullable, nonatomic, assign) NSURL *fileURL;
@end

API_AVAILABLE(macos(14.0), macCatalyst(18.2))
@interface SCScreenshotManager : NSObject
- (instancetype)init API_UNAVAILABLE(ios, tvos, macCatalyst, macos);
/*!
 @abstract captureSampleBufferWithFilter:configuration:completionHandler:
 @param contentFilter is the filter containing the content to take a screenshot of
 @param config is the stream configuration containing information on how to format the screenshot
 @param completionHandler is the handler that will deliver the screenshot to the user
 @discussion this method takes a screenshot using the filter and configuration passed in and returns it as a CMSampleBuffer
*/
+ (void)captureSampleBufferWithFilter:(SCContentFilter *)contentFilter configuration:(SCStreamConfiguration *)config completionHandler:(nullable void (^)(CMSampleBufferRef _Nullable sampleBuffer, NSError *_Nullable error))completionHandler NS_SWIFT_NAME(captureSampleBuffer(contentFilter:configuration:completionHandler:)) API_AVAILABLE(macos(14.0));

/*!
 @abstract captureImageWithFilter:configuration:completionHandler:
 @param contentFilter is the filter containing the content to take a screenshot of
 @param config is the stream configuration containing information on how to format the screenshot
 @param completionHandler is the handler that will deliver the screenshot to the user
 @discussion this method takes a screenshot using the filter and configuration passed in and returns it as a CGImage in BGRA format if captureDynamicRange is SCCaptureDynamicRangeSDR, in RGhA format if captureDynamicRange is SCCaptureDynamicRangeHDRLocalDisplay/SCCaptureDynamicRangeHDRCanonicalDisplay
*/
+ (void)captureImageWithFilter:(SCContentFilter *)contentFilter configuration:(SCStreamConfiguration *)config completionHandler:(nullable void (^)(CGImageRef _Nullable sampleBuffer, NSError *_Nullable error))completionHandler NS_SWIFT_NAME(captureImage(contentFilter:configuration:completionHandler:)) API_AVAILABLE(macos(14.0));

/*!
 @abstract captureImageInRect:completionHandler:
 @param rect the rect for the region in points on the screen space for the screen shot, this is display agnostic and supports multiple displays
 @param completionHandler is the handler that will deliver the screenshot to the client
 @discussion this method returns an image containing the contents of the rectangle in points, specified in display space
*/
+ (void)captureImageInRect:(CGRect)rect completionHandler:(nullable void (^)(CGImageRef _Nullable image, NSError *_Nullable error))completionHandler NS_SWIFT_NAME(captureImage(in:completionHandler:)) API_AVAILABLE(macos(15.2));

/*!
 @abstract captureScreenshotWithFilter:configuration:completionHandler:
 @param contentFilter is the filter containing the content to take a screenshot of
 @param config is the screenshot configuration containing information on how to format the screenshot
 @param completionHandler is the handler that will deliver the SCScreenshotOutput object to the client
 @discussion this method returns an SCScreenshotOutput object containing CGImages of the screenshot requested by the client
*/
+ (void)captureScreenshotWithFilter:(SCContentFilter *)contentFilter configuration:(SCScreenshotConfiguration *)config completionHandler:(nullable void (^)(SCScreenshotOutput *_Nullable output, NSError *_Nullable error))completionHandler NS_SWIFT_NAME(captureScreenshot(contentFilter:configuration:completionHandler:)) API_AVAILABLE(macos(26.0), macCatalyst(26.0));

/*!
 @abstract captureScreenshotWithRect:configuration:completionHandler:
 @param rect the rect for the region in points on the screen space for the screen shot, this is display agnostic and supports multiple displays
 @param config is the screenshot configuration containing information on how to format the screenshot
 @param completionHandler is the handler that will deliver the SCScreenshotOutput object to the client
 @discussion this method returns an SCScreenshotOutput object containing CGImages of the screenshot requested by the client
*/
+ (void)captureScreenshotWithRect:(CGRect)rect configuration:(SCScreenshotConfiguration *)config completionHandler:(nullable void (^)(SCScreenshotOutput *_Nullable output, NSError *_Nullable error))completionHandler NS_SWIFT_NAME(captureScreenshot(rect:configuration:completionHandler:)) API_AVAILABLE(macos(26.0), macCatalyst(26.0));
@end

NS_ASSUME_NONNULL_END
