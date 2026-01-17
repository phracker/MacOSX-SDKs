#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIAccelerometer.h>)
//
//  UIAccelerometer.h
//  UIKit
//
//  Copyright (c) 2007-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>

/* UIAcceleration and UIAccelerometer are deprecated as of iOS 5.0. These classes have been replaced by the Core Motion framework.
 */

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

typedef double UIAccelerationValue API_DEPRECATED("UIAcceleration has been replaced by the CoreMotion framework", ios(2.0, 13.0), tvos(9.0, 13.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

@protocol UIAccelerometerDelegate;

UIKIT_EXTERN API_DEPRECATED("UIAcceleration has been replaced by the CoreMotion framework", ios(2.0, 5.0)) API_UNAVAILABLE(visionos, tvos, watchos) NS_SWIFT_UI_ACTOR
@interface UIAcceleration : NSObject

@property(nonatomic,readonly) NSTimeInterval timestamp;
@property(nonatomic,readonly) UIAccelerationValue x;
@property(nonatomic,readonly) UIAccelerationValue y;
@property(nonatomic,readonly) UIAccelerationValue z;

@end

UIKIT_EXTERN API_DEPRECATED("UIAccelerometer has been replaced by the CoreMotion framework", ios(2.0, 5.0)) API_UNAVAILABLE(visionos, tvos, watchos) NS_SWIFT_UI_ACTOR
@interface UIAccelerometer : NSObject

+ (UIAccelerometer *)sharedAccelerometer;

@property(nonatomic) NSTimeInterval updateInterval; //May be capped at a minimum interval
@property(nullable,nonatomic,weak) id<UIAccelerometerDelegate> delegate;

@end

API_DEPRECATED("UIAcceleration has been replaced by the CoreMotion framework", ios(2.0, 13.0)) API_UNAVAILABLE(visionos, tvos, watchos) NS_SWIFT_UI_ACTOR
@protocol UIAccelerometerDelegate<NSObject>
@optional

- (void)accelerometer:(UIAccelerometer *)accelerometer didAccelerate:(UIAcceleration *)acceleration API_DEPRECATED("", ios(2.0, 5.0)) API_UNAVAILABLE(tvos, visionos, watchos);

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIAccelerometer.h>
#endif
