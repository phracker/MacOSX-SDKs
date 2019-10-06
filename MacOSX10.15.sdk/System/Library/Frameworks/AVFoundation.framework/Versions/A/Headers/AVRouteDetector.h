/*
	File:  AVRouteDetector.h
 
	Framework:  AVFoundation
 
	Copyright 2017 Apple Inc. All rights reserved.
 
 */

#import <AVFoundation/AVBase.h>
#import <Foundation/Foundation.h>

@class AVRouteDetectorInternal;

NS_ASSUME_NONNULL_BEGIN

/*!
 @class		AVRouteDetector
 @abstract	AVRouteDetector detects the presence of media playback routes.
 @discussion	
	If route detection is enabled (it is disabled by default), AVRouteDetector reports whether or not multiple playback routes have been detected. If this is the case, AVKit's AVRoutePickerView can be used to allow users to pick from the set of available routes.
 */

API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0)) API_UNAVAILABLE(watchos)
@interface AVRouteDetector : NSObject
{
@private
	AVRouteDetectorInternal *_routeDetectorInternal;
}

/*!
 @property	routeDetectionEnabled
 @abstract	Whether or not route detection is enabled. The default value is NO.
 @discussion	
	Route detection significantly increases power consumption and must be turned off when it's no longer needed.
 */
@property (getter=isRouteDetectionEnabled) BOOL routeDetectionEnabled;

/*!
 @property	multipleRoutesDetected
 @abstract	This property is YES if, in addition to the local playback route, at least one more playback route has been detected.
 @discussion	
	If multiple route have been detected, AVKit's AVRoutePickerView can be used to allow users to pick from the set of available routes. When the values of this property changes AVRouteDetectorMultipleRoutesDetectedDidChangeNotification is posted.
 */
@property (readonly) BOOL multipleRoutesDetected;

/*!
 @constant	AVRouteDetectorMultipleRoutesDetectedDidChangeNotification
 @abstract	Posted when the value of multipleRoutesDetected changes.
 */
AVF_EXPORT NSNotificationName const AVRouteDetectorMultipleRoutesDetectedDidChangeNotification API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0)) API_UNAVAILABLE(watchos);

@end

NS_ASSUME_NONNULL_END
