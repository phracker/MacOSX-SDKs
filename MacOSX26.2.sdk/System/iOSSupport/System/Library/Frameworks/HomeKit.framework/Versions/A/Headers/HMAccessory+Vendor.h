//
//  HMAccessory+Vendor.h
//  HomeKit
//
//  Copyright © 2025 Apple Inc. All rights reserved.
//

#import <HomeKit/HMAccessory.h>

NS_ASSUME_NONNULL_BEGIN

@interface HMAccessory ()

/*!
 * @brief Returns YES if the current process is entitled to vendor-level access to this accessory.
 */
@property (nonatomic, readonly, getter=isVendorAccessory) BOOL vendorAccessory API_AVAILABLE(ios(26.1), watchos(26.1), tvos(26.1)) API_UNAVAILABLE(macos);

/*!
 * @brief Returns the HAP Accessory Instance ID, or nil if the receiver does not represent a HAP accessory.
 *
 * Requires vendor-level access to this accessory.
 */
@property (nullable, nonatomic, readonly, copy) NSNumber *HAPInstanceID NS_REFINED_FOR_SWIFT API_AVAILABLE(ios(26.1), watchos(26.1), tvos(26.1)) API_UNAVAILABLE(macos);

@end

NS_ASSUME_NONNULL_END
