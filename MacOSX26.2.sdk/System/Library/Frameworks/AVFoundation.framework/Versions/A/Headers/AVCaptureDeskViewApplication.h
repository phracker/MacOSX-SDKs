#if !__has_include(<AVFCapture/AVCaptureDeskViewApplication.h>)
/*
    File:  AVCaptureDeskViewApplication.h
 
    Framework:  AVFoundation
 
    Copyright 2022 Apple Inc. All rights reserved.
*/

#import <AVFoundation/AVBase.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class AVCaptureDeskViewApplicationLaunchConfiguration;

/*!
 @class AVCaptureDeskViewApplication
 @abstract
    Allows a client to programmatically present the Desk View application and be informed when it is done being launched.
 
 @discussion
    Users can launch the Desk View application through the Video Effects button in Control Center when a Desk View capable Continuity Camera is running. Developers may use this interface as a shortcut to launch the Desk View application directly from their application.
 */
API_AVAILABLE(macos(13.0), macCatalyst(16.1)) API_UNAVAILABLE(ios, tvos, watchos, visionos)
@interface AVCaptureDeskViewApplication : NSObject

/*!
 @method presentWithCompletionHandler:
 @abstract
    Presents the Desk View application to the user with no launch configuration.
  
 @param completionHandler
     A block to be called once the Desk View application has been completely launched (or brought to the foreground).
 
 @discussion
    This method allows you to programmatically launch the Desk View application from your own application UI. If the Desk View application is already running, this method brings it to the front. If the Desk View application is minimized in the Dock, this method un-minimizes it and brings it to the front.
 */
- (void)presentWithCompletionHandler:(nullable void (^)(NSError * _Nullable error))completionHandler API_AVAILABLE(macos(13.0), macCatalyst(16.1)) API_UNAVAILABLE(ios, tvos, watchos, visionos);

/*!
 @method presentWithLaunchConfiguration:completionHandler:
 @abstract
    Presents the Desk View application to the user.
 
 @param launchConfiguration
    Launch configuration governing how the Desk View application will be presented.
 
 @param completionHandler
     A block to be called once the Desk View application has been completely launched (or brought to the foreground). Optionally, this completionHandler may fire later, once the user has completed set up mode (see AVCaptureDeskViewApplicationLaunchConfiguration.requiresSetUpModeCompletion).
 
 @discussion
    This method allows you to programmatically launch the Desk View application from your own application UI. If the Desk View application is already running, this method brings it to the front. If the Desk View application is minimized in the Dock, this method un-minimizes it and brings it to the front.
 */
- (void)presentWithLaunchConfiguration:(AVCaptureDeskViewApplicationLaunchConfiguration *)launchConfiguration completionHandler:(nullable void (^)(NSError * _Nullable error))completionHandler NS_SWIFT_NAME(present(launchConfiguration:completionHandler:)) API_AVAILABLE(macos(13.0), macCatalyst(16.1)) API_UNAVAILABLE(ios, tvos, watchos, visionos);

@end


/*!
 @class AVCaptureDeskViewApplicationLaunchConfiguration
 @abstract
    An object for configuring how the Desk View application is presented.
 
 @discussion
    Developers may use this interface to customize the presentation of the Desk View application upon launch.
 */
API_AVAILABLE(macos(13.0), macCatalyst(16.1)) API_UNAVAILABLE(ios, tvos, watchos, visionos)
NS_SWIFT_NAME(AVCaptureDeskViewApplication.LaunchConfiguration)
@interface AVCaptureDeskViewApplicationLaunchConfiguration : NSObject

/*!
 @property mainWindowFrame
 @abstract
    Specifies the desired frame of the Desk View application's main window when launched.
 
 @discussion
    Default value is CGRectZero. The app will use a default value in this case (the user's previously selected position). mainWindowFrame is specified in global screen coordinates. When launching the Desk View application from a Mac Catalyst app, window origin is top left. When launched from a native macOS app, window origin is bottom left.
 */
@property CGRect mainWindowFrame API_AVAILABLE(macos(13.0), macCatalyst(16.1)) API_UNAVAILABLE(ios, tvos, watchos, visionos);

/*!
 @property requiresSetUpModeCompletion
 @abstract
    Specifies whether presentWithLaunchConfiguration:completionHandler:'s completionHandler fires immediately after the application is launched, or only after the user has completed set up.
 
 @discussion
    The Desk View application launches in set up mode, showing the full field of view of an Ultra Wide camera with a superimposed trapezoid indicating the desk region crop that will be shown once set up is complete. By default, your presentWithLaunchConfiguration:completionHandler:'s completionHandler fires after the Desk View application is launched and visible to the user. By setting this property to YES, your completionHandler only fires when the user has completed set up mode and transitioned to the cropped Desk View mode.
 */
@property BOOL requiresSetUpModeCompletion API_AVAILABLE(macos(13.0), macCatalyst(16.1)) API_UNAVAILABLE(ios, tvos, watchos, visionos);

@end

NS_ASSUME_NONNULL_END

#else
#import <AVFCapture/AVCaptureDeskViewApplication.h>
#endif
