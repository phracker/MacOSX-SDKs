//
//  SCShareableContent.h
//  SCShareableContent
//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CGWindow.h>
#import <CoreGraphics/CGDirectDisplay.h>

NS_ASSUME_NONNULL_BEGIN

@class SCContentFilter;

/*!
 @typedef SCShareableContentStyle
 @abstract Defines the type of content being shared
 @constant SCShareableContentStyleNone content not specified
 @constant SCShareableContentStyleWindow window bound content stream
 @constant SCShareableContentStyleDisplay display bound content stream
*/
typedef NS_ENUM(NSInteger, SCShareableContentStyle) {
    SCShareableContentStyleNone,
    SCShareableContentStyleWindow,
    SCShareableContentStyleDisplay,
    SCShareableContentStyleApplication
} API_AVAILABLE(macos(12.3), macCatalyst(18.2));


API_AVAILABLE(macos(12.3), macCatalyst(18.2))
@interface SCRunningApplication : NSObject
/*!
 @abstract bundleIdentifier the bundleIdentifier for the SCRunningApplication
 */
@property (readonly) NSString *bundleIdentifier;

/*!
 @abstract applicationName the application name for the SCRunningApplication
 */
@property (readonly) NSString *applicationName;

/*!
 @abstract processID the SCRunningApplication
 */
@property (readonly) pid_t processID;
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;
@end

API_AVAILABLE(macos(12.3), macCatalyst(18.2))
@interface SCWindow : NSObject
/*!
 @abstract windowID the CGWindowID for the SCWindow
 */
@property (readonly) CGWindowID windowID;

/*!
 @abstract frame the CGRect for the SCWindow
 */
@property (readonly) CGRect frame;

/*!
 @abstract title the window title for the SCWindow
 */
@property (readonly, nullable) NSString *title;

/*!
 @abstract windowLayer the window layer for the SCWindow
 */
@property (readonly) NSInteger windowLayer;

/*!
 @abstract owningApplication is the SCRunningApplication that owns this SCWindow
 */
@property (readonly, nullable) SCRunningApplication *owningApplication;

/*!
 @abstract onScreen the bool property denoting of the SCWindow is on the screen
 */
@property (readonly, getter=isOnScreen) BOOL onScreen;

/*!
 @abstract active the bool property denoting of the SCWindow is active. with Stage Manager, SCWindow can be offScreen and active
 */
@property (readonly, getter=isActive) BOOL active API_AVAILABLE(macos(13.1));
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;
@end

API_AVAILABLE(macos(12.3), macCatalyst(18.2))
@interface SCDisplay : NSObject
/*!
 @abstract displayId the CGDirectDisplayID for the SCDisplay
 */
@property (readonly) CGDirectDisplayID displayID;

/*!
 @abstract width the width, in points, for the SCDisplay
 */
@property (readonly) NSInteger width;

/*!
 @abstract height the height, in points, for the SCDisplay
 */
@property (readonly) NSInteger height;

/*!
 @abstract frame the CGRect frame for the SCDisplay
 */
@property (readonly) CGRect frame;
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;
@end

/*!
 @abstract SCShareableContentInfo
 @discussion SCShareableContentInformation is an object that has information about the content of the stream
*/
API_AVAILABLE(macos(14.0), macCatalyst(18.2))
@interface SCShareableContentInfo : NSObject
/*!
 @abstract style of stream
 */
@property (nonatomic, readonly) SCShareableContentStyle style;

/*!
 @abstract Pixel to points scaling factor
 */
@property (nonatomic, readonly) float pointPixelScale;

/*!
 @abstract Size and location of content in points
 */
@property (nonatomic, readonly) CGRect contentRect;

@end

API_AVAILABLE(macos(12.3), macCatalyst(18.2))
@interface SCShareableContent : NSObject
/*!
@abstract getShareableContentWithCompletionHandler:completionHandler
@param completionHandler the call back that will hand you back a SCShareableContent object
@discussion this method will create a SCShareableContent object that is called on the supplied queue. The SCShareableContent will contain the windows, displays and applications that are available to capture
*/
+ (void)getShareableContentWithCompletionHandler:(void(^)(SCShareableContent * _Nullable shareableContent, NSError * _Nullable error))completionHandler NS_SWIFT_ASYNC(1) NS_SWIFT_ASYNC_NAME(getter:current());

/*!
@abstract getCurrentProcessShareableContentWithCompletionHandler:completionHandler
@param completionHandler the call back that will hand you back a SCShareableContent object
@discussion this method will create a SCShareableContent object that is called on the supplied queue. The SCShareableContent will contain redacted information about windows, displays and applications that are available to capture by current process without user consent via TCC
*/
+ (void)getCurrentProcessShareableContentWithCompletionHandler:(void(^)(SCShareableContent * _Nullable shareableContent, NSError * _Nullable error))completionHandler NS_SWIFT_ASYNC(1) NS_SWIFT_ASYNC_NAME(getter:currentProcess()) API_AVAILABLE(macos(14.4));

/*!
@abstract getShareableContentExcludingDesktopWindows:onScreenWindowsOnly:completionHandler
@param excludeDesktopWindows a BOOL indicating if we should exclude desktop windows
@param onScreenWindowsOnly filter only windows that are on screen
@param completionHandler the call back that will hand you back a SCShareableContent object
@discussion this method will create a SCShareableContent object that is called on the supplied queue. The SCShareableContent will contain the windows, displays and applications that are available to capture
*/
+ (void)getShareableContentExcludingDesktopWindows:(BOOL)excludeDesktopWindows onScreenWindowsOnly:(BOOL)onScreenWindowsOnly completionHandler:(void(^)(SCShareableContent * _Nullable shareableContent, NSError * _Nullable error))completionHandler;

/*!
@abstract getShareableContentExcludingDesktopWindows:onScreenWindowsOnlyBelowWindow:completionHandler
@param excludeDesktopWindows a BOOL indicating if we should exclude desktop windows
@param window filter only windows below this SCWindow
@param completionHandler the call back that will hand you back a SCShareableContent object
@discussion this method will create a SCShareableContent object that is called on the supplied queue. The SCShareableContent will contain the windows, displays and applications that are available to capture
*/
+ (void)getShareableContentExcludingDesktopWindows:(BOOL)excludeDesktopWindows onScreenWindowsOnlyBelowWindow:(SCWindow *)window completionHandler:(void(^)(SCShareableContent * _Nullable shareableContent, NSError * _Nullable error))completionHandler;

/*!
@abstract getShareableContentExcludingDesktopWindows:onScreenWindowsOnlyAboveWindow:completionHandler
@param excludeDesktopWindows a BOOL indicating if we should exclude desktop windows
@param window filter only windows above this SCWindow
@param completionHandler the call back that will hand you back a SCShareableContent object
@discussion this method will create a SCShareableContent object that is called on the supplied queue. The SCShareableContent will contain the windows, displays and applications that are available to capture
*/
+ (void)getShareableContentExcludingDesktopWindows:(BOOL)excludeDesktopWindows onScreenWindowsOnlyAboveWindow:(SCWindow *)window completionHandler:(void(^)(SCShareableContent * _Nullable shareableContent, NSError * _Nullable error))completionHandler;

/*!
@abstract infoForFilter:
@param filter content filter to translate to content details
@discussion this method will create a SCShareableContentInformation object given a filter
*/
+ (SCShareableContentInfo *)infoForFilter:(nonnull SCContentFilter *)filter API_AVAILABLE(macos(14.0));

/*!
 @abstract windows SCShareableContent property that contains all the sharable SCWindows
 */
@property (readonly) NSArray<SCWindow *> *windows;

/*!
 @abstract displays SCShareableContent property that contains all the sharable SCDisplays
 */
@property (readonly) NSArray<SCDisplay *> *displays;

/*!
 @abstract applications SCShareableContent property that contains all the sharable SCRunningApplications
 */
@property (readonly) NSArray<SCRunningApplication *> *applications;
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end
NS_ASSUME_NONNULL_END
