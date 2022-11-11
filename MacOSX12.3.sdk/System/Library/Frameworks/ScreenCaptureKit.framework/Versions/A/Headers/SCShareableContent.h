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

API_AVAILABLE(macos(12.3))
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

API_AVAILABLE(macos(12.3))
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
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;
@end

API_AVAILABLE(macos(12.3))
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

API_AVAILABLE(macos(12.3))
@interface SCShareableContent : NSObject
/*!
@abstract getShareableContentWithCompletionHandler:completionHandler
@param completionHandler the call back that will hand you back a SCShareableContent object
@discussion this method will create a SCShareableContent object that is called on the supplied queue. The SCShareableContent will contain the windows, displays and applications that are available to capture
*/
+ (void)getShareableContentWithCompletionHandler:(void(^)(SCShareableContent * _Nullable shareableContent, NSError * _Nullable error))completionHandler NS_SWIFT_ASYNC(1) NS_SWIFT_ASYNC_NAME(getter:current());

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
