//
//  HMCameraView.h
//  HomeKit
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HomeKit/HMDefines.h>

#if __has_include(<UIKit/UIView.h>)

@class HMCameraSource;

#import <UIKit/UIKit.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/*!
 * @abstract This view can render a camera source.
 */

HM_EXTERN
API_AVAILABLE(ios(10.0), tvos(10.0), macCatalyst(14.0))
API_UNAVAILABLE(watchos)
@interface HMCameraView : UIView

- (instancetype)init;

/*!
 * @brief Represents the camera source.
 */
@property (nullable, nonatomic, strong) HMCameraSource *cameraSource;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#endif
