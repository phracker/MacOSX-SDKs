//
//  HMCameraSource.h
//  HomeKit
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HomeKit/HMDefines.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/*!
 * @brief Abstract class for source of data from a camera.
 */
HM_EXTERN
NS_SWIFT_SENDABLE
API_AVAILABLE(ios(10.0), watchos(3.0), tvos(10.0), macCatalyst(14.0))
API_UNAVAILABLE(macos)
@interface HMCameraSource : NSObject

/*!
 * @brief Represents the aspect ratio of the camera source, defined as width over height.
 */
@property (readonly) double aspectRatio API_AVAILABLE(ios(14.5), watchos(7.4), tvos(14.5), macos(11.3));

- (instancetype)init NS_DESIGNATED_INITIALIZER API_DEPRECATED("HMCameraSource is a base class for other types. Directly creating them is not supported.", ios(10.0, 10.0), watchos(3.0, 3.0), tvos(10.0, 10.0), macCatalyst(14.0, 14.0));

@end

NS_HEADER_AUDIT_END(nullability, sendability)
