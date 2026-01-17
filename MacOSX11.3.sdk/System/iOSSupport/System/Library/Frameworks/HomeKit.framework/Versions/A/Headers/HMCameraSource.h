//
//  HMCameraSource.h
//  HomeKit
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HomeKit/HMDefines.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * @brief Abstract class for source of data from a camera.
 */
HM_EXTERN API_AVAILABLE(ios(10.0), watchos(3.0), tvos(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos)
@interface HMCameraSource : NSObject

/*!
 * @brief Represents the aspect ratio of the camera source, defined as width over height.
 */
@property (readonly) double aspectRatio API_AVAILABLE(ios(14.5), watchos(7.4), tvos(14.5), macos(11.3));

@end

NS_ASSUME_NONNULL_END
