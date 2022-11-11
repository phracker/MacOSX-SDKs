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

NS_ASSUME_NONNULL_BEGIN

/*!
 * @abstract This view can render a camera source.
 */

HM_EXTERN API_AVAILABLE(ios(10.0), tvos(10.0), macCatalyst(14.0)) API_UNAVAILABLE(watchos)
@interface HMCameraView : UIView

/*!
 * @brief Represents the camera source.
 */
@property (strong, nonatomic, nullable) HMCameraSource *cameraSource;

@end

NS_ASSUME_NONNULL_END

#endif
