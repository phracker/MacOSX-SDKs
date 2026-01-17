//
//  HMHomeManager+Vendor.h
//  HomeKit
//
//  Copyright © 2025 Apple Inc. All rights reserved.
//

#import <HomeKit/HMHomeManager.h>

NS_ASSUME_NONNULL_BEGIN

@class HMAccessory;

@interface HMHomeManager (Vendor)

/*!
 * @brief Finds a vendor HAP accessory based on its Long Term Public Key.
 *
 * @param hapPublicKey The HAP Long Term Public Key of the accessory.
 *                     This has a length of 32 bytes. Refer to the
 *                     HomeKit Accessory Protocol Specification for details.
 *
 * If no matching accessory exists, or if the current process does not have
 * vendor-level access to the matching accessory, the result will be nil.
 *
 * An error will be returned if this method is used before available homes have
 * been retrieved by the HMHomeManager, i.e. before the homeManagerDidUpdateHomes:
 * delegate method has been invoked.
 */
- (void)findVendorAccessoryWithHAPPublicKey:(NSData *)hapPublicKey completionHandler:(void (^)(HMAccessory *_Nullable_result, NSError *_Nullable))completion NS_SWIFT_NAME(findVendorAccessory(hapPublicKey:completionHandler:)) NS_SWIFT_ASYNC_NAME(findVendorAccessory(hapPublicKey:)) API_AVAILABLE(ios(26.1), watchos(26.1), tvos(26.1)) API_UNAVAILABLE(macos);

@end

NS_ASSUME_NONNULL_END
